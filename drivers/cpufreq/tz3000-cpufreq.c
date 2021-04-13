/*
 * A cpufreq driver for TZ3000
 *
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/cpufreq.h>
#include <linux/platform_data/tz3000-cpufreq.h>
#include <asm/cpu.h>

/* index field is CPU_Clock_Divide_Setting register value */
static struct cpufreq_frequency_table tz3000_freq_table[] = {
	{ .index = 0x44081000 }, /* /1 */
	{ .index = 0x88082100 }, /* /2 */
	{ .index = 0x88084200 }, /* /4 */
	{ .index = 0x88088400 }, /* /8 */
	{ .frequency = CPUFREQ_TABLE_END },
};
static struct tz3000_cpufreq_platform_data *tz3000_pdata;

#ifdef CONFIG_SMP
struct lpj_info {
	unsigned long	ref;
	unsigned int	freq;
};

static DEFINE_PER_CPU(struct lpj_info, lpj_ref);
static struct lpj_info global_lpj_ref;
#endif

static int tz3000_verify_speed(struct cpufreq_policy *policy)
{
	struct cpufreq_frequency_table *freq_table = tz3000_freq_table;
	return cpufreq_frequency_table_verify(policy, freq_table);
}

static unsigned int tz3000_getspeed(unsigned int cpu)
{
	struct tz3000_cpufreq_platform_data *pdata = tz3000_pdata;
	u32 div;
	div = (__raw_readl(pdata->clkdiv_reg) >> 8) & 0xf;
	div = div ? div * 2 : 1;
	return pdata->pllclk / div / 1000;
}

static int tz3000_target(struct cpufreq_policy *policy,
			 unsigned int target_freq,
			 unsigned int relation)
{
	struct tz3000_cpufreq_platform_data *pdata = tz3000_pdata;
	struct cpufreq_frequency_table *freq_table = tz3000_freq_table;
	struct cpufreq_freqs freqs;
	unsigned int index;
	int i;

	freqs.old = policy->cur;

	if (cpufreq_frequency_table_target(policy, freq_table,
					   target_freq, relation, &index))
		return -EINVAL;

	freqs.new = freq_table[index].frequency;
	freqs.cpu = policy->cpu;
	if (freqs.old == freqs.new)
		return 0;

	pr_debug("%s: transition: %u --> %u (clkdiv 0x%x)\n",
		 __func__, freqs.old, freqs.new, freq_table[index].index);

	for_each_cpu(i, policy->cpus) {
		freqs.cpu = i;
		cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);
	}

	local_irq_disable();
	/* DivEn = 0 */
	__raw_writel(__raw_readl(pdata->clkdiv_reg) & ~0x1, pdata->clkdiv_reg);
	dsb();
	outer_sync();
	__raw_writel(freq_table[index].index, pdata->clkdiv_reg);
	dsb();
	outer_sync();
	/* DivEn = 1 */
	__raw_writel(__raw_readl(pdata->clkdiv_reg) | 0x1, pdata->clkdiv_reg);
	local_irq_enable();

#ifdef CONFIG_SMP /* not needed for v3.7 or lator */
	/*
	 * Note that loops_per_jiffy is not updated on SMP systems in
	 * cpufreq driver. So, update the per-CPU loops_per_jiffy value
	 * on frequency transition. We need to update all dependent CPUs.
	 */
	for_each_cpu(i, policy->cpus) {
		struct lpj_info *lpj = &per_cpu(lpj_ref, i);
		if (!lpj->freq) {
			lpj->ref = per_cpu(cpu_data, i).loops_per_jiffy;
			lpj->freq = freqs.old;
		}

		per_cpu(cpu_data, i).loops_per_jiffy =
			cpufreq_scale(lpj->ref, lpj->freq, freqs.new);
	}

	/* And don't forget to adjust the global one */
	if (!global_lpj_ref.freq) {
		global_lpj_ref.ref = loops_per_jiffy;
		global_lpj_ref.freq = freqs.old;
	}
	loops_per_jiffy = cpufreq_scale(global_lpj_ref.ref, global_lpj_ref.freq,
					freqs.new);
#endif
	for_each_cpu(i, policy->cpus) {
		freqs.cpu = i;
		cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);
	}
	return 0;
}

static int tz3000_cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	struct cpufreq_frequency_table *freq_table = tz3000_freq_table;
	int ret;

	pr_debug("%s: cpu %u\n", __func__, policy->cpu);

	policy->cur = tz3000_getspeed(policy->cpu);
	policy->min = policy->cur;
	policy->max = policy->cur;
	policy->cpuinfo.transition_latency = 0;
	cpumask_setall(policy->cpus);
	ret = cpufreq_frequency_table_cpuinfo(policy, freq_table);
	if (ret)
		return ret;
	cpufreq_frequency_table_get_attr(freq_table, policy->cpu);
	return ret;
}

static int tz3000_cpufreq_cpu_exit(struct cpufreq_policy *policy)
{
	cpufreq_frequency_table_put_attr(policy->cpu);
	return 0;
}

static struct freq_attr *tz3000_cpufreq_attr[] = {
	&cpufreq_freq_attr_scaling_available_freqs,
	NULL,
};

static struct cpufreq_driver tz3000_driver = {
	.flags		= CPUFREQ_STICKY,
	.verify		= tz3000_verify_speed,
	.target		= tz3000_target,
	.get		= tz3000_getspeed,
	.init		= tz3000_cpufreq_cpu_init,
	.exit		= tz3000_cpufreq_cpu_exit,
	.name		= "tz3000_cpufreq",
	.attr           = tz3000_cpufreq_attr,
};

static int __init tz3000_cpufreq_probe(struct platform_device *pdev)
{
	struct tz3000_cpufreq_platform_data *pdata = pdev->dev.platform_data;
	int i;

	if (!pdata)
		return -EINVAL;
	tz3000_pdata = pdata;

	/* initialize frequency table */
	for (i = 0; i < ARRAY_SIZE(tz3000_freq_table) - 1; i++) {
		u32 div = (tz3000_freq_table[i].index >> 8) & 0xf;
		div = div ? div * 2 : 1;
		tz3000_freq_table[i].frequency = pdata->pllclk / div / 1000;
#if !IS_ENABLED(CONFIG_MIGHT_HAVE_CACHE_L2X0)
		tz3000_freq_table[i].index &= ~0xf000;
#endif
		pr_debug("%s: freq: %u index: 0x%x\n",
			 __func__, tz3000_freq_table[i].frequency,
			 tz3000_freq_table[i].index);
	}

	return cpufreq_register_driver(&tz3000_driver);
}

static int __exit tz3000_cpufreq_remove(struct platform_device *pdev)
{
	return cpufreq_unregister_driver(&tz3000_driver);
}

static struct platform_driver tz3000_cpufreq_driver = {
	.driver = {
		.name	 = "tz3000-cpufreq",
		.owner	 = THIS_MODULE,
	},
	.remove = __exit_p(tz3000_cpufreq_remove),
};

static int __init tz3000_cpufreq_init(void)
{
	return platform_driver_probe(&tz3000_cpufreq_driver,
				     tz3000_cpufreq_probe);
}
late_initcall(tz3000_cpufreq_init);
