/*
 * drivers/staging/applite/veu/ve_access.c
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
#include "ve_trace.h"

static ve_virtual_t acs_fw_base;
static ve_virtual_t acs_comm_base;
static struct ve_accessor acs_accessor;

/* set fw are base address */
void acs_set_fw_base(ve_virtual_t fw_base)
{
	acs_fw_base = fw_base;
}

/* get fw are base address */
ve_virtual_t acs_get_fw_base(void)
{
	return acs_fw_base;
}

/* set communication are base address */
void acs_set_comm_base(ve_virtual_t comm_base)
{
	acs_comm_base = comm_base;
}

/* get communication are base address */
ve_virtual_t acs_get_comm_base(void)
{
	return acs_comm_base;
}

/* read 16bit */
void acs_read16(uint32_t addr, uint16_t *val)
{
	*val = *(uint16_t *)addr;
}

/* write 16bit */
void acs_write16(uint32_t addr, uint16_t val)
{
	*(uint16_t *)addr = val;
}

/* read 32bit */
void acs_read32(uint32_t addr, uint32_t *val)
{
	*val = *(uint32_t *)addr;
}

/* write 32bit */
void acs_write32(uint32_t addr, uint32_t val)
{
	*(uint32_t *)addr = val;
}

/* read 32bit (byte swap) */
void acs_rev_read32(uint32_t addr, uint32_t *val)
{
	*val = VE_REV(*(uint32_t *)addr);
}

/* write 32bit (byte swap) */
void acs_rev_write32(uint32_t addr, uint32_t val)
{
	*(uint32_t *)addr = VE_REV(val);
}

/* set accessor */
void acs_set_accessor(struct ve_accessor accessor)
{
	acs_accessor = accessor;
}

/* get accessor */
struct ve_accessor acs_get_accessor(void)
{
	return acs_accessor;
}

/* translate address from physical to vbus
 * physical -> vbus:
 * 1. address translation(physical -> vbus)
 * 2. byte swap(VE_REV)
 */
ve_vbus_t acs_trans_p2vbus_addr(ve_physical_t p_addr)
{
	ve_vbus_t vbus_addr;

	/* peripheral */
	if (ADDRMAP_PERI_SA <= p_addr && p_addr < ADDRMAP_PERI_EA)
		vbus_addr = p_addr + 0x78000000UL;
	/* dram 2GiB - 3GiB */
	else if (ADDRMAP_DRAM_SA <= p_addr && p_addr < ADDRMAP_DRAM_HALF_EA)
		vbus_addr = p_addr - 0x40000000UL;
	else
		vbus_addr = p_addr;

	return VE_REV(vbus_addr);
}

/* translate address from vbus to physical
 * vbus -> physical:
 * 1. byte swap(VE_REV)
 * 2. address translation(vbus -> physical)
 */
ve_physical_t acs_trans_vbus2p_addr(ve_vbus_t vbus_addr)
{
	ve_physical_t p_addr;

	vbus_addr = VE_REV(vbus_addr);
	if (VADDRMAP_PERI_SA <= vbus_addr && vbus_addr < VADDRMAP_PERI_EA) {
		/* peripheral */
		p_addr = vbus_addr - 0x78000000UL;
	} else if (VADDRMAP_DRAM_HALF_SA <= vbus_addr
			&& vbus_addr < VADDRMAP_DRAM_HALF_EA) {
		/* dram 1GiB - 2GiB */
		p_addr = vbus_addr + 0x40000000UL;
	} else {
		p_addr = vbus_addr;
	}

	return p_addr;
}

/* translate address from physical to virtual */
ve_virtual_t acs_trans_p2v_addr(struct ve_address addr, ve_physical_t p_addr)
{
	uint32_t diff;
	ve_virtual_t retval;

	if (addr.p_addr > addr.v_addr) {
		diff = addr.p_addr - addr.v_addr;
		retval = p_addr - diff;
	} else {
		diff = addr.v_addr - addr.p_addr;
		retval = p_addr + diff;
	}

	return retval;
}

/* translate address from virtual to physical */
ve_physical_t acs_trans_v2p_addr(struct ve_address addr, ve_virtual_t v_addr)
{
	uint32_t diff;
	ve_physical_t retval;

	if (addr.p_addr > addr.v_addr) {
		diff = addr.p_addr - addr.v_addr;
		retval = v_addr + diff;
	} else {
		diff = addr.v_addr - addr.p_addr;
		retval = v_addr - diff;
	}

	return retval;
}

/* translate address from vbus to virtual */
ve_virtual_t acs_trans_vbus2v_addr(struct ve_address addr, ve_vbus_t vbus_addr)
{
	ve_physical_t p_addr;
	p_addr = acs_trans_vbus2p_addr(vbus_addr);

	return acs_trans_p2v_addr(addr, p_addr);
}

/* translate address from virtual to vbus */
ve_vbus_t acs_trans_v2vbus_addr(struct ve_address addr, ve_virtual_t v_addr)
{
	ve_physical_t p_addr;

	p_addr = acs_trans_v2p_addr(addr, v_addr);

	return acs_trans_p2vbus_addr(p_addr);
}

/* check align */
enum ve_result acs_chk_align(uint32_t addr, uint32_t align_byte)
{
	if ((addr & (align_byte - 1)) != 0x0)
		return VE_ERROR_PARAMETERS;

	return VE_OK;
}

/* check crossing any 1GiB boundaries */
enum ve_result acs_chk_crossing_memory(uint32_t addr, uint32_t size)
{
	uint64_t tmp;
	uint64_t end_addr;

	tmp = (uint64_t)addr & 0xc0000000ULL;
	end_addr = (uint64_t)addr + (uint64_t)size - 1ULL;

	/* check 4GiB */
	if (end_addr >= 0x100000000ULL) {
		return VE_ERROR_PARAMETERS;
	} else {
		/* check 1GiB boundaries */
		tmp += 0x40000000ULL;
		if (end_addr >= tmp)
			return VE_ERROR_PARAMETERS;
	}

	return VE_OK;
}

/* check VE_FW_AREA and VE_COMM_AREA */
enum ve_result acs_chk_start_up_mem(struct ve_accessor *accessors,
						struct ve_address *fw_addr,
						struct ve_buf *comm_addr)
{
	enum ve_result ret = VE_OK;

	/* check range */
	/* physical */
	ret = acs_chk_data_in_peri_range(accessors->to_vip4.set.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->to_vip4.clear.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->to_vip4.mask.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->to_vip4.selector.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->from_vip4.set.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->from_vip4.clear.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->from_vip4.mask.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->from_vip4.selector.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->to_vip4_nmi.set.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->to_vip4_nmi.clear.p_addr);
	ret |= acs_chk_data_in_peri_range(accessors->to_vip4_nmi.mask.p_addr);
	ret |= acs_chk_data_in_peri_range(
					accessors->to_vip4_nmi.selector.p_addr);
	ret |= acs_chk_data_in_dram_range(fw_addr->p_addr);
	ret |= acs_chk_data_in_dram_range(comm_addr->addr.p_addr);
	/* virtual */
	ret |= acs_chk_addr_zero(accessors->to_vip4.set.v_addr);
	ret |= acs_chk_addr_zero(accessors->to_vip4.clear.v_addr);
	ret |= acs_chk_addr_zero(accessors->to_vip4.mask.v_addr);
	ret |= acs_chk_addr_zero(accessors->to_vip4.selector.v_addr);
	ret |= acs_chk_addr_zero(accessors->from_vip4.set.v_addr);
	ret |= acs_chk_addr_zero(accessors->from_vip4.clear.v_addr);
	ret |= acs_chk_addr_zero(accessors->from_vip4.mask.v_addr);
	ret |= acs_chk_addr_zero(accessors->from_vip4.selector.v_addr);
	ret |= acs_chk_addr_zero(accessors->to_vip4_nmi.set.v_addr);
	ret |= acs_chk_addr_zero(accessors->to_vip4_nmi.clear.v_addr);
	ret |= acs_chk_addr_zero(accessors->to_vip4_nmi.mask.v_addr);
	ret |= acs_chk_addr_zero(accessors->to_vip4_nmi.selector.v_addr);
	ret |= acs_chk_addr_zero(accessors->veu0_addrconf0);
	ret |= acs_chk_addr_zero(accessors->reset_on_vcodec);
	ret |= acs_chk_addr_zero(fw_addr->v_addr);
	ret |= acs_chk_addr_zero(comm_addr->addr.v_addr);
	if (ret != VE_OK)
		return ret;

	/* check align */
	/* physical */
	ret |= acs_chk_align(accessors->to_vip4.set.p_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4.clear.p_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4.mask.p_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4.selector.p_addr, 0x4);
	ret |= acs_chk_align(accessors->from_vip4.set.p_addr, 0x4);
	ret |= acs_chk_align(accessors->from_vip4.clear.p_addr, 0x4);
	ret |= acs_chk_align(accessors->from_vip4.mask.p_addr, 0x4);
	ret |= acs_chk_align(accessors->from_vip4.selector.p_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4_nmi.set.p_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4_nmi.clear.p_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4_nmi.mask.p_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4_nmi.selector.p_addr, 0x4);
	ret |= acs_chk_align(fw_addr->p_addr, 0x01000000UL);  /* 16MB */
	ret |= acs_chk_align(comm_addr->addr.p_addr, 0x8);
	/* virtual */
	ret |= acs_chk_align(accessors->to_vip4.set.v_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4.clear.v_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4.mask.v_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4.selector.v_addr, 0x4);
	ret |= acs_chk_align(accessors->from_vip4.set.v_addr, 0x4);
	ret |= acs_chk_align(accessors->from_vip4.clear.v_addr, 0x4);
	ret |= acs_chk_align(accessors->from_vip4.mask.v_addr, 0x4);
	ret |= acs_chk_align(accessors->from_vip4.selector.v_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4_nmi.set.v_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4_nmi.clear.v_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4_nmi.mask.v_addr, 0x4);
	ret |= acs_chk_align(accessors->to_vip4_nmi.selector.v_addr, 0x4);
	ret |= acs_chk_align(accessors->veu0_addrconf0, 0x4);
	ret |= acs_chk_align(accessors->reset_on_vcodec, 0x4);
	ret |= acs_chk_align(comm_addr->addr.v_addr, 0x8);

	/* check crossing memory */
	ret |= acs_chk_crossing_memory(comm_addr->addr.p_addr, comm_addr->size);

	/* check communication area size */
	if (comm_addr->size < COMM_AREA_SIZE)
		ret |= VE_ERROR_PARAMETERS;

	return ret;
}

/* check address in DRAM range */
enum ve_result acs_chk_data_in_dram_range(ve_physical_t p_addr)
{
	enum ve_result ret = VE_OK;

	if (p_addr < ADDRMAP_DRAM_SA)
		ret = VE_ERROR_PARAMETERS;

	return ret;
}

/* check address in peripheral range */
enum ve_result acs_chk_data_in_peri_range(ve_physical_t p_addr)
{
	enum ve_result ret = VE_OK;

	if (p_addr < ADDRMAP_PERI_SA || ADDRMAP_PERI_EA <= p_addr)
		ret = VE_ERROR_PARAMETERS;

	return ret;
}

/* check virtual address is zero */
enum ve_result acs_chk_addr_zero(uint32_t addr)
{
	enum ve_result ret = VE_OK;

	if (addr == 0x0)
		ret = VE_ERROR_PARAMETERS;

	return ret;
}

/* get command address */
uint32_t acs_get_cmd_addr(uint32_t pu_id)
{
	return COMM_AREA_CMD(pu_id);
}

/* get reset status */
uint32_t acs_get_reset_status(void)
{
	uint32_t val;

	val = *(uint32_t *)(acs_accessor.reset_on_vcodec);

	return val;
}

