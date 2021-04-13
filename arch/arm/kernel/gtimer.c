/*
 *  linux/arch/arm/kernel/smp_gtmr.c
 *
 * (C) Copyright TOSHIBA CORPORATION SEMICONDUCTOR COMPANY 2010
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) "GTMR: " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/smp.h>
#include <linux/jiffies.h>
#include <linux/clockchips.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/io.h>

#include <asm/gtimer.h>

/* set up by the platform code */
void __iomem *gtmr_base;
static unsigned long gtmr_timer_rate;
static int gtmr_irq;

static struct clock_event_device * __percpu *gtmr_evt;

static cycle_t gtmr_get_cycles(struct clocksource *cs)
{
	cycle_t cycles, count0, count1, tmp;

	tmp = (cycle_t) __raw_readl(gtmr_base + GTMR_TIMER_COUNTER1);
	while (1) {
		count0 = (cycle_t) __raw_readl(gtmr_base + GTMR_TIMER_COUNTER0);
		count1 = (cycle_t) __raw_readl(gtmr_base + GTMR_TIMER_COUNTER1);
		if (count1 == tmp)
			break;
		tmp = count1;
	}

	cycles = (count1 << 32) | count0;
	return cycles;
}

static unsigned long gtmr_ctrl;
static unsigned long gtmr_counter0;
static unsigned long gtmr_counter1;

static void gtmr_clocksource_suspend(struct clocksource *cs)
{
	gtmr_ctrl = __raw_readl(gtmr_base + GTMR_TIMER_CONTROL);
	gtmr_counter0 = __raw_readl(gtmr_base + GTMR_TIMER_COUNTER0);
	gtmr_counter1 = __raw_readl(gtmr_base + GTMR_TIMER_COUNTER1);
}

static void gtmr_clocksource_resume(struct clocksource *cs)
{
	unsigned long ctrl;
	unsigned int autoinc;

	autoinc = gtmr_timer_rate / HZ;

	pr_info("GTIMER counter at resume : %ld (msec)\n",
		__raw_readl(gtmr_base +
			    GTMR_TIMER_COUNTER0)/(gtmr_timer_rate/1000));

	ctrl = __raw_readl(gtmr_base + GTMR_TIMER_CONTROL);
	ctrl &= ~GTMR_TIMER_CONTROL_ENABLE;
	__raw_writel(ctrl, gtmr_base + GTMR_TIMER_CONTROL);

	__raw_writel(gtmr_counter0, gtmr_base + GTMR_TIMER_COUNTER0);
	__raw_writel(gtmr_counter1, gtmr_base + GTMR_TIMER_COUNTER1);
	__raw_writel(autoinc, gtmr_base + GTMR_TIMER_VALUE0);
	__raw_writel(0x0, gtmr_base + GTMR_TIMER_VALUE1);

	__raw_writel(autoinc, gtmr_base + GTMR_TIMER_AUTOINC);

	__raw_writel(gtmr_ctrl, gtmr_base + GTMR_TIMER_CONTROL);
}

static struct clocksource clocksource_gtmr = {
	.name	= "gtmr",
	.rating	= 200,
	.read	= gtmr_get_cycles,
	.mask	= CLOCKSOURCE_MASK(64),
	.shift	= 20,
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
	.suspend = gtmr_clocksource_suspend,
	.resume = gtmr_clocksource_resume,
};

void __init gtmr_clocksource_init(void)
{
	clocksource_gtmr.mult =
		clocksource_hz2mult(gtmr_timer_rate, clocksource_gtmr.shift);
	clocksource_register(&clocksource_gtmr);
}

static void gtmr_set_mode(enum clock_event_mode mode,
			  struct clock_event_device *clk)
{
	unsigned long ctrl;

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		/* timer load already set up */
		ctrl =
		    GTMR_TIMER_CONTROL_COMP_ENABLE |
		    GTMR_TIMER_CONTROL_IT_ENABLE | GTMR_TIMER_CONTROL_PERIODIC;
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		/* period set, and timer enabled in 'next_event' hook */
		ctrl =
		    GTMR_TIMER_CONTROL_COMP_ENABLE |
		    GTMR_TIMER_CONTROL_IT_ENABLE | GTMR_TIMER_CONTROL_ONESHOT;
		break;
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
	default:
		ctrl = 0;
	}
	ctrl |= GTMR_TIMER_CONTROL_ENABLE;

	__raw_writel(ctrl, gtmr_base + GTMR_TIMER_CONTROL);
}

static int gtmr_set_next_event(unsigned long delta,
			       struct clock_event_device *unused)
{
	unsigned long ctrl = __raw_readl(gtmr_base + GTMR_TIMER_CONTROL);
	u64 count, count0, count1;
	u32 value0, value1;

	ctrl &= ~GTMR_TIMER_CONTROL_ENABLE;
	__raw_writel(ctrl, gtmr_base + GTMR_TIMER_CONTROL);

	count1 = (u64) __raw_readl(gtmr_base + GTMR_TIMER_COUNTER1);
	count0 = (u64) __raw_readl(gtmr_base + GTMR_TIMER_COUNTER0);
	count = (count1 << 32) | count0;

	count += delta;

	value0 = (u32) (count & 0xffffffff);
	value1 = (u32) ((count >> 32) & 0xffffffff);
	__raw_writel(value0, gtmr_base + GTMR_TIMER_VALUE0);
	__raw_writel(value1, gtmr_base + GTMR_TIMER_VALUE1);

	ctrl |= GTMR_TIMER_CONTROL_ENABLE;
	__raw_writel(ctrl, gtmr_base + GTMR_TIMER_CONTROL);

	return 0;
}


/*
 * IRQ handler for the timer
 */
static irqreturn_t gtmr_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = *(struct clock_event_device **)dev_id;

	if (evt->event_handler == NULL)
		return IRQ_HANDLED;

	/* clear the interrupt */
	__raw_writel(1, gtmr_base + GTMR_TIMER_INTSTAT);

	evt->event_handler(evt);

	return IRQ_HANDLED;
}

/*
 * Setup the clock events
 */
void __cpuinit gtmr_timer_setup(struct clock_event_device *clk)
{
	/* enable clock in gtmr_clocksource_init() */

	struct clock_event_device **this_cpu_clk;

	if (!gtmr_evt) {
		int err;

		gtmr_evt = alloc_percpu(struct clock_event_device *);
		if (!gtmr_evt) {
			pr_err("gtmr: can't allocate memory\n");
			return;
		}

		err = request_percpu_irq(clk->irq, gtmr_timer_interrupt,
					 "gtmr", gtmr_evt);
		if (err) {
			pr_err("gtmr: can't register interrupt %d (%d)\n",
			       clk->irq, err);
			return;
		}
	}

	clk->name = "CA9 global timer";
#ifdef CONFIG_ARM_ERRATA_740657
	clk->features = CLOCK_EVT_FEAT_PERIODIC;
#else
	clk->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
#endif
	clk->rating = 250;
	clk->set_mode = gtmr_set_mode;
	clk->set_next_event = gtmr_set_next_event;
	clk->shift = 20;
	clk->mult = div_sc(gtmr_timer_rate, NSEC_PER_SEC, clk->shift);
	clk->max_delta_ns = clockevent_delta2ns(0xffffffff, clk);
	clk->min_delta_ns = clockevent_delta2ns(0x3ff, clk);

	this_cpu_clk = __this_cpu_ptr(gtmr_evt);
	*this_cpu_clk = clk;

	clockevents_register_device(clk);

	enable_percpu_irq(clk->irq, 0);
}

static struct clock_event_device gtmr_clockevent;

void __cpuinit gtmr_tick_setup(void)
{
	gtmr_clockevent.irq = gtmr_irq;
	gtmr_clockevent.cpumask = cpumask_of(0);

	gtmr_timer_setup(&gtmr_clockevent);
}

void __cpuinit gtmr_setup(void __iomem *base, unsigned int irq,
			  unsigned int rate)
{
	unsigned long ctrl;
	unsigned int autoinc;

	gtmr_base = base;
	gtmr_timer_rate = rate;
	gtmr_irq = irq;

	autoinc = gtmr_timer_rate / HZ;

	pr_info("GTIMER counter at init : %ld (msec)\n",
		__raw_readl(gtmr_base +
			    GTMR_TIMER_COUNTER0)/(gtmr_timer_rate/1000));

	ctrl = __raw_readl(gtmr_base + GTMR_TIMER_CONTROL);
	ctrl &= ~GTMR_TIMER_CONTROL_ENABLE;
	__raw_writel(ctrl, gtmr_base + GTMR_TIMER_CONTROL);

	__raw_writel(autoinc, gtmr_base + GTMR_TIMER_VALUE0);
	__raw_writel(0x0, gtmr_base + GTMR_TIMER_VALUE1);

	__raw_writel(autoinc, gtmr_base + GTMR_TIMER_AUTOINC);

	/* enable, no interrupt or reload */
	ctrl = GTMR_TIMER_CONTROL_ENABLE;
	__raw_writel(ctrl, gtmr_base + GTMR_TIMER_CONTROL);
}

static u32 notrace gtmr_read_sched_clock(void)
{
	if (gtmr_base)
		return __raw_readl(gtmr_base + GTMR_TIMER_COUNTER0);
	return 0;
}

void __init gtmr_sched_clock_init(void)
{
	setup_sched_clock(gtmr_read_sched_clock, 32, gtmr_timer_rate);
}
