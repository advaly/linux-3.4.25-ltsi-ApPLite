/*
 * linux/include/linux/applite/affine_param.h
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
#ifndef __AFFINE_PARAM_H__
#define __AFFINE_PARAM_H__

#include "basic_type.h"
#include "drv_cache_ctrl_defs.h"

#define AFFINE_INTERPOLATION_MODE_LINEAR        0
#define AFFINE_INTERPOLATION_MODE_NEAREST       1

#define AFFINE_PROCESS_DIRECTION_HORIZONTAL     0
#define AFFINE_PROCESS_DIRECTION_VERTICAL       1

struct affine_transformation_param {
	SINT dst_fd;
	ULONG dst_offset;
	ULONG dst_offset_x;
	ULONG dst_offset_y;
	ULONG dst_width;
	ULONG dst_height;
	ULONG dst_pitch;
	SINT src_fd;
	ULONG src_offset;
	ULONG src_width;
	ULONG src_height;
	ULONG src_pitch;
	ULONG src_depth;
	ULONG interpolation_mode;
	ULONG fill_value;
	ULONG process_direction;
	ULONG affn_p0;
	ULONG affn_p1;
	ULONG affn_p2;
	ULONG affn_p3;
	ULONG affn_p4;
	ULONG affn_p5;
	ULONG buffer_cache_ctl;
};

struct affine_table_param {
	SINT dst_fd;
	ULONG dst_offset;
	ULONG dst_offset_x;
	ULONG dst_offset_y;
	ULONG dst_width;
	ULONG dst_height;
	ULONG dst_pitch;
	SINT src_fd;
	ULONG src_offset;
	ULONG src_width;
	ULONG src_height;
	ULONG src_pitch;
	ULONG src_depth;
	ULONG interpolation_mode;
	ULONG fill_value;
	ULONG process_direction;
	SINT table_fd;
	ULONG table_offset;
	ULONG table_pitch;
	ULONG table_sampling_interval;
	ULONG buffer_cache_ctl;
};

struct affine_undistort_param {
	SINT dst_fd;
	ULONG dst_offset;
	ULONG dst_offset_x;
	ULONG dst_offset_y;
	ULONG dst_width;
	ULONG dst_height;
	ULONG dst_pitch;
	SINT src_fd;
	ULONG src_offset;
	ULONG src_width;
	ULONG src_height;
	ULONG src_pitch;
	ULONG src_depth;
	ULONG interpolation_mode;
	ULONG fill_value;
	ULONG process_direction;
	ULONG dist_p0;
	ULONG dist_p1;
	ULONG dist_p2;
	ULONG dist_p3;
	ULONG dist_p4;
	ULONG dist_p5;
	ULONG dist_p6;
	ULONG dist_p7;
	ULONG dist_p8;
	ULONG dist_p9;
	ULONG dist_p10;
	ULONG dist_p11;
	ULONG buffer_cache_ctl;
};

#endif /* __AFFINE_PARAM_H__ */
