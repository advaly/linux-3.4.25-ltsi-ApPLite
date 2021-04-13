/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/hog.c
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
#include <linux/io.h>
#include <linux/kernel.h>
#include "hog.h"
#include "hog_register_util.h"

static inline void add_instruction(gdmac_inst *inst, REG_32 reg_val,
				   unsigned long dst_adr)
{
	gdmac_write_register(inst, dst_adr, reg_val);
}

static void hog_write_register_func(struct hog_dev *dev, REG_32 reg_val)
{
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET(IRECOG_rcohog0_Function_Register_OFFS));
	if ((reg_val & 0x3) == 0) {
		*(dev->roi_mode) = HOG_MODE_DIC;
	} else if ((reg_val & 0x3) == 2) {
		*(dev->roi_mode) = HOG_MODE_FEATURE;
	} else if ((reg_val >> IRECOG_RCOHOG0_FUNCTION_REGISTER_ROI_MODE_SHIFT)
		   & 0x1) {
		*(dev->roi_mode) = HOG_MODE_SVM_REGION;
	} else {
		*(dev->roi_mode) = HOG_MODE_SVM_POSITION;
	}
}

static void hog_write_register_roi_stride(struct hog_dev *dev, REG_32 reg_val)
{
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Region_Of_Interest_Stride_Register_OFFS));
	*(dev->roi_num) = (reg_val & 0xffff) + 1;
}

static ULONG dd_HOG_set_roi_position_addr(ULONG dir_physmem_addr,
					  ULONG dir_pitch,
					  UINT roi_num,
					  struct roi_coord *roi_list)
{
	ULONG roi_addr;
	ULONG *roi_buff;
	ULONG x, y;
	int i;

	roi_buff = (ULONG *) roi_list;
	for (i = 0; i < roi_num; i++) {
		x = roi_list[i].x;
		y = roi_list[i].y;
		roi_buff[(i * 2)] = dir_physmem_addr + (y * dir_pitch) + x;
		roi_buff[(i * 2) + 1] = 0;	/* HBOFFSET */
	}
	if (roi_num == 1) {
		roi_addr = roi_buff[0];
	} else {
		roi_addr = virt_to_phys((void *)roi_buff);
	}
	return roi_addr;
}

static SINT dd_HOG_part_config_dictionary_base(struct hog_dev *dev,
					       /* func */
					       UINT dict_num,
					       /* cell_fmt */
					       UINT cell_num_x,
					       UINT cell_num_y,
					       UINT cell_width,
					       UINT cell_height)
{
	REG_32 reg_val;

	/* func */
	dd_HOG_register_pack_func__dict_num(dev->func, dict_num);

	/* cell_fmt */
	reg_val = dd_HOG_register_pack_cell_format(cell_num_x,
						   cell_num_y,
						   cell_width, cell_height);

	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET(IRECOG_rcohog0_Cell_Format_Register_OFFS));

	/* roi_size */
	reg_val = dd_HOG_register_pack_roi_size(cell_num_x,
						cell_num_y,
						cell_width, cell_height);

	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Region_Of_Interest_Size_Register_OFFS));

	return 0;
}

static SINT dd_HOG_part_config_load_dictionary(struct hog_dev *dev,
					       ULONG format_physmem_addr,
					       ULONG weight_physmem_addr,
					       /* src1_size */
					       UINT format_size,
					       /* src0_size */
					       UINT weight_size)
{
	REG_32 reg_val;

	/*func */
	dd_HOG_register_pack_func__func_mode(dev->func, HOG_FUNC_MODE_DIC);

	add_instruction(dev->inst, weight_physmem_addr,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Source_0_Address_Register_OFFS));
	add_instruction(dev->inst, format_physmem_addr,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Source_1_Address_Register_OFFS));

	reg_val =
	    dd_HOG_register_pack_src_size_dict(weight_size / 2,
					       HOG_SRC_FMT_16BIT);
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET(IRECOG_rcohog0_Source_0_Size_Register_OFFS));

	reg_val =
	    dd_HOG_register_pack_src_size_dict(format_size / 8,
					       HOG_SRC_FMT_64BIT);
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET(IRECOG_rcohog0_Source_1_Size_Register_OFFS));

	/* Not Used ROI_STRIDE, SRC0_LPTCH, SRC1_LPTCH, DST0_SIZE */

	return 0;
}

static VOID dd_HOG_part_config_classify_base__(struct hog_dev *dev,
					       /* src0_lptch */
					       ULONG dir_paddr, UINT dir_pitch,
					       /* src0_size */
					       UINT dir_width,
					       UINT dir_height,
					       UINT dir_half_offset,
					       UINT dir_format, ULONG dst_paddr)
{
	REG_32 reg_val;

	/* func */
	dd_HOG_register_pack_func__hog_mode(dev->func, HOG_MODE_COHOG);

	/* src0_addr */
	add_instruction(dev->inst, dir_paddr,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Source_0_Address_Register_OFFS));

	/* src0_lptch */
	switch (dir_format) {
	case HOG_SRC_FMT_4BIT:
		reg_val = dir_pitch / 2;
		break;
	case HOG_SRC_FMT_8BIT:	/*default */
	default:
		reg_val = dir_pitch;
		break;
	}
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Source_0_Line_Pitch_Register_OFFS));

	/* src0_size */
	reg_val =
	    dd_HOG_register_pack_src_size(dir_width, dir_height,
					  dir_half_offset, dir_format);
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET(IRECOG_rcohog0_Source_0_Size_Register_OFFS));

	/* Not Used SRC1_LPTCH, SRC1_SIZE */

	/* dst0_addr */
	add_instruction(dev->inst, dst_paddr,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Destination_0_Address_Register_OFFS));
}

static SINT dd_HOG_part_config_classify_region(struct hog_dev *dev,
					       /* dictionary num */
					       UINT dict_num,
					       /* roi_stride */
					       UINT roi_num_x,
					       UINT roi_num_y,
					       UINT roi_stride_x,
					       UINT roi_stride_y,
					       /* src0_addr */
					       ULONG dir_physmem_addr,
					       /* src0_lptch */
					       UINT dir_pitch,
					       /* src0_size */
					       UINT dir_width,
					       UINT dir_height,
					       UINT dir_half_offset,
					       UINT dir_format,
					       /* dst0_addr */
					       ULONG dst_physmem_addr)
{
	REG_32 reg_val;

	dd_HOG_part_config_classify_base__(dev,
					   dir_physmem_addr,
					   dir_pitch,
					   dir_width, dir_height,
					   dir_half_offset, dir_format,
					   dst_physmem_addr);

	/* func */
	dd_HOG_register_pack_func__func_mode(dev->func, HOG_FUNC_MODE_SVM);
	dd_HOG_register_pack_func__roi_mode(dev->func, HOG_ROI_MODE_REGION);

	/* roi_stride */
	reg_val =
	    dd_HOG_register_pack_roi_stride_region(roi_num_x, roi_num_y,
						   roi_stride_x, roi_stride_y);
	hog_write_register_roi_stride(dev, reg_val);

	/* dst0_size */
	reg_val = ((roi_num_x * roi_num_y) * dict_num) - 1;
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Destination_0_Format_Register_OFFS));

	return 0;
}

static SINT dd_HOG_part_config_classify_position(struct hog_dev *dev,
						 /* dictionary num */
						 UINT dict_num,
						 /* roi_stride */
						 UINT roi_num,
						 /* src0_lptch */
						 ULONG dir_physmem_addr,
						 UINT dir_pitch,
						 /* src0_size */
						 UINT dir_width,
						 UINT dir_height,
						 UINT dir_half_offset,
						 UINT dir_format,
						 ULONG dst_physmem_addr)
{
	REG_32 reg_val;

	dd_HOG_part_config_classify_base__(dev,
					   dir_physmem_addr,
					   dir_pitch,
					   dir_width, dir_height,
					   dir_half_offset, dir_format,
					   dst_physmem_addr);

	/* func */
	dd_HOG_register_pack_func__func_mode(dev->func, HOG_FUNC_MODE_SVM);
	dd_HOG_register_pack_func__roi_mode(dev->func, HOG_ROI_MODE_POSITION);

	/* roi_stride */
	reg_val = dd_HOG_register_pack_roi_stride_position(roi_num, 0, 0);
	hog_write_register_roi_stride(dev, reg_val);

	/* dst0_size */
	reg_val = (roi_num * dict_num) - 1;
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Destination_0_Format_Register_OFFS));

	return 0;
}

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
				   UINT weight_size)
{
	*(dev->func) = 0;	/* reset */

	dd_HOG_part_config_dictionary_base(dev,
					   dict_num, cell_num_x, cell_num_y,
					   cell_width, cell_height);

	dd_HOG_part_config_load_dictionary(dev,
					   format_physmem_addr,
					   weight_physmem_addr, format_size,
					   weight_size);

	hog_write_register_func(dev, *(dev->func));

	return 0;
}

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
				   ULONG dst_physmem_addr)
{
	/* src0_size */
	UINT dir_half_offset = 0;
	UINT dir_format = HOG_SRC_FMT_8BIT;

	*(dev->func) = 0;	/* reset */

	dd_HOG_part_config_dictionary_base(dev,
					   dict_num, cell_num_x, cell_num_y,
					   cell_width, cell_height);

	dd_HOG_part_config_classify_region(dev,
					   dict_num,
					   roi_num_x, roi_num_y,
					   roi_stride_x, roi_stride_y,
					   dir_physmem_addr,
					   dir_pitch,
					   dir_width, dir_height,
					   dir_half_offset, dir_format,
					   dst_physmem_addr);

	hog_write_register_func(dev, *(dev->func));

	return 0;
}

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
				     UINT dir_pitch, ULONG dst_physmem_addr)
{
	/* src0_size */
	UINT dir_width;
	UINT dir_height;
	UINT dir_half_offset = 0;
	UINT dir_format = HOG_SRC_FMT_8BIT;
	ULONG dir_roi_addr;

	dir_width = cell_num_x * cell_width;
	dir_height = cell_num_y * cell_height;

	dir_roi_addr =
	    dd_HOG_set_roi_position_addr(dir_physmem_addr, dir_pitch, roi_num,
					 roi_list);

	*(dev->func) = 0;	/* reset */

	dd_HOG_part_config_dictionary_base(dev,
					   dict_num, cell_num_x, cell_num_y,
					   cell_width, cell_height);
	dd_HOG_part_config_classify_position(dev, dict_num, roi_num,
					     dir_roi_addr, dir_pitch, dir_width,
					     dir_height, dir_half_offset,
					     dir_format, dst_physmem_addr);

	hog_write_register_func(dev, *(dev->func));

	return 0;
}

void hog_clear_int(struct hog_dev *dev)
{
	add_instruction(dev->inst, HOG_CLEAR_BITS,
			(unsigned int)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Interrupt_Status_Register_OFFS));
}

SINT dd_HOG_send_request(struct hog_dev *dev)
{
	/* Clear Int Mask. */
	hog_clear_int(dev);

	/* Set Int Mask, Currently No Parameter Trans. */
	add_instruction(dev->inst, HOG_INTMASK_NORMAL,
			(unsigned long)dev->reg_base +
			HOG_OFFSET
			(IRECOG_rcohog0_Interrupt_Mask_Register_OFFS));

	/* Kick Hog */
	add_instruction(dev->inst, 0x1,
			(unsigned long)dev->reg_base +
			HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));

	return 0;
}
