/*
 * drivers/staging/applite/vdu/vd_api.c
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "vd_api.h"
#include "vd_accessor.h"
#include "vd_config.h"
#include "vd_comm.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

int vd_errno;

#define EOD_INPUT (1<<0)
#define EOD_OUTPUT (1<<1)
struct vd_ch_state_t {
	int is_used;
	int state;
	uint32_t eod_flags;
};

static enum vd_fw_state vd_fw_state = VD_FW_NOT_INIT;
static struct vd_ch_state_t vd_ch_state[VD_CH_NUM_MAX];

static vd_vbus_t vd_p2v(vd_physical_t p_addr)
{
	if (0x80000000 <= p_addr && p_addr < 0xC0000000)
		return p_addr - 0x40000000UL;
	else
		return p_addr;
}


static vd_physical_t vd_v2p(vd_vbus_t v_addr)
{
	if (0x40000000 <= v_addr && v_addr < 0x80000000)
		return v_addr + 0x40000000UL;
	else
		return v_addr;
}


static void vd_task_update_state(int ch)
{
	enum vd_task_state state;
	uint32_t running_bap;
	uint32_t running_vdp;
	int i;
	int state_change_flag;

	if (vd_ch_state[ch].state != VD_TASK_STARTING
	    && vd_ch_state[ch].state != VD_TASK_STOPPING) {
		return;
	}

	running_bap = vd_acs_get(VDCOMM_RUNNING_BAP(ch));
	running_vdp = vd_acs_get(VDCOMM_RUNNING_VDP(ch));

	if (vd_ch_state[ch].state == VD_TASK_STARTING) {
		if (running_bap != 0 && running_vdp != 0)
			vd_ch_state[ch].state = VD_TASK_DECODING;
	}
	if (vd_ch_state[ch].state == VD_TASK_STOPPING) {
		if (running_bap == 0 && running_vdp == 0) {
			vd_ch_state[ch].state = VD_TASK_PREPARED;

			/* Check if all ch is not decoding */
			state_change_flag = 1;
			for (i = 0; i < VD_CH_NUM_MAX; i++) {
				state = vd_ch_state[i].state;
				state_change_flag
				    &= (state != VD_TASK_DECODING);
			}
			if (state_change_flag)
				vd_fw_state = VD_FW_READY;
		}
	}

	return;
}


static void vd_fw_update_state(void)
{
	uint32_t mep_state[2];
	int i;

	if (vd_fw_state != VD_FW_BOOTING
	    && vd_fw_state != VD_FW_POWER_OFF
	    && vd_fw_state != VD_FW_SHUTTING_DOWN
	    && vd_fw_state != VD_FW_RUNNING) {
		return;
	}

	mep_state[0] = vd_acs_get(VDCOMM_FW_STATE(0));
	mep_state[1] = vd_acs_get(VDCOMM_FW_STATE(1));

	if (vd_fw_state == VD_FW_BOOTING || vd_fw_state == VD_FW_POWER_OFF) {
		if (mep_state[0] == VDCOMM_FW_STATE_READY
		    && mep_state[1] == VDCOMM_FW_STATE_READY) {
			vd_fw_state = VD_FW_READY;
		} else if (mep_state[0] == VDCOMM_FW_STATE_BOOTING
			 || mep_state[1] == VDCOMM_FW_STATE_BOOTING) {
			vd_fw_state = VD_FW_BOOTING;
		}
	} else if (vd_fw_state == VD_FW_SHUTTING_DOWN) {
		if (mep_state[0] == VDCOMM_FW_STATE_SHUTDOWN
		    && mep_state[1] == VDCOMM_FW_STATE_SHUTDOWN) {
			vd_fw_state = VD_FW_SHUT_DOWN;
		}
	} else if (vd_fw_state == VD_FW_RUNNING) {
		for (i = 0; i < VD_CH_NUM_MAX; i++)
			vd_task_update_state(i);
	}

	return;
}


enum vd_result vd_fw_initialize(struct vd_accessor *accessor)
{
	enum vd_result ret;
	int i;
	const uint32_t FW_IF_VERSION_OFFSET = 0x400;
	uint32_t if_version;
	uint32_t *ptr;

	if (vd_fw_state != VD_FW_NOT_INIT) {
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	if (accessor == NULL) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	if ((accessor->fw_address.p_addr & (0x1000000-1)) != 0
	    || accessor->fw_address.v_addr == 0
	    || accessor->lock == NULL
	    || accessor->unlock == NULL
	    || accessor->private_data == NULL
	    || accessor->mbox_addr == 0) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	ret = vd_acs_init(accessor);
	if (ret != VD_SUCCESS) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	ptr = (uint32_t *)(accessor->fw_address.v_addr + FW_IF_VERSION_OFFSET);
	if_version = VD_REV(*ptr);
	if (if_version != VDCOMM_IF_VERSION) {
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	for (i = 0; i < VD_CH_NUM_MAX; i++) {
		vd_ch_state[i].is_used = 0;
		vd_ch_state[i].state = -1;
		vd_ch_state[i].eod_flags = 0;
	}

	vd_fw_state = VD_FW_POWER_OFF;

	return VD_SUCCESS;
}


enum vd_result vd_fw_start_up(uint32_t pu_id)
{
	vd_acs_lock();
	if (pu_id != 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (vd_fw_state != VD_FW_POWER_OFF) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	vd_fw_state = VD_FW_BOOTING;

	vd_acs_unlock();
	return VD_SUCCESS;
}


enum vd_result vd_fw_finalize(void)
{
	vd_acs_lock();

	if (vd_fw_state != VD_FW_SHUT_DOWN) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	vd_fw_state = VD_FW_NOT_INIT;

	vd_acs_unlock();

	return VD_SUCCESS;
}


enum vd_result vd_fw_shut_down(uint32_t pu_id)
{
	int i;

	vd_acs_lock();

	if (pu_id != 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (vd_fw_state != VD_FW_READY) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	for (i = 0; i < VD_CH_NUM_MAX; i++) {
		if (vd_ch_state[i].is_used != 0) {
			vd_acs_unlock();
			vd_errno = __LINE__;
			return VD_NOT_APPLICABLE;
		}
	}

	vd_acs_set(VDCOMM_SHUTDOWNCMD(0), 1);
	vd_acs_set(VDCOMM_SHUTDOWNCMD(1), 1);

	vd_acs_interrupt(MBOX_INT_REG401_SET_OFFS, 0);
	vd_acs_interrupt(MBOX_INT_REG409_SET_OFFS, 0);

	vd_fw_state = VD_FW_SHUTTING_DOWN;

	vd_acs_unlock();

	return VD_SUCCESS;
}


enum vd_result
vd_fw_get_state(uint32_t pu_id, enum vd_fw_state *state)
{
	vd_acs_lock();

	if (pu_id != 0 || state == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	vd_fw_update_state();
	*state = vd_fw_state;

	vd_acs_unlock();
	return VD_SUCCESS;
}


enum vd_result
vd_task_create(uint32_t pu_id, struct vd_task *task)
{
	int i;
	int ch;

	vd_acs_lock();

	if (pu_id != 0 || task == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	vd_fw_update_state();

	if (vd_fw_state != VD_FW_READY && vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	for (i = 0; i < VD_CH_NUM_MAX; i++) {
		if (vd_ch_state[i].is_used == 0) {
			ch = i;
			break;
		}
	}
	if (i == VD_CH_NUM_MAX) {
		vd_acs_unlock();
		/* No available ch was found. */
		vd_errno = __LINE__;
		return VD_NO_MORE;
	}

	task->state = VD_TASK_PREPARED;
	task->ch = ch;
	vd_ch_state[task->ch].is_used = 1;
	vd_ch_state[task->ch].state = VD_TASK_PREPARED;

	vd_acs_unlock();

	return VD_SUCCESS;
}


enum vd_result
vd_task_destroy(struct vd_task *task)
{
	vd_acs_lock();

	if (task == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (vd_ch_state[task->ch].is_used == 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_fw_state != VD_FW_READY && vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_PREPARED) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	vd_ch_state[task->ch].is_used = 0;
	vd_ch_state[task->ch].state = -1;
	task->ch = -1;

	vd_acs_unlock();

	return VD_SUCCESS;
}


enum vd_result
vd_task_start(struct vd_task *task, struct vd_param *param,
	       struct vd_buf *std, struct vd_buf *work, struct vd_buf *frame)
{
	int ch;

	vd_acs_lock();

	if (vd_fw_state == VD_FW_NOT_INIT) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_INIT;
	}
	if (task == NULL || param == NULL ||
	    std == NULL || work == NULL || frame == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (std->size != VD_BUF_STD_SIZE
	    || work->size != VD_BUF_WORK_SIZE
	    || frame->size != VD_BUF_FRAME_SIZE) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if ((std->addr.p_addr & (4*1024-1)) != 0
	    || (work->addr.p_addr & (4*1024-1)) != 0
	    || (frame->addr.p_addr & (1*1024*1024-1)) != 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if ((std->addr.p_addr&(1024*1024*1024))
	    != ((std->addr.p_addr+std->size - 1)&(1024*1024*1024))
	    || (work->addr.p_addr&(1024*1024*1024))
	    != ((work->addr.p_addr+work->size - 1)&(1024*1024*1024))
	    || (frame->addr.p_addr&(1024*1024*1024))
	    != ((frame->addr.p_addr+frame->size - 1)&(1024*1024*1024))) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (std->addr.v_addr == (vd_virtual_t)NULL
	    || work->addr.v_addr == (vd_virtual_t)NULL
	    || frame->addr.v_addr == (vd_virtual_t)NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	if (param->decoder != VD_DECODER_TYPE_H264) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (vd_ch_state[task->ch].is_used == 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_fw_state != VD_FW_READY && vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_PREPARED) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	ch = task->ch;
	vd_ch_state[ch].state = VD_TASK_STARTING;
	vd_ch_state[ch].eod_flags = 0;
	vd_fw_state = VD_FW_RUNNING;

	vd_acs_set(VDCOMM_VSTD_SP(ch), vd_p2v(std->addr.p_addr));
	vd_acs_set(VDCOMM_VSTD_EP(ch), vd_p2v(std->addr.p_addr + std->size));
	vd_acs_set(VDCOMM_VSTD_WP(ch), vd_p2v(std->addr.p_addr));
	vd_acs_set(VDCOMM_VSTD_RP(ch), vd_p2v(std->addr.p_addr));

	vd_acs_set(VDCOMM_WORKMEM_ADR(ch), vd_p2v(work->addr.p_addr));
	vd_acs_set(VDCOMM_WORKMEM_SIZE(ch), work->size);
	vd_acs_set(VDCOMM_FRAMEMEM_ADR(ch), vd_p2v(frame->addr.p_addr));
	vd_acs_set(VDCOMM_FRAMEMEM_SIZE(ch), frame->size);

	vd_acs_set(VDCOMM_VSTD_NUSZ(ch), param->nuf);
	vd_acs_set(VDCOMM_VSTD_EOD(ch), 0);
	vd_acs_set(VDCOMM_OREADY(ch), VDCOMM_OUTPUT_NOT_READY);

	vd_acs_set(VDCOMM_STARTCMD(ch), 1);

	vd_acs_interrupt(MBOX_INT_REG400_SET_OFFS, ch);
	vd_acs_interrupt(MBOX_INT_REG408_SET_OFFS, ch);

	vd_acs_unlock();
	return VD_SUCCESS;
}


enum vd_result
vd_task_stop(struct vd_task *task)
{
	int ch;
	vd_acs_lock();

	if (vd_fw_state == VD_FW_NOT_INIT) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_INIT;
	}
	if (task == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (vd_ch_state[task->ch].is_used == 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_DECODING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	ch = task->ch;
	vd_task_update_state(ch);

	vd_acs_set(VDCOMM_STARTCMD(ch), 0);

	vd_acs_interrupt(MBOX_INT_REG400_SET_OFFS, ch);
	vd_acs_interrupt(MBOX_INT_REG408_SET_OFFS, ch);

	vd_ch_state[ch].state = VD_TASK_STOPPING;

	vd_acs_unlock();
	return VD_SUCCESS;
}


enum vd_result
vd_task_get_state(struct vd_task *task, enum vd_task_state *stat)
{
	vd_acs_lock();

	if (task == NULL || stat == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	vd_task_update_state(task->ch);
	vd_acs_unlock();

	*stat = vd_ch_state[task->ch].state;
	return VD_SUCCESS;
}


enum vd_result
vd_task_get_ch(struct vd_task *task, uint32_t *ch)
{
	vd_acs_lock();

	if (task == NULL || ch == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (task->ch == -1) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	if (vd_fw_state == VD_FW_NOT_INIT) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_INIT;
	}

	*ch = task->ch;
	vd_acs_unlock();
	return VD_SUCCESS;
}


enum vd_result
vd_frame_is_available(struct vd_task *task, uint32_t *is_available)
{
	uint32_t o_ready;
	int ch;

	vd_acs_lock();

	if (task == NULL
	    || task->ch == -1
	    || is_available == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (vd_fw_state == VD_FW_NOT_INIT) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_INIT;
	}

	ch = task->ch;
	vd_task_update_state(ch);

	if (vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_DECODING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	o_ready = vd_acs_get(VDCOMM_OREADY(ch));

	if (o_ready == VDCOMM_OUTPUT_READY)
		*is_available = 1;
	else
		*is_available = 0;

	vd_acs_unlock();
	return VD_SUCCESS;
}


enum vd_result
vd_frame_get(struct vd_task *task, struct vd_frame_info *info)
{
	int ch;
	uint32_t o_ready;
	vd_acs_lock();

	if (task == NULL || task->ch == -1 || info == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	ch = task->ch;
	vd_task_update_state(ch);

	if (vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_DECODING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if ((vd_ch_state[task->ch].eod_flags & EOD_OUTPUT) != 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NO_MORE;
	}

	o_ready = vd_acs_get(VDCOMM_OREADY(ch));
	if (o_ready != VDCOMM_OUTPUT_READY) {
		/* No available frame was found. */
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	info->addr        = vd_v2p(vd_acs_get(VDCOMM_OVTILEADR(ch))) ;
	info->id0[0]            =  vd_acs_get(VDCOMM_OPTS_M(ch));
	info->id0[1]            =  vd_acs_get(VDCOMM_OPTS_L(ch));
	info->id1[0]            =  vd_acs_get(VDCOMM_ODTS_M(ch));
	info->id1[1]            =  vd_acs_get(VDCOMM_ODTS_L(ch));
	info->height            = (vd_acs_get(VDCOMM_OSV(ch)) & 0xffff);
	info->width             = (vd_acs_get(VDCOMM_OSV(ch)) >> 16);
	info->crop_top          = (vd_acs_get(VDCOMM_OVCROP(ch)) >> 16);
	info->crop_bottom       = (vd_acs_get(VDCOMM_OVCROP(ch)) & 0xffff);
	info->crop_left         = (vd_acs_get(VDCOMM_OHCROP(ch)) >> 16);
	info->crop_right        = (vd_acs_get(VDCOMM_OHCROP(ch)) & 0xffff);
	info->num_units_in_tick =  vd_acs_get(VDCOMM_ONUMUNITS(ch));
	info->time_scale        =  vd_acs_get(VDCOMM_OTIMESCALE(ch));
	info->sar_width         = (vd_acs_get(VDCOMM_OSAR(ch))) >> 16;
	info->sar_height        = (vd_acs_get(VDCOMM_OSAR(ch))) & 0xffff;
	info->eod               = (vd_acs_get(VDCOMM_OEOD(ch))) & 0xffff;
	info->interlaced        = 0;

	vd_acs_unlock();

	return VD_SUCCESS;
}


enum vd_result
vd_frame_release(struct vd_task *task)
{
	int ch;
	uint32_t o_ready;
	int eod;

	vd_acs_lock();

	if (task == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	ch = task->ch;
	vd_task_update_state(ch);

	if (vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_DECODING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	o_ready = vd_acs_get(VDCOMM_OREADY(ch));
	if (o_ready != VDCOMM_OUTPUT_READY) {
		/* No available frame was found. */
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	eod = (vd_acs_get(VDCOMM_OEOD(ch))) & 0xffff;
	if (eod != 0)
		vd_ch_state[task->ch].eod_flags |= EOD_OUTPUT;

	vd_acs_set(VDCOMM_OREADY(ch), VDCOMM_OUTPUT_RELEASED);
	vd_acs_interrupt(MBOX_INT_REG410_SET_OFFS, task->ch);

	vd_acs_unlock();

	return VD_SUCCESS;
}


enum vd_result
vd_buffer_get_info(struct vd_task *task, struct vd_ring_buffer_info *info)
{
	int ch;

	vd_acs_lock();

	if (vd_fw_state == VD_FW_NOT_INIT) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (task == NULL || task->ch == -1 || info == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	ch = task->ch;
	vd_task_update_state(ch);

	if (vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_DECODING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	info->sp = vd_v2p(vd_acs_get(VDCOMM_VSTD_SP(ch)));
	info->ep = vd_v2p(vd_acs_get(VDCOMM_VSTD_EP(ch)));
	info->rp = vd_v2p(vd_acs_get(VDCOMM_VSTD_RP(ch)));
	info->wp = vd_v2p(vd_acs_get(VDCOMM_VSTD_WP(ch)));

	vd_acs_unlock();

	return VD_SUCCESS;
}


enum vd_result
vd_buffer_set_wp(struct vd_task *task, struct vd_address *address)
{
	int ch;
	uint32_t sp, ep;
	vd_acs_lock();

	if (vd_fw_state == VD_FW_NOT_INIT) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (task == NULL || address == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (address->v_addr == (vd_virtual_t)NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if ((vd_ch_state[task->ch].eod_flags & EOD_INPUT) != 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	ch = task->ch;
	sp = vd_v2p(vd_acs_get(VDCOMM_VSTD_SP(ch)));
	ep = vd_v2p(vd_acs_get(VDCOMM_VSTD_EP(ch)));
	if (address->p_addr < sp || address->p_addr >= ep) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	vd_task_update_state(ch);

	if (vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_DECODING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	vd_acs_set(VDCOMM_VSTD_WP(ch), vd_p2v(address->p_addr));

	vd_acs_unlock();

	return VD_SUCCESS;
}


enum vd_result
vd_buffer_set_eod(struct vd_task *task)
{
	int ch;

	vd_acs_lock();

	if (task == NULL) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if ((vd_ch_state[task->ch].eod_flags & EOD_INPUT) != 0) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	ch = task->ch;
	vd_task_update_state(ch);

	if (vd_fw_state != VD_FW_RUNNING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}
	if (vd_ch_state[task->ch].state != VD_TASK_DECODING) {
		vd_acs_unlock();
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	ch = task->ch;
	vd_acs_set(VDCOMM_VSTD_EOD(ch), 1);
	vd_ch_state[task->ch].eod_flags |= EOD_INPUT;

	vd_acs_unlock();
	return VD_SUCCESS;
}


enum vd_result
vd_debug_get_fw_version(uint32_t *version)
{
	if (version == NULL) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	if (vd_fw_state == VD_FW_NOT_INIT || vd_fw_state == VD_FW_POWER_OFF) {
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	*version = vd_acs_get(VDCOMM_VER(0));
	return VD_SUCCESS;
}


enum vd_result
vd_debug_get_api_version(uint32_t *version)
{
	if (version == NULL) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	*version = (uint32_t)(VD_API_VERSION + (VDCOMM_IF_VERSION<<16));
	return VD_SUCCESS;
}


enum vd_result
vd_debug_set_trace_buf(uint32_t pu_id,
			struct vd_buf *mem)
{
	if (pu_id != 0 || mem == NULL) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if (mem->size == 0 || (mem->size%4096) != 0) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}
	if ((mem->addr.p_addr%4096) != 0) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	if (vd_fw_state == VD_FW_NOT_INIT) {
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	vd_acs_set(VDCOMM_TRACE_SP(0), vd_p2v(mem->addr.p_addr));
	vd_acs_set(VDCOMM_TRACE_SIZE(0), mem->size/2);
	vd_acs_set(VDCOMM_TRACE_SP(1), vd_p2v(mem->addr.p_addr+mem->size/2));
	vd_acs_set(VDCOMM_TRACE_SIZE(1), mem->size/2);

	return VD_SUCCESS;
}


enum vd_result
vd_debug_get_pc(uint32_t pu_id, uint32_t pc[2])
{
	if (pu_id != 0 || pc == NULL) {
		vd_errno = __LINE__;
		return VD_BAD_PARAM;
	}

	vd_fw_update_state();

	if (vd_fw_state == VD_FW_NOT_INIT
	    || vd_fw_state == VD_FW_POWER_OFF
	    || vd_fw_state == VD_FW_SHUTTING_DOWN
	    || vd_fw_state == VD_FW_SHUT_DOWN) {
		vd_errno = __LINE__;
		return VD_NOT_APPLICABLE;
	}

	vd_acs_set(VDCOMM_NMI_NPC(0), 0xffffffff);
	vd_acs_set(VDCOMM_NMI_NPC(1), 0xffffffff);

	vd_acs_interrupt(MBOX_INT_REG404_SET_OFFS, 0);
	vd_acs_interrupt(MBOX_INT_REG412_SET_OFFS, 0);

	do {
		pc[0] = vd_acs_get(VDCOMM_NMI_NPC(0));
	} while (pc[0] == 0xffffffff);
	do {
		pc[1] = vd_acs_get(VDCOMM_NMI_NPC(1));
	} while (pc[1] == 0xffffffff);

	return VD_SUCCESS;
}

