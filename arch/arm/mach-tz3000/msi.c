/*
 * routines for the Toshiba tz3000 pcie MSI
 *
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

#include <linux/types.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/msi.h>
#include <linux/syscore_ops.h>
#include <asm/mach/irq.h>
#include <mach/platform.h>

static DECLARE_BITMAP(msi_irq_in_use, NR_MSI_IRQS);
static void __iomem *msi_mbox_reg_base;

/* use only INT_REG00,INT_REG04,INT_REG08,INT_REG12 */
#define MBOX_SET_BASE(n)	(0x000 + 0x4 * (n))
#define MBOX_CLEAR_BASE(n)	(0x400 + 0x4 * (n))
#define MBOX_MASK_BASE(n)	(0x800 + 0x4 * (n))

static void tz3000_msi_handler(unsigned int irq, struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	long index = (long)irq_desc_get_handler_data(desc);
	u32 status;
	int i;

	chained_irq_enter(chip, desc);
	status = __raw_readl(msi_mbox_reg_base + MBOX_SET_BASE(index * 4));
	/* clear */
	__raw_writel(status, msi_mbox_reg_base + MBOX_CLEAR_BASE(index * 4));

	for (i = 0; i < 16; i++) {
		if (status & (1 << i))
			generic_handle_irq(IRQ_MSI_START + i * 4 + index);
	}
	chained_irq_exit(chip, desc);
}

static struct irq_chip tz3000_msi_chip = {
	.name = "PCI-MSI",
	.irq_enable = unmask_msi_irq,
	.irq_disable = mask_msi_irq,
	.irq_mask = mask_msi_irq,
	.irq_unmask = unmask_msi_irq,
};

int arch_setup_msi_irq(struct pci_dev *pdev, struct msi_desc *desc)
{
	int irq;
	int pos;
	struct msi_msg msg;

	if (!msi_mbox_reg_base)
		return -ENOSYS;

	do {
		pos = find_first_zero_bit(msi_irq_in_use, NR_MSI_IRQS);
		if (pos >= NR_MSI_IRQS)
			return -ENOSPC;
	} while (test_and_set_bit(pos, msi_irq_in_use));

	irq = IRQ_MSI_START + pos;

	irq_set_msi_desc(irq, desc);

	msg.address_hi = 0x0;
	msg.address_lo = TZ3000_MBOX_PCIE_BASE + MBOX_SET_BASE((pos % 4) * 4);
	msg.data = 1 << (pos / 4);

	write_msi_msg(irq, &msg);
	irq_set_chip_and_handler(irq, &tz3000_msi_chip, handle_simple_irq);
	set_irq_flags(irq, IRQF_VALID);
	dev_dbg(&pdev->dev, "MSI irq %d addr 0x%08x data 0x%x\n",
		irq, msg.address_lo, msg.data);
	return 0;
}

void arch_teardown_msi_irq(unsigned int irq)
{
	int pos = irq - IRQ_MSI_START;

	set_irq_flags(irq, 0);
	clear_bit(pos, msi_irq_in_use);
}

#ifdef CONFIG_PM_SLEEP
static int tz3000_msi_suspend(void)
{
	pr_debug("%s\n", __func__);
	return 0;
}

static void tz3000_msi_resume(void)
{
	int i;

	pr_debug("%s\n", __func__);
	for (i = 0; i < 4; i++) {
		/* clear and unmask */
		__raw_writel(0xffff,
			     msi_mbox_reg_base + MBOX_CLEAR_BASE(i * 4));
		__raw_writel(0xffff0000,
			     msi_mbox_reg_base + MBOX_MASK_BASE(i * 4));
	}
}

static struct syscore_ops tz3000_msi_pm_syscore_ops = {
	.suspend = tz3000_msi_suspend,
	.resume = tz3000_msi_resume,
};
#endif

static int __init tz3000_msi_init(void)
{
	int i;

	if (no_pci_devices() || !pci_msi_enabled())
		return -1;

	msi_mbox_reg_base = ioremap(TZ3000_MBOX_PCIE_BASE, 0x1000);
	if (!msi_mbox_reg_base) {
		pr_err("PCI: unable to map mbox for MSI\n");
		return -1;
	}

	for (i = 0; i < 4; i++) {
		irq_set_chained_handler(IRQ_PCIEMSI(i), tz3000_msi_handler);
		irq_set_handler_data(IRQ_PCIEMSI(i), (void *)(long)i);
		/* clear and unmask */
		__raw_writel(0xffff,
			     msi_mbox_reg_base + MBOX_CLEAR_BASE(i * 4));
		__raw_writel(0xffff0000,
			     msi_mbox_reg_base + MBOX_MASK_BASE(i * 4));
	}
#ifdef CONFIG_PM_SLEEP
	register_syscore_ops(&tz3000_msi_pm_syscore_ops);
#endif
	return 0;
}

subsys_initcall(tz3000_msi_init);
