/*
 * arch/arm/mach-tz3000/include/mach/regs/fdramc_reg_struct_b.h
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

#ifndef _FDRAMC_REG_STRUCT_B_H
#define _FDRAMC_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // DRAMType Register
struct FDRAMC_DRAMTYPE {
	unsigned int reserved:24;		// [31:8]
	unsigned int DRAMType:8;		// [7:0]
};
 // AddressConfig_CS Register
struct FDRAMC_ADDRESSCONFIG_CS {
	unsigned int reserved2:22;		// [31:10]
	unsigned int Chip_Select_Width:2;		// [9:8]
	unsigned int reserved1:2;		// [7:6]
	unsigned int Chip_Select_Bit_Location:6;		// [5:0]
};
 // AddressConfig_Row Register
struct FDRAMC_ADDRESSCONFIG_ROW {
	unsigned int reserved2:19;		// [31:13]
	unsigned int Row_Address_Width:5;		// [12:8]
	unsigned int reserved1:3;		// [7:5]
	unsigned int Row_Bit_Location:5;		// [4:0]
};
 // AddressConfig_Bank Register
struct FDRAMC_ADDRESSCONFIG_BANK {
	unsigned int reserved2:22;		// [31:10]
	unsigned int Bank_Width:2;		// [9:8]
	unsigned int reserved1:3;		// [7:5]
	unsigned int Bank_Bit_Location:5;		// [4:0]
};
 // AddressConfig_Col Register
struct FDRAMC_ADDRESSCONFIG_COL {
	unsigned int reserved4:4;		// [31:28]
	unsigned int Column_Address_Width_1:4;		// [27:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int Column_Bit_Location_1:5;		// [20:16]
	unsigned int reserved2:4;		// [15:12]
	unsigned int Column_Address_Width_0:4;		// [11:8]
	unsigned int reserved1:3;		// [7:5]
	unsigned int Column_Bit_Location_0:5;		// [4:0]
};
 // DataConfig Register
struct FDRAMC_DATACONFIG {
	unsigned int reserved:31;		// [31:1]
	unsigned int DataConfig:1;		// [0]
};
 // BstLenLog Register
struct FDRAMC_BSTLENLOG {
	unsigned int reserved:30;		// [31:2]
	unsigned int BstLenLog:2;		// [1:0]
};
 // MRRBstLenLog Register
struct FDRAMC_MRRBSTLENLOG {
	unsigned int reserved:30;		// [31:2]
	unsigned int MRRBstLenLog:2;		// [1:0]
};
 // BWHalfMode Register
struct FDRAMC_BWHALFMODE {
	unsigned int reserved:31;		// [31:1]
	unsigned int BWHalfMode:1;		// [0]
};
 // APwrDWtPd Register
struct FDRAMC_APWRDWTPD {
	unsigned int reserved:20;		// [31:12]
	unsigned int APwrDWtPd:12;		// [11:0]
};
 // RftoRfMax Register
struct FDRAMC_RFTORFMAX {
	unsigned int reserved:18;		// [31:14]
	unsigned int RftoRfMax:14;		// [13:0]
};
 // PAlltoANYPd Register
struct FDRAMC_PALLTOANYPD {
	unsigned int reserved2:1;		// [31]
	unsigned int reserved:28;		// [30:3]
	unsigned int PAlltoANYPd:3;		// [2:0]
};
 // InitMtoMPd Register
struct FDRAMC_INITMTOMPD {
	unsigned int reserved:29;		// [31:3]
	unsigned int InitMtoMPd:3;		// [2:0]
};
 // ReftoANYPd Register
struct FDRAMC_REFTOANYPD {
	unsigned int reserved:23;		// [31:9]
	unsigned int ReftoANYPd:9;		// [8:0]
};
 // BkAtoRWPd Register
struct FDRAMC_BKATORWPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int BkAtoRWPd:5;		// [4:0]
};
 // AtoAPd Register
struct FDRAMC_ATOAPD {
	unsigned int reserved:28;		// [31:4]
	unsigned int AtoAPd:4;		// [3:0]
};
 // BkRtoPPd Register
struct FDRAMC_BKRTOPPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int BkRtoPPd:5;		// [4:0]
};
 // BkWtoPPd Register
struct FDRAMC_BKWTOPPD {
	unsigned int reserved:26;		// [31:6]
	unsigned int BkWtoPPd:6;		// [5:0]
};
 // BkPtoANYPd Register
struct FDRAMC_BKPTOANYPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int BkPtoANYPd:5;		// [4:0]
};
 // RtoWPd Register
struct FDRAMC_RTOWPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int RtoWPd:5;		// [4:0]
};
 // InitCkeUptoANYPd Register
struct FDRAMC_INITCKEUPTOANYPD {
	unsigned int reserved:14;		// [31:18]
	unsigned int InitCkeUptoANYPd:18;		// [17:0]
};
 // BkAtoAPd Register
struct FDRAMC_BKATOAPD {
	unsigned int reserved:26;		// [31:6]
	unsigned int BkAtoAPd:6;		// [5:0]
};
 // InitOITPd Register
struct FDRAMC_INITOITPD {
	unsigned int reserved:29;		// [31:3]
	unsigned int InitOITPd:3;		// [2:0]
};
 // BkAtoPPd Register
struct FDRAMC_BKATOPPD {
	unsigned int reserved:26;		// [31:6]
	unsigned int BkAtoPPd:6;		// [5:0]
};
 // BkRAtoANYPd Register
struct FDRAMC_BKRATOANYPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int BkRAtoANYPd:5;		// [4:0]
};
 // BkWAtoANYPd Register
struct FDRAMC_BKWATOANYPD {
	unsigned int reserved:26;		// [31:6]
	unsigned int BkWAtoANYPd:6;		// [5:0]
};
 // TAWPd Register
struct FDRAMC_TAWPD {
	unsigned int reserved:26;		// [31:6]
	unsigned int TAWPd:6;		// [5:0]
};
 // FAWPd Register
struct FDRAMC_FAWPD {
	unsigned int reserved2:1;		// [31]
	unsigned int reserved:25;		// [30:6]
	unsigned int FAWPd:6;		// [5:0]
};
 // WtoRPd Register
struct FDRAMC_WTORPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int WtoRPd:5;		// [4:0]
};
 // InitDLLKPd Register
struct FDRAMC_INITDLLKPD {
	unsigned int reserved:22;		// [31:10]
	unsigned int InitDLLKPd:10;		// [9:0]
};
 // SrxtoANYPd Register
struct FDRAMC_SRXTOANYPD {
	unsigned int reserved:23;		// [31:9]
	unsigned int SrxtoANYPd:9;		// [8:0]
};
 // SrxtoRWPd Register
struct FDRAMC_SRXTORWPD {
	unsigned int reserved:22;		// [31:10]
	unsigned int SrxtoRWPd:10;		// [9:0]
};
 // PdxtoANYPd Register
struct FDRAMC_PDXTOANYPD {
	unsigned int reserved:29;		// [31:3]
	unsigned int PdxtoANYPd:3;		// [2:0]
};
 // PdxtoRWPd Register
struct FDRAMC_PDXTORWPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int PdxtoRWPd:5;		// [4:0]
};
 // MtoANYPd Register
struct FDRAMC_MTOANYPD {
	unsigned int reserved:28;		// [31:4]
	unsigned int MtoANYPd:4;		// [3:0]
};
 // ZQCLtoANYPd Register
struct FDRAMC_ZQCLTOANYPD {
	unsigned int reserved:23;		// [31:9]
	unsigned int ZQCLtoANYPd:9;		// [8:0]
};
 // InitZQCLtoANYPd Register
struct FDRAMC_INITZQCLTOANYPD {
	unsigned int reserved:22;		// [31:10]
	unsigned int InitZQCLtoANYPd:10;		// [9:0]
};
 // ZQCStoANYPd Register
struct FDRAMC_ZQCSTOANYPD {
	unsigned int reserved:25;		// [31:7]
	unsigned int ZQCStoANYPd:7;		// [6:0]
};
 // RtoPWDPd Register
struct FDRAMC_RTOPWDPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int RtoPWDPd:5;		// [4:0]
};
 // PdxtoPWDPd Register
struct FDRAMC_PDXTOPWDPD {
	unsigned int reserved:27;		// [31:5]
	unsigned int PdxtoPWDPd:5;		// [4:0]
};
 // SrxtoPWDPd Register
struct FDRAMC_SRXTOPWDPD {
	unsigned int reserved:22;		// [31:10]
	unsigned int SrxtoPWDPd:10;		// [9:0]
};
 // SretoSrxPd Register
struct FDRAMC_SRETOSRXPD {
	unsigned int reserved:28;		// [31:4]
	unsigned int SretoSrxPd:4;		// [3:0]
};
 // PdetoPdxPd Register
struct FDRAMC_PDETOPDXPD {
	unsigned int reserved:29;		// [31:3]
	unsigned int PdetoPdxPd:3;		// [2:0]
};
 // DRkWtoWPd Register
struct FDRAMC_DRKWTOWPD {
	unsigned int reserved:28;		// [31:4]
	unsigned int DRkWtoWPd:4;		// [3:0]
};
 // DRkRtoRPd Register
struct FDRAMC_DRKRTORPD {
	unsigned int reserved:28;		// [31:4]
	unsigned int DRkRtoRPd:4;		// [3:0]
};
 // WRDataLat Register
struct FDRAMC_WRDATALAT {
	unsigned int reserved:28;		// [31:4]
	unsigned int WRDataLat:4;		// [3:0]
};
 // WRDataEnLat Register
struct FDRAMC_WRDATAENLAT {
	unsigned int reserved4:4;		// [31:28]
	unsigned int WRDataEnLat_p3:4;		// [27:24]
	unsigned int reserved3:4;		// [23:20]
	unsigned int WRDataEnLat_p2:4;		// [19:16]
	unsigned int reserved2:4;		// [15:12]
	unsigned int WRDataEnLat_p1:4;		// [11:8]
	unsigned int reserved1:4;		// [7:4]
	unsigned int WRDataEnLat_p0:4;		// [3:0]
};
 // RDDataLat Register
struct FDRAMC_RDDATALAT {
	unsigned int reserved:27;		// [31:5]
	unsigned int RDDataLat:5;		// [4:0]
};
 // CTRLUPD Register
struct FDRAMC_CTRLUPD {
	unsigned int reserved:16;		// [31:16]
	unsigned int CTRLUPD:16;		// [15:0]
};
 // RDtoCTRLUPDPd Register
struct FDRAMC_RDTOCTRLUPDPD {
	unsigned int reserved:26;		// [31:6]
	unsigned int RDtoCTRLUPDPd:6;		// [5:0]
};
 // CmdTiming Register
struct FDRAMC_CMDTIMING {
	unsigned int reserved:30;		// [31:2]
	unsigned int CmdTiming:2;		// [1:0]
};
 // RDTiming Register
struct FDRAMC_RDTIMING {
	unsigned int reserved:31;		// [31:1]
	unsigned int RDTiming:1;		// [0]
};
 // ODTMode_CS0 Register
struct FDRAMC_ODTMODE_CS0 {
	unsigned int reserved3:6;		// [31:26]
	unsigned int ODTMultiRankRD_CS0:2;		// [25:24]
	unsigned int reserved2:6;		// [23:18]
	unsigned int ODTMultiRankWR_CS0:2;		// [17:16]
	unsigned int reserved1:14;		// [15:2]
	unsigned int ODTMode_CS0:2;		// [1:0]
};
 // ODTMode_CS1 Register
struct FDRAMC_ODTMODE_CS1 {
	unsigned int reserved3:6;		// [31:26]
	unsigned int ODTMultiRankRD_CS1:2;		// [25:24]
	unsigned int reserved2:6;		// [23:18]
	unsigned int ODTMultiRankWR_CS1:2;		// [17:16]
	unsigned int reserved1:14;		// [15:2]
	unsigned int ODTMode_CS1:2;		// [1:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _FDRAMC_REG_STRUCT_B_H */
