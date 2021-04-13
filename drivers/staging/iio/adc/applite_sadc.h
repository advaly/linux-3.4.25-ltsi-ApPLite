/*
 * drivers/staging/iio/adc/applite_sadc.h
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2013
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

#ifndef __APPLITE_SADC
#define __APPLITE_SADC

/*
 * APPLITE Slow ADC registers definitions
 */

/* Bit definitions for SADCH[CH NO.] */
#ifdef CONFIG_ARCH_TZ3000
#define SADCH_VALUE_MASK	0x000003FF
#endif
#ifdef CONFIG_ARCH_TZ2000
#define SADCH_VALUE_MASK	0x00000FFF
#endif

/* Bit definitions for SADCTRL: */
#define SADCTRL_VALID		0x00000004
#define SADCTRL_STB		0x00000002
#define SADCTRL_RST		0x00000001

/* Bit definitions for SADDEBUG: */
#define SADDEBUG_ERR0		0x00000040
#define SADDEBUG_ERR1		0x00000020
#define SADDEBUG_ERR2		0x00000010
#define SADDEBUG_ERRMSK		0x00000070
#define SADDEBUG_STS		0x00000007

/* Status definitions for SADDEBUG_STS */
enum {
	SADC_INITIAL = 0,
	SADC_RESET,
	SADC_STB,
	SADC_WAIT,
	SADC_START,
	SADC_CONV,
	SADC_READ,
};

#define SADCH_MAX		16
#ifdef CONFIG_ARCH_TZ3000
#define SADCH_NUM		6
#endif
#ifdef CONFIG_ARCH_TZ2000
#define SADCH_NUM		4
#endif


/*
 * APPLITE Slow ADC registers structure definitions
 */

struct al_sadc_reg {
	u32 sadch[SADCH_MAX];
	u32 sadctrl;
	u32 saddebug;
};


/*
 * APPLITE Slow ADC definitions
 */

#define SADC_ERR_NONE		0


/*
 * APPLITE Slow ADC structure definitions
 */

struct al_sadc_info {
	struct al_sadc_reg *sadc_reg;
	struct clk *clk;
	void __iomem *pmu_base;

	wait_queue_head_t wq_data_avail;
	bool done;

	int sadc_wait_flg;
	int sadc_err;
	unsigned int data[SADCH_NUM]		____cacheline_aligned;
	int sadc_usecount;
};


#endif /* __APPLITE_SADC */
