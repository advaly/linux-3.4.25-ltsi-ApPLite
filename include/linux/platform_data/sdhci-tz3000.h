/*
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __SDHCI_TZ3000_PDATA_H__
#define __SDHCI_TZ3000_PDATA_H__

enum sdhci_tz3000_ec_tune_mode {
	EC_SD_DS,
	EC_SD_HS,
	EC_SD_SDR12,
	EC_SD_SDR25,
	EC_SD_SDR50,
	EC_SD_SDR50_AUTO,
	EC_SD_SDR104,
	EC_SD_DDR50,
	EC_MMC_HS,
	EC_MMC_HS200,
	EC_MMC_HSDDR,
	EC_MMC_MAX,
};

struct sdhci_tz3000_ec_tune_param {
	int otap; /* -1 for OTAPDLYEN=0 */
	int itap; /* -1 for ITAPDLYEN=0 */
	unsigned int usedll:1;
	unsigned int autotune:1;
};

struct sdhci_tz3000_platform_data {
	unsigned long econf_emmc_base;
	struct sdhci_tz3000_ec_tune_param ec_tune_params[EC_MMC_MAX];
	unsigned int f_max;
	unsigned int mmc_caps2;
};

#endif /* __SDHCI_TZ3000_PDATA_H__ */
