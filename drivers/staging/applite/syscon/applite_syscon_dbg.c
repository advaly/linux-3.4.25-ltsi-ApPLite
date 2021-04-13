/*
 * linux/drivers/staging/applite/applite_syscon_dbg.c
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2012
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*===================================
Include Files
===================================*/

#include <linux/kernel.h>
#include <linux/uaccess.h>

#include <linux/applite/applite_syscon.h>
#include "applite_syscon_internal.h"
#include "applite_syscon_regs.h"
#include "applite_syscon_dbg.h"


/*===================================
Static Variables and Functions prototypes
===================================*/


/*===================================
Global Variables and Functions prototypes
===================================*/
__u32 ul_logflags;


/*===================================
Macros
===================================*/

/*===================================
Function Definitions
===================================*/

/*===================================
Module source
===================================*/


void syscon_dump_buf(__u8 *buf, __u32 size)
{
	__u32 i;
	__u32 *p = (__u32 *)buf;

	if (ul_logflags & SYSCON_LOG_DEBUG)
		for (i = 0; i < size; i += 16) {
			pr_info("%p: %08X %08X %08X %08X\n",
				p, p[0], p[1], p[2], p[3]);
			p += 4;
		}
}


