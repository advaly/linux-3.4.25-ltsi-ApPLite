/*
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __TXSS_ETH_PDATA_H__
#define __TXSS_ETH_PDATA_H__

struct txss_eth_platform_data {
	unsigned int is_rgmii:1;
	unsigned int gbit_support:1;
	unsigned int system_clock;
	unsigned int emacdrr;
	unsigned int fifosizer;
	unsigned int rx_buf_size;
};

#endif /* __TXSS_ETH_PDATA_H__ */
