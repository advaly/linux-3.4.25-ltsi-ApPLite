/*
 * linux/drivers/staging/applite/irecog/pyramid/pyramid_tap_coeff.h
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
#ifndef __PYRAMID_TAP_COEFF_H__
#define __PYRAMID_TAP_COEFF_H__

#define TAP_TABLE_SIZE 16

#define TAP_INVALID      -1
#define TAP_LANCZOS2_050  0
#define TAP_LANCZOS2_059  1
#define TAP_LANCZOS2_071  2
#define TAP_LANCZOS2_084  3

int get_tap_coeff_type(unsigned long filbase_value);
void get_tap_coeff(int coeff_id, unsigned long *out_buf);

#endif /* __PYRAMID_TAP_COEFF_H__ */
