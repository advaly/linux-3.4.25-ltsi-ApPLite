/*
 * linux/drivers/staging/applite/applite_vconv_internal.h
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

#if !defined(__VCONV_DRIVER_INTERNAL_MODULE_H__)
#define __VCONV_DRIVER_INTERNAL_MODULE_H__

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

#include <mach/platform.h>
#include <mach/regs/vconv_offs_def.h>
#include <mach/regs/vconv_reg_def.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/pmu_reg_def.h>
#include <mach/regs/econf_offs_def.h>
#include <mach/regs/fdramc_offs_def.h>
#include <mach/regs/cpu_memmap_def.h>

#include "applite_vconv_regs.h"



/*===================================
Types and structures   defined
===================================*/

/* driver values */
#define	DEVICE_NAME			"vconv"
#define	PROC_DEVICE_NAME		"vconv"
#define PROC_STS_NAME			"status"
#define PROC_REG_NAME			"regs"
#define PROC_LOGFLAG_NAME		"logflag"
#define	VCONV_DRIVER_VERSION		"1.0"

/* interrupt values */
#define VCONV_IRQ_NUM			(168)
#define VCONV_ERR_IRQ_NUM		(169)
#define VCONV_IRQ_FLAG			(IRQF_SHARED | IRQF_TRIGGER_HIGH)

/* VEU tile address space values */
#define VCONV_MAX_INDEX			(6)

/* internal values */
#define VCONV_OK			(0)
#define VCONV_NG			(-1)

#define VCONV_ENABLE			(1)
#define VCONV_DISABLE			(0)


/* vconv register values */

#define VCONV_REG_START			CPU_VCONV_REG_BASE
#define VCONV_REG_SIZE			CPU_VCONV_REG_SIZE
#define PMU_REG_START			CPU_PMU_REG_BASE
#define PMU_REG_SIZE			CPU_PMU_REG_SIZE
#define FDRAMC_REG_START		CPU_FDRAMC_REG_BASE
#define FDRAMC_REG_SIZE			CPU_FDRAMC_REG_SIZE
#define ECONF_REG_START			CPU_ECONF_REG_BASE
#define ECONF_REG_SIZE			CPU_ECONF_REG_SIZE

enum vconv_stat {
	VCONV_STAT_IDLE = 0,
	VCONV_STAT_RUN,
	VCONV_STAT_ABORT,
	VCONV_STAT_MAX
};

/* driver structures */
struct vconv_dev {
	struct cdev		cdev;
	struct device		*device;
	struct platform_device	*pdev;
	struct clk		*clk;
	struct completion	comp;
	spinlock_t		lock_dev;
	spinlock_t		lock_reg;
	struct mutex		mutex_run;
	enum vconv_stat		b_run;
	atomic_t		ul_open_count;
	__u8 __iomem		*vconvbase;
	__u8 __iomem		*pmubase;
	__u32			ul_num_frame_end_irq;
	__u32			ul_num_start_err_irq;
	__u32			ul_num_reg_err_irq;
	__u32			ul_num_disp_err_irq;
	__u32			ul_num_merge_err_irq;
	__u32			vconv_usecount;
};


struct vconv_conv_adr {
	__u8 enable;
	struct dma_buf *db;
	struct dma_buf_attachment *dba;
	struct sg_table *sg;
	dma_addr_t addr;
};

/*===================================
Exported Variables
===================================*/

extern __u32 ul_logflags;
extern struct vconv_dev s_vconv_dev;

/*===================================
Macros
===================================*/


/* register access macros */

#define VCONV_WRITE(dev, offset, value)			\
do {							\
	VCONV_TEST("vconv write:adr(%p+0x%08X), val(0x%08X)\n", \
		dev->vconvbase, VCONV_REG(offset), value);	\
	__raw_writel(value, ((dev)->vconvbase + VCONV_REG(offset))); \
} while (0);
#define VCONV_READ(dev, offset, value)			\
do {							\
	VCONV_TEST("vconv read:adr(%p+0x%08X)\n", dev->vconvbase, \
		VCONV_REG(offset));			\
	value = __raw_readl(((dev)->vconvbase + VCONV_REG(offset))); \
} while (0);
#define PMU_WRITE(dev, offset, value)			\
do {							\
	VCONV_TEST("pmu write:adr(%p+0x%08X), val(0x%08X)\n", \
		dev->pmubase, PMU_REG(offset), value);	\
	__raw_writel(value, ((dev)->pmubase + PMU_REG(offset))); \
} while (0);
#define PMU_READ(dev, offset, value)			\
do {							\
	VCONV_TEST("pmu read:adr(%p+0x%08X)\n", dev->pmubase, \
		PMU_REG(offset));			\
	value = __raw_readl(((dev)->pmubase + PMU_REG(offset))); \
} while (0);

#define PMU_RESET_ASSERT(dev)				\
	PMU_WRITE(dev, SoftResetOn_vconvSS_0, PMU_SR_ON_VCONV_ASSERT)
#define PMU_RESET_DEASSERT(dev)				\
	PMU_WRITE(dev, SoftResetOff_vconvSS_0, PMU_SR_OFF_VCONV_DEASSERT)
#define PMU_CLOCK_ON(dev)				\
	PMU_WRITE(dev, ClockGatingOff_vconvSS_0, PMU_CG_OFF_VCONV_RUN);
#define PMU_CLOCK_OFF(dev)				\
	PMU_WRITE(dev, ClockGatingOn_vconvSS_0, PMU_CG_ON_VCONV_STOP);


#define VCONV_RECT_IS_ZERO(s)				\
		(((s).h == 0) && ((s).v == 0))
#define VCONV_RECT_IS_SAME(s1, s2)			\
		(((s1).h == (s2).h) && ((s1).v == (s2).v))

#define VCONV_SCALE_IS_ZERO(s)				\
		(((s).integer == 0) && ((s).fraction == 0))
#define VCONV_SCALE_IS_ONE(s)				\
		(((s).integer == 1) && ((s).fraction == 0))
#define VCONV_SCALE_IS_NOT_ONE(s)			\
		(!VCONV_SCALE_IS_ONE(s))
#define VCONV_SCALE_TO_ULONG(s)				\
		(((__u32)((s).integer) << 16) | (__u32)((s).fraction))
#define VCONV_SCALE_MIN					(0x00004000) /* 1/4 */
#define VCONV_SCALE_MAX					(0x00040000) /* 4 */
#define VCONV_SCALE_SHIFT				(16)
#define VCONV_SCALE_HALF				\
					(1 << (VCONV_SCALE_SHIFT - 1))
#define VCONV_MUL_SCALE(b, s)				\
do {							\
	b *= VCONV_SCALE_TO_ULONG(s);			\
	b = ((b + VCONV_SCALE_HALF) >> VCONV_SCALE_SHIFT); \
} while (0);
#define VCONV_SCALING_SIZE(b, s)			\
do {							\
	b <<= VCONV_SCALE_SHIFT;			\
	b /= VCONV_SCALE_TO_ULONG(s);			\
} while (0);

#define VCONV_VALID_FORMAT(fmt)				\
		((fmt == VCONV_PK_R_BGR565) ||		\
		(fmt == VCONV_PK_R_RGB565) ||		\
		(fmt == VCONV_PK_R_ABGR1555) ||		\
		(fmt == VCONV_PK_R_ARGB1555) ||		\
		(fmt == VCONV_PK_R_ABGR8888) ||		\
		(fmt == VCONV_PK_R_ARGB8888) ||		\
		(fmt == VCONV_PK_T_BGR565) ||		\
		(fmt == VCONV_PK_T_RGB565) ||		\
		(fmt == VCONV_PK_T_ABGR1555) ||		\
		(fmt == VCONV_PK_T_ARGB1555) ||		\
		(fmt == VCONV_PK_T_ABGR8888) ||		\
		(fmt == VCONV_PK_T_ARGB8888) ||		\
		(fmt == VCONV_FL_R_R8G8B8) ||		\
		(fmt == VCONV_FL_T_R8G8B8) ||		\
		(fmt == VCONV_PK_R_AYCBCR8888) ||	\
		(fmt == VCONV_PK_R_ACBCRY8888) ||	\
		(fmt == VCONV_PK_T_AYCBCR8888) ||	\
		(fmt == VCONV_PK_T_ACBCRY8888) ||	\
		(fmt == VCONV_FL_R_Y8CB8CR8_444) ||	\
		(fmt == VCONV_FL_R_Y8CB8CR8_422) ||	\
		(fmt == VCONV_PK_T_VDU1) ||		\
		(fmt == VCONV_PK_T_VDU2) ||		\
		(fmt == VCONV_PT_R_Y8CBCR16) ||		\
		(fmt == VCONV_PT_T_Y8CBCR16) ||		\
		(fmt == VCONV_PT_T_Y8CB8CR8) ||		\
		(fmt == VCONV_PT_T_VEU) ||		\
		(fmt == VCONV_FL_R_Y8CB8CR8_420))


#define VCONV_VALID_IN_FORMAT(fmt)			\
		((fmt == VCONV_PK_R_BGR565) ||		\
		(fmt == VCONV_PK_R_RGB565) ||		\
		(fmt == VCONV_PK_R_ABGR1555) ||		\
		(fmt == VCONV_PK_R_ARGB1555) ||		\
		(fmt == VCONV_PK_R_ABGR8888) ||		\
		(fmt == VCONV_PK_R_ARGB8888) ||		\
		(fmt == VCONV_PK_T_BGR565) ||		\
		(fmt == VCONV_PK_T_RGB565) ||		\
		(fmt == VCONV_PK_T_ABGR1555) ||		\
		(fmt == VCONV_PK_T_ARGB1555) ||		\
		(fmt == VCONV_PK_T_ABGR8888) ||		\
		(fmt == VCONV_PK_T_ARGB8888) ||		\
		(fmt == VCONV_FL_R_R8G8B8) ||		\
		(fmt == VCONV_FL_T_R8G8B8) ||		\
		(fmt == VCONV_PK_R_AYCBCR8888) ||	\
		(fmt == VCONV_PK_R_ACBCRY8888) ||	\
		(fmt == VCONV_PK_T_AYCBCR8888) ||	\
		(fmt == VCONV_PK_T_ACBCRY8888) ||	\
		(fmt == VCONV_FL_R_Y8CB8CR8_444) ||	\
		(fmt == VCONV_FL_R_Y8CB8CR8_422) ||	\
		(fmt == VCONV_PK_T_VDU1) ||		\
		(fmt == VCONV_PK_T_VDU2) ||		\
		(fmt == VCONV_PT_R_Y8CBCR16) ||		\
		(fmt == VCONV_PT_T_Y8CBCR16) ||		\
		(fmt == VCONV_PT_T_Y8CB8CR8) ||		\
		(fmt == VCONV_FL_R_Y8CB8CR8_420))

#define VCONV_VALID_OUT_FORMAT(fmt)			\
		((fmt == VCONV_PK_R_BGR565) ||		\
		(fmt == VCONV_PK_R_RGB565) ||		\
		(fmt == VCONV_PK_R_ABGR1555) ||		\
		(fmt == VCONV_PK_R_ARGB1555) ||		\
		(fmt == VCONV_PK_R_ABGR8888) ||		\
		(fmt == VCONV_PK_R_ARGB8888) ||		\
		(fmt == VCONV_PK_T_BGR565) ||		\
		(fmt == VCONV_PK_T_RGB565) ||		\
		(fmt == VCONV_PK_T_ABGR1555) ||		\
		(fmt == VCONV_PK_T_ARGB1555) ||		\
		(fmt == VCONV_PK_T_ABGR8888) ||		\
		(fmt == VCONV_PK_T_ARGB8888) ||		\
		(fmt == VCONV_FL_R_R8G8B8) ||		\
		(fmt == VCONV_FL_T_R8G8B8) ||		\
		(fmt == VCONV_PK_R_AYCBCR8888) ||	\
		(fmt == VCONV_PK_R_ACBCRY8888) ||	\
		(fmt == VCONV_PK_T_AYCBCR8888) ||	\
		(fmt == VCONV_PK_T_ACBCRY8888) ||	\
		(fmt == VCONV_FL_R_Y8CB8CR8_444) ||	\
		(fmt == VCONV_FL_R_Y8CB8CR8_422) ||	\
		(fmt == VCONV_PT_R_Y8CBCR16) ||		\
		(fmt == VCONV_PT_T_Y8CBCR16) ||		\
		(fmt == VCONV_PT_T_Y8CB8CR8) ||		\
		(fmt == VCONV_PT_T_VEU) ||		\
		(fmt == VCONV_FL_R_Y8CB8CR8_420))

#define VCONV_INVALID_PITCH(dir, prm, bpp, pln)		\
		((prm)->dir##_buffer[pln].pitch < \
		((__u32)((prm)->dir##_img.size.h) * (__u32)(bpp[pln]) / 8))
#define VCONV_INVALID_PITCH_HALF(dir, prm, bpp, pln)	\
		((prm)->dir##_buffer[pln].pitch < \
		((__u32)((prm)->dir##_img.size.h) * (__u32)(bpp[pln]) / 8 / 2))
#define VCONV_INVALID_OUT_PITCH(prm, bpp, pln)		\
		((prm)->out_buffer[pln].pitch < \
		((__u32)((prm)->out_img.size.h) * (__u32)(bpp[pln]) / 8))
#define VCONV_INVALID_OUT_PITCH_HALF(prm, bpp, pln)	\
		((prm)->out_buffer[pln].pitch < \
		((__u32)((prm)->out_img.size.h) * (__u32)(bpp[pln]) / 8 / 2))

#define IS_VCONV_CONV_R2Y(prm)				\
		((VCONV_GET_COLOR(prm->in_img.format) == VCONV_RGB) \
		&& (VCONV_GET_COLOR(prm->out_img.format) != VCONV_RGB))

#define IS_VCONV_CONV_Y2R(prm)				\
		((VCONV_GET_COLOR((prm)->out_img.format) == VCONV_RGB) \
		&& (VCONV_GET_COLOR((prm)->in_img.format) != VCONV_RGB))

#define VCONV_FORMAT_IS_VDU(dir, prm)			\
		(((prm)->dir##_img.format == VCONV_PK_T_VDU1)	\
		|| ((prm)->dir##_img.format == VCONV_PK_T_VDU2))

#define VCONV_FORMAT_IS_VEU(dir, prm)			\
		((prm)->dir##_img.format == VCONV_PT_T_VEU)

#define VCONV_FORMAT_IS_422_420_FL_R(dir, prm)		\
		(((prm)->dir##_img.format == VCONV_FL_R_Y8CB8CR8_422)	\
		|| ((prm)->dir##_img.format == VCONV_FL_R_Y8CB8CR8_420))

#define VCONV_IS_FORMAT_ID_RANGE(f, a, b)		\
		(((a) <= VCONV_GET_FORMAT_ID(f)) &&	\
		(VCONV_GET_FORMAT_ID(f) <= (b)))


/*===================================
Exported Functions prototypes
===================================*/

void vconv_procfs_create(void);
void vconv_procfs_remove(void);
int vconv_init_hw(struct vconv_dev *pdev);
int vconv_exit_hw(struct vconv_dev *pdev);
int vconv_runtime_resume_sub(struct vconv_dev *pdev);
int vconv_runtime_suspend_sub(struct vconv_dev *pdev);
void vconv_mask_irq(struct vconv_dev *pdev, bool bmask);
void vconv_clear_irq(struct vconv_dev *pdev, __u32 *irq);
long vconv_chk_params(struct vconv_dev *pdev, struct vconv_param_ex *prm);
long vconv_start_sub(struct vconv_dev *pdev, struct vconv_param_ex *param);
long vconv_cancel_sub(struct vconv_dev *pdev);
long vconv_verify_sub(struct vconv_dev *pdev, struct vconv_verify *verify);
long vconv_verify(struct vconv_verify *verify);

int vconv_set_total_page_size(struct vconv_dev *pdev);


/* convert linear address to tile address macros */
static inline __u32 phys_to_tile(__u32 p)
{
	return (p & 0xE0000000) | ((p & 0x1FF00000) >> 10);
}

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __VCONV_DRIVER_INTERNAL_MODULE_H__ */

