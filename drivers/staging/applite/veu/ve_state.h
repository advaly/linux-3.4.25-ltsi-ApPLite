/*
 * drivers/staging/applite/veu/ve_state.h
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

#ifndef __VE_STATE_H__
#define __VE_STATE_H__

#ifdef __KERNEL__
#include <linux/stddef.h>
#else
#include <stddef.h>
#endif
#include "ve_api.h"
#include "ve_task.h"

/* API state */
#define API_BOOT_OFF		((uint8_t)0x00)
#define API_BOOT_ON		((uint8_t)0x01)

/* additional FW state */
#define FW_STATE_POWER_ON	((uint32_t)(VE_FW_STATE_READY | \
						VE_FW_STATE_RUNNING | \
						VE_FW_STATE_KILLING))
#define FW_STATE_NOT_INITIAL	((uint32_t)(FW_STATE_POWER_ON | \
						VE_FW_STATE_POWER_OFF))

/* additional task state */
#define TASK_STATE_NA		((uint32_t)0xFFFF)
#define TASK_STATE_ENC_PHASE	((uint32_t)(VE_TASK_WAIT_FOR_FRAME | \
						VE_TASK_ENCODING | \
						VE_TASK_FLUSHING | \
						VE_TASK_WAIT_FOR_FLUSH))
#define TASK_STATE_GETTABLE_ES	((uint32_t)(TASK_STATE_ENC_PHASE | \
						VE_TASK_FINISHED))
#define TASK_STATE_IDLE_PHASE	((uint32_t)(VE_TASK_UNINITIALIZED | \
						VE_TASK_PREPARED | \
						VE_TASK_FINISHED))

void stt_set_api_boot_val(uint8_t val);
enum ve_result stt_chk_boot_api(void);
enum ve_result stt_get_fw_state(uint32_t *state, uint32_t pu_id);
enum ve_result stt_chk_implement(struct ve_task *ctx,
		uint32_t fw_expected_state, uint32_t task_expected_state);
enum ve_result stt_set_next_task_state_in_cmd(uint32_t command,
					int32_t num_of_args, uint32_t *state);
void stt_set_next_task_state_in_rsp(uint32_t command, uint8_t with_eos,
							uint32_t *state);
void stt_set_prev_task_state_in_rsp(uint32_t command, uint32_t *state);
void stt_set_task_state(uint32_t *state, uint32_t setval);

#endif /* __VE_STATE_H__ */

