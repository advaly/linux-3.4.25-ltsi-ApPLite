/*
 * drivers/staging/applite/veu/ve_resources.h
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

#ifndef __VE_RESOURCES_H__
#define __VE_RESOURCES_H__

#include "ve_api.h"

/* parameters */
/* profile */
#define PROFILE_NUM		3
#define PROF_BASELINE		66
#define PROF_MAIN		77
#define PROF_HIGH		100
/* cpbBrNalFactor */
#define FACTOR_LOW_PROF		1200
#define FACTOR_HIGH_PROF	1500
/* level */
#define LEVEL_NUM	6
#define LEVEL_1_2	12
#define LEVEL_3_0	30
#define LEVEL_3_1	31
#define LEVEL_4_0	40
#define LEVEL_4_1	41
#define LEVEL_4_2	42
#define LEVEL_INVALID	0xffffffff
/* horizontal/vertical pixels */
#define MIN_H_SZ	320
#define MAX_H_SZ	1920
#define MIN_V_SZ	240
#define MAX_V_SZ	1088
/* kbps */
#define KBPS_LOWER	128
#define KBPS_UPPER	50000
/* rate control mode */
#define RCM_CBR		0
/* n */
#define N_INVALID	0xffffffff
#define MAX_N	300
/* idr_freq */
#define MAX_IDR_FREQ	10
/* picture structure */
#define PICST_FRM	0
/* slice num minus1 */
#define MAX_SLC_NUM_MINUS1	15
/* entropy coding */
#define CODE_CAVLC		0
#define CODE_CABAC		1
/* sei0 */
#define SEI_INVALID		0x0
#define SEI_BUF_PERIOD		0x1
#define SEI_RECOVERY_POINT	0x2
#define SEI_ALL			(SEI_BUF_PERIOD | SEI_RECOVERY_POINT)
/* vui parameters */
/* aspect ratio idx */
#define EXTENDED_SAR		255
/* video format */
#define MAX_VIDEO_FORMAT_VAL	7
/* colour_primaries, transfer_characteristics */
#define MAX_COLOUR_DESC_VAL	255
/* chroma_loc */
#define MAX_C_LOC_VAL		5

/* buffer size */
#define OUT_BUF_FIXED_SZ		((uint32_t)0x00004000)	/* 16KB */
#define BIN_BUF_FIXED_SZ		((uint32_t)0x0000C000)	/* 48KB */
#define BUF_FIXED_SZ_PER_FRM		((uint32_t)0x00000184)	/* 388B */
#define LINUX_PAGE_1MB			((uint32_t)0x00100000)	/* 1MB */
#define WORK_MEM_SZ			((uint32_t)0x00002400)	/* 9KB */
#define REF_IMG_SZ			((uint32_t)0x00D00000)	/* 13MB */
#define NAL_INFO_ONE_SZ			((uint32_t)0x00000400)	/* 1KB */

/* FW queue num */
#define FW_QUEUE_NUM			((uint32_t)0x00000003)

/* NAL information(contents id) */
#define CMN_EOP				((uint32_t)0x31020000)
#define NAL_INFO_ONE_CONT_SZ		((uint32_t)0x00000010)
#define NAL_INFO_FRM_ID_UPPER_OFS	((uint32_t)0x00000004)
#define NAL_INFO_FRM_ID_LOWER_OFS	((uint32_t)0x00000008)
#define NAL_INFO_ES_ADDR_OFS		((uint32_t)0x0000000C)
#define NAL_UNIT_TYPE_IDR		((uint32_t)0x30050000)
#define NAL_UNIT_TYPE_PIC		((uint32_t)0x30010000)

/* get rp mode */
#define NAL_INFO_NOT_ADV		((uint8_t)0x00)
#define NAL_INFO_ADV			((uint8_t)0x01)

struct rsc_fifo_port {
	uint8_t valid;
	uint8_t reserved0;
	uint16_t reserved1;
	uint8_t *ptr;
};

struct rsc_fifo_base {
	uint32_t *test;
	uint8_t *base;
	uint32_t size;
	uint8_t clear;
	uint8_t flush;
	uint8_t overflow;
	uint8_t reserved;
	struct rsc_fifo_port write;
	struct rsc_fifo_port read1;
	struct rsc_fifo_port read2;
	struct rsc_fifo_port read3;
};

struct rsc_fifo {
	struct rsc_fifo_base *base;
	int32_t port;
};

enum ve_result rsc_chk_hv_sz(uint32_t h_size, uint32_t v_size);
uint32_t rsc_get_ctrl_buf_size(void);
uint32_t rsc_get_output_buf_size(uint32_t h_size, uint32_t v_size);
uint32_t rsc_get_nal_inf_buf_size(void);
uint32_t rsc_get_work_buf_size(uint32_t h_size, uint32_t v_size);
uint32_t rsc_get_ref_buf_size(uint32_t m);
enum ve_result rsc_chk_io_buf_mem(const struct ve_io_buf_area *buf);
void rsc_connect_io_buf(struct ve_io_buf_area *io_buff,
				struct rsc_fifo *output, struct rsc_fifo *nal);
uint32_t rsc_get_1frame_out_buf_size(uint32_t h_size, uint32_t v_size);
uint32_t rsc_get_read_size_for_next_enc(struct ve_io_buf_area *io_buff,
							uint32_t one_frm_size);
enum ve_result rsc_set_default_param(uint32_t h_size, uint32_t v_size,
				uint32_t kbps, enum ve_frame_rate fps,
				enum ve_profile pf, struct ve_param *param);
enum ve_result rsc_chk_param(const struct ve_param *param);
enum ve_result rsc_chk_vui_param(const struct ve_param *param);
enum ve_result rsc_calc_frame_rate(enum ve_frame_rate frame_rate,
					uint32_t *num, uint32_t *denom);
enum ve_result rsc_get_buf_rp(struct ve_io_buf_area *io_buff,
				uint32_t *curr_rp_addr, uint32_t *adv_rp_addr,
				uint32_t *adv_info_rp_addr,
				uint32_t *frm_id_upper, uint32_t *frm_id_lower,
				uint32_t *cont_id, uint8_t mode);
void rsc_set_buf_rp(struct ve_io_buf_area *io_buff,
					uint32_t out_addr, uint32_t inf_addr);

#endif /* __VE_RESOURCES_H__ */

