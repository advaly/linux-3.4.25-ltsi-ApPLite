/*
 * arch/arm/mach-tz3000/include/mach/regs/cpu_memmap_def.h
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
#define CPU_WESTPIER_REG_BASE 0xF010000
#define CPU_WESTPIER_REG_SIZE 0x80

#define CPU_UART_REG_BASE 0x8000000
#define CPU_UART_REG_SIZE 0x8000

#define CPU_ETHER_REG_BASE 0xB1C0000
#define CPU_ETHER_REG_SIZE 0x2000

#define CPU_DISPIF_REG_BASE 0xB120000
#define CPU_DISPIF_REG_SIZE 0x4000

#define CPU_I2SI_REG_BASE 0x8060000
#define CPU_I2SI_REG_SIZE 0x2000

#define CPU_PWM_REG_BASE 0x80B0000
#define CPU_PWM_REG_SIZE 0x400

#define CPU_ECONF_REG_BASE 0xB100000
#define CPU_ECONF_REG_SIZE 0x800

#define CPU_SADC_REG_BASE 0x8110000
#define CPU_SADC_REG_SIZE 0x80

#define CPU_CAMIF_REG_BASE 0xB130000
#define CPU_CAMIF_REG_SIZE 0x4000

#define CPU_FDRAMC_REG_BASE 0xC000000
#define CPU_FDRAMC_REG_SIZE 0x800

#define CPU_SI2C1_REG_BASE 0x4C1000
#define CPU_SI2C1_REG_SIZE 0x100

#define CPU_PCIEC_REG_BASE 0xB160000
#define CPU_PCIEC_REG_SIZE 0x10000

#define CPU_MBOOT_REG_BASE 0x0
#define CPU_MBOOT_REG_SIZE 0x80

#define CPU_SPIB_REG_BASE 0x8050000
#define CPU_SPIB_REG_SIZE 0x2000

#define CPU_I2SO_REG_BASE 0x8070000
#define CPU_I2SO_REG_SIZE 0x2000

#define CPU_EMMCB_REG_BASE 0xB1E1000
#define CPU_EMMCB_REG_SIZE 0x100

#define CPU_GPU_REG_BASE 0xB150000
#define CPU_GPU_REG_SIZE 0x20

#define CPU_NANDC_REG_BASE 0xB1D0000
#define CPU_NANDC_REG_SIZE 0x1000

#define CPU_SI2C0_REG_BASE 0x4C0000
#define CPU_SI2C0_REG_SIZE 0x100

#define CPU_PMU_REG_BASE 0x440000
#define CPU_PMU_REG_SIZE 0x10000

#define CPU_GDMAC_REG_BASE 0x8100000
#define CPU_GDMAC_REG_SIZE 0x2000

#define CPU_DTREE_REG_BASE 0x400000
#define CPU_DTREE_REG_SIZE 0x8

#define CPU_SCOMM_REG_BASE 0x580000
#define CPU_SCOMM_REG_SIZE 0x20

#define CPU_EMMCC_REG_BASE 0xB1E2000
#define CPU_EMMCC_REG_SIZE 0x100

#define CPU_GCONF_REG_BASE 0x401000
#define CPU_GCONF_REG_SIZE 0x80

#define CPU_DBGMON_REG_BASE 0xC010000
#define CPU_DBGMON_REG_SIZE 0x2000

#define CPU_DSGATE_REG_BASE 0xC002000
#define CPU_DSGATE_REG_SIZE 0x400

#define CPU_I2C_REG_BASE 0x8010000
#define CPU_I2C_REG_SIZE 0x8000

#define CPU_USB3HC_REG_BASE 0xB000000
#define CPU_USB3HC_REG_SIZE 0x10000

#define CPU_PPIER_REG_BASE 0x8120000
#define CPU_PPIER_REG_SIZE 0x10000

#define CPU_TMR_REG_BASE 0x80A0000
#define CPU_TMR_REG_SIZE 0x400

#define CPU_SPIMS_REG_BASE 0x8030000
#define CPU_SPIMS_REG_SIZE 0x20000

#define CPU_USB2DC_REG_BASE 0xB180000
#define CPU_USB2DC_REG_SIZE 0x1000

#define CPU_MBOX_REG_BASE 0x80C0000
#define CPU_MBOX_REG_SIZE 0x20000

#define CPU_GPIO_REG_BASE 0x8090000
#define CPU_GPIO_REG_SIZE 0x2000

#define CPU_VCONV_REG_BASE 0xB110000
#define CPU_VCONV_REG_SIZE 0x400

#define CPU_SGPIO_REG_BASE 0x500000
#define CPU_SGPIO_REG_SIZE 0x80

#define CPU_IRECOG_REG_BASE 0xB140000
#define CPU_IRECOG_REG_SIZE 0x4000

#define CPU_I2SC_REG_BASE 0x8080000
#define CPU_I2SC_REG_SIZE 0x100

#define CPU_EMMCA_REG_BASE 0xB1E0000
#define CPU_EMMCA_REG_SIZE 0x100

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CPU_MEMMAP_DEF_H */
