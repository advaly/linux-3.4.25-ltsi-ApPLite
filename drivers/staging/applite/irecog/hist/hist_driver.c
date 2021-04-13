/*
 * linux/drivers/staging/applite/irecog/hist/hist_driver.c
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

#include <linux/applite/irecog/hist_ioctl.h>
#include <linux/applite/irecog/hist_param.h>

#include <mach/regs/irecog_offs_def.h>
#include <mach/regs/irecog_reg_def.h>

#include "hist_driver.h"
#include "hist_util.h"

#include "drv_cache.h"
#include "drv_signal.h"
#include "drv_polling.h"
#include "drv_dmabuf.h"

/* #define ENABLE_DEBUG_PRINT */
#ifdef ENABLE_DEBUG_PRINT
#define DEBUG_PRINT(format, args...)  pr_debug(format , ## args)
#else
#define DEBUG_PRINT(format, args...)
#endif

/**************************************************/
/*
 * macros
 */
/**************************************************/
#define HIST_OFFSET(x) ((x) - IRECOG_rhist_Control_and_Status_Register_OFFS)

/**************************************************/
/*
 * constant defs
 */
/**************************************************/
#define HIST_EXE_DONE 0x0
#define HIST_KICKED   0x1
#define HIST_ERROR    0x2

#define HIST_HW_PARAM_SIZE  (15)

/**************************************************/
/*
 * variables
 */
/**************************************************/
static const char *drv_hist_version = DRV_HIST_VERSION_STR;

static int hist_major = HIST_MAJOR;
static int hist_minor = HIST_MINOR;
static int hist_nr_devs = HIST_NR_DEVS;
static int hist_irq = HIST_IRQ;

module_param(hist_major, int, S_IRUGO | S_IWUSR);
module_param(hist_minor, int, S_IRUGO | S_IWUSR);
module_param(hist_nr_devs, int, S_IRUGO | S_IWUSR);
module_param(hist_irq, int, S_IRUGO | S_IWUSR);

static struct hist_dev *hist_device;
static struct class *phist_class;

static int hist_status = HIST_EXE_DONE;
static wait_queue_head_t wq;
static struct semaphore sem;
static atomic_t refcount = ATOMIC_INIT(0);

static int check_cache_param(ULONG flag)
{
	if ((flag != DRV_CACHE_FLUSH_ALL) && (flag != DRV_NO_CACHE_CTL)) {
		pr_err("%s: invalid buffer_cache_ctl:%lu\n", HIST_NAME, flag);
		return -1;
	}

	return 0;
}

static long hist_reset(struct hist_dev *dev);

static int hist_conv_address(struct hist_dev *dev, int src_fd, int score_fd,
			     int dst_fd)
{
	memset(&dev->src_buf, 0x00, sizeof(struct drv_dmabuf_conv_adr));
	memset(&dev->score_buf, 0x00, sizeof(struct drv_dmabuf_conv_adr));
	memset(&dev->dst_buf, 0x00, sizeof(struct drv_dmabuf_conv_adr));

	if (src_fd >= 0) {
		if (drv_dmabuf_get_phys_addr
		    (dev->device, src_fd, &dev->src_buf, DMA_TO_DEVICE) < 0) {
			return -1;
		}
	}

	if (score_fd >= 0) {
		if (drv_dmabuf_get_phys_addr
		    (dev->device, score_fd, &dev->score_buf,
		     DMA_TO_DEVICE) < 0) {
			return -1;
		}
	}

	if (dst_fd >= 0) {
		if (drv_dmabuf_get_phys_addr
		    (dev->device, dst_fd, &dev->dst_buf, DMA_FROM_DEVICE) < 0) {
			return -1;
		}
	}

	return 0;
}

static int hist_free_address(struct hist_dev *dev)
{
	drv_dmabuf_put_phys_addr(&dev->dst_buf, DMA_FROM_DEVICE);
	drv_dmabuf_put_phys_addr(&dev->src_buf, DMA_TO_DEVICE);
	drv_dmabuf_put_phys_addr(&dev->score_buf, DMA_TO_DEVICE);

	return 0;
}

static int hist_runtime_suspend(struct device *dev)
{
	unsigned int ret;
	struct platform_data *pdata = dev->platform_data;
	struct platform_device *pdev = to_platform_device(dev);
	struct hist_dev *priv = platform_get_drvdata(pdev);

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	iowrite32(IRECOG_RHIST_CONTROL_AND_STATUS_REGISTER_RST_MASK,
		  priv->reg_base +
		  HIST_OFFSET(IRECOG_rhist_Control_and_Status_Register_OFFS));

	ret = drv_wait_register(priv->reg_base +
				HIST_OFFSET
				(IRECOG_rhist_Control_and_Status_Register_OFFS),
				IRECOG_RHIST_CONTROL_AND_STATUS_REGISTER_RST_MASK,
				0x00, DRV_WAIT_REG_TIMEOUT);

	if ((ret & IRECOG_RHIST_CONTROL_AND_STATUS_REGISTER_RST_MASK) != 0x0) {
		pr_err("%s: timeout occured\n", HIST_NAME);
		return -EIO;
	}

	clock_enable(APPLITE_IRECOG_HIST, APPLITE_IRECOG_CLOCK_DISABLE);
	return 0;
}

static int hist_runtime_resume(struct device *dev)
{
	struct platform_data *pdata = dev->platform_data;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	clock_enable(APPLITE_IRECOG_HIST, APPLITE_IRECOG_CLOCK_ENABLE);
	return 0;
}

static long hist_wait_event(struct file *filp)
{
	sigset_t oldset;
	int status = hist_status;
	struct hist_dev *dev = filp->private_data;

	if (status != HIST_EXE_DONE) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		/* signal mask */
		drv_sigmask(&oldset);
		if (wait_event_interruptible(wq,
					     (hist_status == HIST_EXE_DONE))) {

			hist_reset(dev);

			/* signal unmask */
			drv_sigunmask(&oldset);
			hist_status = HIST_EXE_DONE;
			pr_err("%s: wait_event_interruptible fail.\n",
			       HIST_NAME);

			return -ERESTARTSYS;
		}
		/* signal unmask */
		drv_sigunmask(&oldset);
	}

	return 0;
}

static int hist_get_int_status(struct hist_dev *dev)
{
	unsigned int status;
	int ret;

	status =
	    ioread32(dev->reg_base +
		     HIST_OFFSET(IRECOG_rhist_interrupt_status_OFFS));
	if ((status & 0x01) != 0) {
		ret = HIST_EXE_DONE;
	} else {

		ret = HIST_ERROR;
	}

	return ret;
}

static long hist_reset(struct hist_dev *dev)
{
	unsigned int ret;

	iowrite32(IRECOG_RHIST_CONTROL_AND_STATUS_REGISTER_RST_MASK,
		  dev->reg_base +
		  HIST_OFFSET(IRECOG_rhist_Control_and_Status_Register_OFFS));

	/* wait for reset completion */
	ret = drv_wait_register(dev->reg_base +
				HIST_OFFSET
				(IRECOG_rhist_Control_and_Status_Register_OFFS),
				IRECOG_RHIST_CONTROL_AND_STATUS_REGISTER_RST_MASK,
				0x00, DRV_WAIT_REG_TIMEOUT);

	if ((ret & IRECOG_RHIST_CONTROL_AND_STATUS_REGISTER_RST_MASK) != 0x0) {
		pr_err
		    ("%s: timeout occured while waiting for register value to change\n",
		     HIST_NAME);
		return -EIO;
	}

	return 0;
}

static void hist_clear_int(struct hist_dev *dev)
{
	iowrite32(IRECOG_RHIST_INTERRUPT_STATUS_END_MASK,
		  dev->reg_base +
		  HIST_OFFSET(IRECOG_rhist_interrupt_status_OFFS));
}

static SINT dd_HIST_send_request(struct hist_dev *dev)
{
	/* Clear Interrupt Status */
	hist_clear_int(dev);

	/* Set Int Mask. */
	iowrite32(0x0,
		  dev->reg_base +
		  HIST_OFFSET(IRECOG_rhist_interrupt_mask_OFFS));

	/* Kick Hist */
	hist_status = HIST_KICKED;
	iowrite32(IRECOG_RHIST_CONTROL_AND_STATUS_REGISTER_CMD_MASK,
		  dev->reg_base +
		  HIST_OFFSET(IRECOG_rhist_Control_and_Status_Register_OFFS));

	return 0;
}

static irqreturn_t hist_isr(int irq, void *dev_id)
{
	struct hist_dev *dev = dev_id;
	int status;

	status = hist_get_int_status(dev);
	hist_status = status;
	hist_clear_int(dev);

	if (status == HIST_EXE_DONE) {
		wake_up_interruptible(&wq);

	} else if (status == HIST_ERROR) {

		wake_up_interruptible(&wq);
	}

	return IRQ_HANDLED;
}

static int hist_open(struct inode *inode, struct file *filp)
{
	struct hist_dev *dev;

	dev = container_of(inode->i_cdev, struct hist_dev, cdev);
	filp->private_data = dev;

	if (atomic_inc_return(&refcount) == 1) {
		hist_runtime_resume(&dev->pdev->dev);
	}
	return 0;
}

static int hist_release(struct inode *inode, struct file *filp)
{
	struct hist_dev *dev;

	dev = container_of(inode->i_cdev, struct hist_dev, cdev);

	if (atomic_dec_return(&refcount) == 0) {
		hist_runtime_suspend(&dev->pdev->dev);
	}
	return 0;
}

static long hist_get_version(unsigned long val)
{
	drv_version_t version_param;

	memset(&version_param, 0x00, sizeof(drv_version_t));
	memcpy(version_param.version, drv_hist_version,
	       strlen(drv_hist_version));

	if (copy_to_user((void __user *)val,
			 (void *)&version_param, sizeof(drv_version_t))) {
		pr_err("%s: copy_to_user failed version\n", HIST_NAME);
		return -EFAULT;
	}

	return 0;
}

static long hist_check_histgram_param(struct hist_param *param)
{
	if (param->dst_fd < 0) {
		pr_err("%s: invalid dst_fd: %d\n", HIST_NAME, param->dst_fd);
		return -1;
	}

	if (param->dst_offset & 0x0000000f) {
		pr_err("%s: dst_offset muse be aligned 16byte: 0x%x\n",
		       HIST_NAME, param->dst_offset);
		return -1;
	}

	if (param->src_fd < 0) {
		pr_err("%s: invalid src_fd: %d\n", HIST_NAME, param->src_fd);
		return -1;
	}

	if (param->src_height <= 1) {
		if ((param->src_width <= 0) || (param->src_width > 0x1000000)) {
			pr_err("%s: invalid src_width: %d\n", HIST_NAME,
			       param->src_width);
			return -1;
		}
	} else {
		if ((param->src_width <= 0) || (param->src_width > 8192)) {
			pr_err("%s: invalid src_width: %d\n", HIST_NAME,
			       param->src_width);
			return -1;
		}
		if (param->src_height > 2048) {
			pr_err("%s: invalid src_height: %d\n", HIST_NAME,
			       param->src_height);
			return -1;
		}
	}

	if (param->src_pitch < param->src_width) {
		pr_err("%s: invalid src_pitch: %d\n", HIST_NAME,
		       param->src_pitch);
		return -1;
	}

	if (param->src_pitch > 0x1000000) {
		pr_err("%s: invalid src_pitch: %d\n", HIST_NAME,
		       param->src_pitch);
		return -1;
	}

	if ((param->src_type != HIST_FORMAT_U8) &&
	    (param->src_type != HIST_FORMAT_U16) &&
	    (param->src_type != HIST_FORMAT_S8) &&
	    (param->src_type != HIST_FORMAT_S16)) {
		pr_err("%s: invalid src_type:%d\n", HIST_NAME, param->src_type);
		return -1;
	}

	if ((param->src_type == HIST_FORMAT_U8)
	    || (param->src_type == HIST_FORMAT_S8)) {
		if (param->src_pitch & 0x0000000f) {
			pr_err("%s: src_pitch:%d must be 16byte aligned.\n",
			       HIST_NAME, param->src_pitch);
			return -1;
		}
	}

	if ((param->src_type == HIST_FORMAT_U16)
	    || (param->src_type == HIST_FORMAT_S16)) {
		if (param->src_pitch & 0x00000007) {
			pr_err("%s: src_pitch:%d must be 16byte aligned.\n",
			       HIST_NAME, param->src_pitch);
			return -1;
		}
	}

	if ((param->src_x_sample_interval <= 0) ||
	    (param->src_x_sample_interval >= 0xff)) {
		pr_err("%s: invalid src_x_sample_interval:%d\n", HIST_NAME,
		       param->src_x_sample_interval);
		return -1;
	}

	if ((param->src_y_sample_interval <= 0) ||
	    (param->src_y_sample_interval >= 0xff)) {
		pr_err("%s: invalid src_y_sample_interval:%d\n", HIST_NAME,
		       param->src_y_sample_interval);
		return -1;
	}

	if ((param->outlier != HIST_OUTL_COUNT_DISABLE) &&
	    (param->outlier != HIST_OUTL_COUNT_ENABLE)) {
		pr_err("%s: invalid outlier:%d\n", HIST_NAME, param->outlier);
		return -1;
	}

	if ((param->clear != HIST_BIN_CLR_DISABLE) &&
	    (param->clear != HIST_BIN_CLR_ENABLE)) {
		pr_err("%s: invalid clear:%d\n", HIST_NAME, param->clear);
		return -1;
	}

	if ((param->bin_num != HIST_BIN_NUM_256) &&
	    (param->bin_num != HIST_BIN_NUM_512) &&
	    (param->bin_num != HIST_BIN_NUM_1024)) {
		pr_err("%s: invalid bin_num:%d\n", HIST_NAME, param->bin_num);
		return -1;
	}

	if (param->index_shift > 15) {
		pr_err("%s: invalid index_shift: %d\n", HIST_NAME,
		       param->index_shift);
		return -1;
	}

	if (param->index_offset > 32767) {
		pr_err("%s: invalid index_offset: %d\n", HIST_NAME,
		       param->index_offset);
		return -1;
	}

	if (param->index_offset < -32768) {
		pr_err("%s: invalid index_offset: %d\n", HIST_NAME,
		       param->index_offset);
		return -1;
	}

	return 0;
}

static long hist_check_scorevoting_param(struct hist_scorevoting_param *param)
{
	if (param->dst_fd < 0) {
		pr_err("%s: invalid dst_fd: %d\n", HIST_NAME, param->dst_fd);
		return -1;
	}

	if (param->dst_offset & 0x0000000f) {
		pr_err("%s: dst_offset muse be aligned 16byte: 0x%x\n",
		       HIST_NAME, param->dst_offset);
		return -1;
	}

	if (param->src_fd < 0) {
		pr_err("%s: invalid src_fd: %d\n", HIST_NAME, param->src_fd);
		return -1;
	}

	/* check src param */
	if (param->src_height <= 1) {
		if ((param->src_width <= 0) || (param->src_width > 0x1000000)) {
			pr_err("%s: invalid src_width: %d\n", HIST_NAME,
			       param->src_width);
			return -1;
		}
	} else {
		if ((param->src_width <= 0) || (param->src_width > 8192)) {
			pr_err("%s: invalid src_width: %d\n", HIST_NAME,
			       param->src_width);
			return -1;
		}
		if (param->src_height > 2048) {
			pr_err("%s: invalid src_height: %d\n", HIST_NAME,
			       param->src_height);
			return -1;
		}
	}

	if (param->src_pitch < param->src_width) {
		pr_err("%s: invalid src_pitch: %d\n", HIST_NAME,
		       param->src_pitch);
		return -1;
	}

	if (param->src_pitch > 0x1000000) {
		pr_err("%s: invalid src_pitch: %d\n", HIST_NAME,
		       param->src_pitch);
		return -1;
	}

	if ((param->src_type != HIST_FORMAT_U8) &&
	    (param->src_type != HIST_FORMAT_U16) &&
	    (param->src_type != HIST_FORMAT_S8) &&
	    (param->src_type != HIST_FORMAT_S16)) {
		pr_err("%s: invalid src_type:%d\n", HIST_NAME, param->src_type);
		return -1;
	}

	if ((param->src_type == HIST_FORMAT_U8)
	    || (param->src_type == HIST_FORMAT_S8)) {
		if (param->src_pitch & 0x0000000f) {
			pr_err("%s: src_pitch:%d must be 16byte aligned.\n",
			       HIST_NAME, param->src_pitch);
		}
	}

	if ((param->src_type == HIST_FORMAT_U16)
	    || (param->src_type == HIST_FORMAT_S16)) {
		if (param->src_pitch & 0x00000007) {
			pr_err("%s: src_pitch:%d must be 16byte aligned.\n",
			       HIST_NAME, param->src_pitch);
		}
	}

	if ((param->src_x_sample_interval <= 0) ||
	    (param->src_x_sample_interval > 0xff)) {
		pr_err("%s: invalid src_x_sample_interval:%d\n", HIST_NAME,
		       param->src_x_sample_interval);
		return -1;
	}

	if ((param->src_y_sample_interval <= 0) ||
	    (param->src_y_sample_interval > 0xff)) {
		pr_err("%s: invalid src_y_sample_interval:%d\n", HIST_NAME,
		       param->src_y_sample_interval);
		return -1;
	}

	/* check score param */
	if (param->score_fd < 0) {
		pr_err("%s: invalid score_fd: %d\n", HIST_NAME,
		       param->score_fd);
		return -1;
	}

	if (param->score_height <= 1) {
		if ((param->score_width <= 0)
		    || (param->score_width > 0x1000000)) {
			pr_err("%s: invalid score_width: %d\n", HIST_NAME,
			       param->score_width);
			return -1;
		}
	} else {
		if ((param->score_width <= 0) || (param->score_width > 8192)) {
			pr_err("%s: invalid score_width: %d\n", HIST_NAME,
			       param->score_width);
			return -1;
		}
		if (param->score_height > 2048) {
			pr_err("%s: invalid score_height: %d\n", HIST_NAME,
			       param->score_height);
			return -1;
		}
	}

	if (param->score_pitch < param->score_width) {
		pr_err("%s: invalid score_pitch: %d\n", HIST_NAME,
		       param->score_pitch);
		return -1;
	}

	if (param->score_pitch > 0x1000000) {
		pr_err("%s: invalid score_pitch: %d\n", HIST_NAME,
		       param->score_pitch);
		return -1;
	}

	if ((param->score_type != HIST_FORMAT_U8) &&
	    (param->score_type != HIST_FORMAT_U16) &&
	    (param->score_type != HIST_FORMAT_S8) &&
	    (param->score_type != HIST_FORMAT_S16)) {
		pr_err("%s: invalid score_type:%d\n", HIST_NAME,
		       param->score_type);
		return -1;
	}

	if ((param->score_type == HIST_FORMAT_U8)
	    || (param->score_type == HIST_FORMAT_S8)) {
		if (param->score_pitch & 0x0000000f) {
			pr_err("%s: score_pitch:%d must be 16byte aligned.\n",
			       HIST_NAME, param->score_pitch);
		}
	}

	if ((param->score_type == HIST_FORMAT_U16)
	    || (param->score_type == HIST_FORMAT_S16)) {
		if (param->score_pitch & 0x00000007) {
			pr_err("%s: score_pitch:%d must be 16byte aligned.\n",
			       HIST_NAME, param->score_pitch);
		}
	}

	if ((param->score_x_sample_interval <= 0) ||
	    (param->score_x_sample_interval > 0xff)) {
		pr_err("%s: invalid score_x_sample_interval:%d\n", HIST_NAME,
		       param->score_x_sample_interval);
		return -1;
	}

	if ((param->score_y_sample_interval <= 0) ||
	    (param->score_y_sample_interval > 0xff)) {
		pr_err("%s: invalid scoere_y_sample_interval:%d\n", HIST_NAME,
		       param->score_y_sample_interval);
		return -1;
	}

	{
		UINT src_x_sample_num =
		    param->src_width / param->src_x_sample_interval;
		UINT src_y_sample_num =
		    param->src_height / param->src_y_sample_interval;
		UINT score_x_sample_num =
		    param->score_width / param->score_x_sample_interval;
		UINT score_y_sample_num =
		    param->score_height / param->score_y_sample_interval;

		if (src_x_sample_num != score_x_sample_num) {
			pr_err("%s: different sample num src_x:%d score_x:%d\n",
			       HIST_NAME, src_x_sample_num, score_x_sample_num);
			return -1;
		}
		if (src_y_sample_num != score_y_sample_num) {
			pr_err("%s: different sample num src_y:%d score_y:%d\n",
			       HIST_NAME, src_y_sample_num, score_y_sample_num);
			return -1;
		}
	}

	if ((param->outlier != HIST_OUTL_COUNT_DISABLE) &&
	    (param->outlier != HIST_OUTL_COUNT_ENABLE)) {
		pr_err("%s: invalid outlier:%d\n", HIST_NAME, param->outlier);
		return -1;
	}

	if ((param->clear != HIST_BIN_CLR_DISABLE) &&
	    (param->clear != HIST_BIN_CLR_ENABLE)) {
		pr_err("%s: invalid clear:%d\n", HIST_NAME, param->clear);
		return -1;
	}

	if ((param->bin_num != HIST_BIN_NUM_256) &&
	    (param->bin_num != HIST_BIN_NUM_512) &&
	    (param->bin_num != HIST_BIN_NUM_1024)) {
		pr_err("%s: invalid bin_num:%d\n", HIST_NAME, param->bin_num);
		return -1;
	}

	if (param->index_shift > 15) {
		pr_err("%s: invalid index_shift: %d\n", HIST_NAME,
		       param->index_shift);
		return -1;
	}

	if (param->index_offset > 32767) {
		pr_err("%s: invalid index_offset: %d\n", HIST_NAME,
		       param->index_offset);
		return -1;
	}

	if (param->index_offset < -32768) {
		pr_err("%s: invalid index_offset: %d\n", HIST_NAME,
		       param->index_offset);
		return -1;
	}

	return 0;
}

static void write_registers(struct hist_dev *dev, HIST_DESCRIPT *descript)
{
	UINT *uqueue = (UINT *)descript;
	int i;

	/* mode register(0x04) */
	iowrite32((UINT)uqueue[1],
		  dev->reg_base + HIST_OFFSET(IRECOG_rhist_Mode_Register_OFFS));

	/* function register(0x10) - 0x58 */
	for (i = 0; i < HIST_HW_PARAM_SIZE; i++) {
		iowrite32((UINT)uqueue[2 + i],
			  dev->reg_base +
			  HIST_OFFSET
			  (IRECOG_rhist_Histogram_Function_Register_OFFS) +
			  i * 0x4);
	}
}

static long setup_histgram(struct hist_dev *dev, struct hist_param *param)
{
	HIST_DESCRIPT descript;
	SINT ret;

	UINT src_dim = (param->src_height <= 1) ? 1 : 2;
	UINT outlier = (param->outlier == HIST_OUTL_COUNT_DISABLE) ? 0 : 1;
	UINT clear = (param->clear == HIST_BIN_CLR_DISABLE) ? 0 : 1;
	UINT bin_num;
	UINT src_x_sample_num = param->src_width / param->src_x_sample_interval;
	UINT src_y_sample_num =
	    param->src_height / param->src_y_sample_interval;

	UINT condition = 0;
	SINT threshold = 0;

	UINT src_type;
	switch (param->src_type) {
	case HIST_FORMAT_U8:
		src_type = 0;
		break;
	case HIST_FORMAT_U16:
		src_type = 1;
		break;
	case HIST_FORMAT_S8:
		src_type = 2;
		break;
	case HIST_FORMAT_S16:
		src_type = 3;
		break;
	default:
		pr_err("%s: invalid param src_type:%d\n", __func__,
		       param->src_type);
		return -1;
	}

	switch (param->bin_num) {
	case HIST_BIN_NUM_256:
		bin_num = 0;
		break;
	case HIST_BIN_NUM_512:
		bin_num = 1;
		break;
	case HIST_BIN_NUM_1024:
		bin_num = 2;
		break;
	default:
		pr_err("%s: invalid param bin_num:%d\n", __func__,
		       param->bin_num);
		return -1;
	}

	ret = dd_HIST_config_histogram(&descript,
				       (VOID *)((char *)dev->dst_buf.addr +
						param->dst_offset),
				       (VOID *)((char *)dev->src_buf.addr +
						param->src_offset),
				       param->src_pitch, src_dim, src_type,
				       param->src_x_sample_interval,
				       param->src_y_sample_interval,
				       src_x_sample_num, src_y_sample_num,
				       outlier, clear, bin_num,
				       param->index_shift, param->index_offset,
				       condition, threshold);
	if (ret < 0) {
		pr_err("%s: dd_HIST_config_histgram fail.\n", __func__);
		return -1;
	}

	write_registers(dev, &descript);

	return 0;
}

static long setup_scorevoting(struct hist_dev *dev,
			      struct hist_scorevoting_param *param)
{
	HIST_DESCRIPT descript;
	SINT ret;

	UINT src_dim = (param->src_height <= 1) ? 1 : 2;
	UINT outlier = (param->outlier == HIST_OUTL_COUNT_DISABLE) ? 0 : 1;
	UINT clear = (param->clear == HIST_BIN_CLR_DISABLE) ? 0 : 1;
	UINT bin_num;
	UINT src_x_sample_num = param->src_width / param->src_x_sample_interval;
	UINT src_y_sample_num =
	    param->src_height / param->src_y_sample_interval;

	UINT condition = 0;
	SINT threshold = 0;

	UINT src_type, score_type;
	switch (param->src_type) {
	case HIST_FORMAT_U8:
		src_type = 0;
		break;
	case HIST_FORMAT_U16:
		src_type = 1;
		break;
	case HIST_FORMAT_S8:
		src_type = 2;
		break;
	case HIST_FORMAT_S16:
		src_type = 3;
		break;
	default:
		pr_err("%s: invalid param src_type:%d\n", __func__,
		       param->src_type);
		return -1;
	}

	switch (param->score_type) {
	case HIST_FORMAT_U8:
		score_type = 0;
		break;
	case HIST_FORMAT_U16:
		score_type = 1;
		break;
	case HIST_FORMAT_S8:
		score_type = 2;
		break;
	case HIST_FORMAT_S16:
		score_type = 3;
		break;
	default:
		pr_err("%s: invalid param score_type:%d\n", __func__,
		       param->score_type);
		return -1;
	}

	switch (param->bin_num) {
	case HIST_BIN_NUM_256:
		bin_num = 0;
		break;
	case HIST_BIN_NUM_512:
		bin_num = 1;
		break;
	case HIST_BIN_NUM_1024:
		bin_num = 2;
		break;
	default:
		pr_err("%s: invalid param bin_num:%d\n", __func__,
		       param->bin_num);
		return -1;
	}

	ret = dd_HIST_config_scorevoting(&descript,
					 (VOID *)((char *)dev->dst_buf.addr +
						  param->dst_offset),
					 (VOID *)((char *)dev->src_buf.addr +
						  param->src_offset),
					 param->src_pitch, src_dim, src_type,
					 param->src_x_sample_interval,
					 param->src_y_sample_interval,
					 src_x_sample_num, src_y_sample_num,
					 (VOID *)((char *)dev->score_buf.addr +
						  param->score_offset),
					 param->score_pitch, score_type,
					 param->score_x_sample_interval,
					 param->score_y_sample_interval,
					 outlier, clear, bin_num,
					 param->index_shift,
					 param->index_offset, condition,
					 threshold);
	if (ret < 0) {
		pr_err("%s: dd_HIST_config_histgram fail.\n", __func__);
		return -1;
	}

	write_registers(dev, &descript);

	return 0;
}

static long hist_ioctl(struct file *filp, unsigned int cmd, unsigned long val)
{
	struct hist_dev *dev = filp->private_data;
	long ret;

	switch (cmd) {
	case HIST_IOCTL_HISTOGRAM:
		{
			struct hist_param param;
			if (copy_from_user
			    ((void *)&param, (const void __user *)val,
			     sizeof(struct hist_param))) {
				pr_err("%s: copy_from_user failed hist_param\n",
				       HIST_NAME);
				return -EFAULT;
			}

			if (hist_check_histgram_param(&param) < 0) {
				pr_err("%s: invalid ioctl parameter %d\n",
				       HIST_NAME, cmd);
				return -EINVAL;
			}
			if (check_cache_param(param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				return -ERESTARTSYS;
			}

			if (hist_status != HIST_EXE_DONE) {
				up(&sem);
				return -EAGAIN;
			}
			if (hist_conv_address
			    (dev, param.src_fd, -1, param.dst_fd) < 0) {
				pr_err
				    ("%s: failed to get phys address from fd %d\n",
				     HIST_NAME, cmd);
				up(&sem);
				return -EINVAL;
			}

			if (setup_histgram(dev, &param) < 0) {
				pr_err("%s: dd_HIST_config_histogram %d\n",
				       HIST_NAME, cmd);
				up(&sem);
				return -EINVAL;
			}

			if (param.buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
				DEBUG_PRINT("%s %s %d: hist cache flush\n",
					    __FILE__, __func__, __LINE__);
				drv_cache_flush_all();
			}

			dd_HIST_send_request(dev);

			ret = hist_wait_event(filp);
			hist_free_address(dev);
			up(&sem);

			return ret;
		}
		break;

	case HIST_IOCTL_HISTOGRAM_SCOREVOTING:
		{
			struct hist_scorevoting_param param;
			if (copy_from_user
			    ((void *)&param, (const void __user *)val,
			     sizeof(struct hist_scorevoting_param))) {
				pr_err
				    ("%s: copy_from_user failed hist_scorevoting_param\n",
				     HIST_NAME);
				return -EFAULT;
			}

			if (hist_check_scorevoting_param(&param) < 0) {
				pr_err("%s: invalid ioctl parameter %d\n",
				       HIST_NAME, cmd);
				return -EINVAL;
			}
			if (check_cache_param(param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				return -ERESTARTSYS;
			}

			if (hist_status != HIST_EXE_DONE) {
				up(&sem);
				return -EAGAIN;
			}
			if (hist_conv_address
			    (dev, param.src_fd, param.score_fd,
			     param.dst_fd) < 0) {
				pr_err
				    ("%s: failed to get phys address from fd %d\n",
				     HIST_NAME, cmd);
				up(&sem);
				return -EINVAL;
			}

			if (setup_scorevoting(dev, &param) < 0) {
				pr_err("%s: dd_HIST_config_scorevoting %d\n",
				       HIST_NAME, cmd);
				up(&sem);
				return -EINVAL;
			}

			if (param.buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
				DEBUG_PRINT("%s %s %d: hist cache flush\n",
					    __FILE__, __func__, __LINE__);
				drv_cache_flush_all();
			}

			dd_HIST_send_request(dev);

			ret = hist_wait_event(filp);
			hist_free_address(dev);
			up(&sem);

			return ret;
		}
		break;

	case HIST_IOCTL_TABLE_MODE:
		{
			pr_info("%s HIST_IOCTL_TABLE_MODE not implemented.\n",
				HIST_NAME);
			return -EINVAL;
		}
		break;

	case HIST_IOCTL_GET_VERSION:
		return hist_get_version(val);
		break;

	case HIST_IOCTL_INITIALIZE:
		if (hist_reset(dev) < 0) {
			pr_err("%s: reset failed\n", HIST_NAME);
			return -EIO;
		}
		break;

	default:
		pr_err("%s: invalid ioctl command %d\n", HIST_NAME, cmd);
		return -EINVAL;
		break;
	}

	return 0;
}

static const struct file_operations hist_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = hist_ioctl,
	.open = hist_open,
	.release = hist_release,
};

static void hist_setup_cdev(struct hist_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(hist_major, hist_minor + index);

	cdev_init(&dev->cdev, &hist_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev %d\n", HIST_NAME, index);
	}
}

static int __devinit hist_probe(struct platform_device *pdev)
{
	int ret;
	dev_t dev = 0;

	/* allocation of device number */
	if (hist_major) {
		dev = MKDEV(hist_major, hist_minor);
		ret = register_chrdev_region(dev, hist_nr_devs, HIST_NAME);
	} else {
		ret =
		    alloc_chrdev_region(&dev, hist_minor, hist_nr_devs,
					HIST_NAME);
		hist_major = MAJOR(dev);
	}
	if (ret < 0) {
		pr_err("%s: can't get major %d\n", HIST_NAME, hist_major);
		return ret;
	}

	hist_device = kmalloc(sizeof(struct hist_dev), GFP_KERNEL);
	if (!hist_device) {
		pr_err("%s: kmalloc failed\n", HIST_NAME);
		ret = -ENOMEM;
		goto err0;
	}
	memset(hist_device, 0, sizeof(struct hist_dev));
	hist_device->pdev = pdev;
	platform_set_drvdata(pdev, hist_device);

	/* mapping of hist MMIO */
	if (!request_mem_region(HIST_BASE, HIST_SIZE, HIST_NAME)) {
		pr_err("%s: request_mem_region failed.\n", HIST_NAME);
		ret = -ENODEV;
		goto err1;
	}

	hist_device->reg_base = ioremap_nocache(HIST_BASE, HIST_SIZE);
	if (!hist_device->reg_base) {
		ret = -ENODEV;
		goto err2;
	}

	/* register interrupt service routine */
	ret = request_irq(hist_irq, hist_isr, 0, HIST_NAME, hist_device);
	if (ret < 0) {
		pr_err("%s: request_irq failed\n", HIST_NAME);
		goto err3;
	}

	hist_status = HIST_EXE_DONE;
	sema_init(&sem, 1);
	init_waitqueue_head(&wq);
	hist_setup_cdev(hist_device, 0);

	/* create hist class */
	phist_class = class_create(THIS_MODULE, HIST_NAME);
	if (IS_ERR(phist_class)) {
		ret = PTR_ERR(phist_class);
		pr_err("%s: class_create failed\n", HIST_NAME);
		goto err4;
	}

	/* create device structure */
	hist_device->device =
	    device_create(phist_class, NULL, dev, NULL, HIST_NAME);
	if (IS_ERR(hist_device->device)) {
		ret = PTR_ERR(hist_device->device);
		pr_err("%s: device_create failed\n", HIST_NAME);
		goto err5;
	}

	pm_runtime_enable(&pdev->dev);

	pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
		HIST_NAME, DRV_HIST_VERSION_STR, MAJOR(dev), MINOR(dev));

	return 0;

err5:
	class_destroy(phist_class);
err4:
	cdev_del(&hist_device->cdev);
err3:
	iounmap(hist_device->reg_base);
err2:
	release_mem_region(HIST_BASE, HIST_SIZE);
err1:
	kfree(hist_device);
err0:
	unregister_chrdev_region(dev, hist_nr_devs);

	return ret;
}

static int __devexit hist_remove(struct platform_device *pdev)
{
	dev_t dev = MKDEV(hist_major, hist_minor);

	if (hist_device) {

		/* reset device */
		hist_runtime_resume(&pdev->dev);
		hist_reset(hist_device);
		hist_runtime_suspend(&pdev->dev);

		device_destroy(phist_class, dev);
		class_destroy(phist_class);
		cdev_del(&hist_device->cdev);
		free_irq(hist_irq, hist_device);
		iounmap(hist_device->reg_base);
		release_mem_region(HIST_BASE, HIST_SIZE);
		kfree(hist_device);
	}
	pm_runtime_disable(&pdev->dev);
	platform_set_drvdata(pdev, NULL);

	unregister_chrdev_region(dev, hist_nr_devs);

	pr_info("%s: exit\n", HIST_NAME);

	return 0;
}

static int hist_suspend(struct device *dev)
{
	int ret = 0;

	if (atomic_read(&refcount) > 0) {
		ret = -EBUSY;
	}

	DEBUG_PRINT("%s: %s: %d\n", HIST_NAME, __func__, ret);

	return ret;
}

static int hist_resume(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops hist_pm_ops = {
	.suspend = hist_suspend,
	.resume = hist_resume,
	.runtime_suspend = hist_runtime_suspend,
	.runtime_resume = hist_runtime_resume,
};

static struct platform_driver hist_driver = {
	.driver = {
		   .name = "irecog_hist",
		   .owner = THIS_MODULE,
		   .pm = &hist_pm_ops,
		   },
	.probe = hist_probe,
	.remove = hist_remove,
};

static int __init hist_init(void)
{
	return platform_driver_register(&hist_driver);
}

static void __exit hist_exit(void)
{
	platform_driver_unregister(&hist_driver);
}

module_init(hist_init);
module_exit(hist_exit);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_VERSION(DRV_HIST_VERSION_STR);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("HIST HWE module");
