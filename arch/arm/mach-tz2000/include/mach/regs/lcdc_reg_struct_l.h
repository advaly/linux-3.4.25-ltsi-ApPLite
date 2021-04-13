/*
 * arch/arm/mach-tz2000/include/mach/regs/lcdc_reg_struct_l.h
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

#ifndef _LCDC_REG_STRUCT_L_H
#define _LCDC_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // GDCDCR_L Register
struct LCDC_GDCDCR_L {
	unsigned int PHDISP:1;		// [0]
	unsigned int PHSYNC:1;		// [1]
	unsigned int PVSYNC:1;		// [2]
	unsigned int CSYNC:1;		// [3]
	unsigned int EXTSYNC:1;		// [4]
	unsigned int reserved3:1;		// [5]
	unsigned int reserved2:1;		// [6]
	unsigned int VORD:1;		// [7]
	unsigned int ARTH:2;		// [9:8]
	unsigned int ARTHCD:1;		// [10]
	unsigned int reserved:1;		// [11]
	unsigned int PDC:1;		// [12]
	unsigned int IDC:1;		// [13]
	unsigned int ADBS:1;		// [14]
	unsigned int FBACT:1;		// [15]
	unsigned int HDISP:1;		// [16]
	unsigned int HSYNC:1;		// [17]
	unsigned int VSYNC:1;		// [18]
	unsigned int GBER:1;		// [19]
	unsigned int A16:1;		// [20]
	unsigned int B16:1;		// [21]
	unsigned int C16:1;		// [22]
	unsigned int D16:1;		// [23]
	unsigned int AEN:1;		// [24]
	unsigned int WAEN:1;		// [25]
	unsigned int BEN:1;		// [26]
	unsigned int WBEN:1;		// [27]
	unsigned int CEN:1;		// [28]
	unsigned int WCEN:1;		// [29]
	unsigned int DEN:1;		// [30]
	unsigned int WDEN:1;		// [31]
};
 // GDCDCR_U Register
struct LCDC_GDCDCR_U {
	unsigned int EEN:1;		// [0]
	unsigned int WEEN:1;		// [1]
	unsigned int reserved5:2;		// [3:2]
	unsigned int E16:1;		// [4]
	unsigned int reserved4:3;		// [7:5]
	unsigned int CCEN:1;		// [8]
	unsigned int SCCEN:1;		// [9]
	unsigned int SCCM:1;		// [10]
	unsigned int reserved3:1;		// [11]
	unsigned int DITHEN:2;		// [13:12]
	unsigned int reserved2:6;		// [19:14]
	unsigned int ARGBEN:1;		// [20]
	unsigned int LAD:1;		// [21]
	unsigned int UPDREG:2;		// [23:22]
	unsigned int GAPEN:1;		// [24]
	unsigned int GAPCOL:1;		// [25]
	unsigned int GAPACC:1;		// [26]
	unsigned int GAPSE:1;		// [27]
	unsigned int reserved:1;		// [28]
	unsigned int PNLIFON:1;		// [29]
	unsigned int DISPIFON:1;		// [30]
	unsigned int GDCON:1;		// [31]
};
 // GDCLARA0_L Register
struct LCDC_GDCLARA0_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCLARA1_L Register
struct LCDC_GDCLARA1_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCWARA_L Register
struct LCDC_GDCWARA_L {
	unsigned int reserved:3;		// [2:0]
	unsigned int WAR:29;		// [31:3]
};
 // GDCBGCR_L Register
struct LCDC_GDCBGCR_L {
	unsigned int reserved:8;		// [7:0]
	unsigned int BGBLUE:8;		// [15:8]
	unsigned int BGGREEN:8;		// [23:16]
	unsigned int BGRED:8;		// [31:24]
};
 // GDCLARB0_L Register
struct LCDC_GDCLARB0_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCLARB1_L Register
struct LCDC_GDCLARB1_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCWARB_L Register
struct LCDC_GDCWARB_L {
	unsigned int reserved:3;		// [2:0]
	unsigned int WAR:29;		// [31:3]
};
 // GDCLARC0_L Register
struct LCDC_GDCLARC0_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCLARC1_L Register
struct LCDC_GDCLARC1_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCLARD0_L Register
struct LCDC_GDCLARD0_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCLARD1_L Register
struct LCDC_GDCLARD1_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCMWRA_L Register
struct LCDC_GDCMWRA_L {
	unsigned int MWR:13;		// [12:0]
	unsigned int reserved:19;		// [31:13]
};
 // GDCMWRB_L Register
struct LCDC_GDCMWRB_L {
	unsigned int MWR:13;		// [12:0]
	unsigned int reserved:19;		// [31:13]
};
 // GDCMWRC_L Register
struct LCDC_GDCMWRC_L {
	unsigned int MWR:13;		// [12:0]
	unsigned int reserved:19;		// [31:13]
};
 // GDCMWRD_L Register
struct LCDC_GDCMWRD_L {
	unsigned int MWR:13;		// [12:0]
	unsigned int reserved:19;		// [31:13]
};
 // GDCMWRE_L Register
struct LCDC_GDCMWRE_L {
	unsigned int MWR:13;		// [12:0]
	unsigned int reserved:19;		// [31:13]
};
 // GDCLSRA_L Register
struct LCDC_GDCLSRA_L {
	unsigned int LVS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int LHS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCLSRB_L Register
struct LCDC_GDCLSRB_L {
	unsigned int LVS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int LHS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCLSRC_L Register
struct LCDC_GDCLSRC_L {
	unsigned int LVS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int LHS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCLSRD_L Register
struct LCDC_GDCLSRD_L {
	unsigned int LVS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int LHS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCLSRE_L Register
struct LCDC_GDCLSRE_L {
	unsigned int LVS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int LHS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCLDRA_L Register
struct LCDC_GDCLDRA_L {
	unsigned int LHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int LWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCLDRB_L Register
struct LCDC_GDCLDRB_L {
	unsigned int LHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int LWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCLDRC_L Register
struct LCDC_GDCLDRC_L {
	unsigned int LHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int LWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCLDRD_L Register
struct LCDC_GDCLDRD_L {
	unsigned int LHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int LWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCLDRE_L Register
struct LCDC_GDCLDRE_L {
	unsigned int LHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int LWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCWSRA_L Register
struct LCDC_GDCWSRA_L {
	unsigned int WVDS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int WHDS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCWSRB_L Register
struct LCDC_GDCWSRB_L {
	unsigned int WVDS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int WHDS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCWIMRA_L Register
struct LCDC_GDCWIMRA_L {
	unsigned int WHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int WWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCWIMRB_L Register
struct LCDC_GDCWIMRB_L {
	unsigned int WHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int WWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCCAVRA_L Register
struct LCDC_GDCCAVRA_L {
	unsigned int ALPHAA:8;		// [7:0]
	unsigned int WALPHAA:8;		// [15:8]
	unsigned int ALPHAB:8;		// [23:16]
	unsigned int WALPHAB:8;		// [31:24]
};
 // GDCCAVRA_U Register
struct LCDC_GDCCAVRA_U {
	unsigned int ALPHAC:8;		// [7:0]
	unsigned int WALPHAC:8;		// [15:8]
	unsigned int ALPHAD:8;		// [23:16]
	unsigned int WALPHAD:8;		// [31:24]
};
 // GDCCAVRB_L Register
struct LCDC_GDCCAVRB_L {
	unsigned int ALPHAE:8;		// [7:0]
	unsigned int WALPHAE:8;		// [15:8]
	unsigned int reserved:16;		// [31:16]
};
 // GDCHSR_L Register
struct LCDC_GDCHSR_L {
	unsigned int HCR:13;		// [12:0]
	unsigned int reserved2:3;		// [15:13]
	unsigned int HSPWR:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // GDCVSR_L Register
struct LCDC_GDCVSR_L {
	unsigned int VCR:11;		// [10:0]
	unsigned int reserved3:5;		// [15:11]
	unsigned int VSPWR:8;		// [23:16]
	unsigned int reserved2:2;		// [25:24]
	unsigned int reserved:6;		// [31:26]
};
 // GDCCBAR0_L Register
struct LCDC_GDCCBAR0_L {
	unsigned int reserved:3;		// [2:0]
	unsigned int CBAR:29;		// [31:3]
};
 // GDCCBAR1_L Register
struct LCDC_GDCCBAR1_L {
	unsigned int reserved:3;		// [2:0]
	unsigned int CBAR:29;		// [31:3]
};
 // GDCCBAR2_L Register
struct LCDC_GDCCBAR2_L {
	unsigned int reserved:3;		// [2:0]
	unsigned int CBAR:29;		// [31:3]
};
 // GDCINTR_L Register
struct LCDC_GDCINTR_L {
	unsigned int GAPMSK:1;		// [0]
	unsigned int HSYNCMSK:1;		// [1]
	unsigned int VSYNCMSK:1;		// [2]
	unsigned int GBERMSK:1;		// [3]
	unsigned int GAPINT:1;		// [4]
	unsigned int HSYNCINT:1;		// [5]
	unsigned int VSYNCINT:1;		// [6]
	unsigned int GBERINT:1;		// [7]
	unsigned int IFURMSK:1;		// [8]
	unsigned int OFURMSK:1;		// [9]
	unsigned int VSLMSK:1;		// [10]
	unsigned int GPEMSK:1;		// [11]
	unsigned int IFURINT:1;		// [12]
	unsigned int OFURINT:1;		// [13]
	unsigned int VSLINT:1;		// [14]
	unsigned int GPEINT:1;		// [15]
	unsigned int LINE:11;		// [26:16]
	unsigned int DLEMSK:1;		// [27]
	unsigned int reserved:3;		// [30:28]
	unsigned int DLEINT:1;		// [31]
};
 // GDCINTR_U Register
struct LCDC_GDCINTR_U {
	unsigned int APCMSK:1;		// [0]
	unsigned int APEMSK:1;		// [1]
	unsigned int reserved2:2;		// [3:2]
	unsigned int APCINT:1;		// [4]
	unsigned int APEINT:1;		// [5]
	unsigned int reserved:26;		// [31:6]
};
 // GDCLARE0_L Register
struct LCDC_GDCLARE0_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCLARE1_L Register
struct LCDC_GDCLARE1_L {
	unsigned int reserved:1;		// [0]
	unsigned int SSCROLL:2;		// [2:1]
	unsigned int SAR:29;		// [31:3]
};
 // GDCWARC_L Register
struct LCDC_GDCWARC_L {
	unsigned int reserved:3;		// [2:0]
	unsigned int WAR:29;		// [31:3]
};
 // GDCWARD_L Register
struct LCDC_GDCWARD_L {
	unsigned int reserved:3;		// [2:0]
	unsigned int WAR:29;		// [31:3]
};
 // GDCWARE_L Register
struct LCDC_GDCWARE_L {
	unsigned int reserved:3;		// [2:0]
	unsigned int WAR:29;		// [31:3]
};
 // GDCWSRC_L Register
struct LCDC_GDCWSRC_L {
	unsigned int WVDS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int WHDS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCWSRD_L Register
struct LCDC_GDCWSRD_L {
	unsigned int WVDS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int WHDS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCWSRE_L Register
struct LCDC_GDCWSRE_L {
	unsigned int WVDS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int WHDS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCWIMRC_L Register
struct LCDC_GDCWIMRC_L {
	unsigned int WHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int WWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCWIMRD_L Register
struct LCDC_GDCWIMRD_L {
	unsigned int WHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int WWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCWIMRE_L Register
struct LCDC_GDCWIMRE_L {
	unsigned int WHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int WWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCSCVRA_L Register
struct LCDC_GDCSCVRA_L {
	unsigned int CCV0:24;		// [23:0]
	unsigned int reserved:7;		// [30:24]
	unsigned int ACT0:1;		// [31]
};
 // GDCSCVRA_U Register
struct LCDC_GDCSCVRA_U {
	unsigned int CCV1:24;		// [23:0]
	unsigned int reserved:7;		// [30:24]
	unsigned int ACT1:1;		// [31]
};
 // GDCSCVRB_L Register
struct LCDC_GDCSCVRB_L {
	unsigned int CCV2:24;		// [23:0]
	unsigned int reserved:7;		// [30:24]
	unsigned int ACT2:1;		// [31]
};
 // GDCSCVRB_U Register
struct LCDC_GDCSCVRB_U {
	unsigned int CCV3:24;		// [23:0]
	unsigned int reserved:7;		// [30:24]
	unsigned int ACT3:1;		// [31]
};
 // GDCSCVRC_L Register
struct LCDC_GDCSCVRC_L {
	unsigned int CCV4:24;		// [23:0]
	unsigned int reserved:7;		// [30:24]
	unsigned int ACT4:1;		// [31]
};
 // GDCSCVRC_U Register
struct LCDC_GDCSCVRC_U {
	unsigned int CCV5:24;		// [23:0]
	unsigned int reserved:7;		// [30:24]
	unsigned int ACT5:1;		// [31]
};
 // GDCSCVRD_L Register
struct LCDC_GDCSCVRD_L {
	unsigned int CCV6:24;		// [23:0]
	unsigned int reserved:7;		// [30:24]
	unsigned int ACT6:1;		// [31]
};
 // GDCSCVRD_U Register
struct LCDC_GDCSCVRD_U {
	unsigned int CCV7:24;		// [23:0]
	unsigned int reserved:7;		// [30:24]
	unsigned int ACT7:1;		// [31]
};
 // GDCGCAR_L Register
struct LCDC_GDCGCAR_L {
	unsigned int GCAR:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDCDSR_L Register
struct LCDC_GDCDSR_L {
	unsigned int DVS:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int DHS:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // GDCDIMR_L Register
struct LCDC_GDCDIMR_L {
	unsigned int DHEIGHT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int DWIDTH:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // GDCPROTR_L Register
struct LCDC_GDCPROTR_L {
	unsigned int GDCWPL:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // GDCGBEAR_L Register
struct LCDC_GDCGBEAR_L {
	unsigned int GBADDR:32;		// [31:0]
};
 // GDCGBECR_L Register
struct LCDC_GDCGBECR_L {
	unsigned int WR:1;		// [0]
	unsigned int BTYPE:1;		// [1]
	unsigned int BSIZE:3;		// [4:2]
	unsigned int RTYPE:2;		// [6:5]
	unsigned int reserved2:1;		// [7]
	unsigned int BEN:8;		// [15:8]
	unsigned int ID:4;		// [19:16]
	unsigned int LEN:4;		// [23:20]
	unsigned int reserved:8;		// [31:24]
};
 // APCCR_L Register
struct LCDC_APCCR_L {
	unsigned int CHKFR:7;		// [6:0]
	unsigned int CHKERR:1;		// [7]
	unsigned int reserved:22;		// [29:8]
	unsigned int AUTO:1;		// [30]
	unsigned int APCON:1;		// [31]
};
 // APCCR_U Register
struct LCDC_APCCR_U {
	unsigned int PG:7;		// [6:0]
	unsigned int reserved2:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // APCCWR_L Register
struct LCDC_APCCWR_L {
	unsigned int VCWS:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int HCWS:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // APCCWR_U Register
struct LCDC_APCCWR_U {
	unsigned int CWHEIGHT:7;		// [6:0]
	unsigned int reserved2:9;		// [15:7]
	unsigned int CWWIDTH:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // APCCSR_L Register
struct LCDC_APCCSR_L {
	unsigned int CURCHKSUM:22;		// [21:0]
	unsigned int reserved:10;		// [31:22]
};
 // APCCSR_U Register
struct LCDC_APCCSR_U {
	unsigned int EXPCHKSUM:22;		// [21:0]
	unsigned int reserved:10;		// [31:22]
};
 // APCPVR_L Register
struct LCDC_APCPVR_L {
	unsigned int BLUEL:8;		// [7:0]
	unsigned int GREENL:8;		// [15:8]
	unsigned int REDL:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // APCPVR_U Register
struct LCDC_APCPVR_U {
	unsigned int BLUEP:8;		// [7:0]
	unsigned int GREENP:8;		// [15:8]
	unsigned int REDP:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // APCPROTR_L Register
struct LCDC_APCPROTR_L {
	unsigned int APCWPL:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // GDCCCLUTR0_L Register
struct LCDC_GDCCCLUTR0_L {
	unsigned int CLUTR0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR0_U Register
struct LCDC_GDCCCLUTR0_U {
	unsigned int CLUTR1:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR1_L Register
struct LCDC_GDCCCLUTR1_L {
	unsigned int CLUTR2:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR1_U Register
struct LCDC_GDCCCLUTR1_U {
	unsigned int CLUTR3:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR2_L Register
struct LCDC_GDCCCLUTR2_L {
	unsigned int CLUTR4:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR2_U Register
struct LCDC_GDCCCLUTR2_U {
	unsigned int CLUTR5:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR3_L Register
struct LCDC_GDCCCLUTR3_L {
	unsigned int CLUTR6:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR3_U Register
struct LCDC_GDCCCLUTR3_U {
	unsigned int CLUTR7:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR4_L Register
struct LCDC_GDCCCLUTR4_L {
	unsigned int CLUTR8:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR4_U Register
struct LCDC_GDCCCLUTR4_U {
	unsigned int CLUTR9:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR5_L Register
struct LCDC_GDCCCLUTR5_L {
	unsigned int CLUTR10:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR5_U Register
struct LCDC_GDCCCLUTR5_U {
	unsigned int CLUTR11:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR6_L Register
struct LCDC_GDCCCLUTR6_L {
	unsigned int CLUTR12:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR6_U Register
struct LCDC_GDCCCLUTR6_U {
	unsigned int CLUTR13:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR7_L Register
struct LCDC_GDCCCLUTR7_L {
	unsigned int CLUTR14:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR7_U Register
struct LCDC_GDCCCLUTR7_U {
	unsigned int CLUTR15:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR8_L Register
struct LCDC_GDCCCLUTR8_L {
	unsigned int CLUTR16:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR8_U Register
struct LCDC_GDCCCLUTR8_U {
	unsigned int CLUTR17:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR9_L Register
struct LCDC_GDCCCLUTR9_L {
	unsigned int CLUTR18:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR9_U Register
struct LCDC_GDCCCLUTR9_U {
	unsigned int CLUTR19:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR10_L Register
struct LCDC_GDCCCLUTR10_L {
	unsigned int CLUTR20:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR10_U Register
struct LCDC_GDCCCLUTR10_U {
	unsigned int CLUTR21:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR11_L Register
struct LCDC_GDCCCLUTR11_L {
	unsigned int CLUTR22:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR11_U Register
struct LCDC_GDCCCLUTR11_U {
	unsigned int CLUTR23:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR12_L Register
struct LCDC_GDCCCLUTR12_L {
	unsigned int CLUTR24:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR12_U Register
struct LCDC_GDCCCLUTR12_U {
	unsigned int CLUTR25:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR13_L Register
struct LCDC_GDCCCLUTR13_L {
	unsigned int CLUTR26:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR13_U Register
struct LCDC_GDCCCLUTR13_U {
	unsigned int CLUTR27:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR14_L Register
struct LCDC_GDCCCLUTR14_L {
	unsigned int CLUTR28:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR14_U Register
struct LCDC_GDCCCLUTR14_U {
	unsigned int CLUTR29:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR15_L Register
struct LCDC_GDCCCLUTR15_L {
	unsigned int CLUTR30:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR15_U Register
struct LCDC_GDCCCLUTR15_U {
	unsigned int CLUTR31:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR16_L Register
struct LCDC_GDCCCLUTR16_L {
	unsigned int CLUTR32:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR16_U Register
struct LCDC_GDCCCLUTR16_U {
	unsigned int CLUTR33:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR17_L Register
struct LCDC_GDCCCLUTR17_L {
	unsigned int CLUTR34:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR17_U Register
struct LCDC_GDCCCLUTR17_U {
	unsigned int CLUTR35:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR18_L Register
struct LCDC_GDCCCLUTR18_L {
	unsigned int CLUTR36:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR18_U Register
struct LCDC_GDCCCLUTR18_U {
	unsigned int CLUTR37:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR19_L Register
struct LCDC_GDCCCLUTR19_L {
	unsigned int CLUTR38:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR19_U Register
struct LCDC_GDCCCLUTR19_U {
	unsigned int CLUTR39:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR20_L Register
struct LCDC_GDCCCLUTR20_L {
	unsigned int CLUTR40:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR20_U Register
struct LCDC_GDCCCLUTR20_U {
	unsigned int CLUTR41:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR21_L Register
struct LCDC_GDCCCLUTR21_L {
	unsigned int CLUTR42:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR21_U Register
struct LCDC_GDCCCLUTR21_U {
	unsigned int CLUTR43:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR22_L Register
struct LCDC_GDCCCLUTR22_L {
	unsigned int CLUTR44:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR22_U Register
struct LCDC_GDCCCLUTR22_U {
	unsigned int CLUTR45:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR23_L Register
struct LCDC_GDCCCLUTR23_L {
	unsigned int CLUTR46:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR23_U Register
struct LCDC_GDCCCLUTR23_U {
	unsigned int CLUTR47:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR24_L Register
struct LCDC_GDCCCLUTR24_L {
	unsigned int CLUTR48:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR24_U Register
struct LCDC_GDCCCLUTR24_U {
	unsigned int CLUTR49:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR25_L Register
struct LCDC_GDCCCLUTR25_L {
	unsigned int CLUTR50:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR25_U Register
struct LCDC_GDCCCLUTR25_U {
	unsigned int CLUTR51:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR26_L Register
struct LCDC_GDCCCLUTR26_L {
	unsigned int CLUTR52:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR26_U Register
struct LCDC_GDCCCLUTR26_U {
	unsigned int CLUTR53:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR27_L Register
struct LCDC_GDCCCLUTR27_L {
	unsigned int CLUTR54:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR27_U Register
struct LCDC_GDCCCLUTR27_U {
	unsigned int CLUTR55:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR28_L Register
struct LCDC_GDCCCLUTR28_L {
	unsigned int CLUTR56:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR28_U Register
struct LCDC_GDCCCLUTR28_U {
	unsigned int CLUTR57:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR29_L Register
struct LCDC_GDCCCLUTR29_L {
	unsigned int CLUTR58:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR29_U Register
struct LCDC_GDCCCLUTR29_U {
	unsigned int CLUTR59:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR30_L Register
struct LCDC_GDCCCLUTR30_L {
	unsigned int CLUTR60:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR30_U Register
struct LCDC_GDCCCLUTR30_U {
	unsigned int CLUTR61:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR31_L Register
struct LCDC_GDCCCLUTR31_L {
	unsigned int CLUTR62:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR31_U Register
struct LCDC_GDCCCLUTR31_U {
	unsigned int CLUTR63:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR32_L Register
struct LCDC_GDCCCLUTR32_L {
	unsigned int CLUTR64:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR32_U Register
struct LCDC_GDCCCLUTR32_U {
	unsigned int CLUTR65:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR33_L Register
struct LCDC_GDCCCLUTR33_L {
	unsigned int CLUTR66:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR33_U Register
struct LCDC_GDCCCLUTR33_U {
	unsigned int CLUTR67:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR34_L Register
struct LCDC_GDCCCLUTR34_L {
	unsigned int CLUTR68:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR34_U Register
struct LCDC_GDCCCLUTR34_U {
	unsigned int CLUTR69:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR35_L Register
struct LCDC_GDCCCLUTR35_L {
	unsigned int CLUTR70:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR35_U Register
struct LCDC_GDCCCLUTR35_U {
	unsigned int CLUTR71:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR36_L Register
struct LCDC_GDCCCLUTR36_L {
	unsigned int CLUTR72:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR36_U Register
struct LCDC_GDCCCLUTR36_U {
	unsigned int CLUTR73:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR37_L Register
struct LCDC_GDCCCLUTR37_L {
	unsigned int CLUTR74:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR37_U Register
struct LCDC_GDCCCLUTR37_U {
	unsigned int CLUTR75:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR38_L Register
struct LCDC_GDCCCLUTR38_L {
	unsigned int CLUTR76:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR38_U Register
struct LCDC_GDCCCLUTR38_U {
	unsigned int CLUTR77:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR39_L Register
struct LCDC_GDCCCLUTR39_L {
	unsigned int CLUTR78:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR39_U Register
struct LCDC_GDCCCLUTR39_U {
	unsigned int CLUTR79:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR40_L Register
struct LCDC_GDCCCLUTR40_L {
	unsigned int CLUTR80:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR40_U Register
struct LCDC_GDCCCLUTR40_U {
	unsigned int CLUTR81:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR41_L Register
struct LCDC_GDCCCLUTR41_L {
	unsigned int CLUTR82:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR41_U Register
struct LCDC_GDCCCLUTR41_U {
	unsigned int CLUTR83:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR42_L Register
struct LCDC_GDCCCLUTR42_L {
	unsigned int CLUTR84:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR42_U Register
struct LCDC_GDCCCLUTR42_U {
	unsigned int CLUTR85:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR43_L Register
struct LCDC_GDCCCLUTR43_L {
	unsigned int CLUTR86:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR43_U Register
struct LCDC_GDCCCLUTR43_U {
	unsigned int CLUTR87:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR44_L Register
struct LCDC_GDCCCLUTR44_L {
	unsigned int CLUTR88:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR44_U Register
struct LCDC_GDCCCLUTR44_U {
	unsigned int CLUTR89:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR45_L Register
struct LCDC_GDCCCLUTR45_L {
	unsigned int CLUTR90:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR45_U Register
struct LCDC_GDCCCLUTR45_U {
	unsigned int CLUTR91:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR46_L Register
struct LCDC_GDCCCLUTR46_L {
	unsigned int CLUTR92:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR46_U Register
struct LCDC_GDCCCLUTR46_U {
	unsigned int CLUTR93:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR47_L Register
struct LCDC_GDCCCLUTR47_L {
	unsigned int CLUTR94:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR47_U Register
struct LCDC_GDCCCLUTR47_U {
	unsigned int CLUTR95:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR48_L Register
struct LCDC_GDCCCLUTR48_L {
	unsigned int CLUTR96:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR48_U Register
struct LCDC_GDCCCLUTR48_U {
	unsigned int CLUTR97:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR49_L Register
struct LCDC_GDCCCLUTR49_L {
	unsigned int CLUTR98:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR49_U Register
struct LCDC_GDCCCLUTR49_U {
	unsigned int CLUTR99:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR50_L Register
struct LCDC_GDCCCLUTR50_L {
	unsigned int CLUTR100:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR50_U Register
struct LCDC_GDCCCLUTR50_U {
	unsigned int CLUTR101:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR51_L Register
struct LCDC_GDCCCLUTR51_L {
	unsigned int CLUTR102:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR51_U Register
struct LCDC_GDCCCLUTR51_U {
	unsigned int CLUTR103:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR52_L Register
struct LCDC_GDCCCLUTR52_L {
	unsigned int CLUTR104:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR52_U Register
struct LCDC_GDCCCLUTR52_U {
	unsigned int CLUTR105:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR53_L Register
struct LCDC_GDCCCLUTR53_L {
	unsigned int CLUTR106:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR53_U Register
struct LCDC_GDCCCLUTR53_U {
	unsigned int CLUTR107:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR54_L Register
struct LCDC_GDCCCLUTR54_L {
	unsigned int CLUTR108:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR54_U Register
struct LCDC_GDCCCLUTR54_U {
	unsigned int CLUTR109:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR55_L Register
struct LCDC_GDCCCLUTR55_L {
	unsigned int CLUTR110:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR55_U Register
struct LCDC_GDCCCLUTR55_U {
	unsigned int CLUTR111:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR56_L Register
struct LCDC_GDCCCLUTR56_L {
	unsigned int CLUTR112:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR56_U Register
struct LCDC_GDCCCLUTR56_U {
	unsigned int CLUTR113:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR57_L Register
struct LCDC_GDCCCLUTR57_L {
	unsigned int CLUTR114:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR57_U Register
struct LCDC_GDCCCLUTR57_U {
	unsigned int CLUTR115:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR58_L Register
struct LCDC_GDCCCLUTR58_L {
	unsigned int CLUTR116:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR58_U Register
struct LCDC_GDCCCLUTR58_U {
	unsigned int CLUTR117:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR59_L Register
struct LCDC_GDCCCLUTR59_L {
	unsigned int CLUTR118:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR59_U Register
struct LCDC_GDCCCLUTR59_U {
	unsigned int CLUTR119:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR60_L Register
struct LCDC_GDCCCLUTR60_L {
	unsigned int CLUTR120:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR60_U Register
struct LCDC_GDCCCLUTR60_U {
	unsigned int CLUTR121:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR61_L Register
struct LCDC_GDCCCLUTR61_L {
	unsigned int CLUTR122:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR61_U Register
struct LCDC_GDCCCLUTR61_U {
	unsigned int CLUTR123:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR62_L Register
struct LCDC_GDCCCLUTR62_L {
	unsigned int CLUTR124:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR62_U Register
struct LCDC_GDCCCLUTR62_U {
	unsigned int CLUTR125:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR63_L Register
struct LCDC_GDCCCLUTR63_L {
	unsigned int CLUTR126:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR63_U Register
struct LCDC_GDCCCLUTR63_U {
	unsigned int CLUTR127:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR64_L Register
struct LCDC_GDCCCLUTR64_L {
	unsigned int CLUTR128:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR64_U Register
struct LCDC_GDCCCLUTR64_U {
	unsigned int CLUTR129:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR65_L Register
struct LCDC_GDCCCLUTR65_L {
	unsigned int CLUTR130:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR65_U Register
struct LCDC_GDCCCLUTR65_U {
	unsigned int CLUTR131:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR66_L Register
struct LCDC_GDCCCLUTR66_L {
	unsigned int CLUTR132:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR66_U Register
struct LCDC_GDCCCLUTR66_U {
	unsigned int CLUTR133:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR67_L Register
struct LCDC_GDCCCLUTR67_L {
	unsigned int CLUTR134:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR67_U Register
struct LCDC_GDCCCLUTR67_U {
	unsigned int CLUTR135:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR68_L Register
struct LCDC_GDCCCLUTR68_L {
	unsigned int CLUTR136:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR68_U Register
struct LCDC_GDCCCLUTR68_U {
	unsigned int CLUTR137:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR69_L Register
struct LCDC_GDCCCLUTR69_L {
	unsigned int CLUTR138:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR69_U Register
struct LCDC_GDCCCLUTR69_U {
	unsigned int CLUTR139:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR70_L Register
struct LCDC_GDCCCLUTR70_L {
	unsigned int CLUTR140:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR70_U Register
struct LCDC_GDCCCLUTR70_U {
	unsigned int CLUTR141:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR71_L Register
struct LCDC_GDCCCLUTR71_L {
	unsigned int CLUTR142:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR71_U Register
struct LCDC_GDCCCLUTR71_U {
	unsigned int CLUTR143:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR72_L Register
struct LCDC_GDCCCLUTR72_L {
	unsigned int CLUTR144:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR72_U Register
struct LCDC_GDCCCLUTR72_U {
	unsigned int CLUTR145:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR73_L Register
struct LCDC_GDCCCLUTR73_L {
	unsigned int CLUTR146:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR73_U Register
struct LCDC_GDCCCLUTR73_U {
	unsigned int CLUTR147:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR74_L Register
struct LCDC_GDCCCLUTR74_L {
	unsigned int CLUTR148:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR74_U Register
struct LCDC_GDCCCLUTR74_U {
	unsigned int CLUTR149:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR75_L Register
struct LCDC_GDCCCLUTR75_L {
	unsigned int CLUTR150:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR75_U Register
struct LCDC_GDCCCLUTR75_U {
	unsigned int CLUTR151:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR76_L Register
struct LCDC_GDCCCLUTR76_L {
	unsigned int CLUTR152:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR76_U Register
struct LCDC_GDCCCLUTR76_U {
	unsigned int CLUTR153:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR77_L Register
struct LCDC_GDCCCLUTR77_L {
	unsigned int CLUTR154:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR77_U Register
struct LCDC_GDCCCLUTR77_U {
	unsigned int CLUTR155:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR78_L Register
struct LCDC_GDCCCLUTR78_L {
	unsigned int CLUTR156:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR78_U Register
struct LCDC_GDCCCLUTR78_U {
	unsigned int CLUTR157:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR79_L Register
struct LCDC_GDCCCLUTR79_L {
	unsigned int CLUTR158:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR79_U Register
struct LCDC_GDCCCLUTR79_U {
	unsigned int CLUTR159:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR80_L Register
struct LCDC_GDCCCLUTR80_L {
	unsigned int CLUTR160:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR80_U Register
struct LCDC_GDCCCLUTR80_U {
	unsigned int CLUTR161:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR81_L Register
struct LCDC_GDCCCLUTR81_L {
	unsigned int CLUTR162:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR81_U Register
struct LCDC_GDCCCLUTR81_U {
	unsigned int CLUTR163:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR82_L Register
struct LCDC_GDCCCLUTR82_L {
	unsigned int CLUTR164:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR82_U Register
struct LCDC_GDCCCLUTR82_U {
	unsigned int CLUTR165:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR83_L Register
struct LCDC_GDCCCLUTR83_L {
	unsigned int CLUTR166:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR83_U Register
struct LCDC_GDCCCLUTR83_U {
	unsigned int CLUTR167:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR84_L Register
struct LCDC_GDCCCLUTR84_L {
	unsigned int CLUTR168:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR84_U Register
struct LCDC_GDCCCLUTR84_U {
	unsigned int CLUTR169:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR85_L Register
struct LCDC_GDCCCLUTR85_L {
	unsigned int CLUTR170:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR85_U Register
struct LCDC_GDCCCLUTR85_U {
	unsigned int CLUTR171:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR86_L Register
struct LCDC_GDCCCLUTR86_L {
	unsigned int CLUTR172:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR86_U Register
struct LCDC_GDCCCLUTR86_U {
	unsigned int CLUTR173:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR87_L Register
struct LCDC_GDCCCLUTR87_L {
	unsigned int CLUTR174:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR87_U Register
struct LCDC_GDCCCLUTR87_U {
	unsigned int CLUTR175:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR88_L Register
struct LCDC_GDCCCLUTR88_L {
	unsigned int CLUTR176:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR88_U Register
struct LCDC_GDCCCLUTR88_U {
	unsigned int CLUTR177:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR89_L Register
struct LCDC_GDCCCLUTR89_L {
	unsigned int CLUTR178:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR89_U Register
struct LCDC_GDCCCLUTR89_U {
	unsigned int CLUTR179:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR90_L Register
struct LCDC_GDCCCLUTR90_L {
	unsigned int CLUTR180:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR90_U Register
struct LCDC_GDCCCLUTR90_U {
	unsigned int CLUTR181:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR91_L Register
struct LCDC_GDCCCLUTR91_L {
	unsigned int CLUTR182:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR91_U Register
struct LCDC_GDCCCLUTR91_U {
	unsigned int CLUTR183:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR92_L Register
struct LCDC_GDCCCLUTR92_L {
	unsigned int CLUTR184:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR92_U Register
struct LCDC_GDCCCLUTR92_U {
	unsigned int CLUTR185:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR93_L Register
struct LCDC_GDCCCLUTR93_L {
	unsigned int CLUTR186:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR93_U Register
struct LCDC_GDCCCLUTR93_U {
	unsigned int CLUTR187:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR94_L Register
struct LCDC_GDCCCLUTR94_L {
	unsigned int CLUTR188:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR94_U Register
struct LCDC_GDCCCLUTR94_U {
	unsigned int CLUTR189:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR95_L Register
struct LCDC_GDCCCLUTR95_L {
	unsigned int CLUTR190:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR95_U Register
struct LCDC_GDCCCLUTR95_U {
	unsigned int CLUTR191:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR96_L Register
struct LCDC_GDCCCLUTR96_L {
	unsigned int CLUTR192:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR96_U Register
struct LCDC_GDCCCLUTR96_U {
	unsigned int CLUTR193:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR97_L Register
struct LCDC_GDCCCLUTR97_L {
	unsigned int CLUTR194:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR97_U Register
struct LCDC_GDCCCLUTR97_U {
	unsigned int CLUTR195:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR98_L Register
struct LCDC_GDCCCLUTR98_L {
	unsigned int CLUTR196:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR98_U Register
struct LCDC_GDCCCLUTR98_U {
	unsigned int CLUTR197:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR99_L Register
struct LCDC_GDCCCLUTR99_L {
	unsigned int CLUTR198:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR99_U Register
struct LCDC_GDCCCLUTR99_U {
	unsigned int CLUTR199:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR100_L Register
struct LCDC_GDCCCLUTR100_L {
	unsigned int CLUTR200:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR100_U Register
struct LCDC_GDCCCLUTR100_U {
	unsigned int CLUTR201:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR101_L Register
struct LCDC_GDCCCLUTR101_L {
	unsigned int CLUTR202:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR101_U Register
struct LCDC_GDCCCLUTR101_U {
	unsigned int CLUTR203:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR102_L Register
struct LCDC_GDCCCLUTR102_L {
	unsigned int CLUTR204:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR102_U Register
struct LCDC_GDCCCLUTR102_U {
	unsigned int CLUTR205:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR103_L Register
struct LCDC_GDCCCLUTR103_L {
	unsigned int CLUTR206:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR103_U Register
struct LCDC_GDCCCLUTR103_U {
	unsigned int CLUTR207:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR104_L Register
struct LCDC_GDCCCLUTR104_L {
	unsigned int CLUTR208:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR104_U Register
struct LCDC_GDCCCLUTR104_U {
	unsigned int CLUTR209:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR105_L Register
struct LCDC_GDCCCLUTR105_L {
	unsigned int CLUTR210:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR105_U Register
struct LCDC_GDCCCLUTR105_U {
	unsigned int CLUTR211:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR106_L Register
struct LCDC_GDCCCLUTR106_L {
	unsigned int CLUTR212:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR106_U Register
struct LCDC_GDCCCLUTR106_U {
	unsigned int CLUTR213:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR107_L Register
struct LCDC_GDCCCLUTR107_L {
	unsigned int CLUTR214:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR107_U Register
struct LCDC_GDCCCLUTR107_U {
	unsigned int CLUTR215:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR108_L Register
struct LCDC_GDCCCLUTR108_L {
	unsigned int CLUTR216:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR108_U Register
struct LCDC_GDCCCLUTR108_U {
	unsigned int CLUTR217:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR109_L Register
struct LCDC_GDCCCLUTR109_L {
	unsigned int CLUTR218:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR109_U Register
struct LCDC_GDCCCLUTR109_U {
	unsigned int CLUTR219:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR110_L Register
struct LCDC_GDCCCLUTR110_L {
	unsigned int CLUTR220:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR110_U Register
struct LCDC_GDCCCLUTR110_U {
	unsigned int CLUTR221:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR111_L Register
struct LCDC_GDCCCLUTR111_L {
	unsigned int CLUTR222:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR111_U Register
struct LCDC_GDCCCLUTR111_U {
	unsigned int CLUTR223:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR112_L Register
struct LCDC_GDCCCLUTR112_L {
	unsigned int CLUTR224:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR112_U Register
struct LCDC_GDCCCLUTR112_U {
	unsigned int CLUTR225:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR113_L Register
struct LCDC_GDCCCLUTR113_L {
	unsigned int CLUTR226:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR113_U Register
struct LCDC_GDCCCLUTR113_U {
	unsigned int CLUTR227:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR114_L Register
struct LCDC_GDCCCLUTR114_L {
	unsigned int CLUTR228:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR114_U Register
struct LCDC_GDCCCLUTR114_U {
	unsigned int CLUTR229:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR115_L Register
struct LCDC_GDCCCLUTR115_L {
	unsigned int CLUTR230:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR115_U Register
struct LCDC_GDCCCLUTR115_U {
	unsigned int CLUTR231:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR116_L Register
struct LCDC_GDCCCLUTR116_L {
	unsigned int CLUTR232:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR116_U Register
struct LCDC_GDCCCLUTR116_U {
	unsigned int CLUTR233:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR117_L Register
struct LCDC_GDCCCLUTR117_L {
	unsigned int CLUTR234:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR117_U Register
struct LCDC_GDCCCLUTR117_U {
	unsigned int CLUTR235:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR118_L Register
struct LCDC_GDCCCLUTR118_L {
	unsigned int CLUTR236:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR118_U Register
struct LCDC_GDCCCLUTR118_U {
	unsigned int CLUTR237:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR119_L Register
struct LCDC_GDCCCLUTR119_L {
	unsigned int CLUTR238:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR119_U Register
struct LCDC_GDCCCLUTR119_U {
	unsigned int CLUTR239:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR120_L Register
struct LCDC_GDCCCLUTR120_L {
	unsigned int CLUTR240:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR120_U Register
struct LCDC_GDCCCLUTR120_U {
	unsigned int CLUTR241:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR121_L Register
struct LCDC_GDCCCLUTR121_L {
	unsigned int CLUTR242:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR121_U Register
struct LCDC_GDCCCLUTR121_U {
	unsigned int CLUTR243:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR122_L Register
struct LCDC_GDCCCLUTR122_L {
	unsigned int CLUTR244:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR122_U Register
struct LCDC_GDCCCLUTR122_U {
	unsigned int CLUTR245:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR123_L Register
struct LCDC_GDCCCLUTR123_L {
	unsigned int CLUTR246:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR123_U Register
struct LCDC_GDCCCLUTR123_U {
	unsigned int CLUTR247:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR124_L Register
struct LCDC_GDCCCLUTR124_L {
	unsigned int CLUTR248:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR124_U Register
struct LCDC_GDCCCLUTR124_U {
	unsigned int CLUTR249:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR125_L Register
struct LCDC_GDCCCLUTR125_L {
	unsigned int CLUTR250:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR125_U Register
struct LCDC_GDCCCLUTR125_U {
	unsigned int CLUTR251:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR126_L Register
struct LCDC_GDCCCLUTR126_L {
	unsigned int CLUTR252:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR126_U Register
struct LCDC_GDCCCLUTR126_U {
	unsigned int CLUTR253:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR127_L Register
struct LCDC_GDCCCLUTR127_L {
	unsigned int CLUTR254:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTR127_U Register
struct LCDC_GDCCCLUTR127_U {
	unsigned int CLUTR255:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG0_L Register
struct LCDC_GDCCCLUTG0_L {
	unsigned int CLUTG0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG0_U Register
struct LCDC_GDCCCLUTG0_U {
	unsigned int CLUTG1:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG1_L Register
struct LCDC_GDCCCLUTG1_L {
	unsigned int CLUTG2:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG1_U Register
struct LCDC_GDCCCLUTG1_U {
	unsigned int CLUTG3:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG2_L Register
struct LCDC_GDCCCLUTG2_L {
	unsigned int CLUTG4:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG2_U Register
struct LCDC_GDCCCLUTG2_U {
	unsigned int CLUTG5:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG3_L Register
struct LCDC_GDCCCLUTG3_L {
	unsigned int CLUTG6:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG3_U Register
struct LCDC_GDCCCLUTG3_U {
	unsigned int CLUTG7:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG4_L Register
struct LCDC_GDCCCLUTG4_L {
	unsigned int CLUTG8:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG4_U Register
struct LCDC_GDCCCLUTG4_U {
	unsigned int CLUTG9:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG5_L Register
struct LCDC_GDCCCLUTG5_L {
	unsigned int CLUTG10:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG5_U Register
struct LCDC_GDCCCLUTG5_U {
	unsigned int CLUTG11:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG6_L Register
struct LCDC_GDCCCLUTG6_L {
	unsigned int CLUTG12:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG6_U Register
struct LCDC_GDCCCLUTG6_U {
	unsigned int CLUTG13:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG7_L Register
struct LCDC_GDCCCLUTG7_L {
	unsigned int CLUTG14:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG7_U Register
struct LCDC_GDCCCLUTG7_U {
	unsigned int CLUTG15:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG8_L Register
struct LCDC_GDCCCLUTG8_L {
	unsigned int CLUTG16:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG8_U Register
struct LCDC_GDCCCLUTG8_U {
	unsigned int CLUTG17:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG9_L Register
struct LCDC_GDCCCLUTG9_L {
	unsigned int CLUTG18:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG9_U Register
struct LCDC_GDCCCLUTG9_U {
	unsigned int CLUTG19:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG10_L Register
struct LCDC_GDCCCLUTG10_L {
	unsigned int CLUTG20:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG10_U Register
struct LCDC_GDCCCLUTG10_U {
	unsigned int CLUTG21:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG11_L Register
struct LCDC_GDCCCLUTG11_L {
	unsigned int CLUTG22:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG11_U Register
struct LCDC_GDCCCLUTG11_U {
	unsigned int CLUTG23:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG12_L Register
struct LCDC_GDCCCLUTG12_L {
	unsigned int CLUTG24:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG12_U Register
struct LCDC_GDCCCLUTG12_U {
	unsigned int CLUTG25:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG13_L Register
struct LCDC_GDCCCLUTG13_L {
	unsigned int CLUTG26:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG13_U Register
struct LCDC_GDCCCLUTG13_U {
	unsigned int CLUTG27:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG14_L Register
struct LCDC_GDCCCLUTG14_L {
	unsigned int CLUTG28:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG14_U Register
struct LCDC_GDCCCLUTG14_U {
	unsigned int CLUTG29:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG15_L Register
struct LCDC_GDCCCLUTG15_L {
	unsigned int CLUTG30:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG15_U Register
struct LCDC_GDCCCLUTG15_U {
	unsigned int CLUTG31:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG16_L Register
struct LCDC_GDCCCLUTG16_L {
	unsigned int CLUTG32:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG16_U Register
struct LCDC_GDCCCLUTG16_U {
	unsigned int CLUTG33:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG17_L Register
struct LCDC_GDCCCLUTG17_L {
	unsigned int CLUTG34:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG17_U Register
struct LCDC_GDCCCLUTG17_U {
	unsigned int CLUTG35:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG18_L Register
struct LCDC_GDCCCLUTG18_L {
	unsigned int CLUTG36:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG18_U Register
struct LCDC_GDCCCLUTG18_U {
	unsigned int CLUTG37:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG19_L Register
struct LCDC_GDCCCLUTG19_L {
	unsigned int CLUTG38:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG19_U Register
struct LCDC_GDCCCLUTG19_U {
	unsigned int CLUTG39:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG20_L Register
struct LCDC_GDCCCLUTG20_L {
	unsigned int CLUTG40:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG20_U Register
struct LCDC_GDCCCLUTG20_U {
	unsigned int CLUTG41:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG21_L Register
struct LCDC_GDCCCLUTG21_L {
	unsigned int CLUTG42:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG21_U Register
struct LCDC_GDCCCLUTG21_U {
	unsigned int CLUTG43:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG22_L Register
struct LCDC_GDCCCLUTG22_L {
	unsigned int CLUTG44:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG22_U Register
struct LCDC_GDCCCLUTG22_U {
	unsigned int CLUTG45:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG23_L Register
struct LCDC_GDCCCLUTG23_L {
	unsigned int CLUTG46:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG23_U Register
struct LCDC_GDCCCLUTG23_U {
	unsigned int CLUTG47:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG24_L Register
struct LCDC_GDCCCLUTG24_L {
	unsigned int CLUTG48:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG24_U Register
struct LCDC_GDCCCLUTG24_U {
	unsigned int CLUTG49:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG25_L Register
struct LCDC_GDCCCLUTG25_L {
	unsigned int CLUTG50:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG25_U Register
struct LCDC_GDCCCLUTG25_U {
	unsigned int CLUTG51:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG26_L Register
struct LCDC_GDCCCLUTG26_L {
	unsigned int CLUTG52:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG26_U Register
struct LCDC_GDCCCLUTG26_U {
	unsigned int CLUTG53:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG27_L Register
struct LCDC_GDCCCLUTG27_L {
	unsigned int CLUTG54:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG27_U Register
struct LCDC_GDCCCLUTG27_U {
	unsigned int CLUTG55:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG28_L Register
struct LCDC_GDCCCLUTG28_L {
	unsigned int CLUTG56:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG28_U Register
struct LCDC_GDCCCLUTG28_U {
	unsigned int CLUTG57:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG29_L Register
struct LCDC_GDCCCLUTG29_L {
	unsigned int CLUTG58:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG29_U Register
struct LCDC_GDCCCLUTG29_U {
	unsigned int CLUTG59:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG30_L Register
struct LCDC_GDCCCLUTG30_L {
	unsigned int CLUTG60:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG30_U Register
struct LCDC_GDCCCLUTG30_U {
	unsigned int CLUTG61:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG31_L Register
struct LCDC_GDCCCLUTG31_L {
	unsigned int CLUTG62:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG31_U Register
struct LCDC_GDCCCLUTG31_U {
	unsigned int CLUTG63:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG32_L Register
struct LCDC_GDCCCLUTG32_L {
	unsigned int CLUTG64:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG32_U Register
struct LCDC_GDCCCLUTG32_U {
	unsigned int CLUTG65:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG33_L Register
struct LCDC_GDCCCLUTG33_L {
	unsigned int CLUTG66:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG33_U Register
struct LCDC_GDCCCLUTG33_U {
	unsigned int CLUTG67:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG34_L Register
struct LCDC_GDCCCLUTG34_L {
	unsigned int CLUTG68:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG34_U Register
struct LCDC_GDCCCLUTG34_U {
	unsigned int CLUTG69:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG35_L Register
struct LCDC_GDCCCLUTG35_L {
	unsigned int CLUTG70:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG35_U Register
struct LCDC_GDCCCLUTG35_U {
	unsigned int CLUTG71:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG36_L Register
struct LCDC_GDCCCLUTG36_L {
	unsigned int CLUTG72:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG36_U Register
struct LCDC_GDCCCLUTG36_U {
	unsigned int CLUTG73:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG37_L Register
struct LCDC_GDCCCLUTG37_L {
	unsigned int CLUTG74:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG37_U Register
struct LCDC_GDCCCLUTG37_U {
	unsigned int CLUTG75:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG38_L Register
struct LCDC_GDCCCLUTG38_L {
	unsigned int CLUTG76:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG38_U Register
struct LCDC_GDCCCLUTG38_U {
	unsigned int CLUTG77:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG39_L Register
struct LCDC_GDCCCLUTG39_L {
	unsigned int CLUTG78:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG39_U Register
struct LCDC_GDCCCLUTG39_U {
	unsigned int CLUTG79:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG40_L Register
struct LCDC_GDCCCLUTG40_L {
	unsigned int CLUTG80:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG40_U Register
struct LCDC_GDCCCLUTG40_U {
	unsigned int CLUTG81:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG41_L Register
struct LCDC_GDCCCLUTG41_L {
	unsigned int CLUTG82:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG41_U Register
struct LCDC_GDCCCLUTG41_U {
	unsigned int CLUTG83:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG42_L Register
struct LCDC_GDCCCLUTG42_L {
	unsigned int CLUTG84:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG42_U Register
struct LCDC_GDCCCLUTG42_U {
	unsigned int CLUTG85:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG43_L Register
struct LCDC_GDCCCLUTG43_L {
	unsigned int CLUTG86:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG43_U Register
struct LCDC_GDCCCLUTG43_U {
	unsigned int CLUTG87:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG44_L Register
struct LCDC_GDCCCLUTG44_L {
	unsigned int CLUTG88:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG44_U Register
struct LCDC_GDCCCLUTG44_U {
	unsigned int CLUTG89:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG45_L Register
struct LCDC_GDCCCLUTG45_L {
	unsigned int CLUTG90:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG45_U Register
struct LCDC_GDCCCLUTG45_U {
	unsigned int CLUTG91:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG46_L Register
struct LCDC_GDCCCLUTG46_L {
	unsigned int CLUTG92:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG46_U Register
struct LCDC_GDCCCLUTG46_U {
	unsigned int CLUTG93:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG47_L Register
struct LCDC_GDCCCLUTG47_L {
	unsigned int CLUTG94:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG47_U Register
struct LCDC_GDCCCLUTG47_U {
	unsigned int CLUTG95:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG48_L Register
struct LCDC_GDCCCLUTG48_L {
	unsigned int CLUTG96:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG48_U Register
struct LCDC_GDCCCLUTG48_U {
	unsigned int CLUTG97:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG49_L Register
struct LCDC_GDCCCLUTG49_L {
	unsigned int CLUTG98:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG49_U Register
struct LCDC_GDCCCLUTG49_U {
	unsigned int CLUTG99:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG50_L Register
struct LCDC_GDCCCLUTG50_L {
	unsigned int CLUTG100:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG50_U Register
struct LCDC_GDCCCLUTG50_U {
	unsigned int CLUTG101:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG51_L Register
struct LCDC_GDCCCLUTG51_L {
	unsigned int CLUTG102:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG51_U Register
struct LCDC_GDCCCLUTG51_U {
	unsigned int CLUTG103:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG52_L Register
struct LCDC_GDCCCLUTG52_L {
	unsigned int CLUTG104:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG52_U Register
struct LCDC_GDCCCLUTG52_U {
	unsigned int CLUTG105:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG53_L Register
struct LCDC_GDCCCLUTG53_L {
	unsigned int CLUTG106:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG53_U Register
struct LCDC_GDCCCLUTG53_U {
	unsigned int CLUTG107:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG54_L Register
struct LCDC_GDCCCLUTG54_L {
	unsigned int CLUTG108:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG54_U Register
struct LCDC_GDCCCLUTG54_U {
	unsigned int CLUTG109:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG55_L Register
struct LCDC_GDCCCLUTG55_L {
	unsigned int CLUTG110:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG55_U Register
struct LCDC_GDCCCLUTG55_U {
	unsigned int CLUTG111:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG56_L Register
struct LCDC_GDCCCLUTG56_L {
	unsigned int CLUTG112:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG56_U Register
struct LCDC_GDCCCLUTG56_U {
	unsigned int CLUTG113:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG57_L Register
struct LCDC_GDCCCLUTG57_L {
	unsigned int CLUTG114:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG57_U Register
struct LCDC_GDCCCLUTG57_U {
	unsigned int CLUTG115:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG58_L Register
struct LCDC_GDCCCLUTG58_L {
	unsigned int CLUTG116:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG58_U Register
struct LCDC_GDCCCLUTG58_U {
	unsigned int CLUTG117:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG59_L Register
struct LCDC_GDCCCLUTG59_L {
	unsigned int CLUTG118:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG59_U Register
struct LCDC_GDCCCLUTG59_U {
	unsigned int CLUTG119:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG60_L Register
struct LCDC_GDCCCLUTG60_L {
	unsigned int CLUTG120:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG60_U Register
struct LCDC_GDCCCLUTG60_U {
	unsigned int CLUTG121:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG61_L Register
struct LCDC_GDCCCLUTG61_L {
	unsigned int CLUTG122:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG61_U Register
struct LCDC_GDCCCLUTG61_U {
	unsigned int CLUTG123:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG62_L Register
struct LCDC_GDCCCLUTG62_L {
	unsigned int CLUTG124:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG62_U Register
struct LCDC_GDCCCLUTG62_U {
	unsigned int CLUTG125:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG63_L Register
struct LCDC_GDCCCLUTG63_L {
	unsigned int CLUTG126:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG63_U Register
struct LCDC_GDCCCLUTG63_U {
	unsigned int CLUTG127:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG64_L Register
struct LCDC_GDCCCLUTG64_L {
	unsigned int CLUTG128:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG64_U Register
struct LCDC_GDCCCLUTG64_U {
	unsigned int CLUTG129:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG65_L Register
struct LCDC_GDCCCLUTG65_L {
	unsigned int CLUTG130:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG65_U Register
struct LCDC_GDCCCLUTG65_U {
	unsigned int CLUTG131:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG66_L Register
struct LCDC_GDCCCLUTG66_L {
	unsigned int CLUTG132:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG66_U Register
struct LCDC_GDCCCLUTG66_U {
	unsigned int CLUTG133:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG67_L Register
struct LCDC_GDCCCLUTG67_L {
	unsigned int CLUTG134:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG67_U Register
struct LCDC_GDCCCLUTG67_U {
	unsigned int CLUTG135:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG68_L Register
struct LCDC_GDCCCLUTG68_L {
	unsigned int CLUTG136:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG68_U Register
struct LCDC_GDCCCLUTG68_U {
	unsigned int CLUTG137:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG69_L Register
struct LCDC_GDCCCLUTG69_L {
	unsigned int CLUTG138:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG69_U Register
struct LCDC_GDCCCLUTG69_U {
	unsigned int CLUTG139:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG70_L Register
struct LCDC_GDCCCLUTG70_L {
	unsigned int CLUTG140:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG70_U Register
struct LCDC_GDCCCLUTG70_U {
	unsigned int CLUTG141:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG71_L Register
struct LCDC_GDCCCLUTG71_L {
	unsigned int CLUTG142:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG71_U Register
struct LCDC_GDCCCLUTG71_U {
	unsigned int CLUTG143:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG72_L Register
struct LCDC_GDCCCLUTG72_L {
	unsigned int CLUTG144:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG72_U Register
struct LCDC_GDCCCLUTG72_U {
	unsigned int CLUTG145:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG73_L Register
struct LCDC_GDCCCLUTG73_L {
	unsigned int CLUTG146:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG73_U Register
struct LCDC_GDCCCLUTG73_U {
	unsigned int CLUTG147:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG74_L Register
struct LCDC_GDCCCLUTG74_L {
	unsigned int CLUTG148:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG74_U Register
struct LCDC_GDCCCLUTG74_U {
	unsigned int CLUTG149:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG75_L Register
struct LCDC_GDCCCLUTG75_L {
	unsigned int CLUTG150:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG75_U Register
struct LCDC_GDCCCLUTG75_U {
	unsigned int CLUTG151:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG76_L Register
struct LCDC_GDCCCLUTG76_L {
	unsigned int CLUTG152:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG76_U Register
struct LCDC_GDCCCLUTG76_U {
	unsigned int CLUTG153:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG77_L Register
struct LCDC_GDCCCLUTG77_L {
	unsigned int CLUTG154:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG77_U Register
struct LCDC_GDCCCLUTG77_U {
	unsigned int CLUTG155:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG78_L Register
struct LCDC_GDCCCLUTG78_L {
	unsigned int CLUTG156:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG78_U Register
struct LCDC_GDCCCLUTG78_U {
	unsigned int CLUTG157:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG79_L Register
struct LCDC_GDCCCLUTG79_L {
	unsigned int CLUTG158:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG79_U Register
struct LCDC_GDCCCLUTG79_U {
	unsigned int CLUTG159:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG80_L Register
struct LCDC_GDCCCLUTG80_L {
	unsigned int CLUTG160:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG80_U Register
struct LCDC_GDCCCLUTG80_U {
	unsigned int CLUTG161:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG81_L Register
struct LCDC_GDCCCLUTG81_L {
	unsigned int CLUTG162:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG81_U Register
struct LCDC_GDCCCLUTG81_U {
	unsigned int CLUTG163:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG82_L Register
struct LCDC_GDCCCLUTG82_L {
	unsigned int CLUTG164:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG82_U Register
struct LCDC_GDCCCLUTG82_U {
	unsigned int CLUTG165:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG83_L Register
struct LCDC_GDCCCLUTG83_L {
	unsigned int CLUTG166:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG83_U Register
struct LCDC_GDCCCLUTG83_U {
	unsigned int CLUTG167:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG84_L Register
struct LCDC_GDCCCLUTG84_L {
	unsigned int CLUTG168:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG84_U Register
struct LCDC_GDCCCLUTG84_U {
	unsigned int CLUTG169:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG85_L Register
struct LCDC_GDCCCLUTG85_L {
	unsigned int CLUTG170:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG85_U Register
struct LCDC_GDCCCLUTG85_U {
	unsigned int CLUTG171:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG86_L Register
struct LCDC_GDCCCLUTG86_L {
	unsigned int CLUTG172:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG86_U Register
struct LCDC_GDCCCLUTG86_U {
	unsigned int CLUTG173:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG87_L Register
struct LCDC_GDCCCLUTG87_L {
	unsigned int CLUTG174:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG87_U Register
struct LCDC_GDCCCLUTG87_U {
	unsigned int CLUTG175:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG88_L Register
struct LCDC_GDCCCLUTG88_L {
	unsigned int CLUTG176:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG88_U Register
struct LCDC_GDCCCLUTG88_U {
	unsigned int CLUTG177:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG89_L Register
struct LCDC_GDCCCLUTG89_L {
	unsigned int CLUTG178:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG89_U Register
struct LCDC_GDCCCLUTG89_U {
	unsigned int CLUTG179:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG90_L Register
struct LCDC_GDCCCLUTG90_L {
	unsigned int CLUTG180:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG90_U Register
struct LCDC_GDCCCLUTG90_U {
	unsigned int CLUTG181:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG91_L Register
struct LCDC_GDCCCLUTG91_L {
	unsigned int CLUTG182:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG91_U Register
struct LCDC_GDCCCLUTG91_U {
	unsigned int CLUTG183:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG92_L Register
struct LCDC_GDCCCLUTG92_L {
	unsigned int CLUTG184:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG92_U Register
struct LCDC_GDCCCLUTG92_U {
	unsigned int CLUTG185:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG93_L Register
struct LCDC_GDCCCLUTG93_L {
	unsigned int CLUTG186:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG93_U Register
struct LCDC_GDCCCLUTG93_U {
	unsigned int CLUTG187:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG94_L Register
struct LCDC_GDCCCLUTG94_L {
	unsigned int CLUTG188:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG94_U Register
struct LCDC_GDCCCLUTG94_U {
	unsigned int CLUTG189:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG95_L Register
struct LCDC_GDCCCLUTG95_L {
	unsigned int CLUTG190:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG95_U Register
struct LCDC_GDCCCLUTG95_U {
	unsigned int CLUTG191:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG96_L Register
struct LCDC_GDCCCLUTG96_L {
	unsigned int CLUTG192:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG96_U Register
struct LCDC_GDCCCLUTG96_U {
	unsigned int CLUTG193:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG97_L Register
struct LCDC_GDCCCLUTG97_L {
	unsigned int CLUTG194:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG97_U Register
struct LCDC_GDCCCLUTG97_U {
	unsigned int CLUTG195:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG98_L Register
struct LCDC_GDCCCLUTG98_L {
	unsigned int CLUTG196:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG98_U Register
struct LCDC_GDCCCLUTG98_U {
	unsigned int CLUTG197:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG99_L Register
struct LCDC_GDCCCLUTG99_L {
	unsigned int CLUTG198:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG99_U Register
struct LCDC_GDCCCLUTG99_U {
	unsigned int CLUTG199:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG100_L Register
struct LCDC_GDCCCLUTG100_L {
	unsigned int CLUTG200:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG100_U Register
struct LCDC_GDCCCLUTG100_U {
	unsigned int CLUTG201:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG101_L Register
struct LCDC_GDCCCLUTG101_L {
	unsigned int CLUTG202:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG101_U Register
struct LCDC_GDCCCLUTG101_U {
	unsigned int CLUTG203:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG102_L Register
struct LCDC_GDCCCLUTG102_L {
	unsigned int CLUTG204:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG102_U Register
struct LCDC_GDCCCLUTG102_U {
	unsigned int CLUTG205:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG103_L Register
struct LCDC_GDCCCLUTG103_L {
	unsigned int CLUTG206:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG103_U Register
struct LCDC_GDCCCLUTG103_U {
	unsigned int CLUTG207:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG104_L Register
struct LCDC_GDCCCLUTG104_L {
	unsigned int CLUTG208:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG104_U Register
struct LCDC_GDCCCLUTG104_U {
	unsigned int CLUTG209:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG105_L Register
struct LCDC_GDCCCLUTG105_L {
	unsigned int CLUTG210:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG105_U Register
struct LCDC_GDCCCLUTG105_U {
	unsigned int CLUTG211:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG106_L Register
struct LCDC_GDCCCLUTG106_L {
	unsigned int CLUTG212:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG106_U Register
struct LCDC_GDCCCLUTG106_U {
	unsigned int CLUTG213:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG107_L Register
struct LCDC_GDCCCLUTG107_L {
	unsigned int CLUTG214:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG107_U Register
struct LCDC_GDCCCLUTG107_U {
	unsigned int CLUTG215:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG108_L Register
struct LCDC_GDCCCLUTG108_L {
	unsigned int CLUTG216:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG108_U Register
struct LCDC_GDCCCLUTG108_U {
	unsigned int CLUTG217:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG109_L Register
struct LCDC_GDCCCLUTG109_L {
	unsigned int CLUTG218:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG109_U Register
struct LCDC_GDCCCLUTG109_U {
	unsigned int CLUTG219:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG110_L Register
struct LCDC_GDCCCLUTG110_L {
	unsigned int CLUTG220:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG110_U Register
struct LCDC_GDCCCLUTG110_U {
	unsigned int CLUTG221:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG111_L Register
struct LCDC_GDCCCLUTG111_L {
	unsigned int CLUTG222:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG111_U Register
struct LCDC_GDCCCLUTG111_U {
	unsigned int CLUTG223:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG112_L Register
struct LCDC_GDCCCLUTG112_L {
	unsigned int CLUTG224:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG112_U Register
struct LCDC_GDCCCLUTG112_U {
	unsigned int CLUTG225:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG113_L Register
struct LCDC_GDCCCLUTG113_L {
	unsigned int CLUTG226:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG113_U Register
struct LCDC_GDCCCLUTG113_U {
	unsigned int CLUTG227:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG114_L Register
struct LCDC_GDCCCLUTG114_L {
	unsigned int CLUTG228:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG114_U Register
struct LCDC_GDCCCLUTG114_U {
	unsigned int CLUTG229:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG115_L Register
struct LCDC_GDCCCLUTG115_L {
	unsigned int CLUTG230:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG115_U Register
struct LCDC_GDCCCLUTG115_U {
	unsigned int CLUTG231:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG116_L Register
struct LCDC_GDCCCLUTG116_L {
	unsigned int CLUTG232:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG116_U Register
struct LCDC_GDCCCLUTG116_U {
	unsigned int CLUTG233:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG117_L Register
struct LCDC_GDCCCLUTG117_L {
	unsigned int CLUTG234:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG117_U Register
struct LCDC_GDCCCLUTG117_U {
	unsigned int CLUTG235:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG118_L Register
struct LCDC_GDCCCLUTG118_L {
	unsigned int CLUTG236:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG118_U Register
struct LCDC_GDCCCLUTG118_U {
	unsigned int CLUTG237:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG119_L Register
struct LCDC_GDCCCLUTG119_L {
	unsigned int CLUTG238:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG119_U Register
struct LCDC_GDCCCLUTG119_U {
	unsigned int CLUTG239:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG120_L Register
struct LCDC_GDCCCLUTG120_L {
	unsigned int CLUTG240:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG120_U Register
struct LCDC_GDCCCLUTG120_U {
	unsigned int CLUTG241:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG121_L Register
struct LCDC_GDCCCLUTG121_L {
	unsigned int CLUTG242:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG121_U Register
struct LCDC_GDCCCLUTG121_U {
	unsigned int CLUTG243:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG122_L Register
struct LCDC_GDCCCLUTG122_L {
	unsigned int CLUTG244:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG122_U Register
struct LCDC_GDCCCLUTG122_U {
	unsigned int CLUTG245:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG123_L Register
struct LCDC_GDCCCLUTG123_L {
	unsigned int CLUTG246:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG123_U Register
struct LCDC_GDCCCLUTG123_U {
	unsigned int CLUTG247:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG124_L Register
struct LCDC_GDCCCLUTG124_L {
	unsigned int CLUTG248:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG124_U Register
struct LCDC_GDCCCLUTG124_U {
	unsigned int CLUTG249:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG125_L Register
struct LCDC_GDCCCLUTG125_L {
	unsigned int CLUTG250:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG125_U Register
struct LCDC_GDCCCLUTG125_U {
	unsigned int CLUTG251:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG126_L Register
struct LCDC_GDCCCLUTG126_L {
	unsigned int CLUTG252:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG126_U Register
struct LCDC_GDCCCLUTG126_U {
	unsigned int CLUTG253:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG127_L Register
struct LCDC_GDCCCLUTG127_L {
	unsigned int CLUTG254:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTG127_U Register
struct LCDC_GDCCCLUTG127_U {
	unsigned int CLUTG255:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB0_L Register
struct LCDC_GDCCCLUTB0_L {
	unsigned int CLUTB0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB0_U Register
struct LCDC_GDCCCLUTB0_U {
	unsigned int CLUTB1:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB1_L Register
struct LCDC_GDCCCLUTB1_L {
	unsigned int CLUTB2:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB1_U Register
struct LCDC_GDCCCLUTB1_U {
	unsigned int CLUTB3:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB2_L Register
struct LCDC_GDCCCLUTB2_L {
	unsigned int CLUTB4:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB2_U Register
struct LCDC_GDCCCLUTB2_U {
	unsigned int CLUTB5:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB3_L Register
struct LCDC_GDCCCLUTB3_L {
	unsigned int CLUTB6:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB3_U Register
struct LCDC_GDCCCLUTB3_U {
	unsigned int CLUTB7:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB4_L Register
struct LCDC_GDCCCLUTB4_L {
	unsigned int CLUTB8:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB4_U Register
struct LCDC_GDCCCLUTB4_U {
	unsigned int CLUTB9:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB5_L Register
struct LCDC_GDCCCLUTB5_L {
	unsigned int CLUTB10:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB5_U Register
struct LCDC_GDCCCLUTB5_U {
	unsigned int CLUTB11:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB6_L Register
struct LCDC_GDCCCLUTB6_L {
	unsigned int CLUTB12:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB6_U Register
struct LCDC_GDCCCLUTB6_U {
	unsigned int CLUTB13:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB7_L Register
struct LCDC_GDCCCLUTB7_L {
	unsigned int CLUTB14:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB7_U Register
struct LCDC_GDCCCLUTB7_U {
	unsigned int CLUTB15:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB8_L Register
struct LCDC_GDCCCLUTB8_L {
	unsigned int CLUTB16:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB8_U Register
struct LCDC_GDCCCLUTB8_U {
	unsigned int CLUTB17:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB9_L Register
struct LCDC_GDCCCLUTB9_L {
	unsigned int CLUTB18:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB9_U Register
struct LCDC_GDCCCLUTB9_U {
	unsigned int CLUTB19:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB10_L Register
struct LCDC_GDCCCLUTB10_L {
	unsigned int CLUTB20:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB10_U Register
struct LCDC_GDCCCLUTB10_U {
	unsigned int CLUTB21:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB11_L Register
struct LCDC_GDCCCLUTB11_L {
	unsigned int CLUTB22:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB11_U Register
struct LCDC_GDCCCLUTB11_U {
	unsigned int CLUTB23:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB12_L Register
struct LCDC_GDCCCLUTB12_L {
	unsigned int CLUTB24:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB12_U Register
struct LCDC_GDCCCLUTB12_U {
	unsigned int CLUTB25:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB13_L Register
struct LCDC_GDCCCLUTB13_L {
	unsigned int CLUTB26:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB13_U Register
struct LCDC_GDCCCLUTB13_U {
	unsigned int CLUTB27:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB14_L Register
struct LCDC_GDCCCLUTB14_L {
	unsigned int CLUTB28:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB14_U Register
struct LCDC_GDCCCLUTB14_U {
	unsigned int CLUTB29:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB15_L Register
struct LCDC_GDCCCLUTB15_L {
	unsigned int CLUTB30:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB15_U Register
struct LCDC_GDCCCLUTB15_U {
	unsigned int CLUTB31:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB16_L Register
struct LCDC_GDCCCLUTB16_L {
	unsigned int CLUTB32:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB16_U Register
struct LCDC_GDCCCLUTB16_U {
	unsigned int CLUTB33:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB17_L Register
struct LCDC_GDCCCLUTB17_L {
	unsigned int CLUTB34:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB17_U Register
struct LCDC_GDCCCLUTB17_U {
	unsigned int CLUTB35:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB18_L Register
struct LCDC_GDCCCLUTB18_L {
	unsigned int CLUTB36:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB18_U Register
struct LCDC_GDCCCLUTB18_U {
	unsigned int CLUTB37:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB19_L Register
struct LCDC_GDCCCLUTB19_L {
	unsigned int CLUTB38:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB19_U Register
struct LCDC_GDCCCLUTB19_U {
	unsigned int CLUTB39:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB20_L Register
struct LCDC_GDCCCLUTB20_L {
	unsigned int CLUTB40:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB20_U Register
struct LCDC_GDCCCLUTB20_U {
	unsigned int CLUTB41:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB21_L Register
struct LCDC_GDCCCLUTB21_L {
	unsigned int CLUTB42:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB21_U Register
struct LCDC_GDCCCLUTB21_U {
	unsigned int CLUTB43:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB22_L Register
struct LCDC_GDCCCLUTB22_L {
	unsigned int CLUTB44:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB22_U Register
struct LCDC_GDCCCLUTB22_U {
	unsigned int CLUTB45:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB23_L Register
struct LCDC_GDCCCLUTB23_L {
	unsigned int CLUTB46:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB23_U Register
struct LCDC_GDCCCLUTB23_U {
	unsigned int CLUTB47:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB24_L Register
struct LCDC_GDCCCLUTB24_L {
	unsigned int CLUTB48:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB24_U Register
struct LCDC_GDCCCLUTB24_U {
	unsigned int CLUTB49:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB25_L Register
struct LCDC_GDCCCLUTB25_L {
	unsigned int CLUTB50:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB25_U Register
struct LCDC_GDCCCLUTB25_U {
	unsigned int CLUTB51:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB26_L Register
struct LCDC_GDCCCLUTB26_L {
	unsigned int CLUTB52:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB26_U Register
struct LCDC_GDCCCLUTB26_U {
	unsigned int CLUTB53:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB27_L Register
struct LCDC_GDCCCLUTB27_L {
	unsigned int CLUTB54:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB27_U Register
struct LCDC_GDCCCLUTB27_U {
	unsigned int CLUTB55:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB28_L Register
struct LCDC_GDCCCLUTB28_L {
	unsigned int CLUTB56:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB28_U Register
struct LCDC_GDCCCLUTB28_U {
	unsigned int CLUTB57:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB29_L Register
struct LCDC_GDCCCLUTB29_L {
	unsigned int CLUTB58:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB29_U Register
struct LCDC_GDCCCLUTB29_U {
	unsigned int CLUTB59:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB30_L Register
struct LCDC_GDCCCLUTB30_L {
	unsigned int CLUTB60:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB30_U Register
struct LCDC_GDCCCLUTB30_U {
	unsigned int CLUTB61:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB31_L Register
struct LCDC_GDCCCLUTB31_L {
	unsigned int CLUTB62:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB31_U Register
struct LCDC_GDCCCLUTB31_U {
	unsigned int CLUTB63:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB32_L Register
struct LCDC_GDCCCLUTB32_L {
	unsigned int CLUTB64:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB32_U Register
struct LCDC_GDCCCLUTB32_U {
	unsigned int CLUTB65:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB33_L Register
struct LCDC_GDCCCLUTB33_L {
	unsigned int CLUTB66:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB33_U Register
struct LCDC_GDCCCLUTB33_U {
	unsigned int CLUTB67:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB34_L Register
struct LCDC_GDCCCLUTB34_L {
	unsigned int CLUTB68:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB34_U Register
struct LCDC_GDCCCLUTB34_U {
	unsigned int CLUTB69:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB35_L Register
struct LCDC_GDCCCLUTB35_L {
	unsigned int CLUTB70:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB35_U Register
struct LCDC_GDCCCLUTB35_U {
	unsigned int CLUTB71:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB36_L Register
struct LCDC_GDCCCLUTB36_L {
	unsigned int CLUTB72:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB36_U Register
struct LCDC_GDCCCLUTB36_U {
	unsigned int CLUTB73:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB37_L Register
struct LCDC_GDCCCLUTB37_L {
	unsigned int CLUTB74:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB37_U Register
struct LCDC_GDCCCLUTB37_U {
	unsigned int CLUTB75:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB38_L Register
struct LCDC_GDCCCLUTB38_L {
	unsigned int CLUTB76:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB38_U Register
struct LCDC_GDCCCLUTB38_U {
	unsigned int CLUTB77:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB39_L Register
struct LCDC_GDCCCLUTB39_L {
	unsigned int CLUTB78:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB39_U Register
struct LCDC_GDCCCLUTB39_U {
	unsigned int CLUTB79:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB40_L Register
struct LCDC_GDCCCLUTB40_L {
	unsigned int CLUTB80:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB40_U Register
struct LCDC_GDCCCLUTB40_U {
	unsigned int CLUTB81:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB41_L Register
struct LCDC_GDCCCLUTB41_L {
	unsigned int CLUTB82:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB41_U Register
struct LCDC_GDCCCLUTB41_U {
	unsigned int CLUTB83:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB42_L Register
struct LCDC_GDCCCLUTB42_L {
	unsigned int CLUTB84:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB42_U Register
struct LCDC_GDCCCLUTB42_U {
	unsigned int CLUTB85:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB43_L Register
struct LCDC_GDCCCLUTB43_L {
	unsigned int CLUTB86:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB43_U Register
struct LCDC_GDCCCLUTB43_U {
	unsigned int CLUTB87:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB44_L Register
struct LCDC_GDCCCLUTB44_L {
	unsigned int CLUTB88:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB44_U Register
struct LCDC_GDCCCLUTB44_U {
	unsigned int CLUTB89:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB45_L Register
struct LCDC_GDCCCLUTB45_L {
	unsigned int CLUTB90:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB45_U Register
struct LCDC_GDCCCLUTB45_U {
	unsigned int CLUTB91:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB46_L Register
struct LCDC_GDCCCLUTB46_L {
	unsigned int CLUTB92:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB46_U Register
struct LCDC_GDCCCLUTB46_U {
	unsigned int CLUTB93:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB47_L Register
struct LCDC_GDCCCLUTB47_L {
	unsigned int CLUTB94:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB47_U Register
struct LCDC_GDCCCLUTB47_U {
	unsigned int CLUTB95:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB48_L Register
struct LCDC_GDCCCLUTB48_L {
	unsigned int CLUTB96:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB48_U Register
struct LCDC_GDCCCLUTB48_U {
	unsigned int CLUTB97:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB49_L Register
struct LCDC_GDCCCLUTB49_L {
	unsigned int CLUTB98:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB49_U Register
struct LCDC_GDCCCLUTB49_U {
	unsigned int CLUTB99:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB50_L Register
struct LCDC_GDCCCLUTB50_L {
	unsigned int CLUTB100:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB50_U Register
struct LCDC_GDCCCLUTB50_U {
	unsigned int CLUTB101:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB51_L Register
struct LCDC_GDCCCLUTB51_L {
	unsigned int CLUTB102:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB51_U Register
struct LCDC_GDCCCLUTB51_U {
	unsigned int CLUTB103:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB52_L Register
struct LCDC_GDCCCLUTB52_L {
	unsigned int CLUTB104:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB52_U Register
struct LCDC_GDCCCLUTB52_U {
	unsigned int CLUTB105:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB53_L Register
struct LCDC_GDCCCLUTB53_L {
	unsigned int CLUTB106:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB53_U Register
struct LCDC_GDCCCLUTB53_U {
	unsigned int CLUTB107:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB54_L Register
struct LCDC_GDCCCLUTB54_L {
	unsigned int CLUTB108:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB54_U Register
struct LCDC_GDCCCLUTB54_U {
	unsigned int CLUTB109:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB55_L Register
struct LCDC_GDCCCLUTB55_L {
	unsigned int CLUTB110:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB55_U Register
struct LCDC_GDCCCLUTB55_U {
	unsigned int CLUTB111:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB56_L Register
struct LCDC_GDCCCLUTB56_L {
	unsigned int CLUTB112:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB56_U Register
struct LCDC_GDCCCLUTB56_U {
	unsigned int CLUTB113:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB57_L Register
struct LCDC_GDCCCLUTB57_L {
	unsigned int CLUTB114:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB57_U Register
struct LCDC_GDCCCLUTB57_U {
	unsigned int CLUTB115:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB58_L Register
struct LCDC_GDCCCLUTB58_L {
	unsigned int CLUTB116:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB58_U Register
struct LCDC_GDCCCLUTB58_U {
	unsigned int CLUTB117:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB59_L Register
struct LCDC_GDCCCLUTB59_L {
	unsigned int CLUTB118:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB59_U Register
struct LCDC_GDCCCLUTB59_U {
	unsigned int CLUTB119:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB60_L Register
struct LCDC_GDCCCLUTB60_L {
	unsigned int CLUTB120:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB60_U Register
struct LCDC_GDCCCLUTB60_U {
	unsigned int CLUTB121:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB61_L Register
struct LCDC_GDCCCLUTB61_L {
	unsigned int CLUTB122:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB61_U Register
struct LCDC_GDCCCLUTB61_U {
	unsigned int CLUTB123:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB62_L Register
struct LCDC_GDCCCLUTB62_L {
	unsigned int CLUTB124:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB62_U Register
struct LCDC_GDCCCLUTB62_U {
	unsigned int CLUTB125:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB63_L Register
struct LCDC_GDCCCLUTB63_L {
	unsigned int CLUTB126:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB63_U Register
struct LCDC_GDCCCLUTB63_U {
	unsigned int CLUTB127:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB64_L Register
struct LCDC_GDCCCLUTB64_L {
	unsigned int CLUTB128:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB64_U Register
struct LCDC_GDCCCLUTB64_U {
	unsigned int CLUTB129:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB65_L Register
struct LCDC_GDCCCLUTB65_L {
	unsigned int CLUTB130:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB65_U Register
struct LCDC_GDCCCLUTB65_U {
	unsigned int CLUTB131:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB66_L Register
struct LCDC_GDCCCLUTB66_L {
	unsigned int CLUTB132:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB66_U Register
struct LCDC_GDCCCLUTB66_U {
	unsigned int CLUTB133:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB67_L Register
struct LCDC_GDCCCLUTB67_L {
	unsigned int CLUTB134:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB67_U Register
struct LCDC_GDCCCLUTB67_U {
	unsigned int CLUTB135:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB68_L Register
struct LCDC_GDCCCLUTB68_L {
	unsigned int CLUTB136:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB68_U Register
struct LCDC_GDCCCLUTB68_U {
	unsigned int CLUTB137:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB69_L Register
struct LCDC_GDCCCLUTB69_L {
	unsigned int CLUTB138:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB69_U Register
struct LCDC_GDCCCLUTB69_U {
	unsigned int CLUTB139:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB70_L Register
struct LCDC_GDCCCLUTB70_L {
	unsigned int CLUTB140:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB70_U Register
struct LCDC_GDCCCLUTB70_U {
	unsigned int CLUTB141:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB71_L Register
struct LCDC_GDCCCLUTB71_L {
	unsigned int CLUTB142:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB71_U Register
struct LCDC_GDCCCLUTB71_U {
	unsigned int CLUTB143:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB72_L Register
struct LCDC_GDCCCLUTB72_L {
	unsigned int CLUTB144:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB72_U Register
struct LCDC_GDCCCLUTB72_U {
	unsigned int CLUTB145:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB73_L Register
struct LCDC_GDCCCLUTB73_L {
	unsigned int CLUTB146:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB73_U Register
struct LCDC_GDCCCLUTB73_U {
	unsigned int CLUTB147:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB74_L Register
struct LCDC_GDCCCLUTB74_L {
	unsigned int CLUTB148:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB74_U Register
struct LCDC_GDCCCLUTB74_U {
	unsigned int CLUTB149:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB75_L Register
struct LCDC_GDCCCLUTB75_L {
	unsigned int CLUTB150:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB75_U Register
struct LCDC_GDCCCLUTB75_U {
	unsigned int CLUTB151:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB76_L Register
struct LCDC_GDCCCLUTB76_L {
	unsigned int CLUTB152:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB76_U Register
struct LCDC_GDCCCLUTB76_U {
	unsigned int CLUTB153:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB77_L Register
struct LCDC_GDCCCLUTB77_L {
	unsigned int CLUTB154:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB77_U Register
struct LCDC_GDCCCLUTB77_U {
	unsigned int CLUTB155:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB78_L Register
struct LCDC_GDCCCLUTB78_L {
	unsigned int CLUTB156:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB78_U Register
struct LCDC_GDCCCLUTB78_U {
	unsigned int CLUTB157:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB79_L Register
struct LCDC_GDCCCLUTB79_L {
	unsigned int CLUTB158:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB79_U Register
struct LCDC_GDCCCLUTB79_U {
	unsigned int CLUTB159:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB80_L Register
struct LCDC_GDCCCLUTB80_L {
	unsigned int CLUTB160:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB80_U Register
struct LCDC_GDCCCLUTB80_U {
	unsigned int CLUTB161:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB81_L Register
struct LCDC_GDCCCLUTB81_L {
	unsigned int CLUTB162:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB81_U Register
struct LCDC_GDCCCLUTB81_U {
	unsigned int CLUTB163:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB82_L Register
struct LCDC_GDCCCLUTB82_L {
	unsigned int CLUTB164:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB82_U Register
struct LCDC_GDCCCLUTB82_U {
	unsigned int CLUTB165:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB83_L Register
struct LCDC_GDCCCLUTB83_L {
	unsigned int CLUTB166:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB83_U Register
struct LCDC_GDCCCLUTB83_U {
	unsigned int CLUTB167:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB84_L Register
struct LCDC_GDCCCLUTB84_L {
	unsigned int CLUTB168:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB84_U Register
struct LCDC_GDCCCLUTB84_U {
	unsigned int CLUTB169:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB85_L Register
struct LCDC_GDCCCLUTB85_L {
	unsigned int CLUTB170:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB85_U Register
struct LCDC_GDCCCLUTB85_U {
	unsigned int CLUTB171:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB86_L Register
struct LCDC_GDCCCLUTB86_L {
	unsigned int CLUTB172:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB86_U Register
struct LCDC_GDCCCLUTB86_U {
	unsigned int CLUTB173:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB87_L Register
struct LCDC_GDCCCLUTB87_L {
	unsigned int CLUTB174:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB87_U Register
struct LCDC_GDCCCLUTB87_U {
	unsigned int CLUTB175:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB88_L Register
struct LCDC_GDCCCLUTB88_L {
	unsigned int CLUTB176:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB88_U Register
struct LCDC_GDCCCLUTB88_U {
	unsigned int CLUTB177:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB89_L Register
struct LCDC_GDCCCLUTB89_L {
	unsigned int CLUTB178:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB89_U Register
struct LCDC_GDCCCLUTB89_U {
	unsigned int CLUTB179:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB90_L Register
struct LCDC_GDCCCLUTB90_L {
	unsigned int CLUTB180:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB90_U Register
struct LCDC_GDCCCLUTB90_U {
	unsigned int CLUTB181:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB91_L Register
struct LCDC_GDCCCLUTB91_L {
	unsigned int CLUTB182:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB91_U Register
struct LCDC_GDCCCLUTB91_U {
	unsigned int CLUTB183:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB92_L Register
struct LCDC_GDCCCLUTB92_L {
	unsigned int CLUTB184:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB92_U Register
struct LCDC_GDCCCLUTB92_U {
	unsigned int CLUTB185:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB93_L Register
struct LCDC_GDCCCLUTB93_L {
	unsigned int CLUTB186:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB93_U Register
struct LCDC_GDCCCLUTB93_U {
	unsigned int CLUTB187:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB94_L Register
struct LCDC_GDCCCLUTB94_L {
	unsigned int CLUTB188:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB94_U Register
struct LCDC_GDCCCLUTB94_U {
	unsigned int CLUTB189:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB95_L Register
struct LCDC_GDCCCLUTB95_L {
	unsigned int CLUTB190:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB95_U Register
struct LCDC_GDCCCLUTB95_U {
	unsigned int CLUTB191:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB96_L Register
struct LCDC_GDCCCLUTB96_L {
	unsigned int CLUTB192:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB96_U Register
struct LCDC_GDCCCLUTB96_U {
	unsigned int CLUTB193:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB97_L Register
struct LCDC_GDCCCLUTB97_L {
	unsigned int CLUTB194:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB97_U Register
struct LCDC_GDCCCLUTB97_U {
	unsigned int CLUTB195:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB98_L Register
struct LCDC_GDCCCLUTB98_L {
	unsigned int CLUTB196:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB98_U Register
struct LCDC_GDCCCLUTB98_U {
	unsigned int CLUTB197:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB99_L Register
struct LCDC_GDCCCLUTB99_L {
	unsigned int CLUTB198:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB99_U Register
struct LCDC_GDCCCLUTB99_U {
	unsigned int CLUTB199:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB100_L Register
struct LCDC_GDCCCLUTB100_L {
	unsigned int CLUTB200:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB100_U Register
struct LCDC_GDCCCLUTB100_U {
	unsigned int CLUTB201:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB101_L Register
struct LCDC_GDCCCLUTB101_L {
	unsigned int CLUTB202:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB101_U Register
struct LCDC_GDCCCLUTB101_U {
	unsigned int CLUTB203:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB102_L Register
struct LCDC_GDCCCLUTB102_L {
	unsigned int CLUTB204:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB102_U Register
struct LCDC_GDCCCLUTB102_U {
	unsigned int CLUTB205:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB103_L Register
struct LCDC_GDCCCLUTB103_L {
	unsigned int CLUTB206:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB103_U Register
struct LCDC_GDCCCLUTB103_U {
	unsigned int CLUTB207:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB104_L Register
struct LCDC_GDCCCLUTB104_L {
	unsigned int CLUTB208:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB104_U Register
struct LCDC_GDCCCLUTB104_U {
	unsigned int CLUTB209:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB105_L Register
struct LCDC_GDCCCLUTB105_L {
	unsigned int CLUTB210:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB105_U Register
struct LCDC_GDCCCLUTB105_U {
	unsigned int CLUTB211:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB106_L Register
struct LCDC_GDCCCLUTB106_L {
	unsigned int CLUTB212:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB106_U Register
struct LCDC_GDCCCLUTB106_U {
	unsigned int CLUTB213:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB107_L Register
struct LCDC_GDCCCLUTB107_L {
	unsigned int CLUTB214:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB107_U Register
struct LCDC_GDCCCLUTB107_U {
	unsigned int CLUTB215:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB108_L Register
struct LCDC_GDCCCLUTB108_L {
	unsigned int CLUTB216:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB108_U Register
struct LCDC_GDCCCLUTB108_U {
	unsigned int CLUTB217:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB109_L Register
struct LCDC_GDCCCLUTB109_L {
	unsigned int CLUTB218:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB109_U Register
struct LCDC_GDCCCLUTB109_U {
	unsigned int CLUTB219:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB110_L Register
struct LCDC_GDCCCLUTB110_L {
	unsigned int CLUTB220:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB110_U Register
struct LCDC_GDCCCLUTB110_U {
	unsigned int CLUTB221:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB111_L Register
struct LCDC_GDCCCLUTB111_L {
	unsigned int CLUTB222:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB111_U Register
struct LCDC_GDCCCLUTB111_U {
	unsigned int CLUTB223:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB112_L Register
struct LCDC_GDCCCLUTB112_L {
	unsigned int CLUTB224:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB112_U Register
struct LCDC_GDCCCLUTB112_U {
	unsigned int CLUTB225:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB113_L Register
struct LCDC_GDCCCLUTB113_L {
	unsigned int CLUTB226:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB113_U Register
struct LCDC_GDCCCLUTB113_U {
	unsigned int CLUTB227:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB114_L Register
struct LCDC_GDCCCLUTB114_L {
	unsigned int CLUTB228:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB114_U Register
struct LCDC_GDCCCLUTB114_U {
	unsigned int CLUTB229:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB115_L Register
struct LCDC_GDCCCLUTB115_L {
	unsigned int CLUTB230:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB115_U Register
struct LCDC_GDCCCLUTB115_U {
	unsigned int CLUTB231:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB116_L Register
struct LCDC_GDCCCLUTB116_L {
	unsigned int CLUTB232:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB116_U Register
struct LCDC_GDCCCLUTB116_U {
	unsigned int CLUTB233:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB117_L Register
struct LCDC_GDCCCLUTB117_L {
	unsigned int CLUTB234:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB117_U Register
struct LCDC_GDCCCLUTB117_U {
	unsigned int CLUTB235:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB118_L Register
struct LCDC_GDCCCLUTB118_L {
	unsigned int CLUTB236:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB118_U Register
struct LCDC_GDCCCLUTB118_U {
	unsigned int CLUTB237:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB119_L Register
struct LCDC_GDCCCLUTB119_L {
	unsigned int CLUTB238:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB119_U Register
struct LCDC_GDCCCLUTB119_U {
	unsigned int CLUTB239:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB120_L Register
struct LCDC_GDCCCLUTB120_L {
	unsigned int CLUTB240:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB120_U Register
struct LCDC_GDCCCLUTB120_U {
	unsigned int CLUTB241:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB121_L Register
struct LCDC_GDCCCLUTB121_L {
	unsigned int CLUTB242:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB121_U Register
struct LCDC_GDCCCLUTB121_U {
	unsigned int CLUTB243:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB122_L Register
struct LCDC_GDCCCLUTB122_L {
	unsigned int CLUTB244:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB122_U Register
struct LCDC_GDCCCLUTB122_U {
	unsigned int CLUTB245:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB123_L Register
struct LCDC_GDCCCLUTB123_L {
	unsigned int CLUTB246:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB123_U Register
struct LCDC_GDCCCLUTB123_U {
	unsigned int CLUTB247:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB124_L Register
struct LCDC_GDCCCLUTB124_L {
	unsigned int CLUTB248:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB124_U Register
struct LCDC_GDCCCLUTB124_U {
	unsigned int CLUTB249:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB125_L Register
struct LCDC_GDCCCLUTB125_L {
	unsigned int CLUTB250:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB125_U Register
struct LCDC_GDCCCLUTB125_U {
	unsigned int CLUTB251:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB126_L Register
struct LCDC_GDCCCLUTB126_L {
	unsigned int CLUTB252:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB126_U Register
struct LCDC_GDCCCLUTB126_U {
	unsigned int CLUTB253:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB127_L Register
struct LCDC_GDCCCLUTB127_L {
	unsigned int CLUTB254:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDCCCLUTB127_U Register
struct LCDC_GDCCCLUTB127_U {
	unsigned int CLUTB255:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LCDC_REG_STRUCT_L_H */
