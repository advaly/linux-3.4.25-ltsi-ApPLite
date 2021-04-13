/*
 * linux/driver/video/applite/applitefb_tz2000gfx.c
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

#include <linux/module.h>
#include <linux/version.h>

#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/ioctl.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/fb.h>

#if defined(CONFIG_PM_RUNTIME)
#include <linux/pm_runtime.h>
#endif /* defined(CONFIG_PM_RUNTIME) */
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/uaccess.h>

#include <linux/applite/tz2000_gfx.h>
#include "applitefb.h"
#include "tz2000gfx_internal.h"
#include "tz2000_regs.h"


/******************************************************************************/

#ifndef TZ2000_IRQ
#define TZ2000_GASINT_IRQ	177
#define TZ2000_GAMPINT_IRQ	178
#endif


#define TZ2000_GFX_REG_BASE		CPU_GFX_REG_BASE
#define TZ2000_GFX_REG_SIZE		CPU_GFX_REG_SIZE
#define TZ2000_PMU_REG_BASE		CPU_PMU_REG_BASE
#define TZ2000_PMU_REG_SIZE		CPU_PMU_REG_SIZE

#define TZ2000_PMU_CGON_GFX_OFFS	PMU_CLOCKGATINGON_GFXSS_0_OFS
#define TZ2000_PMU_CGOFF_GFX_OFFS	PMU_CLOCKGATINGOFF_GFXSS_0_OFS
#define TZ2000_PMU_SRON_GFX_OFFS	PMU_SOFTRESETON_GFXSS_0_OFS
#define TZ2000_PMU_SROFF_GFX_OFFS	PMU_SOFTRESETOFF_GFXSS_0_OFS


/******************************************************************************/

#if defined(__DBG_TZ2000GFX__)
#define QPRINT(fmt, ...)						\
	     pr_info("- %-17s: " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define QPRINT(x...)		do {} while (0)
#endif

#if defined(__TEST_TZ2000GFX__)
#define TEST_PRINT(fmt, ...)						\
	     pr_info("[%-20s]: " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define TEST_PRINT(x...)	do {} while (0)
#endif


#define QDUMP(msg)	QPRINT("%-12s (%srunning)", msg,		\
				shared->hw_running ? "" : "not ");



/******************************************************************************/


/******************************************************************************/


static DECLARE_WAIT_QUEUE_HEAD(wait_idle);

static struct tz2000gfx_drv	tz2000_drv;
static struct tz2000gfx_share	*shared;


static union {
	struct applite_gfx_line		line[TZ2000GFX_BATCH_NUM];
	struct applite_gfx_blit_prm	blit_prm[TZ2000GFX_BATCH_NUM];
	struct applite_gfx_triangle	tri[TZ2000GFX_BATCH_NUM];
} batch_buffer;


static irqreturn_t
tz2000gfx_gamp_irq(int irq, void *ctx);
static int
tz2000gfx_reset(struct tz2000gfx_share *shared);
/******************************************************************************/

#if !defined(_MERGE_FBDEV_)
static void
tz2000gfx_hw_init(struct tz2000gfx_share *shared)
{
	TEST_PRINT("start\n");
	QPRINT("Setting PMU...");

	/* reset assert */
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_SRON_GFX_OFFS, 0x00000001);
	/* clock gating off */
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_CGOFF_GFX_OFFS, 0x00000001);
	/* reset deassert */
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_SROFF_GFX_OFFS, 0x00000001);

	TEST_PRINT("success\n");
}

static int
tz2000gfx_hw_exit(struct tz2000gfx_share *shared)
{
	__u32 val;

	TEST_PRINT("start\n");

	val = tz2000_read(&tz2000_drv, GFX_REG(GASR));
	if ((val & GASR_BUSY_RUNNING) == GASR_BUSY_RUNNING)
		return -EBUSY;
	/* reset assert */
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_SRON_GFX_OFFS, 0x00000001);
	/* clock gating off */
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_CGON_GFX_OFFS, 0x00000001);

	TEST_PRINT("success\n");
	return 0;
}

#endif
void tz2000gfx_resume(void)
{
	TEST_PRINT("start\n");

	/* clock gating off */
#if defined(_MERGE_FBDEV_)
	clk_prepare_enable(priv.clk_gfx);
#else
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_CGOFF_GFX_OFFS, 0x00000001);
#endif
	/* reset deassert */
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_SROFF_GFX_OFFS, 0x00000001);

	/* gfx reset */
	tz2000gfx_reset(shared);

	TEST_PRINT("success\n");
}

int tz2000gfx_suspend(void)
{
	__u32 val;

	TEST_PRINT("start\n");

	val = tz2000_read(&tz2000_drv, GFX_REG(GASR));
	if ((val & GASR_BUSY_RUNNING) == GASR_BUSY_RUNNING) {
		pr_err("%s: GFX GASR BUSY.(0x%x)\n", __func__, val);
		return -EBUSY;
	}

	/* reset assert */
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_SRON_GFX_OFFS, 0x00000001);
	/* clock gating on */
#if defined(_MERGE_FBDEV_)
	clk_disable_unprepare(priv.clk_gfx);
#else
	tz2000_pmu_write(&tz2000_drv, TZ2000_PMU_CGON_GFX_OFFS, 0x00000001);
#endif

	TEST_PRINT("success\n");
	return 0;
}

static int
tz2000gfx_reset(struct tz2000gfx_share *shared)
{
	TEST_PRINT("start\n");
	QPRINT("Resetting hardware...");

	/* disable interrupt */
	tz2000_write(&tz2000_drv, GFX_REG(GAIMR), 0);
	tz2000_write(&tz2000_drv, GFX_REG(GASCR), GASCR_GARESET_ON);

	QPRINT("Initializing cmd buffer area...");
	memset((void *)shared, 0, sizeof(struct tz2000gfx_share));

	QPRINT("Clearing interrupts...");
	/* clear interrupt */
	tz2000_write(&tz2000_drv, GFX_REG(GAICR), TZ2000_ALL_INTERRUPT);
	/* enable interrupt */
	tz2000_write(&tz2000_drv, GFX_REG(GAIMR), TZ2000_ALL_INTERRUPT);
	/* enable GA */
	tz2000_write(&tz2000_drv, GFX_REG(GASCR), GASCR_GAEN_ENABLED);

	QDUMP("Ready");

	TEST_PRINT("success\n");
	return 0;
}

static int
tz2000gfx_wait_idle(struct tz2000gfx_share *shared)
{
	int ret;

	TEST_PRINT("start\n");
	QDUMP("Waiting.....");

	/* Does not need to be atomic. There's a lock in user space,
	* but anyhow, this is just for statistics. */
	shared->num_wait_idle++;
	ret = wait_event_interruptible_timeout(wait_idle, !shared->hw_running, 100*HZ);
	if (!ret)
		pr_err("%s: TIMEOUT! (%srunning status:%08x)\n",
			__func__,
			shared->hw_running ? "" : "not ",
			tz2000_read(&tz2000_drv, GFX_REG(GASR)));

	QDUMP("........done");

	TEST_PRINT("end(%d)\n", ret);
	return (ret > 0) ? 0 : (ret < 0) ? ret : -ETIMEDOUT;
}


static int
tz2000gfx_emit_cmd(struct tz2000gfx_share *shared)
{
	__u32	phys;

	TEST_PRINT("start\n");
	QDUMP("start hardware...");
	if (tz2000gfx_wait_idle(shared) != 0) {
		TEST_PRINT("end\n");
		return -ETIMEDOUT;
	}

	/* add END to command list */
	tz2000_cmdlist_push(shared, C_CSEND);
	phys = tz2000_drv.shared_phys +
		(TZ2000GFX_BUFFER_WORDS * shared->buf_idx * sizeof(__u64));
	shared->hw_running = 1;
	/* change work buffer */
	tz2000_cmdlist_swap(shared);

	tz2000_write(&tz2000_drv, GFX_REG(GACLAR), phys);
	TEST_PRINT("success\n");
	return 0;
}

static int
tz2000gfx_draw_line(struct tz2000gfx_share *shared,
			struct applite_gfx_drawline *dl)
{
	int i;
	__u64 cmd;

	TEST_PRINT("start\n");
	QDUMP("add draw line command...");
	if (tz2000_cmdlist_get_free_size(shared) < (8 + (3 * dl->num))) {
		QDUMP("command buffer full.....");
		i = tz2000gfx_emit_cmd(shared);
		if (i != 0) {
			TEST_PRINT("end(%d)\n", i);
			return i;
		}
	}
	/* add command list */
	QPRINT("dst(%08x(%08x) - %d x %d) num:%d", dl->dst_addr,
		virt_to_phys((void *)(dl->dst_addr)), dl->dst_width,
		dl->dst_height, dl->num);

	/* clipping window */
	if (dl->clip == CLIP_OPT_ENABLE) {
		QPRINT("clip(%d, %d) - (%d, %d)",
			dl->clip_start.x, dl->clip_start.y,
			dl->clip_end.x, dl->clip_end.y);
		cmd = C_LGPR(DE_CLIP_START_REG,
			DE_CLIP_START_VAL(dl->clip_start.x, dl->clip_start.y));
		tz2000_cmdlist_push(shared, cmd);
		cmd = C_LGPR(DE_CLIP_END_REG,
			DE_CLIP_END_VAL(dl->clip_end.x, dl->clip_end.y));
		tz2000_cmdlist_push(shared, cmd);
	}

	/* destination address & size */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(DE_DST_ADR_REG, virt_to_phys((void *)(dl->dst_addr)));
#else
	cmd = C_LGPR(DE_DST_ADR_REG, dl->dst_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);
	cmd = C_LGPR(DE_MEM_DIM_REG,
			DE_MEM_DIM_VAL(dl->dst_width, dl->dst_height));
	tz2000_cmdlist_push(shared, cmd);

	/* line thickness */
	cmd = C_LGPR(DE_LINE_THICK_REG, THICK_TO_U32(dl->thick));
	tz2000_cmdlist_push(shared, cmd);

	QPRINT("color(%08x/%08x)", dl->color, dl->bg_color);

	/* draw color RGBA or RGB */
	cmd = C_LGPR(DE_COLOR_REG, dl->color);
	tz2000_cmdlist_push(shared, cmd);

	/* draw background color RGBA or RGB */
	cmd = C_LGPR(DE_BK_COLOR_REG, dl->bg_color);
	tz2000_cmdlist_push(shared, cmd);

	/* draw start */
	for (i = 0; i < dl->num; i++) {
		QPRINT("line(%d, %d) - (%d, %d)",
			dl->line[i].sp.x, dl->line[i].sp.y,
			dl->line[i].ep.x, dl->line[i].ep.y);
		/* start position */
		cmd = C_LGPR(DE_LINE_START_REG, POS_TO_U32(dl->line[i].sp));
		tz2000_cmdlist_push(shared, cmd);

		/* end position */
		cmd = C_LGPR(DE_LINE_END_REG, POS_TO_U32(dl->line[i].ep));
		tz2000_cmdlist_push(shared, cmd);

		/* draw command */
		cmd = CMD_DL(CODE(dl->cmd), dl->sp_caps, dl->ep_caps, dl->blend, dl->clip);
		tz2000_cmdlist_push(shared, cmd);

	}

	TEST_PRINT("success\n");
	return 0;
}

static int
tz2000gfx_fill_triangle(struct tz2000gfx_share *shared,
			struct applite_gfx_filltriangle *dt)
{
	int i;
	__u64 cmd;

	TEST_PRINT("start\n");
	QDUMP("add fill triangle command...");
	if (tz2000_cmdlist_get_free_size(shared) < (8 + (4 * dt->num))) {
		QDUMP("command buffer full.....");
		i = tz2000gfx_emit_cmd(shared);
		if (i != 0) {
			TEST_PRINT("end(%d)\n", i);
			return i;
		}
	}
	/* add command list */
	QPRINT("dst(%08x(%08x) - %d x %d) num:%d", dt->dst_addr,
		virt_to_phys((void *)(dt->dst_addr)), dt->dst_width,
		dt->dst_height, dt->num);

	/* clipping window */
	if (dt->clip == CLIP_OPT_ENABLE) {
		QPRINT("clip(%d, %d) - (%d, %d)",
			dt->clip_start.x, dt->clip_start.y,
			dt->clip_end.x, dt->clip_end.y);
		cmd = C_LGPR(DE_CLIP_START_REG,
			DE_CLIP_START_VAL(dt->clip_start.x, dt->clip_start.y));
		tz2000_cmdlist_push(shared, cmd);
		cmd = C_LGPR(DE_CLIP_END_REG,
			DE_CLIP_END_VAL(dt->clip_end.x, dt->clip_end.y));
		tz2000_cmdlist_push(shared, cmd);
	}

	/* destination address & size */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(DE_DST_ADR_REG, virt_to_phys((void *)(dt->dst_addr)));
#else
	cmd = C_LGPR(DE_DST_ADR_REG, dt->dst_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);
	cmd = C_LGPR(DE_MEM_DIM_REG,
			DE_MEM_DIM_VAL(dt->dst_width, dt->dst_height));
	tz2000_cmdlist_push(shared, cmd);

	/* line thickness */
	cmd = C_LGPR(DE_LINE_THICK_REG, THICK_TO_U32(dt->thick));
	tz2000_cmdlist_push(shared, cmd);

	QPRINT("color(%08x/%08x)", dt->color, dt->bg_color);

	/* draw color RGBA or RGB */
	cmd = C_LGPR(DE_COLOR_REG, dt->color);
	tz2000_cmdlist_push(shared, cmd);

	/* draw background color RGBA or RGB */
	cmd = C_LGPR(DE_BK_COLOR_REG, dt->bg_color);
	tz2000_cmdlist_push(shared, cmd);

	/* draw start */
	for (i = 0; i < dt->num; i++) {
		QPRINT("line(%d, %d) - (%d, %d) -(%d, %d)",
			dt->triangle[i].pt1.x, dt->triangle[i].pt1.y,
			dt->triangle[i].pt2.x, dt->triangle[i].pt2.y,
			dt->triangle[i].pt3.x, dt->triangle[i].pt3.y);
		/* edge 1 position */
		cmd = C_LGPR(DE_TRI_PT1_REG, POS_TO_U32(dt->triangle[i].pt1));
		tz2000_cmdlist_push(shared, cmd);

		/* edge 2 position */
		cmd = C_LGPR(DE_TRI_PT2_REG, POS_TO_U32(dt->triangle[i].pt2));
		tz2000_cmdlist_push(shared, cmd);

		/* edge 3 position */
		cmd = C_LGPR(DE_TRI_PT3_REG, POS_TO_U32(dt->triangle[i].pt3));
		tz2000_cmdlist_push(shared, cmd);

		/* draw command */
		cmd = CMD_DT(CODE(dt->cmd), dt->antialiase, dt->blend, dt->clip);
		tz2000_cmdlist_push(shared, cmd);
	}

	TEST_PRINT("success\n");
	return 0;
}

static int v_split, h_split;
static __u32 dst_x, dst_y;
static struct applite_gfx_blit_prm sv_prm;
static int
tz2000gfx_blit_overlap_split(int src_bpp, int dst_bpp,
			struct applite_gfx_blit_prm *org)
{
	TEST_PRINT("start(src_bpp:%d, dst_bpp:%d)\n", src_bpp, dst_bpp);

	/* save blit parameter */
	sv_prm = *org;

	if ((src_bpp == dst_bpp) && (org->src_addr < org->dst_addr) &&
		((org->src_addr + org->src_width * src_bpp * org->img_height)
			> org->dst_addr)) {
		/* detect overlaped */
		TEST_PRINT("detect overlaped\n");
		TEST_PRINT("%08x/%08x - %dx%d -> %08x/%08x\n", org->src_addr,
				org->src_width, org->img_width, org->img_height,
				 org->dst_addr, org->dst_width);
	} else {
		v_split = 1;
		h_split = 1;
		return 1;
	}

	/* calc dst offset position (x, y) from src */
	dst_y = (org->dst_addr - org->src_addr) / (org->src_width * src_bpp);
	dst_x = (org->dst_addr - org->src_addr) - (dst_y * org->src_width * src_bpp);

	TEST_PRINT("dst(%d,%d)\n", dst_x, dst_y);
	/* */
	/* src (0, 0) - (img_width x img_height) -> dst (x, y) */
	/* */

	/* set split height */
	if (dst_y == 0)
		v_split = 1;
	else if ((org->img_height - dst_y) > dst_y)
		v_split = (org->img_height - 1) / dst_y + 1;
	else
		v_split = 2;

	/* set split width */
	if (dst_x == 0)
		h_split = 1;
	else if ((org->img_width - dst_x) > dst_x)
		v_split = (org->img_width - 1) / dst_x + 1;
	else
		h_split = 2;

	TEST_PRINT("success v_split:%d/h_split:%d\n", v_split, h_split);

	return v_split * h_split;
}

static void
tz2000gfx_blit_overlap_split_get_next(int idx, int bpp,
				struct applite_gfx_blit_prm *prm)
{
	int i, v, h;
	__u16 x_off, y_off;
	__u32 width = 0, height = 0;

	TEST_PRINT("start(idx:%d)\n", idx);

	prm->src_width  = sv_prm.src_width;
	prm->dst_width  = sv_prm.dst_width;

	if ((v_split == 1) && (h_split == 1)) {
		prm->src_addr   = sv_prm.src_addr;
		prm->dst_addr   = sv_prm.dst_addr;
		prm->img_width  = sv_prm.img_width;
		prm->img_height = sv_prm.img_height;
		return;
	}

	/* set split width */
	v = idx / h_split;
	h = idx - v * h_split;
	TEST_PRINT("hv(%d, %d)\n", h, v);

	x_off = sv_prm.img_width;
	if (h_split == 1) {
		x_off = 0;
		width = sv_prm.img_width;
	} else if (h == (h_split - 1)) {
		x_off = 0;
		width = dst_x;
	} else {
		for (i = 0; (i <= h) && (i < h_split - 1); i++) {
			if ((x_off - dst_x) > dst_x) {
				width = dst_x;
				x_off -= dst_x;
			} else {
				width = x_off - dst_x;
				x_off = dst_x;
			}
		}
	}

	y_off = sv_prm.img_height;
	if (v_split == 1) {
		y_off = 0;
		height = sv_prm.img_height;
	} else if (v == (v_split - 1)) {
		y_off = 0;
		height = dst_y;
	} else {
		for (i = 0; (i <= v) && (i < v_split - 1); i++) {
			if ((y_off - dst_y) > dst_y) {
				height = dst_y;
				y_off -= dst_y;
			} else {
				height = y_off - dst_y;
				y_off = dst_y;
			}
		}
	}

	TEST_PRINT("offset(%d, %d), size(%d, %d)\n",
					x_off, y_off, width, height);

	prm->img_width = width;
	prm->img_height = height;
	prm->src_addr = sv_prm.src_addr + y_off * sv_prm.src_width * bpp +
		x_off * bpp;
	prm->dst_addr = sv_prm.dst_addr + y_off * sv_prm.dst_width * bpp +
		x_off * bpp;
	TEST_PRINT("success\n");
}

static int
tz2000gfx_blit_core(struct tz2000gfx_share *shared, struct applite_gfx_blit *blt,
					struct applite_gfx_blit_prm *prm, int b_init)
{
	int i;
	__u64 cmd;

	TEST_PRINT("start\n");
	QDUMP("add blit command...");
	if (tz2000_cmdlist_get_free_size(shared) < (11 + 7)) {
		QDUMP("command buffer full.....");
		i = tz2000gfx_emit_cmd(shared);
		if (i != 0) {
			TEST_PRINT("end(%d)\n", i);
			return i;
		}
		b_init = 0;
	}
	if (b_init == 0) {
		/* add command list */
		/* clipping window */
		if (blt->clip == CLIP_OPT_ENABLE) {
			QPRINT("clip (%08x : (%d, %d)",
				blt->clip_addr, blt->clip_width, blt->clip_height);
#if defined(_FIXUP_ADDR_VIRT_)
			cmd = C_LGPR(BE_CLIP_START_REG, virt_to_phys((void *)(blt->clip_addr)));
#else
			cmd = C_LGPR(BE_CLIP_START_REG, blt->clip_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
			tz2000_cmdlist_push(shared, cmd);
			cmd = C_LGPR(BE_CLIP_WIDTH_REG, blt->clip_width);
			tz2000_cmdlist_push(shared, cmd);
			cmd = C_LGPR(BE_CLIP_HEIGHT_REG, blt->clip_height);
			tz2000_cmdlist_push(shared, cmd);
		}

		/* conversion configuration */
		/* source alpha value */
		cmd = C_LGPR(BE_SRC_ALPHA_REG, blt->src_alpha);
		tz2000_cmdlist_push(shared, cmd);

		/* source transparency color */
		cmd = C_LGPR(BE_SRC_TRANS_PAT_REG, blt->src_ckey);
		tz2000_cmdlist_push(shared, cmd);

		/* destination alpha value */
		cmd = C_LGPR(BE_DST_ALPHA_REG, blt->dst_alpha);
		tz2000_cmdlist_push(shared, cmd);

		/* destination transparency color */
		if (blt->transparency == TRANSCOLOR_OPT_ENABLE) {
			cmd = C_LGPR(BE_DST_TRANS_PAT_REG, blt->dst_ckey);
			tz2000_cmdlist_push(shared, cmd);
		}

		/* filling configuration */
		if (blt->format == FMT_OPT_RGBA) {
			/* RGBA Fill Preset */
			cmd = C_LGPR(BE_RGBA_FILL_PRESET_REG, blt->preset);
		} else {
			/* RGB Fill Preset */
			cmd = C_LGPR(BE_RGB_FILL_PRESET_REG, blt->preset);
		}
		tz2000_cmdlist_push(shared, cmd);

		/* fading / raster operation */
		/* fading factor */
		if (blt->fade != FADE_OPT_NO) {
			cmd = C_LGPR(BE_FADE_FACTOR_REG, blt->fade_factor);
			tz2000_cmdlist_push(shared, cmd);
		}

		/* raster operation */
		if (blt->rop_opt == ROP_OPT_ENABLE) {
			cmd = C_LGPR(BE_ROP_REG, ROP_TO_U32(blt->rop));
			tz2000_cmdlist_push(shared, cmd);
		}
	}

	/* source address */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(BE_SRC_ADR_REG, virt_to_phys((void *)(prm->src_addr)));
#else
	cmd = C_LGPR(BE_SRC_ADR_REG, prm->src_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);

	/* source memory width */
	cmd = C_LGPR(BE_SRC_MEM_WIDTH_REG, prm->src_width);
	tz2000_cmdlist_push(shared, cmd);

	/* destination memory width */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(BE_DST_ADR_REG, virt_to_phys((void *)(prm->dst_addr)));
#else
	cmd = C_LGPR(BE_DST_ADR_REG, prm->dst_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);

	/* destination memory width */
	cmd = C_LGPR(BE_DST_MEM_WIDTH_REG, prm->dst_width);
	tz2000_cmdlist_push(shared, cmd);

	/* destination dot count */
	cmd = C_LGPR(BE_DST_DOT_CNT_REG, prm->img_width);
	tz2000_cmdlist_push(shared, cmd);

	/* destination dot count */
	cmd = C_LGPR(BE_DST_LINE_CNT_REG, prm->img_height);
	tz2000_cmdlist_push(shared, cmd);

	/* draw command */
	switch (blt->cmd) {
	case CMD_BLITO16:
	case CMD_BLITORLEI16:
	case CMD_BLITORLEI24:
		cmd = C_BLITO_RGB(CODE(blt->cmd), blt->format, blt->transparency, blt->fade, blt->clip);
		break;
	case CMD_BLITO32:
	case CMD_BLITORLEI24A:
	case CMD_BLITORLEI32:
		cmd = C_BLITO_RGBA(CODE(blt->cmd), blt->format, blt->fade, blt->clip);
		break;
	case CMD_BLITOP16:
	case CMD_BLITOP32:
		cmd = C_BLITOP_RGB(CODE(blt->cmd), blt->fade, blt->clip);
		break;
	case CMD_BLITB16:
	case CMD_BLITB32:
	case CMD_BLITBRLEI16:
	case CMD_BLITBRLEI24:
	case CMD_BLITBRLEI24A:
	case CMD_BLITBRLEI32:
		cmd = C_BLITB_RGB(CODE(blt->cmd), blt->protect, blt->rop_opt, blt->format, blt->blend, blt->transparency, blt->fade, blt->clip);
		break;
	case CMD_BLITBP16:
	case CMD_BLITBP32:
		cmd = C_BLITBP_RGB(CODE(blt->cmd), blt->protect, blt->rop_opt, blt->blend, blt->fade, blt->clip);
		break;
	default:
		pr_err("%s: INVALID CMD (%02x)\n", __func__, blt->cmd);
	}
	tz2000_cmdlist_push(shared, cmd);

	TEST_PRINT("success\n");
	return 0;
}

static int
tz2000gfx_blit(struct tz2000gfx_share *shared, struct applite_gfx_blit *blt)
{
	int i, j, k, split;
	int src_bpp, dst_bpp;
	struct applite_gfx_blit_prm prm;

	TEST_PRINT("start\n");
	QDUMP("add blit command...");
	if (tz2000_cmdlist_get_free_size(shared) < (11 + (7 * blt->num))) {
		QDUMP("command buffer full.....");
		i = tz2000gfx_emit_cmd(shared);
		if (i != 0) {
			TEST_PRINT("end(%d)\n", i);
			return i;
		}
	}

	if (blt->format == FMT_OPT_RGB16)
		dst_bpp = 2;
	else
		dst_bpp = 4;

	switch (blt->cmd) {
	case CMD_BLITO16:
	case CMD_BLITORLEI16:
	case CMD_BLITOP16:
	case CMD_BLITB16:
	case CMD_BLITBRLEI16:
	case CMD_BLITBP16:
		src_bpp = 2;
		break;
	case CMD_BLITORLEI24:
	case CMD_BLITORLEI24A:
	case CMD_BLITBRLEI24:
	case CMD_BLITBRLEI24A:
		src_bpp = 3;
		break;
	case CMD_BLITO32:
	case CMD_BLITORLEI32:
	case CMD_BLITOP32:
	case CMD_BLITB32:
	case CMD_BLITBRLEI32:
	case CMD_BLITBP32:
	default:
		src_bpp = 4;
	}

	/* draw start */
	for (i = 0; i < blt->num; i++) {
		split = tz2000gfx_blit_overlap_split(src_bpp, dst_bpp,
							&(blt->blit[i]));
		QPRINT("[%d] src(%08x - %d) -> dst(%08x - %d) - %d x %d",
			i, blt->blit[i].src_addr, blt->blit[i].src_width,
			blt->blit[i].dst_addr, blt->blit[i].dst_width,
			blt->blit[i].img_width, blt->blit[i].img_height);
		for (j = 0; j < split; j++) {
			tz2000gfx_blit_overlap_split_get_next(j, src_bpp, &prm);
			TEST_PRINT("[%d] src(%08x - %d) -> dst(%08x - %d) - %d x %d",
				j, prm.src_addr, prm.src_width,
				prm.dst_addr, prm.dst_width,
				prm.img_width, prm.img_height);

			k = tz2000gfx_blit_core(shared, blt, &prm, i);
			if (k != 0)
				TEST_PRINT("end(%d)\n", i);
		}
	}

	TEST_PRINT("success\n");
	return 0;
}

static int
tz2000gfx_transform(struct tz2000gfx_share *shared,
			struct applite_gfx_transform *trans)
{
	int i;
	__u64 cmd;

	TEST_PRINT("start\n");

	QDUMP("add transform command...");
	if (tz2000_cmdlist_get_free_size(shared) < 16) {
		QDUMP("command buffer full.....");
		i = tz2000gfx_emit_cmd(shared);
		if (i != 0) {
			TEST_PRINT("end(%d)\n", i);
			return i;
		}
	}
	QPRINT("src(%08x - %d) -> lut(%08x %d x %d) -> dst(%08x - %d) - %d x %d",
			trans->src_addr, trans->src_width,
			trans->lut_addr, trans->lut_width, trans->lut_line_cnt,
			trans->dst_addr, trans->dst_width,
			trans->img_width, trans->img_line_cnt);

	/* add command list */
	/* source address */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(TE_SRC_ADR_REG, virt_to_phys((void *)(trans->src_addr)));
#else
	cmd = C_LGPR(TE_SRC_ADR_REG, trans->src_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);

	/* source memory width */
	cmd = C_LGPR(TE_SRC_MEM_WIDTH_REG, trans->src_width);
	tz2000_cmdlist_push(shared, cmd);

	/* source fading factor value */
	cmd = C_LGPR(TE_FADE_FACTOR_REG, trans->fade_factor);
	tz2000_cmdlist_push(shared, cmd);

	/* source alpha value */
	cmd = C_LGPR(TE_SRC_ALPHA_REG, trans->src_alpha);
	tz2000_cmdlist_push(shared, cmd);

	/* LUT address */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(TE_LUT_ADR_REG, virt_to_phys((void *)(trans->lut_addr)));
#else
	cmd = C_LGPR(TE_LUT_ADR_REG, trans->lut_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);

	/* LUT memory width */
	cmd = C_LGPR(TE_LUT_WIDTH_REG, trans->lut_width);
	tz2000_cmdlist_push(shared, cmd);

	/* LUT line count */
	cmd = C_LGPR(TE_LUT_LINE_CNT_REG, trans->lut_line_cnt);
	tz2000_cmdlist_push(shared, cmd);

	/* destination address */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(TE_DST_ADR_REG, virt_to_phys((void *)(trans->dst_addr)));
#else
	cmd = C_LGPR(TE_DST_ADR_REG, trans->dst_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);

	/* destination memory width */
	cmd = C_LGPR(TE_DST_MEM_WIDTH_REG, trans->dst_width);
	tz2000_cmdlist_push(shared, cmd);

	/* destination image width */
	cmd = C_LGPR(TE_DST_IMG_WIDTH_REG, trans->img_width);
	tz2000_cmdlist_push(shared, cmd);

	/* destination image line count */
	cmd = C_LGPR(TE_DST_LINE_CNT_REG, trans->img_line_cnt);
	tz2000_cmdlist_push(shared, cmd);

	/* destination alpha value */
	cmd = C_LGPR(TE_DST_ALPHA_REG, trans->dst_alpha);
	tz2000_cmdlist_push(shared, cmd);

	/* color format */
	cmd = C_LGPR(TE_COLOR_REG, TE_COLOR_VAL(trans->src_fmt, trans->dst_fmt));
	tz2000_cmdlist_push(shared, cmd);

	/* predefined color */
	cmd = C_LGPR(TE_PREDEFINED_COLOR_REG, trans->pre_color);
	tz2000_cmdlist_push(shared, cmd);

	switch (trans->cmd) {
	case CMD_TRANSB:
		cmd = C_TRANSB(trans->protect, trans->fade, trans->blend, trans->mode, trans->filter);
		break;
	case CMD_TRANSO:
		cmd = C_TRANSO(trans->mode, trans->filter);
		break;
	default:
		pr_err("%s: INVALID CMD (%02x)\n", __func__, trans->cmd);
	}
	tz2000_cmdlist_push(shared, cmd);

	TEST_PRINT("success\n");
	return 0;
}


static int
tz2000gfx_rotation(struct tz2000gfx_share *shared,
			struct applite_gfx_rotation *rot)
{
	int i;
	__u64 cmd;

	TEST_PRINT("start\n");

	QDUMP("add rotation command...");
	if (tz2000_cmdlist_get_free_size(shared) < 24) {
		QDUMP("command buffer full.....");
		i = tz2000gfx_emit_cmd(shared);
		if (i != 0) {
			TEST_PRINT("end(%d)\n", i);
			return i;
		}
	}
	/* add command list */
	/* clipping window */
	if (rot->clip == CLIP_OPT_ENABLE) {
		QPRINT("clip (%d, %d) - (%d, %d)",
			rot->clip_start.x, rot->clip_start.y,
			rot->clip_end.x, rot->clip_end.y);
		cmd = C_LGPR(RE_CLIP_START_REG,
			RE_CLIP_START_VAL(rot->clip_start.x, rot->clip_start.y));
		tz2000_cmdlist_push(shared, cmd);
		cmd = C_LGPR(RE_CLIP_END_REG,
			RE_CLIP_END_VAL(rot->clip_end.x, rot->clip_end.y));
		tz2000_cmdlist_push(shared, cmd);
	}

	QPRINT("src (%08x - (%d)", virt_to_phys((void *)(rot->src_addr)),
				rot->src_width);
	/* source address */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(RE_SRC_ADR_REG, virt_to_phys((void *)(rot->src_addr)));
#else
	cmd = C_LGPR(RE_SRC_ADR_REG, rot->src_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);

	/* source memory width */
	cmd = C_LGPR(RE_SRC_MEM_WIDTH_REG, rot->src_width);
	tz2000_cmdlist_push(shared, cmd);

	/* source fading factor */
	cmd = C_LGPR(RE_SRC_FADE_REG, rot->fade_factor);
	tz2000_cmdlist_push(shared, cmd);

	/* source alpha */
	cmd = C_LGPR(RE_SRC_ALPHA_REG, rot->src_alpha);
	tz2000_cmdlist_push(shared, cmd);

	QPRINT("dst (%08x - (%d, %d)", virt_to_phys((void *)(rot->dst_addr)),
				rot->dst_width, rot->dst_height);
	/* destination address */
#if defined(_FIXUP_ADDR_VIRT_)
	cmd = C_LGPR(RE_DST_ADR_REG, virt_to_phys((void *)(rot->dst_addr)));
#else
	cmd = C_LGPR(RE_DST_ADR_REG, rot->dst_addr);
#endif	/* _FIXUP_ADDR_VIRT_ */
	tz2000_cmdlist_push(shared, cmd);

	/* destination memory width & height */
	cmd = C_LGPR(RE_DST_DIM_REG,
		RE_DST_DIM_VAL(rot->dst_width, rot->dst_height));
	tz2000_cmdlist_push(shared, cmd);

	/* destination alpha value */
	cmd = C_LGPR(RE_DST_ALPHA_REG, rot->dst_alpha);
	tz2000_cmdlist_push(shared, cmd);

	/* color */
	cmd = C_LGPR(RE_COLOR_REG, RE_COLOR_VAL(rot->dst_fmt, rot->src_fmt));
	tz2000_cmdlist_push(shared, cmd);

	/* rotation SX */
	cmd = C_LGPR(RE_ROT_SX_REG, rot->sx);
	tz2000_cmdlist_push(shared, cmd);

	/* rotation SHX */
	cmd = C_LGPR(RE_ROT_SHX_REG, rot->shx);
	tz2000_cmdlist_push(shared, cmd);

	/* rotation SHY */
	cmd = C_LGPR(RE_ROT_SHY_REG, rot->shy);
	tz2000_cmdlist_push(shared, cmd);

	/* rotation SY */
	cmd = C_LGPR(RE_ROT_SY_REG, rot->sy);
	tz2000_cmdlist_push(shared, cmd);

	/* rotation W0 */
	cmd = C_LGPR(RE_ROT_W0_REG, rot->w0);
	tz2000_cmdlist_push(shared, cmd);

	/* rotation W1 */
	cmd = C_LGPR(RE_ROT_W1_REG, rot->w1);
	tz2000_cmdlist_push(shared, cmd);

	/* rotation W2 */
	cmd = C_LGPR(RE_ROT_W2_REG, rot->w2);
	tz2000_cmdlist_push(shared, cmd);

	QPRINT("pt (%d, %d) - (%d, %d) - (%d, %d) - (%d, %d)",
		rot->pt[0].x, rot->pt[0].y,
		rot->pt[1].x, rot->pt[1].y,
		rot->pt[2].x, rot->pt[2].y,
		rot->pt[3].x, rot->pt[3].y);

	/* rotation */
	cmd = C_LGPR(RE_ROT_FRCC1_REG,
		RE_ROT_FRCC1_VAL(rot->pt[0].x, rot->pt[0].y));
	tz2000_cmdlist_push(shared, cmd);

	/* rotation */
	cmd = C_LGPR(RE_ROT_FRCC2_REG,
		RE_ROT_FRCC1_VAL(rot->pt[1].x, rot->pt[1].y));
	tz2000_cmdlist_push(shared, cmd);

	/* rotation */
	cmd = C_LGPR(RE_ROT_FRCC3_REG,
		RE_ROT_FRCC1_VAL(rot->pt[2].x, rot->pt[2].y));
	tz2000_cmdlist_push(shared, cmd);

	/* rotation */
	cmd = C_LGPR(RE_ROT_FRCC4_REG,
		RE_ROT_FRCC1_VAL(rot->pt[3].x, rot->pt[3].y));
	tz2000_cmdlist_push(shared, cmd);

	/* rotation */
	cmd = C_LGPR(RE_ROT_SRC_POS_REG, rot->start_pt);
	tz2000_cmdlist_push(shared, cmd);

	switch (rot->cmd) {
	case CMD_ROTB:
		cmd = C_ROTB(rot->protect, rot->fade, rot->blend,
						rot->clip, rot->filter);
		break;
	case CMD_ROTO:
		cmd = C_ROTO(rot->clip, rot->filter);
		break;
	default:
		pr_err("%s: INVALID CMD (%02x)\n", __func__, rot->cmd);
	}
	tz2000_cmdlist_push(shared, cmd);

	TEST_PRINT("success\n");
	return 0;
}


static int
tz2000gfx_coef(struct tz2000gfx_share *shared,
			struct applite_gfx_filter *filter)
{
	int	i;
	__u8	*c = filter->coeff;

	TEST_PRINT("start\n");

	QDUMP("add coef command...");
	for (i = 0; i < (256 / 4); i++, c += 4)
		tz2000_write(&tz2000_drv, DEFC_OFFS(i),
			DEFC_VAL(c[i], c[i + 1], c[i + 2], c[i + 3]));
	TEST_PRINT("success\n");
	return 0;
}


/******************************************************************************/

static irqreturn_t
tz2000gfx_irq(int irq, void *ctx)
{
	struct tz2000gfx_drv	*drv = (struct tz2000gfx_drv *)ctx;
	__u32			status = tz2000_read(drv, GFX_REG(GAICR));

	TEST_PRINT("start\n");

	TEST_PRINT("status = %08x\n", status);
	if (!(status & TZ2000_ALL_INTERRUPT)) {
		pr_warn("%s: bogus interrupt, INT_STATUS 0x%08x!\n",
				__func__, status);
		return IRQ_NONE;
	}

	/* Clear the interrupt. */
	tz2000_write(drv, GFX_REG(GAICR), status);

	shared->num_interrupts++;

	/* done command list execution */
	if (status & GAICR_CSLEI_MASK) {
		if (!shared->hw_running)
			pr_warn("%s: hw not running? "
				"INT_STATUS 0x%08x!\n", __func__, status);

		shared->num_idle++;

		QDUMP(" '-> Idle.");

		shared->hw_running = 0;
		wake_up_all(&wait_idle);
		shared->num_done++;
	}

	/* detect error */
	if (status & TZ2000_ERR_INTERRUPT) {
		pr_err("%s: error! INT_STATUS 0x%08x!\n", __func__, status);
		if (status & GAICR_GARBI_ERROR) {
			__u32 stat = tz2000_read(drv, GFX_REG(GARBBECR));
			pr_err("%s: Read Buffer Bus-Error : 0x%08x\n"
				"len:%d, id:%d, ben:0x%02x, rtype:%d, "
				"bsize:%d, btype:%s, wr:%s\n",
				__func__,
				tz2000_read(drv, GFX_REG(GARBBEAR)),
				_LEN_VAL(stat), _ID_VAL(stat), _BEN_VAL(stat),
				_RTYPE_VAL(stat), (1 << _BSIZE_VAL(stat)),
				_BTYPE_VAL(stat) == 0 ? "FIXED" : "INCR",
				_WR_VAL(stat) == 0 ? "Read" : "Write");
		}
		if (status & GAICR_GACBI_ERROR) {
			__u32 stat = tz2000_read(drv, GFX_REG(GACBBECR));
			pr_err("%s: Cache Buffer Bus-Error : 0x%08x\n"
				"len:%d, id:%d, ben:0x%02x, rtype:%d, "
				"bsize:%d, btype:%s, wr:%s\n",
				__func__,
				tz2000_read(drv, GFX_REG(GACBBEAR)),
				_LEN_VAL(stat), _ID_VAL(stat), _BEN_VAL(stat),
				_RTYPE_VAL(stat), (1 << _BSIZE_VAL(stat)),
				_BTYPE_VAL(stat) == 0 ? "FIXED" : "INCR",
				_WR_VAL(stat) == 0 ? "Read" : "Write");
		}
		if (status & GAICR_GAWBRI_ERROR) {
			__u32 stat = tz2000_read(drv, GFX_REG(GAWBRBECR));
			pr_err("%s: Write Buffer Read Bus-Error : 0x%08x\n"
				"len:%d, id:%d, ben:0x%02x, rtype:%d, "
				"bsize:%d, btype:%s, wr:%s\n",
				__func__,
				tz2000_read(drv, GFX_REG(GAWBRBEAR)),
				_LEN_VAL(stat), _ID_VAL(stat), _BEN_VAL(stat),
				_RTYPE_VAL(stat), (1 << _BSIZE_VAL(stat)),
				_BTYPE_VAL(stat) == 0 ? "FIXED" : "INCR",
				_WR_VAL(stat) == 0 ? "Read" : "Write");
		}
		if (status & GAICR_GAWBWI_ERROR) {
			__u32 stat = tz2000_read(drv, GFX_REG(GAWBWBECR));
			pr_err("%s: Write Buffer Write Bus-Error : 0x%08x\n"
				"len:%d, id:%d, ben:0x%02x, rtype:%d, "
				"bsize:%d, btype:%s, wr:%s\n",
				__func__,
				tz2000_read(drv, GFX_REG(GAWBWBEAR)),
				_LEN_VAL(stat), _ID_VAL(stat), _BEN_VAL(stat),
				_RTYPE_VAL(stat), (1 << _BSIZE_VAL(stat)),
				_BTYPE_VAL(stat) == 0 ? "FIXED" : "INCR",
				_WR_VAL(stat) == 0 ? "Read" : "Write");
		}
		if (status & GAICR_CSCEI_ERROR) {
			pr_err("%s: Command Error : 0x%08x\n",
				__func__,
				tz2000_read(drv, GFX_REG(GASR)));
			tz2000gfx_reset(drv->share);
		}
		QDUMP(" '-> Idle.");
		shared->hw_running = 0;
		wake_up_all(&wait_idle);
	}

	TEST_PRINT("success\n");
	return IRQ_HANDLED;
}

static irqreturn_t
tz2000gfx_gamp_irq(int irq, void *ctx)
{
	struct tz2000gfx_drv	*drv = (struct tz2000gfx_drv *)ctx;
	__u32			status = tz2000_read(drv, GFX_REG(GAMPICR));

	TEST_PRINT("start\n");

	TEST_PRINT("status = %08x\n", status);
	/* Clear the interrupt. */
	tz2000_write(drv, GFX_REG(GAMPICR), status);

	if (status & GAMPICR_GAMPCI_MASK)
		pr_err("%s: Memory Protection Configuration "
			"Error STATUS INT_STATUS 0x%08x\n",
			__func__, status);
	else if (status & GAMPICR_GAMPI_MASK)
		pr_err("%s: Memory Protection "
			"Error STATUS INT_STATUS 0x%08x access address 0x%08x "
			"(0x%08x-0x%08x, 0x%08x-0x%08x)\n",
			__func__, status,
			tz2000_read(drv, GFX_REG(GAMPACR)),
			tz2000_read(drv, GFX_REG(GAMPR0LR)),
			tz2000_read(drv, GFX_REG(GAMPR0HR)),
			tz2000_read(drv, GFX_REG(GAMPR1LR)),
			tz2000_read(drv, GFX_REG(GAMPR1HR)));
	else {
		pr_warn("%s: bogus interrupt, INT_STATUS 0x%08x!\n",
			__func__, status);
		return IRQ_NONE;
	}
	TEST_PRINT("success\n");
	return IRQ_HANDLED;
}


/******************************************************************************/


#if !defined(_MERGE_FBDEV_)
static long
tz2000gfx_ioctl(struct file   *filp,
		unsigned int   cmd,
		unsigned long  arg)
#else
long
tz2000gfx_ioctl(struct fb_info *info,
		unsigned int   cmd,
		unsigned long  arg)
#endif
{
	int				ret;
	int				num;
	void __user			*ptr;
	struct applite_gfx_blit		blit;
	struct applite_gfx_transform	trans;
	struct applite_gfx_rotation	rot;
	struct applite_gfx_drawline	dl;
	struct applite_gfx_filltriangle	dt;
	struct applite_gfx_filter	coef;

	TEST_PRINT("start\n");

	switch (cmd) {
	case TZ2000GFX_IOCTL_RESET:
		return tz2000gfx_reset(shared);

	case TZ2000GFX_IOCTL_WAIT_IDLE:
		return tz2000gfx_wait_idle(shared);

	case TZ2000GFX_IOCTL_EMIT_CMD:
		return tz2000gfx_emit_cmd(shared);

	case TZ2000GFX_IOCTL_DRAWLINE:
		if (arg == 0) {
			pr_err("%s: failed (arg is NULL)\n", __func__);
			return -EINVAL;
		}
		if (copy_from_user(&dl, (void __user *)arg,
				sizeof(struct applite_gfx_drawline))) {
			pr_err("%s: copy_from_user(arg) failed "
				"0x%08lx -> %p / %d\n",
				__func__, arg, &dl,
				sizeof(struct applite_gfx_drawline));
			return -EFAULT;
		}
		TEST_PRINT("copy_from_user(drawline) success batch:%d\n",
				dl.num);
		if (dl.line == NULL) {
			pr_err("%s: failed (line is NULL)\n", __func__);
			return -EINVAL;
		}
		num = dl.num;
		ptr = (void __user *)(dl.line);
		while (num > 0) {
			dl.num = min(num, TZ2000GFX_BATCH_NUM);
			if (copy_from_user(batch_buffer.line, ptr,
				sizeof(struct applite_gfx_line) * dl.num)) {
				pr_err("%s: copy_from_user(dl.line) failed "
					"%p -> %p / %d\n",
					__func__, dl.line, batch_buffer.line,
					sizeof(struct applite_gfx_line) * dl.num);
				return -EFAULT;
			}
			dl.line = batch_buffer.line;
			ret = tz2000gfx_draw_line(shared, &dl);
			if (ret != 0)
				break;
			num -= dl.num;
			ptr += (sizeof(struct applite_gfx_line) * dl.num);
		}
		return ret;

	case TZ2000GFX_IOCTL_FILLTRIANGLE:
		if (arg == 0) {
			pr_err("%s: failed (arg is NULL)\n", __func__);
			return -EINVAL;
		}
		if (copy_from_user(&dt, (void __user *)arg,
				sizeof(struct applite_gfx_filltriangle))) {
			pr_err("%s: copy_from_user(arg) failed "
				"0x%08lx -> %p / %d\n",
				__func__, arg, &dt,
				sizeof(struct applite_gfx_filltriangle));
			return -EFAULT;
		}
		TEST_PRINT("copy_from_user(filltriangle) success batch:%d\n",
				dt.num);
		if (dt.triangle == NULL) {
			pr_err("%s: failed (triangle is NULL)\n", __func__);
			return -EINVAL;
		}
		num = dt.num;
		ptr = (void __user *)(dt.triangle);
		while (num > 0) {
			dt.num = min(num, TZ2000GFX_BATCH_NUM);
			if (copy_from_user(batch_buffer.tri, ptr,
				sizeof(struct applite_gfx_triangle) * dt.num)) {
				pr_err("%s: copy_from_user(dt.triangle) failed "
					"%p -> %p / %d\n",
					__func__, dt.triangle, batch_buffer.tri,
					sizeof(struct applite_gfx_triangle) * dt.num);
				return -EFAULT;
			}
			dt.triangle = batch_buffer.tri;
			ret = tz2000gfx_fill_triangle(shared, &dt);
			if (ret != 0)
				break;
			num -= dt.num;
			ptr += (sizeof(struct applite_gfx_triangle) * dt.num);
		}
		return ret;

	case TZ2000GFX_IOCTL_BLIT:
		if (arg == 0) {
			pr_err("%s: failed (arg is NULL)\n", __func__);
			return -EINVAL;
		}
		if (copy_from_user(&blit, (void __user *)arg,
				sizeof(struct applite_gfx_blit))) {
			pr_err("%s: copy_from_user(arg) failed "
				"0x%08lx -> %p / %d\n",
				__func__, arg, &blit,
				sizeof(struct applite_gfx_blit));
			return -EFAULT;
		}
		TEST_PRINT("copy_from_user(blit) success batch:%d\n",
				blit.num);
		if (blit.blit == NULL) {
			pr_err("%s: failed (blit is NULL)\n", __func__);
			return -EINVAL;
		}
		num = blit.num;
		ptr = (void __user *)(blit.blit);
		while (num > 0) {
			blit.num = min(num, TZ2000GFX_BATCH_NUM);
			if (copy_from_user(batch_buffer.blit_prm, ptr,
				sizeof(struct applite_gfx_blit_prm) * blit.num)) {
				pr_err("%s: copy_from_user(blit.blit) failed "
					"%p -> %p / %d\n",
					__func__, blit.blit,
					batch_buffer.blit_prm,
					sizeof(struct applite_gfx_blit_prm) * blit.num);
				return -EFAULT;
			}
			blit.blit = batch_buffer.blit_prm;
			ret = tz2000gfx_blit(shared, &blit);
			if (ret != 0)
				break;
			num -= blit.num;
			ptr += (sizeof(struct applite_gfx_blit_prm) * blit.num);
		}
		return ret;

	case TZ2000GFX_IOCTL_TRANSFORM:
		if (arg == 0) {
			pr_err("%s: failed (arg is NULL)\n", __func__);
			return -EINVAL;
		}
		if (copy_from_user(&trans, (void __user *)arg,
				sizeof(struct applite_gfx_transform))) {
			pr_err("%s: copy_from_user(arg) failed "
				"0x%08lx -> %p / %d\n",
				__func__, arg, &trans,
				sizeof(struct applite_gfx_transform));
			return -EFAULT;
		}
		TEST_PRINT("copy_from_user(transform) success\n");
		return tz2000gfx_transform(shared, &trans);

	case TZ2000GFX_IOCTL_ROTATION:
		if (arg == 0) {
			pr_err("%s: failed (arg is NULL)\n", __func__);
			return -EINVAL;
		}
		if (copy_from_user(&rot, (void __user *)arg,
				sizeof(struct applite_gfx_rotation))) {
			pr_err("%s: copy_from_user(arg) failed "
				"0x%08lx -> %p / %d\n",
				__func__, arg, &rot,
				sizeof(struct applite_gfx_rotation));
			return -EFAULT;
		}
		TEST_PRINT("copy_from_user(rotation) success\n");
		return tz2000gfx_rotation(shared, &rot);

	case TZ2000GFX_IOCTL_COEF:
		if (arg == 0) {
			pr_err("%s: failed (arg is NULL)\n", __func__);
			return -EINVAL;
		}
		if (copy_from_user(&coef, (void __user *)arg,
				sizeof(struct applite_gfx_filter))) {
			pr_err("%s: copy_from_user(arg) failed "
				"0x%08lx -> %p / %d\n",
				__func__, arg, &coef,
				sizeof(struct applite_gfx_filter));
			return -EFAULT;
		}
		TEST_PRINT("copy_from_user(filter) success\n");
		return tz2000gfx_coef(shared, &coef);
	}

	TEST_PRINT("end(%d)\n", -ENOIOCTLCMD);
	return -ENOIOCTLCMD;
}


/******************************************************************************/

#if !defined(_MERGE_FBDEV_)
static const struct file_operations tz2000gfx_fops = {
	.unlocked_ioctl = tz2000gfx_ioctl,
};

static struct miscdevice tz2000gfx_miscdev = {
	.minor = 196,           /* 7*7*2*2 */
	.name  = "tz2000gfx",
	.fops  = &tz2000gfx_fops
};
#endif

/******************************************************************************/

int
tz2000gfx_init(void)
{
	int ret;

	TEST_PRINT("start\n");

	/* Register the TZ2000 graphics device. */
#if !defined(_MERGE_FBDEV_)
	ret = misc_register(&tz2000gfx_miscdev);
	if (ret < 0) {
		pr_err("%s: misc_register() for minor %d failed! (error %d)\n",
			__func__, tz2000gfx_miscdev.minor, ret);
		return ret;
	}
	TEST_PRINT("misc_register() success\n");
#endif

	/* allocate shared buffer */
	shared = dma_alloc_coherent(NULL, sizeof(struct tz2000gfx_share),
			&(tz2000_drv.shared_phys), GFP_KERNEL);
	if (shared == NULL) {
		pr_err("%s: dma_alloc_coherent() failed!\n", __func__);
		ret = -ENOMEM;
		goto error_dma_alloc_coherent;
	}
	pr_info("tz2000gfx: shared area at %p [%x/%x] using %d bytes\n",
			shared, virt_to_phys(shared), tz2000_drv.shared_phys,
			sizeof(struct tz2000gfx_share));
	tz2000_drv.share = shared;

	/* map register */
#if defined(_MERGE_FBDEV_)
	tz2000_drv.gfxbase = priv.gfx_regs;
	tz2000_drv.pmubase = priv.pmu_regs;
#else
	tz2000_drv.gfxbase = (__u8 __iomem *)ioremap_nocache(TZ2000_GFX_REG_BASE,
							TZ2000_GFX_REG_SIZE);
	if (tz2000_drv.gfxbase == NULL) {
		pr_err("%s: ioremap() for register 0x%08x failed!\n",
			__func__, TZ2000_GFX_REG_BASE);
		ret = -EFAULT;
		goto error_ioremap;
	}
	TEST_PRINT("ioremap_nocache(GFX_REG) success %p/%08x\n",
			tz2000_drv.gfxbase, TZ2000_GFX_REG_BASE);

	tz2000_drv.pmubase = (__u8 __iomem *)ioremap_nocache(TZ2000_PMU_REG_BASE,
							TZ2000_PMU_REG_SIZE);
	if (tz2000_drv.pmubase == NULL) {
		pr_err("%s: ioremap() for register 0x%08x failed!\n",
			__func__, TZ2000_PMU_REG_BASE);
		ret = -EFAULT;
		goto error_ioremap2;
	}
	TEST_PRINT("ioremap_nocache(PMU_REG) success %p/%08x\n",
			tz2000_drv.pmubase, TZ2000_PMU_REG_BASE);
#endif

	/* Register the GAS interrupt handler. */
	ret = request_irq(TZ2000_GASINT_IRQ, tz2000gfx_irq, IRQF_SHARED,
			"GFX", (void *)&tz2000_drv);
	if (ret) {
		pr_err("%s: request_irq() for interrupt %d failed! "
			"(error %d)\n", __func__, TZ2000_GASINT_IRQ, ret);
		ret = -EFAULT;
		goto error_gas;
	}
	TEST_PRINT("request_irq(GAS) success\n");

	/* Register the GAMP interrupt handler. */
	ret = request_irq(TZ2000_GAMPINT_IRQ, tz2000gfx_gamp_irq, IRQF_SHARED,
			"GFX", (void *)&tz2000_drv);
	if (ret) {
		pr_err("%s: request_irq() for interrupt %d failed! "
			"(error %d)\n", __func__, TZ2000_GAMPINT_IRQ, ret);
		ret = -EFAULT;
		goto error_gamp;
	}
	TEST_PRINT("request_irq(GAMP) success\n");

#if !defined(_MERGE_FBDEV_)
	tz2000gfx_hw_init(shared);
	tz2000gfx_reset(shared);
#endif

	TEST_PRINT("success\n");
	return 0;


error_gamp:
	TEST_PRINT("free_irq(GAS)\n");
	free_irq(TZ2000_GASINT_IRQ, (void *)&tz2000_drv);
error_gas:
#if !defined(_MERGE_FBDEV_)
	TEST_PRINT("iounmap(PMU_REG)\n");
	iounmap(tz2000_drv.pmubase);
error_ioremap2:
	TEST_PRINT("iounmap(GFX_REG)\n");
	iounmap(tz2000_drv.gfxbase);
error_ioremap:
#endif
	TEST_PRINT("dma_free_coherent()\n");
	dma_free_coherent(NULL, sizeof(struct tz2000gfx_share), (void *)shared,
			tz2000_drv.shared_phys);
error_dma_alloc_coherent:
#if !defined(_MERGE_FBDEV_)
	TEST_PRINT("misc_deregister()\n");
	misc_deregister(&tz2000gfx_miscdev);
#endif

	TEST_PRINT("failed(%d)\n", ret);
	return ret;
}

/******************************************************************************/

void
tz2000gfx_exit(void)
{
	TEST_PRINT("start\n");

#if !defined(_MERGE_FBDEV_)
	/* wait for idle */
	while (tz2000gfx_hw_exit(shared) != 0)
		;
#endif
	/* disable interrupt */
	if (tz2000_drv.gfxbase != NULL)
		tz2000_write(&tz2000_drv, GFX_REG(GAIMR), 0);

	TEST_PRINT("free_irq(GAS)\n");
	free_irq(TZ2000_GASINT_IRQ, (void *)&tz2000_drv);
	TEST_PRINT("free_irq(GAMP)\n");
	free_irq(TZ2000_GAMPINT_IRQ, (void *)&tz2000_drv);

#if !defined(_MERGE_FBDEV_)
	TEST_PRINT("iounmap(PMU_REG)\n");
	if (tz2000_drv.pmubase != NULL)
		iounmap(tz2000_drv.pmubase);
	TEST_PRINT("iounmap(GFX_REG)\n");
	if (tz2000_drv.gfxbase != NULL)
		iounmap(tz2000_drv.gfxbase);
#endif

	TEST_PRINT("dma_free_coherent()\n");
	dma_free_coherent(NULL, sizeof(struct tz2000gfx_share), (void *)shared,
			tz2000_drv.shared_phys);

#if !defined(_MERGE_FBDEV_)
	TEST_PRINT("misc_deregister()\n");
	misc_deregister(&tz2000gfx_miscdev);
#endif

	TEST_PRINT("success\n");
}

