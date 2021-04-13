/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/filter_util_gdmac.c
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
#include <linux/cdev.h>
#include <linux/io.h>

#include "filter_util_gdmac.h"
#include "filter_public.h"
#include "filter_descript.h"
#include "filter_parameter_gdmac.h"
#include "filter_define.h"
#include "filter_status.h"
/*#include "dbg_print.h" */
#define print_err(fmt, ...) \
  pr_err(fmt, ##__VA_ARGS__)

/* #define BASE_SDK_VER_EARLIER_THAN_4_0_0 */

/**
 * <pre>
 *
 * @brief Set Filter Request to Filter HW Register Descriptor
 *
 * @retval
 *
 * </pre>
 */
SINT dd_gdmac_FILTER_config_param(struct filter_dev *dev,
				  FILTER_DESCRIPT *descript,
				  FILTER_PARAMETER *parameter)
{
	UINT *transbase;
	UINT trans_num;
	SSHORT *hif_value;
	SSHORT org_width;
	SSHORT max_width;
	SSHORT min_width;
	SINT width;
	SINT iwidth;
	UINT factor;
	SSHORT hbgn;
	SSHORT hend;
	SSHORT vbgn;
	SSHORT vend;
	SINT vratio;
	UINT itrans;
	UINT index;
	SINT ich;
	UINT filter_base_vaddr, filter_base_paddr;
	UINT *filter_param;
	UINT trans_addr;

	/* Set Filter Parameter Set Base Address */
	filter_base_vaddr = (UINT)(unsigned long)dev->param_base;	/* dd_get_filter_base_address(); */
	filter_base_paddr = FILTER_FW_IMAGE;	/* dd_get_filter_base_paddress(); */
	filter_param = (UINT *)filter_base_vaddr;

	/* Check Sequence Id */
	if (filter_param[FILTER_SEQUENCE_NUM] <= parameter->sequence_id) {
		print_err("Invalid sequence id %d\n", parameter->sequence_id);
		return FILTER_ERROR;
	}

	/* progID */
	descript->info.sequence_id = parameter->sequence_id;
	descript->info.mode = FILTER_INIT;

	/* Get Index of The Sequence Transaction Info Base */
	index = parameter->sequence_id + FILTER_SEQUENCE_OFFSET;

	/* Check If The Requested Sequence is Exist */
	if ((filter_param[index] + filter_base_vaddr) == 0x0UL) {
		print_err("Request Sequence Not Exist id %d\n",
			  parameter->sequence_id);
		return FILTER_ERROR;
	}
#ifdef ENABLE_QEMU_FPARAM
	transbase = (UINT *)(filter_param[index] + filter_base_vaddr);
#else
	/* for speyside board */
	dev->filter_base_phys = filter_param[index];
	dev->filter_base_virt = phys_to_virt(filter_param[index]);

	transbase = (UINT *)dev->filter_base_virt;
#endif

	if (transbase[FILTER_TRANS_NUM] > FILTER_TRNUM_MAX) {
		print_err("Invalid Transaction Number %d\n",
			  transbase[FILTER_TRANS_NUM]);
		return FILTER_ERROR;
	}

	/* Set Trunsaction Number */
	trans_num = transbase[FILTER_TRANS_NUM];
	descript->info.inittrnum = (USHORT)trans_num;

	/* Input/Output Channel Number */
	if ((parameter->in_channel_num > FILTER_MAX_IN_CHANNEL)
	    || (parameter->in_channel_num == 0)
	    || (parameter->out_channel_num > FILTER_MAX_OUT_CHANNEL)) {
		print_err("Invalid channel number Error in %d out %d\n",
			  parameter->in_channel_num,
			  parameter->out_channel_num);
		return FILTER_ERROR;
	}
	/* Request Frame Number */
	if (parameter->frame_num > (SINT) FILTER_MAX_FRAME) {
		print_err("Invalid frame num %d\n", parameter->frame_num);
		return FILTER_ERROR;
	}

	/* Set In/Out ch & Frame num */
	descript->info.imgfrmchnum
	    = ((UINT)parameter->in_channel_num << FILTER_IMGFRM_IN_BIT)
	    | ((UINT)parameter->out_channel_num << FILTER_IMGFRM_OUT_BIT)
	    | ((UINT)parameter->frame_num << FILTER_IMGFRM_FRAME_BIT);

	/* Filter Driver Won't Support Parameter Transaction, So far. Do Nothing */
	descript->info.prmtrnum = 0;

	/* Set Transfer Infomation */
	for (itrans = 0; itrans < trans_num; itrans++) {
		/* Top Address of Parameter Info. @main mem */
		index = (itrans * 3) + FILTER_PARAM_OFFSET_ADDR;

#ifdef ENABLE_QEMU_FPARAM
#if 1				/* Vis2, qemu-speyside-1.0.0 */
		trans_addr = transbase[index] + filter_base_vaddr;
#else
		/* previous qemu-speyside-1.0.0 */
		trans_addr = transbase[index] + (UINT)transbase;
#endif
		descript->init_param[itrans * 2] =
		    transbase[index] + filter_base_paddr;

#else
		/* for speyside board */
		trans_addr = transbase[index] + (UINT)transbase;
		descript->init_param[itrans * 2] =
		    transbase[index] + dev->filter_base_phys;
#endif
		/* Transaction Size(In Unit of 64Byte) */
		descript->init_param[(itrans * 2) + 1]
		    = transbase[(itrans * 3) + FILTER_PARAM_SIZE] << 16;

		/* HIF Address */
		descript->init_param[(itrans * 2) + 1] |=
		    (transbase[(itrans * 3) + FILTER_PARAM_HIF_ADDR] >> 5);

		/* Only For Different Size */
		hif_value = (SSHORT *)trans_addr;

#if 0				/* previous qemu-speyside-1.0.0 */
		if (transbase[(itrans * 3) + FILTER_PARAM_HIF_ADDR] !=
		    FILTER_IMEM_HIF_ADDR) {
			/* plus Program Addr Offset */
			descript->init_param[itrans * 2] +=
			    (UINT)transbase - filter_base_vaddr;
		}
#endif
		/* Do HIF == IOC */
		if (transbase[(itrans * 3) + FILTER_PARAM_HIF_ADDR] !=
		    FILTER_IOC_HIF_ADDR) {
			continue;
		}

		/* Address of HIF IOC Register */
		descript->ioc_addr = (SSHORT *)hif_value;

		/* Only When Overwrite the width is in 2*SIMD */
		org_width = hif_value[FILTER_HIFIOC_IHWID_OFFSET];
		max_width =
		    (SSHORT)((USHORT)(org_width + ((2 * FILTER_SIMD_NUM) - 1))
			     & ~((2 * ((USHORT)FILTER_SIMD_NUM)) - 1));
		min_width = (SSHORT)(max_width - (2 * FILTER_SIMD_NUM));
		if ((parameter->width > max_width)
		    || (parameter->width <= min_width)) {
			print_err
			    ("Error frame width=%d, max width =%d, minimum width=%d\n",
			     parameter->width, max_width, min_width);

			return FILTER_ERROR;
		}

		/* IHWID */
		descript->ihwid = parameter->width;

		/* IHWIDBL */
		if ((parameter->width % (2 * FILTER_SIMD_NUM)) == 0) {
			descript->ihwidbl
			    =
			    (USHORT)((parameter->width /
				      (2 * FILTER_SIMD_NUM)) * (2 *
								FILTER_SIMD_NUM));
		} else {
			descript->ihwidbl
			    =
			    (USHORT)(((parameter->width /
				       (2 * FILTER_SIMD_NUM)) * (2 *
								 FILTER_SIMD_NUM))
				     + (2 * FILTER_SIMD_NUM));
		}
		hbgn = hif_value[FILTER_HIFIOC_HBGN_OFFSET];
		descript->hbgn = hbgn;
#ifdef BASE_SDK_VER_EARLIER_THAN_4_0_0
		hend = (SSHORT)((parameter->width - 1) - hbgn);
#else /* SDK 4.0.0 */
		hend = (SSHORT)(parameter->width - 1);
#endif
		if (hend <= hbgn) {
			print_err
			    ("Filter Config Error.. hend (%d) > hbgn(%d)\n",
			     hend, hbgn);
			return FILTER_ERROR;
		}

		/* HEND */
		descript->hend = hend;

		/* IVWID */
		descript->ivwid = parameter->height;
		vbgn = hif_value[FILTER_HIFIOC_VBGN_OFFSET];
		descript->vbgn = vbgn;

		/* IVWIDBL */
		descript->ivwidbl = parameter->height;
		vend = (SSHORT)((parameter->height - 1) - vbgn);

		if (vend <= vbgn) {
			print_err
			    ("Filter Config Error.. vend (%d) > vbgn(%d)\n",
			     vend, vbgn);
			return FILTER_ERROR;
		}

		descript->vend = vend;

	/**
	 * @note Overwrite Output Height = 1/2
	 * @caution All Scaling Factors Must Be The Same
	 */
		vratio =
		    parameter->out_channel_info[0].
		    ratio >> FILTER_RATIO_BIT_HEIGHT;

		/* 1/2 */
		if (vratio == 1) {
			descript->info.mode = FILTER_INIT_VSCALE;
		}
	}

	/* Input Channel */
	for (ich = 0; ich < parameter->in_channel_num; ich++) {

		/* Base Address of The Frame Memory */
		if (((UINT)parameter->in_channel_info[ich].addr & 0xf) != 0) {
			print_err("Invalid input frame addr %dth %x\n", ich,
				  (UINT)parameter->in_channel_info[ich].addr);
			return FILTER_ERROR;
		}

		descript->image_set[(ich * 2) + 1].initaddr
		    = (UINT)parameter->in_channel_info[ich].addr;

		/* Bit Accuracy */
		switch (parameter->in_channel_info[ich].bit_accuracy) {
		case FILTER_BITACC_S8:
		case FILTER_BITACC_U8:
		case FILTER_BITACC_S16:
			break;
		default:
			print_err("Invalid bit accuracy %dth in ch %x\n", ich,
				  parameter->in_channel_info[ich].bit_accuracy);
			return FILTER_ERROR;
		}

		/* Transform Scaling Factor */
		switch (parameter->in_channel_info[ich].ratio) {
		case FILTER_RATIO_1_4HV:
		case FILTER_RATIO_1_2HV:
		case FILTER_RATIO_1_2H:
		case FILTER_RATIO_1_2V:
		case FILTER_RATIO_1HV:
		case FILTER_RATIO_2HV:
		case FILTER_RATIO_2H:
		case FILTER_RATIO_2V:
			break;
		default:
			print_err("Invalid ratio %dth in ch %x\n", ich,
				  parameter->in_channel_info[ich].ratio);
			return FILTER_ERROR;
		}

		/* Check Alignment (width + lineoffset) must be 16bytes align */
		factor =
		    (UINT)(parameter->in_channel_info[ich].ratio >>
			   FILTER_RATIO_BIT_WIDTH) & 0x03;
		iwidth = (SINT) (descript->ihwid << (3 - factor)) >> 1;
		width =
		    iwidth + (SINT) parameter->in_channel_info[ich].line_offset;
		width +=
		    (SINT) (((UINT)parameter->in_channel_info[ich].
			     bit_accuracy >> 1) & 0x01UL)
		    * iwidth;

		if ((((UINT)width & 0xf) != 0)
		    || (parameter->in_channel_info[ich].line_offset >
			FILTER_MAX_LINEOFFSET)) {
			print_err("Invalid line_offset %dth in ch %x\n", ich,
				  parameter->in_channel_info[ich].line_offset);
			return FILTER_ERROR;
		}
		descript->image_set[(ich * 2) + 1].ratiooffset
		    = (((UINT)parameter->in_channel_info[ich].bit_accuracy)
		       | ((UINT)parameter->in_channel_info[ich].
			  ratio)) << FILTER_IMG_RATIO_BIT;

		/* Line offset */
		descript->image_set[(ich * 2) + 1].ratiooffset
		    |= parameter->in_channel_info[ich].line_offset;

	}

	/* Output Channel */
	for (ich = 0; ich < parameter->out_channel_num; ich++) {
		/* Base Address of The Frame Memory */
		if (((UINT)parameter->out_channel_info[ich].addr & 0xf) != 0) {
			print_err("Invalid output frame addr %dth %x\n", ich,
				  (UINT)parameter->out_channel_info[ich].addr);
			return FILTER_ERROR;
		}

		descript->image_set[ich * 2].initaddr
		    = (UINT)parameter->out_channel_info[ich].addr;

		/* Bit Accuracy */
		switch (parameter->out_channel_info[ich].bit_accuracy) {
		case FILTER_BITACC_S8:
		case FILTER_BITACC_U8:
		case FILTER_BITACC_S16:
			break;
		default:
			print_err("Invalid bit accuracy %dth out ch %x\n", ich,
				  parameter->out_channel_info[ich].
				  bit_accuracy);
			return FILTER_ERROR;
		}

		/* Transform Scaling Factor */
		switch (parameter->out_channel_info[ich].ratio) {
		case FILTER_RATIO_1_2HV:
		case FILTER_RATIO_1_2H:
		case FILTER_RATIO_1_2V:
		case FILTER_RATIO_1HV:
			break;
		default:
			print_err("Invalid ratio %dth out ch %x\n", ich,
				  parameter->out_channel_info[ich].ratio);
			return FILTER_ERROR;
		}

		/* Check Alignment (width + lineoffset) must be 16bytes align */
		factor =
		    ((UINT)parameter->out_channel_info[ich].
		     ratio >> FILTER_RATIO_BIT_WIDTH) & 0x03;
		iwidth = (descript->ihwid << 1) >> (3 - factor);
		width =
		    iwidth +
		    (SINT) parameter->out_channel_info[ich].line_offset;
		width +=
		    (SINT) (((UINT)parameter->out_channel_info[ich].
			     bit_accuracy >> 1) & 0x01UL)
		    * iwidth;

		if ((((UINT)width & 0x0f) != 0)
		    || (parameter->out_channel_info[ich].line_offset >
			FILTER_MAX_LINEOFFSET)) {
			print_err("Invalid line_offset %dth out ch %x\n", ich,
				  parameter->out_channel_info[ich].line_offset);
			return FILTER_ERROR;
		}
		descript->image_set[ich * 2].ratiooffset
		    = (((UINT)parameter->out_channel_info[ich].bit_accuracy)
		       | ((UINT)parameter->out_channel_info[ich].
			  ratio)) << FILTER_IMG_RATIO_BIT;

		/* Line offset */
		descript->image_set[ich * 2].ratiooffset
		    |= parameter->out_channel_info[ich].line_offset;
	}

	/* Filter Parameters on HIF */
	if ((parameter->hif_param_num != 0) && (parameter->hif_param == NULL)) {
		print_err
		    ("Invalid Overwrite Filter Parameter Address is NULL\n");
		return FILTER_ERROR;
	}
	descript->hif_param_num = parameter->hif_param_num;
	descript->hif_param = parameter->hif_param;

	return FILTER_SUCCESS;
}
