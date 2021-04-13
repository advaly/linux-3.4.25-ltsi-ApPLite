/*
 * drivers/staging/applite/vdu/applite_vdu_base.c
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
 *	task_std=N		Default N=2048(KiB), input-ring buffer size
 *	task_work=N		Default N=22528(KiB), fw is work memory size
 *	uf_thr=N		Default N=1048576, underflow threshold for
 *				input ring-buffer
 *	debug=b			Default false, debug flag
 *	trace_area_size=b	Default N=4(KiB), trace buffer size
 *	power_ctrl=XXX		Default on, power control (on, off, or auto)
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

#include <linux/applite/applite_vdu.h>
#include "applite_vdu_internal.h"


/* MODULE INFORMATION */
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Speyside Video Decoder Driver");
MODULE_VERSION(VDU_DRIVER_VERSION_STRING);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("vdu");


/*===================================
Static Variables and Functions prototypes
===================================*/

static struct vdu_driver vdu_dev;
static struct class *pvdu_class;
static dev_t vdu_number;
static int dev_num;

static int vdu_open(struct inode *inode, struct file *file);
static int vdu_release(struct inode *inode, struct file *file);
static long vdu_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/* Encapsulate the module parameter settings */
static struct vdu_mod_data mod_data = {
	.task_std	= VDU_TASK_STD_SIZE_KiB,
	.task_work	= VDU_TASK_WORK_SIZE_KiB,
	.uf_thr		= VDU_UNDERFLOW_THR,
	.debug		= false,
	.trace_area_size = VDU_TRACE_SIZE_KiB,
	.power_ctrl	= "on"
};

module_param_named(task_std, mod_data.task_std, int, S_IRUGO);
MODULE_PARM_DESC(task_std, "size of input ring-buffer size (KiB)");

module_param_named(task_work, mod_data.task_work, int, S_IRUGO);
MODULE_PARM_DESC(task_work, "fw is work memory size (KiB)");

module_param_named(uf_thr, mod_data.uf_thr, int, S_IRUGO);
MODULE_PARM_DESC(uf_thr, "underflow threshold for input ring-buffer (byte)");

module_param_named(debug, mod_data.debug, bool, S_IRUGO);
MODULE_PARM_DESC(debug, "debug flag (false, or true)");

module_param_named(trace_area_size, mod_data.trace_area_size, int, S_IRUGO);
MODULE_PARM_DESC(trace_area_size, "trace buffer size (KiB)");

module_param_named(power_ctrl, mod_data.power_ctrl, charp, S_IRUGO);
/*MODULE_PARM_DESC(power_ctrl, "power control (on, off, or auto)");*/
MODULE_PARM_DESC(power_ctrl, "power control (on, or off)");

static const struct file_operations vdu_fops = {
	.owner          = THIS_MODULE,
	.open           = vdu_open,
	.release        = vdu_release,
	.unlocked_ioctl = vdu_ioctl,
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


static int vdu_open(struct inode *inode, struct file *file)
{
	int ierr = 0;
	struct vdu_op_device *op_dev = NULL;
	struct vdu_driver *pdev = container_of(
		inode->i_cdev,
		struct vdu_driver, cdev);

	DBG(pdev, "enter [dev_num=%d]\n", dev_num);

	if (pdev == NULL) {
		ERROR(pdev, "not device structure\n");
		return -EINVAL;
	}

	op_dev = vdu_kmalloc(sizeof(*op_dev));
	if (op_dev == NULL) {
		ERROR(pdev, "kernel memory allocate failed [size=%d]\n",
			sizeof(*op_dev));
		ierr = -ENOMEM;
		goto fail_1;
	}
	DBG(pdev, "kmalloc(0x%08x)\n", (u32)op_dev);

	if (dev_num == 0) {
		/* initialize VIP1 FW */
		vdu_internal_init_resource(pdev);
		if (pdev->devsts < VDU_STAT_RESET_ON) {
			/* download VIP1 FW */
			ierr = vdu_internal_fw_download(pdev);
			if (ierr < 0)
				goto fail_2;
			pdev->devsts = VDU_STAT_RESET_ON;
		}
		ierr = vdu_internal_initialize(pdev);
		if (ierr < 0)
			goto fail_2;
		pdev->devsts = VDU_STAT_IDLE;
	}

	dev_num++;
	op_dev->pdev = pdev;
	op_dev->taskid = 0;
	file->private_data = op_dev;

	DBG(pdev, "leave [rtn=%d]\n", ierr);

	return ierr;

fail_2:
	DBG(pdev, "kfree(0x%08x)\n", (u32)op_dev);
	vdu_kfree(op_dev);
fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static int vdu_release(struct inode *inode, struct file *file)
{
	int ierr = 0;
	struct vdu_op_device *op_dev = file->private_data;
	struct vdu_driver *pdev = op_dev->pdev;
	struct vdu_task *ptask = NULL;

	DBG(pdev, "enter [dev_num=%d]\n", dev_num);

	if (op_dev->taskid) {
		ierr = vdu_internal_searchtask(pdev, op_dev->taskid, &ptask);
		if (!ierr) {
			/* stop task & destroy */
			vdu_internal_cancel_task(pdev, ptask);
			vdu_internal_stop_task(pdev, ptask);
			vdu_internal_destroy_task(pdev, ptask);
		}
	}
	DBG(pdev, "kfree(0x%08x)\n", (u32)op_dev);
	vdu_kfree(op_dev);
	file->private_data = NULL;

	dev_num--;
	if (dev_num == 0) {
		if (pdev->devsts > VDU_STAT_RESET_ON) {
			/* finalize VIP1 */
			vdu_internal_finalize(pdev,
				VDU_FIN_PHASE1|VDU_FIN_PHASE2|VDU_FIN_PHASE3);

			/* clear resource */
			vdu_internal_clear_resource(pdev);

			/* initialize resource */
			vdu_internal_init_resource(pdev);
		}
		pdev->devsts = VDU_STAT_NOFW;
	}
	ierr = 0;
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static long vdu_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ierr = 0;
	struct vdu_op_device *op_dev = file->private_data;
	struct vdu_driver *pdev = op_dev->pdev;
	void __user *argp = (void __user *)arg;
	struct vdec_start arg_start;
	struct vdec_getininfo arg_getininfo;
	struct vdec_setindata arg_setindata;
	struct vdec_getoutframe arg_getoutframe;
	struct vdec_waitforinbuf arg_waitforinbuf;
	struct vdec_waitforoutframe arg_waitforoutframe;
	struct vdec_getoutframewithconv arg_getoutframewithconv;

	DBG(pdev, "enter [cmd=0x%08x]\n", cmd);

	if (pdev->devsts < VDU_STAT_IDLE) {
		/* not initialize */
		ERROR(pdev, "not initialize VD_API\n");
		ierr =  -EVDUNOINIT;
		goto fail_1;
	}

	switch (cmd) {
	case IOC_VDEC_START:
		if (copy_from_user(&arg_start,
				argp, sizeof(arg_start))) {
			ERROR(pdev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = vdu_ioctl_start(pdev, &arg_start, &op_dev->taskid);
		break;

	case IOC_VDEC_STOP:
		ierr = vdu_ioctl_stop(pdev, op_dev->taskid);
		break;

	case IOC_VDEC_GETININFO:
		ierr = vdu_ioctl_getininfo(pdev,
			&arg_getininfo, op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_getininfo,
					sizeof(arg_getininfo))) {
				ERROR(pdev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	case IOC_VDEC_SETINDATA:
		if (copy_from_user(&arg_setindata, argp,
				sizeof(arg_setindata))) {
			ERROR(pdev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = vdu_ioctl_setindata(pdev,
			&arg_setindata, op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_setindata,
					sizeof(arg_setindata))) {
				ERROR(pdev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	case IOC_VDEC_GETOUTFRAME:
		if (copy_from_user(&arg_getoutframe, argp,
				sizeof(arg_getoutframe))) {
			ERROR(pdev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = vdu_ioctl_getoutframe(pdev, &arg_getoutframe,
			op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_getoutframe,
					sizeof(arg_getoutframe))) {
				ERROR(pdev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	case IOC_VDEC_RELOUTFRAME:
		ierr = vdu_ioctl_reloutframe(pdev, op_dev->taskid);
		break;

	case IOC_VDEC_WAITFORINBUF:
		if (copy_from_user(&arg_waitforinbuf, argp,
				sizeof(arg_waitforinbuf))) {
			ERROR(pdev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = vdu_ioctl_waitforinbuf(pdev,
			&arg_waitforinbuf, op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_waitforinbuf,
					sizeof(arg_waitforinbuf))) {
				ERROR(pdev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	case IOC_VDEC_WAITFOROUTFRAME:
		if (copy_from_user(&arg_waitforoutframe, argp,
				sizeof(arg_waitforoutframe))) {
			ERROR(pdev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = vdu_ioctl_waitforoutframe(pdev,
			&arg_waitforoutframe, op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_waitforoutframe,
					sizeof(arg_waitforoutframe))) {
				ERROR(pdev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	case IOC_VDEC_CANCEL:
		ierr = vdu_ioctl_cancel(pdev, op_dev->taskid);
		break;

	case IOC_VDEC_GETOUTFRAMEWITHCONV:
		if (copy_from_user(&arg_getoutframewithconv, argp,
				sizeof(arg_getoutframewithconv))) {
			ERROR(pdev, "copy_from_user() failed [argp=%lx]\n",
				(unsigned long)argp);
			ierr = -EFAULT;
			break;
		}
		ierr = vdu_ioctl_getoutframewithconv(pdev,
			&arg_getoutframewithconv, op_dev->taskid);
		if (ierr == 0) {
			if (copy_to_user(argp, &arg_getoutframewithconv,
					sizeof(arg_getoutframewithconv))) {
				ERROR(pdev, "copy_to_user() failed [argp=%lx]\n",
					(unsigned long)argp);
				ierr = -EFAULT;
			}
		}
		break;

	default:
		ERROR(pdev, "illegal ioctl command [cmd=%x]\n", cmd);
		ierr = -ENOIOCTLCMD;
		break;
	}

	DBG(pdev, "leave [rtn=%d]\n", (u32)ierr);
	return ierr;

fail_1:
	DBG(pdev, "leave [rtn=%d]\n", (u32)ierr);
	return ierr;
}

static irqreturn_t vdu_irq(int irq, void *dev_id)
{
	int32_t handled = IRQ_HANDLED;
	unsigned long flag;
	struct vdu_driver *pdev = (struct vdu_driver *)dev_id;

	/*DBG(&vdu_dev, "enter\n");*/

	spin_lock_irqsave(&pdev->splock, flag);
	vdu_internal_irq_function(pdev);
	spin_unlock_irqrestore(&pdev->splock, flag);

	/*DBG(pdev, "leave\n");*/
	return IRQ_RETVAL(handled);
}

static int __devinit
vdu_probe(struct platform_device *pdev)
{
	int ierr = 0;
	int i;

	memset(&vdu_dev, 0x00, sizeof(vdu_dev));
	vdu_dev.pdev = pdev;

	DBG(&vdu_dev, "enter\n");

	/* create proc fs */
	vdu_procfs_create();

	/* register char device */
	ierr = alloc_chrdev_region(&vdu_number, 0, 1, VDU_DEVICE_NAME);
	if (ierr) {
		ERROR(&vdu_dev, "alloc_chrdev_region() failed [err=%d]\n", ierr);
		vdu_procfs_remove();	/* #1 */
		vdu_dev.fail = 1;
		return ierr;
	}
	pvdu_class = class_create(THIS_MODULE, VDU_DEVICE_NAME);
	if (IS_ERR(pvdu_class)) {
		ierr = PTR_ERR(pvdu_class);
		ERROR(&vdu_dev, "class_create() failed [err=%d]\n", ierr);
		unregister_chrdev_region(MAJOR(vdu_number), 1);	/* #2 */
		vdu_procfs_remove();				/* #1 */
		vdu_dev.fail = 1;
		return ierr;
	}
	cdev_init(&(vdu_dev.cdev), &vdu_fops);
	vdu_dev.cdev.owner = THIS_MODULE;
	ierr = cdev_add(&(vdu_dev.cdev), vdu_number, 1);
	if (ierr) {
		ERROR(&vdu_dev, "cdev_add() failed [err=%d]\n", ierr);
		class_destroy(pvdu_class);			/* #3 */
		unregister_chrdev_region(MAJOR(vdu_number), 1);	/* #2 */
		vdu_procfs_remove();				/* #1 */
		vdu_dev.fail = 1;
		return ierr;
	}
	vdu_dev.device = device_create(pvdu_class, NULL, vdu_number,
		NULL, VDU_DEVICE_NAME);
	if (IS_ERR(vdu_dev.device)) {
		ierr = PTR_ERR(vdu_dev.device);
		ERROR(&vdu_dev, "device_create() failed [err=%d]\n", ierr);
		cdev_del(&(vdu_dev.cdev));			/* #4 */
		class_destroy(pvdu_class);			/* #3 */
		unregister_chrdev_region(MAJOR(vdu_number), 1);	/* #2 */
		vdu_procfs_remove();				/* #1 */
		vdu_dev.fail = 1;
		return ierr;
	}
	vdu_dev.device = &pdev->dev;

	dev_num = 0;
	vdu_dev.devsts = VDU_STAT_NOFW;
	spin_lock_init(&vdu_dev.splock);
	init_waitqueue_head(&vdu_dev.vdu_waitq);
	vdu_dev.wait_cond = 0;
	sema_init(&vdu_dev.vdu_sem, 1);

	DBG(&vdu_dev, "call request_irq(%d)\n", IRQ_NUMBER_VDU);
	if (request_irq(IRQ_NUMBER_VDU, vdu_irq, 0, VDU_DEVICE_NAME,
			&vdu_dev)) {
		ERROR(&vdu_dev, "request_irq() failed [irq=%d]\n",
			IRQ_NUMBER_VDU);
		ierr = -EINVAL;
		goto fail_1;
	}
	vdu_dev.irq = IRQ_NUMBER_VDU;

	/* set module parameter */
	if (mod_data.task_std < 1) {
		ERROR(&vdu_dev, "invalid task_std parameter: %d\n",
			mod_data.task_std);
		ierr = -EINVAL;
		goto fail_1;
	}
	vdu_dev.vdu_task_std_size = (int32_t)VDU_TOBYTE(mod_data.task_std);
	DBG(&vdu_dev, "task_std parameter(%d)\n", vdu_dev.vdu_task_std_size);
	if (mod_data.task_work < 1) {
		ERROR(&vdu_dev, "invalid task_work parameter: %d\n",
			mod_data.task_work);
		ierr = -EINVAL;
		goto fail_1;
	}
	vdu_dev.vdu_task_work_size = (int32_t)VDU_TOBYTE(mod_data.task_work);
	DBG(&vdu_dev, "task_work parameter(%d)\n", vdu_dev.vdu_task_work_size);
	if ((mod_data.uf_thr < 0) ||
	    ((vdu_dev.vdu_task_std_size-1) < mod_data.uf_thr)) {
		ERROR(&vdu_dev, "invalid uf_thr parameter: %d\n",
			mod_data.uf_thr);
		ierr = -EINVAL;
		goto fail_1;
	}
	vdu_dev.uf_thr = (int32_t)mod_data.uf_thr;
	DBG(&vdu_dev, "uf_thr parameter(%d)\n", vdu_dev.uf_thr);
	if (mod_data.debug == true) {
		if (mod_data.trace_area_size < 1) {
			ERROR(&vdu_dev, "invalid trace_area_size parameter: %d\n", mod_data.trace_area_size);
			ierr = -EINVAL;
			goto fail_1;
		}
		vdu_dev.debug = true;
		vdu_dev.trace_area_size =
			(int32_t)VDU_TOBYTE(mod_data.trace_area_size);
	}
	DBG(&vdu_dev, "debug parameter(%d)\n", vdu_dev.debug);
	DBG(&vdu_dev, "trace_area_size parameter(%d)\n",
		vdu_dev.trace_area_size);
	if (strnicmp(mod_data.power_ctrl, "on", 8) == 0) {
		vdu_dev.pctrl = VDU_POWER_CTRL_ON;
	} else if (strnicmp(mod_data.power_ctrl, "off", 8) == 0) {
		vdu_dev.pctrl = VDU_POWER_CTRL_OFF;
/*
	} else if (strnicmp(mod_data.power_ctrl, "auto", 8) == 0) {
		vdu_dev.pctrl = VDU_POWER_CTRL_AUTO;
*/
	} else {
		ERROR(&vdu_dev, "invalid power control parameter: %s\n",
			mod_data.power_ctrl);
		ierr = -EINVAL;
		goto fail_1;
	}
	DBG(&vdu_dev, "power_ctrl parameter(%d)\n", vdu_dev.pctrl);

	/* ioremap */
	vdu_dev.io[VDU_IOMEM_PMU_REG] = CPU_PMU_REG_BASE;
	vdu_dev.iomem[VDU_IOMEM_PMU_REG] =
		ioremap_nocache(vdu_dev.io[VDU_IOMEM_PMU_REG],
				CPU_PMU_REG_SIZE);
	if (!vdu_dev.iomem[VDU_IOMEM_PMU_REG]) {
		ERROR(&vdu_dev, "ioremap(%x:%d) failed\n",
			vdu_dev.io[VDU_IOMEM_PMU_REG], CPU_PMU_REG_SIZE);
		ierr = -ENOMEM;
		goto fail_1;
	}
	vdu_dev.io[VDU_IOMEM_ECONF_REG] = CPU_ECONF_REG_BASE;
	vdu_dev.iomem[VDU_IOMEM_ECONF_REG] =
		ioremap_nocache(vdu_dev.io[VDU_IOMEM_ECONF_REG],
				CPU_ECONF_REG_SIZE);
	if (!vdu_dev.iomem[VDU_IOMEM_ECONF_REG]) {
		ERROR(&vdu_dev, "ioremap(%x:%d) failed\n",
			vdu_dev.io[VDU_IOMEM_ECONF_REG], CPU_ECONF_REG_SIZE);
		ierr = -ENOMEM;
		goto fail_1;
	}
	vdu_dev.io[VDU_IOMEM_MBOX_REG] = CPU_MBOX_REG_BASE;
	vdu_dev.iomem[VDU_IOMEM_MBOX_REG] =
		ioremap_nocache(vdu_dev.io[VDU_IOMEM_MBOX_REG],
				CPU_MBOX_REG_SIZE);
	if (!vdu_dev.iomem[VDU_IOMEM_MBOX_REG]) {
		ERROR(&vdu_dev, "ioremap(%x:%d) failed\n",
			vdu_dev.io[VDU_IOMEM_MBOX_REG], CPU_MBOX_REG_SIZE);
		ierr = -ENOMEM;
		goto fail_1;
	}

	vdu_dev.clk = clk_get(&(pdev->dev), "vdu");
	if (IS_ERR(vdu_dev.clk)) {
		ERROR(&vdu_dev, "clk_get(%s) failed\n",
					dev_name(&(pdev->dev)));
		ierr = -EFAULT;
		goto fail_1;
	}
	pm_runtime_enable(&(pdev->dev));

	vdu_internal_init_resource(&vdu_dev);

	ierr = vdu_internal_alloc_fwarea(&vdu_dev);
	if (ierr < 0)
		goto fail_1;

	INFO(&vdu_dev, "vdu Driver [%s] Initialized.[%d.%d]\n",
		VDU_DRIVER_VERSION_STRING,
		MAJOR(vdu_number), MINOR(vdu_number));
	return 0;

fail_1:
	if (vdu_dev.irq)
		free_irq(IRQ_NUMBER_VDU, &vdu_dev);
	for (i = 0; i < VDU_IOMEM_MAX; i++) {
		if (vdu_dev.iomem[i]) {
			DBG(&vdu_dev, "iounmap 0x%08x\n",
				(u32)vdu_dev.iomem[i]);
			iounmap(vdu_dev.iomem[i]);
		}
	}
	device_destroy(pvdu_class, vdu_number);		/* #5 */
	cdev_del(&(vdu_dev.cdev));			/* #4 */
	class_destroy(pvdu_class);			/* #3 */
	unregister_chrdev_region(MAJOR(vdu_number), 1);	/* #2 */
	vdu_procfs_remove();				/* #1 */
	vdu_dev.fail = 1;
	return ierr;
}

static int __devexit
vdu_remove(struct platform_device *pdev)
{
	int i;

	if (vdu_dev.fail)
		goto done_1;

	free_irq(IRQ_NUMBER_VDU, &vdu_dev);

	/* clear resource */
	vdu_internal_clear_resource(&vdu_dev);

	vdu_internal_free_fwarea(&vdu_dev);

	pm_runtime_disable(&(pdev->dev));
	clk_put(vdu_dev.clk);

	vdu_dev.devsts = VDU_STAT_NOFW;

	/* iounmap */
	for (i = 0; i < VDU_IOMEM_MAX; i++) {
		if (vdu_dev.iomem[i]) {
			DBG(&vdu_dev, "iounmap 0x%08x\n",
				(u32)vdu_dev.iomem[i]);
			iounmap(vdu_dev.iomem[i]);
		}
	}

	device_destroy(pvdu_class, vdu_number);
	cdev_del(&(vdu_dev.cdev));
	unregister_chrdev_region(MAJOR(vdu_number), 1);
	class_destroy(pvdu_class);
	vdu_procfs_remove();

done_1:
	INFO(&vdu_dev, "vdu Driver Uninitialized.\n");

	return 0;
}

static int vdu_suspend(struct device *dev)
{
	DBG(&vdu_dev, "enter [dev=%p]\n", dev);
	if (dev_num > 0)
		return -EBUSY;
	return 0;
}

static int vdu_resume(struct device *dev)
{
	DBG(&vdu_dev, "enter [dev=%p]\n", dev);
	return 0;
}

static int vdu_runtime_suspend(struct device *dev)
{

	DBG(&vdu_dev, "enter [dev=%p]\n", dev);
	vdu_internal_vip1_reset(&vdu_dev, 1);
	vcodec_power_down();
	return 0;
}

static int vdu_runtime_resume(struct device *dev)
{

	DBG(&vdu_dev, "enter [dev=%p]\n", dev);
	vcodec_power_up();
	vdu_internal_vip1_reset(&vdu_dev, 0);
	return 0;
}

static const struct dev_pm_ops applite_vdu_pm_ops = {
	.suspend = vdu_suspend,
	.resume = vdu_resume,
	.runtime_suspend = vdu_runtime_suspend,
	.runtime_resume = vdu_runtime_resume,
};

static struct platform_driver applite_vdu_driver = {
	.probe = vdu_probe,
	.remove = vdu_remove,
	.driver = {
		.name = "applitevdu",
		.owner = THIS_MODULE,
		.pm = &applite_vdu_pm_ops,
	},
};

static int __init vdu_init(void)
{
	return platform_driver_register(&applite_vdu_driver);
}

static void __exit vdu_cleanup(void)
{
	platform_driver_unregister(&applite_vdu_driver);

}


module_init(vdu_init);
module_exit(vdu_cleanup);
