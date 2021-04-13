/*
 * drivers/staging/applite/veu/ve_command.h
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

#ifndef __VE_COMMAND_H__
#define __VE_COMMAND_H__

#ifdef __KERNEL__
#include <linux/stddef.h>
#else
#include <stddef.h>
#endif
#include "ve_api.h"
#include "ve_task.h"

struct cmd_area {
	uint32_t com_task_api;
	uint32_t com_task_fw;
	uint32_t com_command_id;
	uint32_t com_num_of_args;
	uint32_t com_arg[VE_MAX_PARAMS_NUM];
};

enum ve_result cmd_mk_power_on_off_param(uint32_t cmd_addr);
enum ve_result cmd_mk_initialize_param(uint32_t cmd_addr);
enum ve_result cmd_mk_resources_param(const struct ve_param *enc_param,
			struct ve_io_buf_area *io_buff, uint32_t cmd_addr);
enum ve_result cmd_mk_encode_param(struct ve_picture_entry *pic,
							uint32_t cmd_addr);
enum ve_result cmd_mk_kill_task_param(uint32_t cmd_addr);
enum ve_result cmd_prepare_send_command(uint32_t pu_id);
void cmd_post_send_command(uint32_t pu_id);
enum ve_result cmd_send_command(uint32_t cmd_id, uint32_t cmd_addr,
					struct ve_task *ctx, uint32_t pu_id);

#endif /* __VE_COMMAND_H__ */

