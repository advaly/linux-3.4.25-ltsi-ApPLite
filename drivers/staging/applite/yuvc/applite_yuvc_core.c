/*
 * linux/drivers/staging/applite/applite_yuvc_core.c
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

/*===================================
 Include Files
===================================*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/dma-buf.h>
#include <linux/delay.h>

#include <linux/applite/applite_yuvc.h>
#include "applite_yuvc_internal.h"
#include "applite_yuvc_dbg.h"

/*===================================
Static Variables and Functions prototypes
===================================*/

/* parameters checking functions */
/* static int yuvc_get_bpp(__u32 format, __u8 *bpp); */
static int yuvc_get_in_buff_num(struct yuvc_dev *pdev, __u8 format);
static int yuvc_trans_fifo(struct yuvc_dev *pdev,
	struct yuvc_param *prm, struct yuvc_conv_adr *conv_adr);
static int yuvc_chk_pitch(struct yuvc_param *prm);
static int yuvc_chk_size(struct yuvc_param *prm);
static int yuvc_chk_offset(struct yuvc_param *prm);
static int yuvc_chk_align(struct yuvc_param *prm, struct yuvc_conv_adr *adr);
static int yuvc_chk_coef(struct yuvc_param *prm);
static int yuvc_chk_others(struct yuvc_param *prm);

/* address converting functions */
static int yuvc_get_phys_addr(struct yuvc_dev *pdev,
		struct yuvc_buffer *prm,
		struct yuvc_conv_adr *padr,
		enum dma_data_direction dir);
static int yuvc_put_phys_addr(struct yuvc_buffer *prm,
		struct yuvc_conv_adr *padr,
		enum dma_data_direction dir);
static int yuvc_conv_address(struct yuvc_dev *pdev,
		struct yuvc_param *prm,
		struct yuvc_conv_adr *adr);
static int yuvc_free_address(struct yuvc_dev *pdev,
		struct yuvc_param *prm,
		struct yuvc_conv_adr *adr);

/*===================================
Global Variables and Functions prototypes
===================================*/
static int bpp_list[4] = {  /* byte per pixel */
		4,		/* ARGB8888 : 2 pixel/64 bit */
		4,		/* RGBA8888 : 2 pixel/64 bit */
		3,		/* RGB888   : 8 pixel/192 bit */
		2		/* RGB565   : 4 pixel/64 bit */
};

#ifndef YUVC_USE_GDMAC
static __u32 *pIn0, *pIn02;		/* conv_adr[0] */
static __u32 *pIn1, *pIn12;		/* conv_adr[1] */
static __u32 *pIn2, *pIn22;		/* conv_adr[2] */
#endif

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
static int yuvc_get_in_buff_num(struct yuvc_dev *pdev,
		__u8 format)
{
	if ((pdev == NULL) || !(YUVC_VALID_IN_FORMAT(format))) {
		YUVC_ERR("invalid parameter pdev[%p], format[%d]\n",
			pdev, format);
		return YUVC_NG;
	}
	switch ((int)format) {
	case	YUVC_YUY2:
	case	YUVC_YUY2_1:
		pdev->i_in_buff_num = 1;
		break;
	case	YUVC_NV12:
		pdev->i_in_buff_num = 2;
		break;
	case	YUVC_I420:
		pdev->i_in_buff_num = 3;
		break;
	}

	return YUVC_OK;
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
static int yuvc_get_phys_addr(struct yuvc_dev *pdev,
		struct yuvc_buffer *prm,
		struct yuvc_conv_adr *padr,
		enum dma_data_direction dir)
{
	YUVC_FUNC_START("\n");

	/* check input parameters */
	if ((pdev == NULL) || (prm == NULL) || (padr == NULL)) {
		YUVC_ERR("invalid parameter pdev[%p], prm[%p], padr[%p]\n",
			pdev, prm, padr);
		return YUVC_NG;
	}
	if (prm->mode != YUVC_USE_FD) {
		padr->db = (struct dma_buf *)NULL;
		padr->dba = (struct dma_buf_attachment *)NULL;
		padr->sg = (struct sg_table *)NULL;
		padr->addr = (dma_addr_t)prm->phys_addr;
		padr->enable = YUVC_ENABLE;
		DUMP_YUVC_CONV_ADR(padr);
		YUVC_FUNC_END("OK\n");
		return YUVC_OK;
	}
	/* get phys address from fd */
	padr->db = dma_buf_get(prm->fd);
	if (IS_ERR(padr->db)) {
		YUVC_ERR("dma_buf_get() failed fd[%d]\n", prm->fd);
		return YUVC_NG;
	}
#if 0	/* for IT */
	padr->db = NULL;
#endif	/* for IT */
	padr->dba = dma_buf_attach(padr->db, pdev->device);
	if (IS_ERR(padr->dba)) {
		YUVC_ERR("dma_buf_attach() failed db[%p]\n", padr->db);
		goto ERR_dma_buf_attach;
	}
#if 0	/* for IT */
	padr->dba = NULL;
#endif	/* for IT */
	padr->sg = dma_buf_map_attachment(padr->dba, dir);
	if (IS_ERR(padr->sg)) {
		YUVC_ERR("dma_buf_map_attachment() failed dba[%p]\n",
			padr->dba);
		goto ERR_dma_buf_map_attachment;
	}
	/* convert sg_table to dma_addr_t */
	padr->addr = sg_phys(padr->sg->sgl);
	YUVC_INFO("converted address[%08x], sg's dma_address(%08x)\n",
		padr->addr, padr->sg->sgl->dma_address);
	padr->enable = YUVC_ENABLE;

	DUMP_YUVC_CONV_ADR(padr);
	YUVC_FUNC_END("OK\n");

	return YUVC_OK;

ERR_dma_buf_map_attachment:
	dma_buf_detach(padr->db, padr->dba);
ERR_dma_buf_attach:
	dma_buf_put(padr->db);

	YUVC_FUNC_END("NG\n");

	return YUVC_NG;
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
static int yuvc_put_phys_addr(struct yuvc_buffer *prm,
		struct yuvc_conv_adr *padr,
		enum dma_data_direction dir)
{
	YUVC_FUNC_START("\n");

	/* check input parameters */
	if ((prm == NULL) || (padr == NULL)) {
		YUVC_ERR("invalid parameter prm[%p], padr[%p]\n", prm, padr);
		return YUVC_NG;
	}
	DUMP_YUVC_CONV_ADR(padr);

	if (padr->enable != (__u8)YUVC_ENABLE) {
		YUVC_INFO("addr enable is YUVC_DISABLE\n");
		return YUVC_OK;
	}
	if (prm->mode != YUVC_USE_FD) {
		padr->enable = YUVC_DISABLE;
		YUVC_FUNC_END("OK\n");
		return YUVC_OK;
	}
	/* release address */
	if (!IS_ERR_OR_NULL(padr->dba) && !IS_ERR_OR_NULL(padr->sg))
		dma_buf_unmap_attachment(padr->dba, padr->sg, dir);

	if (!IS_ERR_OR_NULL(padr->db) && !IS_ERR_OR_NULL(padr->dba))
		dma_buf_detach(padr->db, padr->dba);

	if (!IS_ERR_OR_NULL(padr->db))
		dma_buf_put(padr->db);

	padr->enable = YUVC_DISABLE;

	DUMP_YUVC_CONV_ADR(padr);

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
static int yuvc_conv_address(struct yuvc_dev *pdev,
		struct yuvc_param *prm,
		struct yuvc_conv_adr *adr)
{
	int idx;

	YUVC_FUNC_START("\n");

	/* check input parameters */
	if ((pdev == NULL) || (prm == NULL) || (adr == NULL)) {
		YUVC_ERR("invalid parameter pdev[%p], prm[%p], adr[%p]\n",
			pdev, prm, adr);
		return YUVC_NG;
	}
	if (yuvc_get_in_buff_num(pdev, prm->img.in_format)) {
		YUVC_ERR("can not get input buffer num\n");
		return YUVC_NG;
	}

	/* input buff + output buff */
	memset(adr, 0, sizeof(struct yuvc_conv_adr) * (YUVC_INPUT_BUF_NUM+YUVC_OUTPUT_BUF_NUM));

	/* convert input image phys address from fd */
	for (idx = 0; idx < pdev->i_in_buff_num; idx++) {
		if (yuvc_get_phys_addr(pdev, &(prm->in_buffer[idx]),
				&(adr[idx]), DMA_TO_DEVICE) != YUVC_OK) {
			YUVC_ERR("yuvc_get_phys_addr() failed in_img[%d]\n",
				idx);
			goto ERR_yuvc_get_phys_addr;
		}
	}

	if (yuvc_get_phys_addr(pdev, &(prm->out_buffer),
			&(adr[YUVC_INPUT_BUF_NUM]),
			DMA_FROM_DEVICE) != YUVC_OK) {
		YUVC_ERR("yuvc_get_phys_addr() failed out_img[%d]\n",
			idx);
		goto ERR_yuvc_get_phys_addr;
	}

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;

ERR_yuvc_get_phys_addr:
	/* release converted address */
	for (idx = 0; idx < YUVC_INPUT_BUF_NUM; idx++) {
		yuvc_put_phys_addr(&(prm->in_buffer[idx]),
				&(adr[idx]), DMA_TO_DEVICE);
	}

	yuvc_put_phys_addr(&(prm->out_buffer),
			&(adr[YUVC_INPUT_BUF_NUM]), DMA_FROM_DEVICE);

	YUVC_FUNC_END("NG\n");

	return YUVC_NG;
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
static int yuvc_free_address(struct yuvc_dev *pdev,
		struct yuvc_param *prm,
		struct yuvc_conv_adr *adr)
{
	int idx;

	YUVC_FUNC_START("\n");

	/* check input parameters */
	if ((pdev == NULL) || (prm == NULL) || (adr == NULL)) {
		YUVC_ERR("invalid parameter pdev[%p], prm[%p], adr[%p]\n",
			pdev, prm, adr);
		return YUVC_NG;
	}

	/* release converted address */
	for (idx = 0; idx < pdev->i_in_buff_num; idx++) {
		yuvc_put_phys_addr(&(prm->in_buffer[idx]),
				&(adr[idx]), DMA_TO_DEVICE);
	}

	yuvc_put_phys_addr(&(prm->out_buffer),
			&(adr[YUVC_INPUT_BUF_NUM]), DMA_FROM_DEVICE);

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
/* check vuvc_param's out_buffer.pitch */
static int yuvc_chk_pitch(struct yuvc_param *prm)
{
	YUVC_FUNC_START("\n");
	if (prm == NULL) {
		YUVC_ERR("invalid parameters prm(%p)\n", prm);
		return YUVC_NG;
	}

	YUVC_TEST("output pitch=%d", prm->out_buffer.pitch);
	if (!YUVC_IS_CHECK_RANGE(prm->out_buffer.pitch, 1, 32768)) {
		YUVC_ERR("invalid output buffer pitch %d\n",
			prm->out_buffer.pitch);
		return YUVC_NG;
	}

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
static int yuvc_chk_size(struct yuvc_param *prm)
{
	YUVC_FUNC_START("\n");

	if (prm == NULL) {
		YUVC_ERR("invalid parameters prm(%p)\n", prm);
		return YUVC_NG;
	}

	YUVC_TEST("size(h/v)=(%d/%d)\n", prm->img.size.h, prm->img.size.v);

	/* check input image v size :						*/
	/*		420 v-size is 120-2046 and multiple of 2	*/
	if ((prm->img.in_format == YUVC_NV12) ||
		(prm->img.in_format == YUVC_I420)) {
		YUVC_TEST("in format[%s]\n",
			yuvc_format_to_str(prm->img.in_format));
		if ((!YUVC_IS_CHECK_RANGE(prm->img.size.v, 120, 2046)) ||
			(prm->img.size.v & 0x0001)) {
			YUVC_ERR("invalid in_img format(%08x) v-size(%d)\n",
				prm->img.in_format, prm->img.size.v);
			return YUVC_NG;
		}
	} else {
		/* check input image v size :	*/
		/*		422 v-size is 120-2046	*/
		YUVC_TEST("in format[%s]\n",
			yuvc_format_to_str(prm->img.in_format));
		if (!YUVC_IS_CHECK_RANGE(prm->img.size.v, 120, 2046)) {
			YUVC_ERR("invalid in_img format(%08x) v-size(%d)\n",
				prm->img.in_format, prm->img.size.v);
			return YUVC_NG;
		}
	}

	/* check input image h size :	*/
	/*		h-size is 160-2046		*/
	if (!YUVC_IS_CHECK_RANGE(prm->img.size.h, 160, 2046)) {
		YUVC_ERR("invalid in_img format(%08x) h-size(%d)\n",
			prm->img.in_format, prm->img.size.h);
		return YUVC_NG;
	}

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
/* check vuvc_param's conv.in_offset[0-2], conv.out_offset[0-2] */
static int yuvc_chk_offset(struct yuvc_param *prm)
{
	int			i;

	YUVC_FUNC_START("\n");
	if (prm == NULL) {
		YUVC_ERR("invalid parameters prm(%p)\n", prm);
		return YUVC_NG;
	}

	for (i = 0; i < YUVC_INPUT_YUV_MAX; i++) {
		if (prm->conv.in_offset[i] & (__s16)0xfe00) {
			YUVC_ERR("invalid input offset[%d] (0x%04x)\n",
					i, prm->conv.in_offset[i]);
			return YUVC_NG;
		}
	}

	for (i = 0; i < YUVC_OUTPUT_RGB_MAX; i++) {
		if (prm->conv.out_offset[i] & (__s16)0xfe00) {
			YUVC_ERR("invalid output offset[%d] (0x%04x)\n",
					i, prm->conv.out_offset[i]);
			return YUVC_NG;
		}
	}
	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
static int yuvc_chk_align(struct yuvc_param *prm, struct yuvc_conv_adr *adr)
{
	int idx;

	YUVC_FUNC_START("\n");
	if ((prm == NULL) || (adr == NULL)) {
		YUVC_ERR("invalid parameters prm(%p), adr(%p)\n", prm, adr);
		return YUVC_NG;
	}

	/* check image(all) : image buffer address is 16byte alignment */
	for (idx = 0; idx < (YUVC_INPUT_BUF_NUM+YUVC_OUTPUT_BUF_NUM); idx++) {
		if ((adr[idx].enable == YUVC_ENABLE) &&
			(adr[idx].addr & 0x0000000F)) {
			YUVC_ERR("invalid image buffer[%d] is " \
				"not 16byte-align (%08x)\n",
				idx, adr[idx].addr);
			return YUVC_NG;
		}
	}

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
/* check vuvc_param's conv.yconef[0-2], conv.ucoef[0-2], conv.vcoef[0-2] */
static int yuvc_chk_coef(struct yuvc_param *prm)
{
	int		i;

	YUVC_FUNC_START("\n");
	if (prm == NULL) {
		YUVC_ERR("invalid parameters prm(%p)\n", prm);
		return YUVC_NG;
	}

	for (i = 0; i < YUVC_INPUT_COEF_MAX; i++) {
		if (prm->conv.ycoef[i] & (__s16)0xfe00) {
			YUVC_ERR("invalid Y input coefficient[%d] (0x%04x)\n",
					i, prm->conv.ycoef[i]);
			return YUVC_NG;
		}
	}
	for (i = 0; i < YUVC_INPUT_COEF_MAX; i++) {
		if (prm->conv.ucoef[i] & (__s16)0xfc00) {
			YUVC_ERR("invalid U input coefficient[%d] (0x%04x)\n",
					i, prm->conv.ucoef[i]);
			return YUVC_NG;
		}
	}
	for (i = 0; i < YUVC_INPUT_COEF_MAX; i++) {
		if (prm->conv.vcoef[i] & (__s16)0xfc00) {
			YUVC_ERR("invalid V input coefficient[%d] (0x%04x)\n",
					i, prm->conv.vcoef[i]);
			return YUVC_NG;
		}
	}
	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
static int yuvc_chk_others(struct yuvc_param *prm)
{
	int			i;

	YUVC_FUNC_START("\n");
	if (prm == NULL) {
		YUVC_ERR("invalid parameters prm(%p)\n", prm);
		return YUVC_NG;
	}

	/* check image format */
	if (!YUVC_VALID_IN_FORMAT(prm->img.in_format)) {
		YUVC_ERR("invalid in image format (%08x)\n",
			prm->img.in_format);
		return YUVC_NG;
	}
	if (!YUVC_VALID_OUT_FORMAT(prm->img.out_format)) {
		YUVC_ERR("invalid out image format (%08x)\n",
			prm->img.out_format);
		return YUVC_NG;
	}

	/* check buffer mode */
	for (i = 0; i < YUVC_INPUT_BUF_NUM; i++) {
		if (!YUVC_VALID_BUF_MODE(prm->in_buffer[i].mode)) {
			YUVC_INFO("input buffer[%d] mode %d\n",
				i, (int)prm->in_buffer[i].mode);
			continue;
		}
		if (prm->in_buffer[i].mode == YUVC_USE_FD) {
			/* check prm->in_buffer[i].fd */
			YUVC_INFO("in buffer mode is YUVC_USE_FD\n");
		}
		if (prm->in_buffer[i].mode == YUVC_USE_ADDRESS) {
			/* check prm->in_buffer[i].phys_addr */
			YUVC_INFO("in buffer mode is YUVC_USE_ADDRESS\n");
		}
	}
	if (!YUVC_VALID_BUF_MODE(prm->out_buffer.mode)) {
		YUVC_ERR("invalid output buffer mode %d\n",
			(int)prm->out_buffer.mode);
		return YUVC_NG;
	}
	if (prm->out_buffer.mode == YUVC_USE_FD) {
		/* check prm->out_buffer.fd */	/* T.B.D. */
		YUVC_INFO("out buffer mode is YUVC_USE_FD\n");
	}
	if (prm->out_buffer.mode == YUVC_USE_ADDRESS) {
		/* check prm->out_buffer.phys_addr */	/* T.B.D */
		YUVC_INFO("out buffer mode is YUVC_USE_ADDRESS\n");
	}
	YUVC_FUNC_END("OK\n");
	return YUVC_OK;
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
int yuvc_init_hw(struct yuvc_dev *pdev)
{
#if defined(_TEST_BUILD_)
	ktime_t s, e;
#endif	/* _TEST_BUILD_ */
	YUVC_FUNC_START("\n");

	if (pdev == NULL) {
		YUVC_ERR("invalid parameters pdev(%p)\n", pdev);
		return YUVC_NG;
	}
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	/* reset assert */
	PMU_RESET_ASSERT(pdev);
	/* clock gating off */
	clk_prepare_enable(pdev->clk);

#if defined(_TEST_BUILD_)
	s = ktime_get();
#endif	/* _TEST_BUILD_ */
	/* wait min 15ns [3 clock(200MHz)] */
	ndelay(20);
#if defined(_TEST_BUILD_)
	e = ktime_get();
	YUVC_TEST("delay time [%lld ns]\n", ktime_to_ns(ktime_sub(e, s)));
#endif	/* _TEST_BUILD_ */

	/* reset deassert */
	PMU_RESET_DEASSERT(pdev);

	clk_disable_unprepare(pdev->clk);

	spin_unlock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
int yuvc_exit_hw(struct yuvc_dev *pdev)
{
	YUVC_FUNC_START("\n");

	if (pdev == NULL) {
		YUVC_ERR("invalid parameters pdev(%p)\n", pdev);
		return YUVC_NG;
	}
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	/* clock gating off */
	clk_prepare_enable(pdev->clk);
	/* reset assert */
	PMU_RESET_ASSERT(pdev);
	/* clock gating on */
	clk_disable_unprepare(pdev->clk);
	spin_unlock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
int yuvc_runtime_resume_sub(struct yuvc_dev *pdev)
{
	YUVC_FUNC_START("\n");

	if (pdev == NULL) {
		YUVC_ERR("invalid parameters pdev(%p)\n", pdev);
		return YUVC_NG;
	}
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	/* reset assert */
	PMU_RESET_ASSERT(pdev);
	/* clock gating off */
	clk_prepare_enable(pdev->clk);

	/* wait min 15ns [3 clock(200MHz)] */
	ndelay(20);

	/* reset deassert */
	PMU_RESET_DEASSERT(pdev);

	spin_unlock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
int yuvc_runtime_suspend_sub(struct yuvc_dev *pdev)
{
	__u32 regs;

	YUVC_FUNC_START("\n");

	if (pdev == NULL) {
		YUVC_ERR("invalid parameters pdev(%p)\n", pdev);
		return YUVC_NG;
	}

	/* check status */
	YUVC_READ(pdev, W_RUN, regs);
	if (regs & 0x03)
		return -EBUSY;

	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	/* reset assert */
	PMU_RESET_ASSERT(pdev);
	/* clock gating on */
	clk_disable_unprepare(pdev->clk);
	spin_unlock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
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
void yuvc_mask_irq(struct yuvc_dev *pdev, bool bmask)
{
	__u32 mask = 0;
	unsigned long flags;

	YUVC_FUNC_START("\n");
	if (pdev == NULL) {
		YUVC_ERR("invalid parameters pdev(%p)\n", pdev);
		return;
	}

	if (bmask == true) {
		/* disable all interrupt */
		mask = YUVC_INT_MASK_ALL;
	} else {
		/* disable yuvc function interrupt */
		mask = 0x00000000;
	}
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock_irqsave(&(pdev->lock_reg), flags);
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	YUVC_WRITE(pdev, INT, mask);
	spin_unlock_irqrestore(&(pdev->lock_reg), flags);
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	YUVC_FUNC_END("OK\n");
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
void yuvc_clear_irq(struct yuvc_dev *pdev, __u32 *irq)
{
	YUVC_FUNC_START("\n");
	if ((pdev == NULL) || (irq == NULL)) {
		YUVC_ERR("invalid parameters pdev(%p), irq(%p)\n",
			pdev, irq);
		return;
	}

	YUVC_READ(pdev, INT, *irq);
	/* one write to clear interrupt */
	YUVC_WRITE(pdev, INT, *irq);

	YUVC_FUNC_END("OK\n");
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
long yuvc_chk_params(struct yuvc_dev *pdev, struct yuvc_param *prm)
{
	YUVC_FUNC_START("\n");

	if ((pdev == NULL) || (prm == NULL)) {
		YUVC_ERR("invalid parameters pdev(%p), prm(%p)\n", pdev, prm);
		return YUVC_NG;
	}
	/* check yuvc_img_param's in_format, out_format, out_alpha */
	if (yuvc_chk_others(prm) != YUVC_OK) {
		YUVC_ERR("yuvc_chk_others() failed\n");
		return YUVC_NG;
	}
	/* check vuvc_img_param's size.h, size.v */
	if (yuvc_chk_size(prm) != YUVC_OK) {
		YUVC_ERR("yuvc_chk_size() failed\n");
		return YUVC_NG;
	}
	/* check vuvc_param's conv.in_offset[0-2], conv.out_offset[0-2] */
	if (yuvc_chk_offset(prm) != YUVC_OK) {
		YUVC_ERR("yuvc_chk_offset() failed\n");
		return YUVC_NG;
	}
	/* check vuvc_param's conv.yconef[0-2], conv.ucoef[0-2], conv.vcoef[0-2] */
	if (yuvc_chk_coef(prm) != YUVC_OK) {
		YUVC_ERR("yuvc_chk_coef() failed\n");
		return YUVC_NG;
	}
	/* check vuvc_param's out_buffer.pitch */
	if (yuvc_chk_pitch(prm) != YUVC_OK) {
		YUVC_ERR("yuvc_chk_pitch() failed\n");
		return YUVC_NG;
	}

	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
}

#ifdef YUVC_USE_GDMAC
static int yuvc_trans_fifo(struct yuvc_dev *pdev, struct yuvc_param *prm, struct yuvc_conv_adr *conv_adr)
{
	int ierr;
	dma_addr_t src_addr[YUVC_INPUT_BUF_NUM];

	/* set source address */

	/*
	 *  YUY2:  [0] - Y
	 *  NV12:  [0] - Y  [1] - UV
	 *  I420:  [0] - Y  [1] - U   [2] - V
	 */
	src_addr[0] = conv_adr[0].addr + prm->in_buffer[0].offset;
	src_addr[1] = conv_adr[1].addr + prm->in_buffer[1].offset;
	src_addr[2] = conv_adr[2].addr + prm->in_buffer[2].offset;
	if (!pdev->dmac_status) {
		/* 1st frame */
		switch (prm->img.in_format) {
		case YUVC_YUY2:
		case YUVC_YUY2_1:
			pdev->dmac_type = YUVC_DMA_YUY2;
			break;

		case YUVC_NV12:
			pdev->dmac_type = YUVC_DMA_NV12;
			break;

		case YUVC_I420:
			pdev->dmac_type = YUVC_DMA_I420;
			break;
		}

		ierr = yuvc_dma_setup(pdev->dmac_type, src_addr,
		prm->img.size.h, prm->img.size.v);
		if (ierr) {
			YUVC_ERR("yuvc_dma_setup() failed errno=%d\n", ierr);
			return YUVC_NG;
		}
		pdev->dmac_status = 1;
	} else {
		/* next frame */
		yuvc_dma_next_src(pdev->dmac_type, src_addr);
	}

	/* start dma */
	yuvc_dma_start(pdev->dmac_type);

	return 0;
}
#else	/* YUVC_USE_GDMAC */
static int yuvc_trans_fifo(struct yuvc_dev *pdev, struct yuvc_param *prm, struct yuvc_conv_adr *conv_adr)
{
	int	i, j;
	int	idx[3];	/* work index number */
	int	line;
	int	dpl;	/* data num per line */

	__u8 *pOut, *pOut2;	/* conv_adr[3] */
	pIn02 = NULL;		/* conv_adr[0] */
	pIn12 = NULL;		/* conv_adr[1] */
	pIn22 = NULL;		/* conv_adr[2] */

	/* zero clear output buff */
	pOut2 = dma_buf_kmap(conv_adr[YUVC_INPUT_BUF_NUM].db, 0);
	pOut = pOut2 + prm->out_buffer.offset;
	for (i = 0; i < (prm->img.size.h * prm->img.size.v); i++)
		pOut[i] = 0;

	dma_buf_kunmap(conv_adr[YUVC_INPUT_BUF_NUM].db, 0, pOut2);

	pIn02 = dma_buf_kmap(conv_adr[0].db, 0);
	pIn0 = pIn02 + prm->in_buffer[0].offset / 4;

	if (YUVC_IN_FORMAT_IS_YUY2(prm->img.in_format)) {
		dpl = prm->img.size.h;	/* data num per line */

		for (line = 0; line < (prm->img.size.v * 2); line++) {
			for (j = 0; j < dpl; j += 32) {
				/* set Y/U/V */
				idx[0] = (dpl * line + j) / 4;

				YUVC_COPY_FIFO_L(pIn0, idx[0], pdev->pfifo[YUVC_FIFO_Y0], 8);
			}
		}

		/* dummy write */
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_Y0], 8);

	} else if (prm->img.in_format == YUVC_NV12) {
		pIn12 = dma_buf_kmap(conv_adr[1].db, 0);
		pIn1 = pIn12 + prm->in_buffer[1].offset / 4;

		dpl = prm->img.size.h;	/* data num per line */
		YUVC_TEST("check0:(size.v/size.h/dpl)=(%d/%d/%d)\n", prm->img.size.v, prm->img.size.h, dpl);

		for (line = 0; line < prm->img.size.v; line += 2) {
			for (j = 0; j < dpl; j += 16) {
				/* set U/V */
				idx[0] = (dpl * (line / 2 - 1) + j) / 4 ;		/* odd - 1.5 H */
				idx[1] = (dpl * (line / 2) + j) / 4;			/* odd + 0.5 H */
				idx[2] = (dpl * (line / 2 + 1) + j) / 4;		/* even + 1.5 H */

				if (line <= 0) {
					YUVC_COPY_FIFO_L(pIn1, idx[1], pdev->pfifo[YUVC_FIFO_C0], 4);
				} else {
					YUVC_COPY_FIFO_L(pIn1, idx[0], pdev->pfifo[YUVC_FIFO_C0], 4);
				}

				YUVC_COPY_FIFO_L(pIn1, idx[1], pdev->pfifo[YUVC_FIFO_C1], 4);

				if (line < (prm->img.size.v - 2)) {
					YUVC_COPY_FIFO_L(pIn1, idx[2], pdev->pfifo[YUVC_FIFO_C2], 4);
				} else {
					YUVC_COPY_FIFO_L(pIn1, idx[1], pdev->pfifo[YUVC_FIFO_C2], 4);
				}

				/* set Y */
				idx[0] = (dpl * line + j) / 4;		/* odd line */
				idx[1] = (dpl * (line + 1) + j) / 4;	/* even line */
				idx[2] = 0;				/* not use */

				YUVC_COPY_FIFO_L(pIn0, idx[0], pdev->pfifo[YUVC_FIFO_Y0], 4);
				YUVC_COPY_FIFO_L(pIn0, idx[1], pdev->pfifo[YUVC_FIFO_Y1], 4);
			}
		}	/* for (line < remain_size) */

		/* dummy write */
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_C0], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_C1], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_C2], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_Y0], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_Y1], 4);

	} else if (prm->img.in_format == YUVC_I420) {
		pIn12 = dma_buf_kmap(conv_adr[1].db, 0);
		pIn1 = pIn12 + prm->in_buffer[1].offset / 4;
		pIn22 = dma_buf_kmap(conv_adr[2].db, 0);
		pIn2 = pIn22 + prm->in_buffer[2].offset / 4;

		dpl = prm->img.size.h;	/* data num per line */

		for (line = 0; line < prm->img.size.v; line += 2) {
			for (j = 0; j < dpl; j += 32) {

				/* set U */
				idx[0] = (dpl * (line / 2 - 1) + j) / 8;		/* odd - 1.5 H */
				idx[1] = (dpl * (line / 2) + j) / 8;			/* odd + 0.5 H */
				idx[2] = (dpl * (line / 2 + 1) + j) / 8;		/* even + 1.5 H */

				if (line <= 0) {
					YUVC_COPY_FIFO_L(pIn1, idx[1], pdev->pfifo[YUVC_FIFO_C0], 4);
				} else {
					YUVC_COPY_FIFO_L(pIn1, idx[0], pdev->pfifo[YUVC_FIFO_C0], 4);
				}

				YUVC_COPY_FIFO_L(pIn1, idx[1], pdev->pfifo[YUVC_FIFO_C1], 4);

				if (line < (prm->img.size.v - 2)) {
					YUVC_COPY_FIFO_L(pIn1, idx[2], pdev->pfifo[YUVC_FIFO_C2], 4);
				} else {
					YUVC_COPY_FIFO_L(pIn1, idx[1], pdev->pfifo[YUVC_FIFO_C2], 4);
				}

				/* set V */
				if (line <= 0) {
					YUVC_COPY_FIFO_L(pIn2, idx[1], pdev->pfifo[YUVC_FIFO_V0], 4);
				} else {
					YUVC_COPY_FIFO_L(pIn2, idx[0], pdev->pfifo[YUVC_FIFO_V0], 4);
				}

				YUVC_COPY_FIFO_L(pIn2, idx[1], pdev->pfifo[YUVC_FIFO_V1], 4);

				if (line < (prm->img.size.v - 2)) {
					YUVC_COPY_FIFO_L(pIn2, idx[2], pdev->pfifo[YUVC_FIFO_V2], 4);
				} else {
					YUVC_COPY_FIFO_L(pIn2, idx[1], pdev->pfifo[YUVC_FIFO_V2], 4);
				}

				/* set Y */
				idx[0] = (dpl * line + j) / 4;		/* odd line */
				idx[1] = (dpl * (line + 1) + j) / 4;	/* even line */
				idx[2] = 0;				/* not use */

				YUVC_COPY_FIFO_L(pIn0, idx[0], pdev->pfifo[YUVC_FIFO_Y0], 8);
				YUVC_COPY_FIFO_L(pIn0, idx[1], pdev->pfifo[YUVC_FIFO_Y1], 8);
			}
		}	/* for (line < remain_size) */

		/* dummy write */
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_C0], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_C1], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_C2], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_V0], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_V1], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_V2], 4);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_Y0], 8);
		YUVC_SET_FIFO_L(YUVC_FIFO_DMY_VAL, pdev->pfifo[YUVC_FIFO_Y1], 8);
	}

	if (pIn02)
		dma_buf_kunmap(conv_adr[0].db, 0, pIn02);
	if (pIn12)
		dma_buf_kunmap(conv_adr[1].db, 0, pIn12);
	if (pIn22)
		dma_buf_kunmap(conv_adr[2].db, 0, pIn22);

	return 0;
}
#endif	/* YUVC_USE_GDMAC */

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long yuvc_start_sub(struct yuvc_dev *pdev, struct yuvc_param *prm)
{
	int		ierr = 0;
	__u32		u32val;
	struct yuvc_conv_adr	conv_adr[YUVC_INPUT_BUF_NUM+YUVC_OUTPUT_BUF_NUM];
	int		retry;
	unsigned long	tmo;

	YUVC_FUNC_START("\n");

	if ((pdev == NULL) || (prm == NULL)) {
		YUVC_ERR("invalid parameters pdev(%p), prm(%p)\n", pdev, prm);
		return YUVC_NG;
	}
	/* convert fd to phys address, convert phys address to tile address */
	if (yuvc_conv_address(pdev, prm, conv_adr) != YUVC_OK) {
		YUVC_ERR("yuvc_conv_address() failed\n");
		return -EINVAL;
	}

	/* check align */
	if (yuvc_chk_align(prm, conv_adr) != YUVC_OK) {
		YUVC_ERR("yuvc_chk_align() failed\n");
		yuvc_free_address(pdev, prm, conv_adr);
		return -EINVAL;
	}
	YUVC_TEST("try mutex_run\n");

	mutex_lock(&(pdev->mutex_run));
	YUVC_TEST("get mutex_run\n");

	pdev->yuvc_usecount++;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	YUVC_TEST("runtime_get call\n");
	pm_runtime_get_sync(&(pdev->pdev->dev));
#else
	if (pdev->yuvc_usecount == 1)
		yuvc_runtime_resume_sub(pdev);
#endif
	YUVC_TEST("usecount:%d\n", pdev->yuvc_usecount);

	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
	spin_lock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	/*
	 * yuvc control register
	 */
	/* Clear status register */
	YUVC_WRITE(pdev, STATUS, YUVC_STATUS_MB_ERROR_ALL);
	YUVC_WRITE(pdev, INT, YUVC_INT_ALL);
	YUVC_WRITE(pdev, W_STOP, YUVC_W_STOP_ALL);

	/* Set system register */
	YUVC_WRITE(pdev, STADR, 0x00000000);
	YUVC_WRITE(pdev, ENDADR, 0xbfffffff);

	/* Set interrupt mask */
	YUVC_WRITE(pdev, INT_MASK, 0x00000000);

	/* Set YUVC mode, coef */
	if (YUVC_OUT_FORMAT_IS_RGB8888(prm->img.out_format))
		u32val = (YUVC_VAL(prm->img.out_format, MODE_CF_OUTMODE) |
				YUVC_VAL(prm->img.in_format, MODE_CF_INMODE) |
				YUVC_VAL(prm->img.out_alpha, MODE_CF_ALPHA));
	else
		u32val = (YUVC_VAL(prm->img.out_format, MODE_CF_OUTMODE) |
				YUVC_VAL(prm->img.in_format, MODE_CF_INMODE));

	YUVC_WRITE(pdev, MODE, u32val);

	u32val = (YUVC_VAL(prm->img.size.v, SIZE_CF_VSIZE) |
				YUVC_VAL(prm->img.size.h, SIZE_CF_HSIZE));
	YUVC_WRITE(pdev, SIZE, u32val);

	u32val = YUVC_VAL(prm->conv.in_offset[YUVC_INPUT_Y], OFFSET_Y_CF_YOFFSET);
	YUVC_WRITE(pdev, OFFSET_Y, u32val);
	u32val = (YUVC_VAL(prm->conv.in_offset[YUVC_INPUT_U], OFFSET_UV_CF_UOFFSET) |
			YUVC_VAL(prm->conv.in_offset[YUVC_INPUT_V], OFFSET_UV_CF_VOFFSET));
	YUVC_WRITE(pdev, OFFSET_UV, u32val);

	u32val = (YUVC_VAL(prm->conv.out_offset[YUVC_OUTPUT_R], OFFSET_RG_CF_ROFFSET) |
			YUVC_VAL(prm->conv.out_offset[YUVC_OUTPUT_G], OFFSET_RG_CF_GOFFSET));
	YUVC_WRITE(pdev, OFFSET_RG, u32val);
	u32val = YUVC_VAL(prm->conv.out_offset[YUVC_OUTPUT_B], OFFSET_B_CF_BOFFSET);
	YUVC_WRITE(pdev, OFFSET_B, u32val);

	u32val = (YUVC_VAL(prm->conv.ycoef[YUVC_INPUT_COEF_R], YCOEF_RG_CF_YCOEF_R) |
			YUVC_VAL(prm->conv.ycoef[YUVC_INPUT_COEF_G], YCOEF_RG_CF_YCOEF_G));
	YUVC_WRITE(pdev, YCOEF_RG, u32val);
	u32val = YUVC_VAL(prm->conv.ycoef[YUVC_INPUT_COEF_B], YCOEF_B_CF_YCOEF_B);
	YUVC_WRITE(pdev, YCOEF_B, u32val);
	u32val = (YUVC_VAL(prm->conv.ucoef[YUVC_INPUT_COEF_R], UCOEF_RG_CF_UCOEF_R) |
			YUVC_VAL(prm->conv.ucoef[YUVC_INPUT_COEF_G], UCOEF_RG_CF_UCOEF_G));
	YUVC_WRITE(pdev, UCOEF_RG, u32val);
	u32val = YUVC_VAL(prm->conv.ucoef[YUVC_INPUT_COEF_B], UCOEF_B_CF_UCOEF_B);
	YUVC_WRITE(pdev, UCOEF_B, u32val);
	u32val = (YUVC_VAL(prm->conv.vcoef[YUVC_INPUT_COEF_R], VCOEF_RG_CF_VCOEF_R) |
			YUVC_VAL(prm->conv.vcoef[YUVC_INPUT_COEF_G], VCOEF_RG_CF_VCOEF_G));
	YUVC_WRITE(pdev, VCOEF_RG, u32val);
	u32val = YUVC_VAL(prm->conv.vcoef[YUVC_INPUT_COEF_B], VCOEF_B_CF_VCOEF_B);
	YUVC_WRITE(pdev, VCOEF_B, u32val);

	/* Set Data */
	if (YUVC_IN_FORMAT_IS_YUY2(prm->img.in_format)) {
		YUVC_WRITE(pdev, W_ENABLE, YUVC_W_ENABLE_CF_ENABLE_W00);
	} else {
		YUVC_WRITE(pdev, W_ENABLE, YUVC_W_ENABLE_CF_ENABLE_ALL);
	}

	if (YUVC_IN_FORMAT_IS_YUY2(prm->img.in_format)) {
		/* use 1 output port */
		YUVC_WRITE(pdev, W00_STADR, (int)(conv_adr[YUVC_INPUT_BUF_NUM].addr));
		YUVC_WRITE(pdev, W00_ENDADR,
			((int)(conv_adr[YUVC_INPUT_BUF_NUM].addr) +
			 (prm->img.size.h * bpp_list[prm->img.out_format]) - 1));

		YUVC_WRITE(pdev, W00_HEIGHT, prm->img.size.v);
		YUVC_WRITE(pdev, W00_PITCH,	prm->out_buffer.pitch);
		YUVC_WRITE(pdev, W00_CFG0,	0x00000300);

		YUVC_WRITE(pdev, W01_STADR, 0);
		YUVC_WRITE(pdev, W01_ENDADR, 0);
		YUVC_WRITE(pdev, W01_HEIGHT, 0);
		YUVC_WRITE(pdev, W01_PITCH,	0);
		YUVC_WRITE(pdev, W01_CFG0,	0x00000000);

		/* Redmine #4159 */
		YUVC_WRITE(pdev, W00_SRAM_BASE, 0x00000000);
		YUVC_WRITE(pdev, W00_SRAM_SIZE, 0x00000020);
		YUVC_WRITE(pdev, W01_SRAM_BASE, 0x00000000);
		YUVC_WRITE(pdev, W01_SRAM_SIZE, 0x00000000);
	} else {
		/* use 2 output port */
		YUVC_WRITE(pdev, W00_STADR, (int)(conv_adr[YUVC_INPUT_BUF_NUM].addr));
		YUVC_WRITE(pdev, W00_ENDADR,
			((int)(conv_adr[YUVC_INPUT_BUF_NUM].addr) +
			 (prm->img.size.h * bpp_list[prm->img.out_format]) - 1));

		YUVC_WRITE(pdev, W00_HEIGHT, (prm->img.size.v / 2));
		YUVC_WRITE(pdev, W00_PITCH,	(prm->out_buffer.pitch * 2));
		YUVC_WRITE(pdev, W00_CFG0,	0x00000300);

		YUVC_WRITE(pdev, W01_STADR,
			(int)(conv_adr[YUVC_INPUT_BUF_NUM].addr) +  (prm->img.size.h * bpp_list[prm->img.out_format]));
		YUVC_WRITE(pdev, W01_ENDADR,
			((int)(conv_adr[YUVC_INPUT_BUF_NUM].addr) +
			 (prm->img.size.h * bpp_list[prm->img.out_format] * 2) - 1));

		YUVC_WRITE(pdev, W01_HEIGHT, (prm->img.size.v / 2));
		YUVC_WRITE(pdev, W01_PITCH,	(prm->out_buffer.pitch * 2));
		YUVC_WRITE(pdev, W01_CFG0,	0x00000300);

		/* Redmine #4159 */
		YUVC_WRITE(pdev, W00_SRAM_BASE, 0x00000000);
		YUVC_WRITE(pdev, W00_SRAM_SIZE, 0x00000010);
		YUVC_WRITE(pdev, W01_SRAM_BASE, 0x00000010);
		YUVC_WRITE(pdev, W01_SRAM_SIZE, 0x00000010);
	}

	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");
	spin_lock(&(pdev->lock_dev));
	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");

	pdev->b_run = YUVC_STAT_RUN;
	spin_unlock(&(pdev->lock_dev));
	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");

	DUMP_YUVC_DEV(pdev);		/* for TEST */

	/* start */
	YUVC_WRITE(pdev, START, YUVC_START_ON);

	spin_unlock(&(pdev->lock_reg));
	DUMP_SPINLOCK(&(pdev->lock_reg), "reg");

	/* start data transfer to yuvc FIFO */
	pdev->convert_status = 0;
	ierr = yuvc_trans_fifo(pdev, prm, conv_adr);
	if (ierr)
		goto FINISH;

#if defined(_TEST_BUILD_)
#if 0	/* for IT */
	DUMP_YUVC_BUFF(conv_adr, 0, prm->in_buffer[0].offset);	/* input buffer */
	DUMP_YUVC_BUFF(conv_adr, 0, prm->in_buffer[1].offset);	/* input buffer */
	DUMP_YUVC_BUFF(conv_adr, 0, prm->in_buffer[2].offset);	/* input buffer */
#endif	/* for IT */
#endif	/* _TEST_BUILD_ */

	YUVC_INFO("wait_for_completion_timeout() start.\n");
	retry = 1;
	do {
		tmo = wait_for_completion_timeout(&(pdev->comp),
					msecs_to_jiffies(YUVC_CONV_TIMEOUT));
		if (tmo)
			break;
		retry--;
	} while (retry);
	YUVC_INFO("wait_for_completion_timeout() end.\n");
	if (!retry) {
		/* timeout! */
		yuvc_cancel_sub(pdev);
		YUVC_ERR("yuvc convert timeout\n");
		ierr = -EINVAL;
		goto FINISH;
	}

	if (pdev->convert_status) {
		YUVC_ERR("fail to yuvc convert\n");
		ierr = -EINVAL;
	}

#ifdef YUVC_USE_GDMAC
	/* stop dma */
	yuvc_dma_stop(pdev->dmac_type);
#endif

FINISH:
	pdev->yuvc_usecount--;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	YUVC_TEST("runtime_put call\n");
	pm_runtime_put_sync(&(pdev->pdev->dev));
#else
	if (!pdev->yuvc_usecount)
		yuvc_runtime_suspend_sub(pdev);
#endif
	YUVC_TEST("usecount:%d\n", pdev->yuvc_usecount);

	YUVC_TEST("free mutex_run\n");
	mutex_unlock(&(pdev->mutex_run));

	if (yuvc_free_address(pdev, prm, conv_adr) != YUVC_OK) {
		YUVC_ERR("yuvc_free_address() failed\n");
		ierr = -EFAULT;
	}

	DUMP_YUVC_DEV(pdev);		/* for TEST */
	YUVC_FUNC_END("ret(%d)\n", ierr);
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
long yuvc_cancel_sub(struct yuvc_dev *pdev)
{
	__u32	regs;

	YUVC_FUNC_START("\n");

	if (pdev == NULL) {
		YUVC_ERR("invalid parameters pdev(%p)\n", pdev);
		return YUVC_NG;
	}

	pdev->yuvc_usecount++;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	YUVC_TEST("runtime_get call\n");
	pm_runtime_get_sync(&(pdev->pdev->dev));
#else
	if (pdev->yuvc_usecount == 1)
		yuvc_runtime_resume_sub(pdev);
#endif
	YUVC_TEST("usecount:%d\n", pdev->yuvc_usecount);

	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");
	spin_lock(&(pdev->lock_dev));
	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");

	/* check running status */
	if (pdev->b_run != YUVC_STAT_IDLE) {
		DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
		spin_lock(&(pdev->lock_reg));
		DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
#ifdef YUVC_USE_GDMAC
		if (pdev->dmac_status)
			yuvc_dma_stop(pdev->dmac_type);
#endif
		/* do abort */
		pdev->b_run = YUVC_STAT_ABORT;
		YUVC_INFO("force abort\n");
		YUVC_WRITE(pdev, RESET, YUVC_RESET_ON);
		/* wait for idle state */
		do {
			/* delay */
			YUVC_READ(pdev, INT, regs);
			YUVC_INFO("read status[%08x]\n", regs);
		} while (regs & YUVC_INT_ABORT_G00);
		YUVC_INFO("yuvc status become to abort\n");
		spin_unlock(&(pdev->lock_reg));
		DUMP_SPINLOCK(&(pdev->lock_reg), "reg");
		complete(&(pdev->comp));
	}

	spin_unlock(&(pdev->lock_dev));
	DUMP_SPINLOCK(&(pdev->lock_dev), "dev");

	pdev->yuvc_usecount--;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	YUVC_TEST("runtime_put call\n");
	pm_runtime_put_sync(&(pdev->pdev->dev));
#else
	if (!pdev->yuvc_usecount)
		yuvc_runtime_suspend_sub(pdev);
#endif
	YUVC_TEST("usecount:%d\n", pdev->yuvc_usecount);

	DUMP_YUVC_DEV(pdev);		/* for TEST */
	YUVC_FUNC_END("OK\n");

	return YUVC_OK;
}
