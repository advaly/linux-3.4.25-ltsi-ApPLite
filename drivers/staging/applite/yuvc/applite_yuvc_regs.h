/*
 * linux/drivers/staging/applite/applite_yuvc_regs.h
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

#if !defined(__YUVC_DRIVER_REGS_H__)
#define __YUVC_DRIVER_REGS_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*===================================
include Files
===================================*/
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>


/*===================================
Types and structures   defined
===================================*/

/* DEFINITION REGISTERS VALUES : YUVC */
#define YUVC_REG(reg)			(YUVC_YUVC_##reg##_OFFS)
#define YUVC_R_MASK(reg)		(YUVC_YUVC_##reg##_MASK)
#define YUVC_R_SHIFT(reg)		(YUVC_YUVC_##reg##_SHIFT)
#define YUVC_VAL(v, shift)		((__u32)v << YUVC_R_SHIFT(shift))

/* YUVC_START */	/* address offset = 0x0000 */
#define YUVC_START_ON					YUVC_VAL(1, START_YUVC_START)

/* YUVC_RESET */	/* address offset = 0x0004 */
#define YUVC_RESET_ON					YUVC_VAL(1, RESET_YUVC_RESET)

/* YUVC_MODE */		/* address offset = 0x0008 */
#define YUVC_CF_RGBLIMIT_ON				YUVC_VAL(1, MODE_CF_RGBLIMIT)

/* YUVC_STATUS */	/* address offset = 0x0E00 */
#define YUVC_STATUS_ERROR_INBAND		YUVC_VAL(1, STATUS_MB_ERROR_INBAND)
#define YUVC_STATUS_ERROR_REGION		YUVC_VAL(1, STATUS_MB_ERROR_REGION)
#define YUVC_STATUS_MB_ERROR_ALL	\
		(YUVC_STATUS_ERROR_INBAND | YUVC_STATUS_ERROR_REGION)

/* YUVC_INT_MASK */		/* address offset = 0x0120 */
#define YUVC_INT_MASK_ABORT_G00			YUVC_VAL(1, INT_MASK_CF_ABORT_MASK_G00)
#define YUVC_INT_MASK_MB_ERR			YUVC_VAL(1, INT_MASK_CF_MB_ERR_MASK)
#define YUVC_INT_MASK_INT_G00			YUVC_VAL(1, INT_MASK_CF_INT_MASK_G00)
#define YUVC_INT_MASK_ALL			\
		(YUVC_INT_MASK_ABORT_G00 | YUVC_INT_MASK_MB_ERR | YUVC_INT_MASK_INT_G00)

/* YUVC_W_ENABLE */	/* address offset = 0x0134 */
#define YUVC_W_ENABLE_CF_ENABLE_W01		YUVC_VAL(1, W_ENABLE_CF_ENABLE_W01)
#define YUVC_W_ENABLE_CF_ENABLE_W00		YUVC_VAL(1, W_ENABLE_CF_ENABLE_W00)
#define YUVC_W_ENABLE_CF_ENABLE_ALL	\
		(YUVC_W_ENABLE_CF_ENABLE_W01 | YUVC_W_ENABLE_CF_ENABLE_W00)

/* YUVC_INT */		/* address offset = 0x0E04 */
#define YUVC_INT_ABORT_G00				YUVC_VAL(1, INT_ABORT_G00)
#define YUVC_INT_MB_ERR					YUVC_VAL(1, INT_MB_ERR)
#define YUVC_INT_INT_G00				YUVC_VAL(1, INT_INT_G00)
#define YUVC_INT_ALL				\
		(YUVC_INT_ABORT_G00 | YUVC_INT_MB_ERR | YUVC_INT_INT_G00)

/* YUVC_W_STOP */	/* address offset = 0x0E14 */
#define YUVC_W_STOP_ABORT_W00			YUVC_VAL(1, W_STOP_ABORT_W00)
#define YUVC_W_STOP_ABORT_W01			YUVC_VAL(1, W_STOP_ABORT_W01)
#define YUVC_W_STOP_ALL				\
		(YUVC_W_STOP_ABORT_W00 | YUVC_W_STOP_ABORT_W01)

/* YUVC input FIFO */
#define YUVC_FIFO_SIZE						(0x00000200)	/* 512 byte */
#define YUVC_FIFO_Y0_ADDR					(0x0F080000)
#define YUVC_FIFO_Y1_ADDR					(0x0F080200)
#define YUVC_FIFO_C0_ADDR					(0x0F080400)
#define YUVC_FIFO_C1_ADDR					(0x0F080600)
#define YUVC_FIFO_C2_ADDR					(0x0F080800)
#define YUVC_FIFO_V0_ADDR					(0x0F080A00)
#define YUVC_FIFO_V1_ADDR					(0x0F080C00)
#define YUVC_FIFO_V2_ADDR					(0x0F080E00)

enum yuvc_fifo_id {
	YUVC_FIFO_Y0 = 0,
	YUVC_FIFO_Y1,
	YUVC_FIFO_C0,
	YUVC_FIFO_C1,
	YUVC_FIFO_C2,
	YUVC_FIFO_V0,
	YUVC_FIFO_V1,
	YUVC_FIFO_V2
};

#define YUVC_FIFO_DMY_VAL			(0xffffffff)

/* DEFINITION REGISTERS VALUES : PMU */
#define PMU_REG(reg)			(PMU_##reg##_OFS)
#define PMU_R_SHIFT(reg)		(PMU_##reg##_SHIFT)
#define PMU_VAL(v, shift)		((__u32)v << PMU_R_SHIFT(shift))

#define PMU_CG_ON_YUVC_RUN		\
	PMU_VAL(0, CLOCKGATINGON_YUVCSS_0_CG_WCLKDIV2_YUVC)
#define PMU_CG_ON_YUVC_STOP		\
	PMU_VAL(1, CLOCKGATINGON_YUVCSS_0_CG_WCLKDIV2_YUVC)
#define PMU_CG_OFF_YUVC_RUN		\
	PMU_VAL(1, CLOCKGATINGOFF_YUVCSS_0_CG_WCLKDIV2_YUVC)
#define PMU_CG_OFF_YUVC_STOP		\
	PMU_VAL(0, CLOCKGATINGOFF_YUVCSS_0_CG_WCLKDIV2_YUVC)
#define PMU_SR_ON_YUVC_ASSERT		\
	PMU_VAL(1, SOFTRESETON_YUVCSS_0_SRST_WRSTDIV2_YUVC_N)
#define PMU_SR_ON_YUVC_DEASSERT	\
	PMU_VAL(0, SOFTRESETON_YUVCSS_0_SRST_WRSTDIV2_YUVC_N)
#define PMU_SR_OFF_YUVC_ASSERT		\
	PMU_VAL(0, SOFTRESETOFF_YUVCSS_0_SRST_WRSTDIV2_YUVC_N)
#define PMU_SR_OFF_YUVC_DEASSERT	\
	PMU_VAL(1, SOFTRESETOFF_YUVCSS_0_SRST_WRSTDIV2_YUVC_N)

/*===================================
Exported Variables
===================================*/



/*===================================
Exported Functions prototypes
===================================*/

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __YUVC_DRIVER_REGS_H__ */

