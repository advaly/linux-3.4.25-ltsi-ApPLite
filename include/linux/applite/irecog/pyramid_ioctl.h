/*
 * linux/include/linux/applite/pyramid_ioctl.h
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
#ifndef __PYRAMID_IOCTL_H__
#define __PYRAMID_IOCTL_H__

#include "basic_type.h"
#include <linux/ioctl.h>
#include "pyramid_image.h"
#include "drv_cache_ctrl_defs.h"

typedef struct {
	unsigned char fil_mode;
	unsigned long rdct_ratio[4];
	unsigned char p_num;
	unsigned char p_clr_sel;
	unsigned long input_w_size;
	unsigned long input_h_size;
	unsigned long crop_image;
	unsigned long crop_pos_x;
	unsigned long crop_pos_y;
	unsigned long crop_size_w;
	unsigned long crop_size_h;
	unsigned long output_w_size[4];
	unsigned long output_h_size[4];
	pyramid_image input;
	pyramid_image output[4];
	ULONG buffer_cache_ctl;
} pyramid_param;

#define P_NUM_4PICS 0
#define P_NUM_1PIC  1

#define CROP_DISABLE 0
#define CROP_ENABLE  1

#define PYRAMID_IOCTL_MAGIC  0xB9
#define PYRAMID_IOCTL_SHRINK_1IMAGE _IOW(PYRAMID_IOCTL_MAGIC, 0, pyramid_param)
#define PYRAMID_IOCTL_GET_VERSION   _IO(PYRAMID_IOCTL_MAGIC, 1)
#define PYRAMID_IOCTL_INITIALIZE    _IO(PYRAMID_IOCTL_MAGIC, 2)

#endif /* __PYRAMID_IOCTL_H__ */
