/*
 * linux/drivers/staging/applite/irecog/gdmac_common/include/gdmac_instructions.h
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
#ifndef __GDMAC_INSTRUCTIONS_H_
#define __GDMAC_INSTRUCTIONS_H_

#include <linux/io.h>
#include <linux/types.h>

#define GDMAC_SUCCESS 0
#define GDMAC_FAIL -1

#define GDMAC_SAR 0
#define GDMAC_CCR 1
#define GDMAC_DAR 2

#define GDMAC_SINGLE 0
#define GDMAC_BURST  1

#define GDMAC_NOT_FOREVER 0
#define GDMAC_FOREVER 1

#define GDMAC_LOOP_COUNTER0 0
#define GDMAC_LOOP_COUNTER1 1

#define GDMAC_CCR_FIXED_ADDRESS 0
#define GDMAC_CCR_INC_ADDRESS   1

#define GDMAC_CCR_NO_SWAP     0
#define GDMAC_CCR_SWAP_16BIT  1
#define GDMAC_CCR_SWAP_32BIT  2
#define GDMAC_CCR_SWAP_64BIT  3
#define GDMAC_CCR_SWAP_128BIT 4

/* for channel control register */
typedef struct {
	uint8_t src_int;
	uint8_t src_burst_size;
	uint8_t src_burst_len;
	uint8_t dst_int;
	uint8_t dst_burst_size;
	uint8_t dst_burst_len;
	uint8_t endian_swap;
} dma330_ccr;

typedef enum {
	UPDATED,
	NOT_UPDATED
} update_sar;

/* instructions */
typedef struct {
	uint8_t *inst_buf;	/* for instructions set (aligned) */
	uint8_t *inst_buf_org;	/* for instructions set (original) */
	uint32_t inst_pos;	/* current position */
	uint32_t inst_size;	/* inst_buf size */
	uint32_t *reg_buf;	/* for simple register write */
	uint32_t reg_pos;	/* current position */
	uint32_t reg_size;	/* reg_buf size */
	uint32_t *work_buf;	/* working memory */
	uint32_t work_pos;	/* working memory position */
	uint32_t work_size;	/* working memory size */
	update_sar update_sar_flg;	/* update sorce address register flag */
} gdmac_inst;

void dma330_dmaaddh(gdmac_inst *inst, uint8_t address_register, uint16_t imm);
void dma330_dmaend(gdmac_inst *inst);
void dma330_dmaflushp(gdmac_inst *inst, uint8_t peripheral);
void dma330_dmago(gdmac_inst *inst, uint8_t ns, uint8_t channel, uint32_t imm);
void dma330_dmakill(gdmac_inst *inst);
void dma330_dmald(gdmac_inst *inst, uint8_t type);
void dma330_dmaldp(gdmac_inst *inst, uint8_t type, uint8_t peripheral);
void dma330_dmalp(gdmac_inst *inst, uint8_t loop_counter_id,
		  uint16_t loop_iterations);
void dma330_dmalpend(gdmac_inst *inst, uint8_t loop_counter_id,
		     uint8_t is_forever, uint8_t type, uint8_t backwards_jump);
void dma330_dmamov(gdmac_inst *inst, uint8_t dst_reg, uint32_t imm);
void dma330_dmamov_ccr(gdmac_inst *inst, dma330_ccr *ccr);
void dma330_dmanop(gdmac_inst *inst);
void dma330_dmarmb(gdmac_inst *inst);
void dma330_dmasev(gdmac_inst *inst, uint8_t event_num);
void dma330_dmast(gdmac_inst *inst, uint8_t type);
void dma330_dmastp(gdmac_inst *inst, uint8_t type, uint8_t peripheral);
void dma330_dmastz(gdmac_inst *inst);
void dma330_dmawfe(gdmac_inst *inst, uint8_t invalid, uint8_t event_num);
void dma330_dmawfp(gdmac_inst *inst, uint8_t type, uint8_t peripheral);
void dma330_dmawmb(gdmac_inst *inst);

void gdmac_copy_word_interval(gdmac_inst *inst,
			      uint32_t src_addr,
			      uint32_t dst_addr,
			      uint16_t num_of_words_per_block,
			      uint16_t dst_addr_interval,
			      uint16_t num_of_blocks);
void gdmac_copy_word(gdmac_inst *inst,
		     uint32_t src_addr, uint32_t dst_addr, uint16_t length);
void gdmac_copy_word_over_256(gdmac_inst *inst,
			      uint32_t src_addr,
			      uint32_t dst_addr, uint32_t num_of_words);

void gdmac_write_register(gdmac_inst *inst, uint32_t dst_addr, uint32_t value);
void gdmac_write_register_halfword(gdmac_inst *inst, uint32_t dst_addr,
				   uint16_t value);

uint32_t gdmac_add_data(gdmac_inst *inst, uint32_t *data, uint32_t num_of_data);
gdmac_inst *gdmac_allocate(uint32_t inst_buf_size, uint32_t work_buf_size,
			   uint32_t reg_buf_size);
void gdmac_free(gdmac_inst *inst);
void gdmac_clear(gdmac_inst *inst);

void gdmac_exec_dmakill_master(void __iomem *reg_base);
void gdmac_exec_dmakill_slave(void __iomem *reg_base, uint8_t channel);
void gdmac_exec_instructions(void __iomem *reg_base, uint8_t channel,
			     gdmac_inst *inst, uint32_t cache_ctl);

#endif /*  __GDMAC_INSTRUCTIONS_H_ */
