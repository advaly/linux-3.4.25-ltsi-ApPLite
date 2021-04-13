/*
 * arch/arm/mach-tz2000/include/mach/regs/i2sc_reg_struct_l.h
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

#ifndef _I2SC_REG_STRUCT_L_H
#define _I2SC_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // START Register
struct I2SC_START {
	unsigned int Start:1;		// [0]
	unsigned int reserved2:7;		// [7:1]
	unsigned int MCKStart:1;		// [8]
	unsigned int reserved:23;		// [31:9]
};
 // BUSY Register
struct I2SC_BUSY {
	unsigned int Busy:1;		// [0]
	unsigned int SeriBusy:1;		// [1]
	unsigned int reserved2:6;		// [7:2]
	unsigned int MCKBusy:1;		// [8]
	unsigned int reserved:23;		// [31:9]
};
 // AUDIOSET Register
struct I2SC_AUDIOSET {
	unsigned int WordLen:5;		// [4:0]
	unsigned int reserved3:3;		// [7:5]
	unsigned int SCLKTOWS:1;		// [8]
	unsigned int reserved2:2;		// [10:9]
	unsigned int Edge:1;		// [11]
	unsigned int MtoWS:2;		// [13:12]
	unsigned int reserved:18;		// [31:14]
};
 // INTSTAT Register
struct I2SC_INTSTAT {
	unsigned int Int:1;		// [0]
	unsigned int ORErr:1;		// [1]
	unsigned int URErr:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // INTMASK Register
struct I2SC_INTMASK {
	unsigned int Mask:1;		// [0]
	unsigned int ORMask:1;		// [1]
	unsigned int URMask:1;		// [2]
	unsigned int reserved2:13;		// [15:3]
	unsigned int DMACMSK:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // INTCLR Register
struct I2SC_INTCLR {
	unsigned int IntClr:1;		// [0]
	unsigned int ORClr:1;		// [1]
	unsigned int URClr:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // INTSET Register
struct I2SC_INTSET {
	unsigned int IntSet:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // MUTE Register
struct I2SC_MUTE {
	unsigned int MuteN:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // EPTR Register
struct I2SC_EPTR {
	unsigned int ErrPointer:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // MODESET Register
struct I2SC_MODESET {
	unsigned int WS:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int IESEL:2;		// [5:4]
	unsigned int reserved:26;		// [31:6]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _I2SC_REG_STRUCT_L_H */
