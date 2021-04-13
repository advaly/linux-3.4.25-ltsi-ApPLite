/*
 * drivers/staging/applite/vdu/vd_config.h
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

#ifndef VD_CONFIG_H
#define VD_CONFIG_H


#ifdef __KERNEL__
	#include <linux/swab.h>
	#define VD_REV(val)     swab32(val)
#else
	#define VD_REV(val)     __builtin_bswap32(val)
#endif


#define VD_CH_NUM_MAX (2)

#define VD_BUF_STD_SIZE    (2*1024*1024)
#define VD_BUF_WORK_SIZE  (22*1024*1024)
#define VD_BUF_FRAME_SIZE (39*1024*1024)

#ifdef __KERNEL__
#include <mach/regs/mbox_offs_def.h>
#else
#define MBOX_INT_REG400_SET_OFFS       0x00004000
#define MBOX_INT_REG401_SET_OFFS       0x00004004
#define MBOX_INT_REG404_SET_OFFS       0x00004010
#define MBOX_INT_REG408_SET_OFFS       0x00004020
#define MBOX_INT_REG409_SET_OFFS       0x00004024
#define MBOX_INT_REG410_SET_OFFS       0x00004028
#define MBOX_INT_REG412_SET_OFFS       0x00004030
#define MBOX_MBOX_TAS00_OFFS           0x00008000
#define MBOX_MBOX_TAS01_OFFS           0x00008004
#endif

#endif
