/*
 * arch/arm/mach-tz3000/include/mach/regs/gconf_reg_struct_b.h
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

#ifndef _GCONF_REG_STRUCT_B_H
#define _GCONF_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // I2SSEL Register
struct GCONF_I2SSEL {
	unsigned int reserved1:28;		// [31:4]
	unsigned int I2SSEL:3;		// [3:1]
	unsigned int OE_N:1;		// [0]
};
 // PINSHARE0 Register
struct GCONF_PINSHARE0 {
	unsigned int GPIO_SEL0:24;		// [31:8]
	unsigned int reserved1:8;		// [7:0]
};
 // PINSHARE1 Register
struct GCONF_PINSHARE1 {
	unsigned int GPIO_SEL1:32;		// [31:0]
};
 // PINSHARE2 Register
struct GCONF_PINSHARE2 {
	unsigned int reserved1:31;		// [31:1]
	unsigned int SDIME_SEL:1;		// [0]
};
 // PINSHARE3 Register
struct GCONF_PINSHARE3 {
	unsigned int reserved1:31;		// [31:1]
	unsigned int eMMC2_SEL:1;		// [0]
};
 // CPU_EVENT Register
struct GCONF_CPU_EVENT {
	unsigned int reserved2:1;		// [31]
	unsigned int reserved:30;		// [30:1]
	unsigned int CPU_EVENT:1;		// [0]
};
 // CPU_STANDBY_STATUS Register
struct GCONF_CPU_STANDBY_STATUS {
	unsigned int reserved:26;		// [31:6]
	unsigned int CPU_STANDBYWFE:2;		// [5:4]
	unsigned int reserved2:2;		// [3:2]
	unsigned int CPU_STANDBYWFI:2;		// [1:0]
};
 // GDMAC_CTRL0 Register
struct GCONF_GDMAC_CTRL0 {
	unsigned int reserved:29;		// [31:3]
	unsigned int BOOT_MANAGER_NS:1;		// [2]
	unsigned int BOOT_FROM_PC:1;		// [1]
	unsigned int PCLKEN:1;		// [0]
};
 // GDMAC_CTRL1 Register
struct GCONF_GDMAC_CTRL1 {
	unsigned int BOOT_ADDR:32;		// [31:0]
};
 // GDMAC_CTRL2 Register
struct GCONF_GDMAC_CTRL2 {
	unsigned int BOOT_IRQ_NS:32;		// [31:0]
};
 // GDMAC_CTRL3 Register
struct GCONF_GDMAC_CTRL3 {
	unsigned int BOOT_PERIPH_NS:32;		// [31:0]
};
 // GDMAC_CTRL4 Register
struct GCONF_GDMAC_CTRL4 {
	unsigned int reserved:2;		// [31:30]
	unsigned int SYNCSEL:30;		// [29:0]
};
 // GDMAC_CTRL5 Register
struct GCONF_GDMAC_CTRL5 {
	unsigned int reserved:2;		// [31:30]
	unsigned int ENABLE_DMACTC:30;		// [29:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GCONF_REG_STRUCT_B_H */
