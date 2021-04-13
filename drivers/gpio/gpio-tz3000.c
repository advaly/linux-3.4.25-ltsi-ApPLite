/*
 * A gpio chip driver for TZ3000
 *
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include <linux/errno.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/platform_data/gpio-tz3000.h>
#include <linux/syscore_ops.h>
#include <asm/mach/irq.h>
#include <mach/platform.h>

#define GP_CR		0x00
#define GP_DR		0x04
#define GP_ODS		0x08
#define GP_ODC		0x0c
#define GP_INTS		0x10
#define GP_INTC(n)	(0x14 + (n) * 4)
#define GP_INTM(n)	(0x1c + (n) * 4)
#define GP_SMP		0x30
#define GP_ODR		0x34
#define GP_IR(n)	(0x38 + (n) * 4)
#define GP_ODTP		0x4c
#define GP_PUDEN	0x50
#define GP_PUDSEL	0x54
#define GP_INPEN	0x58

#ifdef CONFIG_TZ3000_SGPIO
#define SGPIO_MBOX_CLEAR 0x430
#define SGPIO_MBOX_MASK 0x830
#endif

struct tz3000_gpio_chip {
	struct gpio_chip chip;
	char label[16];
	void __iomem *regbase;
	unsigned int irq_base;
#ifdef CONFIG_TZ3000_SGPIO
	void __iomem *sgpio_regbase;
	u32 cur_mask;
#endif
#ifdef CONFIG_PM_SLEEP
	struct {
		u32 cr;
		u32 intc[2];
		u32 intm;
		u32 smp;
		u32 odr;
		u32 odtp;
		u32 puden;
		u32 pudsel;
		u32 inpen;
	} saved;
#endif
};
#define to_tz3000_gpio_chip(c) container_of(c, struct tz3000_gpio_chip, chip)

static DEFINE_SPINLOCK(tz3000_gpio_lock);

static int tz3000_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct tz3000_gpio_chip *tz3000_gpio = to_tz3000_gpio_chip(chip);
	return __raw_readl(tz3000_gpio->regbase + GP_DR) & (1 << offset);
}

static void tz3000_gpio_set(struct gpio_chip *chip, unsigned int offset,
			    int value)
{
	struct tz3000_gpio_chip *tz3000_gpio = to_tz3000_gpio_chip(chip);
	if (value)
		__raw_writel(1 << offset, tz3000_gpio->regbase + GP_ODS);
	else
		__raw_writel(1 << offset, tz3000_gpio->regbase + GP_ODC);
}

static int tz3000_gpio_dir_in(struct gpio_chip *chip, unsigned int offset)
{
	struct tz3000_gpio_chip *tz3000_gpio = to_tz3000_gpio_chip(chip);
	void __iomem *reg = tz3000_gpio->regbase + GP_CR;
	unsigned long flags;
	spin_lock_irqsave(&tz3000_gpio_lock, flags);
	__raw_writel(__raw_readl(reg) & ~(1 << offset), reg);
	spin_unlock_irqrestore(&tz3000_gpio_lock, flags);
	return 0;
}

static int tz3000_gpio_dir_out(struct gpio_chip *chip, unsigned int offset,
			     int value)
{
	struct tz3000_gpio_chip *tz3000_gpio = to_tz3000_gpio_chip(chip);
	void __iomem *reg = tz3000_gpio->regbase + GP_CR;
	unsigned long flags;

	spin_lock_irqsave(&tz3000_gpio_lock, flags);
	/* direction must be set before data value */
	__raw_writel(__raw_readl(reg) | (1 << offset), reg);
	tz3000_gpio_set(chip, offset, value);
	spin_unlock_irqrestore(&tz3000_gpio_lock, flags);
	return 0;
}

static int tz3000_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct tz3000_gpio_chip *tz3000_gpio = to_tz3000_gpio_chip(chip);
	return tz3000_gpio->irq_base + offset;
}

static void tz3000_gpio_irq_mask(struct irq_data *d)
{
	struct tz3000_gpio_chip *tz3000_gpio = irq_data_get_irq_chip_data(d);
	unsigned offset = d->irq - tz3000_gpio->irq_base;
	void __iomem *reg = tz3000_gpio->regbase + GP_INTM(0);
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&tz3000_gpio_lock, flags);
	val = __raw_readl(reg) | (1 << offset);
	__raw_writel(val, reg);
#ifdef CONFIG_TZ3000_SGPIO
	tz3000_gpio->cur_mask = val;
#endif
	spin_unlock_irqrestore(&tz3000_gpio_lock, flags);
}

static void tz3000_gpio_irq_unmask(struct irq_data *d)
{
	struct tz3000_gpio_chip *tz3000_gpio = irq_data_get_irq_chip_data(d);
	unsigned offset = d->irq - tz3000_gpio->irq_base;
	void __iomem *reg = tz3000_gpio->regbase + GP_INTM(0);
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&tz3000_gpio_lock, flags);
	val = __raw_readl(reg) & ~(1 << offset);
	__raw_writel(val, reg);
#ifdef CONFIG_TZ3000_SGPIO
	tz3000_gpio->cur_mask = val;
#endif
	spin_unlock_irqrestore(&tz3000_gpio_lock, flags);
}

static int tz3000_gpio_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct tz3000_gpio_chip *tz3000_gpio = irq_data_get_irq_chip_data(d);
	unsigned offset = d->irq - tz3000_gpio->irq_base;
	void __iomem *reg = tz3000_gpio->regbase + GP_INTC(offset / 16);
	unsigned long flags;
	int mode;
	u32 val;
	unsigned int shift;

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_RISING:
		mode = 3;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		mode = 1;
		break;
	default:
		return -EINVAL;
	}

	shift = (offset % 16) * 2;
	spin_lock_irqsave(&tz3000_gpio_lock, flags);
	val = __raw_readl(reg);
	val = (val & ~(3 << shift)) | (mode << shift);
	__raw_writel(val, reg);
	spin_unlock_irqrestore(&tz3000_gpio_lock, flags);
	return 0;
}

static void tz3000_gpio_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	struct tz3000_gpio_chip *tz3000_gpio = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	int i;
	u32 status;

	chained_irq_enter(chip, desc);
#ifdef CONFIG_TZ3000_SGPIO
	if (irq == IRQ_SGPIO)
		__raw_writel(1, tz3000_gpio->sgpio_regbase + SGPIO_MBOX_CLEAR);
#endif
	status = __raw_readl(tz3000_gpio->regbase + GP_IR(0));
#ifdef CONFIG_TZ3000_SGPIO
	status &= ~tz3000_gpio->cur_mask;
#else
	status &= ~__raw_readl(tz3000_gpio->regbase + GP_INTM(0));
#endif
	__raw_writel(status, tz3000_gpio->regbase + GP_IR(0));
	for (i = 0; i < 32; i++) {
		if (status & (1 << i))
			generic_handle_irq(tz3000_gpio->irq_base + i);
	}
#ifdef CONFIG_TZ3000_SGPIO
	if (irq == IRQ_SGPIO)
		__raw_writel(tz3000_gpio->cur_mask,
			     tz3000_gpio->regbase + GP_INTM(0));
#endif
	chained_irq_exit(chip, desc);
}

static struct irq_chip tz3000_gpio_irq_chip = {
	.name		= "GPIO",
	.irq_mask	= tz3000_gpio_irq_mask,
	.irq_unmask	= tz3000_gpio_irq_unmask,
	.irq_set_type	= tz3000_gpio_irq_set_type,
};

static void tz3000_gpio_irq_init(struct tz3000_gpio_chip *tz3000_gpio,
				 unsigned int parent_irq)
{
	int i;

	__raw_writel(0, tz3000_gpio->regbase + GP_INTC(0));
	__raw_writel(0, tz3000_gpio->regbase + GP_INTC(1));
	for (i = 0; i < 5; i++) {
		__raw_writel(~0, tz3000_gpio->regbase + GP_INTM(i));
		__raw_writel(~0, tz3000_gpio->regbase + GP_IR(i));
	}
#ifdef CONFIG_TZ3000_SGPIO
	if (parent_irq == IRQ_SGPIO) {
		u32 val;
		__raw_writel(1, tz3000_gpio->sgpio_regbase + SGPIO_MBOX_CLEAR);
		val = __raw_readl(tz3000_gpio->sgpio_regbase + SGPIO_MBOX_MASK);
		val &= ~1;
		__raw_writel(val, tz3000_gpio->sgpio_regbase + SGPIO_MBOX_MASK);
	}
#endif
	for (i = 0; i < tz3000_gpio->chip.ngpio; i++) {
		int irq = tz3000_gpio->irq_base + i;
		irq_set_chip_data(irq, tz3000_gpio);
		irq_set_chip_and_handler(irq, &tz3000_gpio_irq_chip,
					 handle_simple_irq);
		set_irq_flags(irq, IRQF_VALID);
	}
	irq_set_chained_handler(parent_irq, tz3000_gpio_irq_handler);
	irq_set_handler_data(parent_irq, tz3000_gpio);
}

#ifdef CONFIG_PM_SLEEP
/*
 * use syscore_ops instead of platform_device's pm entries so that
 * other subsys (i.e. PCIe) can use gpio in its suspend/resume
 * entries.
 */
static void tz3000_gpio_suspend_one(struct tz3000_gpio_chip *tz3000_gpio)
{
	int i;

	tz3000_gpio->saved.cr = __raw_readl(tz3000_gpio->regbase + GP_CR);
	tz3000_gpio->saved.odtp = __raw_readl(tz3000_gpio->regbase + GP_ODTP);
	tz3000_gpio->saved.puden = __raw_readl(tz3000_gpio->regbase + GP_PUDEN);
	tz3000_gpio->saved.pudsel =
		__raw_readl(tz3000_gpio->regbase + GP_PUDSEL);
	tz3000_gpio->saved.inpen = __raw_readl(tz3000_gpio->regbase + GP_INPEN);
	tz3000_gpio->saved.smp = __raw_readl(tz3000_gpio->regbase + GP_SMP);
	tz3000_gpio->saved.odr = __raw_readl(tz3000_gpio->regbase + GP_ODR);

	for (i = 0; i < 2; i++)
		tz3000_gpio->saved.intc[i] =
			__raw_readl(tz3000_gpio->regbase + GP_INTC(i));
	tz3000_gpio->saved.intm =
		__raw_readl(tz3000_gpio->regbase + GP_INTM(0));

	/* mask all interrupts */
	__raw_writel(~0, tz3000_gpio->regbase + GP_INTM(0));
}

static void tz3000_gpio_resume_one(struct tz3000_gpio_chip *tz3000_gpio)
{
	int i;

	__raw_writel(tz3000_gpio->saved.cr, tz3000_gpio->regbase + GP_CR);
	__raw_writel(tz3000_gpio->saved.odtp, tz3000_gpio->regbase + GP_ODTP);
	__raw_writel(tz3000_gpio->saved.puden, tz3000_gpio->regbase + GP_PUDEN);
	__raw_writel(tz3000_gpio->saved.pudsel,
		     tz3000_gpio->regbase + GP_PUDSEL);
	__raw_writel(tz3000_gpio->saved.inpen, tz3000_gpio->regbase + GP_INPEN);
	__raw_writel(tz3000_gpio->saved.smp, tz3000_gpio->regbase + GP_SMP);
	__raw_writel(tz3000_gpio->saved.odr, tz3000_gpio->regbase + GP_ODR);

	for (i = 0; i < 2; i++)
		__raw_writel(tz3000_gpio->saved.intc[i],
			     tz3000_gpio->regbase + GP_INTC(i));

	/* clear all pending interrupts */
	for (i = 0; i < 5; i++)
		__raw_writel(~0, tz3000_gpio->regbase + GP_IR(i));

	/* restore masks */
	__raw_writel(tz3000_gpio->saved.intm,
		     tz3000_gpio->regbase + GP_INTM(0));
	for (i = 1; i < 5; i++)
		__raw_writel(~0, tz3000_gpio->regbase + GP_INTM(i));
#ifdef CONFIG_TZ3000_SGPIO
	if (tz3000_gpio->sgpio_regbase) {
		u32 val;
		__raw_writel(1, tz3000_gpio->sgpio_regbase + SGPIO_MBOX_CLEAR);
		val = __raw_readl(tz3000_gpio->sgpio_regbase + SGPIO_MBOX_MASK);
		val &= ~1;
		__raw_writel(val, tz3000_gpio->sgpio_regbase + SGPIO_MBOX_MASK);
	}
#endif
}

static struct tz3000_gpio_chip *tz3000_gpios[8];

static int tz3000_gpio_suspend(void)
{
	int i;

	for (i = ARRAY_SIZE(tz3000_gpios) - 1; i >= 0; i--) {
		if (tz3000_gpios[i])
			tz3000_gpio_suspend_one(tz3000_gpios[i]);
	}
	return 0;
}

static void tz3000_gpio_resume(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(tz3000_gpios); i++) {
		if (tz3000_gpios[i])
			tz3000_gpio_resume_one(tz3000_gpios[i]);
	}
}

static struct syscore_ops tz3000_gpio_syscore_ops = {
	.suspend	= tz3000_gpio_suspend,
	.resume		= tz3000_gpio_resume,
};
#endif

static int __devinit tz3000_gpio_probe(struct platform_device *pdev)
{
	unsigned int id;
	unsigned int gpio_base;
	unsigned int nr_gpio;
	int parent_irq;
	unsigned int irq_base;
	struct tz3000_gpio_platform_data *pdata;
	struct tz3000_gpio_chip *tz3000_gpio;
	struct gpio_chip *chip;
	struct resource *res;

	id = pdev->id;
#ifdef CONFIG_PM_SLEEP
	if (id >= ARRAY_SIZE(tz3000_gpios))
		return -EINVAL;
#endif
	pdata = pdev->dev.platform_data;
	gpio_base = pdata->gpio_base;
	nr_gpio = pdata->nr_gpio;
	irq_base = pdata->irq_base;

	tz3000_gpio = devm_kzalloc(&pdev->dev,
				   sizeof(*tz3000_gpio), GFP_KERNEL);
	if (!tz3000_gpio)
		return -ENOMEM;
	platform_set_drvdata(pdev, tz3000_gpio);
	tz3000_gpio->irq_base = irq_base;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EBUSY;
	tz3000_gpio->regbase = devm_request_and_ioremap(&pdev->dev, res);
	if (!tz3000_gpio->regbase)
		return -EBUSY;
	parent_irq = platform_get_irq(pdev, 0);
	if (parent_irq < 0)
		return -EBUSY;

#ifdef CONFIG_TZ3000_SGPIO
	if (parent_irq == IRQ_SGPIO) {
		tz3000_gpio->sgpio_regbase =
			devm_ioremap(&pdev->dev,
				     TZ3000_MBOX_INTGEN_REG(1), 0x1000);
		if (!tz3000_gpio->sgpio_regbase)
			return -EBUSY;
	}
#endif
	snprintf(tz3000_gpio->label, sizeof(tz3000_gpio->label), "gpio%u", id);
	chip = &tz3000_gpio->chip;
	chip->base = gpio_base;
	chip->label = tz3000_gpio->label;
	chip->direction_input = tz3000_gpio_dir_in;
	chip->direction_output = tz3000_gpio_dir_out;
	chip->get = tz3000_gpio_get;
	chip->set = tz3000_gpio_set;
	chip->to_irq = tz3000_gpio_to_irq;
	chip->ngpio = nr_gpio;
	if (gpiochip_add(chip))
		return -EBUSY;
	tz3000_gpio_irq_init(tz3000_gpio, parent_irq);
#ifdef CONFIG_PM_SLEEP
	tz3000_gpios[id] = tz3000_gpio;
#endif
	return 0;
}

static struct platform_driver tz3000_gpio_driver = {
	.driver		= {
		.name	= "tz3000-gpio",
		.owner	= THIS_MODULE,
	},
	.probe		= tz3000_gpio_probe,
};

static int __init tz3000_gpio_init(void)
{
	int ret;
	ret = platform_driver_register(&tz3000_gpio_driver);
#ifdef CONFIG_PM_SLEEP
	if (ret == 0)
		register_syscore_ops(&tz3000_gpio_syscore_ops);
#endif
	return ret;
}
postcore_initcall(tz3000_gpio_init);
