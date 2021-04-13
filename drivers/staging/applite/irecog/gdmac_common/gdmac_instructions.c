/*
 * linux/drivers/staging/applite/irecog/gdmac_common/gdmac_instructions.c
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
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/io.h>

#include <linux/applite/irecog/drv_cache_ctrl_defs.h>

#include "gdmac_public.h"
#include "gdmac_instructions.h"
#include "drv_cache.h"

#define INST_BUF_ALIGN 32
#define align(addr)  (((addr) + ((INST_BUF_ALIGN)-1)) & ~((INST_BUF_ALIGN)-1))

/* instruction length (bytes) */
#define SIZE_DMAADDH   3
#define SIZE_DMAEND    1
#define SIZE_DMAFLUSHP 2
#define SIZE_DMAGO     6
#define SIZE_DMAKILL   1
#define SIZE_DMALD     1
#define SIZE_DMALDP    2
#define SIZE_DMALP     2
#define SIZE_DMALPEND  2
#define SIZE_DMAMOV    6
#define SIZE_DMANOP    1
#define SIZE_DMARMB    1
#define SIZE_DMASEV    2
#define SIZE_DMAST     1
#define SIZE_DMASTP    2
#define SIZE_DMASTZ    1
#define SIZE_DMAWFE    2
#define SIZE_DMAWFP    2
#define SIZE_DMAWMB    1

/* instruction opcode */
#define OPCODE_DMAADDH   0x54
#define OPCODE_DMAEND    0x00
#define OPCODE_DMAFLUSHP 0x35
#define OPCODE_DMAGO     0xA0
#define OPCODE_DMAKILL   0x01
#define OPCODE_DMALD     0x04
#define OPCODE_DMALDP    0x25
#define OPCODE_DMALP     0x20
#define OPCODE_DMALPEND  0x28
#define OPCODE_DMAMOV    0xBC
#define OPCODE_DMANOP    0x18
#define OPCODE_DMARMB    0x12
#define OPCODE_DMASEV    0x34
#define OPCODE_DMAST     0x08
#define OPCODE_DMASTP    0x29
#define OPCODE_DMASTZ    0x0C
#define OPCODE_DMAWFE    0x36
#define OPCODE_DMAWFP    0x30
#define OPCODE_DMAWMB    0x13

/**************************************************/
/*
 * @brief get_buf
 *
 * @param inst
 *
 * @return current buffer
 */
/**************************************************/
static inline uint8_t *get_buffer(gdmac_inst *inst)
{

	if (inst->inst_pos >= inst->inst_size) {
		pr_err("dma330 driver: buffer overflow.\n");
		return inst->inst_buf;
	}

	return inst->inst_buf + inst->inst_pos;
}

/**************************************************/
/*
 * @brief update
 *
 * @param inst
 * @param size
 */
/**************************************************/
static inline void update(gdmac_inst *inst, uint32_t size)
{
	inst->inst_pos += size;
}

/**************************************************/
/*
 * @brief add_register_value
 *
 * @param inst
 *
 * @return address
 */
/**************************************************/
static inline uint32_t *add_register_value(gdmac_inst *inst, uint32_t value)
{
	uint32_t *src;

	if (inst->reg_pos >= inst->reg_size - 1) {
		pr_err("dma330 driver: buffer overflow.\n");
		return inst->reg_buf;
	}

	src = inst->reg_buf + inst->reg_pos;
	*src = value;
	inst->reg_pos++;

	return src;
}

/**************************************************/
/*
 * @brief gdmac_allocate
 *
 * @param inst
 * @param inst_buf_size
 * @param work_buf_size
 * @param reg_buf_size
 *
 * @return gdmac_inst
 *
 */
/**************************************************/
gdmac_inst *gdmac_allocate(uint32_t inst_buf_size, uint32_t work_buf_size,
			   uint32_t reg_buf_size)
{
	gdmac_inst *inst;

	/* allocate struct */
	inst = kmalloc(sizeof(gdmac_inst), GFP_KERNEL);
	if (inst == NULL) {
		return NULL;
	}

	/* allocate instruction */
	inst->inst_buf_org =
	    kmalloc(inst_buf_size * sizeof(uint8_t) + INST_BUF_ALIGN,
		    GFP_KERNEL | GFP_DMA);
	if (inst->inst_buf_org == NULL) {
		kfree(inst);
		return NULL;
	}
	inst->inst_size = inst_buf_size;
	inst->inst_buf = (uint8_t *) align((unsigned long)inst->inst_buf_org);

	/* allocate working buffer */
	inst->work_buf =
	    kmalloc(work_buf_size * sizeof(uint32_t), GFP_KERNEL | GFP_DMA);
	if (inst->work_buf == NULL) {
		kfree(inst->inst_buf_org);
		kfree(inst);
		return NULL;
	}
	inst->work_size = work_buf_size;

	/* allocate register buffer */
	inst->reg_buf =
	    kmalloc(reg_buf_size * sizeof(uint32_t), GFP_KERNEL | GFP_DMA);
	if (inst->reg_buf == NULL) {
		kfree(inst->inst_buf_org);
		kfree(inst->work_buf);
		kfree(inst);
		return NULL;
	}
	inst->reg_size = reg_buf_size;

	gdmac_clear(inst);

	return inst;
}
EXPORT_SYMBOL(gdmac_allocate);

/**************************************************/
/*
 * @brief gdmac_free
 *
 * @param inst
 *
 */
/**************************************************/
void gdmac_free(gdmac_inst *inst)
{
	if (inst == NULL) {
		return;
	}

	if (inst->inst_buf_org != NULL) {
		kfree(inst->inst_buf_org);
	}
	if (inst->reg_buf != NULL) {
		kfree(inst->reg_buf);
	}
	if (inst->work_buf != NULL) {
		kfree(inst->work_buf);
	}

	kfree(inst);
}
EXPORT_SYMBOL(gdmac_free);

/**************************************************/
/*
 * @brief gdmac_clear
 *
 * @param inst
 *
 */
/**************************************************/
void gdmac_clear(gdmac_inst *inst)
{
	if (inst == NULL) {
		return;
	}

	inst->inst_pos = 0;
	inst->work_pos = 0;
	inst->reg_pos = 0;
	inst->update_sar_flg = UPDATED;
}
EXPORT_SYMBOL(gdmac_clear);

/**************************************************/
/*
 * @brief dma330_dmaaddh
 *
 * @param inst
 * @param addres_register
 * @param imm
 *
 */
/**************************************************/
void dma330_dmaaddh(gdmac_inst *inst, uint8_t address_register, uint16_t imm)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAADDH;

	switch (address_register) {
	case GDMAC_SAR:
		*(buf + 0) |= 0x00 << 1;	/* SAR */
		inst->update_sar_flg = UPDATED;
		break;
	case GDMAC_DAR:
		*(buf + 0) |= 0x01 << 1;	/* DAR */
		break;
	}

	*(uint16_t *) (buf + 1) = imm;

	update(inst, SIZE_DMAADDH);
}
EXPORT_SYMBOL(dma330_dmaaddh);

/**************************************************/
/*
 * @brief dma330_dmaend
 *
 * @param inst
 *
 */
/**************************************************/
void dma330_dmaend(gdmac_inst *inst)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAEND;

	update(inst, SIZE_DMAEND);
}
EXPORT_SYMBOL(dma330_dmaend);

/**************************************************/
/*
 * @brief dma330_dmaflushp
 *
 * @param inst
 * @param peripheral
 *
 */
/**************************************************/
void dma330_dmaflushp(gdmac_inst *inst, uint8_t peripheral)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAFLUSHP;
	*(buf + 1) = (peripheral & 0x1f) << 3;

	update(inst, SIZE_DMAFLUSHP);
}
EXPORT_SYMBOL(dma330_dmaflushp);

/**************************************************/
/*
 * @brief dma330_dmago
 *
 * @param inst
 * @param ns
 * @param channel
 * @param imm
 *
 */
/**************************************************/
void dma330_dmago(gdmac_inst *inst, uint8_t ns, uint8_t channel, uint32_t imm)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAGO;
	*(buf + 0) |= ((ns & 0x01) << 1);
	*(buf + 1) = channel & 0x07;

	*(uint32_t *)(buf + 2) = imm;

	update(inst, SIZE_DMAGO);
}
EXPORT_SYMBOL(dma330_dmago);

/**************************************************/
/*
 * @brief dma330_dmakill
 *
 * @param inst
 *
 */
/**************************************************/
void dma330_dmakill(gdmac_inst *inst)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAKILL;

	update(inst, SIZE_DMAKILL);
}
EXPORT_SYMBOL(dma330_dmakill);

/**************************************************/
/*
 * @brief dma330_dmald
 *
 * @param inst
 * @param type
 *
 */
/**************************************************/
void dma330_dmald(gdmac_inst *inst, uint8_t type)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMALD;

	switch (type) {
	case GDMAC_SINGLE:
		*(buf + 0) |= 0x01;
		break;
	case GDMAC_BURST:
		*(buf + 0) |= 0x03;
		break;
	default:
		break;
	}

	update(inst, SIZE_DMALD);
}
EXPORT_SYMBOL(dma330_dmald);

/**************************************************/
/*
 * @brief dma330_dmaldp
 *
 * @param inst
 * @param type
 * @param peripheral
 *
 */
/**************************************************/
void dma330_dmaldp(gdmac_inst *inst, uint8_t type, uint8_t peripheral)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMALDP;

	switch (type) {
	case GDMAC_SINGLE:
		*(buf + 0) |= 0x00;
		break;
	case GDMAC_BURST:
		*(buf + 0) |= (0x01 << 1);
		break;
	default:
		break;
	}

	*(buf + 1) = (peripheral & 0x1f) << 3;

	update(inst, SIZE_DMALDP);
}
EXPORT_SYMBOL(dma330_dmaldp);

/**************************************************/
/*
 * @brief dma330_dmalp
 *
 * @param inst
 * @param loop_counter_id
 * @param loop_iterations
 *
 */
/**************************************************/
void dma330_dmalp(gdmac_inst *inst, uint8_t loop_counter_id,
		  uint16_t loop_iterations)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMALP;
	*(buf + 0) |= ((loop_counter_id & 0x01) << 1);	/* lc */

	if (loop_iterations > 0) {
		*(buf + 1) = (loop_iterations - 1) & 0xff;
	} else {
		*(buf + 1) = 0x00;
	}

	update(inst, SIZE_DMALP);
}
EXPORT_SYMBOL(dma330_dmalp);

/**************************************************/
/*
 * @brief dma330_dmalpend
 *
 * @param inst
 * @param loop_counter_id
 * @param is_forever
 * @param type
 * @param backwards_jump
 *
 */
/**************************************************/
void dma330_dmalpend(gdmac_inst *inst, uint8_t loop_counter_id,
		     uint8_t is_forever, uint8_t type, uint8_t backwards_jump)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMALPEND;
	*(buf + 0) |= ((loop_counter_id & 0x01) << 2);	/*lc */

	if (is_forever != GDMAC_FOREVER) {
		*(buf + 0) |= (0x01 << 4);	/* nf */
	}

	/* bs */
	switch (type) {
	case GDMAC_SINGLE:
		*(buf + 0) |= 0x01;
		break;
	case GDMAC_BURST:
		*(buf + 0) |= 0x03;
		break;
	default:
		break;
	}

	*(buf + 1) = backwards_jump;

	update(inst, SIZE_DMALPEND);
}
EXPORT_SYMBOL(dma330_dmalpend);

/**************************************************/
/*
 * @brief dma330_dmamov
 *
 * @param inst
 * @param dst_reg
 * @param imm
 *
 */
/**************************************************/
void dma330_dmamov(gdmac_inst *inst, uint8_t dst_reg, uint32_t imm)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAMOV;

	/* rd */
	switch (dst_reg) {
	case GDMAC_SAR:
		*(buf + 1) = 0x00;	/* SAR */
		inst->update_sar_flg = UPDATED;
		break;
	case GDMAC_CCR:
		*(buf + 1) = 0x01;	/* CCR */
		break;
	case GDMAC_DAR:
		*(buf + 1) = 0x02;	/* DAR */
		break;
	default:
		*(buf + 1) = 0x00;
		break;
	}

	*(uint32_t *)(get_buffer(inst) + 2) = imm;

	update(inst, SIZE_DMAMOV);
}
EXPORT_SYMBOL(dma330_dmamov);

/**************************************************/
/*
 * @brief get_burst_size
 *
 * @param size
 *
 * @return burst size
 *
 */
/**************************************************/
static inline uint8_t get_burst_size(int size)
{
	uint8_t ret = 0;
	switch (size) {
	case 1:
		ret = 0x00;
		break;
	case 2:
		ret = 0x01;
		break;
	case 4:
		ret = 0x02;
		break;
	case 8:
		ret = 0x03;
		break;
	case 16:
		ret = 0x04;
		break;
	default:
		break;
	}
	return ret;
}

/**************************************************/
/*
 * @brief dma330_dmamov_ccr
 *
 * @param inst
 * @param ccr
 *
 */
/**************************************************/
void dma330_dmamov_ccr(gdmac_inst *inst, dma330_ccr *ccr)
{
	uint8_t *buf = get_buffer(inst);

	uint32_t val = 0x00000000;
	uint8_t endian = 0x00;

	*(buf + 0) = OPCODE_DMAMOV;
	*(buf + 1) = 0x01;	/* CCR */

	/* source */
	if (ccr->src_int == GDMAC_CCR_INC_ADDRESS) {
		val |= 0x01;
	}
	val |= (get_burst_size(ccr->src_burst_size) & 0x07) << 1;
	val |= ((ccr->src_burst_len - 1) & 0x0f) << 4;

	/* destination */
	if (ccr->dst_int == GDMAC_CCR_INC_ADDRESS) {
		val |= 0x01 << 14;
	}
	val |= (get_burst_size(ccr->dst_burst_size) & 0x07) << 15;
	val |= ((ccr->dst_burst_len - 1) & 0x0f) << 18;

	/* endian swap */
	switch (ccr->endian_swap) {
	case GDMAC_CCR_NO_SWAP:
		endian = 0x00;
		break;
	case GDMAC_CCR_SWAP_16BIT:
		endian = 0x01;
		break;
	case GDMAC_CCR_SWAP_32BIT:
		endian = 0x02;
		break;
	case GDMAC_CCR_SWAP_64BIT:
		endian = 0x03;
		break;
	case GDMAC_CCR_SWAP_128BIT:
		endian = 0x04;
		break;
	default:
		endian = 0x00;
		break;
	}
	val |= endian << 28;

	*(uint32_t *)(buf + 2) = val;

	update(inst, SIZE_DMAMOV);
}
EXPORT_SYMBOL(dma330_dmamov_ccr);

/**************************************************/
/*
 * @brief dma330_dmanop
 *
 * @param inst
 *
 */
/**************************************************/
void dma330_dmanop(gdmac_inst *inst)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMANOP;

	update(inst, SIZE_DMANOP);
}
EXPORT_SYMBOL(dma330_dmanop);

/**************************************************/
/*
 * @brief dma330_dmarmb
 *
 * @param inst
 *
 */
/**************************************************/
void dma330_dmarmb(gdmac_inst *inst)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMARMB;

	update(inst, SIZE_DMARMB);
}
EXPORT_SYMBOL(dma330_dmarmb);

/**************************************************/
/*
 * @brief dma330_dmasev
 *
 * @param inst
 * @param event_num
 *
 */
/**************************************************/
void dma330_dmasev(gdmac_inst *inst, uint8_t event_num)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMASEV;
	*(buf + 1) = (event_num & 0x1f) << 3;

	update(inst, SIZE_DMASEV);
}
EXPORT_SYMBOL(dma330_dmasev);

/**************************************************/
/*
 * @brief dma330_dmast
 *
 * @param inst
 * @param type
 *
 */
/**************************************************/
void dma330_dmast(gdmac_inst *inst, uint8_t type)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAST;

	switch (type) {
	case GDMAC_SINGLE:
		*(buf + 0) |= 0x01;
		break;
	case GDMAC_BURST:
		*(buf + 0) |= 0x03;
		break;
	default:
		break;
	}

	update(inst, SIZE_DMAST);
}
EXPORT_SYMBOL(dma330_dmast);

/**************************************************/
/*
 * @brief dma330_dmastp
 *
 * @param inst
 * @param type
 * @param peripheral
 *
 */
/**************************************************/
void dma330_dmastp(gdmac_inst *inst, uint8_t type, uint8_t peripheral)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMASTP;

	switch (type) {
	case GDMAC_SINGLE:
		*(buf + 0) |= (0x00 << 1);
		break;
	case GDMAC_BURST:
		*(buf + 0) |= (0x01 << 1);
		break;
	default:
		break;
	}

	*(buf + 1) = (peripheral & 0x1f) << 3;

	update(inst, SIZE_DMASTP);
}
EXPORT_SYMBOL(dma330_dmastp);

/**************************************************/
/*
 * @brief dma330_dmastz
 *
 * @param inst
 *
 */
/**************************************************/
void dma330_dmastz(gdmac_inst *inst)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMASTZ;

	update(inst, SIZE_DMASTZ);
}
EXPORT_SYMBOL(dma330_dmastz);

/**************************************************/
/*
 * @brief dma330_dmawfe
 *
 * @param inst
 * @param invalid
 * @param event_num
 *
 */
/**************************************************/
void dma330_dmawfe(gdmac_inst *inst, uint8_t invalid, uint8_t event_num)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAWFE;

	*(buf + 1) = (event_num & 0x1f) << 3;
	*(buf + 1) |= ((invalid & 0x01) << 1);

	update(inst, SIZE_DMAWFE);
}
EXPORT_SYMBOL(dma330_dmawfe);

/**************************************************/
/*
 * @brief dma330_dmawfp
 *
 * @param inst
 * @param type
 * @param peripheral
 *
 */
/**************************************************/
void dma330_dmawfp(gdmac_inst *inst, uint8_t type, uint8_t peripheral)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAWFP;

	switch (type) {
	case GDMAC_SINGLE:
		*(buf + 0) |= 0x00;
		break;
	case GDMAC_BURST:
		*(buf + 0) |= 0x02;
		break;
	default:
		break;
	}

	*(buf + 1) = (peripheral & 0x1f) << 3;

	update(inst, SIZE_DMAWFP);
}
EXPORT_SYMBOL(dma330_dmawfp);

/**************************************************/
/*
 * @brief dma330_wmawmb
 *
 * @param buf
 *
 */
/**************************************************/
void dma330_dmawmb(gdmac_inst *inst)
{
	uint8_t *buf = get_buffer(inst);

	*(buf + 0) = OPCODE_DMAWMB;

	update(inst, SIZE_DMAWMB);
}
EXPORT_SYMBOL(dma330_dmawmb);

/**************************************************/
/*
 * @brief gdmac_copy_word_over_256
 *
 * @param inst
 * @param src_addr (physical address)
 * @param dst_addr (physical address)
 * @param num_of_words
 *
 */
/**************************************************/
void gdmac_copy_word_over_256(gdmac_inst *inst, uint32_t src_addr,
			      uint32_t dst_addr, uint32_t num_of_words)
{
	dma330_ccr ccr;
	uint16_t c0, c1;
	uint16_t remain;

	ccr.src_int = GDMAC_CCR_INC_ADDRESS;
	ccr.src_burst_size = 4;	/* word */
	ccr.src_burst_len = 1;	/* burst len:1  */
	ccr.dst_int = GDMAC_CCR_INC_ADDRESS;
	ccr.dst_burst_size = 4;	/* word */
	ccr.dst_burst_len = 1;	/* burst len:1 */
	ccr.endian_swap = GDMAC_CCR_NO_SWAP;

	/* set source and destination address */
	dma330_dmamov(inst, GDMAC_SAR, src_addr);
	dma330_dmamov(inst, GDMAC_DAR, dst_addr);
	dma330_dmamov_ccr(inst, &ccr);

	if (num_of_words > 256) {
		c0 = 256;
		c1 = num_of_words / 256;
		remain = num_of_words - c1 * 256;
	} else {
		c0 = num_of_words;
		c1 = 0;
		remain = 0;
	}

	if (c1 > 0) {
		dma330_dmalp(inst, GDMAC_LOOP_COUNTER1, c1);
	}

	dma330_dmalp(inst, GDMAC_LOOP_COUNTER0, c0);
	dma330_dmald(inst, GDMAC_SINGLE);
	dma330_dmast(inst, GDMAC_SINGLE);
	dma330_dmawmb(inst);
	dma330_dmalpend(inst, GDMAC_LOOP_COUNTER0, GDMAC_NOT_FOREVER,
			GDMAC_SINGLE, SIZE_DMALD + SIZE_DMAST + SIZE_DMAWMB);

	if (c1 > 0) {
		dma330_dmalpend(inst, GDMAC_LOOP_COUNTER1, GDMAC_NOT_FOREVER,
				GDMAC_SINGLE,
				SIZE_DMALP + SIZE_DMALD + SIZE_DMAST +
				SIZE_DMAWMB + SIZE_DMALPEND);
	}

	if (remain > 0) {
		dma330_dmalp(inst, GDMAC_LOOP_COUNTER0, remain);
		dma330_dmald(inst, GDMAC_SINGLE);
		dma330_dmast(inst, GDMAC_SINGLE);
		dma330_dmawmb(inst);
		dma330_dmalpend(inst, GDMAC_LOOP_COUNTER0, GDMAC_NOT_FOREVER,
				GDMAC_SINGLE,
				SIZE_DMALD + SIZE_DMAST + SIZE_DMAWMB);
	}
}
EXPORT_SYMBOL(gdmac_copy_word_over_256);

/**************************************************/
/*
 * @brief gdmac_copy_word
 *
 * @param inst
 * @param src_addr (physical address)
 * @param dst_addr (physical address)
 * @param num_of_words
 *
 */
/**************************************************/
void gdmac_copy_word(gdmac_inst *inst, uint32_t src_addr, uint32_t dst_addr,
		     uint16_t num_of_words)
{
	dma330_ccr ccr;

	ccr.src_int = GDMAC_CCR_INC_ADDRESS;
	ccr.src_burst_size = 4;	/* word */
	ccr.src_burst_len = 1;	/* burst len:1  */
	ccr.dst_int = GDMAC_CCR_INC_ADDRESS;
	ccr.dst_burst_size = 4;	/* word */
	ccr.dst_burst_len = 1;	/* burst len:1 */
	ccr.endian_swap = GDMAC_CCR_NO_SWAP;

	/* set source and destination address */
	dma330_dmamov(inst, GDMAC_SAR, src_addr);
	dma330_dmamov(inst, GDMAC_DAR, dst_addr);
	dma330_dmamov_ccr(inst, &ccr);

	dma330_dmalp(inst, GDMAC_LOOP_COUNTER0, num_of_words);

	dma330_dmald(inst, GDMAC_SINGLE);
	dma330_dmast(inst, GDMAC_SINGLE);
	dma330_dmawmb(inst);

	dma330_dmalpend(inst,
			GDMAC_LOOP_COUNTER0,
			GDMAC_NOT_FOREVER,
			GDMAC_SINGLE, SIZE_DMALD + SIZE_DMAST + SIZE_DMAWMB);

}
EXPORT_SYMBOL(gdmac_copy_word);

/**************************************************/
/*
 * @brief gdmac_copy_word_interval
 *
 * @param inst
 * @param src_addr (physical address)
 * @param dst_addr (physical address)
 * @param num_of_words_per_block
 * @param dst_addr_interval
 * @param num_of_blocks
 *
 */
/**************************************************/
void gdmac_copy_word_interval(gdmac_inst *inst,
			      uint32_t src_addr,
			      uint32_t dst_addr,
			      uint16_t num_of_words_per_block,
			      uint16_t dst_addr_interval,
			      uint16_t num_of_blocks)
{
	dma330_ccr ccr;

	ccr.src_int = GDMAC_CCR_INC_ADDRESS;
	ccr.src_burst_size = 4;	/* word */
	ccr.src_burst_len = 1;	/* burst len:1  */
	ccr.dst_int = GDMAC_CCR_INC_ADDRESS;
	ccr.dst_burst_size = 4;	/* word */
	ccr.dst_burst_len = 1;	/* burst len:1 */
	ccr.endian_swap = GDMAC_CCR_NO_SWAP;

	/* set source and destination address */
	dma330_dmamov(inst, GDMAC_SAR, src_addr);
	dma330_dmamov(inst, GDMAC_DAR, dst_addr);
	dma330_dmamov_ccr(inst, &ccr);

	dma330_dmalp(inst, GDMAC_LOOP_COUNTER1, num_of_blocks);

	dma330_dmalp(inst, GDMAC_LOOP_COUNTER0, num_of_words_per_block);
	dma330_dmald(inst, GDMAC_SINGLE);
	dma330_dmast(inst, GDMAC_SINGLE);
	dma330_dmawmb(inst);
	dma330_dmalpend(inst, GDMAC_LOOP_COUNTER0, GDMAC_NOT_FOREVER,
			GDMAC_SINGLE, SIZE_DMALD + SIZE_DMAST + SIZE_DMAWMB);

	dma330_dmaaddh(inst, GDMAC_DAR,
		       dst_addr_interval - num_of_words_per_block * 0x4);

	dma330_dmalpend(inst, GDMAC_LOOP_COUNTER1, GDMAC_NOT_FOREVER,
			GDMAC_SINGLE,
			SIZE_DMALP + SIZE_DMALD + SIZE_DMAST + SIZE_DMAWMB +
			SIZE_DMAADDH + SIZE_DMALPEND);

}
EXPORT_SYMBOL(gdmac_copy_word_interval);

/**************************************************/
/*
 * @brief gdmac_write_register_sar
 *
 * @param inst
 * @param dst_addr (physical address)
 * @param value
 *
 */
/**************************************************/
static void gdmac_write_register_sar(gdmac_inst *inst, uint32_t dst_addr,
				     uint32_t value)
{
	dma330_ccr ccr;
	uint32_t *src = add_register_value(inst, value);

	ccr.src_int = GDMAC_CCR_INC_ADDRESS;
	ccr.src_burst_size = 4;	/* word */
	ccr.src_burst_len = 1;	/* burst len:1  */
	ccr.dst_int = GDMAC_CCR_INC_ADDRESS;
	ccr.dst_burst_size = 4;	/* word */
	ccr.dst_burst_len = 1;	/* burst len:1 */
	ccr.endian_swap = GDMAC_CCR_NO_SWAP;

	/* set source and destination address */
	dma330_dmamov(inst, GDMAC_SAR, virt_to_phys(src));
	dma330_dmamov(inst, GDMAC_DAR, dst_addr);
	dma330_dmamov_ccr(inst, &ccr);

	dma330_dmald(inst, GDMAC_SINGLE);
	dma330_dmast(inst, GDMAC_SINGLE);
	dma330_dmawmb(inst);
}
EXPORT_SYMBOL(gdmac_write_register_sar);

/**************************************************/
/*
 * @brief gdmac_write_register_sar
 *
 * @param inst
 * @param dst_addr (physical address)
 * @param value
 *
 */
/**************************************************/
void gdmac_write_register_halfword(gdmac_inst *inst, uint32_t dst_addr,
				   uint16_t value)
{
	dma330_ccr ccr;
	uint32_t *src = add_register_value(inst, (uint32_t)value);

	ccr.src_int = GDMAC_CCR_INC_ADDRESS;
	ccr.src_burst_size = 2;	/* half word */
	ccr.src_burst_len = 1;	/* burst len:1  */
	ccr.dst_int = GDMAC_CCR_INC_ADDRESS;
	ccr.dst_burst_size = 2;	/* half word */
	ccr.dst_burst_len = 1;	/* burst len:1 */
	ccr.endian_swap = GDMAC_CCR_NO_SWAP;

	/* set source and destination address */
	dma330_dmamov(inst, GDMAC_SAR, virt_to_phys(src));
	dma330_dmamov(inst, GDMAC_DAR, dst_addr);
	dma330_dmamov_ccr(inst, &ccr);

	dma330_dmald(inst, GDMAC_SINGLE);
	dma330_dmast(inst, GDMAC_SINGLE);
	dma330_dmawmb(inst);
}
EXPORT_SYMBOL(gdmac_write_register_halfword);

/**************************************************/
/*
 * @brief gdmac_write_register
 *
 * @param inst
 * @param dst_addr (physical address)
 * @param value
 *
 */
/**************************************************/
void gdmac_write_register(gdmac_inst *inst, uint32_t dst_addr, uint32_t value)
{
	if (inst->update_sar_flg == UPDATED) {
		gdmac_write_register_sar(inst, dst_addr, value);
		inst->update_sar_flg = NOT_UPDATED;

	} else {
		add_register_value(inst, value);
		dma330_dmamov(inst, GDMAC_DAR, dst_addr);
		dma330_dmald(inst, GDMAC_SINGLE);
		dma330_dmast(inst, GDMAC_SINGLE);
		dma330_dmawmb(inst);
	}
}
EXPORT_SYMBOL(gdmac_write_register);

/**************************************************/
/*
 * @brief gdmac_exec_dmakill_master
 *
 * @param reg_base
 *
 */
/**************************************************/
void gdmac_exec_dmakill_master(void __iomem *reg_base)
{
	iowrite32(0x00010000, reg_base + DMA330_DBGINST0);	/* set instruction */
	iowrite32(0x00, reg_base + DMA330_DBGCMD);	/* execute */
}
EXPORT_SYMBOL(gdmac_exec_dmakill_master);

/**************************************************/
/*
 * @brief gdmac_exec_dmakill_slave
 *
 * @param reg_base
 * @param channel
 *
 */
/**************************************************/
void gdmac_exec_dmakill_slave(void __iomem *reg_base, uint8_t channel)
{
	/* DMAKILL ch0 */
	unsigned long val = 0x00010000 | ((channel & 0x07) << 8) | 0x01;

	iowrite32(val, reg_base + DMA330_DBGINST0);	/* set instruction */
	iowrite32(0x00, reg_base + DMA330_DBGCMD);	/* execute */
}
EXPORT_SYMBOL(gdmac_exec_dmakill_slave);

/**************************************************/
/*
 * @brief gdmac_exec_dmakill_slave
 *
 * @param reg_base
 * @param channel
 * @param inst
 *
 */
/**************************************************/
void gdmac_exec_instructions(void __iomem *reg_base, uint8_t channel,
			     gdmac_inst *inst, uint32_t cache_ctl)
{
	unsigned long val =
	    0x00a00000 | ((channel & 0x07) << 24) | ((channel & 0x07) << 8);

	/* cache flush */
	if (!(cache_ctl & DRV_CACHE_FLUSH_ALL)) {
		drv_cache_flush(virt_to_phys(inst->inst_buf), inst->inst_size);
		drv_cache_flush(virt_to_phys(inst->work_buf), inst->work_size);
		drv_cache_flush(virt_to_phys(inst->reg_buf), inst->reg_size);
	}

	iowrite32(val, reg_base + DMA330_DBGINST0);	/* set instruction */
	iowrite32(virt_to_phys(inst->inst_buf), reg_base + DMA330_DBGINST1);	/* set instruction */
	iowrite32(0x00, reg_base + DMA330_DBGCMD);	/* execute */
}
EXPORT_SYMBOL(gdmac_exec_instructions);

/**************************************************/
/*
 * @brief gdmac_add_data
 *
 * @param inst
 * @param data
 * @param num_of_data
 *
 * @return physical address
 *
 */
/**************************************************/
uint32_t gdmac_add_data(gdmac_inst *inst, uint32_t *data, uint32_t num_of_data)
{
	uint32_t *buf;
	int i;

	if (inst->work_pos >= inst->work_size - num_of_data) {
		pr_err("dma330 driver: buffer overflow.\n");
		return (uint32_t)inst->work_buf;
	}

	buf = inst->work_buf + inst->work_pos;
	for (i = 0; i < num_of_data; i++) {
		*(buf + i) = *(data + i);
	}
	inst->work_pos += num_of_data;

	return (uint32_t)virt_to_phys(buf);
}
EXPORT_SYMBOL(gdmac_add_data);
