/*
 * linux/drivers/staging/applite/irecog/pyramid/pyramid_setup.c
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

#include <linux/applite/irecog/pyramid_ioctl.h>

#include "pyramid_driver.h"
#include "pyramid_setup.h"

/*#define ENABLE_RDCT_BITSHIFT */

/**************************************************/
/*
 * @brief write_reg
 *
 * @param value
 * @param base
 * @param offset
 *
 */
/**************************************************/
static void write_reg(unsigned long value, void __iomem *base,
		      unsigned long offset)
{
	iowrite32(value, base + offset);
}

/**************************************************/
/*
 * @brief read_reg
 *
 * @param base
 * @param offset
 *
 */
/**************************************************/
static unsigned long read_reg(void __iomem *base, unsigned long offset)
{
	return ioread32(base + offset);
}

/**************************************************/
/*
 * @brief setup read port
 *
 * @param rvdmac_base
 * @param port_no
 * @param enabled
 * @param phy_adr
 * @param width
 * @param height
 * @param pitch
 *
 */
/**************************************************/
void setup_read_port(void __iomem *rvdmac_base,
		     unsigned int port_no,
		     unsigned int enabled,
		     unsigned long phy_adr,
		     unsigned long width,
		     unsigned long height, unsigned long pitch)
{
	unsigned long reg_value;

	if (port_no >= MAX_READ_PORT) {
		pr_err("setup_read_port: invalid port:%d\n", port_no);
		return;
	}

	reg_value = read_reg(rvdmac_base, IRECOG_rpyramid_PYM_R_ENABLE_OFFS);

	if (enabled == PYM_ENABLE) {

		write_reg(reg_value | (0x01 << port_no), rvdmac_base,
			  IRECOG_rpyramid_PYM_R_ENABLE_OFFS);

		write_reg(phy_adr, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_STADR_OFFS +
			  _PYM_R_INTERVAL * port_no);
		write_reg(phy_adr + width - 1, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_ENDADR_OFFS +
			  _PYM_R_INTERVAL * port_no);
		write_reg(height, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_HEIGHT_OFFS +
			  _PYM_R_INTERVAL * port_no);
		write_reg(pitch, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_PITCH_OFFS +
			  _PYM_R_INTERVAL * port_no);

	} else {
		write_reg(reg_value & ~(0x01 << port_no), rvdmac_base,
			  IRECOG_rpyramid_PYM_R_ENABLE_OFFS);
		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_STADR_OFFS +
			  _PYM_R_INTERVAL * port_no);
		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_ENDADR_OFFS +
			  _PYM_R_INTERVAL * port_no);
		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_HEIGHT_OFFS +
			  _PYM_R_INTERVAL * port_no);
		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_PITCH_OFFS +
			  _PYM_R_INTERVAL * port_no);
	}
}

/**************************************************/
/*
 * @brief setup write port
 *
 * @param rvdmac_base
 * @param port_no
 * @param enabled
 * @param phy_adr
 * @param width
 * @param height
 * @param pitch
 *
 */
/**************************************************/
void setup_write_port(void __iomem *rvdmac_base,
		      unsigned int port_no,
		      unsigned int enabled,
		      unsigned long phy_adr,
		      unsigned long width,
		      unsigned long height, unsigned long pitch)
{
	unsigned long reg_value;

	if (port_no >= MAX_WRITE_PORT) {
		pr_err("setup_write_port: invalid port:%d\n", port_no);
		return;
	}

	reg_value = read_reg(rvdmac_base, IRECOG_rpyramid_PYM_W_ENABLE_OFFS);

	if (enabled == PYM_ENABLE) {

		write_reg(reg_value | (0x01 << port_no), rvdmac_base,
			  IRECOG_rpyramid_PYM_W_ENABLE_OFFS);

		write_reg(phy_adr, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_STADR_OFFS +
			  _PYM_W_INTERVAL * port_no);
		write_reg(phy_adr + width - 1, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_ENDADR_OFFS +
			  _PYM_W_INTERVAL * port_no);
		write_reg(height, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_HEIGHT_OFFS +
			  _PYM_W_INTERVAL * port_no);
		write_reg(pitch, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_PITCH_OFFS +
			  _PYM_W_INTERVAL * port_no);

	} else {

		write_reg(reg_value & ~(0x01 << port_no), rvdmac_base,
			  IRECOG_rpyramid_PYM_W_ENABLE_OFFS);

		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_STADR_OFFS +
			  _PYM_W_INTERVAL * port_no);
		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_ENDADR_OFFS +
			  _PYM_W_INTERVAL * port_no);
		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_HEIGHT_OFFS +
			  _PYM_W_INTERVAL * port_no);
		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_PITCH_OFFS +
			  _PYM_W_INTERVAL * port_no);
	}
}

/**************************************************/
/*
 * @brief setup table port
 *
 * @param rvdmac_base
 * @param id
 * @param enabled
 * @param phy_adr
 * @param size
 *
 */
/**************************************************/
void setup_table_port(void __iomem *rvdmac_base,
		      unsigned int id,
		      unsigned int enabled,
		      unsigned long phy_adr, unsigned long size)
{
	unsigned long reg_value;

	if (id >= MAX_TABLE_NUM) {
		pr_err("setup_table_port: invalid table:%d\n", id);
		return;
	}

	reg_value = read_reg(rvdmac_base, IRECOG_rpyramid_PYM_T_ENABLE_OFFS);

	if (enabled == PYM_ENABLE) {

		write_reg(reg_value | (0x01 << id), rvdmac_base,
			  IRECOG_rpyramid_PYM_T_ENABLE_OFFS);

		write_reg(phy_adr, rvdmac_base,
			  IRECOG_rpyramid_PYM_T00_STADR_OFFS +
			  _PYM_T_INTERVAL * id);
		write_reg(size, rvdmac_base,
			  IRECOG_rpyramid_PYM_T00_SIZE_OFFS +
			  _PYM_T_INTERVAL * id);

	} else {

		write_reg(reg_value & ~(0x01 << id), rvdmac_base,
			  IRECOG_rpyramid_PYM_T_ENABLE_OFFS);

		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_T00_STADR_OFFS +
			  _PYM_T_INTERVAL * id);
		write_reg(0x0, rvdmac_base,
			  IRECOG_rpyramid_PYM_T00_SIZE_OFFS +
			  _PYM_T_INTERVAL * id);
	}

}

/**************************************************/
/*
 * @brief setup_rscaler
 *
 * @param rscaler_base
 * @param param
 *
 */
/**************************************************/
void setup_rscaler(void __iomem *rscaler_base, pyramid_param *param)
{
	int i;
	unsigned long value;
	unsigned char port_sel;
	unsigned char yuv_sel;

	/* filter mode */
	value = ((0x0) << 4) | (param->fil_mode & 0x07);
	write_reg(value, rscaler_base,
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_YHFILMODE_OFFS));

	value = ((0x0) << 4) | (param->fil_mode & 0x07);
	write_reg(value, rscaler_base,
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_YVFILMODE_OFFS));

	value = ((0x0) << 4) | (param->fil_mode & 0x07);
	write_reg(value, rscaler_base,
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_CHFILMODE_OFFS));

	value = ((0x0) << 4) | (param->fil_mode & 0x07);
	write_reg(value, rscaler_base,
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_CVFILMODE_OFFS));

	/* reducation ratio */
	for (i = 0; i < MAX_ROUTE; i++) {
#if defined(ENABLE_RDCT_BITSHIFT)
		value = (param->rdct_ratio[i] & 0x7FFF8) << 3;
#else
		value = (param->rdct_ratio[i] & 0x7FFF8);
#endif
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YH1FILBASE_OFFS) +
			  _RS_CS_YHFILBASE_INTERVAL * i);
	}
	for (i = 0; i < MAX_ROUTE; i++) {
#if defined(ENABLE_RDCT_BITSHIFT)
		value = (param->rdct_ratio[i] & 0x7FFF8) << 3;
#else
		value = (param->rdct_ratio[i] & 0x7FFF8);
#endif
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YV1FILBASE_OFFS) +
			  _RS_CS_YVFILBASE_INTERVAL * i);
	}
	for (i = 0; i < MAX_ROUTE; i++) {
#if defined(ENABLE_RDCT_BITSHIFT)
		value = (param->rdct_ratio[i] & 0x7FFF8) << 3;
#else
		value = (param->rdct_ratio[i] & 0x7FFF8);
#endif
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CH1FILBASE_OFFS) +
			  _RS_CS_CHFILBASE_INTERVAL * i);
	}
	for (i = 0; i < MAX_ROUTE; i++) {
#if defined(ENABLE_RDCT_BITSHIFT)
		value = (param->rdct_ratio[i] & 0x7FFF8) << 3;
#else
		value = (param->rdct_ratio[i] & 0x7FFF8);
#endif
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CV1FILBASE_OFFS) +
			  _RS_CS_CVFILBASE_INTERVAL * i);
	}

	/* port setting */
	/* port_sel: 0000b -> port4 port3 port2 port1 */
	if (param->p_num == P_NUM_4PICS) {
		port_sel = 0xf;
	} else {
		port_sel = 0x1;
	}

	/* yuv_sel: 000b -> cr cb y */
	switch (param->p_clr_sel) {
	case P_CLR_SEL_Y:
		yuv_sel = 0x01;
		break;
	case P_CLR_SEL_CBCR:
		yuv_sel = 0x6;
		break;
	case P_CLR_SEL_YCBCR:
		yuv_sel = 0x7;
		break;
	default:
		yuv_sel = 0x01;
		break;
	}

	value = (((yuv_sel >> 0) & (port_sel >> 0)) & 0x01) << 27;
	value |= (((yuv_sel >> 1) & (port_sel >> 0)) & 0x01) << 26;
	value |= (((yuv_sel >> 2) & (port_sel >> 0)) & 0x01) << 25;
	value |= (((yuv_sel >> 0) & (port_sel >> 1)) & 0x01) << 24;
	value |= (((yuv_sel >> 1) & (port_sel >> 1)) & 0x01) << 23;
	value |= (((yuv_sel >> 2) & (port_sel >> 1)) & 0x01) << 22;
	value |= (((yuv_sel >> 0) & (port_sel >> 2)) & 0x01) << 21;
	value |= (((yuv_sel >> 1) & (port_sel >> 2)) & 0x01) << 20;
	value |= (((yuv_sel >> 2) & (port_sel >> 2)) & 0x01) << 19;
	value |= (((yuv_sel >> 0) & (port_sel >> 3)) & 0x01) << 18;
	value |= (((yuv_sel >> 1) & (port_sel >> 3)) & 0x01) << 17;
	value |= (((yuv_sel >> 2) & (port_sel >> 3)) & 0x01) << 16;
	value |= (0x0) << 8;
	value |= (0x0) << 4;
	write_reg(value, rscaler_base,
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_MODE_OFFS));

	/* set image size */
	if ((yuv_sel >> 0) & 0x01) {
		value =
		    ((param->
		      input_w_size & 0x07FF) << 16) | (param->input_h_size &
						       0x07FF);
	} else {
		value = 0x00000000;
	}
	write_reg(value, rscaler_base,
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_YHVSIN_OFFS));
	if (((yuv_sel >> 1) & 0x01) || ((yuv_sel >> 2) & 0x01)) {
		value =
		    ((param->
		      input_w_size & 0x07FF) << 16) | (param->input_h_size &
						       0x07FF);
	} else {
		value = 0x00000000;
	}
	write_reg(value, rscaler_base,
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_CHVSIN_OFFS));

	/* set output image size */
	for (i = 0; i < MAX_ROUTE; i++) {
		if (((yuv_sel >> 0) & 0x01) & ((port_sel >> i) & 0x01)) {
			value =
			    ((param->output_w_size[i] & 0x07FF) << 16) |
			    (param->output_h_size[i] & 0x07FF);
		} else {
			value = 0x00000000;
		}
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YHV1SZOUT_OFFS) +
			  _RS_CS_YHVSZOUT_INTERVAL * i);
	}
	for (i = 0; i < MAX_ROUTE; i++) {
		if ((((yuv_sel >> 1) | (yuv_sel >> 2)) & 0x01) &
		    ((port_sel > i) & 0x01)) {
			value =
			    ((param->output_w_size[i] & 0x07FF) << 16) |
			    (param->output_h_size[i] & 0x07FF);
		} else {
			value = 0x00000000;
		}
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CHV1SZOUT_OFFS) +
			  _RS_CS_CHVSZOUT_INTERVAL * i);
	}

	/* crop image setting */
	if (param->crop_image == CROP_ENABLE) {
		/* crop width */
		value = (1 << 16) | (param->crop_size_w & 0x07ff);
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YHFILPSMODE_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CHFILPSMODE_OFFS));

		/* crop origin(x) */
		value = (param->crop_pos_x & 0x1fffff) << 16;
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YPHOS_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CPHOS_OFFS));

		/* crop height */
		value = (1 << 16) | (param->crop_size_h & 0x07ff);
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YVFILPSMODE_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CVFILPSMODE_OFFS));

		/* crop origin(y) */
		value = (param->crop_pos_y & 0x1fffff) << 16;
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YPVOS_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CPVOS_OFFS));

	} else {
		value = 0x00000000;
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YHFILPSMODE_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YPHOS_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YVFILPSMODE_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_YPVOS_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CHFILPSMODE_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CPHOS_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CVFILPSMODE_OFFS));
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_CPVOS_OFFS));
	}

	/* set default value */
	value = 0x00000000;
	write_reg(value, rscaler_base,
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_OAINSET_OFFS));

	for (i = 0; i < _RS_CS_OAOUTSET_NUM; i++) {
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_OAOUTSET1_OFFS) +
			  _RS_CS_OAOUTSET_INTERVAL * i);
	}
	for (i = 0; i < _RS_CS_HOAOUTSET_NUM; i++) {
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_H1OAOUTSET_OFFS) +
			  _RS_CS_HOAOUTSET_INTERVAL * i);
	}
	for (i = 0; i < _RS_CS_VOAOUTSET_NUM; i++) {
		write_reg(value, rscaler_base,
			  RSCALER_OFFSET
			  (IRECOG_rpyramid_RSCALER_CS_V1OAOUTSET_OFFS) +
			  _RS_CS_VOAOUTSET_INTERVAL * i);
	}
}

/**************************************************/
/*
 * @brief initialize
 *
 * @param rvdmac_base
 */
/**************************************************/
void initialize(void __iomem *rvdmac_base)
{
	int i;

	/* mbus setting */
	write_reg(0x00000003, rvdmac_base, IRECOG_rpyramid_PYM_STATUS_OFFS);
	write_reg(MBUS_STADR, rvdmac_base, IRECOG_rpyramid_PYM_STADR_OFFS);
	write_reg(MBUS_ENDADR, rvdmac_base, IRECOG_rpyramid_PYM_ENDADR_OFFS);
	write_reg(0x00070700, rvdmac_base, IRECOG_rpyramid_PYM_CFG_OFFS);

	/* mbus setting */
	write_reg(0x00000000, rvdmac_base, IRECOG_rpyramid_PYM_T00_INTL_OFFS);
	for (i = 0; i < _PYM_R_NUM; i++) {
		write_reg(0x00000000, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_INTL_OFFS +
			  _PYM_R_INTERVAL * i);
	}
	for (i = 0; i < _PYM_W_NUM; i++) {
		write_reg(0x00000000, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_INTL_OFFS +
			  _PYM_W_INTERVAL * i);
	}

	/* interrupt mask setting */
	write_reg(0x00000000, rvdmac_base, IRECOG_rpyramid_PYM_INT_MASK_OFFS);

	/* set configuration register0 */
	write_reg(0x00000210, rvdmac_base, IRECOG_rpyramid_PYM_T00_CFG_OFFS);	/* data bus:32bit */

	for (i = 0; i < _PYM_R_NUM; i++) {
		write_reg(0x00000000, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_CFG0_OFFS +
			  _PYM_R_INTERVAL * i);
	}
	for (i = 0; i < _PYM_W_NUM; i++) {
		write_reg(0x00000000, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_CFG0_OFFS +
			  _PYM_W_INTERVAL * i);
	}

	/* set configuration register1 */
	for (i = 0; i < _PYM_R_NUM; i++) {
		write_reg(0x00010000, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_CFG1_OFFS +
			  _PYM_R_INTERVAL * i);
	}
	for (i = 0; i < _PYM_W_NUM; i++) {
		write_reg(0x00010000, rvdmac_base,
			  IRECOG_rpyramid_PYM_W00_CFG1_OFFS +
			  _PYM_W_INTERVAL * i);
	}

	/* sram setting */
	write_reg(0x00000000, rvdmac_base,
		  IRECOG_rpyramid_PYM_T00_SRAM_BASE_OFFS);
	for (i = 0; i < _PYM_R_NUM; i++) {
		write_reg(0x00000040 * (i + 1), rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_SRAM_BASE_OFFS +
			  _PYM_R_INTERVAL * i);
	}

	write_reg(0x00000000, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 0);
	write_reg(0x00000040, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 1);
	write_reg(0x00000070, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 2);
	write_reg(0x00000090, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 3);
	write_reg(0x000000b0, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 4);
	write_reg(0x000000f0, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 5);
	write_reg(0x00000120, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 6);
	write_reg(0x00000140, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 7);
	write_reg(0x00000160, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 8);
	write_reg(0x000001a0, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 9);
	write_reg(0x000001d0, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS +
		  _PYM_W_INTERVAL * 10);
	write_reg(0x000001f0, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS +
		  _PYM_W_INTERVAL * 11);

	write_reg(0x00000040, rvdmac_base,
		  IRECOG_rpyramid_PYM_T00_SRAM_SIZE_OFFS);
	for (i = 0; i < _PYM_R_NUM; i++) {
		write_reg(0x00000040, rvdmac_base,
			  IRECOG_rpyramid_PYM_R00_SRAM_SIZE_OFFS +
			  _PYM_R_INTERVAL * i);
	}

	write_reg(0x00000040, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 0);
	write_reg(0x00000030, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 1);
	write_reg(0x00000020, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 2);
	write_reg(0x00000020, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 3);
	write_reg(0x00000040, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 4);
	write_reg(0x00000030, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 5);
	write_reg(0x00000020, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 6);
	write_reg(0x00000020, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 7);
	write_reg(0x00000040, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 8);
	write_reg(0x00000030, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 9);
	write_reg(0x00000020, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS +
		  _PYM_W_INTERVAL * 10);
	write_reg(0x00000020, rvdmac_base,
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS +
		  _PYM_W_INTERVAL * 11);
}
