/*
 * arch/arm/mach-tz2000/include/mach/regs/ethermac_reg_struct_b.h
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

#ifndef _ETHERMAC_REG_STRUCT_B_H
#define _ETHERMAC_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // EMACDRR Register
struct ETHERMAC_EMACDRR {
	unsigned int DRDADR:32;		// [31:0]
};
 // EMACDRTRGR Register
struct ETHERMAC_EMACDRTRGR {
	unsigned int Reserved:3;		// [31:29]
	unsigned int DRDTRG:11;		// [28:18]
	unsigned int Reserved2:5;		// [17:13]
	unsigned int DRDMSK:11;		// [12:2]
	unsigned int Reserved3:2;		// [1:0]
};
 // EMACDRENR Register
struct ETHERMAC_EMACDRENR {
	unsigned int Reserved:31;		// [31:1]
	unsigned int DRDEN:1;		// [0]
};
 // EMACINTR Register
struct ETHERMAC_EMACINTR {
	unsigned int Reserved:30;		// [31:2]
	unsigned int SERR:1;		// [1]
	unsigned int DMAINT:1;		// [0]
};
 // EMACINTENR Register
struct ETHERMAC_EMACINTENR {
	unsigned int Reserved:30;		// [31:2]
	unsigned int SERR:1;		// [1]
	unsigned int DMAINT:1;		// [0]
};
 // EMACINTDCR Register
struct ETHERMAC_EMACINTDCR {
	unsigned int Reserved:7;		// [31:25]
	unsigned int IDLY:21;		// [24:4]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int IDLYEN:1;		// [0]
};
 // EMACFINFR Register
struct ETHERMAC_EMACFINFR {
	unsigned int Reserved:3;		// [31:29]
	unsigned int INTDLY:1;		// [28]
	unsigned int Reserved2:6;		// [27:22]
	unsigned int TFSZ:2;		// [21:20]
	unsigned int Reserved3:2;		// [19:18]
	unsigned int RFSZ:2;		// [17:16]
	unsigned int Reserved4:3;		// [15:13]
	unsigned int PHYINT_N:1;		// [12]
	unsigned int Reserved5:6;		// [11:6]
	unsigned int MACFLT:2;		// [5:4]
	unsigned int PHYIFWAR:1;		// [3]
	unsigned int PHYIF:3;		// [2:0]
};
 // DMACR Register
struct ETHERMAC_DMACR {
	unsigned int Reserved:25;		// [31:7]
	unsigned int DE:1;		// [6]
	unsigned int DL:2;		// [5:4]
	unsigned int Reserved2:2;		// [3:2]
	unsigned int SWRT:1;		// [1]
	unsigned int SWRR:1;		// [0]
};
 // DMATXR Register
struct ETHERMAC_DMATXR {
	unsigned int Reserved:30;		// [31:2]
	unsigned int TRNS:2;		// [1:0]
};
 // DMARXR Register
struct ETHERMAC_DMARXR {
	unsigned int Reserved:31;		// [31:1]
	unsigned int RCV:1;		// [0]
};
 // DMAINTR Register
struct ETHERMAC_DMAINTR {
	unsigned int WB1:1;		// [31]
	unsigned int WB0:1;		// [30]
	unsigned int FTC1:1;		// [29]
	unsigned int TUC:1;		// [28]
	unsigned int ROC:1;		// [27]
	unsigned int TABT:1;		// [26]
	unsigned int RABT:1;		// [25]
	unsigned int RFRMER:1;		// [24]
	unsigned int Reserved:1;		// [23]
	unsigned int MINT:1;		// [22]
	unsigned int FTC0:1;		// [21]
	unsigned int TDE:1;		// [20]
	unsigned int TFE:1;		// [19]
	unsigned int FRC:1;		// [18]
	unsigned int RDE:1;		// [17]
	unsigned int RFE:1;		// [16]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int TINT3:1;		// [10]
	unsigned int TINT2:1;		// [9]
	unsigned int TINT1:1;		// [8]
	unsigned int RINT8:1;		// [7]
	unsigned int RINT7:1;		// [6]
	unsigned int RINT6:1;		// [5]
	unsigned int RINT5:1;		// [4]
	unsigned int RINT4:1;		// [3]
	unsigned int RINT3:1;		// [2]
	unsigned int RINT2:1;		// [1]
	unsigned int RINT1:1;		// [0]
};
 // DMAINTENR Register
struct ETHERMAC_DMAINTENR {
	unsigned int WB1:1;		// [31]
	unsigned int WB0:1;		// [30]
	unsigned int FTC1:1;		// [29]
	unsigned int TUC:1;		// [28]
	unsigned int ROC:1;		// [27]
	unsigned int TABT:1;		// [26]
	unsigned int RABT:1;		// [25]
	unsigned int RFRMER:1;		// [24]
	unsigned int Reserved:1;		// [23]
	unsigned int MINT:1;		// [22]
	unsigned int FTC0:1;		// [21]
	unsigned int TDE:1;		// [20]
	unsigned int TFE:1;		// [19]
	unsigned int FRC:1;		// [18]
	unsigned int RDE:1;		// [17]
	unsigned int RFE:1;		// [16]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int TINT3:1;		// [10]
	unsigned int TINT2:1;		// [9]
	unsigned int TINT1:1;		// [8]
	unsigned int RINT8:1;		// [7]
	unsigned int RINT7:1;		// [6]
	unsigned int RINT6:1;		// [5]
	unsigned int RINT5:1;		// [4]
	unsigned int RINT4:1;		// [3]
	unsigned int RINT3:1;		// [2]
	unsigned int RINT2:1;		// [1]
	unsigned int RINT1:1;		// [0]
};
 // ERRMSKR Register
struct ETHERMAC_ERRMSKR {
	unsigned int Reserved:14;		// [31:18]
	unsigned int TABT:1;		// [17]
	unsigned int RABT:1;		// [16]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int TINT3:1;		// [10]
	unsigned int TINT2:1;		// [9]
	unsigned int TINT1:1;		// [8]
	unsigned int RINT8:1;		// [7]
	unsigned int RINT7:1;		// [6]
	unsigned int RINT6:1;		// [5]
	unsigned int RINT5:1;		// [4]
	unsigned int RINT4:1;		// [3]
	unsigned int RINT3:1;		// [2]
	unsigned int RINT2:1;		// [1]
	unsigned int RINT1:1;		// [0]
};
 // RXMISCNTR Register
struct ETHERMAC_RXMISCNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int MIS:16;		// [15:0]
};
 // TXFIFOTHR Register
struct ETHERMAC_TXFIFOTHR {
	unsigned int Reserved:21;		// [31:11]
	unsigned int FO:11;		// [10:0]
};
 // FIFOSIZER Register
struct ETHERMAC_FIFOSIZER {
	unsigned int Reserved:19;		// [31:13]
	unsigned int TA:5;		// [12:8]
	unsigned int RA:8;		// [7:0]
};
 // DMARXMODR Register
struct ETHERMAC_DMARXMODR {
	unsigned int Reserved:31;		// [31:1]
	unsigned int RCVMOD:1;		// [0]
};
 // RXPADR Register
struct ETHERMAC_RXPADR {
	unsigned int Reserved:11;		// [31:21]
	unsigned int PADS:5;		// [20:16]
	unsigned int PADP:16;		// [15:0]
};
 // RXFIFOTHR Register
struct ETHERMAC_RXFIFOTHR {
	unsigned int Reserved:11;		// [31:21]
	unsigned int RFF:5;		// [20:16]
	unsigned int Reserved2:8;		// [15:8]
	unsigned int RFD:8;		// [7:0]
};
 // TXFIFOSTSR Register
struct ETHERMAC_TXFIFOSTSR {
	unsigned int Reserved:1;		// [31]
	unsigned int WAI:1;		// [30]
	unsigned int DMA:1;		// [29]
	unsigned int STP:1;		// [28]
	unsigned int Reserved2:1;		// [27]
	unsigned int WB:1;		// [26]
	unsigned int F_EN:1;		// [25]
	unsigned int D_EN:1;		// [24]
	unsigned int Reserved3:5;		// [23:19]
	unsigned int FAM:3;		// [18:16]
	unsigned int Reserved4:8;		// [15:8]
	unsigned int DAM:8;		// [7:0]
};
 // RXFIFOSTSR Register
struct ETHERMAC_RXFIFOSTSR {
	unsigned int Reserved:6;		// [31:26]
	unsigned int F_EN:1;		// [25]
	unsigned int D_EN:1;		// [24]
	unsigned int Reserved2:3;		// [23:21]
	unsigned int FAM:5;		// [20:16]
	unsigned int Reserved3:4;		// [15:12]
	unsigned int DAM:12;		// [11:0]
};
 // MACCR Register
struct ETHERMAC_MACCR {
	unsigned int Reserved:5;		// [31:27]
	unsigned int TRCCM:1;		// [26]
	unsigned int RCPT:1;		// [25]
	unsigned int TCPT:1;		// [24]
	unsigned int RCSC:1;		// [23]
	unsigned int Reserved2:1;		// [22]
	unsigned int DPAD:1;		// [21]
	unsigned int RZPF:1;		// [20]
	unsigned int TZPF:1;		// [19]
	unsigned int PFR:1;		// [18]
	unsigned int RXF:1;		// [17]
	unsigned int TXF:1;		// [16]
	unsigned int Reserved3:9;		// [15:7]
	unsigned int RPE:1;		// [6]
	unsigned int TPE:1;		// [5]
	unsigned int Reserved4:3;		// [4:2]
	unsigned int DPM:1;		// [1]
	unsigned int PRM:1;		// [0]
};
 // LENLMTR Register
struct ETHERMAC_LENLMTR {
	unsigned int Reserved:14;		// [31:18]
	unsigned int LENLMT:18;		// [17:0]
};
 // MACINTR Register
struct ETHERMAC_MACINTR {
	unsigned int Reserved:27;		// [31:5]
	unsigned int PFRI:1;		// [4]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int FCI:1;		// [0]
};
 // MACINTENR Register
struct ETHERMAC_MACINTENR {
	unsigned int Reserved:27;		// [31:5]
	unsigned int PFRI:1;		// [4]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int FCI:1;		// [0]
};
 // PHYINTR Register
struct ETHERMAC_PHYINTR {
	unsigned int Reserved:31;		// [31:1]
	unsigned int PHYIP:1;		// [0]
};
 // RGIBSR Register
struct ETHERMAC_RGIBSR {
	unsigned int Reserved:32;		// [31:0]
};
 // MACSTSR Register
struct ETHERMAC_MACSTSR {
	unsigned int Reserved:28;		// [31:4]
	unsigned int SPEED:2;		// [3:2]
	unsigned int DUPLEX:1;		// [1]
	unsigned int Reserved2:1;		// [0]
};
 // PHYIFR Register
struct ETHERMAC_PHYIFR {
	unsigned int CYC_CLKSW:16;		// [31:16]
	unsigned int Reserved:15;		// [15:1]
	unsigned int SEL_PHYIF:1;		// [0]
};
 // APFTPR Register
struct ETHERMAC_APFTPR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int APFTP:16;		// [15:0]
};
 // MPFTPR Register
struct ETHERMAC_MPFTPR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int MPFTP:16;		// [15:0]
};
 // PFTXCNTR Register
struct ETHERMAC_PFTXCNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int PFTXCNT:16;		// [15:0]
};
 // PFRXCNTR Register
struct ETHERMAC_PFRXCNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int PFRXCNT:16;		// [15:0]
};
 // PFRTLMTR Register
struct ETHERMAC_PFRTLMTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int PFRTLMT:16;		// [15:0]
};
 // PFRTCNTR Register
struct ETHERMAC_PFRTCNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int PFRTCNT:16;		// [15:0]
};
 // MACGCR Register
struct ETHERMAC_MACGCR {
	unsigned int Reserved:26;		// [31:6]
	unsigned int SPEED:2;		// [5:4]
	unsigned int Reserved2:2;		// [3:2]
	unsigned int BSE:1;		// [1]
	unsigned int Reserved3:1;		// [0]
};
 // BSTLMTR Register
struct ETHERMAC_BSTLMTR {
	unsigned int Reserved:20;		// [31:12]
	unsigned int BSTLMT:12;		// [11:0]
};
 // UMACAR Register
struct ETHERMAC_UMACAR {
	unsigned int UMADR:32;		// [31:0]
};
 // LMACAR Register
struct ETHERMAC_LMACAR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int LMADR:16;		// [15:0]
};
 // TINT1CNTR Register
struct ETHERMAC_TINT1CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int TINT1CNT:16;		// [15:0]
};
 // TINT2CNTR Register
struct ETHERMAC_TINT2CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int TINT2CNT:16;		// [15:0]
};
 // TINT3CNTR Register
struct ETHERMAC_TINT3CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int TINT3CNT:16;		// [15:0]
};
 // RINT1CNTR Register
struct ETHERMAC_RINT1CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RINT1CNT:16;		// [15:0]
};
 // RINT2CNTR Register
struct ETHERMAC_RINT2CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RINT2CNT:16;		// [15:0]
};
 // RINT3CNTR Register
struct ETHERMAC_RINT3CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RINT3CNT:16;		// [15:0]
};
 // RINT4CNTR Register
struct ETHERMAC_RINT4CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RINT4CNT:16;		// [15:0]
};
 // RINT5CNTR Register
struct ETHERMAC_RINT5CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RINT5CNT:16;		// [15:0]
};
 // RINT6CNTR Register
struct ETHERMAC_RINT6CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RINT6CNT:16;		// [15:0]
};
 // RINT7CNTR Register
struct ETHERMAC_RINT7CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RINT7CNT:16;		// [15:0]
};
 // RINT8CNTR Register
struct ETHERMAC_RINT8CNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RINT8CNT:16;		// [15:0]
};
 // MDIOSTSR Register
struct ETHERMAC_MDIOSTSR {
	unsigned int Reserved:31;		// [31:1]
	unsigned int BSY:1;		// [0]
};
 // MDIOCMDR Register
struct ETHERMAC_MDIOCMDR {
	unsigned int Reserved:30;		// [31:2]
	unsigned int OP:2;		// [1:0]
};
 // MDIOADRR Register
struct ETHERMAC_MDIOADRR {
	unsigned int Reserved:22;		// [31:10]
	unsigned int PHYADR:5;		// [9:5]
	unsigned int PHYREG:5;		// [4:0]
};
 // MDIODATR Register
struct ETHERMAC_MDIODATR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int PHYDATA:16;		// [15:0]
};
 // MDIOCYCR Register
struct ETHERMAC_MDIOCYCR {
	unsigned int Reserved:24;		// [31:8]
	unsigned int CYCOCLK:8;		// [7:0]
};
 // DESCCR Register
struct ETHERMAC_DESCCR {
	unsigned int Reserved:30;		// [31:2]
	unsigned int ENT:1;		// [1]
	unsigned int ENR:1;		// [0]
};
 // DTXSPAR Register
struct ETHERMAC_DTXSPAR {
	unsigned int DTXSPA:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // DTXCPAR Register
struct ETHERMAC_DTXCPAR {
	unsigned int DTXCPA:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // DTXLPAR Register
struct ETHERMAC_DTXLPAR {
	unsigned int DTXLPA:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // DTXDLR Register
struct ETHERMAC_DTXDLR {
	unsigned int Reserved:31;		// [31:1]
	unsigned int DTXDL:1;		// [0]
};
 // DRXSPAR Register
struct ETHERMAC_DRXSPAR {
	unsigned int DRXSPA:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // DRXCPAR Register
struct ETHERMAC_DRXCPAR {
	unsigned int DRXCPA:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // DRXLPAR Register
struct ETHERMAC_DRXLPAR {
	unsigned int DRXLPA:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // DRXDLR Register
struct ETHERMAC_DRXDLR {
	unsigned int Reserved:31;		// [31:1]
	unsigned int DTXDL:1;		// [0]
};
 // FMAR00HR Register
struct ETHERMAC_FMAR00HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR00LR Register
struct ETHERMAC_FMAR00LR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FLMADR:16;		// [15:0]
};
 // FMAR01HR Register
struct ETHERMAC_FMAR01HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR01LR Register
struct ETHERMAC_FMAR01LR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FLMADR:16;		// [15:0]
};
 // FMAR02HR Register
struct ETHERMAC_FMAR02HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR02LR Register
struct ETHERMAC_FMAR02LR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FLMADR:16;		// [15:0]
};
 // FMAR03HR Register
struct ETHERMAC_FMAR03HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR03LR Register
struct ETHERMAC_FMAR03LR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FLMADR:16;		// [15:0]
};
 // FMAR04HR Register
struct ETHERMAC_FMAR04HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR04LR Register
struct ETHERMAC_FMAR04LR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FLMADR:16;		// [15:0]
};
 // FMAR05HR Register
struct ETHERMAC_FMAR05HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR05LR Register
struct ETHERMAC_FMAR05LR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FLMADR:16;		// [15:0]
};
 // FMAR06HR Register
struct ETHERMAC_FMAR06HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR06LR Register
struct ETHERMAC_FMAR06LR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FLMADR:16;		// [15:0]
};
 // FMAR07HR Register
struct ETHERMAC_FMAR07HR {
	unsigned int FUMADR:32;		// [31:0]
};
 // FMAR07LR Register
struct ETHERMAC_FMAR07LR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FLMADR:16;		// [15:0]
};
 // FLTCR Register
struct ETHERMAC_FLTCR {
	unsigned int Reserved:27;		// [31:5]
	unsigned int MODE:1;		// [4]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int ENBL:1;		// [0]
};
 // FLTENTR Register
struct ETHERMAC_FLTENTR {
	unsigned int Reserved:8;		// [31:24]
	unsigned int ENT_EN_WE:8;		// [23:16]
	unsigned int Reserved2:8;		// [15:8]
	unsigned int ENT_EN:8;		// [7:0]
};
 // FLTFWCNTR Register
struct ETHERMAC_FLTFWCNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FORWARD:16;		// [15:0]
};
 // FLTDRCNTR Register
struct ETHERMAC_FLTDRCNTR {
	unsigned int Reserved:16;		// [31:16]
	unsigned int DROP:16;		// [15:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ETHERMAC_REG_STRUCT_B_H */
