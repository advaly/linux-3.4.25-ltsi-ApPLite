/*
 * arch/arm/mach-tz3000/include/mach/regs/econf_reg_struct_b.h
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

#ifndef _ECONF_REG_STRUCT_B_H
#define _ECONF_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // VDU0_ADDRCONF0 Register
struct ECONF_VDU0_ADDRCONF0 {
	unsigned int BASE:8;		// [31:24]
	unsigned int reserved:24;		// [23:0]
};
 // VDU0_ADDRCONF1 Register
struct ECONF_VDU0_ADDRCONF1 {
	unsigned int reserved3:15;		// [31:17]
	unsigned int SET2:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SET1:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SET0:1;		// [0]
};
 // VDU1_ADDRCONF0 Register
struct ECONF_VDU1_ADDRCONF0 {
	unsigned int BASE:8;		// [31:24]
	unsigned int reserved:24;		// [23:0]
};
 // VDU1_ADDRCONF1 Register
struct ECONF_VDU1_ADDRCONF1 {
	unsigned int reserved3:15;		// [31:17]
	unsigned int SET2:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SET1:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SET0:1;		// [0]
};
 // VEU0_ADDRCONF0 Register
struct ECONF_VEU0_ADDRCONF0 {
	unsigned int BASE:8;		// [31:24]
	unsigned int reserved:24;		// [23:0]
};
 // VEU0_ADDRCONF1 Register
struct ECONF_VEU0_ADDRCONF1 {
	unsigned int reserved3:15;		// [31:17]
	unsigned int SET2:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SET1:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SET0:1;		// [0]
};
 // VDIME_ADDRCONF0 Register
struct ECONF_VDIME_ADDRCONF0 {
	unsigned int BASE:8;		// [31:24]
	unsigned int reserved:24;		// [23:0]
};
 // VDIME_ADDRCONF1 Register
struct ECONF_VDIME_ADDRCONF1 {
	unsigned int reserved3:15;		// [31:17]
	unsigned int SET2:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int SET1:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int SET0:1;		// [0]
};
 // GPIER_PM Register
struct ECONF_GPIER_PM {
	unsigned int reserved2:23;		// [31:9]
	unsigned int POW_DOWN_OK:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int POW_DOWN_REQ:1;		// [0]
};
 // VPIER_PM Register
struct ECONF_VPIER_PM {
	unsigned int reserved2:23;		// [31:9]
	unsigned int POW_DOWN_OK:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int POW_DOWN_REQ:1;		// [0]
};
 // IPIER_PM Register
struct ECONF_IPIER_PM {
	unsigned int reserved2:23;		// [31:9]
	unsigned int POW_DOWN_OK:1;		// [8]
	unsigned int reserved:7;		// [7:1]
	unsigned int POW_DOWN_REQ:1;		// [0]
};
 // VTILE_SETTING Register
struct ECONF_VTILE_SETTING {
	unsigned int reserved:29;		// [31:3]
	unsigned int TOTALPAGESIZE:3;		// [2:0]
};
 // EMMCA_CFG_CAPABILITY0 Register
struct ECONF_EMMCA_CFG_CAPABILITY0 {
	unsigned int SLOTTYPE:2;		// [31:30]
	unsigned int ASYNCINTRSUPPORT:1;		// [29]
	unsigned int SUPPORT64BIT:1;		// [28]
	unsigned int reserved3:1;		// [27]
	unsigned int SUPPORT1P8VOLT:1;		// [26]
	unsigned int SUPPORT3P0VOLT:1;		// [25]
	unsigned int SUPPORT3P3VOLT:1;		// [24]
	unsigned int SUSPRESSUPPORT:1;		// [23]
	unsigned int SDMASUPPORT:1;		// [22]
	unsigned int HIGHSPEEDSUPPORT:1;		// [21]
	unsigned int reserved2:1;		// [20]
	unsigned int ADMA2SUPPORT:1;		// [19]
	unsigned int SUPPORT8BIT:1;		// [18]
	unsigned int MAXBLKLENGTH:2;		// [17:16]
	unsigned int BASECLKFREQ:8;		// [15:8]
	unsigned int TIMEOUTCLKUNIT:1;		// [7]
	unsigned int reserved1:1;		// [6]
	unsigned int TIMEOUTCLKFREQ:6;		// [5:0]
};
 // EMMCA_CFG_CAPABILITY1 Register
struct ECONF_EMMCA_CFG_CAPABILITY1 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int SPIBLKMODE:1;		// [25]
	unsigned int SPISUPPORT:1;		// [24]
	unsigned int CLKMLTPLY:8;		// [23:16]
	unsigned int RETUNINGMODES:2;		// [15:14]
	unsigned int TUNINGFORSDR50:1;		// [13]
	unsigned int reserved3:1;		// [12]
	unsigned int RETUNINGTIMERCNT:4;		// [11:8]
	unsigned int reserved2:1;		// [7]
	unsigned int DDRIVERSUPPORT:1;		// [6]
	unsigned int CDRIVERSUPPORT:1;		// [5]
	unsigned int ADRIVERSUPPORT:1;		// [4]
	unsigned int reserved1:1;		// [3]
	unsigned int DDR50SUPPORT:1;		// [2]
	unsigned int SDR104SUPPORT:1;		// [1]
	unsigned int SDR50SUPPORT:1;		// [0]
};
 // EMMCA_CFG_MAXCURNT Register
struct ECONF_EMMCA_CFG_MAXCURNT {
	unsigned int reserved1:8;		// [31:24]
	unsigned int MAXCRNT1P8V:8;		// [23:16]
	unsigned int MAXCRNT3P0V:8;		// [15:8]
	unsigned int MAXCRNT3P3V:8;		// [7:0]
};
 // EMMCA_CFG_PRESET0 Register
struct ECONF_EMMCA_CFG_PRESET0 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int DSPPRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int INITPRESETVAL:13;		// [12:0]
};
 // EMMCA_CFG_PRESET1 Register
struct ECONF_EMMCA_CFG_PRESET1 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int SDR12PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int HSPPRESETVAL:13;		// [12:0]
};
 // EMMCA_CFG_PRESET2 Register
struct ECONF_EMMCA_CFG_PRESET2 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int SDR50PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int SDR25PRESETVAL:13;		// [12:0]
};
 // EMMCA_CFG_PRESET3 Register
struct ECONF_EMMCA_CFG_PRESET3 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int DDR50PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int SDR104PRESETVAL:13;		// [12:0]
};
 // EMMCA_CFG_WKUP Register
struct ECONF_EMMCA_CFG_WKUP {
	unsigned int reserved1:31;		// [31:1]
	unsigned int ASYNCWKUPEN:1;		// [0]
};
 // EMMCA_CTRL_DLYCHG Register
struct ECONF_EMMCA_CTRL_DLYCHG {
	unsigned int reserved2:15;		// [31:17]
	unsigned int TAPCHGWINSTS:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int TAPCHGWIN:1;		// [0]
};
 // EMMCA_CTRL_INDLY Register
struct ECONF_EMMCA_CTRL_INDLY {
	unsigned int reserved4:3;		// [31:29]
	unsigned int ITAPDLYSELSTS:5;		// [28:24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int ITAPDLYENSTS:1;		// [16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int ITAPDLYSEL:5;		// [12:8]
	unsigned int reserved1:7;		// [7:1]
	unsigned int ITAPDLYEN:1;		// [0]
};
 // EMMCA_CTRL_OUTDLY Register
struct ECONF_EMMCA_CTRL_OUTDLY {
	unsigned int reserved4:4;		// [31:28]
	unsigned int OTAPDLYSELSTS:4;		// [27:24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int OTAPDLYENSTS:1;		// [16]
	unsigned int reserved2:4;		// [15:12]
	unsigned int OTAPDLYSEL:4;		// [11:8]
	unsigned int reserved1:7;		// [7:1]
	unsigned int OTAPDLYEN:1;		// [0]
};
 // EMMCA_CTRL_DLL0 Register
struct ECONF_EMMCA_CTRL_DLL0 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int DLLREADY:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int DLLENABLE:1;		// [0]
};
 // EMMCA_CTRL_DLL1 Register
struct ECONF_EMMCA_CTRL_DLL1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int DLLCLKSELSTS:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int DLLCLKSEL:1;		// [0]
};
 // EMMCB_CFG_CAPABILITY0 Register
struct ECONF_EMMCB_CFG_CAPABILITY0 {
	unsigned int SLOTTYPE:2;		// [31:30]
	unsigned int ASYNCINTRSUPPORT:1;		// [29]
	unsigned int SUPPORT64BIT:1;		// [28]
	unsigned int reserved3:1;		// [27]
	unsigned int SUPPORT1P8VOLT:1;		// [26]
	unsigned int SUPPORT3P0VOLT:1;		// [25]
	unsigned int SUPPORT3P3VOLT:1;		// [24]
	unsigned int SUSPRESSUPPORT:1;		// [23]
	unsigned int SDMASUPPORT:1;		// [22]
	unsigned int HIGHSPEEDSUPPORT:1;		// [21]
	unsigned int reserved2:1;		// [20]
	unsigned int ADMA2SUPPORT:1;		// [19]
	unsigned int SUPPORT8BIT:1;		// [18]
	unsigned int MAXBLKLENGTH:2;		// [17:16]
	unsigned int BASECLKFREQ:8;		// [15:8]
	unsigned int TIMEOUTCLKUNIT:1;		// [7]
	unsigned int reserved1:1;		// [6]
	unsigned int TIMEOUTCLKFREQ:6;		// [5:0]
};
 // EMMCB_CFG_CAPABILITY1 Register
struct ECONF_EMMCB_CFG_CAPABILITY1 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int SPIBLKMODE:1;		// [25]
	unsigned int SPISUPPORT:1;		// [24]
	unsigned int CLKMLTPLY:8;		// [23:16]
	unsigned int RETUNINGMODES:2;		// [15:14]
	unsigned int TUNINGFORSDR50:1;		// [13]
	unsigned int reserved3:1;		// [12]
	unsigned int RETUNINGTIMERCNT:4;		// [11:8]
	unsigned int reserved2:1;		// [7]
	unsigned int DDRIVERSUPPORT:1;		// [6]
	unsigned int CDRIVERSUPPORT:1;		// [5]
	unsigned int ADRIVERSUPPORT:1;		// [4]
	unsigned int reserved1:1;		// [3]
	unsigned int DDR50SUPPORT:1;		// [2]
	unsigned int SDR104SUPPORT:1;		// [1]
	unsigned int SDR50SUPPORT:1;		// [0]
};
 // EMMCB_CFG_MAXCURNT Register
struct ECONF_EMMCB_CFG_MAXCURNT {
	unsigned int reserved1:8;		// [31:24]
	unsigned int MAXCRNT1P8V:8;		// [23:16]
	unsigned int MAXCRNT3P0V:8;		// [15:8]
	unsigned int MAXCRNT3P3V:8;		// [7:0]
};
 // EMMCB_CFG_PRESET0 Register
struct ECONF_EMMCB_CFG_PRESET0 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int DSPPRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int INITPRESETVAL:13;		// [12:0]
};
 // EMMCB_CFG_PRESET1 Register
struct ECONF_EMMCB_CFG_PRESET1 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int SDR12PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int HSPPRESETVAL:13;		// [12:0]
};
 // EMMCB_CFG_PRESET2 Register
struct ECONF_EMMCB_CFG_PRESET2 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int SDR50PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int SDR25PRESETVAL:13;		// [12:0]
};
 // EMMCB_CFG_PRESET3 Register
struct ECONF_EMMCB_CFG_PRESET3 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int DDR50PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int SDR104PRESETVAL:13;		// [12:0]
};
 // EMMCB_CFG_WKUP Register
struct ECONF_EMMCB_CFG_WKUP {
	unsigned int reserved1:31;		// [31:1]
	unsigned int ASYNCWKUPEN:1;		// [0]
};
 // EMMCB_CTRL_DLYCHG Register
struct ECONF_EMMCB_CTRL_DLYCHG {
	unsigned int reserved2:15;		// [31:17]
	unsigned int TAPCHGWINSTS:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int TAPCHGWIN:1;		// [0]
};
 // EMMCB_CTRL_INDLY Register
struct ECONF_EMMCB_CTRL_INDLY {
	unsigned int reserved4:3;		// [31:29]
	unsigned int ITAPDLYSELSTS:5;		// [28:24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int ITAPDLYENSTS:1;		// [16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int ITAPDLYSEL:5;		// [12:8]
	unsigned int reserved1:7;		// [7:1]
	unsigned int ITAPDLYEN:1;		// [0]
};
 // EMMCB_CTRL_OUTDLY Register
struct ECONF_EMMCB_CTRL_OUTDLY {
	unsigned int reserved4:4;		// [31:28]
	unsigned int OTAPDLYSELSTS:4;		// [27:24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int OTAPDLYENSTS:1;		// [16]
	unsigned int reserved2:4;		// [15:12]
	unsigned int OTAPDLYSEL:4;		// [11:8]
	unsigned int reserved1:7;		// [7:1]
	unsigned int OTAPDLYEN:1;		// [0]
};
 // EMMCB_CTRL_DLL0 Register
struct ECONF_EMMCB_CTRL_DLL0 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int DLLREADY:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int DLLENABLE:1;		// [0]
};
 // EMMCB_CTRL_DLL1 Register
struct ECONF_EMMCB_CTRL_DLL1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int DLLCLKSELSTS:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int DLLCLKSEL:1;		// [0]
};
 // EMMCC_CFG_CAPABILITY0 Register
struct ECONF_EMMCC_CFG_CAPABILITY0 {
	unsigned int SLOTTYPE:2;		// [31:30]
	unsigned int ASYNCINTRSUPPORT:1;		// [29]
	unsigned int SUPPORT64BIT:1;		// [28]
	unsigned int reserved3:1;		// [27]
	unsigned int SUPPORT1P8VOLT:1;		// [26]
	unsigned int SUPPORT3P0VOLT:1;		// [25]
	unsigned int SUPPORT3P3VOLT:1;		// [24]
	unsigned int SUSPRESSUPPORT:1;		// [23]
	unsigned int SDMASUPPORT:1;		// [22]
	unsigned int HIGHSPEEDSUPPORT:1;		// [21]
	unsigned int reserved2:1;		// [20]
	unsigned int ADMA2SUPPORT:1;		// [19]
	unsigned int SUPPORT8BIT:1;		// [18]
	unsigned int MAXBLKLENGTH:2;		// [17:16]
	unsigned int BASECLKFREQ:8;		// [15:8]
	unsigned int TIMEOUTCLKUNIT:1;		// [7]
	unsigned int reserved1:1;		// [6]
	unsigned int TIMEOUTCLKFREQ:6;		// [5:0]
};
 // EMMCC_CFG_CAPABILITY1 Register
struct ECONF_EMMCC_CFG_CAPABILITY1 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int SPIBLKMODE:1;		// [25]
	unsigned int SPISUPPORT:1;		// [24]
	unsigned int CLKMLTPLY:8;		// [23:16]
	unsigned int RETUNINGMODES:2;		// [15:14]
	unsigned int TUNINGFORSDR50:1;		// [13]
	unsigned int reserved3:1;		// [12]
	unsigned int RETUNINGTIMERCNT:4;		// [11:8]
	unsigned int reserved2:1;		// [7]
	unsigned int DDRIVERSUPPORT:1;		// [6]
	unsigned int CDRIVERSUPPORT:1;		// [5]
	unsigned int ADRIVERSUPPORT:1;		// [4]
	unsigned int reserved1:1;		// [3]
	unsigned int DDR50SUPPORT:1;		// [2]
	unsigned int SDR104SUPPORT:1;		// [1]
	unsigned int SDR50SUPPORT:1;		// [0]
};
 // EMMCC_CFG_MAXCURNT Register
struct ECONF_EMMCC_CFG_MAXCURNT {
	unsigned int reserved1:8;		// [31:24]
	unsigned int MAXCRNT1P8V:8;		// [23:16]
	unsigned int MAXCRNT3P0V:8;		// [15:8]
	unsigned int MAXCRNT3P3V:8;		// [7:0]
};
 // EMMCC_CFG_PRESET0 Register
struct ECONF_EMMCC_CFG_PRESET0 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int DSPPRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int INITPRESETVAL:13;		// [12:0]
};
 // EMMCC_CFG_PRESET1 Register
struct ECONF_EMMCC_CFG_PRESET1 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int SDR12PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int HSPPRESETVAL:13;		// [12:0]
};
 // EMMCC_CFG_PRESET2 Register
struct ECONF_EMMCC_CFG_PRESET2 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int SDR50PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int SDR25PRESETVAL:13;		// [12:0]
};
 // EMMCC_CFG_PRESET3 Register
struct ECONF_EMMCC_CFG_PRESET3 {
	unsigned int reserved2:3;		// [31:29]
	unsigned int DDR50PRESETVAL:13;		// [28:16]
	unsigned int reserved1:3;		// [15:13]
	unsigned int SDR104PRESETVAL:13;		// [12:0]
};
 // EMMCC_CFG_WKUP Register
struct ECONF_EMMCC_CFG_WKUP {
	unsigned int reserved1:31;		// [31:1]
	unsigned int ASYNCWKUPEN:1;		// [0]
};
 // EMMCC_CTRL_DLYCHG Register
struct ECONF_EMMCC_CTRL_DLYCHG {
	unsigned int reserved2:15;		// [31:17]
	unsigned int TAPCHGWINSTS:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int TAPCHGWIN:1;		// [0]
};
 // EMMCC_CTRL_INDLY Register
struct ECONF_EMMCC_CTRL_INDLY {
	unsigned int reserved4:3;		// [31:29]
	unsigned int ITAPDLYSELSTS:5;		// [28:24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int ITAPDLYENSTS:1;		// [16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int ITAPDLYSEL:5;		// [12:8]
	unsigned int reserved1:7;		// [7:1]
	unsigned int ITAPDLYEN:1;		// [0]
};
 // EMMCC_CTRL_OUTDLY Register
struct ECONF_EMMCC_CTRL_OUTDLY {
	unsigned int reserved4:4;		// [31:28]
	unsigned int OTAPDLYSELSTS:4;		// [27:24]
	unsigned int reserved3:7;		// [23:17]
	unsigned int OTAPDLYENSTS:1;		// [16]
	unsigned int reserved2:4;		// [15:12]
	unsigned int OTAPDLYSEL:4;		// [11:8]
	unsigned int reserved1:7;		// [7:1]
	unsigned int OTAPDLYEN:1;		// [0]
};
 // EMMCC_CTRL_DLL0 Register
struct ECONF_EMMCC_CTRL_DLL0 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int DLLREADY:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int DLLENABLE:1;		// [0]
};
 // EMMCC_CTRL_DLL1 Register
struct ECONF_EMMCC_CTRL_DLL1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int DLLCLKSELSTS:1;		// [16]
	unsigned int reserved1:15;		// [15:1]
	unsigned int DLLCLKSEL:1;		// [0]
};
 // HNANDCTL Register
struct ECONF_HNANDCTL {
	unsigned int reserved1:29;		// [31:3]
	unsigned int ECCMODEODD:1;		// [2]
	unsigned int NACEMSK:1;		// [1]
	unsigned int NANDCSL:1;		// [0]
};
 // PCIEEP_INTCFG Register
struct ECONF_PCIEEP_INTCFG {
	unsigned int reserved2:27;		// [31:5]
	unsigned int MSI_EN:1;		// [4]
	unsigned int reserved1:3;		// [3:1]
	unsigned int INTX_DIS:1;		// [0]
};
 // USB3XHCI_FLADJ Register
struct ECONF_USB3XHCI_FLADJ {
	unsigned int reserved1:26;		// [31:6]
	unsigned int FLADJ:6;		// [5:0]
};
 // USB2PHY_CONFIG0 Register
struct ECONF_USB2PHY_CONFIG0 {
	unsigned int CONFIG0:32;		// [31:0]
};
 // USB2PHY_CONFIG1 Register
struct ECONF_USB2PHY_CONFIG1 {
	unsigned int reserved1:31;		// [31:1]
	unsigned int CONFIG1:1;		// [0]
};
 // HSIO_MUX_CTL Register
struct ECONF_HSIO_MUX_CTL {
	unsigned int reserved2:14;		// [31:18]
	unsigned int HSIO_SSP_REFCLKCORE_EN:1;		// [17]
	unsigned int HSIO_SSP_REFCLK100M_EN:1;		// [16]
	unsigned int reserved1:12;		// [15:4]
	unsigned int HSIO_MUX_SEN:1;		// [3]
	unsigned int HSIO_MUX_SSEL:1;		// [2]
	unsigned int HSIO_MUX_HEN:1;		// [1]
	unsigned int HSIO_MUX_HSEL:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ECONF_REG_STRUCT_B_H */
