/*
 * linux/drivers/staging/applite/irecog/gdmac_pyramid/gdmac_pyramid_driver.c
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

#include <linux/applite/irecog/gdmac_pyramid_ioctl.h>
#include <linux/applite/irecog/drv_cache_ctrl_defs.h>

#include "gdmac_public.h"
#include "gdmac_pyramid_driver.h"
#include "gdmac_instructions.h"

#include "pyramid.h"
#include "mailbox_public.h"
#include "gdmac_public.h"
#include "drv_defs.h"
#include "drv_cache.h"
#include "drv_signal.h"
#include "drv_polling.h"

#define INST_BUF_SIZE 4096
#define WORK_BUF_SIZE 4096
#define REG_BUF_SIZE  1024

#define STATUS_POLL_MAX 1000

static const char *drv_gdmac_pyramid_version = DRV_GDMAC_PYRAMID_VERSION_STR;

static int gdmac_pyramid_major = GDMAC_PYRAMID_MAJOR;
static int gdmac_pyramid_minor = GDMAC_PYRAMID_MINOR;
static int gdmac_pyramid_nr_devs = GDMAC_PYRAMID_NR_DEVS;
static int gdmac_pyramid_irq = GDMAC_EVENT_IRQ0;

module_param(gdmac_pyramid_major, int, S_IRUGO | S_IWUSR);
module_param(gdmac_pyramid_minor, int, S_IRUGO | S_IWUSR);
module_param(gdmac_pyramid_nr_devs, int, S_IRUGO | S_IWUSR);
module_param(gdmac_pyramid_irq, int, S_IRUGO | S_IWUSR);

typedef enum {
	STATE_IDLE,
	STATE_RUNNING,
} state_t;

struct gdmac_pyramid_dev {
	struct cdev cdev;
	struct device *device;
	struct platform_device *pdev;
	void __iomem *gdmac_reg_base;
	void __iomem *mailbox_reg_base;
	void __iomem *pyramid_reg_base;
	void __iomem *rvdmac_reg_base;
	void __iomem *rscaler_reg_base;
	gdmac_inst *inst;
};

static state_t gdmac_pyramid_state = STATE_IDLE;
static wait_queue_head_t wq;
static struct semaphore sem;
static struct gdmac_pyramid_dev *ctrl_dev;
static struct class *pgdmac_pyramid_class;
static atomic_t refcount = ATOMIC_INIT(0);

static int check_cache_param(unsigned long flag)
{
	if (flag != DRV_CACHE_FLUSH_ALL) {
		pr_err("%s: invalid buffer_cache_ctl:%lu\n", GDMAC_PYRAMID_NAME,
		       flag);
		return -1;
	}

	return 0;
}

static int gdmac_pyramid_runtime_suspend(struct device *dev)
{
	unsigned int ret;
	struct platform_data *pdata = dev->platform_data;
	struct platform_device *pdev = to_platform_device(dev);
	struct gdmac_pyramid_dev *priv = platform_get_drvdata(pdev);
	unsigned long bits;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	bits = IRECOG_RPYRAMID_PYM_R_RUN_RUN_R00_MASK |
	    IRECOG_RPYRAMID_PYM_R_RUN_RUN_R01_MASK |
	    IRECOG_RPYRAMID_PYM_R_RUN_RUN_R02_MASK;
	ret = drv_wait_register(priv->rvdmac_reg_base +
				IRECOG_rpyramid_PYM_R_RUN_OFFS,
				bits, 0x00, DRV_WAIT_REG_TIMEOUT);
	if ((ret & bits) != 0x0) {
		pr_err("%s: timeout occured\n", GDMAC_PYRAMID_NAME);
		return -EIO;
	}

	bits = IRECOG_RPYRAMID_PYM_W_RUN_RUN_W00_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W01_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W02_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W03_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W04_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W05_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W06_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W07_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W08_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W09_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W10_MASK |
	    IRECOG_RPYRAMID_PYM_W_RUN_RUN_W11_MASK;
	ret = drv_wait_register(priv->rvdmac_reg_base +
				IRECOG_rpyramid_PYM_W_RUN_OFFS,
				bits, 0x00, DRV_WAIT_REG_TIMEOUT);
	if ((ret & bits) != 0x0) {
		pr_err("%s: timeout occured\n", GDMAC_PYRAMID_NAME);
		return -EIO;
	}

	bits = IRECOG_RPYRAMID_PYM_T_RUN_RUN_TP00_MASK;
	ret = drv_wait_register(priv->rvdmac_reg_base +
				IRECOG_rpyramid_PYM_T_RUN_OFFS,
				bits, 0x00, DRV_WAIT_REG_TIMEOUT);
	if ((ret & bits) != 0x0) {
		pr_err("%s: timeout occured\n", GDMAC_PYRAMID_NAME);
		return -EIO;
	}

	clock_enable(APPLITE_IRECOG_PYRAMID, APPLITE_IRECOG_CLOCK_DISABLE);
	return 0;
}

static int gdmac_pyramid_runtime_resume(struct device *dev)
{
	struct platform_data *pdata = dev->platform_data;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	clock_enable(APPLITE_IRECOG_PYRAMID, APPLITE_IRECOG_CLOCK_ENABLE);
	return 0;
}

/**************************************************/
/*
 * @brief pyramid_ abort
 *
 * @param dev
 *
 */
/**************************************************/
static void pyramid_abort(struct gdmac_pyramid_dev *dev)
{
	iowrite32(0x01,
		  dev->rscaler_reg_base +
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_RESET_OFFS));
	iowrite32(0x01, dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_CTRL_OFFS);
}

static void initialize_hwe(struct gdmac_pyramid_dev *dev);
/**************************************************/
/*
 * @brief clear_int
 *
 * @param dev
 *
 */
/**************************************************/
static void clear_int(struct gdmac_pyramid_dev *dev)
{
	int val;

	val = ioread32(dev->gdmac_reg_base + DMA330_INTEN);
	iowrite32(val | 0x00000001, dev->gdmac_reg_base + DMA330_INTEN);

	iowrite32(0x00000001, dev->gdmac_reg_base + DMA330_INTCLR);
}

/**************************************************/
/*
 * @brief pyramid_isr
 *
 * @param irq
 * @param dev
 *
 * @return
 */
/**************************************************/
static irqreturn_t pyramid_isr(int irq, void *dev_id)
{
	struct gdmac_pyramid_dev *dev = dev_id;

	clear_int(dev);

	gdmac_pyramid_state = STATE_IDLE;
	wake_up_interruptible(&wq);

	return IRQ_HANDLED;
}

/**************************************************/
/*
 * @brief gdmac_pyramid_open
 *
 * @param inode
 * @param filp
 *
 * @retval 0  success
 * @retval -1 fail
 */
/**************************************************/
static int gdmac_pyramid_open(struct inode *inode, struct file *filp)
{
	struct gdmac_pyramid_dev *dev;

	dev = container_of(inode->i_cdev, struct gdmac_pyramid_dev, cdev);
	filp->private_data = dev;

	if (atomic_inc_return(&refcount) == 1) {
		gdmac_pyramid_runtime_resume(&dev->pdev->dev);
	}
	return 0;
}

/**************************************************/
/*
 * @brief gdmac_pyramid_release
 *
 * @param inode
 * @param filp
 *
 * @retval 0  success
 * @retval -1 fail
 */
/**************************************************/
static int gdmac_pyramid_release(struct inode *inode, struct file *filp)
{
	struct gdmac_pyramid_dev *dev;

	dev = container_of(inode->i_cdev, struct gdmac_pyramid_dev, cdev);

	if (atomic_dec_return(&refcount) == 0) {
		gdmac_pyramid_runtime_suspend(&dev->pdev->dev);
	}
	return 0;
}

/**************************************************/
/*
 * @brief execute
 *
 * @param dev
 * @param pyramid
 *
 * @retval 0  success
 * @retval -1 fail
 *
 */
/**************************************************/
static int execute(struct gdmac_pyramid_dev *dev, gdmac_pyramid *pyramid)
{
	int cnt = 0;

	/* DMAKILL ch0 */
	gdmac_exec_dmakill_slave(dev->gdmac_reg_base, 0);

	clear_int(dev);

	/* check dbg status register */
	while (ioread32(dev->gdmac_reg_base + DMA330_DBGSTATUS) != 0x0) {
		if (++cnt > STATUS_POLL_MAX) {
			pr_err("%s:gdmac invalid status.\n",
			       GDMAC_PYRAMID_NAME);
			return -1;
		}
	}

	/* cache */
	if (pyramid->buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
#if 0
		/* pyramid_cache_flush(pyramid); */
#else
		drv_cache_flush_all();
#endif
	}

	/* kick ch0 */
	gdmac_pyramid_state = STATE_RUNNING;
	gdmac_exec_instructions(dev->gdmac_reg_base, 0, dev->inst,
				pyramid->buffer_cache_ctl);

#if 0
	/* cache invalidate */
	/*pyramid_cache_invalidate(pyramid); */
#endif

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
static void mask_cpuint(struct gdmac_pyramid_dev *dev)
{
	disable_irq(PYRAMID_IRQ);
}

/**************************************************/
/*
 * @brief unmask_cpuint
 *
 * @param dev
 *
 */
/**************************************************/
static void unmask_cpuint(struct gdmac_pyramid_dev *dev)
{
	enable_irq(PYRAMID_IRQ);
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
static int32_t mmap_gdmac_register(struct gdmac_pyramid_dev *dev,
				   uint32_t reg_type)
{
	uint32_t reg_base;

	if (reg_type == GDMAC_PYRAMID_REG_TYPE_SECURE) {
		reg_base = GDMAC_BASE;
	} else if (reg_type == GDMAC_PYRAMID_REG_TYPE_NON_SECURE) {
		reg_base = GDMAC_NONSECURE_BASE;
	} else {
		pr_err("%s: invalid reg_type.\n", GDMAC_PYRAMID_NAME);
		goto err;
	}

	if (dev->gdmac_reg_base) {
		iounmap(ctrl_dev->gdmac_reg_base);
	}

	dev->gdmac_reg_base = ioremap_nocache(reg_base, GDMAC_SIZE);
	if (!dev->gdmac_reg_base) {
		pr_err("%s: ioremap gdmac failed.\n", GDMAC_PYRAMID_NAME);
		goto err;
	}

	return 0;

err:
	return -1;
}

/**************************************************/
/*
 * @brief gdmac_pyramid_ioctl
 *
 * @param filp
 * @param cmd
 * @param val
 *
 * @retval 0  success
 *
 */
/**************************************************/
static long gdmac_pyramid_ioctl(struct file *filp, unsigned int cmd,
				unsigned long val)
{
	struct gdmac_pyramid_dev *dev = filp->private_data;
	uint32_t ret = 0;
	gdmac_pyramid pyramid;
	sigset_t oldset;

	switch (cmd) {

	case GDMAC_IOCTL_PYRAMID_IMAGES:
		if (copy_from_user
		    ((void *)&pyramid, (const void __user *)val,
		     sizeof(gdmac_pyramid))) {
			pr_err("%s: copy_from_user fail.\n",
			       GDMAC_PYRAMID_NAME);
			return -EFAULT;
		}
		if (pyramid_parameter_check(&pyramid) < 0) {
			pr_err("%s: invalid parameter.\n", GDMAC_PYRAMID_NAME);
			return -EINVAL;
		}
		if (check_cache_param(pyramid.buffer_cache_ctl) < 0) {
			return -EINVAL;
		}

		if (down_interruptible(&sem)) {
			pr_err("%s: down_interruptibel fail.\n",
			       GDMAC_PYRAMID_NAME);
			return -ERESTARTSYS;
		}
		if (gdmac_pyramid_state != STATE_IDLE) {
			pr_err("%s: invalid state.\n", GDMAC_PYRAMID_NAME);
			up(&sem);
			return -EAGAIN;
		}

		pyramid_create_instructions(dev->inst, &pyramid);

		mask_cpuint(dev);

		/* execute */
		if (execute(dev, &pyramid) < 0) {
			pr_err("%s: execute fail.\n", GDMAC_PYRAMID_NAME);
			unmask_cpuint(dev);
			up(&sem);
			return -EINVAL;
		}

		/* signal amsk */
		drv_sigmask(&oldset);
		/* wait */
		if (wait_event_interruptible
		    (wq, (gdmac_pyramid_state == STATE_IDLE))) {
			/* signak unmask */
			drv_sigunmask(&oldset);

			pr_err("%s: wait_event_interruptible fail.\n",
			       GDMAC_PYRAMID_NAME);

			gdmac_pyramid_state = STATE_IDLE;
			pyramid_abort(dev);

			unmask_cpuint(dev);
			up(&sem);

			return -ERESTARTSYS;
		}
		/* signal unmask */
		drv_sigunmask(&oldset);
		unmask_cpuint(dev);
		up(&sem);

		break;

	case GDMAC_IOCTL_PYRAMID_GET_VERSION:
		{
			drv_version_t version_param;

			memset(&version_param, 0x00, sizeof(drv_version_t));
			memcpy(version_param.version, drv_gdmac_pyramid_version,
			       strlen(drv_gdmac_pyramid_version));

			if (copy_to_user((void __user *)val,
					 (void *)&version_param,
					 sizeof(drv_version_t))) {
				pr_err("%s: copy_to_user failed version\n",
				       GDMAC_PYRAMID_NAME);
				return -EFAULT;
			}
		}
		break;

	case GDMAC_IOCTL_PYRAMID_SET_REG_TYPE:
		{
			uint32_t reg_type = 0;

			if (copy_from_user
			    ((void *)&reg_type, (const void __user *)val,
			     sizeof(uint32_t))) {
				pr_err("%s: copy_from_user fail.\n",
				       GDMAC_PYRAMID_NAME);
				return -EFAULT;
			}

			if (mmap_gdmac_register(ctrl_dev, reg_type) != 0) {
				pr_err("%s: ioremap gdmac failed.\n",
				       GDMAC_PYRAMID_NAME);
				return -EFAULT;
			}
		}
		break;

	case GDMAC_IOCTL_PYRAMID_INITIALIZE:
		initialize_hwe(dev);
		break;

		/* invalid command */
	default:
		pr_err("%s: invalid ioctl command 0x%x\n", GDMAC_PYRAMID_NAME,
		       cmd);
		return -EINVAL;
		break;
	}

	return ret;
}

static const struct file_operations gdmac_pyramid_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = gdmac_pyramid_ioctl,
	.open = gdmac_pyramid_open,
	.release = gdmac_pyramid_release,
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
static void setup_cdev(struct gdmac_pyramid_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(gdmac_pyramid_major, gdmac_pyramid_minor + index);

	cdev_init(&dev->cdev, &gdmac_pyramid_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev %d\n", GDMAC_PYRAMID_NAME, index);
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
static void initialize_hwe(struct gdmac_pyramid_dev *dev)
{
	int i;

	/* reset mailbox */
	iowrite32(MAILBOX_SEL_PYRAMID, dev->mailbox_reg_base + MBOX_INT_SEL0_OFFS);	/* 24 */
	iowrite32(MAILBOX_SEL_CVIA, dev->mailbox_reg_base + MBOX_INT_SEL1_OFFS);	/* 25 */
	iowrite32(MAILBOX_SEL_COHOG0, dev->mailbox_reg_base + MBOX_INT_SEL2_OFFS);	/* 26 */
	iowrite32(MAILBOX_SEL_COHOG1, dev->mailbox_reg_base + MBOX_INT_SEL3_OFFS);	/* 27 */

	/* mbus setting */
	iowrite32(0x00000003,
		  dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_STATUS_OFFS);
	iowrite32(MBUS_STADR,
		  dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_STADR_OFFS);
	iowrite32(MBUS_ENDADR,
		  dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_ENDADR_OFFS);
	iowrite32(0x00070700,
		  dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_CFG_OFFS);

	/* mbus setting */
	iowrite32(0x00000000,
		  dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_T00_INTL_OFFS);
	for (i = 0; i < _PYM_R_NUM; i++) {
		iowrite32(0x00000000,
			  dev->rvdmac_reg_base +
			  IRECOG_rpyramid_PYM_R00_INTL_OFFS +
			  _PYM_R_INTERVAL * i);
	}
	for (i = 0; i < _PYM_W_NUM; i++) {
		iowrite32(0x00000000,
			  dev->rvdmac_reg_base +
			  IRECOG_rpyramid_PYM_W00_INTL_OFFS +
			  _PYM_W_INTERVAL * i);
	}
	/* interrupt mask setting */
	iowrite32(0x00000000,
		  dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_INT_MASK_OFFS);

	/* set configuration register0 */
	iowrite32(0x00000210, dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_T00_CFG_OFFS);	/* data bus:32bit */
	for (i = 0; i < _PYM_R_NUM; i++) {
		iowrite32(0x00000000,
			  dev->rvdmac_reg_base +
			  IRECOG_rpyramid_PYM_R00_CFG0_OFFS +
			  _PYM_R_INTERVAL * i);
	}
	for (i = 0; i < _PYM_W_NUM; i++) {
		iowrite32(0x00000000,
			  dev->rvdmac_reg_base +
			  IRECOG_rpyramid_PYM_W00_CFG0_OFFS +
			  _PYM_W_INTERVAL * i);
	}
	/* set configuration register1 */
	for (i = 0; i < _PYM_R_NUM; i++) {
		iowrite32(0x00010000,
			  dev->rvdmac_reg_base +
			  IRECOG_rpyramid_PYM_R00_CFG1_OFFS +
			  _PYM_R_INTERVAL * i);
	}
	for (i = 0; i < _PYM_W_NUM; i++) {
		iowrite32(0x00010000,
			  dev->rvdmac_reg_base +
			  IRECOG_rpyramid_PYM_W00_CFG1_OFFS +
			  _PYM_W_INTERVAL * i);
	}

	/* sram setting */
	iowrite32(0x00000000,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_T00_SRAM_BASE_OFFS);
	for (i = 0; i < _PYM_R_NUM; i++) {
		iowrite32(0x00000040 * (i + 1),
			  dev->rvdmac_reg_base +
			  IRECOG_rpyramid_PYM_R00_SRAM_BASE_OFFS +
			  _PYM_R_INTERVAL * i);
	}
	iowrite32(0x00000000,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 0);
	iowrite32(0x00000040,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 1);
	iowrite32(0x00000070,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 2);
	iowrite32(0x00000090,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 3);
	iowrite32(0x000000b0,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 4);
	iowrite32(0x000000f0,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 5);
	iowrite32(0x00000120,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 6);
	iowrite32(0x00000140,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 7);
	iowrite32(0x00000160,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 8);
	iowrite32(0x000001a0,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS + _PYM_W_INTERVAL * 9);
	iowrite32(0x000001d0,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS +
		  _PYM_W_INTERVAL * 10);
	iowrite32(0x000001f0,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_BASE_OFFS +
		  _PYM_W_INTERVAL * 11);

	iowrite32(0x00000040,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_T00_SRAM_SIZE_OFFS);
	for (i = 0; i < _PYM_R_NUM; i++) {
		iowrite32(0x00000040,
			  dev->rvdmac_reg_base +
			  IRECOG_rpyramid_PYM_R00_SRAM_SIZE_OFFS +
			  _PYM_R_INTERVAL * i);
	}
	iowrite32(0x00000040,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 0);
	iowrite32(0x00000030,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 1);
	iowrite32(0x00000020,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 2);
	iowrite32(0x00000020,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 3);
	iowrite32(0x00000040,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 4);
	iowrite32(0x00000030,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 5);
	iowrite32(0x00000020,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 6);
	iowrite32(0x00000020,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 7);
	iowrite32(0x00000040,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 8);
	iowrite32(0x00000030,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS + _PYM_W_INTERVAL * 9);
	iowrite32(0x00000020,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS +
		  _PYM_W_INTERVAL * 10);
	iowrite32(0x00000020,
		  dev->rvdmac_reg_base +
		  IRECOG_rpyramid_PYM_W00_SRAM_SIZE_OFFS +
		  _PYM_W_INTERVAL * 11);
}

/**************************************************/
/*
 * @brief gdmac_pyramid_probe
 *
 * @retval 0  success
 *
 */
/**************************************************/
static int __devinit gdmac_pyramid_probe(struct platform_device *pdev)
{
	int ret;
	dev_t dev = 0;

	/* allocation of device number */
	if (gdmac_pyramid_major) {
		dev = MKDEV(gdmac_pyramid_major, gdmac_pyramid_minor);
		ret =
		    register_chrdev_region(dev, gdmac_pyramid_nr_devs,
					   GDMAC_PYRAMID_NAME);
	} else {
		ret =
		    alloc_chrdev_region(&dev, gdmac_pyramid_minor,
					gdmac_pyramid_nr_devs,
					GDMAC_PYRAMID_NAME);
		gdmac_pyramid_major = MAJOR(dev);
	}
	if (ret < 0) {
		pr_err("%s: can't get major %d\n", GDMAC_PYRAMID_NAME,
		       gdmac_pyramid_major);
		return ret;
	}

	ctrl_dev = kmalloc(sizeof(struct gdmac_pyramid_dev), GFP_KERNEL);
	if (!ctrl_dev) {
		pr_err("%s: kmalloc failed\n", GDMAC_PYRAMID_NAME);
		ret = -ENOMEM;
		goto err0;
	}
	memset(ctrl_dev, 0, sizeof(struct gdmac_pyramid_dev));

	ctrl_dev->pdev = pdev;
	platform_set_drvdata(pdev, ctrl_dev);

	/* GDMAC I/O */
	if (mmap_gdmac_register(ctrl_dev, GDMAC_PYRAMID_REG_TYPE_SECURE) != 0) {
		pr_err("%s: ioremap gdmac failed.\n", GDMAC_PYRAMID_NAME);
		ret = -ENODEV;
		goto err1;
	}

	/* irq */
	ret =
	    request_irq(gdmac_pyramid_irq, pyramid_isr, IRQF_SHARED,
			GDMAC_PYRAMID_NAME, ctrl_dev);
	if (ret < 0) {
		pr_err("%s: request_irq failed\n", GDMAC_PYRAMID_NAME);
		goto err2;
	}

	sema_init(&sem, 1);
	init_waitqueue_head(&wq);
	setup_cdev(ctrl_dev, 0);

	ctrl_dev->inst =
	    gdmac_allocate(INST_BUF_SIZE, WORK_BUF_SIZE, REG_BUF_SIZE);
	if (ctrl_dev->inst == NULL) {
		pr_err("%s: gdmac_allocate failed.\n", GDMAC_PYRAMID_NAME);
		ret = -ENOMEM;
		goto err3;
	}

	if (pyramid_initialize() < 0) {
		pr_err("%s: pyramid initialize failed.\n", GDMAC_PYRAMID_NAME);
		ret = -ENOMEM;
		goto err4;
	}

	/* mailbox */
	if (!request_mem_region(MAILBOX_BASE, MAILBOX_SIZE, GDMAC_PYRAMID_NAME)) {
		/* pr_err("%s: request_mem_region mailbox failed.\n", GDMAC_PYRAMID_NAME); */
	}
	ctrl_dev->mailbox_reg_base =
	    ioremap_nocache(MAILBOX_BASE, MAILBOX_SIZE);
	if (!ctrl_dev->mailbox_reg_base) {
		pr_err("%s: ioremap mailbox failed.\n", GDMAC_PYRAMID_NAME);
		ret = -ENODEV;
		goto err5;
	}

	/* pyramid */
	ctrl_dev->pyramid_reg_base =
	    ioremap_nocache(PYRAMID_BASE, PYRAMID_SIZE);
	if (!ctrl_dev->pyramid_reg_base) {
		pr_err("%s: ioremap rpyramid failed.\n", GDMAC_PYRAMID_NAME);
		ret = -ENODEV;
		goto err6;
	}
	ctrl_dev->rvdmac_reg_base =
	    ctrl_dev->pyramid_reg_base + IRECOG_rpyramid_PYM_STADR_OFFS;
	ctrl_dev->rscaler_reg_base = ctrl_dev->pyramid_reg_base + RSCALER_BASE;

	/* create gdmac_pyramid class */
	pgdmac_pyramid_class = class_create(THIS_MODULE, GDMAC_PYRAMID_NAME);
	if (IS_ERR(pgdmac_pyramid_class)) {
		ret = PTR_ERR(pgdmac_pyramid_class);
		pr_err("%s: class_create failed\n", GDMAC_PYRAMID_NAME);
		goto err7;
	}

	/* create device structure */
	ctrl_dev->device =
	    device_create(pgdmac_pyramid_class, NULL, dev, NULL,
			  GDMAC_PYRAMID_NAME);
	if (IS_ERR(ctrl_dev->device)) {
		ret = PTR_ERR(ctrl_dev->device);
		pr_err("%s: device_create failed\n", GDMAC_PYRAMID_NAME);
		goto err8;
	}

	gdmac_pyramid_state = STATE_IDLE;

	pm_runtime_enable(&pdev->dev);

	pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
		GDMAC_PYRAMID_NAME,
		DRV_GDMAC_PYRAMID_VERSION_STR, MAJOR(dev), MINOR(dev));
	return 0;

err8:
	class_destroy(pgdmac_pyramid_class);
err7:
	cdev_del(&ctrl_dev->cdev);
err6:
	iounmap(ctrl_dev->mailbox_reg_base);
err5:
	release_mem_region(MAILBOX_BASE, MAILBOX_SIZE);
err4:
	gdmac_free(ctrl_dev->inst);
err3:
	free_irq(gdmac_pyramid_irq, ctrl_dev);
err2:
	iounmap(ctrl_dev->gdmac_reg_base);
err1:
	kfree(ctrl_dev);
err0:
	unregister_chrdev_region(dev, gdmac_pyramid_nr_devs);

	return ret;
}

/**************************************************/
/*
 * @brief gdmac_pyramid_remove
 *
 */
/**************************************************/
static int __devexit gdmac_pyramid_remove(struct platform_device *pdev)
{
	dev_t dev = MKDEV(gdmac_pyramid_major, gdmac_pyramid_minor);

	pyramid_finalize();

	if (ctrl_dev) {

		device_destroy(pgdmac_pyramid_class, dev);
		class_destroy(pgdmac_pyramid_class);

		cdev_del(&ctrl_dev->cdev);

		iounmap(ctrl_dev->gdmac_reg_base);

		iounmap(ctrl_dev->mailbox_reg_base);
		release_mem_region(MAILBOX_BASE, MAILBOX_SIZE);

		iounmap(ctrl_dev->pyramid_reg_base);

		gdmac_free(ctrl_dev->inst);
		free_irq(gdmac_pyramid_irq, ctrl_dev);
		kfree(ctrl_dev);
	}
	pm_runtime_disable(&pdev->dev);
	platform_set_drvdata(pdev, NULL);

	unregister_chrdev_region(dev, gdmac_pyramid_nr_devs);

	pr_info("%s: exit\n", GDMAC_PYRAMID_NAME);
	return 0;
}

static int gdmac_pyramid_suspend(struct device *dev)
{
	int ret = 0;

	if (atomic_read(&refcount) > 0) {
		ret = -EBUSY;
	}

	pr_debug("%s: %s: %d\n", GDMAC_PYRAMID_NAME, __func__, ret);

	return ret;
}

static int gdmac_pyramid_resume(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops gdmac_pyramid_pm_ops = {
	.suspend = gdmac_pyramid_suspend,
	.resume = gdmac_pyramid_resume,
	.runtime_suspend = gdmac_pyramid_runtime_suspend,
	.runtime_resume = gdmac_pyramid_runtime_resume,
};

static struct platform_driver gdmac_pyramid_driver = {
	.driver = {
		   .name = "irecog_gdmac_pyramid",
		   .owner = THIS_MODULE,
		   .pm = &gdmac_pyramid_pm_ops,
		   },
	.probe = gdmac_pyramid_probe,
	.remove = gdmac_pyramid_remove,
};

static int __init gdmac_pyramid_init(void)
{
	return platform_driver_register(&gdmac_pyramid_driver);
}

static void __exit gdmac_pyramid_exit(void)
{
	platform_driver_unregister(&gdmac_pyramid_driver);
}

module_init(gdmac_pyramid_init);
module_exit(gdmac_pyramid_exit);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_VERSION(DRV_GDMAC_PYRAMID_VERSION_STR);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("GDMAC PYRAMID module");
