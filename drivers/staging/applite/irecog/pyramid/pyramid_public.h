/*
 * linux/drivers/staging/applite/irecog/pyramid/pyramid_public.h
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
#ifndef __PYRAMID_PUBLIC_H__
#define __PYRAMID_PUBLIC_H__

#include <linux/applite/irecog/drv_cmn.h>

#include <mach/regs/irecog_offs_def.h>
#include <mach/regs/irecog_reg_def.h>

/* temporary add */
#define MAX_READ_PORT   3
#define MAX_WRITE_PORT 12
#define MAX_TABLE_NUM  16
#define MAX_ROUTE       4

#define _PYM_R_INTERVAL 0x40
#define _PYM_R_NUM      3

#define _PYM_W_INTERVAL 0x40
#define _PYM_W_NUM      12

#define _PYM_T_INTERVAL 0x8

#define MBUS_STADR  0x00000000
#define MBUS_ENDADR 0xFFFFFFFF

#define RSCALER_OFFSET(x) ((x) - IRECOG_rpyramid_RSCALER_CS_START_OFFS)

#endif /* __PYRAMID_PUBLIC_H__ */
