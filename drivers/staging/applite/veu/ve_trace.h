/*
 * drivers/staging/applite/veu/ve_trace.h
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

#ifndef __VE_TRACE_H__
#define __VE_TRACE_H__

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#ifdef VE_LOG_TRACE

/*
 * MSB means kind of software(FW/API): 0:API 1:FW
 * bit30-16 mean LEVEL.
 * bit15-0 mean log ID.
 */
#define VE_LT_LEVEL_MASK	(0x7fff0000) /*all log */
#define VE_LT_LEVEL1		(0x00010000)
#define VE_LT_LEVEL2		(0x00020000)
#define VE_LT_LEVEL3		(0x00030000)

/*
 * If VE_LT_XXX is added this file, it must be added to id_text_table[]
 * and TABLE_SIZE is incremented.
 */
#define VE_LT_START             (VE_LT_LEVEL1 | 0x0000)
#define VE_LT_INIT_API          (VE_LT_LEVEL2 | 0x0001)
#define VE_LT_FIN_API           (VE_LT_LEVEL2 | 0x0002)
#define VE_LT_GET_API_VER       (VE_LT_LEVEL2 | 0x0003)
#define VE_LT_GET_FW_VER        (VE_LT_LEVEL2 | 0x0004)
#define VE_LT_GET_FW_STAT       (VE_LT_LEVEL2 | 0x0005)
#define VE_LT_START_UP          (VE_LT_LEVEL2 | 0x0006)
#define VE_LT_SHUT_DOWN         (VE_LT_LEVEL2 | 0x0007)
#define VE_LT_GET_TSK_REQ       (VE_LT_LEVEL2 | 0x0008)
#define VE_LT_CALC_DEF          (VE_LT_LEVEL2 | 0x0009)
#define VE_LT_CALC_IO           (VE_LT_LEVEL2 | 0x000a)
#define VE_LT_CRATE_TSK         (VE_LT_LEVEL2 | 0x000b)
#define VE_LT_DESTROY_TSK       (VE_LT_LEVEL2 | 0x000c)
#define VE_LT_CREATE_IO         (VE_LT_LEVEL2 | 0x000d)
#define VE_LT_GET_TSK_STAT      (VE_LT_LEVEL2 | 0x000e)
#define VE_LT_GET_PRIVATE       (VE_LT_LEVEL2 | 0x000f)
#define VE_LT_GET_READ_SZ       (VE_LT_LEVEL2 | 0x0010)
#define VE_LT_HANDLE_ITR        (VE_LT_LEVEL1 | 0x0011)
#define VE_LT_SEND_INIT_TSK     (VE_LT_LEVEL2 | 0x0012)
#define VE_LT_SEND_RSC          (VE_LT_LEVEL2 | 0x0013)
#define VE_LT_SEND_ENCODE       (VE_LT_LEVEL1 | 0x0014)
#define VE_LT_SEND_KILL         (VE_LT_LEVEL2 | 0x0015)
#define VE_LT_GET_OUTPUT        (VE_LT_LEVEL2 | 0x0016)
#define VE_LT_NEXT_OUTPUT       (VE_LT_LEVEL2 | 0x0017)

#define VE_LT_DBG_001           (VE_LT_LEVEL3 | 0x0101)

#define VE_LT_PRM_OUTMODE       (VE_LT_LEVEL2 | 0x0201)
#define VE_LT_PRM_PROFILE       (VE_LT_LEVEL2 | 0x0202)
#define VE_LT_PRM_LEVEL         (VE_LT_LEVEL2 | 0x0203)
#define VE_LT_PRM_H_SIZE        (VE_LT_LEVEL2 | 0x0204)
#define VE_LT_PRM_V_SIZE        (VE_LT_LEVEL2 | 0x0205)
#define VE_LT_PRM_FPS           (VE_LT_LEVEL2 | 0x0206)
#define VE_LT_PRM_KBPS          (VE_LT_LEVEL2 | 0x0207)
#define VE_LT_PRM_MAXKBPS       (VE_LT_LEVEL2 | 0x0208)
#define VE_LT_PRM_CPB_KSIZE     (VE_LT_LEVEL2 | 0x0209)
#define VE_LT_PRM_RCM           (VE_LT_LEVEL2 | 0x020a)
#define VE_LT_PRM_M             (VE_LT_LEVEL2 | 0x020b)
#define VE_LT_PRM_N             (VE_LT_LEVEL2 | 0x020c)
#define VE_LT_PRM_IDR_FREQ      (VE_LT_LEVEL2 | 0x020d)
#define VE_LT_PRM_PIC_STRUCT    (VE_LT_LEVEL2 | 0x020e)
#define VE_LT_PRM_SLICE_NUM_1   (VE_LT_LEVEL2 | 0x020f)
#define VE_LT_PRM_SCLMTX        (VE_LT_LEVEL2 | 0x0210)
#define VE_LT_PRM_CODING        (VE_LT_LEVEL2 | 0x0211)
#define VE_LT_PRM_W_PRED        (VE_LT_LEVEL2 | 0x0212)
#define VE_LT_PRM_REF_B         (VE_LT_LEVEL2 | 0x0213)
#define VE_LT_PRM_INTER_VIEW    (VE_LT_LEVEL2 | 0x0214)
#define VE_LT_PRM_VUI_PRM       (VE_LT_LEVEL2 | 0x0215)
#define VE_LT_PRM_SEI0          (VE_LT_LEVEL2 | 0x0216)

void  ve_log_trace(uint32_t id, uint32_t value);
#define VELOGTRACE(...) ve_log_trace(__VA_ARGS__)

#else
#define VELOGTRACE(...)
#endif

#ifdef TOOL_TRACE2TXT /* API does not this define statement */

#define TABLE_SIZE  47

struct ID_TEXT_TABLE {
	unsigned int id;
	char *text;
};

struct ID_TEXT_TABLE id_text_table[TABLE_SIZE] = {
	{VE_LT_START,         "%u %u ***** ve_set_trace_log_buf :0x%08x\n"},
	{VE_LT_INIT_API,      "%u %u ***** ve_initialize_api :0x%08x\n"},
	{VE_LT_FIN_API,       "%u %u ***** ve_finalize_api\n"},
	{VE_LT_GET_API_VER,   "%u %u ***** ve_get_api_version\n"},
	{VE_LT_GET_FW_VER,    "%u %u ***** ve_get_fw_version\n"},
	{VE_LT_GET_FW_STAT,   "%u %u ***** ve_get_fw_state\n"},
	{VE_LT_START_UP,      "%u %u ***** ve_start_up_pu: pu_id(%d)\n"},
	{VE_LT_SHUT_DOWN,     "%u %u ***** ve_shut_down_pu: pu_id(%d)\n"},
	{VE_LT_GET_TSK_REQ,   "%u %u ***** ve_get_task_requirements\n"},
	{VE_LT_CALC_DEF,      "%u %u ***** ve_calc_default_param\n"},
	{VE_LT_CALC_IO,       "%u %u ***** ve_calc_io_buf_requirements\n"},
	{VE_LT_CRATE_TSK,     "%u %u ***** ve_create_task\n"},
	{VE_LT_DESTROY_TSK,   "%u %u ***** ve_destroy_task\n"},
	{VE_LT_CREATE_IO,     "%u %u ***** ve_create_io_buf\n"},
	{VE_LT_GET_TSK_STAT,  "%u %u ***** ve_get_task_state\n"},
	{VE_LT_GET_PRIVATE,   "%u %u ***** ve_get_private_data_from_task\n"},
	{VE_LT_GET_READ_SZ,   "%u %u ***** ve_get_read_size_for_next_enc\n"},
	{VE_LT_HANDLE_ITR,    "%u %u ***** ve_handle_interrupt: pu_id(%d\n)"},
	{VE_LT_SEND_INIT_TSK, "%u %u ***** ve_send_initialize_task_cmd\n"},
	{VE_LT_SEND_RSC,      "%u %u ***** ve_send_resources_cmd\n"},
	{VE_LT_SEND_ENCODE,   "%u %u ***** ve_send_encode_cmd\n"},
	{VE_LT_SEND_KILL,     "%u %u ***** ve_send_kill_task_cmd\n"},
	{VE_LT_GET_OUTPUT,    "%u %u ***** ve_get_output_buf_entry\n"},
	{VE_LT_NEXT_OUTPUT,   "%u %u ***** ve_next_output_buf_entry\n"},
	{VE_LT_DBG_001,       "%u %u ***** 0x%08x\n"},
	{VE_LT_PRM_OUTMODE,	"%u %u *** param output_mode       : 0x%08x\n"},
	{VE_LT_PRM_PROFILE,	"%u %u *** param profile           : %d\n"},
	{VE_LT_PRM_LEVEL,	"%u %u *** param level             : %d\n"},
	{VE_LT_PRM_H_SIZE,	"%u %u *** param h size            : %d\n"},
	{VE_LT_PRM_V_SIZE,	"%u %u *** param v size            : %d\n"},
	{VE_LT_PRM_FPS,		"%u %u *** param fps               : 0x%08x\n"},
	{VE_LT_PRM_KBPS,	"%u %u *** param kbps              : %d\n"},
	{VE_LT_PRM_MAXKBPS,	"%u %u *** param max kbps          : %d\n"},
	{VE_LT_PRM_CPB_KSIZE,	"%u %u *** param cpb ksize         : %d\n"},
	{VE_LT_PRM_RCM,		"%u %u *** param rate control mode : 0x%08x\n"},
	{VE_LT_PRM_M,		"%u %u *** param m                 : 0x%08x\n"},
	{VE_LT_PRM_N,		"%u %u *** param n                 : 0x%08x\n"},
	{VE_LT_PRM_IDR_FREQ,	"%u %u *** param idr freq          : 0x%08x\n"},
	{VE_LT_PRM_PIC_STRUCT,	"%u %u *** param picture structure : 0x%08x\n"},
	{VE_LT_PRM_SLICE_NUM_1,	"%u %u *** param slice num - 1     : 0x%08x\n"},
	{VE_LT_PRM_SCLMTX,	"%u %u *** param scaling matrix    : 0x%08x\n"},
	{VE_LT_PRM_CODING,	"%u %u *** param entropy coding    : 0x%08x\n"},
	{VE_LT_PRM_W_PRED,	"%u %u *** param weighted pred     : 0x%08x\n"},
	{VE_LT_PRM_REF_B,	"%u %u *** param reference b       : 0x%08x\n"},
	{VE_LT_PRM_INTER_VIEW,	"%u %u *** param inter view pred   : 0x%08x\n"},
	{VE_LT_PRM_VUI_PRM,	"%u %u *** param vui params        : 0x%08x\n"},
	{VE_LT_PRM_SEI0,	"%u %u *** param sei0              : 0x%08x\n"},
};

#endif  /* TOOL_TRACE2TXT */

#endif  /* __VE_TRACE_H__ */

