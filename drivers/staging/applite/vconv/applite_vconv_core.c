/*
 * linux/drivers/staging/applite/applite_vconv_core.c
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

/*===================================
 Include Files
===================================*/

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/dma-buf.h>

#include <linux/applite/applite_vconv.h>
#include "applite_vconv_internal.h"
#include "applite_vconv_dbg.h"


/*===================================
Static Variables and Functions prototypes
===================================*/


/* parameters checking functions */
static int vconv_get_bpp(__u32 format, __u8 *bpp);
static int vconv_chk_pitch(struct vconv_param_ex *prm);
static int vconv_chk_size(struct vconv_param_ex *prm);
static int vconv_chk_offset(struct vconv_param_ex *prm);
static int vconv_chk_align(struct vconv_param_ex *prm, struct vconv_conv_adr *adr);
static int vconv_chk_scale(struct vconv_param_ex *prm);
static int vconv_chk_others(struct vconv_param_ex *prm);

/* address convertion functions */
static int vconv_get_phys_addr(struct vconv_dev *pdev,
		struct vconv_buffer_ex *prm,
		struct vconv_conv_adr *padr,
		enum dma_data_direction dir);
static int vconv_put_phys_addr(struct vconv_buffer_ex *prm,
		struct vconv_conv_adr *padr,
		enum dma_data_direction dir);
static int vconv_conv_tiling_addr(struct vconv_param_ex *prm,
		struct vconv_conv_adr *adr);
static int vconv_conv_address(struct vconv_dev *pdev,
		struct vconv_param_ex *prm,
		struct vconv_conv_adr *adr);
static int vconv_free_address(struct vconv_dev *pdev,
		struct vconv_param_ex *prm,
		struct vconv_conv_adr *adr);

/*===================================
Global Variables and Functions prototypes
===================================*/


/*===================================
Macros
===================================*/

/*===================================
Function Definitions
===================================*/

/*===================================
Module source
===================================*/



/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_get_phys_addr(struct vconv_dev *pdev,
		struct vconv_buffer_ex *prm,
		struct vconv_conv_adr *padr,
		enum dma_data_direction dir)
{
	VCONV_FUNC_START("\n");

	/* check input parameters */
	if ((pdev == NULL) || (prm == NULL) || (padr == NULL)) {
		VCONV_ERR("invalid parameter pdev[%p], prm[%p], padr[%p]\n",
			pdev, prm, padr);
		return VCONV_NG;
	}
	if (prm->mode != VCONV_USE_FD) {
		padr->db = NULL;
		padr->dba = NULL;
		padr->sg = NULL;
		padr->addr = (dma_addr_t)prm->phys;
		padr->enable = VCONV_ENABLE;
		VCONV_INFO("convert address [%08x/%p]\n", padr->addr, prm->phys);
		DUMP_VCONV_CONV_ADR(padr);
		VCONV_FUNC_END("OK\n");
		return VCONV_OK;
	}
	/* get phys address from fd */
	padr->db = dma_buf_get(prm->fd);
	if (IS_ERR(padr->db)) {
		VCONV_ERR("dma_buf_get() failed fd[%d]\n", prm->fd);
		return VCONV_NG;
	}
	padr->dba = dma_buf_attach(padr->db, pdev->device);
	if (IS_ERR(padr->dba)) {
		VCONV_ERR("dma_buf_attach() failed db[%p]\n", padr->db);
		goto ERR_dma_buf_attach;
	}
	padr->sg = dma_buf_map_attachment(padr->dba, dir);
	if (IS_ERR(padr->sg)) {
		VCONV_ERR("dma_buf_map_attachment() failed dba[%p]\n",
			padr->dba);
		goto ERR_dma_buf_map_attachment;
	}
	/* convert sg_table to dma_addr_t */
	padr->addr = sg_phys(padr->sg->sgl);
	VCONV_INFO("converted address[%08x], sg's dma_address(%08x)\n",
		padr->addr, padr->sg->sgl->dma_address);
	padr->enable = VCONV_ENABLE;

	DUMP_VCONV_CONV_ADR(padr);

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;

ERR_dma_buf_map_attachment:
	dma_buf_detach(padr->db, padr->dba);
ERR_dma_buf_attach:
	dma_buf_put(padr->db);

	VCONV_FUNC_END("NG\n");

	return VCONV_NG;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_put_phys_addr(struct vconv_buffer_ex *prm,
		struct vconv_conv_adr *padr,
		enum dma_data_direction dir)
{
	VCONV_FUNC_START("\n");

	/* check input parameters */
	if ((prm == NULL) || (padr == NULL)) {
		VCONV_ERR("invalid parameter prm[%p], padr[%p]\n", prm, padr);
		return VCONV_NG;
	}
	DUMP_VCONV_CONV_ADR(padr);

	if (padr->enable != VCONV_ENABLE)
		return VCONV_OK;

	if (prm->mode != VCONV_USE_FD) {
		padr->enable = VCONV_DISABLE;
		VCONV_FUNC_END("nothing OK\n");
		return VCONV_OK;
	}
	/* release address */
	if (!IS_ERR_OR_NULL(padr->dba) && !IS_ERR_OR_NULL(padr->sg))
		dma_buf_unmap_attachment(padr->dba, padr->sg, dir);

	if (!IS_ERR_OR_NULL(padr->db) && !IS_ERR_OR_NULL(padr->dba))
		dma_buf_detach(padr->db, padr->dba);

	if (!IS_ERR_OR_NULL(padr->db))
		dma_buf_put(padr->db);

	padr->enable = VCONV_DISABLE;

	DUMP_VCONV_CONV_ADR(padr);

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_conv_tiling_addr(struct vconv_param_ex *prm,
		struct vconv_conv_adr *adr)
{
	int idx;
	VCONV_FUNC_START("\n");

	/* check input parameters */
	if ((prm == NULL) || (adr == NULL)) {
		VCONV_ERR("invalid parameter prm[%p], adr[%p]\n", prm, adr);
		return VCONV_NG;
	}
	if ((prm->in_img.format == VCONV_PK_T_VDU1)
		|| (prm->in_img.format == VCONV_PK_T_VDU2)) {
		/* calculate converted address */
		VCONV_INFO("convert tiling address [VDU1/VDU2]\n");
		adr[VCONV_PLANE_A].addr = phys_to_tile(adr[VCONV_PLANE_A].addr);
		adr[VCONV_PLANE_A].addr += prm->in_buffer[VCONV_PLANE_A].offset;
		VCONV_TEST("converted address %08x\n",
			adr[VCONV_PLANE_A].addr);
	} else {
		for (idx = 0; idx < VCONV_GET_PLANE(prm->in_img.format);
								idx++)
			adr[idx].addr += prm->in_buffer[idx].offset;
	}
	/* set adr to output image pointer */
	adr = &adr[VCONV_PLANE_MAX];
	if (prm->out_img.format == VCONV_PT_T_VEU) {
		/* calculate converted address */
		VCONV_INFO("convert tiling address [VEU]\n");
		VCONV_TEST("convert address %08x, %08x, offset %08x, %08x\n",
			adr[VCONV_PLANE_A].addr, adr[VCONV_PLANE_B].addr,
			prm->out_buffer[VCONV_PLANE_A].offset,
			prm->out_buffer[VCONV_PLANE_B].offset);
		adr[VCONV_PLANE_A].addr = phys_to_tile(adr[VCONV_PLANE_A].addr);
		adr[VCONV_PLANE_A].addr +=
				prm->out_buffer[VCONV_PLANE_A].offset;
		adr[VCONV_PLANE_B].addr = phys_to_tile(adr[VCONV_PLANE_B].addr);
		adr[VCONV_PLANE_B].addr +=
				prm->out_buffer[VCONV_PLANE_B].offset;
		VCONV_TEST("converted address %08x, %08x\n",
			adr[VCONV_PLANE_A].addr, adr[VCONV_PLANE_B].addr);
	} else {
		for (idx = 0; idx < VCONV_GET_PLANE(prm->out_img.format);
								idx++)
			adr[idx].addr += prm->out_buffer[idx].offset;
	}

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_conv_address(struct vconv_dev *pdev,
		struct vconv_param_ex *prm,
		struct vconv_conv_adr *adr)
{
	int idx;

	VCONV_FUNC_START("\n");

	/* check input parameters */
	if ((pdev == NULL) || (prm == NULL) || (adr == NULL)) {
		VCONV_ERR("invalid parameter pdev[%p], prm[%p], adr[%p]\n",
			pdev, prm, adr);
		return VCONV_NG;
	}

	/* 3 planes x in/out */
	memset(adr, 0, sizeof(struct vconv_conv_adr) * VCONV_PLANE_MAX * 2);

	/* convert input image phys address from fd */
	for (idx = 0; idx < VCONV_GET_PLANE(prm->in_img.format); idx++) {
		if (vconv_get_phys_addr(pdev, &(prm->in_buffer[idx]),
				&(adr[idx]), DMA_TO_DEVICE) != VCONV_OK) {
			VCONV_ERR("vconv_get_phys_addr() failed in_img[%d]\n",
				idx);
			goto ERR_vconv_get_phys_addr;
		}
#if defined(_TEST_BUILD_)
{
#if 0
		__u8 *p, *p2;
		int i;

		p2 = dma_buf_kmap(adr[idx].db, 0);
		p = p2 + prm->in_buffer[idx].offset;
		VCONV_TEST("plane No.%d, addr:%p\n", idx, p);

		for (i = 0; i < 1024; i += 16) {
			VCONV_TEST("%08x %02x %02x %02x %02x %02x %02x " \
				"%02x %02x %02x %02x %02x %02x %02x %02x " \
				"%02x %02x\n",
				i, p[i + 0], p[i + 1], p[i + 2], p[i + 3],
				p[i + 4], p[i + 5], p[i + 6], p[i + 7],
				p[i + 8], p[i + 9], p[i + 10], p[i + 11],
				p[i + 12], p[i + 13], p[i + 14], p[i + 15]);
		}
		dma_buf_kunmap(adr[idx].db, 0, p2);
#endif
}
#endif	/* _TEST_BUILD_ */
	}

	for (idx = 0; idx < VCONV_GET_PLANE(prm->out_img.format); idx++) {
		if (vconv_get_phys_addr(pdev, &(prm->out_buffer[idx]),
				&(adr[VCONV_PLANE_MAX + idx]),
				DMA_FROM_DEVICE) != VCONV_OK) {
			VCONV_ERR("vconv_get_phys_addr() failed out_img[%d]\n",
				idx);
			goto ERR_vconv_get_phys_addr;
		}
	}

	/* convert phys address to tile address */
	vconv_conv_tiling_addr(prm, adr);

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;

ERR_vconv_get_phys_addr:
	/* release converted address */
	for (idx = 0; idx < VCONV_GET_PLANE(prm->in_img.format); idx++) {
		vconv_put_phys_addr(&(prm->in_buffer[idx]),
				&(adr[idx]), DMA_TO_DEVICE);
	}

	for (idx = 0; idx < VCONV_GET_PLANE(prm->out_img.format); idx++) {
		vconv_put_phys_addr(&(prm->out_buffer[idx]),
				&(adr[VCONV_PLANE_MAX + idx]), DMA_FROM_DEVICE);
	}

	VCONV_FUNC_END("NG\n");

	return VCONV_NG;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_free_address(struct vconv_dev *pdev,
		struct vconv_param_ex *prm,
		struct vconv_conv_adr *adr)
{
	int idx;

	VCONV_FUNC_START("\n");

	/* check input parameters */
	if ((pdev == NULL) || (prm == NULL) || (adr == NULL)) {
		VCONV_ERR("invalid parameter pdev[%p], prm[%p], adr[%p]\n",
			pdev, prm, adr);
		return VCONV_NG;
	}

	/* release converted address */
	for (idx = 0; idx < VCONV_GET_PLANE(prm->in_img.format); idx++) {
		vconv_put_phys_addr(&(prm->in_buffer[idx]),
				&(adr[idx]), DMA_TO_DEVICE);
	}

	for (idx = 0; idx < VCONV_GET_PLANE(prm->out_img.format); idx++) {
#if defined(_TEST_BUILD_)
{
#if 0
		__u8 *p, *p2;
		int i;

		p2 = dma_buf_kmap(adr[idx + VCONV_PLANE_MAX].db, 0);
		p = p2 + prm->out_buffer[idx].offset;
		VCONV_TEST("plane No.%d, addr:%p(%p+%08x)\n",
				idx, p, p2, prm->out_buffer[idx].offset);
		for (i = 0; i < 1024; i += 16) {
			VCONV_TEST("%08x %02x %02x %02x %02x %02x %02x " \
				"%02x %02x %02x %02x %02x %02x %02x %02x " \
				"%02x %02x\n",
				i, p[i + 0], p[i + 1], p[i + 2], p[i + 3],
				p[i + 4], p[i + 5], p[i + 6], p[i + 7],
				p[i + 8], p[i + 9], p[i + 10], p[i + 11],
				p[i + 12], p[i + 13], p[i + 14], p[i + 15]);
		}
		dma_buf_kunmap(adr[idx + VCONV_PLANE_MAX].db, 0, p2);
#endif
}
#endif	/* _TEST_BUILD_ */
		vconv_put_phys_addr(&(prm->out_buffer[idx]),
				&(adr[VCONV_PLANE_MAX + idx]), DMA_FROM_DEVICE);
	}

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_get_bpp(__u32 format, __u8 *bpp)
{
	int ierr = VCONV_NG;

	VCONV_FUNC_START("format(%08x)\n", format);
	if (bpp == NULL) {
		VCONV_ERR("invalid parameters bpp(%p)\n", bpp);
		return VCONV_NG;
	}

	switch (format) {
	case VCONV_PK_T_VDU1:
	case VCONV_PK_T_VDU2:
		bpp[0] = 12;
		bpp[1] = bpp[2] = 0;
		ierr = VCONV_OK;
		break;
	case VCONV_PK_R_BGR565:
	case VCONV_PK_R_RGB565:
	case VCONV_PK_R_ABGR1555:
	case VCONV_PK_R_ARGB1555:
	case VCONV_PK_T_BGR565:
	case VCONV_PK_T_RGB565:
	case VCONV_PK_T_ABGR1555:
	case VCONV_PK_T_ARGB1555:
		bpp[0] = 16;
		bpp[1] = bpp[2] = 0;
		ierr = VCONV_OK;
		break;
	case VCONV_PK_R_ABGR8888:
	case VCONV_PK_R_ARGB8888:
	case VCONV_PK_T_ABGR8888:
	case VCONV_PK_T_ARGB8888:
	case VCONV_PK_R_AYCBCR8888:
	case VCONV_PK_R_ACBCRY8888:
	case VCONV_PK_T_AYCBCR8888:
	case VCONV_PK_T_ACBCRY8888:
		bpp[0] = 32;
		bpp[1] = bpp[2] = 0;
		ierr = VCONV_OK;
		break;
	case VCONV_FL_R_R8G8B8:
	case VCONV_FL_T_R8G8B8:
	case VCONV_FL_R_Y8CB8CR8_444:
		bpp[0] = bpp[1] = bpp[2] = 8;
		ierr = VCONV_OK;
		break;
	case VCONV_FL_R_Y8CB8CR8_422:	/* CAMERA */
		bpp[0] = 8;
		bpp[1] = bpp[2] = 4;
		ierr = VCONV_OK;
		break;
	case VCONV_FL_R_Y8CB8CR8_420:	/* VENEZIA */
	case VCONV_PT_T_Y8CB8CR8:	/* VENEZIA */
		bpp[0] = 8;
		bpp[1] = bpp[2] = 2;
		ierr = VCONV_OK;
		break;
	case VCONV_PT_R_Y8CBCR16:	/* GPU */
	case VCONV_PT_T_Y8CBCR16:	/* GPU */
	case VCONV_PT_T_VEU:
		bpp[0] = 8;
		bpp[1] = 4;
		bpp[2] = 0;
		ierr = VCONV_OK;
		break;
	}

	VCONV_FUNC_END("ret(%d)\n", ierr);

	return ierr;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_chk_pitch(struct vconv_param_ex *prm)
{
	int idx;
	__u8 bpp[VCONV_PLANE_MAX];

	VCONV_FUNC_START("\n");
	if (prm == NULL) {
		VCONV_ERR("invalid parameters prm(%p)\n", prm);
		return VCONV_NG;
	}

	/* check & modify input image(vdu1/vdu2) : pitch is over h-size */
	if (VCONV_FORMAT_IS_VDU(in, prm)) {
		VCONV_TEST("format is (vdu1/vdu2)[%s]\n",
			vconv_format_to_str(prm->in_img.format));
		for (idx = 0; idx < VCONV_GET_PLANE(prm->in_img.format);
								idx++) {
			if (prm->in_buffer[idx].pitch < prm->in_img.size.h) {
				/* set pitch to h-size */
				VCONV_INFO("change in pitch[%d] %d to %d\n",
					idx, prm->in_buffer[idx].pitch,
					prm->in_img.size.h);
				prm->in_buffer[idx].pitch = prm->in_img.size.h;
			}
		}
		goto CHK_PITCH_OUTPUT_IMAGE;
	}
	if (vconv_get_bpp(prm->in_img.format, bpp) != VCONV_OK) {
		VCONV_ERR("vconv_get_bpp() for in_img failed\n");
		return VCONV_NG;
	}
	/* check input image(YCbCr4:2:2/YCbCr4:2:0) : pitch is over h-size/2 */
	if (VCONV_FORMAT_IS_422_420_FL_R(in, prm)) {
		VCONV_TEST("format is (YCbCr4:2:2/YCbCr4:2:0)[%s]\n",
			vconv_format_to_str(prm->in_img.format));
		for (idx = 0; idx < VCONV_GET_PLANE(prm->in_img.format);
								idx++) {
			/*  */
			if (VCONV_INVALID_PITCH_HALF(in, prm, bpp, idx)) {
				VCONV_ERR("invalid in_img[%d] pitch(%d) < " \
					"h-size(%d) *bpp(%d) / 2\n",
					idx, prm->in_buffer[idx].pitch,
					prm->in_img.size.h, bpp[idx]);
				return VCONV_NG;
			}
		}
	} else {
		/* check input image(others) : pitch is over h-size */
		VCONV_TEST("format is (other YCbCr4:2:2/YCbCr4:2:0)[%s]\n",
			vconv_format_to_str(prm->in_img.format));
		for (idx = 0; idx < VCONV_GET_PLANE(prm->in_img.format);
								idx++) {
			if (VCONV_INVALID_PITCH(in, prm, bpp, idx)) {
				VCONV_ERR("invalid in_img[%d] pitch(%d) < " \
					"h-size(%d) * bpp(%d)\n",
					idx, prm->in_buffer[idx].pitch,
					prm->in_img.size.h, bpp[idx]);
				return VCONV_NG;
			}
		}
	}
CHK_PITCH_OUTPUT_IMAGE:
	/* check & modify output image(veu) : pitch is over h-size */
	if (VCONV_FORMAT_IS_VEU(out, prm)) {
		VCONV_TEST("format is (veu)[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		for (idx = 0; idx < VCONV_GET_PLANE(prm->out_img.format);
								idx++) {
			if (prm->out_buffer[idx].pitch < prm->out_img.size.h) {
				/* set pitch to h-size */
				VCONV_INFO("change out pitch[%d] %d to %d\n",
					idx, prm->out_buffer[idx].pitch,
					prm->out_img.size.h);
				prm->out_buffer[idx].pitch =
						prm->out_img.size.h;
			}
		}
		goto CHK_PITCH_END;
	}
	if (vconv_get_bpp(prm->out_img.format, bpp) != VCONV_OK) {
		VCONV_ERR("vconv_get_bpp() for out_img failed\n");
		return VCONV_NG;
	}
	/* check output image(YCbCr4:2:2/YCbCr4:2:0) : pitch is over h-size/2 */
	if (VCONV_FORMAT_IS_422_420_FL_R(out, prm)) {
		VCONV_TEST("format is (YCbCr4:2:2/YCbCr4:2:0)[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		for (idx = 0; idx < VCONV_PLANE_MAX; idx++) {
			if (VCONV_INVALID_PITCH_HALF(out, prm, bpp, idx)) {
				VCONV_ERR("invalid out_img[%d] pitch(%d) < " \
					"h-size(%d) * bpp(%d) / 2\n",
					idx, prm->out_buffer[idx].pitch,
					prm->out_img.size.h, bpp[idx]);
				return VCONV_NG;
			}
		}
	} else {
		VCONV_TEST("format is (other YCbCr4:2:2/YCbCr4:2:0)[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		for (idx = 0; idx < VCONV_PLANE_MAX; idx++) {
			if (VCONV_INVALID_PITCH(out, prm, bpp, idx)) {
				VCONV_ERR("invalid out_img[%d] pitch(%d) < " \
					"h-size(%d) * bpp(%d)\n",
					idx, prm->out_buffer[idx].pitch,
					prm->out_img.size.h, bpp[idx]);
				return VCONV_NG;
			}
		}
	}

CHK_PITCH_END:
	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_chk_size(struct vconv_param_ex *prm)
{
	__u32 size;

	VCONV_FUNC_START("\n");
	if (prm == NULL) {
		VCONV_ERR("invalid parameters prm(%p)\n", prm);
		return VCONV_NG;
	}
	/* check input image(R8G8B8 FL T/4:2:0 PT T) : */
	/*                          h-size is 64-2016 and multiple of 32 */
	if ((prm->in_img.format == VCONV_FL_T_R8G8B8) ||
		(prm->in_img.format == VCONV_PT_T_Y8CBCR16)) {
		VCONV_TEST("in format[%s]\n",
			vconv_format_to_str(prm->in_img.format));
		if ((64 > prm->in_img.size.h) ||
			(prm->in_img.size.h > 2016) ||
			(prm->in_img.size.h & 0x001F)) {
			VCONV_ERR("invalid in_img format(%08x) h-size(%d)\n",
				prm->in_img.format, prm->in_img.size.h);
			return VCONV_NG;
		}
	} else {
		/* check input image(others) : */
		/*                  h-size is 64-2032 and multiple of 16 */
		VCONV_TEST("in format[%s]\n",
			vconv_format_to_str(prm->in_img.format));
		if ((64 > prm->in_img.size.h) ||
			(prm->in_img.size.h > 2032) ||
			(prm->in_img.size.h & 0x000F)) {
			VCONV_ERR("invalid in_img format(%08x) h-size(%d)\n",
				prm->in_img.format, prm->in_img.size.h);
			return VCONV_NG;
		}
	}
	/* check output image(R8G8B8 FL T/4:2:0 PT T) : */
	/*                  h-size is 64-2016 and multiple of 32 */
	if ((prm->out_img.format == VCONV_FL_T_R8G8B8) ||
		(prm->out_img.format == VCONV_PT_T_Y8CBCR16)) {
		VCONV_TEST("out format[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		if ((64 > prm->out_img.size.h) ||
			(prm->out_img.size.h > 2016) ||
			(prm->out_img.size.h & 0x001F)) {
			VCONV_ERR("invalid out_img format(%08x) h-size(%d)\n",
				prm->out_img.format, prm->out_img.size.h);
			return VCONV_NG;
		}
	} else {
		/* check output image(others) : */
		/*                 h-size is 64-2032 and multiple of 16 */
		VCONV_TEST("out format[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		if ((64 > prm->out_img.size.h) ||
			(prm->out_img.size.h > 2032) ||
			(prm->out_img.size.h & 0x000F)) {
			VCONV_ERR("invalid out_img format(%08x) h-size(%d)\n",
				prm->out_img.format, prm->out_img.size.h);
			return VCONV_NG;
		}
	}

	/* check input image(4:2:0 PT T) : */
	/*                  v-size is 64-1088 and multiple of 16 */
	if ((prm->in_img.format == VCONV_PT_T_Y8CBCR16) ||
		(prm->in_img.format == VCONV_PT_T_Y8CB8CR8)) {
		VCONV_TEST("in format[%s]\n",
			vconv_format_to_str(prm->in_img.format));
		if ((64 > prm->in_img.size.v) ||
			(prm->in_img.size.v > 1088) ||
			(prm->in_img.size.v & 0x000F)) {
			VCONV_ERR("invalid in_img format(%08x) v-size(%d)\n",
				prm->in_img.format, prm->in_img.size.v);
			return VCONV_NG;
		}
	} else {
		/* check input image(others) : */
		/*             v-size is 64-1088 and multiple of 8 */
		VCONV_TEST("in format[%s]\n",
			vconv_format_to_str(prm->in_img.format));
		if ((64 > prm->in_img.size.v) ||
			(prm->in_img.size.v > 1088) ||
			(prm->in_img.size.v & 0x0007)) {
			VCONV_ERR("invalid in_img format(%08x) v-size(%d)\n",
				prm->in_img.format, prm->in_img.size.v);
			return VCONV_NG;
		}
	}
	/* check output image(4:2:0 PT T) : */
	/*             v-size is 64-1088 and multiple of 16 */
	if ((prm->out_img.format == VCONV_PT_T_Y8CBCR16) ||
		(prm->out_img.format == VCONV_PT_T_Y8CB8CR8)) {
		VCONV_TEST("out format[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		if ((64 > prm->out_img.size.v) ||
			(prm->out_img.size.v > 1088) ||
			(prm->out_img.size.v & 0x000F)) {
			VCONV_ERR("invalid out_img format(%08x) v-size(%d)\n",
				prm->out_img.format, prm->out_img.size.v);
			return VCONV_NG;
		}
	} else {
		/* check output image(others) : */
		/*               v-size is 64-1088 and multiple of 8 */
		VCONV_TEST("out format[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		if ((64 > prm->out_img.size.v) ||
			(prm->out_img.size.v > 1088) ||
			(prm->out_img.size.v & 0x0007)) {
			VCONV_ERR("invalid out_img format(%08x) v-size(%d)\n",
				prm->out_img.format, prm->out_img.size.v);
			return VCONV_NG;
		}
	}

#if 0	/* don't need to do this test, because of included in the above test */
	/* check input image(all) : h-size and v-size non zero */
	if (VCONV_RECT_IS_ZERO(prm->in_img.size)) {
		VCONV_ERR("invalid in_img size(%d,%d)\n",
			prm->in_img.size.h, prm->in_img.size.v);
		return VCONV_NG;
	}
	/* check output image(all) : h-size and v-size non zero */
	if (VCONV_RECT_IS_ZERO(prm->out_img.size)) {
		VCONV_ERR("invalid out_img size(%d,%d)\n",
			prm->out_img.size.h, prm->out_img.size.v);
		return VCONV_NG;
	}
#endif
	/* check image(all) : */
	/*  output image h-size is over input image h-size * scale + offset */
	size = prm->in_img.size.h;
	VCONV_SCALING_SIZE(size, prm->out_img.hscale);
	VCONV_TEST("h-size:%d <- %d * %08x\n",
			size, prm->out_img.size.h,
			VCONV_SCALE_TO_ULONG(prm->out_img.hscale));
	if ((prm->out_img.size.h + 4) < (size + prm->out_img.offset.h)) {
		VCONV_ERR("invalid scale h-size out(%d), in(%d), " \
			"scale(%d), offset(%d)\n",
			prm->out_img.size.h, prm->in_img.size.h,
			size, prm->out_img.offset.h);
		return VCONV_NG;
	}
	/* check image(all) : */
	/* output image v-size is over input image v-size * scale + offset */
	size = prm->in_img.size.v;
	VCONV_SCALING_SIZE(size, prm->out_img.vscale);
	VCONV_TEST("v-size:%d <- %d * %08x\n",
			size, prm->out_img.size.v,
			VCONV_SCALE_TO_ULONG(prm->out_img.vscale));
	if ((prm->out_img.size.v + 4) < (size + prm->out_img.offset.v)) {
		VCONV_ERR("invalid scale v-size out(%d), in(%d), " \
			"scale(%d), offset(%d)\n",
			prm->out_img.size.v, prm->in_img.size.v,
			size, prm->out_img.offset.v);
		return VCONV_NG;
	}
	/* check image(tile) : output image size is same input image size */
	if (VCONV_GET_SCAN(prm->out_img.format) == VCONV_TILE) {
		VCONV_TEST("out format[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		if (!VCONV_RECT_IS_SAME(prm->in_img.size, prm->out_img.size)) {
			VCONV_ERR("invalid image size out(%d,%d), in(%d,%d)\n",
				prm->out_img.size.h, prm->out_img.size.v,
				prm->in_img.size.h, prm->in_img.size.v);
			return VCONV_NG;
		}
	}
	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_chk_offset(struct vconv_param_ex *prm)
{
	VCONV_FUNC_START("\n");
	if (prm == NULL) {
		VCONV_ERR("invalid parameters prm(%p)\n", prm);
		return VCONV_NG;
	}
	/* check image(tile) : output image offset is zero */
	if (VCONV_GET_SCAN(prm->out_img.format) == VCONV_TILE) {
		VCONV_TEST("out image format is TILE[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		if (!VCONV_RECT_IS_ZERO(prm->out_img.offset)) {
			VCONV_ERR("invalid image offset (%d,%d)\n",
				prm->out_img.offset.h, prm->out_img.offset.v);
			return VCONV_NG;
		}
	}
	/* check image(4:2:0) : output image v-offset is even */
	if (VCONV_GET_COLOR(prm->out_img.format) == VCONV_YCBCR420) {
		VCONV_TEST("out format[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		if (prm->out_img.offset.v & 0x0001) {
			VCONV_ERR("invalid image v-offset (%d)\n",
				prm->out_img.offset.v);
			return VCONV_NG;
		}
	}
	/* check image(4:2:2/4:2:0) : output image h-offset is even */
	if ((VCONV_GET_COLOR(prm->out_img.format) == VCONV_YCBCR422) ||
		(VCONV_GET_COLOR(prm->out_img.format) == VCONV_YCBCR420)) {
		VCONV_TEST("out format[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		if (prm->out_img.offset.h & 0x0001) {
			VCONV_ERR("invalid image h-offset (%d)\n",
				prm->out_img.offset.h);
			return VCONV_NG;
		}
	}

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_chk_align(struct vconv_param_ex *prm,
				struct vconv_conv_adr *adr)
{
	int idx;

	VCONV_FUNC_START("\n");
	if ((prm == NULL) || (adr == NULL)) {
		VCONV_ERR("invalid parameters prm(%p), adr(%p)\n", prm, adr);
		return VCONV_NG;
	}
	/* check image(all) : image buffer address is 16byte alignment */
	for (idx = 0; idx < (VCONV_PLANE_MAX * 2); idx++) {
		if ((adr[idx].enable == VCONV_ENABLE) &&
			(adr[idx].addr & 0x0000000F)) {
			VCONV_ERR("invalid image buffer[%d] is " \
				"not 16byte-align (%08x)\n",
				idx, adr[idx].addr);
			return VCONV_NG;
		}
	}

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_chk_scale(struct vconv_param_ex *prm)
{
	VCONV_FUNC_START("\n");
	if (prm == NULL) {
		VCONV_ERR("invalid parameters prm(%p)\n", prm);
		return VCONV_NG;
	}
	/* check image(all) : h-scale 1/4 - 4 */
	if ((VCONV_SCALE_MIN > VCONV_SCALE_TO_ULONG(prm->out_img.hscale)) ||
		(VCONV_SCALE_TO_ULONG(prm->out_img.hscale) > VCONV_SCALE_MAX)) {
		VCONV_ERR("invalid h-scale range [%08x]\n",
			VCONV_SCALE_TO_ULONG(prm->out_img.hscale));
		return VCONV_NG;
	}
	/* check image(all) : v-scale 1/4 - 4 */
	if ((VCONV_SCALE_MIN > VCONV_SCALE_TO_ULONG(prm->out_img.vscale)) ||
		(VCONV_SCALE_TO_ULONG(prm->out_img.vscale) > VCONV_SCALE_MAX)) {
		VCONV_ERR("invalid v-scale range [%08x]\n",
			VCONV_SCALE_TO_ULONG(prm->out_img.vscale));
		return VCONV_NG;
	}
#if 0	/* below check is covered previous check */
	/* check image(all) : h-scale is not zero */
	/* check image(all) : v-scale is not zero */
#endif
	/* check output image(tile) : h-scale is one */
	/* check output image(tile) : v-scale is one */
	if ((VCONV_GET_SCAN(prm->out_img.format) == VCONV_TILE) &&
		(VCONV_SCALE_IS_NOT_ONE(prm->out_img.hscale) ||
		VCONV_SCALE_IS_NOT_ONE(prm->out_img.vscale))) {
		VCONV_TEST("out format[%s]\n",
			vconv_format_to_str(prm->out_img.format));
		VCONV_ERR("invalid tile scale h(%08x) v(%08x)\n",
			VCONV_SCALE_TO_ULONG(prm->out_img.hscale),
			VCONV_SCALE_TO_ULONG(prm->out_img.vscale));
		return VCONV_NG;
	}

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int vconv_chk_others(struct vconv_param_ex *prm)
{
	VCONV_FUNC_START("\n");
	if (prm == NULL) {
		VCONV_ERR("invalid parameters prm(%p)\n", prm);
		return VCONV_NG;
	}

	/* check image format */
	if (!VCONV_VALID_IN_FORMAT(prm->in_img.format)) {
		VCONV_ERR("invalid in image format (%08x)\n",
			prm->in_img.format);
		return VCONV_NG;
	}
	if (!VCONV_VALID_OUT_FORMAT(prm->out_img.format)) {
		VCONV_ERR("invalid out image format (%08x)\n",
			prm->out_img.format);
		return VCONV_NG;
	}
	/* check input image(except RGB PK id(2-5)) : alpha_mode is off */
	if (!((VCONV_GET_COLOR(prm->in_img.format) == VCONV_RGB) &&
		(VCONV_GET_PLANE(prm->in_img.format) == 1) &&
		VCONV_IS_FORMAT_ID_RANGE(prm->in_img.format, 2, 5))) {
		VCONV_TEST("in format[%s]\n",
			vconv_format_to_str(prm->in_img.format));
		if (prm->alpha == VCONV_ALPHA_USE_IMG) {
			VCONV_ERR("invalid alpha mode for in_img " \
				"format(%08x))\n",
				prm->in_img.format);
			return VCONV_NG;
		}
	}

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}




/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
int vconv_init_hw(struct vconv_dev *pdev)
{
#if defined(_TEST_BUILD_)
	ktime_t s, e;
#endif	/* _TEST_BUILD_ */
	VCONV_FUNC_START("\n");

	if (pdev == NULL) {
		VCONV_ERR("invalid parameters pdev(%p)\n", pdev);
		return VCONV_NG;
	}
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	/* reset assert */
	PMU_RESET_ASSERT(pdev);
	/* clock gating off */
	clk_prepare_enable(s_vconv_dev.clk);
	VCONV_TEST("pmu :ClockGatingOff:val(0x%08X)\n",
		__raw_readl(pdev->pmubase + PMU_CLOCKGATINGOFF_VCONVSS_0_OFS)&0x1);

#if defined(_TEST_BUILD_)
	s = ktime_get();
#endif	/* _TEST_BUILD_ */
	/* wait min 15ns [3 clock(200MHz)] */
	ndelay(20);
#if defined(_TEST_BUILD_)
	e = ktime_get();
	VCONV_TEST("delay time [%lld ns]\n", ktime_to_ns(ktime_sub(e, s)));
#endif	/* _TEST_BUILD_ */
	/* reset deassert */
	PMU_RESET_DEASSERT(pdev);
	spin_unlock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	vconv_set_total_page_size(pdev);

	vconv_mask_irq(pdev, false);

	/* clock stop */
	clk_disable_unprepare(s_vconv_dev.clk);
	VCONV_TEST("pmu :ClockGatingOn:val(0x%08X)\n",
		__raw_readl(pdev->pmubase + PMU_CLOCKGATINGON_VCONVSS_0_OFS)&0x1);

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
int vconv_exit_hw(struct vconv_dev *pdev)
{
	VCONV_FUNC_START("\n");

	if (pdev == NULL) {
		VCONV_ERR("invalid parameters pdev(%p)\n", pdev);
		return VCONV_NG;
	}

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
int vconv_runtime_resume_sub(struct vconv_dev *pdev)
{
	VCONV_FUNC_START("\n");

	if (pdev == NULL) {
		VCONV_ERR("invalid parameters pdev(%p)\n", pdev);
		return VCONV_NG;
	}
	spin_lock(&(pdev->lock_reg));
	/* clock gating off */
	clk_prepare_enable(pdev->clk);

	/* wait min 15ns [3 clock(200MHz)] */
	ndelay(20);
	spin_unlock(&(pdev->lock_reg));

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
int vconv_runtime_suspend_sub(struct vconv_dev *pdev)
{
	VCONV_FUNC_START("\n");

	if (pdev == NULL) {
		VCONV_ERR("invalid parameters pdev(%p)\n", pdev);
		return VCONV_NG;
	}
	spin_lock(&(pdev->lock_reg));

	/* clock gating on */
	clk_disable_unprepare(pdev->clk);

	spin_unlock(&(pdev->lock_reg));

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
void vconv_mask_irq(struct vconv_dev *pdev, bool bmask)
{
	__u32 mask = 0;
	unsigned long flags;

	VCONV_FUNC_START("\n");
	if (pdev == NULL) {
		VCONV_ERR("invalid parameters pdev(%p)\n", pdev);
		return;
	}

	if (bmask == true) {
		/* disable all interrupt */
		mask = VCONV_IRQ_ALL;
	} else {
		/* disable fconv function interrupt */
		mask = (VCONV_IRQ_DISP_ERROR | VCONV_IRQ_MERGE_ERROR);
	}
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock_irqsave(&(pdev->lock_reg), flags);
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	VCONV_WRITE(pdev, SET_IRQ_MASK, mask);
	spin_unlock_irqrestore(&(pdev->lock_reg), flags);
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	VCONV_FUNC_END("OK\n");
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
void vconv_clear_irq(struct vconv_dev *pdev, __u32 *irq)
{
	VCONV_FUNC_START("\n");
	if ((pdev == NULL) || (irq == NULL)) {
		VCONV_ERR("invalid parameters pdev(%p), irq(%p)\n",
			pdev, irq);
		return;
	}

	VCONV_READ(pdev, IRQ, *irq);
	/* one write to clear interrupt */
	VCONV_WRITE(pdev, IRQ, *irq);

	VCONV_FUNC_END("OK\n");
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long vconv_chk_params(struct vconv_dev *pdev, struct vconv_param_ex *prm)
{
	VCONV_FUNC_START("\n");

	if ((pdev == NULL) || (prm == NULL)) {
		VCONV_ERR("invalid parameters pdev(%p), prm(%p)\n", pdev, prm);
		return VCONV_NG;
	}
	/* AVOID REG_ERROR */
	if (vconv_chk_others(prm) != VCONV_OK) {
		VCONV_ERR("vconv_chk_others() failed\n");
		return VCONV_NG;
	}
	/* check image pitch */
	if (vconv_chk_pitch(prm) != VCONV_OK) {
		VCONV_ERR("vconv_chk_pitch() failed\n");
		return VCONV_NG;
	}
	if (vconv_chk_size(prm) != VCONV_OK) {
		VCONV_ERR("vconv_chk_size() failed\n");
		return VCONV_NG;
	}
	if (vconv_chk_offset(prm) != VCONV_OK) {
		VCONV_ERR("vconv_chk_offset() failed\n");
		return VCONV_NG;
	}
#if 0	/* align check is after vconv_conv_address() */
	if (vconv_chk_align(prm) != VCONV_OK) {
		VCONV_ERR("vconv_chk_align() failed\n");
		return VCONV_NG;
	}
#endif
	if (vconv_chk_scale(prm) != VCONV_OK) {
		VCONV_ERR("vconv_chk_scale() failed\n");
		return VCONV_NG;
	}

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long vconv_start_sub(struct vconv_dev *pdev, struct vconv_param_ex *prm)
{
	long ierr = 0;
	struct vconv_conv_adr conv_adr[VCONV_PLANE_MAX * 2];

	VCONV_FUNC_START("\n");

	if ((pdev == NULL) || (prm == NULL)) {
		VCONV_ERR("invalid parameters pdev(%p), prm(%p)\n", pdev, prm);
		return VCONV_NG;
	}
	/* Redmine #2067 note-#10 */
	/* convert fd to phys address, convert phys address to tile address */
	if (vconv_conv_address(pdev, prm, conv_adr) != VCONV_OK) {
		VCONV_ERR("vconv_conv_address() failed\n");
		return -EINVAL;
	}

	/* check align */
	if (vconv_chk_align(prm, conv_adr) != VCONV_OK) {
		VCONV_ERR("vconv_chk_align() failed\n");
		ierr = -EINVAL;
		goto FINISH;
	}

	VCONV_TEST("try mutex_run\n");
	mutex_lock(&(pdev->mutex_run));
	VCONV_TEST("get mutex_run\n");

	pdev->vconv_usecount++;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	VCONV_TEST("runtime_get call\n");
	pm_runtime_get_sync(&(pdev->pdev->dev));
#else
	if (pdev->vconv_usecount == 1)
		vconv_runtime_resume_sub(pdev);
#endif
	VCONV_TEST("usecount:%d\n", pdev->vconv_usecount);

	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	/* set registers */
	/* status control register */
	VCONV_WRITE(pdev, SET_DUMMY_READ, VCONV_DUMMY_READ_ON);
	VCONV_WRITE(pdev, SET_BUSIF, VCONV_OUTSTAND_CMD8);
	VCONV_WRITE(pdev, SET_SEL_ALPHA,
				(prm->alpha & VCONV_SET_SEL_ALPHA_MASK));
	/* color conversion setting register */
	if (IS_VCONV_CONV_R2Y(prm)) {
		VCONV_WRITE(pdev, SET_R2YMTX_OFFSET,
			VCONV_MK_OFFSET(prm->conv.r2y));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF00,
			(prm->conv.r2y.coef[0][0] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF01,
			(prm->conv.r2y.coef[0][1] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF02,
			(prm->conv.r2y.coef[0][2] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF10,
			(prm->conv.r2y.coef[1][0] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF11,
			(prm->conv.r2y.coef[1][1] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF12,
			(prm->conv.r2y.coef[1][2] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF20,
			(prm->conv.r2y.coef[2][0] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF21,
			(prm->conv.r2y.coef[2][1] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_R2YMTX_COEF22,
			(prm->conv.r2y.coef[2][2] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_YLIMIT,
			VCONV_MK_Y_LIMIT(prm->conv.r2y));
		VCONV_WRITE(pdev, SET_CLIMIT,
			VCONV_MK_C_LIMIT(prm->conv.r2y));
	} else if (IS_VCONV_CONV_Y2R(prm)) {
		VCONV_WRITE(pdev, SET_Y2RMTX_OFFSET,
			VCONV_MK_OFFSET(prm->conv.y2r));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF00,
			(prm->conv.y2r.coef[0][0] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF01,
			(prm->conv.y2r.coef[0][1] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF02,
			(prm->conv.y2r.coef[0][2] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF10,
			(prm->conv.y2r.coef[1][0] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF11,
			(prm->conv.y2r.coef[1][1] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF12,
			(prm->conv.y2r.coef[1][2] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF20,
			(prm->conv.y2r.coef[2][0] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF21,
			(prm->conv.y2r.coef[2][1] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_Y2RMTX_COEF22,
			(prm->conv.y2r.coef[2][2] & VCONV_MTX_COEF_MSK));
		VCONV_WRITE(pdev, SET_RGBLIMIT,
			VCONV_MK_R_LIMIT(prm->conv.y2r));
	}
	/* channel 0 transfer setting register -input image setting */
	VCONV_WRITE(pdev, SET_IN_FORMAT0, prm->in_img.format);
	VCONV_WRITE(pdev, SET_IN_HSIZE0,
			(prm->in_img.size.h & VCONV_SIZE_MSK));
	VCONV_WRITE(pdev, SET_IN_VSIZE0,
			(prm->in_img.size.v & VCONV_SIZE_MSK));
	VCONV_WRITE(pdev, SET_IN_BASEADDR_A0, conv_adr[0].addr);
	VCONV_WRITE(pdev, SET_IN_BASEADDR_B0, conv_adr[1].addr);
	VCONV_WRITE(pdev, SET_IN_BASEADDR_C0, conv_adr[2].addr);
	VCONV_WRITE(pdev, SET_IN_PITCH_A0,
			(prm->in_buffer[0].pitch & VCONV_PITCH_MSK));
	VCONV_WRITE(pdev, SET_IN_PITCH_B0,
			(prm->in_buffer[1].pitch & VCONV_PITCH_MSK));
	VCONV_WRITE(pdev, SET_IN_PITCH_C0,
			(prm->in_buffer[2].pitch & VCONV_PITCH_MSK));
	/* channel 0 transfer setting register - output image setting */
	VCONV_WRITE(pdev, SET_OUT_FORMAT0, prm->out_img.format);
	VCONV_WRITE(pdev, SET_OUT_HSIZE0,
			(prm->out_img.size.h & VCONV_SIZE_MSK));
	VCONV_WRITE(pdev, SET_OUT_VSIZE0,
			(prm->out_img.size.v & VCONV_SIZE_MSK));
	VCONV_WRITE(pdev, SET_OUT_BASEADDR_A0, conv_adr[3].addr);
	VCONV_WRITE(pdev, SET_OUT_BASEADDR_B0, conv_adr[4].addr);
	VCONV_WRITE(pdev, SET_OUT_BASEADDR_C0, conv_adr[5].addr);
	VCONV_WRITE(pdev, SET_OUT_PITCH_A0,
			(prm->out_buffer[0].pitch & VCONV_PITCH_MSK));
	VCONV_WRITE(pdev, SET_OUT_PITCH_B0,
			(prm->out_buffer[1].pitch & VCONV_PITCH_MSK));
	VCONV_WRITE(pdev, SET_OUT_PITCH_C0,
			(prm->out_buffer[2].pitch & VCONV_PITCH_MSK));
	VCONV_WRITE(pdev, SET_OUT_HOFFSET0,
			(prm->out_img.offset.h & VCONV_OUT_OFFSET_MSK));
	VCONV_WRITE(pdev, SET_OUT_VOFFSET0,
			(prm->out_img.offset.v & VCONV_OUT_OFFSET_MSK));
	VCONV_WRITE(pdev, SET_OUT_HSCALE0,
			VCONV_MK_SCALE(prm->out_img.hscale));
	VCONV_WRITE(pdev, SET_OUT_VSCALE0,
			VCONV_MK_SCALE(prm->out_img.vscale));
	VCONV_WRITE(pdev, SET_OUT_HDELTA0,
			(prm->out_img.delta.h & VCONV_DELTA_MSK));
	VCONV_WRITE(pdev, SET_OUT_VDELTA0,
			(prm->out_img.delta.v & VCONV_DELTA_MSK));
	/* channel 0 transfer setting register - data setting */
	VCONV_WRITE(pdev, SET_FORCE_MODE0,
			(prm->force_mode.mode & VCONV_FORCE_MODE_MSK));
	VCONV_WRITE(pdev, SET_FORCE_GY0,
			(prm->force_mode.gy & VCONV_FORCE_MSK));
	VCONV_WRITE(pdev, SET_FORCE_BCB0,
			(prm->force_mode.bcb & VCONV_FORCE_MSK));
	VCONV_WRITE(pdev, SET_FORCE_RCR0,
			(prm->force_mode.rcr & VCONV_FORCE_MSK));
	VCONV_WRITE(pdev, SET_FORCE_A0,
			(prm->force_mode.alpha & VCONV_FORCE_MSK));
	VCONV_WRITE(pdev, SET_CROP0, VCONV_MK_CROP(prm->crop));

	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");
	spin_lock(&(pdev->lock_dev));
	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");

	pdev->b_run = VCONV_STAT_RUN;
	spin_unlock(&(pdev->lock_dev));
	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");

	DUMP_VCONV_DEV(pdev);		/* for TEST */

	/* start */
	VCONV_WRITE(pdev, START, VCONV_START_ON);

	spin_unlock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	/* wait for completion */
#if 1	/* Redmine #2734 */
	VCONV_INFO("wait_for_completion() start.\n");
	wait_for_completion(&(pdev->comp));
	VCONV_INFO("wait_for_completion() end.\n");
#else
	VCONV_INFO("wait_for_completion_interruptible() start.\n");
	ierr = wait_for_completion_interruptible(&(pdev->comp));
	VCONV_INFO("wait_for_completion_interruptible() [%ld] end.\n", ierr);

	if (signal_pending(current)) {
		VCONV_INFO("wakeup by signal()\n");
		vconv_cancel_sub(pdev);
		ierr = -EINTR;
	}
#endif

	pdev->vconv_usecount--;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	VCONV_TEST("runtime_put call\n");
	pm_runtime_put_sync(&(pdev->pdev->dev));
#else
	if (!pdev->vconv_usecount)
		vconv_runtime_suspend_sub(pdev);
#endif
	VCONV_TEST("usecount:%d\n", pdev->vconv_usecount);

FINISH:
	VCONV_TEST("free mutex_run\n");
	mutex_unlock(&(pdev->mutex_run));

	if (vconv_free_address(pdev, prm, conv_adr) != VCONV_OK) {
		VCONV_ERR("vconv_free_address() failed\n");
		ierr = -EFAULT;
	}

	DUMP_VCONV_DEV(pdev);		/* for TEST */

	VCONV_FUNC_END("ret(%ld)\n", ierr);
	return ierr;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long vconv_cancel_sub(struct vconv_dev *pdev)
{
	__u32 regs;

	VCONV_FUNC_START("\n");

	if (pdev == NULL) {
		VCONV_ERR("invalid parameters pdev(%p)\n", pdev);
		return VCONV_NG;
	}

	pdev->vconv_usecount++;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	VCONV_TEST("runtime_get call\n");
	pm_runtime_get_sync(&(pdev->pdev->dev));
#else
	if (pdev->vconv_usecount == 1)
		vconv_runtime_resume_sub(pdev);
#endif
	VCONV_TEST("usecount:%d\n", pdev->vconv_usecount);

	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");
	spin_lock(&(pdev->lock_dev));
	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");

	/* check running status */
	if (pdev->b_run != VCONV_STAT_IDLE) {
		DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
		spin_lock(&(pdev->lock_reg));
		DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
		/* do abort */
		VCONV_INFO("force abort\n");
		VCONV_WRITE(pdev, ABORT, VCONV_ABORT_ON);
		/* wait for idle state */
		do {
			/* delay */
			VCONV_READ(pdev, TRANS_STATUS, regs);
			VCONV_INFO("read status[%08x]\n", regs);
		} while (regs & VCONV_TRANS_STATUS_RUN);
		VCONV_INFO("vconv status become to idle\n");
		spin_unlock(&(pdev->lock_reg));
		DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
		pdev->b_run = VCONV_STAT_ABORT;
		complete(&(pdev->comp));
	}

	spin_unlock(&(pdev->lock_dev));
	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");

	pdev->vconv_usecount--;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	VCONV_TEST("runtime_put call\n");
	pm_runtime_put_sync(&(pdev->pdev->dev));
#else
	if (!pdev->vconv_usecount)
		vconv_runtime_suspend_sub(pdev);
#endif
	VCONV_TEST("usecount:%d\n", pdev->vconv_usecount);

	DUMP_VCONV_DEV(pdev);		/* for TEST */

	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long vconv_verify_sub(struct vconv_dev *pdev, struct vconv_verify *verify)
{
	int iret;
	struct vconv_conv_adr adr;
	struct vconv_buffer_ex buf_ex;

	VCONV_FUNC_START("\n");

	if (pdev == NULL) {
		VCONV_ERR("invalid parameters pdev(%p)\n", pdev);
		return VCONV_NG;
	}
	/* get vtile address */
	buf_ex.mode   = VCONV_USE_FD;
	buf_ex.fd     = verify->buf.fd;
	buf_ex.offset = verify->buf.offset;
	buf_ex.pitch  = verify->buf.pitch;
	iret = vconv_get_phys_addr(pdev, &buf_ex, &adr, DMA_TO_DEVICE);
	if (iret != VCONV_OK)
		return -EINVAL;

	adr.addr = phys_to_tile(adr.addr);
	adr.addr += verify->buf.offset;

	/* compare data */
	iret = check_veu_data((__u32)(adr.addr), (__u32)(verify->exp_buf),
			verify->exp_rect.h, verify->exp_rect.v);
	if (iret != VCONV_OK)
		return -EINVAL;


	VCONV_FUNC_END("OK\n");

	return VCONV_OK;
}



/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
int vconv_set_total_page_size(struct vconv_dev *pdev)
{
	struct resource		*fdramc_res;
	struct resource		*econf_res;
	__u8 __iomem		*econf;
	__u8 __iomem		*fdramc;
	__u8 pagesize,	/* 3bit enable */
		 addr_conf_col, bwhalf_mode;

	VCONV_FUNC_START("\n");

	fdramc_res = platform_get_resource_byname(pdev->pdev,
						IORESOURCE_MEM, "fdramc");
	if (fdramc_res == NULL)
		return -EFAULT;

	econf_res = platform_get_resource_byname(pdev->pdev,
						IORESOURCE_MEM, "econf");
	if (econf_res == NULL)
		return -EFAULT;

	econf = (__u8 __iomem *)ioremap(econf_res->start,
						resource_size(econf_res));
	if (econf == NULL) {
		VCONV_ERR("ioremap() failed ECONF Registers[%08x - %d]\n",
			econf_res->start, resource_size(econf_res));
		return -ENOMEM;
	}
	fdramc = (__u8 __iomem *)ioremap(fdramc_res->start,
						resource_size(fdramc_res));
	if (fdramc == NULL) {
		VCONV_ERR("ioremap() failed FDRAMC Registers[%08x - %d]\n",
			fdramc_res->start, resource_size(fdramc_res));
		iounmap(econf);
		return -ENOMEM;
	}
	addr_conf_col = (__raw_readl(fdramc + FDRAMC_AddressConfig_Col_OFFS) >> 8) & 0xF;
	bwhalf_mode = (__raw_readl(fdramc + FDRAMC_BWHalfMode_OFFS) & 0x1);
	pagesize = addr_conf_col + (bwhalf_mode == 0 ? 2 : 1) - 10;
	VCONV_INFO("totalpagesize(%d), AddressConfig_Col(%02x), " \
		"bwhalfMode(%d)\n",
		pagesize, addr_conf_col, bwhalf_mode);
	__raw_writel(pagesize, (econf + ECONF_VTILE_SETTING_OFFS));
	iounmap(econf);
	iounmap(fdramc);
	VCONV_FUNC_END("OK\n");
	return VCONV_OK;
}


