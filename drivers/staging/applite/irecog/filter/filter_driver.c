/*
 * linux/drivers/staging/applite/irecog/filter/filter_driver.c
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
#include <linux/delay.h>

#include <mach/hardware.h>
#include <mach/regs/cpu_memmap_def.h>
#include <mach/regs/pmu_reg_def.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/platform_data/applite_irecog.h>

#include <linux/applite/irecog/filter_ioctl.h>
#include <linux/applite/irecog/filter_param.h>

#include "filter_public.h"
#include "filter_driver.h"

#include "sl_filter.h"
#include "sl_sequenceid.h"
#include "filter_util.h"
#include "filter_parameter.h"
#include "filter_define.h"

#include "drv_cache.h"
#include "drv_signal.h"
#include "drv_polling.h"
#include "drv_dmabuf.h"

#define FPARAM_UINT_SIZE 64

/*#include "dbg_print.h" */
#define print_err(fmt, ...) \
	do { \
		pr_err("%s: ", FILTER_NAME); pr_err(fmt, ##__VA_ARGS__);\
	} while (0)

static const char *drv_filter_version = DRV_FILTER_VERSION_STR;

static int filter_major = FILTER_MAJOR;
static int filter_minor = FILTER_MINOR;
static int filter_nr_devs = FILTER_NR_DEVS;
static int filter_irq = FILTER_IRQ;

module_param(filter_major, int, S_IRUGO | S_IWUSR);
module_param(filter_minor, int, S_IRUGO | S_IWUSR);
module_param(filter_nr_devs, int, S_IRUGO | S_IWUSR);
module_param(filter_irq, int, S_IRUGO | S_IWUSR);

static struct filter_dev_set *filter_device_set;
static struct class *pfilter_class;

static int filter_status = FILTER_STATUS_EXE_DONE;
static wait_queue_head_t wq;
static struct semaphore sem;
static atomic_t refcount = ATOMIC_INIT(0);

static int check_cache_param(ULONG flag)
{
	if (flag != DRV_CACHE_FLUSH_ALL) {
		pr_err("%s: invalid buffer_cache_ctl:%lu\n", FILTER_NAME, flag);
		return -1;
	}

	return 0;
}

static int filter_correct_color_conv_address(struct filter_dev *dev,
					     struct filter_correct_color_param
					     *param,
					     struct drv_dmabuf_conv_adr
					     conv_addr[])
{
	int i;

	for (i = 0; i < 6; i++) {
		memset(&conv_addr[i], 0x00, sizeof(conv_addr[i]));
	}

	if (drv_dmabuf_get_phys_addr
	    (dev->device, param->src_y_fd, &conv_addr[0], DMA_TO_DEVICE) < 0) {
		return -1;
	}

	if (drv_dmabuf_get_phys_addr
	    (dev->device, param->src_u_fd, &conv_addr[1], DMA_TO_DEVICE) < 0) {
		return -1;
	}

	if (drv_dmabuf_get_phys_addr
	    (dev->device, param->src_v_fd, &conv_addr[2], DMA_TO_DEVICE) < 0) {
		return -1;
	}

	if (drv_dmabuf_get_phys_addr
	    (dev->device, param->src_tonemapped_y_fd, &conv_addr[3],
	     DMA_TO_DEVICE) < 0) {
		return -1;
	}

	if (drv_dmabuf_get_phys_addr
	    (dev->device, param->dst_u_fd, &conv_addr[4],
	     DMA_FROM_DEVICE) < 0) {
		return -1;
	}

	if (drv_dmabuf_get_phys_addr
	    (dev->device, param->dst_v_fd, &conv_addr[5],
	     DMA_FROM_DEVICE) < 0) {
		return -1;
	}

	return 0;
}

static int filter_correct_color_free_address(struct drv_dmabuf_conv_adr
					     conv_addr[])
{
	drv_dmabuf_put_phys_addr(&conv_addr[0], DMA_TO_DEVICE);
	drv_dmabuf_put_phys_addr(&conv_addr[1], DMA_TO_DEVICE);
	drv_dmabuf_put_phys_addr(&conv_addr[2], DMA_TO_DEVICE);
	drv_dmabuf_put_phys_addr(&conv_addr[3], DMA_TO_DEVICE);
	drv_dmabuf_put_phys_addr(&conv_addr[4], DMA_FROM_DEVICE);
	drv_dmabuf_put_phys_addr(&conv_addr[5], DMA_FROM_DEVICE);

	return 0;
}

static int filter_tomemapping_luma_conv_address(struct filter_dev *dev,
						struct
						filter_tonemapping_luma_param
						*param,
						struct drv_dmabuf_conv_adr
						*src_addr,
						struct drv_dmabuf_conv_adr
						*dst_addr)
{
	if (drv_dmabuf_get_phys_addr(dev->device,
				     param->src_fd,
				     src_addr, DMA_TO_DEVICE) < 0) {
		return -1;
	}

	if (drv_dmabuf_get_phys_addr(dev->device,
				     param->dst_fd,
				     dst_addr, DMA_FROM_DEVICE) < 0) {
		return -1;
	}

	return 0;
}

static int filter_tonemapping_free_address(struct drv_dmabuf_conv_adr *src_addr,
					   struct drv_dmabuf_conv_adr *dst_addr)
{
	drv_dmabuf_put_phys_addr(src_addr, DMA_TO_DEVICE);
	drv_dmabuf_put_phys_addr(dst_addr, DMA_FROM_DEVICE);

	return 0;
}

static int filter_conv_address(struct filter_dev *dev,
			       int num,
			       int fd[],
			       struct drv_dmabuf_conv_adr conv_addr[], int dir)
{
	int i;
	for (i = 0; i < num; i++) {
		memset(&conv_addr[i], 0x00, sizeof(conv_addr[i]));
		if (drv_dmabuf_get_phys_addr
		    (dev->device, fd[i], &conv_addr[i], dir)) {
			pr_err("%s : fd[%d]:%d\n", FILTER_NAME, i, fd[i]);
			return -1;
		}
	}

	return 0;
}

static int filter_free_address(int num,
			       struct drv_dmabuf_conv_adr conv_addr[], int dir)
{
	int i;
	for (i = 0; i < num; i++) {
		drv_dmabuf_put_phys_addr(&conv_addr[i], dir);
	}
	return 0;
}

static int filter_runtime_suspend(struct device *dev)
{
	unsigned int ret;
	struct platform_data *pdata = dev->platform_data;
	struct platform_device *pdev = to_platform_device(dev);
	struct filter_dev *priv = platform_get_drvdata(pdev);
	unsigned long bits;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	iowrite32(0x0, priv->reg_base + FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	ret = drv_wait_register(priv->reg_base +
				FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS),
				IRECOG_RFILTER_CMD_CMD_MASK,
				0x0, DRV_WAIT_REG_TIMEOUT);
	if ((ret & IRECOG_RFILTER_CMD_CMD_MASK) != 0x0) {
		pr_err("%s: timeout occured\n", FILTER_NAME);
		return -EIO;
	}

	bits = IRECOG_RFILTER_TRNSSTAT_PT_MASK |
	    IRECOG_RFILTER_TRNSSTAT_OIT_MASK | IRECOG_RFILTER_TRNSSTAT_IIT_MASK;
	ret = drv_wait_register(priv->reg_base +
				FILTER_OFFSET(IRECOG_rfilter_TRNSSTAT_OFFS),
				bits, 0x00, DRV_WAIT_REG_TIMEOUT);
	if ((ret & bits) != 0x0) {
		pr_err("%s: timeout occured\n", FILTER_NAME);
		return -EIO;
	}

	clock_enable(APPLITE_IRECOG_FILTER, APPLITE_IRECOG_CLOCK_DISABLE);
	return 0;
}

static int filter_runtime_resume(struct device *dev)
{
	struct platform_data *pdata = dev->platform_data;

	void (*clock_enable) (unsigned int, int) =
	    ((struct applite_irecog_platform_data *)pdata)->clock_enable;

	clock_enable(APPLITE_IRECOG_FILTER, APPLITE_IRECOG_CLOCK_ENABLE);
	return 0;
}

static inline void filter_init_kick(struct filter_dev *dev, REG_32 reg_val)
{
	if (reg_val == 0x1) {
		filter_status = FILTER_STATUS_INIT_KICKED;
	}
	iowrite32(reg_val,
		  dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_INITSTART_OFFS));
}

static inline long filter_clear_int(struct filter_dev *dev)
{
	unsigned int ret;

	iowrite32(FILTER_CLEAR_BITS,
		  dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_INTCLR_OFFS));
	ret =
	    drv_wait_register(dev->reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_INTSTAT_OFFS),
			      FILTER_CLEAR_BITS, 0x0, DRV_WAIT_REG_TIMEOUT);
	if ((ret & FILTER_CLEAR_BITS) != 0x0) {
		pr_err
		    ("%s: timeout occured while waiting for register value to change\n",
		     FILTER_NAME);
		return -EIO;
	}

	return 0;
}

static inline long filter_reset(struct filter_dev *dev)
{
	unsigned int ret;

	iowrite32(0x1, dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_RST_OFFS));
	/* wait for reset completion */
	ret =
	    drv_wait_register(dev->reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_RST_OFFS),
			      0xffffffff, 0x0, DRV_WAIT_REG_TIMEOUT);
	if (ret != 0x0) {
		pr_err
		    ("%s: timeout occured while waiting for register value to change\n",
		     FILTER_NAME);
		return -EIO;
	}

	iowrite32(0x1, dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	ret =
	    drv_wait_register(dev->reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS),
			      0xffffffff, 0x1, DRV_WAIT_REG_TIMEOUT);
	if (ret != 0x1) {
		pr_err
		    ("%s: timeout occured while waiting for register value to change\n",
		     FILTER_NAME);
		return -EIO;
	}

	return 0;
}

static inline long filter_init_cmd(struct filter_dev *dev)
{
	unsigned int ret;

	iowrite32(0x0, dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	ret =
	    drv_wait_register(dev->reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS),
			      0xffffffff, 0x0, DRV_WAIT_REG_TIMEOUT);
	if (ret != 0x0) {
		pr_err
		    ("%s: timeout occured while waiting for register value to change\n",
		     FILTER_NAME);
		return -EIO;
	}
	iowrite32(0x1, dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	ret =
	    drv_wait_register(dev->reg_base +
			      FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS),
			      0xffffffff, 0x1, DRV_WAIT_REG_TIMEOUT);
	if (ret != 0x1) {
		pr_err
		    ("%s: timeout occured while waiting for register value to change\n",
		     FILTER_NAME);
		return -EIO;
	}

	return 0;
}

static void filter_write_register_number_info(struct filter_dev *dev,
					      FILTER_DESCRIPT *descript)
{
	iowrite32(descript->info.inittrnum,
		  dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_INITTRNUM_OFFS));
	iowrite32(descript->info.imgfrmchnum,
		  dev->reg_base +
		  FILTER_OFFSET(IRECOG_rfilter_IMGFRMCHNUM_OFFS));
	iowrite32(descript->info.prmtrnum,
		  dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_PRMTRNUM_OFFS));
}

static void filter_write_register_image_size(struct filter_dev *dev,
					     FILTER_DESCRIPT *descript)
{
	UINT i;

	for (i = 0; i < FILTER_HW_IMG_SIZE; i++) {
		if (i % 2) {
			/* img size */
			iowrite32(((UINT *)&descript->image_set)[i],
				  dev->reg_base +
				  FILTER_OFFSET
				  (IRECOG_rfilter_OIMG0INITADDR_OFFS) + i * 4);
		} else {
			if (((UINT *)&descript->image_set)[i + 1]) {
				/* img addr */
				iowrite32(((UINT *)&descript->image_set)[i],
					  dev->reg_base +
					  FILTER_OFFSET
					  (IRECOG_rfilter_OIMG0INITADDR_OFFS) +
					  i * 4);
			}
		}
	}
}

static void filter_write_register_init_param(struct filter_dev *dev,
					     FILTER_DESCRIPT *descript)
{
	UINT i;

	for (i = 0; i < FILTER_HW_INIT_SIZE; i++) {
		if (i % 2) {
			/* init param size */
			iowrite32(((UINT *)&descript->init_param)[i],
				  dev->reg_base +
				  FILTER_OFFSET(IRECOG_rfilter_DINITIADDR0_OFFS)
				  + i * 4);
		} else {
			/* init param address */
			if (((UINT *)&descript->init_param)[i + 1]) {
				iowrite32(((UINT *)&descript->init_param)[i],
					  dev->reg_base +
					  FILTER_OFFSET
					  (IRECOG_rfilter_DINITIADDR0_OFFS) +
					  i * 4);
			}
		}
	}
}

/**
 * filter_driver
 */
/**
 * @brief Filter Module Initialization
 * @retval Success : Main Bus Address , Fail: NULL
 */
SSHORT *dd_FILTER_get_HIF_address(struct filter_dev *dev, SINT sequence_id,
				      /**< Filter Sequence Id */
				  UINT HIF_address)
{
/**< HIF Address */
	SSHORT *hif_address;
	UINT *transbase;
	UINT trans_num;
	UINT hif_size;
	UINT address;
	UINT index;
	UINT i;
	UINT filter_base_addr;
	UINT *filter_param;
	SSHORT *retval = NULL;

	/* Filter Parameter Table Base Address */
	filter_base_addr = (UINT)(unsigned long)dev->param_base;	/* dd_get_filter_base_address(); */
	filter_param = (UINT *)filter_base_addr;

	/* Check Sequence Id */
	if ((sequence_id < 0) ||
	    (filter_param[FILTER_SEQUENCE_NUM] <= (UINT)sequence_id)) {
		print_err("Invalid sequence id %d\n", sequence_id);
		return retval;
	}

	/* Get Index of The Sequence Transaction Info Base */
	index = (UINT)(sequence_id + FILTER_SEQUENCE_OFFSET);

#ifdef ENABLE_QEMU_FPARAM
	transbase = (UINT *)(filter_param[index] + filter_base_addr);
#else
	/* for speyside board */
	dev->filter_base_phys = filter_param[index];
	dev->filter_base_virt = phys_to_virt(filter_param[index]);

	transbase = (UINT *)dev->filter_base_virt;
#endif

	if (transbase[FILTER_TRANS_NUM] > FILTER_TRNUM_MAX) {
		print_err("Invalid Transaction Number %d\n",
			  transbase[FILTER_TRANS_NUM]);
		return retval;
	}

	/* Set Trunsaction Number */
	trans_num = transbase[FILTER_TRANS_NUM];
	for (i = 0; i < trans_num; i++) {

#ifdef ENABLE_QEMU_FPARAM

		/* Set Uncache Address */
#if 1				/* Vis2, qemu-speyside-1.0.0 */
		hif_address
		    =
		    (SSHORT *)(transbase[(i * 3) + FILTER_PARAM_OFFSET_ADDR] +
			       filter_base_addr);
#else
		/* previous qemu-speyside-1.0.0 */
		/* plus Program Addr Offset */
		hif_address
		    =
		    (SSHORT *)(transbase[(i * 3) + FILTER_PARAM_OFFSET_ADDR] +
			       filter_base_addr + filter_param[index]);
#endif

#else
		/* for speyside board */
		hif_address
		    =
		    (SSHORT *)(transbase[(i * 3) + FILTER_PARAM_OFFSET_ADDR] +
			       (UINT)dev->filter_base_virt);

#endif

		/* In SHORT Word Size */
		hif_size = (transbase[(i * 3) + FILTER_PARAM_SIZE] * 64) / 2;
		address = transbase[(i * 3) + FILTER_PARAM_HIF_ADDR];

		/* Check If The Data is In Current Region */
		if ((address <= HIF_address)
		    && ((address + hif_size) > HIF_address)) {
			retval = hif_address + (HIF_address - address);

			break;
		}
	}

	return retval;
}

static SINT dd_filter_start(struct filter_dev *dev,
			    FILTER_DESCRIPT *descript, UINT mode,
			    UINT sequence_id)
{
	FILTER_DESCRIPT *pqueue;
	UINT *plqueue;
	UINT param_id;
	SSHORT *ioc_addr;

	if (filter_reset(dev) < 0) {
		return -1;
	}
	if (filter_init_cmd(dev) < 0) {
		return -1;
	}
	if (filter_clear_int(dev) < 0) {
		return -1;
	}

	/* Write Register DATA */
	pqueue = descript;
	plqueue = (UINT *)pqueue;

	/* Mask mode & sequence id */
	plqueue[0] &= FILTER_INITTRNUM_MASK;

	/* Copy Number Info */
	filter_write_register_number_info(dev, pqueue);

	/* Copy Image Size */
	filter_write_register_image_size(dev, pqueue);

	/* Set Int Mask, Currently No Parameter Trans. */
	iowrite32(FILTER_INTMASK_SEQ_FRAME,
		  dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_INTMASK_OFFS));

	/* Kick Filter */
	/* Override IOC data */
#if 0
	pqueue->ioc_addr[FILTER_HIFIOC_IHWID_OFFSET]
	    = (SSHORT)pqueue->ihwid;
	pqueue->ioc_addr[FILTER_HIFIOC_IHWIDBL_OFFSET]
	    = (SSHORT)pqueue->ihwidbl;
	pqueue->ioc_addr[FILTER_HIFIOC_IVWID_OFFSET]
	    = (SSHORT)pqueue->ivwid;
	pqueue->ioc_addr[FILTER_HIFIOC_IVWIDBL_OFFSET]
	    = (SSHORT)pqueue->ivwidbl;
	pqueue->ioc_addr[FILTER_HIFIOC_HEND_OFFSET] = pqueue->hend;
	pqueue->ioc_addr[FILTER_HIFIOC_VEND_OFFSET] = pqueue->vend;
#else
	ioc_addr = (SSHORT *)(pqueue->ioc_addr + FILTER_HIFIOC_IHWID_OFFSET);
	*ioc_addr = (SSHORT)pqueue->ihwid;
	ioc_addr = (SSHORT *)(pqueue->ioc_addr + FILTER_HIFIOC_IHWIDBL_OFFSET);
	*ioc_addr = (SSHORT)pqueue->ihwidbl;
	ioc_addr = (SSHORT *)(pqueue->ioc_addr + FILTER_HIFIOC_IVWID_OFFSET);
	*ioc_addr = (SSHORT)pqueue->ivwid;
	ioc_addr = (SSHORT *)(pqueue->ioc_addr + FILTER_HIFIOC_IVWIDBL_OFFSET);
	*ioc_addr = (SSHORT)pqueue->ivwidbl;
	ioc_addr = (SSHORT *)(pqueue->ioc_addr + FILTER_HIFIOC_HEND_OFFSET);
	*ioc_addr = pqueue->hend;
	ioc_addr = (SSHORT *)(pqueue->ioc_addr + FILTER_HIFIOC_VEND_OFFSET);
	*ioc_addr = pqueue->vend;
#endif

	/* Copy Init Param */
	filter_write_register_init_param(dev, descript);

	/* Overwrite HIF Paramter If Needed */
	for (param_id = 0; param_id < pqueue->hif_param_num; param_id++) {
#if 0
		*pqueue->hif_param[param_id].addr
		    = pqueue->hif_param[param_id].data;
#else
		SSHORT *hif_param_addr;
		hif_param_addr = (SSHORT *)pqueue->hif_param[param_id].addr;
		*hif_param_addr = pqueue->hif_param[param_id].data;
#endif
	}

	/* cache control */
	if (dev->buffer_cache_ctl & DRV_CACHE_FLUSH_ALL) {
		drv_cache_flush_all();
	}

	/* Kick Init Param Trans */
	filter_init_kick(dev, 0x1);

	return 0;
}

SINT dd_FILTER_send_request(struct filter_dev *dev, FILTER_DESCRIPT *descript)
{
	UINT mode;
	UINT sequence_id;

	mode = descript->info.mode;
	sequence_id = descript->info.sequence_id;

	return dd_filter_start(dev, descript, mode, sequence_id);
}

/* --------------------------------------------------------------------- */
static SINT dd_filter_div(struct filter_dev *dev, UCHAR *dst, UCHAR *src,
			  UINT width, UINT height, UINT pitch)
{
	FILTER_PARAMETER parameter;
	FILTER_DESCRIPT descript;
	SINT ret;
	SINT i;
	UCHAR *src1;
	UCHAR *src2;

	src1 = src;
	src2 = src;

	/* ----- get_sequence_id (SL_FILTER_ID_DIV) ----- */
	parameter.sequence_id = (SL_FILTER_ID_DIV * 10) + ((width - 1) >> 7);

	/* ----- set_parameter ----- */
	parameter.frame_num = 1;

	parameter.width = (USHORT)width;
	parameter.height = (USHORT)height;

	parameter.in_channel_num = 2;
	parameter.in_channel_info[0].addr = (UINT)src1;
	parameter.in_channel_info[1].addr = (UINT)src2;

	for (i = 0; i < 2; i++) {
		parameter.in_channel_info[i].ratio = FILTER_RATIO_1HV;
		parameter.in_channel_info[i].bit_accuracy = FILTER_BITACC_U8;
		parameter.in_channel_info[i].line_offset = pitch - width;
	}

	parameter.out_channel_num = 1;
	parameter.out_channel_info[0].addr = (UINT)dst;
	parameter.out_channel_info[0].ratio = FILTER_RATIO_1HV;
	parameter.out_channel_info[0].bit_accuracy = FILTER_BITACC_U8;
	parameter.out_channel_info[0].line_offset = pitch - width;

	for (i = 1; i < 4; i++) {
		descript.image_set[i * 2].initaddr = 0;
		descript.image_set[i * 2].ratiooffset = 0;
		descript.image_set[(i * 2) + 1].initaddr = 0;
		descript.image_set[(i * 2) + 1].ratiooffset = 0;
	}

	parameter.hif_param_num = 0;
	parameter.hif_param = NULL;

	ret = dd_FILTER_config_param(dev, &descript, &parameter);

	/* send request */
	if (ret == 0) {
		ret = dd_FILTER_send_request(dev, &descript);
	}

	return ret;
}

/* --------------------------------------------------------------------- */
#define WAIT_TIME_FILTER_RESET_1 (300)	/* wait time */

static UINT get_time_us(void)
{
	struct timeval tv;
	do_gettimeofday(&tv);

	return (UINT)tv.tv_usec;
}

static SINT s_check_wait_time(UINT t_start, UINT t_end, UINT th)
{
	UINT time;
	SINT ret;

	if (t_start <= t_end) {
		time = t_end - t_start;
	} else {
		time = ((1000 * 1000 - t_start) + t_end) + 1;
	}

	if (time >= th) {
		ret = -1;
	} else {
		ret = 0;
	}
	return ret;
}


static SINT dd_filter_bus_init_local(struct filter_dev *dev)
{
	UINT i;
	SINT req = 0;
	UINT width = 128;
	UINT height = 4;
	UINT pitch = 128;
	unsigned long long t1, t2;
	UCHAR *src;
	UCHAR *dst;
	UINT reg_value_1, reg_value_2;
	UINT reg_val;
	SINT wait_time;

	if (filter_status != FILTER_STATUS_EXE_DONE) {
		pr_err("%s: invalid status.\n", FILTER_NAME);
		return -1;
	}

	src = kmalloc(height * pitch * sizeof(char), GFP_KERNEL);
	if (src == NULL) {
		pr_err("%s: kmalloc fail\n", FILTER_NAME);
		return -1;
	}

	dst = kmalloc(height * pitch * sizeof(char), GFP_KERNEL);
	if (dst == NULL) {
		kfree(src);
		pr_err("%s: kmalloc fail\n", FILTER_NAME);
		return -1;
	}

	/* call filter */
	dev->buffer_cache_ctl = DRV_CACHE_FLUSH_ALL;
	req =
	    dd_filter_div(dev, (UCHAR *) virt_to_phys(dst),
			  (UCHAR *) virt_to_phys(src), width, height, pitch);
	if (req != 0) {
		pr_err("%s: dd_filter_dev fail\n", FILTER_NAME);
		goto err;
	}

	if (filter_status == FILTER_STATUS_EXE_DONE) {
		goto done;
	}

	/* normal end */
	/* check the CMD-reg */
	reg_val =
	    ioread32(dev->reg_base + FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	while ((filter_status != FILTER_STATUS_EXE_DONE)
	       && ((reg_val & 0x00000001) == 0)) {
		for (i = 0; i < 300; i++) {
			asm("nop");
		}
		reg_val =
		    ioread32(dev->reg_base +
			     FILTER_OFFSET(IRECOG_rfilter_CMD_OFFS));
	}

	if (filter_status == FILTER_STATUS_EXE_DONE) {
		goto done;
	}

	/* normal end */
	/* check the TRNSSTAT-reg */
	reg_val =
	    ioread32(dev->reg_base +
		     FILTER_OFFSET(IRECOG_rfilter_TRNSSTAT_OFFS));
	while ((filter_status != FILTER_STATUS_EXE_DONE)
	       && ((reg_val & 0x00000006) == 0)) {
		for (i = 0; i < 300; i++) {
			asm("nop");
		}
		reg_val =
		    ioread32(dev->reg_base +
			     FILTER_OFFSET(IRECOG_rfilter_TRNSSTAT_OFFS));
	}

	if (filter_status == FILTER_STATUS_EXE_DONE) {
		goto done;
	}

	/* normal end */
	/* wait WAIT_TIME_FILTER_RESET_1 us */
	t1 = get_time_us();
	t2 = get_time_us();
	wait_time = s_check_wait_time(t1, t2, WAIT_TIME_FILTER_RESET_1);
	while ((filter_status != FILTER_STATUS_EXE_DONE) && (wait_time == 0)) {
		for (i = 0; i < 300; i++) {
			asm("nop");
		}
		t2 = get_time_us();
		wait_time = s_check_wait_time(t1, t2, WAIT_TIME_FILTER_RESET_1);
	}

	if (filter_status == FILTER_STATUS_EXE_DONE) {
		goto done;
	}

	/* normal end */
	/* read the OFRMCNTV-reg */
	for (i = 0; i < 3; i++) {
		reg_value_1 =
		    ioread32(dev->reg_base +
			     FILTER_OFFSET(IRECOG_rfilter_OFRMCNTV_OFFS)) &
		    0x0000FFFF;
		udelay(100);
		reg_value_2 =
		    ioread32(dev->reg_base +
			     FILTER_OFFSET(IRECOG_rfilter_OFRMCNTV_OFFS)) &
		    0x0000FFFF;

		/* check the OFRMCNTV-reg */
		if (reg_value_1 == reg_value_2) {
			break;
		}

		/* wait 100us */
		udelay(100);
	}

	if (filter_status == FILTER_STATUS_EXE_DONE) {
		goto done;
	}

	/* normal end */
	/* filter HW reset */
	pr_info("%s: force reset\n", FILTER_NAME);
	{
		unsigned int rst_on =
		    PMU_SOFTRESETON_IRECOGSS_0_SRST_ASYNCFRST_N_MASK;
		unsigned int rst_off =
		    PMU_SOFTRESETOFF_IRECOGSS_0_SRST_ASYNCFRST_N_MASK;

		rst_off |=
		    PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_SHAREDBUS_N_MASK;

		/* filter reset */
		writel(rst_on,
		       __io_address(CPU_PMU_REG_BASE +
				    PMU_SOFTRESETON_IRECOGSS_0_OFS));
		udelay(10);

		/* shardbus reset */
		rst_on = PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_SHAREDBUS_N_MASK;
		writel(rst_on,
		       __io_address(CPU_PMU_REG_BASE +
				    PMU_SOFTRESETON_IRECOGSS_0_OFS));
		udelay(10);

		writel(rst_off,
		       __io_address(CPU_PMU_REG_BASE +
				    PMU_SOFTRESETOFF_IRECOGSS_0_OFS));
	}

	filter_status = FILTER_STATUS_EXE_DONE;

	kfree(src);
	kfree(dst);
	return 1;

err:
	kfree(src);
	kfree(dst);
	return -1;

done:
	kfree(src);
	kfree(dst);
	return 0;
}

static long filter_check_sobel_direction3x3_param(struct
						  filter_sobel_direction3x3_param
						  *param)
{
	/* select */
	if (param->dst_select > FILTER_SOBEL_IMAGE_OUT_ALL) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* image size */
	if ((param->width < FILTER_SOBEL_DIR_MIN_IMG_WIDTH)
	    || (param->width > FILTER_SOBEL_DIR_MAX_IMG_WIDTH)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}
	if ((param->height < FILTER_SOBEL_DIR_MIN_IMG_HEIGHT)
	    || (param->height > FILTER_SOBEL_DIR_MAX_IMG_HEIGHT)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->pitch == 0)
	    || ((param->pitch & FILTER_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* image size <= line pitch */
	if (param->width > param->pitch) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* filter W/A */
	if (((param->width & 0x7f) != 0) && ((param->width & 0x7f) < 80)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	return 0;
}

static long filter_check_image_smoothing_param(struct
					       filter_image_smoothing_param
					       *param)
{
	/* image size */
	if ((param->width < FILTER_IMG_SMOOTH_MIN_IMG_WIDTH)
	    || (param->width > FILTER_IMG_SMOOTH_MAX_IMG_WIDTH)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}
	if ((param->height < FILTER_IMG_SMOOTH_MIN_IMG_HEIGHT)
	    || (param->height > FILTER_IMG_SMOOTH_MAX_IMG_HEIGHT)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->pitch == 0)
	    || ((param->pitch & FILTER_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* image size <= line pitch */
	if (param->width > param->pitch) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* filter W/A (output 16bit) */
	if (((param->width & 0x7f) != 0) && ((param->width & 0x7f) < 40)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* depth */
	if ((param->depth != FILTER_IMG_DEPTH8)
	    && (param->depth != FILTER_IMG_DEPTH16)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* filter size */
	if ((param->filter_size != FILTER_IMG_SMOOTH_FILTER_SIZE_3)
	    && (param->filter_size != FILTER_IMG_SMOOTH_FILTER_SIZE_5)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* normalizer */
	if ((param->normalizer < FILTER_IMG_SMOOTH_MIN_NORMALIZER)
	    || (param->normalizer > FILTER_IMG_SMOOTH_MAX_NORMALIZER)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	return 0;
}

static long filter_check_average_image_param(struct filter_average_image_param
					     *param)
{
	/* image size */
	if ((param->width != FILTER_AVE_IMG_MAX_IMG_WIDTH)
	    || (param->height != FILTER_AVE_IMG_MAX_IMG_HEIGHT)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->src_pitch == 0)
	    || ((param->src_pitch & FILTER_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}
	if ((param->dst_pitch == 0)
	    || ((param->dst_pitch & FILTER_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* image size <= line pitch */
	if ((param->width > param->src_pitch)
	    || (param->width > param->dst_pitch)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	/* filter W/A */
	if (((param->width & 0x7f) != 0) && ((param->width & 0x7f) < 80)) {
		pr_err("%s: %s %d: invalid parameter.\n", FILTER_NAME, __func__,
		       __LINE__);
		return -EINVAL;
	}

	return 0;
}

static long check_tonemapping_luma_param(struct filter_tonemapping_luma_param
					 *param)
{
	if (param->src_fd < 0) {
		pr_err("%s: %s %d: invalid src_fd:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->src_fd);
		return -EINVAL;
	}
	if (param->src_offset % 64) {
		pr_err("%s: %s %d: invalid src_offset:%d\n", FILTER_NAME,
		       __func__, __LINE__, param->src_offset);
		return -EINVAL;
	}

	if (param->dst_fd < 0) {
		pr_err("%s: %s %d: invalid dst_fd:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->dst_fd);
		return -EINVAL;
	}
	if (param->dst_offset % 64) {
		pr_err("%s: %s %d: invalid dst_offset:%d\n", FILTER_NAME,
		       __func__, __LINE__, param->dst_offset);
		return -EINVAL;
	}

	/* image size */
	if ((param->width < FILTER_TONEMAP_LUMA_MIN_IMG_WIDTH)
	    || (param->width > FILTER_TONEMAP_LUMA_MAX_IMG_WIDTH)) {
		pr_err("%s: %s %d: invalid width:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->width);
		return -EINVAL;
	}
	if ((param->height < FILTER_TONEMAP_LUMA_MIN_IMG_HEIGHT)
	    || (param->height > FILTER_TONEMAP_LUMA_MAX_IMG_HEIGHT)) {
		pr_err("%s: %s %d: invalid height:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->height);
		return -EINVAL;
	}

	/* block size */
	if (param->width % FILTER_TONEMAPPING_LUMA_BLOCK_W) {
		pr_err
		    ("%s: %s %d: invalid width:%d (not a multiple of block width)\n",
		     FILTER_NAME, __func__, __LINE__, param->width);
		return -EINVAL;
	}
	if (param->height % FILTER_TONEMAPPING_LUMA_BLOCK_H) {
		pr_err
		    ("%s: %s %d: invalid height:%d (not a multiple of block height)\n",
		     FILTER_NAME, __func__, __LINE__, param->width);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->pitch == 0)
	    || ((param->pitch & FILTER_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: %s %d: invalid pitch:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->pitch);
		return -EINVAL;
	}

	/* image size <= line pitch */
	if (param->width > param->pitch) {
		pr_err("%s: %s %d: invalid pitch:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->pitch);
		return -EINVAL;
	}

	/* blend */
	if (param->blend > FILTER_TONEMAPPING_LUMA_MAX_BLEND) {
		pr_err("%s: %s %d: invalid blend:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->blend);
		return -EINVAL;
	}

	/* div_num */
	if (param->div_num != 1) {
		pr_err("%s: %s %d: invalid div_num:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->div_num);
		return -EINVAL;
	}
	/* div_sel */
	if (param->div_sel != 0) {
		pr_err("%s: %s %d: invalid div_sel:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->div_sel);
		return -EINVAL;
	}

	/* filter W/A */
	if (((param->width & 0x7f) != 0) && ((param->width & 0x7f) < 80)) {
		pr_err("%s: %s %d: invalid width:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->width);
		return -EINVAL;
	}

	return 0;
}

static long filter_check_correct_color_param(struct filter_correct_color_param
					     *param)
{
	/* image size */
	if ((param->width < FILTER_CORRECT_COLOR_MIN_IMG_WIDTH)
	    || (param->width > FILTER_CORRECT_COLOR_MAX_IMG_WIDTH)) {
		pr_err("%s: %s %d: invalid width:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->width);
		return -EINVAL;
	}
	if ((param->height < FILTER_CORRECT_COLOR_MIN_IMG_HEIGHT)
	    || (param->height > FILTER_CORRECT_COLOR_MAX_IMG_HEIGHT)) {
		pr_err("%s: %s %d: invalid height:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->height);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->pitch == 0)
	    || ((param->pitch & FILTER_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: %s %d: invalid pitch:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->pitch);
		return -EINVAL;
	}

	/* image size <= line pitch */
	if (param->width > param->pitch) {
		pr_err("%s: %s %d: invalid pitch:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->pitch);
		return -EINVAL;
	}

	/* color rate */
	if ((param->color_rate < FILTER_CORRECT_COLOR_MIN_COLOR_RATE)
	    || (param->color_rate > FILTER_CORRECT_COLOR_MAX_COLOR_RATE)) {
		pr_err("%s: %s %d: invalid color_rate:%d\n", FILTER_NAME,
		       __func__, __LINE__, param->color_rate);
		return -EINVAL;
	}

	return 0;
}

static long filter_check_noise_reduction_y_param(struct
						 filter_noise_reduction_y_param
						 *param)
{
	/* image size */
	if ((param->width < FILTER_NR_MIN_IMG_WIDTH)
	    || (param->width > FILTER_NR_MAX_IMG_WIDTH)) {
		pr_err("%s: %s %d: invalid width:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->width);
		return -EINVAL;
	}
	if ((param->height < FILTER_NR_MIN_IMG_HEIGHT)
	    || (param->height > FILTER_NR_MAX_IMG_HEIGHT)) {
		pr_err("%s: %s %d: invalid height:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->height);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->pitch == 0)
	    || ((param->pitch & FILTER_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: %s %d: invalid pitch:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->pitch);
		return -EINVAL;
	}

	/* image size <= line pitch */
	if (param->width > param->pitch) {
		pr_err("%s: %s %d: invalid pitch:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->pitch);
		return -EINVAL;
	}

	/* threshold */
	if ((param->threshold < FILTER_NR_MIN_TH)
	    || (param->threshold > FILTER_NR_MAX_TH)) {
		pr_err("%s: %s %d: invalid threshold:%d\n", FILTER_NAME,
		       __func__, __LINE__, param->threshold);
		return -EINVAL;
	}

	return 0;
}

static long filter_check_noise_reduction_uv_param(struct
						  filter_noise_reduction_uv_param
						  *param)
{
	/* image size */
	if ((param->width < FILTER_NR_MIN_IMG_WIDTH)
	    || (param->width > FILTER_NR_MAX_IMG_WIDTH)) {
		pr_err("%s: %s %d: invalid width:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->width);
		return -EINVAL;
	}
	if ((param->height < FILTER_NR_MIN_IMG_HEIGHT)
	    || (param->height > FILTER_NR_MAX_IMG_HEIGHT)) {
		pr_err("%s: %s %d: invalid height:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->height);
		return -EINVAL;
	}

	/* line pitch */
	if ((param->pitch == 0)
	    || ((param->pitch & FILTER_LPITCH_ALIGN_MASK) > 0)) {
		pr_err("%s: %s %d: invalid pitch:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->pitch);
		return -EINVAL;
	}

	/* image size <= line pitch */
	if (param->width > param->pitch) {
		pr_err("%s: %s %d: invalid pitch:%d\n", FILTER_NAME, __func__,
		       __LINE__, param->pitch);
		return -EINVAL;
	}
	return 0;
}

static long filter_wait_event(struct file *filp)
{
	sigset_t oldset;
	struct filter_dev *dev = filp->private_data;

	if (filter_status != FILTER_STATUS_EXE_DONE) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		/* signal mask */
		drv_sigmask(&oldset);
		if (wait_event_interruptible(wq,
					     (filter_status ==
					      FILTER_STATUS_EXE_DONE))) {

			filter_reset(dev);

			/* signal unmask */
			drv_sigunmask(&oldset);
			filter_status = FILTER_STATUS_EXE_DONE;

			pr_err("%s: wait_event_interruptible fail.\n",
			       FILTER_NAME);
			return -ERESTARTSYS;
		}
		/* signak unmask */
		drv_sigunmask(&oldset);
	}

	return 0;
}

static int filter_get_int_status(struct filter_dev *dev)
{
	unsigned int status;
	int ret;

	status =
	    ioread32(dev->reg_base +
		     FILTER_OFFSET(IRECOG_rfilter_INTSTAT_OFFS));
	if ((status & FILTER_HW_INIT_END) != 0) {
		ret = FILTER_STATUS_INIT_DONE;
	} else
	if ((status & (FILTER_HW_LAST_IMG_END | FILTER_HW_LAST_PARAM_END)))	{
		ret = FILTER_STATUS_EXE_DONE;
	} else if ((status & FILTER_HW_ERROR_STATUS) != 0) {
		ret = FILTER_STATUS_ERROR;
	} else {
		ret = FILTER_STATUS_OTHERS;
	}

	return ret;
}

static irqreturn_t filter_isr(int irq, void *dev_id)
{
	struct filter_dev *dev = dev_id;
	int status;

	status = filter_get_int_status(dev);
	filter_status = status;
	if (filter_clear_int(dev) < 0) {
		status = FILTER_STATUS_ERROR;
		filter_status = status;
		wake_up_interruptible(&wq);
		return IRQ_HANDLED;
	}

	if (status == FILTER_STATUS_INIT_DONE) {
		iowrite32(0x1,
			  dev->reg_base +
			  FILTER_OFFSET(IRECOG_rfilter_IMGSTART_OFFS));
	} else if (status == FILTER_STATUS_EXE_DONE) {
		wake_up_interruptible(&wq);
	} else if (status == FILTER_STATUS_ERROR) {
		wake_up_interruptible(&wq);
	}

	return IRQ_HANDLED;
}

static int filter_open(struct inode *inode, struct file *filp)
{
	struct filter_dev *dev;

	dev = container_of(inode->i_cdev, struct filter_dev, cdev);
	filp->private_data = dev;

	if (atomic_inc_return(&refcount) == 1) {
		filter_runtime_resume(&dev->pdev->dev);
	}
	return 0;
}

static int filter_release(struct inode *inode, struct file *filp)
{
	struct filter_dev *dev;

	dev = container_of(inode->i_cdev, struct filter_dev, cdev);

	if (atomic_dec_return(&refcount) == 0) {
		filter_runtime_suspend(&dev->pdev->dev);
	}
	return 0;
}

#ifdef ENABLE_QEMU_FPARAM
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

static long filter_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct filter_dev *dev = filp->private_data;
	long ret;

	switch (cmd) {
	case FILTER_IOCTL_SOBEL_DIRECTIION3x3:
		{
			struct filter_sobel_direction3x3_param dir_param;
			if (copy_from_user
			    ((void *)&dir_param, (const void __user *)arg,
			     sizeof(struct filter_sobel_direction3x3_param))) {
				pr_err
				    ("%s: copy_from_user failed filter_sobel_direction3x3_param\n",
				     FILTER_NAME);
				return -EFAULT;
			}

			if (filter_check_sobel_direction3x3_param(&dir_param) <
			    0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       FILTER_NAME);
				return -EINVAL;
			}
			if (check_cache_param(dir_param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       FILTER_NAME);
				return -ERESTARTSYS;
			}
			if (filter_status != FILTER_STATUS_EXE_DONE) {
				pr_err("%s: invalid status.\n", FILTER_NAME);
				up(&sem);
				return -EAGAIN;
			}
#if 0				/* use flush all */
			/* cache flush input image */
			/* drv_cache_flush(dir_param.src_adr, dir_param.pitch * dir_param.height); */
#endif

			dev->buffer_cache_ctl = dir_param.buffer_cache_ctl;

			switch (dir_param.dst_select) {
			case FILTER_SOBEL_IMAGE_OUT_THR:
#if 0				/* use flush all */
				/* cache flush */
				/* drv_cache_flush(dir_param.dst_dir_thr_adr, dir_param.pitch * dir_param.height); */
#endif
				if (sl_sobel_direction3x3(dev,
							  dir_param.
							  dst_dir_thr_adr,
							  dir_param.src_adr,
							  dir_param.width,
							  dir_param.height,
							  dir_param.pitch,
							  dir_param.threshold) <
				    0) {
					pr_err
					    ("%s: sl_sobel_direction3x3 failed.\n",
					     FILTER_NAME);
					up(&sem);
					return -EINVAL;
				}
				break;

			case FILTER_SOBEL_IMAGE_OUT_NOTHR_INTENSITY:
#if 0				/* use flush all */
				/* cache flush */
				/* drv_cache_flush(dir_param.dst_dir_nothr_adr, dir_param.pitch * dir_param.height); */
				/* drv_cache_flush(dir_param.dst_int_adr      , dir_param.pitch * dir_param.height*2); */
#endif
				if (sl_sobel_direction3x3_and_intensity(dev,
									dir_param.
									dst_dir_nothr_adr,
									dir_param.
									dst_int_adr,
									dir_param.
									src_adr,
									dir_param.
									width,
									dir_param.
									height,
									dir_param.
									pitch)
				    < 0) {
					pr_err
					    ("%s: sl_sobel_direction3x3_and_intensity failed.\n",
					     FILTER_NAME);
					up(&sem);
					return -EINVAL;
				}
				break;

			case FILTER_SOBEL_IMAGE_OUT_ALL:
#if 0				/* use flush all */
				/* cache flush */
				/* drv_cache_flush(dir_param.dst_dir_thr_adr  , dir_param.pitch * dir_param.height); */
				/* drv_cache_flush(dir_param.dst_dir_nothr_adr, dir_param.pitch * dir_param.height); */
				/* drv_cache_flush(dir_param.dst_int_adr      , dir_param.pitch * dir_param.height*2); */
#endif
				if (sl_sobel_direction3x3_and_intensity_with_threshold(dev, dir_param.dst_dir_thr_adr, dir_param.dst_dir_nothr_adr, dir_param.dst_int_adr, dir_param.src_adr, dir_param.width, dir_param.height, dir_param.pitch, dir_param.threshold) < 0) {
					up(&sem);
					pr_err
					    ("%s: sl_sobel_direction3x3_and_intensity_with_threshold failed.\n",
					     FILTER_NAME);
					return -EINVAL;
				}
				break;
			}

			ret = filter_wait_event(filp);
			up(&sem);

			return ret;

		}
		break;
	case FILTER_IOCTL_IMAGE_SMOOTHING:
		{
			struct filter_image_smoothing_param msk_param;
			SSHORT *coef;
			UINT coef_size;

			if (copy_from_user
			    ((void *)&msk_param, (const void __user *)arg,
			     sizeof(struct filter_image_smoothing_param))) {
				pr_err
				    ("%s: copy_from_user failed filter_2d_param\n",
				     FILTER_NAME);
				return -EFAULT;
			}
			coef_size =
			    msk_param.filter_size * msk_param.filter_size;
			coef = kmalloc(sizeof(SSHORT) * coef_size, GFP_KERNEL);
			if (!coef) {
				pr_err("%s: kmalloc failed\n", FILTER_NAME);
				return -ENOMEM;
			}
			if (copy_from_user
			    ((void *)coef,
			     (const void __user *)(UINT)msk_param.coef,
			     sizeof(SSHORT) * coef_size)) {
				pr_err("%s: copy_from_user failed coef\n",
				       FILTER_NAME);
				kfree(coef);
				return -EFAULT;
			}

			if (filter_check_image_smoothing_param(&msk_param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       FILTER_NAME);
				kfree(coef);
				return -EINVAL;
			}
			if (check_cache_param(msk_param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       FILTER_NAME);
				kfree(coef);
				return -ERESTARTSYS;
			}
			if (filter_status != FILTER_STATUS_EXE_DONE) {
				pr_err("%s: invalid status.\n", FILTER_NAME);
				up(&sem);
				kfree(coef);
				return -EAGAIN;
			}
#if 0				/* use flush all */
			/* cache flush input image */
			/* drv_cache_flush(msk_param.src_adr, msk_param.pitch * msk_param.height * (msk_param.depth >> 3)); */
			/* cache invalidate */
			/* drv_cache_flush(msk_param.dst_adr, msk_param.pitch * msk_param.height * 2); */
#endif
			dev->buffer_cache_ctl = msk_param.buffer_cache_ctl;
			if (sl_filter_2d(dev,
					 msk_param.dst_adr,
					 msk_param.src_adr,
					 msk_param.width,
					 msk_param.height,
					 msk_param.pitch,
					 msk_param.depth,
					 msk_param.filter_size,
					 coef, msk_param.normalizer) < 0) {
				pr_err("%s: sl_filter_2d failed.\n",
				       FILTER_NAME);
				up(&sem);
				kfree(coef);
				return -EINVAL;
			}

			ret = filter_wait_event(filp);

			kfree(coef);
			up(&sem);

			return ret;
		}

		break;
	case FILTER_IOCTL_AVERAGE_IMAGE:
		{
			struct filter_average_image_param ave_param;
			if (copy_from_user
			    ((void *)&ave_param, (const void __user *)arg,
			     sizeof(struct filter_average_image_param))) {
				pr_err
				    ("%s: copy_from_user failed filter_average_image_param\n",
				     FILTER_NAME);
				return -EFAULT;
			}

			if (filter_check_average_image_param(&ave_param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       FILTER_NAME);
				return -EINVAL;
			}
			if (check_cache_param(ave_param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       FILTER_NAME);
				return -ERESTARTSYS;
			}
			if (filter_status != FILTER_STATUS_EXE_DONE) {
				pr_err("%s: invalid status.\n", FILTER_NAME);
				up(&sem);
				return -EAGAIN;
			}
#if 0				/* use flush all */
			/* cache flush input image */
			/* drv_cache_flush(ave_param.src_adr, ave_param.src_pitch * ave_param.height); */
			/* 16bit buffer is used for input and output. */
			/* drv_cache_flush(ave_param.dst_16bit_adr, ave_param.dst_pitch * ave_param.height*2); */
			/* cache invalidate */
			/* drv_cache_invalidate(ave_param.dst_8bit_adr , ave_param.dst_pitch * ave_param.height); */

#endif
			dev->buffer_cache_ctl = ave_param.buffer_cache_ctl;
			if (sl_average_image(dev,
					     ave_param.dst_16bit_adr,
					     ave_param.dst_8bit_adr,
					     ave_param.src_adr,
					     ave_param.width,
					     ave_param.height,
					     ave_param.src_pitch,
					     ave_param.dst_pitch) < 0) {
				pr_err("%s: sl_averate_image.\n", FILTER_NAME);
				up(&sem);
				return -EINVAL;
			}

			ret = filter_wait_event(filp);
			up(&sem);

			return ret;
		}
		break;

	case FILTER_IOCTL_TONEMAPPING_LUMA:
		{
			struct filter_tonemapping_luma_param tonemap_param;
			struct drv_dmabuf_conv_adr src_addr;
			struct drv_dmabuf_conv_adr dst_addr;

			if (copy_from_user
			    ((void *)&tonemap_param, (const void __user *)arg,
			     sizeof(struct filter_tonemapping_luma_param))) {
				pr_err
				    ("%s: copy_from_user failed filter_tonemapping_luma_param_param\n",
				     FILTER_NAME);
				return -EFAULT;
			}

			if (check_tonemapping_luma_param(&tonemap_param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       FILTER_NAME);
				return -EINVAL;
			}
			if (check_cache_param(tonemap_param.buffer_cache_ctl) <
			    0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       FILTER_NAME);
				return -ERESTARTSYS;
			}
			if (filter_status != FILTER_STATUS_EXE_DONE) {
				pr_err("%s: invalid status.\n", FILTER_NAME);
				up(&sem);
				return -EAGAIN;
			}

			dev->buffer_cache_ctl = tonemap_param.buffer_cache_ctl;

			if (filter_tomemapping_luma_conv_address
			    (dev, &tonemap_param, &src_addr, &dst_addr) < 0) {
				pr_err
				    ("%s : filter_tomemapping_luma_conv_address fail\n",
				     FILTER_NAME);
				up(&sem);
				return -EINVAL;
			}

			if (copy_from_user(dev->tonemap,
					   (const void __user *)tonemap_param.
					   tonemap_addr_virt,
					   FILTER_TONEMAPPING_LUMA_LUT_SIZE)) {
				pr_err("%s : copy_from_user fail\n",
				       FILTER_NAME);
				up(&sem);
				return -EFAULT;
			}

			if (sl_tonemapping_luma(dev,
						dst_addr.addr +
						tonemap_param.dst_offset,
						src_addr.addr +
						tonemap_param.src_offset,
						dev->tonemap,
						tonemap_param.width,
						tonemap_param.height,
						tonemap_param.pitch,
						tonemap_param.blend) < 0) {
				filter_tonemapping_free_address(&src_addr,
								&dst_addr);
				pr_err("%s : sl_tonemapping_luma failed.\n",
				       FILTER_NAME);
				up(&sem);
				return -EINVAL;
			}

			ret = filter_wait_event(filp);

			filter_tonemapping_free_address(&src_addr, &dst_addr);
			up(&sem);

			return ret;

		}
		break;

	case FILTER_IOCTL_CORRECT_COLOR:
		{
			struct filter_correct_color_param param;
			struct drv_dmabuf_conv_adr conv_addr[6];

			if (copy_from_user
			    ((void *)&param, (const void __user *)arg,
			     sizeof(struct filter_correct_color_param))) {
				pr_err
				    ("%s: copy_from_user failed filter_correct_color_param\n",
				     FILTER_NAME);
				return -EFAULT;
			}

			if (filter_check_correct_color_param(&param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       FILTER_NAME);
				return -EINVAL;
			}
			if (check_cache_param(param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       FILTER_NAME);
				return -ERESTARTSYS;
			}
			if (filter_status != FILTER_STATUS_EXE_DONE) {
				pr_err("%s: invalid status.\n", FILTER_NAME);
				up(&sem);
				return -EAGAIN;
			}
			dev->buffer_cache_ctl = param.buffer_cache_ctl;

			if (filter_correct_color_conv_address
			    (dev, &param, conv_addr) < 0) {
				pr_err
				    ("%s: failed to get phys address from fd.\n",
				     FILTER_NAME);
				up(&sem);
				return -EINVAL;
			}

			if (sl_correct_color(dev,
					     conv_addr[0].addr +
					     param.src_y_offset,
					     conv_addr[1].addr +
					     param.src_u_offset,
					     conv_addr[2].addr +
					     param.src_v_offset,
					     conv_addr[3].addr +
					     param.src_tonemapped_y_offset,
					     conv_addr[4].addr +
					     param.dst_u_offset,
					     conv_addr[5].addr +
					     param.dst_v_offset, param.width,
					     param.height, param.pitch,
					     param.color_rate) < 0) {
				pr_err("%s: sl_correct_color failed.\n",
				       FILTER_NAME);
				up(&sem);
				filter_correct_color_free_address(conv_addr);
				return -EINVAL;
			}

			ret = filter_wait_event(filp);
			up(&sem);

			filter_correct_color_free_address(conv_addr);

			return ret;
		}
		break;

	case FILTER_IOCTL_NOISE_REDUCTION_Y:
		{
			struct filter_noise_reduction_y_param param;
			struct drv_dmabuf_conv_adr in_addr[4];
			struct drv_dmabuf_conv_adr out_addr[3];
			int in_fd[4];
			int out_fd[3];

			if (copy_from_user
			    ((void *)&param, (const void __user *)arg,
			     sizeof(struct filter_noise_reduction_y_param))) {
				pr_err
				    ("%s: copy_from_user failed filter_noise_reduction_y_param\n",
				     FILTER_NAME);
				return -EFAULT;
			}

			if (filter_check_noise_reduction_y_param(&param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       FILTER_NAME);
				return -EINVAL;
			}
			if (check_cache_param(param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_intertuptible failed.\n",
				       FILTER_NAME);
				return -ERESTARTSYS;
			}
			if (filter_status != FILTER_STATUS_EXE_DONE) {
				pr_err("%s: invalid status.\n", FILTER_NAME);
				up(&sem);
				return -EAGAIN;
			}
			dev->buffer_cache_ctl = param.buffer_cache_ctl;

			in_fd[0] = param.in_src_fd;
			in_fd[1] = param.in_blend_fd;
			in_fd[2] = param.in_nr_fd;
			in_fd[3] = param.in_md_fd;
			if (filter_conv_address
			    (dev, 4, in_fd, in_addr, DMA_TO_DEVICE) < 0) {
				pr_err("%s: filter_conv_address fail.\n",
				       FILTER_NAME);
				up(&sem);
				return -EINVAL;
			}

			out_fd[0] = param.out_md_fd;
			out_fd[1] = param.out_nr_fd;
			out_fd[2] = param.out_diff_flag_fd;
			if (filter_conv_address
			    (dev, 3, out_fd, out_addr, DMA_FROM_DEVICE) < 0) {
				filter_free_address(4, in_addr, DMA_TO_DEVICE);
				pr_err("%s: filter_conv_address fail.\n",
				       FILTER_NAME);
				up(&sem);
				return -EINVAL;
			}

			if (sl_noise_reduction_y(dev,
						 in_addr[0].addr +
						 param.in_src_offset,
						 in_addr[1].addr +
						 param.in_blend_offset,
						 in_addr[2].addr +
						 param.in_nr_offset,
						 in_addr[3].addr +
						 param.in_md_offset,
						 out_addr[0].addr +
						 param.out_md_offset,
						 out_addr[1].addr +
						 param.out_nr_offset,
						 out_addr[2].addr +
						 param.out_diff_flag_offset,
						 param.width, param.height,
						 param.pitch,
						 param.threshold) < 0) {
				pr_err("%s: sl_noise_reduction_y failed.\n",
				       FILTER_NAME);
				up(&sem);
				filter_free_address(4, in_addr, DMA_TO_DEVICE);
				filter_free_address(3, out_addr,
						    DMA_FROM_DEVICE);
				return -EINVAL;
			}

			ret = filter_wait_event(filp);

			filter_free_address(4, in_addr, DMA_TO_DEVICE);
			filter_free_address(3, out_addr, DMA_FROM_DEVICE);

			up(&sem);
			return ret;
		}
		break;

	case FILTER_IOCTL_NOISE_REDUCTION_UV:
		{
			struct filter_noise_reduction_uv_param param;
			struct drv_dmabuf_conv_adr in_addr[3];
			struct drv_dmabuf_conv_adr out_addr[1];
			int in_fd[3];
			int out_fd[1];

			if (copy_from_user
			    ((void *)&param, (const void __user *)arg,
			     sizeof(struct filter_noise_reduction_uv_param))) {
				pr_err
				    ("%s: copy_from_user failed filter_noise_reduction_uv_param\n",
				     FILTER_NAME);
				return -EFAULT;
			}

			if (filter_check_noise_reduction_uv_param(&param) < 0) {
				pr_err("%s: invalid ioctl parameter.\n",
				       FILTER_NAME);
				return -EINVAL;
			}
			if (check_cache_param(param.buffer_cache_ctl) < 0) {
				return -EINVAL;
			}

			if (down_interruptible(&sem)) {
				pr_err("%s: down_interruptible failed.\n",
				       FILTER_NAME);
				return -ERESTARTSYS;
			}
			if (filter_status != FILTER_STATUS_EXE_DONE) {
				pr_err("%s: invalid status.\n", FILTER_NAME);
				up(&sem);
				return -EAGAIN;
			}
			dev->buffer_cache_ctl = param.buffer_cache_ctl;

			in_fd[0] = param.in_color_fd;
			in_fd[1] = param.in_nr_fd;
			in_fd[2] = param.in_diff_flag_fd;
			if (filter_conv_address
			    (dev, 3, in_fd, in_addr, DMA_TO_DEVICE) < 0) {
				pr_err("%s: filter_conv_address fail.\n",
				       FILTER_NAME);
				up(&sem);
				return -EINVAL;
			}

			out_fd[0] = param.out_nr_fd;
			if (filter_conv_address
			    (dev, 1, out_fd, out_addr, DMA_FROM_DEVICE) < 0) {
				filter_free_address(3, in_addr, DMA_TO_DEVICE);
				pr_err("%s: filter_conv_address fail.\n",
				       FILTER_NAME);
				up(&sem);
				return -EINVAL;
			}

			if (sl_noise_reduction_uv(dev,
						  in_addr[0].addr +
						  param.in_color_offset,
						  in_addr[1].addr +
						  param.in_nr_offset,
						  in_addr[2].addr +
						  param.in_diff_flag_offset,
						  out_addr[0].addr +
						  param.out_nr_offset,
						  param.width, param.height,
						  param.pitch) < 0) {
				pr_err("%s: sl_noise_reduction_uv failed.\n",
				       FILTER_NAME);
				up(&sem);
				filter_free_address(3, in_addr, DMA_TO_DEVICE);
				filter_free_address(1, out_addr,
						    DMA_FROM_DEVICE);
				return -EINVAL;
			}

			ret = filter_wait_event(filp);
			filter_free_address(3, in_addr, DMA_TO_DEVICE);
			filter_free_address(1, out_addr, DMA_FROM_DEVICE);

			up(&sem);
			return ret;
		}
		break;

	case FILTER_IOCTL_GET_VERSION:
		{
			drv_version_t version_param;

			memset(&version_param, 0x00, sizeof(drv_version_t));
			memcpy(version_param.version, drv_filter_version,
			       strlen(drv_filter_version));

			if (copy_to_user((void __user *)arg,
					 (void *)&version_param,
					 sizeof(drv_version_t))) {
				pr_err("%s: copy_to_user failed version\n",
				       FILTER_NAME);
				return -EFAULT;
			}
		}
		break;

	case FILTER_IOCTL_SET_FPARAM_ADDR:
		{
			uint32_t fparam_base;

			if (copy_from_user
			    ((void *)&fparam_base, (const void __user *)arg,
			     sizeof(uint32_t))) {
				pr_err
				    ("%s: copy_from_user failed set_fparam_addr.\n",
				     FILTER_NAME);
				return -EFAULT;
			}
#ifndef ENABLE_QEMU_FPARAM
			dev->param_base =
			    (void __iomem *)phys_to_virt(fparam_base);
			dev->param_size =
			    *(uint32_t *)(unsigned long)dev->param_base;
#endif
		}
		break;

	case FILTER_IOCTL_INITIALIZE:

		if (filter_reset(dev) < 0) {
			pr_err("%s: reset failed.\n", FILTER_NAME);
			return -EIO;
		}
#ifdef ENABLE_QEMU_FPARAM
		if (mmap_fparam_qemu(dev) != 0) {
			pr_err("%s: ioremap fparam failed.\n", FILTER_NAME);
			return -EFAULT;
		}
#endif
		break;

	case FILTER_IOCTL_BUS_INIT:
		dd_filter_bus_init_local(dev);
		break;

	default:
		pr_err("%s: invalid ioctl command 0x%x\n", FILTER_NAME, cmd);
		return -EINVAL;
		break;
	}

	return 0;
}

static const struct file_operations filter_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = filter_ioctl,
	.open = filter_open,
	.release = filter_release,
};

static void filter_setup_cdev(struct filter_dev *dev, int index)
{
	int err;
	dev_t devno = MKDEV(filter_major, filter_minor + index);

	cdev_init(&dev->cdev, &filter_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev %d\n", FILTER_NAME, index);
	}
}

static int __devinit filter_probe(struct platform_device *pdev)
{
	int cnt;
	int ret;
	dev_t dev = 0;
	struct filter_dev *ioctl_dev;

	/* allocation of device number */
	if (filter_major) {
		dev = MKDEV(filter_major, filter_minor);
		ret = register_chrdev_region(dev, filter_nr_devs, FILTER_NAME);
	} else {
		ret =
		    alloc_chrdev_region(&dev, filter_minor, filter_nr_devs,
					FILTER_NAME);
		filter_major = MAJOR(dev);
	}
	if (ret < 0) {
		pr_err("%s: can't get major %d\n", FILTER_NAME, filter_major);
		return ret;
	}

	filter_device_set = kmalloc(sizeof(struct filter_dev_set), GFP_KERNEL);
	if (!filter_device_set) {
		pr_err("%s: kmalloc failed.\n", FILTER_NAME);
		ret = -ENOMEM;
		goto err0;
	}

	memset(filter_device_set, 0, sizeof(struct filter_dev_set));
	ioctl_dev = &(filter_device_set->ioctl_dev);

	ioctl_dev->pdev = pdev;
	platform_set_drvdata(pdev, ioctl_dev);

	if (sl_tonemapping_init(ioctl_dev) < 0) {
		ret = -ENODEV;
		pr_err("%s: sl_tonemapping_init failed.\n", FILTER_NAME);
		goto err1;
	}

	/* mapping of filter MMIO */
	if (!request_mem_region(FILTER_BASE, FILTER_SIZE, FILTER_NAME)) {
		pr_err("%s: request_mem_region failed.\n", FILTER_NAME);
		ret = -ENODEV;
		goto err1;
	}

	ioctl_dev->reg_base = ioremap_nocache(FILTER_BASE, FILTER_SIZE);
	if (!ioctl_dev->reg_base) {
		pr_err("%s: ioremap_nocache failed.\n", FILTER_NAME);
		ret = -ENODEV;
		goto err2;
	}

	/* init semaphore */
	sema_init(&sem, 1);
	/* init waitqueue */
	init_waitqueue_head(&wq);
	/* init status */
	filter_status = FILTER_STATUS_EXE_DONE;

	/* register interrupt service routine */
	ret = request_irq(filter_irq, filter_isr, 0, FILTER_NAME, ioctl_dev);
	if (ret < 0) {
		pr_err("%s: request_irq failed\n", FILTER_NAME);
		goto err3;
	}

	/* register cdev */
	cnt = 0;
	filter_setup_cdev(ioctl_dev, cnt++);

	/* create filter class */
	pfilter_class = class_create(THIS_MODULE, FILTER_NAME);
	if (IS_ERR(pfilter_class)) {
		ret = PTR_ERR(pfilter_class);
		pr_err("%s: class_create failed\n", FILTER_NAME);
		goto err4;
	}

	/* create device structure */
	ioctl_dev->device =
	    device_create(pfilter_class, NULL, dev, NULL, "%s_ioctl",
			  FILTER_NAME);
	if (IS_ERR(ioctl_dev->device)) {
		ret = PTR_ERR(ioctl_dev->device);
		pr_err("%s: device_create failed\n", FILTER_NAME);
		goto err5;
	}

	pm_runtime_enable(&pdev->dev);

	pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
		FILTER_NAME, DRV_FILTER_VERSION_STR, MAJOR(dev), MINOR(dev));

	return 0;

err5:
	class_destroy(pfilter_class);
err4:
	cdev_del(&ioctl_dev->cdev);
err3:
	iounmap(ioctl_dev->reg_base);
err2:
	release_mem_region(FILTER_BASE, FILTER_SIZE);
	sl_tonemapping_finalize(ioctl_dev);
err1:
	kfree(filter_device_set);
err0:
	return ret;
}

static int __devexit filter_remove(struct platform_device *pdev)
{
	dev_t dev = MKDEV(filter_major, filter_minor);
	struct filter_dev *ioctl_dev;

	/* reset device */
	if (filter_device_set) {

		ioctl_dev = &(filter_device_set->ioctl_dev);
		filter_runtime_resume(&pdev->dev);
		filter_reset(ioctl_dev);
		filter_runtime_suspend(&pdev->dev);

#ifdef ENABLE_QEMU_FPARAM
		iounmap(ioctl_dev->param_base);
#endif

		device_destroy(pfilter_class, dev);
		class_destroy(pfilter_class);
		cdev_del(&ioctl_dev->cdev);

		free_irq(filter_irq, ioctl_dev);
		iounmap(ioctl_dev->reg_base);
		release_mem_region(FILTER_BASE, FILTER_SIZE);

		sl_tonemapping_finalize(ioctl_dev);
		kfree(filter_device_set);
	}
	pm_runtime_disable(&pdev->dev);
	platform_set_drvdata(pdev, NULL);

	unregister_chrdev_region(dev, filter_nr_devs);

	pr_info("%s: exit\n", FILTER_NAME);

	return 0;
}

static int filter_suspend(struct device *dev)
{
	int ret = 0;

	if (atomic_read(&refcount) > 0) {
		ret = -EBUSY;
	}

	pr_debug("%s: %s: %d\n", FILTER_NAME, __func__, ret);

	return ret;
}

static int filter_resume(struct device *dev)
{
	return 0;
}

static const struct dev_pm_ops filter_pm_ops = {
	.suspend = filter_suspend,
	.resume = filter_resume,
	.runtime_suspend = filter_runtime_suspend,
	.runtime_resume = filter_runtime_resume,
};

static struct platform_driver filter_driver = {
	.driver = {
		   .name = "irecog_filter",
		   .owner = THIS_MODULE,
		   .pm = &filter_pm_ops,
		   },
	.probe = filter_probe,
	.remove = filter_remove,
};

static int __init filter_init(void)
{
	return platform_driver_register(&filter_driver);
}

static void __exit filter_exit(void)
{
	platform_driver_unregister(&filter_driver);
}

module_init(filter_init);
module_exit(filter_exit);

MODULE_AUTHOR("TOSHIBA Corp.");
MODULE_VERSION(DRV_FILTER_VERSION_STR);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Filter HWE module");
