/*
 * arch/arm/mach-tz2000/include/mach/regs/dtree_reg_struct_b.h
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

#ifndef _DTREE_REG_STRUCT_B_H
#define _DTREE_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // REV1 Register
struct DTREE_REV1 {
	unsigned int reserved:16;		// [31:16]
	unsigned int PCODE:16;		// [15:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DTREE_REG_STRUCT_B_H */
