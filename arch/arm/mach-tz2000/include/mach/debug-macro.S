/* arch/arm/mach-tz2000/include/mach/debug-macro.S
 *
 * Debugging macro include header
 *
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *  Copyright (C) 1994-1999 Russell King
 *  Moved from linux/arch/arm/kernel/debug.S by Ben Dooks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/serial_reg.h>
#define UART_SHIFT	2

		.macro addruart,rp,rv,tmp
		mov	\rp, #0x0800
		mov	\rv, #0xfe00		@ virtual base
		lsl	\rp, \rp, #16
		lsl	\rv, \rv, #16
#if CONFIG_TZ2000_DEBUG_UART != 0
		add	\rp, \rp, #(0x1000 * CONFIG_TZ2000_DEBUG_UART)
		add	\rv, \rv, #(0x1000 * CONFIG_TZ2000_DEBUG_UART)
#endif
		.endm

		.macro senduart,rd,rx
		str	\rd, [\rx, #UART_TX << UART_SHIFT]
		.endm

		.macro waituart,rd,rx
		.endm

		.macro busyuart,rd,rx
1002:		ldr	\rd, [\rx, #UART_LSR << UART_SHIFT]
		and	\rd, \rd, #UART_LSR_TEMT | UART_LSR_THRE
		teq	\rd, #UART_LSR_TEMT | UART_LSR_THRE
		bne	1002b
		.endm
