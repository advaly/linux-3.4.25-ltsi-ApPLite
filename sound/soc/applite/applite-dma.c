/*
 * sound/soc/applite/applite-dma.c
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

#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/dmaengine.h>
#include <linux/fsl/mxs-dma.h>

#include <sound/core.h>
#include <sound/initval.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/dmaengine_pcm.h>

#include "applite-tzxxx.h"
#include "applite-dma.h"


struct dma_channle {
	int use_ch[DMA_CH_MAX];
};

static struct dma_channle use_channles = {
	.use_ch[0] = 1,	/* ch0 is no use */
	.use_ch[1] = 1, /* use irecog */
	.use_ch[2] = 0,
	.use_ch[3] = 0,
};

static int dma_irq_num[DMA_CH_MAX] = {
	-1,     /* ch0 is no use */
	137,
	138,
	139
};


static void __iomem *pl330_base;

static void print_dma_param_info(struct DMA_parameters dma_param)
{
	/* Parameter list for a DMA operation */
	dma_debug("     direction = %d\n", (u32)dma_param.direction);
	dma_debug("     peripheral = %d\n", (u32)dma_param.peripheral);
	dma_debug("     src_addr = 0x%x\n", (u32)dma_param.src_addr);
	dma_debug("     dst_addr = 0x%x\n", (u32)dma_param.dst_addr);
	dma_debug("     trans_size = %d\n", (u32)dma_param.trans_size);
	dma_debug("     irq_enable = %d\n", (u32)dma_param.irq_enable);
	dma_debug("     forever = %d\n", (u32)dma_param.forever);
	dma_debug("     bw_jump = %d\n", (u32)dma_param.bw_jump);
	dma_debug("     last_req = %d\n", (u32)dma_param.last_req);
}

static int _emit_DMAMOVC_CCR(u8 *mcode_ptr, u32 dmacon)
{
	/* DMAMOV CCR, ...  */
	u8 enc_bytes[6];
	u32 i;

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

static int _emit_DMAMOVC(u8 *mcode_ptr, u8 dir, u32 st_addr)
{
	/* DMAMOV SAR, start addr
	 * DMAMOV DAR, start addr   */
	u8 enc_bytes[6];
	u32 i;

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

static int _emit_DMALD(u8 *mcode_ptr)
{
	/* DMALD, DMALDS, DMALDB  */
	u8 bs = 1;
	u8 x = 1;
	u8 enc_bytes[1];
	u32 i;

	enc_bytes[0] = (u8)(0x04|(bs<<1)|(x<<0));

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 1;
}

static int _emit_DMALDP(u8 *mcode_ptr, u8 peripheral, u8 burst_size)
{
	/* DMALDPS, DMALDPB (Load Peripheral)  */
	u8 bs;
	u8 enc_bytes[2];
	u32 i;

	if (peripheral > PL330_MAX_PERIPHERAL_NUM) {
		print_warning("[%s] The peripheral number is too big ! : %d\n",
			__FUNCTION__, peripheral);
		return 0;
	}

	bs = (burst_size == 1) ? 0 : 1; /* single -> 0, burst -> 1 */

	enc_bytes[0] = (u8)(0x25|(bs<<1));
	enc_bytes[1] = (u8)(0x00|((peripheral&0x1f)<<3));

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

static int _emit_DMAST(u8 *mcode_ptr)
{
	/* DMAST, DMASTS, DMASTB  */
	u8 bs = 1;
	u8 x = 1;
	u8 enc_bytes[1];
	u32 i;

	enc_bytes[0] = (u8)(0x08|(bs<<1)|(x<<0));

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 1;
}

static int _emit_DMASTP(u8 *mcode_ptr, u8 peripheral, u8 burst_size)
{
	/* DMASTPS, DMASTPB (Store and notify Peripheral)  */
	u8 bs;
	u8 enc_bytes[2];
	u32 i;

	if (peripheral > PL330_MAX_PERIPHERAL_NUM) {
		print_warning("[%s] The peripheral number is too big ! : %d\n",
			__FUNCTION__, peripheral);
		return 0;
	}

	bs = (burst_size == 1) ? 0 : 1; /* single:0, burst:1 */

	enc_bytes[0] = (u8)(0x29|(bs<<1));
	enc_bytes[1] = (u8)(0x00|((peripheral&0x1f)<<3));

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

#if 0
static int _emit_DMASTZ(u8 *mcode_ptr)
{
	/* DMASTZ  */
	u8 enc_bytes[1];
	u32 i;

	enc_bytes[0] = (u8)(0x0c);

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 1;
}
#endif

static int _emit_DMALP(u8 *mcode_ptr, u8 loop_cnt, u8 iteration)
{
	/* DMALP  */
	u8 enc_bytes[2];
	u32 i;

	enc_bytes[0] = (u8)(0x20|(loop_cnt<<1));
	enc_bytes[1] = (u8)(iteration);

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

static int _emit_DMALPFE(u8 *mcode_ptr, u8 bw_jump)
{
	/* DMALPFE  */
	u8 bs = 0;
	u8 x = 0;
	u8 enc_bytes[2];
	u32 i;

	enc_bytes[0] = (u8)(0x28|(0<<4)|(1<<2)|(bs<<1)|x);
	enc_bytes[1] = (u8)(bw_jump);

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr + i, enc_bytes[i]);

	return 2;
}

static int _emit_DMALPEND(u8 *mcode_ptr, u8 loop_cnt, u8 bw_jump)
{
	/* DMALPEND, DMALPENDS, DMALPENDB  */
	u8 bs = 0;
	u8 x = 0;
	u8 enc_bytes[2];
	u32 i;

	enc_bytes[0] = (u8)(0x38|(1<<4)|(loop_cnt<<2)|(bs<<1)|x);
	enc_bytes[1] = (u8)(bw_jump);

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr + i, enc_bytes[i]);

	return 2;
}

static int _emit_DMAWFP(u8 *mcode_ptr, u8 peripheral)
{
	/*  DMAWFP, DMAWFPS, DMAWFPB (Wait For Peripheral) */
	u8 bs = 1;
	u8 p = 0;
	u8 enc_bytes[2];
	u32 i;

	if (peripheral > PL330_MAX_PERIPHERAL_NUM) {
		print_warning("[%s] The peripheral number is too big ! : %d\n",
			__FUNCTION__, peripheral);
		return 0;
	}

	enc_bytes[0] = (u8)(0x30|(bs<<1)|p);
	enc_bytes[1] = (u8)(0x00|((peripheral&0x1f)<<3));

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

#if 0
static int _emit_DMAWFE(u8 *mcode_ptr, u8 event_num)
{
	/* DMAWFE (Wait For Event) : 0 ~ 31 */
	u8 enc_bytes[2];
	u32 i;

	if (event_num > PL330_MAX_EVENT_NUM) {
		print_warning("[%s] The event_num number is too big ! : %d\n",
			__FUNCTION__, event_num);
		return 0;
	}

	enc_bytes[0] = (u8)(0x36);
	/* for cache coherency, invalid is issued.  */
	enc_bytes[1] = (u8)((event_num<<3)|0x2);

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}
#endif

static int _emit_DMAFLUSHP(u8 *mcode_ptr, u8 peripheral)
{
	/*  DMAFLUSHP (Flush and notify Peripheral) */
	u8 enc_bytes[2];
	u32 i;

	if (peripheral > PL330_MAX_PERIPHERAL_NUM) {
		print_warning("[%s] The peripheral number is too big ! : %d\n",
			__FUNCTION__, peripheral);
		return 0;
	}

	enc_bytes[0] = (u8)(0x35);
	enc_bytes[1] = (u8)(0x00|((peripheral&0x1f)<<3));

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 2;
}

static int _emit_DMAEND(u8 *mcode_ptr)
{
	/* DMAEND */
	dma_outp8(mcode_ptr, 0x00);

	return 1;
}

#if 0
static int _emit_DMAADDH(u8 *mcode_ptr, int src_dir, __u16 st_addr)
{
	/* DMAADDH (Add Halfword) */
	u8 uDir = (src_dir) ? 0 : 1; /* src addr=0, dst addr=1 */
	u8 enc_bytes[3];
	u32 i;

	enc_bytes[0] = (u8)(0x54|(uDir<<1));
	enc_bytes[1] = (u8)((st_addr>>0)&0xff);
	enc_bytes[2] = (u8)((st_addr>>8)&0xff);

	for (i = 0; i < 3; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 3;
}
#endif

#if 0
static int _emit_DMAKILL(u8 *mcode_ptr)
{
	/* DMAKILL (Kill) */
	u8 enc_bytes[1];
	u32 i;

	enc_bytes[0] = (u8)(0x01);

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 1;
}
#endif

#if 0
static int _emit_DMANOP(u8 *mcode_ptr)
{
	/* DMANOP (No operation) */
	u8 enc_bytes[1];
	u32 i;

	enc_bytes[0] = (u8)(0x18);

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 1;
}
#endif

#if 0
static int _emit_DMARMB(u8 *mcode_ptr)
{
	/* DMARMB (Read Memory Barrier) */
	u8 enc_bytes[1];
	u32 i;

	enc_bytes[0] = (u8)(0x12);

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr+i, enc_bytes[i]);

	return 1;
}
#endif

static int _emit_DMASEV(u8 *mcode_ptr, u8 event_num)
{
	/* DMASEV (Send Event) : 0 ~ 31 */
	u8 enc_bytes[2];
	u32 i;

	enc_bytes[0] = (u8)(0x34);
	enc_bytes[1] = (u8)((event_num<<3)|0x0);

	if (event_num > PL330_MAX_EVENT_NUM) {
		print_warning("[%s] Event number is too big ! : %d\n",
			__FUNCTION__, event_num);
		return 0;
	}

	for (i = 0; i < 2; i++)
		dma_outp8(mcode_ptr + i, enc_bytes[i]);

	return 2;
}

static int _emit_DMAWMB(u8 *mcode_ptr)
{
	/* DMAWMB (Write Memory Barrier) */
	u8 enc_bytes[1];
	u32 i;

	enc_bytes[0] = (u8)(0x13);

	for (i = 0; i < 1; i++)
		dma_outp8(mcode_ptr + i, enc_bytes[i]);

	return 1;
}

static void _emit_DMAGO_DBGINST(u32 *mcode_ptr, u8 chan_num,
			u32 buf_addr, u8 secure_bit)
{
	/* DMAGO over DBGINST[0:1] registers */
	u32 x;
	u8 uDmaGo;	/* DMAGO instruction */
	u32 mcode_u32 = (u32)mcode_ptr;

	if (chan_num > PL330_MAX_CHANNEL_NUM) {
		print_warning("[%s] Channel number is too big ! : %d\n",
			__FUNCTION__, chan_num);
		return;
	}

	do {
		x = dma_inp32(mcode_u32+PL330_DMA_DBGSTATUS);
	} while ((x&0x1) == 0x1);

	uDmaGo = (secure_bit == 0) ?
		(0xa0|(0<<1)) :	/* secure mode : M2M DMA only   */
		(0xa0|(1<<1));	/* non-secure mode : M2P/P2M DMA only */
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

	if (chan_num > PL330_MAX_CHANNEL_NUM) {
		print_warning("[%s] Channel number is too big ! : %d\n",
			__FUNCTION__, chan_num);
		return;
	}

	do {
		x = dma_inp32(mcode_u32+PL330_DMA_DBGSTATUS);
	} while ((x&0x1) == 0x1);

	/* issue instruction by channel thread */
	dma_outp32(mcode_u32+PL330_DMA_DBGINST0,
		(0<<24)|(1<<16)|(chan_num<<8)|(1<<0));
	dma_outp32(mcode_u32+PL330_DMA_DBGINST1, 0);
	/* 0 : execute the instruction that the DBGINST0,1 registers contain */
	dma_outp32(mcode_u32+PL330_DMA_DBGCMD, 0);

	do {
		x = dma_inp32(mcode_u32+PL330_DMA_DBGSTATUS);
	} while ((x&0x1) == 0x1);
}

static void _emit_DMAKILL_DGBINST_ALLCH(u32 *mcode_ptr)
{
	/* DMAKILL over DBGINST[0:1] registers - Stop a DMA controller
	   (stop all of the channels) */
	u32 x;
	u32 mcode_u32 = (u32)mcode_ptr;

	do {
		x = dma_inp32(mcode_u32+PL330_DMA_DBGSTATUS);
	} while ((x&0x1) == 0x1);

	/* issue instruction by manager thread */
	dma_outp32(mcode_u32+PL330_DMA_DBGINST0,
		(0<<24)|(1<<16)|(0<<8)|(0<<0));
	dma_outp32(mcode_u32+PL330_DMA_DBGINST1, 0);
	/* 0 : execute the instruction that the DBGINST0,1 registers contain */
	dma_outp32(mcode_u32+PL330_DMA_DBGCMD, 0);

	do {
		x = dma_inp32(mcode_u32+PL330_DMA_DBGSTATUS);
	} while ((x&0x1) == 0x1);
}

static void _DMA_GO_command(u32 *mcode_ptr, int chan_num,
		u32 buf_addr, int secure_mode)
{
	dma_debug("%s entered - channel Num=%d\n", __FUNCTION__, chan_num);
	dma_debug("mcode_ptr=0x%p, buf_addr=0x%x, secure_mode=%d\n\n",
		mcode_ptr, buf_addr, secure_mode);
	_emit_DMAGO_DBGINST(mcode_ptr, (u8)chan_num,
		buf_addr, (u8)secure_mode);
}

static void _DMA_stop_channel(u32 *mcode_ptr, int chan_num)
{
	dma_debug("%s entered - channel Num=%d\n", __FUNCTION__, chan_num);
	_emit_DMAKILL_DBGINST(mcode_ptr, (u8)chan_num);
}

static void _DMA_stop_controller(u32 *mcode_ptr)
{
	dma_debug("%s entered - mcode_ptr=0x%p\n", __FUNCTION__, mcode_ptr);
	_emit_DMAKILL_DGBINST_ALLCH(mcode_ptr);
}

static int _DMA_start_address(u8 *mcode_ptr, int st_addr)
{
	dma_debug("%s entered - start addr=0x%x\n", __FUNCTION__, st_addr);
	return _emit_DMAMOVC(mcode_ptr, 0, (u32)st_addr);
}

static int _DMA_destination_address(u8 *mcode_ptr, int st_addr)
{
	dma_debug("%s entered - destination addr=0x%x\n", __FUNCTION__, st_addr);
	return _emit_DMAMOVC(mcode_ptr, 2, (u32)st_addr);
}

static int _DMA_ccr(u8 *mcode_ptr, struct DMA_ccr dmacon)
{
	dma_debug("%s entered\n", __FUNCTION__);
	return _emit_DMAMOVC_CCR(mcode_ptr, *(u32 *)&dmacon);
}

static int _irq_to_DMA_channel(u8 *mcode_ptr, int event_num)
{
	dma_debug("%s entered - Event num : %d\n", __FUNCTION__, event_num);
	return _emit_DMASEV(mcode_ptr, (u8)event_num);
}

#ifndef USE_I2S_INTERRUPT
static int _DMA_transfer_size(u8 *mcode_ptr,
	struct DMA_parameters dma_param, int chan_num,
	struct DMA_controller *dma_ctrl)
{
	int mcode_size = 0, msize = 0;
	int lc0 = 0, lc1 = 0, lcSize = 0;
	int mLoopStart0 = 0, mLoopStart1 = 0;
	int i = 0;

	dma_debug("%s entered\n", __FUNCTION__);

	switch (dma_param.direction) {
	case PL330_M2P_DMA:
	case PL330_P2M_DMA:
		if (dma_param.trans_size > (2*1024*1024)) {
			print_warning("[%s] The chunk size is too big !: %lu\n",
				__FUNCTION__, dma_param.trans_size);
			return 0;
		}
		break;

	default:
		print_warning("[%s] Invaild DMA direction entered !\n", __FUNCTION__);
		break;
	}

	lcSize = (dma_param.ccr.src_burst_len+1) * (1<<dma_param.ccr.src_burst_size) * 2;
	/* 128byte = 4byte(32bit) * 16burst * 2times */
	lc0 = dma_param.period_bytes / lcSize;
	dma_debug("period_bytes=%d, lcSize=%d,  lc0=%d\n",
		dma_param.period_bytes, lcSize, lc0);

	lc1 = dma_param.trans_size / dma_param.period_bytes;
	dma_debug("buffer_bytes=%ld, lc1=%d\n", dma_param.trans_size, lc1);

	dma_ctrl->period_node[0].no = 0;
	dma_ctrl->period_node[0].period_bytes = dma_param.period_bytes;
	list_add_tail(&dma_ctrl->period_node[0].list,
		&dma_ctrl->period_list);
	for (i = 1; i < lc1; i++) {
		dma_ctrl->period_node[i].no = i;
		dma_ctrl->period_node[i].period_bytes = dma_param.period_bytes;
		list_add_tail(&dma_ctrl->period_node[i].list,
			&dma_ctrl->period_list);
	}

	if (lc1 > 1) {
		msize = _emit_DMALP(mcode_ptr+mcode_size, 0, lc1-1);
		mcode_size += msize;
		mLoopStart1 = mcode_size;

		msize = _emit_DMALP(mcode_ptr+mcode_size, 1, lc0-1);
		mcode_size += msize;
		mLoopStart0 = mcode_size;
	} else {
		msize = _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
		mcode_size += msize;
		mLoopStart0 = mcode_size;
	}

	switch (dma_param.direction) {
	case PL330_M2P_DMA:
		msize = _emit_DMAWFP(mcode_ptr+mcode_size,
				(u8)dma_param.peripheral);
		mcode_size += msize;
		msize = _emit_DMALD(mcode_ptr+mcode_size);
		mcode_size += msize;
		msize = _emit_DMAST(mcode_ptr+mcode_size);
		mcode_size += msize;
		msize = _emit_DMALD(mcode_ptr+mcode_size);
		mcode_size += msize;
		msize = _emit_DMASTP(mcode_ptr+mcode_size,
			(u8)dma_param.peripheral, 0);
		mcode_size += msize;
		msize = _emit_DMAWMB(mcode_ptr+mcode_size);
		mcode_size += msize;
		break;

	case PL330_P2M_DMA:
		msize = _emit_DMAWFP(mcode_ptr+mcode_size,
			(u8)dma_param.peripheral);
		mcode_size += msize;
		msize = _emit_DMALD(mcode_ptr+mcode_size);
		mcode_size += msize;
		msize = _emit_DMAST(mcode_ptr+mcode_size);
		mcode_size += msize;
		msize = _emit_DMALDP(mcode_ptr+mcode_size,
			(u8)dma_param.peripheral, 0);
		mcode_size += msize;
		msize = _emit_DMAST(mcode_ptr+mcode_size);
		mcode_size += msize;
		msize = _emit_DMAWMB(mcode_ptr+mcode_size);
		mcode_size += msize;
		break;

	default:
		print_warning("[%s] Invaild DMA direction selected !\n",
			__FUNCTION__);
		break;
	}

	if (lc1 > 1) {
		msize = _emit_DMALPEND(mcode_ptr+mcode_size, 1,
			(u8)(mcode_size-mLoopStart0));
		mcode_size += msize;

		if (dma_param.irq_enable) {
			msize = _irq_to_DMA_channel(mcode_ptr+mcode_size,
						chan_num);
			mcode_size += msize;
		}
		msize = _emit_DMALPEND(mcode_ptr+mcode_size, 0,
			(u8)(mcode_size-mLoopStart1));
		mcode_size += msize;
	} else {
		msize = _emit_DMALPEND(mcode_ptr+mcode_size, 0,
			(u8)(mcode_size-mLoopStart0));
		mcode_size += msize;

		if (dma_param.irq_enable) {
			msize = _irq_to_DMA_channel(mcode_ptr+mcode_size,
						chan_num);
			mcode_size += msize;
		}
	}

	if (dma_param.trans_size%dma_param.period_bytes) {
		lc0 = (dma_param.trans_size%dma_param.period_bytes) / lcSize;
		dma_debug("Remaining=%ld, lc0=%d\n", dma_param.trans_size, lc0);

		dma_ctrl->period_node[i].no = i;
		dma_ctrl->period_node[i].period_bytes = lc0 * lcSize;
		list_add_tail(&dma_ctrl->period_node[i].list,
			&dma_ctrl->period_list);

		msize = _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
		mcode_size += msize;
		mLoopStart0 = mcode_size;

		switch (dma_param.direction) {
		case PL330_M2P_DMA:
			msize = _emit_DMAWFP(mcode_ptr+mcode_size,
					(u8)dma_param.peripheral);
			mcode_size += msize;
			msize = _emit_DMALD(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMAST(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMALD(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMASTP(mcode_ptr+mcode_size,
					(u8)dma_param.peripheral, 0);
			mcode_size += msize;
			msize = _emit_DMAWMB(mcode_ptr+mcode_size);
			mcode_size += msize;
			break;

		case PL330_P2M_DMA:
			msize = _emit_DMAWFP(mcode_ptr+mcode_size,
					(u8)dma_param.peripheral);
			mcode_size += msize;
			msize = _emit_DMALD(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMAST(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMALDP(mcode_ptr+mcode_size,
					(u8)dma_param.peripheral, 0);
			mcode_size += msize;
			msize = _emit_DMAST(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMAWMB(mcode_ptr+mcode_size);
			mcode_size += msize;
			break;

		default:
			print_warning("[%s] Invaild DMA direction selected !\n",
				__FUNCTION__);
			break;
		}
		msize = _emit_DMALPEND(mcode_ptr+mcode_size, 0,
				(u8)(mcode_size-mLoopStart0));
		mcode_size += msize;

		if (dma_param.irq_enable) {
			msize = _irq_to_DMA_channel(mcode_ptr+mcode_size,
					chan_num);
			mcode_size += msize;
		}
	}

	if (dma_param.trans_size%lcSize)
		print_warning("%s : Buffer size is not 128 bytes units. size=%ld\n",
			PL330_SND_DMA, dma_param.trans_size);

	return mcode_size;
}
#else
static int _DMA_transfer_size(u8 *mcode_ptr,
	struct DMA_parameters dma_param, int chan_num,
	struct DMA_controller *dma_ctrl)
{
	int mcode_size = 0, msize = 0;
	int lc0 = 0, lc1 = 0, lcRemainder = 0, lcSize = 0;
	int mLoopStart0 = 0, mLoopStart1 = 0;

	dma_debug("%s entered\n", __FUNCTION__);

	switch (dma_param.direction) {
	case PL330_M2P_DMA:
	case PL330_P2M_DMA:
		if (dma_param.trans_size > (2*1024*1024)) {
			print_warning("[%s] The chunk size is too big !: %lu\n",
				__FUNCTION__, dma_param.trans_size);
			return 0;
		}
		break;

	default:
		print_warning("[%s] Invaild DMA direction entered !\n", __FUNCTION__);
		break;
	}

	lcSize = (dma_param.ccr.src_burst_len+1)*(1<<dma_param.ccr.src_burst_size)*2;

	lc0 = dma_param.trans_size/lcSize;
	lcRemainder = dma_param.trans_size - (lc0*lcSize);
	dma_debug("trans_size=%d, lcSize=%d,  lc0=%d,  lcRemainder=%d\n", dma_param.trans_size, lcSize, lc0, lcRemainder);

	if (lc0 > PL330_MAX_ITERATION_NUM) {
		lc1 = lc0/PL330_MAX_ITERATION_NUM;
		dma_debug("  Inner loop : lc1=%d\n", lc1);

		if (lc1 <= PL330_MAX_ITERATION_NUM) {
			msize = _emit_DMALP(mcode_ptr+mcode_size, 0, lc1-1);
			mcode_size += msize;
			mLoopStart1 = mcode_size;

			msize = _emit_DMALP(mcode_ptr+mcode_size, 1,
				PL330_MAX_ITERATION_NUM-1);
			mcode_size += msize;
			mLoopStart0 = mcode_size;

			switch (dma_param.direction) {
			case PL330_M2P_DMA:
				msize = _emit_DMAWFP(mcode_ptr+mcode_size,
					(u8)dma_param.peripheral);
				mcode_size += msize;
				msize = _emit_DMALD(mcode_ptr+mcode_size);
				mcode_size += msize;
				msize = _emit_DMAST(mcode_ptr+mcode_size);
				mcode_size += msize;
				msize = _emit_DMALD(mcode_ptr+mcode_size);
				mcode_size += msize;
				msize = _emit_DMASTP(mcode_ptr+mcode_size,
					(u8)dma_param.peripheral, 0);
				mcode_size += msize;
				msize = _emit_DMAWMB(mcode_ptr+mcode_size);
				mcode_size += msize;
				break;

			case PL330_P2M_DMA:
				msize = _emit_DMAWFP(mcode_ptr+mcode_size,
					(u8)dma_param.peripheral);
				mcode_size += msize;
				msize = _emit_DMALD(mcode_ptr+mcode_size);
				mcode_size += msize;
				msize = _emit_DMAST(mcode_ptr+mcode_size);
				mcode_size += msize;
				msize = _emit_DMALDP(mcode_ptr+mcode_size,
					(u8)dma_param.peripheral, 0);
				mcode_size += msize;
				msize = _emit_DMAST(mcode_ptr+mcode_size);
				mcode_size += msize;
				msize = _emit_DMAWMB(mcode_ptr+mcode_size);
				mcode_size += msize;
				break;

			default:
				print_warning("[%s] Invaild DMA direction selected !\n",
					__FUNCTION__);
				break;
			}
			msize = _emit_DMALPEND(mcode_ptr+mcode_size, 1,
				(u8)(mcode_size-mLoopStart0));
			mcode_size += msize;

			msize = _emit_DMALPEND(mcode_ptr+mcode_size, 0,
				(u8)(mcode_size-mLoopStart1));
			mcode_size += msize;

			lc0 = lc0 - (lc1*PL330_MAX_ITERATION_NUM);
		} else {
			print_warning("[%s] The transfer size is over the limit (lc1=%d)\n", __FUNCTION__, lc1);
		}
	}

	if (lc0 > 0) {
		dma_debug("Single loop : lc0=%d\n", lc0);
		msize = _emit_DMALP(mcode_ptr+mcode_size, 0, lc0-1);
		mcode_size += msize;
		mLoopStart0 = mcode_size;

		switch (dma_param.direction) {
		case PL330_M2P_DMA:
			msize = _emit_DMAWFP(mcode_ptr+mcode_size,
				(u8)dma_param.peripheral);
			mcode_size += msize;
			msize = _emit_DMALD(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMAST(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMALD(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMASTP(mcode_ptr+mcode_size,
				(u8)dma_param.peripheral, 0);
			mcode_size += msize;
			msize = _emit_DMAWMB(mcode_ptr+mcode_size);
			mcode_size += msize;
			break;

		case PL330_P2M_DMA:
			msize = _emit_DMAWFP(mcode_ptr+mcode_size,
				(u8)dma_param.peripheral);
			mcode_size += msize;
			msize = _emit_DMALD(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMAST(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMALDP(mcode_ptr+mcode_size,
				(u8)dma_param.peripheral, 0);
			mcode_size += msize;
			msize = _emit_DMAST(mcode_ptr+mcode_size);
			mcode_size += msize;
			msize = _emit_DMAWMB(mcode_ptr+mcode_size);
			mcode_size += msize;
			break;

		default:
			print_warning("[%s] Invaild DMA direction selected !\n",
				__FUNCTION__);
			break;
		}

		msize = _emit_DMALPEND(mcode_ptr+mcode_size, 0,
			(u8)(mcode_size-mLoopStart0));
		mcode_size += msize;
	}
	return mcode_size;
}
#endif

static int _DMA_set_infinite_loop(u8 *mcode_ptr, int bw_jump)
{
	dma_debug("%s entered - Backward jump offset : %d\n", __FUNCTION__, bw_jump);
	return _emit_DMALPFE(mcode_ptr, (u8)bw_jump);
}

static int _DMA_mark_end(u8 *mcode_ptr)
{
	dma_debug("%s entered\n\n", __FUNCTION__);
	return _emit_DMAEND(mcode_ptr);
}

int start_DMA_controller(void)
{
	dma_debug("%s entered\n\n", __FUNCTION__);

	pl330_base = NULL;

	if (!pl330_base)
		pl330_base = ioremap(PL330_REG_BASE, PL330_REG_SIZE);

	if (!pl330_base) {
		dma_err("%s : ioremap failed(PL330)\n", PL330_SND_DMA);
		return -ENXIO;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(start_DMA_controller);

void stop_DMA_controller(void)
{
	dma_debug("%s entered\n\n", __FUNCTION__);

	if (!pl330_base)
		return;

	_DMA_stop_controller((u32 *)((unsigned long)pl330_base));
	iounmap(pl330_base);
	pl330_base = NULL;
}
EXPORT_SYMBOL_GPL(stop_DMA_controller);

#ifndef USE_I2S_INTERRUPT
static irqreturn_t dma_irq_handler(int irq, void *data)
{
	struct DMA_controller *dma_ctrl = data;
	struct period_node *period_node;
	u32 mcode_u32 = (u32)((unsigned long)pl330_base);
	u32 x = dma_inp32(mcode_u32+PL330_DMA_INTEN);

	/*dma_debug("%s\n", __func__);*/
	if (x & (1 << dma_ctrl->chan_num))
		dma_outp32(mcode_u32+PL330_DMA_INTCLR,
			(1<<dma_ctrl->chan_num));

	if (dma_ctrl->callback) {
		period_node = list_entry(dma_ctrl->period_list.next,
			struct period_node, list);
		list_del(&period_node->list);
		/*dma_debug("[%d]:%d\n", period_node->no, period_node->period_bytes);*/
		dma_ctrl->callback(dma_ctrl->callback_param,
					period_node->period_bytes);
		list_add_tail(&period_node->list,
			&dma_ctrl->period_list);
	}

	return IRQ_HANDLED;
}
#endif

int alloc_DMA_channel(struct DMA_controller *dma_ctrl, int chan_num)
{
	int err = 0;
	int i, ch;

	if (!pl330_base) {
		err = start_DMA_controller();
		if (err < 0)
			return err;
	}

	if (chan_num >= DMA_CH_MAX) {
		dma_err("%s : illegal dma channel [ch=%d]\n", PL330_SND_DMA,
			chan_num);
		return -EINVAL;
	}

	ch = -1;
	if (chan_num == DMA_CH_AUTO) {
		for (i = 1; i < DMA_CH_MAX; i++) {
			if (!use_channles.use_ch[i]) {
				ch = i;
				break;
			}
		}
	} else {
		if (!use_channles.use_ch[chan_num])
			ch = chan_num;
	}
	if (ch < 0) {
		dma_err("%s : requested channel is in use [ch=%d]\n",
			PL330_SND_DMA, chan_num);
		return -EBUSY;
	}
	use_channles.use_ch[ch] = 1;

	dma_ctrl->status = DMA_STOP;
	dma_ctrl->chan_num = ch;
	dma_ctrl->mcode_cpu = NULL;
	dma_ctrl->mcode_bus = 0;
	dma_ctrl->mcode_cpu = dma_alloc_coherent(
		NULL, sizeof(u32)*32,
		&dma_ctrl->mcode_bus, GFP_KERNEL|GFP_DMA);
	if (!dma_ctrl->mcode_cpu) {
		use_channles.use_ch[ch] = 0;
		dma_err("%s : dma_alloc_coherent failed\n", PL330_SND_DMA);
		return -ENOMEM;
	}
#ifndef USE_I2S_INTERRUPT
	err = request_irq(dma_irq_num[dma_ctrl->chan_num],
	dma_irq_handler, 0, "pl330", dma_ctrl);
	if (err) {
		dma_err("%s : failed to request_irq(%d)\n",
			PL330_SND_DMA, dma_irq_num[dma_ctrl->chan_num]);
		dma_free_coherent(NULL, sizeof(u32)*32,
		dma_ctrl->mcode_cpu, dma_ctrl->mcode_bus);
		dma_ctrl->mcode_cpu = NULL;
		dma_ctrl->mcode_bus = 0;
		return err;
	}
#endif
	dma_debug("%s : DMA channel %d is assigned\n", PL330_SND_DMA, ch);

	return 0;
}
EXPORT_SYMBOL_GPL(alloc_DMA_channel);

void free_DMA_channel(struct DMA_controller *dma_ctrl)
{
	if (!dma_ctrl->mcode_cpu)
		return;

#ifndef USE_I2S_INTERRUPT
	free_irq(dma_irq_num[dma_ctrl->chan_num], dma_ctrl);
#endif
	dma_free_coherent(NULL, sizeof(u32)*32,
		dma_ctrl->mcode_cpu, dma_ctrl->mcode_bus);
	dma_ctrl->mcode_cpu = NULL;
	dma_ctrl->mcode_bus = 0;

	if ((dma_ctrl->chan_num > DMA_CH_AUTO) &&
	    (dma_ctrl->chan_num < DMA_CH_MAX)) {
		dma_debug("%s : DMA channel %d is released\n", PL330_SND_DMA,
			dma_ctrl->chan_num);
		use_channles.use_ch[dma_ctrl->chan_num] = 0;
	}
}
EXPORT_SYMBOL_GPL(free_DMA_channel);

int setup_DMA_channel(struct DMA_controller *dma_ctrl,
		struct DMA_parameters dma_param)
{
	int mcode_size = 0, msize = 0;
	u8 *mbuf;

	dma_debug("%s entered : Channel Num=%d\n",
			__FUNCTION__, dma_ctrl->chan_num);

	if (!dma_ctrl->mcode_cpu) {
		dma_err("%s : not dma control area\n", PL330_SND_DMA);
		return -ENOMEM;
	}
	mbuf = (u8 *)dma_ctrl->mcode_cpu;

	if (PL330_ENABLE_SECURE) {
		dma_param.ccr.src_protect = 0; /* secure mode */
		dma_param.ccr.dst_protect = 0; /* secure mode */
	} else {
		dma_param.ccr.src_protect = 2; /* non-secure mode */
		dma_param.ccr.dst_protect = 2; /* non-secure mode */
	}
	print_dma_param_info(dma_param);

	dma_ctrl->buffer_size = dma_param.trans_size;
	dma_ctrl->period_bytes = dma_param.period_bytes;
	dma_ctrl->periods = dma_param.periods;
	dma_ctrl->callback = dma_param.callback;
	dma_ctrl->callback_param = dma_param.callback_param;

	msize = _DMA_start_address(mbuf+mcode_size, dma_param.src_addr);
	mcode_size += msize;

	msize = _DMA_destination_address(mbuf+mcode_size, dma_param.dst_addr);
	mcode_size += msize;

	msize = _DMA_ccr(mbuf+mcode_size, dma_param.ccr);
	mcode_size += msize;

	msize = _emit_DMAFLUSHP(mbuf+mcode_size, (u8)dma_param.peripheral);
	mcode_size += msize;

	INIT_LIST_HEAD(&dma_ctrl->period_list);
	msize = _DMA_transfer_size(mbuf+mcode_size,
		dma_param, dma_ctrl->chan_num, dma_ctrl);
	mcode_size += msize;

#if 0
	if (dma_param.irq_enable) {
		msize = _irq_to_DMA_channel(mbuf+mcode_size,
			dma_ctrl->chan_num);
		mcode_size += msize;
	}
#endif

	if (dma_param.forever) {
		msize = _DMA_set_infinite_loop(mbuf+mcode_size,
			dma_param.bw_jump+mcode_size);
		mcode_size += msize;
	}
	if (dma_param.last_req) {
		msize = _DMA_mark_end(mbuf+mcode_size);
		mcode_size += msize;
	}
	ddmaasm(dma_ctrl->mcode_cpu);

	return mcode_size;
}
EXPORT_SYMBOL_GPL(setup_DMA_channel);

void start_DMA_channel(struct DMA_controller *dma_ctrl, int secure_mode)
{
	dma_debug("%s entered - channel Num=%d\n", __FUNCTION__, dma_ctrl->chan_num);

	if (!pl330_base || !dma_ctrl->mcode_cpu)
		return;

	if (PL330_ENABLE_SECURE)
		secure_mode = 0; /* secure mode */
	else
		secure_mode = 1; /* non-secure mode */
	if (dma_ctrl->status == DMA_STOP) {
#ifndef USE_I2S_INTERRUPT
		u32 mcode_u32 = (u32)((unsigned long)pl330_base);
		u32 x = dma_inp32(mcode_u32+PL330_DMA_INTEN);
		dma_outp32(mcode_u32+PL330_DMA_INTEN,
				(x |= (1<<dma_ctrl->chan_num)));
#endif
		dma_ctrl->offset = 0;

		_DMA_GO_command((u32 *)((unsigned long)pl330_base),
			dma_ctrl->chan_num, (u32)dma_ctrl->mcode_bus, secure_mode);
		dma_ctrl->status = DMA_START;
	}
}
EXPORT_SYMBOL_GPL(start_DMA_channel);

void stop_DMA_channel(struct DMA_controller *dma_ctrl)
{
	dma_debug("%s entered - channel Num=%d\n", __FUNCTION__, dma_ctrl->chan_num);

	if (!pl330_base && !dma_ctrl->mcode_cpu)
		return;

	if (dma_ctrl->status == DMA_START) {
#ifndef USE_I2S_INTERRUPT
		u32 mcode_u32 = (u32)((unsigned long)pl330_base);
		u32 x = dma_inp32(mcode_u32+PL330_DMA_INTEN);
		dma_outp32(mcode_u32+PL330_DMA_INTEN,
			(x &= ~(1<<dma_ctrl->chan_num)));
#endif
		dma_ctrl->offset = 0;

		_DMA_stop_channel((u32 *)((unsigned long)pl330_base),
			dma_ctrl->chan_num);
		dma_ctrl->status = DMA_STOP;
	}
}
EXPORT_SYMBOL_GPL(stop_DMA_channel);
