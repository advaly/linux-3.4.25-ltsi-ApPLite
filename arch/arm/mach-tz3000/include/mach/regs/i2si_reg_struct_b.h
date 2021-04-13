/*
 * arch/arm/mach-tz3000/include/mach/regs/i2si_reg_struct_b.h
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

#ifndef _I2SI_REG_STRUCT_B_H
#define _I2SI_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // I2SI0_START Register
struct I2SI_I2SI0_START {
	unsigned int reserved:23;		// [31:9]
	unsigned int MCKStart:1;		// [8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int Start:1;		// [0]
};
 // I2SI0_BUSY Register
struct I2SI_I2SI0_BUSY {
	unsigned int reserved:23;		// [31:9]
	unsigned int MCKBusy:1;		// [8]
	unsigned int reserved2:6;		// [7:2]
	unsigned int SeriBusy:1;		// [1]
	unsigned int Busy:1;		// [0]
};
 // I2SI0_AUDIOSET Register
struct I2SI_I2SI0_AUDIOSET {
	unsigned int reserved:18;		// [31:14]
	unsigned int MtoWS:2;		// [13:12]
	unsigned int Edge:1;		// [11]
	unsigned int reserved2:2;		// [10:9]
	unsigned int SCLKTOWS:1;		// [8]
	unsigned int reserved3:2;		// [7:6]
	unsigned int WordLen:6;		// [5:0]
};
 // I2S0_INTSTAT Register
struct I2SI_I2S0_INTSTAT {
	unsigned int reserved:29;		// [31:3]
	unsigned int URErr:1;		// [2]
	unsigned int ORErr:1;		// [1]
	unsigned int Int:1;		// [0]
};
 // I2SI0_INTMASK Register
struct I2SI_I2SI0_INTMASK {
	unsigned int reserved:15;		// [31:17]
	unsigned int DMACMSK:1;		// [16]
	unsigned int reserved2:13;		// [15:3]
	unsigned int URMask:1;		// [2]
	unsigned int ORMask:1;		// [1]
	unsigned int Mask:1;		// [0]
};
 // I2SI0_INTCLR Register
struct I2SI_I2SI0_INTCLR {
	unsigned int reserved:29;		// [31:3]
	unsigned int URClr:1;		// [2]
	unsigned int ORClr:1;		// [1]
	unsigned int IntClr:1;		// [0]
};
 // I2SI0_INTSET Register
struct I2SI_I2SI0_INTSET {
	unsigned int reserved:30;		// [31:2]
	unsigned int IntSet:2;		// [1:0]
};
 // I2SI0_MUTE Register
struct I2SI_I2SI0_MUTE {
	unsigned int reserved:31;		// [31:1]
	unsigned int MuteN:1;		// [0]
};
 // I2SI0_EPTR Register
struct I2SI_I2SI0_EPTR {
	unsigned int reserved:24;		// [31:8]
	unsigned int ErrPointer:8;		// [7:0]
};
 // I2SI0_MODESET Register
struct I2SI_I2SI0_MODESET {
	unsigned int reserved:26;		// [31:6]
	unsigned int IESEL:2;		// [5:4]
	unsigned int reserved2:1;		// [3]
	unsigned int WS:3;		// [2:0]
};
 // I2SI0_LMEM Register
struct I2SI_I2SI0_LMEM {
	unsigned int SDAT:32;		// [31:0]
};
 // I2SI1_START Register
struct I2SI_I2SI1_START {
	unsigned int reserved:23;		// [31:9]
	unsigned int MCKStart:1;		// [8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int Start:1;		// [0]
};
 // I2SI1_BUSY Register
struct I2SI_I2SI1_BUSY {
	unsigned int reserved:23;		// [31:9]
	unsigned int MCKBusy:1;		// [8]
	unsigned int reserved2:6;		// [7:2]
	unsigned int SeriBusy:1;		// [1]
	unsigned int Busy:1;		// [0]
};
 // I2SI1_AUDIOSET Register
struct I2SI_I2SI1_AUDIOSET {
	unsigned int reserved:18;		// [31:14]
	unsigned int MtoWS:2;		// [13:12]
	unsigned int Edge:1;		// [11]
	unsigned int reserved2:2;		// [10:9]
	unsigned int SCLKTOWS:1;		// [8]
	unsigned int reserved3:2;		// [7:6]
	unsigned int WordLen:6;		// [5:0]
};
 // I2SI1_INTSTAT Register
struct I2SI_I2SI1_INTSTAT {
	unsigned int reserved:29;		// [31:3]
	unsigned int URErr:1;		// [2]
	unsigned int ORErr:1;		// [1]
	unsigned int Int:1;		// [0]
};
 // I2SI1_INTMASK Register
struct I2SI_I2SI1_INTMASK {
	unsigned int reserved:15;		// [31:17]
	unsigned int DMACMSK:1;		// [16]
	unsigned int reserved2:13;		// [15:3]
	unsigned int URMask:1;		// [2]
	unsigned int ORMask:1;		// [1]
	unsigned int Mask:1;		// [0]
};
 // I2SI1_INTCLR Register
struct I2SI_I2SI1_INTCLR {
	unsigned int reserved:29;		// [31:3]
	unsigned int URClr:1;		// [2]
	unsigned int ORClr:1;		// [1]
	unsigned int IntClr:1;		// [0]
};
 // I2SI1_INTSET Register
struct I2SI_I2SI1_INTSET {
	unsigned int reserved:30;		// [31:2]
	unsigned int IntSet:2;		// [1:0]
};
 // I2SI1_MUTE Register
struct I2SI_I2SI1_MUTE {
	unsigned int reserved:31;		// [31:1]
	unsigned int MuteN:1;		// [0]
};
 // I2SI1_EPTR Register
struct I2SI_I2SI1_EPTR {
	unsigned int reserved:24;		// [31:8]
	unsigned int ErrPointer:8;		// [7:0]
};
 // I2SI1_MODESET Register
struct I2SI_I2SI1_MODESET {
	unsigned int reserved:26;		// [31:6]
	unsigned int IESEL:2;		// [5:4]
	unsigned int reserved2:1;		// [3]
	unsigned int WS:3;		// [2:0]
};
 // I2SI1_LMEM Register
struct I2SI_I2SI1_LMEM {
	unsigned int SDAT:32;		// [31:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _I2SI_REG_STRUCT_B_H */
