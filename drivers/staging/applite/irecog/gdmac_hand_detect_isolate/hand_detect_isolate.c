/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/hand_detect_isolate.c
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
#include <linux/slab.h>
#include <linux/uaccess.h>

#include "drv_defs.h"

#include "hand_detect_isolate.h"
#include "gdmac_port_def.h"
#include "drv_cache.h"
#include "sl_filter_gdmac.h"
#include "gdmac_hand_detect_isolate_driver.h"

static int hog0_roi_mode = HOG_MODE_DIC;
static int hog0_roi_num;
static unsigned int hog0_func;
static int hog1_roi_mode = HOG_MODE_DIC;
static int hog1_roi_num;
static unsigned int hog1_func;

static struct roi_coord
*roi_list[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM]
    [GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM];

/*
 * filter W/A
 * IHWID % 128 == 0
 * or
 * output 16bit: IHWID % 128 >= 40
 *        8bit:  IHWID % 128 >= 80
 */
/* actual-width + (80 - (actual-width % 128)) */
static unsigned long dir_image_in_width[GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM] = {
	380,
	336,			/* actual: 320 */
	336,			/* actual: 269 */
	226,
	208,			/* actual: 190 */
	208,			/* actual: 160 */
	208,			/* actual: 134 */
	113,
	95
};

static unsigned long dir_image_out_width[GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM] = {
	DIR_IMAGE_OUT0_W,
	DIR_IMAGE_OUT1_W,
	DIR_IMAGE_OUT2_W,
	DIR_IMAGE_OUT3_W,
	DIR_IMAGE_OUT4_W,
	DIR_IMAGE_OUT5_W,
	DIR_IMAGE_OUT6_W,
	DIR_IMAGE_OUT7_W,
	DIR_IMAGE_OUT8_W
};

static unsigned long dir_image_out_height[GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM] = {
	DIR_IMAGE_OUT0_H,
	DIR_IMAGE_OUT1_H,
	DIR_IMAGE_OUT2_H,
	DIR_IMAGE_OUT3_H,
	DIR_IMAGE_OUT4_H,
	DIR_IMAGE_OUT5_H,
	DIR_IMAGE_OUT6_H,
	DIR_IMAGE_OUT7_H,
	DIR_IMAGE_OUT8_H
};

/**************************************************/
/*
 * @brief pitch_64byte_check
 *
 * @param pitch
 *
 * @retval 0
 * @retval -EINVAL
 *
 */
/**************************************************/
#define PITCH 64
static inline unsigned long get_pitch64_value(unsigned long pitch)
{
	if ((pitch % PITCH) == 0) {
		return pitch;
	}

	return pitch + PITCH - (pitch % PITCH);
}

/**************************************************/
/*
 * @brief hand_detect_isolate_cache_flush
 *
 * @param param
 *
 */
/**************************************************/
void hand_detect_isolate_cache_flush(gdmac_hand_detect_isolate *param)
{
	int i, n;

	/* hog */
	for (i = 0; i < GDMAC_HAND_DETECT_ISOLATE_DICT_NUM; i++) {
		/* dict */
		drv_cache_flush(param->dict[i].format_adr,
				param->dict[i].format_size);
		drv_cache_flush(param->dict[i].weight_adr,
				param->dict[i].weight_size);

		/* roi */
		for (n = param->layer_min; n <= param->layer_max; n++) {
			drv_cache_flush(virt_to_phys(roi_list[i][n]),
					param->setting[n].roi_num[i] *
					sizeof(struct roi_coord));
		}
		if (param->hand_num == HAND_NUM_ONE) {
			break;
		}
	}

	/* filter */
	for (n = param->layer_min; n <= param->layer_max; n++) {
		drv_cache_flush(param->setting[n].input_image_adr,
				param->setting[n].input_image_pitch *
				dir_image_out_height[n]);

		drv_cache_flush(param->setting[n].dst_dir_thr_adr,
				param->setting[n].input_image_pitch *
				dir_image_out_height[n]);

		drv_cache_flush(param->setting[n].dst_dir_nothr_adr,
				param->setting[n].input_image_pitch *
				dir_image_out_height[n]);

		drv_cache_flush(param->setting[n].dst_dir_int_adr,
				param->setting[n].input_image_pitch *
				dir_image_out_height[n] * 2);
	}
}

/**************************************************/
/*
 * @brief hand_detect_isolate_cache_invalidate
 *
 * @param param
 *
 */
/**************************************************/
void hand_detect_isolate_cache_invalidate(gdmac_hand_detect_isolate *param)
{
	int i, n;

	/* hog */
	for (i = 0; i < GDMAC_HAND_DETECT_ISOLATE_DICT_NUM; i++) {
		for (n = param->layer_min; n <= param->layer_max; n++) {
			drv_cache_invalidate(param->setting[n].dst_adr[i],
					     param->setting[n].roi_num[i] * 4);
		}
		if (param->hand_num == HAND_NUM_ONE) {
			break;
		}
	}
}

/**************************************************/
/*
 * @brief hand_detect_isolate_initialize
 *
 * @param hog[]
 * @param dict
 * @param filter
 *
 */
/**************************************************/
int hand_detect_isolate_initialize(struct hog_dev hog[],
				   struct dict_dev *dict,
				   struct filter_dev *filter)
{
	int i, n;

	hog[0].reg_base = HOG0_BASE;
	hog[0].roi_mode = &hog0_roi_mode;
	hog[0].roi_num = &hog0_roi_num;
	hog[0].func = &hog0_func;

	hog[1].reg_base = HOG1_BASE;
	hog[1].roi_mode = &hog1_roi_mode;
	hog[1].roi_num = &hog1_roi_num;
	hog[1].func = &hog1_func;

	dict->reg_base = DICT_BASE;
	filter->reg_base = FILTER_BASE;

	for (i = 0; i < GDMAC_HAND_DETECT_ISOLATE_DICT_NUM; i++) {
		for (n = 0; n < GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM; n++) {
			/* initialize roi_list */
			roi_list[i][n] = NULL;
		}
	}

	return 0;
}

/**************************************************/
/*
 * @brief hand_detect_isolate_finalize
 *
 */
/**************************************************/
void hand_detect_isolate_finalize(void)
{
	int i, n;

	for (i = 0; i < GDMAC_HAND_DETECT_ISOLATE_DICT_NUM; i++) {
		for (n = 0; n < GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM; n++) {
			kfree(roi_list[i][n]);
		}
	}
}

/**************************************************/
/*
 * @brief hand_detect_parameter_check
 *
 * @param param
 * @param mode
 *
 */
/**************************************************/
int hand_detect_isolate_parameter_check(gdmac_hand_detect_isolate *param,
					int32_t mode)
{
	int i, n;

	if ((param->dict_bank_mode != HOG_DICT_BANK_MODE0)
	    && (param->dict_bank_mode != HOG_DICT_BANK_MODE1)) {
		return -EINVAL;
	}

	if ((param->hand_num != HAND_NUM_BOTH)
	    && (param->hand_num != HAND_NUM_ONE)) {
		return -EINVAL;
	}

	/* layer  */
	if (param->layer_max >= GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM) {
		return -EINVAL;
	}

	if (param->layer_min > param->layer_max) {
		return -EINVAL;
	}

	for (i = 0; i < GDMAC_HAND_DETECT_ISOLATE_DICT_NUM; i++) {
		/* dict num */
		if ((param->dict[i].dict_num < HOG_MIN_DICT_NUM)
		    || (param->dict[i].dict_num > HOG_MAX_DICT_NUM)) {
			return -EINVAL;
		}
		/* cell num */
		if ((param->dict[i].cell_num_w < HOG_MIN_CELL_NUM)
		    || (param->dict[i].cell_num_w > HOG_MAX_CELL_NUM)) {
			return -EINVAL;
		}
		if ((param->dict[i].cell_num_h < HOG_MIN_CELL_NUM)
		    || (param->dict[i].cell_num_h > HOG_MAX_CELL_NUM)) {
			return -EINVAL;
		}

		/* cell size */
		if ((param->dict[i].cell_size_w < HOG_MIN_CELL_SIZE)
		    || (param->dict[i].cell_size_w > HOG_MAX_CELL_SIZE)) {
			return -EINVAL;
		}
		if ((param->dict[i].cell_size_h < HOG_MIN_CELL_SIZE)
		    || (param->dict[i].cell_size_h > HOG_MAX_CELL_SIZE)) {
			return -EINVAL;
		}

		if (mode == ROI_MODE) {
			/* roi size */
			if ((param->dict[i].cell_size_w *
			     param->dict[i].cell_num_w) > HOG_MAX_ROI_WDTH) {
				return -EINVAL;
			}

			/* roi num */
			for (n = param->layer_min; n <= param->layer_max; n++) {
				if ((param->setting[n].roi_num[i] <
				     HOG_MIN_ROI_NUM)
				    || (param->setting[n].roi_num[i] >
					HOG_MAX_ROI_NUM)) {
					return -EINVAL;
				}
			}
		}

		if (mode == REGION_MODE) {
			/* roi size */
			if (((param->dict[i].cell_size_w *
			      param->dict[i].cell_num_w) - 1) >
			    HOG_MAX_ROI_WDTH_REGION) {
				return -EINVAL;
			}
			if (((param->dict[i].cell_size_h *
			      param->dict[i].cell_num_h) - 1) >
			    HOG_MAX_ROI_HIGT_REGION) {
				return -EINVAL;
			}
			for (n = param->layer_min; n <= param->layer_max; n++) {
				/* roi num */
				if ((param->setting[n].roi_num_w[i] <
				     HOG_MIN_ROI_REGION_NUM)
				    || (param->setting[n].roi_num_w[i] >
					HOG_MAX_ROI_REGION_NUM)) {
					return -EINVAL;
				}
				/* roi stride num */
				if ((param->setting[n].roi_stride_w[i] <
				     HOG_MIN_STRIDE_NUM)
				    || (param->setting[n].roi_stride_w[i] >
					HOG_MAX_STRIDE_NUM)) {
					return -EINVAL;
				}

				/* size check */
				if (((param->dict[i].cell_size_w *
				      param->dict[i].cell_num_w - 1)
				     +
				     param->setting[n].roi_stride_w[i] *
				     param->setting[n].roi_num_w[i]) >
				    dir_image_out_width[n]) {
					return -EINVAL;
				}
				if (((param->dict[i].cell_size_h *
				      param->dict[i].cell_num_h - 1)
				     +
				     param->setting[n].roi_stride_h[i] *
				     param->setting[n].roi_num_h[i]) >
				    dir_image_out_height[n]) {
					return -EINVAL;
				}
			}
		}

		if (param->hand_num == HAND_NUM_ONE) {
			break;
		}
	}

	/* line pitch */
	for (n = param->layer_min; n <= param->layer_max; n++) {
		if ((param->setting[n].input_image_pitch == 0) ||
		    ((param->setting[n].
		      input_image_pitch & HOG_LPITCH_ALIGN_MASK) > 0)) {
			return -EINVAL;
		}

		if (param->setting[n].input_image_pitch < dir_image_in_width[n]) {
			return -EINVAL;
		}
	}

	return 0;
}

/**************************************************/
/*
 * @brief hand_detect_isolate_create_instructions
 *
 * @param instructions[]
 * @param hog[]
 * @param dict
 * @param filter
 * @param param
 * @param mode
 *
 */
/**************************************************/
int hand_detect_isolate_create_instructions(gdmac_inst *instructions[],
					    struct hog_dev hog[],
					    struct dict_dev *dict,
					    struct filter_dev *filter,
					    gdmac_hand_detect_isolate *param,
					    int32_t mode)
{
	int trans = 0;
	int i, n;
	int ret = 0;
	gdmac_inst *inst;

	/* copy roi list */
	if (mode == ROI_MODE) {
		for (n = param->layer_min; n <= param->layer_max; n++) {
			for (i = 0; i < GDMAC_HAND_DETECT_ISOLATE_DICT_NUM; i++) {
				kfree(roi_list[i][n]);
				roi_list[i][n] =
				    kmalloc(sizeof(struct roi_coord) *
					    param->setting[n].roi_num[i],
					    GFP_KERNEL);
				if (!roi_list[i][n]) {
					ret = -ENOMEM;
					goto err;
				}
				if (copy_from_user
				    ((void *)roi_list[i][n],
				     (const void __user *)(UINT)
				     param->setting[n].roi_list[i],
				     sizeof(struct roi_coord) *
				     param->setting[n].roi_num[i])) {
					pr_err
					    ("%s:copy_from_user failed roi_list\n",
					     GDMAC_HAND_DETECT_ISOLATE_NAME);
					ret = -ENOMEM;
					goto err;
				}
			}
		}
	}

	/* --- cvia ------------------------------------------------------------- */
	for (n = param->layer_min; n <= param->layer_max; n++) {
		inst = instructions[trans];
		gdmac_clear(inst);

		filter->inst = inst;

		/* init peripherals */
		dma330_dmaflushp(inst, GDMAC_CVIA_PORT);

		/* execute filter */
		sl_gdmac_sobel_direction3x3_and_intensity_with_threshold(filter,
									 param->
									 setting
									 [n].
									 dst_dir_thr_adr,
									 param->
									 setting
									 [n].
									 dst_dir_nothr_adr,
									 param->
									 setting
									 [n].
									 dst_dir_int_adr,
									 param->
									 setting
									 [n].
									 input_image_adr,
									 dir_image_in_width
									 [n],
									 dir_image_out_height
									 [n],
									 param->
									 setting
									 [n].
									 input_image_pitch,
									 param->
									 setting
									 [n].
									 threshold);
		/* wait for filter interrupt */
		dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_CVIA_PORT);
		filter_clear_int(filter);
		dma330_dmaflushp(inst, GDMAC_CVIA_PORT);

		/* gdmac interrupt */
		dma330_dmasev(inst, GDMAC_INT1);
		dma330_dmaend(inst);

		trans++;
	}

	/* --- hog ------------------------------------------------------------- */
	inst = instructions[trans];
	gdmac_clear(inst);

	hog[0].inst = inst;
	hog[1].inst = inst;

	/* init peripherals */
	dma330_dmaflushp(inst, GDMAC_HOG0_PORT);
	dma330_dmaflushp(inst, GDMAC_HOG1_PORT);

	/* set dict bank mode */
	gdmac_write_register(inst, DICT_BASE + DICT_CTRL_OFFSET,
			     param->dict_bank_mode);

	/* CoHOG-A dictionary load */
	dd_HOG_config_load_dictionary(&hog[0],
				      param->dict[0].dict_num,
				      param->dict[0].cell_num_w,
				      param->dict[0].cell_num_h,
				      param->dict[0].cell_size_w,
				      param->dict[0].cell_size_h,
				      param->dict[0].format_adr,
				      param->dict[0].weight_adr,
				      param->dict[0].format_size,
				      param->dict[0].weight_size);

	dd_HOG_send_request(&hog[0]);

	/* CoHOG-B dictionary load */
	dd_HOG_config_load_dictionary(&hog[1],
				      param->dict[1].dict_num,
				      param->dict[1].cell_num_w,
				      param->dict[1].cell_num_h,
				      param->dict[1].cell_size_w,
				      param->dict[1].cell_size_h,
				      param->dict[1].format_adr,
				      param->dict[1].weight_adr,
				      param->dict[1].format_size,
				      param->dict[1].weight_size);
	dd_HOG_send_request(&hog[1]);

	/* wait for CoHOG-A interrupt */
	dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG0_PORT);
	hog_clear_int(&hog[0]);
	dma330_dmaflushp(inst, GDMAC_HOG0_PORT);

	/* wait for CoHOG-B interrupt */
	dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG1_PORT);
	hog_clear_int(&hog[1]);
	dma330_dmaflushp(inst, GDMAC_HOG1_PORT);

	for (n = param->layer_min; n <= param->layer_max; n++) {

		/* CoHOG-A execute */
		if (mode == ROI_MODE) {
			dd_HOG_config_classify_position(&hog[0],
							param->dict[0].dict_num,
							param->dict[0].
							cell_num_w,
							param->dict[0].
							cell_num_h,
							param->dict[0].
							cell_size_w,
							param->dict[0].
							cell_size_h,
							param->setting[n].
							roi_num[0],
							roi_list[0][n],
							param->setting[n].
							dst_dir_thr_adr,
							param->setting[n].
							input_image_pitch,
							param->setting[n].
							dst_adr[0]);
		}
		if (mode == REGION_MODE) {
			dd_HOG_config_classify_region(&hog[0],
						      param->dict[0].dict_num,
						      param->dict[0].cell_num_w,
						      param->dict[0].cell_num_h,
						      param->dict[0].
						      cell_size_w,
						      param->dict[0].
						      cell_size_h,
						      param->setting[n].
						      roi_num_w[0],
						      param->setting[n].
						      roi_num_h[0],
						      param->setting[n].
						      roi_stride_w[0],
						      param->setting[n].
						      roi_stride_h[0],
						      param->setting[n].
						      dst_dir_thr_adr,
						      param->setting[n].
						      input_image_pitch,
						      dir_image_out_width[n],
						      dir_image_out_height[n],
						      param->setting[n].
						      dst_adr[0]);
		}

		dd_HOG_send_request(&hog[0]);

		/* CoHOG-B execute */
		if (mode == ROI_MODE) {
			dd_HOG_config_classify_position(&hog[1],
							param->dict[1].dict_num,
							param->dict[1].
							cell_num_w,
							param->dict[1].
							cell_num_h,
							param->dict[1].
							cell_size_w,
							param->dict[1].
							cell_size_h,
							param->setting[n].
							roi_num[1],
							roi_list[1][n],
							param->setting[n].
							dst_dir_thr_adr,
							param->setting[n].
							input_image_pitch,
							param->setting[n].
							dst_adr[1]);
		}
		if (mode == REGION_MODE) {
			dd_HOG_config_classify_region(&hog[1],
						      param->dict[1].dict_num,
						      param->dict[1].cell_num_w,
						      param->dict[1].cell_num_h,
						      param->dict[1].
						      cell_size_w,
						      param->dict[1].
						      cell_size_h,
						      param->setting[n].
						      roi_num_w[1],
						      param->setting[n].
						      roi_num_h[1],
						      param->setting[n].
						      roi_stride_w[1],
						      param->setting[n].
						      roi_stride_h[1],
						      param->setting[n].
						      dst_dir_thr_adr,
						      param->setting[n].
						      input_image_pitch,
						      dir_image_out_width[n],
						      dir_image_out_height[n],
						      param->setting[n].
						      dst_adr[1]);
		}

		dd_HOG_send_request(&hog[1]);

		/* wait for CoHOG-A */
		dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG0_PORT);
		hog_clear_int(&hog[0]);
		dma330_dmaflushp(inst, GDMAC_HOG0_PORT);

		/* wait for CoHOG-B */
		dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG1_PORT);
		hog_clear_int(&hog[1]);
		dma330_dmaflushp(inst, GDMAC_HOG1_PORT);
	}

	/* gdmac interrupt */
	dma330_dmasev(inst, GDMAC_INT1);
	dma330_dmaend(inst);

err:
	return ret;
}

/**************************************************/
/*
 * @brief hand_detect_isolate_create_instructions_one_hand
 *
 * @param inst
 * @param hog[]
 * @param dict
 * @param filter
 * @param param
 * @param mode
 *
 */
/**************************************************/
int hand_detect_isolate_create_instructions_one_hand(gdmac_inst *instructions[],
						     struct hog_dev hog[],
						     struct dict_dev *dict,
						     struct filter_dev *filter,
						     gdmac_hand_detect_isolate
						     *param, int32_t mode)
{
	int trans = 0;
	unsigned int n;
	int ret = 0;
	gdmac_inst *inst;

	/* copy roi list */
	if (mode == ROI_MODE) {
		for (n = param->layer_min; n <= param->layer_max; n++) {
			kfree(roi_list[0][n]);
			roi_list[0][n] =
			    kmalloc(sizeof(struct roi_coord) *
				    param->setting[n].roi_num[0], GFP_KERNEL);
			if (!roi_list[0][n]) {
				ret = -ENOMEM;
				goto err;
			}
			if (copy_from_user
			    ((void *)roi_list[0][n],
			     (const void __user *)(UINT)param->setting[n].
			     roi_list[0],
			     sizeof(struct roi_coord) *
			     param->setting[n].roi_num[0])) {
				pr_err("%s:copy_from_user failed roi_list\n",
				       GDMAC_HAND_DETECT_ISOLATE_NAME);
				ret = -ENOMEM;
				goto err;
			}
		}
	}

	/* --- cvia ------------------------------------------------------------- */
	for (n = param->layer_min; n <= param->layer_max; n++) {
		inst = instructions[trans];
		gdmac_clear(inst);

		filter->inst = inst;

		/* init peripherals */
		dma330_dmaflushp(inst, GDMAC_CVIA_PORT);

		/* execute filter */
		sl_gdmac_sobel_direction3x3_and_intensity_with_threshold(filter,
									 param->
									 setting
									 [n].
									 dst_dir_thr_adr,
									 param->
									 setting
									 [n].
									 dst_dir_nothr_adr,
									 param->
									 setting
									 [n].
									 dst_dir_int_adr,
									 param->
									 setting
									 [n].
									 input_image_adr,
									 dir_image_in_width
									 [n],
									 dir_image_out_height
									 [n],
									 param->
									 setting
									 [n].
									 input_image_pitch,
									 param->
									 setting
									 [n].
									 threshold);
		/* wait for filter interrupt */
		dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_CVIA_PORT);
		filter_clear_int(filter);
		dma330_dmaflushp(inst, GDMAC_CVIA_PORT);

		/* gdmac interrupt */
		dma330_dmasev(inst, GDMAC_INT1);
		dma330_dmaend(inst);

		trans++;
	}

	/* --- hog ------------------------------------------------------------- */
	inst = instructions[trans];
	gdmac_clear(inst);

	hog[0].inst = inst;
	hog[1].inst = inst;

	/* initialize peripherals */
	dma330_dmaflushp(inst, GDMAC_HOG0_PORT);
	dma330_dmaflushp(inst, GDMAC_HOG1_PORT);

	/* set dict bank mode */
	gdmac_write_register(inst, DICT_BASE + DICT_CTRL_OFFSET,
			     HOG_DICT_BANK_MODE1);

	/* CoHOG0 dictionary load */
	dd_HOG_config_load_dictionary(&hog[0],
				      param->dict[0].dict_num,
				      param->dict[0].cell_num_w,
				      param->dict[0].cell_num_h,
				      param->dict[0].cell_size_w,
				      param->dict[0].cell_size_h,
				      param->dict[0].format_adr,
				      param->dict[0].weight_adr,
				      param->dict[0].format_size,
				      param->dict[0].weight_size);
	dd_HOG_send_request(&hog[0]);

	/* CoHOG1 dictionary load */
	dd_HOG_config_load_dictionary(&hog[1],
				      param->dict[0].dict_num,
				      param->dict[0].cell_num_w,
				      param->dict[0].cell_num_h,
				      param->dict[0].cell_size_w,
				      param->dict[0].cell_size_h,
				      param->dict[0].format_adr,
				      param->dict[0].weight_adr,
				      param->dict[0].format_size,
				      param->dict[0].weight_size);
	dd_HOG_send_request(&hog[1]);

	/* wait for CoHOG0 interrupt */
	dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG0_PORT);
	hog_clear_int(&hog[0]);
	dma330_dmaflushp(inst, GDMAC_HOG0_PORT);

	/* wait for CoHOG1 interrupt */
	dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG1_PORT);
	hog_clear_int(&hog[1]);
	dma330_dmaflushp(inst, GDMAC_HOG1_PORT);

	for (n = param->layer_min; n <= param->layer_max; n += 2) {
		/* CoHOG0 execute */
		if (mode == ROI_MODE) {
			dd_HOG_config_classify_position(&hog[0],
							param->dict[0].dict_num,
							param->dict[0].
							cell_num_w,
							param->dict[0].
							cell_num_h,
							param->dict[0].
							cell_size_w,
							param->dict[0].
							cell_size_h,
							param->setting[n].
							roi_num[0],
							roi_list[0][n],
							param->setting[n].
							dst_dir_thr_adr,
							param->setting[n].
							input_image_pitch,
							param->setting[n].
							dst_adr[0]);
		}
		if (mode == REGION_MODE) {
			dd_HOG_config_classify_region(&hog[0],
						      param->dict[0].dict_num,
						      param->dict[0].cell_num_w,
						      param->dict[0].cell_num_h,
						      param->dict[0].
						      cell_size_w,
						      param->dict[0].
						      cell_size_h,
						      param->setting[n].
						      roi_num_w[0],
						      param->setting[n].
						      roi_num_h[0],
						      param->setting[n].
						      roi_stride_w[0],
						      param->setting[n].
						      roi_stride_h[0],
						      param->setting[n].
						      dst_dir_thr_adr,
						      param->setting[n].
						      input_image_pitch,
						      dir_image_out_width[n],
						      dir_image_out_height[n],
						      param->setting[n].
						      dst_adr[0]);
		}
		dd_HOG_send_request(&hog[0]);

		if ((n + 1) <= param->layer_max) {
			/* CoHOG1 execute */
			if (mode == ROI_MODE) {
				dd_HOG_config_classify_position(&hog[1],
								param->dict
								[0].dict_num,
								param->dict
								[0].cell_num_w,
								param->dict
								[0].cell_num_h,
								param->dict
								[0].cell_size_w,
								param->dict
								[0].cell_size_h,
								param->setting[n
									       +
									       1].
								roi_num[0],
								roi_list[0][n +
									    1],
								param->
								setting[n +
									1].
								dst_dir_thr_adr,
								param->
								setting[n +
									1].
								input_image_pitch,
								param->
								setting[n +
									1].
								dst_adr[0]);
			}
			if (mode == REGION_MODE) {
				dd_HOG_config_classify_region(&hog[1],
							      param->dict[0].
							      dict_num,
							      param->dict[0].
							      cell_num_w,
							      param->dict[0].
							      cell_num_h,
							      param->dict[0].
							      cell_size_w,
							      param->dict[0].
							      cell_size_h,
							      param->setting[n +
									     1].
							      roi_num_w[0],
							      param->setting[n +
									     1].
							      roi_num_h[0],
							      param->setting[n +
									     1].
							      roi_stride_w[0],
							      param->setting[n +
									     1].
							      roi_stride_h[0],
							      param->setting[n +
									     1].
							      dst_dir_thr_adr,
							      param->setting[n +
									     1].
							      input_image_pitch,
							      dir_image_out_width
							      [n],
							      dir_image_out_height
							      [n],
							      param->setting[n +
									     1].
							      dst_adr[0]);
			}
			dd_HOG_send_request(&hog[1]);
		}

		/* wait for CoHOG0 interrupt */
		dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG0_PORT);
		hog_clear_int(&hog[0]);
		dma330_dmaflushp(inst, GDMAC_HOG0_PORT);

		if ((n + 1) <= param->layer_max) {
			/* wait for CoHOG1 interrupt */
			dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG1_PORT);
			hog_clear_int(&hog[1]);
			dma330_dmaflushp(inst, GDMAC_HOG1_PORT);
		}
	}

	/* gdmac interrupt */
	dma330_dmasev(inst, GDMAC_INT1);
	dma330_dmaend(inst);

err:
	return ret;
}

/**************************************************/
/*
 * @brief hand_detect_isolate_create_instructions_single
 *
 * @param inst
 * @param hog[]
 * @param dict
 * @param filter
 * @param param
 * @param mode
 *
 */
/**************************************************/
int hand_detect_isolate_create_instructions_single(gdmac_inst *instructions[],
						   struct hog_dev hog[],
						   struct dict_dev *dict,
						   struct filter_dev *filter,
						   gdmac_hand_detect_isolate
						   *param, int32_t mode)
{
	int trans = 0;
	unsigned int n;
	int ret = 0;
	gdmac_inst *inst;

	/* copy roi list */
	if (mode == ROI_MODE) {
		for (n = param->layer_min; n <= param->layer_max; n++) {
			kfree(roi_list[0][n]);
			roi_list[0][n] =
			    kmalloc(sizeof(struct roi_coord) *
				    param->setting[n].roi_num[0], GFP_KERNEL);
			if (!roi_list[0][n]) {
				ret = -ENOMEM;
				goto err;
			}
			if (copy_from_user
			    ((void *)roi_list[0][n],
			     (const void __user *)(UINT)param->setting[n].
			     roi_list[0],
			     sizeof(struct roi_coord) *
			     param->setting[n].roi_num[0])) {
				pr_err("%s:copy_from_user failed roi_list\n",
				       GDMAC_HAND_DETECT_ISOLATE_NAME);
				ret = -ENOMEM;
				goto err;
			}
		}
	}

	/* --- cvia ------------------------------------------------------------- */
	for (n = param->layer_min; n <= param->layer_max; n++) {
		inst = instructions[trans];
		gdmac_clear(inst);

		filter->inst = inst;

		/* init peripherals */
		dma330_dmaflushp(inst, GDMAC_CVIA_PORT);

		/* execute filter */
		sl_gdmac_sobel_direction3x3_and_intensity_with_threshold(filter,
									 param->
									 setting
									 [n].
									 dst_dir_thr_adr,
									 param->
									 setting
									 [n].
									 dst_dir_nothr_adr,
									 param->
									 setting
									 [n].
									 dst_dir_int_adr,
									 param->
									 setting
									 [n].
									 input_image_adr,
									 dir_image_in_width
									 [n],
									 dir_image_out_height
									 [n],
									 param->
									 setting
									 [n].
									 input_image_pitch,
									 param->
									 setting
									 [n].
									 threshold);
		/* wait for filter interrupt */
		dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_CVIA_PORT);
		filter_clear_int(filter);
		dma330_dmaflushp(inst, GDMAC_CVIA_PORT);

		/* gdmac interrupt */
		dma330_dmasev(inst, GDMAC_INT1);
		dma330_dmaend(inst);

		trans++;
	}

	/* --- hog ------------------------------------------------------------- */
	inst = instructions[trans];
	gdmac_clear(inst);

	hog[0].inst = inst;

	/* initialize peripherals */
	dma330_dmaflushp(inst, GDMAC_HOG0_PORT);

	/* set dict bank mode */
	gdmac_write_register(inst, DICT_BASE + DICT_CTRL_OFFSET,
			     HOG_DICT_BANK_MODE0);

	/* CoHOG0 dictionary load */
	dd_HOG_config_load_dictionary(&hog[0],
				      param->dict[0].dict_num,
				      param->dict[0].cell_num_w,
				      param->dict[0].cell_num_h,
				      param->dict[0].cell_size_w,
				      param->dict[0].cell_size_h,
				      param->dict[0].format_adr,
				      param->dict[0].weight_adr,
				      param->dict[0].format_size,
				      param->dict[0].weight_size);
	dd_HOG_send_request(&hog[0]);

	/* wait for CoHOG0 interrupt */
	dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG0_PORT);
	hog_clear_int(&hog[0]);
	dma330_dmaflushp(inst, GDMAC_HOG0_PORT);

	for (n = param->layer_min; n <= param->layer_max; n++) {
		/* CoHOG0 execute */
		if (mode == ROI_MODE) {
			dd_HOG_config_classify_position(&hog[0],
							param->dict[0].dict_num,
							param->dict[0].
							cell_num_w,
							param->dict[0].
							cell_num_h,
							param->dict[0].
							cell_size_w,
							param->dict[0].
							cell_size_h,
							param->setting[n].
							roi_num[0],
							roi_list[0][n],
							param->setting[n].
							dst_dir_thr_adr,
							param->setting[n].
							input_image_pitch,
							param->setting[n].
							dst_adr[0]);
		}
		if (mode == REGION_MODE) {
			dd_HOG_config_classify_region(&hog[0],
						      param->dict[0].dict_num,
						      param->dict[0].cell_num_w,
						      param->dict[0].cell_num_h,
						      param->dict[0].
						      cell_size_w,
						      param->dict[0].
						      cell_size_h,
						      param->setting[n].
						      roi_num_w[0],
						      param->setting[n].
						      roi_num_h[0],
						      param->setting[n].
						      roi_stride_w[0],
						      param->setting[n].
						      roi_stride_h[0],
						      param->setting[n].
						      dst_dir_thr_adr,
						      param->setting[n].
						      input_image_pitch,
						      dir_image_out_width[n],
						      dir_image_out_height[n],
						      param->setting[n].
						      dst_adr[0]);
		}
		dd_HOG_send_request(&hog[0]);

		/* wait for CoHOG0 interrupt */
		dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_HOG0_PORT);
		hog_clear_int(&hog[0]);
		dma330_dmaflushp(inst, GDMAC_HOG0_PORT);
	}

	/* gdmac interrupt */
	dma330_dmasev(inst, GDMAC_INT1);
	dma330_dmaend(inst);

err:
	return ret;
}
