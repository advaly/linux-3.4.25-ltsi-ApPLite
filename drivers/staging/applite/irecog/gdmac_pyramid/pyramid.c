/*
 * linux/drivers/staging/applite/irecog/gdmac_pyramid/pyramid.c
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
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#include <mach/regs/irecog_offs_def.h>
#include <mach/regs/irecog_reg_def.h>

#include "pyramid_tap_coeff.h"
#include "pyramid.h"
#include "gdmac_port_def.h"
#include "drv_defs.h"
#include "drv_cache.h"
#include "gdmac_pyramid_driver.h"

#define ENABLE 0
#define DISABLE -1

static unsigned long reduction_ratio[MAX_ROUTE] = {
	0x00013068,
	0x00016A08,
	0x0001AE88,
	0x00020000
};

/* tap coeff table */
static unsigned long *table_adr[MAX_TABLE_NUM];

static int output_w_size[GDMAC_PYRAMID_OUT_NUM] = {
	GDMAC_PYRAMID_OUT0_W,
	GDMAC_PYRAMID_OUT1_W,
	GDMAC_PYRAMID_OUT2_W,
	GDMAC_PYRAMID_OUT3_W,
	GDMAC_PYRAMID_OUT4_W,
	GDMAC_PYRAMID_OUT5_W,
	GDMAC_PYRAMID_OUT6_W,
	GDMAC_PYRAMID_OUT7_W,
	GDMAC_PYRAMID_OUT8_W,
	GDMAC_PYRAMID_OUT9_W,
	GDMAC_PYRAMID_OUT10_W,
	GDMAC_PYRAMID_OUT11_W
};

static int output_h_size[GDMAC_PYRAMID_OUT_NUM] = {
	GDMAC_PYRAMID_OUT0_H,
	GDMAC_PYRAMID_OUT1_H,
	GDMAC_PYRAMID_OUT2_H,
	GDMAC_PYRAMID_OUT3_H,
	GDMAC_PYRAMID_OUT4_H,
	GDMAC_PYRAMID_OUT5_H,
	GDMAC_PYRAMID_OUT6_H,
	GDMAC_PYRAMID_OUT7_H,
	GDMAC_PYRAMID_OUT8_H,
	GDMAC_PYRAMID_OUT9_H,
	GDMAC_PYRAMID_OUT10_H,
	GDMAC_PYRAMID_OUT11_H
};

/**************************************************/
/*
 * @brief pyramid_cache_flush
 *
 * @param pyramid
 *
 */
/**************************************************/
void pyramid_cache_flush(gdmac_pyramid *pyramid)
{
	int i;

	if ((pyramid->p_clr_sel == P_CLR_SEL_Y)
	    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {
		drv_cache_flush(pyramid->input.y_adr,
				pyramid->input.y_pitch * GDMAC_PYRAMID_IN_H);
	}

	if ((pyramid->p_clr_sel == P_CLR_SEL_CBCR)
	    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {
		drv_cache_flush(pyramid->input.cb_adr,
				pyramid->input.cb_pitch * GDMAC_PYRAMID_IN_H);
		drv_cache_flush(pyramid->input.cr_adr,
				pyramid->input.cr_pitch * GDMAC_PYRAMID_IN_H);
	}

	for (i = 0; i < MAX_TABLE_NUM; i++) {
		drv_cache_flush(virt_to_phys(table_adr[i]), TAP_TABLE_SIZE * 4);
	}
}

/**************************************************/
/*
 * @brief pyramid_cache_invalidate
 *
 * @param pyramid
 *
 */
/**************************************************/
void pyramid_cache_invalidate(gdmac_pyramid *pyramid)
{
	int i;

	/* Y check */
	if ((pyramid->p_clr_sel == P_CLR_SEL_Y)
	    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {
		for (i = 0; i < GDMAC_PYRAMID_OUT_NUM; i++) {
			drv_cache_invalidate(pyramid->output[i].y_adr,
					     pyramid->output[i].y_pitch *
					     output_h_size[i]);
		}
	}

	/* Cb/Cr check */
	if ((pyramid->p_clr_sel == P_CLR_SEL_CBCR)
	    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {
		for (i = 0; i < GDMAC_PYRAMID_OUT_NUM; i++) {
			drv_cache_invalidate(pyramid->output[i].cb_adr,
					     pyramid->output[i].cb_pitch *
					     output_h_size[i]);
			drv_cache_invalidate(pyramid->output[i].cr_adr,
					     pyramid->output[i].cr_pitch *
					     output_h_size[i]);
		}
	}
}

/**************************************************/
/*
 * @brief rscaler_image_size_setting
 *
 * @param inst
 * @param p_clr_sel
 * @param input_w_size
 * @param input_h_size
 * @param out_index
 *
 */
/**************************************************/
static void rscaler_image_size_setting(gdmac_inst *inst,
				       unsigned char p_clr_sel,
				       unsigned int input_w_size,
				       unsigned int input_h_size, int out_index)
{
	int i;
	int c = 0;
	uint32_t buf[12];
	unsigned long rscaler_base =
	    PYRAMID_BASE + IRECOG_rpyramid_RSCALER_CS_START_OFFS;

	/* RSCALER_CS_YHVSIN */
	if ((p_clr_sel == P_CLR_SEL_Y) || (p_clr_sel == P_CLR_SEL_YCBCR)) {
		buf[c++] =
		    ((input_w_size & 0x07FF) << 16) | (input_h_size & 0x07FF);
	} else {
		buf[c++] = 0x00000000;
	}

	/* RSCALER_CS_CHVSIN */
	if ((p_clr_sel == P_CLR_SEL_CBCR) || (p_clr_sel == P_CLR_SEL_YCBCR)) {
		buf[c++] =
		    ((input_w_size & 0x07FF) << 16) | (input_h_size & 0x07FF);
	} else {
		buf[c++] = 0x00000000;
	}

	for (i = 0; i < 4; i++) {
		/* Y */
		if ((p_clr_sel == P_CLR_SEL_Y)
		    || (p_clr_sel == P_CLR_SEL_YCBCR)) {
			buf[c++] =
			    ((output_w_size[out_index + i] & 0x07FF) << 16) |
			    (output_h_size[out_index + i] & 0x07FF);
		} else {
			buf[c++] = 0x00000000;
		}
		/* Cb, Cr */
		if ((p_clr_sel == P_CLR_SEL_CBCR)
		    || (p_clr_sel == P_CLR_SEL_YCBCR)) {
			buf[c++] =
			    ((output_w_size[out_index + i] & 0x07FF) << 16) |
			    (output_h_size[out_index + i] & 0x07FF);
		} else {
			buf[c++] = 0x00000000;
		}
	}

	gdmac_copy_word(inst, gdmac_add_data(inst, buf, c),
			rscaler_base +
			RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_YHVSIN_OFFS),
			c);
}

/**************************************************/
/*
 * @brief rscaler_filmode_setting
 *
 * @param inst
 * @param fil_mode
 *
 */
/**************************************************/
static void rscaler_filmode_setting(gdmac_inst *inst, unsigned char fil_mode)
{
	int i;
	int c = 0;
	uint32_t buf[3 * 4];
	unsigned long rscaler_base =
	    PYRAMID_BASE + IRECOG_rpyramid_RSCALER_CS_START_OFFS;

	for (i = 0; i < 4; i++) {
		buf[c++] = fil_mode & 0x07;
		buf[c++] = 0x00000000;
		buf[c++] = 0x00000000;
	}

	gdmac_copy_word_interval(inst,
				 gdmac_add_data(inst, buf, c),
				 rscaler_base +
				 RSCALER_OFFSET
				 (IRECOG_rpyramid_RSCALER_CS_YHFILMODE_OFFS), 3,
				 0x20, 4);
}

/**************************************************/
/*
 * @brief rscaler_filbase_setting
 *
 * @param inst
 * @param id
 * @param fil_mode
 * @param reg_offset
 *
 */
/**************************************************/
static void rscaler_filbase_setting(gdmac_inst *inst)
{
	int i, j;
	int c = 0;
	uint32_t buf[2 * 16];
	unsigned long rscaler_base =
	    PYRAMID_BASE + IRECOG_rpyramid_RSCALER_CS_START_OFFS;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			/*      buf[c++] = reduction_ratio[i] << 3; */
			buf[c++] = reduction_ratio[i];
			buf[c++] = 0x00000000;
		}
	}

	gdmac_copy_word_interval(inst,
				 gdmac_add_data(inst, buf, c),
				 rscaler_base +
				 RSCALER_OFFSET
				 (IRECOG_rpyramid_RSCALER_CS_YH1FILBASE_OFFS),
				 2, 0x20, 16);
}

/**************************************************/
/*
 * @brief rscaler_setting
 *
 * @param inst
 * @param pyramid
 *
 */
/**************************************************/
static void rscaler_setting(gdmac_inst *inst, gdmac_pyramid *pyramid)
{
	int i;
	int c = 0;
	uint32_t buf[8];
	unsigned long rscaler_base =
	    PYRAMID_BASE + IRECOG_rpyramid_RSCALER_CS_START_OFFS;
	unsigned long mode;

	switch (pyramid->p_clr_sel) {
	case P_CLR_SEL_Y:
		mode = (0x1 << 27) | (0x1 << 24) | (0x1 << 21) | (0x1 << 18);
		break;

	case P_CLR_SEL_CBCR:
		mode = (0x3 << 25) | (0x3 << 22) | (0x3 << 19) | (0x3 << 16);
		break;

	case P_CLR_SEL_YCBCR:
		mode = (0x7 << 25) | (0x7 << 22) | (0x7 << 19) | (0x7 << 16);
		break;

	default:
		mode = 0x00000000;
		break;
	}

	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_MODE_OFFS), mode);
	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_OAINSET_OFFS),
			     0x00000000);

	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_YHFILPSMODE_OFFS),
			     0x00000000);
	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_YVFILPSMODE_OFFS),
			     0x00000000);
	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_CHFILPSMODE_OFFS),
			     0x00000000);
	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_CVFILPSMODE_OFFS),
			     0x00000000);

	rscaler_image_size_setting(inst, pyramid->p_clr_sel, GDMAC_PYRAMID_IN_W,
				   GDMAC_PYRAMID_IN_H, 0);

	for (i = 0; i < 4; i++) {
		buf[c++] = 0x00000000;
	}
	gdmac_copy_word(inst, gdmac_add_data(inst, buf, c),
			rscaler_base +
			RSCALER_OFFSET
			(IRECOG_rpyramid_RSCALER_CS_OAOUTSET1_OFFS), c);

	rscaler_filmode_setting(inst, pyramid->fil_mode);
	rscaler_filbase_setting(inst);
}

/**************************************************/
/*
 * @brief rvdmac_clear_status
 *
 * @param inst
 *
 */
/**************************************************/
static void rvdmac_clear_status(gdmac_inst *inst)
{
	unsigned long rvdmac_base =
	    PYRAMID_BASE + IRECOG_rpyramid_PYM_STADR_OFFS;
	int c = 0;
	uint32_t buf[4];

	buf[c++] = 0x00000003;	/* PYM_STATUS 0x0E00 */
	buf[c++] = 0x00018001;	/* PYM_INT    0x0E04 */
	buf[c++] = 0x00000007;	/* PYM_R_STOP 0x0E10 */
	buf[c++] = 0x00000FFF;	/* PYM_W_STOP 0x0E14 */

	gdmac_copy_word_interval(inst,
				 gdmac_add_data(inst, buf, c),
				 rvdmac_base + IRECOG_rpyramid_PYM_STATUS_OFFS,
				 2, 0x10, 2);
}

/**************************************************/
/*
 * @brief rvdmac_port_enable
 *
 * @param inst
 * @param pyramid
 * @param table_port_enable
 *
 */
/**************************************************/
static void rvdmac_port_enable(gdmac_inst *inst, gdmac_pyramid *pyramid,
			       int table_port_enable)
{
	int c = 0;
	uint32_t buf[4];
	unsigned long rvdmac_base =
	    PYRAMID_BASE + IRECOG_rpyramid_PYM_STADR_OFFS;

	switch (pyramid->p_clr_sel) {
	case P_CLR_SEL_Y:
		buf[c++] = (0x1 << 0);	/* PYM_R_ENABLE */
		buf[c++] = (0xf << 0);	/* PYM_W_ENABLE */
		break;

	case P_CLR_SEL_CBCR:
		buf[c++] = ((0x1 << 1) | (0x1 << 2));	/* PYM_R_ENABLE */
		buf[c++] = ((0xf << 4) | (0xf << 8));	/* PYM_W_ENABLE */
		break;

	case P_CLR_SEL_YCBCR:
		buf[c++] = ((0x1 << 0) | (0x1 << 1) | (0x1 << 2));	/* PYM_R_ENABLE */
		buf[c++] = ((0xf << 0) | (0xf << 4) | (0xf << 8));	/* PYM_W_ENABLE */
		break;

	default:
		buf[c++] = 0x00000000;
		buf[c++] = 0x00000000;
		break;
	}

	if (table_port_enable == ENABLE) {
		buf[c++] = 0x0000ffff;	/* PYM_T_ENABLE */
	} else {
		buf[c++] = 0x00000000;	/* PYM_T_ENABLE */
	}

	gdmac_copy_word(inst, gdmac_add_data(inst, buf, c),
			rvdmac_base + IRECOG_rpyramid_PYM_R_ENABLE_OFFS, c);
}

/**************************************************/
/*
 * @brief rvdmac_table_port_setting
 *
 * @param inst
 *
 */
/**************************************************/
static void rvdmac_table_port_setting(gdmac_inst *inst)
{
	int i;
	int c = 0;
	uint32_t buf[MAX_TABLE_NUM * 2];
	unsigned long rvdmac_base =
	    PYRAMID_BASE + IRECOG_rpyramid_PYM_STADR_OFFS;

	for (i = 0; i < MAX_TABLE_NUM; i++) {
		buf[c++] = virt_to_phys(table_adr[i]);
		buf[c++] = TAP_TABLE_SIZE * 4;
	}

	gdmac_copy_word(inst, gdmac_add_data(inst, buf, c),
			rvdmac_base + IRECOG_rpyramid_PYM_T00_STADR_OFFS, c);
}

/**************************************************/
/*
 * @brief rvdmac_read_port_setting
 *
 * @param inst
 * @param input_y_adr
 * @param input_cb_adr
 * @param input_cr_adr
 * @param input_w_size
 * @param input_h_size
 * @param input_y_pitch
 * @param input_cb_pitch
 * @param input_cr_pitch
 * @param p_clr_sel
 *
 */
/**************************************************/
static void rvdmac_read_port_setting(gdmac_inst *inst,
				     unsigned long input_y_adr,
				     unsigned long input_cb_adr,
				     unsigned long input_cr_adr,
				     unsigned long input_w_size,
				     unsigned long input_h_size,
				     unsigned long input_y_pitch,
				     unsigned long input_cb_pitch,
				     unsigned long input_cr_pitch,
				     unsigned char p_clr_sel)
{
	int i;
	int c = 0;
	uint32_t buf[4 * 3];
	unsigned long rvdmac_base =
	    PYRAMID_BASE + IRECOG_rpyramid_PYM_STADR_OFFS;

	/* read port 0 setting */
	if ((p_clr_sel == P_CLR_SEL_Y) || (p_clr_sel == P_CLR_SEL_YCBCR)) {
		buf[c++] = input_y_adr;
		buf[c++] = input_y_adr + input_w_size - 1;
		buf[c++] = input_h_size;
		buf[c++] = input_y_pitch;
	} else {
		for (i = 0; i < 4; i++) {
			buf[c++] = 0;
		}
	}

	/* read port 1/2 setting */
	if ((p_clr_sel == P_CLR_SEL_CBCR) || (p_clr_sel == P_CLR_SEL_YCBCR)) {
		buf[c++] = input_cb_adr;
		buf[c++] = input_cb_adr + input_w_size - 1;
		buf[c++] = input_h_size;
		buf[c++] = input_cb_pitch;
		buf[c++] = input_cr_adr;
		buf[c++] = input_cr_adr + input_w_size - 1;
		buf[c++] = input_h_size;
		buf[c++] = input_cr_pitch;
	} else {
		for (i = 0; i < 8; i++) {
			buf[c++] = 0;
		}
	}

	gdmac_copy_word_interval(inst,
				 gdmac_add_data(inst, buf, c),
				 rvdmac_base +
				 IRECOG_rpyramid_PYM_R00_STADR_OFFS, 4, 0x40,
				 3);
}

/**************************************************/
/*
 * @brief rvdmac_write_port_setting
 *
 * @param inst
 * @param pyramid
 * @param out_index
 *
 */
/**************************************************/
static void rvdmac_write_port_setting(gdmac_inst *inst,
				      gdmac_pyramid *pyramid, int out_index)
{
	int i, j;
	int c = 0;
	uint32_t buf[4 * 12];
	unsigned long rvdmac_base =
	    PYRAMID_BASE + IRECOG_rpyramid_PYM_STADR_OFFS;

	/* write port y(0-3) setting */
	for (i = 0; i < 4; i++) {
		if ((pyramid->p_clr_sel == P_CLR_SEL_Y)
		    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {
			buf[c++] = pyramid->output[out_index + i].y_adr;
			buf[c++] =
			    pyramid->output[out_index + i].y_adr +
			    output_w_size[out_index + i] - 1;
			buf[c++] = output_h_size[out_index + i];
			buf[c++] = pyramid->output[out_index + i].y_pitch;
		} else {
			for (j = 0; j < 4; j++) {
				buf[c++] = 0;
			}
		}
	}

	/* write port cb(4-7) setting */
	for (i = 0; i < 4; i++) {
		if ((pyramid->p_clr_sel == P_CLR_SEL_CBCR)
		    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {
			buf[c++] = pyramid->output[out_index + i].cb_adr;
			buf[c++] =
			    pyramid->output[out_index + i].cb_adr +
			    output_w_size[out_index + i] - 1;
			buf[c++] = output_h_size[out_index + i];
			buf[c++] = pyramid->output[out_index + i].cb_pitch;
		} else {
			for (j = 0; j < 4; j++) {
				buf[c++] = 0;
			}
		}
	}

	/* write port cr(8-11) setting */
	for (i = 0; i < 4; i++) {
		if ((pyramid->p_clr_sel == P_CLR_SEL_CBCR)
		    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {
			buf[c++] = pyramid->output[out_index + i].cr_adr;
			buf[c++] =
			    pyramid->output[out_index + i].cr_adr +
			    output_w_size[out_index + i] - 1;
			buf[c++] = output_h_size[out_index + i];
			buf[c++] = pyramid->output[out_index + i].cr_pitch;
		} else {
			for (j = 0; j < 4; j++) {
				buf[c++] = 0;
			}
		}
	}

	gdmac_copy_word_interval(inst,
				 gdmac_add_data(inst, buf, c),
				 rvdmac_base +
				 IRECOG_rpyramid_PYM_W00_STADR_OFFS, 4, 0x40,
				 12);
}

/**************************************************/
/*
 * @brief rvdmac_port_setting
 *
 * @param inst
 * @param input_y_adr
 * @param input_cb_adr
 * @param input_cr_adr
 * @param input_w_size
 * @param input_h_size
 * @param input_y_pitch
 * @param input_cb_pitch
 * @param input_cr_pitch
 * @param pyramid
 * @param out_index
 *
 */
/**************************************************/
static void rvdmac_port_setting(gdmac_inst *inst,
				unsigned long input_y_adr,
				unsigned long input_cb_adr,
				unsigned long input_cr_adr,
				unsigned long input_w_size,
				unsigned long input_h_size,
				unsigned long input_y_pitch,
				unsigned long input_cb_pitch,
				unsigned long input_cr_pitch,
				gdmac_pyramid *pyramid, int out_index)
{
	rvdmac_read_port_setting(inst,
				 input_y_adr,
				 input_cb_adr,
				 input_cr_adr,
				 input_w_size,
				 input_h_size,
				 input_y_pitch,
				 input_cb_pitch,
				 input_cr_pitch, pyramid->p_clr_sel);

	rvdmac_write_port_setting(inst, pyramid, out_index);
}

/**************************************************/
/*
 * @brief pyramid_initialize
 *
 * return 0
 * return -ENOMEM
 *
 */
/**************************************************/
int pyramid_initialize(void)
{
	int i;

	/* tap coeff table initialize */
	for (i = 0; i < MAX_TABLE_NUM; i++) {
		table_adr[i] =
		    kmalloc(sizeof(unsigned long) * TAP_TABLE_SIZE,
			    GFP_KERNEL | GFP_DMA);
		if (!table_adr[i]) {
			pr_err("%s: kmalloc failed.", GDMAC_PYRAMID_NAME);
			goto err;
		}
	}

	get_tap_coeff(TAP_LANCZOS2_084, table_adr[0 * 4 + 0]);
	get_tap_coeff(TAP_LANCZOS2_084, table_adr[0 * 4 + 1]);
	get_tap_coeff(TAP_LANCZOS2_084, table_adr[0 * 4 + 2]);
	get_tap_coeff(TAP_LANCZOS2_084, table_adr[0 * 4 + 3]);
	get_tap_coeff(TAP_LANCZOS2_071, table_adr[1 * 4 + 0]);
	get_tap_coeff(TAP_LANCZOS2_071, table_adr[1 * 4 + 1]);
	get_tap_coeff(TAP_LANCZOS2_071, table_adr[1 * 4 + 2]);
	get_tap_coeff(TAP_LANCZOS2_071, table_adr[1 * 4 + 3]);
	get_tap_coeff(TAP_LANCZOS2_059, table_adr[2 * 4 + 0]);
	get_tap_coeff(TAP_LANCZOS2_059, table_adr[2 * 4 + 1]);
	get_tap_coeff(TAP_LANCZOS2_059, table_adr[2 * 4 + 2]);
	get_tap_coeff(TAP_LANCZOS2_059, table_adr[2 * 4 + 3]);
	get_tap_coeff(TAP_LANCZOS2_050, table_adr[3 * 4 + 0]);
	get_tap_coeff(TAP_LANCZOS2_050, table_adr[3 * 4 + 1]);
	get_tap_coeff(TAP_LANCZOS2_050, table_adr[3 * 4 + 2]);
	get_tap_coeff(TAP_LANCZOS2_050, table_adr[3 * 4 + 3]);

	return 0;

err:
	for (i = 0; i < MAX_TABLE_NUM; i++) {
		kfree(table_adr[i]);
	}
	return -ENOMEM;
}

/**************************************************/
/*
 * @brief pyramid_finalize
 *
 */
/**************************************************/
void pyramid_finalize(void)
{
	int i;

	for (i = 0; i < MAX_TABLE_NUM; i++) {
		kfree(table_adr[i]);
	}
}

/**************************************************/
/*
 * @brief pyramid_create_instructions
 *
 * @param rvdmac_base
 *
 */
/**************************************************/
void pyramid_create_instructions(gdmac_inst *inst, gdmac_pyramid *pyramid)
{
	unsigned long rscaler_base =
	    PYRAMID_BASE + IRECOG_rpyramid_RSCALER_CS_START_OFFS;
	unsigned long rvdmac_base =
	    PYRAMID_BASE + IRECOG_rpyramid_PYM_STADR_OFFS;

	/* clear instruction buffer */
	gdmac_clear(inst);

	/* --- 1st time -------------------------------------------- */
	dma330_dmaflushp(inst, GDMAC_PYRAMID_PORT);

	/* clear interrupt */
	rvdmac_clear_status(inst);

	/* interrupt mask */
	gdmac_write_register(inst,
			     rvdmac_base + IRECOG_rpyramid_PYM_INT_MASK_OFFS,
			     0x00000000);

	/* rvdmac port enable */
	rvdmac_port_enable(inst, pyramid, ENABLE);

	/* rvdmac table port setting */
	rvdmac_table_port_setting(inst);

	/* rvdmac read port setting  */
	rvdmac_port_setting(inst,
			    pyramid->input.y_adr,
			    pyramid->input.cb_adr,
			    pyramid->input.cr_adr,
			    GDMAC_PYRAMID_IN_W,
			    GDMAC_PYRAMID_IN_H,
			    pyramid->input.y_pitch,
			    pyramid->input.cb_pitch,
			    pyramid->input.cr_pitch, pyramid, 0);

	/* rscaler setting */
	rscaler_setting(inst, pyramid);

	/* kick(1st) */
	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_START_OFFS), 0x01);

	/* --- prepare 2nd time ------------------------------------ */
	/* port setting */
	rvdmac_port_enable(inst, pyramid, DISABLE);

	/* rvdmac read port setting  */
	rvdmac_port_setting(inst,
			    pyramid->output[3].y_adr,
			    pyramid->output[3].cb_adr,
			    pyramid->output[3].cr_adr,
			    output_w_size[3],
			    output_h_size[3],
			    pyramid->output[3].y_pitch,
			    pyramid->output[3].cb_pitch,
			    pyramid->output[3].cr_pitch, pyramid, 4);
	/* image size setting */
	rscaler_image_size_setting(inst, pyramid->p_clr_sel, output_w_size[3],
				   output_h_size[3], 4);

	/* wait */
	dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_PYRAMID_PORT);

	/* clear interrupt */
	rvdmac_clear_status(inst);

	/* initialize peripheral */
	dma330_dmaflushp(inst, GDMAC_PYRAMID_PORT);

	/* kick(2nd) */
	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_START_OFFS), 0x01);

	/* --- prepare 3rd time ------------------------------------ */
	/* port setting */
	rvdmac_port_enable(inst, pyramid, DISABLE);

	/* rvdmac read port setting  */
	rvdmac_port_setting(inst,
			    pyramid->output[7].y_adr,
			    pyramid->output[7].cb_adr,
			    pyramid->output[7].cr_adr,
			    output_w_size[7],
			    output_h_size[7],
			    pyramid->output[7].y_pitch,
			    pyramid->output[7].cb_pitch,
			    pyramid->output[7].cr_pitch, pyramid, 8);

	/* image size setting */
	rscaler_image_size_setting(inst, pyramid->p_clr_sel, output_w_size[7],
				   output_h_size[7], 8);

	/* wait */
	dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_PYRAMID_PORT);

	/* clear interrupt */
	rvdmac_clear_status(inst);

	/* initialize peripheral */
	dma330_dmaflushp(inst, GDMAC_PYRAMID_PORT);

	/* kick(3rd) */
	gdmac_write_register(inst,
			     rscaler_base +
			     RSCALER_OFFSET
			     (IRECOG_rpyramid_RSCALER_CS_START_OFFS), 0x01);

	/* --- wait for pyramid interrupt -------------------------- */

	/* wait */
	dma330_dmawfp(inst, GDMAC_SINGLE, GDMAC_PYRAMID_PORT);

	/* clear interrupt */
	rvdmac_clear_status(inst);

	/* interrupt */
	dma330_dmasev(inst, GDMAC_INT0);

	/* dmaend */
	dma330_dmaend(inst);
}

/**************************************************/
/*
 * @brief pitch_64byte_check
 *
 * @param pitch
 *
 * @retval 0
 * @retval -EINVAL
 *
 */
/**************************************************/
static inline int pitch_64byte_check(unsigned long pitch)
{
	if ((pitch % 64) != 0) {
		return -EINVAL;
	}

	return 0;
}

/**************************************************/
/*
 * @brief pyramid_parameter_check
 *
 * @param pyramid
 *
 * @retval 0
 * @retval -EINVAL
 *
 */
/**************************************************/
int pyramid_parameter_check(gdmac_pyramid *pyramid)
{
	int i;

	if (pyramid->fil_mode > FIL_MODE_NEAREST) {
		pr_err("%s: invalid fil_mode:%d", GDMAC_PYRAMID_NAME,
		       pyramid->fil_mode);
		return -EINVAL;
	}
	if (pyramid->p_clr_sel > P_CLR_SEL_YCBCR) {
		pr_err("%s: invalid p_clr_sel:%d", GDMAC_PYRAMID_NAME,
		       pyramid->p_clr_sel);
		return -EINVAL;
	}

	/* Y check */
	if ((pyramid->p_clr_sel == P_CLR_SEL_Y)
	    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {

		if ((pyramid->input.y_pitch < GDMAC_PYRAMID_IN_W) ||
		    (pitch_64byte_check(pyramid->input.y_pitch) < 0)) {
			pr_err("%s: invalid input.y_pitch:%lu",
			       GDMAC_PYRAMID_NAME, pyramid->input.y_pitch);
			return -EINVAL;
		}

		for (i = 0; i < GDMAC_PYRAMID_OUT_NUM; i++) {
			if ((pyramid->output[i].y_pitch < output_w_size[i]) ||
			    (pitch_64byte_check(pyramid->output[i].y_pitch) <
			     0)) {
				pr_err("%s: invalid output[%d].y_pitch:%lu",
				       GDMAC_PYRAMID_NAME, i,
				       pyramid->output[i].y_pitch);
				return -EINVAL;
			}
		}
	}

	/* Cb/Cr check */
	if ((pyramid->p_clr_sel == P_CLR_SEL_CBCR)
	    || (pyramid->p_clr_sel == P_CLR_SEL_YCBCR)) {

		if ((pyramid->input.cb_pitch < GDMAC_PYRAMID_IN_W) ||
		    (pitch_64byte_check(pyramid->input.cb_pitch) < 0)) {
			pr_err("%s: invalid input.cb_pitch:%lu",
			       GDMAC_PYRAMID_NAME, pyramid->input.cb_pitch);
			return -EINVAL;
		}
		if ((pyramid->input.cr_pitch < GDMAC_PYRAMID_IN_W) ||
		    (pitch_64byte_check(pyramid->input.cr_pitch) < 0)) {
			pr_err("%s: invalid input.cr_pitch:%lu",
			       GDMAC_PYRAMID_NAME, pyramid->input.cr_pitch);
			return -EINVAL;
		}

		for (i = 0; i < GDMAC_PYRAMID_OUT_NUM; i++) {
			if ((pyramid->output[i].y_pitch < output_w_size[i]) ||
			    (pitch_64byte_check(pyramid->output[i].y_pitch) <
			     0)) {
				pr_err("%s: invalid output[%d].y_pitch:%lu",
				       GDMAC_PYRAMID_NAME, i,
				       pyramid->output[i].y_pitch);
				return -EINVAL;
			}
			if ((pyramid->output[i].cb_pitch < output_w_size[i]) ||
			    (pitch_64byte_check(pyramid->output[i].cb_pitch) <
			     0)) {
				pr_err("%s: invalid output[%d].cb_pitch:%lu",
				       GDMAC_PYRAMID_NAME, i,
				       pyramid->output[i].cb_pitch);
				return -EINVAL;
			}
			if ((pyramid->output[i].cr_pitch < output_w_size[i]) ||
			    (pitch_64byte_check(pyramid->output[i].cr_pitch) <
			     0)) {
				pr_err("%s: invalid output[%d].cr_pitch:%lu",
				       GDMAC_PYRAMID_NAME, i,
				       pyramid->output[i].cr_pitch);
				return -EINVAL;
			}
		}
	}

	return 0;
}
