/*
 * drivers/staging/applite/vdu/vd_accessor.c
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
#include "vd_comm.h"
#include "vd_config.h"
#include "vd_accessor.h"

static struct vd_accessor vd_s_acs;

enum vd_result vd_acs_init(const struct vd_accessor *acs)
{
	vd_s_acs = *acs;

	return VD_SUCCESS;
}


void vd_acs_lock(void)
{
	vd_s_acs.lock(vd_s_acs.private_data);
}


void vd_acs_unlock(void)
{
	vd_s_acs.unlock(vd_s_acs.private_data);
}


void vd_acs_set(uint32_t offset, uint32_t value)
{
	uint32_t *v_addr;

	v_addr = (void *)(vd_s_acs.fw_address.v_addr + offset);
	*v_addr = VD_REV(value);

	return;
}


uint32_t vd_acs_get(uint32_t offset)
{
	uint32_t *v_addr;

	v_addr = (void *)(vd_s_acs.fw_address.v_addr + offset);

	return VD_REV(*v_addr);
}


void vd_acs_interrupt(uint32_t offset, uint32_t bit)
{
	uint32_t *reg;

	reg = (uint32_t *)(vd_s_acs.mbox_addr + offset);

	*reg = (1<<bit);

	return;
}


/*void vd_acs_tas_get(void)
{
	volatile uint32_t *tas;
	tas = (uint32_t *)(vd_s_acs.mbox_addr + MBOX_MBOX_TAS00_OFFS);
	do {
		; // Nothing to do.
	} while (*tas != 0);
	return;
}
void vd_acs_tas_release(void)
{
	uint32_t *tas;
	tas = (uint32_t *)(vd_s_acs.mbox_addr + MBOX_MBOX_TAS00_OFFS);
	*tas = 0;
	return;
}
*/
