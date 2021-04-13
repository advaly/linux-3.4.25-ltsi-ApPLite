/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/gdmac_filter.c
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
#include <linux/slab.h>

#include <linux/applite/irecog/filter_param.h>

#include "filter_public.h"
#include "gdmac_filter.h"
#include "sl_filter.h"
#include "filter_define.h"
#include "gdmac_instructions.h"
#include "gdmac_port_def.h"

#include "drv_cache.h"

#define print_err(fmt, ...) \
  pr_err(fmt, ##__VA_ARGS__)

#define FPARAM_UINT_SIZE 64

static UINT filter_get_program_size(struct filter_dev *dev)
{
	UINT trans_num;
	UINT last_trans_offset;
	UINT last_trans_size;
	UINT prog_size;

	UINT *transbase;

	if (!dev->filter_base_virt) {
		return 0;
	}

	transbase = (UINT *)dev->filter_base_virt;

	trans_num = transbase[0];

	last_trans_offset = transbase[(trans_num - 1) * 3 + 1 + 0];
	last_trans_size = transbase[(trans_num - 1) * 3 + 1 + 1];
	prog_size = last_trans_offset + last_trans_size * FPARAM_UINT_SIZE;

	return prog_size;
}

static void filter_cache_flush_fparam(struct filter_dev *dev)
{
	UINT prog_size = filter_get_program_size(dev);

	drv_cache_flush(dev->filter_base_phys, prog_size);
}

static inline void add_instruction(gdmac_inst *inst, REG_32 reg_val,
				   unsigned long dst_adr)
{
	gdmac_write_register(inst, dst_adr, reg_val);
}

static void filter_init_kick(struct filter_dev *dev, REG_32 reg_val)
{
	add_instruction(dev->inst, reg_val,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_INITSTART_OFFS));
}

static void filter_init_cmd(struct filter_dev *dev)
{

#if 0
	/* reset */
	add_instruction(dev->inst, 0x1,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_RST_OFFS));
	gdmac_dummy_read(dev->inst,
			 (unsigned long)dev->reg_base +
			 FILTER_OFFSET(IRECOG_rfilter_RST_OFFS), 200);

	/* halt */
	add_instruction(dev->inst, 0x0,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	gdmac_dummy_read(dev->inst,
			 (unsigned long)dev->reg_base +
			 FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS), 200);

	/* writeable */
	add_instruction(dev->inst, 0x1,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	gdmac_dummy_read(dev->inst,
			 (unsigned long)dev->reg_base +
			 FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS), 200);
#endif
}

void filter_clear_int(struct filter_dev *dev)
{
	add_instruction(dev->inst, FILTER_CLEAR_BITS,
			(unsigned int)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_INTCLR_OFFS));
}

static void filter_write_register_number_info(struct filter_dev *dev,
					      FILTER_DESCRIPT *descript)
{
	add_instruction(dev->inst, descript->info.inittrnum,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_INITTRNUM_OFFS));
	add_instruction(dev->inst, descript->info.imgfrmchnum,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_IMGFRMCHNUM_OFFS));
	add_instruction(dev->inst, descript->info.prmtrnum,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_PRMTRNUM_OFFS));
}

static void filter_write_register_image_size(struct filter_dev *dev,
					     FILTER_DESCRIPT *descript)
{
	UINT i;

	for (i = 0; i < FILTER_HW_IMG_SIZE; i++) {
		if (i % 2) {
			/* img size */
			add_instruction(dev->inst,
					((UINT *)&descript->image_set)[i],
					(unsigned long)dev->reg_base +
					FILTER_OFFSET
					(IRECOG_rfilter_OIMG0INITADDR_OFFS) +
					i * 4);
		} else {
			if (((UINT *)&descript->image_set)[i + 1]) {
				/* img addr */
				add_instruction(dev->inst,
						((UINT *)
						 &descript->image_set)[i],
						(unsigned long)dev->reg_base +
						FILTER_OFFSET
						(IRECOG_rfilter_OIMG0INITADDR_OFFS)
						+ i * 4);
			}
		}
	}
}

static void filter_write_register_init_param(struct filter_dev *dev,
					     FILTER_DESCRIPT *descript)
{
	UINT i;

	for (i = 0; i < FILTER_HW_INIT_SIZE; i++) {
		if (i % 2) {
			/* init param size */
			add_instruction(dev->inst,
					((UINT *)&descript->init_param)[i],
					(unsigned long)dev->reg_base +
					FILTER_OFFSET
					(IRECOG_rfilter_DINITIADDR0_OFFS) +
					i * 4);
		} else {
			/* init param address */
			if (((UINT *)&descript->init_param)[i + 1]) {
				add_instruction(dev->inst,
						((UINT *)
						 &descript->init_param)[i],
						(unsigned long)dev->reg_base +
						FILTER_OFFSET
						(IRECOG_rfilter_DINITIADDR0_OFFS)
						+ i * 4);
			}
		}
	}
}

/**
 * filter_driver
 */
/**
 * @brief Filter Module Initialization
 * @retval Success : Main Bus Address , Fail: NULL
 */
SSHORT *dd_gdmac_FILTER_get_HIF_address(struct filter_dev *dev,
					SINT sequence_id,
				      /**< Filter Sequence Id */
					UINT HIF_address)
{
/**< HIF Address */
	SSHORT *hif_address;
	UINT *transbase;
	UINT trans_num;
	UINT hif_size;
	UINT address;
	UINT index;
	UINT i;
	UINT filter_base_addr;
	UINT *filter_param;
	SSHORT *retval = NULL;

	/* Filter Parameter Table Base Address */
	filter_base_addr = (UINT)(unsigned long)dev->param_base;	/* dd_get_filter_base_address(); */
	filter_param = (UINT *)filter_base_addr;

	/* Check Sequence Id */
	if ((sequence_id < 0) ||
	    (filter_param[FILTER_SEQUENCE_NUM] <= (UINT)sequence_id)) {
		print_err("Invalid sequence id %d\n", sequence_id);
		return retval;
	}

	/* Get Index of The Sequence Transaction Info Base */
	index = (UINT)(sequence_id + FILTER_SEQUENCE_OFFSET);

#ifdef ENABLE_QEMU_FPARAM
	transbase = (UINT *)(filter_param[index] + filter_base_addr);
#else
	/* for speyside board */
	dev->filter_base_phys = filter_param[index];
	dev->filter_base_virt = phys_to_virt(filter_param[index]);

	transbase = (UINT *)dev->filter_base_virt;
#endif

	if (transbase[FILTER_TRANS_NUM] > FILTER_TRNUM_MAX) {
		print_err("Invalid Transaction Number %d\n",
			  transbase[FILTER_TRANS_NUM]);
		return retval;
	}

	/* Set Trunsaction Number */
	trans_num = transbase[FILTER_TRANS_NUM];
	for (i = 0; i < trans_num; i++) {
		/* Set Uncache Address */
#ifdef ENABLE_QEMU_FPARAM
		hif_address
		    =
		    (SSHORT *)(transbase[(i * 3) + FILTER_PARAM_OFFSET_ADDR] +
			       filter_base_addr);
#else
		/* for speyside board */
		hif_address
		    =
		    (SSHORT *)(transbase[(i * 3) + FILTER_PARAM_OFFSET_ADDR] +
			       (UINT)dev->filter_base_virt);
#endif
		/* In SHORT Word Size */
		hif_size = (transbase[(i * 3) + FILTER_PARAM_SIZE] * 64) / 2;
		address = transbase[(i * 3) + FILTER_PARAM_HIF_ADDR];

		/* Check If The Data is In Current Region */
		if ((address <= HIF_address)
		    && ((address + hif_size) > HIF_address)) {
			retval = hif_address + (HIF_address - address);
			break;
		}
	}

	return retval;
}

static SINT dd_filter_start(struct filter_dev *dev,
			    FILTER_DESCRIPT *descript, UINT mode,
			    UINT sequence_id)
{
	FILTER_DESCRIPT *pqueue;
	UINT *plqueue;
	UINT param_id;

	filter_init_cmd(dev);
	filter_clear_int(dev);

	/* Write Register DATA */
	pqueue = descript;
	plqueue = (UINT *)pqueue;

	/* Mask mode & sequence id */
	plqueue[0] &= FILTER_INITTRNUM_MASK;

	/* Copy Number Info */
	filter_write_register_number_info(dev, pqueue);

	/* Copy Image Size */
	filter_write_register_image_size(dev, pqueue);

	/* Set Int Mask, Currently No Parameter Trans. */
	add_instruction(dev->inst, FILTER_INTMASK_SEQ_FRAME,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_INTMASK_OFFS));

	/* Kick Filter */
	/* Override IOC data */
#ifdef ENABLE_QEMU_FPARAM
	gdmac_write_register_halfword(dev->inst,
				      FILTER_FW_IMAGE + ((unsigned long)
							 &pqueue->ioc_addr
							 [FILTER_HIFIOC_IHWID_OFFSET]
							 - (unsigned long)
							 dev->param_base),
				      (SSHORT)pqueue->ihwid);
	gdmac_write_register_halfword(dev->inst,
				      FILTER_FW_IMAGE + ((unsigned long)
							 &pqueue->ioc_addr
							 [FILTER_HIFIOC_IHWIDBL_OFFSET]
							 - (unsigned long)
							 dev->param_base),
				      (SSHORT)pqueue->ihwidbl);
	gdmac_write_register_halfword(dev->inst,
				      FILTER_FW_IMAGE + ((unsigned long)
							 &pqueue->ioc_addr
							 [FILTER_HIFIOC_IVWID_OFFSET]
							 - (unsigned long)
							 dev->param_base),
				      (SSHORT)pqueue->ivwid);
	gdmac_write_register_halfword(dev->inst,
				      FILTER_FW_IMAGE + ((unsigned long)
							 &pqueue->ioc_addr
							 [FILTER_HIFIOC_IVWIDBL_OFFSET]
							 - (unsigned long)
							 dev->param_base),
				      (SSHORT)pqueue->ivwidbl);
	gdmac_write_register_halfword(dev->inst,
				      FILTER_FW_IMAGE + ((unsigned long)
							 &pqueue->ioc_addr
							 [FILTER_HIFIOC_HEND_OFFSET]
							 - (unsigned long)
							 dev->param_base),
				      pqueue->hend);
	gdmac_write_register_halfword(dev->inst,
				      FILTER_FW_IMAGE + ((unsigned long)
							 &pqueue->ioc_addr
							 [FILTER_HIFIOC_VEND_OFFSET]
							 - (unsigned long)
							 dev->param_base),
				      pqueue->vend);
#else
	gdmac_write_register_halfword(dev->inst,
				      virt_to_phys(&pqueue->ioc_addr
						   [FILTER_HIFIOC_IHWID_OFFSET]),
				      (SSHORT)pqueue->ihwid);
	gdmac_write_register_halfword(dev->inst,
				      virt_to_phys(&pqueue->ioc_addr
						   [FILTER_HIFIOC_IHWIDBL_OFFSET]),
				      (SSHORT)pqueue->ihwidbl);
	gdmac_write_register_halfword(dev->inst,
				      virt_to_phys(&pqueue->ioc_addr
						   [FILTER_HIFIOC_IVWID_OFFSET]),
				      (SSHORT)pqueue->ivwid);
	gdmac_write_register_halfword(dev->inst,
				      virt_to_phys(&pqueue->ioc_addr
						   [FILTER_HIFIOC_IVWIDBL_OFFSET]),
				      (SSHORT)pqueue->ivwidbl);
	gdmac_write_register_halfword(dev->inst,
				      virt_to_phys(&pqueue->ioc_addr
						   [FILTER_HIFIOC_HEND_OFFSET]),
				      pqueue->hend);
	gdmac_write_register_halfword(dev->inst,
				      virt_to_phys(&pqueue->ioc_addr
						   [FILTER_HIFIOC_VEND_OFFSET]),
				      pqueue->vend);
#endif

	/* Copy Init Param */
	filter_write_register_init_param(dev, descript);

	/* Overwrite HIF Paramter If Needed */
	for (param_id = 0; param_id < pqueue->hif_param_num; param_id++) {

#ifdef ENABLE_QEMU_FPARAM
		gdmac_write_register_halfword(dev->inst,
					      FILTER_FW_IMAGE + ((unsigned long)
								 pqueue->
								 hif_param
								 [param_id].
								 addr -
								 (unsigned long)
								 dev->
								 param_base),
					      pqueue->hif_param[param_id].data);
#else
		gdmac_write_register_halfword(dev->inst,
					      virt_to_phys(pqueue->hif_param
							   [param_id].addr),
					      pqueue->hif_param[param_id].data);
#endif
	}

	/* Kick Init Param Trans */
	filter_init_kick(dev, 0x1);

	/* wait */
	dma330_dmawfp(dev->inst, GDMAC_SINGLE, GDMAC_CVIA_PORT);
	filter_clear_int(dev);
	dma330_dmaflushp(dev->inst, GDMAC_CVIA_PORT);

	/* Start Image Processing */
	add_instruction(dev->inst, 1,
			(unsigned long)dev->reg_base +
			FILTER_OFFSET(IRECOG_rfilter_IMGSTART_OFFS));

	/* cache flush */
	filter_cache_flush_fparam(dev);

	return 0;
}

SINT dd_gdmac_FILTER_send_request(struct filter_dev *dev,
				  FILTER_DESCRIPT *descript)
{
	UINT mode;
	UINT sequence_id;

	mode = descript->info.mode;
	sequence_id = descript->info.sequence_id;

	return dd_filter_start(dev, descript, mode, sequence_id);
}
