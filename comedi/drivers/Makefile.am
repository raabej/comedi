

AM_CFLAGS = $(COMEDI_CFLAGS) $(LINUX_CFLAGS)
LINK = $(top_builddir)/modtool -o $@

# mpc8260cpm.ko
# comedi_rt_timer.ko

module_PROGRAMS = 8255.ko \
 adl_pci9111.ko \
 adl_pci9118.ko \
 adv_pci1710.ko \
 amcc_s5933.ko \
 adv_pci_dio.ko \
 amplc_pci230.ko \
 amplc_pc236.ko \
 amplc_pc263.ko \
 cb_pcidas.ko \
 cb_pcidas64.ko \
 cb_pcidda.ko \
 cb_pcimdas.ko \
 cb_pcimdda.ko \
 cb_das16_cs.ko \
 comedi_fc.ko \
 contec_pci_dio.ko \
 daqboard2000.ko \
 das08.ko \
 das08_cs.ko \
 das16.ko \
 das16m1.ko \
 das6402.ko \
 das800.ko \
 das1800.ko \
 dt2801.ko \
 dt2811.ko \
 dt2814.ko \
 dt2815.ko \
 dt2817.ko \
 dt282x.ko \
 dt3000.ko \
 fl512.ko \
 gsc_hpdi.ko \
 ii_pci20kc.ko \
 icp_multi.ko \
 ke_counter.ko \
 me_daq.ko \
 mite.ko \
 multiq3.ko \
 ni_660x.ko \
 ni_670x.ko \
 ni_atmio.ko \
 ni_mio_cs.ko \
 ni_pcimio.ko \
 ni_pcidio.ko \
 ni_6527.ko \
 ni_atmio16d.ko \
 ni_at_a2150.ko \
 ni_labpc.ko \
 ni_labpc_cs.ko \
 ni_daq_dio24.ko \
 ni_at_ao.ko \
 pcm3730.ko \
 pcmad.ko \
 poc.ko \
 pcl711.ko \
 pcl724.ko \
 pcl725.ko \
 pcl726.ko \
 pcl812.ko \
 pcl816.ko \
 pcl818.ko \
 quatech_daqp_cs.ko \
 comedi_parport.ko \
 rtd520.ko \
 rti800.ko \
 rti802.ko \
 skel.ko \
 ssv_dnp.ko \
 comedi_test.ko

8255_ko_SOURCES = 8255.c
adl_pci9111_ko_SOURCES = adl_pci9111.c
adl_pci9118_ko_SOURCES = adl_pci9118.c
adv_pci1710_ko_SOURCES = adv_pci1710.c
amcc_s5933_ko_SOURCES = amcc_s5933.c
adv_pci_dio_ko_SOURCES = adv_pci_dio.c
amplc_pci230_ko_SOURCES = amplc_pci230.c
amplc_pc236_ko_SOURCES = amplc_pc236.c
amplc_pc263_ko_SOURCES = amplc_pc263.c
cb_pcidas_ko_SOURCES = cb_pcidas.c
cb_pcidas64_ko_SOURCES = cb_pcidas64.c
cb_pcidda_ko_SOURCES = cb_pcidda.c
cb_pcimdas_ko_SOURCES = cb_pcimdas.c
cb_pcimdda_ko_SOURCES = cb_pcimdda.c
cb_das16_cs_ko_SOURCES = cb_das16_cs.c
comedi_fc_ko_SOURCES = comedi_fc.c
contec_pci_dio_ko_SOURCES = contec_pci_dio.c
daqboard2000_ko_SOURCES = daqboard2000.c
das08_ko_SOURCES = das08.c
das08_cs_ko_SOURCES = das08_cs.c
das16_ko_SOURCES = das16.c
das16m1_ko_SOURCES = das16m1.c
das6402_ko_SOURCES = das6402.c
das800_ko_SOURCES = das800.c
das1800_ko_SOURCES = das1800.c
dt2801_ko_SOURCES = dt2801.c
dt2811_ko_SOURCES = dt2811.c
dt2814_ko_SOURCES = dt2814.c
dt2815_ko_SOURCES = dt2815.c
dt2817_ko_SOURCES = dt2817.c
dt282x_ko_SOURCES = dt282x.c
dt3000_ko_SOURCES = dt3000.c
fl512_ko_SOURCES = fl512.c
gsc_hpdi_ko_SOURCES = gsc_hpdi.c
ii_pci20kc_ko_SOURCES = ii_pci20kc.c
icp_multi_ko_SOURCES = icp_multi.c
ke_counter_ko_SOURCES = ke_counter.c
me_daq_ko_SOURCES = me_daq.c
mite_ko_SOURCES = mite.c
multiq3_ko_SOURCES = multiq3.c
ni_660x_ko_SOURCES = ni_660x.c
ni_670x_ko_SOURCES = ni_670x.c
ni_atmio_ko_SOURCES = ni_atmio.c
ni_mio_cs_ko_SOURCES = ni_mio_cs.c
ni_pcimio_ko_SOURCES = ni_pcimio.c
ni_pcidio_ko_SOURCES = ni_pcidio.c
ni_6527_ko_SOURCES = ni_6527.c
ni_atmio16d_ko_SOURCES = ni_atmio16d.c
ni_at_a2150_ko_SOURCES = ni_at_a2150.c
ni_labpc_ko_SOURCES = ni_labpc.c
ni_labpc_cs_ko_SOURCES = ni_labpc_cs.c
ni_daq_dio24_ko_SOURCES = ni_daq_dio24.c
ni_at_ao_ko_SOURCES = ni_at_ao.c
pcm3730_ko_SOURCES = pcm3730.c
pcmad_ko_SOURCES = pcmad.c
poc_ko_SOURCES = poc.c
pcl711_ko_SOURCES = pcl711.c
pcl724_ko_SOURCES = pcl724.c
pcl725_ko_SOURCES = pcl725.c
pcl726_ko_SOURCES = pcl726.c
pcl812_ko_SOURCES = pcl812.c
pcl816_ko_SOURCES = pcl816.c
pcl818_ko_SOURCES = pcl818.c
quatech_daqp_cs_ko_SOURCES = quatech_daqp_cs.c
comedi_parport_ko_SOURCES = comedi_parport.c
comedi_rt_timer_ko_SOURCES = comedi_rt_timer.c
rtd520_ko_SOURCES = rtd520.c
rti800_ko_SOURCES = rti800.c
rti802_ko_SOURCES = rti802.c
skel_ko_SOURCES = skel.c
ssv_dnp_ko_SOURCES = ssv_dnp.c
comedi_test_ko_SOURCES = comedi_test.c

mite_ko_CFLAGS = $(AM_CFLAGS) -DEXPORT_SYMTAB
8255_ko_CFLAGS = $(AM_CFLAGS) -DEXPORT_SYMTAB
amcc_s5933_ko_CFLAGS = $(AM_CFLAGS) -DEXPORT_SYMTAB
comedi_fc_ko_CFLAGS = $(AM_CFLAGS) -DEXPORT_SYMTAB
ni_labpc_ko_CFLAGS = $(AM_CFLAGS) -DEXPORT_SYMTAB
das08_ko_CFLAGS = $(AM_CFLAGS) -DEXPORT_SYMTAB
