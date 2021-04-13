/*
 * linux/drivers/staging/applite/irecog/filter/filter_define.h
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
#include <linux/applite/irecog/basic_type.h>
/*#include "basic_queue.h"*/

#ifndef FILTER_DEFINE_H
#define FILTER_DEFINE_H

#define FILTER_BINARY_SIZE   (0x3F0000)		   /**< 4MB-64KB */

#define FILTER_QUEUE_SIZE    (236/4)

#define FILTER_ENDFLAG_SIZE  (FILTER_NQUEUE*2)

#define FILTER_NUM           (2)

/* Filter SIMD Size */
#define FILTER_SIMD_NUM      (64)

/**
 * Macro Definitions for FILTER_FW_IMAGE in Offset Address(in Word)
 *
 *  index              Data
 *    0                Total Size
 *    1                Total Sequence Number
 *    2                Sequence 0 Offset Addr(0)
 *    3                Sequence 1 Offset Addr(1)
 *       ...................
 *    n-1              Sequence n-2 Offset Addr(n-2)
 *    n                Sequence n-1 Offset Addr(n-1)
 *------------------------------------------------
 * Addr(n-1)
 *    0                Number of Transaction
 *    1                Trans0 Main Memory Offset Addr
 *    2                Trans0 Size
 *    3                Trans0 HIF Addr
 *       ...................
 *  n*3+1           Trans(n-1) Main Memory Offset Addr
 *  n*3+2           Trans(n-1) Size
 *  n*3+3           Trans(n-1) HIF Addr
 */
#define FILTER_TOTAL_SIZE        (0)
#define FILTER_SEQUENCE_NUM      (1)
#define FILTER_SEQUENCE_OFFSET   (2)

/* Offset Index of A Sequence */
#define FILTER_TRANS_NUM         (0)
#define FILTER_PARAM_OFFSET_ADDR (1)
#define FILTER_PARAM_SIZE        (2)
#define FILTER_PARAM_HIF_ADDR    (3)

#define FILTER_TRANS_OFFSET      (1)
/*--------------------------------------*/
#define FILTER_TRNUM_MAX         (8)
#define FILTER_MAX_IN_CHANNEL    (4)
#define FILTER_MAX_OUT_CHANNEL   (4)
#define FILTER_MAX_FRAME         (0x10000UL)

#define FILTER_MAX_LINEOFFSET    (0x10000UL)

/* Interrupt Mask Setting */
#define FILTER_INTMASK_SEQ_FRAME 0x1a
#define FILTER_INTMASK_SEQ_PARA  0xe

#if 0				/* defined in filter_driver.h */
enum filter_hw_status_e {
	FILTER_HW_INIT_END = 1,
	FILTER_HW_NON_LAST_IMG_END = 2,
	FILTER_HW_LAST_IMG_END = 4,
	FILTER_HW_NON_LAST_PARAM_END = 8,
	FILTER_HW_LAST_PARAM_END = 16,
	FILTER_HW_CONFLICT = 64
};
typedef enum filter_hw_status_e FILTER_HW_STATUS;
#endif

/* Activate Bit Map */
#define FILTER0_ACTIVE (0x01)
#define FILTER1_ACTIVE (0x02)

/* Filter Parameter Nor Address & Size */

/*#define FILTER_ROM_BASE         (NOR_CACHE_BASE+0x03C00000) */
#endif /* FILTER_DEFINE_H */
