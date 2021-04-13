/*
 * linux/include/linux/applite/hist_ioctl.h
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
#ifndef __HIST_IOCTL_H__
#define __HIST_IOCTL_H__

#include <linux/ioctl.h>
#include "drv_cmn.h"
#include "hist_param.h"

/*
// PYRAMID: 0xB9
// AFFINE: 0xBA
// HIST: 0xBB
// MATCH: 0xBC
// HOG: 0xBD
// DICT: 0xBE
// FILTER: 0xBF
*/

#define HIST_IOCTL_MAGIC 0xBB

#define HIST_IOCTL_HISTOGRAM             _IOW(HIST_IOCTL_MAGIC, 0x00, struct hist_param)
#define HIST_IOCTL_HISTOGRAM_SCOREVOTING _IOW(HIST_IOCTL_MAGIC, 0x01, struct hist_scorevoting_param)
#define HIST_IOCTL_TABLE_MODE            _IO(HIST_IOCTL_MAGIC, 0x02)
#define HIST_IOCTL_GET_VERSION           _IOR(HIST_IOCTL_MAGIC, 0x03, drv_version_t)
#define HIST_IOCTL_INITIALIZE            _IO(HIST_IOCTL_MAGIC, 0x04)

#endif /* __HIST_IOCTL_H__ */
