/*
 * drivers/staging/applite/veu/ve_api.c
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

#ifdef __KERNEL__
#include <linux/string.h>
#else
#include <string.h>
#endif
#include "ve_api.h"
#include "ve_task.h"
#include "ve_access.h"
#include "ve_command.h"
#include "ve_response.h"
#include "ve_resources.h"
#include "ve_state.h"
#include "ve_version.h"
#include "ve_trace.h"

/* initialize api */
enum ve_result ve_initialize_api(struct ve_accessor *accessors,
					struct ve_address *fw_address,
					struct ve_buf *comm_area)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (accessors == NULL || fw_address == NULL || comm_area == NULL)
		return VE_ERROR_PARAMETERS;
	if (accessors->lock == NULL || accessors->unlock == NULL)
		return VE_ERROR_PARAMETERS;

	/* check boot */
	if (stt_chk_boot_api() == VE_OK)
		return VE_ERROR_REJECT;

	/* check memory */
	ret = acs_chk_start_up_mem(accessors, fw_address, comm_area);
	if (ret != VE_OK)
		return ret;

	/* set address base */
	acs_set_fw_base(fw_address->v_addr);
	acs_set_comm_base(comm_area->addr.v_addr);

	/* initialize communication area */
	memset((uint8_t *)comm_area->addr.v_addr, 0x0, COMM_AREA_SIZE);

	/* set econf */
	acs_write32(accessors->veu0_addrconf0, fw_address->p_addr);

	/* write value into fw address */
	acs_write32(VIP4_FW_COMM_BASE,
		acs_trans_p2vbus_addr(comm_area->addr.p_addr + CMN_BASE_OFS));
	acs_write32(VIP4_FW_INT_SET_HOST,
		acs_trans_p2vbus_addr(accessors->from_vip4.set.p_addr));
	acs_write32(VIP4_FW_INT_CLEAR_VIP4,
		acs_trans_p2vbus_addr(accessors->to_vip4.clear.p_addr));
	acs_write32(VIP4_FW_COMMAND,
		acs_trans_p2vbus_addr(comm_area->addr.p_addr + CMD_BASE_OFS));
	acs_write32(VIP4_FW_RESPONSE,
		acs_trans_p2vbus_addr(comm_area->addr.p_addr + RESP_BASE_OFS));
	acs_write32(VIP4_FW_RESPONSE_KILL, acs_trans_p2vbus_addr(
				comm_area->addr.p_addr + RESP_KILL_BASE_OFS));

	/* set accessors */
	acs_set_accessor(*accessors);

	/* set fw state */
	acs_rev_write32(CMN_FW_STATE, VE_FW_STATE_POWER_OFF);

	stt_set_api_boot_val(API_BOOT_ON);

	return ret;
}

/* finalize api */
enum ve_result ve_finalize_api(void)
{
	enum ve_result ret = VE_OK;
	uint32_t reset_val;

	/* check fw state */
	ret = stt_chk_implement(NULL, VE_FW_STATE_POWER_OFF, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_FIN_API, (uint32_t)0);

	/* check [reset on] vp4 */
	reset_val = acs_get_reset_status();
	if ((reset_val & VE_RST_ON) == 0x0)
		return VE_ERROR_STATE;

	stt_set_api_boot_val(API_BOOT_OFF);

	return VE_OK;
}

/* get api version */
enum ve_result ve_get_api_version(uint32_t *version, uint32_t *build)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (version == NULL || build == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, FW_STATE_NOT_INITIAL, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_GET_API_VER, (uint32_t)0);

	*version = (uint32_t)VE_VERSION;
	*build = 0;

	return ret;
}

/* get fw version and build number */
enum ve_result ve_get_fw_version(uint32_t *version, uint32_t *build)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (version == NULL || build == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, FW_STATE_NOT_INITIAL, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_GET_FW_VER, (uint32_t)0);

	acs_rev_read32(VIP4_FW_VERSION, version);
	acs_rev_read32(VIP4_FW_BUILD, build);

	return ret;
}

/* get fw state */
enum ve_result ve_get_fw_state(uint32_t *state, uint32_t pu_id)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (state == NULL)
		return VE_ERROR_PARAMETERS;

	/* check pu_id */
	if (pu_id > VIP4_PU_MAX_VAL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, FW_STATE_NOT_INITIAL, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_GET_FW_STAT, (uint32_t)0);

	ret = stt_get_fw_state(state, pu_id);

	return ret;
}

/* start up process unit */
enum ve_result ve_start_up_pu(uint32_t pu_id)
{
	enum ve_result ret;
	uint32_t reset_val;

	/* check pu_id */
	if (pu_id > VIP4_PU_MAX_VAL)
		return VE_ERROR_PARAMETERS;

	/* check boot */
	if (stt_chk_boot_api() != VE_OK)
		return VE_ERROR_REJECT;

	VELOGTRACE(VE_LT_START_UP, pu_id);

	ret = cmd_prepare_send_command(pu_id);
	if (ret != VE_OK)
		return ret;

	/* check fw state */
	ret = stt_chk_implement(NULL, VE_FW_STATE_POWER_OFF, TASK_STATE_NA);
	if (ret != VE_OK)
		goto out;

	/* check [reset off] vp4 */
	reset_val = acs_get_reset_status();
	if ((reset_val & VE_RST_ON) != 0x0) {
		ret = VE_ERROR_STATE;
		goto out;
	}

	/* set command parameters */
	ret = cmd_mk_power_on_off_param(acs_get_cmd_addr(pu_id));
	if (ret != VE_OK)
		goto out;

	ret = cmd_send_command(VE_CMD_START_UP_PU,
					acs_get_cmd_addr(pu_id), NULL, pu_id);

out:
	cmd_post_send_command(pu_id);

	return ret;
}

/* shut down process unit */
enum ve_result ve_shut_down_pu(uint32_t pu_id)
{
	enum ve_result ret;

	/* check pu_id */
	if (pu_id > VIP4_PU_MAX_VAL)
		return VE_ERROR_PARAMETERS;

	/* check boot */
	if (stt_chk_boot_api() != VE_OK)
		return VE_ERROR_REJECT;

	VELOGTRACE(VE_LT_SHUT_DOWN, pu_id);

	ret = cmd_prepare_send_command(pu_id);
	if (ret != VE_OK)
		return ret;

	/* check fw state */
	ret = stt_chk_implement(NULL, VE_FW_STATE_READY, TASK_STATE_NA);
	if (ret != VE_OK)
		goto out;

	/* set command parameters */
	ret = cmd_mk_power_on_off_param(acs_get_cmd_addr(pu_id));
	if (ret != VE_OK)
		goto out;

	/* send command */
	ret = cmd_send_command(VE_CMD_SHUT_DOWN_PU,
					acs_get_cmd_addr(pu_id), NULL, pu_id);
out:
	cmd_post_send_command(pu_id);

	return ret;
}

/* get the byte size task requirements */
enum ve_result ve_get_task_requirements(uint32_t *api_area, uint32_t *fw_area)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (api_area == NULL || fw_area == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, FW_STATE_POWER_ON, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_GET_TSK_REQ, (uint32_t)0);

	*api_area = sizeof(struct ve_task);
	acs_rev_read32(CMN_FW_CTX_SZ, fw_area);

	return ret;
}

/* calculate default parameters */
enum ve_result ve_calc_default_param(struct ve_param *param,
					uint32_t horizontal_pixels,
					uint32_t vertical_pixels,
					uint32_t kbps,
					enum ve_frame_rate fps,
					enum ve_profile pf)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (param == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, FW_STATE_POWER_ON, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_CALC_DEF, (uint32_t)0);

	/* set default parameters */
	ret = rsc_set_default_param(horizontal_pixels, vertical_pixels,
							kbps, fps, pf, param);

	return ret;
}

/* calculate io buffer requirements */
enum ve_result ve_calc_io_buf_requirements(struct ve_io_buf_area *rqmt,
						const struct ve_param *param)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (rqmt == NULL || param == NULL)
		return VE_ERROR_PARAMETERS;

	/* check horizontal/vertical size */
	if (rsc_chk_hv_sz(param->horizontal_pixels,
					param->vertical_pixels) != VE_OK)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, FW_STATE_POWER_ON, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_CALC_IO, (uint32_t)0);

	/* get size */
	rqmt->control.size = rsc_get_ctrl_buf_size();
	rqmt->output.size = rsc_get_output_buf_size(param->horizontal_pixels,
							param->vertical_pixels);
	rqmt->nal.size = rsc_get_nal_inf_buf_size();
	rqmt->work.size = rsc_get_work_buf_size(param->horizontal_pixels,
							param->vertical_pixels);
	rqmt->reference.size = rsc_get_ref_buf_size(param->m);

	return ret;
}

/* create task */
enum ve_result ve_create_task(struct ve_task **task,
				const struct ve_task_work_area *work_area,
				void *private_data)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (task == NULL || work_area == NULL || private_data == NULL)
		return VE_ERROR_PARAMETERS;
	if (work_area->api == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, FW_STATE_POWER_ON, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_CRATE_TSK, (uint32_t)0);

	/* check memory */
	ret = tsk_chk_creating_mem(work_area);
	if (ret != VE_OK)
		return ret;

	*task = (struct ve_task *)(work_area->api);
	(*task)->task_fw = acs_trans_p2vbus_addr(work_area->fw.p_addr);
	(*task)->private_data = private_data;
	(*task)->enc_state = NO_ENC;

	/* change task state */
	stt_set_task_state(&((*task)->state), VE_TASK_UNINITIALIZED);

	return ret;
}

/* destroy task */
enum ve_result ve_destroy_task(struct ve_task *task)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (task == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(task, FW_STATE_POWER_ON, TASK_STATE_IDLE_PHASE);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_DESTROY_TSK, (uint32_t)0);

	/* change task state */
	stt_set_task_state(&(task->state), VE_TASK_INITIAL);

	return ret;
}

/* create io buffer */
enum ve_result ve_create_io_buf(struct ve_task *ctx,
				const struct ve_io_buf_area *buf_area)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (ctx == NULL || buf_area == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(ctx, FW_STATE_POWER_ON, VE_TASK_PREPARED);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_CREATE_IO, (uint32_t)0);

	/* check memory */
	ret = rsc_chk_io_buf_mem(buf_area);
	if (ret != VE_OK)
		return ret;

	ctx->io_buff = *buf_area;

	/* connect output/nal buffer */
	rsc_connect_io_buf(&(ctx->io_buff),
				&(ctx->output_fifo), &(ctx->nal_info_fifo));

	return ret;
}

/* get task state */
enum ve_result ve_get_task_state(struct ve_task *ctx, uint32_t *state)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (ctx == NULL || state == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(ctx, FW_STATE_POWER_ON, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_GET_TSK_STAT, (uint32_t)0);

	*state = ctx->state;

	return ret;
}

/* get private data */
enum ve_result ve_get_private_data_from_task(struct ve_task *ctx,
						void **private_data)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (ctx == NULL || private_data == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(ctx, FW_STATE_POWER_ON, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_GET_PRIVATE, (uint32_t)0);

	*private_data = ctx->private_data;

	return ret;
}

/* get read size for next encoding */
enum ve_result ve_get_read_size_for_next_enc(struct ve_task *ctx,
						uint32_t *required_size)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (ctx == NULL || required_size == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(ctx, FW_STATE_POWER_ON, TASK_STATE_ENC_PHASE);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_GET_READ_SZ, (uint32_t)0);

	/* get read size */
	*required_size = rsc_get_read_size_for_next_enc(&(ctx->io_buff),
							ctx->one_frm_size);

	return ret;
}

/* handler interrupt */
enum ve_result ve_handle_interrupt(struct ve_response *resp,
				struct ve_dying_message *msg, uint32_t pu_id)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (resp == NULL || msg == NULL)
		return VE_ERROR_PARAMETERS;

	/* check pu_id */
	if (pu_id > VIP4_PU_MAX_VAL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, FW_STATE_NOT_INITIAL, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_HANDLE_ITR, pu_id);

	ret = rsp_handle_interrupt(resp, msg, pu_id);

	return ret;
}

/* initialize task */
enum ve_result ve_send_initialize_task_cmd(struct ve_task *ctx, uint32_t pu_id)
{
	enum ve_result ret = VE_OK;

	/* check boot */
	if (stt_chk_boot_api() != VE_OK)
		return VE_ERROR_REJECT;

	VELOGTRACE(VE_LT_SEND_INIT_TSK, (uint32_t)0);

	ret = cmd_prepare_send_command(pu_id);
	if (ret != VE_OK)
		return ret;

	/* check NULL */
	if (ctx == NULL) {
		ret = VE_ERROR_PARAMETERS;
		goto out;
	}

	/* check pu_id */
	if (pu_id > VIP4_PU_MAX_VAL) {
		ret = VE_ERROR_PARAMETERS;
		goto out;
	}

	/* check fw and task state */
	ret = stt_chk_implement(ctx, VE_FW_STATE_READY, VE_TASK_UNINITIALIZED);
	if (ret != VE_OK)
		goto out;

	/* set command parameters */
	cmd_mk_initialize_param(acs_get_cmd_addr(pu_id));

	ret = cmd_send_command(VE_CMD_INITIALIZE_TASK,
					acs_get_cmd_addr(pu_id), ctx, pu_id);

out:
	cmd_post_send_command(pu_id);

	return ret;
}

/* set parameters and allocate buffer */
enum ve_result ve_send_resources_cmd(struct ve_task *ctx,
					const struct ve_param *param,
					uint32_t pu_id)
{
	enum ve_result ret = VE_OK;

	/* check boot */
	if (stt_chk_boot_api() != VE_OK)
		return VE_ERROR_REJECT;

	VELOGTRACE(VE_LT_SEND_RSC, (uint32_t)0);

	ret = cmd_prepare_send_command(pu_id);
	if (ret != VE_OK)
		return ret;

	/* check NULL */
	if (ctx == NULL || param == NULL) {
		ret = VE_ERROR_PARAMETERS;
		goto out;
	}

	/* check pu_id */
	if (pu_id > VIP4_PU_MAX_VAL) {
		ret = VE_ERROR_PARAMETERS;
		goto out;
	}

	/* check fw and task state */
	ret = stt_chk_implement(ctx, VE_FW_STATE_READY, VE_TASK_PREPARED);
	if (ret != VE_OK)
		goto out;

	/* check encode parameters */
	ret = rsc_chk_param(param);
	if (ret != VE_OK)
		goto out;
	if (param->vui_parameters == 1) {
		ret = rsc_chk_vui_param(param);
		if (ret != VE_OK)
			goto out;
	}

	/* save 1frame output buffer */
	ctx->one_frm_size = rsc_get_1frame_out_buf_size(
			param->horizontal_pixels, param->vertical_pixels);

	/* set command parameters */
	ret = cmd_mk_resources_param(param, &(ctx->io_buff),
						acs_get_cmd_addr(pu_id));
	if (ret != VE_OK)
		goto out;

	ret = cmd_send_command(VE_CMD_INITIALIZE_IOBUFFER,
					acs_get_cmd_addr(pu_id), ctx, pu_id);
out:
	cmd_post_send_command(pu_id);

	return ret;
}

/* exec encoding */
enum ve_result ve_send_encode_cmd(struct ve_task *ctx,
					struct ve_picture_entry *pic,
					uint32_t pu_id)
{
	enum ve_result ret = VE_OK;
	uint32_t read_size;

	/* check boot */
	if (stt_chk_boot_api() != VE_OK)
		return VE_ERROR_REJECT;

	VELOGTRACE(VE_LT_SEND_ENCODE, (uint32_t)0);

	ret = cmd_prepare_send_command(pu_id);
	if (ret != VE_OK)
		return ret;

	/* check NULL */
	if (ctx == NULL) {
		ret = VE_ERROR_PARAMETERS;
		goto out;
	}
	if (ctx->enc_state == NO_ENC && pic == NULL) {
		ret = VE_ERROR_INSUFFICIENT_INPUT_FRAME;
		goto out;
	}

	/* check pu_id */
	if (pu_id > VIP4_PU_MAX_VAL) {
		ret = VE_ERROR_PARAMETERS;
		goto out;
	}

	/* check attribute */
	if (pic != NULL) {
		if (pic->attribute > VE_PIC_SYNC_FRAME) {
			ret = VE_ERROR_PARAMETERS;
			goto out;
		}
	}

	/* check fw and task state */
	ret = stt_chk_implement(ctx, VE_FW_STATE_READY,
			(VE_TASK_WAIT_FOR_FRAME | VE_TASK_WAIT_FOR_FLUSH));
	if (ret != VE_OK)
		goto out;

	/* check output buffer */
	read_size = rsc_get_read_size_for_next_enc(&(ctx->io_buff),
							ctx->one_frm_size);
	if (read_size != 0) {
		ret = VE_ERROR_INSUFFICIENT_FREE_SPACE;
		goto out;
	}

	ret = cmd_mk_encode_param(pic, acs_get_cmd_addr(pu_id));
	if (ret != VE_OK)
		goto out;

	ret = cmd_send_command(VE_CMD_ENCODE,
					acs_get_cmd_addr(pu_id), ctx, pu_id);
out:
	cmd_post_send_command(pu_id);

	return ret;
}

/* kill task */
enum ve_result ve_send_kill_task_cmd(struct ve_task *ctx, uint32_t pu_id)
{
	enum ve_result ret = VE_OK;

	/* check boot */
	if (stt_chk_boot_api() != VE_OK)
		return VE_ERROR_REJECT;

	VELOGTRACE(VE_LT_SEND_KILL, (uint32_t)0);

	ret = cmd_prepare_send_command(pu_id);
	if (ret != VE_OK)
		return ret;

	/* check NULL */
	if (ctx == NULL) {
		ret = VE_ERROR_PARAMETERS;
		goto out;
	}

	/* check pu_id */
	if (pu_id > VIP4_PU_MAX_VAL) {
		ret = VE_ERROR_PARAMETERS;
		goto out;
	}

	/* check fw and task state */
	ret = stt_chk_implement(ctx, (VE_FW_STATE_READY | VE_FW_STATE_RUNNING),
							TASK_STATE_ENC_PHASE);
	if (ret != VE_OK)
		goto out;

	ret = cmd_mk_kill_task_param(acs_get_cmd_addr(pu_id));
	if (ret != VE_OK)
		goto out;

	ret = cmd_send_command(VE_CMD_KILL_TASK,
					acs_get_cmd_addr(pu_id), ctx, pu_id);

out:
	cmd_post_send_command(pu_id);

	return ret;
}

/* get output buffer entry */
enum ve_result ve_get_output_buf_entry(struct ve_task *ctx,
					struct ve_output_entry *entry)
{
	enum ve_result ret = VE_OK;
	uint32_t base_addr;
	uint32_t curr_rp_addr;
	uint32_t adv_addr;
	uint32_t tmp[3];
	uint32_t cont_id;

	/* check NULL */
	if (ctx == NULL || entry == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw and task state */
	ret = stt_chk_implement(ctx, FW_STATE_POWER_ON, TASK_STATE_GETTABLE_ES);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_GET_OUTPUT, (uint32_t)0);

	ret = rsc_get_buf_rp(&(ctx->io_buff), &curr_rp_addr, &adv_addr,
				&tmp[0], &tmp[1], &tmp[2], &cont_id,
				NAL_INFO_NOT_ADV);
	if (ret != VE_OK)
		return ret;

	base_addr = ctx->io_buff.output.addr.v_addr;
	entry->begin = curr_rp_addr - base_addr;
	entry->end = adv_addr - base_addr;
	entry->frame_id = ((uint64_t)tmp[1] << 32) | (uint64_t)tmp[2];

	/* attribute */
	if (cont_id == NAL_UNIT_TYPE_IDR)
		entry->attribute = VE_PIC_SYNC_FRAME;
	else
		entry->attribute = VE_PIC_NOTHING;

	return ret;
}

/* advance rp of output and nal info buffers */
enum ve_result ve_next_output_buf_entry(struct ve_task *ctx)
{
	enum ve_result ret = VE_OK;
	uint32_t adv_addr;
	uint32_t adv_info_addr;
	uint32_t tmp[4];

	/* check NULL */
	if (ctx == NULL)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(ctx, FW_STATE_POWER_ON, TASK_STATE_GETTABLE_ES);
	if (ret != VE_OK)
		return ret;

	VELOGTRACE(VE_LT_NEXT_OUTPUT, (uint32_t)0);

	ret = rsc_get_buf_rp(&(ctx->io_buff), &tmp[0], &adv_addr,
				&adv_info_addr, &tmp[1], &tmp[2], &tmp[3],
				NAL_INFO_ADV);
	if (ret != VE_OK)
		return ret;

	/* output */
	rsc_set_buf_rp(&(ctx->io_buff), adv_addr, adv_info_addr);

	return ret;
}

/* set trace log buffer */
enum ve_result ve_set_trace_log_buf(struct ve_buf *log_buf, uint32_t pu_id)
{
	enum ve_result ret = VE_OK;

	/* check NULL */
	if (log_buf == NULL)
		return VE_ERROR_PARAMETERS;
	if (log_buf->addr.p_addr == 0)
		return VE_ERROR_PARAMETERS;

	/* check align */
	ret = acs_chk_align(log_buf->addr.p_addr, 0x10);
	ret |= acs_chk_align(log_buf->size, 0x20);
	if (ret != VE_OK)
		return ret;

	/* check size */
	if (log_buf->size < 0x00100000)
		return VE_ERROR_PARAMETERS;

	/* check fw state */
	ret = stt_chk_implement(NULL, VE_FW_STATE_POWER_OFF, TASK_STATE_NA);
	if (ret != VE_OK)
		return ret;

	acs_rev_write32(CMN_VE_LOG_SEQ, 0);

#ifdef VE_LOG_TRACE
	{
		uint32_t ve_size = log_buf->size >> 1;

		acs_write32(CMN_FW_LOG_BEGIN, acs_trans_p2vbus_addr(
					log_buf->addr.p_addr + ve_size));
		acs_write32(CMN_FW_LOG_END, acs_trans_p2vbus_addr(
					log_buf->addr.p_addr + log_buf->size));
		acs_rev_write32(CMN_VE_LOG_BEGIN, log_buf->addr.v_addr);
		acs_rev_write32(CMN_VE_LOG_END,
					(log_buf->addr.v_addr + ve_size));
		acs_rev_write32(CMN_VE_LOG_CUR, log_buf->addr.v_addr);
		VELOGTRACE(VE_LT_START, ve_size);
	}
#else
	acs_write32(CMN_FW_LOG_BEGIN,
				acs_trans_p2vbus_addr(log_buf->addr.p_addr));
	acs_write32(CMN_FW_LOG_END, acs_trans_p2vbus_addr(
				log_buf->addr.p_addr + log_buf->size));
	acs_write32(CMN_VE_LOG_BEGIN, 0);
	acs_write32(CMN_VE_LOG_END, 0);
	acs_write32(CMN_VE_LOG_CUR, 0);
#endif

	return ret;
}

