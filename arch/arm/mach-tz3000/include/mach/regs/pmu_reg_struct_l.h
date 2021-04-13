/*
 * arch/arm/mach-tz3000/include/mach/regs/pmu_reg_struct_l.h
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _PMU_REG_STRUCT_L_H
#define _PMU_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // PowerSwitchOn_TOP Register
struct PMU_POWERSWITCHON_TOP {
	unsigned int PSW_TOP:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // PowerSwitchOn_CPU Register
struct PMU_POWERSWITCHON_CPU {
	unsigned int PSW_CPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // PowerSwitchOn_GPU Register
struct PMU_POWERSWITCHON_GPU {
	unsigned int PSW_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // PowerSwitchOn_VIDEO Register
struct PMU_POWERSWITCHON_VIDEO {
	unsigned int PSW_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // PowerSwitchOff_TOP Register
struct PMU_POWERSWITCHOFF_TOP {
	unsigned int PSW_TOP:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // PowerSwitchOff_CPU Register
struct PMU_POWERSWITCHOFF_CPU {
	unsigned int PSW_CPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // PowerSwitchOff_GPU Register
struct PMU_POWERSWITCHOFF_GPU {
	unsigned int PSW_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // PowerSwitchOff_VIDEO Register
struct PMU_POWERSWITCHOFF_VIDEO {
	unsigned int PSW_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // InIsoOn_GPU Register
struct PMU_INISOON_GPU {
	unsigned int InIso_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // InIsoOn_VIDEO Register
struct PMU_INISOON_VIDEO {
	unsigned int InIso_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // InIsoOff_GPU Register
struct PMU_INISOOFF_GPU {
	unsigned int InIso_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // InIsoOff_VIDEO Register
struct PMU_INISOOFF_VIDEO {
	unsigned int InIso_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // OutIsoOn_TOP Register
struct PMU_OUTISOON_TOP {
	unsigned int OutIso_TOP:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // OutIsoOn_CPU Register
struct PMU_OUTISOON_CPU {
	unsigned int OutIso_CPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // OutIsoOn_GPU Register
struct PMU_OUTISOON_GPU {
	unsigned int OutIso_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // OutIsoOn_VIDEO Register
struct PMU_OUTISOON_VIDEO {
	unsigned int OutIso_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // OutIsoOff_TOP Register
struct PMU_OUTISOOFF_TOP {
	unsigned int OutIso_TOP:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // OutIsoOff_CPU Register
struct PMU_OUTISOOFF_CPU {
	unsigned int OutIso_CPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // OutIsoOff_GPU Register
struct PMU_OUTISOOFF_GPU {
	unsigned int OutIso_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // OutIsoOff_VIDEO Register
struct PMU_OUTISOOFF_VIDEO {
	unsigned int OutIso_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOn_westpierSS_0 Register
struct PMU_CLOCKGATINGON_WESTPIERSS_0 {
	unsigned int CG_wclk_westpier_mpier0:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclk_westpier_mpier1:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOn_cpuSS_0 Register
struct PMU_CLOCKGATINGON_CPUSS_0 {
	unsigned int CG_coreclk:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclk_cpu:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOn_periSS_0 Register
struct PMU_CLOCKGATINGON_PERISS_0 {
	unsigned int CG_wclkdiv2_peri_ppier:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv2_peri_gdmac:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv2_mbox:1;		// [16]
	unsigned int reserved3:7;		// [23:17]
	unsigned int CG_wclkdiv4_peri_timer:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // ClockGatingOn_periSS_1 Register
struct PMU_CLOCKGATINGON_PERISS_1 {
	unsigned int CG_wclkdiv2_peri_pwm:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv16_peri_adc:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv2_peri_gpio0:1;		// [16]
	unsigned int reserved3:3;		// [19:17]
	unsigned int CG_wclkdiv2_peri_gpio1:1;		// [20]
	unsigned int reserved4:3;		// [23:21]
	unsigned int CG_wclkdiv4_peri_i2cp:1;		// [24]
	unsigned int reserved5:7;		// [31:25]
};
 // ClockGatingOn_periSS_2 Register
struct PMU_CLOCKGATINGON_PERISS_2 {
	unsigned int CG_wclkdiv2_peri_i2si0:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_wclkdiv2_peri_i2si1:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_wclkdiv2_peri_i2so0:1;		// [8]
	unsigned int reserved3:3;		// [11:9]
	unsigned int CG_wclkdiv2_peri_i2so1:1;		// [12]
	unsigned int reserved4:3;		// [15:13]
	unsigned int CG_wclkdiv2_peri_i2sc0:1;		// [16]
	unsigned int reserved5:7;		// [23:17]
	unsigned int CG_amclk_i2s:1;		// [24]
	unsigned int reserved6:3;		// [27:25]
	unsigned int CG_io_AMCLKO_o:1;		// [28]
	unsigned int reserved7:3;		// [31:29]
};
 // ClockGatingOn_periSS_3 Register
struct PMU_CLOCKGATINGON_PERISS_3 {
	unsigned int CG_wclkdiv2_spib0:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_spib0cclk:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_wclkdiv2_peri_spims0:1;		// [8]
	unsigned int reserved3:7;		// [15:9]
	unsigned int CG_wclkdiv2_spib1:1;		// [16]
	unsigned int reserved4:3;		// [19:17]
	unsigned int CG_spib1cclk:1;		// [20]
	unsigned int reserved5:3;		// [23:21]
	unsigned int CG_wclkdiv2_peri_spims1:1;		// [24]
	unsigned int reserved6:7;		// [31:25]
};
 // ClockGatingOn_periSS_4 Register
struct PMU_CLOCKGATINGON_PERISS_4 {
	unsigned int CG_wclkdiv4_peri_uart:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_uart0clk:1;		// [8]
	unsigned int reserved2:3;		// [11:9]
	unsigned int CG_uart1clk:1;		// [12]
	unsigned int reserved3:3;		// [15:13]
	unsigned int CG_uart2clk:1;		// [16]
	unsigned int reserved4:3;		// [19:17]
	unsigned int CG_uart3clk:1;		// [20]
	unsigned int reserved5:3;		// [23:21]
	unsigned int CG_uart4clk:1;		// [24]
	unsigned int reserved6:7;		// [31:25]
};
 // ClockGatingOn_dramcSS_0 Register
struct PMU_CLOCKGATINGON_DRAMCSS_0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int CG_wclk_dramc:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOn_mbootSS_0 Register
struct PMU_CLOCKGATINGON_MBOOTSS_0 {
	unsigned int CG_wclkdiv2_mboot:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOn_dbgmonSS_0 Register
struct PMU_CLOCKGATINGON_DBGMONSS_0 {
	unsigned int CG_wclkdiv2_dbgmon:1;		// [0]
	unsigned int reserved:15;		// [15:1]
	unsigned int CG_mclk_dbgmon:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // ClockGatingOn_eastpierSS_0 Register
struct PMU_CLOCKGATINGON_EASTPIERSS_0 {
	unsigned int CG_eclk_eastpier:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_gclkdivN_gpu_eastpier:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_rclk_eastpier:1;		// [16]
	unsigned int reserved3:7;		// [23:17]
	unsigned int CG_vclkdivN_eastpier:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // ClockGatingOn_hsioSS_0 Register
struct PMU_CLOCKGATINGON_HSIOSS_0 {
	unsigned int CG_uclk_usb2:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_eclkdiv2_hsio_usb2dc:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_uclk_usbss:1;		// [8]
	unsigned int CG_eclkdiv2_hsio_usb3pcie:1;		// [9]
	unsigned int reserved3:6;		// [15:10]
	unsigned int CG_eclkdiv8_hsio_usb3hc:1;		// [16]
	unsigned int CG_eclk_hsio_usb3hc:1;		// [17]
	unsigned int reserved4:6;		// [23:18]
	unsigned int CG_eclk_hsio_pcie_axi:1;		// [24]
	unsigned int CG_eclk_hsio_pcie_apb:1;		// [25]
	unsigned int reserved5:6;		// [31:26]
};
 // ClockGatingOn_dispifSS_0 Register
struct PMU_CLOCKGATINGON_DISPIFSS_0 {
	unsigned int CG_eclk_dispif:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_dclk:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOn_camifSS_0 Register
struct PMU_CLOCKGATINGON_CAMIFSS_0 {
	unsigned int CG_eclk_camif_csirx0:1;		// [0]
	unsigned int CG_eclk_camif_csirx1:1;		// [1]
	unsigned int CG_eclk_camif_csirx2:1;		// [2]
	unsigned int CG_eclk_camif_csirx3:1;		// [3]
	unsigned int reserved:4;		// [7:4]
	unsigned int CG_eclk_camif_cvdmac_ccbus_dphyrx:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOn_vcodecSS_0 Register
struct PMU_CLOCKGATINGON_VCODECSS_0 {
	unsigned int CG_vclkdivN_bap:1;		// [0]
	unsigned int CG_vclkdivN_bap_avc:1;		// [1]
	unsigned int reserved:6;		// [7:2]
	unsigned int CG_vclkdivN_vdp:1;		// [8]
	unsigned int CG_vclkdivN_vdp_avc:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int CG_vclkdivN_vp4:1;		// [16]
	unsigned int CG_vclkdivN_vp4_avc:1;		// [17]
	unsigned int reserved3:6;		// [23:18]
	unsigned int CG_vclkdivN_vdime:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // ClockGatingOn_vconvSS_0 Register
struct PMU_CLOCKGATINGON_VCONVSS_0 {
	unsigned int CG_eclk_vconv:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOn_irecogSS_0 Register
struct PMU_CLOCKGATINGON_IRECOGSS_0 {
	unsigned int CG_rclk_pym_cnt:1;		// [0]
	unsigned int CG_rclk_pym_vdm:1;		// [1]
	unsigned int CG_rclk_pym_y1:1;		// [2]
	unsigned int CG_rclk_pym_y2:1;		// [3]
	unsigned int CG_rclk_pym_y3:1;		// [4]
	unsigned int CG_rclk_pym_y4:1;		// [5]
	unsigned int CG_rclk_pym_c1:1;		// [6]
	unsigned int CG_rclk_pym_c2:1;		// [7]
	unsigned int CG_rclk_pym_c3:1;		// [8]
	unsigned int CG_rclk_pym_c4:1;		// [9]
	unsigned int CG_rclk_sharedbus:1;		// [10]
	unsigned int CG_rclk_affine:1;		// [11]
	unsigned int CG_rclk_histgram:1;		// [12]
	unsigned int CG_rclk_match:1;		// [13]
	unsigned int CG_rclk_cohog0:1;		// [14]
	unsigned int CG_rclk_cohog1:1;		// [15]
	unsigned int CG_fclk:1;		// [16]
	unsigned int CG_eclk_irecog:1;		// [17]
	unsigned int CG_rclkdiv2_affine:1;		// [18]
	unsigned int CG_rclkdiv2_histgram:1;		// [19]
	unsigned int CG_rclkdiv2_match:1;		// [20]
	unsigned int CG_rclkdiv2_cohog0:1;		// [21]
	unsigned int CG_rclkdiv2_cohog1:1;		// [22]
	unsigned int reserved:9;		// [31:23]
};
 // ClockGatingOn_gpuSS_0 Register
struct PMU_CLOCKGATINGON_GPUSS_0 {
	unsigned int CG_gclkdivN_gpu:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOn_econfSS_0 Register
struct PMU_CLOCKGATINGON_ECONFSS_0 {
	unsigned int CG_eclkdiv2_econf:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOn_etherSS_0 Register
struct PMU_CLOCKGATINGON_ETHERSS_0 {
	unsigned int CG_eclk_ether:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOn_emmcSS_0 Register
struct PMU_CLOCKGATINGON_EMMCSS_0 {
	unsigned int CG_eclk_emmca_axi:1;		// [0]
	unsigned int CG_eclk_emmca_xin:1;		// [1]
	unsigned int reserved:6;		// [7:2]
	unsigned int CG_eclk_emmcb_axi:1;		// [8]
	unsigned int CG_eclk_emmcb_xin:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int CG_eclk_emmcc_axi:1;		// [16]
	unsigned int CG_eclk_emmcc_xin:1;		// [17]
	unsigned int reserved3:14;		// [31:18]
};
 // ClockGatingOn_nandcSS_0 Register
struct PMU_CLOCKGATINGON_NANDCSS_0 {
	unsigned int CG_eclkdiv2_nandc:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_eclkdiv2_nandc_m0_m0n:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOff_westpierSS_0 Register
struct PMU_CLOCKGATINGOFF_WESTPIERSS_0 {
	unsigned int CG_wclk_westpier_mpier0:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclk_westpier_mpier1:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOff_cpuSS_0 Register
struct PMU_CLOCKGATINGOFF_CPUSS_0 {
	unsigned int CG_coreclk:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclk_cpu:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOff_periSS_0 Register
struct PMU_CLOCKGATINGOFF_PERISS_0 {
	unsigned int CG_wclkdiv2_peri_ppier:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv2_peri_gdmac:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv2_mbox:1;		// [16]
	unsigned int reserved3:7;		// [23:17]
	unsigned int CG_wclkdiv4_peri_timer:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // ClockGatingOff_periSS_1 Register
struct PMU_CLOCKGATINGOFF_PERISS_1 {
	unsigned int CG_wclkdiv2_peri_pwm:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv16_peri_adc:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv2_peri_gpio0:1;		// [16]
	unsigned int reserved3:3;		// [19:17]
	unsigned int CG_wclkdiv2_peri_gpio1:1;		// [20]
	unsigned int reserved4:3;		// [23:21]
	unsigned int CG_wclkdiv4_peri_i2cp:1;		// [24]
	unsigned int reserved5:7;		// [31:25]
};
 // ClockGatingOff_periSS_2 Register
struct PMU_CLOCKGATINGOFF_PERISS_2 {
	unsigned int CG_wclkdiv2_peri_i2si0:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_wclkdiv2_peri_i2si1:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_wclkdiv2_peri_i2so0:1;		// [8]
	unsigned int reserved3:3;		// [11:9]
	unsigned int CG_wclkdiv2_peri_i2so1:1;		// [12]
	unsigned int reserved4:3;		// [15:13]
	unsigned int CG_wclkdiv2_peri_i2sc0:1;		// [16]
	unsigned int reserved5:7;		// [23:17]
	unsigned int CG_amclk_i2s:1;		// [24]
	unsigned int reserved6:3;		// [27:25]
	unsigned int CG_io_AMCLKO_o:1;		// [28]
	unsigned int reserved7:3;		// [31:29]
};
 // ClockGatingOff_periSS_3 Register
struct PMU_CLOCKGATINGOFF_PERISS_3 {
	unsigned int CG_wclkdiv2_spib0:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_spib0cclk:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_wclkdiv2_peri_spims0:1;		// [8]
	unsigned int reserved3:7;		// [15:9]
	unsigned int CG_wclkdiv2_spib1:1;		// [16]
	unsigned int reserved4:3;		// [19:17]
	unsigned int CG_spib1cclk:1;		// [20]
	unsigned int reserved5:3;		// [23:21]
	unsigned int CG_wclkdiv2_peri_spims1:1;		// [24]
	unsigned int reserved6:7;		// [31:25]
};
 // ClockGatingOff_periSS_4 Register
struct PMU_CLOCKGATINGOFF_PERISS_4 {
	unsigned int CG_wclkdiv4_peri_uart:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_uart0clk:1;		// [8]
	unsigned int reserved2:3;		// [11:9]
	unsigned int CG_uart1clk:1;		// [12]
	unsigned int reserved3:3;		// [15:13]
	unsigned int CG_uart2clk:1;		// [16]
	unsigned int reserved4:3;		// [19:17]
	unsigned int CG_uart3clk:1;		// [20]
	unsigned int reserved5:3;		// [23:21]
	unsigned int CG_uart4clk:1;		// [24]
	unsigned int reserved6:7;		// [31:25]
};
 // ClockGatingOff_dramcSS_0 Register
struct PMU_CLOCKGATINGOFF_DRAMCSS_0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int CG_wclk_dramc:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOff_mbootSS_0 Register
struct PMU_CLOCKGATINGOFF_MBOOTSS_0 {
	unsigned int CG_wclkdiv2_mboot:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOff_dbgmonSS_0 Register
struct PMU_CLOCKGATINGOFF_DBGMONSS_0 {
	unsigned int CG_wclkdiv2_dbgmon:1;		// [0]
	unsigned int reserved:15;		// [15:1]
	unsigned int CG_mclk_dbgmon:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // ClockGatingOff_eastpierSS_0 Register
struct PMU_CLOCKGATINGOFF_EASTPIERSS_0 {
	unsigned int CG_eclk_eastpier:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_gclkdivN_gpu_eastpier:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_rclk_eastpier:1;		// [16]
	unsigned int reserved3:7;		// [23:17]
	unsigned int CG_vclkdivN_eastpier:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // ClockGatingOff_hsioSS_0 Register
struct PMU_CLOCKGATINGOFF_HSIOSS_0 {
	unsigned int CG_uclk_usb2:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_eclkdiv2_hsio_usb2dc:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_uclk_usbss:1;		// [8]
	unsigned int CG_eclkdiv2_hsio_usb3pcie:1;		// [9]
	unsigned int reserved3:6;		// [15:10]
	unsigned int CG_eclkdiv8_hsio_usb3hc:1;		// [16]
	unsigned int CG_eclk_hsio_usb3hc:1;		// [17]
	unsigned int reserved4:6;		// [23:18]
	unsigned int CG_eclk_hsio_pcie_axi:1;		// [24]
	unsigned int CG_eclk_hsio_pcie_apb:1;		// [25]
	unsigned int reserved5:6;		// [31:26]
};
 // ClockGatingOff_dispifSS_0 Register
struct PMU_CLOCKGATINGOFF_DISPIFSS_0 {
	unsigned int CG_eclk_dispif:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_dclk:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOff_camifSS_0 Register
struct PMU_CLOCKGATINGOFF_CAMIFSS_0 {
	unsigned int CG_eclk_camif_csirx0:1;		// [0]
	unsigned int CG_eclk_camif_csirx1:1;		// [1]
	unsigned int CG_eclk_camif_csirx2:1;		// [2]
	unsigned int CG_eclk_camif_csirx3:1;		// [3]
	unsigned int reserved:4;		// [7:4]
	unsigned int CG_eclk_camif_cvdmac_ccbus_dphyrx:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOff_vcodecSS_0 Register
struct PMU_CLOCKGATINGOFF_VCODECSS_0 {
	unsigned int CG_vclkdivN_bap:1;		// [0]
	unsigned int CG_vclkdivN_bap_avc:1;		// [1]
	unsigned int reserved:6;		// [7:2]
	unsigned int CG_vclkdivN_vdp:1;		// [8]
	unsigned int CG_vclkdivN_vdp_avc:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int CG_vclkdivN_vp4:1;		// [16]
	unsigned int CG_vclkdivN_vp4_avc:1;		// [17]
	unsigned int reserved3:6;		// [23:18]
	unsigned int CG_vclkdivN_vdime:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // ClockGatingOff_vconvSS_0 Register
struct PMU_CLOCKGATINGOFF_VCONVSS_0 {
	unsigned int CG_eclk_vconv:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOff_irecogSS_0 Register
struct PMU_CLOCKGATINGOFF_IRECOGSS_0 {
	unsigned int CG_rclk_pym_cnt:1;		// [0]
	unsigned int CG_rclk_pym_vdm:1;		// [1]
	unsigned int CG_rclk_pym_y1:1;		// [2]
	unsigned int CG_rclk_pym_y2:1;		// [3]
	unsigned int CG_rclk_pym_y3:1;		// [4]
	unsigned int CG_rclk_pym_y4:1;		// [5]
	unsigned int CG_rclk_pym_c1:1;		// [6]
	unsigned int CG_rclk_pym_c2:1;		// [7]
	unsigned int CG_rclk_pym_c3:1;		// [8]
	unsigned int CG_rclk_pym_c4:1;		// [9]
	unsigned int CG_rclk_sharedbus:1;		// [10]
	unsigned int CG_rclk_affine:1;		// [11]
	unsigned int CG_rclk_histgram:1;		// [12]
	unsigned int CG_rclk_match:1;		// [13]
	unsigned int CG_rclk_cohog0:1;		// [14]
	unsigned int CG_rclk_cohog1:1;		// [15]
	unsigned int CG_fclk:1;		// [16]
	unsigned int CG_eclk_irecog:1;		// [17]
	unsigned int CG_rclkdiv2_affine:1;		// [18]
	unsigned int CG_rclkdiv2_histgram:1;		// [19]
	unsigned int CG_rclkdiv2_match:1;		// [20]
	unsigned int CG_rclkdiv2_cohog0:1;		// [21]
	unsigned int CG_rclkdiv2_cohog1:1;		// [22]
	unsigned int reserved:9;		// [31:23]
};
 // ClockGatingOff_gpuSS_0 Register
struct PMU_CLOCKGATINGOFF_GPUSS_0 {
	unsigned int CG_gclkdivN_gpu:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOff_econfSS_0 Register
struct PMU_CLOCKGATINGOFF_ECONFSS_0 {
	unsigned int CG_eclkdiv2_econf:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOff_etherSS_0 Register
struct PMU_CLOCKGATINGOFF_ETHERSS_0 {
	unsigned int CG_eclk_ether:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOff_emmcSS_0 Register
struct PMU_CLOCKGATINGOFF_EMMCSS_0 {
	unsigned int CG_eclk_emmca_axi:1;		// [0]
	unsigned int CG_eclk_emmca_xin:1;		// [1]
	unsigned int reserved:6;		// [7:2]
	unsigned int CG_eclk_emmcb_axi:1;		// [8]
	unsigned int CG_eclk_emmcb_xin:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int CG_eclk_emmcc_axi:1;		// [16]
	unsigned int CG_eclk_emmcc_xin:1;		// [17]
	unsigned int reserved3:14;		// [31:18]
};
 // ClockGatingOff_nandcSS_0 Register
struct PMU_CLOCKGATINGOFF_NANDCSS_0 {
	unsigned int CG_eclkdiv2_nandc:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_eclkdiv2_nandc_m0_m0n:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // SoftResetOn_westpierSS_0 Register
struct PMU_SOFTRESETON_WESTPIERSS_0 {
	unsigned int SRST_mixedwrst_westpier_mpier0_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_mixedwrst_westpier_mpier1_n:1;		// [8]
	unsigned int SRST_mixedwrst_westpier_mpier1IF_n:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int SRST_mixeddramcrst_dramcIF_n:1;		// [16]
	unsigned int SRST_wrst_westpier_mpier1_n:1;		// [17]
	unsigned int SRST_mixedwrst_westpier_drammx_n:1;		// [18]
	unsigned int SRST_asyncdsgaterst_n:1;		// [19]
	unsigned int reserved3:12;		// [31:20]
};
 // SoftResetOn_cpuSS_0 Register
struct PMU_SOFTRESETON_CPUSS_0 {
	unsigned int SRST_asynccorerst_smpgn_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrst_cpu_n:1;		// [8]
	unsigned int SRST_asynccorerst_l2c_n:1;		// [9]
	unsigned int SRST_asynccorerst_scu_n:1;		// [10]
	unsigned int reserved2:1;		// [11]
	unsigned int SRST_asynccorerst_wd0_n:1;		// [12]
	unsigned int SRST_asynccorerst_wd1_n:1;		// [13]
	unsigned int reserved3:2;		// [15:14]
	unsigned int SRST_asynccorerst_neon0_n:1;		// [16]
	unsigned int SRST_asynccorerst_neon1_n:1;		// [17]
	unsigned int reserved4:2;		// [19:18]
	unsigned int SRST_asynccorerst_cpu0_n:1;		// [20]
	unsigned int SRST_asynccorerst_cpu1_n:1;		// [21]
	unsigned int reserved5:10;		// [31:22]
};
 // SoftResetOn_cpuSS_1 Register
struct PMU_SOFTRESETON_CPUSS_1 {
	unsigned int SRST_asynccorerst_coresight_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asynccorerst_dbg0_n:1;		// [8]
	unsigned int SRST_asynccorerst_dbg1_n:1;		// [9]
	unsigned int reserved2:22;		// [31:10]
};
 // SoftResetOn_periSS_0 Register
struct PMU_SOFTRESETON_PERISS_0 {
	unsigned int SRST_mixedwrstdiv2_peri_ppier_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv2_peri_gdmac_n:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv2_mbox_n:1;		// [16]
	unsigned int reserved3:7;		// [23:17]
	unsigned int SRST_asyncwrstdiv4_peri_timer_n:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // SoftResetOn_periSS_1 Register
struct PMU_SOFTRESETON_PERISS_1 {
	unsigned int SRST_asyncwrstdiv2_peri_pwm_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv16_adc_n:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv2_peri_gpio0_n:1;		// [16]
	unsigned int reserved3:3;		// [19:17]
	unsigned int SRST_asyncwrstdiv2_peri_gpio1_n:1;		// [20]
	unsigned int reserved4:3;		// [23:21]
	unsigned int SRST_asyncwrstdiv4_i2cp_n:1;		// [24]
	unsigned int reserved5:7;		// [31:25]
};
 // SoftResetOn_periSS_2 Register
struct PMU_SOFTRESETON_PERISS_2 {
	unsigned int SRST_asyncwrstdiv2_peri_i2si0_n:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_asyncwrstdiv2_peri_i2si1_n:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_asyncwrstdiv2_peri_i2so0_n:1;		// [8]
	unsigned int reserved3:3;		// [11:9]
	unsigned int SRST_asyncwrstdiv2_peri_i2so1_n:1;		// [12]
	unsigned int reserved4:3;		// [15:13]
	unsigned int SRST_asyncwrstdiv2_peri_i2sc0_n:1;		// [16]
	unsigned int reserved5:15;		// [31:17]
};
 // SoftResetOn_periSS_3 Register
struct PMU_SOFTRESETON_PERISS_3 {
	unsigned int SRST_wrstdiv2_peri_spib0_n:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_spib0crst_n:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_asyncwrstdiv2_peri_spims0_n:1;		// [8]
	unsigned int reserved3:7;		// [15:9]
	unsigned int SRST_wrstdiv2_peri_spib1_n:1;		// [16]
	unsigned int reserved4:3;		// [19:17]
	unsigned int SRST_spib1crst_n:1;		// [20]
	unsigned int reserved5:3;		// [23:21]
	unsigned int SRST_asyncwrstdiv2_peri_spims1_n:1;		// [24]
	unsigned int reserved6:7;		// [31:25]
};
 // SoftResetOn_periSS_4 Register
struct PMU_SOFTRESETON_PERISS_4 {
	unsigned int SRST_asyncwrstdiv4_peri_uart_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncuart0rst_n:1;		// [8]
	unsigned int reserved2:3;		// [11:9]
	unsigned int SRST_asyncuart1rst_n:1;		// [12]
	unsigned int reserved3:3;		// [15:13]
	unsigned int SRST_asyncuart2rst_n:1;		// [16]
	unsigned int reserved4:3;		// [19:17]
	unsigned int SRST_asyncuart3rst_n:1;		// [20]
	unsigned int reserved5:3;		// [23:21]
	unsigned int SRST_asyncuart4rst_n:1;		// [24]
	unsigned int reserved6:7;		// [31:25]
};
 // SoftResetOn_dramcSS_0 Register
struct PMU_SOFTRESETON_DRAMCSS_0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int SRST_asyncwrst_dramc_n:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // SoftResetOn_mbootSS_0 Register
struct PMU_SOFTRESETON_MBOOTSS_0 {
	unsigned int SRST_asyncwrstdiv2_mboot_n:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SoftResetOn_dbgmonSS_0 Register
struct PMU_SOFTRESETON_DBGMONSS_0 {
	unsigned int SRST_wrstdiv2_dbgmon_n:1;		// [0]
	unsigned int reserved:15;		// [15:1]
	unsigned int SRST_mrst_dbgmon_n:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // SoftResetOn_eastpierSS_0 Register
struct PMU_SOFTRESETON_EASTPIERSS_0 {
	unsigned int SRST_mixederst_eastpier_n:1;		// [0]
	unsigned int SRST_mixederst_epierIFgpier_n:1;		// [1]
	unsigned int SRST_mixederst_epierIFipier_n:1;		// [2]
	unsigned int SRST_mixederst_epierIFvpier_n:1;		// [3]
	unsigned int reserved:4;		// [7:4]
	unsigned int SRST_mixedgrstdivN_eastpier_n:1;		// [8]
	unsigned int SRST_mixedgrstdivN_gpierIFepier_n:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int SRST_mixedrrst_eastpier_n:1;		// [16]
	unsigned int SRST_mixedrrst_ipierIFepier_n:1;		// [17]
	unsigned int reserved3:6;		// [23:18]
	unsigned int SRST_mixedvrstdivN_eastpier_n:1;		// [24]
	unsigned int SRST_mixedvrstdivN_vpierIFepier_n:1;		// [25]
	unsigned int reserved4:6;		// [31:26]
};
 // SoftResetOn_hsioSS_0 Register
struct PMU_SOFTRESETON_HSIOSS_0 {
	unsigned int SRST_asyncurst_usb2_n:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_asyncerstdiv2_hsio_usb2dc_n:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_asyncurst_usbSS_n:1;		// [8]
	unsigned int SRST_asyncerstdiv2_hsio_usb3pcie_n:1;		// [9]
	unsigned int reserved3:6;		// [15:10]
	unsigned int SRST_asyncerstdiv8_hsio_usb3hc_n:1;		// [16]
	unsigned int SRST_asyncerst_hsio_usb3hc_n:1;		// [17]
	unsigned int reserved4:6;		// [23:18]
	unsigned int SRST_asyncerst_hsio_pcie_axi_n:1;		// [24]
	unsigned int SRST_asyncerst_hsio_pcie_apb_n:1;		// [25]
	unsigned int reserved5:6;		// [31:26]
};
 // SoftResetOn_dispifSS_0 Register
struct PMU_SOFTRESETON_DISPIFSS_0 {
	unsigned int SRST_asyncerst_dispif_n:1;		// [0]
	unsigned int SRST_erst_dispif_n:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // SoftResetOn_camifSS_0 Register
struct PMU_SOFTRESETON_CAMIFSS_0 {
	unsigned int SRST_asyncerst_camif_csirx0_n:1;		// [0]
	unsigned int SRST_asyncerst_camif_csirx1_n:1;		// [1]
	unsigned int SRST_asyncerst_camif_csirx2_n:1;		// [2]
	unsigned int SRST_asyncerst_camif_csirx3_n:1;		// [3]
	unsigned int reserved:4;		// [7:4]
	unsigned int SRST_erst_camif_cvdmac_n:1;		// [8]
	unsigned int SRST_erst_camif_ccbus_n:1;		// [9]
	unsigned int SRST_asyncerst_camif_dphyrx_n:1;		// [10]
	unsigned int reserved2:21;		// [31:11]
};
 // SoftResetOn_vcodecSS_0 Register
struct PMU_SOFTRESETON_VCODECSS_0 {
	unsigned int SRST_vrstdivN_bap_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_vrstdivN_vdp_n:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_vrstdivN_vp4_n:1;		// [16]
	unsigned int reserved3:7;		// [23:17]
	unsigned int SRST_vrstdivN_vdime_n:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // SoftResetOn_vconvSS_0 Register
struct PMU_SOFTRESETON_VCONVSS_0 {
	unsigned int SRST_asyncerst_vconv_n:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SoftResetOn_irecogSS_0 Register
struct PMU_SOFTRESETON_IRECOGSS_0 {
	unsigned int SRST_rrst_pym_cnt_n:1;		// [0]
	unsigned int SRST_rrst_pym_vdm_n:1;		// [1]
	unsigned int SRST_rrst_pym_y1_n:1;		// [2]
	unsigned int SRST_rrst_pym_y2_n:1;		// [3]
	unsigned int SRST_rrst_pym_y3_n:1;		// [4]
	unsigned int SRST_rrst_pym_y4_n:1;		// [5]
	unsigned int SRST_rrst_pym_c1_n:1;		// [6]
	unsigned int SRST_rrst_pym_c2_n:1;		// [7]
	unsigned int SRST_rrst_pym_c3_n:1;		// [8]
	unsigned int SRST_rrst_pym_c4_n:1;		// [9]
	unsigned int SRST_rrst_sharedbus_n:1;		// [10]
	unsigned int SRST_asyncrrst_affine_n:1;		// [11]
	unsigned int SRST_asyncrrst_histgram_n:1;		// [12]
	unsigned int SRST_asyncrrst_match_n:1;		// [13]
	unsigned int SRST_asyncrrst_cohog0_n:1;		// [14]
	unsigned int SRST_asyncrrst_cohog1_n:1;		// [15]
	unsigned int SRST_asyncfrst_n:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // SoftResetOn_gpuSS_0 Register
struct PMU_SOFTRESETON_GPUSS_0 {
	unsigned int SRST_mixedgrstdivN_gpu_n:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SoftResetOn_econfSS_0 Register
struct PMU_SOFTRESETON_ECONFSS_0 {
	unsigned int SRST_asyncerstdiv2_econf_n:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SoftResetOn_etherSS_0 Register
struct PMU_SOFTRESETON_ETHERSS_0 {
	unsigned int SRST_erst_ether_n:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_asyncethrst_n:1;		// [4]
	unsigned int reserved2:27;		// [31:5]
};
 // SoftResetOn_emmcSS_0 Register
struct PMU_SOFTRESETON_EMMCSS_0 {
	unsigned int SRST_asyncerst_emmca_axi_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncerst_emmcb_axi_n:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncerst_emmcc_axi_n:1;		// [16]
	unsigned int reserved3:15;		// [31:17]
};
 // SoftResetOn_nandcSS_0 Register
struct PMU_SOFTRESETON_NANDCSS_0 {
	unsigned int SRST_asyncerstdiv2_nandc_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncerstdiv2_nandc_m0_n:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // SoftResetOff_westpierSS_0 Register
struct PMU_SOFTRESETOFF_WESTPIERSS_0 {
	unsigned int SRST_mixedwrst_westpier_mpier0_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_mixedwrst_westpier_mpier1_n:1;		// [8]
	unsigned int SRST_mixedwrst_westpier_mpier1IF_n:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int SRST_mixeddramcrst_dramcIF_n:1;		// [16]
	unsigned int SRST_wrst_westpier_mpier1_n:1;		// [17]
	unsigned int SRST_mixedwrst_westpier_drammx_n:1;		// [18]
	unsigned int SRST_asyncdsgaterst_n:1;		// [19]
	unsigned int reserved3:12;		// [31:20]
};
 // SoftResetOff_cpuSS_0 Register
struct PMU_SOFTRESETOFF_CPUSS_0 {
	unsigned int SRST_asynccorerst_smpgn_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrst_cpu_n:1;		// [8]
	unsigned int SRST_asynccorerst_l2c_n:1;		// [9]
	unsigned int SRST_asynccorerst_scu_n:1;		// [10]
	unsigned int reserved2:1;		// [11]
	unsigned int SRST_asynccorerst_wd0_n:1;		// [12]
	unsigned int SRST_asynccorerst_wd1_n:1;		// [13]
	unsigned int reserved3:2;		// [15:14]
	unsigned int SRST_asynccorerst_neon0_n:1;		// [16]
	unsigned int SRST_asynccorerst_neon1_n:1;		// [17]
	unsigned int reserved4:2;		// [19:18]
	unsigned int SRST_asynccorerst_cpu0_n:1;		// [20]
	unsigned int SRST_asynccorerst_cpu1_n:1;		// [21]
	unsigned int reserved5:10;		// [31:22]
};
 // SoftResetOff_cpuSS_1 Register
struct PMU_SOFTRESETOFF_CPUSS_1 {
	unsigned int SRST_asynccorerst_coresight_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asynccorerst_dbg0_n:1;		// [8]
	unsigned int SRST_asynccorerst_dbg1_n:1;		// [9]
	unsigned int reserved2:22;		// [31:10]
};
 // SoftResetOff_periSS_0 Register
struct PMU_SOFTRESETOFF_PERISS_0 {
	unsigned int SRST_mixedwrstdiv2_peri_ppier_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv2_peri_gdmac_n:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv2_mbox_n:1;		// [16]
	unsigned int reserved3:7;		// [23:17]
	unsigned int SRST_asyncwrstdiv4_peri_timer_n:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // SoftResetOff_periSS_1 Register
struct PMU_SOFTRESETOFF_PERISS_1 {
	unsigned int SRST_asyncwrstdiv2_peri_pwm_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv16_adc_n:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv2_peri_gpio0_n:1;		// [16]
	unsigned int reserved3:3;		// [19:17]
	unsigned int SRST_asyncwrstdiv2_peri_gpio1_n:1;		// [20]
	unsigned int reserved4:3;		// [23:21]
	unsigned int SRST_asyncwrstdiv4_i2cp_n:1;		// [24]
	unsigned int reserved5:7;		// [31:25]
};
 // SoftResetOff_periSS_2 Register
struct PMU_SOFTRESETOFF_PERISS_2 {
	unsigned int SRST_asyncwrstdiv2_peri_i2si0_n:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_asyncwrstdiv2_peri_i2si1_n:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_asyncwrstdiv2_peri_i2so0_n:1;		// [8]
	unsigned int reserved3:3;		// [11:9]
	unsigned int SRST_asyncwrstdiv2_peri_i2so1_n:1;		// [12]
	unsigned int reserved4:3;		// [15:13]
	unsigned int SRST_asyncwrstdiv2_peri_i2sc0_n:1;		// [16]
	unsigned int reserved5:15;		// [31:17]
};
 // SoftResetOff_periSS_3 Register
struct PMU_SOFTRESETOFF_PERISS_3 {
	unsigned int SRST_wrstdiv2_peri_spib0_n:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_spib0crst_n:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_asyncwrstdiv2_peri_spims0_n:1;		// [8]
	unsigned int reserved3:7;		// [15:9]
	unsigned int SRST_wrstdiv2_peri_spib1_n:1;		// [16]
	unsigned int reserved4:3;		// [19:17]
	unsigned int SRST_spib1crst_n:1;		// [20]
	unsigned int reserved5:3;		// [23:21]
	unsigned int SRST_asyncwrstdiv2_peri_spims1_n:1;		// [24]
	unsigned int reserved6:7;		// [31:25]
};
 // SoftResetOff_periSS_4 Register
struct PMU_SOFTRESETOFF_PERISS_4 {
	unsigned int SRST_asyncwrstdiv4_peri_uart_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncuart0rst_n:1;		// [8]
	unsigned int reserved2:3;		// [11:9]
	unsigned int SRST_asyncuart1rst_n:1;		// [12]
	unsigned int reserved3:3;		// [15:13]
	unsigned int SRST_asyncuart2rst_n:1;		// [16]
	unsigned int reserved4:3;		// [19:17]
	unsigned int SRST_asyncuart3rst_n:1;		// [20]
	unsigned int reserved5:3;		// [23:21]
	unsigned int SRST_asyncuart4rst_n:1;		// [24]
	unsigned int reserved6:7;		// [31:25]
};
 // SoftResetOff_dramcSS_0 Register
struct PMU_SOFTRESETOFF_DRAMCSS_0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int SRST_asyncwrst_dramc_n:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // SoftResetOff_mbootSS_0 Register
struct PMU_SOFTRESETOFF_MBOOTSS_0 {
	unsigned int SRST_asyncwrstdiv2_mboot_n:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SoftResetOff_dbgmonSS_0 Register
struct PMU_SOFTRESETOFF_DBGMONSS_0 {
	unsigned int SRST_wrstdiv2_dbgmon_n:1;		// [0]
	unsigned int reserved:15;		// [15:1]
	unsigned int SRST_mrst_dbgmon_n:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // SoftResetOff_eastpierSS_0 Register
struct PMU_SOFTRESETOFF_EASTPIERSS_0 {
	unsigned int SRST_mixederst_eastpier_n:1;		// [0]
	unsigned int SRST_mixederst_epierIFgpier_n:1;		// [1]
	unsigned int SRST_mixederst_epierIFipier_n:1;		// [2]
	unsigned int SRST_mixederst_epierIFvpier_n:1;		// [3]
	unsigned int reserved:4;		// [7:4]
	unsigned int SRST_mixedgrstdivN_eastpier_n:1;		// [8]
	unsigned int SRST_mixedgrstdivN_gpierIFepier_n:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int SRST_mixedrrst_eastpier_n:1;		// [16]
	unsigned int SRST_mixedrrst_ipierIFepier_n:1;		// [17]
	unsigned int reserved3:6;		// [23:18]
	unsigned int SRST_mixedvrstdivN_eastpier_n:1;		// [24]
	unsigned int SRST_mixedvrstdivN_vpierIFepier_n:1;		// [25]
	unsigned int reserved4:6;		// [31:26]
};
 // SoftResetOff_hsioSS_0 Register
struct PMU_SOFTRESETOFF_HSIOSS_0 {
	unsigned int SRST_asyncurst_usb2_n:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_asyncerstdiv2_hsio_usb2dc_n:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_asyncurst_usbSS_n:1;		// [8]
	unsigned int SRST_asyncerstdiv2_hsio_usb3pcie_n:1;		// [9]
	unsigned int reserved3:6;		// [15:10]
	unsigned int SRST_asyncerstdiv8_hsio_usb3hc_n:1;		// [16]
	unsigned int SRST_asyncerst_hsio_usb3hc_n:1;		// [17]
	unsigned int reserved4:6;		// [23:18]
	unsigned int SRST_asyncerst_hsio_pcie_axi_n:1;		// [24]
	unsigned int SRST_asyncerst_hsio_pcie_apb_n:1;		// [25]
	unsigned int reserved5:6;		// [31:26]
};
 // SoftResetOff_dispifSS_0 Register
struct PMU_SOFTRESETOFF_DISPIFSS_0 {
	unsigned int SRST_asyncerst_dispif_n:1;		// [0]
	unsigned int SRST_erst_dispif_n:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // SoftResetOff_camifSS_0 Register
struct PMU_SOFTRESETOFF_CAMIFSS_0 {
	unsigned int SRST_asyncerst_camif_csirx0_n:1;		// [0]
	unsigned int SRST_asyncerst_camif_csirx1_n:1;		// [1]
	unsigned int SRST_asyncerst_camif_csirx2_n:1;		// [2]
	unsigned int SRST_asyncerst_camif_csirx3_n:1;		// [3]
	unsigned int reserved:4;		// [7:4]
	unsigned int SRST_erst_camif_cvdmac_n:1;		// [8]
	unsigned int SRST_erst_camif_ccbus_n:1;		// [9]
	unsigned int SRST_asyncerst_camif_dphyrx_n:1;		// [10]
	unsigned int reserved2:21;		// [31:11]
};
 // SoftResetOff_vcodecSS_0 Register
struct PMU_SOFTRESETOFF_VCODECSS_0 {
	unsigned int SRST_vrstdivN_bap_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_vrstdivN_vdp_n:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_vrstdivN_vp4_n:1;		// [16]
	unsigned int reserved3:7;		// [23:17]
	unsigned int SRST_vrstdivN_vdime_n:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // SoftResetOff_vconvSS_0 Register
struct PMU_SOFTRESETOFF_VCONVSS_0 {
	unsigned int SRST_asyncerst_vconv_n:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SoftResetOff_irecogSS_0 Register
struct PMU_SOFTRESETOFF_IRECOGSS_0 {
	unsigned int SRST_rrst_pym_cnt_n:1;		// [0]
	unsigned int SRST_rrst_pym_vdm_n:1;		// [1]
	unsigned int SRST_rrst_pym_y1_n:1;		// [2]
	unsigned int SRST_rrst_pym_y2_n:1;		// [3]
	unsigned int SRST_rrst_pym_y3_n:1;		// [4]
	unsigned int SRST_rrst_pym_y4_n:1;		// [5]
	unsigned int SRST_rrst_pym_c1_n:1;		// [6]
	unsigned int SRST_rrst_pym_c2_n:1;		// [7]
	unsigned int SRST_rrst_pym_c3_n:1;		// [8]
	unsigned int SRST_rrst_pym_c4_n:1;		// [9]
	unsigned int SRST_rrst_sharedbus_n:1;		// [10]
	unsigned int SRST_asyncrrst_affine_n:1;		// [11]
	unsigned int SRST_asyncrrst_histgram_n:1;		// [12]
	unsigned int SRST_asyncrrst_match_n:1;		// [13]
	unsigned int SRST_asyncrrst_cohog0_n:1;		// [14]
	unsigned int SRST_asyncrrst_cohog1_n:1;		// [15]
	unsigned int SRST_asyncfrst_n:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // SoftResetOff_gpuSS_0 Register
struct PMU_SOFTRESETOFF_GPUSS_0 {
	unsigned int SRST_mixedgrstdivN_gpu_n:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SoftResetOff_econfSS_0 Register
struct PMU_SOFTRESETOFF_ECONFSS_0 {
	unsigned int SRST_asyncerstdiv2_econf_n:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SoftResetOff_etherSS_0 Register
struct PMU_SOFTRESETOFF_ETHERSS_0 {
	unsigned int SRST_erst_ether_n:1;		// [0]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_asyncethrst_n:1;		// [4]
	unsigned int reserved2:27;		// [31:5]
};
 // SoftResetOff_emmcSS_0 Register
struct PMU_SOFTRESETOFF_EMMCSS_0 {
	unsigned int SRST_asyncerst_emmca_axi_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncerst_emmcb_axi_n:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncerst_emmcc_axi_n:1;		// [16]
	unsigned int reserved3:15;		// [31:17]
};
 // SoftResetOff_nandcSS_0 Register
struct PMU_SOFTRESETOFF_NANDCSS_0 {
	unsigned int SRST_asyncerstdiv2_nandc_n:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncerstdiv2_nandc_m0_n:1;		// [8]
	unsigned int reserved2:23;		// [31:9]
};
 // ClockGatingOnForPower_TOP Register
struct PMU_CLOCKGATINGONFORPOWER_TOP {
	unsigned int CGPower_TOP:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOnForPower_CPU Register
struct PMU_CLOCKGATINGONFORPOWER_CPU {
	unsigned int CGPower_CPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOnForPower_GPU Register
struct PMU_CLOCKGATINGONFORPOWER_GPU {
	unsigned int CGPower_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOnForPower_VIDEO Register
struct PMU_CLOCKGATINGONFORPOWER_VIDEO {
	unsigned int CGPower_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOffForPower_TOP Register
struct PMU_CLOCKGATINGOFFFORPOWER_TOP {
	unsigned int CGPower_TOP:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOffForPower_CPU Register
struct PMU_CLOCKGATINGOFFFORPOWER_CPU {
	unsigned int CGPower_CPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOffForPower_GPU Register
struct PMU_CLOCKGATINGOFFFORPOWER_GPU {
	unsigned int CGPower_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ClockGatingOffForPower_VIDEO Register
struct PMU_CLOCKGATINGOFFFORPOWER_VIDEO {
	unsigned int CGPower_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // CPU_Clock_Divede_Setting Register
struct PMU_CPU_CLOCK_DIVEDE_SETTING {
	unsigned int DivEn:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int Core_Div:4;		// [11:8]
	unsigned int L2C_Div:4;		// [15:12]
	unsigned int PERIPH_Div:4;		// [19:16]
	unsigned int reserved2:4;		// [23:20]
	unsigned int DAPB_Div:4;		// [27:24]
	unsigned int ATB_Div:4;		// [31:28]
};
 // Frequency_GPU Register
struct PMU_FREQUENCY_GPU {
	unsigned int Frequency_GPU:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int FrequencyCTRL_GPU:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // Frequency_VIDEO Register
struct PMU_FREQUENCY_VIDEO {
	unsigned int Frequency_VIDEO:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int FrequencyCTRL_VIDEO:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // Frequency_irecogSS Register
struct PMU_FREQUENCY_IRECOGSS {
	unsigned int Frequency_irecogSS:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int FrequencyCTRL_irecogSS:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // AUDIO_CLOCK_0 Register
struct PMU_AUDIO_CLOCK_0 {
	unsigned int Frequency_io_AMCLKO_o:2;		// [1:0]
	unsigned int reserved:2;		// [3:2]
	unsigned int Frequency_amclk_i2s:2;		// [5:4]
	unsigned int reserved2:22;		// [27:6]
	unsigned int AudioPLL_Source:1;		// [28]
	unsigned int reserved3:3;		// [31:29]
};
 // UART_CLOCK_0 Register
struct PMU_UART_CLOCK_0 {
	unsigned int uart0clk_sel:2;		// [1:0]
	unsigned int reserved:2;		// [3:2]
	unsigned int uart1clk_sel:3;		// [6:4]
	unsigned int reserved2:1;		// [7]
	unsigned int uart2clk_sel:2;		// [9:8]
	unsigned int reserved3:2;		// [11:10]
	unsigned int uart3clk_sel:2;		// [13:12]
	unsigned int reserved4:2;		// [15:14]
	unsigned int uart4clk_sel:2;		// [17:16]
	unsigned int reserved5:14;		// [31:18]
};
 // PLLConfig_PLLCPU_0 Register
struct PMU_PLLCONFIG_PLLCPU_0 {
	unsigned int PLLCPU_PD:1;		// [0]
	unsigned int PLLCPU_BP:1;		// [1]
	unsigned int PLLCPU_RESET:1;		// [2]
	unsigned int reserved:9;		// [11:3]
	unsigned int PLLCPU_LFR:3;		// [14:12]
	unsigned int reserved2:1;		// [15]
	unsigned int PLLCPU_BCP:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int PLLCPU_IVCP:3;		// [26:24]
	unsigned int reserved4:1;		// [27]
	unsigned int PLLCPU_ISCP:2;		// [29:28]
	unsigned int reserved5:1;		// [30]
	unsigned int PLLCPU_SWEN:1;		// [31]
};
 // PLLConfig_PLLCPU_1 Register
struct PMU_PLLCONFIG_PLLCPU_1 {
	unsigned int PLLCPU_ND:7;		// [6:0]
	unsigned int reserved:1;		// [7]
	unsigned int PLLCPU_PRD:5;		// [12:8]
	unsigned int reserved2:3;		// [15:13]
	unsigned int PLLCPU_PSD:4;		// [19:16]
	unsigned int reserved3:8;		// [27:20]
	unsigned int PLLCPU_FSEL:1;		// [28]
	unsigned int reserved4:3;		// [31:29]
};
 // PLLConfig_PLLETH_0 Register
struct PMU_PLLCONFIG_PLLETH_0 {
	unsigned int PLLETH_PD:1;		// [0]
	unsigned int PLLETH_BP:1;		// [1]
	unsigned int PLLETH_RESET:1;		// [2]
	unsigned int reserved:5;		// [7:3]
	unsigned int PLLETH_OSW:2;		// [9:8]
	unsigned int reserved2:2;		// [11:10]
	unsigned int PLLETH_LFR:3;		// [14:12]
	unsigned int reserved3:1;		// [15]
	unsigned int PLLETH_BCP:5;		// [20:16]
	unsigned int reserved4:3;		// [23:21]
	unsigned int PLLETH_IVCP:3;		// [26:24]
	unsigned int reserved5:1;		// [27]
	unsigned int PLLETH_ISCP:2;		// [29:28]
	unsigned int reserved6:1;		// [30]
	unsigned int PLLETH_SWEN:1;		// [31]
};
 // PLLConfig_PLLETH_1 Register
struct PMU_PLLCONFIG_PLLETH_1 {
	unsigned int PLLETH_ND:7;		// [6:0]
	unsigned int reserved:1;		// [7]
	unsigned int PLLETH_PRD:5;		// [12:8]
	unsigned int reserved2:3;		// [15:13]
	unsigned int PLLETH_PSD:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int PLLETH_PRESCL:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // PLLConfig_PLLDSI_0 Register
struct PMU_PLLCONFIG_PLLDSI_0 {
	unsigned int PLLDSI_PD:1;		// [0]
	unsigned int PLLDSI_BP:1;		// [1]
	unsigned int PLLDSI_RESET:1;		// [2]
	unsigned int reserved:5;		// [7:3]
	unsigned int PLLDSI_OSW:2;		// [9:8]
	unsigned int reserved2:2;		// [11:10]
	unsigned int PLLDSI_LFR:3;		// [14:12]
	unsigned int reserved3:1;		// [15]
	unsigned int PLLDSI_BCP:5;		// [20:16]
	unsigned int reserved4:3;		// [23:21]
	unsigned int PLLDSI_IVCP:3;		// [26:24]
	unsigned int reserved5:1;		// [27]
	unsigned int PLLDSI_ISCP:2;		// [29:28]
	unsigned int reserved6:1;		// [30]
	unsigned int PLLDSI_SWEN:1;		// [31]
};
 // PLLConfig_PLLDSI_1 Register
struct PMU_PLLCONFIG_PLLDSI_1 {
	unsigned int PLLDSI_ND:7;		// [6:0]
	unsigned int reserved:1;		// [7]
	unsigned int PLLDSI_PRD:5;		// [12:8]
	unsigned int reserved2:3;		// [15:13]
	unsigned int PLLDSI_PSD:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int PLLDSI_PRESCL:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // PLLConfig_PLLI2S_0 Register
struct PMU_PLLCONFIG_PLLI2S_0 {
	unsigned int PLLI2S_PD:1;		// [0]
	unsigned int PLLI2S_BP:1;		// [1]
	unsigned int PLLI2S_RESET:1;		// [2]
	unsigned int reserved:5;		// [7:3]
	unsigned int PLLI2S_OSW:2;		// [9:8]
	unsigned int reserved2:2;		// [11:10]
	unsigned int PLLI2S_LFR:3;		// [14:12]
	unsigned int reserved3:1;		// [15]
	unsigned int PLLI2S_BCP:5;		// [20:16]
	unsigned int reserved4:3;		// [23:21]
	unsigned int PLLI2S_IVCP:3;		// [26:24]
	unsigned int reserved5:1;		// [27]
	unsigned int PLLI2S_ISCP:2;		// [29:28]
	unsigned int reserved6:1;		// [30]
	unsigned int PLLI2S_SWEN:1;		// [31]
};
 // PLLConfig_PLLI2S_1 Register
struct PMU_PLLCONFIG_PLLI2S_1 {
	unsigned int reserved:8;		// [7:0]
	unsigned int PLLI2S_REFDIV:5;		// [12:8]
	unsigned int reserved2:3;		// [15:13]
	unsigned int PLLI2S_OUTDIV:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int PLLI2S_PRESCL:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // PLLConfig_PLLI2S_2 Register
struct PMU_PLLCONFIG_PLLI2S_2 {
	unsigned int PLLI2S_INTE:6;		// [5:0]
	unsigned int reserved:2;		// [7:6]
	unsigned int PLLI2S_DITHEN:1;		// [8]
	unsigned int PLLI2S_SSCEN:1;		// [9]
	unsigned int PLLI2S_MODTYPE:1;		// [10]
	unsigned int reserved2:5;		// [15:11]
	unsigned int PLLI2S_NUME:16;		// [31:16]
};
 // PLLConfig_PLLI2S_3 Register
struct PMU_PLLCONFIG_PLLI2S_3 {
	unsigned int PLLI2S_TRLEN:7;		// [6:0]
	unsigned int reserved:1;		// [7]
	unsigned int PLLI2S_FNLEN:7;		// [14:8]
	unsigned int reserved2:1;		// [15]
	unsigned int PLLI2S_DSFT:16;		// [31:16]
};
 // SeqStatus_DFS_GPU Register
struct PMU_SEQSTATUS_DFS_GPU {
	unsigned int SeqStatus_DFS_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_DFS_VIDEO Register
struct PMU_SEQSTATUS_DFS_VIDEO {
	unsigned int SeqStatus_DFS_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_DFS_irecogSS Register
struct PMU_SEQSTATUS_DFS_IRECOGSS {
	unsigned int SeqStatus_DFS_irecogSS:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_PowerOn_TOP Register
struct PMU_SEQSTATUS_POWERON_TOP {
	unsigned int SeqStatus_PowerOn_TOP:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_PowerOn_CPU Register
struct PMU_SEQSTATUS_POWERON_CPU {
	unsigned int SeqStatus_PowerOn_CPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_PowerOn_GPU Register
struct PMU_SEQSTATUS_POWERON_GPU {
	unsigned int SeqStatus_PowerOn_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_PowerOn_VIDEO Register
struct PMU_SEQSTATUS_POWERON_VIDEO {
	unsigned int SeqStatus_PowerOn_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_PowerOff_TOP Register
struct PMU_SEQSTATUS_POWEROFF_TOP {
	unsigned int SeqStatus_PowerOff_TOP:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_PowerOff_CPU Register
struct PMU_SEQSTATUS_POWEROFF_CPU {
	unsigned int SeqStatus_PowerOff_CPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_PowerOff_GPU Register
struct PMU_SEQSTATUS_POWEROFF_GPU {
	unsigned int SeqStatus_PowerOff_GPU:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // SeqStatus_PowerOff_VIDEO Register
struct PMU_SEQSTATUS_POWEROFF_VIDEO {
	unsigned int SeqStatus_PowerOff_VIDEO:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // Status_PswAck Register
struct PMU_STATUS_PSWACK {
	unsigned int reserved:2;		// [1:0]
	unsigned int Status_PswAck_GPU:1;		// [2]
	unsigned int Status_PswAck_VIDEO:1;		// [3]
	unsigned int reserved2:28;		// [31:4]
};
 // ModeStatus_WatchdogTimer Register
struct PMU_MODESTATUS_WATCHDOGTIMER {
	unsigned int WatchdogTimerFlag_cpu:2;		// [1:0]
	unsigned int reserved:6;		// [7:2]
	unsigned int WatchdogTimerFlag_timer:1;		// [8]
	unsigned int reserved2:3;		// [11:9]
	unsigned int WatchdogTimerFlag_stimer:1;		// [12]
	unsigned int reserved3:19;		// [31:13]
};
 // Status_Interrupt Register
struct PMU_STATUS_INTERRUPT {
	unsigned int Status_irq_pmu:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // Mask_Interrupt Register
struct PMU_MASK_INTERRUPT {
	unsigned int Mask_irq_pmu:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // EFUSE_0 Register
struct PMU_EFUSE_0 {
	unsigned int efuse_e0000:1;		// [0]
	unsigned int efuse_e0001:1;		// [1]
	unsigned int efuse_e0002:1;		// [2]
	unsigned int efuse_e0003:1;		// [3]
	unsigned int efuse_e0004:1;		// [4]
	unsigned int efuse_e0005:1;		// [5]
	unsigned int efuse_e0006:1;		// [6]
	unsigned int efuse_e0007:1;		// [7]
	unsigned int efuse_e0008:1;		// [8]
	unsigned int efuse_e0009:1;		// [9]
	unsigned int efuse_e0010:1;		// [10]
	unsigned int efuse_e0011:1;		// [11]
	unsigned int efuse_e0012:1;		// [12]
	unsigned int efuse_e0013:1;		// [13]
	unsigned int efuse_e0014:1;		// [14]
	unsigned int efuse_e0015:1;		// [15]
	unsigned int efuse_e0016:1;		// [16]
	unsigned int efuse_e0017:1;		// [17]
	unsigned int efuse_e0018:1;		// [18]
	unsigned int efuse_e0019:1;		// [19]
	unsigned int efuse_e0020:1;		// [20]
	unsigned int efuse_e0021:1;		// [21]
	unsigned int efuse_e0022:1;		// [22]
	unsigned int efuse_e0023:1;		// [23]
	unsigned int efuse_e0024:1;		// [24]
	unsigned int efuse_e0025:1;		// [25]
	unsigned int efuse_e0026:1;		// [26]
	unsigned int efuse_e0027:1;		// [27]
	unsigned int efuse_e0028:1;		// [28]
	unsigned int efuse_e0029:1;		// [29]
	unsigned int efuse_e0030:1;		// [30]
	unsigned int efuse_e0031:1;		// [31]
};
 // EFUSE_1 Register
struct PMU_EFUSE_1 {
	unsigned int efuse_e0100:1;		// [0]
	unsigned int efuse_e0101:1;		// [1]
	unsigned int efuse_e0102:1;		// [2]
	unsigned int efuse_e0103:1;		// [3]
	unsigned int efuse_e0104:1;		// [4]
	unsigned int efuse_e0105:1;		// [5]
	unsigned int efuse_e0106:1;		// [6]
	unsigned int efuse_e0107:1;		// [7]
	unsigned int efuse_e0108:1;		// [8]
	unsigned int efuse_e0109:1;		// [9]
	unsigned int efuse_e0110:1;		// [10]
	unsigned int efuse_e0111:1;		// [11]
	unsigned int efuse_e0112:1;		// [12]
	unsigned int efuse_e0113:1;		// [13]
	unsigned int efuse_e0114:1;		// [14]
	unsigned int efuse_e0115:1;		// [15]
	unsigned int efuse_e0116:1;		// [16]
	unsigned int efuse_e0117:1;		// [17]
	unsigned int efuse_e0118:1;		// [18]
	unsigned int efuse_e0119:1;		// [19]
	unsigned int efuse_e0120:1;		// [20]
	unsigned int efuse_e0121:1;		// [21]
	unsigned int efuse_e0122:1;		// [22]
	unsigned int efuse_e0123:1;		// [23]
	unsigned int efuse_e0124:1;		// [24]
	unsigned int efuse_e0125:1;		// [25]
	unsigned int efuse_e0126:1;		// [26]
	unsigned int efuse_e0127:1;		// [27]
	unsigned int efuse_e0128:1;		// [28]
	unsigned int efuse_e0129:1;		// [29]
	unsigned int efuse_e0130:1;		// [30]
	unsigned int efuse_e0131:1;		// [31]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PMU_REG_STRUCT_L_H */
