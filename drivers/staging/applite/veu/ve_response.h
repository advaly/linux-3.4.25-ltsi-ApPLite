/*
 * drivers/staging/applite/veu/ve_response.h
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

#ifndef __VE_RESPONSE_H__
#define __VE_RESPONSE_H__

#ifdef __KERNEL__
#include <linux/stddef.h>
#else
#include <stddef.h>
#endif
#include "ve_api.h"
#include "ve_task.h"

/* bit mask for interrupt */
#define BIT_MSK_NORMAL	((uint32_t)0x80000000)
#define BIT_MSK_FATAL	((uint32_t)0x40000000)
#define BIT_MSK_KILL	((uint32_t)0x20000000)

/* local error code for ve_response/ve_dying_message */
#define RESP_OK			((uint32_t)0x00000000)
#define RESP_ERROR		((uint32_t)0x00000001)
#define RESP_ENC_OK_IDR_ERROR	((uint32_t)0x00000002)
#define RESP_NOTHING		((uint32_t)0xffffffff)

struct rsp_area {
	uint32_t resp_task_api;
	uint32_t resp_task_fw;
	uint32_t resp_command_id;
	uint32_t resp_num_of_args;
	uint32_t resp_arg[VE_MAX_PARAMS_NUM];
	uint32_t fw_state;
};

struct rsp_kill_area {
	uint32_t resp_task_api;
	uint32_t resp_task_fw;
	uint32_t resp_arg;
};

enum ve_result rsp_handle_interrupt(struct ve_response *resp,
				struct ve_dying_message *msg, uint32_t pu_id);

#endif /* __VE_RESPONSE_H__ */

