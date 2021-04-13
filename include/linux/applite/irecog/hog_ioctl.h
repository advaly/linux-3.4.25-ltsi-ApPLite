/*
 * linux/include/linux/applite/hog_ioctl.h
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
#ifndef __HOG_IOCTL_H__
#define __HOG_IOCTL_H__

#include <linux/ioctl.h>
#include "drv_cache_ctrl_defs.h"

/*
// PYRAMID: 0xB9
// AFFINE: 0xBA
// HIST: 0xBB
// MATCH: 0xBC
// HOG: 0xBD
// DICT: 0xBE
// FILTER: 0xBF
*/

#define HOG_IOCTL_MAGIC         0xBD

#define HOG_IOCTL_LOAD_DICTIONARY       _IO(HOG_IOCTL_MAGIC, 0x00)
#define HOG_IOCTL_CLASSIFY_POSITION     _IO(HOG_IOCTL_MAGIC, 0x01)

#define HOG_IOCTL_SET_DICT_BANK_MODE    _IO(HOG_IOCTL_MAGIC, 0x02)
#define HOG_IOCTL_GET_VERSION           _IO(HOG_IOCTL_MAGIC, 0x03)
#define HOG_IOCTL_INITIALIZE            _IO(HOG_IOCTL_MAGIC, 0x04)

#define HOG_IOCTL_CLASSIFY_REGION       _IO(HOG_IOCTL_MAGIC, 0x05)

#endif /* __HOG_IOCTL_H__ */
