/*
 * linux/arch/arm/mach-tz3000/include/mach/hardware.h
 *
 * This file is the hardware definitions of TZ3000
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
#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

/* macro to get at IO space when running virtually */
#ifdef CONFIG_MMU
/*
 * Statically mapped addresses:
 *
 * 0000 0000 - 0000 0fff -> feff 0000 - feff 0fff (MBOOT)
 * 0040 1000 - 0040 1fff -> fe40 1000 - fe40 1fff (GCONF)
 * 0800 0000 - 0812 ffff -> fe00 0000 - fe12 ffff (UART, etc.)
 * 0044 0000 - 0044 ffff -> fe44 0000 - fe44 ffff (PMU)
 * 0058 0000 - 0058 0fff -> fe58 0000 - fe58 0fff (SCOMM)
 * 0f10 0000 - 0f10 3fff -> fe30 0000 - fe30 3fff (CA9)
 */

#define IO_ADDRESS(x)	(((x) & 0xfff00000) == 0x0f100000 ? \
			 (((x) & 0x000fffff) + 0xfe300000) : \
			 (((x) & 0xfff00000) != 0 ? \
			  (((x) & 0x00ffffff) + 0xfe000000) : \
			  ((x) & 0x00000fff) + 0xfeff0000))
#else
#define	IO_ADDRESS(x)	(x)
#endif
#define __io_address(n)		IOMEM(IO_ADDRESS(n))

#endif /* __ASM_ARCH_HARDWARE_H */
