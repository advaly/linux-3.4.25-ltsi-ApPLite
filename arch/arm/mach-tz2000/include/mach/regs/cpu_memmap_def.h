/*
 * arch/arm/mach-tz2000/include/mach/regs/cpu_memmap_def.h
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

#ifndef CPU_MEMMAP_DEF_H
#define CPU_MEMMAP_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// memmap
#define CPU_PMU_REG_BASE 0x440000
#define CPU_PMU_REG_SIZE 0x10000

#define CPU_GDMAC_REG_BASE 0x8100000
#define CPU_GDMAC_REG_SIZE 0x2000

#define CPU_DTREE_REG_BASE 0x400000
#define CPU_DTREE_REG_SIZE 0x8

#define CPU_UART_REG_BASE 0x8000000
#define CPU_UART_REG_SIZE 0x4000

#define CPU_I2SI_REG_BASE 0x8060000
#define CPU_I2SI_REG_SIZE 0x200

#define CPU_PWM_REG_BASE 0x80B0000
#define CPU_PWM_REG_SIZE 0x400

#define CPU_GCONF_REG_BASE 0x401000
#define CPU_GCONF_REG_SIZE 0x80

#define CPU_TELOMERE_REG_BASE 0xA200000
#define CPU_TELOMERE_REG_SIZE 0x4000

#define CPU_GFX_REG_BASE 0xA040000
#define CPU_GFX_REG_SIZE 0x400

#define CPU_RTC_REG_BASE 0x481000
#define CPU_RTC_REG_SIZE 0x1000

#define CPU_I2C_REG_BASE 0x8010000
#define CPU_I2C_REG_SIZE 0x4000

#define CPU_EMMC4SD_REG_BASE 0xA1C0000
#define CPU_EMMC4SD_REG_SIZE 0x100

#define CPU_ETHERMAC_REG_BASE 0xA180000
#define CPU_ETHERMAC_REG_SIZE 0x2000

#define CPU_YUVC_REG_BASE 0xA080000
#define CPU_YUVC_REG_SIZE 0x1000

#define CPU_USB2HCE_REG_BASE 0xA0C0000
#define CPU_USB2HCE_REG_SIZE 0x100

#define CPU_EMMC8SD_REG_BASE 0xA280000
#define CPU_EMMC8SD_REG_SIZE 0x100

#define CPU_TMR_REG_BASE 0x80A0000
#define CPU_TMR_REG_SIZE 0x400

#define CPU_SPIMS_REG_BASE 0x8030000
#define CPU_SPIMS_REG_SIZE 0x20000

#define CPU_USB2DC_REG_BASE 0xA100000
#define CPU_USB2DC_REG_SIZE 0x1000

#define CPU_LCDC_REG_BASE 0xA000000
#define CPU_LCDC_REG_SIZE 0x1000

#define CPU_SADC12_REG_BASE 0x8110000
#define CPU_SADC12_REG_SIZE 0x80

#define CPU_MBOX_REG_BASE 0x80C0000
#define CPU_MBOX_REG_SIZE 0x20000

#define CPU_SPIB_REG_BASE 0x8050000
#define CPU_SPIB_REG_SIZE 0x800

#define CPU_I2SO_REG_BASE 0x8070000
#define CPU_I2SO_REG_SIZE 0x200

#define CPU_GPIO_REG_BASE 0x8090000
#define CPU_GPIO_REG_SIZE 0x2000

#define CPU_WCONF_REG_BASE 0xA2C0000
#define CPU_WCONF_REG_SIZE 0x800

#define CPU_I2SC_REG_BASE 0x8080000
#define CPU_I2SC_REG_SIZE 0x100

#define CPU_USB2HCO_REG_BASE 0xA0E0000
#define CPU_USB2HCO_REG_SIZE 0x200

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CPU_MEMMAP_DEF_H */
