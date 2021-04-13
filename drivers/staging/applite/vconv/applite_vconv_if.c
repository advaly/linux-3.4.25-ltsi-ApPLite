/*
 * linux/drivers/staging/applite/applite_vconv_if.c
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

#include <linux/applite/applite_vconv.h>
#include "applite_vconv_internal.h"
#include "applite_vconv_regs.h"
#include "applite_vconv_dbg.h"

/* MODULE INFORMATION */
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Speyside Video Converter Driver");
MODULE_VERSION(VCONV_DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("vconv");
module_param(ul_logflags, int, S_IRUGO | S_IWUSR | S_IWGRP);
MODULE_PARM_DESC(ul_logflags, "log level");

/*===================================
Static Variables and Functions prototypes
===================================*/

static struct class *pvconv_class;
static dev_t vconv_number;
struct vconv_dev s_vconv_dev;

static int __init vconv_init(void);
static void __exit vconv_exit(void);
static int __devinit vconv_probe(struct platform_device *pdev);
static int __devexit vconv_remove(struct platform_device *pdev);
static int vconv_open(struct inode *inode, struct file *file);
static int vconv_release(struct inode *inode, struct file *file);
static long vconv_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static irqreturn_t vconv_irq(int irq, void *arg);
static int vconv_suspend(struct device *dev);
static int vconv_resume(struct device *dev);
static int vconv_runtime_suspend(struct device *dev);
static int vconv_runtime_resume(struct device *dev);


static const struct file_operations vconv_fops = {
	.owner		= THIS_MODULE,
	.open		= vconv_open,
	.release	= vconv_release,
	.unlocked_ioctl	= vconv_ioctl,
};

static const struct dev_pm_ops applite_vconv_pm_ops = {
	.suspend = vconv_suspend,
	.resume = vconv_resume,
	.runtime_suspend = vconv_runtime_suspend,
	.runtime_resume = vconv_runtime_resume,
};

static struct platform_driver applite_vconv_driver = {
	.probe = vconv_probe,
	.remove = vconv_remove,
	.driver = {
		.name = "vconv",
		.owner = THIS_MODULE,
		.pm = &applite_vconv_pm_ops,
	},
};

/*===================================
Global Variables and Functions prototypes
===================================*/


/*===================================
Macros
===================================*/

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
static int vconv_open(struct inode *inode, struct file *file)
{
	int ierr = 0;
	int i_open;
	struct vconv_dev *pdev =
			container_of(inode->i_cdev, struct vconv_dev, cdev);
	VCONV_FUNC_START("pdev(%p)\n", pdev);

	if (pdev == NULL) {
		VCONV_ERR("invalid parameter\n");
		return -EINVAL;
	}
	DUMP_VCONV_DEV(pdev);

	file->private_data = pdev;

	/* update internal information */
	i_open = atomic_add_return(1, &(pdev->ul_open_count));

	/* check first open, and register interrupt handler */
	if (i_open == 1) {
		VCONV_TEST("first open. do request_irq()\n");
		ierr = request_irq(VCONV_IRQ_NUM, vconv_irq,
					VCONV_IRQ_FLAG, DEVICE_NAME, pdev);
		if (ierr != 0) {
			/* error */
			VCONV_ERR("request_irq(%d) failed %d\n",
					VCONV_IRQ_NUM, ierr);
			goto VCONV_FINISH;
		}
		/* unmask interrupt */
		ierr = request_irq(VCONV_ERR_IRQ_NUM, vconv_irq,
					VCONV_IRQ_FLAG, DEVICE_NAME, pdev);
		if (ierr != 0) {
			/* error */
			VCONV_ERR("request_irq(%d) failed %d\n",
					VCONV_ERR_IRQ_NUM, ierr);
		}
		/* unmask interrupt */
		vconv_mask_irq(pdev, false);
	}

VCONV_FINISH:

	/* exclusive internal parameter access */
	DUMP_VCONV_DEV(pdev);
	VCONV_FUNC_END("ret(%d)\n", ierr);

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
static int vconv_release(struct inode *inode, struct file *file)
{
	int ierr = 0;
	int i_open;
	struct vconv_dev *pdev = file->private_data;

	VCONV_FUNC_START("\n");

	if (pdev == NULL) {
		VCONV_ERR("invalid parameter\n");
		return -EINVAL;
	}
	DUMP_VCONV_DEV(pdev);

	/* update internal information */
	i_open = atomic_sub_return(1, &(pdev->ul_open_count));

	if (i_open == 0) {
		VCONV_TEST("last close. do free_irq()\n");
		/* force stop, if running */
		if (pdev->b_run == VCONV_STAT_RUN) {
			VCONV_INFO("vconv running. do cancel\n");
			ierr = vconv_cancel();
		}
		/* mask interrupt */
		vconv_mask_irq(pdev, true);
		/* unregister irq handler */
		free_irq(VCONV_IRQ_NUM, pdev);
		free_irq(VCONV_ERR_IRQ_NUM, pdev);
	}

	DUMP_VCONV_DEV(pdev);

	VCONV_FUNC_END("ret(%d)\n", ierr);

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
static long vconv_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ierr = 0;
	struct vconv_param prm;
	struct vconv_verify verify;
	struct vconv_param_ex prm_ex;

	VCONV_FUNC_START("arg:%08x\n", cmd);

	/* parameter check */
	switch (cmd) {
	case IOC_VCONV_START:
		VCONV_PM_START("IOC_VCONV_START\n");
		if (arg == 0) {
			VCONV_ERR("invalid argument\n");
			ierr = -EINVAL;
			break;
		}
		if (copy_from_user(&prm, (void __user *)arg,
					sizeof(struct vconv_param))) {
			VCONV_ERR("copy_from_user() failed\n");
			ierr = -EFAULT;
			break;
		}
		ierr = vconv_start(&prm);
		VCONV_PM_END("IOC_VCONV_START\n");
		break;
	case IOC_VCONV_CANCEL:
		VCONV_PM_START("IOC_VCONV_CANCEL\n");
		ierr = vconv_cancel();
		VCONV_PM_END("IOC_VCONV_CANCEL\n");
		break;
	case IOC_VCONV_VERIFY:
		VCONV_INFO("IOC_VCONV_VERIFY\n");
		if (arg == 0) {
			VCONV_ERR("invalid argument\n");
			ierr = -EINVAL;
			break;
		}
		if (copy_from_user(&verify, (void __user *)arg,
					sizeof(struct vconv_verify))) {
			VCONV_ERR("copy_from_user() failed\n");
			ierr = -EFAULT;
			break;
		}
		ierr = vconv_verify(&verify);
		break;
	case IOC_VCONV_START_EX:
		VCONV_PM_START("IOC_VCONV_START_EX\n");
		if (arg == 0) {
			VCONV_ERR("invalid argument\n");
			ierr = -EINVAL;
			break;
		}
		if (copy_from_user(&prm_ex, (void __user *)arg,
					sizeof(struct vconv_param_ex))) {
			VCONV_ERR("copy_from_user() failed\n");
			ierr = -EFAULT;
			break;
		}
		ierr = vconv_start_ex(&prm_ex);
		VCONV_PM_END("IOC_VCONV_START_EX\n");
		break;
	default:
		VCONV_ERR("invalid cmd[%08x]\n", cmd);
		ierr = -ENOIOCTLCMD;
	}
	VCONV_FUNC_END("ret(%ld)\n", ierr);
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
static irqreturn_t vconv_irq(int irq, void *arg)
{
	irqreturn_t ierr = IRQ_NONE;
	__u32 irq_stat;
	struct vconv_dev *pdev = (struct vconv_dev *)arg;

/*	VCONV_FUNC_START("\n"); */

	if (pdev == NULL) {
		VCONV_ERR("invalid argument\n");
		return -EINVAL;
	}
	DUMP_VCONV_DEV(pdev);

	/* read & clear interrupt status */
	vconv_clear_irq(pdev, &irq_stat);

	if (irq_stat & VCONV_IRQ_START_ERROR) {
		/* wake up */
		VCONV_INFO("interrupt:START_ERROR\n");
		ierr = IRQ_HANDLED;
		pdev->ul_num_start_err_irq++;
		VCONV_TEST("status change to VCONV_STAT_IDLE. and wakeup\n");
		if (pdev->b_run == VCONV_STAT_RUN)
			pdev->b_run = VCONV_STAT_IDLE;

		complete(&(pdev->comp));
	}
	if (irq_stat & VCONV_IRQ_REG_ERROR) {
		/* wake up */
		VCONV_INFO("interrupt:REG_ERROR\n")
		ierr = IRQ_HANDLED;
		pdev->ul_num_reg_err_irq++;
		VCONV_TEST("status change to VCONV_STAT_IDLE. and wakeup\n");
		if (pdev->b_run == VCONV_STAT_RUN)
			pdev->b_run = VCONV_STAT_IDLE;

		complete(&(pdev->comp));
	}
	if (irq_stat & VCONV_IRQ_FRAME_END) {
		/* wake up */
		VCONV_INFO("interrupt:FRAME_END\n")
		ierr = IRQ_HANDLED;
		pdev->ul_num_frame_end_irq++;
		VCONV_TEST("status change to VCONV_STAT_IDLE. and wakeup\n");
		if (pdev->b_run == VCONV_STAT_RUN)
			pdev->b_run = VCONV_STAT_IDLE;

		complete(&(pdev->comp));
	}
	if (irq_stat & VCONV_IRQ_DISP_ERROR) {
		/* not supported */
		VCONV_INFO("interrupt:DISP_ERROR\n")
		ierr = IRQ_HANDLED;
		pdev->ul_num_disp_err_irq++;
	}
	if (irq_stat & VCONV_IRQ_MERGE_ERROR) {
		/* not supported */
		VCONV_INFO("interrupt:MERGE_ERROR\n")
		ierr = IRQ_HANDLED;
		pdev->ul_num_merge_err_irq++;
	}

	DUMP_VCONV_DEV(pdev);
/*	VCONV_FUNC_END("ret(%d)\n", ierr); */
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
long vconv_start(struct vconv_param *param)
{
	struct vconv_param_ex	prm_ex;
	int			i;

	VCONV_FUNC_START("param:%p\n", param);

	/* parameter check */
	if (param == NULL) {
		VCONV_ERR("invalid argument\n");
		return -EINVAL;
	}
	/* copy parameters */
	for (i = 0; i < VCONV_PLANE_MAX; i++) {
		prm_ex.in_buffer[i].mode    = VCONV_USE_FD;
		prm_ex.in_buffer[i].fd      = param->in_buffer[i].fd;
		prm_ex.in_buffer[i].offset  = param->in_buffer[i].offset;
		prm_ex.in_buffer[i].pitch   = param->in_buffer[i].pitch;
		prm_ex.out_buffer[i].mode   = VCONV_USE_FD;
		prm_ex.out_buffer[i].fd     = param->out_buffer[i].fd;
		prm_ex.out_buffer[i].offset = param->out_buffer[i].offset;
		prm_ex.out_buffer[i].pitch  = param->out_buffer[i].pitch;
	}
	prm_ex.in_img     = param->in_img;
	prm_ex.out_img    = param->out_img;
	prm_ex.force_mode = param->force_mode;
	prm_ex.crop       = param->crop;
	prm_ex.conv       = param->conv;
	prm_ex.alpha      = param->alpha;

	if (vconv_chk_params(&s_vconv_dev, &prm_ex) != VCONV_OK) {
		VCONV_ERR("vconv_chk_params() failed\n");
		return -EINVAL;
	}
	return vconv_start_sub(&s_vconv_dev, &prm_ex);
}
EXPORT_SYMBOL(vconv_start);

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long vconv_start_ex(struct vconv_param_ex *param)
{
	VCONV_FUNC_START("param:%p\n", param);

	/* parameter check */
	if (param == NULL) {
		VCONV_ERR("invalid argument\n");
		return -EINVAL;
	}
	if (vconv_chk_params(&s_vconv_dev, param) != VCONV_OK) {
		VCONV_ERR("vconv_chk_params() failed\n");
		return -EINVAL;
	}
	return vconv_start_sub(&s_vconv_dev, param);
}
EXPORT_SYMBOL(vconv_start_ex);

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long vconv_cancel(void)
{
	VCONV_FUNC_START("\n");

	return vconv_cancel_sub(&s_vconv_dev);
}
EXPORT_SYMBOL(vconv_cancel);


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
long vconv_verify(struct vconv_verify *verify)
{
	VCONV_FUNC_START("\n");

	return vconv_verify_sub(&s_vconv_dev, verify);
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
static int __devinit vconv_probe(struct platform_device *pdev)
{
	int ierr = 0;
	struct resource *vconv_res;
	struct resource *pmu_res;

	VCONV_FUNC_START("\n");

	/* initialize internal parameters */
	memset((void *)&s_vconv_dev, 0, sizeof(struct vconv_dev));

	DUMP_VCONV_DEV(&(s_vconv_dev));		/* for TEST */

	spin_lock_init(&(s_vconv_dev.lock_dev));
	spin_lock_init(&(s_vconv_dev.lock_reg));
	mutex_init(&(s_vconv_dev.mutex_run));
	init_completion(&(s_vconv_dev.comp));
	atomic_set(&(s_vconv_dev.ul_open_count), 0);
	s_vconv_dev.b_run = VCONV_STAT_IDLE;
	s_vconv_dev.pdev = pdev;
	s_vconv_dev.vconv_usecount = 0;

	/* create proc fs */
	vconv_procfs_create();

	/* allocate character device number */
	ierr = alloc_chrdev_region(&vconv_number, 0, 1, DEVICE_NAME);
	if (ierr) {
		VCONV_ERR("alloc_chrdev_region() failed %d\n", ierr);
		return ierr;
	}

	/* create vconv class */
	pvconv_class = class_create(THIS_MODULE, DEVICE_NAME);
	if (IS_ERR(pvconv_class)) {
		ierr = PTR_ERR(pvconv_class);
		VCONV_ERR("class_create() failed %d\n", ierr);
		goto fail_class_create;
	}

	/* initialize cdev structure */
	cdev_init(&(s_vconv_dev.cdev), &vconv_fops);
	s_vconv_dev.cdev.owner = THIS_MODULE;

	/* register cdev structure */
	ierr = cdev_add(&(s_vconv_dev.cdev), vconv_number, 1);
	if (ierr) {
		VCONV_ERR("cdev_add() failed %d\n", ierr);
		goto fail_cdev_add;
	}

	/* create device structure */
	s_vconv_dev.device =
		device_create(pvconv_class, NULL, vconv_number, NULL,
			DEVICE_NAME);
	if (IS_ERR(s_vconv_dev.device)) {
		ierr = PTR_ERR(s_vconv_dev.device);
		cdev_del(&(s_vconv_dev.cdev));
		VCONV_ERR("device_create() failed %d\n", ierr);
		goto fail_device_create;
	}

	/* allocate registers memory region */
	vconv_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "vconv");
	if (vconv_res == NULL) {
		ierr = -EBUSY;
		goto fail_requet_mem_region;
	}
	pmu_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pmu");
	if (pmu_res == NULL) {
		ierr = -EBUSY;
		goto fail_requet_mem_region;
	}

	/* remapping registers */
	s_vconv_dev.vconvbase =
		(__u8 __iomem *)ioremap(vconv_res->start,
						resource_size(vconv_res));
	if (s_vconv_dev.vconvbase == NULL) {
		VCONV_ERR("ioremap() failed VCONV Registers[%08x - %d]\n",
				vconv_res->start, resource_size(vconv_res));
		ierr = -ENOMEM;
		goto fail_ioremap;
	}
	s_vconv_dev.pmubase =
			(__u8 __iomem *)ioremap(pmu_res->start,
						 resource_size(pmu_res));
	if (s_vconv_dev.pmubase == NULL) {
		VCONV_ERR("ioremap() failed PMU Registers[%08x - %d]\n",
				pmu_res->start, resource_size(pmu_res));
		ierr = -ENOMEM;
		goto fail_ioremap2;
	}
	platform_set_drvdata(pdev, &s_vconv_dev);

	s_vconv_dev.clk = clk_get(&(pdev->dev), NULL);
	if (IS_ERR(s_vconv_dev.clk)) {
		VCONV_ERR("clk_get(%s) failed\n", dev_name(&(pdev->dev)));
		ierr = -EFAULT;
		goto fail_clk_get;
	}

	/* initialize registers */
	vconv_init_hw(&s_vconv_dev);

	DUMP_VCONV_DEV(&(s_vconv_dev));		/* for TEST */

	pr_info("vconv Driver [%s] Initialized.[%d.%d]\n",
		VCONV_DRIVER_VERSION,
		MAJOR(vconv_number), MINOR(vconv_number));

	pm_runtime_enable(&(pdev->dev));

	VCONV_FUNC_END("\n");

	return 0;

fail_clk_get:
	iounmap(s_vconv_dev.pmubase);
fail_ioremap2:
	iounmap(s_vconv_dev.vconvbase);
fail_ioremap:
fail_requet_mem_region:
	device_destroy(pvconv_class, vconv_number);
fail_device_create:
	cdev_del(&(s_vconv_dev.cdev));
fail_cdev_add:
	class_destroy(pvconv_class);
fail_class_create:
	unregister_chrdev_region(MAJOR(vconv_number), 1);

	vconv_procfs_remove();

	VCONV_ERR("vconv Driver [%s] load failed.\n", VCONV_DRIVER_VERSION);

	VCONV_FUNC_END("\n");

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
static int __devexit vconv_remove(struct platform_device *pdev)
{
	VCONV_FUNC_START("\n");

	pm_runtime_disable(&(pdev->dev));

	/* uninitialize registers */
	vconv_exit_hw(&s_vconv_dev);

	clk_put(s_vconv_dev.clk);

	/* memory io unmap */
	iounmap(s_vconv_dev.pmubase);
	VCONV_TEST("iounmap() pmubase:%p\n", s_vconv_dev.pmubase);
	iounmap(s_vconv_dev.vconvbase);
	VCONV_TEST("iounmap() vconvbase:%p\n", s_vconv_dev.vconvbase);
	device_destroy(pvconv_class, vconv_number);
	VCONV_TEST("device_destroy() success\n");
	cdev_del(&(s_vconv_dev.cdev));
	VCONV_TEST("cdev_del() success\n");
	unregister_chrdev_region(MAJOR(vconv_number), 1);
	VCONV_TEST("unregister_chrdev_region() success\n");
	class_destroy(pvconv_class);
	VCONV_TEST("class_destroy() success\n");

	vconv_procfs_remove();
	VCONV_INFO("vconv Driver Uninitialized.\n");

	VCONV_FUNC_END("\n");
	return 0;
}

static int vconv_suspend(struct device *dev)
{
	VCONV_FUNC_START("\n");
	VCONV_INFO("usecount:%d\n", s_vconv_dev.vconv_usecount);
	if (s_vconv_dev.vconv_usecount > 0)
		return -EBUSY;

	return 0;
}

static int vconv_resume(struct device *dev)
{
	VCONV_FUNC_START("\n");
	vconv_init_hw(&s_vconv_dev);
	return 0;
}

static int vconv_runtime_suspend(struct device *dev)
{
	VCONV_FUNC_START("\n");
	return vconv_runtime_suspend_sub(&s_vconv_dev);
}

static int vconv_runtime_resume(struct device *dev)
{
	VCONV_FUNC_START("\n");
	return vconv_runtime_resume_sub(&s_vconv_dev);
}

static int __init vconv_init(void)
{
	VCONV_FUNC_START("\n");
	return platform_driver_register(&applite_vconv_driver);
}

static void __exit vconv_exit(void)
{
	VCONV_FUNC_START("\n");
	platform_driver_unregister(&applite_vconv_driver);
	VCONV_FUNC_END("\n");
}


module_init(vconv_init);
module_exit(vconv_exit);



