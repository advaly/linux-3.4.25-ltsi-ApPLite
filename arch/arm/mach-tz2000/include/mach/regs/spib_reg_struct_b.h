/*
 * arch/arm/mach-tz2000/include/mach/regs/spib_reg_struct_b.h
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

#ifndef _SPIB_REG_STRUCT_B_H
#define _SPIB_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // SPIB0_FlshMemMap0 Register
struct SPIB_SPIB0_FLSHMEMMAP0 {
	unsigned int FBA:16;		// [31:16]
	unsigned int reserved:10;		// [15:6]
	unsigned int FDEN:4;		// [5:2]
	unsigned int reserved2:1;		// [1]
	unsigned int RE:1;		// [0]
};
 // SPIB0_FlshMemMap1 Register
struct SPIB_SPIB0_FLSHMEMMAP1 {
	unsigned int FBA:16;		// [31:16]
	unsigned int reserved:10;		// [15:6]
	unsigned int FDEN:4;		// [5:2]
	unsigned int reserved2:1;		// [1]
	unsigned int RE:1;		// [0]
};
 // SPIB0_DirAccCtrl0 Register
struct SPIB_SPIB0_DIRACCCTRL0 {
	unsigned int reserved:11;		// [31:21]
	unsigned int SPR:5;		// [20:16]
	unsigned int SCSD:8;		// [15:8]
	unsigned int reserved2:1;		// [7]
	unsigned int PollWIP:1;		// [6]
	unsigned int SDCE:4;		// [5:2]
	unsigned int SMOD:2;		// [1:0]
};
 // SPIB0_DirAccCtrl1 Register
struct SPIB_SPIB0_DIRACCCTRL1 {
	unsigned int reserved:11;		// [31:21]
	unsigned int SPR:5;		// [20:16]
	unsigned int SCSD:8;		// [15:8]
	unsigned int reserved2:1;		// [7]
	unsigned int PollWIP:1;		// [6]
	unsigned int SDCE:4;		// [5:2]
	unsigned int SMOD:2;		// [1:0]
};
 // SPIB0_DirRdCtrl0 Register
struct SPIB_SPIB0_DIRRDCTRL0 {
	unsigned int SpiCmdOp:8;		// [31:24]
	unsigned int reserved:8;		// [23:16]
	unsigned int SpiDmyByteCnt:4;		// [15:12]
	unsigned int SpiAddrByteCnt:1;		// [11]
	unsigned int reserved2:3;		// [10:8]
	unsigned int SpiDatIOCtrl:2;		// [7:6]
	unsigned int SpiDmyIOCtrl:2;		// [5:4]
	unsigned int SpiAdrIOCtrl:2;		// [3:2]
	unsigned int SpiCmdIOCtrl:2;		// [1:0]
};
 // SPIB0_DirRdCtrl1 Register
struct SPIB_SPIB0_DIRRDCTRL1 {
	unsigned int SpiCmdOp:8;		// [31:24]
	unsigned int reserved:8;		// [23:16]
	unsigned int SpiDmyByteCnt:4;		// [15:12]
	unsigned int SpiAddrByteCnt:1;		// [11]
	unsigned int reserved2:3;		// [10:8]
	unsigned int SpiDatIOCtrl:2;		// [7:6]
	unsigned int SpiDmyIOCtrl:2;		// [5:4]
	unsigned int SpiAdrIOCtrl:2;		// [3:2]
	unsigned int SpiCmdIOCtrl:2;		// [1:0]
};
 // SPIB0_PrgAccCtrl0 Register
struct SPIB_SPIB0_PRGACCCTRL0 {
	unsigned int reserved:11;		// [31:21]
	unsigned int SPR:5;		// [20:16]
	unsigned int SCSD:8;		// [15:8]
	unsigned int reserved2:2;		// [7:6]
	unsigned int SDCE:4;		// [5:2]
	unsigned int SMOD:2;		// [1:0]
};
 // SPIB0_PrgAccCtrl1 Register
struct SPIB_SPIB0_PRGACCCTRL1 {
	unsigned int SecBufDatByteCnt:8;		// [31:24]
	unsigned int reserved:5;		// [23:19]
	unsigned int PriBufDatByteCnt:3;		// [18:16]
	unsigned int reserved2:10;		// [15:6]
	unsigned int SecBufEn:1;		// [5]
	unsigned int PriBufEn:1;		// [4]
	unsigned int reserved3:2;		// [3:2]
	unsigned int SpiCsNum:1;		// [1]
	unsigned int SpiCycGo:1;		// [0]
};
 // SPIB0_PrgAccIntEn Register
struct SPIB_SPIB0_PRGACCINTEN {
	unsigned int reserved:31;		// [31:1]
	unsigned int SpiIntEn:1;		// [0]
};
 // SPIB0_PrgAccStat Register
struct SPIB_SPIB0_PRGACCSTAT {
	unsigned int reserved:30;		// [31:2]
	unsigned int SpiCycInPrgrs:1;		// [1]
	unsigned int SpiCycDone:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SPIB_REG_STRUCT_B_H */
