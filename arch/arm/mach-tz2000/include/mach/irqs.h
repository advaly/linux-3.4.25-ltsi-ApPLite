/*
 * linux/arch/arm/mach-tz2000/include/mach/irqs.h
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

#define IRQ_UART(x)		(IRQ_GIC_START + 32 + (x))	/* 64 - 67 */
#define IRQ_I2C(x)		(IRQ_GIC_START + 42 + (x))	/* 74 - 77 */
#define IRQ_SPIM(x)		(IRQ_GIC_START + 48 + (x))	/* 80 - 81 */
#define IRQ_SPIB(x)		(IRQ_GIC_START + 52 + (x))	/* 84 */
#define IRQ_GPIO(x)		(IRQ_GIC_START + 64 + (x))	/* 96 - 97 */
#define IRQ_PMU_CPU(x)		(IRQ_GIC_START + 120 + (x))	/* 152 */
#define IRQ_CTI(x)		(IRQ_GIC_START + 124 + (x))	/* 156 */
#define IRQ_USB2H_EHCI		(IRQ_GIC_START + 138)	/* 170 */
#define IRQ_USB2H_OHCI		(IRQ_GIC_START + 139)	/* 171 */
#define IRQ_EMMCA		(IRQ_GIC_START + 140)	/* 172 */
#define IRQ_EMMCB		(IRQ_GIC_START + 142)	/* 174 */
#define IRQ_ETHER		(IRQ_GIC_START + 153)	/* 185 */

#define IRQ_GPIO_START		(IRQ_GIC_START + 224)
#define NR_GPIO_IRQS		(32 * 2)
#define NR_IRQS			(IRQ_GPIO_START + NR_GPIO_IRQS)

#define IRQ_I2SI0_INT		88
#define IRQ_I2SI0_ERR		89
#define IRQ_I2SO0_INT		92
#define IRQ_I2SO0_ERR		93

#endif /* __MACH_IRQS_H */
