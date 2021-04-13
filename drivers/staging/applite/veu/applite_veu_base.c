/*
 * drivers/staging/applite/veu/applite_veu_base.c
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

/*
 * Module options:
 *
 *      power_ctrl=XXX          Default on, power control (on, off, or auto)
 */

/*===================================
Include Files
===================================*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/interrupt.h> /* tasklet */
#include <linux/sched.h>     /* task_struct */
#include <linux/wait.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/pm_domain.h>


#include <linux/applite/applite_veu.h>
#include "applite_veu_internal.h"

/* MODULE INFORMATION */
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Speyside Video Encoder Driver");
MODULE_VERSION(VEU_DRIVER_VERSION_STRING);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("veu");


/*===================================
Static Variables and Functions prototypes
===================================*/

struct veu_driver s_veu_dev;
static struct class *pveu_class;
static dev_t veu_number;
static int dev_num;

static int veu_open(struct inode *inode, struct file *file);
static int veu_release(struct inode *inode, struct file *file);
static long veu_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static void veu_tasklet(unsigned long);
static irqreturn_t veu_irq(int, void *);

/* 20130410A */
/* Encapsulate the module parameter settings */
static struct veu_mod_data mod_data = {
	/*.power_ctrl = "off"*/
	.power_ctrl = "on"
};

module_param_named(power_ctrl, mod_data.power_ctrl, charp, S_IRUGO);
/*MODULE_PARM_DESC(power_ctrl, "power control (on, off, or auto)");*/
MODULE_PARM_DESC(power_ctrl, "power control (on, or off)");

static const struct file_operations veu_fops = {
	.owner          = THIS_MODULE,
	.open           = veu_open,
	.release        = veu_release,
	.unlocked_ioctl = veu_ioctl,
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


static int veu_open(struct inode *inode, struct file *file)
{
	int ierr = 0;
	struct veu_op_device *op_dev = NULL;
	struct veu_driver *pdev = container_of(
		inode->i_cdev,
		struct veu_driver, cdev);

	DBG(&s_veu_dev, "enter [dev_num=%d]\n", dev_num);

	if (pdev == NULL) {
		ERROR(&s_veu_dev, "not device structure\n");
		ierr = -EINVAL;
		goto fail_1;
	}

	down(&pdev->veu_sem);

	op_dev = kmalloc(sizeof(*op_dev), GFP_KERNEL);
	if (op_dev == NULL) {
		ERROR(&s_veu_dev, "kernel memory allocate failed [size=%d]\n", sizeof(*op_dev));
		ierr = -ENOMEM;
		goto fail_2;
	}
	sema_init(&op_dev->veu_sem, 1); /* 20130410A */

	if (dev_num == 0) {
		/* initialize VE_API & VIP4 FW */
		veu_internal_init_resource(pdev);
		if (pdev->devsts < VEU_STAT_RESET_ON) {
			/* download VIP4 FW */
			ierr = veu_internal_fw_download(pdev);
			if (ierr < 0)
				goto fail_2;
			pdev->devsts = VEU_STAT_RESET_ON;
		}
		ierr = veu_internal_initialize(pdev);
		if (ierr < 0)
			goto fail_2;
		pdev->devsts = VEU_STAT_IDLE;
	}

	/* create task */
	ierr = veu_internal_cretask(pdev, &op_dev->taskid);
	if (ierr < 0)
		goto fail_3;

	dev_num++;
	op_dev->pdev = pdev;
	file->private_data = op_dev;

	up(&pdev->veu_sem);

	DBG(&s_veu_dev, "leave [rtn=%d]\n", ierr);

	return ierr;
fail_3:
	veu_internal_finalize(pdev);
fail_2:
	kfree(op_dev);
	up(&pdev->veu_sem);
fail_1:
	DBG(&s_veu_dev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static int veu_release(struct inode *inode, struct file *file)
{
	int ierr = 0;
	struct veu_op_device *op_dev = file->private_data;
	struct veu_driver *pdev;

	DBG(&s_veu_dev, "enter [dev_num=%d]\n", dev_num);

	if ((op_dev == NULL) || (op_dev->pdev == NULL)) {
		ERROR(&s_veu_dev, "not device structure\n");
		ierr = -EINVAL;
		goto fail_1;
	}
	pdev = op_dev->pdev;

	down(&pdev->veu_sem);

	/* kill task */
	veu_internal_killtask(pdev, op_dev->taskid);
	kfree(op_dev);
	file->private_data = NULL;

	dev_num--;
	if (dev_num == 0) {
		tasklet_kill(&pdev->veu_tasklet);
		if (pdev->devsts > VEU_STAT_RESET_ON) {
			/* finalize VE_API & VIP4 */
			veu_internal_finalize(pdev);

			/* clear resource */
			veu_internal_clear_resource(pdev);

			/* initialize resource */
			veu_internal_init_resource(pdev);
		}
		pdev->devsts = VEU_STAT_NOFW;
	}

	up(&pdev->veu_sem);

	DBG(&s_veu_dev, "leave [rtn=%d]\n", ierr);

	return ierr;
fail_1:
	DBG(&s_veu_dev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static long veu_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ierr = 0;
	struct veu_op_device *op_dev = file->private_data;
	struct veu_driver *pdev;
	void __user *argp = (void __user *)arg;
	struct venc_getparam arg_getparam;
	struct venc_setparam arg_setparam;
	struct venc_setinframe arg_setinframe;
	struct venc_waitforevents arg_waitforevents;
	struct venc_getoutframe arg_getoutframe;
	struct venc_setinframewithcnv arg_setinframewithcnv;

	DBG(&s_veu_dev, "enter [cmd=0x%08x]\n", cmd);

	if ((op_dev == NULL) || (op_dev->pdev == NULL)) {
		ERROR(&s_veu_dev, "not device structure\n");
		ierr = -EINVAL;
		goto fail_1;
	}
	pdev = op_dev->pdev;

	/* get semaphore */
	down(&op_dev->veu_sem); /* 20130410A */

	switch (cmd) {
	case IOC_VENC_GETPARAM:
		if (pdev->devsts < VEU_STAT_IDLE) {
			/* not initialize */
			ERROR(&s_veu_dev, "not initialize VE_API\n");
			ierr = -EVEUNOINIT;
			break;
		}
		if (copy_from_user(&arg_getparam, argp, sizeof(arg_getparam))) {
			ERROR(&s_veu_dev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = veu_ioctl_getparam(pdev, &arg_getparam, op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_getparam,
				sizeof(arg_getparam))) {
				ERROR(&s_veu_dev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	case IOC_VENC_SETPARAM:
		if (pdev->devsts < VEU_STAT_IDLE) {
			/* not initialize */
			ERROR(&s_veu_dev, "not initialize VE_API\n");
			ierr = -EVEUNOINIT;
			break;
		}
		if (copy_from_user(&arg_setparam, argp, sizeof(arg_setparam))) {
			ERROR(&s_veu_dev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = veu_ioctl_setparam(pdev, &arg_setparam, op_dev->taskid);
		break;

	case IOC_VENC_SETINFRAME:
		if (pdev->devsts < VEU_STAT_IDLE) {
			/* not initialize */
			ERROR(&s_veu_dev, "not initialize VE_API\n");
			ierr = -EVEUNOINIT;
			break;
		}
		if (copy_from_user(&arg_setinframe, argp,
			sizeof(arg_setinframe))) {
			ERROR(&s_veu_dev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = veu_ioctl_setinframe(pdev, &arg_setinframe,
			op_dev->taskid);
		break;

	case IOC_VENC_WAITFOREVENTS:
		if (pdev->devsts < VEU_STAT_IDLE) {
			/* not initialize */
			ERROR(&s_veu_dev, "not initialize VE_API\n");
			ierr = -EVEUNOINIT;
			break;
		}
		if (copy_from_user(&arg_waitforevents, argp,
			sizeof(arg_waitforevents))) {
			ERROR(&s_veu_dev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = veu_ioctl_waitforevents(pdev, &arg_waitforevents,
			op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_waitforevents,
				sizeof(arg_waitforevents))) {
				ERROR(&s_veu_dev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	case IOC_VENC_GETOUTFRAME:
		if (pdev->devsts < VEU_STAT_IDLE) {
			/* not initialize */
			ERROR(&s_veu_dev, "not initialize VE_API\n");
			ierr = -EVEUNOINIT;
			break;
		}
		if (copy_from_user(&arg_getoutframe, argp,
			sizeof(arg_getoutframe))) {
			ERROR(&s_veu_dev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = veu_ioctl_getoutframe(pdev, &arg_getoutframe,
			op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_getoutframe,
				sizeof(arg_getoutframe))) {
				ERROR(&s_veu_dev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	case IOC_VENC_SETINFRAMEWITHCONVERT:
		if (pdev->devsts < VEU_STAT_IDLE) {
			/* not initialize */
			ERROR(&s_veu_dev, "not initialize VE_API\n");
			ierr = -EVEUNOINIT;
			break;
		}
		if (copy_from_user(&arg_setinframewithcnv, argp,
			sizeof(arg_setinframewithcnv))) {
			ERROR(&s_veu_dev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = veu_ioctl_setinframewithcnv(pdev,
			&arg_setinframewithcnv, op_dev->taskid);
		break;

	default:
		ERROR(&s_veu_dev, "illegal ioctl command [cmd=%x]\n", cmd);
		ierr = -ENOIOCTLCMD;
		break;
	}

	/* put semaphore */
	up(&op_dev->veu_sem); /* 20130410A */

	DBG(&s_veu_dev, "leave [rtn=%d]\n", (int)ierr);

	return ierr;
fail_1:
	DBG(&s_veu_dev, "leave [rtn=%d]\n", (int)ierr);
	return ierr;
}

static void veu_tasklet(unsigned long data)
{
	struct veu_driver *pdev = (struct veu_driver *)data;

	veu_internal_tasklet_function(pdev);
}

static irqreturn_t veu_irq(int irq, void *dev_id)
{
	int32_t handled = IRQ_HANDLED;
	unsigned long flag;
	struct veu_driver *pdev = (struct veu_driver *)dev_id;

	spin_lock_irqsave(&pdev->splock, flag);
	veu_internal_irq_function(pdev);
	spin_unlock_irqrestore(&pdev->splock, flag);

	return IRQ_RETVAL(handled);
}

static int __devinit
veu_probe(struct platform_device *pdev)
{
	int i;
	int ierr = 0;

	memset(&s_veu_dev, 0x00, sizeof(s_veu_dev));
	s_veu_dev.pdev = pdev;

	DBG(&s_veu_dev, "enter\n");

	/* create proc fs */
	veu_procfs_create();

	/* register char device */
	ierr = alloc_chrdev_region(&veu_number, 0, 1, VEU_DEVICE_NAME);
	if (ierr) {
		ERROR(&s_veu_dev, "alloc_chrdev_region() failed [err=%d]\n",
			ierr);
		goto fail_1;
	}
	pveu_class = class_create(THIS_MODULE, VEU_DEVICE_NAME);
	if (IS_ERR(pveu_class)) {
		ierr = PTR_ERR(pveu_class);
		ERROR(&s_veu_dev, "class_create() failed [err=%d]\n", ierr);
		goto fail_2;
	}
	cdev_init(&(s_veu_dev.cdev), &veu_fops);
	s_veu_dev.cdev.owner = THIS_MODULE;
	ierr = cdev_add(&(s_veu_dev.cdev), veu_number, 1);
	if (ierr) {
		ERROR(&s_veu_dev, "cdev_add() failed [err=%d]\n", ierr);
		goto fail_3;
	}
	s_veu_dev.device = device_create(pveu_class, NULL, veu_number,
		NULL, VEU_DEVICE_NAME);
	if (IS_ERR(s_veu_dev.device)) {
		ierr = PTR_ERR(s_veu_dev.device);
		ERROR(&s_veu_dev, "device_create() failed [err=%d]\n",
			ierr);
		goto fail_4;
	}
	s_veu_dev.device = &pdev->dev;

	DBG(&s_veu_dev, "call request_irq(%d)\n", IRQ_NUMBER_VEU);
	if (request_irq(IRQ_NUMBER_VEU, veu_irq, 0, VEU_DEVICE_NAME,
		&s_veu_dev)) {
		ERROR(&s_veu_dev, "request_irq() failed [irq=%d]\n",
			IRQ_NUMBER_VEU);
		ierr = -EINVAL;
		goto fail_5;
	}
	s_veu_dev.irq = IRQ_NUMBER_VEU;

	/* ioremap */
	s_veu_dev.io[VEU_IOMEM_PMU_REG] = CPU_PMU_REG_BASE;
	s_veu_dev.iomem[VEU_IOMEM_PMU_REG] =
		ioremap_nocache(s_veu_dev.io[VEU_IOMEM_PMU_REG],
				CPU_PMU_REG_SIZE);
	if (!s_veu_dev.iomem[VEU_IOMEM_PMU_REG]) {
		ERROR(&s_veu_dev, "ioremap(%x:%d) failed\n",
			s_veu_dev.io[VEU_IOMEM_PMU_REG], CPU_PMU_REG_SIZE);
		ierr = -ENOMEM;
		goto fail_5;
	}
	s_veu_dev.io[VEU_IOMEM_MBOX_REG] = CPU_MBOX_REG_BASE;
	s_veu_dev.iomem[VEU_IOMEM_MBOX_REG] =
		ioremap_nocache(s_veu_dev.io[VEU_IOMEM_MBOX_REG],
				CPU_MBOX_REG_SIZE);
	if (!s_veu_dev.iomem[VEU_IOMEM_MBOX_REG]) {
		ERROR(&s_veu_dev, "ioremap(%x:%d) failed\n",
			s_veu_dev.io[VEU_IOMEM_MBOX_REG], CPU_MBOX_REG_SIZE);
		ierr = -ENOMEM;
		goto fail_5;
	}
	s_veu_dev.io[VEU_IOMEM_ECONF_REG] = CPU_ECONF_REG_BASE;
	s_veu_dev.iomem[VEU_IOMEM_ECONF_REG] =
		ioremap_nocache(s_veu_dev.io[VEU_IOMEM_ECONF_REG],
				CPU_ECONF_REG_SIZE);
	if (!s_veu_dev.iomem[VEU_IOMEM_ECONF_REG]) {
		ERROR(&s_veu_dev, "ioremap(%x:%d) failed\n",
			s_veu_dev.io[VEU_IOMEM_ECONF_REG], CPU_ECONF_REG_SIZE);
		ierr = -ENOMEM;
		goto fail_5;
	}

	/* set module parameter */ /* 20130410A */
	if (strnicmp(mod_data.power_ctrl, "on", 8) == 0) {
		s_veu_dev.pctrl = VEU_POWER_CTRL_ON;
	} else if (strnicmp(mod_data.power_ctrl, "off", 8) == 0) {
		s_veu_dev.pctrl = VEU_POWER_CTRL_OFF;
/*
	} else if (strnicmp(mod_data.power_ctrl, "auto", 8) == 0) {
		s_veu_dev.pctrl = VEU_POWER_CTRL_AUTO;
*/
	} else {
		ERROR(&s_veu_dev, "invalid power control parameter: %s\n",
			mod_data.power_ctrl);
		ierr = -EINVAL;
		goto fail_5;
	}
	DBG(&s_veu_dev, "power_ctrl parameter(%d)\n", s_veu_dev.pctrl);

	s_veu_dev.clk = clk_get(&(pdev->dev), "veu");
	if (IS_ERR(s_veu_dev.clk)) {
		ERROR(&s_veu_dev, "clk_get(%s) failed\n",
						dev_name(&(pdev->dev)));
		ierr = -EFAULT;
		goto fail_5;
	}
	pm_runtime_enable(&(pdev->dev));

	dev_num = 0;
	s_veu_dev.devsts = VEU_STAT_NOFW;
	spin_lock_init(&s_veu_dev.splock);
	init_waitqueue_head(&s_veu_dev.veu_waitq);
	s_veu_dev.wait_cond = 0;
	sema_init(&s_veu_dev.veu_sem, 1);
	tasklet_init(&s_veu_dev.veu_tasklet, veu_tasklet,
		(unsigned long)&s_veu_dev);

	veu_internal_init_resource(&s_veu_dev);

#ifdef __KEEP_FWAREA
	veu_internal_alloc_fwarea(&s_veu_dev);
#endif

	INFO(&s_veu_dev, "veu Driver [%s] Initialized.[%d.%d]\n",
		VEU_DRIVER_VERSION_STRING,
		MAJOR(veu_number), MINOR(veu_number));
	return 0;

fail_5:
	if (s_veu_dev.irq)
		free_irq(IRQ_NUMBER_VEU, &s_veu_dev);
	/* iounmap */
	for (i = 0; i < VEU_IOMEM_MAX; i++) {
		if (s_veu_dev.iomem[i])
			iounmap(s_veu_dev.iomem[i]);
	}
	device_destroy(pveu_class, veu_number);
fail_4:
	cdev_del(&(s_veu_dev.cdev));
fail_3:
	class_destroy(pveu_class);
fail_2:
	unregister_chrdev_region(MAJOR(veu_number), 1);
fail_1:
	veu_procfs_remove();
	return ierr;
}

static int __devexit
veu_remove(struct platform_device *pdev)
{
	int i;

	free_irq(IRQ_NUMBER_VEU, &s_veu_dev);

	/* clear resource */
	veu_internal_clear_resource(&s_veu_dev);
#ifdef __KEEP_FWAREA
	veu_internal_free_fwarea(&s_veu_dev);
#endif
	veu_internal_free_tracearea(&s_veu_dev);
	s_veu_dev.devsts = VEU_STAT_NOFW;

	pm_runtime_disable(&(pdev->dev));
	clk_put(s_veu_dev.clk);

	/* iounmap */
	for (i = 0; i < VEU_IOMEM_MAX; i++) {
		if (s_veu_dev.iomem[i])
			iounmap(s_veu_dev.iomem[i]);
	}

	device_destroy(pveu_class, veu_number);
	cdev_del(&(s_veu_dev.cdev));
	unregister_chrdev_region(MAJOR(veu_number), 1);
	class_destroy(pveu_class);
	veu_procfs_remove();
	INFO(&s_veu_dev, "veu Driver Uninitialized.\n");

	return 0;
}

static int veu_suspend(struct device *dev)
{
	DBG(&s_veu_dev, "enter [dev=%p]\n", dev);
	if (dev_num > 0)
		return -EBUSY;
	return 0;
}

static int veu_resume(struct device *dev)
{
	DBG(&s_veu_dev, "enter [dev=%p]\n", dev);
	return 0;
}

static int veu_runtime_suspend(struct device *dev)
{
	DBG(&s_veu_dev, "enter [dev=%p]\n", dev);
	veu_internal_vip4_reset(&s_veu_dev, 1);
	vcodec_power_down();
	return 0;
}

static int veu_runtime_resume(struct device *dev)
{
	DBG(&s_veu_dev, "enter [dev=%p]\n", dev);
	vcodec_power_up();
	veu_internal_vip4_reset(&s_veu_dev, 0);
	return 0;
}

static const struct dev_pm_ops applite_veu_pm_ops = {
	.suspend = veu_suspend,
	.resume = veu_resume,
	.runtime_suspend = veu_runtime_suspend,
	.runtime_resume = veu_runtime_resume,
};

static struct platform_driver applite_veu_driver = {
	.probe = veu_probe,
	.remove = veu_remove,
	.driver = {
		.name = "appliteveu",
		.owner = THIS_MODULE,
		.pm = &applite_veu_pm_ops,
	},
};

static int __init veu_init(void)
{
	return platform_driver_register(&applite_veu_driver);
}

static void __exit veu_cleanup(void)
{
	platform_driver_unregister(&applite_veu_driver);

}


module_init(veu_init);
module_exit(veu_cleanup);
