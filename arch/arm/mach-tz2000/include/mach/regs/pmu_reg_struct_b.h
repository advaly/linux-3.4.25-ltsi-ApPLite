/*
 * arch/arm/mach-tz2000/include/mach/regs/pmu_reg_struct_b.h
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

#ifndef _PMU_REG_STRUCT_B_H
#define _PMU_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // PowerSwitchOn_TOP Register
struct PMU_POWERSWITCHON_TOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int PSW_TOP:1;		// [0]
};
 // PowerSwitchOff_TOP Register
struct PMU_POWERSWITCHOFF_TOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int PSW_TOP:1;		// [0]
};
 // InIsoOn_TOP Register
struct PMU_INISOON_TOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int InIso_TOP:1;		// [0]
};
 // InIsoOff_TOP Register
struct PMU_INISOOFF_TOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int InIso_TOP:1;		// [0]
};
 // OutIsoOn_TOP Register
struct PMU_OUTISOON_TOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int OutIso_TOP:1;		// [0]
};
 // OutIsoOn_DRAMC Register
struct PMU_OUTISOON_DRAMC {
	unsigned int reserved:31;		// [31:1]
	unsigned int OutIso_DRAMC:1;		// [0]
};
 // OutIsoOff_TOP Register
struct PMU_OUTISOOFF_TOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int OutIso_TOP:1;		// [0]
};
 // OutIsoOff_DRAMC Register
struct PMU_OUTISOOFF_DRAMC {
	unsigned int reserved:31;		// [31:1]
	unsigned int OutIso_DRAMC:1;		// [0]
};
 // ClockGatingOn_westpierSS_0 Register
struct PMU_CLOCKGATINGON_WESTPIERSS_0 {
	unsigned int reserved2:7;		// [31:25]
	unsigned int CG_wclk_westpier_fdconv:1;		// [24]
	unsigned int reserved:23;		// [23:1]
	unsigned int CG_wclk_westpier_mpier:1;		// [0]
};
 // ClockGatingOn_cpuSS_0 Register
struct PMU_CLOCKGATINGON_CPUSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_coreclk:1;		// [0]
};
 // ClockGatingOn_periSS_0 Register
struct PMU_CLOCKGATINGON_PERISS_0 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int CG_wclkdiv4_peri_timer:1;		// [24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int CG_wclkdiv2_mbox:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv2_peri_gdmac:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv4_peri_ppier:1;		// [0]
};
 // ClockGatingOn_periSS_1 Register
struct PMU_CLOCKGATINGON_PERISS_1 {
	unsigned int reserved5:7;		// [31:25]
	unsigned int CG_wclkdiv4_peri_i2cp:1;		// [24]
	unsigned int reserved4:3;		// [23:21]
	unsigned int CG_wclkdiv4_peri_gpio1:1;		// [20]
	unsigned int reserved3:3;		// [19:17]
	unsigned int CG_wclkdiv4_peri_gpio0:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv16_peri_adc:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv4_peri_pwm:1;		// [0]
};
 // ClockGatingOn_periSS_2 Register
struct PMU_CLOCKGATINGON_PERISS_2 {
	unsigned int reserved5:3;		// [31:29]
	unsigned int CG_io_AMCLKO_o:1;		// [28]
	unsigned int reserved4:3;		// [27:25]
	unsigned int CG_amclk_i2s:1;		// [24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int CG_wclkdiv4_peri_i2sc0:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv4_peri_i2so0:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv4_peri_i2si0:1;		// [0]
};
 // ClockGatingOn_periSS_3 Register
struct PMU_CLOCKGATINGON_PERISS_3 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int CG_wclkdiv4_peri_spims1:1;		// [24]
	unsigned int reserved3:15;		// [23:9]
	unsigned int CG_wclkdiv4_peri_spims0:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_spib0cclk:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_wclkdiv4_peri_spib0:1;		// [0]
};
 // ClockGatingOn_periSS_4 Register
struct PMU_CLOCKGATINGON_PERISS_4 {
	unsigned int reserved5:11;		// [31:21]
	unsigned int CG_uart3clk:1;		// [20]
	unsigned int reserved4:3;		// [19:17]
	unsigned int CG_uart2clk:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int CG_uart1clk:1;		// [12]
	unsigned int reserved2:3;		// [11:9]
	unsigned int CG_uart0clk:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv4_peri_uart:1;		// [0]
};
 // ClockGatingOn_dramcSS_0 Register
struct PMU_CLOCKGATINGON_DRAMCSS_0 {
	unsigned int reserved3:15;		// [31:17]
	unsigned int CG_wclkdiv2_dramc:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclk_dramc:1;		// [8]
	unsigned int reserved:8;		// [7:0]
};
 // ClockGatingOn_mbootSS_0 Register
struct PMU_CLOCKGATINGON_MBOOTSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_mboot:1;		// [0]
};
 // ClockGatingOn_wconfSS_0 Register
struct PMU_CLOCKGATINGON_WCONFSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_wclkdiv4_wconf:1;		// [0]
};
 // ClockGatingOn_usb2hdSS_0 Register
struct PMU_CLOCKGATINGON_USB2HDSS_0 {
	unsigned int reserved4:19;		// [31:13]
	unsigned int CG_wclkdiv2_usb2hd_h:1;		// [12]
	unsigned int reserved3:3;		// [11:9]
	unsigned int CG_wclkdiv2_usb2hd_ohci:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_wclkdiv2_usb2hd_ehci:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_uclk_usb2:1;		// [0]
};
 // ClockGatingOn_lcdcSS_0 Register
struct PMU_CLOCKGATINGON_LCDCSS_0 {
	unsigned int reserved2:23;		// [31:9]
	unsigned int CG_dotclk:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv2_lcdc:1;		// [0]
};
 // ClockGatingOn_yuvcSS_0 Register
struct PMU_CLOCKGATINGON_YUVCSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_yuvc:1;		// [0]
};
 // ClockGatingOn_gfxSS_0 Register
struct PMU_CLOCKGATINGON_GFXSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_gfx:1;		// [0]
};
 // ClockGatingOn_etherSS_0 Register
struct PMU_CLOCKGATINGON_ETHERSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_ether:1;		// [0]
};
 // ClockGatingOn_emmcSS_0 Register
struct PMU_CLOCKGATINGON_EMMCSS_0 {
	unsigned int reserved:30;		// [31:2]
	unsigned int CG_wclkdiv2_emmc4sd_x:1;		// [1]
	unsigned int CG_wclkdiv4_emmc4sd_h:1;		// [0]
};
 // ClockGatingOn_telomereSS_0 Register
struct PMU_CLOCKGATINGON_TELOMERESS_0 {
	unsigned int reserved4:14;		// [31:18]
	unsigned int CG_wclkdiv2_emmc8sd_x:1;		// [17]
	unsigned int CG_wclkdiv2_emmc8sd_h:1;		// [16]
	unsigned int reserved3:7;		// [15:9]
	unsigned int CG_wclkdiv2_telomere:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_nclk:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_nclkdiv2:1;		// [0]
};
 // ClockGatingOff_westpierSS_0 Register
struct PMU_CLOCKGATINGOFF_WESTPIERSS_0 {
	unsigned int reserved2:7;		// [31:25]
	unsigned int CG_wclk_westpier_fdconv:1;		// [24]
	unsigned int reserved:23;		// [23:1]
	unsigned int CG_wclk_westpier_mpier:1;		// [0]
};
 // ClockGatingOff_cpuSS_0 Register
struct PMU_CLOCKGATINGOFF_CPUSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_coreclk:1;		// [0]
};
 // ClockGatingOff_periSS_0 Register
struct PMU_CLOCKGATINGOFF_PERISS_0 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int CG_wclkdiv4_peri_timer:1;		// [24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int CG_wclkdiv2_mbox:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv2_peri_gdmac:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv4_peri_ppier:1;		// [0]
};
 // ClockGatingOff_periSS_1 Register
struct PMU_CLOCKGATINGOFF_PERISS_1 {
	unsigned int reserved5:7;		// [31:25]
	unsigned int CG_wclkdiv4_peri_i2cp:1;		// [24]
	unsigned int reserved4:3;		// [23:21]
	unsigned int CG_wclkdiv4_peri_gpio1:1;		// [20]
	unsigned int reserved3:3;		// [19:17]
	unsigned int CG_wclkdiv4_peri_gpio0:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv16_peri_adc:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv4_peri_pwm:1;		// [0]
};
 // ClockGatingOff_periSS_2 Register
struct PMU_CLOCKGATINGOFF_PERISS_2 {
	unsigned int reserved5:3;		// [31:29]
	unsigned int CG_io_AMCLKO_o:1;		// [28]
	unsigned int reserved4:3;		// [27:25]
	unsigned int CG_amclk_i2s:1;		// [24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int CG_wclkdiv4_peri_i2sc0:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclkdiv4_peri_i2so0:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv4_peri_i2si0:1;		// [0]
};
 // ClockGatingOff_periSS_3 Register
struct PMU_CLOCKGATINGOFF_PERISS_3 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int CG_wclkdiv4_peri_spims1:1;		// [24]
	unsigned int reserved3:15;		// [23:9]
	unsigned int CG_wclkdiv4_peri_spims0:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_spib0cclk:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_wclkdiv4_peri_spib0:1;		// [0]
};
 // ClockGatingOff_periSS_4 Register
struct PMU_CLOCKGATINGOFF_PERISS_4 {
	unsigned int reserved5:11;		// [31:21]
	unsigned int CG_uart3clk:1;		// [20]
	unsigned int reserved4:3;		// [19:17]
	unsigned int CG_uart2clk:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int CG_uart1clk:1;		// [12]
	unsigned int reserved2:3;		// [11:9]
	unsigned int CG_uart0clk:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv4_peri_uart:1;		// [0]
};
 // ClockGatingOff_dramcSS_0 Register
struct PMU_CLOCKGATINGOFF_DRAMCSS_0 {
	unsigned int reserved3:15;		// [31:17]
	unsigned int CG_wclkdiv2_dramc:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int CG_wclk_dramc:1;		// [8]
	unsigned int reserved:8;		// [7:0]
};
 // ClockGatingOff_mbootSS_0 Register
struct PMU_CLOCKGATINGOFF_MBOOTSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_mboot:1;		// [0]
};
 // ClockGatingOff_wconfSS_0 Register
struct PMU_CLOCKGATINGOFF_WCONFSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv4_wconf:1;		// [0]
};
 // ClockGatingOff_usb2hdSS_0 Register
struct PMU_CLOCKGATINGOFF_USB2HDSS_0 {
	unsigned int reserved4:19;		// [31:13]
	unsigned int CG_wclkdiv2_usb2hd_h:1;		// [12]
	unsigned int reserved3:3;		// [11:9]
	unsigned int CG_wclkdiv2_usb2hd_ohci:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_wclkdiv2_usb2hd_ehci:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_uclk_usb2:1;		// [0]
};
 // ClockGatingOff_lcdcSS_0 Register
struct PMU_CLOCKGATINGOFF_LCDCSS_0 {
	unsigned int reserved2:23;		// [31:9]
	unsigned int CG_dotclk:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int CG_wclkdiv2_lcdc:1;		// [0]
};
 // ClockGatingOff_yuvcSS_0 Register
struct PMU_CLOCKGATINGOFF_YUVCSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_yuvc:1;		// [0]
};
 // ClockGatingOff_gfxSS_0 Register
struct PMU_CLOCKGATINGOFF_GFXSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_gfx:1;		// [0]
};
 // ClockGatingOff_etherSS_0 Register
struct PMU_CLOCKGATINGOFF_ETHERSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int CG_wclkdiv2_ether:1;		// [0]
};
 // ClockGatingOff_emmcSS_0 Register
struct PMU_CLOCKGATINGOFF_EMMCSS_0 {
	unsigned int reserved:30;		// [31:2]
	unsigned int CG_wclkdiv2_emmc4sd_x:1;		// [1]
	unsigned int CG_wclkdiv4_emmc4sd_h:1;		// [0]
};
 // ClockGatingOff_telomereSS_0 Register
struct PMU_CLOCKGATINGOFF_TELOMERESS_0 {
	unsigned int reserved4:14;		// [31:18]
	unsigned int CG_wclkdiv2_emmc8sd_x:1;		// [17]
	unsigned int CG_wclkdiv2_emmc8sd_h:1;		// [16]
	unsigned int reserved3:7;		// [15:9]
	unsigned int CG_wclkdiv2_telomere:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int CG_nclk:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int CG_nclkdiv2:1;		// [0]
};
 // SoftResetOn_westpierSS_0 Register
struct PMU_SOFTRESETON_WESTPIERSS_0 {
	unsigned int reserved2:7;		// [31:25]
	unsigned int SRST_mixedwrst_westpier_fdconv_n:1;		// [24]
	unsigned int reserved:23;		// [23:1]
	unsigned int SRST_mixedwrst_westpier_mpier_n:1;		// [0]
};
 // SoftResetOn_cpuSS_0 Register
struct PMU_SOFTRESETON_CPUSS_0 {
	unsigned int reserved4:11;		// [31:21]
	unsigned int SRST_asynccorerst_cpu0_n:1;		// [20]
	unsigned int reserved3:7;		// [19:13]
	unsigned int SRST_asynccorerst_wd0_n:1;		// [12]
	unsigned int reserved2:1;		// [11]
	unsigned int SRST_asynccorerst_scu_n:1;		// [10]
	unsigned int reserved:9;		// [9:1]
	unsigned int SRST_asynccorerst_smpgn_n:1;		// [0]
};
 // SoftResetOn_cpuSS_1 Register
struct PMU_SOFTRESETON_CPUSS_1 {
	unsigned int reserved2:23;		// [31:9]
	unsigned int SRST_asynccorerst_dbg0_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asynccorerst_coresight_n:1;		// [0]
};
 // SoftResetOn_periSS_0 Register
struct PMU_SOFTRESETON_PERISS_0 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int SRST_asyncwrstdiv4_peri_timer_n:1;		// [24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int SRST_asyncwrstdiv2_mbox_n:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv2_peri_gdmac_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_mixedwrstdiv4_peri_ppier_n:1;		// [0]
};
 // SoftResetOn_periSS_1 Register
struct PMU_SOFTRESETON_PERISS_1 {
	unsigned int reserved5:7;		// [31:25]
	unsigned int SRST_asyncwrstdiv4_peri_i2cp_n:1;		// [24]
	unsigned int reserved4:3;		// [23:21]
	unsigned int SRST_asyncwrstdiv4_peri_gpio1_n:1;		// [20]
	unsigned int reserved3:3;		// [19:17]
	unsigned int SRST_asyncwrstdiv4_peri_gpio0_n:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv16_peri_adc_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv4_peri_pwm_n:1;		// [0]
};
 // SoftResetOn_periSS_2 Register
struct PMU_SOFTRESETON_PERISS_2 {
	unsigned int reserved3:15;		// [31:17]
	unsigned int SRST_asyncwrstdiv4_peri_i2sc0_n:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv4_peri_i2so0_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv4_peri_i2si0_n:1;		// [0]
};
 // SoftResetOn_periSS_3 Register
struct PMU_SOFTRESETON_PERISS_3 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int SRST_asyncwrstdiv4_peri_spims1_n:1;		// [24]
	unsigned int reserved3:15;		// [23:9]
	unsigned int SRST_asyncwrstdiv4_peri_spims0_n:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_spib0crst_n:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_wrstdiv4_peri_spib0_n:1;		// [0]
};
 // SoftResetOn_periSS_4 Register
struct PMU_SOFTRESETON_PERISS_4 {
	unsigned int reserved5:11;		// [31:21]
	unsigned int SRST_asyncuart3rst_n:1;		// [20]
	unsigned int reserved4:3;		// [19:17]
	unsigned int SRST_asyncuart2rst_n:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int SRST_asyncuart1rst_n:1;		// [12]
	unsigned int reserved2:3;		// [11:9]
	unsigned int SRST_asyncuart0rst_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv4_peri_uart_n:1;		// [0]
};
 // SoftResetOn_dramcSS_0 Register
struct PMU_SOFTRESETON_DRAMCSS_0 {
	unsigned int reserved2:23;		// [31:9]
	unsigned int SRST_mixedwrstdiv2_dramc_n:1;		// [8]
	unsigned int reserved:8;		// [7:0]
};
 // SoftResetOn_mbootSS_0 Register
struct PMU_SOFTRESETON_MBOOTSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_asyncwrstdiv2_mboot_n:1;		// [0]
};
 // SoftResetOn_wconfSS_0 Register
struct PMU_SOFTRESETON_WCONFSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_asyncwrstdiv4_wconf_n:1;		// [0]
};
 // SoftResetOn_usb2hdSS_0 Register
struct PMU_SOFTRESETON_USB2HDSS_0 {
	unsigned int reserved6:17;		// [31:15]
	unsigned int SRST_asyncurst_usb2_udc_n:1;		// [14]
	unsigned int reserved5:1;		// [13]
	unsigned int SRST_asyncwrstdiv2_usb2hd_h_n:1;		// [12]
	unsigned int reserved4:1;		// [11]
	unsigned int SRST_asyncurst_usb2_uhc_n:1;		// [10]
	unsigned int reserved3:1;		// [9]
	unsigned int SRST_asyncwrstdiv2_usb2hd_ohci_n:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_asyncwrstdiv2_usb2hd_ehci_n:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_asyncurst_usb2_por_n:1;		// [0]
};
 // SoftResetOn_lcdcSS_0 Register
struct PMU_SOFTRESETON_LCDCSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_asyncwrstdiv2_lcdc_n:1;		// [0]
};
 // SoftResetOn_yuvcSS_0 Register
struct PMU_SOFTRESETON_YUVCSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_wrstdiv2_yuvc_n:1;		// [0]
};
 // SoftResetOn_gfxSS_0 Register
struct PMU_SOFTRESETON_GFXSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_asyncwrstdiv2_gfx_n:1;		// [0]
};
 // SoftResetOn_etherSS_0 Register
struct PMU_SOFTRESETON_ETHERSS_0 {
	unsigned int reserved2:27;		// [31:5]
	unsigned int SRST_asyncwrstdiv2_ether_n:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_wrstdiv2_ether_n:1;		// [0]
};
 // SoftResetOn_emmcSS_0 Register
struct PMU_SOFTRESETON_EMMCSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_mixedwrstdiv4_emmc4sd_h_n:1;		// [0]
};
 // SoftResetOn_telomereSS_0 Register
struct PMU_SOFTRESETON_TELOMERESS_0 {
	unsigned int reserved3:14;		// [31:18]
	unsigned int SRST_asyncwrstdiv2_emmc8sd_x_n:1;		// [17]
	unsigned int SRST_mixedwrstdiv2_emmc8sd_h_n:1;		// [16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int SRST_mixedwrstdiv2_telomere_n:1;		// [9]
	unsigned int SRST_asyncwrstdiv2_telomere_n:1;		// [8]
	unsigned int reserved:6;		// [7:2]
	unsigned int SRST_nrstdiv2_n:1;		// [1]
	unsigned int SRST_asyncnrstdiv2_n:1;		// [0]
};
 // SoftResetOff_westpierSS_0 Register
struct PMU_SOFTRESETOFF_WESTPIERSS_0 {
	unsigned int reserved2:7;		// [31:25]
	unsigned int SRST_mixedwrst_westpier_fdconv_n:1;		// [24]
	unsigned int reserved:23;		// [23:1]
	unsigned int SRST_mixedwrst_westpier_mpier_n:1;		// [0]
};
 // SoftResetOff_cpuSS_0 Register
struct PMU_SOFTRESETOFF_CPUSS_0 {
	unsigned int reserved4:11;		// [31:21]
	unsigned int SRST_asynccorerst_cpu0_n:1;		// [20]
	unsigned int reserved3:7;		// [19:13]
	unsigned int SRST_asynccorerst_wd0_n:1;		// [12]
	unsigned int reserved2:1;		// [11]
	unsigned int SRST_asynccorerst_scu_n:1;		// [10]
	unsigned int reserved:9;		// [9:1]
	unsigned int SRST_asynccorerst_smpgn_n:1;		// [0]
};
 // SoftResetOff_cpuSS_1 Register
struct PMU_SOFTRESETOFF_CPUSS_1 {
	unsigned int reserved2:23;		// [31:9]
	unsigned int SRST_asynccorerst_dbg0_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asynccorerst_coresight_n:1;		// [0]
};
 // SoftResetOff_periSS_0 Register
struct PMU_SOFTRESETOFF_PERISS_0 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int SRST_asyncwrstdiv4_peri_timer_n:1;		// [24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int SRST_asyncwrstdiv2_mbox_n:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv2_peri_gdmac_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_mixedwrstdiv4_peri_ppier_n:1;		// [0]
};
 // SoftResetOff_periSS_1 Register
struct PMU_SOFTRESETOFF_PERISS_1 {
	unsigned int reserved5:7;		// [31:25]
	unsigned int SRST_asyncwrstdiv4_i2cp_n:1;		// [24]
	unsigned int reserved4:3;		// [23:21]
	unsigned int SRST_asyncwrstdiv4_peri_gpio1_n:1;		// [20]
	unsigned int reserved3:3;		// [19:17]
	unsigned int SRST_asyncwrstdiv4_peri_gpio0_n:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv16_peri_adc_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv4_peri_pwm_n:1;		// [0]
};
 // SoftResetOff_periSS_2 Register
struct PMU_SOFTRESETOFF_PERISS_2 {
	unsigned int reserved3:15;		// [31:17]
	unsigned int SRST_asyncwrstdiv4_peri_i2sc0_n:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SRST_asyncwrstdiv4_peri_i2so0_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv4_peri_i2si0_n:1;		// [0]
};
 // SoftResetOff_periSS_3 Register
struct PMU_SOFTRESETOFF_PERISS_3 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int SRST_asyncwrstdiv4_peri_spims1_n:1;		// [24]
	unsigned int reserved3:15;		// [23:9]
	unsigned int SRST_asyncwrstdiv4_peri_spims0_n:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_spib0crst_n:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_wrstdiv4_peri_spib0_n:1;		// [0]
};
 // SoftResetOff_periSS_4 Register
struct PMU_SOFTRESETOFF_PERISS_4 {
	unsigned int reserved5:11;		// [31:21]
	unsigned int SRST_asyncuart3rst_n:1;		// [20]
	unsigned int reserved4:3;		// [19:17]
	unsigned int SRST_asyncuart2rst_n:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int SRST_asyncuart1rst_n:1;		// [12]
	unsigned int reserved2:3;		// [11:9]
	unsigned int SRST_asyncuart0rst_n:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SRST_asyncwrstdiv4_peri_uart_n:1;		// [0]
};
 // SoftResetOff_dramcSS_0 Register
struct PMU_SOFTRESETOFF_DRAMCSS_0 {
	unsigned int reserved2:23;		// [31:9]
	unsigned int SRST_mixedwrstdiv2_dramc_n:1;		// [8]
	unsigned int reserved:8;		// [7:0]
};
 // SoftResetOff_mbootSS_0 Register
struct PMU_SOFTRESETOFF_MBOOTSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_asyncwrstdiv2_mboot_n:1;		// [0]
};
 // SoftResetOff_wconfSS_0 Register
struct PMU_SOFTRESETOFF_WCONFSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_asyncwrstdiv4_wconf_n:1;		// [0]
};
 // SoftResetOff_usb2hdSS_0 Register
struct PMU_SOFTRESETOFF_USB2HDSS_0 {
	unsigned int reserved6:17;		// [31:15]
	unsigned int SRST_asyncurst_usb2_udc_n:1;		// [14]
	unsigned int reserved5:1;		// [13]
	unsigned int SRST_asyncwrstdiv2_usb2hd_h_n:1;		// [12]
	unsigned int reserved4:1;		// [11]
	unsigned int SRST_asyncurst_usb2_uhc_n:1;		// [10]
	unsigned int reserved3:1;		// [9]
	unsigned int SRST_asyncwrstdiv2_usb2hd_ohci_n:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int SRST_asyncwrstdiv2_usb2hd_ehci_n:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_asyncurst_usb2_por_n:1;		// [0]
};
 // SoftResetOff_lcdcSS_0 Register
struct PMU_SOFTRESETOFF_LCDCSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_asyncwrstdiv2_lcdc_n:1;		// [0]
};
 // SoftResetOff_yuvcSS_0 Register
struct PMU_SOFTRESETOFF_YUVCSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_wrstdiv2_yuvc_n:1;		// [0]
};
 // SoftResetOff_gfxSS_0 Register
struct PMU_SOFTRESETOFF_GFXSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_asyncwrstdiv2_gfx_n:1;		// [0]
};
 // SoftResetOff_etherSS_0 Register
struct PMU_SOFTRESETOFF_ETHERSS_0 {
	unsigned int reserved2:27;		// [31:5]
	unsigned int SRST_asyncwrstdiv2_ether_n:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int SRST_wrstdiv2_ether_n:1;		// [0]
};
 // SoftResetOff_emmcSS_0 Register
struct PMU_SOFTRESETOFF_EMMCSS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SRST_mixedwrstdiv4_emmc4sd_h_n:1;		// [0]
};
 // SoftResetOff_telomereSS_0 Register
struct PMU_SOFTRESETOFF_TELOMERESS_0 {
	unsigned int reserved3:14;		// [31:18]
	unsigned int SRST_asyncwrstdiv2_emmc8sd_x_n:1;		// [17]
	unsigned int SRST_mixedwrstdiv2_emmc8sd_h_n:1;		// [16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int SRST_mixedwrstdiv2_telomere_n:1;		// [9]
	unsigned int SRST_asyncwrstdiv2_telomere_n:1;		// [8]
	unsigned int reserved:6;		// [7:2]
	unsigned int SRST_nrstdiv2_n:1;		// [1]
	unsigned int SRST_asyncnrstdiv2_n:1;		// [0]
};
 // ClockGatingOnForPower_TOP Register
struct PMU_CLOCKGATINGONFORPOWER_TOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int CGPower_TOP:1;		// [0]
};
 // ClockGatingOnForPower_DRAMC Register
struct PMU_CLOCKGATINGONFORPOWER_DRAMC {
	unsigned int reserved:31;		// [31:1]
	unsigned int CGPower_DRAMC:1;		// [0]
};
 // ClockGatingOffForPower_TOP Register
struct PMU_CLOCKGATINGOFFFORPOWER_TOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int CGPower_TOP:1;		// [0]
};
 // ClockGatingOffForPower_DRAMC Register
struct PMU_CLOCKGATINGOFFFORPOWER_DRAMC {
	unsigned int reserved:31;		// [31:1]
	unsigned int CGPower_DRAMC:1;		// [0]
};
 // POREN Register
struct PMU_POREN {
	unsigned int reserved2:20;		// [31:12]
	unsigned int POREN_TOP:1;		// [11]
	unsigned int POREN_TOP_IOB:1;		// [10]
	unsigned int POREN_TOP_IOA:1;		// [9]
	unsigned int POREN_TOP_EMMC1:1;		// [8]
	unsigned int POREN_TOP_EMMC0:1;		// [7]
	unsigned int POREN_TOP_USB:1;		// [6]
	unsigned int POREN_TOP_ADC:1;		// [5]
	unsigned int POREN_TOP_NAND:1;		// [4]
	unsigned int reserved:3;		// [3:1]
	unsigned int POREN_SYSCON:1;		// [0]
};
 // DDR_Control Register
struct PMU_DDR_CONTROL {
	unsigned int reserved:31;		// [31:1]
	unsigned int PWDN_DDRPHY:1;		// [0]
};
 // USB_Control Register
struct PMU_USB_CONTROL {
	unsigned int reserved:29;		// [31:3]
	unsigned int SHUNT_VDD33_USB:1;		// [2]
	unsigned int PWEN2_VDD33_USB:1;		// [1]
	unsigned int PWEN1_VDD33_USB:1;		// [0]
};
 // NAND_Control Register
struct PMU_NAND_CONTROL {
	unsigned int LDO_PDREGMON:1;		// [31]
	unsigned int reserved2:21;		// [30:10]
	unsigned int LDO_DISEN:1;		// [9]
	unsigned int LDO_PDINT:1;		// [8]
	unsigned int reserved:5;		// [7:3]
	unsigned int SHUNT_VDD33_NAND:1;		// [2]
	unsigned int PWEN2_VDD33_NAND:1;		// [1]
	unsigned int PWEN1_VDD33_NAND:1;		// [0]
};
 // SPI_Control Register
struct PMU_SPI_CONTROL {
	unsigned int reserved:31;		// [31:1]
	unsigned int SPIBIO_DIS:1;		// [0]
};
 // CPU_Clock_Divede_Setting Register
struct PMU_CPU_CLOCK_DIVEDE_SETTING {
	unsigned int ATB_Div:4;		// [31:28]
	unsigned int DAPB_Div:4;		// [27:24]
	unsigned int reserved3:4;		// [23:20]
	unsigned int PERIPH_Div:4;		// [19:16]
	unsigned int reserved2:4;		// [15:12]
	unsigned int Core_Div:4;		// [11:8]
	unsigned int reserved:7;		// [7:1]
	unsigned int DivEn:1;		// [0]
};
 // PANEL_CLOCK_0 Register
struct PMU_PANEL_CLOCK_0 {
	unsigned int reserved:30;		// [31:2]
	unsigned int Frequency_dotclk:2;		// [1:0]
};
 // AUDIO_CLOCK_0 Register
struct PMU_AUDIO_CLOCK_0 {
	unsigned int reserved2:26;		// [31:6]
	unsigned int Frequency_amclk_i2s:2;		// [5:4]
	unsigned int reserved:2;		// [3:2]
	unsigned int Frequency_io_AMCLKO_o:2;		// [1:0]
};
 // UART_CLOCK_0 Register
struct PMU_UART_CLOCK_0 {
	unsigned int reserved4:18;		// [31:14]
	unsigned int uart3clk_sel:2;		// [13:12]
	unsigned int reserved3:2;		// [11:10]
	unsigned int uart2clk_sel:2;		// [9:8]
	unsigned int reserved2:1;		// [7]
	unsigned int uart1clk_sel:3;		// [6:4]
	unsigned int reserved:2;		// [3:2]
	unsigned int uart0clk_sel:2;		// [1:0]
};
 // PLLConfig_PLLLCD_0 Register
struct PMU_PLLCONFIG_PLLLCD_0 {
	unsigned int PLLLCD_SWEN:1;		// [31]
	unsigned int reserved6:1;		// [30]
	unsigned int PLLLCD_ISCP:2;		// [29:28]
	unsigned int reserved5:1;		// [27]
	unsigned int PLLLCD_IVCP:3;		// [26:24]
	unsigned int reserved4:3;		// [23:21]
	unsigned int PLLLCD_BCP:5;		// [20:16]
	unsigned int reserved3:1;		// [15]
	unsigned int PLLLCD_LFR:3;		// [14:12]
	unsigned int reserved2:2;		// [11:10]
	unsigned int PLLLCD_OSW:2;		// [9:8]
	unsigned int reserved:5;		// [7:3]
	unsigned int PLLLCD_RESET:1;		// [2]
	unsigned int PLLLCD_BP:1;		// [1]
	unsigned int PLLLCD_PD:1;		// [0]
};
 // PLLConfig_PLLLCD_1 Register
struct PMU_PLLCONFIG_PLLLCD_1 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int PLLLCD_PRESCL:1;		// [24]
	unsigned int reserved3:4;		// [23:20]
	unsigned int PLLLCD_PSD:4;		// [19:16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int PLLLCD_PRD:5;		// [12:8]
	unsigned int reserved:1;		// [7]
	unsigned int PLLLCD_ND:7;		// [6:0]
};
 // PLLConfig_PLLI2S_0 Register
struct PMU_PLLCONFIG_PLLI2S_0 {
	unsigned int PLLI2S_SWEN:1;		// [31]
	unsigned int reserved6:1;		// [30]
	unsigned int PLLI2S_ISCP:2;		// [29:28]
	unsigned int reserved5:1;		// [27]
	unsigned int PLLI2S_IVCP:3;		// [26:24]
	unsigned int reserved4:3;		// [23:21]
	unsigned int PLLI2S_BCP:5;		// [20:16]
	unsigned int reserved3:1;		// [15]
	unsigned int PLLI2S_LFR:3;		// [14:12]
	unsigned int reserved2:2;		// [11:10]
	unsigned int PLLI2S_OSW:2;		// [9:8]
	unsigned int reserved:5;		// [7:3]
	unsigned int PLLI2S_RESET:1;		// [2]
	unsigned int PLLI2S_BP:1;		// [1]
	unsigned int PLLI2S_PD:1;		// [0]
};
 // PLLConfig_PLLI2S_1 Register
struct PMU_PLLCONFIG_PLLI2S_1 {
	unsigned int reserved4:7;		// [31:25]
	unsigned int PLLI2S_PRESCL:1;		// [24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int PLLI2S_OUTDIV:5;		// [20:16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int PLLI2S_REFDIV:5;		// [12:8]
	unsigned int reserved:8;		// [7:0]
};
 // PLLConfig_PLLI2S_2 Register
struct PMU_PLLCONFIG_PLLI2S_2 {
	unsigned int PLLI2S_NUME:16;		// [31:16]
	unsigned int reserved2:5;		// [15:11]
	unsigned int PLLI2S_MODTYPE:1;		// [10]
	unsigned int PLLI2S_SSCEN:1;		// [9]
	unsigned int PLLI2S_DITHEN:1;		// [8]
	unsigned int reserved:2;		// [7:6]
	unsigned int PLLI2S_INTE:6;		// [5:0]
};
 // PLLConfig_PLLI2S_3 Register
struct PMU_PLLCONFIG_PLLI2S_3 {
	unsigned int PLLI2S_DSFT:16;		// [31:16]
	unsigned int reserved2:1;		// [15]
	unsigned int PLLI2S_FNLEN:7;		// [14:8]
	unsigned int reserved:1;		// [7]
	unsigned int PLLI2S_TRLEN:7;		// [6:0]
};
 // Status_PswAck Register
struct PMU_STATUS_PSWACK {
	unsigned int reserved:31;		// [31:1]
	unsigned int Status_PswAck_TOP:1;		// [0]
};
 // ModeStatus_WatchdogTimer Register
struct PMU_MODESTATUS_WATCHDOGTIMER {
	unsigned int reserved3:19;		// [31:13]
	unsigned int WatchdogTimerFlag_stimer:1;		// [12]
	unsigned int reserved2:3;		// [11:9]
	unsigned int WatchdogTimerFlag_timer:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int WatchdogTimerFlag_cpu:1;		// [0]
};
 // Status_Interrupt Register
struct PMU_STATUS_INTERRUPT {
	unsigned int reserved:30;		// [31:2]
	unsigned int Status_irq_pmu_stop:1;		// [1]
	unsigned int Status_irq_pmu_dfs:1;		// [0]
};
 // Mask_Interrupt Register
struct PMU_MASK_INTERRUPT {
	unsigned int reserved:31;		// [31:1]
	unsigned int Mask_irq_pmu:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PMU_REG_STRUCT_B_H */
