/*
 * drivers/staging/applite/veu/ve_resources.c
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

#include "ve_resources.h"
#include "ve_access.h"
#include "ve_task.h"
#include "ve_trace.h"

/* profile */
static const uint32_t profile_idc[PROFILE_NUM] = {
	PROF_BASELINE,		/* Baseline */
	PROF_MAIN,		/* Main */
	PROF_HIGH,		/* High */
};

static const uint32_t level_idc[LEVEL_NUM] = {
	LEVEL_1_2,	/* Level 1.2 */
	LEVEL_3_0,	/* Level 3.0 */
	LEVEL_3_1,	/* Level 3.1 */
	LEVEL_4_0,	/* Level 4.0 */
	LEVEL_4_1,	/* Level 4.1 */
	LEVEL_4_2,	/* Level 4.2 */
};

struct level_table {
	uint32_t idc;		/* level_idc */
	uint32_t max_fs;	/* MaxFs */
	uint32_t sqrt_max_fsx8;	/* sqrt(MaxFs x 8) */
	uint32_t max_mbpsx100;	/* MaxMBPS x 100 */
	uint32_t max_br;	/* MaxBR */
	uint32_t max_cpb;	/* MaxCPB */
};

static const struct level_table level_param[LEVEL_NUM] = {
	{12, 396, 56, 600000, 384, 1000},
	{30, 1620, 113, 4050000, 10000, 10000},
	{31, 3600, 169, 10800000, 14000, 14000},
	{40, 8160, 255, 24576000, 20000, 20000},
	{41, 8160, 255, 24576000, 50000, 62500},
	{42, 8160, 255, 52224000, 50000, 62500},
};

static uint32_t get_mb_width(uint32_t h_size);
static uint32_t get_mb_height(uint32_t v_size);
static uint32_t get_mb_num(uint32_t h_size, uint32_t v_size);
static void get_buf_ptr(struct ve_address ctl_addr, struct ve_address addr,
				uint32_t offset, uint8_t **rp, uint8_t **wp);
static enum ve_result get_level_idx(uint32_t level_idc, uint32_t *level_idx);
static uint32_t get_level(uint32_t h_size, uint32_t v_size, uint32_t kbps,
				enum ve_frame_rate fps, uint32_t factor);
static enum ve_result get_frame_ratex100(enum ve_frame_rate frame_rate,
						uint32_t *frame_ratex100);
static uint32_t get_n(enum ve_frame_rate fps);
static void overwrite_param_in_baseline_pf(struct ve_param *param);
static void overwrite_param_in_main_pf(struct ve_param *param);

/* check horizontal/vertical size */
enum ve_result rsc_chk_hv_sz(uint32_t h_size, uint32_t v_size)
{
	enum ve_result ret = VE_ERROR_PARAMETERS;

	if (h_size < MIN_H_SZ || MAX_H_SZ < h_size || h_size % 2)
		goto out;
	if (v_size < MIN_V_SZ || MAX_V_SZ < v_size || v_size % 2)
		goto out;

	ret = VE_OK;

out:
	return ret;
}

/* get control buffer size */
uint32_t rsc_get_ctrl_buf_size(void)
{
	/* rcs_fifo_base x 2 */
	return (uint32_t)(sizeof(struct rsc_fifo_base) << 1);
}

/* get output(nal) buffer size */
uint32_t rsc_get_output_buf_size(uint32_t h_size, uint32_t v_size)
{
	uint32_t buf_size;
	uint32_t tmp;

	buf_size = rsc_get_1frame_out_buf_size(h_size, v_size)
						* (2 + FW_QUEUE_NUM + 1);

	/* 16 byte align (FW constraint) */
	tmp = buf_size % 16;
	if (tmp != 0)
		buf_size += (16 - tmp);

	return buf_size;
}

/* get nal info buffer size */
uint32_t rsc_get_nal_inf_buf_size(void)
{
	return LINUX_PAGE_1MB;
}

/* get work buffer size */
uint32_t rsc_get_work_buf_size(uint32_t h_size, uint32_t v_size)
{
	uint32_t mb_num;
	uint32_t buf_size;
	uint32_t tmp;

	mb_num = get_mb_num(h_size, v_size);
	buf_size = (BIN_BUF_FIXED_SZ + BUF_FIXED_SZ_PER_FRM * mb_num)
						* (2 + FW_QUEUE_NUM + 1);

	/* 16 byte align (FW constraint) */
	tmp = buf_size % 16;
	if (tmp != 0)
		buf_size += (16 - tmp);

	/* work mem + bin */
	return WORK_MEM_SZ + buf_size;
}

/* get reference buffer size */
uint32_t rsc_get_ref_buf_size(uint32_t m)
{
	return REF_IMG_SZ;
}

/* check VE_BUF_CTL, VE_BUF_OUT, VE_BUF_INF, VE_BUF_WRK and VE_BUF_REF */
enum ve_result rsc_chk_io_buf_mem(const struct ve_io_buf_area *buf)
{
	enum ve_result ret = VE_OK;

	/* check range */
	/* physical */
	ret = acs_chk_data_in_dram_range(buf->control.addr.p_addr);
	ret |= acs_chk_data_in_dram_range(buf->output.addr.p_addr);
	ret |= acs_chk_data_in_dram_range(buf->nal.addr.p_addr);
	ret |= acs_chk_data_in_dram_range(buf->work.addr.p_addr);
	ret |= acs_chk_addr_zero(buf->reference.addr);
	/* virtual */
	ret |= acs_chk_addr_zero(buf->control.addr.v_addr);
	ret |= acs_chk_addr_zero(buf->output.addr.v_addr);
	ret |= acs_chk_addr_zero(buf->nal.addr.v_addr);
	ret |= acs_chk_addr_zero(buf->work.addr.v_addr);
	if (ret != VE_OK)
		return ret;

	/* check align */
	/* physical */
	ret |= acs_chk_align(buf->control.addr.p_addr, 0x40);
	ret |= acs_chk_align(buf->output.addr.p_addr, 0x10);
	ret |= acs_chk_align(buf->nal.addr.p_addr, 0x10);
	ret |= acs_chk_align(buf->work.addr.p_addr, 0x10);
	ret |= acs_chk_align(buf->reference.addr, 0x400);
	/* virtual */
	ret |= acs_chk_align(buf->control.addr.v_addr, 0x40);
	ret |= acs_chk_align(buf->output.addr.v_addr, 0x10);
	ret |= acs_chk_align(buf->nal.addr.v_addr, 0x10);
	ret |= acs_chk_align(buf->work.addr.v_addr, 0x10);
	/* size */
	ret |= acs_chk_align(buf->output.size, 0x10);
	ret |= acs_chk_align(buf->work.size, 0x10);

	/* check crossing memory */
	ret |= acs_chk_crossing_memory(buf->output.addr.p_addr,
						buf->output.size);
	ret |= acs_chk_crossing_memory(buf->nal.addr.p_addr,
						buf->nal.size);
	ret |= acs_chk_crossing_memory(buf->work.addr.p_addr,
						buf->work.size);

	return ret;
}

/* connect io buffer */
void rsc_connect_io_buf(struct ve_io_buf_area *io_buff,
				struct rsc_fifo *output, struct rsc_fifo *nal)
{
	uint32_t output_base_addr;
	uint32_t nal_base_addr;
	uint32_t tmp;

	/* | fifo(output) | fifo(info) | fifobase(output) | fifobase(info) | */
	output_base_addr = (uint32_t)io_buff->control.addr.v_addr;
	nal_base_addr = output_base_addr + sizeof(struct rsc_fifo_base);

	output->base = (struct rsc_fifo_base *)output_base_addr;
	nal->base = (struct rsc_fifo_base *)nal_base_addr;

	/* connect buffers */
	tmp = acs_trans_p2vbus_addr(io_buff->output.addr.p_addr);
	output->base->base = (uint8_t *)tmp;
	output->base->size = VE_REV(io_buff->output.size);

	tmp = acs_trans_p2vbus_addr(io_buff->nal.addr.p_addr);
	nal->base->base = (uint8_t *)tmp;
	nal->base->size = VE_REV(io_buff->nal.size);
}

/* get 1 frame output buffer size */
uint32_t rsc_get_1frame_out_buf_size(uint32_t h_size, uint32_t v_size)
{
	uint32_t mb_num;

	mb_num = get_mb_num(h_size, v_size);

	return OUT_BUF_FIXED_SZ + BUF_FIXED_SZ_PER_FRM * mb_num;
}


/* get read size for next encoding */
uint32_t rsc_get_read_size_for_next_enc(struct ve_io_buf_area *io_buff,
							uint32_t one_frm_size)
{
	uint8_t *rp;
	uint8_t *wp;
	uint32_t empty_size;
	uint32_t need_size;
	uint32_t output_req_size = 0;
	uint32_t info_req_size = 0;
	uint32_t req_size = 0;
	uint32_t tmp;

	/* check output buf */
	get_buf_ptr(io_buff->control.addr, io_buff->output.addr, 0,
					(uint8_t **)&rp, (uint8_t **)&wp);

	if (wp == rp)
		empty_size = io_buff->output.size;
	else if (wp > rp)
		empty_size = io_buff->output.size \
					- ((uint32_t)wp - (uint32_t)rp);
	else
		empty_size = (uint32_t)rp - (uint32_t)wp;

	need_size = one_frm_size;

	if (empty_size >= need_size)
		output_req_size = 0;
	else
		output_req_size = need_size - empty_size;

	/* check nal info buf */
	get_buf_ptr(io_buff->control.addr, io_buff->nal.addr,
					(uint32_t)sizeof(struct rsc_fifo_base),
					(uint8_t **)&rp, (uint8_t **)&wp);

	if (wp == rp)
		empty_size = io_buff->nal.size;
	else if (wp > rp)
		empty_size = io_buff->nal.size \
					- ((uint32_t)wp - (uint32_t)rp);
	else
		empty_size = (uint32_t)rp - (uint32_t)wp;

	/* calculate info_req_size */
	tmp = empty_size / NAL_INFO_ONE_SZ;
	if (tmp >= FW_QUEUE_NUM)
		info_req_size = 0;
	else
		info_req_size = one_frm_size * (FW_QUEUE_NUM - tmp);

	/* select req_size */
	if (output_req_size > info_req_size)
		req_size = output_req_size;
	else
		req_size = info_req_size;

	return req_size;
}

/* set default encode parameters */
enum ve_result rsc_set_default_param(uint32_t h_size, uint32_t v_size,
				uint32_t kbps, enum ve_frame_rate fps,
				enum ve_profile pf, struct ve_param *param)
{
	enum ve_result ret = VE_ERROR_PARAMETERS;
	uint32_t idx;
	uint32_t level;
	uint32_t n;
	uint32_t factor;

	/* check argument */
	if (rsc_chk_hv_sz(h_size, v_size) != VE_OK)
		goto out;
	if (kbps < KBPS_LOWER || KBPS_UPPER < kbps)
		goto out;
	if (pf > VE_PF_HIGH)
		goto out;

	/* get value */
	n = get_n(fps);		/* include checking fps */
	if (n == N_INVALID)
		goto out;

	if (pf == VE_PF_BASELINE || pf == VE_PF_MAIN)
		factor = FACTOR_LOW_PROF;
	else
		factor = FACTOR_HIGH_PROF;

	level = get_level(h_size, v_size, kbps, fps, factor);
	if (level == LEVEL_INVALID)
		goto out;
	if (get_level_idx(level, &idx) != VE_OK)
		goto out;

	param->output_mode = 0;
	param->level = level;
	param->horizontal_pixels = h_size;
	param->vertical_pixels = v_size;
	param->frame_rate = fps;
	param->kbps = kbps;
	param->max_kbps = factor * level_param[idx].max_br / 1000;
	param->cpb_size_kbits = 0;
	param->rate_control_mode = RCM_CBR;
	param->m = 3;
	param->n = n;
	param->idr_freq = 0;
	param->picture_struct = PICST_FRM;
	param->slice_num_minus1 = 0;
	param->scaling_matrix = 1;
	param->entropy_coding = CODE_CABAC;
	param->weighted_pred = 1;
	param->reference_b = 1;
	param->inter_view_pred = 0;
	param->vui_parameters = 0;
	param->sei0 = SEI_INVALID;

	switch (pf) {
	case VE_PF_BASELINE:
		overwrite_param_in_baseline_pf(param);
		param->profile = PROF_BASELINE;
		break;
	case VE_PF_MAIN:
		overwrite_param_in_main_pf(param);
		param->profile = PROF_MAIN;
		break;
	default:
		param->profile = PROF_HIGH;
		break;
	}

	VELOGTRACE(VE_LT_PRM_OUTMODE, param->output_mode);
	VELOGTRACE(VE_LT_PRM_PROFILE, param->profile);
	VELOGTRACE(VE_LT_PRM_LEVEL, param->level);
	VELOGTRACE(VE_LT_PRM_H_SIZE, param->horizontal_pixels);
	VELOGTRACE(VE_LT_PRM_V_SIZE, param->vertical_pixels);
	VELOGTRACE(VE_LT_PRM_FPS, param->frame_rate);
	VELOGTRACE(VE_LT_PRM_KBPS, param->kbps);
	VELOGTRACE(VE_LT_PRM_MAXKBPS, param->max_kbps);
	VELOGTRACE(VE_LT_PRM_CPB_KSIZE, param->cpb_size_kbits);
	VELOGTRACE(VE_LT_PRM_RCM, param->rate_control_mode);
	VELOGTRACE(VE_LT_PRM_M, param->m);
	VELOGTRACE(VE_LT_PRM_N, param->n);
	VELOGTRACE(VE_LT_PRM_IDR_FREQ, param->idr_freq);
	VELOGTRACE(VE_LT_PRM_PIC_STRUCT, param->picture_struct);
	VELOGTRACE(VE_LT_PRM_SLICE_NUM_1, param->slice_num_minus1);
	VELOGTRACE(VE_LT_PRM_SCLMTX, param->scaling_matrix);
	VELOGTRACE(VE_LT_PRM_CODING, param->entropy_coding);
	VELOGTRACE(VE_LT_PRM_W_PRED, param->weighted_pred);
	VELOGTRACE(VE_LT_PRM_REF_B, param->reference_b);
	VELOGTRACE(VE_LT_PRM_INTER_VIEW, param->inter_view_pred);
	VELOGTRACE(VE_LT_PRM_VUI_PRM, param->vui_parameters);
	VELOGTRACE(VE_LT_PRM_SEI0, param->sei0);

#if 0
	/* VUI */
	param->aspect_ratio_info_present_flag = 1;
	param->aspect_ratio_idc = 1;
	param->sar_width = 0;
	param->sar_height = 0;
	param->overscan_info_present_flag = 0;
	param->overscan_appropriate_flag = 0;
	param->video_signal_type_present_flag = 1;
	param->video_format = 5;
	param->video_full_range_flag = 0;
	param->colour_description_present_flag = 1;
	param->colour_primaries = 1;
	param->transfer_characteristics = 1;
	param->matrix_coefficients = 1;
	param->chroma_loc_info_present_flag = 0;
	param->chroma_sample_loc_type_top_field = 0;
	param->chroma_sample_loc_type_bottom_field = 0;
	param->timing_info_present_flag = 1;
	param->num_units_in_tick = 1001;
	param->fixed_frame_rate_flag = 1;
	param->nal_hrd_parameters_present_flag = 1;
	param->vcl_hrd_parameters_present_flag = 0;
	param->low_delay_hrd_flag = 0;
	param->pic_struct_present_flag = 1;
	param->bitstream_restriction_flag = 0;
#endif

	ret = VE_OK;

out:
	return ret;
}

/* check parameters */
enum ve_result rsc_chk_param(const struct ve_param *param)
{
	enum ve_result ret = VE_ERROR_PARAMETERS;
	uint32_t i;
	uint32_t mb_width;
	uint32_t mb_height;
	uint32_t mb_num;
	uint32_t idx;
	uint32_t factor;
	uint32_t tmp;

	/* output_mode */
	if (param->output_mode != 0)
		goto out;

	/* profile */
	for (i = 0; i < PROFILE_NUM; i++) {
		if (param->profile == profile_idc[i])
			break;
	}
	if (i == PROFILE_NUM)
		goto out;

	/* level */
	for (i = 0; i < LEVEL_NUM; i++) {
		if (param->level == level_idc[i])
			break;
	}
	if (i == LEVEL_NUM)
		goto out;

	/* horizontal/vertical_pixels */
	if (rsc_chk_hv_sz(param->horizontal_pixels,
					param->vertical_pixels) != VE_OK)
		goto out;

	/* get level limit */
	if (get_level_idx(param->level, &idx) != VE_OK)
		goto out;
	mb_width = get_mb_width(param->horizontal_pixels);
	mb_height = get_mb_height(param->vertical_pixels);
	mb_num = get_mb_num(param->horizontal_pixels, param->vertical_pixels);

	/* check MaxFs */
	if (mb_num > level_param[idx].max_fs)
		goto out;
	else if (mb_width > level_param[idx].sqrt_max_fsx8
			|| mb_height > level_param[idx].sqrt_max_fsx8)
		goto out;

	/* frame_rate */
	if (get_frame_ratex100(param->frame_rate, &tmp) != VE_OK)
		goto out;

	if (mb_num * tmp > level_param[idx].max_mbpsx100)
		goto out;

	/* kbps */
	if (param->profile == PROF_BASELINE
					|| param->profile == PROF_MAIN)
		factor = FACTOR_LOW_PROF;
	else
		factor = FACTOR_HIGH_PROF;

	if (param->kbps != 0) {
		tmp = factor * level_param[idx].max_br / 1000;
		if (param->kbps < KBPS_LOWER || KBPS_UPPER < param->kbps)
			goto out;
		else if (param->kbps > tmp)
			goto out;
	}

	/* cpb_size_kbits */
	if (param->cpb_size_kbits != 0)
		goto out;

	/* rate_control_mode */
	if (param->rate_control_mode > RCM_CBR)
		goto out;

	/* m */
	if (param->profile == PROF_BASELINE)
		tmp = 1;
	else
		tmp = 3;

	if (param->m == 0 || param->m > tmp)
		goto out;

	/* n */
	if (param->n > MAX_N)
		goto out;
	else if (param->n % param->m != 0)
		goto out;

	/* idr_freq */
	if (param->idr_freq > MAX_IDR_FREQ)
		goto out;

	/* picture_struct */
	if (param->picture_struct != PICST_FRM)
		goto out;

	/* slice_num_minus1 */
	if (param->slice_num_minus1 > MAX_SLC_NUM_MINUS1)
		goto out;

	/* scaling_matrix */
	if (param->scaling_matrix > 1)
		goto out;
	else if (param->profile != PROF_HIGH && param->scaling_matrix != 0)
		goto out;

	/* entropy_coding */
	if (param->entropy_coding > CODE_CABAC)
		goto out;
	else if (param->profile == PROF_BASELINE
					&& param->entropy_coding != CODE_CAVLC)
		goto out;

	/* weighted_pred */
	if (param->weighted_pred > 1)
		goto out;
	else if (param->m < 2 && param->weighted_pred != 0)
		goto out;

	/* reference_b */
	if (param->reference_b > 1)
		goto out;
	else if (param->m != 3 && param->reference_b != 0)
		goto out;

	/* inter_view_pred */
	if (param->inter_view_pred != 0)
		goto out;

	/* vui_parameters */
	if (param->vui_parameters > 1)
		goto out;

	/* sei0 */
	if (param->sei0 > SEI_ALL) {
		goto out;
	} else if (param->sei0 & SEI_BUF_PERIOD) {
		if (param->vui_parameters == 0
				|| param->pic_struct_present_flag == 0)
			goto out;
	}

	ret = VE_OK;

out:
	return ret;
}

/* check vui parameters */
enum ve_result rsc_chk_vui_param(const struct ve_param *param)
{
	enum ve_result ret = VE_ERROR_PARAMETERS;

	/* aspect_ratio_info_present_flag */
	if (param->aspect_ratio_info_present_flag > 1)
		goto out;

	/* aspect_ratio_idc */
	if (param->aspect_ratio_info_present_flag) {
		if (param->aspect_ratio_idc > EXTENDED_SAR) {
			goto out;
		} else if (param->aspect_ratio_idc == EXTENDED_SAR) {
			/* sar_width, sar_height */
			if (param->sar_width == 0 || param->sar_height == 0)
				goto out;
		}
	}

	/* overscan_info_present_flag */
	if (param->overscan_info_present_flag > 1)
		goto out;

	/* overscan_appropriate_flag */
	if (param->overscan_info_present_flag) {
		if (param->overscan_appropriate_flag > 1)
			goto out;
	}

	/* video_signal_type_present_flag */
	if (param->video_signal_type_present_flag > 1)
		goto out;

	if (param->video_signal_type_present_flag) {
		/* video_format */
		if (param->video_format > MAX_VIDEO_FORMAT_VAL)
			goto out;

		/* video_full_range_flag */
		if (param->video_full_range_flag > 1)
			goto out;

		/* colour_description_present_flag */
		if (param->colour_description_present_flag > 1)
			goto out;

		if (param->colour_description_present_flag) {
			/* colour_primaries */
			if (param->colour_primaries > MAX_COLOUR_DESC_VAL)
				goto out;

			/* transfer_characteristics */
			if (param->transfer_characteristics
							> MAX_COLOUR_DESC_VAL)
				goto out;

			/* matrix_coefficients */
			if (param->matrix_coefficients > MAX_COLOUR_DESC_VAL)
				goto out;
		}
	}

	/* chroma_loc_info_present_flag */
	if (param->chroma_loc_info_present_flag > 1)
		goto out;

	if (param->chroma_loc_info_present_flag) {
		/* chroma_sample_loc_type_top_field */
		if (param->chroma_sample_loc_type_top_field > MAX_C_LOC_VAL)
			goto out;

		/* chroma_sample_loc_type_bottom_field */
		if (param->chroma_sample_loc_type_bottom_field > MAX_C_LOC_VAL)
			goto out;
	}

	/* timing_info_present_flag */
	if (param->timing_info_present_flag > 1)
		goto out;

	if (param->timing_info_present_flag) {
		/* num_units_in_tick */
		if (param->num_units_in_tick == 0)
			goto out;

		/* time_scale */
		if (param->time_scale == 0)
			goto out;

		/* fixed_frame_rate_flag */
		if (param->fixed_frame_rate_flag > 1)
			goto out;
	}

	/* nal_hrd_parameters_present_flag */
	if (param->nal_hrd_parameters_present_flag > 1)
		goto out;

	/* vcl_hrd_parameters_present_flag(FW constraint) */
	if (param->vcl_hrd_parameters_present_flag != 0)
		goto out;

	if (param->nal_hrd_parameters_present_flag
				|| param->vcl_hrd_parameters_present_flag) {
		/* low_delay_hrd_flag */
		if (param->low_delay_hrd_flag > 1)
			goto out;
		else if (param->low_delay_hrd_flag
					&& param->timing_info_present_flag
					&& param->fixed_frame_rate_flag)
			goto out;
	}

	/* pic_struct_present_flag */
	if (param->pic_struct_present_flag > 1)
		goto out;

	/* bitstream_restriction_flag */
	if (param->bitstream_restriction_flag > 1)
		goto out;

	ret = VE_OK;

out:
	return ret;
}

/* calculate frame rate */
enum ve_result rsc_calc_frame_rate(enum ve_frame_rate frame_rate,
					uint32_t *num, uint32_t *denom)
{
	enum ve_result ret = VE_OK;

	switch (frame_rate) {
	case VE_FPS_11_98HZ:
		*num = 12;
		*denom = 1;
		break;
	case VE_FPS_14_98HZ:
		*num = 15;
		*denom = 1;
		break;
	case VE_FPS_15HZ:
		*num = 15;
		*denom = 0;
		break;
	case VE_FPS_23_97HZ:
		*num = 24;
		*denom = 1;
		break;
	case VE_FPS_24HZ:
		*num = 24;
		*denom = 0;
		break;
	case VE_FPS_25HZ:
		*num = 25;
		*denom = 0;
		break;
	case VE_FPS_29_97HZ:
		*num = 30;
		*denom = 1;
		break;
	case VE_FPS_30HZ:
		*num = 30;
		*denom = 0;
		break;
	case VE_FPS_47_95HZ:
		*num = 48;
		*denom = 1;
		break;
	case VE_FPS_48HZ:
		*num = 48;
		*denom = 0;
		break;
	case VE_FPS_50HZ:
		*num = 50;
		*denom = 0;
		break;
	case VE_FPS_59_94HZ:
		*num = 60;
		*denom = 1;
		break;
	case VE_FPS_60HZ:
		*num = 60;
		*denom = 0;
		break;
	default:
		ret = VE_ERROR_PARAMETERS;
		break;
	}
	return ret;
}

/* get and advance buf rp */
enum ve_result rsc_get_buf_rp(struct ve_io_buf_area *io_buff,
				uint32_t *curr_rp_addr, uint32_t *adv_rp_addr,
				uint32_t *adv_info_rp_addr,
				uint32_t *frm_id_upper, uint32_t *frm_id_lower,
				uint32_t *cont_id, uint8_t mode)
{
	enum ve_result ret = VE_OK;
	uint8_t *rp;
	uint8_t *wp;
	uint32_t tmp;
	uint32_t info_s_addr;
	uint32_t info_e_addr;

	get_buf_ptr(io_buff->control.addr, io_buff->nal.addr,
					(uint32_t)sizeof(struct rsc_fifo_base),
					(uint8_t **)&rp, (uint8_t **)&wp);

	if (rp == wp)
		return VE_ERROR_STATE;

	/* get current rp of output buffer from info fifo */
	*curr_rp_addr = acs_trans_vbus2v_addr(io_buff->output.addr,
				*(uint32_t *)(rp + NAL_INFO_ES_ADDR_OFS));
	*frm_id_upper = VE_REV(*(uint32_t *)(rp + NAL_INFO_FRM_ID_UPPER_OFS));
	*frm_id_lower = VE_REV(*(uint32_t *)(rp + NAL_INFO_FRM_ID_LOWER_OFS));

	/* search EOP */
	info_s_addr = io_buff->nal.addr.v_addr;
	info_e_addr = info_s_addr + io_buff->nal.size;

	*cont_id = 0xffffffffUL;
	do {
		tmp = VE_REV(*(uint32_t *)rp);
		if ((tmp & 0xffff0000UL) == CMN_EOP)
			break;
		if (*cont_id == 0xffffffffUL) {
			tmp &= 0xff1fffffUL;
			if (tmp == NAL_UNIT_TYPE_IDR
						|| tmp == NAL_UNIT_TYPE_PIC)
				*cont_id = tmp;
		}
		rp += NAL_INFO_ONE_CONT_SZ;
		if ((uint32_t)rp >= info_e_addr)
			rp = (uint8_t *)info_s_addr;
	} while (wp != rp);

	/* next es address */
	*adv_rp_addr = acs_trans_vbus2v_addr(io_buff->output.addr,
				*(uint32_t *)(rp + NAL_INFO_ES_ADDR_OFS));

	if (mode == NAL_INFO_ADV) {
		rp += NAL_INFO_ONE_CONT_SZ;
		if ((uint32_t)rp >= info_e_addr)
			rp = (uint8_t *)info_s_addr;
	}

	/* update info rp */
	*adv_info_rp_addr = (uint32_t)rp;

	return ret;
}

/* set buffer rp */
void rsc_set_buf_rp(struct ve_io_buf_area *io_buff,
					uint32_t out_addr, uint32_t inf_addr)
{
	struct rsc_fifo_base *base;

	/* output */
	base = (struct rsc_fifo_base *)(io_buff->control.addr.v_addr);
	base->read1.ptr = (uint8_t *)acs_trans_v2vbus_addr(
					io_buff->output.addr, out_addr);

	/* nal info */
	base = (struct rsc_fifo_base *)(io_buff->control.addr.v_addr +
						sizeof(struct rsc_fifo_base));
	base->read1.ptr = (uint8_t *)acs_trans_v2vbus_addr(
					io_buff->nal.addr, inf_addr);
}

static uint32_t get_mb_width(uint32_t h_size)
{
	return (h_size + 15) >> 4;
}

static uint32_t get_mb_height(uint32_t v_size)
{
	return (v_size + 15) >> 4;
}

static uint32_t get_mb_num(uint32_t h_size, uint32_t v_size)
{
	return get_mb_width(h_size) * get_mb_height(v_size);
}

static void get_buf_ptr(struct ve_address ctl_addr, struct ve_address addr,
				uint32_t offset, uint8_t **rp, uint8_t **wp)
{
	struct rsc_fifo_base *base;

	/* fifo */
	base = (struct rsc_fifo_base *)(ctl_addr.v_addr + offset);
	*rp = (uint8_t *)acs_trans_vbus2v_addr(addr, (uint32_t)base->read1.ptr);
	*wp = (uint8_t *)acs_trans_vbus2v_addr(addr, (uint32_t)base->write.ptr);
}

static enum ve_result get_level_idx(uint32_t level_idc, uint32_t *level_idx)
{
	enum ve_result ret = VE_ERROR_PARAMETERS;
	uint32_t i;

	for (i = 0; i < LEVEL_NUM; i++) {
		if (level_idc == level_param[i].idc) {
			ret = VE_OK;
			*level_idx = i;
			break;
		}
	}

	return ret;
}

static uint32_t get_level(uint32_t h_size, uint32_t v_size, uint32_t kbps,
				enum ve_frame_rate fps, uint32_t factor)
{
	uint32_t level = LEVEL_INVALID;
	uint32_t mb_num;
	uint32_t mbpsx100;
	uint32_t tmp;
	uint32_t i;

	mb_num = get_mb_num(h_size, v_size);
	if (get_frame_ratex100(fps, &mbpsx100) != VE_OK)
		goto out;
	mbpsx100 *= mb_num;

	for (i = 0; i < LEVEL_NUM; i++) {
		tmp = factor * level_param[i].max_br / 1000;
		if (mb_num <= level_param[i].max_fs
			&& mbpsx100 <= level_param[i].max_mbpsx100
							&& kbps <= tmp) {
			level = level_idc[i];
			break;
		}
	}

out:
	return level;
}

static enum ve_result get_frame_ratex100(enum ve_frame_rate frame_rate,
						uint32_t *frame_ratex100)
{
	enum ve_result ret = VE_OK;

	switch (frame_rate) {
	case VE_FPS_11_98HZ:
		*frame_ratex100 = 1198;
		break;
	case VE_FPS_14_98HZ:
		*frame_ratex100 = 1498;
		break;
	case VE_FPS_15HZ:
		*frame_ratex100 = 1500;
		break;
	case VE_FPS_23_97HZ:
		*frame_ratex100 = 2397;
		break;
	case VE_FPS_24HZ:
		*frame_ratex100 = 2400;
		break;
	case VE_FPS_25HZ:
		*frame_ratex100 = 2500;
		break;
	case VE_FPS_29_97HZ:
		*frame_ratex100 = 2997;
		break;
	case VE_FPS_30HZ:
		*frame_ratex100 = 3000;
		break;
	case VE_FPS_47_95HZ:
		*frame_ratex100 = 4795;
		break;
	case VE_FPS_48HZ:
		*frame_ratex100 = 4800;
		break;
	case VE_FPS_50HZ:
		*frame_ratex100 = 5000;
		break;
	case VE_FPS_59_94HZ:
		*frame_ratex100 = 5994;
		break;
	case VE_FPS_60HZ:
		*frame_ratex100 = 6000;
		break;
	default:
		ret = VE_ERROR_PARAMETERS;
		break;
	}

	return ret;
}

static uint32_t get_n(enum ve_frame_rate fps)
{
	uint32_t n = N_INVALID;
	uint32_t frame_ratex100;
	uint32_t tmp;

	if (get_frame_ratex100(fps, &frame_ratex100) != VE_OK)
		goto out;

	n = (uint32_t)(frame_ratex100 / 2 / 100);
	tmp = n % 3;
	if (tmp != 0)
		n += (3 - tmp);	/* fixed M == 3 */

out:
	return n;
}

static void overwrite_param_in_baseline_pf(struct ve_param *param)
{
	param->m = 1;
	param->scaling_matrix = 0;
	param->entropy_coding = CODE_CAVLC;
	param->weighted_pred = 0;
	param->reference_b = 0;
}

static void overwrite_param_in_main_pf(struct ve_param *param)
{
	param->scaling_matrix = 0;
}

