/*
 * linux/arch/arm/include/asm/gtimer.h
 *
 * (C) Copyright TOSHIBA CORPORATION SEMICONDUCTOR COMPANY 2010
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef __ASMARM_GTIMER_H
#define __ASMARM_GTIMER_H

#include <linux/clockchips.h>
#include <asm/sched_clock.h>

#define GTMR_TIMER_COUNTER0		0x00
#define GTMR_TIMER_COUNTER1		0x04
#define GTMR_TIMER_CONTROL		0x08
#define GTMR_TIMER_INTSTAT		0x0C
#define GTMR_TIMER_VALUE0		0x10
#define GTMR_TIMER_VALUE1		0x14
#define GTMR_TIMER_AUTOINC		0x18

#define GTMR_TIMER_CONTROL_ENABLE	(1 << 0)
#define GTMR_TIMER_CONTROL_COMP_ENABLE	(1 << 1)
#define GTMR_TIMER_CONTROL_IT_ENABLE	(1 << 2)
#define GTMR_TIMER_CONTROL_ONESHOT	(0 << 3)
#define GTMR_TIMER_CONTROL_PERIODIC	(1 << 3)

extern void __iomem *gtmr_base;

void gtmr_clocksource_init(void);
void gtmr_timer_setup(struct clock_event_device *clk);
void gtmr_tick_setup(void);
void gtmr_setup(void __iomem *base, unsigned int irq, unsigned int rate);

void gtmr_sched_clock_init(void);

#endif
