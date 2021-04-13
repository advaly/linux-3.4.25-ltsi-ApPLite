/*
 * arch/arm/mach-tz2000/include/mach/regs/gconf_reg_struct_b.h
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


 // PINSHARE0 Register
struct GCONF_PINSHARE0 {
	unsigned int Reserved:3;		// [31:29]
	unsigned int GPIO_DISP_SEL:1;		// [28]
	unsigned int Reserved2:3;		// [27:25]
	unsigned int GPIO_ETHER_SEL:1;		// [24]
	unsigned int Reserved3:2;		// [23:22]
	unsigned int GPIO_EMMC1_SEL:1;		// [21]
	unsigned int GPIO_EMMC0_SEL:1;		// [20]
	unsigned int Reserved4:4;		// [19:16]
	unsigned int GPIO_UART3_DSEL:1;		// [15]
	unsigned int GPIO_UART3_FSEL:1;		// [14]
	unsigned int GPIO_UART2_DSEL:1;		// [13]
	unsigned int GPIO_UART2_FSEL:1;		// [12]
	unsigned int Reserved5:4;		// [11:8]
	unsigned int Reserved6:4;		// [7:4]
	unsigned int GPIO_SPI3_SEL:1;		// [3]
	unsigned int GPIO_SPI2_SEL:1;		// [2]
	unsigned int Reserved7:2;		// [1:0]
};
 // PINSHARE1 Register
struct GCONF_PINSHARE1 {
	unsigned int reserved1:31;		// [31:1]
	unsigned int EMMC1_SDCARD_SEL:1;		// [0]
};
 // PINSHARE2 Register
struct GCONF_PINSHARE2 {
	unsigned int reserved1:30;		// [31:2]
	unsigned int TDIME_SEL:1;		// [1]
	unsigned int SDIME_SEL:1;		// [0]
};
 // PINSHARE3 Register
struct GCONF_PINSHARE3 {
	unsigned int reserved1:31;		// [31:1]
	unsigned int DDRPHY_DEBUG_SEL:1;		// [0]
};
 // CPU_EVENT Register
struct GCONF_CPU_EVENT {
	unsigned int reserved2:1;		// [31]
	unsigned int reserved:30;		// [30:1]
	unsigned int CPU_EVENT:1;		// [0]
};
 // CPU_STANDBY_STATUS Register
struct GCONF_CPU_STANDBY_STATUS {
	unsigned int reserved:27;		// [31:5]
	unsigned int CPU_STANDBYWFE:1;		// [4]
	unsigned int reserved2:3;		// [3:1]
	unsigned int CPU_STANDBYWFI:1;		// [0]
};
 // GDMAC_CTRL0 Register
struct GCONF_GDMAC_CTRL0 {
	unsigned int reserved:29;		// [31:3]
	unsigned int BOOT_MANAGER_NS:1;		// [2]
	unsigned int BOOT_FROM_PC:1;		// [1]
	unsigned int reserved2:1;		// [0]
};
 // GDMAC_CTRL1 Register
struct GCONF_GDMAC_CTRL1 {
	unsigned int BOOT_ADDR:32;		// [31:0]
};
 // GDMAC_CTRL2 Register
struct GCONF_GDMAC_CTRL2 {
	unsigned int reserved:16;		// [31:16]
	unsigned int BOOT_IRQ_NS:16;		// [15:0]
};
 // GDMAC_CTRL3 Register
struct GCONF_GDMAC_CTRL3 {
	unsigned int reserved:8;		// [31:24]
	unsigned int BOOT_PERIPH_NS:24;		// [23:0]
};
 // GDMAC_CTRL4 Register
struct GCONF_GDMAC_CTRL4 {
	unsigned int reserved:8;		// [31:24]
	unsigned int SYNCSEL:24;		// [23:0]
};
 // GDMAC_CTRL5 Register
struct GCONF_GDMAC_CTRL5 {
	unsigned int reserved:8;		// [31:24]
	unsigned int ENABLE_DMACTC:24;		// [23:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GCONF_REG_STRUCT_B_H */
