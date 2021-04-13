/*
 * linux/drivers/staging/applite/applite_yuvc_internal.h
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

#if !defined(__YUVC_DRIVER_INTERNAL_MODULE_H__)
#define __YUVC_DRIVER_INTERNAL_MODULE_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*===================================
include Files
===================================*/
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/applite/applite_yuvc.h>

#include <mach/platform.h>
#include <mach/regs/cpu_memmap_def.h>
#include <mach/regs/yuvc_offs_def.h>
#include <mach/regs/yuvc_reg_def.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/pmu_reg_def.h>

#include "applite_yuvc_regs.h"
#include "applite_yuvc_dma.h"

/*===================================
Types and structures   defined
===================================*/

/* driver values */
#define	DEVICE_NAME			"yuvc"
#define	PROC_DEVICE_NAME		"yuvc"
#define PROC_STS_NAME			"status"
#define PROC_REG_NAME			"regs"
#define PROC_LOGFLAG_NAME		"logflag"
#define	YUVC_DRIVER_VERSION		"1.1"

/* interrupt values */
#define YUVC_IRQ_NUM			(181)
#define YUVC_IRQ_FLAG			(IRQF_SHARED | IRQF_TRIGGER_HIGH)

/* internal values */
#define YUVC_OK				(0)
#define YUVC_NG				(-1)

#define YUVC_ENABLE			(1)
#define YUVC_DISABLE			(0)

/* use gdmac */
#define YUVC_USE_GDMAC
/*#undef YUVC_USE_GDMAC*/

/* convert timeout */
#define YUVC_CONV_TIMEOUT		(1000)	/* 1ms */

/* yuvc register values */
#define YUVC_REG_START			(CPU_YUVC_REG_BASE)	/* 0x0A80000 ref. cpu_memap_def.h */
#define YUVC_REG_SIZE			(CPU_YUVC_REG_SIZE)	/* 0x0001000 ref. cpu_memap_def.h */
#define PMU_REG_START			TZ2000_PMU_BASE
#define PMU_REG_SIZE			TZ2000_PMU_SIZE

enum yuvc_stat {
	YUVC_STAT_IDLE = 0,
	YUVC_STAT_RUN,
	YUVC_STAT_ABORT,
	YUVC_STAT_MAX
};

/* driver structures */
struct yuvc_dev {
	struct cdev		cdev;
	struct device		*device;
	struct platform_device	*pdev;
	struct clk		*clk;
	struct completion	comp;
	spinlock_t		lock_dev;
	spinlock_t		lock_reg;
	struct mutex		mutex_run;
	enum yuvc_stat		b_run;
	atomic_t		ul_open_count;
	__u8 __iomem		*yuvcbase;
	__u8 __iomem		*pmubase;

	/* for transfer data */
	int					i_in_buff_num;
#ifndef YUVC_USE_GDMAC
	__u32 __iomem		*pfifo[8];
#endif	/* not YUVC_USE_GDMAC */

	/* convert status */
	int			convert_status;

#ifdef YUVC_USE_GDMAC
	__u32 			dmac_status;
	enum yuvc_dma_type 	dmac_type;
#endif
	__u32			yuvc_usecount;
};

struct yuvc_conv_adr {
	__u8				enable;
	struct dma_buf		*db;
	struct dma_buf_attachment	*dba;
	struct sg_table		*sg;
	dma_addr_t			addr;
};

/*===================================
Exported Variables
===================================*/

extern __u32 ul_logflags;
extern struct yuvc_dev s_yuvc_dev;

/*===================================
Macros
===================================*/


/* register access macros */

#define YUVC_WRITE(dev, offset, value)			\
do {							\
	YUVC_TEST("yuvc write:adr(%p+0x%08X), val(0x%08X)\n", \
		dev->yuvcbase, YUVC_REG(offset), value);	\
	__raw_writel(value, ((dev)->yuvcbase + YUVC_REG(offset))); \
} while (0);

#define YUVC_READ(dev, offset, value)			\
do {							\
	YUVC_TEST("yuvc read:adr(%p+0x%08X)\n", dev->yuvcbase, \
		YUVC_REG(offset));			\
	value = __raw_readl(((dev)->yuvcbase + YUVC_REG(offset))); \
} while (0);

#define YUVC_READ_2(dev, offset, value)			\
do {							\
	value = __raw_readl(((dev)->yuvcbase + YUVC_REG(offset))); \
	YUVC_TEST("yuvc read:adr(%p+0x%08X), val(0x%08X)\n", dev->yuvcbase, \
		YUVC_REG(offset), value);			\
} while (0);

#define PMU_WRITE(dev, offset, value)			\
do {							\
	YUVC_TEST("pmu write:adr(%p+0x%08X), val(0x%08X)\n", \
		dev->pmubase, PMU_REG(offset), value);	\
	__raw_writel(value, ((dev)->pmubase + PMU_REG(offset))); \
} while (0);

#define PMU_READ(dev, offset, value)			\
do {							\
	YUVC_TEST("pmu read:adr(%p+0x%08X)\n", dev->pmubase, \
		PMU_REG(offset));			\
	value = __raw_readl(((dev)->pmubase + PMU_REG(offset))); \
} while (0);

#define YUVC_WFIFO_L(value, fifo)		\
do {							\
	__raw_writel(value, fifo);	\
} while (0);

#define YUVC_SET_FIFO_L(value, fifo, num)		\
do {							\
	int		i;					\
	for (i = 0; i < num; i++)	\
		__raw_writel(value, fifo+i);	\
} while (0);

#define YUVC_COPY_FIFO_L(src, idx, fifo, num)		\
do {							\
	int		i;					\
	for (i = 0; i < num; i++)	\
		__raw_writel(src[idx+i], fifo+i);	\
} while (0);

#define PMU_RESET_ASSERT(dev)				\
	PMU_WRITE(dev, SOFTRESETON_YUVCSS_0, PMU_SR_ON_YUVC_ASSERT)
#define PMU_RESET_DEASSERT(dev)				\
	PMU_WRITE(dev, SOFTRESETOFF_YUVCSS_0, PMU_SR_OFF_YUVC_DEASSERT)
#define PMU_CLOCK_ON(dev)				\
	PMU_WRITE(dev, CLOCKGATINGOFF_YUVCSS_0, PMU_CG_OFF_YUVC_RUN);
#define PMU_CLOCK_OFF(dev)				\
	PMU_WRITE(dev, CLOCKGATINGON_YUVCSS_0, PMU_CG_ON_YUVC_STOP);

#define YUVC_VALID_IN_FORMAT(fmt)	\
		((fmt == YUVC_YUY2) ||		\
		(fmt == YUVC_YUY2_1) ||		\
		(fmt == YUVC_NV12) ||		\
		(fmt == YUVC_I420))

#define YUVC_VALID_OUT_FORMAT(fmt)	\
		((fmt == YUVC_ARGB8888) ||	\
		(fmt == YUVC_RGBA8888) ||	\
		(fmt == YUVC_RGB888) ||		\
		(fmt == YUVC_RGB565))

#define YUVC_VALID_BUF_MODE(mode)	\
		((mode == YUVC_USE_FD) ||	\
		(mode == YUVC_USE_ADDRESS))

#define YUVC_IS_CHECK_RANGE(f, a, b)		\
		(((a) <= (f)) &&	\
		((f) <= (b)))

#define YUVC_IN_FORMAT_IS_YUY2(fmt)	\
		((fmt == YUVC_YUY2) ||		\
		(fmt == YUVC_YUY2_1))

#define YUVC_OUT_FORMAT_IS_RGB8888(fmt)	\
		((fmt == YUVC_ARGB8888) ||	\
		(fmt == YUVC_RGBA8888))


/*===================================
Exported Functions prototypes
===================================*/

void yuvc_procfs_create(void);
void yuvc_procfs_remove(void);
int yuvc_init_hw(struct yuvc_dev *pdev);
int yuvc_exit_hw(struct yuvc_dev *pdev);
int yuvc_runtime_suspend_sub(struct yuvc_dev *pdev);
int yuvc_runtime_resume_sub(struct yuvc_dev *pdev);
void yuvc_mask_irq(struct yuvc_dev *pdev, bool bmask);
void yuvc_clear_irq(struct yuvc_dev *pdev, __u32 *irq);
long yuvc_chk_params(struct yuvc_dev *pdev, struct yuvc_param *prm);
long yuvc_start_sub(struct yuvc_dev *pdev, struct yuvc_param *param);
long yuvc_cancel_sub(struct yuvc_dev *pdev);

int yuvc_set_total_page_size(void);


/* convert linear address to tile address macros */
static inline __u32 phys_to_veu(__u32 p)
{
	return (p & 0xE0000000) | ((p & 0x1FE00000) >> 10);
}

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __YUVC_DRIVER_INTERNAL_MODULE_H__ */

