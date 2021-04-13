/*
 * linux/drivers/media/video/applite-camera.c
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
#define __DEBUG
#define __APPLITE_DEBUG

#include <linux/init.h>
#include <linux/module.h>
#include <linux/videodev2.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/vmalloc.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/pm_runtime.h>

#include <media/v4l2-common.h>
#include <media/v4l2-dev.h>
#include <media/videobuf2-dma-contig.h>
#include <media/soc_camera.h>
#include <media/soc_mediabus.h>
#include <media/applite-camera.h>

#include <mach/regs/camif_offs_def.h>

#ifndef V4L2_PIX_FMT_YU24
#define V4L2_PIX_FMT_YU24	v4l2_fourcc('Y', 'U', '2', '4')
#endif

#define SELF_CLK

/*
 CAMIF registers
 */
/* CVDMAC */
#define CAM_STADR		CAMIF_CAM_STADR_OFFS
#define CAM_ENDADR		CAMIF_CAM_ENDADR_OFFS
#define CAM_DMRADR		CAMIF_CAM_DMRADR_OFFS
#define CAM_CFG			CAMIF_CAM_CFG_OFFS
#define CAM_INT_MASK		CAMIF_CAM_INT_MASK_OFFS
#define CAM_W_ENABLE		CAMIF_CAM_W_ENABLE_OFFS
#define CAM_CTRL		CAMIF_CAM_CTRL_OFFS
#define CAM_W_BASE1(ch, n)	(0x40 * ((ch)*3+(n)))
#define CAM_W_STADR(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_STADR_OFFS)
#define CAM_W_ENDAD(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_ENDADR_OFFS)
#define CAM_W_HEIGH(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_HEIGHT_OFFS)
#define CAM_W_PITCH(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_PITCH_OFFS)
#define CAM_W_CFG0(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_CFG0_OFFS)
#define CAM_W_CFG1(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_CFG1_OFFS)
#define CAM_W_SRAM_BASE(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_SRAM_BASE_OFFS)
#define CAM_W_SRAM_SIZE(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_SRAM_SIZE_OFFS)
#define CAM_W_INTL(ch, n)	(CAM_W_BASE1(ch, n) + CAMIF_CAM_W00_INTL_OFFS)
#define CAM_W_ENABLE_BUF	CAMIF_CAM_W_ENABLE_BUF_OFFS
#define CAM_W_BASE2(ch, n)	(0x20 * ((ch)*3+(n)))
#define CAM_W_STADR_BUF(ch, n)	(CAM_W_BASE2(ch, n) + CAMIF_CAM_W00_STADR_BUF_OFFS)
#define CAM_W_ENDAD_BUF(ch, n)	(CAM_W_BASE2(ch, n) + CAMIF_CAM_W00_ENDADR_BUF_OFFS)
#define CAM_W_HEIGH_BUF(ch, n)	(CAM_W_BASE2(ch, n) + CAMIF_CAM_W00_HEIGHT_BUF_OFFS)
#define CAM_W_PITCH_BUF(ch, n)	(CAM_W_BASE2(ch, n) + CAMIF_CAM_W00_PITCH_BUF_OFFS)
#define CAM_W_CFG0_BUF(ch, n)	(CAM_W_BASE2(ch, n) + CAMIF_CAM_W00_CFG0_BUF_OFFS)
#define CAM_W_CFG1_BUF(ch, n)	(CAM_W_BASE2(ch, n) + CAMIF_CAM_W00_CFG1_BUF_OFFS)
#define CAM_STATUS		CAMIF_CAM_STATUS_OFFS
#define CAM_INT			CAMIF_CAM_INT_OFFS
#define CAM_W_SRAM		CAMIF_CAM_W_SRAM_OFFS
#define CAM_W_STOP		CAMIF_CAM_W_STOP_OFFS
#define CAM_W_RUN		CAMIF_CAM_W_RUN_OFFS
/* CSIRX */
#define CRX_BASE(ch)			(0x400 * (ch))
#define CRX_CDSIRX_CLKEN(ch)		(CRX_BASE(ch) + CAMIF_CRX0_CDSIRX_CLKEN_OFFS)
#define CRX_CDSIRX_CLKSEL(ch)		(CRX_BASE(ch) + CAMIF_CRX0_CDSIRX_CLKSEL_OFFS)
#define CRX_MODE_CONFIG(ch)		(CRX_BASE(ch) + CAMIF_CRX0_MODE_CONFIG_OFFS)
#define CRX_CDSIRX_SYSTEM_INIT(ch)	(CRX_BASE(ch) + CAMIF_CRX0_CDSIRX_SYSTEM_INIT_OFFS)
#define CRX_LANE_ENABLE(ch)		(CRX_BASE(ch) + CAMIF_CRX0_LANE_ENABLE_OFFS)
#define CRX_VC_ENABLE(ch)		(CRX_BASE(ch) + CAMIF_CRX0_VC_ENABLE_OFFS)
#define CRX_CDSIRX_START(ch)		(CRX_BASE(ch) + CAMIF_CRX0_CDSIRX_START_OFFS)
#define CRX_LINE_INIT_COUNT(ch)		(CRX_BASE(ch) + CAMIF_CRX0_LINE_INIT_COUNT_OFFS)
#define CRX_HSRXTO_COUNT(ch)		(CRX_BASE(ch) + CAMIF_CRX0_HSRXTO_COUNT_OFFS)
#define CRX_FUNC_ENABLE(ch)		(CRX_BASE(ch) + CAMIF_CRX0_FUNC_ENABLE_OFFS)
#define CRX_FUNC_MODE(ch)		(CRX_BASE(ch) + CAMIF_CRX0_FUNC_MODE_OFFS)
#define CRX_LPRX_STATE_INT_STAT(ch)	(CRX_BASE(ch) + CAMIF_CRX0_LPRX_STATE_INT_STAT_OFFS)
#define CRX_LPRX_STATE_INT_MASK(ch)	(CRX_BASE(ch) + CAMIF_CRX0_LPRX_STATE_INT_MASK_OFFS)
#define CRX_CDSIRX_INTERNAL_STAT(ch)	(CRX_BASE(ch) + CAMIF_CRX0_CDSIRX_INTERNAL_STAT_OFFS)
#define CRX_RXERR_INT_STAT(ch)		(CRX_BASE(ch) + CAMIF_CRX0_RXERR_INT_STAT_OFFS)
#define CRX_RXERR_INT_MASK(ch)		(CRX_BASE(ch) + CAMIF_CRX0_RXERR_INT_MASK_OFFS)
#define CRX_ERR_STATUS(ch)		(CRX_BASE(ch) + CAMIF_CRX0_ERR_STATUS_OFFS)
#define CRX_PPI_HSRX_CNTRL(ch)		(CRX_BASE(ch) + CAMIF_CRX0_PPI_HSRX_CNTRL_OFFS)
#define CRX_PPI_HSRX_COUNT(ch)		(CRX_BASE(ch) + CAMIF_CRX0_PPI_HSRX_COUNT_OFFS)
#define CRX_PPI_DPHY_DLYCNTRL(ch)	(CRX_BASE(ch) + CAMIF_CRX0_PPI_DPHY_DLYCNTRL_OFFS)
#define CRX_PPI_DPHY_LPRX_THSLD(ch)	(CRX_BASE(ch) + CAMIF_CRX0_PPI_DPHY_LPRX_THSLD_OFFS)
#define CRX_PPI_DPHY_LPRXCALCNTRL(ch)	(CRX_BASE(ch) + CAMIF_CRX0_PPI_DPHY_LPRXCALCNTRL_OFFS)
#define CRX_PPI_DPHY_LPRXAUTOCALST(ch)	(CRX_BASE(ch) + CAMIF_CRX0_PPI_DPHY_LPRXAUTOCALST_OFFS)
#define CRX_LANE_STATUS_HS(ch)		(CRX_BASE(ch) + CAMIF_CRX0_LANE_STATUS_HS_OFFS)
#define CRX_LANE_STATUS_LP(ch)		(CRX_BASE(ch) + CAMIF_CRX0_LANE_STATUS_LP_OFFS)
#define CRX_VC0_SH_INT_STAT(ch)		(CRX_BASE(ch) + CAMIF_CRX0_VC0_SH_INT_STAT_OFFS)
#define CRX_VC0_SH_INT_MASK(ch)		(CRX_BASE(ch) + CAMIF_CRX0_VC0_SH_INT_MASK_OFFS)
#define CRX_VC0_LN0_INT_STAT(ch)	(CRX_BASE(ch) + CAMIF_CRX0_VC0_LN0_INT_STAT_OFFS)
#define CRX_VC0_LN1_INT_STAT(ch)	(CRX_BASE(ch) + CAMIF_CRX0_VC0_LN1_INT_STAT_OFFS)
#define CRX_VC0_LN0_INT_MASK(ch)	(CRX_BASE(ch) + CAMIF_CRX0_VC0_LN0_INT_MASK_OFFS)
#define CRX_VC0_LN1_INT_MASK(ch)	(CRX_BASE(ch) + CAMIF_CRX0_VC0_LN1_INT_MASK_OFFS)
/* CSIDF */
#define CDF_BASE(ch)			(0x400 * (ch))
#define CDF_ENABLE(ch)			(CDF_BASE(ch) + CAMIF_CDF0_ENABLE_OFFS)
#define CDF_SKIP_FRAME(ch)		(CDF_BASE(ch) + CAMIF_CDF0_SKIP_FRAME_OFFS)
#define CDF_SELECT_INPUT_PORT(ch)	(CDF_BASE(ch) + CAMIF_CDF0_SELECT_INPUT_PORT_OFFS)
#define CDF_CNTRL_INPUT_HEIGHT(ch)	(CDF_BASE(ch) + CAMIF_CDF0_CNTRL_INPUT_HEIGHT_OFFS)
#define CDF_CNTRL_INPUT_WIDTH(ch)	(CDF_BASE(ch) + CAMIF_CDF0_CNTRL_INPUT_WIDTH_OFFS)
#define CDF_CNTRL_CONVERSION(ch)	(CDF_BASE(ch) + CAMIF_CDF0_CNTRL_CONVERSION_OFFS)
#define CDF_CNTRL_MEMORY_OUTPUT(ch)	(CDF_BASE(ch) + CAMIF_CDF0_CNTRL_MEMORY_OUTPUT_OFFS)
#define CDF_INT_STAT(ch)		(CDF_BASE(ch) + CAMIF_CDF0_INT_STAT_OFFS)
#define CDF_INT_MASK(ch)		(CDF_BASE(ch) + CAMIF_CDF0_INT_MASK_OFFS)
#define CDF_INT_HSYNCN_LINENUM(ch)	(CDF_BASE(ch) + CAMIF_CDF0_INT_HSYNCN_LINENUM_OFFS)
/* other */
#define CDPHY_LANE_CONFIG	CAMIF_CDPHY_LANE_CONFIG_OFFS
#define INT_SRC_SUB_MOD		CAMIF_CAMIF_INT_SRC_SUB_MOD_OFFS

/* interrupt registers bit */
#define MOD_INT_LPRXSTATE(ch)	(1 << (19 + ((ch) * 4)))
#define MOD_INT_RXERR(ch)	(1 << (18 + ((ch) * 4)))
#define MOD_INT_SHTPK(ch)	(1 << (17 + ((ch) * 4)))
#define MOD_INT_LNGPK(ch)	(1 << (16 + ((ch) * 4)))
#define MOD_INT_CDF(ch)		(1 << (8 + (ch)))
#define MOD_INT_DMAC		(1 << 0)

#define CDF_INT_VSYNC		(1 << 11)
#define CDF_INT_HSYNC		(1 << 10)
#define CDF_INT_FEND		(1 << 9)
#define CDF_INT_CONVE		(1 << 8)
#define CDF_INT_MEMOUTE		(1 << 7)
#define CDF_INT_YDATAE		(1 << 6)
#define CDF_INT_UDATAE		(1 << 5)
#define CDF_INT_VDATAE		(1 << 4)
#define CDF_INT_IFORMATE	(1 << 3)
#define CDF_INT_IHEIGHTE	(1 << 2)
#define CDF_INT_IWIDTHE		(1 << 1)
#define CDF_INT_FENDE		(1 << 0)
#define CDF_INT_ERR	(CDF_INT_CONVE | CDF_INT_MEMOUTE | CDF_INT_YDATAE | \
		CDF_INT_UDATAE | CDF_INT_VDATAE | CDF_INT_IFORMATE | \
		CDF_INT_IHEIGHTE | CDF_INT_IWIDTHE | CDF_INT_FENDE)

#define DMA_INT_ABORT(ch)	(1 << (16 + (ch)))
#define DMA_INT_END(ch)		(1 << (0 + (ch)))

#ifdef SELF_CLK
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/cpu_memmap_def.h>
#endif

#define CAMIF_MIN_FRAME	2

enum boudrate {
	BPS_80_110M = 0,
	BPS_110_140M,
	BPS_140_170M,
	BPS_170_200M,
	BPS_200_250M,
	BPS_250_300M,
	BPS_300_400M,
	BPS_400_500M,
	BPS_500_600M,
	BPS_600_700M,
	BPS_700_800M,
	BPS_NR,
};

/* per video frame buffer */
struct applite_cam_buffer {
	struct vb2_buffer vb; /* v4l buffer must be first */
	struct list_head queue;
};

struct applite_cam_dev {
	struct soc_camera_host soc_host;
	struct soc_camera_device *icd;

	void __iomem *base;
	void __iomem *pmu_base;
	unsigned int irq;
	unsigned int rxch;
	unsigned int cdfch;
	unsigned int dmach;
	unsigned int dmach_port;
	unsigned int num_lane;
	unsigned int sram_base;
	unsigned int sram_size;
	size_t buf_total;
	int mbps;
	bool csirx_unused;
	int lane_config;

	spinlock_t lock;		/* Protects video buffer lists */
	struct list_head capture;
	struct vb2_buffer *active;
	struct vb2_buffer *dma_active;
	struct vb2_buffer *last_active;
	struct vb2_alloc_ctx *alloc_ctx;
	unsigned int buf_cnt;
	int stream_state;

	enum v4l2_field field;
	int sequence;

	u32 abort_done;
	wait_queue_head_t wq_abort;

	struct clk *common_clk;
	struct clk *csirx_clk;
};


static DEFINE_SPINLOCK(camif_lock);
static int applite_cam_runtime_suspend(struct device *dev);
static int applite_cam_runtime_resume(struct device *dev);

#ifdef SELF_CLK
static int camif_usecount;
#endif


static struct applite_cam_buffer *to_applite_vb(struct vb2_buffer *vb)
{
	return container_of(vb, struct applite_cam_buffer, vb);
}

static inline void camif_write(struct applite_cam_dev *priv,
				u32 offset, u32 data)
{
	__raw_writel(data, priv->base + offset);
}

static inline u32 camif_read(struct applite_cam_dev *priv, u32 offset)
{
	return __raw_readl(priv->base + offset);
}

static int camif_get_bps(struct applite_cam_dev *priv)
{
	int mbps = priv->mbps;
	int ret;

	if (mbps < 110)
		ret = BPS_80_110M;
	else if (mbps < 140)
		ret = BPS_110_140M;
	else if (mbps < 170)
		ret = BPS_140_170M;
	else if (mbps < 200)
		ret = BPS_170_200M;
	else if (mbps < 250)
		ret = BPS_200_250M;
	else if (mbps < 300)
		ret = BPS_250_300M;
	else if (mbps < 400)
		ret = BPS_300_400M;
	else if (mbps < 500)
		ret = BPS_400_500M;
	else if (mbps < 600)
		ret = BPS_500_600M;
	else if (mbps < 700)
		ret = BPS_600_700M;
	else
		ret = BPS_700_800M;

	return ret;
}

#ifdef APPLITE_DEBUG
static void camif_regdump(struct applite_cam_dev *priv)
{
	int i, j;
	u32 base;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	base = 0;
	printk(KERN_INFO "CVDMAC common\n");
	for (i = 0; i < 0x40; i += 0x10) {
		printk(KERN_INFO "%8x: %8x %8x %8x %8x\n", base + i,
				camif_read(priv, base + i),
				camif_read(priv, base + i + 4),
				camif_read(priv, base + i + 8),
				camif_read(priv, base + i + 0xc));
	}
	printk(KERN_INFO "%8x: %8x\n", CAM_W_ENABLE_BUF,
			camif_read(priv, CAM_W_ENABLE_BUF));
	printk(KERN_INFO "%8x: %8x\n", CAM_INT,
			camif_read(priv, CAM_INT));
	printk(KERN_INFO "%8x: %8x\n", CAM_W_SRAM,
			camif_read(priv, CAM_W_SRAM));
	printk(KERN_INFO "%8x: %8x\n", CAM_W_STOP,
			camif_read(priv, CAM_W_STOP));
	printk(KERN_INFO "%8x: %8x\n", CAM_W_RUN,
			camif_read(priv, CAM_W_RUN));
	for (j = 0; j < 3; j++) {
		printk(KERN_INFO "CVDMAC port %d\n", j);
		base = CAM_W_STADR(priv->dmach, j);
		for (i = 0; i < 0x30; i += 0x10) {
			printk(KERN_INFO "%8x: %8x %8x %8x %8x\n", base + i,
					camif_read(priv, base + i),
					camif_read(priv, base + i + 4),
					camif_read(priv, base + i + 8),
					camif_read(priv, base + i + 0xc));
		}
		printk(KERN_INFO "CVDMAC port %d buf\n", j);
		base = CAM_W_STADR_BUF(priv->dmach, j);
		for (i = 0; i < 0x20; i += 0x10) {
			printk(KERN_INFO "%8x: %8x %8x %8x %8x\n", base + i,
					camif_read(priv, base + i),
					camif_read(priv, base + i + 4),
					camif_read(priv, base + i + 8),
					camif_read(priv, base + i + 0xc));
		}
	}

	if (priv->csirx_unused)
		goto skip;

	base = CRX_CDSIRX_CLKEN(priv->rxch) & ~0xf;
	printk(KERN_INFO "CSIRX\n");
	for (i = 0; i < 0x1c0; i += 0x10) {
		printk(KERN_INFO "%8x: %8x %8x %8x %8x\n", base + i,
				camif_read(priv, base + i),
				camif_read(priv, base + i + 4),
				camif_read(priv, base + i + 8),
				camif_read(priv, base + i + 0xc));
	}

	base = CDF_ENABLE(priv->cdfch);
	printk(KERN_INFO "CSIDF\n");
	for (i = 0; i < 0x130; i += 0x10) {
		printk(KERN_INFO "%8x: %8x %8x %8x %8x\n", base + i,
				camif_read(priv, base + i),
				camif_read(priv, base + i + 4),
				camif_read(priv, base + i + 8),
				camif_read(priv, base + i + 0xc));
	}

skip:
	printk(KERN_INFO "CDPHY_LANE_CONFIG: %8x\n",
			camif_read(priv, CDPHY_LANE_CONFIG));
	printk(KERN_INFO "INT_SRC_SUB_MOD: %8x\n",
			camif_read(priv, INT_SRC_SUB_MOD));

	spin_unlock_irqrestore(&priv->lock, flags);
}

static int read_proc_regdump(char *page, char **start,
		off_t offset, int count, int *eof, void *data)
{
	struct applite_cam_dev *priv = data;

	camif_regdump(priv);

	return 0;
}
#else
static void camif_regdump(struct applite_cam_dev *priv) {}
#endif

static int applite_camif_set_format(struct applite_cam_dev *priv,
					struct soc_camera_device *icd)
{
	u32 pixfmt = icd->current_fmt->host_fmt->fourcc;
	u32 i, val, format, swap, sep;
	u32 sram_base = priv->sram_base;
	u32 sram_size[3] = {0, 0, 0};

	switch (pixfmt) {
	case V4L2_PIX_FMT_YU24:
		format = 3;
		swap = 0;
		sep = 3;
		sram_size[0] = sram_size[1] = sram_size[2] = priv->sram_size / 3;
		break;
	case V4L2_PIX_FMT_YUYV:
		format = 0;
		swap = 1;
		sep = 0;
		sram_size[0] = priv->sram_size;
		break;
	case V4L2_PIX_FMT_YVU420:
	case V4L2_PIX_FMT_YUV420:
		format = 2;
		swap = 0;
		sep = 3;
		sram_size[0] = (priv->sram_size * 2) / 3;
		sram_size[1] = sram_size[2] = priv->sram_size / 6;
		break;
	case V4L2_PIX_FMT_NV12:
		format = 2;
		swap = 0;
		sep = 2;
		sram_size[0] = (priv->sram_size * 2) / 3;
		sram_size[1] = priv->sram_size / 3;
		break;
	default:
		/* V4L2_PIX_FMT_UYVY */
		format = 0;
		swap = 0;
		sep = 0;
		sram_size[0] = priv->sram_size;
		break;
	}

	camif_write(priv, CDF_CNTRL_CONVERSION(priv->cdfch), format);
	val = (0<<16) | (swap<<8) | (sep<<0);
	camif_write(priv, CDF_CNTRL_MEMORY_OUTPUT(priv->cdfch), val);

	camif_write(priv, CDF_CNTRL_INPUT_WIDTH(priv->cdfch), icd->user_width);
	camif_write(priv, CDF_CNTRL_INPUT_HEIGHT(priv->cdfch), icd->user_height);

	for (i = 0; i < 3; i++) {
		camif_write(priv, CAM_W_SRAM_BASE(priv->dmach, i), sram_base);
		camif_write(priv, CAM_W_SRAM_SIZE(priv->dmach, i), sram_size[i]);
		sram_base += sram_size[i];
	}

	return 0;
}

static int applite_camif_set_dma(struct applite_cam_dev *priv,
					struct soc_camera_device *icd)
{
	u32 pixfmt = icd->current_fmt->host_fmt->fourcc;
	u32 i, sep;
	u32 start[3], end[3], height[3], pitch[3];
	u32 phys_addr_top;
	u32 pix_num = icd->user_width * icd->user_height;

	phys_addr_top = (u32)vb2_dma_contig_plane_dma_addr(priv->active, 0);

	switch (pixfmt) {
	case V4L2_PIX_FMT_YU24:
		sep = 3;
		start[0] = phys_addr_top;
		start[1] = start[0] + pix_num;
		start[2] = start[1] + pix_num;
		pitch[0] = pitch[1] = pitch[2] = icd->user_width;
		height[0] = height[1] = height[2] = icd->user_height;
		end[0] = start[0] + pitch[0] - 1;
		end[1] = start[1] + pitch[1] - 1;
		end[2] = start[2] + pitch[2] - 1;
		priv->dmach_port = 0x7;
		break;
	case V4L2_PIX_FMT_YVU420:
		sep = 3;
		start[0] = phys_addr_top;
		start[2] = start[0] + pix_num;
		start[1] = start[2] + pix_num / 4;
		pitch[0] = icd->user_width;
		pitch[1] = pitch[2] = icd->user_width / 2;
		height[0] = icd->user_height;
		height[1] = height[2] = icd->user_height / 2;
		end[0] = start[0] + pitch[0] - 1;
		end[1] = start[1] + pitch[1] - 1;
		end[2] = start[2] + pitch[2] - 1;
		priv->dmach_port = 0x7;
		break;
	case V4L2_PIX_FMT_YUV420:
		sep = 3;
		start[0] = phys_addr_top;
		start[1] = start[0] + pix_num;
		start[2] = start[1] + pix_num / 4;
		pitch[0] = icd->user_width;
		pitch[1] = pitch[2] = icd->user_width / 2;
		height[0] = icd->user_height;
		height[1] = height[2] = icd->user_height / 2;
		end[0] = start[0] + pitch[0] - 1;
		end[1] = start[1] + pitch[1] - 1;
		end[2] = start[2] + pitch[2] - 1;
		priv->dmach_port = 0x7;
		break;
	case V4L2_PIX_FMT_NV12:
		sep = 2;
		start[0] = phys_addr_top;
		start[1] = start[0] + pix_num;
		pitch[0] = pitch[1] = icd->user_width;
		height[0] = icd->user_height;
		height[1] = icd->user_height / 2;
		end[0] = start[0] + pitch[0] - 1;
		end[1] = start[1] + pitch[1] - 1;
		priv->dmach_port = 0x3;
		break;
	default:
		/* V4L2_PIX_FMT_YUYV */
		/* V4L2_PIX_FMT_UYVY */
		sep = 1;
		start[0] = phys_addr_top;
		pitch[0] = icd->user_width * 2;
		height[0] = icd->user_height;
		end[0] = start[0] + pitch[0] - 1;
		priv->dmach_port = 0x1;
		break;
	}

	for (i = 0; i < sep; i++) {
		camif_write(priv, CAM_W_STADR(priv->dmach, i), start[i]);
		camif_write(priv, CAM_W_ENDAD(priv->dmach, i), end[i]);
		camif_write(priv, CAM_W_HEIGH(priv->dmach, i), height[i]);
		camif_write(priv, CAM_W_PITCH(priv->dmach, i), pitch[i]);
	}

	return 0;
}

static int applite_camif_capture_start(struct applite_cam_dev *priv)
{
	u32 val;
	unsigned long flags;

	spin_lock_irqsave(&camif_lock, flags);

	/* Claer DMA interrupt */
	val = DMA_INT_END(priv->dmach) | DMA_INT_ABORT(priv->dmach);
	camif_write(priv, CAM_INT, val);

	/* start DMA */
	val = camif_read(priv, CAM_W_ENABLE);
	val |= priv->dmach_port << (priv->dmach * 3);
	camif_write(priv, CAM_W_ENABLE, val);

	spin_unlock_irqrestore(&camif_lock, flags);

	/* Claer CSIDF interrupt */
	camif_write(priv, CDF_INT_STAT(priv->cdfch), 0xffffffff);

	/* Unmask CSIDF vsync/error interrupt */
	val = camif_read(priv, CDF_INT_MASK(priv->cdfch));
	val &= ~(CDF_INT_VSYNC);
	camif_write(priv, CDF_INT_MASK(priv->cdfch), val);

	/* Start CSIDF */
	camif_write(priv, CDF_ENABLE(priv->cdfch), 1);

	return 0;
}

static int applite_camif_capture_stop(struct applite_cam_dev *priv)
{
	u32 val;
	unsigned long flags;

	/* Stop CSIDF */
	camif_write(priv, CDF_ENABLE(priv->cdfch), 0);

	/* Clear DMA abort int */
	camif_write(priv, CAM_INT, DMA_INT_ABORT(priv->dmach));

	/* Check CVDMAC state */
	if (!(camif_read(priv, CAM_W_RUN) & (0x7 << (priv->dmach * 3)))) {
		dev_dbg(priv->icd->parent, "skip CVDMAC abort\n");
		goto skip_cvdmac_abort;
	}

	/* Unmask DMA abort int */
	spin_lock_irqsave(&camif_lock, flags);
	val = camif_read(priv, CAM_INT_MASK);
	val &= ~DMA_INT_ABORT(priv->dmach);
	camif_write(priv, CAM_INT_MASK, val);
	spin_unlock_irqrestore(&camif_lock, flags);

	/* Abort DMA */
	priv->abort_done = 0;
	camif_write(priv, CAM_CTRL, 1 << priv->dmach);

	/* Wait for DMA abort int */
	wait_event_interruptible_timeout(priv->wq_abort,
			priv->abort_done == 1, msecs_to_jiffies(50));
	if (!priv->abort_done) {
		dev_err(priv->icd->parent, "no abort int\n");
		camif_regdump(priv);
	}

	camif_write(priv, CAM_W_STOP, 7 << (priv->dmach * 3));

skip_cvdmac_abort:
	spin_lock_irqsave(&camif_lock, flags);
	/* Mask abort int */
	val = camif_read(priv, CAM_INT_MASK);
	val |= DMA_INT_ABORT(priv->dmach);
	camif_write(priv, CAM_INT_MASK, val);
	/* stop DMA */
	val = camif_read(priv, CAM_W_ENABLE);
	val &= ~(0x7 << (priv->dmach * 3));
	camif_write(priv, CAM_W_ENABLE, val);
	spin_unlock_irqrestore(&camif_lock, flags);

	return 0;
}

static irqreturn_t applite_camif_intr(int irq, void *data)
{
	struct applite_cam_dev *priv = data;
	struct device *dev = priv->icd->parent;
	struct vb2_buffer *vb;
	struct applite_cam_buffer *buf;
	u32 mod_sts, rxerr_sts = 0, cdf_sts, dma_sts;

	mod_sts = camif_read(priv, INT_SRC_SUB_MOD);
	cdf_sts = camif_read(priv, CDF_INT_STAT(priv->cdfch));
	dma_sts = camif_read(priv, CAM_INT);
	if (!priv->csirx_unused) {
		rxerr_sts = camif_read(priv, CRX_RXERR_INT_STAT(priv->rxch));
		if (rxerr_sts) {
			camif_write(priv, CRX_RXERR_INT_STAT(priv->rxch), rxerr_sts);
			if (rxerr_sts & ~0x02000003)
				dev_err(dev, "rxerr = 0x%x\n", rxerr_sts);
		}
		dev_dbg(dev, "INTR: mod=0x%x rxerr= 0x%x cdf=0x%x dma=0x%x\n",
				mod_sts, rxerr_sts, cdf_sts, dma_sts);
	} else {
		dev_dbg(dev, "INTR: mod=0x%x cdf=0x%x dma=0x%x\n",
				mod_sts, cdf_sts, dma_sts);
	}

	if (!(mod_sts & (MOD_INT_CDF(priv->cdfch) | MOD_INT_DMAC)))
		return IRQ_NONE;

	dma_sts &= DMA_INT_END(priv->dmach) | DMA_INT_ABORT(priv->dmach);

	/* clear interrupt */
	camif_write(priv, CDF_INT_STAT(priv->cdfch), cdf_sts);
	camif_write(priv, CAM_INT, dma_sts);

	spin_lock(&priv->lock);

	/* Check dma status */
	if (dma_sts) {
		vb = priv->dma_active;
		if (dma_sts & DMA_INT_ABORT(priv->dmach)) {
			priv->abort_done = 1;
			wake_up(&priv->wq_abort);
			if (vb) {
				priv->buf_cnt--;
				dev_dbg(dev, "DMA abort.\n");
				vb2_buffer_done(vb, VB2_BUF_STATE_ERROR);
				priv->dma_active = NULL;
				goto next;
			}
		}
		if (!vb)
			goto next;

		if (dma_sts & DMA_INT_END(priv->dmach)) {
			priv->buf_cnt--;
			dev_dbg(dev, "%s: index=%d cnt=%d\n", __func__,
				vb->v4l2_buf.index, priv->buf_cnt);
			do_gettimeofday(&vb->v4l2_buf.timestamp);
			vb->v4l2_buf.field = priv->field;
			vb->v4l2_buf.sequence = priv->sequence++;
			vb2_buffer_done(vb, VB2_BUF_STATE_DONE);
			priv->dma_active = NULL;
		}
	}

next:
	/* Check csidf status */
	if (cdf_sts & CDF_INT_ERR)
		dev_err(dev, "CSIDF error 0x%x\n", cdf_sts);

	if (cdf_sts & CDF_INT_VSYNC) {
		vb = priv->active;
		if (!vb)
			goto out;

		if (priv->last_active) {
			priv->dma_active = priv->last_active;
			priv->last_active = NULL;
		} else if (!priv->dma_active) {
			priv->dma_active = vb;
			buf = to_applite_vb(vb);
			list_del_init(&buf->queue);
		}

		if (!list_empty(&priv->capture)) {
			priv->active = &list_entry(priv->capture.next,
					struct applite_cam_buffer, queue)->vb;
			applite_camif_set_dma(priv, priv->icd);
		} else {
			dev_warn(dev, "*** Queue none. ***\n");
			priv->last_active = priv->dma_active;
			priv->dma_active = NULL;
			priv->active = NULL;
		}
	}

out:
	spin_unlock(&priv->lock);

	return IRQ_HANDLED;
}

static int applite_camif_init(struct applite_cam_dev *priv)
{
	struct device *dev = priv->icd->parent;
	u32 val, i;
	unsigned long flags;
	int ret;

#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_get_sync(dev);
#else
	applite_cam_runtime_resume(dev);
#endif

	camif_write(priv, CDPHY_LANE_CONFIG, priv->lane_config);

	if (priv->csirx_unused)
		goto skip_csirx;

	/* Enable CSIRX clock */
	camif_write(priv, CRX_CDSIRX_CLKEN(priv->rxch), 1);

	/* Enable RX_ERR & LPRX STATE block*/
	camif_write(priv, CRX_FUNC_ENABLE(priv->rxch), (1<<10) | (1<<8));

	/* All mask of CSIRX interrupt */
	camif_write(priv, CRX_LPRX_STATE_INT_MASK(priv->rxch), 0xffffffff);
	camif_write(priv, CRX_RXERR_INT_MASK(priv->rxch), 0xffffffff);
	camif_write(priv, CRX_VC0_SH_INT_MASK(priv->rxch), 0xffffffff);
	camif_write(priv, CRX_VC0_LN0_INT_MASK(priv->rxch), 0xffffffff);
	camif_write(priv, CRX_VC0_LN1_INT_MASK(priv->rxch), 0xffffffff);

	/* LPRX auto Calibration start */
	camif_write(priv, CRX_LPRX_STATE_INT_STAT(priv->rxch), 0xffffffff);
	camif_write(priv, CRX_PPI_DPHY_DLYCNTRL(priv->rxch), 0x00044220);
	camif_write(priv, CRX_PPI_DPHY_LPRXCALCNTRL(priv->rxch), 100 << 16);
	camif_write(priv, CRX_PPI_DPHY_LPRX_THSLD(priv->rxch), 0x2aa);
	camif_write(priv, CRX_PPI_DPHY_LPRXAUTOCALST(priv->rxch), 1);

skip_csirx:
	/* Initialize Common CVDMAC */
	camif_write(priv, CAM_STADR, PHYS_OFFSET);
	camif_write(priv, CAM_ENDADR, 0xffffffff);
	camif_write(priv, CAM_DMRADR, PHYS_OFFSET);
	camif_write(priv, CAM_CFG, 0x0007070f);

	/* Disable DMA port */
	spin_lock_irqsave(&camif_lock, flags);
	val = camif_read(priv, CAM_W_ENABLE);
	val &= ~(0x7 << (priv->dmach * 3));
	camif_write(priv, CAM_W_ENABLE, val);
	spin_unlock_irqrestore(&camif_lock, flags);

	/* Initialize DMA port */
	for (i = 0; i < 3; i++) {
		val = (2<<8) | (0<<16) | (0<<24);
		camif_write(priv, CAM_W_CFG0(priv->dmach, i), val);
		val = (0<<0) | (1<<16);
		camif_write(priv, CAM_W_CFG1(priv->dmach, i), val);
		camif_write(priv, CAM_W_INTL(priv->dmach, i), 0);
	}

	if (priv->csirx_unused) {
		camif_write(priv, CDF_SELECT_INPUT_PORT(priv->cdfch), 1);
		goto skip_csirx2;
	}

	/* Wait LPRX Auto Calibration done (100msec) */
	for (i = 0; i < 1000; i++) {
		val = camif_read(priv, CRX_LPRX_STATE_INT_STAT(priv->rxch));
		if (val & (1 << 4))
			break;
		usleep_range(100, 200);
	}
	if (!(val & (1 << 4)))
		dev_err(dev, "Auto calibration timeout. %x\n", val);

	/* Clear LPRX state */
	camif_write(priv, CRX_LPRX_STATE_INT_STAT(priv->rxch), 0xffffffff);

skip_csirx2:
	/* All mask of interrupt */
	camif_write(priv, CDF_INT_MASK(priv->cdfch), 0xffffffff);
	spin_lock_irqsave(&camif_lock, flags);
	val = camif_read(priv, CAM_INT_MASK);
	val |= DMA_INT_ABORT(priv->dmach) | DMA_INT_END(priv->dmach);
	camif_write(priv, CAM_INT_MASK, val);
	spin_unlock_irqrestore(&camif_lock, flags);

	ret = request_irq(priv->irq, applite_camif_intr,
			IRQF_SHARED, dev_name(dev), priv);
	if (ret) {
		dev_err(dev, "Unable to register interrupt.\n");
		return ret;
	}

	return 0;
}

static void applite_camif_deinit(struct applite_cam_dev *priv)
{
	u32 val;
	unsigned long flags;
	struct device *dev = priv->icd->parent;

	if (priv->csirx_unused)
		goto next;

	/* Clear CSIRX internal status */
	camif_write(priv, CRX_CDSIRX_SYSTEM_INIT(priv->rxch), 1);

	/* Disable CSIRX clock */
	camif_write(priv, CRX_CDSIRX_CLKEN(priv->rxch), 0);

	/* All mask of interrupt */
	camif_write(priv, CRX_FUNC_ENABLE(priv->rxch), 0);
	camif_write(priv, CDF_INT_MASK(priv->cdfch), 0xffffffff);

next:
	/* Disable DMA port */
	spin_lock_irqsave(&camif_lock, flags);
	val = camif_read(priv, CAM_INT_MASK);
	val |= DMA_INT_ABORT(priv->dmach) | DMA_INT_END(priv->dmach);
	camif_write(priv, CAM_INT_MASK, val);
	val = camif_read(priv, CAM_W_ENABLE);
	val &= ~(0x7 << (priv->dmach * 3));
	camif_write(priv, CAM_W_ENABLE, val);
	spin_unlock_irqrestore(&camif_lock, flags);

#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_put_sync(dev);
#else
	applite_cam_runtime_suspend(dev);
#endif

	free_irq(priv->irq, priv);
}

static void applite_camif_csirx_start(struct applite_cam_dev *priv, int bps)
{
	u32 val, i;
	u32 bps_val[BPS_NR] = {1, 2, 3, 4, 1, 2, 3, 4, 5, 6, 7};

	/* Initialize csirx0, phy */
	if (bps <= BPS_170_200M)
		val = 0x101;
	else
		val = 0x001;
	camif_write(priv, CRX_CDSIRX_CLKSEL(priv->rxch), val);
	camif_write(priv, CRX_MODE_CONFIG(priv->rxch), 0x1);
	camif_write(priv, CRX_LANE_ENABLE(priv->rxch), 0x10 | priv->num_lane);
	camif_write(priv, CRX_VC_ENABLE(priv->rxch), 0x1);
	camif_write(priv, CRX_LINE_INIT_COUNT(priv->rxch), 21000);
	camif_write(priv, CRX_HSRXTO_COUNT(priv->rxch), 100000);
	camif_write(priv, CRX_PPI_HSRX_CNTRL(priv->rxch), 0x41000000);
	val = 0x20000000 | bps_val[bps];
	camif_write(priv, CRX_PPI_HSRX_COUNT(priv->rxch), val);

	dev_dbg(priv->icd->parent, "%s: bps_val:%d\n", __func__,  bps_val[bps]);

	/* Start CSIRX */
	camif_write(priv, CRX_CDSIRX_START(priv->rxch), 1);

	/* Wait Line init done (100msec) */
	for (i = 0; i < 1000; i++) {
		val = camif_read(priv, CRX_LPRX_STATE_INT_STAT(priv->rxch));
		if (val & (1 << 0))
			break;
		usleep_range(100, 200);
	}
	if (!(val & (1 << 0)))
		dev_err(priv->icd->parent, "Line init timeout. %x\n", val);

	camif_write(priv, CRX_LPRX_STATE_INT_STAT(priv->rxch), 1 << 0);
}

static void applite_camif_csirx_stop(struct applite_cam_dev *priv,
					u32 msec_per_frame)
{
	u32 val, i, busy = 0;
	u32 stat_mask[4] = {0x003fffff, 0x00ffffff, 0x03ffffff, 0x0fffffff};

	/* Wait CSIRX stop (time of 2 frame) */
	for (i = 0; i < msec_per_frame * 2; i++) {
		busy = 0;
		val = camif_read(priv, CRX_LANE_STATUS_HS(priv->rxch));
		if (val)
			busy = 1;
		val = camif_read(priv, CRX_LANE_STATUS_LP(priv->rxch));
		if (!(val & (1 << 0)) || !(val & (1 << 7)))
			busy = 1;
		val = camif_read(priv, CRX_CDSIRX_INTERNAL_STAT(priv->rxch));
		if (val & stat_mask[priv->num_lane-1])
			busy = 1;

		if (!busy)
			break;
		usleep_range(1000, 1000);
	}
	if (busy) {
		dev_err(priv->icd->parent, "CSIRX stop error.\n");
		camif_regdump(priv);
	}

	/* Stop CSIRX */
	camif_write(priv, CRX_CDSIRX_START(priv->rxch), 0);
}

/*
 * Videobuf operations
 */
static int applite_videobuf_setup(struct vb2_queue *vq,
			const struct v4l2_format *fmt,
			unsigned int *count, unsigned int *num_planes,
			unsigned int sizes[], void *alloc_ctxs[])
{
	struct soc_camera_device *icd = soc_camera_from_vb2q(vq);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct applite_cam_dev *priv = ici->priv;
	int bytes_per_line;
	unsigned int height;

	if (fmt) {
		const struct soc_camera_format_xlate *xlate =
			soc_camera_xlate_by_fourcc(icd, fmt->fmt.pix.pixelformat);
		if (!xlate)
			return -EINVAL;
		bytes_per_line = soc_mbus_bytes_per_line(fmt->fmt.pix.width,
							 xlate->host_fmt);
		height = fmt->fmt.pix.height;
	} else {
		/* Called from VIDIOC_REQBUFS or in compatibility mode */
		bytes_per_line = soc_mbus_bytes_per_line(icd->user_width,
						icd->current_fmt->host_fmt);
		height = icd->user_height;
	}
	if (bytes_per_line < 0)
		return bytes_per_line;

	sizes[0] = bytes_per_line * height;

	alloc_ctxs[0] = priv->alloc_ctx;

	if (!vq->num_buffers)
		priv->sequence = 0;

	if (*count < CAMIF_MIN_FRAME)
		*count = CAMIF_MIN_FRAME;

	*num_planes = 1;

	priv->buf_cnt = 0;

	dev_dbg(icd->parent, "%s: count=%d, size=%u w=%d h=%d\n",
		__func__, *count, sizes[0], icd->user_width, icd->user_height);

	return 0;
}

static int applite_videobuf_init(struct vb2_buffer *vb)
{
	struct soc_camera_device *icd = soc_camera_from_vb2q(vb->vb2_queue);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct applite_cam_dev *priv = ici->priv;
	struct applite_cam_buffer *buf = to_applite_vb(vb);

	/* This is for locking debugging only */
	INIT_LIST_HEAD(&buf->queue);

	priv->buf_total += vb2_plane_size(vb, 0);
	dev_dbg(icd->parent, "%s: %zu bytes buffers\n",
			__func__, priv->buf_total);

	return 0;
}

static int applite_videobuf_prepare(struct vb2_buffer *vb)
{
	struct applite_cam_buffer *buf = to_applite_vb(vb);

	/* Added list head initialization on alloc */
	WARN(!list_empty(&buf->queue), "Buffer %p on queue!\n", vb);

	return 0;
}

static void applite_videobuf_queue(struct vb2_buffer *vb)
{
	struct soc_camera_device *icd = soc_camera_from_vb2q(vb->vb2_queue);
	struct device *dev = icd->parent;
	struct soc_camera_host *ici = to_soc_camera_host(dev);
	struct applite_cam_dev *priv = ici->priv;
	struct applite_cam_buffer *buf = to_applite_vb(vb);
	const struct soc_mbus_pixelfmt *host_fmt = icd->current_fmt->host_fmt;
	int bytes_per_line = soc_mbus_bytes_per_line(icd->user_width, host_fmt);
	size_t new_size;
	unsigned long flags;

	dev_dbg(dev, "%s: bpl=%d h=%d index=%d\n",
		__func__, bytes_per_line, icd->user_height, vb->v4l2_buf.index);

	if (bytes_per_line < 0) {
		dev_err(dev, "bytes_per_line too small. %d\n", bytes_per_line);
		goto error;
	}

	new_size = bytes_per_line * icd->user_height;

	if (vb2_plane_size(vb, 0) < new_size) {
		dev_err(dev, "Buffer #%d too small (%lu < %zu)\n",
			vb->v4l2_buf.index, vb2_plane_size(vb, 0), new_size);
		goto error;
	}

	vb2_set_plane_payload(vb, 0, new_size);

#ifdef APPLITE_DEBUG
	/* helps to see what DMA actually has written */
	if (vb2_plane_vaddr(vb, 0))
		memset(vb2_plane_vaddr(vb, 0),
				0xaa, vb2_get_plane_payload(vb, 0));
#endif

	spin_lock_irqsave(&priv->lock, flags);
	list_add_tail(&buf->queue, &priv->capture);
	priv->buf_cnt++;

	if (!priv->active) {
		priv->active = vb;
		applite_camif_set_dma(priv, icd);
		if (priv->stream_state == 1) {
			priv->stream_state = 2;
			applite_camif_capture_start(priv);
		}
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(dev, "%s: (vb=0x%p) 0x%p 0x%p %lu cnt=%d\n", __func__,
			vb, vb2_plane_vaddr(vb, 0),
			(void *)vb2_dma_contig_plane_dma_addr(vb, 0),
			vb2_get_plane_payload(vb, 0),
			priv->buf_cnt);

	return;

error:
	vb2_buffer_done(vb, VB2_BUF_STATE_ERROR);
}

static void applite_videobuf_release(struct vb2_buffer *vb)
{
	struct soc_camera_device *icd = soc_camera_from_vb2q(vb->vb2_queue);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct applite_cam_dev *priv = ici->priv;
	struct applite_cam_buffer *buf = to_applite_vb(vb);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	if (priv->active == vb)
		priv->active = NULL;

	if (buf->queue.next)
		list_del_init(&buf->queue);

	priv->buf_total -= vb2_plane_size(vb, 0);
	dev_dbg(icd->parent, "%s: %zu bytes buffers\n",
			__func__, priv->buf_total);

	spin_unlock_irqrestore(&priv->lock, flags);
}

static int applite_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct soc_camera_device *icd = soc_camera_from_vb2q(q);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct applite_cam_dev *priv = ici->priv;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);

	if (!priv->csirx_unused)
		applite_camif_csirx_start(priv, camif_get_bps(priv));

	v4l2_subdev_call(sd, video, s_stream, 1);

	priv->stream_state = 1;
	if (priv->buf_cnt) {
		priv->stream_state = 2;
		applite_camif_capture_start(priv);
	}

	return 0;
}

static int applite_stop_streaming(struct vb2_queue *q)
{
	struct soc_camera_device *icd = soc_camera_from_vb2q(q);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct applite_cam_dev *priv = ici->priv;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct applite_cam_buffer *buf, *tmp;
	struct v4l2_streamparm parm;
	struct v4l2_fract *tpf;
	unsigned long flags;
	u32 msec_per_frame;
	int ret;

	applite_camif_capture_stop(priv);
	priv->stream_state = 0;

	v4l2_subdev_call(sd, video, s_stream, 0);

	spin_lock_irqsave(&priv->lock, flags);

	priv->active = NULL;
	if (priv->dma_active) {
		priv->buf_cnt--;
		vb2_buffer_done(priv->dma_active, VB2_BUF_STATE_ERROR);
		priv->dma_active = NULL;
	}
	if (priv->last_active) {
		priv->buf_cnt--;
		vb2_buffer_done(priv->last_active, VB2_BUF_STATE_ERROR);
		priv->last_active = NULL;
	}

	list_for_each_entry_safe(buf, tmp, &priv->capture, queue) {
		list_del_init(&buf->queue);
		priv->buf_cnt--;
		vb2_buffer_done(&buf->vb, VB2_BUF_STATE_ERROR);
	}

	spin_unlock_irqrestore(&priv->lock, flags);

	if (priv->csirx_unused)
		return 0;

	parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = v4l2_subdev_call(sd, video, g_parm, &parm);
	if (!ret && parm.parm.capture.capability == V4L2_CAP_TIMEPERFRAME) {
		tpf = &parm.parm.capture.timeperframe;
		msec_per_frame = (tpf->numerator * 1000) / tpf->denominator;
	} else {
		msec_per_frame = 100;
	}

	applite_camif_csirx_stop(priv, msec_per_frame);

	return 0;
}

static struct vb2_ops applite_videobuf_ops = {
	.queue_setup		= applite_videobuf_setup,
	.buf_init		= applite_videobuf_init,
	.buf_prepare		= applite_videobuf_prepare,
	.buf_queue		= applite_videobuf_queue,
	.buf_cleanup		= applite_videobuf_release,
	.wait_prepare		= soc_camera_unlock,
	.wait_finish		= soc_camera_lock,
	.start_streaming	= applite_start_streaming,
	.stop_streaming		= applite_stop_streaming,
};

static int applite_cam_init_videobuf(struct vb2_queue *q,
					struct soc_camera_device *icd)
{
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->drv_priv = icd;
	q->ops = &applite_videobuf_ops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_struct_size = sizeof(struct applite_cam_buffer);

	return vb2_queue_init(q);
}

/* Called with .video_lock held */
static int applite_cam_add_device(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct applite_cam_dev *priv = ici->priv;

	if (priv->icd)
		return -EBUSY;

	dev_dbg(icd->parent, "AppLite Camera driver attached to camera %d\n",
		 icd->devnum);

	priv->buf_total = 0;
	priv->icd = icd;

	applite_camif_init(priv);

	return 0;
}

/* Called with .video_lock held */
static void applite_cam_remove_device(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct applite_cam_dev *priv = ici->priv;

	BUG_ON(icd != priv->icd);

	applite_camif_deinit(priv);

	/* make sure active buffer is canceled */
	spin_lock_irq(&priv->lock);
	if (priv->active) {
		list_del_init(&to_applite_vb(priv->active)->queue);
		priv->buf_cnt--;
		vb2_buffer_done(priv->active, VB2_BUF_STATE_ERROR);
		priv->active = NULL;
	}
	spin_unlock_irq(&priv->lock);


	priv->icd = NULL;

	dev_dbg(icd->parent, "AppLite Camera driver detached from camera %d\n",
		 icd->devnum);
}

static const struct soc_mbus_pixelfmt applite_cam_formats[] = {
	{
		.fourcc			= V4L2_PIX_FMT_YUYV,
		.name			= "YUYV",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_2X8_PADHI,
		.order			= SOC_MBUS_ORDER_LE,
	}, {
		.fourcc			= V4L2_PIX_FMT_YVU420,
		.name			= "YV12",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_1_5X8,
		.order			= SOC_MBUS_ORDER_LE,
	}, {
		.fourcc			= V4L2_PIX_FMT_YUV420,
		.name			= "YU12",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_1_5X8,
		.order			= SOC_MBUS_ORDER_LE,
	}, {
		.fourcc			= V4L2_PIX_FMT_NV12,
		.name			= "NV12",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_1_5X8,
		.order			= SOC_MBUS_ORDER_LE,
	}, {
		.fourcc			= V4L2_PIX_FMT_YU24,
		.name			= "YU24",
		.bits_per_sample	= 8,
		.packing		= SOC_MBUS_PACKING_3X8,
		.order			= SOC_MBUS_ORDER_LE,
	},
};

#define APPLITE_BUS_FLAGS (V4L2_MBUS_CSI2_CONTINUOUS_CLOCK | \
		V4L2_MBUS_CSI2_LANES | V4L2_MBUS_CSI2_CHANNELS)

static int applite_cam_try_bus_param(struct soc_camera_device *icd,
				    const unsigned int depth)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct v4l2_mbus_config cfg = {.type = V4L2_MBUS_PARALLEL,};
	unsigned long common_flags = APPLITE_BUS_FLAGS;
	int ret;

	ret = v4l2_subdev_call(sd, video, g_mbus_config, &cfg);
	if (!ret)
		common_flags = soc_mbus_config_compatible(&cfg,
							  common_flags);
	else if (ret != -ENOIOCTLCMD)
		return ret;

	return 0;
}

/* This will be corrected as we get more formats */
static bool applite_cam_packing_supported(const struct soc_mbus_pixelfmt *fmt)
{
	return	fmt->packing == SOC_MBUS_PACKING_NONE ||
		(fmt->bits_per_sample == 8 &&
		 fmt->packing == SOC_MBUS_PACKING_1_5X8) ||
		(fmt->bits_per_sample == 8 &&
		 fmt->packing == SOC_MBUS_PACKING_2X8_PADHI) ||
		(fmt->bits_per_sample == 8 &&
		 fmt->packing == SOC_MBUS_PACKING_3X8);
}

static int applite_cam_get_formats(struct soc_camera_device *icd,
		unsigned int idx, struct soc_camera_format_xlate *xlate)
{
	struct device *dev = icd->parent;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	int ret, k, n;
	int formats = 0;
	enum v4l2_mbus_pixelcode code;
	const struct soc_mbus_pixelfmt *fmt;

	ret = v4l2_subdev_call(sd, video, enum_mbus_fmt, idx, &code);
	if (ret < 0)
		/* No more formats */
		return 0;

	fmt = soc_mbus_get_fmtdesc(code);
	if (!fmt) {
		dev_warn(dev, "Unsupported format code #%u: %d\n", idx, code);
		return 0;
	}

	/* This also checks support for the requested bits-per-sample */
	ret = applite_cam_try_bus_param(icd, fmt->bits_per_sample);
	if (ret < 0)
		return 0;

	switch (code) {
	case V4L2_MBUS_FMT_UYVY8_2X8:
		n = ARRAY_SIZE(applite_cam_formats);
		formats += n;
		for (k = 0; xlate && k < n; k++) {
			xlate->host_fmt	= &applite_cam_formats[k];
			xlate->code	= code;
			xlate++;
			dev_dbg(dev, "Providing format %s using code %d\n",
				applite_cam_formats[k].name, code);
		}
		break;
	default:
		if (!applite_cam_packing_supported(fmt))
			return 0;
	}

	/* Generic pass-through */
	formats++;
	if (xlate) {
		xlate->host_fmt	= fmt;
		xlate->code	= code;
		dev_dbg(dev, "Providing format %c%c%c%c in pass-through mode\n",
			(fmt->fourcc >> (0*8)) & 0xFF,
			(fmt->fourcc >> (1*8)) & 0xFF,
			(fmt->fourcc >> (2*8)) & 0xFF,
			(fmt->fourcc >> (3*8)) & 0xFF);
		xlate++;
	}

	return formats;
}

static int applite_cam_set_fmt(struct soc_camera_device *icd,
				struct v4l2_format *f)
{
	struct device *dev = icd->parent;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct soc_camera_host *ici = to_soc_camera_host(dev);
	struct applite_cam_dev *priv = ici->priv;
	const struct soc_camera_format_xlate *xlate;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_mbus_framefmt mf;
	__u32 pixfmt = pix->pixelformat;
	int ret;

	xlate = soc_camera_xlate_by_fourcc(icd, pixfmt);
	if (!xlate) {
		dev_warn(dev, "Format %x not found\n", pixfmt);
		return -EINVAL;
	}

	mf.width	= pix->width;
	mf.height	= pix->height;
	mf.field	= pix->field;
	mf.colorspace	= pix->colorspace;
	mf.code		= xlate->code;

	ret = v4l2_subdev_call(sd, video, s_mbus_fmt, &mf);
	if (ret < 0)
		return ret;

	pix->width		= mf.width;
	pix->height		= mf.height;
	pix->field		= mf.field;
	priv->field		= mf.field;
	pix->colorspace		= mf.colorspace;
	icd->current_fmt	= xlate;

	dev_dbg(dev, "S_FMT(pix=0x%x, fld 0x%x, code 0x%x, %ux%u)\n",
			pixfmt, mf.field, mf.code, pix->width, pix->height);

	return 0;
}

static int applite_cam_try_fmt(struct soc_camera_device *icd,
			      struct v4l2_format *f)
{
	struct device *dev = icd->parent;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	const struct soc_camera_format_xlate *xlate;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_mbus_framefmt mf;
	__u32 pixfmt = pix->pixelformat;
	int ret;

	xlate = soc_camera_xlate_by_fourcc(icd, pixfmt);
	if (pixfmt && !xlate) {
		dev_err(icd->parent, "Format %x not found\n", pixfmt);
		return -EINVAL;
	}

	dev_dbg(dev, "USER_FMT(pix=0x%x, %ux%u)\n",
			pixfmt, pix->width, pix->height);

	/* limit to sensor capabilities */
	mf.width	= pix->width;
	mf.height	= pix->height;
	mf.field	= pix->field;
	mf.colorspace	= pix->colorspace;
	mf.code		= xlate->code;

	ret = v4l2_subdev_call(sd, video, try_mbus_fmt, &mf);
	if (ret < 0)
		return ret;

	pix->width	= mf.width;
	pix->height	= mf.height;
	pix->colorspace	= mf.colorspace;

	switch (mf.field) {
	case V4L2_FIELD_ANY:
		pix->field = V4L2_FIELD_NONE;
		break;
	case V4L2_FIELD_NONE:
		break;
	default:
		dev_err(dev, "Field type %d unsupported.\n",
			mf.field);
		ret = -EINVAL;
	}

	dev_dbg(dev, "%s: return %d, fmt 0x%x, %ux%u\n",
		__func__, ret, pix->pixelformat, pix->width, pix->height);

	return ret;
}

static unsigned int applite_cam_poll(struct file *file, poll_table *pt)
{
	struct soc_camera_device *icd = file->private_data;
	return vb2_poll(&icd->vb2_vidq, file, pt);
}

static int applite_cam_querycap(struct soc_camera_host *ici,
					struct v4l2_capability *cap)
{
	/* cap->name is set by the friendly caller:-> */
	strlcpy(cap->card, "AppLite Camera", sizeof(cap->card));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
	return 0;
}

static int applite_cam_set_bus_param(struct soc_camera_device *icd)
{
	struct device *dev = icd->parent;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct soc_camera_host *ici = to_soc_camera_host(dev);
	struct applite_cam_dev *priv = ici->priv;
	struct v4l2_mbus_config cfg = {.type = V4L2_MBUS_CSI2,};
	u32 pixfmt = icd->current_fmt->host_fmt->fourcc;
	unsigned long common_flags = APPLITE_BUS_FLAGS;
	int ret;

	ret = v4l2_subdev_call(sd, video, g_mbus_config, &cfg);
	if (!ret) {
		common_flags = soc_mbus_config_compatible(&cfg,
							  common_flags);
		if (!common_flags) {
			dev_err(dev,
				 "Flags incompatible: camera 0x%x, host 0x%lx\n",
				 cfg.flags, common_flags);
			return -EINVAL;
		}
	} else if (ret != -ENOIOCTLCMD) {
		return ret;
	}

	dev_dbg(dev, "Flags cam: 0x%x common: 0x%lx\n",
				cfg.flags, common_flags);

	/* CIS2 clock rate */
	priv->mbps = V4L2_MBUS_CSI2_GET_MBPS(cfg.flags);

	cfg.flags = common_flags;
	ret = v4l2_subdev_call(sd, video, s_mbus_config, &cfg);
	if (ret < 0 && ret != -ENOIOCTLCMD) {
		dev_dbg(dev, "camera s_mbus_config(0x%lx) returned %d\n",
				common_flags, ret);
		return ret;
	}

	/* Number of Data Lane */
	priv->num_lane = fls(cfg.flags & V4L2_MBUS_CSI2_LANES);

	applite_camif_set_format(priv, icd);

	dev_dbg(dev, "%s: pixfmt=%x w=%d h=%d bps=%dMbps num_lane=%d\n",
			__func__, pixfmt, icd->user_width, icd->user_height,
			priv->mbps, priv->num_lane);

	return 0;
}

static int applite_cam_get_parm(struct soc_camera_device *icd,
				struct v4l2_streamparm *parm)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct v4l2_captureparm *cp;
	int ret;

	ret = v4l2_subdev_call(sd, video, g_parm, parm);
	if (ret) {
		cp = &parm->parm.capture;
		cp->capability = 0;
	}
	return 0;
}

static int applite_cam_set_parm(struct soc_camera_device *icd,
				struct v4l2_streamparm *parm)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct device *dev = icd->parent;
	struct soc_camera_host *ici = to_soc_camera_host(dev);
	struct applite_cam_dev *priv = ici->priv;
	struct v4l2_mbus_config cfg = {.type = V4L2_MBUS_CSI2,};
	unsigned long common_flags = APPLITE_BUS_FLAGS;
	int ret;

	ret = v4l2_subdev_call(sd, video, s_parm, parm);
	if (ret) {
		dev_dbg(dev, "set param error %d\n", ret);
		return ret;
	}

	ret = v4l2_subdev_call(sd, video, g_mbus_config, &cfg);
	if (!ret) {
		common_flags = soc_mbus_config_compatible(&cfg,
							  common_flags);
		if (!common_flags) {
			dev_err(dev,
				 "Flags incompatible: camera 0x%x, host 0x%lx\n",
				 cfg.flags, common_flags);
			return -EINVAL;
		}
	}
	/* CIS2 clock rate */
	priv->mbps = V4L2_MBUS_CSI2_GET_MBPS(cfg.flags);

	dev_dbg(dev, "%s: bps=%dMbps\n", __func__, priv->mbps);

	return 0;
}

static struct soc_camera_host_ops applite_cam_host_ops = {
	.owner		= THIS_MODULE,
	.add		= applite_cam_add_device,
	.remove		= applite_cam_remove_device,
	.set_fmt	= applite_cam_set_fmt,
	.try_fmt	= applite_cam_try_fmt,
	.get_formats	= applite_cam_get_formats,
	.init_videobuf2	= applite_cam_init_videobuf,
	.poll		= applite_cam_poll,
	.querycap	= applite_cam_querycap,
	.set_bus_param	= applite_cam_set_bus_param,
	.get_parm	= applite_cam_get_parm,
	.set_parm	= applite_cam_set_parm,
};

static int __devinit applite_cam_probe(struct platform_device *pdev)
{
	struct applite_cam_dev *priv;
	struct soc_camera_host *soc_host;
	struct applite_camera_platform_data *pdata;
	struct resource *res, *pmu_res;
	unsigned int irq;
	int ret = 0;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "camif");
	irq = platform_get_irq(pdev, 0);
	if (!res || (int)irq <= 0) {
		dev_err(&pdev->dev, "Not enough CAMIF platform resources.\n");
		ret = -ENODEV;
		goto egetres;
	}

	priv = vzalloc(sizeof(*priv));
	if (!priv) {
		dev_err(&pdev->dev, "Could not allocate priv\n");
		ret = -ENOMEM;
		goto ealloc;
	}

	priv->base = ioremap(res->start, resource_size(res));
	if (!priv->base) {
		dev_err(&pdev->dev, "Unable to ioremap registers.\n");
		ret = -ENOMEM;
		goto eioremap;
	}

	pmu_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pmu");
	if (pmu_res == NULL) {
		dev_err(&pdev->dev, "Not enough CAMIF platform resources(PMU).\n");
		ret = -ENODEV;
		goto eioremap2;
	}
	priv->pmu_base = ioremap(pmu_res->start, resource_size(pmu_res));
	if (!priv->pmu_base) {
		dev_err(&pdev->dev, "Unable to ioremap registers(PMU).\n");
		ret = -ENOMEM;
		goto eioremap2;
	}

	priv->common_clk = clk_get(&(pdev->dev), "camif_common");
	if (IS_ERR(priv->common_clk)) {
		dev_err(&pdev->dev, "Unable to get clock(common_clk).\n");
		ret = -EFAULT;
		goto eclkget;
	}

	priv->csirx_clk = clk_get(&(pdev->dev), "camif_csirx");
	if (IS_ERR(priv->csirx_clk)) {
		dev_err(&pdev->dev, "Unable to get clock(csirx_clk).\n");
		ret = -EFAULT;
		goto eclkget2;
	}

	dev_dbg(&pdev->dev, "base=0x%p map=0x%p irq=%d\n",
			(void *)res->start, priv->base, irq);

	priv->irq = irq;
	pdata = pdev->dev.platform_data;
	if (pdata) {
		priv->csirx_unused = pdata->csirx_unused;
		switch (pdata->lane_config) {
		case LANE_CONFIG_2LANEx2:
			priv->lane_config = 2;
			break;
		case LANE_CONFIG_4LANEx1:
			priv->lane_config = 0;
			break;
		default: /* LANE_CONFIG_1LANEx4 */
			priv->lane_config = 7;
			break;
		}
	} else {
		priv->lane_config = 7;
	}
	priv->rxch = pdev->id;
	priv->dmach = priv->cdfch = pdev->id;
	priv->sram_size = 1440 / 4;
	priv->sram_base = priv->sram_size * priv->dmach;

	/* list of video-buffers */
	INIT_LIST_HEAD(&priv->capture);
	spin_lock_init(&priv->lock);
	init_waitqueue_head(&priv->wq_abort);

	soc_host		= &priv->soc_host;
	soc_host->v4l2_dev.dev	= &pdev->dev;
	soc_host->drv_name	= dev_name(&pdev->dev);
	soc_host->nr		= pdev->id;
	soc_host->ops		= &applite_cam_host_ops;
	soc_host->priv		= priv;

	priv->alloc_ctx = vb2_dma_contig_init_ctx(&pdev->dev);
	if (IS_ERR(priv->alloc_ctx)) {
		dev_err(&pdev->dev, "vb2_dma_contig_init_ctx err\n");
		ret = PTR_ERR(priv->alloc_ctx);
		goto eallocctx;
	}

	pm_runtime_enable(&(pdev->dev));

	ret = soc_camera_host_register(soc_host);
	if (ret) {
		dev_err(&pdev->dev, "soc_camera_host_register err\n");
		goto ecamhostreg;
	}

#ifdef APPLITE_DEBUG
	{
		struct proc_dir_entry *proc;
		proc = create_proc_read_entry(dev_name(&pdev->dev), 0644,
				NULL, read_proc_regdump, priv);

	}
#endif
	return 0;

ecamhostreg:
	vb2_dma_contig_cleanup_ctx(priv->alloc_ctx);
eallocctx:
	clk_put(priv->csirx_clk);
eclkget2:
	clk_put(priv->common_clk);
eclkget:
	iounmap(priv->pmu_base);
eioremap2:
	iounmap(priv->base);
eioremap:
	vfree(priv);
ealloc:
egetres:
	return ret;
}

static int __devexit applite_cam_remove(struct platform_device *pdev)
{
	struct soc_camera_host *soc_host = to_soc_camera_host(&pdev->dev);
	struct applite_cam_dev *priv = container_of(soc_host,
					struct applite_cam_dev, soc_host);

	dev_dbg(&pdev->dev, "%s:removed.\n", __func__);

#ifdef APPLITE_DEBUG
	remove_proc_entry(dev_name(&pdev->dev), NULL);
#endif

	soc_camera_host_unregister(soc_host);

	dev_dbg(&pdev->dev, "%s:runtime disable.\n", __func__);
	pm_runtime_disable(&(pdev->dev));

	clk_put(priv->common_clk);
	clk_put(priv->csirx_clk);
	iounmap(priv->base);
	iounmap(priv->pmu_base);
	vb2_dma_contig_cleanup_ctx(priv->alloc_ctx);
	vfree(priv);

	return 0;
}

static int applite_cam_suspend(struct device *dev)
{
	/* check for idle */
	dev_dbg(dev, "%s : start usecount=%d\n", __func__,
			camif_usecount);
	if (camif_usecount > 0)
		return -EBUSY;

	return 0;
}

static int applite_cam_resume(struct device *dev)
{
	dev_dbg(dev, "%s start\n", __func__);
	return 0;
}

static int applite_cam_runtime_suspend(struct device *dev)
{
	unsigned long flags;
	struct soc_camera_host *soc_host = to_soc_camera_host(dev);
	struct applite_cam_dev *priv = container_of(soc_host,
					struct applite_cam_dev, soc_host);

	dev_dbg(dev, "%s start\n", __func__);

	spin_lock_irqsave(&camif_lock, flags);
	/* Reset CSIRXx module */
	__raw_writel((1<<priv->cdfch),
			priv->pmu_base + PMU_SoftResetOn_camifSS_0_OFFS);
	/* Disable CSIRXx clock */
	clk_disable_unprepare(priv->csirx_clk);
	dev_dbg(dev, "ClockGatingOn(csirx):0x%x\n",
		__raw_readl(priv->pmu_base + PMU_ClockGatingOn_camifSS_0_OFFS)&0xF);
	if (!(--camif_usecount)) {
		/* Reset DPHY/CCBUS/CVDMAC module */
		__raw_writel((7<<8), (priv->pmu_base +
				PMU_SoftResetOn_camifSS_0_OFFS));
		/* Disable DPHY/CCBUS/CVDMAC clock */
		clk_disable_unprepare(priv->common_clk);
		dev_dbg(dev, "ClockGatingOn(common):%d\n",
			(__raw_readl(priv->pmu_base + PMU_ClockGatingOn_camifSS_0_OFFS)>>8)&0x1);
	}
	spin_unlock_irqrestore(&camif_lock, flags);

	return 0;
}

static int applite_cam_runtime_resume(struct device *dev)
{
	unsigned long flags;
	struct soc_camera_host *soc_host = to_soc_camera_host(dev);
	struct applite_cam_dev *priv = container_of(soc_host,
					struct applite_cam_dev, soc_host);

	dev_dbg(dev, "%s start\n", __func__);

	spin_lock_irqsave(&camif_lock, flags);
	if (camif_usecount++ == 0) {
		/* Enable DPHY/CCBUS/CVDMAC clock */
		clk_prepare_enable(priv->common_clk);
		dev_dbg(dev, "ClockGatingOff(common):%d\n",
			(__raw_readl(priv->pmu_base + PMU_ClockGatingOff_camifSS_0_OFFS)>>8)&0x1);
		/* Unreset DPHY/CCBUS/CVDMAC module */
		__raw_writel((7<<8), (priv->pmu_base +
				PMU_SoftResetOff_camifSS_0_OFFS));
	}
	/* Enable CSIRXx clock */
	clk_prepare_enable(priv->csirx_clk);
	dev_dbg(dev, "ClockGatingOff(csirx):0x%x\n",
		__raw_readl(priv->pmu_base + PMU_ClockGatingOff_camifSS_0_OFFS)&0xF);
	/* Unreset CSIRXx module */
	__raw_writel((1<<priv->cdfch),
			priv->pmu_base + PMU_SoftResetOff_camifSS_0_OFFS);
	spin_unlock_irqrestore(&camif_lock, flags);

	return 0;
}


static const struct dev_pm_ops applite_cam_pm_ops = {
	.suspend = applite_cam_suspend,
	.resume = applite_cam_resume,
	.runtime_suspend = applite_cam_runtime_suspend,
	.runtime_resume = applite_cam_runtime_resume,
};

static struct platform_driver applite_cam_driver = {
	.driver		= {
		.name	= "applite_cam",
		.owner = THIS_MODULE,
		.pm = &applite_cam_pm_ops,
	},
	.probe		= applite_cam_probe,
	.remove		= __devexit_p(applite_cam_remove),
};

module_platform_driver(applite_cam_driver);

MODULE_DESCRIPTION("App Lite SoC Camera Host driver");
MODULE_LICENSE("GPL v2");
