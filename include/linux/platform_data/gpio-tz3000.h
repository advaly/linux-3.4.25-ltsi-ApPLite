/*
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __GPIO_TZ3000_PDATA_H__
#define __GPIO_TZ3000_PDATA_H__

struct tz3000_gpio_platform_data {
	unsigned int gpio_base;
	unsigned int nr_gpio;
	unsigned int irq_base;
};

#endif /* __GPIO_TZ3000_PDATA_H__ */
