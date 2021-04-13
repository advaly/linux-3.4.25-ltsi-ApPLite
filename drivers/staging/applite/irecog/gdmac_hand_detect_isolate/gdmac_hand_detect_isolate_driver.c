/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/gdmac_hand_detect_isolate_dirver.c
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
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/wait.h>
#include <asm/page.h>
#include <linux/sched.h>
#include <linux/semaphore.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/platform_data/applite_irecog.h>

#include <linux/applite/irecog/gdmac_hand_detect_isolate_ioctl.h>

#include "filter_public.h"
#include "hog_public.h"
#include "hog.h"
#include "drv_defs.h"

#include "gdmac_public.h"
#include "gdmac_hand_detect_isolate_driver.h"
#include "gdmac_instructions.h"

#include "hand_detect_isolate.h"
#include "mailbox_public.h"
#include "drv_cache.h"
#include "drv_signal.h"
#include "drv_polling.h"

#define INST_BUF_SIZE 65536
#define WORK_BUF_SIZE  4096
#define REG_BUF_SIZE   1024

#define STATUS_POLL_MAX 1000

static const char *drv_gdmac_hand_detect_isolate_version =
    DRV_GDMAC_HAND_DETECT_ISOLATE_VERSION_STR;

static int gdmac_hand_detect_isolate_major = GDMAC_HAND_DETECT_ISOLATE_MAJOR;
static int gdmac_hand_detect_isolate_minor = GDMAC_HAND_DETECT_ISOLATE_MINOR;
static int gdmac_hand_detect_isolate_nr_devs =
    GDMAC_HAND_DETECT_ISOLATE_NR_DEVS;
static int gdmac_hand_detect_isolate_irq = GDMAC_EVENT_IRQ1;

module_param(gdmac_hand_detect_isolate_major, int, S_IRUGO | S_IWUSR);
module_param(gdmac_hand_detect_isolate_minor, int, S_IRUGO | S_IWUSR);
module_param(gdmac_hand_detect_isolate_nr_devs, int, S_IRUGO | S_IWUSR);
module_param(gdmac_hand_detect_isolate_irq, int, S_IRUGO | S_IWUSR);

typedef enum {
	STATE_IDLE,
	STATE_RUNNING,
} state_t;

struct gdmac_hand_detect_isolate_dev {

	struct cdev cdev;
	struct device *device;
	struct platform_device *pdev;
	void __iomem *gdmac_reg_base;
	void __iomem *mailbox_reg_base;
	void __iomem *filter_reg_base;
	void __iomem *hog0_reg_base;
	void __iomem *hog1_reg_base;

	struct hog_dev hog[2];
	struct dict_dev dict;
	struct filter_dev filter;
	gdmac_inst *inst[MAX_TRANS_NUM];
	int trans_cnt;
	int trans_num;
	ULONG buffer_cache_ctl;
};

static state_t gdmac_state = STATE_IDLE;
static wait_queue_head_t wq;
static struct semaphore sem;
static struct gdmac_hand_detect_isolate_dev *ctrl_dev;
static struct class *pgdmac_hand_detect_isolate_class;
static atomic_t refcount = ATOMIC_INIT(0);

static int check_cache_param(ULONG flag)
{
	if (flag != DRV_CACHE_FLUSH_ALL) {
		pr_err("%s: invalid buffer_cache_ctl:%lu\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME, flag);
		return -1;
	}

	return 0;
}

/* tasklet */
static void gdmac_tasklet_func(unsigned long data);
static DECLARE_TASKLET(gdmac_tasklet, gdmac_tasklet_func, (unsigned long)NULL);

static int initialize_hwe(struct gdmac_hand_detect_isolate_dev *dev);

static int gdmac_hand_detect_isolate_runtime_suspend(struct device *dev)
{
	unsigned int ret;
	struct platform_data *pdata = dev->platform_data;
	struct platform_device *pdev = to_platform_device(dev);
	struct gdmac_hand_detect_isolate_dev *priv = platform_get_drvdata(pdev);
	unsigned long bits;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	/* filter */
	iowrite32(0x0,
		  priv->filter_reg_base +
		  FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	ret =
	    drv_wait_register(priv->filter_reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS),
			      IRECOG_RFILTER_CMD_CMD_MASK, 0x00,
			      DRV_WAIT_REG_TIMEOUT);
	if ((ret & IRECOG_RFILTER_CMD_CMD_MASK) != 0x0) {
		pr_err("%s: timeout occured\n", GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -EIO;
	}

	bits = IRECOG_RFILTER_TRNSSTAT_PT_MASK |
	    IRECOG_RFILTER_TRNSSTAT_OIT_MASK | IRECOG_RFILTER_TRNSSTAT_IIT_MASK;
	ret = drv_wait_register(priv->filter_reg_base +
				FILTER_OFFSET(IRECOG_rfilter_TRNSSTAT_OFFS),
				bits, 0x00, DRV_WAIT_REG_TIMEOUT);
	if ((ret & bits) != 0x0) {
		pr_err("%s: timeout occured\n", GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -EIO;
	}

	/* hog */
	iowrite32(IRECOG_RCOHOG0_CONTROL_REGISTER_RST_MASK,
		  priv->hog0_reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));

	ret = drv_wait_register(priv->hog0_reg_base +
				HOG_OFFSET
				(IRECOG_rcohog0_Control_Register_OFFS),
				IRECOG_RCOHOG0_CONTROL_REGISTER_CMD_MASK, 0x00,
				DRV_WAIT_REG_TIMEOUT);
	if ((ret & IRECOG_RCOHOG0_CONTROL_REGISTER_CMD_MASK) != 0x0) {
		pr_err("%s: timeout occured\n", GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -EIO;
	}

	iowrite32(IRECOG_RCOHOG1_CONTROL_REGISTER_RST_MASK,
		  priv->hog1_reg_base +
		  HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));

	ret = drv_wait_register(priv->hog1_reg_base +
				HOG_OFFSET
				(IRECOG_rcohog0_Control_Register_OFFS),
				IRECOG_RCOHOG1_CONTROL_REGISTER_CMD_MASK, 0x00,
				DRV_WAIT_REG_TIMEOUT);
	if ((ret & IRECOG_RCOHOG1_CONTROL_REGISTER_CMD_MASK) != 0x0) {
		pr_err("%s: timeout occured\n", GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -EIO;
	}

	clock_enable(APPLITE_IRECOG_HOG | APPLITE_IRECOG_FILTER,
		     APPLITE_IRECOG_CLOCK_DISABLE);
	return 0;
}

static int gdmac_hand_detect_isolate_runtime_resume(struct device *dev)
{
	struct platform_data *pdata = dev->platform_data;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	clock_enable(APPLITE_IRECOG_HOG | APPLITE_IRECOG_FILTER,
		     APPLITE_IRECOG_CLOCK_ENABLE);
	return 0;
}

#ifdef ENABLE_QEMU_FPARAM
/**************************************************/
/*
 * @brief mmap_fparam_qemu
 *
 * @param dev
 *
 */
/**************************************************/
static int mmap_fparam_qemu(struct filter_dev *dev)
{
	if (dev->param_base) {
		iounmap(dev->param_base);
	}

	/* get param size */
	dev->param_base = ioremap(FILTER_FW_IMAGE, 4);
	if (!dev->param_base) {
		goto err;
	}
	dev->param_size = ioread32(dev->param_base);
	iounmap(dev->param_base);

	dev->param_base = ioremap(FILTER_FW_IMAGE, dev->param_size);
	if (!dev->param_base) {
		goto err;
	}

	return 0;

err:
	return -1;
}
#endif

/**************************************************/
/*
 * @brief clear_int
 *
 * @param dev
 *
 */
/**************************************************/
static void clear_int(struct gdmac_hand_detect_isolate_dev *dev)
{
	int val;

	val = ioread32(dev->gdmac_reg_base + DMA330_INTEN);
	iowrite32(val | 0x00000002, dev->gdmac_reg_base + DMA330_INTEN);

	iowrite32(0x00000002, dev->gdmac_reg_base + DMA330_INTCLR);
}

/**************************************************/
/*
 * @brief reset_device
 *
 * @param dev
 *
 * @retval 0
 * @retval -1
 *
 */
/**************************************************/
static int reset_device(struct gdmac_hand_detect_isolate_dev *dev)
{
	int cnt;
	unsigned int ret;

	/* check dma330 debug status */
	cnt = 0;
	ret = drv_wait_register(dev->gdmac_reg_base + DMA330_DBGSTATUS,
				0xffffffff, 0x0, DRV_WAIT_REG_TIMEOUT);
	if (ret != 0x0) {
		pr_err("%s:gdmac invalid status.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -1;
	}

	/* filter reset */
	cnt = 0;
	iowrite32(0x1,
		  dev->filter_reg_base +
		  FILTER_OFFSET(IRECOG_rfilter_RST_OFFS));
	ret =
	    drv_wait_register(dev->filter_reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_RST_OFFS),
			      0xffffffff, 0x0, DRV_WAIT_REG_TIMEOUT);
	if (ret != 0x0) {
		pr_err("%s:filter reset failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -1;
	}
	cnt = 0;
	iowrite32(0x0,
		  dev->filter_reg_base +
		  FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	ret =
	    drv_wait_register(dev->filter_reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS),
			      0xffffffff, 0x0, DRV_WAIT_REG_TIMEOUT);
	if (ret != 0x0) {
		pr_err("%s:filter reset failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -1;
	}
	iowrite32(0x1,
		  dev->filter_reg_base +
		  FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	ret =
	    drv_wait_register(dev->filter_reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS),
			      0xffffffff, 0x1, DRV_WAIT_REG_TIMEOUT);
	if (ret != 0x1) {
		pr_err("%s:filter reset failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -1;
	}

	return 0;
}

/**************************************************/
/*
 * @briefgdmac_tasklet_func
 *
 * @return
 */
/**************************************************/
static void gdmac_tasklet_func(unsigned long data)
{
	if (++ctrl_dev->trans_cnt < ctrl_dev->trans_num) {
		reset_device(ctrl_dev);
		gdmac_exec_instructions(ctrl_dev->gdmac_reg_base, 0,
					ctrl_dev->inst[ctrl_dev->trans_cnt],
					ctrl_dev->buffer_cache_ctl);

	} else {
		gdmac_state = STATE_IDLE;
		wake_up_interruptible(&wq);
	}
}

/**************************************************/
/*
 * @brief isolate_isr
 *
 * @param irq
 * @param dev
 *
 * @return
 */
/**************************************************/
static irqreturn_t isolate_isr(int irq, void *dev_id)
{
	struct gdmac_hand_detect_isolate_dev *dev = dev_id;

	clear_int(dev);

	tasklet_hi_schedule(&gdmac_tasklet);

	return IRQ_HANDLED;
}

/**************************************************/
/*
 * @brief gdmac_hand_detect_isolate_open
 *
 * @param inode
 * @param filp
 *
 * @retval 0  success
 * @retval -1 fail
 */
/**************************************************/
static int gdmac_hand_detect_isolate_open(struct inode *inode,
					  struct file *filp)
{
	struct gdmac_hand_detect_isolate_dev *dev;

	dev =
	    container_of(inode->i_cdev, struct gdmac_hand_detect_isolate_dev,
			 cdev);
	filp->private_data = dev;

	if (atomic_inc_return(&refcount) == 1) {
		gdmac_hand_detect_isolate_runtime_resume(&dev->pdev->dev);
	}
	return 0;
}

/**************************************************/
/*
 * @brief gdmac_hand_detect_isolate_release
 *
 * @param inode
 * @param filp
 *
 * @retval 0  success
 * @retval -1 fail
 */
/**************************************************/
static int gdmac_hand_detect_isolate_release(struct inode *inode,
					     struct file *filp)
{
	struct gdmac_hand_detect_isolate_dev *dev;

	dev =
	    container_of(inode->i_cdev, struct gdmac_hand_detect_isolate_dev,
			 cdev);

	if (atomic_dec_return(&refcount) == 0) {
		gdmac_hand_detect_isolate_runtime_suspend(&dev->pdev->dev);
	}
	return 0;
}

/**************************************************/
/*
 * @brief execute
 *
 * @param dev
 * @param param
 *
 * @retval 0  success
 * @retval -1 fail
 */
/**************************************************/
static int execute(struct gdmac_hand_detect_isolate_dev *dev,
		   gdmac_hand_detect_isolate *param)
{
	/* DMAKILL ch0 */
	gdmac_exec_dmakill_slave(dev->gdmac_reg_base, 0);

	clear_int(dev);
	reset_device(dev);

	/* cache */
	if (param->buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
#if 0
		/* hand_detect_isolate_cache_flush(param); */
		/* hand_detect_isolate_cache_invalidate(param); */
#else
		drv_cache_flush_all();
#endif
	}

	/* kick ch0 */
	dev->trans_cnt = 0;
	dev->trans_num = (param->layer_max - param->layer_min + 1) + 1;	/* (filter int)*layer_num + hog int  */
	gdmac_state = STATE_RUNNING;
	dev->buffer_cache_ctl = param->buffer_cache_ctl;
	gdmac_exec_instructions(dev->gdmac_reg_base, 0,
				dev->inst[dev->trans_cnt],
				dev->buffer_cache_ctl);

	return 0;
}

/**************************************************/
/*
 * @brief mask_cpuint
 *
 * @param dev
 *
 */
/**************************************************/
static void mask_cpuint(struct gdmac_hand_detect_isolate_dev *dev)
{
	disable_irq(FILTER_IRQ);
	disable_irq(HOG0_IRQ);
	disable_irq(HOG1_IRQ);
}

/**************************************************/
/*
 * @brief unmask_cpuint
 *
 * @param dev
 *
 */
/**************************************************/
static void unmask_cpuint(struct gdmac_hand_detect_isolate_dev *dev)
{
	enable_irq(FILTER_IRQ);
	enable_irq(HOG0_IRQ);
	enable_irq(HOG1_IRQ);
}

/**************************************************/
/*
 * @brief mmap_gdmac_register
 *
 * @param dev
 * @param reg_type
 *
 */
/**************************************************/
static int32_t mmap_gdmac_register(struct gdmac_hand_detect_isolate_dev *dev,
				   uint32_t reg_type)
{
	uint32_t reg_base;

	if (reg_type == GDMAC_HAND_DETECT_ISOLATE_REG_TYPE_SECURE) {
		reg_base = GDMAC_BASE;
	} else if (reg_type == GDMAC_HAND_DETECT_ISOLATE_REG_TYPE_NON_SECURE) {
		reg_base = GDMAC_NONSECURE_BASE;
	} else {
		pr_err("%s: imvalid gdmac reg type.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		goto err;
	}

	if (dev->gdmac_reg_base) {
		iounmap(ctrl_dev->gdmac_reg_base);
	}

	dev->gdmac_reg_base = ioremap_nocache(reg_base, GDMAC_SIZE);
	if (!dev->gdmac_reg_base) {
		pr_err("%s: ioremap gdmac failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		goto err;
	}

	return 0;

err:
	return -1;
}

/**************************************************/
/*
 * @brief gdmac_hand_detect_isolate_ioctl
 *
 * @param filp
 * @param cmd
 * @param val
 *
 * @retval 0 success
 *
 */
/**************************************************/
static long gdmac_hand_detect_isolate_ioctl(struct file *filp, unsigned int cmd,
					    unsigned long val)
{
	struct gdmac_hand_detect_isolate_dev *dev = filp->private_data;
	uint32_t ret = 0;
	gdmac_hand_detect_isolate param;
	sigset_t oldset;
	int32_t mode;

	switch (cmd) {

	case GDMAC_IOCTL_HAND_DETECT_ISOLATE:
	case GDMAC_IOCTL_HAND_DETECT_ISOLATE_REGION:

		if (cmd == GDMAC_IOCTL_HAND_DETECT_ISOLATE) {
			mode = ROI_MODE;
		} else if (cmd == GDMAC_IOCTL_HAND_DETECT_ISOLATE_REGION) {
			mode = REGION_MODE;
		} else {
			pr_err("%s: invalid cmd.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			return -EFAULT;
		}

		if (copy_from_user
		    ((void *)&param, (const void __user *)val,
		     sizeof(gdmac_hand_detect_isolate))) {
			pr_err("%s: copy_from_user fail.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			return -EFAULT;
		}
		if (hand_detect_isolate_parameter_check(&param, mode) < 0) {
			pr_err("%s: invalid parameter.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			return -EINVAL;
		}
		if (check_cache_param(param.buffer_cache_ctl) < 0) {
			return -EINVAL;
		}

		if (down_interruptible(&sem)) {
			pr_err("%s: down_interruptible failed.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			return -ERESTARTSYS;
		}
		if (gdmac_state != STATE_IDLE) {
			pr_err("%s: invalid state.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			up(&sem);
			return -EAGAIN;
		}

		if (param.hand_num == HAND_NUM_BOTH) {
			hand_detect_isolate_create_instructions(dev->inst,
								dev->hog,
								&dev->dict,
								&dev->filter,
								&param, mode);
		} else if ((param.hand_num == HAND_NUM_ONE)
			   && (param.dict_bank_mode == HOG_DICT_BANK_MODE1)) {
			hand_detect_isolate_create_instructions_one_hand
			    (dev->inst, dev->hog, &dev->dict, &dev->filter,
			     &param, mode);
		} else if ((param.hand_num == HAND_NUM_ONE)
			   && (param.dict_bank_mode == HOG_DICT_BANK_MODE0)) {
			hand_detect_isolate_create_instructions_single
			    (dev->inst, dev->hog, &dev->dict, &dev->filter,
			     &param, mode);
		}

		mask_cpuint(dev);

		/* execute */
		if (execute(dev, &param) < 0) {
			pr_err("%s: execute fail.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			unmask_cpuint(dev);
			up(&sem);
			return -EINVAL;
		}

		/* signak mask */
		drv_sigmask(&oldset);
		/* wait */
		if (wait_event_interruptible(wq, (gdmac_state == STATE_IDLE))) {

			/* signak unmask */
			drv_sigunmask(&oldset);

			pr_err("%s: wait_event_interruptible fail.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);

			gdmac_state = STATE_IDLE;

			tasklet_kill(&gdmac_tasklet);
			unmask_cpuint(dev);
			up(&sem);

			return -ERESTARTSYS;
		}
		/* signak unmask */
		drv_sigunmask(&oldset);

		tasklet_kill(&gdmac_tasklet);
		unmask_cpuint(dev);
		up(&sem);

		break;

	case GDMAC_IOCTL_HAND_DETECT_ISOLATE_GET_VERSION:
		{
			drv_version_t version_param;

			memset(&version_param, 0x00, sizeof(drv_version_t));
			memcpy(version_param.version,
			       drv_gdmac_hand_detect_isolate_version,
			       strlen(drv_gdmac_hand_detect_isolate_version));

			if (copy_to_user((void __user *)val,
					 (void *)&version_param,
					 sizeof(drv_version_t))) {
				pr_err("%s: copy_to_user failed version\n",
				       GDMAC_HAND_DETECT_ISOLATE_NAME);
				return -EFAULT;
			}
		}
		break;

	case GDMAC_IOCTL_HAND_DETECT_ISOLATE_SET_FPARAM_ADDR:
		{
			uint32_t fparam_base;

			if (copy_from_user
			    ((void *)&fparam_base, (const void __user *)val,
			     sizeof(uint32_t))) {
				pr_err
				    ("%s: copy_from_user failed set_fparam_addr.\n",
				     GDMAC_HAND_DETECT_ISOLATE_NAME);
				return -EFAULT;
			}
#ifndef ENABLE_QEMU_FPARAM
			dev->filter.param_base =
			    (void __iomem *)phys_to_virt(fparam_base);
			dev->filter.param_size =
			    *(uint32_t *)(unsigned long)dev->filter.param_base;
#endif
		}
		break;

	case GDMAC_IOCTL_HAND_DETECT_ISOLATE_SET_REG_TYPE:
		{
			uint32_t reg_type = 0;

			if (copy_from_user
			    ((void *)&reg_type, (const void __user *)val,
			     sizeof(uint32_t))) {
				pr_err("%s: copy_from_user failed.\n",
				       GDMAC_HAND_DETECT_ISOLATE_NAME);
				return -EFAULT;
			}

			if (mmap_gdmac_register(ctrl_dev, reg_type) != 0) {
				pr_err("%s: mmap_gdmac_register failed.\n",
				       GDMAC_HAND_DETECT_ISOLATE_NAME);
				return -EFAULT;
			}
		}
		break;

	case GDMAC_IOCTL_HAND_DETECT_ISOLATE_INITIALIZE:
		if (initialize_hwe(dev) != 0) {
			pr_err("%s: initialize failed.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			return -EFAULT;
		}
#ifdef ENABLE_QEMU_FPARAM
		if (mmap_fparam_qemu(&dev->filter) != 0) {
			pr_err("%s: initialize(mmap) failed.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			return -EFAULT;
		}
#endif
		break;

		/* invalid command */
	default:
		pr_err("%s: invalid ioctl command 0x%0x\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME, cmd);
		return -EINVAL;
		break;
	}

	return ret;
}

static const struct file_operations gdmac_hand_detect_isolate_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = gdmac_hand_detect_isolate_ioctl,
	.open = gdmac_hand_detect_isolate_open,
	.release = gdmac_hand_detect_isolate_release,
};

/**************************************************/
/*
 * @brief setup_cdev
 *
 * @param dev
 * @param index
 *
 */
/**************************************************/
static void setup_cdev(struct gdmac_hand_detect_isolate_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(gdmac_hand_detect_isolate_major,
			    gdmac_hand_detect_isolate_minor + index);

	cdev_init(&dev->cdev, &gdmac_hand_detect_isolate_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev %d\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME, index);
	}
}

/**************************************************/
/*
 * @brief initialize_hwe
 *
 * @param dev
 *
 */
/**************************************************/
static int initialize_hwe(struct gdmac_hand_detect_isolate_dev *dev)
{
	struct resource *retval;
	void __iomem *reg_base;
	unsigned int ret;

	/* filter reset */
	iowrite32(0x1,
		  dev->filter_reg_base +
		  FILTER_OFFSET(IRECOG_rfilter_RST_OFFS));
	ret =
	    drv_wait_register(dev->filter_reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_RST_OFFS), 0x1, 0x0,
			      DRV_WAIT_REG_TIMEOUT);
	if ((ret & 0x1) != 0x0) {
		pr_err("%s: filter reset failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		return -1;
	}

	/* reset hog0 */
	retval =
	    request_mem_region(HOG0_BASE, HOG0_SIZE,
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
	if (!retval) {
		/* pr_err("%s: request_mem_region hog0 failed.\n", GDMAC_HAND_DETECT_ISOLATE_NAME); */
	}
	reg_base = ioremap_nocache(HOG0_BASE, HOG0_SIZE);
	if (!reg_base) {
		pr_err("%s: ioremap hog0 failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		if (retval) {
			release_mem_region(HOG0_BASE, HOG0_SIZE);
		}
		return -1;
	}

	iowrite32(IRECOG_RCOHOG0_CONTROL_REGISTER_RST_MASK,
		  reg_base + HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));

	iounmap(reg_base);
	if (retval) {
		release_mem_region(HOG0_BASE, HOG0_SIZE);
	}

	/* reset hog1 */
	retval =
	    request_mem_region(HOG1_BASE, HOG1_SIZE,
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
	if (!retval) {
		/* pr_err("%s: request_mem_region hog1 failed.\n", GDMAC_HAND_DETECT_ISOLATE_NAME); */
	}
	reg_base = ioremap_nocache(HOG1_BASE, HOG1_SIZE);
	if (!reg_base) {
		pr_err("%s: ioremap hog1 failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		if (retval) {
			release_mem_region(HOG0_BASE, HOG0_SIZE);
		}
		return -1;
	}

	iowrite32(IRECOG_RCOHOG0_CONTROL_REGISTER_RST_MASK,
		  reg_base + HOG_OFFSET(IRECOG_rcohog0_Control_Register_OFFS));

	iounmap(reg_base);
	if (retval) {
		release_mem_region(HOG1_BASE, HOG1_SIZE);
	}

	/* reset mailbox */
	iowrite32(MAILBOX_SEL_PYRAMID, dev->mailbox_reg_base + MBOX_INT_SEL0_OFFS);	/* 24 */
	iowrite32(MAILBOX_SEL_CVIA, dev->mailbox_reg_base + MBOX_INT_SEL1_OFFS);	/* 25 */
	iowrite32(MAILBOX_SEL_COHOG0, dev->mailbox_reg_base + MBOX_INT_SEL2_OFFS);	/* 26 */
	iowrite32(MAILBOX_SEL_COHOG1, dev->mailbox_reg_base + MBOX_INT_SEL3_OFFS);	/* 27 */

	return 0;
}

/**************************************************/
/*
 * @brief gdmac_hand_detect_isolate_probe
 *
 * @retval 0  success
 */
/**************************************************/
static int __devinit
gdmac_hand_detect_isolate_probe(struct platform_device *pdev)
{
	int i;
	int ret;
	dev_t dev = 0;

	/* allocation of device number */
	if (gdmac_hand_detect_isolate_major) {
		dev =
		    MKDEV(gdmac_hand_detect_isolate_major,
			  gdmac_hand_detect_isolate_minor);
		ret =
		    register_chrdev_region(dev,
					   gdmac_hand_detect_isolate_nr_devs,
					   GDMAC_HAND_DETECT_ISOLATE_NAME);
	} else {
		ret =
		    alloc_chrdev_region(&dev, gdmac_hand_detect_isolate_minor,
					gdmac_hand_detect_isolate_nr_devs,
					GDMAC_HAND_DETECT_ISOLATE_NAME);
		gdmac_hand_detect_isolate_major = MAJOR(dev);
	}
	if (ret < 0) {
		pr_err("%s: can't get major %d\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME,
		       gdmac_hand_detect_isolate_major);
		return ret;
	}

	ctrl_dev =
	    kmalloc(sizeof(struct gdmac_hand_detect_isolate_dev), GFP_KERNEL);
	if (!ctrl_dev) {
		pr_err("%s: kmalloc failed\n", GDMAC_HAND_DETECT_ISOLATE_NAME);
		ret = -ENOMEM;
		goto err0;
	}
	memset(ctrl_dev, 0, sizeof(struct gdmac_hand_detect_isolate_dev));
	ctrl_dev->pdev = pdev;
	platform_set_drvdata(pdev, ctrl_dev);

	/* gdmac register */
	if (mmap_gdmac_register
	    (ctrl_dev, GDMAC_HAND_DETECT_ISOLATE_REG_TYPE_SECURE) != 0) {
		pr_err("%s: ioremap gdmac failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		ret = -ENODEV;
		goto err1;
	}

	/* irq */
	ret =
	    request_irq(gdmac_hand_detect_isolate_irq, isolate_isr, IRQF_SHARED,
			GDMAC_HAND_DETECT_ISOLATE_NAME, ctrl_dev);
	if (ret < 0) {
		pr_err("%s: request_irq failed\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		goto err2;
	}

	/* mailbox */
	ctrl_dev->mailbox_reg_base =
	    ioremap_nocache(MAILBOX_BASE, MAILBOX_SIZE);
	if (!ctrl_dev->mailbox_reg_base) {
		pr_err("%s: ioremap mailbox failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		ret = -ENODEV;
		goto err3;
	}

	/* filter */
	ctrl_dev->filter_reg_base = ioremap_nocache(FILTER_BASE, FILTER_SIZE);
	if (!ctrl_dev->filter_reg_base) {
		pr_err("%s: ioremap filter failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		goto err4;
	}

	/* hog */
	ctrl_dev->hog0_reg_base = ioremap_nocache(HOG0_BASE, HOG0_SIZE);
	if (!ctrl_dev->hog0_reg_base) {
		pr_err("%s: ioremap filter failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		goto err5;
	}
	ctrl_dev->hog1_reg_base = ioremap_nocache(HOG1_BASE, HOG1_SIZE);
	if (!ctrl_dev->hog1_reg_base) {
		pr_err("%s: ioremap filter failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		goto err6;
	}

	sema_init(&sem, 1);
	init_waitqueue_head(&wq);

	setup_cdev(ctrl_dev, 0);

	/* allocate instruction memory */
	for (i = 0; i < MAX_TRANS_NUM; i++) {
		ctrl_dev->inst[i] =
		    gdmac_allocate(INST_BUF_SIZE, WORK_BUF_SIZE, REG_BUF_SIZE);
		if (ctrl_dev->inst[i] == NULL) {
			pr_err("%s: gdmac_allocate failed.\n",
			       GDMAC_HAND_DETECT_ISOLATE_NAME);
			ret = -ENOMEM;
			goto err7;
		}
	}

	/* initialize */
	if (hand_detect_isolate_initialize
	    (ctrl_dev->hog, &ctrl_dev->dict, &ctrl_dev->filter) < 0) {
		pr_err("%s: hand_detect_isolate_initialize failed.\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		ret = -ENOMEM;
		goto err8;
	}

	/* create gdmac_hand_detect_isolate class */
	pgdmac_hand_detect_isolate_class =
	    class_create(THIS_MODULE, GDMAC_HAND_DETECT_ISOLATE_NAME);
	if (IS_ERR(pgdmac_hand_detect_isolate_class)) {
		ret = PTR_ERR(pgdmac_hand_detect_isolate_class);
		pr_err("%s: class_create failed\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		goto err9;
	}

	/* create device structure */
	ctrl_dev->device =
	    device_create(pgdmac_hand_detect_isolate_class, NULL, dev, NULL,
			  GDMAC_HAND_DETECT_ISOLATE_NAME);
	if (IS_ERR(ctrl_dev->device)) {
		ret = PTR_ERR(ctrl_dev->device);
		pr_err("%s: device_create failed\n",
		       GDMAC_HAND_DETECT_ISOLATE_NAME);
		goto err10;
	}

	pm_runtime_enable(&pdev->dev);

	pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
		GDMAC_HAND_DETECT_ISOLATE_NAME,
		DRV_GDMAC_HAND_DETECT_ISOLATE_VERSION_STR,
		MAJOR(dev), MINOR(dev));
	return 0;

err10:
	class_destroy(pgdmac_hand_detect_isolate_class);
err9:
	cdev_del(&ctrl_dev->cdev);
err8:
	for (i = 0; i < MAX_TRANS_NUM; i++) {
		if (ctrl_dev->inst[i] != NULL) {
			gdmac_free(ctrl_dev->inst[i]);
		}
	}
err7:
	iounmap(ctrl_dev->hog1_reg_base);
err6:
	iounmap(ctrl_dev->hog0_reg_base);
err5:
	iounmap(ctrl_dev->filter_reg_base);
err4:
	iounmap(ctrl_dev->mailbox_reg_base);
err3:
	free_irq(gdmac_hand_detect_isolate_irq, ctrl_dev);
err2:
	iounmap(ctrl_dev->gdmac_reg_base);
err1:
	kfree(ctrl_dev);
err0:
	unregister_chrdev_region(dev, gdmac_hand_detect_isolate_nr_devs);

	return ret;
}

/**************************************************/
/*
 * @brief gdmac_hand_detect_isolate_remove
 *
 */
/**************************************************/
static int __devexit
gdmac_hand_detect_isolate_remove(struct platform_device *pdev)
{
	int i;
	dev_t dev = MKDEV(gdmac_hand_detect_isolate_major,
			  gdmac_hand_detect_isolate_minor);

	hand_detect_isolate_finalize();

	tasklet_kill(&gdmac_tasklet);

	if (ctrl_dev) {
		device_destroy(pgdmac_hand_detect_isolate_class, dev);
		class_destroy(pgdmac_hand_detect_isolate_class);

		cdev_del(&ctrl_dev->cdev);

#ifdef ENABLE_QEMU_FPARAM
		iounmap(ctrl_dev->filter.param_base);
#endif

		iounmap(ctrl_dev->gdmac_reg_base);
		iounmap(ctrl_dev->mailbox_reg_base);
		iounmap(ctrl_dev->filter_reg_base);
		iounmap(ctrl_dev->hog0_reg_base);
		iounmap(ctrl_dev->hog1_reg_base);

		for (i = 0; i < MAX_TRANS_NUM; i++) {
			if (ctrl_dev->inst[i] != NULL) {
				gdmac_free(ctrl_dev->inst[i]);
			}
		}

		free_irq(gdmac_hand_detect_isolate_irq, ctrl_dev);
		kfree(ctrl_dev);
	}
	pm_runtime_disable(&pdev->dev);
	platform_set_drvdata(pdev, NULL);

	unregister_chrdev_region(dev, gdmac_hand_detect_isolate_nr_devs);

	pr_info("%s: exit\n", GDMAC_HAND_DETECT_ISOLATE_NAME);
	return 0;
}

static int gdmac_hand_detect_isolate_suspend(struct device *dev)
{
	int ret = 0;

	if (atomic_read(&refcount) > 0) {
		ret = -EBUSY;
	}

	pr_debug("%s: %s: %d\n", GDMAC_HAND_DETECT_ISOLATE_NAME, __func__, ret);

	return ret;
}

static int gdmac_hand_detect_isolate_resume(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops gdmac_hand_detect_isolate_pm_ops = {
	.suspend = gdmac_hand_detect_isolate_suspend,
	.resume = gdmac_hand_detect_isolate_resume,
	.runtime_suspend = gdmac_hand_detect_isolate_runtime_suspend,
	.runtime_resume = gdmac_hand_detect_isolate_runtime_resume,
};

static struct platform_driver gdmac_hand_detect_isolate_driver = {
	.driver = {
		   .name = "irecog_gdmac_hand_detect_isolate",
		   .owner = THIS_MODULE,
		   .pm = &gdmac_hand_detect_isolate_pm_ops,
		   },
	.probe = gdmac_hand_detect_isolate_probe,
	.remove = gdmac_hand_detect_isolate_remove,
};

static int __init gdmac_hand_detect_isolate_init(void)
{
	return platform_driver_register(&gdmac_hand_detect_isolate_driver);
}

static void __exit gdmac_hand_detect_isolate_exit(void)
{
	platform_driver_unregister(&gdmac_hand_detect_isolate_driver);
}

module_init(gdmac_hand_detect_isolate_init);
module_exit(gdmac_hand_detect_isolate_exit);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_VERSION(DRV_GDMAC_HAND_DETECT_ISOLATE_VERSION_STR);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("GDMAC Hand Detect Isolate module");
