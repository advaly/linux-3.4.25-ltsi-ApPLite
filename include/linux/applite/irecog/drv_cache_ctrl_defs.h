/*
 * linux/include/linux/applite/drv_cache_ctrl_defs.h
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
#ifndef _DRV_CACHE_CTRL_DEFS_H_
#define _DRV_CACHE_CTRL_DEFS_H_

#define DRV_NO_CACHE_CTL            0x00
#define DRV_CACHE_FLUSH_ALL         0x01
#define DRV_INBUF_FLUSH_RANGE       0x02
#define DRV_OUTBUF_INVALIDATE_RANGE 0x04

#endif /* _DRV_CACHE_CTRL_DEFS_H_ */
