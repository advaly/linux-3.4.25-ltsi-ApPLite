/*
 * linux/drivers/staging/applite/irecog/pyramid/pyramid_setup.h
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
#ifndef __PYRAMID_SETUP_H__
#define __PYRAMID_SETUP_H__

#include <linux/io.h>

#include <linux/applite/irecog/pyramid_ioctl.h>

#define PYM_DISABLE 0
#define PYM_ENABLE 1

void setup_read_port(void __iomem *rvdmac_base,
		     unsigned int port_no,
		     unsigned int enabled,
		     unsigned long phy_adr,
		     unsigned long width,
		     unsigned long height, unsigned long pitch);

void setup_write_port(void __iomem *rvdmac_base,
		      unsigned int port_no,
		      unsigned int enabled,
		      unsigned long phy_adr,
		      unsigned long width,
		      unsigned long height, unsigned long pitch);

void setup_table_port(void __iomem *rvdmac_base,
		      unsigned int id,
		      unsigned int enabled,
		      unsigned long phy_adr, unsigned long size);

void setup_rscaler(void __iomem *rscaler_base, pyramid_param *param);
void initialize(void __iomem *rvdmac_base);

#endif /* __PYRAMID_SETUP_H__ */
