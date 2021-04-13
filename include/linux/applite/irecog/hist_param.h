/*
 * linux/include/linux/applite/hist_param.h
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
#ifndef __HIST_PARAM_H__
#define __HIST_PARAM_H__

#include "basic_type.h"
#include "drv_cache_ctrl_defs.h"

#define HIST_BIN_NUM_256  0
#define HIST_BIN_NUM_512  1
#define HIST_BIN_NUM_1024 2

#define HIST_BIN_CLR_DISABLE 0
#define HIST_BIN_CLR_ENABLE  1

#define HIST_OUTL_COUNT_DISABLE 0
#define HIST_OUTL_COUNT_ENABLE  1

#define HIST_FORMAT_U8  0
#define HIST_FORMAT_U16 1
#define HIST_FORMAT_S8  2
#define HIST_FORMAT_S16 3

struct hist_param {
	SINT dst_fd;
	UINT dst_offset;
	SINT src_fd;
	UINT src_offset;

	UINT src_width;
	UINT src_height;
	UINT src_pitch;
	UINT src_type;

	UINT src_x_sample_interval;
	UINT src_y_sample_interval;

	UINT outlier;
	UINT clear;
	UINT bin_num;

	UINT index_shift;
	SINT index_offset;

	ULONG buffer_cache_ctl;
};

struct hist_scorevoting_param {
	SINT dst_fd;
	UINT dst_offset;
	SINT src_fd;
	UINT src_offset;
	SINT score_fd;
	UINT score_offset;

	UINT src_width;
	UINT src_height;
	UINT src_pitch;
	UINT src_type;

	UINT src_x_sample_interval;
	UINT src_y_sample_interval;

	UINT score_width;
	UINT score_height;
	UINT score_pitch;
	UINT score_type;

	UINT score_x_sample_interval;
	UINT score_y_sample_interval;

	UINT outlier;
	UINT clear;
	UINT bin_num;

	UINT index_shift;
	SINT index_offset;

	ULONG buffer_cache_ctl;
};

#endif /* _HIST_PARAM_H__ */
