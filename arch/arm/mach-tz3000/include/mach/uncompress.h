/*
 * linux/arch/arm/mach-tz3000/include/mach/uncompress.h
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
#include <linux/io.h>
#include <linux/serial_reg.h>
#include <mach/platform.h>

#define UART_SHIFT	2

static inline void putc(int c)
{
	void __iomem *base = IOMEM(TZ3000_UART_BASE +
				   0x1000 * CONFIG_TZ3000_DEBUG_UART);

	while (!(__raw_readl(base + (UART_LSR << UART_SHIFT)) & UART_LSR_THRE))
		barrier();
	__raw_writel(c, base + (UART_TX << UART_SHIFT));
}

static inline void flush(void)
{
	void __iomem *base = IOMEM(TZ3000_UART_BASE +
				   0x1000 * CONFIG_TZ3000_DEBUG_UART);

	while (!(__raw_readl(base + (UART_LSR << UART_SHIFT)) & UART_LSR_THRE))
		barrier();
}

/* nothing to do */
#define arch_decomp_setup()
#define arch_decomp_wdog()
