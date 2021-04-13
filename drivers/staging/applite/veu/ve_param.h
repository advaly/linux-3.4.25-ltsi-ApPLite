/*
 * drivers/staging/applite/veu/ve_param.h
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2013
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

#ifndef __VE_PARAM_H__
#define __VE_PARAM_H__

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif

/* fps */
enum ve_frame_rate {
	VE_FPS_11_98HZ,
	VE_FPS_14_98HZ,
	VE_FPS_15HZ,
	VE_FPS_23_97HZ,
	VE_FPS_24HZ,
	VE_FPS_25HZ,
	VE_FPS_29_97HZ,
	VE_FPS_30HZ,
	VE_FPS_47_95HZ,
	VE_FPS_48HZ,
	VE_FPS_50HZ,
	VE_FPS_59_94HZ,
	VE_FPS_60HZ,
};

/* parameters for encoding */
struct ve_param {
	uint32_t output_mode;
	uint32_t profile;
	uint32_t level;
	uint32_t horizontal_pixels;
	uint32_t vertical_pixels;
	enum ve_frame_rate frame_rate;
	uint32_t kbps;
	uint32_t max_kbps;
	uint32_t cpb_size_kbits;
	uint32_t rate_control_mode;
	uint32_t m;
	uint32_t n;
	uint32_t idr_freq;
	uint32_t picture_struct;
	uint32_t slice_num_minus1;
	uint32_t scaling_matrix;
	uint32_t entropy_coding;
	uint32_t weighted_pred;
	uint32_t reference_b;
	uint32_t inter_view_pred;
	uint32_t vui_parameters;
	uint32_t sei0;
	/* vui parameters */
	uint32_t aspect_ratio_info_present_flag;
	uint32_t aspect_ratio_idc;
	uint32_t sar_width;
	uint32_t sar_height;
	uint32_t overscan_info_present_flag;
	uint32_t overscan_appropriate_flag;
	uint32_t video_signal_type_present_flag;
	uint32_t video_format;
	uint32_t video_full_range_flag;
	uint32_t colour_description_present_flag;
	uint32_t colour_primaries;
	uint32_t transfer_characteristics;
	uint32_t matrix_coefficients;
	uint32_t chroma_loc_info_present_flag;
	uint32_t chroma_sample_loc_type_top_field;
	uint32_t chroma_sample_loc_type_bottom_field;
	uint32_t timing_info_present_flag;
	uint32_t num_units_in_tick;
	uint32_t time_scale;
	uint32_t fixed_frame_rate_flag;
	uint32_t nal_hrd_parameters_present_flag;
	uint32_t vcl_hrd_parameters_present_flag;
	uint32_t low_delay_hrd_flag;
	uint32_t pic_struct_present_flag;
	uint32_t bitstream_restriction_flag;
};

#endif /* __VE_PARAM_H__ */

