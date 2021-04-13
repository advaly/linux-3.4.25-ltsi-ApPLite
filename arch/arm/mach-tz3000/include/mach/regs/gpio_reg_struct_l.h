/*
 * arch/arm/mach-tz3000/include/mach/regs/gpio_reg_struct_l.h
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

#ifndef _GPIO_REG_STRUCT_L_H
#define _GPIO_REG_STRUCT_L_H

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
 // GP0_INTS Register
struct GPIO_GP0_INTS {
	unsigned int INT:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
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
 // GP0_INTM1 Register
struct GPIO_GP0_INTM1 {
	unsigned int INTM1:32;		// [31:0]
};
 // GP0_INTM2 Register
struct GPIO_GP0_INTM2 {
	unsigned int INTM2:32;		// [31:0]
};
 // GP0_INTM3 Register
struct GPIO_GP0_INTM3 {
	unsigned int INTM3:32;		// [31:0]
};
 // GP0_INTM4 Register
struct GPIO_GP0_INTM4 {
	unsigned int INTM4:32;		// [31:0]
};
 // GP0_SMP Register
struct GPIO_GP0_SMP {
	unsigned int SMP_INTERVAL:16;		// [15:0]
	unsigned int SMP_POINT_NUMBER:3;		// [18:16]
	unsigned int reserved:13;		// [31:19]
};
 // GP0_ODR Register
struct GPIO_GP0_ODR {
	unsigned int ODR:32;		// [31:0]
};
 // GP0_IR0 Register
struct GPIO_GP0_IR0 {
	unsigned int STAT:32;		// [31:0]
};
 // GP0_IR1 Register
struct GPIO_GP0_IR1 {
	unsigned int STAT:32;		// [31:0]
};
 // GP0_IR2 Register
struct GPIO_GP0_IR2 {
	unsigned int STAT:32;		// [31:0]
};
 // GP0_IR3 Register
struct GPIO_GP0_IR3 {
	unsigned int STAT:32;		// [31:0]
};
 // GP0_IR4 Register
struct GPIO_GP0_IR4 {
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
	unsigned int INT:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
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
 // GP1_INTM1 Register
struct GPIO_GP1_INTM1 {
	unsigned int INTM1:32;		// [31:0]
};
 // GP1_INTM2 Register
struct GPIO_GP1_INTM2 {
	unsigned int INTM2:32;		// [31:0]
};
 // GP1_INTM3 Register
struct GPIO_GP1_INTM3 {
	unsigned int INTM3:32;		// [31:0]
};
 // GP1_INTM4 Register
struct GPIO_GP1_INTM4 {
	unsigned int INTM4:32;		// [31:0]
};
 // GP1_SMP Register
struct GPIO_GP1_SMP {
	unsigned int SMP_INTERVAL:16;		// [15:0]
	unsigned int SMP_POINT_NUMBER:3;		// [18:16]
	unsigned int reserved:13;		// [31:19]
};
 // GP1_ODR Register
struct GPIO_GP1_ODR {
	unsigned int ODR:32;		// [31:0]
};
 // GP1_IR0 Register
struct GPIO_GP1_IR0 {
	unsigned int STAT:32;		// [31:0]
};
 // GP1_IR1 Register
struct GPIO_GP1_IR1 {
	unsigned int STAT:32;		// [31:0]
};
 // GP1_IR2 Register
struct GPIO_GP1_IR2 {
	unsigned int STAT:32;		// [31:0]
};
 // GP1_IR3 Register
struct GPIO_GP1_IR3 {
	unsigned int STAT:32;		// [31:0]
};
 // GP1_IR4 Register
struct GPIO_GP1_IR4 {
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

#endif /* _GPIO_REG_STRUCT_L_H */
