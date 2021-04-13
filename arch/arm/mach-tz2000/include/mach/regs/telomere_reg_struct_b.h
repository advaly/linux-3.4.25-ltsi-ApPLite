/*
 * arch/arm/mach-tz2000/include/mach/regs/telomere_reg_struct_b.h
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

#ifndef _TELOMERE_REG_STRUCT_B_H
#define _TELOMERE_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // NCM_MODE Register
struct TELOMERE_NCM_MODE {
	unsigned int reserved:30;		// [31:2]
	unsigned int MODE:2;		// [1:0]
};
 // NCM_STAT Register
struct TELOMERE_NCM_STAT {
	unsigned int reserved:29;		// [31:3]
	unsigned int STAT:3;		// [2:0]
};
 // NANDC_SETTING Register
struct TELOMERE_NANDC_SETTING {
	unsigned int reserved:12;		// [31:20]
	unsigned int STORAGE_SIZE:4;		// [19:16]
	unsigned int MEM_SIZE:4;		// [15:12]
	unsigned int reserved2:10;		// [11:2]
	unsigned int CACHE_READY:1;		// [1]
	unsigned int READY:1;		// [0]
};
 // NANDC_STAT Register
struct TELOMERE_NANDC_STAT {
	unsigned int VALUE:32;		// [31:0]
};
 // INTM_STAT Register
struct TELOMERE_INTM_STAT {
	unsigned int reserved:28;		// [31:4]
	unsigned int CACHE_ACCESS_ERROR:1;		// [3]
	unsigned int AXI_ERROR:1;		// [2]
	unsigned int MAILBOX:1;		// [1]
	unsigned int CACHEOP:1;		// [0]
};
 // INTM_MSKEDSTAT Register
struct TELOMERE_INTM_MSKEDSTAT {
	unsigned int reserved:28;		// [31:4]
	unsigned int CACHE_ACCESS_ERROR:1;		// [3]
	unsigned int AXI_ERROR:1;		// [2]
	unsigned int MAILBOX:1;		// [1]
	unsigned int CACHEOP:1;		// [0]
};
 // INTM_CLR Register
struct TELOMERE_INTM_CLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int CACHE_ACCESS_ERROR:1;		// [3]
	unsigned int AXI_ERROR:1;		// [2]
	unsigned int reserved2:1;		// [1]
	unsigned int CACHEOP:1;		// [0]
};
 // INTM_MASK Register
struct TELOMERE_INTM_MASK {
	unsigned int reserved:28;		// [31:4]
	unsigned int CACHE_ACCESS_ERROR:1;		// [3]
	unsigned int AXI_ERROR:1;		// [2]
	unsigned int MAILBOX:1;		// [1]
	unsigned int CACHEOP:1;		// [0]
};
 // CCTRL_MFADDR Register
struct TELOMERE_CCTRL_MFADDR {
	unsigned int ADDR:20;		// [31:12]
	unsigned int reserved:12;		// [11:0]
};
 // CCTRL_MFSIZE Register
struct TELOMERE_CCTRL_MFSIZE {
	unsigned int FLUSH_SIZE:20;		// [31:12]
	unsigned int reserved:9;		// [11:3]
	unsigned int COMMAND:3;		// [2:0]
};
 // GPR_0 Register
struct TELOMERE_GPR_0 {
	unsigned int VALUE:32;		// [31:0]
};
 // GPR_1 Register
struct TELOMERE_GPR_1 {
	unsigned int VALUE:32;		// [31:0]
};
 // GPR_2 Register
struct TELOMERE_GPR_2 {
	unsigned int VALUE:32;		// [31:0]
};
 // GPR_3 Register
struct TELOMERE_GPR_3 {
	unsigned int VALUE:32;		// [31:0]
};
 // BINSEMA_0 Register
struct TELOMERE_BINSEMA_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SEMAPHORE:1;		// [0]
};
 // BINSEMA_1 Register
struct TELOMERE_BINSEMA_1 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SEMAPHORE:1;		// [0]
};
 // BINSEMA_2 Register
struct TELOMERE_BINSEMA_2 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SEMAPHORE:1;		// [0]
};
 // BINSEMA_3 Register
struct TELOMERE_BINSEMA_3 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SEMAPHORE:1;		// [0]
};
 // MAILBOX_M2N Register
struct TELOMERE_MAILBOX_M2N {
	unsigned int VALUE:32;		// [31:0]
};
 // MAILBOX_M2NC Register
struct TELOMERE_MAILBOX_M2NC {
	unsigned int VALUE:32;		// [31:0]
};
 // MAILBOX_N2M Register
struct TELOMERE_MAILBOX_N2M {
	unsigned int VALUE:32;		// [31:0]
};
 // MAILBOX_N2MC Register
struct TELOMERE_MAILBOX_N2MC {
	unsigned int VALUE:32;		// [31:0]
};
 // BINSEMA_REF_0 Register
struct TELOMERE_BINSEMA_REF_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SEMAPHORE:1;		// [0]
};
 // BINSEMA_REF_1 Register
struct TELOMERE_BINSEMA_REF_1 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SEMAPHORE:1;		// [0]
};
 // BINSEMA_REF_2 Register
struct TELOMERE_BINSEMA_REF_2 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SEMAPHORE:1;		// [0]
};
 // BINSEMA_REF_3 Register
struct TELOMERE_BINSEMA_REF_3 {
	unsigned int reserved:31;		// [31:1]
	unsigned int SEMAPHORE:1;		// [0]
};
 // INTN_STAT Register
struct TELOMERE_INTN_STAT {
	unsigned int reserved:29;		// [31:3]
	unsigned int MAILBOX:1;		// [2]
	unsigned int WRITEBACK:1;		// [1]
	unsigned int REFILL:1;		// [0]
};
 // INTN_MSKEDSTAT Register
struct TELOMERE_INTN_MSKEDSTAT {
	unsigned int reserved:29;		// [31:3]
	unsigned int MAILBOX:1;		// [2]
	unsigned int WRITEBACK:1;		// [1]
	unsigned int REFILL:1;		// [0]
};
 // INTN_MASK Register
struct TELOMERE_INTN_MASK {
	unsigned int reserved:29;		// [31:3]
	unsigned int MAILBOX:1;		// [2]
	unsigned int WRITEBACK:1;		// [1]
	unsigned int REFILL:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TELOMERE_REG_STRUCT_B_H */
