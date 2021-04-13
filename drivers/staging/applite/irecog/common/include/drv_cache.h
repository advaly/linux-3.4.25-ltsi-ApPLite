/*
 * linux/drivers/staging/applite/irecog/common/include/drv_cache.h
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
#ifndef _DRV_CACHE_H_
#define _DRV_CACHE_H_

#include <linux/dma-mapping.h>
#include <asm/cacheflush.h>
#include <linux/io.h>
#include <linux/smp.h>
#include <linux/applite/irecog/drv_cache_ctrl_defs.h>

/**************************************************/
/*
 * @brief drv_cache_flush
 *
 * @param adr_phys
 * @param size
 *
 * @note
 *  kmalloced memory only
 *
 */
/**************************************************/
static inline void drv_cache_flush(unsigned long adr_phys, unsigned long size)
{
	dmac_flush_range(phys_to_virt(adr_phys), phys_to_virt(adr_phys + size));
	outer_flush_range(adr_phys, adr_phys + size);
}

/**************************************************/
/*
 * @brief drv_cache_invalidate
 *
 * @param adr_phys
 * @param size
 *
 * @note
 *  kmalloced memory only
 *
 */
/**************************************************/
static inline void drv_cache_invalidate(unsigned long adr_phys,
					unsigned long size)
{
	dmac_unmap_area(phys_to_virt(adr_phys), size, DMA_FROM_DEVICE);
	outer_inv_range(adr_phys, adr_phys + size);
}

static inline void _flush_cache_all(void)
{
	flush_cache_all();
}

/**************************************************/
/*
 * @brief drv_cache_flush_all
 *
 * @note
 *  kmalloced memory only
 *
 */
/**************************************************/
static inline void drv_cache_flush_all(void)
{
#if defined(CONFIG_SMP)
	on_each_cpu((smp_call_func_t) _flush_cache_all, NULL, 1);
#else
	flush_cache_all();
#endif
	outer_flush_all();
}

#endif /* _DRV_CACHE_H_ */
