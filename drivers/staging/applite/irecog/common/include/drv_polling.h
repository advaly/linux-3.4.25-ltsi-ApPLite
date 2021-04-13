/*
 * linux/drivers/staging/applite/irecog/common/include/drv_polling.h
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
#ifndef DRV_POLLING_H_
#define DRV_POLLING_H_

#include <linux/io.h>
#include <linux/delay.h>

#define DRV_WAIT_REG_TIMEOUT    1000

static inline unsigned int drv_wait_register(void __iomem *reg,
					     unsigned int mask,
					     unsigned int val,
					     unsigned long timeout)
{
	unsigned int ret;
	unsigned long deadline;

	ret = ioread32(reg);

	deadline = jiffies + msecs_to_jiffies(timeout);

	while ((ret & mask) != val && time_before(jiffies, deadline)) {
		ret = ioread32(reg);
	}

	return ret;
}

#endif /* DRV_POLLING_H_ */
