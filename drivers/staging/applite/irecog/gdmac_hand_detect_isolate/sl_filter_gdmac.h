/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/sl_filter_gdmac.h
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
#ifndef _SL_FILTER_GDMAC_H
#define _SL_FILTER_GDMAC_H

#include <linux/applite/irecog/basic_type.h>

SINT sl_gdmac_sobel_direction3x3(struct filter_dev *dev,
				 ULONG dst_physmem_addr,
				 ULONG src_physmem_addr,
				 UINT width, UINT height, UINT pitch,
				 USHORT threshold);

SINT sl_gdmac_sobel_direction3x3_and_intensity(struct filter_dev *dev,
					       ULONG dst_dir_physmem_addr,
					       ULONG dst_int_physmem_addr,
					       ULONG src_physmem_addr,
					       UINT width, UINT height,
					       UINT pitch);

SINT sl_gdmac_sobel_direction3x3_and_intensity_with_threshold(struct filter_dev
							      *dev,
							      ULONG
							      dst_dir_physmem_addr,
							      ULONG
							      dst_dir_nothr_physmem_addr,
							      ULONG
							      dst_int_physmem_addr,
							      ULONG
							      src_physmem_addr,
							      UINT width,
							      UINT height,
							      UINT pitch,
							      USHORT threshold);

SINT sl_gdmac_filter_2d(struct filter_dev *dev,
			ULONG dst_physmem_addr,
			ULONG src_physmem_addr,
			UINT width, UINT height, UINT pitch, UINT depth,
			UINT filter_size, const SSHORT *coef,
			SSHORT normalizer);

SINT sl_gdmac_average_image(struct filter_dev *dev,
			    ULONG dst_16bit_physmem_addr,
			    ULONG dst_8bit_physmem_addr,
			    ULONG src_physmem_addr,
			    UINT width,
			    UINT height, UINT src_pitch, UINT dst_pitch);

#endif /* _SL_FILTER_H */
