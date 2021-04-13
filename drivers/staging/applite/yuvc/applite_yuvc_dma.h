/*
 * linux/drivers/staging/applite/applite_yuvc_dma.h
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

#ifndef _APPLITE_DMA_H
#define _APPLITE_DMA_H

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#include "mach/regs/cpu_memmap_def.h"
#include "mach/regs/gdmac_offs_def.h"
#define CCR_PROTECT	0 /* secure */
#define SECURE_BIT	0 /* secure */
#else
#include "mach/regs/cpu_memmap_def.h"
#include "mach/regs/gdmac_offs_def.h"
#define CCR_PROTECT	2 /* non-secure */
#define SECURE_BIT	1 /* non-secure */
#endif

/*#define TEST_M2M	1*/
/*#define USE_DMA_IRQ	1*/
/*#define DMA_PROG_DUMP	1*/

/*===================================
Types and structures   defined
===================================*/

enum yuvc_dma_type {
	YUVC_DMA_YUY2,
	YUVC_DMA_NV12,
	YUVC_DMA_I420
};

enum yuvc_dma_fifo {
	YUVC_DMA_FIFO_Y = 0,
	YUVC_DMA_FIFO_C,
	YUVC_DMA_FIFO_V,

	YUVC_DMA_FIFO_MAX
};

/* source address num */
enum yuvc_dma_yuy2_src {
	YUVC_DMA_YUY2_SRC_YUV = 0
};

enum yuvc_dma_nv12_src {
	YUVC_DMA_NV12_SRC_Y = 0,
	YUVC_DMA_NV12_SRC_UV
};

enum yuvc_dma_i420_src {
	YUVC_DMA_I420_SRC_Y = 0,
	YUVC_DMA_I420_SRC_U,
	YUVC_DMA_I420_SRC_V
};

/* DMA ch */
enum yuvc_dma_yuy2_ch {
	YUVC_DMA_YUY2_CH_Y = 4
};

enum yuvc_dma_nv12_ch {
	YUVC_DMA_NV12_CH_Y = 4,
	YUVC_DMA_NV12_CH_C
};

enum yuvc_dma_i420_ch {
	YUVC_DMA_I420_CH_Y = 4,
	YUVC_DMA_I420_CH_C,
	YUVC_DMA_I420_CH_V
};

/* DMA local event */
enum yuvc_dma_nv12_ev {
	YUVC_DMA_NV12_EV_C = 11,
	YUVC_DMA_NV12_EV_Y
};

enum yuvc_dma_i420_ev {
	YUVC_DMA_I420_EV_Y = 11,
	YUVC_DMA_I420_EV_C,
	YUVC_DMA_I420_EV_V,
};


struct DMA_ccr {
	unsigned src_mode:1;            /* [0] Transfer size not count */
	unsigned src_burst_size:3;      /* [3:1] Source 1 transfer size */
	unsigned src_burst_len:4;       /* [7:4] Source burst len */
	unsigned src_protect:3;         /* [10:8] Source Protection set 101b=5 */
	unsigned src_cache:3;           /* [13:11] Source Cache control */
	unsigned dst_mode:1;            /* [14] Destination increment */
	unsigned dst_burst_size:3;      /* [17:15] Destination 1 transfer size */
	unsigned dst_burst_len:4;       /* [21:18] Destination burst len */
	unsigned dst_protect:3;         /* [24:22] Source Protection set 101b=5 */
	unsigned dst_cache:3;           /* [27:25] Source Cache control */
	unsigned swap_size:4;           /* [31:28] endian_swap_size */
};

struct DMA_src {
	int offset;
	int add;
};

enum DMA_cond {
	SINGLE,
	BURST,
	ALWAYS
};

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define PL330_DMA_DBGSTATUS GDMAC_GDT0_DBGSTATUS_OFFS
#define PL330_DMA_DBGCMD    GDMAC_GDT0_DBGCMD_OFFS
#define PL330_DMA_DBGINST0  GDMAC_GDT0_DBGINST0_OFFS
#define PL330_DMA_DBGINST1  GDMAC_GDT0_DBGINST1_OFFS
#define PL330_DMA_INTEN     GDMAC_GDT0_INTEN_OFFS
#define PL330_DMA_INTCLR    GDMAC_GDT0_INTCLR_OFFS
#else
#define PL330_DMA_DBGSTATUS GDMAC_GDT1_DBGSTATUS_OFFS
#define PL330_DMA_DBGCMD    GDMAC_GDT1_DBGCMD_OFFS
#define PL330_DMA_DBGINST0  GDMAC_GDT1_DBGINST0_OFFS
#define PL330_DMA_DBGINST1  GDMAC_GDT1_DBGINST1_OFFS
#define PL330_DMA_INTEN     GDMAC_GDT1_INTEN_OFFS
#define PL330_DMA_INTCLR    GDMAC_GDT1_INTCLR_OFFS
#endif
#define _CS		0x100
#define CS(n)		(_CS + (n)*0x8)
#define _SAR		0x400
#define SAR(n)		(_SAR + (n)*0x20)
#define _DAR		0x400
#define DAR(n)		(_DAR + (n)*0x20 + 4)


#define YUVC_DMA_CH_MAX		8
#define YUVC_DMA_ASM_SZ		512
#define YUVC_DMA_PERIPHERAL	16
#define YUVC_DMA_YUY2_Y_BURST	(8*8)	 /* 8byte x 8burst */
#define YUVC_DMA_NV12_Y_BURST	(8*2)	 /* 8byte x 2burst */
#define YUVC_DMA_NV12_C_BURST	(8*2)	 /* 8byte x 2burst */
#define YUVC_DMA_I420_Y_BURST	(8*4)	 /* 8byte x 4burst */
#define YUVC_DMA_I420_C_BURST	(8*2)	 /* 8byte x 2burst */
#define YUVC_DMA_I420_V_BURST	(8*2)	 /* 8byte x 2burst */

#define YUVC_DMA_FIFO_Y0_ADDR	(0x0F080000)
#define YUVC_DMA_FIFO_Y1_ADDR	(0x0F080200)
#define YUVC_DMA_FIFO_C0_ADDR	(0x0F080400)
#define YUVC_DMA_FIFO_C1_ADDR	(0x0F080600)
#define YUVC_DMA_FIFO_C2_ADDR	(0x0F080800)
#define YUVC_DMA_FIFO_V0_ADDR	(0x0F080A00)
#define YUVC_DMA_FIFO_V1_ADDR	(0x0F080C00)
#define YUVC_DMA_FIFO_V2_ADDR	(0x0F080E00)
#define YUVC_DMA_SRC_ADDR_MAX	16

#define PL330_MAX_ITERATION_NUM	256
#define dma_outp8(addr, data)	(*(volatile u8 *)(addr) = (data))
#define dma_outp32(addr, data)	(*(volatile u32 *)(addr) = (data))
#define dma_inp32(addr)		(*(volatile u32 *)(addr))
#if 0
  #define DBG			pr_err
#else
  #define DBG(fmt, args...)
#endif
#define ERROR			pr_err


/*===================================
Exported Functions prototypes
===================================*/
int yuvc_dma_setup(enum yuvc_dma_type type, u32 src_addr[3], u32 width, u32 height);
int yuvc_dma_next_src(enum yuvc_dma_type type, u32 src_addr[3]);
int yuvc_dma_start(enum yuvc_dma_type type);
int yuvc_dma_stop(enum yuvc_dma_type type);
void yuvc_dma_clear(enum yuvc_dma_type type);
void yuvc_dma_status(int chan_num);

#endif /* _APPLITE_DMA_H */
