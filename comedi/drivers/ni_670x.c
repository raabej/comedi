/*
    module/ni_670x.c
    Hardware driver for NI 670x devices

    COMEDI - Linux Control and Measurement Device Interface
    Copyright (C) 1997-2001 David A. Schleef <ds@schleef.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

/*
	Bart Joris <bjoris@advalvas.be> Last updated on 20/08/2001
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/malloc.h>
#include <linux/errno.h> 
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/init.h>

#include <asm/io.h>

#include <linux/comedidev.h>
#include "mite.h"

#define PCI_VENDOR_ID_NATINST	0x1093

#define AO_VALUE_OFFSET			0x00
#define	AO_CHAN_OFFSET			0x0c
#define	AO_STATUS_OFFSET		0x10
#define AO_CONTROL_OFFSET		0x10
#define	DIO_PORT0_DIR_OFFSET	0x20	
#define	DIO_PORT0_DATA_OFFSET	0x24
#define	DIO_PORT1_DIR_OFFSET	0x28
#define	DIO_PORT1_DATA_OFFSET	0x2c
#define	MISC_STATUS_OFFSET		0x14
#define	MISC_CONTROL_OFFSET		0x14

/* Board description*/

typedef struct ni_670x_board_struct
{
	unsigned short dev_id;
	char *name;
	unsigned short ao_chans;
	unsigned short ao_bits;
}ni_670x_board;
ni_670x_board ni_670x_boards[] = 
{
	{
	dev_id		: 0x2c90,
	name		: "ni 6703",
	ao_chans	: 16,
	ao_bits		: 16,
	},
	{
	dev_id		: 0x0,			/* ????? */
	name		: "ni 6704",
	ao_chans	: 32,
	ao_bits		: 16,
	},
};

static struct pci_device_id ni_670x_pci_table[] __devinitdata = {
	{ PCI_VENDOR_ID_NATINST, 0x2c90, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	//{ PCI_VENDOR_ID_NATINST, 0x2c90, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0 }
};
MODULE_DEVICE_TABLE(pci, ni_670x_pci_table);

#define thisboard ((ni_670x_board *)dev->board_ptr)

typedef struct
{
	struct mite_struct *mite;
	int boardtype;
	int dio;
	lsampl_t ao_readback[32];
}ni_670x_private;

#define devpriv ((ni_670x_private *)dev->private)
#define n_ni_670x_boards (sizeof(ni_670x_boards)/sizeof(ni_670x_boards[0]))

static int ni_670x_attach(comedi_device *dev,comedi_devconfig *it);
static int ni_670x_detach(comedi_device *dev);

static comedi_driver driver_ni_670x=
{
	driver_name:	"ni_670x",
	module:		THIS_MODULE,
	attach:		ni_670x_attach,
	detach:		ni_670x_detach,
};
COMEDI_INITCLEANUP(driver_ni_670x);

static int ni_670x_find_device(comedi_device *dev,int bus,int slot);

static int ni_670x_ao_winsn(comedi_device *dev,comedi_subdevice *s,comedi_insn *insn,lsampl_t *data);
static int ni_670x_ao_rinsn(comedi_device *dev,comedi_subdevice *s,comedi_insn *insn,lsampl_t *data);
static int ni_670x_dio_insn_bits(comedi_device *dev,comedi_subdevice *s,comedi_insn *insn,lsampl_t *data);
static int ni_670x_dio_insn_config(comedi_device *dev,comedi_subdevice *s,comedi_insn *insn,lsampl_t *data);


static int ni_670x_attach(comedi_device *dev,comedi_devconfig *it)
{
	comedi_subdevice *s;
	int ret;
	
	printk("comedi%d: ni_670x: ",dev->minor);

	if((ret=alloc_private(dev,sizeof(ni_670x_private)))<0)
		return ret;
		
	ret=ni_670x_find_device(dev,it->options[0],it->options[1]);
	if(ret<0) return ret;
	
	dev->iobase=mite_setup(devpriv->mite);
	dev->board_name=thisboard->name;
	dev->irq=mite_irq(devpriv->mite);
	printk(" %s",dev->board_name);

	dev->n_subdevices=2;
	
	if(alloc_subdevices(dev)<0)
		return -ENOMEM;

	s=dev->subdevices+0;
	/* analog output subdevice */
	s->type			=	COMEDI_SUBD_AO;
	s->subdev_flags		=	SDF_WRITEABLE;
	s->n_chan		= 	thisboard->ao_chans;
	s->maxdata		=	0xffff;
	s->range_table		=	&range_bipolar10; 
	s->insn_write 		= 	&ni_670x_ao_winsn;
	s->insn_read 		= 	&ni_670x_ao_rinsn;

	s=dev->subdevices+1;
	/* digital i/o subdevice */
	s->type			=	COMEDI_SUBD_DIO;
	s->subdev_flags	=	SDF_READABLE|SDF_WRITEABLE;
	s->n_chan		=	8;
	s->maxdata		=	1;
	s->range_table	=	&range_digital;
	s->insn_bits 	= 	ni_670x_dio_insn_bits;
	s->insn_config 	= 	ni_670x_dio_insn_config;
	
	writel(0x10 ,dev->iobase + MISC_CONTROL_OFFSET);	/* Config of misc registers */	
	writel(0x00 ,dev->iobase + AO_CONTROL_OFFSET);		/* Config of ao registers */
	
	printk("attached\n");

	return 1;
}


static int ni_670x_detach(comedi_device *dev)
{
	printk("comedi%d: ni_670x: remove\n",dev->minor);
	
	if(dev->private && devpriv->mite)
		mite_unsetup(devpriv->mite);
		
	if(dev->irq)
		comedi_free_irq(dev->irq,dev);
	
	return 0;
}




static int ni_670x_ao_winsn(comedi_device *dev,comedi_subdevice *s,comedi_insn *insn,lsampl_t *data)
{
	int i;
	int chan = CR_CHAN(insn->chanspec);

	/* Channel number mapping :
	
	NI 6703/ NI 6704	| NI 6704 Only
	----------------------------------------------------
	vch(0)	:	0	| ich(16)	:	1
	vch(1)	:	2	| ich(17)	:	3
	  .	:	.	|   .			.
	  .	:	.	|   .			.
	  .	:	.	|   .			.
	vch(15)	:	30	| ich(31)	:	31	*/
	
	
	if (chan>15)			
		chan = (chan-15)*2-1;	
	else				
		chan = chan*2;

	for(i=0;i<insn->n;i++)
	{
		writel(chan,dev->iobase + AO_CHAN_OFFSET);		/* First write in channel register which channel to use */
		writel(data[i],dev->iobase + AO_VALUE_OFFSET);  /* write channel value */
		devpriv->ao_readback[chan] = data[i];
	}

	return i;
}

static int ni_670x_ao_rinsn(comedi_device *dev,comedi_subdevice *s,comedi_insn *insn,lsampl_t *data)
{
	int i;
	int chan = CR_CHAN(insn->chanspec);

	for(i=0;i<insn->n;i++)
		data[i] = devpriv->ao_readback[chan];

	return i;
}

static int ni_670x_dio_insn_bits(comedi_device *dev,comedi_subdevice *s,comedi_insn *insn,lsampl_t *data)
{
	if(insn->n!=2)return -EINVAL;

	/* The insn data is a mask in data[0] and the new data
	 * in data[1], each channel cooresponding to a bit. */
	if(data[0])
	{
		s->state &= ~data[0];
		s->state |= data[0]&data[1];
		writel(s->state,dev->iobase + DIO_PORT0_DATA_OFFSET);
	}
	
	/* on return, data[1] contains the value of the digital
	 * input lines. */
	data[1]=readl(dev->iobase + DIO_PORT0_DATA_OFFSET);

	return 2;
}

static int ni_670x_dio_insn_config(comedi_device *dev,comedi_subdevice *s,comedi_insn *insn,lsampl_t *data)
{
	int chan=CR_CHAN(insn->chanspec);
	

	if(insn->n!=1) return -EINVAL;

	if(data[0]==COMEDI_OUTPUT)
	{
		s->io_bits |= 1<<chan;
	}
	else
	{
		s->io_bits &= ~(1<<chan);
	}
	writel(s->io_bits,dev->iobase + DIO_PORT0_DIR_OFFSET);

	return 1;
}

static int ni_670x_find_device(comedi_device *dev,int bus,int slot)
{
	struct mite_struct *mite;
	int i;

	for(mite=mite_devices;mite;mite=mite->next)
	{
		if(mite->used)continue;
		if(bus || slot)
		{
		
#if LINUX_VERSION_CODE < 0x020155
			if(bus!=mite->pci_bus || slot!=PCI_SLOT(mite->pci_device_fn))
				continue;
#else
			if(bus!=mite->pcidev->bus->number || slot!=PCI_SLOT(mite->pcidev->devfn))
				continue;
#endif
		}

		for(i=0;i<n_ni_670x_boards;i++)
		{
			if(mite_device_id(mite)==ni_670x_boards[i].dev_id)
			{
				dev->board_ptr=ni_670x_boards+i;
				devpriv->mite=mite;

				return 0;
			}
		}
	}
	printk("no device found\n");
	mite_list_devices();
	return -EIO;
}
