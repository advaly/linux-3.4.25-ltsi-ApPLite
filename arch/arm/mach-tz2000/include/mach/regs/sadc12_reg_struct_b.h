/*
 * arch/arm/mach-tz2000/include/mach/regs/sadc12_reg_struct_b.h
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

#ifndef _SADC12_REG_STRUCT_B_H
#define _SADC12_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // SAD00CH Register
struct SADC12_SAD00CH {
	unsigned int reserved:20;		// [31:12]
	unsigned int SAD00CH:12;		// [11:0]
};
 // SAD01CH Register
struct SADC12_SAD01CH {
	unsigned int reserved:20;		// [31:12]
	unsigned int SAD01CH:12;		// [11:0]
};
 // SAD02CH Register
struct SADC12_SAD02CH {
	unsigned int reserved:20;		// [31:12]
	unsigned int SAD02CH:12;		// [11:0]
};
 // SAD03CH Register
struct SADC12_SAD03CH {
	unsigned int reserved:20;		// [31:12]
	unsigned int SAD03CH:12;		// [11:0]
};
 // SADCTRL Register
struct SADC12_SADCTRL {
	unsigned int reserved:29;		// [31:3]
	unsigned int Valid:1;		// [2]
	unsigned int STB:1;		// [1]
	unsigned int RST:1;		// [0]
};
 // SADDEBUG Register
struct SADC12_SADDEBUG {
	unsigned int reserved:25;		// [31:7]
	unsigned int SEQERR2:1;		// [6]
	unsigned int SEQERR1:1;		// [5]
	unsigned int SEQERR0:1;		// [4]
	unsigned int reserved2:1;		// [3]
	unsigned int STATUS:3;		// [2:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SADC12_REG_STRUCT_B_H */
