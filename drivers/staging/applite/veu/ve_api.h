/*
 * drivers/staging/applite/veu/ve_api.h
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

#ifndef __VE_API_H__
#define __VE_API_H__

#include "ve_param.h"

/* fw state */
#define VE_FW_STATE_INITIAL	((uint32_t)(1<<1))
#define VE_FW_STATE_POWER_OFF	((uint32_t)(1<<2))
#define VE_FW_STATE_READY	((uint32_t)(1<<3))
#define VE_FW_STATE_RUNNING	((uint32_t)(1<<4))
#define VE_FW_STATE_KILLING	((uint32_t)(1<<5))

/* attribution of input data */
#define VE_PIC_NOTHING		((uint32_t)0x00000000)
#define VE_PIC_SYNC_FRAME	((uint32_t)0x00000001)

/* the max number of parameters for command */
#define VE_MAX_PARAMS_NUM 0x3a

typedef uint32_t ve_virtual_t;
typedef uint32_t ve_physical_t;
typedef uint32_t ve_vbus_t;
typedef uint32_t ve_vtile_t;

/* error code */
enum ve_result {
	VE_OK,
	VE_ERROR_REJECT,
	VE_ERROR_PARAMETERS,
	VE_ERROR_STATE,
	VE_ERROR_NONEXISTENT,
	VE_ERROR_FATAL,
	VE_ERROR_INSUFFICIENT_FREE_SPACE,
	VE_ERROR_MBOX_BUSY,
	VE_ERROR_INSUFFICIENT_INPUT_FRAME,
};

/* FW state */
enum ve_task_state {
	VE_TASK_INITIAL			= 0x0000,
	VE_TASK_UNINITIALIZED		= 0x0001,
	VE_TASK_INITIALIZING_TASK	= 0x0002,
	VE_TASK_PREPARED		= 0x0004,
	VE_TASK_INITIALIZING_IOBUFFER	= 0x0008,
	VE_TASK_WAIT_FOR_FRAME		= 0x0010,
	VE_TASK_ENCODING		= 0x0020,
	VE_TASK_FLUSHING		= 0x0040,
	VE_TASK_WAIT_FOR_FLUSH		= 0x0080,
	VE_TASK_DYING			= 0x0100,
	VE_TASK_FINISHED		= 0x0200,
};

/* profile */
enum ve_profile {
	VE_PF_ANY,
	VE_PF_BASELINE,
	VE_PF_MAIN,
	VE_PF_HIGH,
};

/* command */
enum ve_command {
	VE_CMD_START_UP_PU,
	VE_CMD_SHUT_DOWN_PU,
	VE_CMD_INITIALIZE_TASK,
	VE_CMD_INITIALIZE_IOBUFFER,
	VE_CMD_ENCODE,
	VE_CMD_KILL_TASK,
	VE_CMD_NONEXISTENT,
};

/* task context */
struct ve_task;

/* response */
struct ve_response {
	struct ve_task *task;
	uint32_t command;
	uint32_t num_of_params;
	uint32_t param[VE_MAX_PARAMS_NUM];
};

/* dying message */
struct ve_dying_message {
	struct ve_task *task;
	uint32_t param;
};

/* address */
struct ve_address {
	ve_physical_t p_addr;
	ve_virtual_t v_addr;
};

/* mbox */
struct ve_mbox {
	struct ve_address set;
	struct ve_address clear;
	struct ve_address mask;
	struct ve_address selector;
};

/* accessor */
struct ve_accessor {
	void (*lock)(void *private_data);
	void (*unlock)(void *private_data);
	void *private_data;
	struct ve_mbox to_vip4;
	struct ve_mbox from_vip4;
	struct ve_mbox to_vip4_nmi;
	ve_virtual_t veu0_addrconf0;
	ve_virtual_t veu0_addrconf1;
	ve_virtual_t reset_on_vcodec;
};

/* buffer */
struct ve_buf {
	struct ve_address addr;
	uint32_t size;
};

/* vtile buffer */
struct ve_vtile_buf {
	ve_vtile_t addr;
	uint32_t size;
};

/* task work area */
struct ve_task_work_area {
	uint32_t *api;
	struct ve_address fw;
	uint32_t reserved;
};

/* io buffer area */
struct ve_io_buf_area {
	struct ve_buf control;
	struct ve_buf output;
	struct ve_buf nal;
	struct ve_buf work;
	struct ve_vtile_buf reference;
};

/* picture entry */
struct ve_picture_entry {
	ve_vtile_t luma;
	ve_vtile_t chroma;
	uint64_t frame_id;
	uint32_t attribute;
};

/* output entry */
struct ve_output_entry {
	uint32_t begin;
	uint32_t end;
	uint64_t frame_id;
	uint32_t type;
	uint32_t attribute;
};

enum ve_result ve_initialize_api(struct ve_accessor *accessors,
					struct ve_address *fw_address,
					struct ve_buf *comm_area);
enum ve_result ve_finalize_api(void);
enum ve_result ve_get_api_version(uint32_t *version, uint32_t *build);
enum ve_result ve_get_fw_version(uint32_t *version, uint32_t *build);
enum ve_result ve_get_fw_state(uint32_t *state, uint32_t pu_id);
enum ve_result ve_start_up_pu(uint32_t pu_id);
enum ve_result ve_shut_down_pu(uint32_t pu_id);
enum ve_result ve_get_task_requirements(uint32_t *api_area, uint32_t *fw_area);
enum ve_result ve_calc_default_param(struct ve_param *param,
					uint32_t horizontal_pixels,
					uint32_t vertical_pixels,
					uint32_t kbps,
					enum ve_frame_rate fps,
					enum ve_profile pf);
enum ve_result ve_calc_io_buf_requirements(struct ve_io_buf_area *rqmt,
						const struct ve_param *param);
enum ve_result ve_create_task(struct ve_task **task,
				const struct ve_task_work_area *work_area,
				void *private_data);
enum ve_result ve_destroy_task(struct ve_task *task);
enum ve_result ve_create_io_buf(struct ve_task *ctx,
				const struct ve_io_buf_area *buf_area);
enum ve_result ve_get_task_state(struct ve_task *ctx, uint32_t *state);
enum ve_result ve_get_private_data_from_task(struct ve_task *ctx,
						void **private_data);
enum ve_result ve_get_read_size_for_next_enc(struct ve_task *ctx,
						uint32_t *required_size);
enum ve_result ve_handle_interrupt(struct ve_response *resp,
				struct ve_dying_message *msg, uint32_t pu_id);
enum ve_result ve_send_initialize_task_cmd(struct ve_task *ctx, uint32_t pu_id);
enum ve_result ve_send_resources_cmd(struct ve_task *ctx,
					const struct ve_param *param,
					uint32_t pu_id);
enum ve_result ve_send_encode_cmd(struct ve_task *ctx,
					struct ve_picture_entry *pic,
					uint32_t pu_id);
enum ve_result ve_send_kill_task_cmd(struct ve_task *ctx, uint32_t pu_id);
enum ve_result ve_get_output_buf_entry(struct ve_task *ctx,
					struct ve_output_entry *entry);
enum ve_result ve_next_output_buf_entry(struct ve_task *ctx);
enum ve_result ve_set_trace_log_buf(struct ve_buf *log_buf, uint32_t pu_id);

#endif /* __VE_API_H__ */

