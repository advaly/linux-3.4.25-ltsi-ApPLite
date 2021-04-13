/*
 * linux/include/linux/applite/gdmac_pyramid_ioctl.h
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
#ifndef __GDMAC_PYRAMID_IOCTL_H__
#define __GDMAC_PYRAMID_IOCTL_H__

#include <linux/ioctl.h>
#include "pyramid_image.h"
#include "drv_cache_ctrl_defs.h"

#define GDMAC_PYRAMID_OUT_NUM 12

#define GDMAC_PYRAMID_IN_W    640	/* input */
#define GDMAC_PYRAMID_IN_H    480
#define GDMAC_PYRAMID_OUT0_W  538	/* output0 */
#define GDMAC_PYRAMID_OUT0_H  403
#define GDMAC_PYRAMID_OUT1_W  452	/* output1 */
#define GDMAC_PYRAMID_OUT1_H  339
#define GDMAC_PYRAMID_OUT2_W  380	/* output2 */
#define GDMAC_PYRAMID_OUT2_H  285
#define GDMAC_PYRAMID_OUT3_W  320	/* output3 */
#define GDMAC_PYRAMID_OUT3_H  240
#define GDMAC_PYRAMID_OUT4_W  269	/* output4 */
#define GDMAC_PYRAMID_OUT4_H  201
#define GDMAC_PYRAMID_OUT5_W  226	/* output5 */
#define GDMAC_PYRAMID_OUT5_H  169
#define GDMAC_PYRAMID_OUT6_W  190	/* output6 */
#define GDMAC_PYRAMID_OUT6_H  142
#define GDMAC_PYRAMID_OUT7_W  160	/* output7 */
#define GDMAC_PYRAMID_OUT7_H  120
#define GDMAC_PYRAMID_OUT8_W  134	/* output8 */
#define GDMAC_PYRAMID_OUT8_H  100
#define GDMAC_PYRAMID_OUT9_W  113	/* output9 */
#define GDMAC_PYRAMID_OUT9_H   84
#define GDMAC_PYRAMID_OUT10_W  95	/* output10 */
#define GDMAC_PYRAMID_OUT10_H  71
#define GDMAC_PYRAMID_OUT11_W  80	/* output11 */
#define GDMAC_PYRAMID_OUT11_H  60

typedef struct {
	unsigned char fil_mode;
	unsigned char p_clr_sel;
	pyramid_image input;
	pyramid_image output[GDMAC_PYRAMID_OUT_NUM];
	unsigned long buffer_cache_ctl;
} gdmac_pyramid;

#define GDMAC_PYRAMID_REG_TYPE_SECURE     0
#define GDMAC_PYRAMID_REG_TYPE_NON_SECURE 1

#define GDMAC_PYRAMID_IOCTL_MAGIC  0x00
#define GDMAC_IOCTL_PYRAMID_IMAGES        _IOW(GDMAC_PYRAMID_IOCTL_MAGIC, 4, gdmac_pyramid)
#define GDMAC_IOCTL_PYRAMID_GET_VERSION   _IO(GDMAC_PYRAMID_IOCTL_MAGIC, 5)
#define GDMAC_IOCTL_PYRAMID_SET_REG_TYPE  _IOW(GDMAC_PYRAMID_IOCTL_MAGIC, 6, uint32_t)
#define GDMAC_IOCTL_PYRAMID_INITIALIZE    _IO(GDMAC_PYRAMID_IOCTL_MAGIC, 7)

#endif /* __GDMAC_PYRAMID_IOCTL_H__ */
