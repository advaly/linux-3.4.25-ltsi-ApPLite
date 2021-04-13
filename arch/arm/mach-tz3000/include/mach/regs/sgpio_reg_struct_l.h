/*
 * arch/arm/mach-tz3000/include/mach/regs/sgpio_reg_struct_l.h
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

#ifndef _SGPIO_REG_STRUCT_L_H
#define _SGPIO_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // GP_CR Register
struct SGPIO_GP_CR {
	unsigned int CR:32;		// [31:0]
};
 // GP_DR Register
struct SGPIO_GP_DR {
	unsigned int DR:32;		// [31:0]
};
 // GP_ODS Register
struct SGPIO_GP_ODS {
	unsigned int ODS:32;		// [31:0]
};
 // GP_ODC Register
struct SGPIO_GP_ODC {
	unsigned int ODC:32;		// [31:0]
};
 // GP_INTS Register
struct SGPIO_GP_INTS {
	unsigned int INT:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // GP_INTC0 Register
struct SGPIO_GP_INTC0 {
	unsigned int INTC0:32;		// [31:0]
};
 // GP_INTC1 Register
struct SGPIO_GP_INTC1 {
	unsigned int INTC1:32;		// [31:0]
};
 // GP_INTM0 Register
struct SGPIO_GP_INTM0 {
	unsigned int INTM0:32;		// [31:0]
};
 // GP_INTM1 Register
struct SGPIO_GP_INTM1 {
	unsigned int INTM1:32;		// [31:0]
};
 // GP_INTM2 Register
struct SGPIO_GP_INTM2 {
	unsigned int INTM2:32;		// [31:0]
};
 // GP_INTM3 Register
struct SGPIO_GP_INTM3 {
	unsigned int INTM3:32;		// [31:0]
};
 // GP_INTM4 Register
struct SGPIO_GP_INTM4 {
	unsigned int INTM4:32;		// [31:0]
};
 // GP_SMP Register
struct SGPIO_GP_SMP {
	unsigned int SMP_INTERVAL:16;		// [15:0]
	unsigned int SMP_POINT_NUMBER:3;		// [18:16]
	unsigned int reserved:13;		// [31:19]
};
 // GP_ODR Register
struct SGPIO_GP_ODR {
	unsigned int ODR:32;		// [31:0]
};
 // GP_IR0 Register
struct SGPIO_GP_IR0 {
	unsigned int STAT:32;		// [31:0]
};
 // GP_IR1 Register
struct SGPIO_GP_IR1 {
	unsigned int STAT:32;		// [31:0]
};
 // GP_IR2 Register
struct SGPIO_GP_IR2 {
	unsigned int STAT:32;		// [31:0]
};
 // GP_IR3 Register
struct SGPIO_GP_IR3 {
	unsigned int STAT:32;		// [31:0]
};
 // GP_IR4 Register
struct SGPIO_GP_IR4 {
	unsigned int STAT:32;		// [31:0]
};
 // GP_PUDEN Register
struct SGPIO_GP_PUDEN {
	unsigned int PUDEN:32;		// [31:0]
};
 // GP_PUDSEL Register
struct SGPIO_GP_PUDSEL {
	unsigned int PUDSEL:32;		// [31:0]
};
 // GP_INPEN Register
struct SGPIO_GP_INPEN {
	unsigned int INPEN:32;		// [31:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SGPIO_REG_STRUCT_L_H */
