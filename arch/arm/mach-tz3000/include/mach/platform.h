/*
 * linux/arch/arm/mach-tz3000/include/mach/platform.h
 *
 * (C) Copyright TOSHIBA CORPORATION SEMICONDUCTOR COMPANY 2010
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef __ASM_ARCH_PLATFORM_H
#define __ASM_ARCH_PLATFORM_H

#ifndef __ASSEMBLY__
#include <linux/delay.h>
#include <linux/io.h>
#endif

#define TZ3000_PERIPHERAL_BASE		0x08000000
#define TZ3000_PERIPHERAL_SIZE		0x00130000
#define TZ3000_GCONF_BASE		0x00401000
#define TZ3000_GCONF_SIZE		0x00001000
#define TZ3000_PMU_BASE			0x00440000
#define TZ3000_PMU_SIZE			0x00010000
#define TZ3000_SGPIO_BASE		0x00500000
#define TZ3000_SCOMM_BASE		0x00580000
#define TZ3000_SCOMM_SIZE		0x00001000
#define TZ3000_MBOOT_BASE		0x00000000
#define TZ3000_MBOOT_SIZE		0x00001000

#define TZ3000_ECONF_BASE		0x0b100000
#define TZ3000_PCIE_BASE		0x0b160000
#define TZ3000_ETHERMAC_BASE		0x0b1c0000
#define TZ3000_HAM_NAND_BASE		0x0b1d0000
#define TZ3000_EMMCA_BASE		0x0b1e0000
#define TZ3000_EMMCB_BASE		0x0b1e1000
#define TZ3000_EMMCC_BASE		0x0b1e2000
#define TZ3000_USB3HC_BASE		0x0b000000
#define TZ3000_USB2DC_BASE		0x0b180000
#define TZ3000_HAM_NANDC_BASE		0x0a000000
#define TZ3000_UART_BASE		0x08000000
#define TZ3000_I2C_BASE			0x08010000
#define TZ3000_TMR_BASE			0x080a0000
#define TZ3000_GPIO_BASE		0x08090000
#define TZ3000_SPIMS_BASE		0x08030000
#define TZ3000_SPI_BASE			0x08050000
#define TZ3000_MBOX_BASE		0x080c0000

#define TZ3000_CPU_BASE			0x0f100000
#define TZ3000_CPU_SIZE			0x00004000
#define TZ3000_GIC_CPU_BASE		0x0f100100
#define TZ3000_GLOBAL_TMR_BASE		0x0f100200
#define TZ3000_PRIVATE_TMR_BASE		0x0f100600
#define TZ3000_GIC_DIST_BASE		0x0f101000
#define TZ3000_L2C_BASE			0x0f102000
#define TZ3000_PCIE_EXMEM_BASE		0x40000000
#define TZ3000_SPI_FLASH_BASE		0x20000000

#define TZ3000_I2SI_BASE		0x08060000
#define TZ3000_I2SO_BASE		0x08070000
#define TZ3000_I2SC_BASE		0x08080000

#define TZ3000_SYS_FLAGSSET		(TZ3000_MBOOT_BASE + 0x70)

#define TZ3000_BOOTINFO_BASE		(TZ3000_SCOMM_BASE + 0x600)
#define TZ3000_BOOTINFO_FWREV0		(TZ3000_BOOTINFO_BASE + 0x00)
#define TZ3000_BOOTINFO_FWREV1		(TZ3000_BOOTINFO_BASE + 0x04)

#define TZ3000_PLLCLK			600000000 /* default */
#define TXSS_PERIPHCLK			(TZ3000_PLLCLK / 16) /* default */

#define TZ3000_PMU_CGON			(TZ3000_PMU_BASE + 0x1000)
#define TZ3000_PMU_CGON_PERI0		(TZ3000_PMU_CGON + 0x020)
#define TZ3000_PMU_CGON_PERI1		(TZ3000_PMU_CGON + 0x024)
#define TZ3000_PMU_CGON_PERI2		(TZ3000_PMU_CGON + 0x028)
#define TZ3000_PMU_CGON_PERI3		(TZ3000_PMU_CGON + 0x02c)
#define TZ3000_PMU_CGON_PERI4		(TZ3000_PMU_CGON + 0x030)
#define TZ3000_PMU_CGON_HSIO		(TZ3000_PMU_CGON + 0x110)
#define TZ3000_PMU_CGON_ETHER		(TZ3000_PMU_CGON + 0x190)
#define TZ3000_PMU_CGON_EMMC		(TZ3000_PMU_CGON + 0x1a0)
#define TZ3000_PMU_CGON_NANDC		(TZ3000_PMU_CGON + 0x1b0)
#define TZ3000_PMU_CGOFF		(TZ3000_PMU_BASE + 0x1400)
#define TZ3000_PMU_CGOFF_PERI0		(TZ3000_PMU_CGOFF + 0x020)
#define TZ3000_PMU_CGOFF_PERI1		(TZ3000_PMU_CGOFF + 0x024)
#define TZ3000_PMU_CGOFF_PERI2		(TZ3000_PMU_CGOFF + 0x028)
#define TZ3000_PMU_CGOFF_PERI3		(TZ3000_PMU_CGOFF + 0x02c)
#define TZ3000_PMU_CGOFF_PERI4		(TZ3000_PMU_CGOFF + 0x030)
#define TZ3000_PMU_CGOFF_HSIO		(TZ3000_PMU_CGOFF + 0x110)
#define TZ3000_PMU_CGOFF_ETHER		(TZ3000_PMU_CGOFF + 0x190)
#define TZ3000_PMU_CGOFF_EMMC		(TZ3000_PMU_CGOFF + 0x1a0)
#define TZ3000_PMU_CGOFF_NANDC		(TZ3000_PMU_CGOFF + 0x1b0)
#define TZ3000_PMU_SRON			(TZ3000_PMU_BASE + 0x1800)
#define TZ3000_PMU_SRON_CPU0		(TZ3000_PMU_SRON + 0x010)
#define TZ3000_PMU_SRON_CPU1		(TZ3000_PMU_SRON + 0x014)
#define TZ3000_PMU_SRON_PERI0		(TZ3000_PMU_SRON + 0x020)
#define TZ3000_PMU_SRON_PERI1		(TZ3000_PMU_SRON + 0x024)
#define TZ3000_PMU_SRON_PERI2		(TZ3000_PMU_SRON + 0x028)
#define TZ3000_PMU_SRON_PERI3		(TZ3000_PMU_SRON + 0x02c)
#define TZ3000_PMU_SRON_PERI4		(TZ3000_PMU_SRON + 0x030)
#define TZ3000_PMU_SRON_HSIO		(TZ3000_PMU_SRON + 0x110)
#define TZ3000_PMU_SRON_ETHER		(TZ3000_PMU_SRON + 0x190)
#define TZ3000_PMU_SRON_EMMC		(TZ3000_PMU_SRON + 0x1a0)
#define TZ3000_PMU_SRON_NANDC		(TZ3000_PMU_SRON + 0x1b0)
#define TZ3000_PMU_SROFF		(TZ3000_PMU_BASE + 0x1c00)
#define TZ3000_PMU_SROFF_CPU0		(TZ3000_PMU_SROFF + 0x010)
#define TZ3000_PMU_SROFF_CPU1		(TZ3000_PMU_SROFF + 0x014)
#define TZ3000_PMU_SROFF_PERI0		(TZ3000_PMU_SROFF + 0x020)
#define TZ3000_PMU_SROFF_PERI1		(TZ3000_PMU_SROFF + 0x024)
#define TZ3000_PMU_SROFF_PERI2		(TZ3000_PMU_SROFF + 0x028)
#define TZ3000_PMU_SROFF_PERI3		(TZ3000_PMU_SROFF + 0x02c)
#define TZ3000_PMU_SROFF_PERI4		(TZ3000_PMU_SROFF + 0x030)
#define TZ3000_PMU_SROFF_HSIO		(TZ3000_PMU_SROFF + 0x110)
#define TZ3000_PMU_SROFF_ETHER		(TZ3000_PMU_SROFF + 0x190)
#define TZ3000_PMU_SROFF_EMMC		(TZ3000_PMU_SROFF + 0x1a0)
#define TZ3000_PMU_SROFF_NANDC		(TZ3000_PMU_SROFF + 0x1b0)
#define TZ3000_PMU_PLLCONFIG_PLLCPU_0	(TZ3000_PMU_BASE + 0x4500)
#define TZ3000_PMU_PLLCONFIG_PLLCPU_1	(TZ3000_PMU_BASE + 0x4504)
#define TZ3000_PMU_PLLETHR_REG		(TZ3000_PMU_BASE + 0x4520)

#define TZ3000_GCONF_PINSHARE0		(TZ3000_GCONF_BASE + 0x10)
#define TZ3000_GCONF_PINSHARE1		(TZ3000_GCONF_BASE + 0x14)
#define TZ3000_GCONF_PINSHARE3		(TZ3000_GCONF_BASE + 0x28)

#define TZ3000_ECONF_EMMC_BASE(ch)	\
	(TZ3000_ECONF_BASE + 0x100 + (ch) * 0x100)

#define TZ3000_SPIC_ID			0
#define TZ3000_SPIC_INITIAL_SPEED_HZ	18750000
#define TZ3000_SPIC_INITIAL_DEASSERT_TIME	1275
#define TZ3000_SPIC_NUM		2

#define TZ3000_SPIMS_ID			2
#define TZ3000_SPIMS_NUM		2

#define I2C_TZ3000_CH_NUM	5

#define I2C_TZ3000_REG(ch)	(TZ3000_I2C_BASE + (ch) * 0x1000)

#define TZ3000_SPI_REG(ch)	(TZ3000_SPI_BASE + (ch) * 0x1000)

#define TZ3000_GPIO_REG(x)	(TZ3000_GPIO_BASE + (x) * 0x1000)
#define TZ3000_GP_DR(x)			(TZ3000_GPIO_REG(x) + 0x04)
#define TZ3000_GP_SMP(x)		(TZ3000_GPIO_REG(x) + 0x30)

#define TZ3000_SPIMS_REG(x)	(TZ3000_SPIMS_BASE + (x) * 0x10000)
#define TZ3000_MBOX_INTGEN_REG(x)	(TZ3000_MBOX_BASE + (x) * 0x1000)

#define TZ3000_MBOX_PCIE_BASE	TZ3000_MBOX_INTGEN_REG(3)

#ifndef __ASSEMBLY__
int tz3000_pl310_init(void);
void tz3000_enter_suspend(void);
void v7_cpu_resume(void);

#if IS_ENABLED(CONFIG_APPLITE_IRECOG)
void init_irecog(void);
#endif
void tz3000_setup_gdmac(void);
#endif

#endif /* __ASM_ARCH_PLATFORM_H */
