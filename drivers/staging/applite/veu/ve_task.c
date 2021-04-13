/*
 * drivers/staging/applite/veu/ve_task.c
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

#include "ve_task.h"
#include "ve_access.h"

/* check VE_TASK_API and VE_TASK_FW */
enum ve_result tsk_chk_creating_mem(const struct ve_task_work_area *area)
{
	enum ve_result ret = VE_OK;
	uint32_t fw_area_size;

	/* check range */
	/* physical */
	ret = acs_chk_data_in_dram_range(area->fw.p_addr);
	/* virtual */
	ret |= acs_chk_addr_zero((uint32_t)(area->api));
	ret |= acs_chk_addr_zero(area->fw.v_addr);

	/* check align */
	/* physical */
	ret |= acs_chk_align(area->fw.p_addr, 0x8);
	/* virtual */
	ret |= acs_chk_align((uint32_t)(area->api), 0x40);
	ret |= acs_chk_align(area->fw.v_addr, 0x8);

	/* check crossing memory */
	acs_rev_read32(CMN_FW_CTX_SZ, &fw_area_size);
	ret |= acs_chk_crossing_memory(area->fw.p_addr, fw_area_size);

	return ret;
}

