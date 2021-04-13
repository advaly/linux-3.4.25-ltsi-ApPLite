/*
 * linux/drivers/staging/applite/irecog/hog/hog_register_util.h
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
#ifndef HOG_REGISTER_UTIL_H_INCLUDED__
#define HOG_REGISTER_UTIL_H_INCLUDED__

#include <linux/applite/irecog/basic_type.h>

#ifdef _WIN32
#define inline _inline
#endif

/*------------------------------------------------------------------------------------------------
  dd_HOG_register_pack_xxx():
  Functions to generate a register value, which is too complex to generate with a structure.
------------------------------------------------------------------------------------------------*/

/* --ctrl--User Will Not Use CTRL Setting */

/* --initc-- User Will Not Use INTC Setting */

/* --roi_stride-- */
static inline REG_32 dd_HOG_register_pack_roi_stride_region(UINT roi_num_x,
							    UINT roi_num_y,
							    UINT stride_w,
							    UINT stride_h)
{
	return ((roi_num_x - 1) & 0x000000FF)
	    | (((roi_num_y - 1) & 0x000000FF) << 8)
	    | (((stride_w - 1) & 0x000000FF) << 16)
	    | (((stride_h - 1) & 0x000000FF) << 24);
}

static inline REG_32 dd_HOG_register_pack_roi_stride_position(UINT roi_num,
							      UINT stride_w,
							      UINT stride_h)
{
	return ((roi_num - 1) & 0x0000FFFF)
	    | ((stride_w & 0x000000FF) << 16)
	    | ((stride_h & 0x000000FF) << 24);
}

/* --src_size-- */
static inline REG_32 dd_HOG_register_pack_src_size(UINT width, UINT hight,
						   UINT half_byte_offset,
						   UINT format)
{
	return ((width - 1) & 0x0000FFFF)
	    | (((hight - 1) & 0x00000FFF) << 16)
	    | ((half_byte_offset & 0x00000001) << 28)
	    | ((format & 0x0000007) << 29);
}

static inline REG_32 dd_HOG_register_pack_src_size_dict(UINT size, UINT format)
{
	return ((size - 1) & 0x0FFFFFFFUL)
	    | ((format & 0x0000007) << 29);
}

/* --func-- User Will Not Use FUNC Setting */
static inline VOID dd_HOG_register_pack_func__func_mode(REG_32 *reg,
							UINT func_mode)
{
	*reg = (*reg & ~0x00000003UL)
	    | (func_mode & 0x00000003);
}

static inline VOID dd_HOG_register_pack_func__hog_mode(REG_32 *reg,
						       UINT hog_mode)
{
	*reg = (*reg & ~(0x00000001UL << 2))
	    | ((hog_mode & 0x00000001) << 2);
}

static inline VOID dd_HOG_register_pack_func__roi_mode(REG_32 *reg,
						       UINT roi_mode)
{
	*reg = (*reg & ~(0x00000001UL << 3))
	    | ((roi_mode & 0x00000001) << 3);
}

static inline VOID dd_HOG_register_pack_func__dict_num(REG_32 *reg,
						       UINT dict_num)
{
	*reg = (*reg & ~(0x00000003UL << 4))
	    | (((dict_num - 1) & 0x00000003) << 4);
}

/* --cell_num -- */
static inline REG_16 dd_HOG_register_pack_cell_num(UINT num_w, UINT num_h)
{
	return (REG_16) (((num_w - 1) & 0x00000007)
			 | (((num_h - 1) & 0x00000007) << 3));
}

/* --cell_format-- */
static inline REG_32 dd_HOG_register_pack_cell_format(UINT num_w, UINT num_h,
						      UINT size_w, UINT size_h)
{
	return (((num_w - 1) & 0x00000007)
		| (((num_h - 1) & 0x00000007) << 3))
	    | (((size_w - 1) & 0x000000FF) << 16)
	    | (((size_h - 1) & 0x000000FF) << 24);
}

/* --roi_size-- */
static inline REG_32 dd_HOG_register_pack_roi_size(UINT num_w, UINT num_h,
						   UINT size_w, UINT size_h)
{
	return (((num_w * size_w) - 1) & 0x0000FFFF)
	    | ((((num_h * size_h) - 1) & 0x0000FFFF) << 16);
}

#endif /* HOG_REGISTER_UTIL_H_INCLUDED__ */
