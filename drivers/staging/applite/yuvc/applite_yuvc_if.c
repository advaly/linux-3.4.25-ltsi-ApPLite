/*
 * linux/drivers/staging/applite/applite_yuvc_if.c
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

/*===================================
Include Files
===================================*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>
#include <linux/completion.h>

#include <linux/applite/applite_yuvc.h>
#include "applite_yuvc_internal.h"
#include "applite_yuvc_regs.h"
#include "applite_yuvc_dbg.h"

/* MODULE INFORMATION */
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Glenfiddich YUVC Driver");
MODULE_VERSION(YUVC_DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("yuvc");
module_param(ul_logflags, int, S_IRUGO | S_IWUSR | S_IWGRP);
MODULE_PARM_DESC(ul_logflags, "log level");

/*===================================
Static Variables and Functions prototypes
===================================*/

static struct class *pyuvc_class;
static dev_t yuvc_number;
struct yuvc_dev s_yuvc_dev;

static int __init yuvc_init(void);
static void __exit yuvc_exit(void);
static int __devinit yuvc_probe(struct platform_device *pdev);
static int __devexit yuvc_remove(struct platform_device *pdev);
static int yuvc_suspend(struct device *dev);
static int yuvc_resume(struct device *dev);
static int yuvc_runtime_suspend(struct device *dev);
static int yuvc_runtime_resume(struct device *dev);
static int yuvc_open(struct inode *inode, struct file *file);
static int yuvc_release(struct inode *inode, struct file *file);
static long yuvc_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static irqreturn_t yuvc_irq(int irq, void *arg);

static const struct file_operations yuvc_fops = {
	.owner		= THIS_MODULE,
	.open		= yuvc_open,
	.release	= yuvc_release,
	.unlocked_ioctl	= yuvc_ioctl,
};

static const struct dev_pm_ops applite_yuvc_pm_ops = {
	.suspend = yuvc_suspend,
	.resume = yuvc_resume,
	.runtime_suspend = yuvc_runtime_suspend,
	.runtime_resume = yuvc_runtime_resume,
};

static struct platform_driver applite_yuvc_driver = {
	.probe = yuvc_probe,
	.remove = yuvc_remove,
	.driver = {
		.name = "applite-yuvc",
		.owner = THIS_MODULE,
		.pm = &applite_yuvc_pm_ops,
	},
};

/*===================================
Global Variables and Functions prototypes
===================================*/


/*===================================
Macros
===================================*/
#ifndef YUVC_USE_GDMAC
static int  fifo_addr[8] = {
	YUVC_FIFO_Y0_ADDR,
	YUVC_FIFO_Y1_ADDR,
	YUVC_FIFO_C0_ADDR,
	YUVC_FIFO_C1_ADDR,
	YUVC_FIFO_C2_ADDR,
	YUVC_FIFO_V0_ADDR,
	YUVC_FIFO_V1_ADDR,
	YUVC_FIFO_V2_ADDR
};
#endif /* not YUVC_USE_GDMAC */

/*===================================
Function Definitions
===================================*/

/*===================================
Module source
===================================*/


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int yuvc_open(struct inode *inode, struct file *file)
{
	int ierr = 0;
	int i_open;
	struct yuvc_dev *pdev =
			container_of(inode->i_cdev, struct yuvc_dev, cdev);
	YUVC_FUNC_START("pdev(%p)\n", pdev);

	if (pdev == NULL) {
		YUVC_ERR("invalid parameter\n");
		return -EINVAL;
	}
	DUMP_YUVC_DEV(pdev);

	file->private_data = pdev;

	YUVC_INFO("refcount:%d\n",
			atomic_read(&(pdev->device->kobj.kref.refcount)));

	/* update internal information */
	i_open = atomic_add_return(1, &(pdev->ul_open_count));

	/* check first open, and register interrupt handler */
	if (i_open == 1) {
		YUVC_TEST("first open. do request_irq()\n");
		ierr = request_irq(YUVC_IRQ_NUM, yuvc_irq,
					YUVC_IRQ_FLAG, DEVICE_NAME, pdev);
		if (ierr != 0) {
			/* error */
			YUVC_ERR("request_irq(%d) failed %d\n",
					YUVC_IRQ_NUM, ierr);
			goto YUVC_FINISH;
		}
		/* unmask interrupt */
		yuvc_mask_irq(pdev, false);
#ifdef YUVC_USE_GDMAC
		pdev->dmac_status = 0; /* idle */
#endif
	}

YUVC_FINISH:

	/* exclusive internal parameter access */
	DUMP_YUVC_DEV(pdev);
	YUVC_FUNC_END("ret(%d)\n", ierr);

	return ierr;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int yuvc_release(struct inode *inode, struct file *file)
{
	int ierr = 0;
	int i_open;
	struct yuvc_dev *pdev = file->private_data;

	YUVC_FUNC_START("\n");

	if (pdev == NULL) {
		YUVC_ERR("invalid parameter\n");
		return -EINVAL;
	}
	DUMP_YUVC_DEV(pdev);

	/* update internal information */
	i_open = atomic_sub_return(1, &(pdev->ul_open_count));

	if (i_open == 0) {
		YUVC_TEST("last close. do free_irq()\n");
		/* force stop, if running */
		if (pdev->b_run == YUVC_STAT_RUN) {
			YUVC_INFO("yuvc running. do cancel\n");
			ierr = yuvc_cancel();
		}
		/* mask interrupt */
		yuvc_mask_irq(pdev, true);
		/* unregister irq handler */
		free_irq(YUVC_IRQ_NUM, pdev);
#ifdef YUVC_USE_GDMAC
		if (pdev->dmac_status) {
			yuvc_dma_clear(pdev->dmac_type);
			pdev->dmac_status = 0;
		}
#endif
	}

	DUMP_YUVC_DEV(pdev);

	YUVC_FUNC_END("ret(%d)\n", ierr);

	return ierr;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static long yuvc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ierr = 0;
	struct yuvc_param prm;

	YUVC_FUNC_START("arg:%08x\n", cmd);

	/* parameter check */
	switch (cmd) {
	case IOC_YUVC_START:
		YUVC_PM_START("IOC_YUVC_START\n");
		if (arg == 0) {
			YUVC_ERR("invalid argument\n");
			ierr = -EINVAL;
			break;
		}
		if (copy_from_user(&prm, (void __user *)arg,
					sizeof(struct yuvc_param))) {
			YUVC_ERR("copy_from_user() failed\n");
			ierr = -EFAULT;
			break;
		}
		ierr = yuvc_start(&prm);
		YUVC_PM_END("IOC_YUVC_START\n");
		break;
	case IOC_YUVC_CANCEL:
		YUVC_PM_START("IOC_YUVC_CANCEL\n");
		ierr = yuvc_cancel();
		YUVC_PM_END("IOC_YUVC_CANCEL\n");
		break;
	default:
		YUVC_ERR("invalid cmd[%08x]\n", cmd);
		ierr = -ENOIOCTLCMD;
	}
	YUVC_FUNC_END("ret(%ld)\n", ierr);
	return ierr;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static irqreturn_t yuvc_irq(int irq, void *arg)
{
	irqreturn_t ierr = IRQ_NONE;
	__u32	irq_stat;
	__u32	regs;
	struct yuvc_dev *pdev = (struct yuvc_dev *)arg;

	YUVC_FUNC_START("\n");

	if (pdev == NULL) {
		YUVC_ERR("invalid argument\n");
		return -EINVAL;
	}
	DUMP_YUVC_DEV(pdev);

	/* read & clear interrupt status */
	yuvc_clear_irq(pdev, &irq_stat);
	YUVC_TEST("irq_stat=0x%08x\n", irq_stat);

	if (irq_stat & YUVC_INT_INT_G00) {
		/* wake up */
		YUVC_INFO("interrupt:INT_G00\n");
		ierr = IRQ_HANDLED;
/*		YUVC_TEST("status change to YUVC_STAT_IDLE. and wakeup\n"); */

#if 0
		if (pdev->b_run == YUVC_STAT_RUN)
			pdev->b_run = YUVC_STAT_IDLE;
		complete(&(pdev->comp));
#endif
	}
	if (irq_stat & YUVC_INT_MB_ERR) {
		/* wake up */
		YUVC_INFO("interrupt:MB_ERR\n")
		ierr = IRQ_HANDLED;
		pdev->convert_status = YUVC_NG;
/*		YUVC_TEST("status change to YUVC_STAT_IDLE. and wakeup\n"); */

#if 0
		if (pdev->b_run == YUVC_STAT_RUN)
			pdev->b_run = YUVC_STAT_IDLE;
		complete(&(pdev->comp));
#endif
	}
	if (irq_stat & YUVC_INT_ABORT_G00) {
		/* wake up */
		YUVC_INFO("interrupt:INT_ABORT_G00\n")
		ierr = IRQ_HANDLED;
		pdev->convert_status = YUVC_NG;
/*		YUVC_TEST("status change to YUVC_STAT_IDLE. and wakeup\n"); */

		YUVC_READ(pdev, W_STOP, regs);
		YUVC_WRITE(pdev, W_STOP, regs);

#if 0
		if (pdev->b_run == YUVC_STAT_ABORT)
			pdev->b_run = YUVC_STAT_IDLE;
		complete(&(pdev->comp));
#endif
	}

	if (ierr == IRQ_HANDLED) {
		YUVC_TEST("status change to YUVC_STAT_IDLE. and wakeup\n");
		pdev->b_run = YUVC_STAT_IDLE;
		complete(&(pdev->comp));
	}

	DUMP_YUVC_DEV(pdev);
	YUVC_FUNC_END("ret(%d)\n", ierr);
	return ierr;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long yuvc_start(struct yuvc_param *param)
{
	YUVC_FUNC_START("param:%p\n", param);

	/* parameter check */
	if (param == NULL) {
		YUVC_ERR("invalid argument\n");
		return -EINVAL;
	}
	if (yuvc_chk_params(&s_yuvc_dev, param) != YUVC_OK) {
		YUVC_ERR("yuvc_chk_params() failed\n");
		return -EINVAL;
	}
	return yuvc_start_sub(&s_yuvc_dev, param);
}
EXPORT_SYMBOL(yuvc_start);

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long yuvc_cancel(void)
{
	YUVC_FUNC_START("\n");

	return yuvc_cancel_sub(&s_yuvc_dev);
}
EXPORT_SYMBOL(yuvc_cancel);

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int __devinit yuvc_probe(struct platform_device *pdev)
{
	int ierr = 0;
	struct resource *yuvc_res;
	struct resource *pmu_res;

	YUVC_FUNC_START("\n");

	/* initialize internal parameters */
	memset((void *)&s_yuvc_dev, 0, sizeof(struct yuvc_dev));

	DUMP_YUVC_DEV(&(s_yuvc_dev));		/* for TEST */

	spin_lock_init(&(s_yuvc_dev.lock_dev));
	spin_lock_init(&(s_yuvc_dev.lock_reg));
	mutex_init(&(s_yuvc_dev.mutex_run));
	init_completion(&(s_yuvc_dev.comp));
	atomic_set(&(s_yuvc_dev.ul_open_count), 0);
	s_yuvc_dev.b_run = YUVC_STAT_IDLE;
	s_yuvc_dev.pdev = pdev;
	s_yuvc_dev.yuvc_usecount = 0;

	/* create proc fs */
	yuvc_procfs_create();

	/* allocate character device number */
	ierr = alloc_chrdev_region(&yuvc_number, 0, 1, DEVICE_NAME);
	if (ierr) {
		YUVC_ERR("alloc_chrdev_region() failed %d\n", ierr);
		return ierr;
	}

	/* create yuvc class */
	pyuvc_class = class_create(THIS_MODULE, DEVICE_NAME);
	if (IS_ERR(pyuvc_class)) {
		ierr = PTR_ERR(pyuvc_class);
		YUVC_ERR("class_create() failed %d\n", ierr);
		goto fail_class_create;
	}

	/* initialize cdev structure */
	cdev_init(&(s_yuvc_dev.cdev), &yuvc_fops);
	s_yuvc_dev.cdev.owner = THIS_MODULE;

	/* register cdev structure */
	ierr = cdev_add(&(s_yuvc_dev.cdev), yuvc_number, 1);
	if (ierr) {
		YUVC_ERR("cdev_add() failed %d\n", ierr);
		goto fail_cdev_add;
	}

	/* create device structure */
	s_yuvc_dev.device =
		device_create(pyuvc_class, NULL, yuvc_number, NULL,
			DEVICE_NAME);
	if (IS_ERR(s_yuvc_dev.device)) {
		ierr = PTR_ERR(s_yuvc_dev.device);
		cdev_del(&(s_yuvc_dev.cdev));
		YUVC_ERR("device_create() failed %d\n", ierr);
		goto fail_device_create;
	}

	/* remapping registers */
	yuvc_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "yuvc");
	if (yuvc_res == NULL) {
		ierr = -EBUSY;
		goto fail_ioremap;
	}
	pmu_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pmu");
	if (pmu_res == NULL) {
		ierr = -EBUSY;
		goto fail_ioremap;
	}
	s_yuvc_dev.yuvcbase =
		(__u8 __iomem *)ioremap_nocache(yuvc_res->start,
						resource_size(yuvc_res));
	if (s_yuvc_dev.yuvcbase == NULL) {
		YUVC_ERR("ioremap_nocache() failed YUVC Registers[%08x - %d]\n",
				yuvc_res->start, resource_size(yuvc_res));
		ierr = -ENOMEM;
		goto fail_ioremap;
	}
	s_yuvc_dev.pmubase =
		(__u8 __iomem *)ioremap_nocache(pmu_res->start,
						resource_size(pmu_res));
	if (s_yuvc_dev.pmubase == NULL) {
		YUVC_ERR("ioremap_nocache() failed PMU Registers[%08x - %d]\n",
				pmu_res->start, resource_size(pmu_res));
		ierr = -ENOMEM;
		goto fail_ioremap2;
	}

	s_yuvc_dev.clk = clk_get(&(pdev->dev), NULL);
	if (IS_ERR(s_yuvc_dev.clk)) {
		YUVC_ERR("clk_get(%s) failed\n", dev_name(&(pdev->dev)));
		ierr = -EFAULT;
		goto fail_clk_get;
	}

	/* initialize registers */
	yuvc_init_hw(&s_yuvc_dev);

	DUMP_YUVC_DEV(&(s_yuvc_dev));		/* for TEST */

	pr_info("yuvc Driver [%s] Initialized.[%d.%d]\n",
		YUVC_DRIVER_VERSION,
		MAJOR(yuvc_number), MINOR(yuvc_number));

#ifndef YUVC_USE_GDMAC
	{
		int i;
		/* mapping input FIFO */
		for (i = 0; i < 8; i++)
			s_yuvc_dev.pfifo[i] = (__u32 __iomem *)ioremap_nocache(fifo_addr[i], YUVC_FIFO_SIZE);
	}
#endif	/* not YUVC_USE_GDMAC */

	pm_runtime_enable(&(pdev->dev));

	YUVC_FUNC_END("\n");

	return 0;

fail_clk_get:

fail_ioremap2:
	iounmap(s_yuvc_dev.yuvcbase);
fail_ioremap:
	device_destroy(pyuvc_class, yuvc_number);
fail_device_create:
	cdev_del(&(s_yuvc_dev.cdev));
fail_cdev_add:
	class_destroy(pyuvc_class);
fail_class_create:
	unregister_chrdev_region(MAJOR(yuvc_number), 1);

	yuvc_procfs_remove();

	YUVC_ERR("yuvc Driver [%s] load failed.\n", YUVC_DRIVER_VERSION);

	YUVC_FUNC_END("\n");

	return ierr;
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int __devexit yuvc_remove(struct platform_device *pdev)
{
	YUVC_FUNC_START("\n");

#ifndef YUVC_USE_GDMAC
	{
		int i;
		/* unmap input FIFO */
		for (i = 0; i < 8; i++)
			iounmap(s_yuvc_dev.pfifo[i]);
	}
#endif	/* not YUVC_USE_GDMAC */

	/* uninitialize registers */
	yuvc_exit_hw(&s_yuvc_dev);

	pm_runtime_disable(&(pdev->dev));

	clk_put(s_yuvc_dev.clk);

	/* memory io unmap */
	iounmap(s_yuvc_dev.pmubase);
	YUVC_TEST("iounmap() pmubase:%p\n", s_yuvc_dev.pmubase);
	iounmap(s_yuvc_dev.yuvcbase);
	YUVC_TEST("iounmap() yuvcbase:%p\n", s_yuvc_dev.yuvcbase);
	device_destroy(pyuvc_class, yuvc_number);
	YUVC_TEST("device_destroy() success\n");
	cdev_del(&(s_yuvc_dev.cdev));
	YUVC_TEST("cdev_del() success\n");
	unregister_chrdev_region(MAJOR(yuvc_number), 1);
	YUVC_TEST("unregister_chrdev_region() success\n");
	class_destroy(pyuvc_class);
	YUVC_TEST("class_destroy() success\n");

	yuvc_procfs_remove();
	YUVC_INFO("yuvc Driver Uninitialized.\n");

	YUVC_FUNC_END("\n");
	return 0;
}

static int yuvc_suspend(struct device *dev)
{
	YUVC_FUNC_START("\n");
	YUVC_INFO("usecount:%d\n", s_yuvc_dev.yuvc_usecount);
	if (s_yuvc_dev.yuvc_usecount > 0)
		return -EBUSY;
	return 0;
}

static int yuvc_resume(struct device *dev)
{
	YUVC_FUNC_START("\n");
	yuvc_init_hw(&s_yuvc_dev);
	return 0;
}

static int yuvc_runtime_suspend(struct device *dev)
{
	YUVC_FUNC_START("\n");
	return yuvc_runtime_suspend_sub(&s_yuvc_dev);
}

static int yuvc_runtime_resume(struct device *dev)
{
	YUVC_FUNC_START("\n");
	return yuvc_runtime_resume_sub(&s_yuvc_dev);
}

static int __init yuvc_init(void)
{
	YUVC_FUNC_START("\n");
	return platform_driver_register(&applite_yuvc_driver);
}

static void __exit yuvc_exit(void)
{
	YUVC_FUNC_START("\n");
	platform_driver_unregister(&applite_yuvc_driver);
	YUVC_FUNC_END("\n");
}

module_init(yuvc_init);
module_exit(yuvc_exit);

