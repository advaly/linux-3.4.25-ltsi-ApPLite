/*
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __SPI_TC90431_PDATA_H__
#define __SPI_TC90431_PDATA_H__

struct spi_tc90431_platform_data {
	unsigned int hbus_clock;
	unsigned int baud_clock;
	unsigned int max_hz;
};

#endif /* __SPI_TC90431_PDATA_H__ */
