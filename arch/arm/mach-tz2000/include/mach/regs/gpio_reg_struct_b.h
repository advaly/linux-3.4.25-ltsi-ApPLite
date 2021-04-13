/*
 * arch/arm/mach-tz2000/include/mach/regs/gpio_reg_struct_b.h
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

#ifndef _GPIO_REG_STRUCT_B_H
#define _GPIO_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // GP0_CR Register
struct GPIO_GP0_CR {
	unsigned int CR:32;		// [31:0]
};
 // GP0_DR Register
struct GPIO_GP0_DR {
	unsigned int DR:32;		// [31:0]
};
 // GP0_ODS Register
struct GPIO_GP0_ODS {
	unsigned int ODS:32;		// [31:0]
};
 // GP0_ODC Register
struct GPIO_GP0_ODC {
	unsigned int ODC:32;		// [31:0]
};
 // GP_INTS Register
struct GPIO_GP_INTS {
	unsigned int reserved:27;		// [31:5]
	unsigned int INT:5;		// [4:0]
};
 // GP0_INTC0 Register
struct GPIO_GP0_INTC0 {
	unsigned int INTC0:32;		// [31:0]
};
 // GP0_INTC1 Register
struct GPIO_GP0_INTC1 {
	unsigned int INTC1:32;		// [31:0]
};
 // GP0_INTM0 Register
struct GPIO_GP0_INTM0 {
	unsigned int INTM0:32;		// [31:0]
};
 // GP0_SMP Register
struct GPIO_GP0_SMP {
	unsigned int reserved:13;		// [31:19]
	unsigned int smp_point_number:3;		// [18:16]
	unsigned int smp_interval:16;		// [15:0]
};
 // GP0_ODR Register
struct GPIO_GP0_ODR {
	unsigned int ODR:32;		// [31:0]
};
 // GP0_IR0 Register
struct GPIO_GP0_IR0 {
	unsigned int STAT:32;		// [31:0]
};
 // GP0_PUDEN Register
struct GPIO_GP0_PUDEN {
	unsigned int PUDEN:32;		// [31:0]
};
 // GP0_PUDSEL Register
struct GPIO_GP0_PUDSEL {
	unsigned int PUDSEL:32;		// [31:0]
};
 // GP0_INPEN Register
struct GPIO_GP0_INPEN {
	unsigned int INPEN:32;		// [31:0]
};
 // GP1_CR Register
struct GPIO_GP1_CR {
	unsigned int CR:32;		// [31:0]
};
 // GP1_DR Register
struct GPIO_GP1_DR {
	unsigned int DR:32;		// [31:0]
};
 // GP1_ODS Register
struct GPIO_GP1_ODS {
	unsigned int ODS:32;		// [31:0]
};
 // GP1_ODC Register
struct GPIO_GP1_ODC {
	unsigned int ODC:32;		// [31:0]
};
 // GP1_INTS Register
struct GPIO_GP1_INTS {
	unsigned int reserved:27;		// [31:5]
	unsigned int INT:5;		// [4:0]
};
 // GP1_INTC0 Register
struct GPIO_GP1_INTC0 {
	unsigned int INTC0:32;		// [31:0]
};
 // GP1_INTC1 Register
struct GPIO_GP1_INTC1 {
	unsigned int INTC1:32;		// [31:0]
};
 // GP1_INTM0 Register
struct GPIO_GP1_INTM0 {
	unsigned int INTM0:32;		// [31:0]
};
 // GP1_SMP Register
struct GPIO_GP1_SMP {
	unsigned int reserved:13;		// [31:19]
	unsigned int smp_point_number:3;		// [18:16]
	unsigned int smp_interval:16;		// [15:0]
};
 // GP1_ODR Register
struct GPIO_GP1_ODR {
	unsigned int ODR:32;		// [31:0]
};
 // GP1_IR0 Register
struct GPIO_GP1_IR0 {
	unsigned int STAT:32;		// [31:0]
};
 // GP1_PUDEN Register
struct GPIO_GP1_PUDEN {
	unsigned int PUDEN:32;		// [31:0]
};
 // GP1_PUDSEL Register
struct GPIO_GP1_PUDSEL {
	unsigned int PUDSEL:32;		// [31:0]
};
 // GP1_INPEN Register
struct GPIO_GP1_INPEN {
	unsigned int INPEN:32;		// [31:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GPIO_REG_STRUCT_B_H */
