/*
 * arch/arm/mach-tz3000/include/mach/regs/ether_reg_struct_l.h
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

#ifndef _ETHER_REG_STRUCT_L_H
#define _ETHER_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // EMACDRR Register
struct ETHER_EMACDRR {
	unsigned int DRDADR:32;		// [31:0]
};
 // EMACDRTRGR Register
struct ETHER_EMACDRTRGR {
	unsigned int Reserved3:2;		// [1:0]
	unsigned int DRDMSK:11;		// [12:2]
	unsigned int Reserved2:5;		// [17:13]
	unsigned int DRDTRG:11;		// [28:18]
	unsigned int Reserved:3;		// [31:29]
};
 // EMACDRENR Register
struct ETHER_EMACDRENR {
	unsigned int DRDEN:1;		// [0]
	unsigned int Reserved:31;		// [31:1]
};
 // EMACINTR Register
struct ETHER_EMACINTR {
	unsigned int DMAINT:1;		// [0]
	unsigned int SERR:1;		// [1]
	unsigned int Reserved:30;		// [31:2]
};
 // EMACINTENR Register
struct ETHER_EMACINTENR {
	unsigned int DMAINT:1;		// [0]
	unsigned int SERR:1;		// [1]
	unsigned int Reserved:30;		// [31:2]
};
 // EMACINTDCR Register
struct ETHER_EMACINTDCR {
	unsigned int IDLYEN:1;		// [0]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int IDLY:21;		// [24:4]
	unsigned int Reserved:7;		// [31:25]
};
 // EMACFINFR Register
struct ETHER_EMACFINFR {
	unsigned int PHYIF:3;		// [2:0]
	unsigned int PHYIFWAR:1;		// [3]
	unsigned int MACFLT:2;		// [5:4]
	unsigned int Reserved5:6;		// [11:6]
	unsigned int PHYINT_N:1;		// [12]
	unsigned int Reserved4:3;		// [15:13]
	unsigned int RFSZ:2;		// [17:16]
	unsigned int Reserved3:2;		// [19:18]
	unsigned int TFSZ:2;		// [21:20]
	unsigned int Reserved2:6;		// [27:22]
	unsigned int INTDLY:1;		// [28]
	unsigned int Reserved:3;		// [31:29]
};
 // DMACR Register
struct ETHER_DMACR {
	unsigned int SWRR:1;		// [0]
	unsigned int SWRT:1;		// [1]
	unsigned int Reserved2:2;		// [3:2]
	unsigned int DL:2;		// [5:4]
	unsigned int DE:1;		// [6]
	unsigned int Reserved:25;		// [31:7]
};
 // DMATXR Register
struct ETHER_DMATXR {
	unsigned int TRNS:2;		// [1:0]
	unsigned int Reserved:30;		// [31:2]
};
 // DMARXR Register
struct ETHER_DMARXR {
	unsigned int RCV:1;		// [0]
	unsigned int Reserved:31;		// [31:1]
};
 // DMAINTR Register
struct ETHER_DMAINTR {
	unsigned int RINT1:1;		// [0]
	unsigned int RINT2:1;		// [1]
	unsigned int RINT3:1;		// [2]
	unsigned int RINT4:1;		// [3]
	unsigned int RINT5:1;		// [4]
	unsigned int RINT6:1;		// [5]
	unsigned int RINT7:1;		// [6]
	unsigned int RINT8:1;		// [7]
	unsigned int TINT1:1;		// [8]
	unsigned int TINT2:1;		// [9]
	unsigned int TINT3:1;		// [10]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int RFE:1;		// [16]
	unsigned int RDE:1;		// [17]
	unsigned int FRC:1;		// [18]
	unsigned int TFE:1;		// [19]
	unsigned int TDE:1;		// [20]
	unsigned int FTC0:1;		// [21]
	unsigned int MINT:1;		// [22]
	unsigned int Reserved:1;		// [23]
	unsigned int RFRMER:1;		// [24]
	unsigned int RABT:1;		// [25]
	unsigned int TABT:1;		// [26]
	unsigned int ROC:1;		// [27]
	unsigned int TUC:1;		// [28]
	unsigned int FTC1:1;		// [29]
	unsigned int WB0:1;		// [30]
	unsigned int WB1:1;		// [31]
};
 // DMAINTENR Register
struct ETHER_DMAINTENR {
	unsigned int RINT1:1;		// [0]
	unsigned int RINT2:1;		// [1]
	unsigned int RINT3:1;		// [2]
	unsigned int RINT4:1;		// [3]
	unsigned int RINT5:1;		// [4]
	unsigned int RINT6:1;		// [5]
	unsigned int RINT7:1;		// [6]
	unsigned int RINT8:1;		// [7]
	unsigned int TINT1:1;		// [8]
	unsigned int TINT2:1;		// [9]
	unsigned int TINT3:1;		// [10]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int RFE:1;		// [16]
	unsigned int RDE:1;		// [17]
	unsigned int FRC:1;		// [18]
	unsigned int TFE:1;		// [19]
	unsigned int TDE:1;		// [20]
	unsigned int FTC0:1;		// [21]
	unsigned int MINT:1;		// [22]
	unsigned int Reserved:1;		// [23]
	unsigned int RFRMER:1;		// [24]
	unsigned int RABT:1;		// [25]
	unsigned int TABT:1;		// [26]
	unsigned int ROC:1;		// [27]
	unsigned int TUC:1;		// [28]
	unsigned int FTC1:1;		// [29]
	unsigned int WB0:1;		// [30]
	unsigned int WB1:1;		// [31]
};
 // ERRMSKR Register
struct ETHER_ERRMSKR {
	unsigned int RINT1:1;		// [0]
	unsigned int RINT2:1;		// [1]
	unsigned int RINT3:1;		// [2]
	unsigned int RINT4:1;		// [3]
	unsigned int RINT5:1;		// [4]
	unsigned int RINT6:1;		// [5]
	unsigned int RINT7:1;		// [6]
	unsigned int RINT8:1;		// [7]
	unsigned int TINT1:1;		// [8]
	unsigned int TINT2:1;		// [9]
	unsigned int TINT3:1;		// [10]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int RABT:1;		// [16]
	unsigned int TABT:1;		// [17]
	unsigned int Reserved:14;		// [31:18]
};
 // RXMISCNTR Register
struct ETHER_RXMISCNTR {
	unsigned int MIS:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // TXFIFOTHR Register
struct ETHER_TXFIFOTHR {
	unsigned int FO:11;		// [10:0]
	unsigned int Reserved:21;		// [31:11]
};
 // FIFOSIZER Register
struct ETHER_FIFOSIZER {
	unsigned int RA:8;		// [7:0]
	unsigned int TA:5;		// [12:8]
	unsigned int Reserved:19;		// [31:13]
};
 // DMARXMODR Register
struct ETHER_DMARXMODR {
	unsigned int RCVMOD:1;		// [0]
	unsigned int Reserved:31;		// [31:1]
};
 // RXPADR Register
struct ETHER_RXPADR {
	unsigned int PADP:16;		// [15:0]
	unsigned int PADS:5;		// [20:16]
	unsigned int Reserved:11;		// [31:21]
};
 // RXFIFOTHR Register
struct ETHER_RXFIFOTHR {
	unsigned int RFD:8;		// [7:0]
	unsigned int Reserved2:8;		// [15:8]
	unsigned int RFF:5;		// [20:16]
	unsigned int Reserved:11;		// [31:21]
};
 // TXFIFOSTSR Register
struct ETHER_TXFIFOSTSR {
	unsigned int DAM:8;		// [7:0]
	unsigned int Reserved4:8;		// [15:8]
	unsigned int FAM:3;		// [18:16]
	unsigned int Reserved3:5;		// [23:19]
	unsigned int D_EN:1;		// [24]
	unsigned int F_EN:1;		// [25]
	unsigned int WB:1;		// [26]
	unsigned int Reserved2:1;		// [27]
	unsigned int STP:1;		// [28]
	unsigned int DMA:1;		// [29]
	unsigned int WAI:1;		// [30]
	unsigned int Reserved:1;		// [31]
};
 // RXFIFOSTSR Register
struct ETHER_RXFIFOSTSR {
	unsigned int DAM:12;		// [11:0]
	unsigned int Reserved3:4;		// [15:12]
	unsigned int FAM:5;		// [20:16]
	unsigned int Reserved2:3;		// [23:21]
	unsigned int D_EN:1;		// [24]
	unsigned int F_EN:1;		// [25]
	unsigned int Reserved:6;		// [31:26]
};
 // MACCR Register
struct ETHER_MACCR {
	unsigned int PRM:1;		// [0]
	unsigned int DPM:1;		// [1]
	unsigned int Reserved4:3;		// [4:2]
	unsigned int TPE:1;		// [5]
	unsigned int RPE:1;		// [6]
	unsigned int Reserved3:9;		// [15:7]
	unsigned int TXF:1;		// [16]
	unsigned int RXF:1;		// [17]
	unsigned int PFR:1;		// [18]
	unsigned int TZPF:1;		// [19]
	unsigned int RZPF:1;		// [20]
	unsigned int DPAD:1;		// [21]
	unsigned int Reserved2:1;		// [22]
	unsigned int RCSC:1;		// [23]
	unsigned int TCPT:1;		// [24]
	unsigned int RCPT:1;		// [25]
	unsigned int TRCCM:1;		// [26]
	unsigned int Reserved:5;		// [31:27]
};
 // LENLMTR Register
struct ETHER_LENLMTR {
	unsigned int LENLMT:18;		// [17:0]
	unsigned int Reserved:14;		// [31:18]
};
 // MACINTR Register
struct ETHER_MACINTR {
	unsigned int FCI:1;		// [0]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int PFRI:1;		// [4]
	unsigned int Reserved:27;		// [31:5]
};
 // MACINTENR Register
struct ETHER_MACINTENR {
	unsigned int FCI:1;		// [0]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int PFRI:1;		// [4]
	unsigned int Reserved:27;		// [31:5]
};
 // PHYINTR Register
struct ETHER_PHYINTR {
	unsigned int PHYIP:1;		// [0]
	unsigned int Reserved:31;		// [31:1]
};
 // RGIBSR Register
struct ETHER_RGIBSR {
	unsigned int Reserved:32;		// [31:0]
};
 // MACSTSR Register
struct ETHER_MACSTSR {
	unsigned int Reserved2:1;		// [0]
	unsigned int DUPLEX:1;		// [1]
	unsigned int SPEED:2;		// [3:2]
	unsigned int Reserved:28;		// [31:4]
};
 // PHYIFR Register
struct ETHER_PHYIFR {
	unsigned int SEL_PHYIF:1;		// [0]
	unsigned int Reserved:15;		// [15:1]
	unsigned int CYC_CLKSW:16;		// [31:16]
};
 // APFTPR Register
struct ETHER_APFTPR {
	unsigned int APFTP:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // MPFTPR Register
struct ETHER_MPFTPR {
	unsigned int MPFTP:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // PFTXCNTR Register
struct ETHER_PFTXCNTR {
	unsigned int PFTXCNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // PFRXCNTR Register
struct ETHER_PFRXCNTR {
	unsigned int PFRXCNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // PFRTLMTR Register
struct ETHER_PFRTLMTR {
	unsigned int PFRTLMT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // PFRTCNTR Register
struct ETHER_PFRTCNTR {
	unsigned int PFRTCNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // MACGCR Register
struct ETHER_MACGCR {
	unsigned int Reserved3:1;		// [0]
	unsigned int BSE:1;		// [1]
	unsigned int Reserved2:2;		// [3:2]
	unsigned int SPEED:2;		// [5:4]
	unsigned int Reserved:26;		// [31:6]
};
 // BSTLMTR Register
struct ETHER_BSTLMTR {
	unsigned int BSTLMT:12;		// [11:0]
	unsigned int Reserved:20;		// [31:12]
};
 // UMACAR Register
struct ETHER_UMACAR {
	unsigned int UMADR:32;		// [31:0]
};
 // LMACAR Register
struct ETHER_LMACAR {
	unsigned int LMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // TINT1CNTR Register
struct ETHER_TINT1CNTR {
	unsigned int TINT1CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // TINT2CNTR Register
struct ETHER_TINT2CNTR {
	unsigned int TINT2CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // TINT3CNTR Register
struct ETHER_TINT3CNTR {
	unsigned int TINT3CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // RINT1CNTR Register
struct ETHER_RINT1CNTR {
	unsigned int RINT1CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // RINT2CNTR Register
struct ETHER_RINT2CNTR {
	unsigned int RINT2CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // RINT3CNTR Register
struct ETHER_RINT3CNTR {
	unsigned int RINT3CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // RINT4CNTR Register
struct ETHER_RINT4CNTR {
	unsigned int RINT4CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // RINT5CNTR Register
struct ETHER_RINT5CNTR {
	unsigned int RINT5CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // RINT6CNTR Register
struct ETHER_RINT6CNTR {
	unsigned int RINT6CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // RINT7CNTR Register
struct ETHER_RINT7CNTR {
	unsigned int RINT7CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // RINT8CNTR Register
struct ETHER_RINT8CNTR {
	unsigned int RINT8CNT:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // MDIOSTSR Register
struct ETHER_MDIOSTSR {
	unsigned int BSY:1;		// [0]
	unsigned int Reserved:31;		// [31:1]
};
 // MDIOCMDR Register
struct ETHER_MDIOCMDR {
	unsigned int OP:2;		// [1:0]
	unsigned int Reserved:30;		// [31:2]
};
 // MDIOADRR Register
struct ETHER_MDIOADRR {
	unsigned int PHYREG:5;		// [4:0]
	unsigned int PHYADR:5;		// [9:5]
	unsigned int Reserved:22;		// [31:10]
};
 // MDIODATR Register
struct ETHER_MDIODATR {
	unsigned int PHYDATA:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // MDIOCYCR Register
struct ETHER_MDIOCYCR {
	unsigned int CYCOCLK:8;		// [7:0]
	unsigned int Reserved:24;		// [31:8]
};
 // DESCCR Register
struct ETHER_DESCCR {
	unsigned int ENR:1;		// [0]
	unsigned int ENT:1;		// [1]
	unsigned int Reserved:30;		// [31:2]
};
 // DTXSPAR Register
struct ETHER_DTXSPAR {
	unsigned int Reserved:4;		// [3:0]
	unsigned int DTXSPA:28;		// [31:4]
};
 // DTXCPAR Register
struct ETHER_DTXCPAR {
	unsigned int Reserved:4;		// [3:0]
	unsigned int DTXCPA:28;		// [31:4]
};
 // DTXLPAR Register
struct ETHER_DTXLPAR {
	unsigned int Reserved:4;		// [3:0]
	unsigned int DTXLPA:28;		// [31:4]
};
 // DTXDLR Register
struct ETHER_DTXDLR {
	unsigned int DTXDL:1;		// [0]
	unsigned int Reserved:31;		// [31:1]
};
 // DRXSPAR Register
struct ETHER_DRXSPAR {
	unsigned int Reserved:4;		// [3:0]
	unsigned int DRXSPA:28;		// [31:4]
};
 // DRXCPAR Register
struct ETHER_DRXCPAR {
	unsigned int Reserved:4;		// [3:0]
	unsigned int DRXCPA:28;		// [31:4]
};
 // DRXLPAR Register
struct ETHER_DRXLPAR {
	unsigned int Reserved:4;		// [3:0]
	unsigned int DRXLPA:28;		// [31:4]
};
 // DRXDLR Register
struct ETHER_DRXDLR {
	unsigned int DTXDL:1;		// [0]
	unsigned int Reserved:31;		// [31:1]
};
 // FMAR00HR Register
struct ETHER_FMAR00HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR00LR Register
struct ETHER_FMAR00LR {
	unsigned int FLMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FMAR01HR Register
struct ETHER_FMAR01HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR01LR Register
struct ETHER_FMAR01LR {
	unsigned int FLMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FMAR02HR Register
struct ETHER_FMAR02HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR02LR Register
struct ETHER_FMAR02LR {
	unsigned int FLMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FMAR03HR Register
struct ETHER_FMAR03HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR03LR Register
struct ETHER_FMAR03LR {
	unsigned int FLMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FMAR04HR Register
struct ETHER_FMAR04HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR04LR Register
struct ETHER_FMAR04LR {
	unsigned int FLMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FMAR05HR Register
struct ETHER_FMAR05HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR05LR Register
struct ETHER_FMAR05LR {
	unsigned int FLMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FMAR06HR Register
struct ETHER_FMAR06HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR06LR Register
struct ETHER_FMAR06LR {
	unsigned int FLMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FMAR07HR Register
struct ETHER_FMAR07HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR07LR Register
struct ETHER_FMAR07LR {
	unsigned int FLMADR:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FLTCR Register
struct ETHER_FLTCR {
	unsigned int ENBL:1;		// [0]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int MODE:1;		// [4]
	unsigned int Reserved:27;		// [31:5]
};
 // FLTENTR Register
struct ETHER_FLTENTR {
	unsigned int ENT_EN:8;		// [7:0]
	unsigned int Reserved2:8;		// [15:8]
	unsigned int ENT_EN_WE:8;		// [23:16]
	unsigned int Reserved:8;		// [31:24]
};
 // FLTFWCNTR Register
struct ETHER_FLTFWCNTR {
	unsigned int FORWARD:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // FLTDRCNTR Register
struct ETHER_FLTDRCNTR {
	unsigned int DROP:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ETHER_REG_STRUCT_L_H */
