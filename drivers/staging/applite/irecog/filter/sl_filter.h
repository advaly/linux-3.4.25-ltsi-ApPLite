/*
 * linux/drivers/staging/applite/irecog/filter/sl_filter.h
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
#ifndef _SL_FILTER_H
#define _SL_FILTER_H

#include <linux/applite/irecog/basic_type.h>

SINT sl_sobel_direction3x3(struct filter_dev *dev,
			   ULONG dst_physmem_addr,
			   ULONG src_physmem_addr,
			   UINT width, UINT height, UINT pitch,
			   USHORT threshold);

SINT sl_sobel_direction3x3_and_intensity(struct filter_dev *dev,
					 ULONG dst_dir_physmem_addr,
					 ULONG dst_int_physmem_addr,
					 ULONG src_physmem_addr,
					 UINT width, UINT height, UINT pitch);

SINT sl_sobel_direction3x3_and_intensity_with_threshold(struct filter_dev *dev,
							ULONG
							dst_dir_physmem_addr,
							ULONG
							dst_dir_nothr_physmem_addr,
							ULONG
							dst_int_physmem_addr,
							ULONG src_physmem_addr,
							UINT width, UINT height,
							UINT pitch,
							USHORT threshold);

SINT sl_filter_2d(struct filter_dev *dev,
		  ULONG dst_physmem_addr,
		  ULONG src_physmem_addr,
		  UINT width, UINT height, UINT pitch, UINT depth,
		  UINT filter_size, const SSHORT *coef, SSHORT normalizer);

SINT sl_average_image(struct filter_dev *dev,
		      ULONG dst_16bit_physmem_addr,
		      ULONG dst_8bit_physmem_addr,
		      ULONG src_physmem_addr,
		      UINT width, UINT height, UINT src_pitch, UINT dst_pitch);

SINT sl_correct_color(struct filter_dev *dev,
		      ULONG src_y_physmem_addr,
		      ULONG src_u_physmem_addr,
		      ULONG src_v_physmem_addr,
		      ULONG src_tonemapped_y_physmem_addr,
		      ULONG dst_u_physmem_addr,
		      ULONG dst_v_physmem_addr,
		      UINT width, UINT height, UINT pitch, UINT color_rate);
SINT sl_tonemapping_luma(struct filter_dev *dev,
			 ULONG dst_adr,
			 ULONG src_adr,
			 void *tonemap_adr,
			 UINT width, UINT height, UINT pitch, USHORT blend);

SINT sl_noise_reduction_y(struct filter_dev *dev,
			  ULONG in_src_physmem_addr,
			  ULONG in_blend_physmem_addr,
			  ULONG in_nr_physmem_addr,
			  ULONG in_md_physmem_addr,
			  ULONG out_md_physmem_addr,
			  ULONG out_nr_physmem_addr,
			  ULONG out_diff_flag_physmem_addr,
			  UINT width, UINT height, UINT pitch, UINT threshold);

SINT sl_noise_reduction_uv(struct filter_dev *dev,
			   ULONG in_color_physmem_addr,
			   ULONG in_nr_physmem_addr,
			   ULONG in_diff_flag_physmem_addr,
			   ULONG out_nr_physmem_addr,
			   UINT width, UINT height, UINT pitch);

SINT sl_tonemapping_init(struct filter_dev *dev);
void sl_tonemapping_finalize(struct filter_dev *dev);

#endif /* _SL_FILTER_H */
