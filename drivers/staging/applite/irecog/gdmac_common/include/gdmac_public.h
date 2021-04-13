/*
 * linux/drivers/staging/applite/irecog/gdmac_common/include/gdmac_public.h
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
#ifndef __GDMAC_PUBLIC_H_
#define __GDMAC_PUBLIC_H_

#include <mach/regs/gdmac_offs_def.h>
#include <mach/regs/gdmac_reg_def.h>

/* dma330 registers */
#define DMA330_DSR           0x000
#define DMA330_DPC           0x004
#define DMA330_INTEN         0x020
#define DMA330_INT_EVENT_RIS 0x024
#define DMA330_INTMIS        0x028
#define DMA330_INTCLR        0x02C
#define DMA330_FSRD          0x030
#define DMA330_FSRC          0x034
#define DMA330_FTRD          0x038

#define DMA330_FTR_NUM       7
#define DMA330_FTR_BASE      0x040
#define DMA330_FTR_INTERVAL  0x4

#define DMA330_CSR_NUM       7
#define DMA330_CSR_BASE      0x100
#define DMA330_CSR_INTERVAL  0x8

#define DMA330_CPC_NUM       7
#define DMA330_CPC_BASE      0x104
#define DMA330_CPC_INTERVAL  0x8

#define DMA330_SAR_NUM       7
#define DMA330_SAR_BASE      0x400
#define DMA330_SAR_INTERVAL  0x20

#define DMA330_DAR_NUM       7
#define DMA330_DAR_BASE      0x404
#define DMA330_DAR_INTERVAL  0x20

#define DMA330_CCR_NUM       7
#define DMA330_CCR_BASE      0x408
#define DMA330_CCR_INTERVAL  0x20

#define DMA330_LC0_NUM       7
#define DMA330_LC0_BASE      0x40C
#define DMA330_LC0_INTERVAL  0x20

#define DMA330_LC1_NUM       7
#define DMA330_LC1_BASE      0x410
#define DMA330_LC1_INTERVAL  0x20

#define DMA330_DBGSTATUS     0xD00
#define DMA330_DBGCMD        0xD04
#define DMA330_DBGINST0      0xD08
#define DMA330_DBGINST1      0xD0C

#define DMA330_CR0           0xE00
#define DMA330_CR1           0xE04
#define DMA330_CR2           0xE08
#define DMA330_CR3           0xE0C
#define DMA330_CR4           0xE10
#define DMA330_CRD           0xE14

#define DMA330_PERIPH_ID_NUM      4
#define DMA330_PERIPH_ID_BASE     0xFE0
#define DMA330_PERIPH_ID_INTERVAL 0x4

#define DMA330_PCELL_ID_NUM      4
#define DMA330_PCELL_ID_BASE     0xFF0
#define DMA330_PCELL_ID_INTERVAL 0x4

#endif /* __GDMAC_PUBLIC_H_ */
