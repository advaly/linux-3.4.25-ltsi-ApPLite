/*
 * sound/soc/applite/applite-dma.h
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

#ifndef _APPLITE_DMA_H
#define _APPLITE_DMA_H

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#include "mach/regs/cpu_memmap_def.h"
#include "mach/regs/gdmac_offs_def.h"
#else
#include "mach/regs/cpu_memmap_def.h"
#include "mach/regs/gdmac_offs_def.h"
#endif

#include <linux/list.h>


/****************************************************************************/
/* PL330 register                                                           */
/****************************************************************************/

#define PL330_REG_BASE      CPU_GDMAC_REG_BASE
#define PL330_REG_SIZE      CPU_GDMAC_REG_SIZE
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define PL330_DMA_DBGSTATUS GDMAC_GDT0_DBGSTATUS_OFFS
#define PL330_DMA_DBGCMD    GDMAC_GDT0_DBGCMD_OFFS
#define PL330_DMA_DBGINST0  GDMAC_GDT0_DBGINST0_OFFS
#define PL330_DMA_DBGINST1  GDMAC_GDT0_DBGINST1_OFFS
#define PL330_DMA_INTEN     GDMAC_GDT0_INTEN_OFFS
#define PL330_DMA_INTCLR    GDMAC_GDT0_INTCLR_OFFS
#define PL330_ENABLE_SECURE 1	/* secure mode */
#else
	#if 1
#define PL330_DMA_DBGSTATUS GDMAC_GDT1_DBGSTATUS_OFFS
#define PL330_DMA_DBGCMD    GDMAC_GDT1_DBGCMD_OFFS
#define PL330_DMA_DBGINST0  GDMAC_GDT1_DBGINST0_OFFS
#define PL330_DMA_DBGINST1  GDMAC_GDT1_DBGINST1_OFFS
#define PL330_DMA_INTEN     GDMAC_GDT1_INTEN_OFFS
#define PL330_DMA_INTCLR    GDMAC_GDT1_INTCLR_OFFS
#define PL330_ENABLE_SECURE 0	/* non-secure mode */
	#else
#define PL330_DMA_DBGSTATUS GDMAC_GDT0_DBGSTATUS_OFFS
#define PL330_DMA_DBGCMD    GDMAC_GDT0_DBGCMD_OFFS
#define PL330_DMA_DBGINST0  GDMAC_GDT0_DBGINST0_OFFS
#define PL330_DMA_DBGINST1  GDMAC_GDT0_DBGINST1_OFFS
#define PL330_DMA_INTEN     GDMAC_GDT0_INTEN_OFFS
#define PL330_DMA_INTCLR    GDMAC_GDT0_INTCLR_OFFS
#define PL330_ENABLE_SECURE 1	/* secure mode */
	#endif
#endif

#define PL330_SND_DMA			"pl330-dma"

/*#define PL330_DMA_DEBUG*/
#undef PL330_DMA_DEBUG

#define dma_info		pr_info
#define dma_err			pr_err
#ifdef PL330_DMA_DEBUG
	#define dma_debug	pr_err
	#define ddmaasm(p) { \
		u32 *v = (u8 *)p; \
		u8 *x; \
		int count; \
		for (count = 0; count < 32; count++) { \
			x = (u8 *)(v+count); \
			pr_err("[%02d] : %02X%02X%02X%02X\n", \
				count, *(x+0), *(x+1), *(x+2), *(x+3)); \
		} \
		pr_err("\n"); \
	}
#else
	#define dma_debug(fmt...)
	#define ddmaasm(p) { \
	}
#endif
#define print_warning			pr_warning

#define PL330_P2M_DMA			0
#define PL330_M2P_DMA			1

#define PL330_MAX_ITERATION_NUM		256
#define PL330_MAX_JUMPBACK_NUM		256
#define PL330_MAX_EVENT_NUM		32
#define PL330_MAX_PERIPHERAL_NUM	32
#define PL330_MAX_CHANNEL_NUM		8

#define dma_outp8(addr, data)		(*(volatile u8 *)(addr) = (data))
#define dma_outp32(addr, data)		(*(volatile u32 *)(addr) = (data))
#define dma_inp32(addr)			(*(volatile u32 *)(addr))

enum DMA_channel {
	DMA_CH_AUTO = 0,
	DMA_CH1,
	DMA_CH2,
	DMA_CH3,

	DMA_CH_MAX
};

enum DMA_Peripheral_channel {
	DMA_PERI_CH0 = 0,
	DMA_PERI_CH1,
	DMA_PERI_CH2,
	DMA_PERI_CH3,
	DMA_PERI_CH4,
	DMA_PERI_CH5,
	DMA_PERI_CH6,
	DMA_PERI_CH7
};

/* callback_fn */
typedef void (*dma_async_callback)(void *dma_async_param, int bytes);

/* Parameter set for Channel Control Register */
struct DMA_ccr {
	unsigned src_mode:1;		/* [0] Transfer size not count */
	unsigned src_burst_size:3;	/* [3:1] Source 1 transfer size */
	unsigned src_burst_len:4;	/* [7:4] Sourse burst len */
	unsigned src_protect:3;		/* [10:8] Source Protection set 101b=5 */
	unsigned src_cache:3;		/* [13:11] Source Cache control */
	unsigned dst_mode:1;		/* [14] Destination increment */
	unsigned dst_burst_size:3;	/* [17:15] Destination 1 transfer size */
	unsigned dst_burst_len:4;	/* [21:18] Destination burst len */
	unsigned dst_protect:3;		/* [24:22] Source Protection set 101b=5 */
	unsigned dst_cache:3;		/* [27:25] Source Cache control */
	unsigned swap_size:4;		/* [31:28] endian_swap_size */
};

/* Parameter list for a DMA operation */
struct DMA_parameters {
	unsigned long	direction;	/* DMA direction */
	unsigned long	peripheral;	/* DMA Peripheral number */
	unsigned long	src_addr;	/* DMA source address */
	unsigned long	dst_addr;	/* DMA destination address */
	unsigned long	trans_size;	/* DMA Transfer size */
	struct DMA_ccr	ccr;		/* DMA control */
	unsigned long	irq_enable;	/* DMA Send IRQ */
	unsigned long	forever;	/* DMA Infinite Loop - 0(off) */
	unsigned long	bw_jump;	/* DMA backward relative offset */
	unsigned long	last_req;	/* The last DMA Req.  */

	int period_bytes;
	int periods;

	dma_async_callback callback;
	void *callback_param;
};

/* DMA controller */
enum DMA_status {
	DMA_STOP = 0,
	DMA_START,
};

struct period_node {
	struct list_head list;
	int no;
	int period_bytes;
};

struct DMA_controller {
	enum DMA_status status;
	int chan_num;
	void *mcode_cpu;
	dma_addr_t mcode_bus;

	unsigned long offset;
	unsigned long buffer_size;
	int period_bytes;
	int periods;

	struct list_head period_list;
	struct period_node period_node[64];

	dma_async_callback callback;
	void *callback_param;
};

extern int start_DMA_controller(void);
extern void stop_DMA_controller(void);
extern int alloc_DMA_channel(struct DMA_controller *dma_ctrl, int chan_num);
extern void free_DMA_channel(struct DMA_controller *dma_ctrl);
extern int setup_DMA_channel(struct DMA_controller *dma_ctrl,
		struct DMA_parameters dma_param);
extern void start_DMA_channel(struct DMA_controller *dma_ctrl, int secure_mode);
extern void stop_DMA_channel(struct DMA_controller *dma_ctrl);

#endif /* _APPLITE_DMA_H */
