/*
 * linux/drivers/staging/applite/irecog/affine/affine_driver.c
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
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>	/* create_proc_entry */
#include <linux/uaccess.h>	/* copy_from_user */
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/semaphore.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/platform_data/applite_irecog.h>

#include <linux/applite/irecog/affine_ioctl.h>
#include <linux/applite/irecog/affine_param.h>

#include "affine_driver.h"
#include "affine_util.h"

#include "drv_cache.h"
#include "drv_signal.h"
#include "drv_polling.h"
#include "drv_dmabuf.h"

static const char *drv_affine_version = DRV_AFFINE_VERSION_STR;

static int affine_major = AFFINE_MAJOR;
static int affine_minor = AFFINE_MINOR;
static int affine_nr_devs = AFFINE_NR_DEVS;
static int affine_irq = AFFINE_IRQ;

module_param(affine_major, int, S_IRUGO | S_IWUSR);
module_param(affine_minor, int, S_IRUGO | S_IWUSR);
module_param(affine_nr_devs, int, S_IRUGO | S_IWUSR);
module_param(affine_irq, int, S_IRUGO | S_IWUSR);

static struct affine_dev *affine_device;
static struct class *paffine_class;

static int affine_status = AFFINE_EXE_DONE;
static wait_queue_head_t wq;
static struct semaphore sem;
static atomic_t refcount = ATOMIC_INIT(0);

static struct drv_dmabuf_conv_adr affine_buffer[3];	/* 0: output 1: input 2: table */

static int check_cache_param(ULONG flag)
{
	if ((flag != DRV_CACHE_FLUSH_ALL) && (flag != DRV_NO_CACHE_CTL)) {
		pr_err("%s: invalid buffer_cache_ctl:%lu\n", AFFINE_NAME, flag);
		return -1;
	}

	return 0;
}

static long affine_reset(struct affine_dev *dev);

static int affine_conv_address(struct affine_dev *dev,
			       int dst_fd, int src_fd, int table_fd)
{
	int i;

	for (i = 0; i < (sizeof(affine_buffer) / sizeof(affine_buffer[0])); i++) {
		memset(&affine_buffer[i], 0x00, sizeof(affine_buffer[i]));
	}

	if (drv_dmabuf_get_phys_addr
	    (dev->device, dst_fd, &affine_buffer[0], DMA_FROM_DEVICE) < 0) {
		return -1;
	}

	if (drv_dmabuf_get_phys_addr
	    (dev->device, src_fd, &affine_buffer[1], DMA_TO_DEVICE)
	    < 0) {
		return -1;
	}

	if (table_fd >= 0) {
		if (drv_dmabuf_get_phys_addr
		    (dev->device, table_fd, &affine_buffer[2],
		     DMA_TO_DEVICE) < 0) {
			return -1;
		}
	}

	return 0;
}

static int affine_free_address(void)
{
	drv_dmabuf_put_phys_addr(&affine_buffer[0], DMA_FROM_DEVICE);
	drv_dmabuf_put_phys_addr(&affine_buffer[1], DMA_TO_DEVICE);
	drv_dmabuf_put_phys_addr(&affine_buffer[2], DMA_TO_DEVICE);

	return 0;
}

static int affine_runtime_suspend(struct device *dev)
{
	unsigned int ret;
	struct platform_data *pdata = dev->platform_data;
	struct platform_device *pdev = to_platform_device(dev);
	struct affine_dev *priv = platform_get_drvdata(pdev);

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	iowrite32(IRECOG_RAFFINE_CONTROL_REGISTER_O_RST_MASK,
		  priv->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_Control_Register_OFFS));

	ret = drv_wait_register(priv->reg_base +
				AFFINE_OFFSET
				(IRECOG_raffine_Control_Register_OFFS),
				IRECOG_RAFFINE_CONTROL_REGISTER_CMD_MASK, 0x00,
				DRV_WAIT_REG_TIMEOUT);

	if ((ret & IRECOG_RAFFINE_CONTROL_REGISTER_CMD_MASK) != 0x0) {
		pr_err("%s: timeout occured\n", AFFINE_NAME);
		return -EIO;
	}

	clock_enable(APPLITE_IRECOG_AFFINE, APPLITE_IRECOG_CLOCK_DISABLE);
	return 0;
}

static int affine_runtime_resume(struct device *dev)
{
	struct platform_data *pdata = dev->platform_data;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	clock_enable(APPLITE_IRECOG_AFFINE, APPLITE_IRECOG_CLOCK_ENABLE);
	return 0;
}

static long affine_wait_event(struct file *filp)
{
	sigset_t oldset;
	int status = affine_status;
	struct affine_dev *dev = filp->private_data;

	if (status != AFFINE_EXE_DONE) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		/* signal mask */
		drv_sigmask(&oldset);
		if (wait_event_interruptible(wq,
					     (affine_status ==
					      AFFINE_EXE_DONE))) {

			affine_reset(dev);

			/* signal unmask */
			drv_sigunmask(&oldset);
			affine_status = AFFINE_EXE_DONE;

			pr_err("%s: wait_event_interruptible failed.\n",
			       AFFINE_NAME);
			return -ERESTARTSYS;
		}
		/* signal unmask */
		drv_sigunmask(&oldset);
	}

	return 0;
}

static int affine_get_int_status(struct affine_dev *dev)
{
	unsigned int status;
	int ret;

	status =
	    ioread32(dev->reg_base +
		     AFFINE_OFFSET(IRECOG_raffine_status_Register_OFFS));
	if ((status & AFFINE_STATC_HW_END) != 0) {
		ret = AFFINE_EXE_DONE;
	} else {
		ret = AFFINE_ERROR;
	}

	return ret;
}

static long affine_reset(struct affine_dev *dev)
{
	unsigned int ret;

	iowrite32(AFFINE_RESET,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_Control_Register_OFFS));
	/* wait for reset completion */
	ret =
	    drv_wait_register(dev->reg_base +
			      AFFINE_OFFSET
			      (IRECOG_raffine_Control_Register_OFFS),
			      AFFINE_RESET, 0x0, DRV_WAIT_REG_TIMEOUT);
	if ((ret & AFFINE_RESET) != 0x0) {
		pr_err
		    ("%s: timeout occured while waiting for register value to change\n",
		     AFFINE_NAME);
		return -EIO;
	}

	return 0;
}

static void affine_clear_int(struct affine_dev *dev)
{
	iowrite32(AFFINE_CLEAR_BITS,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_status_Register_OFFS));
}

static SINT dd_AFFINE_send_request(struct affine_dev *dev)
{
	/* Clear Interrupt Status */
	affine_clear_int(dev);

	/* Set Int Mask. */
	iowrite32(AFFINE_INTMASK_NORMAL,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_interrupt_mask_OFFS));

	/* Kick Affine */
	affine_status = AFFINE_KICKED;
	iowrite32(0x1,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_Control_Register_OFFS));

	return 0;
}

static irqreturn_t affine_isr(int irq, void *dev_id)
{
	struct affine_dev *dev = dev_id;
	int status;

	status = affine_get_int_status(dev);
	affine_status = status;
	affine_clear_int(dev);

	if (status == AFFINE_EXE_DONE) {
		wake_up_interruptible(&wq);
	} else if (status == AFFINE_ERROR) {
		wake_up_interruptible(&wq);
	}

	return IRQ_HANDLED;
}

static int affine_open(struct inode *inode, struct file *filp)
{
	struct affine_dev *dev;

	dev = container_of(inode->i_cdev, struct affine_dev, cdev);
	filp->private_data = dev;

	if (atomic_inc_return(&refcount) == 1) {
		affine_runtime_resume(&dev->pdev->dev);
	}
	return 0;
}

static int affine_release(struct inode *inode, struct file *filp)
{
	struct affine_dev *dev;

	dev = container_of(inode->i_cdev, struct affine_dev, cdev);

	if (atomic_dec_return(&refcount) == 0) {
		affine_runtime_suspend(&dev->pdev->dev);
	}
	return 0;
}

static long affine_get_version(unsigned long val)
{
	drv_version_t version_param;

	memset(&version_param, 0x00, sizeof(drv_version_t));
	memcpy(version_param.version, drv_affine_version,
	       strlen(drv_affine_version));

	if (copy_to_user((void __user *)val,
			 (void *)&version_param, sizeof(drv_version_t))) {
		pr_err("%s: copy_to_user failed version\n", AFFINE_NAME);
		return -EFAULT;
	}

	return 0;
}

static long affine_check_operation_param(unsigned long interpolation_mode,
					 unsigned long fill_value,
					 unsigned long process_direction)
{
	if ((interpolation_mode > AFFINE_INTERPOLATION_MODE_NEAREST)) {
		pr_err("%s: invalid interpolation_mode:%lu\n", AFFINE_NAME,
		       interpolation_mode);
		return -EINVAL;
	}

	if ((fill_value > 0xffff)) {
		pr_err("%s: invalid fill_value:0x%lx\n", AFFINE_NAME,
		       fill_value);
		return -EINVAL;
	}

	if ((process_direction > AFFINE_PROCESS_DIRECTION_VERTICAL)) {
		pr_err("%s: invalid process_direction:%lu\n", AFFINE_NAME,
		       process_direction);
		return -EINVAL;
	}

	return 0;
}

static long affine_check_image_param(unsigned long dst_offset_x,
				     unsigned long dst_offset_y,
				     unsigned long dst_width,
				     unsigned long dst_height,
				     unsigned long dst_pitch,
				     unsigned long src_width,
				     unsigned long src_height,
				     unsigned long src_pitch,
				     unsigned long src_depth)
{
	if ((dst_width < AFFINE_MIN_IMG_WIDTH)
	    || (dst_width > AFFINE_MAX_IMG_WIDTH)
	    || (dst_height < AFFINE_MIN_IMG_HEIGHT)
	    || (dst_height > AFFINE_MAX_IMG_HEIGHT)
	    || (dst_pitch < AFFINE_MIN_IMG_PITCH)
	    || (dst_pitch > AFFINE_MAX_IMG_PITCH)
	    || (src_width < AFFINE_MIN_IMG_WIDTH)
	    || (src_width > AFFINE_MAX_IMG_WIDTH)
	    || (src_height < AFFINE_MIN_IMG_HEIGHT)
	    || (src_height > AFFINE_MAX_IMG_HEIGHT)
	    || (src_pitch < AFFINE_MIN_IMG_PITCH)
	    || (src_pitch > AFFINE_MAX_IMG_PITCH) || (dst_width > dst_pitch)
	    || (src_width > src_pitch) || ((src_depth == 8)
					   && (((dst_pitch & 0x003f) != 0)
					       || ((src_pitch & 0x003f) != 0)))
	    || ((src_depth > 8)
		&& (((dst_pitch & 0x001f) != 0) || ((src_pitch & 0x001f) != 0)))
	    || (src_depth < 8) || (src_depth > 12)
	    || (dst_offset_x >= AFFINE_MAX_IMG_WIDTH)
	    || (dst_offset_y >= AFFINE_MAX_IMG_HEIGHT)
	    || ((dst_offset_x + dst_width) > AFFINE_MAX_IMG_WIDTH)
	    || ((dst_offset_y + dst_height) > AFFINE_MAX_IMG_HEIGHT)) {

		pr_err("%s: invalid image_param:\n", AFFINE_NAME);
		pr_err("    dst_width:%lu dst_height:%lu dst_pitch:%lu\n",
		       dst_width, dst_height, dst_pitch);
		pr_err("    src_width:%lu src_height:%lu src_pitch:%lu\n",
		       src_width, src_height, src_pitch);
		pr_err("    src_depth:%lu\n", src_depth);
		pr_err("    dst_offset_x:%lu dst_offset_y:%lu\n", dst_offset_x,
		       dst_offset_y);

		return -EINVAL;
	}

	return 0;
}

static long affine_check_trans_param(struct affine_transformation_param *param)
{
	long ret = 0;

	ret = affine_check_operation_param(param->interpolation_mode,
					   param->fill_value,
					   param->process_direction);
	if (ret < 0) {
		return ret;
	}

	ret = affine_check_image_param(param->dst_offset_x,
				       param->dst_offset_y,
				       param->dst_width,
				       param->dst_height,
				       param->dst_pitch,
				       param->src_width,
				       param->src_height,
				       param->src_pitch, param->src_depth);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

static long affine_check_undistort_param(struct affine_undistort_param *param)
{
	long ret = 0;

	ret = affine_check_operation_param(param->interpolation_mode,
					   param->fill_value,
					   param->process_direction);
	if (ret < 0) {
		return ret;
	}

	ret = affine_check_image_param(param->dst_offset_x,
				       param->dst_offset_y,
				       param->dst_width,
				       param->dst_height,
				       param->dst_pitch,
				       param->src_width,
				       param->src_height,
				       param->src_pitch, param->src_depth);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

static long affine_check_table_param(struct affine_table_param *param)
{
	long ret = 0;

	ret = affine_check_operation_param(param->interpolation_mode,
					   param->fill_value,
					   param->process_direction);
	if (ret < 0) {
		return ret;
	}

	ret = affine_check_image_param(param->dst_offset_x,
				       param->dst_offset_y,
				       param->dst_width,
				       param->dst_height,
				       param->dst_pitch,
				       param->src_width,
				       param->src_height,
				       param->src_pitch, param->src_depth);
	if (ret < 0) {
		return ret;
	}

	if (((param->table_pitch & 0x001f) != 0) ||
	    (param->table_pitch < 32) || (param->table_pitch > 2048) ||
	    (param->table_sampling_interval > 4)) {
		return -EINVAL;
	}

	return 0;
}

static long affine_ioctl(struct file *filp, unsigned int cmd, unsigned long val)
{
	struct affine_dev *dev = filp->private_data;
	long ret;

	if (affine_reset(dev) < 0) {
		pr_err("%s: reset failed.\n", AFFINE_NAME);
		return -EIO;
	}

	switch (cmd) {
	case AFFINE_IOCTL_TRANSFORMATION:
		{
			struct affine_transformation_param param;
			if (copy_from_user
			    ((void *)&param, (const void __user *)val,
			     sizeof(struct affine_transformation_param))) {

				pr_err
				    ("%s: copy_from_user failed transformation_param\n",
				     AFFINE_NAME);
				return -EFAULT;
			}

			if (affine_check_trans_param(&param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       AFFINE_NAME);
				return -EINVAL;
			}
			if (check_cache_param(param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       AFFINE_NAME);
				return -ERESTARTSYS;
			}

			if (affine_status != AFFINE_EXE_DONE) {
				pr_err("%s: invalid status.\n", AFFINE_NAME);
				up(&sem);
				return -EAGAIN;
			}
			if (affine_conv_address
			    (dev, param.dst_fd, param.src_fd, -1) < 0) {
				pr_err
				    ("%s: failed to get phys address from fd.\n",
				     AFFINE_NAME);
				up(&sem);
				return -EINVAL;
			}

			affine_config_transformation(dev,
						     &param,
						     affine_buffer[0].addr +
						     param.dst_offset,
						     affine_buffer[1].addr +
						     param.src_offset);

			if (param.buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
				drv_cache_flush_all();
			}

			dd_AFFINE_send_request(dev);

			ret = affine_wait_event(filp);
			affine_free_address();
			up(&sem);

			return ret;
		}
		break;

	case AFFINE_IOCTL_UNDISTORT:
		{
			struct affine_undistort_param param;
			if (copy_from_user
			    ((void *)&param, (const void __user *)val,
			     sizeof(struct affine_undistort_param))) {
				pr_err
				    ("%s: copy_from_user failed undistort_param\n",
				     AFFINE_NAME);
				return -EFAULT;
			}

			if (affine_check_undistort_param(&param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       AFFINE_NAME);
				return -EINVAL;
			}
			if (check_cache_param(param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       AFFINE_NAME);
				return -ERESTARTSYS;
			}

			if (affine_status != AFFINE_EXE_DONE) {
				pr_err("%s: invalid status.\n", AFFINE_NAME);
				up(&sem);
				return -EAGAIN;
			}
			if (affine_conv_address
			    (dev, param.dst_fd, param.src_fd, -1) < 0) {
				pr_err
				    ("%s: failed to get phys address from fd.\n",
				     AFFINE_NAME);
				up(&sem);
				return -EINVAL;
			}

			affine_config_undistort(dev,
						&param,
						affine_buffer[0].addr +
						param.dst_offset,
						affine_buffer[1].addr +
						param.src_offset);

			if (param.buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
				drv_cache_flush_all();
			}

			dd_AFFINE_send_request(dev);

			ret = affine_wait_event(filp);
			affine_free_address();
			up(&sem);

			return ret;
		}
		break;

	case AFFINE_IOCTL_TABLE:
		{
			struct affine_table_param param;
			if (copy_from_user
			    ((void *)&param, (const void __user *)val,
			     sizeof(struct affine_table_param))) {
				pr_err
				    ("%s: copy_from_user failed table_param\n",
				     AFFINE_NAME);
				return -EFAULT;
			}

			if (affine_check_table_param(&param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       AFFINE_NAME);
				return -EINVAL;
			}
			if (check_cache_param(param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       AFFINE_NAME);
				return -ERESTARTSYS;
			}

			if (affine_status != AFFINE_EXE_DONE) {
				pr_err("%s: invalid status\n", AFFINE_NAME);
				up(&sem);
				return -EAGAIN;
			}
			if ((param.table_fd < 0) ||
			    (affine_conv_address
			     (dev, param.dst_fd, param.src_fd,
			      param.table_fd) < 0)) {
				pr_err
				    ("%s: failed to get phys address from fd.\n",
				     AFFINE_NAME);
				up(&sem);
				return -EINVAL;
			}

			affine_config_table(dev,
					    &param,
					    affine_buffer[0].addr +
					    param.dst_offset,
					    affine_buffer[1].addr +
					    param.src_offset,
					    affine_buffer[2].addr +
					    param.table_offset);

			if (param.buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
				drv_cache_flush_all();
			}

			dd_AFFINE_send_request(dev);

			ret = affine_wait_event(filp);
			affine_free_address();
			up(&sem);

			return ret;
		}
		break;

	case AFFINE_IOCTL_GET_VERSION:
		return affine_get_version(val);
		break;

	case AFFINE_IOCTL_INITIALIZE:
		if (affine_reset(dev) < 0) {
			pr_err("%s: reset failed.\n", AFFINE_NAME);
			return -EIO;
		}
		break;

	default:
		pr_err("%s: invalid ioctl command 0x%x\n", AFFINE_NAME, cmd);
		return -EINVAL;
		break;
	}

	return 0;
}

static const struct file_operations affine_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = affine_ioctl,
	.open = affine_open,
	.release = affine_release,
};

static void affine_setup_cdev(struct affine_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(affine_major, affine_minor + index);

	cdev_init(&dev->cdev, &affine_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev %d\n", AFFINE_NAME, index);
	}
}

static int __devinit affine_probe(struct platform_device *pdev)
{
	int ret;
	dev_t dev = 0;

	/* allocation of device number */
	if (affine_major) {
		dev = MKDEV(affine_major, affine_minor);
		ret = register_chrdev_region(dev, affine_nr_devs, AFFINE_NAME);
	} else {
		ret =
		    alloc_chrdev_region(&dev, affine_minor, affine_nr_devs,
					AFFINE_NAME);
		affine_major = MAJOR(dev);
	}
	if (ret < 0) {
		pr_err("%s: can't get major %d\n", AFFINE_NAME, affine_major);
		return ret;
	}

	affine_device = kmalloc(sizeof(struct affine_dev), GFP_KERNEL);
	if (!affine_device) {
		pr_err("%s: kmalloc failed\n", AFFINE_NAME);
		ret = -ENOMEM;
		goto err0;
	}
	memset(affine_device, 0, sizeof(struct affine_dev));
	affine_device->pdev = pdev;
	platform_set_drvdata(pdev, affine_device);

	/* mapping of affine MMIO */
	if (!request_mem_region(AFFINE_BASE, AFFINE_SIZE, AFFINE_NAME)) {
		pr_err("%s: request_mem_region failed.\n", AFFINE_NAME);
		ret = -ENODEV;
		goto err1;
	}

	affine_device->reg_base = ioremap_nocache(AFFINE_BASE, AFFINE_SIZE);
	if (!affine_device->reg_base) {
		pr_err("%s: ioremap_nocache failed.\n", AFFINE_NAME);
		ret = -ENODEV;
		goto err2;
	}

	/* register interrupt service routine */
	ret =
	    request_irq(affine_irq, affine_isr, 0, AFFINE_NAME, affine_device);
	if (ret < 0) {
		pr_err("%s: request_irq failed.\n", AFFINE_NAME);
		goto err3;
	}

	affine_status = AFFINE_EXE_DONE;
	sema_init(&sem, 1);
	init_waitqueue_head(&wq);
	affine_setup_cdev(affine_device, 0);

	/* create affine class */
	paffine_class = class_create(THIS_MODULE, AFFINE_NAME);
	if (IS_ERR(paffine_class)) {
		ret = PTR_ERR(paffine_class);
		pr_err("%s: class_create failed.\n", AFFINE_NAME);
		goto err4;
	}

	/* create device structure */
	affine_device->device =
	    device_create(paffine_class, NULL, dev, NULL, AFFINE_NAME);
	if (IS_ERR(affine_device->device)) {
		ret = PTR_ERR(affine_device->device);
		pr_err("%s: device_create failed.\n", AFFINE_NAME);
		goto err5;
	}

	pm_runtime_enable(&pdev->dev);

	pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
		AFFINE_NAME, DRV_AFFINE_VERSION_STR, MAJOR(dev), MINOR(dev));

	return 0;

err5:
	class_destroy(paffine_class);
err4:
	cdev_del(&affine_device->cdev);
err3:
	iounmap(affine_device->reg_base);
err2:
	release_mem_region(AFFINE_BASE, AFFINE_SIZE);
err1:
	kfree(affine_device);
err0:
	unregister_chrdev_region(dev, affine_nr_devs);

	return ret;
}

static int __devexit affine_remove(struct platform_device *pdev)
{
	dev_t dev = MKDEV(affine_major, affine_minor);

	if (affine_device) {

		/* reset device */
		affine_runtime_resume(&pdev->dev);
		affine_reset(affine_device);
		affine_runtime_suspend(&pdev->dev);

		device_destroy(paffine_class, dev);
		class_destroy(paffine_class);
		cdev_del(&affine_device->cdev);
		free_irq(affine_irq, affine_device);
		iounmap(affine_device->reg_base);
		release_mem_region(AFFINE_BASE, AFFINE_SIZE);
		kfree(affine_device);
	}
	pm_runtime_disable(&pdev->dev);
	platform_set_drvdata(pdev, NULL);

	unregister_chrdev_region(dev, affine_nr_devs);

	pr_info("%s: exit\n", AFFINE_NAME);

	return 0;
}

static int affine_suspend(struct device *dev)
{
	int ret = 0;

	if (atomic_read(&refcount) > 0) {
		ret = -EBUSY;
	}

	pr_debug("%s: %s: %d\n", AFFINE_NAME, __func__, ret);

	return ret;
}

static int affine_resume(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops affine_pm_ops = {
	.suspend = affine_suspend,
	.resume = affine_resume,
	.runtime_suspend = affine_runtime_suspend,
	.runtime_resume = affine_runtime_resume,
};

static struct platform_driver affine_driver = {
	.driver = {
		   .name = "irecog_affine",
		   .owner = THIS_MODULE,
		   .pm = &affine_pm_ops,
		   },
	.probe = affine_probe,
	.remove = affine_remove,
};

static int __init affine_init(void)
{
	return platform_driver_register(&affine_driver);
}

static void __exit affine_exit(void)
{
	platform_driver_unregister(&affine_driver);
}

module_init(affine_init);
module_exit(affine_exit);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_VERSION(DRV_AFFINE_VERSION_STR);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("AFFINE HWE module");
