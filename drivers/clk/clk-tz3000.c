/*
 * Toshiba TZ3000/TZ2000 clk implementation
 *
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <linux/clk-provider.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/clk-tz3000.h>

/**
 * DOC: tz3000/tz2000 gatable clock
 *
 * Traits of this clock:
 * prepare - clk_(un)prepare only ensures parent is (un)prepared
 * enable - clk_enable and clk_disable are functional & control gating
 * rate - inherits rate from parent.  No clk_set_rate support
 * parent - fixed parent.  No clk_set_parent support
 */

/**
 * struct clk_tz_gate - tz3000/tz2000 gatable clock
 *
 * @hw:		handle between common and hardware-specific interfaces
 * @reg:	register controlling gate (reg+0:gate-on, reg+0x400:gate-off)
 * @bit_mask:	multi bits controlling gate
 */
struct clk_tz_gate {
	struct clk_hw hw;
	void __iomem	*reg;
	u32		bit_mask;
	char		*parent[1];
};

#define to_clk_tz_gate(_hw) container_of(_hw, struct clk_tz_gate, hw)
#define CLK_TZ_GATINGOFF_OFFSET 0x400

static int clk_tz_gate_enable(struct clk_hw *hw)
{
	struct clk_tz_gate *gate = to_clk_tz_gate(hw);

	writel(gate->bit_mask, gate->reg + CLK_TZ_GATINGOFF_OFFSET);
	return 0;
}

static void clk_tz_gate_disable(struct clk_hw *hw)
{
	struct clk_tz_gate *gate = to_clk_tz_gate(hw);

	writel(gate->bit_mask, gate->reg);
}

static int clk_tz_gate_is_enabled(struct clk_hw *hw)
{
	struct clk_tz_gate *gate = to_clk_tz_gate(hw);

	return (readl(gate->reg) & gate->bit_mask) == gate->bit_mask ? 0 : 1;
}

static struct clk_ops clk_tz_gate_ops = {
	.enable = clk_tz_gate_enable,
	.disable = clk_tz_gate_disable,
	.is_enabled = clk_tz_gate_is_enabled,
};

struct clk *clk_register_tz_gate_m(struct device *dev, const char *name,
		const char *parent_name, unsigned long flags,
		void __iomem *reg, u32 bit_mask)
{
	struct clk_tz_gate *gate;
	struct clk *clk;

	gate = kzalloc(sizeof(*gate), GFP_KERNEL);

	if (!gate) {
		pr_err("%s: could not allocate gated clk\n", __func__);
		return NULL;
	}

	/* struct clk_tz_gate assignments */
	gate->reg = reg;
	gate->bit_mask = bit_mask;

	if (parent_name) {
		gate->parent[0] = kstrdup(parent_name, GFP_KERNEL);
		if (!gate->parent[0])
			goto out;
	}

	clk = clk_register(dev, name,
			&clk_tz_gate_ops, &gate->hw,
			gate->parent,
			(parent_name ? 1 : 0),
			flags);
	if (clk)
		return clk;
out:
	kfree(gate->parent[0]);
	kfree(gate);

	return NULL;
}
