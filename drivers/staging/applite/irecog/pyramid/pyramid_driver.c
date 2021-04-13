/*
 * linux/drivers/staging/applite/irecog/pyramid/pyramid_driver.c
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

#include <linux/applite/irecog/pyramid_ioctl.h>

#include "pyramid_driver.h"
#include "pyramid_setup.h"
#include "pyramid_tap_coeff.h"

#include "drv_cache.h"
#include "drv_signal.h"
#include "drv_polling.h"

static const char *drv_pyramid_version = DRV_PYRAMID_VERSION_STR;

static int pyramid_major = PYRAMID_MAJOR;
static int pyramid_minor = PYRAMID_MINOR;
static int pyramid_nr_devs = PYRAMID_NR_DEVS;
static int pyramid_irq = PYRAMID_IRQ;

module_param(pyramid_major, int, S_IRUGO | S_IWUSR);
module_param(pyramid_minor, int, S_IRUGO | S_IWUSR);
module_param(pyramid_nr_devs, int, S_IRUGO | S_IWUSR);
module_param(pyramid_irq, int, S_IRUGO | S_IWUSR);

struct pyramid_dev {
	struct cdev cdev;
	struct device *device;
	struct platform_device *pdev;
	void __iomem *reg_base;
	void __iomem *rvdmac_reg_base;
	void __iomem *rscaler_reg_base;
	unsigned long *table_adr[MAX_TABLE_NUM];
};

static struct pyramid_dev *pyramid_ctrl_dev;
static struct class *ppyramid_class;

typedef enum {
	STATE_IDLE,
	STATE_RUNNING,
} state_t;

static state_t pyramid_state = STATE_IDLE;
static wait_queue_head_t wq;
static struct semaphore sem;
static atomic_t refcount = ATOMIC_INIT(0);

static void disable_all_port(void __iomem *rvdmac_base);
static void clear_status_registers(void __iomem *rvdmac_base);
static void execute(struct pyramid_dev *dev, pyramid_param *param);
static void setup_tap_coeff_table(struct pyramid_dev *dev,
				  pyramid_param *param);

static int check_cache_param(ULONG flag)
{
	if ((flag != DRV_CACHE_FLUSH_ALL) && (flag != DRV_NO_CACHE_CTL)) {
		pr_err("%s: invalid buffer_cache_ctl:%lu\n", PYRAMID_NAME,
		       flag);
		return -1;
	}

	return 0;
}

static int pyramid_runtime_suspend(struct device *dev)
{
	unsigned int ret;
	struct platform_data *pdata = dev->platform_data;
	struct platform_device *pdev = to_platform_device(dev);
	struct pyramid_dev *priv = platform_get_drvdata(pdev);
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
		pr_err("%s: timeout occured\n", PYRAMID_NAME);
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
		pr_err("%s: timeout occured\n", PYRAMID_NAME);
		return -EIO;
	}

	bits = IRECOG_RPYRAMID_PYM_T_RUN_RUN_TP00_MASK;
	ret = drv_wait_register(priv->rvdmac_reg_base +
				IRECOG_rpyramid_PYM_T_RUN_OFFS,
				bits, 0x00, DRV_WAIT_REG_TIMEOUT);
	if ((ret & bits) != 0x0) {
		pr_err("%s: timeout occured\n", PYRAMID_NAME);
		return -EIO;
	}

	clock_enable(APPLITE_IRECOG_PYRAMID, APPLITE_IRECOG_CLOCK_DISABLE);
	return 0;
}

static int pyramid_runtime_resume(struct device *dev)
{
	struct platform_data *pdata = dev->platform_data;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	clock_enable(APPLITE_IRECOG_PYRAMID, APPLITE_IRECOG_CLOCK_ENABLE);
	return 0;
}

#if 0
/**************************************************/
/*
 * @brief pyramid_cache_flush
 *
 * @param dev
 * @param param
 *
 */
/**************************************************/
static void pyramid_cache_flush(struct pyramid_dev *dev, pyramid_param *param)
{
	int i;

	if ((param->p_clr_sel == P_CLR_SEL_Y)
	    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
		drv_cache_flush(param->input.y_adr,
				param->input.y_pitch * param->input_h_size);
	}

	if ((param->p_clr_sel == P_CLR_SEL_CBCR)
	    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
		drv_cache_flush(param->input.cb_adr,
				param->input.cb_pitch * param->input_h_size);
		drv_cache_flush(param->input.cr_adr,
				param->input.cr_pitch * param->input_h_size);
	}

	for (i = 0; i < MAX_TABLE_NUM; i++) {
		drv_cache_flush(virt_to_phys(dev->table_adr[i]),
				TAP_TABLE_SIZE * 4);
	}
}

/**************************************************/
/*
 * @brief pyramid_cache_invalidate
 *
 * @param dev
 * @param param
 *
 */
/**************************************************/
static void pyramid_cache_invalidate(struct pyramid_dev *dev,
				     pyramid_param *param)
{
	int i;

	for (i = 0; i < MAX_ROUTE; i++) {
		if ((param->p_clr_sel == P_CLR_SEL_Y)
		    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
			drv_cache_invalidate(param->output[i].y_adr,
					     param->output[i].y_pitch *
					     param->output_h_size[i]);
		}
		if (param->p_num == P_NUM_1PIC) {
			break;
		}
	}

	for (i = 0; i < MAX_ROUTE; i++) {
		if ((param->p_clr_sel == P_CLR_SEL_CBCR)
		    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
			drv_cache_invalidate(param->output[i].cb_adr,
					     param->output[i].cb_pitch *
					     param->output_h_size[i]);
		}
		if (param->p_num == P_NUM_1PIC) {
			break;
		}
	}

	for (i = 0; i < MAX_ROUTE; i++) {
		if ((param->p_clr_sel == P_CLR_SEL_CBCR)
		    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
			drv_cache_invalidate(param->output[i].cr_adr,
					     param->output[i].cr_pitch *
					     param->output_h_size[i]);
		}
		if (param->p_num == P_NUM_1PIC) {
			break;
		}
	}
}
#endif

/**************************************************/
/*
 * @brief clear status
 *
 * @param rvdmac_base
 */
/**************************************************/
static void clear_status_registers(void __iomem *rvdmac_base)
{
	unsigned long status;

	status = ioread32(rvdmac_base + IRECOG_rpyramid_PYM_STATUS_OFFS);

	iowrite32(0x00000003, rvdmac_base + IRECOG_rpyramid_PYM_STATUS_OFFS);
	iowrite32(0x00018001, rvdmac_base + IRECOG_rpyramid_PYM_INT_OFFS);
	iowrite32(0x00000007, rvdmac_base + IRECOG_rpyramid_PYM_R_STOP_OFFS);
	iowrite32(0x00000FFF, rvdmac_base + IRECOG_rpyramid_PYM_W_STOP_OFFS);
}

/**************************************************/
/*
 * @brief pyramid_ abort
 *
 * @param dev
 *
 */
/**************************************************/
static void pyramid_abort(struct pyramid_dev *dev)
{
	iowrite32(0x01,
		  dev->rscaler_reg_base +
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_RESET_OFFS));
	iowrite32(0x01, dev->rvdmac_reg_base + IRECOG_rpyramid_PYM_CTRL_OFFS);
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
	struct pyramid_dev *dev = dev_id;

	clear_status_registers(dev->rvdmac_reg_base);

	pyramid_state = STATE_IDLE;
	wake_up_interruptible(&wq);

	return IRQ_HANDLED;
}

/**************************************************/
/*
 * @brief pyramid_open
 *
 * @param inode
 * @param filp
 *
 * @retval  0 success
 * @retval -1 fail
 */
/**************************************************/
static int pyramid_open(struct inode *inode, struct file *filp)
{
	struct pyramid_dev *dev;

	dev = container_of(inode->i_cdev, struct pyramid_dev, cdev);
	filp->private_data = dev;

	if (atomic_inc_return(&refcount) == 1) {
		pyramid_runtime_resume(&dev->pdev->dev);
	}
	return 0;
}

/**************************************************/
/*
 * @brief pyramid_release
 *
 * @param inode
 * @param filp
 *
 * @retval  0 success
 * @retval -1 fail
 *
 */
/**************************************************/
static int pyramid_release(struct inode *inode, struct file *filp)
{
	struct pyramid_dev *dev;

	dev = container_of(inode->i_cdev, struct pyramid_dev, cdev);

	if (atomic_dec_return(&refcount) == 0) {
		pyramid_runtime_suspend(&dev->pdev->dev);
	}
	return 0;
}

/**************************************************/
/*
 * @brief pitch_64byte_check
 *
 * @param pitch
 *
 * @retval 0
 * @retval -EINVAL
 *
 */
/**************************************************/
static inline int pitch_64byte_check(unsigned long pitch)
{
	if ((pitch % 64) != 0) {
		return -EINVAL;
	}

	return 0;
}

/**************************************************/
/*
 * @brief parameter_check
 *
 * @param param
 *
 * @retval  0
 * @retval -EINVAL
 *
 */
/**************************************************/
static int parameter_check(pyramid_param *param)
{
	int i;

	if (param->fil_mode > FIL_MODE_NEAREST) {
		pr_err("%s: invalid fil_mode:%d\n", PYRAMID_NAME,
		       param->fil_mode);
		goto err;
	}
	if (param->p_num > P_NUM_1PIC) {
		pr_err("%s: invalid p_num:%d\n", PYRAMID_NAME, param->p_num);
		goto err;
	}
	if (param->p_clr_sel > P_CLR_SEL_YCBCR) {
		pr_err("%s: invalid p_clr_sel:%d\n", PYRAMID_NAME,
		       param->p_clr_sel);
		goto err;
	}
	if ((param->input_w_size == 0) || (param->input_h_size == 0)) {
		pr_err("%s: invalid input_w_size:%lu input_h_size:%lu\n",
		       PYRAMID_NAME, param->input_w_size, param->input_h_size);
		goto err;
	}

	/* y */
	if ((param->p_clr_sel == P_CLR_SEL_Y)
	    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
		if ((param->input.y_pitch == 0)
		    || (pitch_64byte_check(param->input.y_pitch) < 0)) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			goto err;
		}
	}

	/* cb / cr */
	if ((param->p_clr_sel == P_CLR_SEL_CBCR)
	    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
		if ((param->input.cb_pitch == 0)
		    || (pitch_64byte_check(param->input.cb_pitch) < 0)) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			goto err;
		}
		if ((param->input.cr_pitch == 0)
		    || (pitch_64byte_check(param->input.cr_pitch) < 0)) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			goto err;
		}
	}

	for (i = 0; i < MAX_ROUTE; i++) {
		if ((param->output_w_size[i] == 0)
		    || (param->output_h_size[i] == 0)) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			goto err;
		}

		if ((param->rdct_ratio[i] < 0x10000)
		    || (param->rdct_ratio[i] > 0x20000)) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			goto err;
		}

		/* y */
		if ((param->p_clr_sel == P_CLR_SEL_Y)
		    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
			if ((param->output[i].y_pitch == 0)
			    || (pitch_64byte_check(param->output[i].y_pitch) <
				0)) {
				pr_err("%s: invalid parameter.\n",
				       PYRAMID_NAME);
				goto err;
			}
		}

		/* cb / cr */
		if ((param->p_clr_sel == P_CLR_SEL_CBCR)
		    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
			if ((param->output[i].cb_pitch == 0)
			    || (pitch_64byte_check(param->output[i].cb_pitch) <
				0)) {
				pr_err("%s: invalid parameter.\n",
				       PYRAMID_NAME);
				goto err;
			}
			if ((param->output[i].cr_pitch == 0) ||
			    (pitch_64byte_check(param->output[i].cr_pitch) <
			     0)) {
				pr_err("%s: invalid parameter.\n",
				       PYRAMID_NAME);
				goto err;
			}
		}
		if (param->p_num == P_NUM_1PIC) {
			break;
		}
	}

	/* crop parameter check */
	if (param->crop_image == CROP_ENABLE) {
		if ((param->crop_size_w == 0) || (param->crop_size_h == 0)) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			goto err;
		}
		if ((param->crop_pos_x + param->crop_size_w) >
		    param->input_w_size) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			goto err;
		}
		if ((param->crop_pos_y + param->crop_size_h) >
		    param->input_h_size) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			goto err;
		}
	}

	return 0;

err:
	return -EINVAL;
}

/**************************************************/
/*
 * @brief setup_tap_coeff_table
 *
 * @param dev
 * @param param
 *
 */
/**************************************************/
static void setup_tap_coeff_table(struct pyramid_dev *dev, pyramid_param *param)
{
	int i;
	int coeff_id;

	for (i = 0; i < MAX_ROUTE; i++) {
		coeff_id = get_tap_coeff_type(param->rdct_ratio[i]);
		get_tap_coeff(coeff_id, dev->table_adr[i * 4 + 0]);
		get_tap_coeff(coeff_id, dev->table_adr[i * 4 + 1]);
		get_tap_coeff(coeff_id, dev->table_adr[i * 4 + 2]);
		get_tap_coeff(coeff_id, dev->table_adr[i * 4 + 3]);
	}
}

/**************************************************/
/*
 * @brief execute
 *
 * @param dev
 * @param param
 *
 */
/**************************************************/
static void execute(struct pyramid_dev *dev, pyramid_param *param)
{
	int i;

	clear_status_registers(dev->rvdmac_reg_base);
	disable_all_port(dev->rvdmac_reg_base);

	if ((param->p_clr_sel == P_CLR_SEL_Y)
	    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
		/* read port setting (Y) */
		setup_read_port(dev->rvdmac_reg_base,
				0,
				PYM_ENABLE,
				param->input.y_adr,
				param->input_w_size,
				param->input_h_size, param->input.y_pitch);
	}
	if ((param->p_clr_sel == P_CLR_SEL_CBCR)
	    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
		/* read port setting (Cb) */
		setup_read_port(dev->rvdmac_reg_base,
				1,
				PYM_ENABLE,
				param->input.cb_adr,
				param->input_w_size,
				param->input_h_size, param->input.cb_pitch);
		/* read port setting (Cr) */
		setup_read_port(dev->rvdmac_reg_base,
				2,
				PYM_ENABLE,
				param->input.cr_adr,
				param->input_w_size,
				param->input_h_size, param->input.cr_pitch);
	}

	/* write port setting (Y) */
	for (i = 0; i < MAX_ROUTE; i++) {
		if ((param->p_clr_sel == P_CLR_SEL_Y)
		    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
			setup_write_port(dev->rvdmac_reg_base, i, PYM_ENABLE,
					 param->output[i].y_adr,
					 param->output_w_size[i],
					 param->output_h_size[i],
					 param->output[i].y_pitch);
		}
		if (param->p_num == P_NUM_1PIC) {
			break;
		}
	}

	/* write port setting (Cb) */
	for (i = 0; i < MAX_ROUTE; i++) {
		if ((param->p_clr_sel == P_CLR_SEL_CBCR)
		    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
			setup_write_port(dev->rvdmac_reg_base, i + 4,
					 PYM_ENABLE, param->output[i].cb_adr,
					 param->output_w_size[i],
					 param->output_h_size[i],
					 param->output[i].cb_pitch);
		}
		if (param->p_num == P_NUM_1PIC) {
			break;
		}
	}

	/* write port setting (Cr) */
	for (i = 0; i < MAX_ROUTE; i++) {
		if ((param->p_clr_sel == P_CLR_SEL_CBCR)
		    || (param->p_clr_sel == P_CLR_SEL_YCBCR)) {
			setup_write_port(dev->rvdmac_reg_base, i + 8,
					 PYM_ENABLE, param->output[i].cr_adr,
					 param->output_w_size[i],
					 param->output_h_size[i],
					 param->output[i].cr_pitch);
		}
		if (param->p_num == P_NUM_1PIC) {
			break;
		}
	}

	/* copy tap table */
	setup_tap_coeff_table(dev, param);

	/* table port setting */
	if ((param->fil_mode == FIL_MODE_8TAP_8OVS)
	    || (param->fil_mode == FIL_MODE_4TAP_16OVS)) {
		for (i = 0; i < MAX_TABLE_NUM; i++) {
			setup_table_port(dev->rvdmac_reg_base,
					 i,
					 PYM_ENABLE,
					 virt_to_phys(dev->table_adr[i]),
					 TAP_TABLE_SIZE * 4);
		}
	}

	/* setup rscaler */
	setup_rscaler(dev->rscaler_reg_base, param);

	/* cache control */
	if (param->buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
#if 0
		/*pyramid_cache_flush(dev, param); */
		/*pyramid_cache_invalidate(dev, param); */
#else
		drv_cache_flush_all();
#endif

	}

	pyramid_state = STATE_RUNNING;
	iowrite32(0x01,
		  dev->rscaler_reg_base +
		  RSCALER_OFFSET(IRECOG_rpyramid_RSCALER_CS_START_OFFS));
}

/**************************************************/
/*
 * @brief pyramid_ioctl
 *
 * @param filp
 * @param cmd
 * @param val
 *
 * @retval  0 success
 *
 */
/**************************************************/
static long pyramid_ioctl(struct file *filp, unsigned int cmd,
			  unsigned long val)
{
	struct pyramid_dev *dev = filp->private_data;
	pyramid_param param;
	long ret = 0;
	sigset_t oldset;

	switch (cmd) {

	case PYRAMID_IOCTL_SHRINK_1IMAGE:
		if (copy_from_user
		    ((void *)&param, (const void __user *)val,
		     sizeof(pyramid_param))) {
			pr_err("%s: copy_from_user failed.\n", PYRAMID_NAME);
			return -EFAULT;
		}

		if (parameter_check(&param) < 0) {
			pr_err("%s: invalid parameter.\n", PYRAMID_NAME);
			return -EINVAL;
		}
		if (check_cache_param(param.buffer_cache_ctl) < 0) {
			return -EINVAL;
		}

		if (down_interruptible(&sem)) {
			pr_err("%s: down interruptible failed.\n",
			       PYRAMID_NAME);
			return -ERESTARTSYS;
		}
		if (pyramid_state != STATE_IDLE) {
			pr_err("%s: invalid state\n", PYRAMID_NAME);
			up(&sem);
			return -EAGAIN;
		}

		execute(dev, &param);

		/* signal mask */
		drv_sigmask(&oldset);
		if (wait_event_interruptible(wq, (pyramid_state == STATE_IDLE))) {

			/* signal unmask */
			drv_sigunmask(&oldset);

			pr_err("%s: wait event interruptible fail.\n",
			       PYRAMID_NAME);

			pyramid_state = STATE_IDLE;
			pyramid_abort(dev);
			up(&sem);

			return -ERESTARTSYS;
		}
		/* signal unmask */
		drv_sigunmask(&oldset);
		up(&sem);

		break;

	case PYRAMID_IOCTL_GET_VERSION:
		{
			drv_version_t version_param;

			memset(&version_param, 0x00, sizeof(drv_version_t));
			memcpy(version_param.version, drv_pyramid_version,
			       strlen(drv_pyramid_version));

			if (copy_to_user((void __user *)val,
					 (void *)&version_param,
					 sizeof(drv_version_t))) {
				pr_err("%s: copy_to_user failed version\n",
				       PYRAMID_NAME);
				return -EFAULT;
			}
		}
		break;

	case PYRAMID_IOCTL_INITIALIZE:
		if (!dev->rvdmac_reg_base) {
			pr_err("%s: initialize failed.\n", PYRAMID_NAME);
			return -EFAULT;
		}
		initialize(dev->rvdmac_reg_base);
		break;

	default:
		pr_err("%s: invalid ioctl command 0x%x\n", PYRAMID_NAME, cmd);
		return -EINVAL;
		break;
	}

	return ret;
}

/**************************************************/
/*
 * @brief disable all port
 *
 * @param rvdmac_base
 */
/**************************************************/
static void disable_all_port(void __iomem *rvdmac_base)
{
	/* disable read port */
	iowrite32(0x00000000, rvdmac_base + IRECOG_rpyramid_PYM_R_ENABLE_OFFS);
	/* disable write port */
	iowrite32(0x00000000, rvdmac_base + IRECOG_rpyramid_PYM_W_ENABLE_OFFS);
	/* disable table port */
	iowrite32(0x00000000, rvdmac_base + IRECOG_rpyramid_PYM_T_ENABLE_OFFS);
}

static const struct file_operations pyramid_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = pyramid_ioctl,
	.open = pyramid_open,
	.release = pyramid_release,
};

/**************************************************/
/*
 * @brief pyramid_setup_cdev
 *
 * @param dev
 * @param index
 *
 */
/**************************************************/
static void pyramid_setup_cdev(struct pyramid_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(pyramid_major, pyramid_minor + index);

	cdev_init(&dev->cdev, &pyramid_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev %d\n", PYRAMID_NAME, index);
	}
}

/**************************************************/
/*
 * @brief pyramid_probe
 *
 * @retval  0 success
 *
 */
/**************************************************/
static int __devinit pyramid_probe(struct platform_device *pdev)
{
	int i;
	int ret = 0;
	dev_t dev = 0;

	/* allocation of device number */
	if (pyramid_major) {
		dev = MKDEV(pyramid_major, pyramid_minor);
		ret =
		    register_chrdev_region(dev, pyramid_nr_devs, PYRAMID_NAME);
	} else {
		ret =
		    alloc_chrdev_region(&dev, pyramid_minor, pyramid_nr_devs,
					PYRAMID_NAME);
		pyramid_major = MAJOR(dev);
	}
	if (ret < 0) {
		pr_err("%s: can't get major %d\n", PYRAMID_NAME, pyramid_major);
		return ret;
	}
	pyramid_ctrl_dev = kmalloc(sizeof(struct pyramid_dev), GFP_KERNEL);
	if (!pyramid_ctrl_dev) {
		pr_err("%s: kmalloc failed\n", PYRAMID_NAME);
		ret = -ENOMEM;
		goto err0;
	}
	memset(pyramid_ctrl_dev, 0, sizeof(struct pyramid_dev));

	pyramid_ctrl_dev->pdev = pdev;
	platform_set_drvdata(pdev, pyramid_ctrl_dev);

	/* mapping of pyramid MMIO */
	if (!request_mem_region(PYRAMID_BASE, PYRAMID_SIZE, PYRAMID_NAME)) {
		pr_err("%s: request_mem_region failed.\n", PYRAMID_NAME);
		ret = -ENODEV;
		goto err1;
	}
	pyramid_ctrl_dev->reg_base =
	    ioremap_nocache(PYRAMID_BASE, PYRAMID_SIZE);
	if (!pyramid_ctrl_dev->reg_base) {
		ret = -ENODEV;
		pr_err("%s: ioremap_nocache failed.\n", PYRAMID_NAME);
		goto err2;
	}

	pyramid_ctrl_dev->rvdmac_reg_base =
	    pyramid_ctrl_dev->reg_base + PYM_BASE;
	pyramid_ctrl_dev->rscaler_reg_base =
	    pyramid_ctrl_dev->reg_base + RSCALER_BASE;

	/* register interrupt service routine */
	ret =
	    request_irq(pyramid_irq, pyramid_isr, 0, PYRAMID_NAME,
			pyramid_ctrl_dev);
	if (ret < 0) {
		pr_err("%s: request_irq failed.\n", PYRAMID_NAME);
		goto err2;
	}

	for (i = 0; i < MAX_TABLE_NUM; i++) {
		pyramid_ctrl_dev->table_adr[i] =
		    kmalloc(sizeof(unsigned long) * TAP_TABLE_SIZE,
			    GFP_KERNEL | GFP_DMA);
		if (!pyramid_ctrl_dev->table_adr[i]) {
			ret = -ENOMEM;
			pr_err("%s: kmalloc failed.\n", PYRAMID_NAME);
			goto err3;
		}
	}

	pyramid_state = STATE_IDLE;
	sema_init(&sem, 1);
	init_waitqueue_head(&wq);
	pyramid_setup_cdev(pyramid_ctrl_dev, 0);

	/* create pyramid class */
	ppyramid_class = class_create(THIS_MODULE, PYRAMID_NAME);
	if (IS_ERR(ppyramid_class)) {
		ret = PTR_ERR(ppyramid_class);
		pr_err("%s: class_create failed\n", PYRAMID_NAME);
		goto err4;
	}

	/* create device structure */
	pyramid_ctrl_dev->device =
	    device_create(ppyramid_class, NULL, dev, NULL, PYRAMID_NAME);
	if (IS_ERR(pyramid_ctrl_dev->device)) {
		ret = PTR_ERR(pyramid_ctrl_dev->device);
		pr_err("%s: device_create failed\n", PYRAMID_NAME);
		goto err5;
	}

	pm_runtime_enable(&pdev->dev);

	pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
		PYRAMID_NAME, DRV_PYRAMID_VERSION_STR, MAJOR(dev), MINOR(dev));
	return 0;

err5:
	class_destroy(ppyramid_class);
err4:
	cdev_del(&pyramid_ctrl_dev->cdev);

err3:
	for (i = 0; i < MAX_TABLE_NUM; i++) {
		kfree(pyramid_ctrl_dev->table_adr[i]);
	}

err2:
	release_mem_region(PYRAMID_BASE, PYRAMID_SIZE);
err1:
	kfree(pyramid_ctrl_dev);
err0:
	unregister_chrdev_region(dev, pyramid_nr_devs);

	return ret;
}

/**************************************************/
/*
 * @brief pyramid_remove
 *
 */
/**************************************************/
static int __devexit pyramid_remove(struct platform_device *pdev)
{
	int i;
	dev_t dev = MKDEV(pyramid_major, pyramid_minor);

	if (pyramid_ctrl_dev) {
		device_destroy(ppyramid_class, dev);
		class_destroy(ppyramid_class);

		cdev_del(&pyramid_ctrl_dev->cdev);
		free_irq(pyramid_irq, pyramid_ctrl_dev);

		iounmap(pyramid_ctrl_dev->reg_base);
		release_mem_region(PYRAMID_BASE, PYRAMID_SIZE);

		for (i = 0; i < MAX_TABLE_NUM; i++) {
			kfree(pyramid_ctrl_dev->table_adr[i]);
		}
		kfree(pyramid_ctrl_dev);
	}
	pm_runtime_disable(&pdev->dev);
	platform_set_drvdata(pdev, NULL);

	unregister_chrdev_region(dev, pyramid_nr_devs);

	pr_info("%s: exit\n", PYRAMID_NAME);
	return 0;
}

static int pyramid_suspend(struct device *dev)
{
	int ret = 0;

	if (atomic_read(&refcount) > 0) {
		ret = -EBUSY;
	}

	pr_debug("%s: %s: %d\n", PYRAMID_NAME, __func__, ret);

	return ret;
}

static int pyramid_resume(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops pyramid_pm_ops = {
	.suspend = pyramid_suspend,
	.resume = pyramid_resume,
	.runtime_suspend = pyramid_runtime_suspend,
	.runtime_resume = pyramid_runtime_resume,
};

static struct platform_driver pyramid_driver = {
	.driver = {
		   .name = "irecog_pyramid",
		   .owner = THIS_MODULE,
		   .pm = &pyramid_pm_ops,
		   },
	.probe = pyramid_probe,
	.remove = pyramid_remove,
};

static int __init pyramid_init(void)
{
	return platform_driver_register(&pyramid_driver);
}

static void __exit pyramid_exit(void)
{
	platform_driver_unregister(&pyramid_driver);
}

module_init(pyramid_init);
module_exit(pyramid_exit);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_VERSION(DRV_PYRAMID_VERSION_STR);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Pyramid HWE module");
