/*
 * drivers/staging/applite/veu/ve_response.c
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

#include "ve_response.h"
#include "ve_access.h"
#include "ve_state.h"
#include "ve_trace.h"

/* handle interrupt */
enum ve_result rsp_handle_interrupt(struct ve_response *resp,
				struct ve_dying_message *msg, uint32_t pu_id)
{
	enum ve_result ret = VE_OK;
	struct ve_accessor access;
	uint32_t bits;
	struct rsp_area *resp_area;
	struct rsp_kill_area *resp_kill_area;
	uint32_t num_of_params;
	uint32_t i;
	uint32_t tmp;

	access = acs_get_accessor();

	/* get cmd response */
	acs_rev_read32(access.from_vip4.set.v_addr, &bits);

	/* check error */
	if ((bits & (BIT_MSK_NORMAL | BIT_MSK_FATAL | BIT_MSK_KILL)) == 0x0) {
		return VE_ERROR_NONEXISTENT;
	} else if ((bits & BIT_MSK_FATAL) != 0x0) {
		ret = VE_ERROR_FATAL;
		goto out;
	}

	/* check the response of normal command */
	if ((bits & BIT_MSK_NORMAL) != 0x0) {

		/* get the response */
		resp_area = (struct rsp_area *)(COMM_AREA_RESP(pu_id));
		resp->task = (struct ve_task *)resp_area->resp_task_api;
		resp->command = VE_REV(resp_area->resp_command_id);
		resp->num_of_params = VE_REV(resp_area->resp_num_of_args);
		num_of_params = resp->num_of_params;

		for (i = 0; i < num_of_params; i++)
			resp->param[i] = VE_REV(resp_area->resp_arg[i]);

		if (resp->command == VE_CMD_START_UP_PU ||
				resp->command == VE_CMD_SHUT_DOWN_PU)
			goto chk_kill_cmd_resp;

		if (resp->param[0] == RESP_OK
				|| resp->param[0] == RESP_ENC_OK_IDR_ERROR) {
			/* set next task state when fw returns OK. */
			stt_set_next_task_state_in_rsp(resp->command,
					(uint8_t)(resp->param[1] == 2),
					&(resp->task->state));
			if (resp->command == VE_CMD_ENCODE) {
				resp->task->enc_state = ENC_DONE;
				if (num_of_params > 2) {
					tmp = resp->param[2];
					resp->param[2] = resp->param[3];
					resp->param[3] = tmp;
				}
			}
		} else if (resp->param[0] == RESP_ERROR) {
			/* set previous task state when fw returns ERROR. */
			stt_set_prev_task_state_in_rsp(resp->command,
					&(resp->task->state));
		}
	} else {
		resp->command = VE_CMD_NONEXISTENT;
		resp->num_of_params = 1;
		resp->param[0] = RESP_NOTHING;
	}

chk_kill_cmd_resp:
	/* get the response of kill command */
	if ((bits & BIT_MSK_KILL) != 0x0) {
		resp_kill_area =
			(struct rsp_kill_area *)(COMM_AREA_RESP_KILL(pu_id));
		msg->task = (struct ve_task *)resp_kill_area->resp_task_api;
		msg->param = VE_REV(resp_kill_area->resp_arg);
		stt_set_task_state(&(msg->task->state), VE_TASK_INITIAL);
	} else {
		msg->param = RESP_NOTHING;
	}

out:
	/* clear bit */
	acs_rev_write32(access.from_vip4.clear.v_addr, bits);

	return ret;
}

