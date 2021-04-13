/*
 * drivers/staging/applite/vdu/vd_api.h
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

#ifndef VD_API_H
#define VD_API_H

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif


#define VD_API_VERSION 5

extern int vd_errno;

typedef uint32_t vd_virtual_t;
typedef uint32_t vd_physical_t;
typedef uint32_t vd_vbus_t;
typedef uint32_t vd_vtile_t;

enum vd_result {
	VD_SUCCESS,
	VD_BAD_PARAM,
	VD_NOT_INIT,
	VD_NOT_APPLICABLE,
	VD_NO_MORE,
};

enum vd_fw_state {
	VD_FW_NOT_INIT,
	VD_FW_POWER_OFF,
	VD_FW_BOOTING,
	VD_FW_READY,
	VD_FW_RUNNING,
	VD_FW_SHUTTING_DOWN,
	VD_FW_SHUT_DOWN,
};

enum vd_task_state {
	VD_TASK_PREPARED,
	VD_TASK_STARTING,
	VD_TASK_DECODING,
	VD_TASK_STOPPING,
};

enum vd_decoder_type {
	VD_DECODER_TYPE_H264,
	VD_DECODER_TYPE_MVC,
};

struct vd_address {
	vd_physical_t p_addr;
	vd_virtual_t  v_addr;
};

struct vd_accessor {
	struct vd_address fw_address;
	void (*lock)(void *private_data);
	void (*unlock)(void *private_data);
	void *private_data;
	vd_virtual_t mbox_addr;
};

struct vd_buf {
	struct vd_address addr;
	uint32_t size;
};

struct vd_task {
	enum vd_task_state state;
	int ch;
};

struct vd_param {
	enum vd_decoder_type decoder;
	uint32_t nuf;
};

struct vd_frame_info {
	vd_vtile_t addr;
	uint32_t id0[2];
	uint32_t id1[2];
	uint32_t width;
	uint32_t height;
	uint32_t crop_top;
	uint32_t crop_bottom;
	uint32_t crop_left;
	uint32_t crop_right;
	uint32_t num_units_in_tick;
	uint32_t time_scale;
	uint32_t sar_width;
	uint32_t sar_height;
	uint32_t interlaced;
	uint32_t eod;
};

struct vd_ring_buffer_info {
	vd_physical_t sp;
	vd_physical_t ep;
	vd_physical_t rp;
	vd_physical_t wp;
};

enum vd_result vd_fw_initialize(struct vd_accessor *accessor);
enum vd_result vd_fw_finalize(void);
enum vd_result vd_fw_start_up(uint32_t pu_id);
enum vd_result vd_fw_shut_down(uint32_t pu_id);
enum vd_result vd_fw_get_state(uint32_t pu_id, enum vd_fw_state *state);

enum vd_result vd_task_create(uint32_t pu_id, struct vd_task *task);
enum vd_result vd_task_destroy(struct vd_task *task);
enum vd_result vd_task_start(struct vd_task *task,
			      struct vd_param *param,
			      struct vd_buf *std,
			      struct vd_buf *work,
			      struct vd_buf *frame);
enum vd_result vd_task_stop(struct vd_task *task);
enum vd_result vd_task_get_state(struct vd_task *task,
				  enum vd_task_state *stat);
enum vd_result vd_task_get_ch(struct vd_task *task, uint32_t *ch);

enum vd_result vd_frame_is_available(struct vd_task *task,
				      uint32_t *is_available);
enum vd_result vd_frame_get(struct vd_task *task,
			     struct vd_frame_info *info);
enum vd_result vd_frame_release(struct vd_task *task);

enum vd_result vd_buffer_get_info(struct vd_task *task,
				   struct vd_ring_buffer_info *info);
enum vd_result vd_buffer_set_wp(struct vd_task *task,
				 struct vd_address *address);
enum vd_result vd_buffer_set_eod(struct vd_task *task);

enum vd_result vd_debug_get_fw_version(uint32_t *version);
enum vd_result vd_debug_get_api_version(uint32_t *version);
enum vd_result vd_debug_set_trace_buf(uint32_t pu_id,
				       struct vd_buf *mem);
enum vd_result vd_debug_get_pc(uint32_t pu_id, uint32_t pc[2]);

#endif /* VD_API_H */
