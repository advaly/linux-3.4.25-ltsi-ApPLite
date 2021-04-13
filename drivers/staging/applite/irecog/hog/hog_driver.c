/*
 * linux/drivers/staging/applite/irecog/hog/hog_driver.c
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
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>	/* create_proc_entry */
#include <linux/uaccess.h>	/* copy_from_user */
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/semaphore.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/platform_data/applite_irecog.h>

#include <linux/applite/irecog/hog_ioctl.h>
#include <linux/applite/irecog/hog_param.h>

#include "hog_register_util.h"
#include "hog_driver.h"
#include "drv_cache.h"
#include "drv_signal.h"
#include "drv_polling.h"

static const char *drv_hog_version = DRV_HOG_VERSION_STR;

static int hog_major = HOG_MAJOR;
static int hog_minor = HOG_MINOR;
static int hog_nr_devs = HOG_NR_DEVS;

static unsigned long hog0_base = HOG0_BASE;
static unsigned long hog0_size = HOG0_SIZE;
static int hog0_irq = HOG0_IRQ;
static unsigned long hog1_base = HOG1_BASE;
static unsigned long hog1_size = HOG1_SIZE;
static int hog1_irq = HOG1_IRQ;
static unsigned long dict_base = DICT_BASE;
static unsigned long dict_size = DICT_SIZE;

module_param(hog_major, int, S_IRUGO | S_IWUSR);
module_param(hog_minor, int, S_IRUGO | S_IWUSR);
module_param(hog_nr_devs, int, S_IRUGO | S_IWUSR);

module_param(hog0_base, ulong, S_IRUGO | S_IWUSR);
module_param(hog0_size, ulong, S_IRUGO | S_IWUSR);
module_param(hog0_irq, int, S_IRUGO | S_IWUSR);
module_param(hog1_base, ulong, S_IRUGO | S_IWUSR);
module_param(hog1_size, ulong, S_IRUGO | S_IWUSR);
module_param(hog1_irq, int, S_IRUGO | S_IWUSR);
module_param(dict_base, ulong, S_IRUGO | S_IWUSR);
module_param(dict_size, ulong, S_IRUGO | S_IWUSR);

static struct hog_dev *hog0_devices;
static struct hog_dev *hog1_devices;
static struct dict_dev *dict_devices;
static struct class *phog_class;

static int hog0_status = HOG_EXE_DONE;
static wait_queue_head_t wq0;
static struct semaphore sem0;
static int hog0_roi_mode = HOG_MODE_DIC;
static int hog0_roi_num;
static unsigned int hog0_func;
static int hog1_status = HOG_EXE_DONE;
static wait_queue_head_t wq1;
static struct semaphore sem1;
static int hog1_roi_mode = HOG_MODE_DIC;
static int hog1_roi_num;
static unsigned int hog1_func;

static atomic_t refcount = ATOMIC_INIT(0);

struct hog_drvdata {
	struct hog_dev *hog0_devices;
	struct hog_dev *hog1_devices;
	struct dict_dev *dict_devices;
};

static int check_cache_param(ULONG flag)
{
	if ((flag != DRV_CACHE_FLUSH_ALL) && (flag != DRV_NO_CACHE_CTL)) {
		pr_err("%s: invalid buffer_cache_ctl:%lu\n", HOG_NAME, flag);
		return -1;
	}

	return 0;
}

static long hog_reset(struct hog_dev *dev);

static int hog_runtime_suspend(struct device *dev)
{
	unsigned int ret;
	struct platform_data *pdata = dev->platform_data;
	struct platform_device *pdev = to_platform_device(dev);
	struct hog_drvdata *priv = platform_get_drvdata(pdev);

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	iowrite32(IRECOG_RCOHOG0_CONTROL_REGISTER_RST_MASK,
		  priv->hog0_devices->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));

	ret = drv_wait_register(priv->hog0_devices->reg_base +
				HOG_OFFSET
				(IRECOG_rcohog0_Control_Register_OFFS),
				IRECOG_RCOHOG0_CONTROL_REGISTER_CMD_MASK, 0x00,
				DRV_WAIT_REG_TIMEOUT);
	if ((ret & IRECOG_RCOHOG0_CONTROL_REGISTER_CMD_MASK) != 0x0) {
		pr_err("%s: timeout occured\n", HOG_NAME);
		return -EIO;
	}

	iowrite32(IRECOG_RCOHOG1_CONTROL_REGISTER_RST_MASK,
		  priv->hog1_devices->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));

	ret = drv_wait_register(priv->hog1_devices->reg_base +
				HOG_OFFSET
				(IRECOG_rcohog0_Control_Register_OFFS),
				IRECOG_RCOHOG1_CONTROL_REGISTER_CMD_MASK, 0x00,
				DRV_WAIT_REG_TIMEOUT);
	if ((ret & IRECOG_RCOHOG1_CONTROL_REGISTER_CMD_MASK) != 0x0) {
		pr_err("%s: timeout occured\n", HOG_NAME);
		return -EIO;
	}

	clock_enable(APPLITE_IRECOG_HOG, APPLITE_IRECOG_CLOCK_DISABLE);
	return 0;
}

static int hog_runtime_resume(struct device *dev)
{
	struct platform_data *pdata = dev->platform_data;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	clock_enable(APPLITE_IRECOG_HOG, APPLITE_IRECOG_CLOCK_ENABLE);
	return 0;
}

#if 0
static void hog_cache_flush_dict(struct hog_dict_param *param)
{
	drv_cache_flush(param->format_adr, param->format_size);
	drv_cache_flush(param->weight_adr, param->weight_size);
}

static void hog_cache_flush_svm_position(struct hog_svm_position_param *param,
					 struct roi_coord *roi_list)
{
	drv_cache_flush(param->dir_adr, param->dir_pitch * param->dir_height);
	drv_cache_flush(virt_to_phys(roi_list),
			param->roi_num * sizeof(struct roi_coord));
}
#endif

static void hog_write_register_func(struct hog_dev *dev, REG_32 reg_val)
{
	iowrite32(reg_val,
		  dev->reg_base +
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
	iowrite32(reg_val,
		  dev->reg_base +
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
	iowrite32(reg_val,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Cell_Format_Register_OFFS));

	/* roi_size */
	reg_val = dd_HOG_register_pack_roi_size(cell_num_x,
						cell_num_y,
						cell_width, cell_height);
	iowrite32(reg_val,
		  dev->reg_base +
		  HOG_OFFSET
		  (IRECOG_rcohog0_Region_Of_Interest_Size_Register_OFFS));

	return 0;
}

static SINT dd_HOG_part_config_load_dictionary(struct hog_dev *dev,
					       ULONG format_physmem_addr,
					       ULONG weight_physmem_addr,
					       /* src1_size */
					       UINT format_size,	/* [byte] */
					       /* src0_size */
					       UINT weight_size	/* [byte] */
    )
{
	REG_32 reg_val;

	/* func */
	dd_HOG_register_pack_func__func_mode(dev->func, HOG_FUNC_MODE_DIC);

	iowrite32(weight_physmem_addr,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Source_0_Address_Register_OFFS));
	iowrite32(format_physmem_addr,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Source_1_Address_Register_OFFS));

	reg_val =
	    dd_HOG_register_pack_src_size_dict(weight_size / 2,
					       HOG_SRC_FMT_16BIT);
	iowrite32(reg_val,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Source_0_Size_Register_OFFS));

	reg_val =
	    dd_HOG_register_pack_src_size_dict(format_size / 8,
					       HOG_SRC_FMT_64BIT);
	iowrite32(reg_val,
		  dev->reg_base +
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
	iowrite32(dir_paddr,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Source_0_Address_Register_OFFS));

	/* src0_lptch */
	switch (dir_format) {
	case HOG_SRC_FMT_4BIT:
		reg_val = dir_pitch / 2;
		break;
	case HOG_SRC_FMT_8BIT:	/* default */
	default:
		reg_val = dir_pitch;
		break;
	}
	iowrite32(reg_val,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Source_0_Line_Pitch_Register_OFFS));

	/* src0_size */
	reg_val =
	    dd_HOG_register_pack_src_size(dir_width, dir_height,
					  dir_half_offset, dir_format);
	iowrite32(reg_val,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Source_0_Size_Register_OFFS));

	/* Not Used SRC1_LPTCH, SRC1_SIZE */

	/* dst0_addr */
	iowrite32(dst_paddr,
		  dev->reg_base +
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
	iowrite32(reg_val,
		  dev->reg_base +
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
	iowrite32(reg_val,
		  dev->reg_base +
		  HOG_OFFSET
		  (IRECOG_rcohog0_Destination_0_Format_Register_OFFS));

	return 0;
}

static SINT dd_HOG_config_load_dictionary(struct hog_dev *dev,
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
	dd_HOG_part_config_load_dictionary(dev, format_physmem_addr,
					   weight_physmem_addr, format_size,
					   weight_size);

	hog_write_register_func(dev, *(dev->func));

	return 0;
}

static SINT dd_HOG_config_classify_region(struct hog_dev *dev,
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

static SINT dd_HOG_config_classify_position(struct hog_dev *dev,
					    /* func */
					    UINT dict_num,
					    /* cell_fmt */
					    UINT cell_num_x,
					    UINT cell_num_y,
					    UINT cell_width, UINT cell_height,
					    /* roi_stride */
					    UINT roi_num,
					    struct roi_coord *roi_list,
					    /* src0_lptch */
					    ULONG dir_physmem_addr,
					    UINT dir_pitch,
					    ULONG dst_physmem_addr)
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

static long hog_check_dict_param(struct hog_dict_param *param)
{
	/* dict num */
	if ((param->dict_num < HOG_MIN_DICT_NUM)
	    || (param->dict_num > HOG_MAX_DICT_NUM)) {
		pr_err("%s: invalid dict_num:%lu\n", HOG_NAME, param->dict_num);
		return -EINVAL;
	}

	/* cell num */
	if ((param->cell_num_w < HOG_MIN_CELL_NUM)
	    || (param->cell_num_w > HOG_MAX_CELL_NUM)) {
		pr_err("%s: invalid cell_num_w:%lu\n", HOG_NAME,
		       param->cell_num_w);
		return -EINVAL;
	}
	if ((param->cell_num_h < HOG_MIN_CELL_NUM)
	    || (param->cell_num_h > HOG_MAX_CELL_NUM)) {
		pr_err("%s: invalid cell_num_h:%lu\n", HOG_NAME,
		       param->cell_num_h);
		return -EINVAL;
	}

	/* cell size */
	if ((param->cell_size_w < HOG_MIN_CELL_SIZE)
	    || (param->cell_size_w > HOG_MAX_CELL_SIZE)) {
		pr_err("%s: invalid cell_size_w:%lu\n", HOG_NAME,
		       param->cell_size_w);
		return -EINVAL;
	}
	if ((param->cell_size_h < HOG_MIN_CELL_SIZE)
	    || (param->cell_size_h > HOG_MAX_CELL_SIZE)) {
		pr_err("%s: invalid cell_size_h:%lu\n", HOG_NAME,
		       param->cell_size_h);
		return -EINVAL;
	}

	/* roi size */
	if ((param->cell_size_w * param->cell_num_w) > HOG_MAX_ROI_WDTH) {
		pr_err("%s: invalid cell_size_w*cell_num_w\n", HOG_NAME);
		return -EINVAL;
	}

	return 0;
}

static long hog_check_svm_position_param(struct hog_svm_position_param *param)
{
	/* dict num */
	if ((param->dict_num < HOG_MIN_DICT_NUM)
	    || (param->dict_num > HOG_MAX_DICT_NUM)) {
		pr_err("%s: invalid dict_num:%lu\n", HOG_NAME, param->dict_num);
		return -EINVAL;
	}

	/* cell num */
	if ((param->cell_num_w < HOG_MIN_CELL_NUM)
	    || (param->cell_num_w > HOG_MAX_CELL_NUM)) {
		pr_err("%s: invalid cell_num_w:%lu\n", HOG_NAME,
		       param->cell_num_w);
		return -EINVAL;
	}
	if ((param->cell_num_h < HOG_MIN_CELL_NUM)
	    || (param->cell_num_h > HOG_MAX_CELL_NUM)) {
		pr_err("%s: invalid cell_num_h:%lu\n", HOG_NAME,
		       param->cell_num_h);
		return -EINVAL;
	}

	/* cell size */
	if ((param->cell_size_w < HOG_MIN_CELL_SIZE)
	    || (param->cell_size_w > HOG_MAX_CELL_SIZE)) {
		pr_err("%s: invalid cell_size_w:%lu\n", HOG_NAME,
		       param->cell_size_w);
		return -EINVAL;
	}
	if ((param->cell_size_h < HOG_MIN_CELL_SIZE)
	    || (param->cell_size_h > HOG_MAX_CELL_SIZE)) {
		pr_err("%s: invalid cell_size_h:%lu\n", HOG_NAME,
		       param->cell_size_h);
		return -EINVAL;
	}

	/* roi size */
	if ((param->cell_size_w * param->cell_num_w) > HOG_MAX_ROI_WDTH) {
		pr_err("%s: invalid cell_size_w*cell_num_w\n", HOG_NAME);
		return -EINVAL;
	}

	/* roi num */
	if ((param->roi_num < HOG_MIN_ROI_NUM)
	    || (param->roi_num > HOG_MAX_ROI_NUM)) {
		pr_err("%s: invalid roi_num:%lu\n", HOG_NAME, param->roi_num);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->dir_pitch == 0)
	    || ((param->dir_pitch & HOG_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: invalid dir_pitch:%lu\n", HOG_NAME,
		       param->dir_pitch);
		return -EINVAL;
	}

	/* dir height */
	if (param->dir_height == 0) {
		pr_err("%s: invalid dir_height:%lu\n", HOG_NAME,
		       param->dir_height);
		return -EINVAL;
	}

	return 0;
}

static long hog_check_svm_region_param(struct hog_svm_region_param *param)
{
	/* dict num */
	if ((param->dict_num < HOG_MIN_DICT_NUM)
	    || (param->dict_num > HOG_MAX_DICT_NUM)) {
		pr_err("%s: invalid dict_num:%lu\n", HOG_NAME, param->dict_num);
		return -EINVAL;
	}

	/* cell num */
	if ((param->cell_num_w < HOG_MIN_CELL_NUM)
	    || (param->cell_num_w > HOG_MAX_CELL_NUM)) {
		pr_err("%s: invalid cell_num_w:%lu\n", HOG_NAME,
		       param->cell_num_w);
		return -EINVAL;
	}
	if ((param->cell_num_h < HOG_MIN_CELL_NUM)
	    || (param->cell_num_h > HOG_MAX_CELL_NUM)) {
		pr_err("%s: invalid cell_num_h:%lu\n", HOG_NAME,
		       param->cell_num_h);
		return -EINVAL;
	}

	/* cell size */
	if ((param->cell_size_w < HOG_MIN_CELL_SIZE)
	    || (param->cell_size_w > HOG_MAX_CELL_SIZE)) {
		pr_err("%s: invalid cell_size_w:%lu\n", HOG_NAME,
		       param->cell_size_w);
		return -EINVAL;
	}
	if ((param->cell_size_h < HOG_MIN_CELL_SIZE)
	    || (param->cell_size_h > HOG_MAX_CELL_SIZE)) {
		pr_err("%s: invalid cell_size_h:%lu\n", HOG_NAME,
		       param->cell_size_h);
		return -EINVAL;
	}

	/* roi num */
	if ((param->roi_num_w < HOG_MIN_ROI_REGION_NUM)
	    || (param->roi_num_w > HOG_MAX_ROI_REGION_NUM)) {
		pr_err("%s: invalid roi_num_w:%lu\n", HOG_NAME,
		       param->roi_num_w);
		return -EINVAL;
	}
	if ((param->roi_num_h < HOG_MIN_ROI_REGION_NUM)
	    || (param->roi_num_h > HOG_MAX_ROI_REGION_NUM)) {
		pr_err("%s: invalid roi_num_h:%lu\n", HOG_NAME,
		       param->roi_num_h);
		return -EINVAL;
	}

	/* roi stride num */
	if ((param->roi_stride_w < HOG_MIN_STRIDE_NUM)
	    || (param->roi_stride_w > HOG_MAX_STRIDE_NUM)) {
		pr_err("%s: invalid roi_stride_w:%lu\n", HOG_NAME,
		       param->roi_stride_w);
		return -EINVAL;
	}
	if ((param->roi_stride_h < HOG_MIN_STRIDE_NUM)
	    || (param->roi_stride_h > HOG_MAX_STRIDE_NUM)) {
		pr_err("%s: invalid roi_stride_h:%lu\n", HOG_NAME,
		       param->roi_stride_h);
		return -EINVAL;
	}

	/* roi size */
	if (((param->cell_size_w * param->cell_num_w) - 1) >
	    HOG_MAX_ROI_WDTH_REGION) {
		pr_err("%s: invalid cell_size_w*cell_num_w\n", HOG_NAME);
		return -EINVAL;
	}
	if (((param->cell_size_h * param->cell_num_h) - 1) >
	    HOG_MAX_ROI_HIGT_REGION) {
		pr_err("%s: invalid cell_size_h*cell_num_h\n", HOG_NAME);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->dir_pitch == 0)
	    || ((param->dir_pitch & HOG_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: invalid dir_pitch:%lu\n", HOG_NAME,
		       param->dir_pitch);
		return -EINVAL;
	}

	/* dir width */
	if ((param->dir_width > HOG_MAX_SRC0_WDTH_REGION)
	    || (param->dir_width == 0)) {
		pr_err("%s: invalid dir_width:%lu\n", HOG_NAME,
		       param->dir_width);
		return -EINVAL;
	}

	/* dir height */
	if ((param->dir_height > HOG_MAX_SRC0_HIGT_REGION)
	    || (param->dir_height == 0)) {
		pr_err("%s: invalid dir_height:%lu\n", HOG_NAME,
		       param->dir_height);
		return -EINVAL;
	}

	/* size check */
	if (((param->cell_size_w * param->cell_num_w - 1) +
	     param->roi_stride_w * param->roi_num_w) > param->dir_width) {
		pr_err("%s: invalid size.\n", HOG_NAME);
		return -EINVAL;
	}
	/* size check */
	if (((param->cell_size_h * param->cell_num_h - 1) +
	     param->roi_stride_h * param->roi_num_h) > param->dir_height) {
		pr_err("%s: invalid size.\n", HOG_NAME);
		return -EINVAL;
	}

	return 0;
}

static long dict_check_param(unsigned long param)
{
	/* bank mode */
	if (param > HOG_DICT_BANK_MODE1) {
		pr_err("%s: invalid bank_mode:%lu\n", HOG_NAME, param);
		return -EINVAL;
	}

	return 0;
}

static long hog_wait_event(struct file *filp)
{
	sigset_t oldset;

	struct hog_dev *dev = filp->private_data;
	int status = *(dev->status);

	if (status != HOG_EXE_DONE) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		/* signal mask */
		drv_sigmask(&oldset);
		if (wait_event_interruptible(*(dev->wq),
					     (*(dev->status) ==
					      HOG_EXE_DONE))) {

			hog_reset(dev);

			/* signal unmask */
			drv_sigunmask(&oldset);
			*(dev->status) = HOG_EXE_DONE;

			pr_err("hog: wait_event_interruptible fail.\n");

			return -ERESTARTSYS;
		}
		/* signal unmask */
		drv_sigunmask(&oldset);
	}

	return 0;
}

static int hog_get_int_status(struct hog_dev *dev)
{
	unsigned int status;
	int ret;

	status =
	    ioread32(dev->reg_base +
		     HOG_OFFSET(IRECOG_rcohog0_Interrupt_Status_Register_OFFS));
	if ((status & HOG_HW_END) != 0) {
		ret = HOG_EXE_DONE;
	} else if ((status & HOG_HW_LINE_OUT_END) != 0) {
		ret = HOG_LINEOUT;
	} else {
		ret = HOG_ERROR;
	}

	return ret;
}

static long hog_reset(struct hog_dev *dev)
{
	unsigned int ret;

	iowrite32(IRECOG_RCOHOG0_CONTROL_REGISTER_RST_MASK,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));
	/* wait for reset completion */
	ret =
	    drv_wait_register(dev->reg_base +
			      HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS),
			      IRECOG_RCOHOG0_CONTROL_REGISTER_RST_MASK, 0x0,
			      DRV_WAIT_REG_TIMEOUT);
	if ((ret & IRECOG_RCOHOG0_CONTROL_REGISTER_RST_MASK) != 0x0) {
		pr_err
		    ("%s: timeout occured while waiting for register value to change\n",
		     HOG_NAME);
		return -EIO;
	}

	return 0;
}

static void hog_clear_int(struct hog_dev *dev)
{
	iowrite32(HOG_CLEAR_BITS,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Interrupt_Status_Register_OFFS));
}

static SINT dd_HOG_send_request(struct hog_dev *dev)
{
	/* Clear Int Mask. */
	hog_clear_int(dev);

	/* Set Int Mask, Currently No Parameter Trans. */
	iowrite32(HOG_INTMASK_NORMAL,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Interrupt_Mask_Register_OFFS));

	/* Kick Hog */
	*(dev->status) = HOG_KICKED;
	iowrite32(0x1,
		  dev->reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));

	return 0;
}

static irqreturn_t hog_isr(int irq, void *dev_id)
{
	struct hog_dev *dev = dev_id;
	int status;

	status = hog_get_int_status(dev);
	*(dev->status) = status;
	hog_clear_int(dev);

	if (status == HOG_EXE_DONE) {
		wake_up_interruptible(dev->wq);
	} else if (status == HOG_LINEOUT) {
		/* do nothing */
	} else if (status == HOG_ERROR) {
		wake_up_interruptible(dev->wq);
	}

	return IRQ_HANDLED;
}

static int hog_open(struct inode *inode, struct file *filp)
{
	struct hog_dev *dev;

	dev = container_of(inode->i_cdev, struct hog_dev, cdev);
	filp->private_data = dev;

	if (atomic_inc_return(&refcount) == 1) {
		hog_runtime_resume(&dev->pdev->dev);
	}
	return 0;
}

static int hog_release(struct inode *inode, struct file *filp)
{
	struct hog_dev *dev;

	dev = container_of(inode->i_cdev, struct hog_dev, cdev);

	if (atomic_dec_return(&refcount) == 0) {
		hog_runtime_suspend(&dev->pdev->dev);
	}
	return 0;
}

static long hog_get_version(unsigned long val)
{
	drv_version_t version_param;

	memset(&version_param, 0x00, sizeof(drv_version_t));
	memcpy(version_param.version, drv_hog_version, strlen(drv_hog_version));

	if (copy_to_user((void __user *)val,
			 (void *)&version_param, sizeof(drv_version_t))) {
		pr_err("%s: copy_to_user failed version\n", HOG_NAME);
		return -EFAULT;
	}
	return 0;
}

static long hog_ioctl(struct file *filp, unsigned int cmd, unsigned long val)
{
	struct hog_dev *dev = filp->private_data;
	long ret;

	switch (cmd) {
	case HOG_IOCTL_LOAD_DICTIONARY:
		{
			struct hog_dict_param dict_param;
			if (copy_from_user
			    ((void *)&dict_param, (const void __user *)val,
			     sizeof(struct hog_dict_param))) {
				pr_err("%s: copy_from_user failed dict_param\n",
				       HOG_NAME);
				return -EFAULT;
			}

			if (hog_check_dict_param(&dict_param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       HOG_NAME);
				return -EINVAL;
			}
			if (check_cache_param(dict_param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(dev->sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       HOG_NAME);
				return -ERESTARTSYS;
			}
			if (*(dev->status) != HOG_EXE_DONE) {
				pr_err("%s: invalid status.\n", HOG_NAME);
				up(dev->sem);
				return -EAGAIN;
			}

			dd_HOG_config_load_dictionary(dev,
						      dict_param.dict_num,
						      dict_param.cell_num_w,
						      dict_param.cell_num_h,
						      dict_param.cell_size_w,
						      dict_param.cell_size_h,
						      dict_param.format_adr,
						      dict_param.weight_adr,
						      dict_param.format_size,
						      dict_param.weight_size);
			/* cache control */
			if (dict_param.buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
				drv_cache_flush_all();
			}

			dd_HOG_send_request(dev);

			ret = hog_wait_event(filp);
			up(dev->sem);

			return ret;
		}
		break;

	case HOG_IOCTL_CLASSIFY_POSITION:
		{
			struct hog_svm_position_param svm_position_param;
			struct roi_coord *roi_list;

			if (copy_from_user
			    ((void *)&svm_position_param,
			     (const void __user *)val,
			     sizeof(struct hog_svm_position_param))) {
				pr_err("%s: copy_from_user failed svm_param\n",
				       HOG_NAME);
				return -EFAULT;
			}
			roi_list =
			    kmalloc(sizeof(struct roi_coord) *
				    svm_position_param.roi_num,
				    GFP_KERNEL | GFP_DMA);
			if (!roi_list) {
				pr_err("%s: kmalloc failed\n", HOG_NAME);
				return -ENOMEM;
			}
			if (copy_from_user
			    ((void *)roi_list, (const void __user *)(UINT)
			     svm_position_param.roi_list,
			     sizeof(struct roi_coord) *
			     svm_position_param.roi_num)) {
				pr_err("%s: copy_from_user failed roi_list\n",
				       HOG_NAME);
				kfree(roi_list);
				return -EFAULT;
			}

			if (hog_check_svm_position_param(&svm_position_param) <
			    0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       HOG_NAME);
				kfree(roi_list);
				return -EINVAL;
			}
			if (svm_position_param.buffer_cache_ctl !=
			    DRV_CACHE_FLUSH_ALL) {
				pr_err("%s: invalid buffer_cache_ctl:%lu\n",
				       HOG_NAME,
				       svm_position_param.buffer_cache_ctl);
				return -EINVAL;
			}

			if (down_interruptible(dev->sem)) {
				pr_err("%s: down_interruptible fail.\n",
				       HOG_NAME);
				kfree(roi_list);
				return -ERESTARTSYS;
			}
			if (*(dev->status) != HOG_EXE_DONE) {
				pr_err("%s: invalid status.\n", HOG_NAME);
				up(dev->sem);
				kfree(roi_list);
				return -EAGAIN;
			}

			dd_HOG_config_classify_position(dev,
							svm_position_param.dict_num,
							svm_position_param.cell_num_w,
							svm_position_param.cell_num_h,
							svm_position_param.cell_size_w,
							svm_position_param.cell_size_h,
							svm_position_param.roi_num,
							roi_list,
							svm_position_param.dir_adr,
							svm_position_param.dir_pitch,
							svm_position_param.dst_adr);
			/* cache control */
			if (svm_position_param.buffer_cache_ctl &
			    DRV_CACHE_FLUSH_ALL) {
#if 0
/*
	hog_cache_flush_svm_position(&svm_position_param, roi_list);
*/
#else
				drv_cache_flush_all();
#endif
			}
#if 0
/*
      drv_cache_invalidate(svm_position_param.dst_adr, svm_position_param.roi_num * 4);
*/
#endif

			dd_HOG_send_request(dev);

			ret = hog_wait_event(filp);
			kfree(roi_list);
			up(dev->sem);

			return ret;
		}
		break;

	case HOG_IOCTL_CLASSIFY_REGION:
		{
			struct hog_svm_region_param svm_region_param;

			if (copy_from_user
			    ((void *)&svm_region_param,
			     (const void __user *)val,
			     sizeof(struct hog_svm_region_param))) {
				pr_err("%s: copy_from_user failed svm_param\n",
				       HOG_NAME);
				return -EFAULT;
			}

			if (hog_check_svm_region_param(&svm_region_param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       HOG_NAME);
				return -EINVAL;
			}
			if (check_cache_param(svm_region_param.buffer_cache_ctl)
			    < 0) {
				return -EINVAL;
			}

			if (down_interruptible(dev->sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       HOG_NAME);
				return -ERESTARTSYS;
			}
			if (*(dev->status) != HOG_EXE_DONE) {
				pr_err("%s: invalid status.\n", HOG_NAME);
				up(dev->sem);
				return -EAGAIN;
			}

			dd_HOG_config_classify_region(dev,
						      svm_region_param.dict_num,
						      svm_region_param.cell_num_w,
						      svm_region_param.cell_num_h,
						      svm_region_param.cell_size_w,
						      svm_region_param.cell_size_h,
						      svm_region_param.roi_num_w,
						      svm_region_param.roi_num_h,
						      svm_region_param.roi_stride_w,
						      svm_region_param.roi_stride_h,
						      svm_region_param.dir_adr,
						      svm_region_param.dir_pitch,
						      svm_region_param.dir_width,
						      svm_region_param.dir_height,
						      svm_region_param.dst_adr);
			/* cache control */
			if (svm_region_param.buffer_cache_ctl &
			    DRV_CACHE_FLUSH_ALL) {
				drv_cache_flush_all();
			}

			dd_HOG_send_request(dev);

			ret = hog_wait_event(filp);
			up(dev->sem);

			return ret;
		}
		break;

	case HOG_IOCTL_GET_VERSION:
		return hog_get_version(val);
		break;

	case HOG_IOCTL_INITIALIZE:
		if (hog_reset(dev) < 0) {
			pr_err("%s: reset failed.\n", HOG_NAME);
			return -EIO;
		}
		break;

	default:
		pr_err("%s: invalid ioctl command 0x%x\n", HOG_NAME, cmd);
		return -EINVAL;
		break;
	}

	return 0;
}

static long dict_ioctl(struct file *filp, unsigned int cmd, unsigned long val)
{
	struct hog_dev *dev = filp->private_data;

	switch (cmd) {
	case HOG_IOCTL_SET_DICT_BANK_MODE:
		if (dict_check_param(val) < 0) {
			pr_err("%s: invalid ioctl parameter.\n", HOG_NAME);
			return -EINVAL;
		}
		if (down_interruptible(&sem0)) {
			pr_err("%s: down_interruptible failed.\n", HOG_NAME);
			return -ERESTARTSYS;
		}
		if (hog0_status != HOG_EXE_DONE) {
			pr_err("%s: invalid status.\n", HOG_NAME);
			up(&sem0);
			return -EAGAIN;
		}

		if (down_interruptible(&sem1)) {
			pr_err("%s: down_interruptible failed.\n", HOG_NAME);
			up(&sem0);
			return -ERESTARTSYS;
		}
		if (hog1_status != HOG_EXE_DONE) {
			pr_err("%s: invalid status.\n", HOG_NAME);
			up(&sem1);
			up(&sem0);
			return -EAGAIN;
		}

		iowrite32(val, dev->reg_base + DICT_CTRL_OFFSET);

		up(&sem1);
		up(&sem0);
		break;
	case HOG_IOCTL_GET_VERSION:
		return hog_get_version(val);
		break;
	default:
		pr_err("%s: invalid ioctl command 0x%x\n", HOG_NAME, cmd);
		return -EINVAL;
		break;
	}

	return 0;
}

static const struct file_operations hog_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = hog_ioctl,
	.open = hog_open,
	.release = hog_release,
};

static const struct file_operations dict_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = dict_ioctl,
	.open = hog_open,
	.release = hog_release,
};

static void hog_setup_cdev(struct hog_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(hog_major, hog_minor + index);

	cdev_init(&dev->cdev, &hog_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev %d\n", HOG_NAME, index);
	}
}

static void dict_setup_cdev(struct dict_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(hog_major, hog_minor + index);

	cdev_init(&dev->cdev, &dict_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev %d\n", HOG_NAME, index);
	}
}

static int __devinit hog_probe(struct platform_device *pdev)
{
	int i;
	int ret;
	dev_t dev = 0;

	/* allocation of device number */
	if (hog_major) {
		dev = MKDEV(hog_major, hog_minor);
		ret = register_chrdev_region(dev, hog_nr_devs, HOG_NAME);
	} else {
		ret =
		    alloc_chrdev_region(&dev, hog_minor, hog_nr_devs, HOG_NAME);
		hog_major = MAJOR(dev);
	}
	if (ret < 0) {
		pr_err("%s: can't get major %d\n", HOG_NAME, hog_major);
		return ret;
	}

	hog0_devices =
	    kmalloc(sizeof(struct hog_dev) * HOG_ELEM_NR_DEVS, GFP_KERNEL);
	if (!hog0_devices) {
		pr_err("%s: kmalloc failed\n", HOG_NAME);
		ret = -ENOMEM;
		goto err0;
	}
	hog1_devices =
	    kmalloc(sizeof(struct hog_dev) * HOG_ELEM_NR_DEVS, GFP_KERNEL);
	if (!hog1_devices) {
		pr_err("%s: kmalloc failed\n", HOG_NAME);
		ret = -ENOMEM;
		goto err1;
	}
	dict_devices =
	    kmalloc(sizeof(struct dict_dev) * DICT_NR_DEVS, GFP_KERNEL);
	if (!dict_devices) {
		pr_err("%s: kmalloc failed\n", HOG_NAME);
		ret = -ENOMEM;
		goto err2;
	}

	memset(hog0_devices, 0, sizeof(struct hog_dev) * HOG_ELEM_NR_DEVS);
	memset(hog1_devices, 0, sizeof(struct hog_dev) * HOG_ELEM_NR_DEVS);
	memset(dict_devices, 0, sizeof(struct dict_dev) * DICT_NR_DEVS);

	hog0_devices->pdev = pdev;
	hog1_devices->pdev = pdev;
	dict_devices->pdev = pdev;

	/* mapping of hog MMIO (hog0, hog1, dict) */
	if (!request_mem_region(hog0_base, hog0_size, HOG0_NAME)) {
		pr_err("%s: request_mem_region failed.\n", HOG_NAME);
		ret = -ENODEV;
		goto err3;
	}
	if (!request_mem_region(hog1_base, hog1_size, HOG1_NAME)) {
		pr_err("%s: request_mem_region failed.\n", HOG_NAME);
		ret = -ENODEV;
		goto err4;
	}
	if (!request_mem_region(dict_base, dict_size, DICT_NAME)) {
		pr_err("%s: request_mem_region failed.\n", HOG_NAME);
		ret = -ENODEV;
		goto err5;
	}

	hog0_devices[HOG_DEV_IOCTL].reg_base =
	    ioremap_nocache(hog0_base, hog0_size);
	if (!hog0_devices[HOG_DEV_IOCTL].reg_base) {
		pr_err("%s: ioremap_nocache failed.\n", HOG_NAME);
		ret = -ENODEV;
		goto err6;
	}
	hog1_devices[HOG_DEV_IOCTL].reg_base =
	    ioremap_nocache(hog1_base, hog1_size);
	if (!hog1_devices[HOG_DEV_IOCTL].reg_base) {
		pr_err("%s: ioremap_nocache failed.\n", HOG_NAME);
		ret = -ENODEV;
		goto err7;
	}
	dict_devices[DICT_DEV_IOCTL].reg_base =
	    ioremap_nocache(dict_base, dict_size);
	if (!dict_devices[DICT_DEV_IOCTL].reg_base) {
		pr_err("%s: ioremap_nocache failed.\n", HOG_NAME);
		ret = -ENODEV;
		goto err8;
	}

	/* register interrupt service routine (hog0, hog1) */
	ret =
	    request_irq(hog0_irq, hog_isr, 0, HOG0_NAME,
			&hog0_devices[HOG_DEV_IOCTL]);
	if (ret < 0) {
		pr_err("%s: request_irq failed\n", HOG_NAME);
		goto err9;
	}
	ret =
	    request_irq(hog1_irq, hog_isr, 0, HOG1_NAME,
			&hog1_devices[HOG_DEV_IOCTL]);
	if (ret < 0) {
		pr_err("%s: request_irq failed\n", HOG_NAME);
		goto err10;
	}

	/* init semaphore (for hog0 and hog1) */
	sema_init(&sem0, 1);
	sema_init(&sem1, 1);

	/* init waitqueue (for hog0 and hog1) */
	init_waitqueue_head(&wq0);
	init_waitqueue_head(&wq1);

	for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
		hog0_devices[i].status = &hog0_status;
		hog0_devices[i].sem = &sem0;
		hog0_devices[i].wq = &wq0;
		hog0_devices[i].roi_mode = &hog0_roi_mode;
		hog0_devices[i].roi_num = &hog0_roi_num;
		hog0_devices[i].func = &hog0_func;
		hog1_devices[i].status = &hog1_status;
		hog1_devices[i].sem = &sem1;
		hog1_devices[i].wq = &wq1;
		hog1_devices[i].roi_mode = &hog1_roi_mode;
		hog1_devices[i].roi_num = &hog1_roi_num;
		hog1_devices[i].func = &hog1_func;
	}

	/* register cdev (hog0, hog1, dict) */
	for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
		hog0_devices[i].dev_base = hog0_devices;
		hog_setup_cdev(&hog0_devices[i], i);
	}
	for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
		hog1_devices[i].dev_base = hog1_devices;
		hog_setup_cdev(&hog1_devices[i], i + HOG_ELEM_NR_DEVS);
	}
	for (i = 0; i < DICT_NR_DEVS; i++) {
		dict_setup_cdev(&dict_devices[i], i + HOG_ELEM_NR_DEVS * 2);
	}

	/* create hog class */
	phog_class = class_create(THIS_MODULE, HOG_NAME);
	if (IS_ERR(phog_class)) {
		ret = PTR_ERR(phog_class);
		pr_err("%s: class_create failed\n", HOG_NAME);
		goto err11;
	}

	/* create device structure */
	for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
		int minor = hog_minor + i;
		dev_t devno = MKDEV(hog_major, minor);
		hog0_devices[i].device =
		    device_create(phog_class, NULL, devno, NULL, "%s%d_ioctl",
				  HOG_NAME, minor);
		if (IS_ERR(hog0_devices[i].device)) {
			ret = PTR_ERR(hog0_devices[i].device);
			pr_err("%s: device_create failed\n", HOG_NAME);
			goto err12;
		}
	}
	for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
		int minor = hog_minor + i + HOG_ELEM_NR_DEVS;
		dev_t devno = MKDEV(hog_major, minor);
		hog1_devices[i].device =
		    device_create(phog_class, NULL, devno, NULL, "%s%d_ioctl",
				  HOG_NAME, minor);
		if (IS_ERR(hog1_devices[i].device)) {
			ret = PTR_ERR(hog1_devices[i].device);
			pr_err("%s: device_create failed\n", HOG_NAME);
			goto err12;
		}
	}
	for (i = 0; i < DICT_NR_DEVS; i++) {
		int minor = hog_minor + i + HOG_ELEM_NR_DEVS * 2;
		dev_t devno = MKDEV(hog_major, minor);
		dict_devices[i].device =
		    /* DICT_NR_DEVS = 1 */
		    device_create(phog_class, NULL, devno, NULL, "%s_ioctl",
				  DICT_NAME);
		if (IS_ERR(dict_devices[i].device)) {
			ret = PTR_ERR(dict_devices[i].device);
			pr_err("%s: device_create failed\n", HOG_NAME);
			goto err12;
		}
	}

	{
		struct hog_drvdata *priv;
		priv = kmalloc(sizeof(struct hog_drvdata), GFP_KERNEL);
		if (!priv) {
			pr_err("%s: kmalloc failed\n", HOG_NAME);
			ret = -ENOMEM;
			goto err12;
		}
		priv->hog0_devices = hog0_devices;
		priv->hog1_devices = hog1_devices;
		priv->dict_devices = dict_devices;
		platform_set_drvdata(pdev, priv);
	}
	pm_runtime_enable(&pdev->dev);

	/* driver initialized */
	for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
		int minor = hog_minor + i;
		dev_t devno = MKDEV(hog_major, minor);
		pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
			HOG_NAME,
			DRV_HOG_VERSION_STR, MAJOR(devno), MINOR(devno));
	}
	for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
		int minor = hog_minor + i + HOG_ELEM_NR_DEVS;
		dev_t devno = MKDEV(hog_major, minor);
		pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
			HOG_NAME,
			DRV_HOG_VERSION_STR, MAJOR(devno), MINOR(devno));
	}
	for (i = 0; i < DICT_NR_DEVS; i++) {
		int minor = hog_minor + i + HOG_ELEM_NR_DEVS * 2;
		dev_t devno = MKDEV(hog_major, minor);
		pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
			HOG_NAME,
			DRV_HOG_VERSION_STR, MAJOR(devno), MINOR(devno));
	}

	return 0;

err12:
	class_destroy(phog_class);
err11:
	for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
		cdev_del(&hog0_devices[i].cdev);
		cdev_del(&hog1_devices[i].cdev);
	}
	for (i = 0; i < DICT_NR_DEVS; i++) {
		cdev_del(&dict_devices[i].cdev);
	}
err10:
	free_irq(hog0_irq, &hog0_devices[HOG_DEV_IOCTL]);
err9:
	iounmap(dict_devices[DICT_DEV_IOCTL].reg_base);
err8:
	iounmap(hog1_devices[HOG_DEV_IOCTL].reg_base);
err7:
	iounmap(hog0_devices[HOG_DEV_IOCTL].reg_base);
err6:
	release_mem_region(dict_base, dict_size);
err5:
	release_mem_region(hog1_base, hog0_size);
err4:
	release_mem_region(hog0_base, hog0_size);
err3:
	kfree(dict_devices);
err2:
	kfree(hog1_devices);
err1:
	kfree(hog0_devices);
err0:
	unregister_chrdev_region(dev, hog_nr_devs);

	return ret;
}

static int __devexit hog_remove(struct platform_device *pdev)
{
	int i;
	dev_t dev = MKDEV(hog_major, hog_minor);
	struct hov_drvdata *priv = platform_get_drvdata(pdev);

	/* reset device */
	hog_runtime_resume(&pdev->dev);
	if (hog0_devices)
		hog_reset(&hog0_devices[HOG_DEV_IOCTL]);
	if (hog1_devices)
		hog_reset(&hog1_devices[HOG_DEV_IOCTL]);
	hog_runtime_suspend(&pdev->dev);

	if (hog0_devices) {
		for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
			dev_t devno = MKDEV(hog_major, hog_minor + i);
			device_destroy(phog_class, devno);
			cdev_del(&hog0_devices[i].cdev);
		}
		free_irq(hog0_irq, &hog0_devices[HOG_DEV_IOCTL]);
		iounmap(hog0_devices[HOG_DEV_IOCTL].reg_base);
		release_mem_region(hog0_base, hog0_size);
		kfree(hog0_devices);
	}

	if (hog1_devices) {
		for (i = 0; i < HOG_ELEM_NR_DEVS; i++) {
			dev_t devno =
			    MKDEV(hog_major, hog_minor + i + HOG_ELEM_NR_DEVS);
			device_destroy(phog_class, devno);
			cdev_del(&hog1_devices[i].cdev);
		}
		free_irq(hog1_irq, &hog1_devices[HOG_DEV_IOCTL]);
		iounmap(hog1_devices[HOG_DEV_IOCTL].reg_base);
		release_mem_region(hog1_base, hog1_size);
		kfree(hog1_devices);
	}

	if (dict_devices) {
		for (i = 0; i < DICT_NR_DEVS; i++) {
			dev_t devno = MKDEV(hog_major,
					    hog_minor + i +
					    HOG_ELEM_NR_DEVS * 2);
			device_destroy(phog_class, devno);
			cdev_del(&dict_devices[i].cdev);
		}
		iounmap(dict_devices[DICT_DEV_IOCTL].reg_base);
		release_mem_region(dict_base, dict_size);
		kfree(dict_devices);
	}

	pm_runtime_disable(&pdev->dev);
	platform_set_drvdata(pdev, priv);
	kfree(priv);

	class_destroy(phog_class);
	unregister_chrdev_region(dev, hog_nr_devs);

	pr_info("%s: exit\n", HOG_NAME);

	return 0;
}

static int hog_suspend(struct device *dev)
{
	int ret = 0;

	if (atomic_read(&refcount) > 0) {
		ret = -EBUSY;
	}

	pr_debug("%s: %s: %d\n", HOG_NAME, __func__, ret);

	return ret;
}

static int hog_resume(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops hog_pm_ops = {
	.suspend = hog_suspend,
	.resume = hog_resume,
	.runtime_suspend = hog_runtime_suspend,
	.runtime_resume = hog_runtime_resume,
};

static struct platform_driver hog_driver = {
	.driver = {
		   .name = "irecog_hog",
		   .owner = THIS_MODULE,
		   .pm = &hog_pm_ops,
		   },
	.probe = hog_probe,
	.remove = hog_remove,
};

static int __init hog_init(void)
{
	return platform_driver_register(&hog_driver);
}

static void __exit hog_exit(void)
{
	platform_driver_unregister(&hog_driver);
}

module_init(hog_init);
module_exit(hog_exit);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_VERSION(DRV_HOG_VERSION_STR);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HOG HWE module");
