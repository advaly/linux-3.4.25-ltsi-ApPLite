/*
 * linux/drivers/staging/applite/applite_yuvc_dma.c
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

#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/errno.h>
#include <linux/fs.h>       /* inode, file, file_operations */
#include <linux/kernel.h>   /* printk */
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/freezer.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/random.h>
#include <linux/interrupt.h>

#include "applite_yuvc_dma.h"

#ifdef TEST_M2M
/*
extern dma_addr_t yuvc_dma_fifo_y0_addr;
extern u32 yuvc_dma_fifo_y0_addr_cpu;
extern dma_addr_t yuvc_dma_fifo_y1_addr;
extern u32 yuvc_dma_fifo_y1_addr_cpu;
extern dma_addr_t yuvc_dma_fifo_c0_addr;
extern u32 yuvc_dma_fifo_c0_addr_cpu;
extern dma_addr_t yuvc_dma_fifo_c1_addr;
extern u32 yuvc_dma_fifo_c1_addr_cpu;
extern dma_addr_t yuvc_dma_fifo_c2_addr;
extern u32 yuvc_dma_fifo_c2_addr_cpu;
extern dma_addr_t yuvc_dma_fifo_v0_addr;
extern u32 yuvc_dma_fifo_v0_addr_cpu;
extern dma_addr_t yuvc_dma_fifo_v1_addr;
extern u32 yuvc_dma_fifo_v1_addr_cpu;
extern dma_addr_t yuvc_dma_fifo_v2_addr;
extern u32 yuvc_dma_fifo_v2_addr_cpu;
*/
#undef YUVC_DMA_FIFO_Y0_ADDR
#define YUVC_DMA_FIFO_Y0_ADDR	((u32)yuvc_dma_fifo_y0_addr)
#undef YUVC_DMA_FIFO_Y1_ADDR
#define YUVC_DMA_FIFO_Y1_ADDR	((u32)yuvc_dma_fifo_y1_addr)
#undef YUVC_DMA_FIFO_C0_ADDR
#define YUVC_DMA_FIFO_C0_ADDR	((u32)yuvc_dma_fifo_c0_addr)
#undef YUVC_DMA_FIFO_C1_ADDR
#define YUVC_DMA_FIFO_C1_ADDR	((u32)yuvc_dma_fifo_c1_addr)
#undef YUVC_DMA_FIFO_C2_ADDR
#define YUVC_DMA_FIFO_C2_ADDR	((u32)yuvc_dma_fifo_c2_addr)
#undef YUVC_DMA_FIFO_V0_ADDR
#define YUVC_DMA_FIFO_V0_ADDR	((u32)yuvc_dma_fifo_v0_addr)
#undef YUVC_DMA_FIFO_V1_ADDR
#define YUVC_DMA_FIFO_V1_ADDR	((u32)yuvc_dma_fifo_v1_addr)
#undef YUVC_DMA_FIFO_V2_ADDR
#define YUVC_DMA_FIFO_V2_ADDR	((u32)yuvc_dma_fifo_v2_addr)
#endif

static void __iomem *pl330_base;
static u32 dma_asm_cpu[YUVC_DMA_CH_MAX];
static dma_addr_t dma_asm_bus[YUVC_DMA_CH_MAX];
/* Y : [0][0...16] */
/* C : [1][0...16] */
/* V : [2][0...16] */
static struct DMA_src dma_asm_src_addr[YUVC_DMA_FIFO_MAX][YUVC_DMA_SRC_ADDR_MAX];

#ifdef USE_DMA_IRQ
static int irq_no[] = {
	136, 137, 138, 139, 140, 141, 142, 143, 144
};
static int req_irq[3] = {0, 0, 0};
static irqreturn_t yuvc_dma_irq_handler(int irq, void *data)
{
	int chan_num = (int)data;
	u32 mcode_u32 = (u32)pl330_base;
	u32 x = dma_inp32(mcode_u32+PL330_DMA_INTEN);

	DBG("%s(ch:%d)\n", __func__, chan_num);

	if (x & (1 << chan_num))
		dma_outp32(mcode_u32+PL330_DMA_INTCLR, (1<<chan_num));

	return IRQ_HANDLED;
}
#endif

/*
 * DMAC(pl330) process
 */
static int _emit_DMAMOVC_CCR(u8 *mcode_ptr, u32 dmacon)
{
	/* DMAMOV CCR, ...  */
	u8 enc_bytes[6];
	int i;

	enc_bytes[0] = (u8)(0xbc);
	enc_bytes[1] = (u8)(0x1);
	enc_bytes[2] = (u8)((dmacon>>0)&0xff);
	enc_bytes[3] = (u8)((dmacon>>8)&0xff);
	enc_bytes[4] = (u8)((dmacon>>16)&0xff);
	enc_bytes[5] = (u8)((dmacon>>24)&0xff);

	for (i = 0; i < 6; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 6;
}

static int _emit_DMAFLUSHP(u8 *mcode_ptr, u8 peripheral)
{
	/*  DMAFLUSHP (Flush and notify Peripheral) */
	u8 enc_bytes[2];
	int i;

	enc_bytes[0] = (u8)(0x35);
	enc_bytes[1] = (u8)(0x00|((peripheral&0x1f)<<3));

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

static int _emit_DMAMOVC(u8 *mcode_ptr, u8 dir, u32 st_addr)
{
	/* DMAMOV SAR, start addr
	 * DMAMOV DAR, start addr */
	u8 enc_bytes[6];
	int i;

	enc_bytes[0] = (u8)(0xbc);
	enc_bytes[1] = (u8)(0x0|dir);
	enc_bytes[2] = (u8)((st_addr>>0)&0xff);
	enc_bytes[3] = (u8)((st_addr>>8)&0xff);
	enc_bytes[4] = (u8)((st_addr>>16)&0xff);
	enc_bytes[5] = (u8)((st_addr>>24)&0xff);

	for (i = 0; i < 6; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 6;
}

static int _emit_DMALP(u8 *mcode_ptr, u8 loop_cnt, u8 iteration)
{
	/* DMALP */
	u8 enc_bytes[2];
	int i;

	enc_bytes[0] = (u8)(0x20|(loop_cnt<<1));
	enc_bytes[1] = (u8)(iteration);

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

static int _emit_DMALD(u8 *mcode_ptr, enum DMA_cond cond)
{
	/* DMALD, DMALDS, DMALDB */
	u8 bs = 0;
	u8 x = 0;
	u8 enc_bytes[1];
	int i;

	if (cond == SINGLE) {
		bs = 0;
		x = 1;
	} else if (cond == BURST) {
		bs = 1;
		x = 1;
	}

	enc_bytes[0] = (u8)(0x04|(bs<<1)|(x<<0));

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 1;
}

static int _emit_DMAST(u8 *mcode_ptr, enum DMA_cond cond)
{
	/* DMAST, DMASTS, DMASTB */
	u8 bs = 0;
	u8 x = 0;
	u8 enc_bytes[1];
	int i;

	if (cond == SINGLE) {
		bs = 0;
		x = 1;
	} else if (cond == BURST) {
		bs = 1;
		x = 1;
	}

	enc_bytes[0] = (u8)(0x08|(bs<<1)|(x<<0));

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 1;
}

static int _emit_DMASTP(u8 *mcode_ptr, u8 peripheral, enum DMA_cond cond)
{
	/* DMASTPS, DMASTPB (Store and notify Peripheral)  */
	u8 bs = 0;
	u8 enc_bytes[2];
	int i;

	if (cond == BURST)
		bs = 1;

	enc_bytes[0] = (u8)(0x29|(bs<<1));
	enc_bytes[1] = (u8)(0x00|((peripheral&0x1f)<<3));

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

static int _emit_DMAADNH(u8 *mcode_ptr, u8 ra, u32 val)
{
	/* DMAADNH */
	u8 enc_bytes[3];
	int i;

	enc_bytes[0] = (u8)(0x5c|(ra<<1));
	enc_bytes[1] = (u8)((val>>0)&0xff);
	enc_bytes[2] = (u8)((val>>8)&0xff);

	for (i = 0; i < 3; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 3;
}

static int _emit_DMAADDH(u8 *mcode_ptr, u8 ra, u32 val)
{
	/* DMAADDH */
	u8 enc_bytes[3];
	int i;

	enc_bytes[0] = (u8)(0x54|(ra<<1));
	enc_bytes[1] = (u8)((val>>0)&0xff);
	enc_bytes[2] = (u8)((val>>8)&0xff);

	for (i = 0; i < 3; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 3;
}

static int _emit_DMAWMB(u8 *mcode_ptr)
{
	/* DMAWMB (Write Memory Barrier) */
	u8 enc_bytes[1];
	int i;

	enc_bytes[0] = (u8)(0x13);

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr + i, enc_bytes[i]);

	return 1;
}

static int _emit_DMASEV(u8 *mcode_ptr, u8 event_num)
{
	/* DMASEV (Send Event) : 0 ~ 31 */
	u8 enc_bytes[2];
	int i;

	enc_bytes[0] = (u8)(0x34);
	enc_bytes[1] = (u8)((event_num<<3)|0x0);

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr + i, enc_bytes[i]);

	return 2;
}

static int _emit_DMAWFE(u8 *mcode_ptr, u8 event_num)
{
	/* DMAWFE (Wait For Event) : 0 ~ 31 */
	u8 enc_bytes[2];
	int i;

	enc_bytes[0] = (u8)(0x36);
	/* for cache coherency, invalid is issued.  */
	enc_bytes[1] = (u8)((event_num<<3)|0x2);

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

#ifndef TEST_M2M
static int _emit_DMAWFP(u8 * mcode_ptr, u8 peripheral, enum DMA_cond cond)
{
	/*  DMAWFP, DMAWFPS, DMAWFPB (Wait For Peripheral) */
	u8 bs = 0;
	u8 p = 1;
	u8 enc_bytes[2];
	int i;

	if (cond == SINGLE) {
		bs = 0;
		p = 0;
	} else if (cond == BURST) {
		bs = 1;
		p = 0;
	}
	enc_bytes[0] = (u8)(0x30|(bs<<1)|p);
	enc_bytes[1] = (u8)(0x00|((peripheral&0x1f)<<3));

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}
#endif

static int _emit_DMALPEND(u8 *mcode_ptr, u8 loop_cnt, u8 bw_jump, enum DMA_cond cond)
{
	/* DMALPEND, DMALPENDS, DMALPENDB  */
	u8 bs = 0;
	u8 x = 0;
	u8 enc_bytes[2];
	int i;

	if (cond == SINGLE) {
		bs = 0;
		x = 1;
	} else if (cond == BURST) {
		bs = 1;
		x = 1;
	}
	enc_bytes[0] = (u8)(0x38|(1<<4)|(loop_cnt<<2)|(bs<<1)|x);
	enc_bytes[1] = (u8)(bw_jump);

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr + i, enc_bytes[i]);

	return 2;
}

static int _emit_DMAEND(u8 *mcode_ptr)
{
	/* DMAEND */
	dma_outp8(mcode_ptr, 0x00);

	return 1;
}

static void _emit_DMAGO_DBGINST(u32 *mcode_ptr, int chan_num, u32 buf_addr)
{
	/* DMAGO over DBGINST[0:1] registers */
	u8 secure_bit = SECURE_BIT;
	u32 x;
	u8 uDmaGo;      /* DMAGO instruction */
	u32 mcode_u32 = (u32)mcode_ptr;

	x = 0x01;
	while ((x&0x1) == 0x1)
		x = dma_inp32(mcode_u32+PL330_DMA_DBGSTATUS);

	uDmaGo = (secure_bit == 0) ?
		(0xa0|(0<<1)) : /* secure mode     */
		(0xa0|(1<<1));  /* non-secure mode */
	dma_outp32(mcode_u32+PL330_DMA_DBGINST0,
		(chan_num<<24)|(uDmaGo<<16)|(chan_num<<8)|(0<<0));
	dma_outp32(mcode_u32+PL330_DMA_DBGINST1, buf_addr);
	/* 0 : execute the instruction that the DBGINST0,1 registers contain */
	dma_outp32(mcode_u32+PL330_DMA_DBGCMD, 0);
}

static void _emit_DMAKILL_DBGINST(u32 *mcode_ptr, u8 chan_num)
{
	/* DMAKILL over DBGINST[0:1] registers - Stop a DMA channel */
	u32 x;
	u32 mcode_u32 = (u32)mcode_ptr;

	x = 0x01;
	while ((x&0x1) == 0x1)
		x = dma_inp32(mcode_u32+PL330_DMA_DBGSTATUS);

	/* issue instruction by channel thread */
	dma_outp32(mcode_u32+PL330_DMA_DBGINST0,
		(0<<24)|(1<<16)|(chan_num<<8)|(1<<0));
	dma_outp32(mcode_u32+PL330_DMA_DBGINST1, 0);
	/* 0 : execute the instruction that the DBGINST0,1 registers contain */
	dma_outp32(mcode_u32+PL330_DMA_DBGCMD, 0);

	x = 0x01;
	while ((x&0x1) == 0x1)
		x = dma_inp32(mcode_u32+PL330_DMA_DBGSTATUS);
}

#ifdef DMA_PROG_DUMP
static void yuvc_dma_prog_dump(int ch)
{
	int i;
	u8 *mcode_ptr = (u8 *)dma_asm_cpu[ch];

	DBG("%s : ch=%d\n", __func__, ch);
	for (i = 0; i < YUVC_DMA_ASM_SZ; i += 4) {
		DBG("0x%08X  %02X%02X%02X%02X\n",
			i,
			*(mcode_ptr),
			*(mcode_ptr+1),
			*(mcode_ptr+2),
			*(mcode_ptr+3));
		mcode_ptr += 4;
	}
}
#endif


/*
 * YUVC DMA sub process
 */
static int clear_yuvc(u8 *mcode_ptr, int mcode_size)
{
	struct DMA_ccr ccr;

	/* DMAMOV CCR SAF DAF SB1 DB1 SS32 DS32 SP2 DP2 */
	ccr.src_mode = 0; ccr.dst_mode = 0;             /* SAF, DAF */
	ccr.src_burst_size = 2; ccr.dst_burst_size = 2; /* SS32, DS32 */
	ccr.src_burst_len = 0; ccr.dst_burst_len = 0;   /* SB1, DB1 */
	ccr.src_protect = CCR_PROTECT; ccr.dst_protect = CCR_PROTECT;
	ccr.src_cache = 0; ccr.dst_cache = 0;
	ccr.swap_size = 0;
	mcode_size += _emit_DMAMOVC_CCR(mcode_ptr+mcode_size, *(u32 *)&ccr);

	/* DMAMOV SAR */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, 0x0A080E04);
	/* DMAMOV DAR */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, 0x0A080E04);
	/* DMALDB */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, BURST);
	/* DMASTPB */
	mcode_size += _emit_DMASTP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL, BURST);

	return mcode_size;
}

/******************************************************************************
 * YUVC DMA for YUY2 format
 */
static void yuvc_dma_prog_yuy2_y(int ch, u32 src_addr, u32 width, u32 height)
{
	struct DMA_ccr ccr;
	u8 *mcode_ptr;
	int mcode_size = 0;
	int mloopstart0 = 0, mloopstart1 = 0;
	int lc_count, lc0, lc1;
	int fifo_num = YUVC_DMA_FIFO_Y;
	int src_num = 0;

	/*
	 * FIFO_Y0
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[ch];

	/* DMAMOV CCR SAI DAI SB8 DB4 SS64 DS64 SP2 DP2 */
	ccr.src_mode = 1; ccr.dst_mode = 1;             /* SAI, DAI */
	ccr.src_burst_size = 3; ccr.dst_burst_size = 3; /* SS64, DS64 */
	ccr.src_burst_len = 7; ccr.dst_burst_len = 3;   /* SB8, DB4 */
	ccr.src_protect = CCR_PROTECT; ccr.dst_protect = CCR_PROTECT;
	ccr.src_cache = 0; ccr.dst_cache = 0;
	ccr.swap_size = 0;
	mcode_size += _emit_DMAMOVC_CCR(mcode_ptr+mcode_size, *(u32 *)&ccr);

	/* DMAFLUSHP P16 */
	mcode_size += _emit_DMAFLUSHP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL);
	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);

	lc_count = height;
	DBG("%s : lc count %d\n", __func__, lc_count);
	while (lc_count) {
		if (lc_count > PL330_MAX_ITERATION_NUM)
			lc0 = PL330_MAX_ITERATION_NUM;
		else
			lc0 = lc_count;
		lc1 = (width * 2) / YUVC_DMA_YUY2_Y_BURST;
		DBG("%s : lc0 %d, lc1 %d\n", __func__, lc0, lc1);

		/* DMALP lc0 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
		mloopstart0 = mcode_size;
		/* DMALP lc1 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 1, lc1-1);
		mloopstart1 = mcode_size;

		/* DMAMOV DAR FIFO(Y0) */
		DBG("YUVC_DMA_FIFO_Y0_ADDR=%x\n", YUVC_DMA_FIFO_Y0_ADDR);
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y0_ADDR);

		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* DMALPEND lc1 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 1,
			(u8)(mcode_size-mloopstart1), ALWAYS);
		/* DMALPEND lc0 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
			(u8)(mcode_size-mloopstart0), ALWAYS);

		lc_count = lc_count - lc0;
	}

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

	/* dummy write(flush FIFO) */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);

	/* DMAMOV DAR FIFO(Y0) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y0_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);
	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);
#ifndef TEST_M2M
	/* DMAWFP */
	mcode_size += _emit_DMAWFP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL, ALWAYS);
#endif

	/* clear YUVC int. */
	mcode_size = clear_yuvc(mcode_ptr, mcode_size);

#ifdef USE_DMA_IRQ
	/* DMASEV */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, ch);
#endif

	/* DMAEND */
	mcode_size += _emit_DMAEND(mcode_ptr+mcode_size);

	return;
}

static void yuvc_dma_prog_yuy2(
			u32 src_addr_yuv,
			u32 width, u32 height)
{
	/*
	 * FIFO_Y0
	 */
	yuvc_dma_prog_yuy2_y(YUVC_DMA_YUY2_CH_Y, src_addr_yuv, width, height);
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_YUY2_CH_Y);
#endif
}

static void yuvc_dma_next_src_yuy2(u32 src_addr_yuv)
{
	int i;
	u8 *mcode_ptr;
	int mcode_size = 0;
	u32 next_src_addr;

	/*
	 * FIFO_Y0
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[YUVC_DMA_YUY2_CH_Y];
	for (i = 0; i < YUVC_DMA_SRC_ADDR_MAX; i++) {
		if (dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].offset == 0xffffffff)
			break;
		mcode_size = dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].offset;
		next_src_addr = src_addr_yuv + dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].add;
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, next_src_addr);
	}
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_YUY2_CH_Y);
#endif
}


/******************************************************************************
 * YUVC DMA for NV12 format
 */

static void yuvc_dma_prog_nv12_y(int ch, u32 src_addr, u32 width, u32 height)
{
	struct DMA_ccr ccr;
	u8 *mcode_ptr;
	int mcode_size = 0;
	int mloopstart0 = 0, mloopstart1 = 0;
	int lc_count, lc0, lc1;
	u32 next_line;
	int fifo_num = YUVC_DMA_FIFO_Y;
	int src_num = 0;

	/*
	 * FIFO_Y0/Y1
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[ch];

	/* DMAMOV CCR SAI DAI SB2 DB2 SS64 DS64 SP2 DP2 */
	ccr.src_mode = 1; ccr.dst_mode = 1;             /* SAI, DAI */
	ccr.src_burst_size = 3; ccr.dst_burst_size = 3; /* SS64, DS64 */
	ccr.src_burst_len = 1; ccr.dst_burst_len = 1;   /* SB2, DB2 */
	ccr.src_protect = CCR_PROTECT; ccr.dst_protect = CCR_PROTECT;
	ccr.src_cache = 0; ccr.dst_cache = 0;
	ccr.swap_size = 0;
	mcode_size += _emit_DMAMOVC_CCR(mcode_ptr+mcode_size, *(u32 *)&ccr);

	/* DMAFLUSHP P16 */
	mcode_size += _emit_DMAFLUSHP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL);
	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);

	lc_count = height / 2; /* even/odd(2) */
	DBG("%s : lc count %d\n", __func__, lc_count);
	while (lc_count) {
		if (lc_count > PL330_MAX_ITERATION_NUM)
			lc0 = PL330_MAX_ITERATION_NUM;
		else
			lc0 = lc_count;
		lc1 = width / YUVC_DMA_NV12_Y_BURST;
		DBG("%s : lc0 %d, lc1 %d\n", __func__, lc0, lc1);
		/* DMALP lc0 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
		mloopstart0 = mcode_size;
		/* DMALP lc1 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 1, lc1-1);
		mloopstart1 = mcode_size;

		/* DMAWFE C */
		mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_C);

		/* even line */

		/* DMAMOV DAR FIFO(Y0) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y0_ADDR);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* odd line */

		/* DMAADDH SAR */
		next_line = width - YUVC_DMA_NV12_Y_BURST;
		mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
		/* DMAMOV DAR FIFO(Y1) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y1_ADDR);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* DMAWMB */
		mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

		/* DMASEV Y */
		mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_Y);

		/* DMAADNH SAR */
		next_line = 0x10000 - width;
		mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);

		/* LPEND lc1 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 1,
			(u8)(mcode_size-mloopstart1), ALWAYS);

		/* DMAADDH SAR */
		next_line = width;
		mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);

		/* LPEND lc0 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
			(u8)(mcode_size-mloopstart0), ALWAYS);

		lc_count = lc_count - lc0;
	}

	/* dummy write(flush FIFO) */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(Y0) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y0_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(Y1) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y1_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

	/* wait other thread end */

	/* DMAWFE C */
	mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_C);

#ifndef TEST_M2M
	/* DMAWFP */
	mcode_size += _emit_DMAWFP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL, ALWAYS);
#endif

	/* clear YUVC int. */
	mcode_size = clear_yuvc(mcode_ptr, mcode_size);

#ifdef USE_DMA_IRQ
	/* DMASEV */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, ch);
#endif

	/* DMAEND */
	mcode_size += _emit_DMAEND(mcode_ptr+mcode_size);

	return;
}

static void yuvc_dma_prog_nv12_c(int ch, u32 src_addr, u32 width, u32 height)
{
	struct DMA_ccr ccr;
	u8 *mcode_ptr;
	int mcode_size = 0;
	int mloopstart0 = 0, mloopstart1 = 0;
	int lc_count, lc0, lc1;
	u32 next_line;
	u32 add_src;
	int fifo_num = YUVC_DMA_FIFO_C;
	int src_num = 0;

	/*
	 * FIFO_C0/C1/C2
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[ch];

	/* DMAMOV CCR SAI DAI SB2 DB2 SS64 DS64 SP2 DP2 */
	ccr.src_mode = 1; ccr.dst_mode = 1;             /* SAI, DAI */
	ccr.src_burst_size = 3; ccr.dst_burst_size = 3; /* SS64, DS64 */
	ccr.src_burst_len = 1; ccr.dst_burst_len = 1;   /* SB2, DB2 */
	ccr.src_protect = CCR_PROTECT; ccr.dst_protect = CCR_PROTECT;
	ccr.src_cache = 0; ccr.dst_cache = 0;
	ccr.swap_size = 0;
	mcode_size += _emit_DMAMOVC_CCR(mcode_ptr+mcode_size, *(u32 *)&ccr);

	/* DMAFLUSHP P16 */
	mcode_size += _emit_DMAFLUSHP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL);

	/*
	 * head line
	 */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);

	lc0 = width / YUVC_DMA_NV12_C_BURST;
	DBG("%s : lc0 %d\n", __func__, lc0);
	/* DMALP lc0 */
	mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
	mloopstart0 = mcode_size;

	/* prev line */

	/* DMAMOV DAR FIFO(C0) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C0_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* current line */

	/* DMAADNH SAR */
	next_line = 0x10000 - YUVC_DMA_NV12_C_BURST;
	mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);
	/* DMAMOV DAR FIFO(C1) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C1_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* next line */

	/* DMAADDH SAR */
	next_line = width - YUVC_DMA_NV12_C_BURST;
	mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
	/* DMAMOV DAR FIFO(C2) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C2_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

	/* DMASEV C */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_C);
	/* DMAWFE Y */
	mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_Y);

	/* DMAADNH SAR */
	next_line = 0x10000 - width;
	mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);

	/* DMALPEND lc0 */
	mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
		(u8)(mcode_size-mloopstart0), ALWAYS);

	/*
	 * loop line : (head line + 1) ... (last line - 1)
	 */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);

	lc_count = height / 2 - 2; /* height / 420format(2) - head/last(2) */
	DBG("%s : lc count %d\n", __func__, lc_count);
	while (lc_count) {
		if (lc_count > PL330_MAX_ITERATION_NUM)
			lc0 = PL330_MAX_ITERATION_NUM;
		else
			lc0 = lc_count;
		lc1 = width / YUVC_DMA_NV12_C_BURST;
		DBG("%s : lc0 %d, lc1 %d\n", __func__, lc0, lc1);
		/* DMALP lc0 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
		mloopstart0 = mcode_size;
		/* DMALP lc1 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 1, lc1-1);
		mloopstart1 = mcode_size;

		/* prev line */

		/* DMAMOV DAR FIFO(C0) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C0_ADDR);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* current line */

		/* DMAADDH SAR */
		next_line = width - YUVC_DMA_NV12_C_BURST;
		mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
		/* DMAMOV DAR FIFO(C1) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C1_ADDR);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* next line */

		/* DMAADDH SAR */
		next_line = width - YUVC_DMA_NV12_C_BURST;
		mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
		/* DMAMOV DAR FIFO(C2) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C2_ADDR);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* DMAWMB */
		mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

		/* DMASEV C */
		mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_C);
		/* DMAWFE Y */
		mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_Y);
		/* DMAADNH SAR */
		next_line = 0x10000 - (width * 2);
		mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);

		/* DMALPEND lc1 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 1,
			(u8)(mcode_size-mloopstart1), ALWAYS);
		/* DMALPEND lc0 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
			(u8)(mcode_size-mloopstart0), ALWAYS);

		lc_count = lc_count - lc0;
	}

	/*
	 * last line
	 */

	/* DMAMOV SAR */
	add_src = width * (height / 2 - 2);
			/* width * (height / 420format(2) - head/last(2)) */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = add_src;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, (src_addr+add_src));

	lc0 = width / YUVC_DMA_NV12_C_BURST;
	DBG("%s : lc0 %d\n", __func__, lc0);
	/* DMALP lc0 */
	mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
	mloopstart0 = mcode_size;

	/* prev line */

	/* DMAMOV DAR FIFO(C0) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C0_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* current line */

	/* DMAADDH SAR */
	next_line = width - YUVC_DMA_NV12_C_BURST;
	mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
	/* DMAMOV DAR FIFO(C1) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C1_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* next line */

	/* DMAADNH SAR */
	next_line = 0x10000 - YUVC_DMA_NV12_C_BURST;
	mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);
	/* DMAMOV DAR FIFO(C2) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C2_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

	/* DMASEV C */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_C);
	/* DMAWFE Y */
	mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_Y);

	/* DMAADNH SAR */
	next_line = 0x10000 - width;
	mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);

	/* DMALPEND lc0 */
	mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
		(u8)(mcode_size-mloopstart0), ALWAYS);

	/* dummy write(flush FIFO) */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(C0) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C0_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(C1) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C1_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(C2) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_C2_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

	/* send event to C */

	/* DMASEV C */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, YUVC_DMA_NV12_EV_C);

#ifdef USE_DMA_IRQ
	/* DMASEV */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, ch);
#endif

	/* DMAEND */
	mcode_size += _emit_DMAEND(mcode_ptr+mcode_size);

	return;
}

static void yuvc_dma_prog_nv12(
			u32 src_addr_y,
			u32 src_addr_uv,
			u32 width, u32 height)
{
	/*
	 * FIFO_Y0/Y1
	 */
	yuvc_dma_prog_nv12_y(YUVC_DMA_NV12_CH_Y, src_addr_y, width, height);
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_NV12_CH_Y);
#endif

	/*
	 * FIFO_C0/C1/C2
	 */
	yuvc_dma_prog_nv12_c(YUVC_DMA_NV12_CH_C, src_addr_uv, width, height);
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_NV12_CH_C);
#endif
}

static void yuvc_dma_next_src_nv12(
			u32 src_addr_y,
			u32 src_addr_uv)
{
	int i;
	u8 *mcode_ptr;
	int mcode_size = 0;
	u32 next_src_addr;

	/*
	 * FIFO_Y0/Y1
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[YUVC_DMA_NV12_CH_Y];
	for (i = 0; i < YUVC_DMA_SRC_ADDR_MAX; i++) {
		if (dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].offset == 0xffffffff)
			break;
		mcode_size = dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].offset;
		next_src_addr = src_addr_y + dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].add;
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, next_src_addr);
	}
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_NV12_CH_Y);
#endif

	/*
	 * FIFO_C0/C1/C2
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[YUVC_DMA_NV12_CH_C];
	for (i = 0; i < YUVC_DMA_SRC_ADDR_MAX; i++) {
		if (dma_asm_src_addr[YUVC_DMA_FIFO_C][i].offset == 0xffffffff)
			break;
		mcode_size = dma_asm_src_addr[YUVC_DMA_FIFO_C][i].offset;
		next_src_addr = src_addr_uv + dma_asm_src_addr[YUVC_DMA_FIFO_C][i].add;
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, next_src_addr);
	}
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_NV12_CH_C);
#endif
}

/******************************************************************************
 * YUVC DMA for I420 format
 */
static void yuvc_dma_prog_i420_y(int ch, u32 src_addr, u32 width, u32 height)
{
	struct DMA_ccr ccr;
	u8 *mcode_ptr;
	int mcode_size = 0;
	int mloopstart0 = 0, mloopstart1 = 0;
	int lc_count, lc0, lc1;
	u32 next_line;
	int fifo_num = YUVC_DMA_FIFO_Y;
	int src_num = 0;

	/*
	 * FIFO_Y0/Y1
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[ch];

	/* DMAMOV CCR SAI DAI SB4 DB4 SS64 DS64 SP2 DP2 */
	ccr.src_mode = 1; ccr.dst_mode = 1;             /* SAI, DAI */
	ccr.src_burst_size = 3; ccr.dst_burst_size = 3; /* SS64, DS64 */
	ccr.src_burst_len = 3; ccr.dst_burst_len = 3;   /* SB4, DB4 */
	ccr.src_protect = CCR_PROTECT; ccr.dst_protect = CCR_PROTECT;
	ccr.src_cache = 0; ccr.dst_cache = 0;
	ccr.swap_size = 0;
	mcode_size += _emit_DMAMOVC_CCR(mcode_ptr+mcode_size, *(u32 *)&ccr);

	/* DMAFLUSHP P16 */
	mcode_size += _emit_DMAFLUSHP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL);

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);

	lc_count = height / 2; /* even/odd(2) */
	DBG("%s : lc count %d\n", __func__, lc_count);
	while (lc_count) {
		if (lc_count > PL330_MAX_ITERATION_NUM)
			lc0 = PL330_MAX_ITERATION_NUM;
		else
			lc0 = lc_count;
		lc1 = width / YUVC_DMA_I420_Y_BURST;
		DBG("%s : lc0 %d, lc1 %d\n", __func__, lc0, lc1);
		/* DMALP lc0 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
		mloopstart0 = mcode_size;
		/* DMALP lc1 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 1, lc1-1);
		mloopstart1 = mcode_size;

		/* DMAWFE C */
		mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_I420_EV_C);
		/* DMAWFE V */
		mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_I420_EV_V);

		/* even line */

		/* DMAMOV DAR FIFO(Y0) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y0_ADDR);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* odd line */

		/* DMAADDH SAR */
		next_line = width - YUVC_DMA_I420_Y_BURST;
		mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
		/* DMAMOV DAR FIFO(Y1) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y1_ADDR);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* DMAWMB */
		mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

		/* DMASEV Y */
		mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, YUVC_DMA_I420_EV_Y);

		/* DMAADNH SAR */
		next_line = 0x10000 - width;
		mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);

		/* LPEND lc1 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 1,
			(u8)(mcode_size-mloopstart1), ALWAYS);

		/* DMAADDH SAR */
		next_line = width;
		mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);

		/* LPEND lc0 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
		(u8)(mcode_size-mloopstart0), ALWAYS);

		lc_count = lc_count - lc0;
	}

	/* wait other thread end */

	/* DMAWFE C */
	mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_I420_EV_C);
	/* DMAWFE V */
	mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_I420_EV_V);

	/* dummy write(flush FIFO) */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(Y0) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y0_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(Y1) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, YUVC_DMA_FIFO_Y1_ADDR);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

#ifndef TEST_M2M
	/* DMAWFP */
	mcode_size += _emit_DMAWFP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL, ALWAYS);
#endif

	/* clear YUVC int. */
	mcode_size = clear_yuvc(mcode_ptr, mcode_size);

	/* DMASEV */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, ch);

	/* DMAEND */
	mcode_size += _emit_DMAEND(mcode_ptr+mcode_size);

	return;
}

static void yuvc_dma_prog_i420_c_v(int ch, u32 src_addr, u32 width, u32 height)
{
	struct DMA_ccr ccr;
	u8 *mcode_ptr;
	int mcode_size = 0;
	int mloopstart0 = 0, mloopstart1 = 0;
	int lc_count, lc0, lc1;
	u32 next_line;
	u32 add_src;
	int fifo_num;
	int src_num = 0;
	int burst;
	u32 fifo_adrs[3];
	int dmasev;

	if (ch == YUVC_DMA_I420_CH_C) {
		fifo_num = YUVC_DMA_FIFO_C;
		burst = YUVC_DMA_I420_C_BURST;
		fifo_adrs[0] = YUVC_DMA_FIFO_C0_ADDR;
		fifo_adrs[1] = YUVC_DMA_FIFO_C1_ADDR;
		fifo_adrs[2] = YUVC_DMA_FIFO_C2_ADDR;
		dmasev = YUVC_DMA_I420_EV_C;
	} else {
		fifo_num = YUVC_DMA_FIFO_V;
		burst = YUVC_DMA_I420_V_BURST;
		fifo_adrs[0] = YUVC_DMA_FIFO_V0_ADDR;
		fifo_adrs[1] = YUVC_DMA_FIFO_V1_ADDR;
		fifo_adrs[2] = YUVC_DMA_FIFO_V2_ADDR;
		dmasev = YUVC_DMA_I420_EV_V;
	}

	/*
	 * FIFO_C0/C1/C2 or FIFO_V0/V1/V2
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[ch];

	/* DMAMOV CCR SAI DAI SB2 DB2 SS64 DS64 SP2 DP2 */
	ccr.src_mode = 1; ccr.dst_mode = 1;             /* SAI, DAI */
	ccr.src_burst_size = 3; ccr.dst_burst_size = 3; /* SS64, DS64 */
	ccr.src_burst_len = 1; ccr.dst_burst_len = 1;   /* SB2, DB2 */
	ccr.src_protect = CCR_PROTECT; ccr.dst_protect = CCR_PROTECT;
	ccr.src_cache = 0; ccr.dst_cache = 0;
	ccr.swap_size = 0;
	mcode_size += _emit_DMAMOVC_CCR(mcode_ptr+mcode_size, *(u32 *)&ccr);

	/* DMAFLUSHP P16 */
	mcode_size += _emit_DMAFLUSHP(mcode_ptr+mcode_size, YUVC_DMA_PERIPHERAL);

	/*
	 * head line
	 */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);

	lc0 = (width / 2) / burst; /* (width / 420format(2)) / burst */
	DBG("%s : lc0 %d\n", __func__, lc0);
	/* DMALP lc0 */
	mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
	mloopstart0 = mcode_size;

	/* prev line */

	/* DMAMOV DAR FIFO(C0/V0) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[0]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* current line */

	/* DMAADNH SAR */
	next_line = 0x10000 - burst;
	mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);
	/* DMAMOV DAR FIFO(C1/V1) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[1]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* next line */

	/* DMAADDH SAR */
	next_line = (width / 2) - burst; /* (width / 420format(2)) - burst */
	mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
	/* DMAMOV DAR FIFO(C2/V2) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[2]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

	/* DMASEV C */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, dmasev);
	/* DMAWFE Y */
	mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_I420_EV_Y);

	/* DMAADNH SAR */
	next_line = 0x10000 - (width / 2); /* -(width / 420format(2)) */
	mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);

	/* DMALPEND lc0 */
	mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
		(u8)(mcode_size-mloopstart0), ALWAYS);

	/*
	 * loop line : (head line + 1) ... (last line - 1)
	 */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);

	lc_count = height / 2 - 2; /* height / 420format(2) - head/last(2) */
	DBG("%s : lc count %d\n", __func__, lc_count);
	while (lc_count) {
		if (lc_count > PL330_MAX_ITERATION_NUM)
			lc0 = PL330_MAX_ITERATION_NUM;
		else
			lc0 = lc_count;
		lc1 = (width / 2) / burst; /* (width / 420format(2)) / burst */
		DBG("%s : lc0 %d, lc1 %d\n", __func__, lc0, lc1);
		/* DMALP lc0 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
		mloopstart0 = mcode_size;
		/* DMALP lc1 */
		mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 1, lc1-1);
		mloopstart1 = mcode_size;

		/* prev line */

		/* DMAMOV DAR FIFO(C0/V0) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[0]);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* current line */

		/* DMAADDH SAR */
		next_line = (width / 2) - burst; /* (width / 420format(2)) - burst */
		mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
		/* DMAMOV DAR FIFO(C1/V1) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[1]);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* next line */

		/* DMAADDH SAR */
		next_line = (width / 2) - burst; /* (width / 420format(2)) - burst */
		mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
		/* DMAMOV DAR FIFO(C2/V2) */
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[2]);
		/* DMALD */
		mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
		/* DMAST */
		mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

		/* DMAWMB */
		mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

		/* DMASEV C */
		mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, dmasev);
		/* DMAWFE Y */
		mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_I420_EV_Y);
		/* DMAADNH SAR */
		next_line = 0x10000 - ((width / 2) * 2);
				/* (width / 420format(2)) * 2 */
		mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);

		/* DMALPEND lc1 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 1,
		(u8)(mcode_size-mloopstart1), ALWAYS);
		/* DMALPEND lc0 */
		mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
		(u8)(mcode_size-mloopstart0), ALWAYS);

		lc_count = lc_count - lc0;
	}

	/*
	 * last line
	 */
	/* DMAMOV SAR */
	add_src = (width / 2) * (height / 2 - 2);
		/* (width / 420format(2)) * (height / 420format(2) - head/last(2)) */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = add_src;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, (src_addr+add_src));

	lc0 = (width / 2) / burst; /* (width / 420format(2)) / burst */
	DBG("%s : lc0 %d\n", __func__, lc0);
	/* DMALP lc0 */
	mcode_size += _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
	mloopstart0 = mcode_size;

	/* prev line */

	/* DMAMOV DAR FIFO(C0/V0)) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[0]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* current line */

	/* DMAADDH SAR */
	next_line = width / 2 - burst; /* (width / 420format(2)) - burst */
	mcode_size += _emit_DMAADDH(mcode_ptr+mcode_size, 0, next_line);
	/* DMAMOV DAR FIFO(C1/V1) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[1]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* next line */

	/* DMAADNH SAR */
	next_line = 0x10000 - burst;
	mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);
	/* DMAMOV DAR FIFO(C2/V2) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[2]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

	/* DMASEV C */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, dmasev);
	/* DMAWFE Y */
	mcode_size += _emit_DMAWFE(mcode_ptr+mcode_size, YUVC_DMA_I420_EV_Y);

	/* DMAADNH SAR */
	next_line = 0x10000 - (width / 2); /* (width / 420format(2)) */
	mcode_size += _emit_DMAADNH(mcode_ptr+mcode_size, 0, next_line);

	/* DMALPEND lc0 */
	mcode_size += _emit_DMALPEND(mcode_ptr+mcode_size, 0,
		(u8)(mcode_size-mloopstart0), ALWAYS);

	/* dummy write(flush FIFO) */

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(C0/V0) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[0]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(C1/V1) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[1]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAMOV SAR */
	dma_asm_src_addr[fifo_num][src_num].offset = mcode_size;
	dma_asm_src_addr[fifo_num][src_num].add = 0;
	src_num++;
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, src_addr);
	/* DMAMOV DAR FIFO(C2/V2) */
	mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 2, fifo_adrs[2]);
	/* DMALD */
	mcode_size += _emit_DMALD(mcode_ptr+mcode_size, ALWAYS);
	/* DMAST */
	mcode_size += _emit_DMAST(mcode_ptr+mcode_size, ALWAYS);

	/* DMAWMB */
	mcode_size += _emit_DMAWMB(mcode_ptr+mcode_size);

	/* DMASEV C */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, dmasev);

#ifdef USE_DMA_IRQ
	/* DMASEV */
	mcode_size += _emit_DMASEV(mcode_ptr+mcode_size, ch);
#endif

	/* DMAEND */
	mcode_size += _emit_DMAEND(mcode_ptr+mcode_size);

	return;
}

static void yuvc_dma_prog_i420(
			u32 src_addr_y,
			u32 src_addr_u,
			u32 src_addr_v,
			u32 width, u32 height)
{
	/*
	 * FIFO_Y0/Y1
	 */
	yuvc_dma_prog_i420_y(YUVC_DMA_I420_CH_Y, src_addr_y, width, height);
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_I420_CH_Y);
#endif

	/*
	 * FIFO_C0/C1/C2
	 */
	yuvc_dma_prog_i420_c_v(YUVC_DMA_I420_CH_C, src_addr_u, width, height);
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_I420_CH_C);
#endif

	/*
	 * FIFO_V0/V1/V2
	 */
	yuvc_dma_prog_i420_c_v(YUVC_DMA_I420_CH_V, src_addr_v, width, height);
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_I420_CH_V);
#endif
}

static void yuvc_dma_next_src_i420(
			u32 src_addr_y,
			u32 src_addr_u,
			u32 src_addr_v)
{
	int i;
	u8 *mcode_ptr;
	int mcode_size = 0;
	u32 next_src_addr;

	/*
	 * FIFO_Y0/Y1
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[YUVC_DMA_I420_CH_Y];
	for (i = 0; i < YUVC_DMA_SRC_ADDR_MAX; i++) {
		if (dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].offset == 0xffffffff)
			break;
		mcode_size = dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].offset;
		next_src_addr = src_addr_y + dma_asm_src_addr[YUVC_DMA_FIFO_Y][i].add;
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, next_src_addr);
	}
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_I420_CH_Y);
#endif

	/*
	 * FIFO_C0/C1/C2
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[YUVC_DMA_I420_CH_C];
	for (i = 0; i < YUVC_DMA_SRC_ADDR_MAX; i++) {
		if (dma_asm_src_addr[YUVC_DMA_FIFO_C][i].offset == 0xffffffff)
			break;
		mcode_size = dma_asm_src_addr[YUVC_DMA_FIFO_C][i].offset;
		next_src_addr = src_addr_u + dma_asm_src_addr[YUVC_DMA_FIFO_C][i].add;
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, next_src_addr);
	}
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_I420_CH_C);
#endif

	/*
	 * FIFO_V0/V1/V2
	 */
	mcode_ptr = (u8 *)dma_asm_cpu[YUVC_DMA_I420_CH_V];
	for (i = 0; i < YUVC_DMA_SRC_ADDR_MAX; i++) {
		if (dma_asm_src_addr[YUVC_DMA_FIFO_V][i].offset == 0xffffffff)
			break;
		mcode_size = dma_asm_src_addr[YUVC_DMA_FIFO_V][i].offset;
		next_src_addr = src_addr_v + dma_asm_src_addr[YUVC_DMA_FIFO_V][i].add;
		mcode_size += _emit_DMAMOVC(mcode_ptr+mcode_size, 0, next_src_addr);
	}
#ifdef DMA_PROG_DUMP
	yuvc_dma_prog_dump(YUVC_DMA_I420_CH_V);
#endif
}

/*
 * YUVC DMA process
 */
int yuvc_dma_setup(enum yuvc_dma_type type,
		u32 src_addr[3],
		u32 width,
		u32 height)
{
	int rtn = 0;
	int i;
	int start_ch;
	int chnum = 0;

	DBG("%s enter(%d)\n", __func__, type);

	pl330_base = NULL;
	for (i = 0; i < YUVC_DMA_CH_MAX; i++) {
		dma_asm_cpu[i] = 0;
		dma_asm_bus[i] = 0;
	}

	pl330_base = ioremap(CPU_GDMAC_REG_BASE, CPU_GDMAC_REG_SIZE);
	if (!pl330_base)
		return -ENOMEM;

	switch (type) {
	case YUVC_DMA_YUY2:
		start_ch = YUVC_DMA_YUY2_CH_Y;
		chnum = 1;
		break;
	case YUVC_DMA_NV12:
		start_ch = YUVC_DMA_NV12_CH_Y;
		chnum = 2;
		break;
	case YUVC_DMA_I420:
		start_ch = YUVC_DMA_I420_CH_Y;
		chnum = 3;
		break;
	}
	for (i = 0; i < chnum; i++) {
		dma_asm_cpu[start_ch+i] = (u32)dma_alloc_coherent(NULL,
			YUVC_DMA_ASM_SZ, &dma_asm_bus[start_ch+i], GFP_KERNEL|GFP_DMA);
		if (!dma_asm_cpu[start_ch+i]) {
			rtn = -ENOMEM;
			goto __err;
		}
	}

	/* clear source addr offset */
	memset(dma_asm_src_addr, 0xff, sizeof(dma_asm_src_addr));

	/* pl330 program */
	switch (type) {
	case YUVC_DMA_YUY2:
		yuvc_dma_prog_yuy2(
			src_addr[YUVC_DMA_YUY2_SRC_YUV],
			width, height
		);
		break;
	case YUVC_DMA_NV12:
		yuvc_dma_prog_nv12(
			src_addr[YUVC_DMA_NV12_SRC_Y],
			src_addr[YUVC_DMA_NV12_SRC_UV],
			width, height
		);
		break;
	case YUVC_DMA_I420:
		yuvc_dma_prog_i420(
			src_addr[YUVC_DMA_I420_SRC_Y],
			src_addr[YUVC_DMA_I420_SRC_U],
			src_addr[YUVC_DMA_I420_SRC_V],
			width, height
		);
		break;
	}

#ifdef USE_DMA_IRQ
	for (i = 0; i < chnum; i++) {
		DBG("request_irq(%d,%x)\n", irq_no[start_ch+i], (start_ch+i));
		if (request_irq(irq_no[start_ch+i], yuvc_dma_irq_handler, 0,
				"pl330", (void *)(start_ch+i)))
			break;
		req_irq[i] = irq_no[start_ch+i];
	}
#endif

	return 0;

__err:
	for (i = 0; i < chnum; i++) {
		if (dma_asm_cpu[start_ch+i]) {
			dma_free_coherent(NULL, YUVC_DMA_ASM_SZ,
				(void *)dma_asm_cpu[start_ch+i], dma_asm_bus[start_ch+i]);
			dma_asm_cpu[start_ch+i] = 0;
		}
	}
	iounmap(pl330_base);
	pl330_base = NULL;
	return rtn;
}
EXPORT_SYMBOL_GPL(yuvc_dma_setup);

int yuvc_dma_next_src(enum yuvc_dma_type type, u32 src_addr[3])
{
	DBG("%s enter(%d)\n", __func__, type);

	/* set next src */
	switch (type) {
	case YUVC_DMA_YUY2:
		yuvc_dma_next_src_yuy2(
			src_addr[YUVC_DMA_YUY2_SRC_YUV]
		);
		break;
	case YUVC_DMA_NV12:
		yuvc_dma_next_src_nv12(
			src_addr[YUVC_DMA_NV12_SRC_Y],
			src_addr[YUVC_DMA_NV12_SRC_UV]
		);
		break;
	case YUVC_DMA_I420:
		yuvc_dma_next_src_i420(
			src_addr[YUVC_DMA_I420_SRC_Y],
			src_addr[YUVC_DMA_I420_SRC_U],
			src_addr[YUVC_DMA_I420_SRC_V]
		);
		break;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(yuvc_dma_next_src);

int yuvc_dma_start(enum yuvc_dma_type type)
{
#ifdef USE_DMA_IRQ
	u32 mcode_u32 = (u32)pl330_base;
	u32 x;
#endif

	DBG("%s enter(%d)\n", __func__, type);

	switch (type) {
	case YUVC_DMA_YUY2:
		/* YUV -> FIFO_Y0 */
		_emit_DMAGO_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_YUY2_CH_Y,
			(u32)dma_asm_bus[YUVC_DMA_YUY2_CH_Y]);
#ifdef USE_DMA_IRQ
		x = dma_inp32(mcode_u32+PL330_DMA_INTEN);
		x |= (1<<YUVC_DMA_YUY2_CH_Y);
		dma_outp32(mcode_u32+PL330_DMA_INTEN, x);
#endif
		break;
	case YUVC_DMA_NV12:
		/* YU -> FIFO_Y0/Y1 */
		_emit_DMAGO_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_NV12_CH_Y,
			(u32)dma_asm_bus[YUVC_DMA_NV12_CH_Y]);
		/* V  -> FIFO_C0/C1/C2 */
		_emit_DMAGO_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_NV12_CH_C,
			(u32)dma_asm_bus[YUVC_DMA_NV12_CH_C]);
#ifdef USE_DMA_IRQ
		x = dma_inp32(mcode_u32+PL330_DMA_INTEN);
		x |= ((1<<YUVC_DMA_NV12_CH_Y) | (1<<YUVC_DMA_NV12_CH_C));
		dma_outp32(mcode_u32+PL330_DMA_INTEN, x);
#endif
		break;
	case YUVC_DMA_I420:
		/* Y  -> FIFO_Y0/Y1 */
		_emit_DMAGO_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_I420_CH_Y,
			(u32)dma_asm_bus[YUVC_DMA_I420_CH_Y]);
		/* U  -> FIFO_C0/C1/C2 */
		_emit_DMAGO_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_I420_CH_C,
			(u32)dma_asm_bus[YUVC_DMA_I420_CH_C]);
		/* V  -> FIFO_V0/V1/V2 */
		_emit_DMAGO_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_I420_CH_V,
			(u32)dma_asm_bus[YUVC_DMA_I420_CH_V]);
#ifdef USE_DMA_IRQ
		x = dma_inp32(mcode_u32+PL330_DMA_INTEN);
		x |= ((1<<YUVC_DMA_I420_CH_Y) | (1<<YUVC_DMA_I420_CH_C) | (1<<YUVC_DMA_I420_CH_V));
		dma_outp32(mcode_u32+PL330_DMA_INTEN, x);
#endif
		break;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(yuvc_dma_start);

int yuvc_dma_stop(enum yuvc_dma_type type)
{
#ifdef USE_DMA_IRQ
	u32 mcode_u32 = (u32)pl330_base;
	u32 x;
#endif

	DBG("%s enter(%d)\n", __func__, type);

	switch (type) {
	case YUVC_DMA_YUY2:
#ifdef USE_DMA_IRQ
		x = dma_inp32(mcode_u32+PL330_DMA_INTEN);
		x &= ~(1<<YUVC_DMA_YUY2_CH_Y);
		dma_outp32(mcode_u32+PL330_DMA_INTEN, x);
#endif
		_emit_DMAKILL_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_YUY2_CH_Y);
		break;
	case YUVC_DMA_NV12:
		_emit_DMAKILL_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_NV12_CH_Y);
		_emit_DMAKILL_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_NV12_CH_C);
#ifdef USE_DMA_IRQ
		x = dma_inp32(mcode_u32+PL330_DMA_INTEN);
		x &= ~((1<<YUVC_DMA_NV12_CH_Y) | (1<<YUVC_DMA_NV12_CH_C));
		dma_outp32(mcode_u32+PL330_DMA_INTEN, x);
#endif
		break;
	case YUVC_DMA_I420:
		_emit_DMAKILL_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_I420_CH_Y);
		_emit_DMAKILL_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_I420_CH_C);
		_emit_DMAKILL_DBGINST((u32 *)((unsigned long)pl330_base),
			YUVC_DMA_I420_CH_V);
#ifdef USE_DMA_IRQ
		x = dma_inp32(mcode_u32+PL330_DMA_INTEN);
		x &= ~((1<<YUVC_DMA_I420_CH_Y) | (1<<YUVC_DMA_I420_CH_C) | (1<<YUVC_DMA_I420_CH_V));
		dma_outp32(mcode_u32+PL330_DMA_INTEN, x);
#endif
		break;
	}
	return 0;
}
EXPORT_SYMBOL_GPL(yuvc_dma_stop);

void yuvc_dma_clear(enum yuvc_dma_type type)
{
	int i;
	int chnum = 0;
	int start_ch;

	DBG("%s enter(%d)\n", __func__, type);

	switch (type) {
	case YUVC_DMA_YUY2:
		start_ch = YUVC_DMA_YUY2_CH_Y;
		chnum = 1;
		break;
	case YUVC_DMA_NV12:
		start_ch = YUVC_DMA_NV12_CH_Y;
		chnum = 2;
		break;
	case YUVC_DMA_I420:
		start_ch = YUVC_DMA_I420_CH_Y;
		chnum = 3;
		break;
	}

	for (i = 0; i < chnum; i++) {
		if (dma_asm_cpu[start_ch+i]) {
			dma_free_coherent(NULL, YUVC_DMA_ASM_SZ,
				(void *)dma_asm_cpu[start_ch+i], dma_asm_bus[start_ch+i]);
			dma_asm_cpu[start_ch+i] = 0;
		}
	}

#ifdef USE_DMA_IRQ
	for (i = 0; i < 3; i++) {
		if (req_irq[i]) {
			free_irq(req_irq[i], (void *)(start_ch+i));
			DBG("free_irq(%d,%x)\n", req_irq[i], (start_ch+i));
		}
		req_irq[i] = 0;
	}
#endif

	if (pl330_base)
		iounmap(pl330_base);
	pl330_base = NULL;

	return;
}
EXPORT_SYMBOL_GPL(yuvc_dma_clear);

void yuvc_dma_status(int chan_num)
{
	u32 mcode_u32;
	u32 x;

	if (!pl330_base)
		return;
	mcode_u32 = (u32)((unsigned long)pl330_base);

	x = dma_inp32(mcode_u32+CS(chan_num));
	DBG("%s(ch:%d) : CS=%08X\n", __func__, chan_num, x);

	x = dma_inp32(mcode_u32+SAR(chan_num));
	DBG("%s(ch:%d) : SAR=%08X\n", __func__, chan_num, x);

	x = dma_inp32(mcode_u32+DAR(chan_num));
	DBG("%s(ch:%d) : DAR=%08X\n", __func__, chan_num, x);
}
EXPORT_SYMBOL_GPL(yuvc_dma_status);
