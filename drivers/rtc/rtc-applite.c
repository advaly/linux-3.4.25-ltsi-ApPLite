/*
 * drivers/rtc/rtc-applite.c
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
#define __DEBUG

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/bcd.h>
#include <linux/rtc.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/io.h>
#include <linux/slab.h>

#include <mach/regs/rtc_offs_def.h>
#include <mach/regs/rtc_reg_def.h>


#define DRV_NAME	"applite-rtc"

#define SEC_MIN_MASK	0x7F
#define DAY_HOUR_MASK	0x3F
#define MON_MASK	0x1F
#define YEAR_MASK	0xFF
#define WEEK_MASK	0x07
#define M_D_Y_SHIFT	8
#define WEEK_SHIFT	5
#define INT_CLR		0x1
#define INT_MASK_ALL	0x3
#define PERIOD_1SEC	0x1

#define COMPTIME_31DAYS ((31 * 24 * 60 * 60) - 60)
#define COMPTIME_30DAYS ((30 * 24 * 60 * 60) - 60)
#define COMPTIME_29DAYS ((29 * 24 * 60 * 60) - 60)
#define COMPTIME_28DAYS ((28 * 24 * 60 * 60) - 60)

static unsigned char APPLITE_RTC_LEAP[4] = { 0, 1, 2, 3};


struct applite_rtc {
	void __iomem		*regbase;
	unsigned long		regsize;
	struct resource		*res;
	int			irq;
	struct rtc_device	*rtc_dev;
	spinlock_t		lock;
	unsigned int		mask_reg;
};



static int applite_rtc_alarm(struct applite_rtc *rtc)
{
	unsigned int tmp;

	/* disable alarm interrupt */
	tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	tmp &= ~RTC_RTC_CTRL_ALEN_MASK;
	__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);

	/* clear alarm interrupt */
	__raw_writel(INT_CLR, rtc->regbase + RTC_RTC_ALARM_INTCLR_OFFS);

	rtc_update_irq(rtc->rtc_dev, 1, RTC_AF | RTC_IRQF);

	return IRQ_HANDLED;
}

static int applite_rtc_period(struct applite_rtc *rtc)
{
	unsigned int tmp;

	/* disable period interrupt */
	tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	tmp &= ~RTC_RTC_CTRL_PREN_MASK;
	__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);

	/* clear period interrupt */
	__raw_writel(INT_CLR, rtc->regbase + RTC_RTC_PERIOD_INTCLR_OFFS);

	rtc_update_irq(rtc->rtc_dev, 1, RTC_UF | RTC_IRQF);

	return IRQ_HANDLED;
}

static irqreturn_t applite_rtc_interrupt(int irq, void *dev_id)
{
	struct applite_rtc *rtc = dev_id;
	unsigned int tmp;
	int ret;

	spin_lock(&rtc->lock);
	tmp = __raw_readl(rtc->regbase + RTC_RTC_RIS_OFFS);
	if (tmp & RTC_RTC_RIS_ALARM_INTRAWST_MASK)
		ret = applite_rtc_alarm(rtc);
	if (tmp & RTC_RTC_RIS_PERIOD_INTRAWST_MASK)
		ret = applite_rtc_period(rtc);
	spin_unlock(&rtc->lock);

	return IRQ_RETVAL(ret);
}


static int applite_rtc_proc(struct device *dev, struct seq_file *seq)
{
	struct applite_rtc *rtc = dev_get_drvdata(dev);
	unsigned int tmp, tmp2, tmp3, tmp4;

	tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	tmp2 = __raw_readl(rtc->regbase + RTC_RTC_INTMASK_OFFS);
	tmp3 = __raw_readl(rtc->regbase + RTC_RTC_RIS_OFFS);
	tmp4 = __raw_readl(rtc->regbase + RTC_RTC_MIS_OFFS);

	seq_printf(seq, "rtc controller\t: %s\n", (tmp & RTC_RTC_CTRL_TMEN_MASK) ?
			"enable" : "disable");
	seq_printf(seq, "hour\t\t: %s\n", (tmp & RTC_RTC_CTRL_HR24_12_MASK) ? "24h" : "12h");
	seq_printf(seq, "time loading\t: %s\n", (tmp & RTC_RTC_CTRL_TMRST_MASK) ? "yes" : "no");
	seq_printf(seq, "alarm time loading\t: %s\n", (tmp & RTC_RTC_CTRL_ALRST_MASK) ?
			"yes" : "no");

	seq_printf(seq, "alarm_IRQ\t: %s\n", (tmp & RTC_RTC_CTRL_ALEN_MASK) ? "enable" : "disable");
	seq_printf(seq, "alarm_MASK\t: %s\n", (tmp2 & RTC_RTC_INTMASK_ALARM_INTMASK_MASK) ?
			"unmask" : "mask");

	seq_printf(seq, "periodic_IRQ\t: %s\n", (tmp & RTC_RTC_CTRL_PREN_MASK) ?
			"enable" : "disable");
	seq_printf(seq, "periodic_MASK\t: %s\n", (tmp2 & RTC_RTC_INTMASK_PERIOD_INTMASK_MASK) ?
			"unmask" : "mask");

	return 0;
}

static int applite_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct applite_rtc *rtc = dev_get_drvdata(dev);
	unsigned int tmp;

	spin_lock_irq(&rtc->lock);

	tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);

	if (!enabled) {
		if (!rtc->rtc_dev->aie_timer.enabled)
			tmp &= ~RTC_RTC_CTRL_ALEN_MASK;
		if (!rtc->rtc_dev->uie_rtctimer.enabled)
			tmp &= ~RTC_RTC_CTRL_PREN_MASK;
	} else {
		if (rtc->rtc_dev->aie_timer.enabled)
			tmp |= RTC_RTC_CTRL_ALEN_MASK;
		if (rtc->rtc_dev->uie_rtctimer.enabled)
			tmp |= RTC_RTC_CTRL_PREN_MASK;
	}

	__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);

	dev_dbg(dev, "%s: irq:%s rtc_ctrl:0x%08x\n", __func__, (enabled) ? "enable" : "disable",
			__raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS));

	spin_unlock_irq(&rtc->lock);
	return 0;
}


static int applite_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct applite_rtc *rtc = platform_get_drvdata(pdev);
	unsigned int tmp, reg1, reg2, reg3, year;
	unsigned char leap_year;
	int cnt, err;

	spin_lock_irq(&rtc->lock);

	/* check of timer setting */
	cnt = 1000;
	do {
		tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	} while ((tmp & RTC_RTC_CTRL_TMRST_MASK) && (cnt-- > 0));
	if (cnt <= 0) {
		dev_err(dev, "%s:invalid RTC_CTRL_TMRST.\n", __func__);
		spin_unlock_irq(&rtc->lock);
		return -EILSEQ;
	}

	/* check timer value of register 2 times read */
	do {
		reg1 = __raw_readl(rtc->regbase + RTC_RTC_CURRENT1_OFFS);
		reg2 = __raw_readl(rtc->regbase + RTC_RTC_CURRENT2_OFFS);
		reg3 = __raw_readl(rtc->regbase + RTC_RTC_CURRENT3_OFFS);

		tmp = __raw_readl(rtc->regbase + RTC_RTC_CURRENT1_OFFS);
	} while ((reg1 & SEC_MIN_MASK) != (tmp & SEC_MIN_MASK));

	tm->tm_sec	= bcd2bin(reg1 & SEC_MIN_MASK);
	tm->tm_min	= bcd2bin((reg1 >> M_D_Y_SHIFT) & SEC_MIN_MASK);
	tm->tm_hour	= bcd2bin(reg2 & DAY_HOUR_MASK);
	tm->tm_mday	= bcd2bin((reg2 >> M_D_Y_SHIFT) & DAY_HOUR_MASK);
	tm->tm_mon	= bcd2bin(reg3 & MON_MASK) - 1;
	tm->tm_wday	= bcd2bin((reg3 >> WEEK_SHIFT) & WEEK_MASK);
	year	= bcd2bin((reg3 >> M_D_Y_SHIFT) & YEAR_MASK);

	/* year (1970-2069) */
	if (year >= 0 && year < 70)
		tm->tm_year = (year + 2000) - 1900;
	else if (year >= 70 && year <= 99)
		tm->tm_year = (year + 1900) - 1900;

	leap_year = (unsigned char)__raw_readl(rtc->regbase + RTC_RTC_CURRENT4_OFFS);

	spin_unlock_irq(&rtc->lock);

	dev_dbg(dev, "%s:%4d-%02d-%02d (%d) %02d:%02d:%02d leap:%d\n", __func__,
		1900 + tm->tm_year, tm->tm_mon+1, tm->tm_mday, tm->tm_wday,
		tm->tm_hour, tm->tm_min, tm->tm_sec, leap_year);

	err = rtc_valid_tm(tm);
	if (err != 0) {
		dev_dbg(dev, "%s:invalid date(%d)", __func__, err);
		return err;
	}

	return 0;
}

static int applite_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct applite_rtc *rtc = platform_get_drvdata(pdev);
	struct rtc_time cmp_tm;
	unsigned int tmp, year;
	unsigned char leap_year;
	unsigned long sec;
	int i;

	dev_dbg(dev, "%s:%4d-%02d-%02d (%d) %02d:%02d:%02d\n", __func__,
		1900 + tm->tm_year, tm->tm_mon+1, tm->tm_mday, tm->tm_wday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);

	/* check year (1970-2069) */
	if ((tm->tm_year < 70) || (tm->tm_year > 169)) {
		dev_err(dev, "%s:time is invalid.\n", __func__);
		return -EINVAL;
	}

	spin_lock_irq(&rtc->lock);

	/* time to seconds */
	rtc_tm_to_time(tm, &sec);

	/* set to tm_wday */
	rtc_time_to_tm(sec, &cmp_tm);

	dev_dbg(dev, "%s:cmp %4d-%02d-%02d (%d) %02d:%02d:%02d\n", __func__,
		1900 + cmp_tm.tm_year, cmp_tm.tm_mon+1, cmp_tm.tm_mday, cmp_tm.tm_wday,
		cmp_tm.tm_hour, cmp_tm.tm_min, cmp_tm.tm_sec);

	/* calculate of leap year */
	year = cmp_tm.tm_year + 1900;
	for (i = 4; i > 0; i--, year++) {
		if (is_leap_year(year))
			break;
	}
	leap_year = APPLITE_RTC_LEAP[i%4];

	/* year (1970-2069) */
	year = cmp_tm.tm_year + 1900;
	if (year >= 2000 && year < 2070)
		year -= 2000;
	else
		year -= 1900;

	/* set to time registers */
	tmp = (bin2bcd(cmp_tm.tm_sec)) | (bin2bcd(cmp_tm.tm_min) << M_D_Y_SHIFT);
	__raw_writel(tmp, rtc->regbase + RTC_RTC_TIMESET1_OFFS);

	tmp = (bin2bcd(tm->tm_hour)) | (bin2bcd(tm->tm_mday) << M_D_Y_SHIFT);
	__raw_writel(tmp, rtc->regbase + RTC_RTC_TIMESET2_OFFS);

	tmp = (bin2bcd(cmp_tm.tm_mon + 1)) | (cmp_tm.tm_wday << WEEK_SHIFT) |
				((bin2bcd(year) & YEAR_MASK) << M_D_Y_SHIFT);
	__raw_writel(tmp, rtc->regbase + RTC_RTC_TIMESET3_OFFS);

	__raw_writel(leap_year, rtc->regbase + RTC_RTC_TIMESET4_OFFS);

	/* load time data (rtc enable/data load/24h) */
	tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	tmp = RTC_RTC_CTRL_TMEN_MASK | RTC_RTC_CTRL_TMRST_MASK | RTC_RTC_CTRL_HR24_12_MASK;
	__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);

	/* check of timer setting */
	i = 1000;
	do {
		tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	} while ((tmp & RTC_RTC_CTRL_TMRST_MASK) && (i-- > 0));
	spin_unlock_irq(&rtc->lock);
	if (i <= 0) {
		dev_err(dev, "%s:invalid RTC_CTRL_TMRST.\n", __func__);
		return -EILSEQ;
	}

	return 0;
}

static int applite_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct applite_rtc *rtc = platform_get_drvdata(pdev);
	struct rtc_time *tm = &wkalrm->time;
	unsigned int reg1, reg2, reg3;
	unsigned int tmp;
	int cnt;


	spin_lock_irq(&rtc->lock);
	/* check of alarm timer setting */
	cnt = 1000;
	do {
		tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	} while ((tmp & RTC_RTC_CTRL_ALRST_MASK) && (cnt-- > 0));
	if (cnt <= 0) {
		dev_err(dev, "%s:invalid RTC_CTRL_ALRST.\n", __func__);
		spin_unlock_irq(&rtc->lock);
		return -EILSEQ;
	}

	/* read alarm registers */
	reg1 = __raw_readl(rtc->regbase + RTC_RTC_ALARM1_OFFS);
	reg2 = __raw_readl(rtc->regbase + RTC_RTC_ALARM2_OFFS);
	reg3 = __raw_readl(rtc->regbase + RTC_RTC_ALARM3_OFFS);

	/* set alarm time */
	tm->tm_sec	= 0;	/* set to 0 (sec is no support) */
	tm->tm_min	= bcd2bin((reg1 >> M_D_Y_SHIFT) & SEC_MIN_MASK);
	tm->tm_hour	= bcd2bin(reg2 & DAY_HOUR_MASK);
	tm->tm_mday	= bcd2bin((reg2 >> M_D_Y_SHIFT) & DAY_HOUR_MASK);
	tm->tm_wday	= bcd2bin((reg3 >> WEEK_SHIFT) & WEEK_MASK);
	tm->tm_mon	= -1;	/* month is no support */
	tm->tm_year	= -1;	/* year is no support */

	wkalrm->enabled = (__raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS) &
				RTC_RTC_CTRL_ALEN_MASK) ? 1 : 0;

	spin_unlock_irq(&rtc->lock);
	dev_dbg(dev, "%s:%s %4d-%02d-%02d (%d) %02d:%02d:%02d\n", __func__,
		(wkalrm->enabled) ? "enable" : "disable",
		tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_wday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);

	return 0;
}

static int applite_rtc_check_alarm(struct device *dev, struct rtc_time *tm, struct rtc_time *now_tm)
{
	int days, next_days;
	unsigned long now_sec, alm_sec;
	unsigned long comp_time;

	/* check to alarm seconds */
	if (tm->tm_sec) {
		dev_err(dev, "%s:alarm is %d seconds.\n", __func__, tm->tm_sec);
		return -EINVAL;
	}
	/* change to seconds */
	now_tm->tm_sec = 0;
	rtc_tm_to_time(now_tm, &now_sec);
	rtc_tm_to_time(tm, &alm_sec);

	/* get days of now month */
	days = rtc_month_days(now_tm->tm_mon, now_tm->tm_year + 1900);
	/* get days of next month */
	next_days = rtc_month_days((now_tm->tm_mon != 11) ? now_tm->tm_mon+1 : 0,
					now_tm->tm_year + 1900);

	comp_time = COMPTIME_31DAYS;
	if (days == 31) { /* 1,3,5,7,8,10,12 month */
		if ((next_days == 30) && (now_tm->tm_mday == 31)) /* next is 4,6,9,11 month */
			comp_time = COMPTIME_30DAYS;
		else if (next_days == 28) { /* next is February */
			if (now_tm->tm_mday == 29)
				comp_time = COMPTIME_30DAYS;
			else if (now_tm->tm_mday == 30)
				comp_time = COMPTIME_29DAYS;
			else if (now_tm->tm_mday == 31)
				comp_time = COMPTIME_28DAYS;
		} else if (next_days == 29) { /* next is February(reap_year) */
			if (now_tm->tm_mday == 30)
				comp_time = COMPTIME_30DAYS;
			else if (now_tm->tm_mday == 31)
				comp_time = COMPTIME_29DAYS;
		}
	} else if (days == 30) /* 4,6,9,11 month */
		comp_time = COMPTIME_30DAYS;
	else if (days == 29) /* February(reap_year) */
		comp_time = COMPTIME_29DAYS;
	else if (days == 28) /* February */
		comp_time = COMPTIME_28DAYS;
	dev_dbg(dev, "%s:cmp (%lu-%lu=%lu) > %lu\n", __func__,
		alm_sec, now_sec, (alm_sec - now_sec), comp_time);

	/* check alarm time */
	if ((alm_sec - now_sec) > comp_time) {
		dev_err(dev, "%s:alarm time is invalid.\n", __func__);
		return -EINVAL;
	}

	return 0;
}

static int applite_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct applite_rtc *rtc = platform_get_drvdata(pdev);
	struct rtc_time *tm = &wkalrm->time;
	struct rtc_time cmp_tm, now_tm;
	unsigned long sec, now_sec;
	unsigned int tmp;
	int err, cnt;

	/* time to seconds */
	rtc_tm_to_time(tm, &sec);
	/* set to tm_wday */
	rtc_time_to_tm(sec, &cmp_tm);

	/* read now time */
	applite_rtc_read_time(dev, &now_tm);
	/* time to seconds */
	rtc_tm_to_time(&now_tm, &now_sec);

	dev_dbg(dev, "%s:now %4d-%02d-%02d (%d) %02d:%02d:%02d\n", __func__,
		1900 + now_tm.tm_year, now_tm.tm_mon+1, now_tm.tm_mday, now_tm.tm_wday,
		now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec);
	dev_dbg(dev, "%s:alarm %4d-%02d-%02d (%d) %02d:%02d:%02d\n", __func__,
		1900 + cmp_tm.tm_year, cmp_tm.tm_mon+1, cmp_tm.tm_mday, cmp_tm.tm_wday,
		cmp_tm.tm_hour, cmp_tm.tm_min, cmp_tm.tm_sec);

	if (rtc->rtc_dev->uie_rtctimer.enabled && (!(sec-now_sec) || (sec-now_sec) == 1)) {
		dev_dbg(dev, "%s:uie timer set.\n", __func__);
		spin_lock_irq(&rtc->lock);
		/* set periodic */
		__raw_writel(PERIOD_1SEC, rtc->regbase + RTC_RTC_PERIODIC_OFFS);

		/* load periodic data */
		tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
		tmp |= RTC_RTC_CTRL_PRRST_MASK;
		__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);

		/* check of periodic timer setting */
		cnt = 1000;
		do {
			tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
		} while ((tmp & RTC_RTC_CTRL_PRRST_MASK) && (cnt-- > 0));
		spin_unlock_irq(&rtc->lock);
		if (cnt <= 0) {
			dev_err(dev, "%s:invalid RTC_CTRL_PRRST.\n", __func__);
			return -EILSEQ;
		}
	} else if (rtc->rtc_dev->aie_timer.enabled) {
		/* set alarm time */

		/* check alarm time */
		err = applite_rtc_check_alarm(dev, &cmp_tm, &now_tm);
		if (unlikely(err < 0))
			return err;

		dev_dbg(dev, "%s:aie timer set.\n", __func__);
		spin_lock_irq(&rtc->lock);
		/* disable alarm interrupt */
		tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
		tmp &= ~RTC_RTC_CTRL_ALEN_MASK;
		__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);
		/* clear alarm interrupt */
		__raw_writel(INT_CLR, rtc->regbase + RTC_RTC_ALARM_INTCLR_OFFS);

		/* set alarm time */
		tmp = (bin2bcd(cmp_tm.tm_min) << M_D_Y_SHIFT);
		__raw_writel(tmp, rtc->regbase + RTC_RTC_ALARM1_OFFS);

		tmp = (bin2bcd(cmp_tm.tm_hour)) | (bin2bcd(cmp_tm.tm_mday) << M_D_Y_SHIFT);
		__raw_writel(tmp, rtc->regbase + RTC_RTC_ALARM2_OFFS);

		tmp = cmp_tm.tm_wday << WEEK_SHIFT;
		__raw_writel(tmp, rtc->regbase + RTC_RTC_ALARM3_OFFS);

		/* load time data (rtc alarm data load/24h) */
		tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
		tmp |= RTC_RTC_CTRL_ALRST_MASK | RTC_RTC_CTRL_HR24_12_MASK;
		__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);

		/* check of alarm timer setting */
		cnt = 1000;
		do {
			tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
		} while ((tmp & RTC_RTC_CTRL_ALRST_MASK) && (cnt-- > 0));
		spin_unlock_irq(&rtc->lock);
		if (cnt <= 0) {
			dev_err(dev, "%s:invalid RTC_CTRL_ALRST.\n", __func__);
			return -EILSEQ;
		}
	} else
		return -EINVAL;

	if (wkalrm->enabled)
		applite_rtc_alarm_irq_enable(dev, 1);
	return 0;
}

static struct rtc_class_ops applite_rtc_ops = {
	.read_time	= applite_rtc_read_time,
	.set_time	= applite_rtc_set_time,
	.read_alarm	= applite_rtc_read_alarm,
	.set_alarm	= applite_rtc_set_alarm,
	.proc		= applite_rtc_proc,
	.alarm_irq_enable = applite_rtc_alarm_irq_enable,
};

static int __init applite_rtc_probe(struct platform_device *pdev)
{
	struct applite_rtc *rtc;
	struct resource *res;
	struct rtc_time r;
	unsigned int tmp;
	int ret;

	rtc = kzalloc(sizeof(struct applite_rtc), GFP_KERNEL);
	if (unlikely(!rtc)) {
		dev_err(&pdev->dev, "allocate failed\n");
		return -ENOMEM;
	}

	spin_lock_init(&rtc->lock);

	/* get irq */
	ret = platform_get_irq(pdev, 0);
	if (unlikely(ret <= 0)) {
		dev_err(&pdev->dev, "No IRQ resource\n");
		ret = -ENOENT;
		goto err_badmap;
	}
	rtc->irq = ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (unlikely(res == NULL)) {
		dev_err(&pdev->dev, "No IO resource\n");
		ret = -ENOENT;
		goto err_badmap;
	}

	rtc->regsize = resource_size(res);

	rtc->regbase = ioremap_nocache(res->start, rtc->regsize);
	if (unlikely(!rtc->regbase)) {
		dev_err(&pdev->dev, "ioremap failed\n");
		ret = -EINVAL;
		goto err_badmap;
	}

	/* register periodic/alarm irqs */
	ret = request_irq(rtc->irq, applite_rtc_interrupt,
			0, DRV_NAME, rtc);
	if (unlikely(ret)) {
		dev_err(&pdev->dev,
			"request IRQ failed with %d, IRQ %d\n",
			ret, rtc->irq);
		goto err_unmap;
	}

	spin_lock_irq(&rtc->lock);
	/* disable alarm & periodic */
	tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	tmp &= ~(RTC_RTC_CTRL_ALEN_MASK | RTC_RTC_CTRL_PREN_MASK);
	__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);
	/* clear interrupt*/
	__raw_writel(INT_CLR, rtc->regbase + RTC_RTC_ALARM_INTCLR_OFFS);
	__raw_writel(INT_CLR, rtc->regbase + RTC_RTC_PERIOD_INTCLR_OFFS);
	/* unmask interrupt*/
	__raw_writel(INT_MASK_ALL, rtc->regbase + RTC_RTC_INTMASK_OFFS);
	spin_unlock_irq(&rtc->lock);

	platform_set_drvdata(pdev, rtc);

	rtc->rtc_dev = rtc_device_register(DRV_NAME, &pdev->dev,
					&applite_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc->rtc_dev)) {
		dev_err(&pdev->dev, "Can't get RTC\n");
		ret = PTR_ERR(rtc->rtc_dev);
		goto err_irq;
	}

	/* reset rtc to epoch 0 if time is invalid */
	ret = rtc_read_time(rtc->rtc_dev, &r);
	if (ret < 0) {
		if (ret == -EILSEQ) {
			dev_err(&pdev->dev, "RTC controller illegal\n");
			goto err_dev;
		}
		rtc_time_to_tm(0, &r);
		if (rtc_set_time(rtc->rtc_dev, &r) == -EILSEQ) {
			dev_err(&pdev->dev, "RTC controller illegal\n");
			goto err_dev;
		}
	}
	/*rtc->rtc_dev->uie_unsupported = 1; */

	dev_dbg(&pdev->dev, "%s:ApPLite RTC Driver probed.\n", __func__);
	return 0;

err_dev:
	rtc_device_unregister(rtc->rtc_dev);
err_irq:
	free_irq(rtc->irq, rtc);
	platform_set_drvdata(pdev, NULL);
err_unmap:
	iounmap(rtc->regbase);
err_badmap:
	kfree(rtc);

	return ret;
}

static int __exit applite_rtc_remove(struct platform_device *pdev)
{
	struct applite_rtc *rtc = platform_get_drvdata(pdev);
	unsigned int tmp;

	rtc_device_unregister(rtc->rtc_dev);

	spin_lock_irq(&rtc->lock);
	/* disable alarm & periodic */
	tmp = __raw_readl(rtc->regbase + RTC_RTC_CTRL_OFFS);
	tmp &= ~(RTC_RTC_CTRL_ALEN_MASK | RTC_RTC_CTRL_PREN_MASK);
	__raw_writel(tmp, rtc->regbase + RTC_RTC_CTRL_OFFS);
	/* clear interrupt*/
	__raw_writel(INT_CLR, rtc->regbase + RTC_RTC_ALARM_INTCLR_OFFS);
	__raw_writel(INT_CLR, rtc->regbase + RTC_RTC_PERIOD_INTCLR_OFFS);
	/* mask interrupt*/
	__raw_writel(0, rtc->regbase + RTC_RTC_INTMASK_OFFS);
	spin_unlock_irq(&rtc->lock);

	free_irq(rtc->irq, rtc);

	iounmap(rtc->regbase);

	platform_set_drvdata(pdev, NULL);

	kfree(rtc);

	dev_dbg(&pdev->dev, "%s:ApPLite RTC Driver removed.\n", __func__);
	return 0;
}

static int applite_rtc_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct applite_rtc *rtc = platform_get_drvdata(pdev);

	dev_dbg(dev, "%s: start\n", __func__);
	spin_lock_irq(&rtc->lock);
	/* save mask register */
	rtc->mask_reg = __raw_readl(rtc->regbase + RTC_RTC_INTMASK_OFFS) & INT_MASK_ALL;
	/* mask interrupt */
	__raw_writel(0, rtc->regbase + RTC_RTC_INTMASK_OFFS);
	dev_dbg(dev, "%s: save mask_reg:0x%x\n", __func__, rtc->mask_reg);
	spin_unlock_irq(&rtc->lock);

	return 0;
}

static int applite_rtc_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct applite_rtc *rtc = platform_get_drvdata(pdev);

	dev_dbg(dev, "%s: start\n", __func__);
	spin_lock_irq(&rtc->lock);
	/* mask interrupt */
	__raw_writel(rtc->mask_reg, rtc->regbase + RTC_RTC_INTMASK_OFFS);
	dev_dbg(dev, "%s: restore mask_reg:0x%x\n", __func__,
			__raw_readl(rtc->regbase + RTC_RTC_INTMASK_OFFS));
	spin_unlock_irq(&rtc->lock);

	return 0;
}

static const struct dev_pm_ops applite_rtc_dev_pm_ops = {
	.suspend = applite_rtc_suspend,
	.resume = applite_rtc_resume,
};

static struct platform_driver applite_rtc_platform_driver = {
	.probe		= applite_rtc_probe,
	.remove		= __devexit_p(applite_rtc_remove),
	.driver = {
		.name	= DRV_NAME,
		.owner	= THIS_MODULE,
		.pm	=  &applite_rtc_dev_pm_ops
	},
};

module_platform_driver(applite_rtc_platform_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("ApP Lite  RTC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
