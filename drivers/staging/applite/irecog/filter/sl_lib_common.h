/*
 * linux/drivers/staging/applite/irecog/filter/sl_lib_common.h
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
#ifndef _SL_LIB_INTERNAL_COMMON_H_
#define _SL_LIB_INTERNAL_COMMON_H_

#define SL_MAX_IMG_WIDTH	1280
#define SL_MAX_IMG_HEIGHT	1024
#define SL_MAX_IMG_PITCH	1280

#define SL_MIN_IMG_WIDTH		1
#define SL_MIN_IMG_HEIGHT		1
#define SL_MIN_IMG_PITCH		16

#define SL_MIN_IMG_FILTER_WIDTH		65
#define SL_MIN_IMG_FILTER_HEIGHT	2
#define SL_MIN_IMG_FILTER_PITCH		80

/* Filter size = 3 */
#define SL_MIN_IMG_FILTER_3_WIDTH		66
#define SL_MIN_IMG_FILTER_3_HEIGHT		(SL_MIN_IMG_FILTER_HEIGHT + 2)
#define SL_MIN_IMG_FILTER_3_PITCH		80

/* Filter size = 5 */
#define SL_MIN_IMG_FILTER_5_WIDTH		67
#define SL_MIN_IMG_FILTER_5_HEIGHT		(SL_MIN_IMG_FILTER_HEIGHT + 4)
#define SL_MIN_IMG_FILTER_5_PITCH		80

/* Filter size = 7 */
#define SL_MIN_IMG_FILTER_7_WIDTH		68
#define SL_MIN_IMG_FILTER_7_HEIGHT		(SL_MIN_IMG_FILTER_HEIGHT + 6)
#define SL_MIN_IMG_FILTER_7_PITCH		80

/* Filter size = 9 */
#define SL_MIN_IMG_FILTER_9_WIDTH		69
#define SL_MIN_IMG_FILTER_9_HEIGHT		(SL_MIN_IMG_FILTER_HEIGHT + 8)
#define SL_MIN_IMG_FILTER_9_PITCH		80

/* Filter size = 11 */
#define SL_MIN_IMG_FILTER_11_WIDTH		70
#define SL_MIN_IMG_FILTER_11_HEIGHT		(SL_MIN_IMG_FILTER_HEIGHT + 10)
#define SL_MIN_IMG_FILTER_11_PITCH		80

/* Filter size = 13 */
#define SL_MIN_IMG_FILTER_13_WIDTH		71
#define SL_MIN_IMG_FILTER_13_HEIGHT		(SL_MIN_IMG_FILTER_HEIGHT + 12)
#define SL_MIN_IMG_FILTER_13_PITCH		80

/* Filter size = 15 */
#define SL_MIN_IMG_FILTER_15_WIDTH		72
#define SL_MIN_IMG_FILTER_15_HEIGHT		(SL_MIN_IMG_FILTER_HEIGHT + 14)
#define SL_MIN_IMG_FILTER_15_PITCH		80

#define SL_MAX_CENTER_X	(1279.0F)
#define SL_MAX_CENTER_Y	(1023.0F)
#define SL_MIN_CENTER_X	(0.0F)
#define SL_MIN_CENTER_Y	(0.0F)

#define SL_MAX_NOTIFY_FLAG 1
#define SL_MAX_NORMALIZE    16

#define SL_DEPTH_COLOR_8    8
#define SL_DEPTH_COLOR_16   16

#endif
