/*
 * arch/arm/mach-tz3000/include/mach/regs/scomm_reg_struct_b.h
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

#ifndef _SCOMM_REG_STRUCT_B_H
#define _SCOMM_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // TAS_NONSEC Register
struct SCOMM_TAS_NONSEC {
	unsigned int reserved:31;		// [31:1]
	unsigned int TAS:1;		// [0]
};
 // INT_NONSEC Register
struct SCOMM_INT_NONSEC {
	unsigned int reserved:31;		// [31:1]
	unsigned int INT:1;		// [0]
};
 // TAS_SECURE Register
struct SCOMM_TAS_SECURE {
	unsigned int reserved:31;		// [31:1]
	unsigned int TAS:1;		// [0]
};
 // INT_SECURE Register
struct SCOMM_INT_SECURE {
	unsigned int reserved:31;		// [31:1]
	unsigned int INT:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SCOMM_REG_STRUCT_B_H */
