/*
 * linux/drivers/staging/applite/irecog/filter/filter_public.h
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
#ifndef __FILTER_PUBLIC_H__
#define __FILTER_PUBLIC_H__

#include <linux/applite/irecog/basic_type.h>
#include <linux/applite/irecog/drv_cmn.h>

#include <mach/regs/irecog_offs_def.h>
#include <mach/regs/irecog_reg_def.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/pmu_reg_def.h>

#define FILTER_OFFSET(x) ((x) - IRECOG_rfilter_RST_OFFS)

#define FILTER_HW_NUM_SIZE                       (3)
#define FILTER_HW_INIT_SIZE                      (16)
#define FILTER_HW_IMG_SIZE                       (16)
#define FILTER_HW_PARAM_SIZE                     (16)

/* Bit Offset of Filter Register */
#define FILTER_IMGFRM_IN_BIT                  (IRECOG_RFILTER_IMGFRMCHNUM_ICHNUM_SHIFT)
#define FILTER_IMGFRM_OUT_BIT                 (IRECOG_RFILTER_IMGFRMCHNUM_OCHNUM_SHIFT)
#define FILTER_IMGFRM_FRAME_BIT               (IRECOG_RFILTER_IMGFRMCHNUM_FNUM_SHIFT)
#define FILTER_IMG_RATIO_BIT                  (16)
#define FILTER_INITTRNUM_MASK                 (0xFF)

/* HIF Address Offset */
#define FILTER_HIFIOC_IHWID_OFFSET            (0x11)
#define FILTER_HIFIOC_IVWID_OFFSET            (0x12)
#define FILTER_HIFIOC_IHWIDBL_OFFSET          (0x13)
#define FILTER_HIFIOC_IVWIDBL_OFFSET          (0x14)
#define FILTER_HIFIOC_HBGN_OFFSET             (0x15)
#define FILTER_HIFIOC_HEND_OFFSET             (0x16)
#define FILTER_HIFIOC_VBGN_OFFSET             (0x17)
#define FILTER_HIFIOC_VEND_OFFSET             (0x18)

/* C-ViA Host I/F Local Address */
#define FILTER_IMEM_HIF_ADDR                   (0x0000UL)
#define FILTER_IOC_HIF_ADDR                    (0x8200UL)
#define FILTER_LMC_HIF_ADDR                    (0x8300UL)
#define FILTER_SRF_HIF_ADDR                    (0x8600UL)
#define FILTER_SSR_HIF_ADDR                    (0x8800UL)

/* Filter Int Clear Bits */
#define FILTER_CLEAR_BITS                      (0x1FFF)

/*----------------------------------------------------------------*/
/*                      struct/enum Definition                    */
/*----------------------------------------------------------------*/

/*--------------------- enum --------------------------*/
enum filter_kick_mode_e {
	FILTER_ADDR_UPDATE = 0x01,
	FILTER_LUT_UPDATE = 0x02,
	FILTER_INIT = 0x10,
	FILTER_INIT_VSCALE = 0x11
};
typedef enum filter_kick_mode_e FILTER_MODE;

#endif /* __FILTER_PUBLIC_H__ */
