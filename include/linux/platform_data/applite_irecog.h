/*
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __APPLITE_IRECOG_H__
#define __APPLITE_IRECOG_H__

#define APPLITE_IRECOG_CLOCK_DISABLE 0
#define APPLITE_IRECOG_CLOCK_ENABLE  1

#define APPLITE_IRECOG_PYRAMID (0x1 << 0)
#define APPLITE_IRECOG_FILTER  (0x1 << 1)
#define APPLITE_IRECOG_HOG     (0x1 << 2)
#define APPLITE_IRECOG_AFFINE  (0x1 << 3)
#define APPLITE_IRECOG_HIST    (0x1 << 4)

struct applite_irecog_platform_data {
	void(*clock_enable)(unsigned int, int);
};

#endif /* __APPLITE_IRECOG_H__ */
