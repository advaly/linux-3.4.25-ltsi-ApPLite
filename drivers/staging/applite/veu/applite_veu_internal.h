/*
 * drivers/staging/applite/veu/applite_veu_internal.h
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

#if !defined(__VEU_DRIVER_INTERNAL_MODULE_H__)
#define __VEU_DRIVER_INTERNAL_MODULE_H__

/*#define NOFWDWN	1*/
/*#define __TRACE	1*/
/*#define __DEBUG	1*/
/*#define __NO_BUG	1*/
#define __KEEP_FWAREA	1

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
#include "mach/regs/mbox_offs_def.h"
#include "mach/regs/mbox_reg_def.h"
#include "mach/regs/econf_offs_def.h"
#include "mach/regs/econf_reg_def.h"
#include "ve_api.h"


/*===================================
Types and structures defined
===================================*/

/* DEFINITION VALUES */
#define VEU_DEVICE_NAME			"veu"
#define VEU_PROC_DEVICE_NAME		"veu"
#define VEU_DRIVER_VERSION_STRING	"1.5"
#define VEU_VIP4_FW_NAME		"applite/veufw.bin"
#define VEU_FW_BLOCK_SIZE		(256*1024)
#define VEU_COMM_AREA_SIZE		(4*1024)
#define VEU_FW_AREA_SIZE		(240*1024)

#define VCONV_DEVICE_FILE		"/dev/vconv"

#define IRQ_NUMBER_VEU			(110)
#define VEU_VEAPI_RSP_TIMEOUT		(1*HZ)  /* 1s */
#define VEU_VEAPI_EVENT_TIMEOUT		(1*HZ)  /* 1s */
#define VEU_VEAPI_RETRY_TIME		(1*HZ)  /* 1s */
#define VEU_VEAPI_RETRY_MAX		(3)
#define VEU_FRAMEID_TBL_MAX		(64)

#if 0
	#define reg_write(v, a) { \
		dprint("%s : REG_W(%08x:%08x)\n", VEU_DEVICE_NAME, \
			(uint32_t)a, (uint32_t)v); \
		__raw_writel(v, (void __iomem *)a); \
	}
	#define reg_read(v, a) { \
		*v = __raw_readl((void __iomem *)a); \
		dprint("%s : REG_R(%08x:%08x)\n", VEU_DEVICE_NAME, \
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
#define reg_dump(s, a) { \
	uint32_t v = __raw_readl((void __iomem *)a); \
	dprint("%s:ADDR=%08x,VAL=%08x\n", s, (uint32_t)a, (uint32_t)v); \
}

/* 20130410A */
#define xprintk(d, level, fmt, args...) \
	printk(level "%s: " fmt , (d)->pdev->name , ## args)
#ifdef __DEBUG
#define dprintk(d, level, fmt, args...) \
	printk(level "%s:%s(): " fmt , (d)->pdev->name , __func__ , ## args)
#else
#define dprintk(d, level, fmt, args...)
#endif

#define ERROR(dev, fmt, args...) \
	xprintk(dev , KERN_ERR , fmt , ## args)
#define INFO(dev, fmt, args...) \
	xprintk(dev , KERN_INFO , fmt , ## args)
#define WARNING(dev, fmt, args...) \
	xprintk(dev , KERN_WARNING , fmt , ## args)
#define DBG(dev, fmt, args...) \
	dprintk(dev , KERN_DEBUG , fmt , ## args)


#if 0
	#define dparam(p) { \
		pr_info("output_mode=%d\n", (p)->output_mode); \
		pr_info("profile=%d\n", (p)->profile); \
		pr_info("level=%d\n", (p)->level); \
		pr_info("horizontal_pixels=%d\n", (p)->horizontal_pixels); \
		pr_info("vertical_pixels=%d\n", (p)->vertical_pixels); \
		pr_info("fps=%d\n", (p)->frame_rate); \
		pr_info("kbps=%d\n", (p)->kbps); \
		pr_info("max_kbps=%d\n", (p)->max_kbps); \
		pr_info("cpb_size_kbits=%d\n", (p)->cpb_size_kbits); \
		pr_info("rate_control_mode=%d\n", (p)->rate_control_mode); \
		pr_info("m=%d\n", (p)->m); \
		pr_info("n=%d\n", (p)->n); \
		pr_info("idr_freq=%d\n", (p)->idr_freq); \
		pr_info("picture_struct=%d\n", (p)->picture_struct); \
		pr_info("slice_num_minus1=%d\n", (p)->slice_num_minus1); \
		pr_info("scaling_matrix=%d\n", (p)->scaling_matrix); \
		pr_info("entropy_coding=%d\n", (p)->entropy_coding); \
		pr_info("weighted_pred=%d\n", (p)->weighted_pred); \
		pr_info("reference_b=%d\n", (p)->reference_b); \
		pr_info("inter_view_pred=%d\n", (p)->inter_view_pred); \
		pr_info("vui_parameters=%d\n", (p)->vui_parameters); \
		pr_info("sei0=%d\n", (p)->sei0); \
		pr_info("aspect_ratio_idc=%d\n", (p)->aspect_ratio_idc); \
		pr_info("sar_width=%d\n", (p)->sar_width); \
		pr_info("sar_height=%d\n", (p)->sar_height); \
		pr_info("overscan_info_present_flag=%d\n", (p)->overscan_info_present_flag); \
		pr_info("overscan_appropriate_flag=%d\n", (p)->overscan_appropriate_flag); \
		pr_info("video_signal_type_present_flag=%d\n", (p)->video_signal_type_present_flag); \
		pr_info("video_format=%d\n", (p)->video_format); \
		pr_info("video_full_range_flag=%d\n", (p)->video_full_range_flag); \
		pr_info("colour_description_present_flag=%d\n", (p)->colour_description_present_flag); \
		pr_info("colour_primaries=%d\n", (p)->colour_primaries); \
		pr_info("transfer_characteristics=%d\n", (p)->transfer_characteristics); \
		pr_info("matrix_coefficients=%d\n", (p)->matrix_coefficients); \
		pr_info("chroma_loc_info_present_flag=%d\n", (p)->chroma_loc_info_present_flag); \
		pr_info("chroma_sample_loc_type_top_field=%d\n", (p)->chroma_sample_loc_type_top_field); \
		pr_info("chroma_sample_loc_type_bottom_field=%d\n", (p)->chroma_sample_loc_type_bottom_field); \
		pr_info("timing_info_present_flag=%d\n", (p)->timing_info_present_flag); \
		pr_info("num_units_in_tick=%d\n", (p)->num_units_in_tick); \
		pr_info("time_scale=%d\n", (p)->time_scale); \
		pr_info("fixed_frame_rate_flag=%d\n", (p)->fixed_frame_rate_flag); \
		pr_info("nal_hrd_parameters_present_flag=%d\n", (p)->nal_hrd_parameters_present_flag); \
		pr_info("vcl_hrd_parameters_present_flag=%d\n", (p)->vcl_hrd_parameters_present_flag); \
		pr_info("low_delay_hrd_flag=%d\n", (p)->low_delay_hrd_flag); \
		pr_info("pic_struct_present_flag=%d\n", (p)->pic_struct_present_flag); \
		pr_info("bitstream_restriction_flag=%d\n", (p)->bitstream_restriction_flag); \
	}
#else
	#define dparam(p) { \
	}
#endif

/* DEFINITION STRUCTURES */
struct veu_mod_data { /* 20130410A */
	char *power_ctrl;
};

enum veu_stat {
	VEU_STAT_NOFW = 0,
	VEU_STAT_RESET_ON,
	VEU_STAT_IDLE,
	VEU_STAT_RUNNING,
	VEU_STAT_MAX
};

enum veu_iomem {
	VEU_IOMEM_PMU_REG = 0,
	VEU_IOMEM_MBOX_REG,
	VEU_IOMEM_ECONF_REG,

	VEU_IOMEM_MAX
};

enum veu_power_ctrl { /* 20130410A */
	VEU_POWER_CTRL_ON = 0,
	VEU_POWER_CTRL_OFF,
	VEU_POWER_CTRL_AUTO,

	VEU_POWER_CTRL_MAX
};

struct veu_driver {
	struct cdev cdev;
	struct platform_device *pdev;
	struct device *device;

	struct clk *clk;

	enum veu_stat devsts;
	struct list_head resp_head; /* 20130410A */
	int32_t resp_num;           /* 20130410A */
	/* spin lock */
	spinlock_t splock;
	/* wait */
	wait_queue_head_t veu_waitq;
	unsigned long wait_cond;
	/* semaphore */
	struct semaphore veu_sem;
	/* tasklet */
	struct tasklet_struct veu_tasklet;
	/* task list */
	struct list_head task_head;  /* SVEU_TASK list head */
	int32_t task_num;
	/* shard memory list */
	struct list_head ma_head;    /* SVEU_MA list head */
	int32_t ma_num;

	/* ioremap */
	uint32_t io[VEU_IOMEM_MAX];
	void __iomem *iomem[VEU_IOMEM_MAX];

	enum veu_power_ctrl pctrl; /* 20130410A */
	int irq;
};

struct veu_op_device {
	struct veu_driver *pdev;
	/* task id */
	uint32_t taskid;
	struct semaphore veu_sem;
};

/* Memory Area Structure */
enum veu_mem_align {
	VEU_MEM_ALIGN_4  = 2,
	VEU_MEM_ALIGN_8,
	VEU_MEM_ALIGN_16,
	VEU_MEM_ALIGN_32,
	VEU_MEM_ALIGN_64,

	VEU_MEM_ALIGN_1K = 10,
	VEU_MEM_ALIGN_2K,
	VEU_MEM_ALIGN_4K,
	VEU_MEM_ALIGN_8K,
	VEU_MEM_ALIGN_16K,
	VEU_MEM_ALIGN_32K,
	VEU_MEM_ALIGN_64K,

	VEU_MEM_ALIGN_1M = 20,
	VEU_MEM_ALIGN_2M,
	VEU_MEM_ALIGN_4M,
	VEU_MEM_ALIGN_8M,
	VEU_MEM_ALIGN_16M
};

enum veu_mem_type {
	VEU_MEM_TYPE_NON = 0,
	VEU_MEM_TYPE_KALLOC,
	VEU_MEM_TYPE_DMA,
	VEU_MEM_TYPE_DMA_FW,
	VEU_MEM_TYPE_MA
};

struct veu_locmem {
	enum veu_mem_type type;
	size_t size;
	enum veu_mem_align align;
	uint32_t addr;
	/* ... */
	uint32_t alloc_mem;
	dma_addr_t dma_addr;
	int fd;
};

/* Encode Status */
enum veu_encode_stat {
	VEU_ENC_STAT_WAITING = 0,
	VEU_ENC_STAT_RUNNING,
	VEU_ENC_STAT_FINISHED,
	VEU_ENC_STAT_MAX
};

/* Encode Management Structure */
struct veu_enc {
	struct list_head list;
	struct ve_picture_entry pic;   /* encode info */
	int fd_luma;
	int fd_chroma;
	struct sg_table *sgt_luma;
	struct sg_table *sgt_chroma;
	enum veu_encode_stat encsts;   /* encode status */
	int retry;
	int flush;
	/**/
	int withconv_enable;
	struct vconv_param vconv_param;
};

/* Event Code */
enum veu_event_code {
	VEU_EVT_ENCODED = 0,
	VEU_EVT_NALOUT,
	VEU_EVT_RELEASE,
	VEU_EVT_MAX
};

/* Event Management Structure */
struct veu_event {
	struct list_head list;
	enum veu_event_code event;
	uint64_t frameid;
	int32_t result;
};

struct veu_frameid_tbl {
	uint64_t frameid_tbl[VEU_FRAMEID_TBL_MAX+1];
	int32_t frameid_wp;
	int32_t frameid_rp_encoded;
	int32_t frameid_rp_nalout;
	int32_t frameid_rp_release;
};

/* VE_API Task Structure */
struct veu_task {
	struct list_head list;
	struct ve_task *ctx;               /* task id for VE_API */
	struct veu_locmem ve_task_api;
	struct veu_locmem ve_task_fw;
	struct veu_locmem ve_buf_ctl;
	struct veu_locmem ve_buf_out;
	struct veu_locmem ve_buf_inf;
	struct veu_locmem ve_buf_wrk;
	struct veu_locmem ve_buf_ref;
	struct ve_param param;
	uint32_t tail_ve_buf_ref;

	struct list_head resp_head; /* 20130410A */
	int32_t resp_num;           /* 20130410A */

	struct list_head encoding_head;    /* struct veu_enc list head */
	struct list_head encoded_head;     /* struct veu_enc list head */
	struct list_head encfin_head;      /* struct veu_event list head */
	struct list_head nal_head;         /* struct veu_event list head */
	struct list_head rel_head;         /* struct veu_event list head */
	struct veu_frameid_tbl frameid_tbl;
	wait_queue_head_t task_waitq;
	unsigned long wait_cond;
	char *outbuf_b;
	char *outbuf_e;

	uint32_t is_eos;
	uint64_t eos_frame_id;

#ifdef __NO_BUG
	struct ve_output_entry entry;
#endif
};

/* Response Structure */ /* 20130410A */
#define VEU_COND_START_UP_PU		0
#define VEU_COND_SHUT_DOWN_PU		1
#define VEU_COND_INITIALIZE_TASK	2
#define VEU_COND_INITIALIZE_IOBUFFER	3
#define VEU_COND_ENCODE			4
#define VEU_COND_KILL_TASK		5
struct veu_response {
	struct list_head list;
	unsigned long resp_flag;
	struct ve_response resp;
	struct ve_dying_message msg;
};

/* Shard Memory Management Structure */
struct veu_ma {
	struct list_head list;
	int fd;
	struct dma_buf *dbuf;
	struct dma_buf_attachment *dbufa;
	int32_t map_count;
};


#define REG_PMU(p, y)	((uint32_t)((unsigned long)(p)->iomem[VEU_IOMEM_PMU_REG])+PMU_##y)
#define REG_ECONF(p, y)	((uint32_t)((unsigned long)(p)->iomem[VEU_IOMEM_ECONF_REG])+ECONF_##y)
#define REG_MBOX1(p, y)	((uint32_t)((unsigned long)(p)->iomem[VEU_IOMEM_MBOX_REG])+MBOX_INT_##y)
#define REG_MBOX5(p, y)	((uint32_t)((unsigned long)(p)->iomem[VEU_IOMEM_MBOX_REG])+MBOX_INT_##y)
#define ADDR_PMU(p, y)	 (((unsigned long)(p)->io[VEU_IOMEM_PMU_REG])+PMU_##y)
#define ADDR_ECONF(p, y) (((unsigned long)(p)->io[VEU_IOMEM_ECONF_REG])+ECONF_##y)
#define ADDR_MBOX1(p, y) (((unsigned long)(p)->io[VEU_IOMEM_MBOX_REG])+MBOX_INT_##y)
#define ADDR_MBOX5(p, y) (((unsigned long)(p)->io[VEU_IOMEM_MBOX_REG])+MBOX_INT_##y)

/*===================================
Exported Variables
===================================*/



/*===================================
Exported Functions prototypes
===================================*/

void veu_procfs_create(void);
void veu_procfs_remove(void);
int veu_ioctl_getparam(struct veu_driver*, struct venc_getparam*, uint32_t);
int veu_ioctl_setparam(struct veu_driver*, struct venc_setparam*, uint32_t);
int veu_ioctl_setinframe(struct veu_driver*, struct venc_setinframe*,
	uint32_t);
int veu_ioctl_waitforevents(struct veu_driver*, struct venc_waitforevents*,
	uint32_t);
int veu_ioctl_getoutframe(struct veu_driver*, struct venc_getoutframe*,
	uint32_t);
int veu_ioctl_setinframewithcnv(struct veu_driver*,
	struct venc_setinframewithcnv*, uint32_t);

int veu_internal_init_resource(struct veu_driver *);
void veu_internal_clear_resource(struct veu_driver *);
int veu_internal_fw_download(struct veu_driver *);
int veu_internal_initialize(struct veu_driver *);
int veu_internal_finalize(struct veu_driver *);
int veu_internal_cretask(struct veu_driver *, uint32_t *);
int veu_internal_killtask(struct veu_driver *, uint32_t);
int veu_internal_getparam(struct veu_driver *,
	struct venc_getparam *, uint32_t);
int veu_internal_setparam(struct veu_driver *,
	struct venc_setparam *, uint32_t);
int veu_internal_setinframe(struct veu_driver *,
	struct venc_setinframe *, uint32_t);
int veu_internal_waitforevents(struct veu_driver *,
	struct venc_waitforevents*, uint32_t);
int veu_internal_getoutframe(struct veu_driver *,
	struct venc_getoutframe*, uint32_t);
int veu_internal_setinframewithcnv(struct veu_driver *,
	struct venc_setinframewithcnv *, uint32_t);

int veu_internal_searchtask(struct veu_driver *,
	uint32_t, struct veu_task **);
void veu_internal_tasklet_function(struct veu_driver *);
void veu_internal_irq_function(struct veu_driver *);
#ifdef __KEEP_FWAREA
int veu_internal_alloc_fwarea(struct veu_driver *);
void veu_internal_free_fwarea(struct veu_driver *);
#endif
int veu_internal_alloc_tracearea(struct veu_driver *, int);
void veu_internal_free_tracearea(struct veu_driver *);
int veu_internal_get_tracearea(struct veu_driver *,
	uint32_t *, uint32_t *);

/* reset & power sequence */
void veu_internal_vip4_reset(struct veu_driver *, int);
void veu_internal_video_power(struct veu_driver *, int);

int vcodec_power_up(void);
int vcodec_power_down(void);

void veu_dump(void);

extern struct veu_driver s_veu_dev;

#endif    /* __VEU_DRIVER_INTERNAL_MODULE_H__ */

