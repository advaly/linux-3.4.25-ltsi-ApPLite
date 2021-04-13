/*
 * linux/include/linux/applite/filter_param.h
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
#ifndef __FILTER_PARAM_H__
#define __FILTER_PARAM_H__

#include "basic_type.h"

#define FILTER_SOBEL_IMAGE_OUT_THR              0
#define FILTER_SOBEL_IMAGE_OUT_NOTHR_INTENSITY  1
#define FILTER_SOBEL_IMAGE_OUT_ALL              2

struct filter_sobel_direction3x3_param {
	UCHAR dst_select;
	ULONG dst_dir_thr_adr;
	ULONG dst_dir_nothr_adr;
	ULONG dst_int_adr;
	ULONG src_adr;
	ULONG width;
	ULONG height;
	ULONG pitch;
	USHORT threshold;
	ULONG buffer_cache_ctl;
};

struct filter_image_smoothing_param {
	ULONG dst_adr;
	ULONG src_adr;
	ULONG width;
	ULONG height;
	ULONG pitch;
	ULONG depth;
	ULONG filter_size;
	SSHORT *coef;
	SSHORT normalizer;
	ULONG buffer_cache_ctl;
};

struct filter_average_image_param {
	ULONG dst_16bit_adr;
	ULONG dst_8bit_adr;
	ULONG src_adr;
	ULONG width;
	ULONG height;
	ULONG src_pitch;
	ULONG dst_pitch;
	ULONG buffer_cache_ctl;
};

struct filter_correct_color_param {
	SINT src_y_fd;
	UINT src_y_offset;
	SINT src_u_fd;
	UINT src_u_offset;
	SINT src_v_fd;
	UINT src_v_offset;
	SINT src_tonemapped_y_fd;
	UINT src_tonemapped_y_offset;
	UINT width;
	UINT height;
	UINT pitch;
	SINT dst_u_fd;
	UINT dst_u_offset;
	SINT dst_v_fd;
	UINT dst_v_offset;
	UINT color_rate;
	ULONG buffer_cache_ctl;
};

struct filter_tonemapping_luma_param {
	SINT src_fd;
	UINT src_offset;
	UINT width;
	UINT pitch;
	UINT height;
	UINT div_num;
	UINT div_sel;
	UINT blend;
	VOID *tonemap_addr_virt;
	SINT dst_fd;
	UINT dst_offset;
	ULONG buffer_cache_ctl;
};

struct filter_noise_reduction_y_param {
	UINT width;
	UINT pitch;
	UINT height;
	UINT threshold;

	SINT in_src_fd;
	UINT in_src_offset;
	SINT in_blend_fd;
	UINT in_blend_offset;
	SINT in_md_fd;
	UINT in_md_offset;
	UINT in_nr_fd;
	UINT in_nr_offset;

	SINT out_md_fd;
	UINT out_md_offset;
	SINT out_nr_fd;
	UINT out_nr_offset;
	SINT out_diff_flag_fd;
	UINT out_diff_flag_offset;

	ULONG buffer_cache_ctl;
};

struct filter_noise_reduction_uv_param {
	UINT width;
	UINT pitch;
	UINT height;

	SINT in_color_fd;
	UINT in_color_offset;
	SINT in_nr_fd;
	UINT in_nr_offset;
	SINT in_diff_flag_fd;
	UINT in_diff_flag_offset;

	SINT out_nr_fd;
	UINT out_nr_offset;

	ULONG buffer_cache_ctl;
};

#endif /* __FILTER_PARAM_H__ */
