/*
 * linux/drivers/staging/applite/syscon/applite_syscon_regs.h
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2012
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

#if !defined(__SYSCON_DRIVER_REGS_H__)
#define __SYSCON_DRIVER_REGS_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*===================================
include Files
===================================*/
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>

#if defined(CONFIG_ARCH_TZ3000)
#include <mach/regs/scomm_offs_def.h>
#else
#define SCOMM_TAS_SECURE_OFFS	(0x10)
#define SCOMM_INT_SECURE_OFFS	(0x14)
#endif
#include <mach/regs/mbox_offs_def.h>
#include <mach/regs/mbox_reg_def.h>
#include <mach/regs/cpu_memmap_def.h>

/*===================================
Types and structures   defined
===================================*/

/* DEFINITION REGISTERS VALUES : SCOMM */
#define SCOMM_REG(reg)			(SCOMM_##reg##_OFFS)
#define SCOMM_R_MASK(reg)		(SCOMM_##reg##_MASK)
#define SCOMM_R_SHIFT(reg)		(SCOMM_##reg##_SHIFT)
#define SCOMM_VAL(v, shift)		((__u32)v << shift)

/* for FW Download */
#define SCOMM_DRV_ABI_OFFS		(0x00000500)
	#define SCOMM_SPEC		(1)
#define SCOMM_DBG_LV_OFFS		(0x00000504)
#define SCOMM_DRAM_WORK_OFFS		(0x00000508)
#define SCOMM_DRAM_DEBUG_OFFS		(0x0000050C)
#define SCOMM_RESERVED_OFFS		(0x00000510)
#define SCOMM_RESERVED_SIZE		(0x000000F0)
#define SCOMM_RESULT_OFFS		(0x00000580)
	#define SCOMM_SUCCESS		(0)

/* for ioctl */
#define SCOMM_REQ_HDR_SIZE		(0x20)
#define SCOMM_REQ_DAT_SIZE		(0x60)

#define SCOMM_REQ_SLOT_OFFS		(0x00000500)
	#define SCOMM_SLOT_L		(1)
	#define SCOMM_SLOT_S		(2)
	#define SCOMM_SLOT_C		(3)
#define SCOMM_REQ_RESULT_OFFS		(0x00000504)
	#define SCOMM_RESULT_OK		(0)
#define SCOMM_REQ_REQID_OFFS		(0x00000508)
#define SCOMM_REQ_DRVDATA_OFFS		(0x0000050C)
#define SCOMM_REQ_RESERVED0_OFFS	(0x00000510)
#define SCOMM_REQ_RESERVED1_OFFS	(0x00000514)
#define SCOMM_REQ_RESERVED2_OFFS	(0x00000518)
#define SCOMM_REQ_RESERVED3_OFFS	(0x0000051C)
#define SCOMM_REQ_REQUEST_OFFS		(0x00000520)

/* for hw_random */
#define SCOMM_REQ_RNG_CMDID_OFFS	(0x00000520)
	#define SCOMM_RNG_CMDID		(0x00000002)

/* for CryptoDev */
#define SCOMM_REQ_C_REQID_OFFS		(0x00000520)
#define SCOMM_REQ_C_RET_OFFS		(0x00000524)
#define SCOMM_REQ_C_ERRSUB_OFFS		(0x00000528)
	#define SCOMM_ERRSUB_PERM	(1)
	#define SCOMM_ERRSUB_QUENO	(2)
	#define SCOMM_ERRSUB_ALIGN	(3)
	#define SCOMM_ERRSUB_TOOLARGE	(4)
	#define SCOMM_ERRSUB_ALGO	(5)
	#define SCOMM_ERRSUB_KEYBITS	(6)
	#define SCOMM_ERRSUB_KEYNO	(7)
	#define SCOMM_ERRSUB_IMPL	(8)
	#define SCOMM_ERRSUB_BLOCKLEN	(9)
	#define SCOMM_ERRSUB_BUSY	(10)
	#define SCOMM_ERRSUB_MEMORY	(11)
#define SCOMM_REQ_C_RESERVED1_OFFS	(0x0000052C)
#define SCOMM_REQ_C_DST_OFFS		(0x00000530)
#define SCOMM_REQ_C_SRC_OFFS		(0x00000534)
#define SCOMM_REQ_C_LEN_OFFS		(0x00000538)
#define SCOMM_REQ_C_IV_OFFS		(0x0000053C)
#define SCOMM_REQ_C_ALGO_OFFS		(0x00000540)
	#define SCOMM_ALGO_AES_ECB	(0x0101)
	#define SCOMM_ALGO_AES_CBC	(0x0102)
	#define SCOMM_ALGO_AES_CTR	(0x0105)
	#define SCOMM_ALGO_SHA1		(0x0201)
	#define SCOMM_ALGO_SHA2_224	(0x0202)
	#define SCOMM_ALGO_SHA2_256	(0x0203)
	#define SCOMM_ALGO_CMAC_AES	(0x0501)
#define SCOMM_REQ_C_MODE_OFFS		(0x00000544)
	#define SCOMM_MODE_ENC		(1 << 0)
	#define SCOMM_MODE_DEC		(0 << 0)
	#define SCOMM_MODE_HEAD		(1 << 4)
	#define SCOMM_MODE_TAIL		(1 << 5)
#define SCOMM_REQ_C_KEYBITS_OFFS	(0x00000545)
	#define SCOMM_KEYBITS_128	(2)
	#define SCOMM_KEYBITS_192	(3)
	#define SCOMM_KEYBITS_256	(4)
#define SCOMM_REQ_C_KEYNO_OFFS		(0x00000546)
#define SCOMM_REQ_C_QUENO_OFFS		(0x00000547)
#define SCOMM_REQ_C_RESERVED2_OFFS	(0x00000548)
#define SCOMM_REQ_C_KEY_OFFS		(0x00000550)
#define SCOMM_REQ_C_RESERVED3_OFFS	(0x00000570)

#define SCOMM_RSP_SLOT_OFFS		(0x00000580)
#define SCOMM_RSP_RESULT_OFFS		(0x00000584)
#define SCOMM_RSP_REQID_OFFS		(0x00000588)
#define SCOMM_RSP_DRVDATA_OFFS		(0x0000058C)
#define SCOMM_RSP_RESPONSE_OFFS		(0x000005A0)

/* for hw_random */
#define SCOMM_RSP_RNG_DATA_OFFS		(0x000005B0)

#define SCOMM_FW_INFO_OFFS		(0x00000600)
#define SCOMM_STATUS_OFFS		(0x00000604)
	#define SCOMM_VER_MASK		SCOMM_VAL(1, 16)
	#define SCOMM_VER_2ND		SCOMM_VAL(0, 16)
	#define SCOMM_VER_3RD		SCOMM_VAL(1, 16)
	#define SCOMM_BUF_NOT_USE	SCOMM_VAL(0, 17)
	#define SCOMM_BUF_USE		SCOMM_VAL(1, 17)
#define SCOMM_COUNTER_OFFS		(0x00000610)
#define SCOMM_TIMER_OFFS		(0x00000618)
#define SCOMM_BOOT_DEVICE_OFFS		(0x00000624)
#if defined(CONFIG_ARCH_TZ3000)
	#define	SCOMM_BD_SPI		(0x00000002)
	#define SCOMM_BD_NAND_4		(0x00000004)
	#define SCOMM_BD_NAND_5		(0x00000005)
	#define SCOMM_BD_EMMC		(0x00000006)
	#define SCOMM_BD_SD		(0x00000007)
#else
	#define	SCOMM_BD_SPI		(0x00000001)
	#define SCOMM_BD_NAND		(0x00000002)
	#define SCOMM_BD_SD_0		(0x00000005)
	#define SCOMM_BD_EMMC_1		(0x00000006)
	#define SCOMM_BD_SD_1		(0x00000007)
#endif
#define SCOMM_MEMORY_SIZE_OFFS		(0x00000630)
#define SCOMM_MEMORY_TYPE_OFFS		(0x00000634)
#if defined(CONFIG_ARCH_TZ3000)
#else
	#define SCOMM_MT_DRAM		(0x00000001)
	#define SCOMM_MT_SRAM		(0x00010002)
	#define SCOMM_MT_NAND		(0x00020002)
	#define SCOMM_MT_SRAM_NAND	(0x00030002)
#endif
#define SCOMM_SYS_CONFIG0_OFFS		(0x00000638)
#define SCOMM_SYS_CONFIG1_OFFS		(0x0000063C)
	#define SCOMM_SUPPORT_CRYPTO	(0x00000001)
	#define SCOMM_SUPPORT_PM	(0x00000100)
#define SCOMM_PWMN_CONFIG0_OFFS		(0x00000670)
	#define SCOMM_WKUP_R_MASK	(0x0000FFFF)
	#define SCOMM_WKUP_GPIO_FALL	(0x00000101)
	#define SCOMM_WKUP_GPIO_RISE	(0x00000301)
	#define SCOMM_WKUP_TIMER	(0x00000002)
	#define SCOMM_WKUP_RTC		(0x00000004)
	#define SCOMM_WKUP_I2C		(0x00000008)
#define SCOMM_PWMN_CONFIG1_OFFS		(0x00000674)
#define SCOMM_PWMN_CONFIG2_OFFS		(0x00000678)
#define SCOMM_PWMN_CONFIG3_OFFS		(0x0000067C)


/* DEFINITION REGISTERS VALUES : MBOX */
#define MBOX_REG(reg)			(MBOX_INT_##reg##_OFFS)
#define MBOX_R_MASK(reg)		(MBOX_INT_##reg##_MASK)
#define MBOX_R_SHIFT(reg)		(MBOX_INT_##reg##_SHIFT)
#define MBOX_VAL(v, shift)		((__u32)v << shift)

/* INT_REG000_SET/INT_REG000_CLEAR/INT_REG000_MASK */

#define MBOX_FW_DL_REQ			MBOX_VAL(1, 0)
#define MBOX_BUF_FREE_REQ		MBOX_VAL(1, 1)
#define MBOX_DRV_INIT_NOTIFY		MBOX_VAL(1, 4)
#define MBOX_DRV_FIN_NOTIFY		MBOX_VAL(1, 5)

/* INT_REG002_SET/INT_REG002_CLEAR/INT_REG002_MASK */
#define MBOX_CMD_RSP_ACK_N		MBOX_VAL(1, 0)
#define MBOX_CMD_RSP_ACK_S		MBOX_VAL(1, 1)

/* INT_REG008_SET/INT_REG008_CLEAR/INT_REG008_MASK */
#define MBOX_FW_DL_RSP			MBOX_VAL(1, 0)
#define MBOX_BUF_FREE_RSP		MBOX_VAL(1, 1)
#define MBOX_008_INT_MASK		(MBOX_FW_DL_RSP | MBOX_BUF_FREE_RSP)

/* INT_REG010_SET/INT_REG010_CLEAR/INT_REG010_MASK */
#define MBOX_CMD_CMP_NOTIFY_N		MBOX_VAL(1, 0)
#define MBOX_CMD_CMP_NOTIFY_S		MBOX_VAL(1, 1)
#define MBOX_CMD_REQ_ERROR_N		MBOX_VAL(1, 2)
#define MBOX_CMD_REQ_ERROR_S		MBOX_VAL(1, 3)
#define MBOX_010_INT_MASK		(MBOX_CMD_CMP_NOTIFY_N | \
					 MBOX_CMD_CMP_NOTIFY_S | \
					 MBOX_CMD_REQ_ERROR_N | \
					 MBOX_CMD_REQ_ERROR_S)

/* INT_REG011_SET/INT_REG011_CLEAR/INT_REG011_MASK */
#define MBOX_CMD_CMP_C_Q0_N		MBOX_VAL(1, 0)
#define MBOX_CMD_CMP_C_Q1_N		MBOX_VAL(1, 1)
#define MBOX_CMD_CMP_C_Q2_N		MBOX_VAL(1, 2)
#define MBOX_CMD_CMP_C_Q3_N		MBOX_VAL(1, 3)
#define MBOX_CMD_CMP_C_Q0_S		MBOX_VAL(1, 4)
#define MBOX_CMD_CMP_C_Q1_S		MBOX_VAL(1, 5)
#define MBOX_CMD_CMP_C_Q2_S		MBOX_VAL(1, 6)
#define MBOX_CMD_CMP_C_Q3_S		MBOX_VAL(1, 7)
#define MBOX_011_INT_MASK		(MBOX_CMD_CMP_C_Q0_N | \
					 MBOX_CMD_CMP_C_Q1_N | \
					 MBOX_CMD_CMP_C_Q2_N | \
					 MBOX_CMD_CMP_C_Q3_N | \
					 MBOX_CMD_CMP_C_Q0_S | \
					 MBOX_CMD_CMP_C_Q1_S | \
					 MBOX_CMD_CMP_C_Q2_S | \
					 MBOX_CMD_CMP_C_Q3_S)


/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __SYSCON_DRIVER_REGS_H__ */

