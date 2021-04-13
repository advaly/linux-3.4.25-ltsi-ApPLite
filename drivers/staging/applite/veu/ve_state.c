/*
 * drivers/staging/applite/veu/ve_state.c
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

#include "ve_state.h"
#include "ve_access.h"
#include "ve_trace.h"

static uint8_t stt_api_boot = API_BOOT_OFF;

static enum ve_result chk_fw_state(uint32_t expected_state, uint32_t pu_id);

/* set api boot on */
void stt_set_api_boot_val(uint8_t val)
{
	stt_api_boot = val;
}

/* check api boot */
enum ve_result stt_chk_boot_api(void)
{
	if (stt_api_boot == API_BOOT_OFF)
		return VE_ERROR_REJECT;

	return VE_OK;
}

/* get fw state */
enum ve_result stt_get_fw_state(uint32_t *state, uint32_t pu_id)
{
	if (stt_chk_boot_api() != VE_OK)
		return VE_ERROR_REJECT;

	/* FIXME use pu_id */
	acs_rev_read32(CMN_FW_STATE, state);

	return VE_OK;
}

/* check implement function */
enum ve_result stt_chk_implement(struct ve_task *ctx,
		uint32_t fw_expected_state, uint32_t task_expected_state)
{
	enum ve_result ret = VE_OK;

	/* check fw state */
	/* FIXME pu_id */
	ret = chk_fw_state(fw_expected_state, 0);
	if (ret != VE_OK)
		return ret;

	/* check task state */
	if (ctx != NULL && task_expected_state != TASK_STATE_NA) {
		if ((ctx->state & task_expected_state) == 0x0)
			ret = VE_ERROR_STATE;
	}

	return ret;
}


/* set next task state in command */
enum ve_result stt_set_next_task_state_in_cmd(uint32_t command,
					int32_t num_of_args, uint32_t *state)
{
	enum ve_result ret = VE_OK;

	switch (command) {
	case VE_CMD_INITIALIZE_TASK:
		*state = VE_TASK_INITIALIZING_TASK;
		break;
	case VE_CMD_INITIALIZE_IOBUFFER:
		*state = VE_TASK_INITIALIZING_IOBUFFER;
		break;
	case VE_CMD_ENCODE:
		if (num_of_args != 0)
			*state = VE_TASK_ENCODING;
		else
			*state = VE_TASK_FLUSHING;
		break;
	case VE_CMD_KILL_TASK:
		*state = VE_TASK_DYING;
		break;
	default:
		ret = VE_ERROR_PARAMETERS;
		break;
	}

	return ret;
}

/* set next task state in response */
void stt_set_next_task_state_in_rsp(uint32_t command, uint8_t with_eos,
							uint32_t *state)
{
	switch (command) {
	case VE_CMD_INITIALIZE_TASK:
		*state = VE_TASK_PREPARED;
		break;
	case VE_CMD_INITIALIZE_IOBUFFER:
		*state = VE_TASK_WAIT_FOR_FRAME;
		break;
	case VE_CMD_ENCODE:
		if (with_eos)
			*state = VE_TASK_FINISHED;
		else if (*state == VE_TASK_FLUSHING)
			*state = VE_TASK_WAIT_FOR_FLUSH;
		else
			*state = VE_TASK_WAIT_FOR_FRAME;
		break;
	default:
		break;
	}
}

/* set previous task state in response */
void stt_set_prev_task_state_in_rsp(uint32_t command, uint32_t *state)
{
	switch (command) {
	case VE_CMD_INITIALIZE_TASK:
		*state = VE_TASK_UNINITIALIZED;
		break;
	case VE_CMD_INITIALIZE_IOBUFFER:
		*state = VE_TASK_PREPARED;
		break;
	case VE_CMD_ENCODE:
		*state = VE_TASK_WAIT_FOR_FRAME;
		break;
	default:
		break;
	}
}

/* set task state */
void stt_set_task_state(uint32_t *state, uint32_t setval)
{
	*state = setval;
}

/* check fw state */
static enum ve_result chk_fw_state(uint32_t expected_state, uint32_t pu_id)
{
	enum ve_result ret = VE_OK;
	uint32_t state;

	ret = stt_get_fw_state(&state, pu_id);
	if (ret != VE_OK)
		return ret;

	if ((state & expected_state) == 0x0)
		return VE_ERROR_STATE;

	return ret;
}

