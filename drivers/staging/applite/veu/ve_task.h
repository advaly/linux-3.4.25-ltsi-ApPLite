/*
 * drivers/staging/applite/veu/ve_task.h
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

#ifndef __VE_TASK_H__
#define __VE_TASK_H__

#include "ve_api.h"
#include "ve_access.h"
#include "ve_resources.h"

#define NO_ENC		0
#define ENC_DONE	1

struct ve_task {
	void *private_data;
	ve_vbus_t task_fw;
	struct ve_io_buf_area io_buff;
	struct rsc_fifo output_fifo;
	struct rsc_fifo nal_info_fifo;
	uint32_t state;
	uint32_t one_frm_size;
	uint32_t enc_state;
};

enum ve_result tsk_chk_creating_mem(const struct ve_task_work_area *area);

#endif /* __VE_TASK_H__ */

