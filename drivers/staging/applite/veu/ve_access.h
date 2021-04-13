/*
 * drivers/staging/applite/veu/ve_access.h
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

#ifndef __VE_ACCESS_H__
#define __VE_ACCESS_H__

#include "ve_api.h"

	#ifdef __KERNEL__
		#include <linux/swab.h>
		#define VE_REV(val)	swab32(val)
	#else
		#define VE_REV(val)	__builtin_bswap32(val)
	#endif

/* reset register bit */
#define VE_RST_ON		((uint32_t)0x00010000)

/* VIP4 core num */
#define VIP4_PU_NUM		1
#define VIP4_PU_MAX_VAL		(VIP4_PU_NUM - 1)

/* fw area */
/* area */
#define VIP4_FW_BASE		(acs_get_fw_base())
#define VIP4_FW_VERSION		(VIP4_FW_BASE + (uint32_t)0x00000100)
#define VIP4_FW_BUILD		(VIP4_FW_BASE + (uint32_t)0x00000104)
#define VIP4_FW_COMM_BASE	(VIP4_FW_BASE + (uint32_t)0x00000108)
#define VIP4_FW_INT_SET_HOST	(VIP4_FW_BASE + (uint32_t)0x0000010c)
#define VIP4_FW_INT_CLEAR_VIP4	(VIP4_FW_BASE + (uint32_t)0x00000110)
#define VIP4_FW_COMMAND		(VIP4_FW_BASE + (uint32_t)0x00000114)
#define VIP4_FW_RESPONSE	(VIP4_FW_BASE + (uint32_t)0x00000118)
#define VIP4_FW_RESPONSE_KILL	(VIP4_FW_BASE + (uint32_t)0x0000011c)
#define VIP4_FW_RESET_OFF	(VIP4_FW_BASE + (uint32_t)0x00000120)
#define VIP4_FW_TRACE_ENABLE	(VIP4_FW_BASE + (uint32_t)0x00000124)

/* communication area */
/* size */
#define COMM_AREA_SIZE		((uint32_t)0x00000400)
/* offset */
#define CMN_BASE_OFS		((uint32_t)0x00000000)
#define CMD_BASE_OFS		((uint32_t)0x00000100)
#define RESP_BASE_OFS		((uint32_t)0x00000200)
#define RESP_KILL_BASE_OFS	((uint32_t)0x00000300)
#define TASK_API_OFS		((uint32_t)0x00000000)
#define TASK_FW_OFS		((uint32_t)0x00000004)
#define RESP_KILL_ARG_OFS	((uint32_t)0x00000008)
#define PUOFS(x)		((uint32_t)(0x400 * (x)))
/* area */
#define COMM_AREA_BASE		(acs_get_comm_base())
/* common */
#define COMM_AREA_CMN		(COMM_AREA_BASE + CMN_BASE_OFS)
#define CMN_VE_LOG_SEQ		(COMM_AREA_CMN + (uint32_t)0x0000)
#define CMN_VE_LOG_BEGIN	(COMM_AREA_CMN + (uint32_t)0x0004)
#define CMN_VE_LOG_END		(COMM_AREA_CMN + (uint32_t)0x0008)
#define CMN_VE_LOG_CUR		(COMM_AREA_CMN + (uint32_t)0x000C)
#define CMN_FW_CTX_SZ		(COMM_AREA_CMN + (uint32_t)0x0020)
#define CMN_FW_STATE		(COMM_AREA_CMN + (uint32_t)0x0024)
#define CMN_FW_LOG_BEGIN	(COMM_AREA_CMN + (uint32_t)0x0028)
#define CMN_FW_LOG_END		(COMM_AREA_CMN + (uint32_t)0x002c)
#define CMN_FW_LOG_CUR		(COMM_AREA_CMN + (uint32_t)0x0030)
/* command */
#define COMM_AREA_CMD(x)	(COMM_AREA_BASE + CMD_BASE_OFS + PUOFS(x))
/* response(general) */
#define COMM_AREA_RESP(x)	(COMM_AREA_BASE + RESP_BASE_OFS + PUOFS(x))
/* response(kill cmd) */
#define COMM_AREA_RESP_KILL(x)	(COMM_AREA_BASE + RESP_KILL_BASE_OFS + PUOFS(x))

/* address map(physical) */
/* size */
#define PERI_SZ			((uint32_t)0x000f0000)	/* 960KiB */
#define DRAM_SZ			((uint32_t)0x80000000)	/* 2GiB */
#define DRAM_HALF_SZ		(DRAM_SZ >> 1)		/* 1GiB */
/* host area */
#define ADDRMAP_PERI_SA		((uint32_t)0x08000000)
#define ADDRMAP_PERI_EA		((uint32_t)(ADDRMAP_PERI_SA + PERI_SZ))
#define ADDRMAP_DRAM_SA		((uint32_t)0x80000000)
#define ADDRMAP_DRAM_HALF_EA	((uint32_t)(ADDRMAP_DRAM_SA + DRAM_HALF_SZ))
/* vbus area */
#define VADDRMAP_PERI_SA	((uint32_t)0x80000000)
#define VADDRMAP_PERI_EA	((uint32_t)(VADDRMAP_PERI_SA + PERI_SZ))
#define VADDRMAP_DRAM_HALF_SA	((uint32_t)0x40000000)
#define VADDRMAP_DRAM_HALF_EA	((uint32_t) \
					(VADDRMAP_DRAM_HALF_SA + DRAM_HALF_SZ))

void acs_set_fw_base(ve_virtual_t fw_base);
ve_virtual_t acs_get_fw_base(void);
void acs_set_comm_base(ve_virtual_t comm_base);
ve_virtual_t acs_get_comm_base(void);
void acs_read16(uint32_t addr, uint16_t *val);
void acs_write16(uint32_t addr, uint16_t val);
void acs_read32(uint32_t addr, uint32_t *val);
void acs_write32(uint32_t addr, uint32_t val);
void acs_rev_read32(uint32_t addr, uint32_t *val);
void acs_rev_write32(uint32_t addr, uint32_t val);
void acs_set_accessor(struct ve_accessor accessor);
struct ve_accessor acs_get_accessor(void);
ve_vbus_t acs_trans_p2vbus_addr(ve_physical_t p_addr);
ve_physical_t acs_trans_vbus2p_addr(ve_vbus_t vbus_addr);
ve_virtual_t acs_trans_p2v_addr(struct ve_address addr, ve_physical_t p_addr);
ve_physical_t acs_trans_v2p_addr(struct ve_address addr, ve_virtual_t v_addr);
ve_virtual_t acs_trans_vbus2v_addr(struct ve_address addr, ve_vbus_t vbus_addr);
ve_vbus_t acs_trans_v2vbus_addr(struct ve_address addr, ve_virtual_t v_addr);
enum ve_result acs_chk_align(uint32_t addr, uint32_t align_byte);
enum ve_result acs_chk_crossing_memory(uint32_t addr, uint32_t size);
enum ve_result acs_chk_start_up_mem(struct ve_accessor *accessors,
						struct ve_address *fw_addr,
						struct ve_buf *comm_addr);
enum ve_result acs_chk_data_in_dram_range(ve_physical_t p_addr);
enum ve_result acs_chk_data_in_peri_range(ve_physical_t p_addr);
enum ve_result acs_chk_addr_zero(uint32_t addr);
uint32_t acs_get_cmd_addr(uint32_t pu_id);
uint32_t acs_get_reset_status(void);

#endif /* __VE_ACCESS_H__ */

