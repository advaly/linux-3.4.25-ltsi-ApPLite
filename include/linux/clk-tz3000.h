/*
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __CLK_TZ3000_H__
#define __CLK_TZ3000_H__

#include <linux/clk-provider.h>
#include <linux/clkdev.h>

struct clk *clk_register_tz_gate_m(struct device *dev, const char *name,
		const char *parent_name, unsigned long flags,
		void __iomem *reg, u32 bit_mask);
#define clk_register_tz_gate(dev, name, parent_name, flags, reg, bit_idx) \
	clk_register_tz_gate_m(dev, name, parent_name, flags, reg, BIT(bit_idx))

struct clk *clk_register_tz_gate_m(struct device *dev, const char *name,
		const char *parent_name, unsigned long flags,
		void __iomem *reg, u32 bit_mask);

#endif /* __CLK_TZ3000_H__ */
