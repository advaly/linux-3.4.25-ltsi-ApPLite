/*
 * drivers/staging/applite/veu/ve_command.c
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

#include "ve_access.h"
#include "ve_command.h"
#include "ve_resources.h"
#include "ve_state.h"

/* make param to startup or shutdown */
enum ve_result cmd_mk_power_on_off_param(uint32_t cmd_addr)
{
	struct cmd_area *cmd;

	cmd = (struct cmd_area *)cmd_addr;

	/* set command */
	cmd->com_num_of_args = VE_REV(1);
	cmd->com_arg[0] = 0x0;

	return VE_OK;
}

/* make param to initialize task */
enum ve_result cmd_mk_initialize_param(uint32_t cmd_addr)
{
	struct cmd_area *cmd;

	cmd = (struct cmd_area *)cmd_addr;

	/* set command */
	cmd->com_num_of_args = VE_REV(1);
	cmd->com_arg[0] = 0x0;

	return VE_OK;
}

/* make param to set resources of task */
enum ve_result cmd_mk_resources_param(const struct ve_param *enc_param,
			struct ve_io_buf_area *io_buff, uint32_t cmd_addr)
{
	enum ve_result ret = VE_OK;
	uint32_t frame_rate_num = 0;
	uint32_t frame_rate_denom;
	struct cmd_area *cmd;
	uint32_t i = 0;

	cmd = (struct cmd_area *)cmd_addr;

	/* calculate frame rate numelator and denomilator */
	ret = rsc_calc_frame_rate(enc_param->frame_rate,
					&frame_rate_num, &frame_rate_denom);
	if (ret != VE_OK)
		return ret;

	/* set command */
	if (enc_param->vui_parameters)
		cmd->com_num_of_args = VE_REV(55);
	else
		cmd->com_num_of_args = VE_REV(30);

	cmd->com_arg[i++] = acs_trans_p2vbus_addr(io_buff->control.addr.p_addr);
	cmd->com_arg[i++] = acs_trans_p2vbus_addr(io_buff->control.addr.p_addr +
						sizeof(struct rsc_fifo_base));
	cmd->com_arg[i++] = acs_trans_p2vbus_addr(io_buff->work.addr.p_addr);
	cmd->com_arg[i++] = VE_REV(io_buff->work.size);
	cmd->com_arg[i++] = acs_trans_p2vbus_addr(io_buff->reference.addr);
	cmd->com_arg[i++] = VE_REV(io_buff->reference.size);
	cmd->com_arg[i++] = VE_REV(enc_param->output_mode);
	cmd->com_arg[i++] = VE_REV(enc_param->profile);
	cmd->com_arg[i++] = VE_REV(enc_param->level);
	cmd->com_arg[i++] = VE_REV(enc_param->horizontal_pixels);
	cmd->com_arg[i++] = VE_REV(enc_param->vertical_pixels);
	cmd->com_arg[i++] = VE_REV(frame_rate_num);
	cmd->com_arg[i++] = VE_REV(frame_rate_denom);
	cmd->com_arg[i++] = VE_REV(enc_param->kbps);
	cmd->com_arg[i++] = VE_REV(enc_param->max_kbps);
	cmd->com_arg[i++] = VE_REV(enc_param->cpb_size_kbits);
	cmd->com_arg[i++] = VE_REV(enc_param->rate_control_mode);
	cmd->com_arg[i++] = VE_REV(enc_param->m);
	cmd->com_arg[i++] = VE_REV(enc_param->n);
	cmd->com_arg[i++] = VE_REV(enc_param->idr_freq);
	cmd->com_arg[i++] = VE_REV(enc_param->picture_struct);
	cmd->com_arg[i++] = VE_REV(enc_param->slice_num_minus1);
	cmd->com_arg[i++] = VE_REV(enc_param->scaling_matrix);
	cmd->com_arg[i++] = VE_REV(enc_param->entropy_coding);
	cmd->com_arg[i++] = VE_REV(enc_param->weighted_pred);
	cmd->com_arg[i++] = VE_REV(enc_param->reference_b);
	cmd->com_arg[i++] = VE_REV(enc_param->inter_view_pred);
	cmd->com_arg[i++] = VE_REV(enc_param->vui_parameters);
	cmd->com_arg[i++] = VE_REV(enc_param->sei0);
	cmd->com_arg[i++] = VE_REV(enc_param->aspect_ratio_info_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->aspect_ratio_idc);
	cmd->com_arg[i++] = VE_REV(enc_param->sar_width);
	cmd->com_arg[i++] = VE_REV(enc_param->sar_height);
	cmd->com_arg[i++] = VE_REV(enc_param->overscan_info_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->overscan_appropriate_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->video_signal_type_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->video_format);
	cmd->com_arg[i++] = VE_REV(enc_param->video_full_range_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->colour_description_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->colour_primaries);
	cmd->com_arg[i++] = VE_REV(enc_param->transfer_characteristics);
	cmd->com_arg[i++] = VE_REV(enc_param->matrix_coefficients);
	cmd->com_arg[i++] = VE_REV(enc_param->chroma_loc_info_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->chroma_sample_loc_type_top_field);
	cmd->com_arg[i++] =
			VE_REV(enc_param->chroma_sample_loc_type_bottom_field);
	cmd->com_arg[i++] = VE_REV(enc_param->timing_info_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->num_units_in_tick);
	cmd->com_arg[i++] = VE_REV(enc_param->time_scale);
	cmd->com_arg[i++] = VE_REV(enc_param->fixed_frame_rate_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->nal_hrd_parameters_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->vcl_hrd_parameters_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->low_delay_hrd_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->pic_struct_present_flag);
	cmd->com_arg[i++] = VE_REV(enc_param->bitstream_restriction_flag);

	return ret;
}

/* make param to encode 1 frame */
enum ve_result cmd_mk_encode_param(struct ve_picture_entry *pic,
							uint32_t cmd_addr)
{
	struct cmd_area *cmd;

	cmd = (struct cmd_area *)cmd_addr;

	/* set command */
	if (pic != NULL) {
		cmd->com_num_of_args = VE_REV(5);
		cmd->com_arg[0] = acs_trans_p2vbus_addr(pic->luma);
		cmd->com_arg[1] = acs_trans_p2vbus_addr(pic->chroma);
		cmd->com_arg[2] = VE_REV(
				(uint32_t)((uint64_t)pic->frame_id >> 32));
		cmd->com_arg[3] =
			VE_REV((uint32_t)(pic->frame_id & 0xffffffffULL));
		cmd->com_arg[4] = VE_REV(pic->attribute);
	} else {
		cmd->com_num_of_args = VE_REV(0);
	}

	return VE_OK;
}

/* make param to kill task */
enum ve_result cmd_mk_kill_task_param(uint32_t cmd_addr)
{
	struct cmd_area *cmd;

	cmd = (struct cmd_area *)cmd_addr;

	/* set command */
	cmd->com_num_of_args = VE_REV(0);

	return VE_OK;
}

/* previous process for send command */
enum ve_result cmd_prepare_send_command(uint32_t pu_id)
{
	enum ve_result ret = VE_OK;
	struct ve_accessor access;
	uint32_t mbox_state;

	/* lock */
	access = acs_get_accessor();
	access.lock(access.private_data);

	/* get mbox state */
	acs_rev_read32(access.to_vip4.set.v_addr, &mbox_state);
	if (mbox_state != 0x0) {
		ret = VE_ERROR_MBOX_BUSY;
		/* unlock */
		access.unlock(access.private_data);
	}

	return ret;
}

/* post process for send command */
void cmd_post_send_command(uint32_t pu_id)
{
	struct ve_accessor access;

	access = acs_get_accessor();

	/* unlock */
	access.unlock(access.private_data);
}


/* send command to VIP4 */
enum ve_result cmd_send_command(uint32_t cmd_id, uint32_t cmd_addr,
					struct ve_task *ctx, uint32_t pu_id)
{
	enum ve_result ret = VE_OK;
	struct cmd_area *cmd;
	uint32_t dummy;
	struct ve_accessor access;

	cmd = (struct cmd_area *)(cmd_addr);

	/* set task data */
	if (cmd_id == VE_CMD_START_UP_PU || cmd_id == VE_CMD_SHUT_DOWN_PU) {
		cmd->com_task_api = 0;
		cmd->com_task_fw = 0;
	} else {
		cmd->com_task_api = (uint32_t)ctx;
		cmd->com_task_fw = ctx->task_fw;
		ret = stt_set_next_task_state_in_cmd(cmd_id,
					cmd->com_num_of_args, &(ctx->state));
	}

	cmd->com_command_id = VE_REV(cmd_id);

	/* dummy read */
	acs_read32(cmd_addr, &dummy);

	/* intrerrupt */
	if (ret == VE_OK) {
		access = acs_get_accessor();
		acs_rev_write32(access.to_vip4.set.v_addr, 0x80000000);
	}

	return ret;
}

