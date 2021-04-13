/*
 * arch/arm/mach-tz3000/include/mach/regs/fdramc_reg_struct_l.h
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

#ifndef _FDRAMC_REG_STRUCT_L_H
#define _FDRAMC_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // DRAMType Register
struct FDRAMC_DRAMTYPE {
	unsigned int DRAMType:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // AddressConfig_CS Register
struct FDRAMC_ADDRESSCONFIG_CS {
	unsigned int Chip_Select_Bit_Location:6;		// [5:0]
	unsigned int reserved1:2;		// [7:6]
	unsigned int Chip_Select_Width:2;		// [9:8]
	unsigned int reserved2:22;		// [31:10]
};
 // AddressConfig_Row Register
struct FDRAMC_ADDRESSCONFIG_ROW {
	unsigned int Row_Bit_Location:5;		// [4:0]
	unsigned int reserved1:3;		// [7:5]
	unsigned int Row_Address_Width:5;		// [12:8]
	unsigned int reserved2:19;		// [31:13]
};
 // AddressConfig_Bank Register
struct FDRAMC_ADDRESSCONFIG_BANK {
	unsigned int Bank_Bit_Location:5;		// [4:0]
	unsigned int reserved1:3;		// [7:5]
	unsigned int Bank_Width:2;		// [9:8]
	unsigned int reserved2:22;		// [31:10]
};
 // AddressConfig_Col Register
struct FDRAMC_ADDRESSCONFIG_COL {
	unsigned int Column_Bit_Location_0:5;		// [4:0]
	unsigned int reserved1:3;		// [7:5]
	unsigned int Column_Address_Width_0:4;		// [11:8]
	unsigned int reserved2:4;		// [15:12]
	unsigned int Column_Bit_Location_1:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int Column_Address_Width_1:4;		// [27:24]
	unsigned int reserved4:4;		// [31:28]
};
 // DataConfig Register
struct FDRAMC_DATACONFIG {
	unsigned int DataConfig:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // BstLenLog Register
struct FDRAMC_BSTLENLOG {
	unsigned int BstLenLog:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // MRRBstLenLog Register
struct FDRAMC_MRRBSTLENLOG {
	unsigned int MRRBstLenLog:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // BWHalfMode Register
struct FDRAMC_BWHALFMODE {
	unsigned int BWHalfMode:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // APwrDWtPd Register
struct FDRAMC_APWRDWTPD {
	unsigned int APwrDWtPd:12;		// [11:0]
	unsigned int reserved:20;		// [31:12]
};
 // RftoRfMax Register
struct FDRAMC_RFTORFMAX {
	unsigned int RftoRfMax:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // PAlltoANYPd Register
struct FDRAMC_PALLTOANYPD {
	unsigned int PAlltoANYPd:3;		// [2:0]
	unsigned int reserved:28;		// [30:3]
	unsigned int reserved2:1;		// [31]
};
 // InitMtoMPd Register
struct FDRAMC_INITMTOMPD {
	unsigned int InitMtoMPd:3;		// [2:0]
	unsigned int reserved:29;		// [31:3]
};
 // ReftoANYPd Register
struct FDRAMC_REFTOANYPD {
	unsigned int ReftoANYPd:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // BkAtoRWPd Register
struct FDRAMC_BKATORWPD {
	unsigned int BkAtoRWPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // AtoAPd Register
struct FDRAMC_ATOAPD {
	unsigned int AtoAPd:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // BkRtoPPd Register
struct FDRAMC_BKRTOPPD {
	unsigned int BkRtoPPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // BkWtoPPd Register
struct FDRAMC_BKWTOPPD {
	unsigned int BkWtoPPd:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // BkPtoANYPd Register
struct FDRAMC_BKPTOANYPD {
	unsigned int BkPtoANYPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // RtoWPd Register
struct FDRAMC_RTOWPD {
	unsigned int RtoWPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // InitCkeUptoANYPd Register
struct FDRAMC_INITCKEUPTOANYPD {
	unsigned int InitCkeUptoANYPd:18;		// [17:0]
	unsigned int reserved:14;		// [31:18]
};
 // BkAtoAPd Register
struct FDRAMC_BKATOAPD {
	unsigned int BkAtoAPd:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // InitOITPd Register
struct FDRAMC_INITOITPD {
	unsigned int InitOITPd:3;		// [2:0]
	unsigned int reserved:29;		// [31:3]
};
 // BkAtoPPd Register
struct FDRAMC_BKATOPPD {
	unsigned int BkAtoPPd:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // BkRAtoANYPd Register
struct FDRAMC_BKRATOANYPD {
	unsigned int BkRAtoANYPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // BkWAtoANYPd Register
struct FDRAMC_BKWATOANYPD {
	unsigned int BkWAtoANYPd:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // TAWPd Register
struct FDRAMC_TAWPD {
	unsigned int TAWPd:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // FAWPd Register
struct FDRAMC_FAWPD {
	unsigned int FAWPd:6;		// [5:0]
	unsigned int reserved:25;		// [30:6]
	unsigned int reserved2:1;		// [31]
};
 // WtoRPd Register
struct FDRAMC_WTORPD {
	unsigned int WtoRPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // InitDLLKPd Register
struct FDRAMC_INITDLLKPD {
	unsigned int InitDLLKPd:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // SrxtoANYPd Register
struct FDRAMC_SRXTOANYPD {
	unsigned int SrxtoANYPd:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // SrxtoRWPd Register
struct FDRAMC_SRXTORWPD {
	unsigned int SrxtoRWPd:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // PdxtoANYPd Register
struct FDRAMC_PDXTOANYPD {
	unsigned int PdxtoANYPd:3;		// [2:0]
	unsigned int reserved:29;		// [31:3]
};
 // PdxtoRWPd Register
struct FDRAMC_PDXTORWPD {
	unsigned int PdxtoRWPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // MtoANYPd Register
struct FDRAMC_MTOANYPD {
	unsigned int MtoANYPd:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // ZQCLtoANYPd Register
struct FDRAMC_ZQCLTOANYPD {
	unsigned int ZQCLtoANYPd:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // InitZQCLtoANYPd Register
struct FDRAMC_INITZQCLTOANYPD {
	unsigned int InitZQCLtoANYPd:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // ZQCStoANYPd Register
struct FDRAMC_ZQCSTOANYPD {
	unsigned int ZQCStoANYPd:7;		// [6:0]
	unsigned int reserved:25;		// [31:7]
};
 // RtoPWDPd Register
struct FDRAMC_RTOPWDPD {
	unsigned int RtoPWDPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // PdxtoPWDPd Register
struct FDRAMC_PDXTOPWDPD {
	unsigned int PdxtoPWDPd:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // SrxtoPWDPd Register
struct FDRAMC_SRXTOPWDPD {
	unsigned int SrxtoPWDPd:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // SretoSrxPd Register
struct FDRAMC_SRETOSRXPD {
	unsigned int SretoSrxPd:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // PdetoPdxPd Register
struct FDRAMC_PDETOPDXPD {
	unsigned int PdetoPdxPd:3;		// [2:0]
	unsigned int reserved:29;		// [31:3]
};
 // DRkWtoWPd Register
struct FDRAMC_DRKWTOWPD {
	unsigned int DRkWtoWPd:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // DRkRtoRPd Register
struct FDRAMC_DRKRTORPD {
	unsigned int DRkRtoRPd:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // WRDataLat Register
struct FDRAMC_WRDATALAT {
	unsigned int WRDataLat:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // WRDataEnLat Register
struct FDRAMC_WRDATAENLAT {
	unsigned int WRDataEnLat_p0:4;		// [3:0]
	unsigned int reserved1:4;		// [7:4]
	unsigned int WRDataEnLat_p1:4;		// [11:8]
	unsigned int reserved2:4;		// [15:12]
	unsigned int WRDataEnLat_p2:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int WRDataEnLat_p3:4;		// [27:24]
	unsigned int reserved4:4;		// [31:28]
};
 // RDDataLat Register
struct FDRAMC_RDDATALAT {
	unsigned int RDDataLat:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // CTRLUPD Register
struct FDRAMC_CTRLUPD {
	unsigned int CTRLUPD:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // RDtoCTRLUPDPd Register
struct FDRAMC_RDTOCTRLUPDPD {
	unsigned int RDtoCTRLUPDPd:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // CmdTiming Register
struct FDRAMC_CMDTIMING {
	unsigned int CmdTiming:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // RDTiming Register
struct FDRAMC_RDTIMING {
	unsigned int RDTiming:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // ODTMode_CS0 Register
struct FDRAMC_ODTMODE_CS0 {
	unsigned int ODTMode_CS0:2;		// [1:0]
	unsigned int reserved1:14;		// [15:2]
	unsigned int ODTMultiRankWR_CS0:2;		// [17:16]
	unsigned int reserved2:6;		// [23:18]
	unsigned int ODTMultiRankRD_CS0:2;		// [25:24]
	unsigned int reserved3:6;		// [31:26]
};
 // ODTMode_CS1 Register
struct FDRAMC_ODTMODE_CS1 {
	unsigned int ODTMode_CS1:2;		// [1:0]
	unsigned int reserved1:14;		// [15:2]
	unsigned int ODTMultiRankWR_CS1:2;		// [17:16]
	unsigned int reserved2:6;		// [23:18]
	unsigned int ODTMultiRankRD_CS1:2;		// [25:24]
	unsigned int reserved3:6;		// [31:26]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _FDRAMC_REG_STRUCT_L_H */
