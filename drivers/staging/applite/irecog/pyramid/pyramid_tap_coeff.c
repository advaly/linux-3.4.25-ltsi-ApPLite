/*
 * linux/drivers/staging/applite/irecog/pyramid/pyramid_tap_coeff.c
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
#include <linux/module.h>
#include "pyramid_tap_coeff.h"

#define TAP_NUM 32

static unsigned short lanczos2_050[TAP_NUM] = {
	0x0000, 0x03FF, 0x03FF, 0x03FE, 0x03FC, 0x03FB, 0x03F9, 0x03F8,
	0x03F7, 0x03F6, 0x03F5, 0x03F5, 0x03F6, 0x03F8, 0x03FC, 0x0000,
	0x0006, 0x000D, 0x0015, 0x001E, 0x0028, 0x0033, 0x003E, 0x0049,
	0x0053, 0x005E, 0x0067, 0x006F, 0x0076, 0x007A, 0x007D, 0x007E
};

static unsigned short lanczos2_059[TAP_NUM] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03FF, 0x03FE,
	0x03FC, 0x03FA, 0x03F8, 0x03F6, 0x03F4, 0x03F3, 0x03F3, 0x03F4,
	0x03F7, 0x03FC, 0x0003, 0x000D, 0x0018, 0x0025, 0x0033, 0x0042,
	0x0052, 0x0062, 0x0070, 0x007D, 0x0089, 0x0090, 0x0096, 0x0098
};

static unsigned short lanczos2_071[TAP_NUM] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x03FF, 0x03FD, 0x03FB, 0x03F8, 0x03F5, 0x03F2,
	0x03F1, 0x03F1, 0x03F4, 0x03FA, 0x0003, 0x0010, 0x0021, 0x0034,
	0x0049, 0x005F, 0x0075, 0x0089, 0x009A, 0x00A8, 0x00B0, 0x00B4
};

static unsigned short lanczos2_084[TAP_NUM] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03FF, 0x03FD, 0x03FA,
	0x03F6, 0x03F1, 0x03EE, 0x03EE, 0x03F1, 0x03FA, 0x0008, 0x001C,
	0x0036, 0x0053, 0x0073, 0x0092, 0x00AE, 0x00C3, 0x00CF, 0x00D4
};

/**************************************************/
/*
 * @brief get_tap_coeff_type
 *
 * @param filbase_value
 *
 * @return tap_id
 */
/**************************************************/
int get_tap_coeff_type(unsigned long filbase_value)
{
	if (filbase_value == 0) {
		return TAP_INVALID;
	}

	if (filbase_value > (0x0001AE89 + (0x00020000 - 0x0001AE89) / 2)) {
		return TAP_LANCZOS2_050;

	} else if (filbase_value > (0x00016A09 + (0x0001AE89 - 0x00016A09) / 2)) {
		return TAP_LANCZOS2_059;

	} else if (filbase_value >
		   (0x0001306F + (0x000016A09 - 0x0001306F) / 2)) {
		return TAP_LANCZOS2_071;

	} else {
		return TAP_LANCZOS2_084;
	}
}
EXPORT_SYMBOL(get_tap_coeff_type);

/**************************************************/
/*
 * @brief get_tap_coeff
 *
 * @param coeff_id
 * @param out_buf
 *
 */
/**************************************************/
void get_tap_coeff(int coeff_id, unsigned long *out_buf)
{
	int i;
	unsigned short *src;

	switch (coeff_id) {
	case TAP_LANCZOS2_050:
		src = lanczos2_050;
		break;
	case TAP_LANCZOS2_059:
		src = lanczos2_059;
		break;
	case TAP_LANCZOS2_071:
		src = lanczos2_071;
		break;
	case TAP_LANCZOS2_084:
		src = lanczos2_084;
		break;
	default:
		return;
	}

	for (i = 0; i < TAP_TABLE_SIZE; i++) {
		*(out_buf + i) =
		    ((*(src + i * 2) << 16) & 0xFFFF0000) | (*(src + i * 2 + 1)
							     & 0x0000FFFF);
	}
}
EXPORT_SYMBOL(get_tap_coeff);
