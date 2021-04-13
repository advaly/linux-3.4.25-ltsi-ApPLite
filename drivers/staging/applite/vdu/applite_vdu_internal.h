/*
 * drivers/staging/applite/vdu/applite_vdu_internal.h
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

#if !defined(__APPLITE_VDU_INTERNAL_H__)
#define __APPLITE_VDU_INTERNAL_H__

#define __DEBUG	0

/*===================================
include Files
===================================*/
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/list.h>
#include <linux/semaphore.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>

#include "mach/regs/cpu_memmap_def.h"
#include "mach/regs/pmu_offs_def.h"
#include "mach/regs/pmu_reg_def.h"
#include "mach/regs/econf_offs_def.h"
#include "mach/regs/mbox_offs_def.h"
#include "mach/regs/mbox_reg_def.h"
#include "vd_api.h"

/*===================================
Types and structures defined
===================================*/

/* DEFINITION VALUES */
#define VDU_DEVICE_NAME			"vdu"
#define VDU_PROC_DEVICE_NAME		"vdu"
#define VDU_DRIVER_VERSION_STRING	"1.0"
#define VDU_VIP1_FW_NAME		"applite/vdufw.bin"
#define VDU_FW_AREA_SIZE		(1024*1024)
#define VDU_TASK_STD_SIZE_KiB		(2048)	/* KiB */
#define VDU_TASK_WORK_SIZE_KiB		(22528)	/* KiB */
#define VDU_TASK_FRAME_SIZE_KiB		(39936) /* KiB */
#define VDU_TRACE_SIZE_KiB		(4)     /* KiB */
#define VDU_TOBYTE(k)			(k*1024)
#define VDU_UNDERFLOW_THR		(VDU_TOBYTE(VDU_TASK_STD_SIZE_KiB)/2)

#define VCONV_DEVICE_FILE		"/dev/vconv"

#define IRQ_NUMBER_VDU			(109)	/* interrupt signal:77 */
#define VDU_VDAPI_RSP_TIMEOUT		(1000)  /* 1s */

#if 0
	#define reg_write(v, a) { \
		pr_info("%s : REG_W(%08X:%08X)\n", VDU_DEVICE_NAME, \
			(uint32_t)a, (uint32_t)v); \
		__raw_writel(v, ((void __iomem *)a); \
	}
	#define reg_read(v, a) { \
		*v = __raw_readl((void __iomem *)a); \
		pr_info("%s : REG_R(%08X:%08X)\n", VDU_DEVICE_NAME, \
			(uint32_t)a, (uint32_t)*v); \
	}
#else
	#define reg_write(v, a) { \
		__raw_writel(v, (void __iomem *)a); \
	}
	#define reg_read(v, a) { \
		*v = __raw_readl((void __iomem *)a); \
	}
#endif

#if 0
	#define reg_write_intr(v, a) { \
		pr_info("%s : REG_W(%08X:%08X)\n", VDU_DEVICE_NAME, \
			(uint32_t)a, (uint32_t)v); \
		__raw_writel(v, (void __iomem *)a); \
	}
	#define reg_read_intr(v, a) { \
		*v = __raw_readl((void __iomem *)a); \
		pr_info("%s : REG_R(%08X:%08X)\n", VDU_DEVICE_NAME, \
			(uint32_t)a, (uint32_t)*v); \
	}
#else
	#define reg_write_intr(v, a) { \
		__raw_writel(v, (void __iomem *)a); \
	}
	#define reg_read_intr(v, a) { \
		*v = __raw_readl((void __iomem *)a); \
	}
#endif


#define xprintk(d, level, fmt, args...) \
	printk(level "%s: " fmt , (d)->pdev->name , ## args)
#if 0
#define dprintk(d, level, fmt, args...) \
	printk(level "%s:%s(): " fmt , (d)->pdev->name , __func__ , ## args)
#else
#define dprintk(d, level, fmt, args...)
#endif

#define ERROR(dev, fmt, args...) \
	xprintk(dev , KERN_ERR , fmt , ## args)
#define INFO(dev, fmt, args...) \
	xprintk(dev , KERN_INFO , fmt , ## args)
#define DBG(dev, fmt, args...) \
	dprintk(dev , KERN_DEBUG , fmt , ## args)


/* finalize flag */
#define VDU_FIN_PHASE1	0x01	/* exec shut_down */
#define VDU_FIN_PHASE2	0x02	/* exec finalize */
#define VDU_FIN_PHASE3	0x04	/* exec reset */

/* wait condition bits */
#define VDU_COND_FW		0
#define VDU_COND_TASK		1
#define VDU_COND_OUTFRM		2
#define VDU_COND_INBUF		3
#define VDU_COND_CANCEL		4

/* Definition strictures */
struct vdu_mod_data {
	int task_std;
	int task_work;
	int uf_thr;
	bool debug;
	int trace_area_size;
	char *power_ctrl;
};

enum vdu_stat {
	VDU_STAT_NOFW = 0,
	VDU_STAT_RESET_ON,
	VDU_STAT_IDLE,
	VDU_STAT_RUNNING,

	VDU_STAT_MAX
};

enum vdu_iomem {
	VDU_IOMEM_PMU_REG = 0,
	VDU_IOMEM_ECONF_REG,
	VDU_IOMEM_MBOX_REG,

	VDU_IOMEM_MAX
};

enum vdu_power_ctrl {
	VDU_POWER_CTRL_ON = 0,
	VDU_POWER_CTRL_OFF,
	VDU_POWER_CTRL_AUTO,

	VDU_POWER_CTRL_MAX
};

/* Memory Area Structure */
enum vdu_mem_align {
	VDU_MEM_ALIGN_4  = 2,
	VDU_MEM_ALIGN_8,
	VDU_MEM_ALIGN_16,
	VDU_MEM_ALIGN_32,
	VDU_MEM_ALIGN_64,

	VDU_MEM_ALIGN_1K = 10,
	VDU_MEM_ALIGN_2K,
	VDU_MEM_ALIGN_4K,
	VDU_MEM_ALIGN_8K,
	VDU_MEM_ALIGN_16K,
	VDU_MEM_ALIGN_32K,
	VDU_MEM_ALIGN_64K,

	VDU_MEM_ALIGN_1M = 20,
	VDU_MEM_ALIGN_2M,
	VDU_MEM_ALIGN_4M,
	VDU_MEM_ALIGN_8M,
	VDU_MEM_ALIGN_16M
};

enum vdu_mem_type {
	VDU_MEM_TYPE_NON = 0,
	VDU_MEM_TYPE_KALLOC,
	VDU_MEM_TYPE_DMA,
	VDU_MEM_TYPE_DMA_FW,
	VDU_MEM_TYPE_MA
};

struct vdu_locmem {
	enum vdu_mem_type type;
	size_t size;
	enum vdu_mem_align align;
	uint32_t addr;
	/* ... */
	uint32_t alloc_mem;
	dma_addr_t dma_addr;
	/* ... */
	int fd;
	int offset;
	struct dma_buf *dbuf;
	struct dma_buf_attachment *dbufa;
	struct sg_table *psgt;
};

struct vdu_driver {
	struct cdev cdev;
	struct platform_device *pdev;
	struct device *device;
	int irq;

	struct clk *clk;

	enum vdu_stat devsts;
	enum vd_result vd_res;
	/* spin lock */
	spinlock_t splock;
	/* wait */
	wait_queue_head_t vdu_waitq;
	unsigned long wait_cond;
	/* semaphore */
	struct semaphore vdu_sem;
	/* task list */
	struct list_head task_head;  /* vdu_task list head */
	int32_t task_num;
	/* local memory */
	struct vdu_locmem vd_fw_area;
	struct vdu_locmem vd_trace;

	/* ioremap */
	uint32_t io[VDU_IOMEM_MAX];
	void __iomem *iomem[VDU_IOMEM_MAX];

	/* module parameter */
	int32_t vdu_task_std_size;
	int32_t vdu_task_work_size;
	int32_t uf_thr;
	bool debug;
	int32_t trace_area_size;
	enum vdu_power_ctrl pctrl;

	/* interrupt status */
	bool fw_int_bap_boot;
	bool fw_int_vdp_boot;

	unsigned int fail;

};

struct vdu_op_device {
	struct vdu_driver *pdev;
	/* task id */
	uint32_t taskid;
};

enum vdu_task_stat {
	VDU_TASK_STAT_IDLE = 0,
	VDU_TASK_STAT_START,
	VDU_TASK_STAT_SET_EOD,
	VDU_TASK_STAT_EOD,
	VDU_TASK_STAT_STOP,
	VDU_TASK_STAT_MAX
};

/* Task Structure */
struct vdu_task {
	struct list_head list;
	struct vd_task ctx;               /* task id for VD_API */
	enum vdu_task_stat tasksts;
	struct vdu_locmem vd_task_std;
	struct vdu_locmem vd_task_work;
	struct vdu_locmem vd_task_frame;

	/* wait */
	wait_queue_head_t vdu_waitq;
	unsigned long wait_cond;

	/* threshold of input buffer free event */
	int32_t uf_thr;

	/* task info */
	uint32_t ch_num;
	char *inbuf_b;
	char *inbuf_e;

	/* interrupt status */
	bool task_int_start_stop;
	bool task_int_underflow;
	bool task_int_outfrm;
};

#define REG_PMU(p, y)	((uint32_t)((unsigned long)(p)->iomem[VDU_IOMEM_PMU_REG])+PMU_##y)
#define REG_ECONF(p, y)	((uint32_t)((unsigned long)(p)->iomem[VDU_IOMEM_ECONF_REG])+ECONF_##y)
#define REG_MBOX1(p, y)	((uint32_t)((unsigned long)(p)->iomem[VDU_IOMEM_MBOX_REG])+MBOX_INT_##y)
#define REG_MBOX4(p, y)	((uint32_t)((unsigned long)(p)->iomem[VDU_IOMEM_MBOX_REG])+MBOX_INT_##y)

/*===================================
Exported Variables
===================================*/



/*===================================
Exported Functions prototypes
===================================*/

void vdu_procfs_create(void);
void vdu_procfs_remove(void);

int vdu_ioctl_start(struct vdu_driver *, struct vdec_start *, uint32_t *);
int vdu_ioctl_stop(struct vdu_driver *, uint32_t);
int vdu_ioctl_getininfo(struct vdu_driver *, struct vdec_getininfo *, uint32_t);
int vdu_ioctl_setindata(struct vdu_driver *, struct vdec_setindata *, uint32_t);
int vdu_ioctl_getoutframe(struct vdu_driver *, struct vdec_getoutframe *,
	uint32_t);
int vdu_ioctl_reloutframe(struct vdu_driver *, uint32_t);
int vdu_ioctl_waitforinbuf(struct vdu_driver *, struct vdec_waitforinbuf *,
	uint32_t);
int vdu_ioctl_waitforoutframe(struct vdu_driver *,
	struct vdec_waitforoutframe *, uint32_t);
int vdu_ioctl_cancel(struct vdu_driver *, uint32_t);
int vdu_ioctl_getoutframewithconv(struct vdu_driver *,
	struct vdec_getoutframewithconv *, uint32_t);

int vdu_internal_init_resource(struct vdu_driver *);
void vdu_internal_clear_resource(struct vdu_driver *);
int vdu_internal_fw_download(struct vdu_driver *);
int vdu_internal_initialize(struct vdu_driver *);
int vdu_internal_finalize(struct vdu_driver *, int);
int vdu_internal_create_task(struct vdu_driver *, uint32_t *);
int vdu_internal_destroy_task(struct vdu_driver *, struct vdu_task *);
int vdu_internal_start_task(struct vdu_driver *, struct vdu_task *,
	struct vdec_start *);
int vdu_internal_stop_task(struct vdu_driver *, struct vdu_task *);
int vdu_internal_cancel_task(struct vdu_driver *, struct vdu_task *);
int vdu_internal_start(struct vdu_driver *, struct vdec_start *,
	uint32_t *);
int vdu_internal_stop(struct vdu_driver *, uint32_t);
int vdu_internal_getininfo(struct vdu_driver *, struct vdec_getininfo *,
	uint32_t);
int vdu_internal_setindata(struct vdu_driver *, struct vdec_setindata *,
	uint32_t);
int vdu_internal_getoutframe(struct vdu_driver *, struct vdec_getoutframe *,
	uint32_t);
int vdu_internal_reloutframe(struct vdu_driver *, uint32_t);
int vdu_internal_waitforinbuf(struct vdu_driver *, struct vdec_waitforinbuf *,
	uint32_t);
int vdu_internal_waitforoutframe(struct vdu_driver *,
	struct vdec_waitforoutframe *, uint32_t);
int vdu_internal_cancel(struct vdu_driver *, uint32_t);
int vdu_internal_getoutframewithconv(struct vdu_driver *,
	struct vdec_getoutframewithconv *, uint32_t);
int vdu_internal_searchtask(struct vdu_driver *, uint32_t, struct vdu_task **);
void vdu_internal_irq_function(struct vdu_driver *);
int vdu_internal_alloc_fwarea(struct vdu_driver *);
void vdu_internal_free_fwarea(struct vdu_driver *);

/* reset & power sequence */
void vdu_internal_vip1_reset(struct vdu_driver *, int);
void vdu_internal_video_power(struct vdu_driver *, int);

int vcodec_power_up(void);
int vcodec_power_down(void);

void vdu_dump(void);

static inline void *vdu_kmalloc(size_t size)
{
	void *p;
	p = kmalloc(size, GFP_KERNEL);
	/*printk("[kmalloc]:0x%08X\n",(u32)p);*/
	return p;
}

static inline void vdu_kfree(void *mem)
{
	/*printk("[kfree  ]:0x%08X\n",(u32)mem);*/
	kfree(mem);
}
#endif    /* __APPLITE_VDU_INTERNAL_H__ */

