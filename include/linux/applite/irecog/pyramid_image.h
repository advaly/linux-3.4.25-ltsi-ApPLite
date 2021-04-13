/*
 * linux/include/linux/applite/pyramid_image.h
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
#ifndef __PYRAMID_IMAGE_H__
#define __PYRAMID_IMAGE_H__

#define FIL_MODE_8TAP_8OVS   0
#define FIL_MODE_4TAP_16OVS  1
#define FIL_MODE_2TAP_128OVS 2
#define FIL_MODE_2TAP_256OVS 3
#define FIL_MODE_2TAP_512OVS 4
#define FIL_MODE_NEAREST     5

#define P_CLR_SEL_Y     0
#define P_CLR_SEL_CBCR  1
#define P_CLR_SEL_YCBCR 2

typedef struct {
	unsigned long y_adr;
	unsigned long cb_adr;
	unsigned long cr_adr;
	unsigned long y_pitch;
	unsigned long cb_pitch;
	unsigned long cr_pitch;
} pyramid_image;

#endif /* __PYRAMID_IMAGE_H__ */
