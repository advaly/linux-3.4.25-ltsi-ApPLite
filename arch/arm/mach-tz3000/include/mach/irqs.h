/*
 * linux/arch/arm/mach-tz3000/include/mach/irqs.h
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

#ifndef __MACH_IRQS_H
#define __MACH_IRQS_H

#define IRQ_GLOBALTIMER		27
#define IRQ_LOCALTIMER		29
#define IRQ_LOCALWDOG		30

#define IRQ_GIC_START		32

#define IRQ_UART(x)		(IRQ_GIC_START + 32 + (x))	/* 64 - 68 */
#define IRQ_I2C(x)		(IRQ_GIC_START + 42 + (x))	/* 74 - 78 */
#define IRQ_SPIM(x)		(IRQ_GIC_START + 48 + (x))	/* 80 - 81 */
#define IRQ_SPIB(x)		(IRQ_GIC_START + 52 + (x))	/* 84 - 85 */
#define IRQ_GPIO(x)		(IRQ_GIC_START + 64 + (x))	/* 96 - 97 */
#define IRQ_SGPIO		(IRQ_GIC_START + 79)	/* 111 */
#define IRQ_PCIEMSI(x)		(IRQ_GIC_START + 84 + (x))	/* 124 - 127 */
#define IRQ_PMU_CPU(x)		(IRQ_GIC_START + 120 + (x))	/* 152 - 153 */
#define IRQ_CTI(x)		(IRQ_GIC_START + 124 + (x))	/* 156 - 157 */
#define IRQ_L310_EVENT		(IRQ_GIC_START + 128)	/* 160 */
#define IRQ_USB3HC		(IRQ_GIC_START + 178)	/* 210 */
#define IRQ_PCIEPORT(x)		(IRQ_GIC_START + 184 + (x))	/* 216 - 218 */
#define IRQ_PCIEINTX(x)		(IRQ_GIC_START + 187 + (x))	/* 219 - 222 */
#define IRQ_ETHER		(IRQ_GIC_START + 192)	/* 224 */
#define IRQ_NAND		(IRQ_GIC_START + 194)	/* 226 */
#define IRQ_EMMCA		(IRQ_GIC_START + 196)	/* 228 */
#define IRQ_EMMCA_WKUP		(IRQ_GIC_START + 197)	/* 229 */
#define IRQ_EMMCB		(IRQ_GIC_START + 198)	/* 230 */
#define IRQ_EMMCC		(IRQ_GIC_START + 199)	/* 231 */

#define IRQ_GPIO_START		(IRQ_GIC_START + 224)
#ifdef CONFIG_TZ3000_SGPIO
#define NR_GPIO_IRQS		(32 * 2 + 8)
#else
#define NR_GPIO_IRQS		(32 * 2)
#endif
#define IRQ_MSI_START		(IRQ_GPIO_START + NR_GPIO_IRQS)
#ifdef CONFIG_PCI_MSI
#define NR_MSI_IRQS		(16 * 4)
#else
#define NR_MSI_IRQS		0
#endif
#define NR_IRQS			(IRQ_GPIO_START + NR_GPIO_IRQS + NR_MSI_IRQS)

#define IRQ_I2SI0_INT		88
#define IRQ_I2SI0_ERR		89
#define IRQ_I2SI1_INT		90
#define IRQ_I2SI1_ERR		91
#define IRQ_I2SO0_INT		92
#define IRQ_I2SO0_ERR		93
#define IRQ_I2SO1_INT		94
#define IRQ_I2SO1_ERR		95

#endif /* __MACH_IRQS_H */
