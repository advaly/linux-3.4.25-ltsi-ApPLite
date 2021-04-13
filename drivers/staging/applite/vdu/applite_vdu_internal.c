/*
 * drivers/staging/applite/vdu/applite_vdu_internal.c
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

/*===================================
Include Files
===================================*/

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/firmware.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/scatterlist.h>
#include <linux/sched.h>	 /* task_struct */
#include <linux/wait.h>
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/dma-buf.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/io.h>
#include <asm/processor.h>
#include <linux/uaccess.h>
#include <asm/pgtable.h>
#include <asm/dma.h>
#include <asm/segment.h>
#include <linux/buffer_head.h>
#include <asm/cacheflush.h>

#include <linux/applite/applite_vdu.h>
#include "applite_vdu_internal.h"

#include <linux/applite/applitema.h>

/*===================================
Static Variables and Functions prototypes
===================================*/

static spinlock_t vdapi_splock;
static unsigned long vdapi_lock_flags;

static int vdu_internal_memory_alloc(struct vdu_driver *, size_t,
	enum vdu_mem_type, enum vdu_mem_align, struct vdu_locmem *);
static void vdu_internal_memory_free(struct vdu_driver *,
	struct vdu_locmem *);
static int vdu_internal_ringbuf_size(struct vdu_driver *,
	struct vdu_task *, uint32_t *);
static int vdu_internal_ringbuf_write(struct vdu_driver *,
	struct vdu_task *, uint32_t, uint32_t);
static void vdu_internal_set_frame_info(struct vdu_driver *, struct vdu_task *,
	struct vdec_frame_info *, struct vd_frame_info *);
static int vdu_internal_wait_event(struct vdu_driver *,
	struct vdu_task *, int, int);
static int vdu_internal_searchtask_for_ch(struct vdu_driver *, int32_t,
	struct vdu_task **);
static uint32_t vdu_internal_phys_to_vdu(uint32_t);
static void vdapi_lock(void *);
static void vdapi_unlock(void *);
static int vdu_internal_vconv(struct vdu_driver *,
	struct vdu_task *, struct vdec_getoutframewithconv *);


/*===================================
Global Variables and Functions prototypes
===================================*/

/*===================================
Macros
===================================*/

/*===================================
Function Definitions
===================================*/

/*===================================
Module source
===================================*/


int vdu_internal_init_resource(struct vdu_driver *pdev)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	INIT_LIST_HEAD(&pdev->task_head);
	pdev->task_num = 0;

	/* MBOX1[REG4-7] : set register */
	reg_write(0, REG_MBOX1(pdev, REG104_SET_OFFS));
	reg_write(0, REG_MBOX1(pdev, REG105_SET_OFFS));
	reg_write(0, REG_MBOX1(pdev, REG106_SET_OFFS));
	reg_write(0, REG_MBOX1(pdev, REG107_SET_OFFS));
	/* MBOX1[REG4-7] : clear register */
	reg_write(MBOX_INT_REG104_CLEAR_CLEAR_BIT,
		REG_MBOX1(pdev, REG104_CLEAR_OFFS));
	reg_write(MBOX_INT_REG105_CLEAR_CLEAR_BIT,
		REG_MBOX1(pdev, REG105_CLEAR_OFFS));
	reg_write(MBOX_INT_REG106_CLEAR_CLEAR_BIT,
		REG_MBOX1(pdev, REG106_CLEAR_OFFS));
	reg_write(MBOX_INT_REG107_CLEAR_CLEAR_BIT,
		REG_MBOX1(pdev, REG107_CLEAR_OFFS));
	/* MBOX1[REG4-7] : mask register */
	reg_write(~MBOX_INT_REG104_MASK_MASK_MASK,
		REG_MBOX1(pdev, REG104_MASK_OFFS));
	reg_write(~MBOX_INT_REG105_MASK_MASK_MASK,
		REG_MBOX1(pdev, REG105_MASK_OFFS));
	reg_write(~MBOX_INT_REG106_MASK_MASK_MASK,
		REG_MBOX1(pdev, REG106_MASK_OFFS));
	reg_write(~MBOX_INT_REG107_MASK_MASK_MASK,
		REG_MBOX1(pdev, REG107_MASK_OFFS));

	/* MBOX4[REG0-15] : set register */
	reg_write(0, REG_MBOX4(pdev, REG400_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG401_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG402_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG403_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG404_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG405_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG406_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG407_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG408_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG409_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG410_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG411_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG412_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG413_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG414_SET_OFFS));
	reg_write(0, REG_MBOX4(pdev, REG415_SET_OFFS));
	/* MBOX4[REG0-15] : clear register */
	reg_write(MBOX_INT_REG400_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG400_CLEAR_OFFS));
	reg_write(MBOX_INT_REG401_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG401_CLEAR_OFFS));
	reg_write(MBOX_INT_REG402_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG402_CLEAR_OFFS));
	reg_write(MBOX_INT_REG403_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG403_CLEAR_OFFS));
	reg_write(MBOX_INT_REG404_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG404_CLEAR_OFFS));
	reg_write(MBOX_INT_REG405_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG405_CLEAR_OFFS));
	reg_write(MBOX_INT_REG406_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG406_CLEAR_OFFS));
	reg_write(MBOX_INT_REG407_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG407_CLEAR_OFFS));
	reg_write(MBOX_INT_REG408_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG408_CLEAR_OFFS));
	reg_write(MBOX_INT_REG409_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG409_CLEAR_OFFS));
	reg_write(MBOX_INT_REG410_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG410_CLEAR_OFFS));
	reg_write(MBOX_INT_REG411_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG411_CLEAR_OFFS));
	reg_write(MBOX_INT_REG412_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG412_CLEAR_OFFS));
	reg_write(MBOX_INT_REG413_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG413_CLEAR_OFFS));
	reg_write(MBOX_INT_REG414_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG414_CLEAR_OFFS));
	reg_write(MBOX_INT_REG415_CLEAR_CLEAR_BIT,
		REG_MBOX4(pdev, REG415_CLEAR_OFFS));
	/* MBOX4[REG0-15] : mask register */
	reg_write(~MBOX_INT_REG400_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG400_MASK_OFFS));
	reg_write(~MBOX_INT_REG401_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG401_MASK_OFFS));
	reg_write(~MBOX_INT_REG402_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG402_MASK_OFFS));
	reg_write(~MBOX_INT_REG403_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG403_MASK_OFFS));
	reg_write(~MBOX_INT_REG404_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG404_MASK_OFFS));
	reg_write(~MBOX_INT_REG405_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG405_MASK_OFFS));
	reg_write(~MBOX_INT_REG406_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG406_MASK_OFFS));
	reg_write(~MBOX_INT_REG407_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG407_MASK_OFFS));
	reg_write(~MBOX_INT_REG408_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG408_MASK_OFFS));
	reg_write(~MBOX_INT_REG409_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG409_MASK_OFFS));
	reg_write(~MBOX_INT_REG410_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG410_MASK_OFFS));
	reg_write(~MBOX_INT_REG411_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG411_MASK_OFFS));
	reg_write(~MBOX_INT_REG412_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG412_MASK_OFFS));
	reg_write(~MBOX_INT_REG413_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG413_MASK_OFFS));
	reg_write(~MBOX_INT_REG414_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG414_MASK_OFFS));
	reg_write(~MBOX_INT_REG415_MASK_MASK_MASK,
		REG_MBOX4(pdev, REG415_MASK_OFFS));

	DBG(pdev, "leave [rtn=%d]\n", ierr);

	return ierr;
}

void vdu_internal_clear_resource(struct vdu_driver *pdev)
{
	unsigned long flags;
	struct vdu_task *ptask, *tnext;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	if (pdev->task_num) {
		/* clear struct vdu_task */
		list_for_each_entry_safe(ptask, tnext, &pdev->task_head, list) {
			list_del(&ptask->list);
			spin_unlock_irqrestore(&pdev->splock, flags);
			vdu_internal_memory_free(pdev, &ptask->vd_task_std);
			vdu_internal_memory_free(pdev, &ptask->vd_task_work);
			vdu_internal_memory_free(pdev, &ptask->vd_task_frame);
			spin_lock_irqsave(&pdev->splock, flags);
			vdu_kfree(ptask);
		}
	}

	spin_unlock_irqrestore(&pdev->splock, flags);

	DBG(pdev, "leave\n");
}

int vdu_internal_fw_download(struct vdu_driver *pdev)
{
	int ierr = 0;
	int32_t fw_size;
	u8 *fw_addr;
	const struct firmware *fw;

	DBG(pdev, "enter\n");

	/* read VIP1 FW image */
	ierr = request_firmware(&fw, VDU_VIP1_FW_NAME, pdev->device);
	if (ierr < 0) {
		ERROR(pdev, "request_firmware() failed [fw=%s][err=%d]\n",
			VDU_VIP1_FW_NAME, ierr);
		goto done_1;
	}
	DBG(pdev, "fw size=%d\n", (int32_t)fw->size);
	if (fw->size > VDU_FW_AREA_SIZE) {
		ERROR(pdev, "fw area is too small [req size=%d][fw size=%d]\n",
			VDU_FW_AREA_SIZE, fw->size);
		ierr = -ENOENT;
		goto done_1;
	}

	/* copy to firmware */
	fw_size = (int32_t)fw->size;
	fw_addr = (u8 *)fw->data;
	DBG(pdev, "copy to fw [0x%x->0x%x:%d]\n",
		(uint32_t)fw_addr, (uint32_t)pdev->vd_fw_area.addr, fw_size);
	memcpy((void *)pdev->vd_fw_area.addr, fw_addr, fw_size);

	release_firmware(fw);
	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_initialize(struct vdu_driver *pdev)
{
	int ierr = 0;
	struct vd_accessor accessor;
	struct vd_buf trace;
	enum vd_fw_state fw_state;
	uint32_t api_version;
	uint32_t fw_version;
	enum vd_result vdret;
	int finish_flag = 0;

	DBG(pdev, "enter\n");

	/* initialize VIP1 */
	spin_lock_init(&vdapi_splock);
	pdev->fw_int_bap_boot = false;
	pdev->fw_int_vdp_boot = false;

	/* call vd_fw_initialize for VD_API */
	accessor.fw_address.p_addr = (vd_physical_t)pdev->vd_fw_area.dma_addr;
	accessor.fw_address.v_addr = (vd_virtual_t)pdev->vd_fw_area.addr;
	accessor.lock  = (void(*)(void *))vdapi_lock;
	accessor.unlock = (void(*)(void *))vdapi_unlock;
	accessor.private_data = &vdapi_splock;
	accessor.mbox_addr = (vd_virtual_t)((unsigned long)pdev->iomem[VDU_IOMEM_MBOX_REG]);

	DBG(pdev, "call vd_fw_initialize()\n");
	DBG(pdev, "\t[fw_address=%08X:%08X]\n",
		accessor.fw_address.p_addr, accessor.fw_address.v_addr);
	DBG(pdev, "\t[mbox_addr=%08X]\n", accessor.mbox_addr);
	vdret = vd_fw_initialize(&accessor);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_fw_initialize() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto fail_initialize;
	}
	DBG(pdev, "return vd_fw_initialize() [ret=%d]\n", vdret);

	/* call vd_fw_get_state for VD_API */
	DBG(pdev, "call vd_fw_get_state()\n");
	vdret = vd_fw_get_state(0, &fw_state);
	DBG(pdev, "return vd_fw_get_state() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_fw_get_state() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		finish_flag |= VDU_FIN_PHASE1; /* vd_fw_finalize() only */
		goto fail_state;
	}
	if (fw_state != VD_FW_POWER_OFF) {
		ERROR(pdev, "VIP1 FW status error [state=%d]\n", fw_state);
		finish_flag |= VDU_FIN_PHASE1; /* vd_fw_finalize() only */
		ierr = -EVDUVDAPI;
		goto fail_state;
	}

	/* call vd_debug_get_api_version for VD_API */
	vdret = vd_debug_get_api_version(&api_version);
	if (vdret == VD_SUCCESS)
		INFO(pdev, "API Version = %08x\n", api_version);

	/* call vd_fw_start_up for VD_API */
	DBG(pdev, "call vd_fw_start_up()\n");
	vdret = vd_fw_start_up(0);
	DBG(pdev, "return vd_fw_start_up() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_fw_start_up() failed [err=%d]\n", vdret);
		finish_flag |= VDU_FIN_PHASE1; /* vd_fw_finalize() only */
		ierr = -EVDUVDAPI;
		goto fail_state;
	}

	/* reset off */
	reg_write(pdev->vd_fw_area.dma_addr,
		REG_ECONF(pdev, VDU0_ADDRCONF0_OFFS));
	reg_write(pdev->vd_fw_area.dma_addr,
		REG_ECONF(pdev, VDU1_ADDRCONF0_OFFS));
	reg_write(pdev->vd_fw_area.dma_addr,
		REG_ECONF(pdev, VDIME_ADDRCONF0_OFFS));
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	DBG(pdev, "pm_runtime_get_sync call\n");
	pm_runtime_get_sync(&(pdev->pdev->dev));
#else
	DBG(pdev, "vcodec_power_up\n");
	vcodec_power_up();			/* video power on */
	DBG(pdev, "vdu_internal_vip1_reset off\n");
	vdu_internal_vip1_reset(pdev, 0);	/* VIP1 reset off */
#endif

	ierr = vdu_internal_wait_event(pdev, NULL,
			VDU_COND_FW, VDU_VDAPI_RSP_TIMEOUT);
	if (ierr < 0) {
		ERROR(pdev, "vd_fw_start_up() timeout\n");
		finish_flag |= (VDU_FIN_PHASE1 | \
				VDU_FIN_PHASE3);
		goto fail_state;
	}

	/* call vd_debug_get_fw_version for vdufw.bin */
	vdret = vd_debug_get_fw_version(&fw_version);
	if (vdret == VD_SUCCESS)
		INFO(pdev, "FW  Version = %08x\n", fw_version);

	/* call vd_fw_get_state for VD_API */
	DBG(pdev, "call vd_fw_get_state()\n");
	vdret = vd_fw_get_state(0, &fw_state);
	DBG(pdev, "return vd_fw_get_state() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_fw_get_state() failed [err=%d]\n", vdret);
		finish_flag |= (VDU_FIN_PHASE1 | \
				VDU_FIN_PHASE2 | \
				VDU_FIN_PHASE3);
		ierr = -EVDUVDAPI;
		goto fail_state;
	}
	if (fw_state != VD_FW_READY) {
		ERROR(pdev, "VIP1 FW status error [state=%d]\n", fw_state);
		finish_flag |= (VDU_FIN_PHASE1 | \
				VDU_FIN_PHASE2 | \
				VDU_FIN_PHASE3);
		ierr = -EVDUVDAPI;
		goto fail_state;
	}

	INFO(pdev, "VIP1 FW area [p_addr=%08X][v_addr=%08X][size=%d]\n",
		pdev->vd_fw_area.dma_addr, pdev->vd_fw_area.addr,
		pdev->vd_fw_area.size);

	if (pdev->debug) {
		/* allocate trace area */
		ierr = vdu_internal_memory_alloc(pdev,
			pdev->trace_area_size,
			VDU_MEM_TYPE_DMA,
			VDU_MEM_ALIGN_4K, &pdev->vd_trace);
		if (!ierr) {
			/* call vd_debug_set_trace_buf for VD_API */
			trace.addr.p_addr =
				(vd_physical_t)pdev->vd_trace.dma_addr;
			trace.addr.v_addr =
				(vd_virtual_t)pdev->vd_trace.addr;
			trace.size = pdev->trace_area_size;
			DBG(pdev, "call vd_debug_set_trace_buf()\n");
			vdret = vd_debug_set_trace_buf(0, &trace);
			DBG(pdev, "return vd_debug_set_trace_buf() [ret=%d]\n",
				vdret);
			if (vdret != VD_SUCCESS) {
				ERROR(pdev, "vd_debug_set_trace_buf() failed [err=%d]\n", vdret);
			} else {
				INFO(pdev, "Trace area [p_addr=%08X][v_addr=%08X][size=%d]\n",
					pdev->vd_trace.dma_addr,
					pdev->vd_trace.addr,
					pdev->vd_trace.size);
			}
		}
	} else {
		pdev->vd_trace.type = VDU_MEM_TYPE_NON;
		vdu_internal_memory_free(pdev, &pdev->vd_trace);
	}

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return 0;

fail_state:
	vdu_internal_finalize(pdev, finish_flag);
fail_initialize:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_finalize(struct vdu_driver *pdev, int flag)
{
	int ierr = 0;
	enum vd_fw_state fw_state;
	enum vd_result vdret;

	DBG(pdev, "enter\n");

	if (flag|VDU_FIN_PHASE1) {
		/* call vd_fw_shut_down for VD_API */
		DBG(pdev, "call vd_fw_shut_down()\n");
		pdev->fw_int_bap_boot = false;
		pdev->fw_int_vdp_boot = false;
		vdret = vd_fw_shut_down(0);
		DBG(pdev, "return vd_fw_shut_down() [ret=%d]\n", vdret);
		if (vdret != VD_SUCCESS) {
			ERROR(pdev, "vd_fw_shut_down() failed [err=%d]\n",
				vdret);
			ierr = -EVDUVDAPI;
		} else {
			ierr = vdu_internal_wait_event(pdev, NULL,
					VDU_COND_FW,
					VDU_VDAPI_RSP_TIMEOUT);
			if (ierr < 0) {
				ERROR(pdev, "vd_fw_shut_down() timeout\n");
			} else {
				/* call vd_fw_get_state for VD_API */
				DBG(pdev, "call vd_fw_get_state()\n");
				vdret = vd_fw_get_state(0, &fw_state);
				DBG(pdev, "return vd_fw_get_state() [ret=%d]\n", vdret);
				if (vdret != VD_SUCCESS) {
					ERROR(pdev, "vd_fw_get_state() failed [err=%d]\n", vdret);
					ierr = -EVDUVDAPI;
				} else {
					if (fw_state != VD_FW_SHUT_DOWN) {
						ERROR(pdev, "VIP1 FW status error [state=%d]\n",
							fw_state);
						ierr = -EVDUVDAPI;
					}
				}
			}
		}
	}

	if (flag|VDU_FIN_PHASE2) {
		/* call vd_fw_finalize for VD_API */
		DBG(pdev, "call vd_fw_finalize()\n");
		vdret = vd_fw_finalize();
		DBG(pdev, "return vd_fw_finalize() [ret=%d]\n", vdret);
		if (vdret != VD_SUCCESS) {
			ERROR(pdev, "vd_fw_finalize() failed [err=%d]\n",
				vdret);
			ierr = -EVDUVDAPI;
		}

		/* call vd_fw_get_state for VD_API */
		DBG(pdev, "call vd_fw_get_state()\n");
		vdret = vd_fw_get_state(0, &fw_state);
		DBG(pdev, "return vd_fw_get_state() [ret=%d]\n", vdret);
		if (vdret != VD_SUCCESS) {
			ERROR(pdev, "vd_fw_get_state() failed [err=%d]\n",
				vdret);
			ierr = -EVDUVDAPI;
		} else {
			if (fw_state != VD_FW_NOT_INIT) {
				ERROR(pdev, "VIP1 FW status error [state=%d]\n", fw_state);
				ierr = -EVDUVDAPI;
			}
		}
	}

	if (flag|VDU_FIN_PHASE3) {
		/* reset on */
#if IS_ENABLED(CONFIG_PM_RUNTIME)
		DBG(pdev, "pm_runtime_put_sync call\n");
		pm_runtime_put_sync(&(pdev->pdev->dev));
#else
		DBG(pdev, "vdu_internal_vip1_reset on\n");
		vdu_internal_vip1_reset(pdev, 1);	/* VIP1 reset on */
		DBG(pdev, "vcodec_power_down\n");
		vcodec_power_down();			/* video power off */
#endif

		if (pdev->debug)
			vdu_internal_memory_free(pdev, &pdev->vd_trace);
	}

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_create_task(struct vdu_driver *pdev, uint32_t *rtaskid)
{
	int ierr = 0;
	enum vd_result vdret;
	struct vdu_task *ptask = NULL;
	unsigned long flags;

	DBG(pdev, "enter\n");

	/* create struct vdu_task */
	ptask = (struct vdu_task *)vdu_kmalloc(sizeof(struct vdu_task));
	if (!ptask) {
		ERROR(pdev, "kernel memory allocate failed [struct vdu_task][size=%d]\n", sizeof(struct vdu_task));
		ierr = -ENOMEM;
		goto done_1;
	}
	ptask->vd_task_std.type = VDU_MEM_TYPE_NON;
	vdu_internal_memory_free(pdev, &ptask->vd_task_std);
	ptask->vd_task_work.type = VDU_MEM_TYPE_NON;
	vdu_internal_memory_free(pdev, &ptask->vd_task_work);
	ptask->vd_task_frame.type = VDU_MEM_TYPE_NON;
	vdu_internal_memory_free(pdev, &ptask->vd_task_frame);
	init_waitqueue_head(&ptask->vdu_waitq);
	ptask->wait_cond = 0;
	ptask->uf_thr = pdev->uf_thr;
	ptask->inbuf_b = ptask->inbuf_e = NULL;
	ptask->tasksts = VDU_TASK_STAT_IDLE;

	/* call vd_task_create for VD_API */
	DBG(pdev, "call vd_task_create(ctx=0x%x)\n", (u32)&ptask->ctx);
	vdret = vd_task_create(0, &ptask->ctx);
	DBG(pdev, "return vd_task_create() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_task_create() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	/* call vd_task_get_ch for VD_API */
	DBG(pdev, "call vd_task_get_ch()\n");
	vdret = vd_task_get_ch(&ptask->ctx, &ptask->ch_num);
	DBG(pdev, "return vd_task_get_ch() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_task_get_ch() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}
	DBG(pdev, "use ch=%d\n", ptask->ch_num);

	/* queuing to device table */
	spin_lock_irqsave(&pdev->splock, flags);
	list_add_tail(&ptask->list, &pdev->task_head);
	pdev->task_num++;
	spin_unlock_irqrestore(&pdev->splock, flags);

	*rtaskid = (uint32_t)ptask;

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
done_1:
	vdu_kfree(ptask);
	*rtaskid = 0;
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_destroy_task(struct vdu_driver *pdev, struct vdu_task *ptask)
{
	int ierr = 0;
	enum vd_result vdret;
	unsigned long flags;

	DBG(pdev, "enter\n");

	/* call vd_task_destroy for VD_API */
	DBG(pdev, "call vd_task_destroy(ctx=0x%x)\n", (u32)&ptask->ctx);
	vdret = vd_task_destroy(&ptask->ctx);
	DBG(pdev, "return vd_task_destroy() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_task_destroy() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	/* delete struct vdu_task */
	spin_lock_irqsave(&pdev->splock, flags);
	list_del(&ptask->list);
	pdev->task_num--;
	spin_unlock_irqrestore(&pdev->splock, flags);

	vdu_internal_memory_free(pdev, &ptask->vd_task_std);
	vdu_internal_memory_free(pdev, &ptask->vd_task_work);
	vdu_internal_memory_free(pdev, &ptask->vd_task_frame);
	vdu_kfree(ptask);

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_start_task(struct vdu_driver *pdev, struct vdu_task *ptask,
		struct vdec_start *pstart)
{
	int ierr = 0;
	enum vd_result vdret;
	enum vd_fw_state fw_state;
	struct vd_param param;
	struct vd_buf std;
	struct vd_buf work;
	struct vd_buf frame;

	DBG(pdev, "enter\n");

	/* allocate memory from local memory */
	ierr = vdu_internal_memory_alloc(pdev,
			pdev->vdu_task_std_size,
			VDU_MEM_TYPE_DMA, VDU_MEM_ALIGN_4K,
			&ptask->vd_task_std);
	if (ierr != 0)
		goto done_1;
	std.addr.p_addr = (vd_physical_t)ptask->vd_task_std.dma_addr;
	std.addr.v_addr = (vd_virtual_t)ptask->vd_task_std.addr;
	std.size = pdev->vdu_task_std_size;
	ierr = vdu_internal_memory_alloc(pdev,
			pdev->vdu_task_work_size,
			VDU_MEM_TYPE_DMA, VDU_MEM_ALIGN_4K,
			&ptask->vd_task_work);
	if (ierr != 0)
		goto done_1;
	work.addr.p_addr = (vd_physical_t)ptask->vd_task_work.dma_addr;
	work.addr.v_addr = (vd_virtual_t)ptask->vd_task_work.addr;
	work.size = pdev->vdu_task_work_size;

	/* from memory allocator */
	ptask->vd_task_frame.fd = pstart->in_outbuffer.fd;
	ptask->vd_task_frame.offset = pstart->in_outbuffer.offset;
	ierr = vdu_internal_memory_alloc(pdev,
		pstart->in_outbuffersize,
		VDU_MEM_TYPE_MA, VDU_MEM_ALIGN_1M,
		&ptask->vd_task_frame);
	if (ierr != 0)
		goto done_1;
	frame.addr.p_addr = (vd_physical_t)ptask->vd_task_frame.dma_addr;
	frame.addr.v_addr = (vd_virtual_t)ptask->vd_task_frame.addr;
	frame.size = pstart->in_outbuffersize;

	/* setting parameter */
	if (pstart->in_uf_thr > 0)
		ptask->uf_thr = pstart->in_uf_thr;
	param.decoder = (enum vd_decoder_type)pstart->in_decoder;
	param.nuf = ptask->uf_thr;

	/* call vd_task_start for VD_API */
	DBG(pdev, "call vd_task_start(ctx=0x%x)\n", (u32)&ptask->ctx);
	DBG(pdev, "\t[decoder=%d][nuf=%d]\n", param.decoder, param.nuf);
	DBG(pdev, "\t[std=%08X:%08X:%d]\n", std.addr.p_addr, std.addr.v_addr, std.size);
	DBG(pdev, "\t[work=%08X:%08X:%d]\n", work.addr.p_addr, work.addr.v_addr, work.size);
	DBG(pdev, "\t[frame=%08X:%08X:%d]\n", frame.addr.p_addr, frame.addr.v_addr, frame.size);
	ptask->task_int_start_stop = false;
	vdret = vd_task_start(&ptask->ctx, &param, &std, &work, &frame);
	DBG(pdev, "return vd_task_start() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_task_start() failed [err=%d]\n", vdret);
		ERROR(pdev, "\t[decoder=%d][nuf=%d]\n",
			param.decoder, param.nuf);
		ERROR(pdev, "\t[std=%08X:%08X:%d]\n",
			std.addr.p_addr, std.addr.v_addr, std.size);
		ERROR(pdev, "\t[work=%08X:%08X:%d]\n",
			work.addr.p_addr, work.addr.v_addr, work.size);
		ERROR(pdev, "\t[frame=%08X:%08X:%d]\n",
			frame.addr.p_addr, frame.addr.v_addr, frame.size);
		ierr = -EVDUVDAPI;
		goto done_1;
	}
	ierr = vdu_internal_wait_event(pdev, ptask,
				VDU_COND_TASK, VDU_VDAPI_RSP_TIMEOUT);
	if (ierr < 0) {
		ERROR(pdev, "vd_task_start() timeout\n");
		goto done_1;
	}

	/* call vd_fw_get_state() for VD_API */
	DBG(pdev, "call vd_fw_get_state()\n");
	vdret = vd_fw_get_state(0, &fw_state);
	DBG(pdev, "return vd_fw_get_state() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_fw_get_state() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}
	if (fw_state != VD_FW_RUNNING) {
		ERROR(pdev, "VIP1 FW status error [state=%d]\n", fw_state);
		ierr = -EVDUVDAPI;
		goto done_1;
	}
	ptask->tasksts = VDU_TASK_STAT_START;

	/* set input ring-buffer address */
	ptask->inbuf_b = (char *)ptask->vd_task_std.addr;
	ptask->inbuf_e = (char *)(ptask->vd_task_std.addr +
		pdev->vdu_task_std_size);

	ierr = 0;
done_1:
	if (ierr < 0) {
		vdu_internal_memory_free(pdev, &ptask->vd_task_std);
		vdu_internal_memory_free(pdev, &ptask->vd_task_work);
		vdu_internal_memory_free(pdev, &ptask->vd_task_frame);
	}
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_stop_task(struct vdu_driver *pdev, struct vdu_task *ptask)
{
	int ierr = 0;
	enum vd_result vdret;
	enum vd_fw_state fw_state;

	DBG(pdev, "enter\n");

	if ((ptask->tasksts < VDU_TASK_STAT_START) ||
	    (ptask->tasksts > VDU_TASK_STAT_EOD)) {
		/* unnecessary */
		ierr = 0;
		goto done_1;
	}

	/* call vd_task_stop for VD_API */
	DBG(pdev, "call vd_task_stop(ctx=0x%x)\n", (u32)&ptask->ctx);
	ptask->task_int_start_stop = false;
	vdret = vd_task_stop(&ptask->ctx);
	DBG(pdev, "return vd_task_stop() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_task_stop() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}
	ierr = vdu_internal_wait_event(pdev, ptask,
				VDU_COND_TASK, VDU_VDAPI_RSP_TIMEOUT);
	if (ierr < 0) {
		ERROR(pdev, "vd_task_stop() timeout\n");
		goto done_1;
	}

	/* call vd_fw_get_state for VD_API */
	DBG(pdev, "call vd_fw_get_state()\n");
	vdret = vd_fw_get_state(0, &fw_state);
	DBG(pdev, "return vd_fw_get_state() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_fw_get_state() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}
	if (fw_state != VD_FW_READY) {
		ERROR(pdev, "VIP1 FW status error [state=%d]\n", fw_state);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	ptask->tasksts = VDU_TASK_STAT_STOP;
	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_cancel_task(struct vdu_driver *pdev, struct vdu_task *ptask)
{
	int ierr = 0;
	unsigned long flags;

	DBG(pdev, "enter\n");

	if (ptask->tasksts < VDU_TASK_STAT_START) {
		/* unnecessary */
		ierr = 0;
		goto done_1;
	}

	/* cancel wait event */
	spin_lock_irqsave(&pdev->splock, flags);
	set_bit(VDU_COND_OUTFRM, &ptask->wait_cond);
	set_bit(VDU_COND_INBUF, &ptask->wait_cond);
	set_bit(VDU_COND_CANCEL, &ptask->wait_cond);
	wake_up_interruptible(&ptask->vdu_waitq);
	spin_unlock_irqrestore(&pdev->splock, flags);

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}


int vdu_internal_start(struct vdu_driver *pdev,
	struct vdec_start *pstart, uint32_t *taskid)
{
	int ierr = 0;
	struct vdu_task *ptask = NULL;

	DBG(pdev, "enter\n");

	if (*taskid) {
		/* get struct vdu_task */
		ierr = vdu_internal_searchtask(pdev, *taskid, &ptask);
		if (!ierr) {
			/* task stop & destroy */
			vdu_internal_cancel_task(pdev, ptask);
			vdu_internal_stop_task(pdev, ptask);
			vdu_internal_destroy_task(pdev, ptask);
		}
	}

	/* create task */
	ierr = vdu_internal_create_task(pdev, taskid);
	if (ierr < 0)
		goto done_1;

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, *taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%x]\n", *taskid);
		goto done_1;
	}

	/* start task */
	ierr = vdu_internal_start_task(pdev, ptask, pstart);
	if (ierr < 0)
		goto done_1;

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_stop(struct vdu_driver *pdev, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask = NULL;

	DBG(pdev, "enter\n");

	if (!taskid)
		goto done_1;

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0)
		goto done_1;

	/* cancel task */
	vdu_internal_cancel_task(pdev, ptask);

	/* stop task */
	vdu_internal_stop_task(pdev, ptask);

	/* destroy task */
	vdu_internal_destroy_task(pdev, ptask);

done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return 0;
}

int vdu_internal_getininfo(struct vdu_driver *pdev,
	struct vdec_getininfo *pgetininfo, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask = NULL;

	DBG(pdev, "enter\n");

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%x]\n", taskid);
		goto done_1;
	}

	if (ptask->tasksts != VDU_TASK_STAT_START) {
		ERROR(pdev, "illegal phase [taskid=%x][sts=%d]\n",
			taskid, ptask->tasksts);
		ierr = -EVDUESTAT;
		goto done_1;
	}

	/* get input ring-buffer free size */
	ierr = vdu_internal_ringbuf_size(pdev, ptask,
			&pgetininfo->out_inbuf_max_size);
	if (ierr < 0)
		goto done_1;

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_setindata(struct vdu_driver *pdev,
	struct vdec_setindata *psetindata, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask = NULL;
	enum vd_result vdret;
	uint32_t free_size;

	DBG(pdev, "enter\n");

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%x]\n", taskid);
		goto done_1;
	}

	if (ptask->tasksts != VDU_TASK_STAT_START) {
		ERROR(pdev, "illegal phase [taskid=%x][sts=%d]\n",
			taskid, ptask->tasksts);
		ierr = -EVDUESTAT;
		goto done_1;
	}

	if (psetindata->in_buffersize && psetindata->in_buffer) {
		/* get input ring-buffer free size */
		ierr = vdu_internal_ringbuf_size(pdev, ptask,
						&free_size);
		if (ierr < 0)
			goto done_1;
		if (free_size < psetindata->in_buffersize) {
			ERROR(pdev, "input ring-buffer is too small [req size=%d][ring-buffer=%d]\n",
				psetindata->in_buffersize, free_size);
			ierr = -EBUSY;
			goto done_1;
		}

		/* write to input ring-buffer */
		ierr = vdu_internal_ringbuf_write(pdev, ptask,
					psetindata->in_buffer,
					psetindata->in_buffersize);
		if (ierr < 0)
			goto done_1;
	}

	if (psetindata->in_eod) {
		/* end of stream data */
		DBG(pdev, "call vd_buffer_set_eod()\n");
		vdret = vd_buffer_set_eod(&ptask->ctx);
		DBG(pdev, "return vd_buffer_set_eod() [ret=%d]\n",
					vdret);
		if (vdret != VD_SUCCESS) {
			ERROR(pdev, "vd_buffer_set_eod() failed [err=%d]\n", vdret);
			ierr = -EVDUVDAPI;
			goto done_1;
		}
		ptask->tasksts = VDU_TASK_STAT_SET_EOD;
	} else {
		/* get input ring-buffer free size */
		ierr = vdu_internal_ringbuf_size(pdev, ptask,
				&psetindata->out_inbuf_max_size);
		if (ierr < 0)
			goto done_1;
	}

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_getoutframe(struct vdu_driver *pdev,
	struct vdec_getoutframe *pgetoutframe, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask = NULL;
	enum vd_result vdret;
	struct vd_frame_info info;
	uint32_t is_available;

	DBG(pdev, "enter\n");

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%x]\n", taskid);
		goto done_1;
	}

	if ((ptask->tasksts < VDU_TASK_STAT_START) ||
	    (ptask->tasksts > VDU_TASK_STAT_SET_EOD)) {
		ERROR(pdev, "illegal phase [taskid=%x][sts=%d]\n",
			taskid, ptask->tasksts);
		ierr = -ENODATA;
		goto done_1;
	}

	/* call vd_frame_is_available for VD_API */
	DBG(pdev, "call vd_frame_is_available()\n");
	ptask->task_int_outfrm = false;
	vdret = vd_frame_is_available(&ptask->ctx, &is_available);
	DBG(pdev, "return vd_frame_is_available() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_frame_is_available() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	if (!is_available) {
		pgetoutframe->out_is_available = 0;
		ierr = vdu_internal_wait_event(pdev, ptask,
				VDU_COND_OUTFRM, pgetoutframe->in_timeout);
		if (ierr < 0) {
			if (ierr == -EVDUTIMEDOUT)
				ierr = -EAGAIN;
			goto done_1;
		}
	}

	/* call vd_frame_get for VD_API */
	DBG(pdev, "call vd_frame_get()\n");
	vdret = vd_frame_get(&ptask->ctx, &info);
	DBG(pdev, "return vd_frame_get() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_frame_get() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	pgetoutframe->out_is_available = 1;
	vdu_internal_set_frame_info(pdev, ptask,
			&pgetoutframe->out_frame_info, &info);
	if (info.eod) {
		/* end of frame */
		ptask->tasksts = VDU_TASK_STAT_EOD;
	}

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_reloutframe(struct vdu_driver *pdev, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask;
	enum vd_result vdret;

	DBG(pdev, "enter\n");

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%x]\n", taskid);
		goto done_1;
	}

	if ((ptask->tasksts < VDU_TASK_STAT_START) ||
	    (ptask->tasksts > VDU_TASK_STAT_EOD)) {
		ERROR(pdev, "illegal phase [taskid=%x][sts=%d]\n",
			taskid, ptask->tasksts);
		ierr = -EVDUESTAT;
		goto done_1;
	}

	/* call vd_frame_release for VD_API */
	DBG(pdev, "call vd_frame_release()\n");
	vdret = vd_frame_release(&ptask->ctx);
	DBG(pdev, "return vd_frame_release() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_frame_release() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_waitforinbuf(struct vdu_driver *pdev,
	struct vdec_waitforinbuf *pwaitforinbuf, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask;
	uint32_t free_size;

	DBG(pdev, "enter\n");

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%x]\n", taskid);
		goto done_1;
	}

	if (ptask->tasksts != VDU_TASK_STAT_START) {
		ERROR(pdev, "illegal phase [taskid=%x][sts=%d]\n",
			taskid, ptask->tasksts);
		ierr = -EVDUESTAT;
		goto done_1;
	}

	/* get input ring-buffer free size */
	ptask->task_int_underflow = false;
	ierr = vdu_internal_ringbuf_size(pdev, ptask, &free_size);
	if (ierr < 0)
		goto done_1;
	/*
	 * 2.0M +-----------+ <-- vdu_task_std_size
	 *      | free_size |
	 * 1.5M +-----------+
	 *      |***********|
	 * 1.0M +-----------+ <-- uf_thr
	 *      |***********|
	 * 0.5M +-----------+
	 *      |***********|
	 * 0.0M +-----------+
	 */
	if ((pdev->vdu_task_std_size - free_size) < ptask->uf_thr) {
		pwaitforinbuf->out_inbuf_max_size = free_size;
		ierr = 0;
		goto done_1;
	}

	pwaitforinbuf->out_inbuf_max_size = 0;
	ierr = vdu_internal_wait_event(pdev, ptask,
			VDU_COND_INBUF, pwaitforinbuf->in_timeout);
	if (ierr < 0) {
		vdu_internal_ringbuf_size(pdev, ptask, &free_size);
		/*ERROR(pdev, "std=%d, uf_thr=%d, free=%d\n",
			pdev->vdu_task_std_size, ptask->uf_thr, free_size);*/
		goto done_1;
	}
	ierr = vdu_internal_ringbuf_size(pdev, ptask,
				&pwaitforinbuf->out_inbuf_max_size);
	if (ierr < 0)
		goto done_1;

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_waitforoutframe(struct vdu_driver *pdev,
	struct vdec_waitforoutframe *pwaitforoutframe, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask;
	struct vd_frame_info info;
	enum vd_result vdret;
	uint32_t is_available;

	DBG(pdev, "enter\n");

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%x]\n", taskid);
		goto done_1;
	}

	if ((ptask->tasksts < VDU_TASK_STAT_START) ||
	    (ptask->tasksts > VDU_TASK_STAT_SET_EOD)) {
		ERROR(pdev, "illegal phase [taskid=%x][sts=%d]\n",
			taskid, ptask->tasksts);
		ierr = -ENODATA;
		goto done_1;
	}

	/* call vd_frame_is_available for VD_API */
	DBG(pdev, "call vd_frame_is_available()\n");
	ptask->task_int_outfrm = false;
	vdret = vd_frame_is_available(&ptask->ctx, &is_available);
	DBG(pdev, "return vd_frame_is_available() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_frame_is_available() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	if (!is_available) {
		pwaitforoutframe->out_is_available = 0;
		ierr = vdu_internal_wait_event(pdev, ptask,
			VDU_COND_OUTFRM, pwaitforoutframe->in_timeout);
		if (ierr < 0)
			goto done_1;
	}

	/* call vd_frame_get for VD_API */
	DBG(pdev, "call vd_frame_get()\n");
	vdret = vd_frame_get(&ptask->ctx, &info);
	DBG(pdev, "return vd_frame_get() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_frame_get() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	pwaitforoutframe->out_is_available = 1;
	vdu_internal_set_frame_info(pdev, ptask,
			&pwaitforoutframe->out_frame_info, &info);
	if (info.eod) {
		/* end of frame */
		ptask->tasksts = VDU_TASK_STAT_EOD;
	}

done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_internal_cancel(struct vdu_driver *pdev, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask = NULL;

	DBG(pdev, "enter\n");

	if (!taskid)
		goto done_1;

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0)
		goto done_1;

	/* cancel task */
	vdu_internal_cancel_task(pdev, ptask);

done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return 0;
}


int vdu_internal_getoutframewithconv(struct vdu_driver *pdev,
	struct vdec_getoutframewithconv *psetinframe, uint32_t taskid)
{
	int ierr = 0;
	struct vdu_task *ptask;

	DBG(pdev, "enter\n");

	/* get struct vdu_task */
	ierr = vdu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%x]\n", taskid);
		goto done_1;
	}

	if ((ptask->tasksts > VDU_TASK_STAT_IDLE) &&
	    (ptask->tasksts < VDU_TASK_STAT_EOD)) {
		ERROR(pdev, "illegal phase [taskid=%x][sts=%d]\n",
			taskid, ptask->tasksts);
		ierr = -ENODATA;
		goto done_1;
	}

	ierr = vdu_internal_vconv(pdev, ptask, psetinframe);
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}


int vdu_internal_searchtask(struct vdu_driver *pdev, uint32_t taskid,
	struct vdu_task **rtask)
{
	int ierr = -EVDUBTSKID;
	struct vdu_task *ptask, *next;
	unsigned long flags;

	DBG(pdev, "enter\n");

	*rtask = NULL;

	spin_lock_irqsave(&pdev->splock, flags);
	list_for_each_entry_safe(ptask, next, &pdev->task_head, list) {
		if (taskid == (uint32_t)ptask) {
			*rtask = ptask;
			ierr = 0;
			break;
		}
	}
	spin_unlock_irqrestore(&pdev->splock, flags);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

void vdu_internal_irq_function(struct vdu_driver *pdev)
{
	struct vdu_task *ptask;
	uint32_t stat4, stat5, stat6, stat7;
	int i;

	/* read interrupt stat */
	reg_read_intr(&stat4, REG_MBOX1(pdev, REG104_SET_OFFS));
	reg_read_intr(&stat5, REG_MBOX1(pdev, REG105_SET_OFFS));
	reg_read_intr(&stat6, REG_MBOX1(pdev, REG106_SET_OFFS));
	reg_read_intr(&stat7, REG_MBOX1(pdev, REG107_SET_OFFS));

#if __DEBUG
	DBG(pdev, "stat4:0x%08x, stat5:0x%08x, stat6:0x%08x, stat7:0x%08x\n",
		stat4, stat5, stat6, stat7);
#endif
	/* stat4:frame available */
	if ((stat4&0x000000FF)) {
		for (i = 0; i < 8; i++) {
			if ((stat4>>i)&0x01) {
				if (!vdu_internal_searchtask_for_ch(pdev,
							i, &ptask)) {
					ptask->task_int_outfrm = true;
					set_bit(VDU_COND_OUTFRM,
						&ptask->wait_cond);
					wake_up_interruptible(&ptask->vdu_waitq);
				}
			}
		}
	}

	/* stat7:nearly underflow */
	if ((stat7&0x000000FF)) {
		for (i = 0; i < 8; i++) {
			if ((stat7>>i)&0x01) {
				if (!vdu_internal_searchtask_for_ch(pdev,
							i, &ptask)) {
					ptask->task_int_underflow = true;
					set_bit(VDU_COND_INBUF,
						&ptask->wait_cond);
					wake_up_interruptible(&ptask->vdu_waitq);
				}
			}
		}
	}

	/* stat6:task stop/start finish */
	if ((stat6&0x000000FF)) {
		for (i = 0; i < 8; i++) {
			if ((stat6>>i)&0x01) {
				if (!vdu_internal_searchtask_for_ch(pdev,
							i, &ptask)) {
					ptask->task_int_start_stop = true;
					set_bit(VDU_COND_TASK,
						&ptask->wait_cond);
#if 1
					wake_up(&ptask->vdu_waitq);
#else
					wake_up_interruptible(&ptask->vdu_waitq);
#endif
				}
			}
		}
	}

	/* stat5:BAP/VDP boot */
	if ((stat5&0x00000003)) {
		if ((stat5&0x00000001))
			pdev->fw_int_bap_boot = true;
		if ((stat5&0x00000002))
			pdev->fw_int_vdp_boot = true;
		if (pdev->fw_int_bap_boot && pdev->fw_int_vdp_boot) {
			set_bit(VDU_COND_FW, &pdev->wait_cond);
#if 1
			wake_up(&pdev->vdu_waitq);
#else
			wake_up_interruptible(&pdev->vdu_waitq);
#endif
		}
	}

	/* clear interrupt stat */
	if (stat4)
		reg_write_intr(stat4, REG_MBOX1(pdev, REG104_CLEAR_OFFS));
	if (stat5)
		reg_write_intr(stat5, REG_MBOX1(pdev, REG105_CLEAR_OFFS));
	if (stat6)
		reg_write_intr(stat6, REG_MBOX1(pdev, REG106_CLEAR_OFFS));
	if (stat7)
		reg_write_intr(stat7, REG_MBOX1(pdev, REG107_CLEAR_OFFS));
}

int vdu_internal_alloc_fwarea(struct vdu_driver *pdev)
{
	int ierr = 0;

	/* allocate VIP1 FW area */
	ierr = vdu_internal_memory_alloc(pdev, VDU_FW_AREA_SIZE,
		VDU_MEM_TYPE_DMA_FW, VDU_MEM_ALIGN_16M, &pdev->vd_fw_area);
	if (ierr != 0)
		return ierr;

	return ierr;
}

void vdu_internal_free_fwarea(struct vdu_driver *pdev)
{
	/* free VD_FW_AREA */
	vdu_internal_memory_free(pdev, &pdev->vd_fw_area);
}


static int vdu_internal_memory_alloc(
		struct vdu_driver *pdev,
		size_t size,
		enum vdu_mem_type type,
		enum vdu_mem_align align,
		struct vdu_locmem *pmem)
{
	int ierr = 0;
	int alloc_size;
	unsigned int align_mask;

	pmem->type = VDU_MEM_TYPE_NON;
	pmem->size = size;
	pmem->align = align;
	pmem->addr = 0;
	pmem->alloc_mem = 0;
	pmem->dma_addr = 0;

	DBG(pdev, "enter [type=%d][size=%d]\n", type, size);

	switch (type) {
	case VDU_MEM_TYPE_KALLOC:
		/* use kmalloc */
		align_mask = 0xffffffff << pmem->align;
		alloc_size = pmem->size + (~align_mask + 1);
		pmem->alloc_mem = (uint32_t)vdu_kmalloc(alloc_size);
		if (pmem->alloc_mem == 0) {
			ERROR(pdev, "kernel memory allocate failed [size=%d]\n",
				alloc_size);
			ierr = -ENOMEM;
			goto done_1;
		}
		if (~align_mask&pmem->alloc_mem) {
			pmem->addr = pmem->alloc_mem + (~align_mask + 1);
			pmem->addr &= align_mask;
		} else {
			pmem->addr = pmem->alloc_mem;
		}
		pmem->type = VDU_MEM_TYPE_KALLOC;
		break;

	case VDU_MEM_TYPE_DMA:
		/* use dma_alloc_coherent */
		pmem->alloc_mem = (uint32_t)dma_alloc_coherent(
			NULL,
			pmem->size,
			&pmem->dma_addr,
			GFP_KERNEL|GFP_DMA);
		if (pmem->alloc_mem == 0) {
			ERROR(pdev, "dma memory allocate failed [size=%d]\n",
				pmem->size);
			ierr = -ENOMEM;
			goto done_1;
		}
		/*printk("[dma_alloc_coherent(1)]:0x%08X\n",pmem->alloc_mem);*/
		memset((void *)pmem->alloc_mem, 0x00, pmem->size);
		pmem->addr = pmem->alloc_mem;
		pmem->type = VDU_MEM_TYPE_DMA;
		DBG(pdev, "VDU_MEM_TYPE_DMA:v=0x%08x p=0x%08x sz=%d\n",
			(u32)pmem->addr, (u32)pmem->dma_addr, pmem->size);
		break;

	case VDU_MEM_TYPE_DMA_FW:
		/* use dma_alloc_coherent */
		pmem->alloc_mem = (uint32_t)dma_alloc_coherent(
			pdev->device,
			pmem->size,
			&pmem->dma_addr,
			GFP_KERNEL|GFP_DMA);
		/*printk("[dma_alloc_coherent(2)]:0x%08X\n",pmem->alloc_mem);*/
		if (pmem->alloc_mem == 0) {
			ERROR(pdev, "dma memory allocate failed [size=%d]\n",
				pmem->size);
			ierr = -ENOMEM;
			goto done_1;
		}
		memset((void *)pmem->alloc_mem, 0x00, pmem->size);
		pmem->addr = pmem->alloc_mem;
		pmem->type = VDU_MEM_TYPE_DMA_FW;
		DBG(pdev, "VDU_MEM_TYPE_DMA_FW:v=0x%08x p=0x%08x sz=%d\n",
			(u32)pmem->addr, (u32)pmem->dma_addr, pmem->size);
		break;

	case VDU_MEM_TYPE_MA:
		if (pmem->fd < 0) {
			ERROR(pdev, "illegal memory allocator fd [fd=%d]\n",
				pmem->fd);
			ierr = -ENOMEM;
			goto done_1;
		}
		pmem->dbuf = dma_buf_get(pmem->fd);
		if (IS_ERR(pmem->dbuf)) {
			ERROR(pdev, "dma_buf_get() failed [fd=%d]\n",
				pmem->fd);
			ierr = -ENOMEM;
			goto done_1;
		}
		pmem->dbufa = dma_buf_attach(pmem->dbuf, pdev->device);
		if (IS_ERR(pmem->dbufa)) {
			ERROR(pdev, "dma_buf_attach() failed [fd=%d]\n",
				pmem->fd);
			dma_buf_put(pmem->dbuf);
			ierr = -ENOMEM;
			goto done_1;
		}
		pmem->psgt = dma_buf_map_attachment(pmem->dbufa, DMA_TO_DEVICE);
		if (IS_ERR_OR_NULL(pmem->psgt)) {
			ERROR(pdev, "dma_buf_map_attachment() failed [fd=%d]\n",
				pmem->fd);
			ierr = -ENOMEM;
			dma_buf_detach(pmem->dbuf, pmem->dbufa);
			dma_buf_put(pmem->dbuf);
			goto done_1;
		}
		pmem->alloc_mem = (uint32_t)phys_to_virt(sg_dma_address(pmem->psgt->sgl));
		/*printk("[ma_alloc]:0x%08X\n",pmem->alloc_mem);*/
		pmem->dma_addr =
			(dma_addr_t)sg_dma_address(pmem->psgt->sgl);
		pmem->addr = pmem->alloc_mem;
		pmem->type = VDU_MEM_TYPE_MA;
		DBG(pdev, "VDU_MEM_TYPE_MA:v=0x%08x p=0x%08x\n",
			(u32)pmem->addr, (u32)pmem->dma_addr);
		break;

	case VDU_MEM_TYPE_NON:
		pr_err("%s : dma memory allocate failed [size=%d]\n",
			VDU_DEVICE_NAME, pmem->size);
		ierr = -ENOMEM;
		goto done_1;
	}

	ierr = 0;
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static void vdu_internal_memory_free(
		struct vdu_driver *pdev,
		struct vdu_locmem *pmem)
{
	DBG(pdev, "enter\n");

	switch (pmem->type) {
	case VDU_MEM_TYPE_KALLOC:
		vdu_kfree((void *)pmem->alloc_mem);
		break;
	case VDU_MEM_TYPE_DMA:
		DBG(pdev, "VDU_MEM_TYPE_DMA:v=0x%08x p=0x%08x sz=%d\n",
			(u32)pmem->addr, (u32)pmem->dma_addr, pmem->size);
		/*printk("[dma_free_coherent(1) ]:0x%08X\n",pmem->alloc_mem);*/
		dma_free_coherent(NULL, pmem->size, (void *)pmem->alloc_mem,
			pmem->dma_addr);
		break;
	case VDU_MEM_TYPE_DMA_FW:
		DBG(pdev, "VDU_MEM_TYPE_DMA_FW:v=0x%08x p=0x%08x sz=%d\n",
			(u32)pmem->addr, (u32)pmem->dma_addr, pmem->size);
		/*printk("[dma_free_coherent(2) ]:0x%08X\n",pmem->alloc_mem);*/
		dma_free_coherent(pdev->device, pmem->size,
			(void *)pmem->alloc_mem, pmem->dma_addr);
		break;
	case VDU_MEM_TYPE_MA:
		DBG(pdev, "VDU_MEM_TYPE_MA:v=0x%08x p=0x%08x",
			(u32)pmem->addr, (u32)pmem->dma_addr);
		/*printk("[ma_free ]:0x%08X\n",pmem->alloc_mem);*/
		dma_buf_unmap_attachment(pmem->dbufa, pmem->psgt, DMA_TO_DEVICE);
		dma_buf_detach(pmem->dbuf, pmem->dbufa);
		dma_buf_put(pmem->dbuf);
		break;

	case VDU_MEM_TYPE_NON:
		break;
	}
	pmem->type = VDU_MEM_TYPE_NON;
	pmem->size = 0;
	pmem->align = 0;
	pmem->addr = 0;
	pmem->alloc_mem = 0;
	pmem->dma_addr = 0;
	pmem->fd = -1;

	DBG(pdev, "leave\n");
}

static int vdu_internal_ringbuf_size(struct vdu_driver *pdev,
	struct vdu_task *ptask, uint32_t *psize)
{
	int ierr = 0;
	enum vd_result vdret;
	struct vd_ring_buffer_info info;
	uint32_t size1 = 0;
	uint32_t size2 = 0;
	unsigned long flags;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	/* call vd_buffer_get_info for VD_API */
	DBG(pdev, "call vd_buffer_get_info()\n");
	vdret = vd_buffer_get_info(&ptask->ctx, &info);
	DBG(pdev, "return vd_buffer_get_info() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_buffer_get_info() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	DBG(pdev, "sp=%08X, ep=%08X, rp=%08X, wp=%08X\n",
		info.sp, info.ep, info.rp, info.wp);

	if (info.rp > info.wp) {
		size1 = info.rp - info.wp - 1;
		size2 = 0;
	} else {
		if (info.rp == info.sp) {
			size1 = info.ep - info.wp - 1;
			size2 = 0;
		} else {
			size1 = info.ep - info.wp;
			size2 = info.rp - info.sp - 1;
		}
	}
	ierr = 0;
done_1:
	*psize = size1 + size2;
	spin_unlock_irqrestore(&pdev->splock, flags);
	DBG(pdev, "leave [occupancy=%d][rtn=%d]\n", *psize, ierr);
	return ierr;
}

static int vdu_internal_ringbuf_write(struct vdu_driver *pdev,
		struct vdu_task *ptask, uint32_t write_buf,
		uint32_t write_size)
{
	int ierr = 0;
	enum vd_result vdret;
	struct vd_address setwp;
	struct vd_ring_buffer_info info;
	uint32_t size1 = 0;
	uint32_t size2 = 0;
	char *wp1 = NULL;
	char *wp2 = NULL;
	int wsize;
	unsigned long flags;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	/* call vd_buffer_get_info for VD_API */
	DBG(pdev, "call vd_buffer_get_info()\n");
	vdret = vd_buffer_get_info(&ptask->ctx, &info);
	DBG(pdev, "return vd_buffer_get_info() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_buffer_get_info() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}

	DBG(pdev, "sp=%08X, ep=%08X, rp=%08X, wp=%08X\n",
		info.sp, info.ep, info.rp, info.wp);

	if (info.rp > info.wp) {
		size1 = info.rp - info.wp - 1;
		size2 = 0;
		if (size1)
			wp1 = (char *)phys_to_virt(info.wp);
	} else {
		if (info.rp == info.sp) {
			size1 = info.ep - info.wp - 1;
			size2 = 0;
		} else {
			size1 = info.ep - info.wp;
			size2 = info.rp - info.sp - 1;
		}
		if (size1)
			wp1 = (char *)phys_to_virt(info.wp);
		if (size2)
			wp2 = (char *)phys_to_virt(info.sp);
	}

	setwp.p_addr = info.wp;
	setwp.v_addr = (vd_virtual_t)phys_to_virt(setwp.p_addr);
	if (size1 && wp1) {
		if (write_size > size1)
			wsize = (int)size1;
		else
			wsize = (int)write_size;
		DBG(pdev, "[1]copy %08X->%08X, %d\n",
			write_buf, (uint32_t)wp1, wsize);
		if (copy_from_user((void *)wp1, (const void __user *)write_buf, wsize)) {
			ERROR(pdev, "copy_from_user() failed [user addr=%08X][kernel addr=%08X][size=%d]\n",
				(u32)write_buf, (u32)wp1, (u32)wsize);
			ierr = -EFAULT;
			goto done_1;
		}
		write_size -= wsize;
		write_buf += wsize;
		setwp.p_addr = info.wp + wsize;
		if (setwp.p_addr == info.ep)
			setwp.p_addr = info.sp;
		setwp.v_addr = (vd_virtual_t)phys_to_virt(setwp.p_addr);
	}
	if (!write_size)
		goto set_wp;

	if (size2 && wp2) {
		if (write_size > size2)
			wsize = (int)size2;
		else
			wsize = (int)write_size;
		DBG(pdev, "[1]copy %08X->%08X, %d\n",
			write_buf, (uint32_t)wp2, wsize);
		if (copy_from_user((void *)wp2, (const void __user *)write_buf, wsize)) {
			ERROR(pdev, "copy_from_user() failed [user addr=%08X][kernel addr=%08X][size=%d]\n",
				(u32)write_buf, (u32)wp2, (u32)wsize);
			ierr = -EFAULT;
			goto done_1;
		}
		setwp.p_addr = info.sp + wsize;
		setwp.v_addr =  (vd_virtual_t)phys_to_virt(setwp.p_addr);
	}

set_wp:
	/* call vd_buffer_set_wp for VD_API */
	DBG(pdev, "call vd_buffer_set_wp(v=%08X,p=%08X)\n",
		setwp.v_addr, setwp.p_addr);
	vdret = vd_buffer_set_wp(&ptask->ctx, &setwp);
	DBG(pdev, "return vd_buffer_set_wp() [ret=%d]\n", vdret);
	if (vdret != VD_SUCCESS) {
		ERROR(pdev, "vd_buffer_set_wp() failed [err=%d]\n", vdret);
		ierr = -EVDUVDAPI;
		goto done_1;
	}
	ierr = 0;
done_1:
	spin_unlock_irqrestore(&pdev->splock, flags);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}
static void vdu_internal_set_frame_info(struct vdu_driver *pdev,
	struct vdu_task *ptask, struct vdec_frame_info *vdec_info,
	struct vd_frame_info *info)
{
	uint32_t offset;
	DBG(pdev, "enter\n");

	/* set frame storage info */
	vdec_info->outbuffer.fd = ptask->vd_task_frame.fd;
	offset = info->addr -
		vdu_internal_phys_to_vdu(ptask->vd_task_frame.dma_addr);
	DBG(pdev, "info.addr=0x%08x, vd_task_frame=0x%08x(tail=0x%08x)\n",
		info->addr, ptask->vd_task_frame.dma_addr,
		vdu_internal_phys_to_vdu(ptask->vd_task_frame.dma_addr));
	vdec_info->outbuffer.offset = offset;
	DBG(pdev, "offset=0x%08x\n", vdec_info->outbuffer.offset);

	vdec_info->id0[0] = info->id0[0];
	vdec_info->id0[1] = info->id0[1];
	vdec_info->id1[0] = info->id1[0];
	vdec_info->id1[1] = info->id1[1];
	vdec_info->width = info->width;
	vdec_info->height = info->height;
	vdec_info->crop_top = info->crop_top;
	vdec_info->crop_bottom = info->crop_bottom;
	vdec_info->crop_left = info->crop_left;
	vdec_info->crop_right = info->crop_right;
	vdec_info->num_units_in_tick = info->num_units_in_tick;
	vdec_info->time_scale = info->time_scale;
	vdec_info->sar_width = info->sar_width;
	vdec_info->sar_height = info->sar_height;
	vdec_info->interlaced = info->interlaced;
	vdec_info->eod = info->eod;

	DBG(pdev, "leave\n");
	return;
}

static int vdu_internal_wait_event(struct vdu_driver *pdev,
	struct vdu_task *ptask, int condition, int timeout)
{
	int ierr = 0;
	enum vd_fw_state fw_state;
	unsigned long flags;

	DBG(pdev, "enter [event=%d][timeout=%d]\n", condition, timeout);

	spin_lock_irqsave(&pdev->splock, flags);

	switch (condition) {
	case VDU_COND_FW:
		if (pdev->fw_int_bap_boot && pdev->fw_int_vdp_boot) {
			ierr = 0;
			goto done_1;
		}
		if (!timeout) {
			ierr = -EVDUTIMEDOUT;
			goto done_1;
		}
		clear_bit(VDU_COND_FW, &pdev->wait_cond);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (timeout < 0) {
			wait_event(
				pdev->vdu_waitq,
				test_bit(VDU_COND_FW, &pdev->wait_cond)
			);
		} else {
			wait_event_timeout(
				pdev->vdu_waitq,
				test_bit(VDU_COND_FW, &pdev->wait_cond),
				msecs_to_jiffies(timeout)
			);
		}
		DBG(pdev, "VDU_COND_FW:wait_cond=%08X\n", (u32)pdev->wait_cond);
		if (0) {
			ierr = -EINTR;
		} else {
			if (test_bit(VDU_COND_FW, &pdev->wait_cond))
				ierr = 0;
			else
				ierr = -EVDUTIMEDOUT;
		}
		break;

	case VDU_COND_TASK:
		if (ptask->task_int_start_stop) {
			ierr = 0;
			goto done_1;
		}
		if (!timeout) {
			ierr = -EVDUTIMEDOUT;
			goto done_1;
		}
		clear_bit(VDU_COND_TASK, &ptask->wait_cond);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (timeout < 0) {
			wait_event(
				ptask->vdu_waitq,
				test_bit(VDU_COND_TASK, &ptask->wait_cond)
			);
		} else {
			wait_event_timeout(
				ptask->vdu_waitq,
				test_bit(VDU_COND_TASK, &ptask->wait_cond),
				msecs_to_jiffies(timeout)
			);
		}
		DBG(pdev, "VDU_COND_TASK:wait_cond=%08X\n", (u32)ptask->wait_cond);
		if (0) {
			ierr = -EINTR;
		} else {
			if (test_bit(VDU_COND_TASK, &ptask->wait_cond))
				ierr = 0;
			else
				ierr = -EVDUTIMEDOUT;
		}
		break;

	case VDU_COND_OUTFRM:
		if (ptask->task_int_outfrm) {
			ierr = 0;
			goto done_1;
		}
		if (!timeout) {
			ierr = -EVDUTIMEDOUT;
			goto done_1;
		}
		clear_bit(VDU_COND_OUTFRM, &ptask->wait_cond);
		clear_bit(VDU_COND_CANCEL, &ptask->wait_cond);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (timeout < 0)
			wait_event_interruptible(
				ptask->vdu_waitq,
				test_bit(VDU_COND_OUTFRM, &ptask->wait_cond)
			);
		else
			wait_event_interruptible_timeout(
				ptask->vdu_waitq,
				test_bit(VDU_COND_OUTFRM, &ptask->wait_cond),
				msecs_to_jiffies(timeout)
			);
		if (signal_pending(current)) {
			ierr = -EINTR;
		} else if (test_bit(VDU_COND_CANCEL, &ptask->wait_cond)) {
			ierr = -EVDUCANCEL;
		} else {
			if (test_bit(VDU_COND_OUTFRM, &ptask->wait_cond))
				ierr = 0;
			else
				ierr = -EVDUTIMEDOUT;
		}
		break;

	case VDU_COND_INBUF:
		if (ptask->task_int_underflow) {
			ierr = 0;
			goto done_1;
		}
		if (!timeout) {
			ierr = -EVDUTIMEDOUT;
			goto done_1;
		}
		clear_bit(VDU_COND_INBUF, &ptask->wait_cond);
		clear_bit(VDU_COND_CANCEL, &ptask->wait_cond);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (timeout < 0)
			wait_event_interruptible(
				ptask->vdu_waitq,
				test_bit(VDU_COND_INBUF, &ptask->wait_cond)
			);
		else
			wait_event_interruptible_timeout(
				ptask->vdu_waitq,
				test_bit(VDU_COND_INBUF, &ptask->wait_cond),
				msecs_to_jiffies(timeout)
			);
		if (signal_pending(current)) {
			ierr = -EINTR;
		} else if (test_bit(VDU_COND_CANCEL, &ptask->wait_cond)) {
			ierr = -EVDUCANCEL;
		} else {
			if (test_bit(VDU_COND_INBUF, &ptask->wait_cond))
				ierr = 0;
			else
				ierr = -EVDUTIMEDOUT;
		}
		break;
	}
#if __DEBUG
	if (ierr) {
		uint32_t stat4, stat5, stat6, stat7;
		reg_read(&stat4, REG_MBOX1(pdev, REG104_SET_OFFS));
		reg_read(&stat5, REG_MBOX1(pdev, REG105_SET_OFFS));
		reg_read(&stat6, REG_MBOX1(pdev, REG106_SET_OFFS));
		reg_read(&stat7, REG_MBOX1(pdev, REG107_SET_OFFS));
		DBG(pdev, "REG104_SET=%08X REG105_SET=%08X REG106_SET=%08X REG107_SET=%08X\n", stat4, stat5, stat6, stat7);
	}
#endif
	vd_fw_get_state(0, &fw_state); /* update stat */

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

done_1:
	spin_unlock_irqrestore(&pdev->splock, flags);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static int vdu_internal_searchtask_for_ch(struct vdu_driver *pdev, int32_t ch,
	struct vdu_task **rtask)
{
	int ierr = -EVDUBTSKID;
	struct vdu_task *ptask, *next;
	/*unsigned long flags;*/

	/*DBG(pdev, "enter [ch=%d]\n", ch);*/

	*rtask = NULL;

	/*spin_lock_irqsave(&pdev->splock, flags);*/
	list_for_each_entry_safe(ptask, next, &pdev->task_head, list) {
		if (ptask->ch_num == ch) {
			*rtask = ptask;
			ierr = 0;
			break;
		}
	}
	/*spin_unlock_irqrestore(&pdev->splock, flags);*/

	/*DBG(pdev, "leave [rtn=%d]\n", ierr);*/
	return ierr;
}

static uint32_t vdu_internal_phys_to_vdu(uint32_t phys)
{
	return (phys & 0xE0000000) | ((phys & 0x1FF00000) >> 10);
}

static void vdapi_lock(void *lock)
{
	spin_lock_irqsave((spinlock_t *)lock, vdapi_lock_flags);
}

static void vdapi_unlock(void *lock)
{
	spin_unlock_irqrestore((spinlock_t *)lock, vdapi_lock_flags);
}

static int vdu_internal_vconv(struct vdu_driver *pdev,
	struct vdu_task *ptask, struct vdec_getoutframewithconv *pparam)
{
	int ierr = 0;
	struct file *filp;

	DBG(pdev, "enter\n");

	filp = filp_open(VCONV_DEVICE_FILE, O_RDONLY, 0600);
	if (IS_ERR(filp)) {
		ERROR(pdev, "vconv driver open failed [file=%s]\n",
			VCONV_DEVICE_FILE);
		ierr = -EVDUVCONV;
		goto done_1;
	}

	if (filp->f_op->unlocked_ioctl(filp,
			IOC_VCONV_START,
			(unsigned long)&pparam->in_vconv_param) < 0) {
		ERROR(pdev, "vconv driver IOC_VCONV_START failed\n");
		ierr = -EVDUVCONV;
		goto done_2;
	}
	filp_close(filp, NULL);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

done_2:
	filp_close(filp, NULL);
done_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}
