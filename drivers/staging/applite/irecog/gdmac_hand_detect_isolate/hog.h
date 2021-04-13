/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/hog.h
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
#ifndef __HOG_H__
#define __HOG_H__

#include <linux/applite/irecog/gdmac_hand_detect_isolate_ioctl.h>

#include "gdmac_instructions.h"
#include "hog_public.h"

struct hog_dev {
	gdmac_inst *inst;
	unsigned long reg_base;
	int *roi_mode;
	int *roi_num;
	unsigned int *func;
};

struct dict_dev {
	unsigned long reg_base;
};

void hog_clear_int(struct hog_dev *dev);
SINT dd_HOG_send_request(struct hog_dev *dev);
SINT dd_HOG_config_load_dictionary(struct hog_dev *dev,
				   /* func */
				   UINT dict_num,
				   /* cell_fmt */
				   UINT cell_num_x,
				   UINT cell_num_y,
				   UINT cell_width,
				   UINT cell_height,
				   ULONG format_physmem_addr,
				   ULONG weight_physmem_addr,
				   /* src1_size */
				   UINT format_size,
				   /* src0_size */
				   UINT weight_size);
SINT dd_HOG_config_classify_position(struct hog_dev *dev,
				     /* func */
				     UINT dict_num,
				     /* cell_fmt */
				     UINT cell_num_x,
				     UINT cell_num_y,
				     UINT cell_width, UINT cell_height,
				     /* roi_stride */
				     UINT roi_num, struct roi_coord *roi_list,
				     /* src0_lptch */
				     ULONG dir_physmem_addr,
				     UINT dir_pitch, ULONG dst_physmem_addr);

SINT dd_HOG_config_classify_region(struct hog_dev *dev,
				   /* func */
				   UINT dict_num,
				   /* cell_fmt */
				   UINT cell_num_x,
				   UINT cell_num_y,
				   UINT cell_width, UINT cell_height,
				   /* roi_stride */
				   UINT roi_num_x,
				   UINT roi_num_y,
				   UINT roi_stride_x, UINT roi_stride_y,
				   /* src0_addr */
				   ULONG dir_physmem_addr,
				   /* src0_lptch */
				   UINT dir_pitch,
				   /* src0_size */
				   UINT dir_width, UINT dir_height,
				   /* dst0_addr */
				   ULONG dst_physmem_addr);

#endif /* __HOG_H__ */
