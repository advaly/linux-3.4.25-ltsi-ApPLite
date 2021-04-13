/*
 * drivers/staging/applite/veu/applite_veu_internal.c
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
#include <linux/io.h>
#include <asm/processor.h>
#include <linux/uaccess.h>
#include <asm/pgtable.h>
#include <asm/dma.h>
#include <asm/segment.h>
#include <linux/buffer_head.h>
#include <asm/cacheflush.h>

#include <linux/applite/applite_veu.h>
#include "applite_veu_internal.h"
#include "applite_veu_common.h"

#include <linux/applite/applitema.h>

/*===================================
Static Variables and Functions prototypes
===================================*/

extern struct veu_driver s_veu_dev;

static spinlock_t veapi_splock;
static unsigned long veapi_lock_flags;
static int veapi_fw_size;
static struct veu_locmem ve_fw_area = {
	.type = VEU_MEM_TYPE_NON
};
static struct veu_locmem ve_comm_area = {
	.type = VEU_MEM_TYPE_NON
};
static struct veu_locmem ve_trace_area = {
	.type = VEU_MEM_TYPE_NON
};
static struct file *memfilp;

static int veu_internal_clear_events(struct veu_driver *, struct veu_task *);
static int veu_internal_map_ma(struct veu_driver *, struct venc_shmem *,
	ve_vtile_t *, struct sg_table **);
static void veu_internal_unmap_ma(struct veu_driver *, int, struct sg_table *);
static int veu_internal_memory_alloc(struct veu_driver *, struct device *,
	size_t, enum veu_mem_type, enum veu_mem_align, struct veu_locmem *);
static void veu_internal_memory_free(struct veu_driver *, struct device *,
	struct veu_locmem *);
static int veu_internal_start_encode(struct veu_driver *);
static int veu_internal_finished_encode(struct veu_driver *);
static int veu_internal_abort_encode(struct veu_driver *, struct veu_task *);
static void veu_internal_sleep(long);
static int veu_internal_naloutsize(struct veu_driver *, struct veu_task *,
	struct ve_output_entry *);
static int veu_internal_nalout(struct veu_driver *, struct veu_task *,
	uint32_t, uint32_t *, struct ve_output_entry *);
static enum ve_frame_rate veu_internal_ve_fps(enum venc_frame_rate);
static enum venc_frame_rate veu_internal_venc_fps(enum ve_frame_rate);
static enum ve_profile veu_internal_ve_profile(enum venc_profile); /* 20130410A */
static void veu_internal_add_event(struct veu_driver *, struct veu_task *,
	enum veu_event_code, uint64_t, int);
static uint32_t veu_internal_phys_to_veu(uint32_t phys);
static void veapi_lock(void *);
static void veapi_unlock(void *);
static int veu_internal_vconv(struct veu_driver *,
		struct veu_task *, struct veu_enc *);
static int veu_internal_response_result(struct veu_driver *, struct veu_task *,
		unsigned long, struct ve_response *); /* 20130410A */
static int veu_internal_searchtask_for_ctx(struct veu_driver *,
		struct ve_task *, struct veu_task **); /* 20130410A */
static char *veu_internal_to_str(unsigned long); /* 20130410A */


/*===================================
Global Variables and Functions prototypes
===================================*/

/*===================================
Macros
===================================*/

/*===================================
Function Definitions
===================================*/
#ifdef NOFWDWN
static int local_request_firmware(struct veu_driver *pdev,
		const struct firmware **rfw, const char *name,
		struct device *device)
{
	struct file *file;
	char path[512];
	mm_segment_t oldfs;
	size_t size = 160 * 1024;
	unsigned long long offset;
	struct firmware *fw = kzalloc(sizeof(struct firmware), GFP_KERNEL);
	if (!fw)
		return -100;
	fw->data = kzalloc(size, GFP_KERNEL);
	if (!fw->data) {
		kfree(fw);
		return -101;
	}

	snprintf(path, 512, "/lib/firmware/%s", name);

	oldfs = get_fs();
	set_fs(get_ds());
	file = filp_open(path, O_RDONLY, 0600);
	set_fs(oldfs);
	if (IS_ERR(file)) {
		kfree(fw->data);
		kfree(fw);
		return -2;
	}

	oldfs = get_fs();
	set_fs(get_ds());
	offset = 0;
	fw->size = vfs_read(file, (char *)fw->data, size, &offset);
	DBG(pdev, "local_request_firmware():read size=%d\n", fw->size);
	set_fs(oldfs);

	filp_close(file, NULL);

	*rfw = fw;

	return 0;
}
static void local_release_firmware(const struct firmware *fw)
{
	kfree(fw->data);
	kfree(fw);
}
#endif

/*===================================
Module source
===================================*/

int veu_internal_init_resource(struct veu_driver *pdev)
{
	int ierr = 0;
	uint32_t v;

	DBG(pdev, "enter\n");

	INIT_LIST_HEAD(&pdev->task_head);
	INIT_LIST_HEAD(&pdev->ma_head);
	INIT_LIST_HEAD(&pdev->resp_head); /* 20130410A */
	pdev->task_num = 0;
	pdev->resp_num = 0; /* 20130410A */
	pdev->ma_num = 0;
	veapi_fw_size = 0;

	/* clear memory area */
#ifndef __KEEP_FWAREA
	ve_fw_area.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ve_fw_area);
#endif
	ve_comm_area.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ve_comm_area);
	memfilp = NULL;

	/* reset on */
	/*veu_internal_vip4_reset(pdev, 1);*/

	/* setup mbox */
	reg_write(0, REG_MBOX5(pdev, REG500_MASK_OFFS));
	reg_read(&v, REG_MBOX5(pdev, REG500_MASK_OFFS));
	reg_write(0, REG_MBOX5(pdev, REG501_MASK_OFFS));
	reg_read(&v, REG_MBOX5(pdev, REG501_MASK_OFFS));
	reg_write(0, REG_MBOX1(pdev, REG108_MASK_OFFS));
	reg_read(&v, REG_MBOX1(pdev, REG108_MASK_OFFS));

	reg_write(MBOX_INT_REG500_CLEAR_CLEAR_BIT,
		REG_MBOX5(pdev, REG500_CLEAR_OFFS));
	reg_read(&v, REG_MBOX5(pdev, REG500_CLEAR_OFFS));
	reg_write(MBOX_INT_REG501_CLEAR_CLEAR_BIT,
		REG_MBOX5(pdev, REG501_CLEAR_OFFS));
	reg_read(&v, REG_MBOX5(pdev, REG501_CLEAR_OFFS));
	reg_write(MBOX_INT_REG101_CLEAR_CLEAR_BIT,
		REG_MBOX1(pdev, REG108_CLEAR_OFFS));
	reg_read(&v, REG_MBOX1(pdev, REG108_CLEAR_OFFS));

	DBG(pdev, "leave [rtn=%d]\n", ierr);

	return ierr;
}

void veu_internal_clear_resource(struct veu_driver *pdev)
{
	unsigned long flags;
	struct veu_task *ptask, *tnext;
	struct veu_response *presp, *rnext;
	struct veu_enc *penc, *enext;
	struct veu_event *pevt, *vnext;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	/* clear struct veu_task */
	list_for_each_entry_safe(ptask, tnext, &pdev->task_head, list) {
		list_del(&ptask->list);
		/* clear struct veu_enc */
		list_for_each_entry_safe(penc, enext,
			&ptask->encoding_head, list) {
			list_del(&penc->list);
			spin_unlock_irqrestore(&pdev->splock, flags);
			veu_internal_unmap_ma(pdev, penc->fd_luma,
				penc->sgt_luma);
			veu_internal_unmap_ma(pdev, penc->fd_chroma,
				penc->sgt_chroma);
			spin_lock_irqsave(&pdev->splock, flags);
			kfree(penc);
		}
		list_for_each_entry_safe(penc, enext,
			&ptask->encoded_head, list) {
			list_del(&penc->list);
			spin_unlock_irqrestore(&pdev->splock, flags);
			veu_internal_unmap_ma(pdev, penc->fd_luma,
				penc->sgt_luma);
			veu_internal_unmap_ma(pdev, penc->fd_chroma,
				penc->sgt_chroma);
			spin_lock_irqsave(&pdev->splock, flags);
			kfree(penc);
		}
		/* clear struct veu_event */
		list_for_each_entry_safe(pevt, vnext,
			&ptask->encfin_head, list) {
			list_del(&pevt->list);
			kfree(pevt);
		}
		list_for_each_entry_safe(pevt, vnext,
			&ptask->nal_head, list) {
			list_del(&pevt->list);
			kfree(pevt);
		}
		list_for_each_entry_safe(pevt, vnext,
			&ptask->rel_head, list) {
			list_del(&pevt->list);
			kfree(pevt);
		}
		/* clear struct veu_response */ /* 20130410A */
		list_for_each_entry_safe(presp, rnext,
			&ptask->resp_head, list) {
			list_del(&presp->list);
			kfree(presp);
		}

		spin_unlock_irqrestore(&pdev->splock, flags);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_task_api);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_task_fw);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_ctl);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_out);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_inf);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_wrk);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_ref);
		spin_lock_irqsave(&pdev->splock, flags);
		kfree(ptask);
	}

	/* clear struct veu_response */ /* 20130410A */
	list_for_each_entry_safe(presp, rnext, &pdev->resp_head, list) {
		list_del(&presp->list);
		kfree(presp);
	}

	spin_unlock_irqrestore(&pdev->splock, flags);

	DBG(pdev, "leave\n");
}

int veu_internal_fw_download(struct veu_driver *pdev)
{
	int ierr = 0;
	int32_t fw_size;
	u8 *fw_addr;
	const struct firmware *fw;

	DBG(pdev, "enter\n");

#ifndef __KEEP_FWAREA
	/* allocate VIP4 FW area */
	ierr = veu_internal_memory_alloc(pdev, pdev->device, VEU_FW_AREA_SIZE,
		VEU_MEM_TYPE_DMA_FW, VEU_MEM_ALIGN_16M, &ve_fw_area);
	if (ierr != 0)
		goto fail_1;
#endif

	/* read VIP4 FW image */
#ifndef NOFWDWN
	ierr = request_firmware(&fw, VEU_VIP4_FW_NAME, pdev->device);
#else
	ierr = local_request_firmware(pdev, &fw, VEU_VIP4_FW_NAME, pdev->device);
#endif
	if (ierr < 0) {
		ERROR(pdev, "request_firmware() failed [fw=%s][err=%d]\n",
			VEU_VIP4_FW_NAME, ierr);
		goto fail_1;
	}
	DBG(pdev, "fw size=%d\n", (int32_t)fw->size);

	/* copy to firmware */
	fw_size = (int32_t)fw->size;
	veapi_fw_size = fw_size;
	fw_addr = (u_char *)fw->data;
	DBG(pdev, "copy to fw [0x%x->0x%x:%d]\n",
		(uint32_t)fw_addr, (uint32_t)ve_fw_area.addr, veapi_fw_size);
	memcpy((void *)ve_fw_area.addr, fw_addr, veapi_fw_size);

#ifndef NOFWDWN
	release_firmware(fw);
#else
	local_release_firmware(fw);
#endif

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_initialize(struct veu_driver *pdev)
{
	int ierr = 0;
	int resp_res;
	struct ve_accessor accessor;
	struct ve_address fw_address;
	struct ve_buf comm_area;
	struct ve_buf trace_area;
	struct ve_response resp;
	uint32_t fw_state;
	uint32_t api_version, api_build;
	uint32_t fw_version, fw_build;
	enum ve_result veret;
	int32_t retry;
	unsigned long flags;

	DBG(pdev, "enter\n");

	/* initialize VIP4 */
	spin_lock_init(&veapi_splock);

	/* call ve_initialize_api for VE_API */
	accessor.lock  = (void(*)(void *))veapi_lock;
	accessor.unlock = (void(*)(void *))veapi_unlock;
	accessor.private_data = &veapi_splock;

	accessor.to_vip4.set.p_addr = ADDR_MBOX5(pdev, REG500_SET_OFFS);
	accessor.to_vip4.set.v_addr = REG_MBOX5(pdev, REG500_SET_OFFS);
	accessor.to_vip4.clear.p_addr = ADDR_MBOX5(pdev, REG500_CLEAR_OFFS);
	accessor.to_vip4.clear.v_addr = REG_MBOX5(pdev, REG500_CLEAR_OFFS);
	accessor.to_vip4.mask.p_addr = ADDR_MBOX5(pdev, REG500_MASK_OFFS);
	accessor.to_vip4.mask.v_addr = REG_MBOX5(pdev, REG500_MASK_OFFS);
	accessor.to_vip4.selector.p_addr = ADDR_MBOX5(pdev, SIG50_SEL_OFFS);
	accessor.to_vip4.selector.v_addr = REG_MBOX5(pdev, SIG50_SEL_OFFS);

	accessor.from_vip4.set.p_addr = ADDR_MBOX1(pdev, REG108_SET_OFFS);
	accessor.from_vip4.set.v_addr = REG_MBOX1(pdev, REG108_SET_OFFS);
	accessor.from_vip4.clear.p_addr = ADDR_MBOX1(pdev, REG108_CLEAR_OFFS);
	accessor.from_vip4.clear.v_addr = REG_MBOX1(pdev, REG108_CLEAR_OFFS);
	accessor.from_vip4.mask.p_addr = ADDR_MBOX1(pdev, REG108_MASK_OFFS);
	accessor.from_vip4.mask.v_addr = REG_MBOX1(pdev, REG108_MASK_OFFS);
	accessor.from_vip4.selector.p_addr = ADDR_MBOX1(pdev, SIG12_SEL_OFFS);
	accessor.from_vip4.selector.v_addr = REG_MBOX1(pdev, SIG12_SEL_OFFS);

	accessor.to_vip4_nmi.set.p_addr = ADDR_MBOX5(pdev, REG501_SET_OFFS);
	accessor.to_vip4_nmi.set.v_addr = REG_MBOX5(pdev, REG501_SET_OFFS);
	accessor.to_vip4_nmi.clear.p_addr = ADDR_MBOX5(pdev, REG501_CLEAR_OFFS);
	accessor.to_vip4_nmi.clear.v_addr = REG_MBOX5(pdev, REG501_CLEAR_OFFS);
	accessor.to_vip4_nmi.mask.p_addr = ADDR_MBOX5(pdev, REG501_MASK_OFFS);
	accessor.to_vip4_nmi.mask.v_addr = REG_MBOX5(pdev, REG501_MASK_OFFS);
	accessor.to_vip4_nmi.selector.p_addr = ADDR_MBOX5(pdev, SIG51_SEL_OFFS);
	accessor.to_vip4_nmi.selector.v_addr = REG_MBOX5(pdev, SIG51_SEL_OFFS);

	accessor.veu0_addrconf0 = REG_ECONF(pdev, VEU0_ADDRCONF0_OFFS);
	accessor.veu0_addrconf1 = REG_ECONF(pdev, VEU0_ADDRCONF1_OFFS);
	accessor.reset_on_vcodec = REG_PMU(pdev, SoftResetOn_vcodecSS_0_OFFS);

	fw_address.p_addr = (ve_physical_t)ve_fw_area.dma_addr;
	fw_address.v_addr = (ve_virtual_t)ve_fw_area.addr;

	/* allocate memory for VE_COMM_AREA */
	ierr = veu_internal_memory_alloc(pdev, pdev->device, VEU_COMM_AREA_SIZE,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_8, &ve_comm_area);
	if (ierr != 0)
		goto fail_1;
	comm_area.addr.p_addr = (ve_physical_t)ve_comm_area.dma_addr;
	comm_area.addr.v_addr = (ve_virtual_t)ve_comm_area.addr;
	comm_area.size = VEU_COMM_AREA_SIZE;

	DBG(pdev, "call ve_initialize_api()\n");
	DBG(pdev, "      [to_vip4.set=%08x:%x08]\n",
		accessor.to_vip4.set.p_addr, accessor.to_vip4.set.v_addr);
	DBG(pdev, "      [to_vip4.clear=%08x:%x08]\n",
		accessor.to_vip4.clear.p_addr, accessor.to_vip4.clear.v_addr);
	DBG(pdev, "      [to_vip4.mask=%08x:%x08]\n",
		accessor.to_vip4.mask.p_addr, accessor.to_vip4.mask.v_addr);
	DBG(pdev, "      [to_vip4.selector=%08x:%x08]\n",
		accessor.to_vip4.selector.p_addr, accessor.to_vip4.selector.v_addr);
	DBG(pdev, "      [from_vip4.set=%08x:%x08]\n",
		accessor.from_vip4.set.p_addr, accessor.from_vip4.set.v_addr);
	DBG(pdev, "      [from_vip4.clear=%08x:%x08]\n",
		accessor.from_vip4.clear.p_addr, accessor.from_vip4.clear.v_addr);
	DBG(pdev, "      [from_vip4.mask=%08x:%x08]\n",
		accessor.from_vip4.mask.p_addr, accessor.from_vip4.mask.v_addr);
	DBG(pdev, "      [from_vip4.selector=%08x:%x08]\n",
		accessor.from_vip4.selector.p_addr, accessor.from_vip4.selector.v_addr);
	DBG(pdev, "      [to_vip4_nmi.set=%08x:%x08]\n",
		accessor.to_vip4_nmi.set.p_addr, accessor.to_vip4_nmi.set.v_addr);
	DBG(pdev, "      [to_vip4_nmi.clear=%08x:%x08]\n",
		accessor.to_vip4_nmi.clear.p_addr, accessor.to_vip4_nmi.clear.v_addr);
	DBG(pdev, "      [to_vip4_nmi.mask=%08x:%x08]\n",
		accessor.to_vip4_nmi.mask.p_addr, accessor.to_vip4_nmi.mask.v_addr);
	DBG(pdev, "      [to_vip4_nmi.selector=%08x:%x08]\n",
		accessor.to_vip4_nmi.selector.p_addr, accessor.to_vip4_nmi.selector.v_addr);
	DBG(pdev, "      [addrconf=%08x:%x08]\n",
		accessor.veu0_addrconf0, accessor.veu0_addrconf1);
	DBG(pdev, "      [reset_on_vcodec=%08x]\n",
		accessor.reset_on_vcodec);
	DBG(pdev, "      [fw_addr=%08x:%08x]\n",
		fw_address.p_addr, fw_address.v_addr);
	DBG(pdev, "      [comm_area=%08x:%08x(%d)]\n",
		comm_area.addr.p_addr, comm_area.addr.v_addr, comm_area.size);

	veret = ve_initialize_api(&accessor, &fw_address, &comm_area);
	if (veret != VE_OK) {
		ERROR(pdev, "ve_initialize_api() failed [err=%d]\n", veret);
		ierr = -EVEUVEAPI;
		goto fail_1;
	}
	DBG(pdev, "return ve_initialize_api()\n");

	if (ve_trace_area.size &&
	    ve_trace_area.addr &&
	    ve_trace_area.dma_addr) {
		DBG(pdev, "call ve_set_trace_log_buf()\n");
		trace_area.addr.p_addr = (ve_physical_t)ve_trace_area.dma_addr;
		trace_area.addr.v_addr = (ve_virtual_t)ve_trace_area.addr;
		trace_area.size = ve_trace_area.size;
		veret = ve_set_trace_log_buf(&trace_area, 0);
		if (veret != VE_OK) {
			ERROR(pdev, "ve_set_trace_log_buf() failed [err=%d]\n", veret);
			ierr = -EVEUVEAPI;
			goto fail_1;
		}
	}

	/* call ve_get_xxx_version for VE_API */
	veret = ve_get_api_version(&api_version, &api_build);
	if (veret == VE_OK)
		pr_info("%s : EV_API Version = %d Build = %d\n",
			VEU_DEVICE_NAME, api_version, api_build);
	veret = ve_get_fw_version(&fw_version, &fw_build);
	if (veret == VE_OK)
		pr_info("%s : FW  Version = %d Build = %d\n",
			VEU_DEVICE_NAME, fw_version, fw_build);

	/* reset off */
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	DBG(pdev, "pm_runtime_get_sync call\n");
	pm_runtime_get_sync(&(pdev->pdev->dev));
#else
	DBG(pdev, "vcodec_power_up\n");
	vcodec_power_up();			/* video power on */
	DBG(pdev, "veu_internal_vip4_reset off\n");
	veu_internal_vip4_reset(pdev, 0);	/* VIP4 reset off */
#endif

	/* call ve_start_up_pu for VE_API */
	retry = VEU_VEAPI_RETRY_MAX;
	clear_bit(VEU_COND_START_UP_PU, &pdev->wait_cond);
	while (retry--) {
		DBG(pdev, "call ve_start_up_pu()\n");
		veret = ve_start_up_pu(0);
		DBG(pdev, "return ve_start_up_pu() [ret=%d]\n", veret);
		if (veret != VE_OK) {
			if (veret == VE_ERROR_MBOX_BUSY) {
				veu_internal_sleep(VEU_VEAPI_RETRY_TIME);
				DBG(pdev, "retry ve_start_up_pu()\n");
				continue;
			}
			ERROR(pdev, "ve_start_up_pu() failed [err=%d]\n",
				veret);
			ierr = -EVEUVEAPI;
			goto fail_3;
		}
rewait:
		DBG(pdev, "call wait_event_timeout()\n");
		wait_event_timeout(pdev->veu_waitq,
			test_bit(VEU_COND_START_UP_PU, &pdev->wait_cond),
			VEU_VEAPI_RSP_TIMEOUT);
		DBG(pdev, "return wait_event_timeout() [cond=%d]\n",
			(s32)pdev->wait_cond);
		if (!test_bit(VEU_COND_START_UP_PU, &pdev->wait_cond)) {
			ERROR(pdev, "ve_start_up_pu() timeout\n");
			ierr = -EVEUTIMEDOUT;
			goto fail_3;
		}
		clear_bit(VEU_COND_START_UP_PU, &pdev->wait_cond);
		/* 20130410A */
		spin_lock_irqsave(&pdev->splock, flags);
		resp_res = veu_internal_response_result(pdev,
				NULL, VEU_COND_START_UP_PU, &resp);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (resp_res) {
			/* rewait */
			goto rewait;
		}
		if (resp.param[0]) {
			ERROR(pdev, "ve_start_up_pu() response error\n");
			ierr = -EVEUVEAPI;
			goto fail_3;
		}
		break;
	}
	if (veret == VE_ERROR_MBOX_BUSY) {
		/* retry over */
		ERROR(pdev, "ve_start_up_pu() retry over\n");
		ierr = -EVEURETRYOVER;
		goto fail_3;
	}

	/* call ve_get_fw_state for VE_API */
	DBG(pdev, "call ve_get_fw_state()\n");
	veret = ve_get_fw_state(&fw_state, 0);
	if (veret != VE_OK) {
		ERROR(pdev, "ve_get_fw_state() failed [err=%d]\n", veret);
		ierr = -EVEUVEAPI;
		goto fail_2;
	}
	if (fw_state != VE_FW_STATE_READY) {
		ERROR(pdev, "VIP4 FW status error [state=%d]\n", fw_state);
		ierr = -EVEUVEAPI;
		goto fail_2;
	}

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
fail_3:
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	DBG(pdev, "pm_runtime_put_sync call\n");
	pm_runtime_put_sync(&(pdev->pdev->dev));
#else
	DBG(pdev, "veu_internal_vip4_reset on\n");
	veu_internal_vip4_reset(pdev, 1);	/* VIP4 reset on */
	DBG(pdev, "vcodec_power_down\n");
	vcodec_power_down();			/* video power off */
#endif
	goto fail_1;
fail_2:
	veu_internal_finalize(pdev);
fail_1:
#ifndef __KEEP_FWAREA
	veu_internal_memory_free(pdev, pdev->device, &ve_fw_area);
#endif
	veu_internal_memory_free(pdev, pdev->device, &ve_comm_area);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_finalize(struct veu_driver *pdev)
{
	int ierr = 0;
	int resp_res;
	struct ve_response resp;
	enum ve_result veret;
	int retry;
	unsigned long flags;

	DBG(pdev, "enter\n");

	/* call ve_shut_down_pu for VE_API */
	retry = VEU_VEAPI_RETRY_MAX;
	clear_bit(VEU_COND_SHUT_DOWN_PU, &pdev->wait_cond);
	while (retry--) {
		DBG(pdev, "call ve_shut_down_pu()\n");
		veret = ve_shut_down_pu(0);
		DBG(pdev, "return ve_shut_down_pu() [ret=%d]\n", veret);
		if (veret != VE_OK) {
			if (veret == VE_ERROR_MBOX_BUSY) {
				veu_internal_sleep(VEU_VEAPI_RETRY_TIME);
				continue;
			}
			ERROR(pdev, "ve_shut_down_pu() failed [err=%d]\n",
				veret);
			ierr = -EVEUVEAPI;
			goto fail_1;
		}
rewait:
		wait_event_timeout(pdev->veu_waitq,
			test_bit(VEU_COND_SHUT_DOWN_PU, &pdev->wait_cond),
			VEU_VEAPI_RSP_TIMEOUT);
		if (!test_bit(VEU_COND_SHUT_DOWN_PU, &pdev->wait_cond)) {
			ERROR(pdev, "ve_shut_down_pu() timeout\n");
			ierr = -EVEUTIMEDOUT;
			goto fail_1;
		}
		clear_bit(VEU_COND_SHUT_DOWN_PU, &pdev->wait_cond);
		/* 20130410A */
		spin_lock_irqsave(&pdev->splock, flags);
		resp_res = veu_internal_response_result(pdev,
				NULL, VEU_COND_SHUT_DOWN_PU, &resp);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (resp_res) {
			/* rewait */
			goto rewait;
		}
		if (resp.param[0]) {
			ERROR(pdev, "ve_shut_down_pu() response error\n");
			ierr = -EVEUVEAPI;
			goto fail_1;
		}
		break;
	}
	if (veret == VE_ERROR_MBOX_BUSY) {
		/* retry over */
		ERROR(pdev, "ve_start_up_pu() retry over\n");
		ierr = -EVEURETRYOVER;
		goto fail_1;
	}

	/* reset on */
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	DBG(pdev, "pm_runtime_put_sync call\n");
	pm_runtime_put_sync(&(pdev->pdev->dev));
#else
	DBG(pdev, "veu_internal_vip4_reset on\n");
	veu_internal_vip4_reset(pdev, 1);	/* VIP4 reset on */
	DBG(pdev, "vcodec_power_down\n");
	vcodec_power_down();			/* video power off */
#endif

	/* call ve_finalize_api for VE_API */
	DBG(pdev, "call ve_finalize_api()\n");
	veret = ve_finalize_api();
	if (veret != VE_OK) {
		ERROR(pdev, "ve_finalize_api() failed [err=%d]\n", veret);
		ierr = -EVEUVEAPI;
		goto fail_2;
	}
	DBG(pdev, "return ve_finalize_api()\n");

	/* free VE_FW_AREA & VE_COMM_AREA */
#ifndef __KEEP_FWAREA
	veu_internal_memory_free(pdev, pdev->device, &ve_fw_area);
#endif
	veu_internal_memory_free(pdev, pdev->device, &ve_comm_area);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	/* reset on */
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	DBG(pdev, "pm_runtime_put_sync call\n");
	pm_runtime_put_sync(&(pdev->pdev->dev));
#else
	DBG(pdev, "veu_internal_vip4_reset on\n");
	veu_internal_vip4_reset(pdev, 1);	/* VIP4 reset on */
	DBG(pdev, "vcodec_power_down\n");
	vcodec_power_down();			/* video power off */
#endif
fail_2:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_cretask(struct veu_driver *pdev, uint32_t *rtaskid)
{
	int ierr = 0;
	int resp_res;
	enum ve_result veret;
	struct ve_response resp;
	uint32_t api_area;
	uint32_t fw_area;
	struct ve_task_work_area tsk_wk;
	struct veu_task *ptask = NULL;
	unsigned long flags;
	int retry;

	DBG(pdev, "enter\n");

	/* create struct veu_task */
	ptask = kmalloc(sizeof(struct veu_task), GFP_KERNEL);
	if (!ptask) {
		ERROR(pdev, "kernel memory allocate failed [struct veu_task][size=%d]\n",
			sizeof(struct veu_task));
		ierr = -ENOMEM;
		goto fail_1;
	}
	memset(ptask, 0x00, sizeof(*ptask));
	ptask->ctx = NULL;
	ptask->ve_task_api.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_task_api);
	ptask->ve_task_fw.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_task_fw);
	ptask->ve_buf_ctl.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_ctl);
	ptask->ve_buf_out.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_out);
	ptask->ve_buf_inf.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_inf);
	ptask->ve_buf_wrk.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_wrk);
	ptask->ve_buf_ref.type = VEU_MEM_TYPE_NON;
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_ref);

	INIT_LIST_HEAD(&ptask->resp_head); /* 20130410A */
	INIT_LIST_HEAD(&ptask->encoding_head);
	INIT_LIST_HEAD(&ptask->encoded_head);
	INIT_LIST_HEAD(&ptask->encfin_head);
	INIT_LIST_HEAD(&ptask->nal_head);
	INIT_LIST_HEAD(&ptask->rel_head);
	veu_com_frameid_clear(&ptask->frameid_tbl);
	init_waitqueue_head(&ptask->task_waitq);
	ptask->wait_cond = 0;
	ptask->is_eos = 0;

	/* call ve_get_task_requirements for VE_API */
	DBG(pdev, "call ve_get_task_requirements()\n");
	veret = ve_get_task_requirements(&api_area, &fw_area);
	if (veret != VE_OK) {
		ERROR(pdev, "ve_get_task_requirements() failed [err=%d]\n",
			veret);
		ierr = -EVEUVEAPI;
		goto fail_1;
	}
	DBG(pdev, "return ve_get_task_requirements() [api_area=%d][fw_area=%d]\n", api_area, fw_area);

	/* allocate memory for the task work area */
	ierr = veu_internal_memory_alloc(pdev, pdev->device, api_area,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_64, &ptask->ve_task_api);
	if (ierr != 0)
		goto fail_1;
	ierr = veu_internal_memory_alloc(pdev, pdev->device, fw_area,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_8, &ptask->ve_task_fw);
	if (ierr != 0)
		goto fail_1;

	/* call ve_create_task for VE_API */
	tsk_wk.api = (uint32_t *)ptask->ve_task_api.addr;
	tsk_wk.fw.p_addr = (ve_physical_t)ptask->ve_task_fw.dma_addr;
	tsk_wk.fw.v_addr = (ve_virtual_t)ptask->ve_task_fw.addr;
	tsk_wk.reserved  = 0;
	DBG(pdev, "call ve_create_task() [api=%x][fw.p_addr=%x][fw.v_addr=%x]\n",
		(uint32_t)tsk_wk.api, tsk_wk.fw.p_addr, tsk_wk.fw.v_addr);
	veret = ve_create_task(&ptask->ctx, &tsk_wk, ptask);
	if (veret != VE_OK) {
		ERROR(pdev, "ve_create_task() failed [err=%d]\n", veret);
		ierr = -EVEUVEAPI;
		goto fail_1;
	}
	DBG(pdev, "return ve_create_task()\n");

	/* queuing to device table */ /* 20130410A */
	spin_lock_irqsave(&pdev->splock, flags);
	list_add_tail(&ptask->list, &pdev->task_head);
	pdev->task_num++;
	spin_unlock_irqrestore(&pdev->splock, flags);

	/* call ve_send_initialize_task_cmd for VE_API */
	retry = VEU_VEAPI_RETRY_MAX;
	clear_bit(VEU_COND_INITIALIZE_TASK, &ptask->wait_cond);
	while (retry--) {
		DBG(pdev, "call ve_send_initialize_task_cmd()\n");
		veret = ve_send_initialize_task_cmd(ptask->ctx, 0);
		if (veret != VE_OK) {
			if (veret == VE_ERROR_MBOX_BUSY) {
				veu_internal_sleep(VEU_VEAPI_RETRY_TIME);
				continue;
			}
			ERROR(pdev, "ve_send_initialize_task_cmd() failed [err=%d]\n", veret);
			ierr = -EVEUVEAPI;
			goto fail_2;
		}
rewait:
		DBG(pdev, "call wait_event_timeout()\n");
		wait_event_timeout(ptask->task_waitq,
			test_bit(VEU_COND_INITIALIZE_TASK, &ptask->wait_cond),
			VEU_VEAPI_RSP_TIMEOUT);
		DBG(pdev, "return wait_event_timeout() [cond=%d]\n",
			(s32)ptask->wait_cond);
		if (!test_bit(VEU_COND_INITIALIZE_TASK, &ptask->wait_cond)) {
			ERROR(pdev, "ve_send_initialize_task_cmd() timeout\n");
			ierr = -EVEUTIMEDOUT;
			goto fail_2;
		}
		clear_bit(VEU_COND_INITIALIZE_TASK, &ptask->wait_cond);
		/* 20130410A */
		spin_lock_irqsave(&pdev->splock, flags);
		resp_res = veu_internal_response_result(pdev,
				ptask, VEU_COND_INITIALIZE_TASK, &resp);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (resp_res) {
			/* rewait */
			goto rewait;
		}
		if (resp.param[0]) {
			ERROR(pdev, "ve_send_initialize_task_cmd() response error\n");
			ierr = -EVEUVEAPI;
			goto fail_2;
		}
		break;
	}
	if (veret == VE_ERROR_MBOX_BUSY) {
		/* retry over */
		ERROR(pdev, "ve_send_initialize_task_cmd() retry over\n");
		ierr = -EVEURETRYOVER;
		goto fail_2;
	}


	*rtaskid = (uint32_t)ptask;
	DBG(pdev, "leave [rtn=%d]\n", ierr);

	return ierr;

fail_2:
	spin_lock_irqsave(&pdev->splock, flags);
	list_del(&ptask->list);
	pdev->task_num++;
	spin_unlock_irqrestore(&pdev->splock, flags);
fail_1:
	if (ptask) {
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_task_api);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_task_fw);
		kfree(ptask);
	}
	*rtaskid = 0;
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_killtask(struct veu_driver *pdev, uint32_t taskid)
{
	int ierr = 0;
	enum ve_result veret;
	struct veu_task *ptask;
	uint32_t task_state;
	int isabort;
	int isdestroy;
	int isloop;
	int retry;
	unsigned long flags;

	DBG(pdev, "enter\n");

	/* get struct veu_task */
	spin_lock_irqsave(&pdev->splock, flags);
	ierr = veu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ierr = 0;
		goto fail_2;
	}
	spin_unlock_irqrestore(&pdev->splock, flags);

	isloop = 1;
	retry = VEU_VEAPI_RETRY_MAX;
	while (isloop) {
		/* call ve_get_task_state */
		veret = ve_get_task_state(ptask->ctx, &task_state);
		if (veret != VE_OK) {
			ERROR(pdev, "ve_get_task_state() failed [err=%d]\n",
				veret);
			goto fail_1;
		}
		pr_info("%s : task state = 0x%08x\n", VEU_DEVICE_NAME, task_state);
		switch (task_state) {
		case VE_TASK_INITIALIZING_TASK:
		case VE_TASK_INITIALIZING_IOBUFFER:
			if (!retry) {
				ERROR(pdev, "initialize process retry over\n");
				isabort = 0;
				isdestroy = 0;
				isloop = 0;	/* loop end */
			} else {
				/* wait response */
				veu_internal_sleep(VEU_VEAPI_RETRY_TIME);
				retry--;
			}
			break;
		case VE_TASK_WAIT_FOR_FRAME:
		case VE_TASK_ENCODING:
		case VE_TASK_FLUSHING:
		case VE_TASK_WAIT_FOR_FLUSH:
			/* abort task */
			isabort = 1;
			isdestroy = 0;
			isloop = 0;	/* loop end */
			break;
		case VE_TASK_UNINITIALIZED:
		case VE_TASK_PREPARED:
		case VE_TASK_FINISHED:
			/* destroy task */
			isabort = 0;
			isdestroy = 1;
			isloop = 0;	/* loop end */
			break;
		default:
			isabort = 0;
			isdestroy = 0;
			isloop = 0;	/* loop end */
			break;
		}
	}

	if (isabort) {
		/* abort encode */
		ierr = veu_internal_abort_encode(pdev, ptask);
		/*if (ierr < 0)
			goto fail_1;*/
	}

	/* clear events */
	ierr = veu_internal_clear_events(pdev, ptask);
	if (ierr < 0)
		goto fail_1;

	if (isdestroy) {
		/* call ve_destroy_task for VE_API */
		DBG(pdev, "call ve_destroy_task()\n");
		veret = ve_destroy_task(ptask->ctx);
		if (veret != VE_OK) {
			ERROR(pdev, "ve_destroy_task() failed [err=%d]\n",
				veret);
			/*ierr = -EVEUVEAPI;*/
			/*goto fail_1;*/
		}
		DBG(pdev, "return ve_destroy_task()\n");
	}

	/* delete struct veu_task */
	spin_lock_irqsave(&pdev->splock, flags);
	list_del(&ptask->list);
	spin_unlock_irqrestore(&pdev->splock, flags);

	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_task_api);
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_task_fw);
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_ctl);
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_out);
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_inf);
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_wrk);
	veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_ref);
	kfree(ptask);
	pdev->task_num--;

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_2:
	spin_unlock_irqrestore(&pdev->splock, flags);
fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_getparam(struct veu_driver *pdev,
	struct venc_getparam *pgetparam, uint32_t taskid)
{
	int ierr = 0;
	enum ve_result veret;
	enum ve_frame_rate fps;
	enum ve_profile profile; /* 20130410A */
	struct veu_task *ptask = NULL;
	unsigned long flags;

	DBG(pdev, "enter\n");

	/* get struct veu_task */
	spin_lock_irqsave(&pdev->splock, flags);
	ierr = veu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%d]\n", taskid);
		goto fail_1;
	}
	spin_unlock_irqrestore(&pdev->splock, flags);

	/* call ve_calc_default_param for VE_API */
	fps = veu_internal_ve_fps(pgetparam->in_fps);
	profile = veu_internal_ve_profile(pgetparam->in_profile); /* 20130410A */
	DBG(pdev, "call ve_calc_default_param()\n");
	veret = ve_calc_default_param(&ptask->param,
		pgetparam->in_horizontal_pixels,
		pgetparam->in_vertical_pixels,
		pgetparam->in_kbps,
		fps,
		profile); /* 20130410A */
	if (veret != VE_OK) {
		ERROR(pdev, "ve_calc_default_param() failed [err=%d]\n",
			veret);
		ierr = -EVEUVEAPI;
		goto fail_2;
	}
	DBG(pdev, "return ve_calc_default_param()\n");

	dparam(&ptask->param);

	/* set return parameter */
	memcpy(&pgetparam->out_param, &ptask->param,
		sizeof(pgetparam->out_param));
	pgetparam->out_param.fps = veu_internal_venc_fps(
		ptask->param.frame_rate);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	spin_unlock_irqrestore(&pdev->splock, flags);
fail_2:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_setparam(struct veu_driver *pdev,
	struct venc_setparam *psetparam, uint32_t taskid)
{
	int ierr = 0;
	int resp_res;
	enum ve_result veret;
	struct ve_response resp;
	struct ve_io_buf_area io_buf;
	struct veu_task *ptask = NULL;
	unsigned long flags;
	int retry;

	DBG(pdev, "enter\n");

	/* get struct veu_task */
	spin_lock_irqsave(&pdev->splock, flags);
	ierr = veu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%d]\n", taskid);
		goto fail_2;
	}
	spin_unlock_irqrestore(&pdev->splock, flags);

	/* set encode parameter */
	memcpy(&ptask->param, psetparam, sizeof(ptask->param));
	ptask->param.frame_rate = veu_internal_ve_fps(psetparam->fps);

	dparam(&ptask->param);

	/* call ve_calc_io_buf_requirements for VE_API */
	DBG(pdev, "call ve_calc_io_buf_requirements()\n");
	veret = ve_calc_io_buf_requirements(&io_buf, &ptask->param);
	if (veret != VE_OK) {
		ERROR(pdev, "ve_calc_io_buf_requirements() failed [err=%d]\n",
			veret);
		ierr = -EVEUVEAPI;
		goto fail_1;
	}
	DBG(pdev, "return ve_calc_io_buf_requirements() [ve_buf_ctl=%d][ve_buf_out=%d][ve_buf_inf=%d][ve_buf_wrk=%d][ve_buf_ref=%d]\n",
		io_buf.control.size, io_buf.output.size,
		io_buf.nal.size, io_buf.work.size, io_buf.reference.size);

	/* allocate memory for io buf */
	ierr = veu_internal_memory_alloc(pdev, pdev->device, io_buf.control.size,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_64, &ptask->ve_buf_ctl);
	if (ierr != 0)
		goto fail_1;
	ierr = veu_internal_memory_alloc(pdev, pdev->device, io_buf.output.size,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_16, &ptask->ve_buf_out);
	if (ierr != 0)
		goto fail_1;
	ierr = veu_internal_memory_alloc(pdev, pdev->device, io_buf.nal.size,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_16, &ptask->ve_buf_inf);
	if (ierr != 0)
		goto fail_1;
	ierr = veu_internal_memory_alloc(pdev, pdev->device, io_buf.work.size,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_16, &ptask->ve_buf_wrk);
	if (ierr != 0)
		goto fail_1;
	ierr = veu_internal_memory_alloc(pdev, pdev->device, io_buf.reference.size,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_2M, &ptask->ve_buf_ref);
	if (ierr != 0)
		goto fail_1;

	io_buf.control.addr.p_addr = (ve_physical_t)ptask->ve_buf_ctl.dma_addr;
	io_buf.control.addr.v_addr = (ve_virtual_t)ptask->ve_buf_ctl.addr;
	io_buf.output.addr.p_addr = (ve_physical_t)ptask->ve_buf_out.dma_addr;
	io_buf.output.addr.v_addr = (ve_virtual_t)ptask->ve_buf_out.addr;
	io_buf.nal.addr.p_addr = (ve_physical_t)ptask->ve_buf_inf.dma_addr;
	io_buf.nal.addr.v_addr = (ve_virtual_t)ptask->ve_buf_inf.addr;
	io_buf.work.addr.p_addr = (ve_physical_t)ptask->ve_buf_wrk.dma_addr;
	io_buf.work.addr.v_addr = (ve_virtual_t)ptask->ve_buf_wrk.addr;
	io_buf.reference.addr = (ve_physical_t)veu_internal_phys_to_veu(
		(uint32_t)ptask->ve_buf_ref.dma_addr);
	ptask->tail_ve_buf_ref = (uint32_t)io_buf.reference.addr;

	/* call ve_create_io_buf for VE_API */
	DBG(pdev, "call ve_create_io_buf() [ctl=%x:%x][out=%x:%x][inf=%x:%x][work=%x:%x][ref=%x]\n",
		(uint32_t)io_buf.control.addr.p_addr,
		(uint32_t)io_buf.control.addr.v_addr,
		(uint32_t)io_buf.output.addr.p_addr,
		(uint32_t)io_buf.output.addr.v_addr,
		(uint32_t)io_buf.nal.addr.p_addr,
		(uint32_t)io_buf.nal.addr.v_addr,
		(uint32_t)io_buf.work.addr.p_addr,
		(uint32_t)io_buf.work.addr.v_addr,
		(uint32_t)io_buf.reference.addr);
	veret = ve_create_io_buf(ptask->ctx, &io_buf);
	if (veret != VE_OK) {
		ERROR(pdev, "ve_create_io_buf() failed [err=%d]\n", veret);
		ierr = -EVEUVEAPI;
		goto fail_1;
	}
	DBG(pdev, "return ve_create_io_buf()\n");

	/* call ve_send_resources_cmd for VE_API */
	retry = VEU_VEAPI_RETRY_MAX;
	clear_bit(VEU_COND_INITIALIZE_IOBUFFER, &ptask->wait_cond);
	while (retry--) {
		DBG(pdev, "call ve_send_resources_cmd()\n");
		veret = ve_send_resources_cmd(ptask->ctx, &ptask->param, 0);
		if (veret != VE_OK) {
			if (veret == VE_ERROR_MBOX_BUSY) {
				veu_internal_sleep(VEU_VEAPI_RETRY_TIME);
				continue;
			}
			ERROR(pdev, "ve_send_resources_cmd() failed [err=%d]\n", veret);
			ierr = -EVEUVEAPI;
			goto fail_1;
		}
		DBG(pdev, "return ve_send_resources_cmd()\n");
rewait:
		wait_event_timeout(ptask->task_waitq,
			test_bit(VEU_COND_INITIALIZE_IOBUFFER,
				&ptask->wait_cond),
			VEU_VEAPI_RSP_TIMEOUT);
		if (!test_bit(VEU_COND_INITIALIZE_IOBUFFER,
				&ptask->wait_cond)) {
			ERROR(pdev, "ve_send_resources_cmd() timeout\n");
			ierr = -EVEUTIMEDOUT;
			goto fail_1;
		}
		clear_bit(VEU_COND_INITIALIZE_IOBUFFER, &ptask->wait_cond);
		/* 20130410A */
		spin_lock_irqsave(&pdev->splock, flags);
		resp_res = veu_internal_response_result(pdev,
				ptask, VEU_COND_INITIALIZE_IOBUFFER, &resp);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (resp_res) {
			/* rewait */
			goto rewait;
		}
		if (resp.param[0]) {
			ERROR(pdev, "ve_send_resources_cmd() response error\n");
			ierr = -EVEUVEAPI;
			goto fail_1;
		}
		break;
	}
	if (veret == VE_ERROR_MBOX_BUSY) {
		/* retry over */
		ierr = -EVEURETRYOVER;
		goto fail_1;
	}

	/* set out-buffer address */
	ptask->outbuf_b = (char *)ptask->ve_buf_out.addr;
	ptask->outbuf_e = (char *)(ptask->ve_buf_out.addr +
		ptask->ve_buf_out.size);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_2:
	spin_unlock_irqrestore(&pdev->splock, flags);
fail_1:
	if (ptask) {
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_ctl);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_out);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_inf);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_wrk);
		veu_internal_memory_free(pdev, pdev->device, &ptask->ve_buf_ref);
	}
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_setinframe(struct veu_driver *pdev,
	struct venc_setinframe *psetinframe, uint32_t taskid)
{
	int ierr = 0;
	struct veu_task *ptask;
	struct veu_enc *newenc = NULL;
	unsigned long flags;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	/* search task */
	ierr = veu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%d]\n", taskid);
		goto fail_1;
	}

	/* create struct veu_enc */
	newenc = kmalloc(sizeof(struct veu_enc), GFP_KERNEL);
	if (!newenc) {
		ierr = -ENOMEM;
		goto fail_1;
	}
	newenc->fd_luma = -1;
	newenc->fd_chroma = -1;
	newenc->sgt_luma = NULL;
	newenc->sgt_chroma = NULL;
	newenc->retry = 0;
	newenc->withconv_enable = 0; /* disable with conv */
	if ((psetinframe->in_lumainputbuf.fd == VENC_INVALID_FRAME_ID) ||
	    (psetinframe->in_chromainputbuf.fd == VENC_INVALID_FRAME_ID))
		newenc->flush = 1;
	else
		newenc->flush = 0;

	newenc->encsts = VEU_ENC_STAT_WAITING;
	ierr = veu_internal_map_ma(pdev, &psetinframe->in_lumainputbuf,
		&newenc->pic.luma, &newenc->sgt_luma);
	if (ierr != 0)
		goto fail_1;
	newenc->fd_luma = psetinframe->in_lumainputbuf.fd;
	ierr = veu_internal_map_ma(pdev, &psetinframe->in_chromainputbuf,
		&newenc->pic.chroma, &newenc->sgt_chroma);
	if (ierr != 0)
		goto fail_1;
	newenc->fd_chroma = psetinframe->in_chromainputbuf.fd;
	newenc->pic.frame_id = psetinframe->in_frameid;
	if (psetinframe->in_sync_frame == 0) {
		/* no attribute */
		newenc->pic.attribute = VE_PIC_NOTHING;
	} else if (psetinframe->in_sync_frame == 1) {
		/* sync frame */
		newenc->pic.attribute = VE_PIC_SYNC_FRAME;
	} else {
		/* no attribute */
		WARN(pdev, "illegal in_sync_frame(%d)\n",
			psetinframe->in_sync_frame);
		newenc->pic.attribute = VE_PIC_NOTHING;
	}

	/* check MSB */
	if ((psetinframe->in_lumainputbuf.fd != VENC_INVALID_FRAME_ID) &&
	    (psetinframe->in_chromainputbuf.fd != VENC_INVALID_FRAME_ID)) {
		if ((newenc->pic.luma&0xc0000000) !=
			 (ptask->tail_ve_buf_ref&0xc0000000)) {
			ERROR(pdev, "illegal input luma buffer address [ref=%08x][buf=%08x]\n",
				ptask->tail_ve_buf_ref, newenc->pic.luma);
			goto fail_1;
		}
		if ((newenc->pic.chroma&0xc0000000) !=
			(ptask->tail_ve_buf_ref&0xc0000000)) {
			ERROR(pdev, "illegal input chroma buffer address [ref=%08x][buf=%08x]\n",
				ptask->tail_ve_buf_ref, newenc->pic.chroma);
			goto fail_1;
		}
	}

	/* queuing to struct veu_task */
	list_add_tail(&newenc->list, &ptask->encoding_head);

	if (pdev->devsts < VEU_STAT_RUNNING) {
		/* scheduling tasklet */
		tasklet_schedule(&pdev->veu_tasklet);
	}

	spin_unlock_irqrestore(&pdev->splock, flags);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	spin_unlock_irqrestore(&pdev->splock, flags);
	if (newenc) {
		if (newenc->sgt_luma)
			veu_internal_unmap_ma(pdev, newenc->fd_luma,
				newenc->sgt_luma);
		if (newenc->sgt_chroma)
			veu_internal_unmap_ma(pdev, newenc->fd_chroma,
				newenc->sgt_chroma);
		kfree(newenc);
	}
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_waitforevents(struct veu_driver *pdev,
	struct venc_waitforevents *pwaitforevents, uint32_t taskid)
{
	int ierr = 0;
	int events = 0;
	struct veu_task *ptask;
	unsigned long flags;
	struct veu_event *pevt_encoded = NULL;
	struct veu_event *pevt_nalout = NULL;
	struct veu_event *pevt_release = NULL;

	DBG(pdev, "enter\n");

	pwaitforevents->out_encframeid = VENC_INVALID_FRAME_ID;
	pwaitforevents->out_encresult = 0;
	pwaitforevents->out_outframeid = VENC_INVALID_FRAME_ID;
	pwaitforevents->out_outsize = 0;
	pwaitforevents->out_relframeid = VENC_INVALID_FRAME_ID;

	spin_lock_irqsave(&pdev->splock, flags);

	/* get struct veu_task */
	ierr = veu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%d]\n", taskid);
		goto fail_1;
	}

	while (1) {
		/* get events */
		if (!list_empty(&ptask->encfin_head)) {
			/* encoded events */
			pevt_encoded = list_entry(ptask->encfin_head.next,
				struct veu_event, list);
			list_del(&pevt_encoded->list);
			DBG(pdev, "encoded events [id=%lld][res=%d]\n",
				pevt_encoded->frameid,
				pevt_encoded->result);
			pwaitforevents->out_encframeid = pevt_encoded->frameid;
			pwaitforevents->out_encresult = pevt_encoded->result;
			kfree(pevt_encoded);
			events++;
		}
		if (!list_empty(&ptask->nal_head)) {
			/* nal out events */
			pevt_nalout = list_entry(ptask->nal_head.next,
				struct veu_event, list);
			list_del(&pevt_nalout->list);
			DBG(pdev, "nal out events [id=%lld][size=%d]\n",
				pevt_nalout->frameid,
				pevt_nalout->result);
			pwaitforevents->out_outframeid = pevt_nalout->frameid;
			pwaitforevents->out_outsize = pevt_nalout->result;
			kfree(pevt_nalout);
			events++;
		}
		if (!list_empty(&ptask->rel_head)) {
			/* input picture release events */
			pevt_release = list_entry(ptask->rel_head.next,
				struct veu_event, list);
			list_del(&pevt_release->list);
			DBG(pdev, "input picture release events [id=%lld]\n",
				pevt_release->frameid);
			pwaitforevents->out_relframeid = pevt_release->frameid;
			kfree(pevt_release);
			events++;
		}
		if (events)
			break;

		/* wait for events */
		clear_bit(VEU_COND_ENCODE, &ptask->wait_cond);
		spin_unlock_irqrestore(&pdev->splock, flags);
		wait_event_timeout(ptask->task_waitq,
				test_bit(VEU_COND_ENCODE, &ptask->wait_cond),
				VEU_VEAPI_RSP_TIMEOUT);
		if (!test_bit(VEU_COND_ENCODE, &ptask->wait_cond)) {
			ierr = -EAGAIN;
			goto fail_2;
		}
		spin_lock_irqsave(&pdev->splock, flags);
	}

	spin_unlock_irqrestore(&pdev->splock, flags);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	spin_unlock_irqrestore(&pdev->splock, flags);
fail_2:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_getoutframe(struct veu_driver *pdev,
	struct venc_getoutframe *pgetoutframe, uint32_t taskid)
{
	int ierr = 0;
	struct veu_task *ptask;
	unsigned long flags;
	struct ve_output_entry entry;

	DBG(pdev, "enter\n");

	pgetoutframe->out_outsize = 0;
	pgetoutframe->out_attribute = 0;

	/* get struct veu_task */
	spin_lock_irqsave(&pdev->splock, flags);
	ierr = veu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%d]\n", taskid);
		goto fail_1;
	}

	spin_unlock_irqrestore(&pdev->splock, flags);

	/* read output data */
	ierr = veu_internal_nalout(pdev, ptask, pgetoutframe->in_outputbuf,
		&pgetoutframe->out_outsize, &entry);
	if (ierr < 0)
		goto fail_2;
	if (entry.attribute == VE_PIC_SYNC_FRAME)
		pgetoutframe->out_attribute |= VENC_PIC_ATTR_SYNC_FRAME;
	if (ptask->is_eos && (ptask->eos_frame_id == entry.frame_id))
		pgetoutframe->out_attribute |= VENC_PIC_ATTR_EOS;

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	spin_unlock_irqrestore(&pdev->splock, flags);
fail_2:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_internal_setinframewithcnv(struct veu_driver *pdev,
	struct venc_setinframewithcnv *psetinframe, uint32_t taskid)
{
	int ierr = 0;
	struct veu_task *ptask;
	struct veu_enc *newenc = NULL;
	unsigned long flags;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	/* search task */
	ierr = veu_internal_searchtask(pdev, taskid, &ptask);
	if (ierr < 0) {
		ERROR(pdev, "invalid task id [taskid=%d]\n", taskid);
		goto fail_1;
	}

	/* create struct veu_enc */
	newenc = kmalloc(sizeof(struct veu_enc), GFP_KERNEL);
	if (!newenc) {
		ierr = -ENOMEM;
		goto fail_1;
	}
	newenc->fd_luma = -1;
	newenc->fd_chroma = -1;
	newenc->sgt_luma = NULL;
	newenc->sgt_chroma = NULL;
	newenc->retry = 0;
	newenc->withconv_enable = 1; /* enable with conv */
	newenc->vconv_param = psetinframe->in_vconv_param;

	newenc->encsts = VEU_ENC_STAT_WAITING;
	newenc->pic.frame_id = psetinframe->in_frameid;
	newenc->pic.attribute = 0; /* don't care */

	/* queuing to struct veu_task */
	list_add_tail(&newenc->list, &ptask->encoding_head);

	if (pdev->devsts < VEU_STAT_RUNNING) {
		/* scheduling tasklet */
		tasklet_schedule(&pdev->veu_tasklet);
	}

	spin_unlock_irqrestore(&pdev->splock, flags);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	spin_unlock_irqrestore(&pdev->splock, flags);
	kfree(newenc);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}


int veu_internal_searchtask(struct veu_driver *pdev, uint32_t taskid,
	struct veu_task **rtask)
{
	int ierr = -EVEUBTSKID;
	struct veu_task *ptask, *next;

	DBG(pdev, "enter\n");

	*rtask = NULL;

	list_for_each_entry_safe(ptask, next, &pdev->task_head, list) {
		if (taskid == (uint32_t)ptask) {
			*rtask = ptask;
			ierr = 0;
			break;
		}
	}

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

/* 20130410A */
void veu_internal_irq_function(struct veu_driver *pdev)
{
	struct veu_task *ptask;
	struct veu_enc *penc;
	struct veu_response *presp_fw = NULL;
	struct veu_response *presp_task = NULL;
	struct veu_response *presp_kill = NULL;
	struct veu_response *presp_enc = NULL;
	struct ve_response response;
	struct ve_dying_message msg;
	enum ve_result ve_res;
	unsigned long resp_flag = 0;
#ifdef __DEBUG
	int i;
#endif

#ifdef __DEBUG
	DBG(pdev, "enter\n");
#endif
	/* call ve_handle_interrupt for VE_API */
	ve_res = ve_handle_interrupt(&response, &msg, 0);
	if (ve_res != VE_OK) {
		ERROR(pdev, "ve_handle_interrupt() failed [err=%d]\n",
			ve_res);
		goto done_1;
	}

#ifdef __DEBUG
	DBG(pdev, "ve_dying_message.param=0x%08x\n", msg.param);
#endif
	/* dying message(VE_CMD_KILL_TASK) */
	if (!msg.param) {
		/* has a dying message */
		set_bit(VEU_COND_KILL_TASK, &resp_flag);
	} else if (msg.param != 0xFFFFFFFF) {
		ERROR(pdev, "illegal dying message [param=0x%08x]\n", msg.param);
	}

#ifdef __DEBUG
	if (response.command != VE_CMD_NONEXISTENT) {
		DBG(pdev, "ve_response.command=0x%08x\n", response.command);
		DBG(pdev, "ve_response.num_of_params=%d\n", response.num_of_params);
		for (i = 0; i < response.num_of_params; i++)
			DBG(pdev, "ve_response.param[%d]=%d\n", i, response.param[i]);
	}
#endif

#ifdef __DEBUG
	if (response.command == VE_CMD_ENCODE) {
		if (response.num_of_params > 3)
			printk(KERN_DEBUG "[REL]:0x%08x%08x\n", response.param[3],
				response.param[2]);
	}
#endif

	/* response(!VE_CMD_KILL_TASK) */
	switch (response.command) {
	case VE_CMD_START_UP_PU:
		set_bit(VEU_COND_START_UP_PU, &resp_flag);
		break;
	case VE_CMD_SHUT_DOWN_PU:
		set_bit(VEU_COND_SHUT_DOWN_PU, &resp_flag);
		break;
	case VE_CMD_INITIALIZE_TASK:
		set_bit(VEU_COND_INITIALIZE_TASK, &resp_flag);
		break;
	case VE_CMD_INITIALIZE_IOBUFFER:
		set_bit(VEU_COND_INITIALIZE_IOBUFFER, &resp_flag);
		break;
	case VE_CMD_ENCODE:
		set_bit(VEU_COND_ENCODE, &resp_flag);
		break;
	default:
		break;
	}

	/* response(VE_CMD_START_UP_PU, VE_CMD_SHUT_DOWN_PU) */
	do {
		if (!test_bit(VEU_COND_START_UP_PU, &resp_flag) &&
		    !test_bit(VEU_COND_SHUT_DOWN_PU, &resp_flag))
			break;
		/* create struct veu_response */
		presp_fw = kmalloc(
			sizeof(struct veu_response), GFP_KERNEL);
		if (!presp_fw) {
			ERROR(pdev, "kernel memory allocate failed [struct veu_response][size=%d]\n",
				sizeof(struct veu_response));
			goto done_1;
		}
		memset(presp_fw, 0x00, sizeof(*presp_fw));
		if (test_bit(VEU_COND_START_UP_PU, &resp_flag)) {
			set_bit(VEU_COND_START_UP_PU, &presp_fw->resp_flag);
			set_bit(VEU_COND_START_UP_PU, &pdev->wait_cond);
		} else {
			set_bit(VEU_COND_SHUT_DOWN_PU, &presp_fw->resp_flag);
			set_bit(VEU_COND_SHUT_DOWN_PU, &pdev->wait_cond);
		}
		presp_fw->resp = response;
		list_add_tail(&presp_fw->list, &pdev->resp_head);
		pdev->resp_num++;
		wake_up(&pdev->veu_waitq);
	} while (0);

	/* response(VE_CMD_INITIALIZE_TASK, VE_CMD_INITIALIZE_IOBUFFER) */
	do {
		if (!test_bit(VEU_COND_INITIALIZE_TASK, &resp_flag) &&
		    !test_bit(VEU_COND_INITIALIZE_IOBUFFER, &resp_flag))
			break;
		if (veu_internal_searchtask_for_ctx(pdev, response.task,
						&ptask))
			break;
		/* create struct veu_response */
		presp_task = kmalloc(
			sizeof(struct veu_response), GFP_KERNEL);
		if (!presp_task) {
			ERROR(pdev, "kernel memory allocate failed [struct veu_response][size=%d]\n",
				sizeof(struct veu_response));
			goto done_1;
		}
		memset(presp_task, 0x00, sizeof(*presp_task));
		if (test_bit(VEU_COND_INITIALIZE_TASK, &resp_flag)) {
			set_bit(VEU_COND_INITIALIZE_TASK, &presp_task->resp_flag);
			set_bit(VEU_COND_INITIALIZE_TASK, &ptask->wait_cond);
		} else {
			set_bit(VEU_COND_INITIALIZE_IOBUFFER, &presp_task->resp_flag);
			set_bit(VEU_COND_INITIALIZE_IOBUFFER, &ptask->wait_cond);
		}
		presp_task->resp = response;
		list_add_tail(&presp_task->list, &ptask->resp_head);
		ptask->resp_num++;
		wake_up(&ptask->task_waitq);
	} while (0);

	/* response(VE_CMD_ENCODE) */
	do {
		if (!test_bit(VEU_COND_ENCODE, &resp_flag))
			break;
		if (veu_internal_searchtask_for_ctx(pdev, response.task,
						&ptask))
			break;
		if (list_empty(&ptask->encoding_head))
			break;
		penc = list_entry(ptask->encoding_head.next,
				struct veu_enc, list);
		if (penc->encsts != VEU_ENC_STAT_RUNNING)
			break;
		/* create struct veu_response */
		presp_enc = kmalloc(
			sizeof(struct veu_response), GFP_KERNEL);
		if (!presp_enc) {
			ERROR(pdev, "kernel memory allocate failed [struct veu_response][size=%d]\n",
				sizeof(struct veu_response));
			goto done_1;
		}
		memset(presp_enc, 0x00, sizeof(*presp_enc));
		set_bit(VEU_COND_ENCODE, &presp_enc->resp_flag);
		presp_enc->resp = response;
		list_add_tail(&presp_enc->list, &ptask->resp_head);
		ptask->resp_num++;
		penc->encsts = VEU_ENC_STAT_FINISHED;
		tasklet_schedule(&pdev->veu_tasklet);
	} while (0);

	/* dying message(VE_CMD_KILL_TASK) */
	do {
		if (!test_bit(VEU_COND_KILL_TASK, &resp_flag))
			break;
		if (veu_internal_searchtask_for_ctx(pdev, msg.task,
						&ptask))
			break;
		/* create struct veu_response */
		presp_kill = kmalloc(
			sizeof(struct veu_response), GFP_KERNEL);
		if (!presp_kill) {
			ERROR(pdev, "kernel memory allocate failed [struct veu_response][size=%d]\n",
				sizeof(struct veu_response));
			goto done_1;
		}
		memset(presp_kill, 0x00, sizeof(*presp_kill));
		set_bit(VEU_COND_KILL_TASK, &presp_kill->resp_flag);
		set_bit(VEU_COND_KILL_TASK, &ptask->wait_cond);
		presp_kill->msg = msg;
		list_add_tail(&presp_kill->list, &ptask->resp_head);
		ptask->resp_num++;
		wake_up(&ptask->task_waitq);
	} while (0);

#ifdef __DEBUG
	DBG(pdev, "leave\n");
#endif
	return;

done_1:
	kfree(presp_fw);
	kfree(presp_task);
	kfree(presp_kill);
	kfree(presp_enc);
#ifdef __DEBUG
	DBG(pdev, "leave\n");
#endif
	return;
}

void veu_internal_tasklet_function(struct veu_driver *pdev)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	switch (pdev->devsts) {
	case VEU_STAT_NOFW:
	case VEU_STAT_RESET_ON:
		break;
	case VEU_STAT_IDLE:
		ierr = veu_internal_start_encode(pdev);
		break;
	case VEU_STAT_RUNNING:
		ierr = veu_internal_finished_encode(pdev);
		if (ierr < 0)
			break;
		ierr = veu_internal_start_encode(pdev);
		break;
	case VEU_STAT_MAX:
		break;
	}
	DBG(pdev, "leave\n");
}

static int veu_internal_clear_events(struct veu_driver *pdev,
	struct veu_task *ptask)
{
	int ierr = 0;
	struct venc_waitforevents waitforevents;
	/*struct venc_getoutframe getoutframe;*/
	struct veu_enc *penc, *next;
	unsigned long flags;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	/* clear struct veu_enc */
	list_for_each_entry_safe(penc, next, &ptask->encoded_head, list) {
		list_del(&penc->list);
		/* create struct veu_event */
		veu_internal_add_event(pdev, ptask, VEU_EVT_RELEASE,
			penc->pic.frame_id, 0);
		veu_com_frameid_release(&ptask->frameid_tbl);
		/* wakeup for encode finish */
		set_bit(VEU_COND_ENCODE, &ptask->wait_cond);
		wake_up(&ptask->task_waitq);
		spin_unlock_irqrestore(&pdev->splock, flags);
		veu_internal_unmap_ma(pdev, penc->fd_luma, penc->sgt_luma);
		veu_internal_unmap_ma(pdev, penc->fd_chroma, penc->sgt_chroma);
		spin_lock_irqsave(&pdev->splock, flags);
		kfree(penc);
	}
	list_for_each_entry_safe(penc, next, &ptask->encoding_head, list) {
		list_del(&penc->list);
		if (penc->encsts == VEU_ENC_STAT_RUNNING) {
			/* create struct veu_event */
			veu_internal_add_event(pdev, ptask, VEU_EVT_ENCODED,
				penc->pic.frame_id, 0);
			veu_com_frameid_encoded(&ptask->frameid_tbl);
			veu_internal_add_event(pdev, ptask, VEU_EVT_RELEASE,
				penc->pic.frame_id, 0);
			veu_com_frameid_release(&ptask->frameid_tbl);
			/* wakeup for encode finish */
			set_bit(VEU_COND_ENCODE, &ptask->wait_cond);
			wake_up(&ptask->task_waitq);
		}
		spin_unlock_irqrestore(&pdev->splock, flags);
		veu_internal_unmap_ma(pdev, penc->fd_luma, penc->sgt_luma);
		veu_internal_unmap_ma(pdev, penc->fd_chroma, penc->sgt_chroma);
		spin_lock_irqsave(&pdev->splock, flags);
		kfree(penc);
	}

	spin_unlock_irqrestore(&pdev->splock, flags);

	/* clear events */
	while (1) {
		spin_lock_irqsave(&pdev->splock, flags);
		if (list_empty(&ptask->encfin_head) &&
			list_empty(&ptask->nal_head) &&
			list_empty(&ptask->rel_head)) {
			/* empty event */
			break;
		}
		spin_unlock_irqrestore(&pdev->splock, flags);
		/* wait events */
		ierr = veu_internal_waitforevents(pdev, &waitforevents,
			(uint32_t)ptask);
		if (ierr < 0)
			goto fail_1;
#if 0 /* don't care */
		if (waitforevents.out_outframeid > 0) {
			getoutframe.in_outputbuf = 0;
			ierr = veu_internal_getoutframe(pdev, &getoutframe,
				(uint32_t)ptask);
			if (ierr < 0)
				goto fail_1;
		}
#endif
	}

	spin_unlock_irqrestore(&pdev->splock, flags);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static int veu_internal_map_ma(struct veu_driver *pdev,
	struct venc_shmem *pmem, ve_vtile_t *vaddr, struct sg_table **rsgt)
{
	int ierr = 0;
	struct veu_ma *pma, *curr, *next;
	struct sg_table *psgt = NULL;
	ve_vtile_t vtile_addr;

	DBG(pdev, "enter\n");

	*vaddr = 0;
	*rsgt = NULL;

	if (pmem->fd < 0) {
		/*ERROR(pdev, "illegal shared memory fd [fd=%d]\n",
			pmem->fd);*/
		goto fail_3;
	}

	pma = NULL;
	list_for_each_entry_safe(curr, next, &pdev->ma_head, list) {
		if (curr->fd == pmem->fd) {
			pma = curr;
			break;
		}
	}

	if (pma == NULL) {
		/* attach shard memory */
		pma = kmalloc(sizeof(struct veu_ma), GFP_KERNEL);
		if (!pma) {
			ERROR(pdev, "kernel memory allocate failed [struct veu_ma][size=%d]\n",
				sizeof(struct veu_ma));
			ierr = -ENOMEM;
			goto fail_2;
		}
		pma->fd = pmem->fd;
		pma->dbuf = NULL;
		pma->dbufa = NULL;
		pma->map_count = 0;
		pma->dbuf = dma_buf_get(pma->fd);
		if (IS_ERR(pma->dbuf)) {
			ERROR(pdev, "dma_buf_get() failed [fd=%d]\n",
				pma->fd);
			ierr = -EFAULT;
			goto fail_3;
		}
		pma->dbufa = dma_buf_attach(pma->dbuf, pdev->device);
		if (IS_ERR(pma->dbufa)) {
			ERROR(pdev, "dma_buf_attach() failed [fd=%d]\n",
				pma->fd);
			ierr = -EFAULT;
			goto fail_1;
		}
		list_add_tail(&pma->list, &pdev->ma_head);
		pdev->ma_num++;
	}

	/* map shard memory */
	psgt = dma_buf_map_attachment(pma->dbufa, DMA_TO_DEVICE);
	if (IS_ERR_OR_NULL(psgt)) {
		ERROR(pdev, "dma_buf_map_attachment() failed [fd=%d]\n",
			pma->fd);
		ierr = -EFAULT;
		goto fail_2;
	}
#if 0
	if (sg_dma_len(psgt->sgl) <= pmem->offset) {
		ERROR(pdev, "illegal memory offset [fd=%d][memsize=%d][offset=%d]\n",
			pma->fd, sg_dma_len(psgt->sgl), pmem->offset);
		ierr = -EFAULT;
		goto fail_2;
	}
#endif
	pma->map_count++;
	vtile_addr = (ve_vtile_t)veu_internal_phys_to_veu(
		(uint32_t)sg_dma_address(psgt->sgl));
	*vaddr = vtile_addr + pmem->offset;
	*rsgt = psgt;

	DBG(pdev, "leave (vaddr=%08x) [rtn=%d]\n", *vaddr, ierr);
	return ierr;

fail_1:
	if (pma) {
		if (!IS_ERR_OR_NULL(pma->dbuf)) {
			dma_buf_put(pma->dbuf);
			pma->dbuf = NULL;
		}
		kfree(pma);
	}
fail_2:
	if (!IS_ERR_OR_NULL(psgt))
		dma_buf_unmap_attachment(pma->dbufa, psgt, DMA_TO_DEVICE);
fail_3:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static void veu_internal_unmap_ma(struct veu_driver *pdev, int fd,
	struct sg_table *psgt)
{
	struct veu_ma *pma, *curr, *next;

	DBG(pdev, "enter\n");

	if ((fd < 0) || (psgt == NULL))
		goto fail_1;

	pma = NULL;
	list_for_each_entry_safe(curr, next, &pdev->ma_head, list) {
		if (curr->fd == fd) {
			pma = curr;
			break;
		}
	}
	if (pma == NULL)
		goto fail_1;

	/* unmap shard memory */
	dma_buf_unmap_attachment(pma->dbufa, psgt, DMA_TO_DEVICE);
	pma->map_count--;
	if (!pma->map_count) {
		/* detach shard memory */
		list_del(&pma->list);
		pdev->ma_num--;
		dma_buf_detach(pma->dbuf, pma->dbufa);
		dma_buf_put(pma->dbuf);
		kfree(pma);
	}

	DBG(pdev, "leave\n");
	return;

fail_1:
	DBG(pdev, "leave\n");
	return;
}


static int veu_internal_memory_alloc(struct veu_driver *pdev,
	struct device *dev, size_t size,
	enum veu_mem_type type, enum veu_mem_align align, struct veu_locmem *pmem)
{
	int ierr = 0;
	int alloc_size;
	unsigned int align_mask;

	pmem->type = VEU_MEM_TYPE_NON;
	pmem->size = size;
	pmem->align = align;
	pmem->addr = 0;
	pmem->alloc_mem = 0;
	pmem->dma_addr = 0;
	pmem->fd = -1;

	DBG(pdev, "enter\n");

	switch (type) {
	case VEU_MEM_TYPE_KALLOC:
		/* use kmalloc */
		align_mask = 0xffffffff << pmem->align;
		alloc_size = pmem->size + (~align_mask + 1);
		pmem->alloc_mem = (uint32_t)kmalloc(alloc_size, GFP_KERNEL);
		if (pmem->alloc_mem == 0) {
			ERROR(pdev, "kernel memory allocate failed [size=%d]\n", alloc_size);
			ierr = -ENOMEM;
			goto fail_1;
		}
		if (~align_mask&pmem->alloc_mem) {
			pmem->addr = pmem->alloc_mem + (~align_mask + 1);
			pmem->addr &= align_mask;
		} else {
			pmem->addr = pmem->alloc_mem;
		}
		pmem->type = VEU_MEM_TYPE_KALLOC;
		break;

	case VEU_MEM_TYPE_DMA:
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
			goto fail_1;
		}
		memset((void *)pmem->alloc_mem, 0x00, pmem->size);
		pmem->addr = pmem->alloc_mem;
		pmem->type = VEU_MEM_TYPE_DMA;
		DBG(pdev, "v=0x%08x p=0x%08x size=%d\n",
			pmem->addr, pmem->dma_addr, pmem->size);
		break;

	case VEU_MEM_TYPE_DMA_FW:
		/* use dma_alloc_coherent */
		pmem->alloc_mem = (uint32_t)dma_alloc_coherent(
			dev,
			pmem->size,
			&pmem->dma_addr,
			GFP_KERNEL|GFP_DMA);
		if (pmem->alloc_mem == 0) {
			ERROR(pdev, "dma memory allocate failed [size=%d]\n",
				pmem->size);
			ierr = -ENOMEM;
			goto fail_1;
		}
		memset((void *)pmem->alloc_mem, 0x00, pmem->size);
		pmem->addr = pmem->alloc_mem;
		pmem->type = VEU_MEM_TYPE_DMA_FW;
		/*pr_info("### alloc fw area [%08x]\n", pmem->alloc_mem);*/
		DBG(pdev, "v=0x%08x p=0x%08x size=%d\n",
			pmem->addr, pmem->dma_addr, pmem->size);
		break;

	case VEU_MEM_TYPE_MA:
	case VEU_MEM_TYPE_NON:
		ERROR(pdev, "dma memory allocate failed [size=%d]\n",
			pmem->size);
		ierr = -ENOMEM;
		goto fail_1;
	}

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static void veu_internal_memory_free(struct veu_driver *pdev,
	struct device *dev, struct veu_locmem *pmem)
{
	DBG(pdev, "enter\n");

	switch (pmem->type) {
	case VEU_MEM_TYPE_KALLOC:
		kfree((void *)pmem->alloc_mem);
		break;
	case VEU_MEM_TYPE_DMA:
		DBG(pdev, "v=0x%08x p=0x%08x size=%d\n",
			pmem->addr, pmem->dma_addr, pmem->size);
		dma_free_coherent(NULL, pmem->size, (void *)pmem->alloc_mem,
			pmem->dma_addr);
		break;
	case VEU_MEM_TYPE_DMA_FW:
		DBG(pdev, "v=0x%08x p=0x%08x size=%d\n",
			pmem->addr, pmem->dma_addr, pmem->size);
		dma_free_coherent(dev, pmem->size, (void *)pmem->alloc_mem,
			pmem->dma_addr);
		/*pr_info("### free fw area [%08x]\n", pmem->alloc_mem);*/
		break;
	case VEU_MEM_TYPE_MA:
	case VEU_MEM_TYPE_NON:
		break;
	}

	pmem->type = VEU_MEM_TYPE_NON;
	pmem->size = 0;
	pmem->align = 0;
	pmem->addr = 0;
	pmem->alloc_mem = 0;
	pmem->dma_addr = 0;
	pmem->fd = -1;

	DBG(pdev, "leave\n");
}

static int veu_internal_start_encode(struct veu_driver *pdev)
{
	int ierr = 0;
	int i;
	struct veu_task *ptask;
	struct veu_enc *penc;
	enum ve_result veret;
	unsigned long flags;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	if (list_empty(&pdev->task_head)) {
		DBG(pdev, "no task\n");
		goto done_1;
	}

	for (i = 0; i < pdev->task_num; i++) {
		ptask = list_entry(pdev->task_head.next, struct veu_task, list);
		if (list_empty(&ptask->encoding_head)) {
			DBG(pdev, "no encoding [task=%d]\n", i);
			continue;
		}
		penc = list_entry(ptask->encoding_head.next,
			struct veu_enc, list);
		if (penc->encsts != VEU_ENC_STAT_WAITING)
			continue;
		/* call ve_send_encode_cmd for VE_API */
		veret = VE_OK;
#ifdef __DEBUG
		printk(KERN_DEBUG "[REQ]:0x%llx\n", penc->pic.frame_id);
#endif
		if (!penc->pic.luma || !penc->pic.chroma) {
			/* flush */
			DBG(pdev, "call ve_send_encode_cmd() [flush]\n");
			veret = ve_send_encode_cmd(ptask->ctx, NULL, 0);
		} else {
			if (penc->withconv_enable) {
				/* enable with vconv */
				spin_unlock_irqrestore(&pdev->splock, flags);
				ierr = veu_internal_vconv(pdev, ptask, penc);
				spin_lock_irqsave(&pdev->splock, flags);
				if (ierr < 0) {
					/* create struct veu_event */
					veu_internal_add_event(pdev, ptask,
						VEU_EVT_ENCODED,
						penc->pic.frame_id, -EVEUVCONV);
					/* wakeup for encode finish */
					set_bit(VEU_COND_ENCODE, &ptask->wait_cond);
					wake_up(&ptask->task_waitq);
					/* delete struct veu_enc */
					list_del(&penc->list);
					spin_unlock_irqrestore(&pdev->splock, flags);
					veu_internal_unmap_ma(pdev, penc->fd_luma,
						penc->sgt_luma);
					veu_internal_unmap_ma(pdev, penc->fd_chroma,
						penc->sgt_chroma);
					spin_lock_irqsave(&pdev->splock, flags);
					kfree(penc);
					continue;
				}
			}
			DBG(pdev, "call ve_send_encode_cmd() [luma=%08x][chroma=%08x][frameid=%llx][attr=%08x]\n",
				penc->pic.luma,
				penc->pic.chroma,
				penc->pic.frame_id,
				penc->pic.attribute);
			veret = ve_send_encode_cmd(ptask->ctx,
				&penc->pic, 0);
		}
		if (veret != VE_OK) {
			if (veret == VE_ERROR_MBOX_BUSY) {
				/* re-scheduling tasklet */
				penc->retry++;
				if (penc->retry < VEU_VEAPI_RETRY_MAX) {
					ERROR(pdev, "ve_send_encode_cmd busy [retry=%d]\n", penc->retry);
					tasklet_schedule(&pdev->veu_tasklet);
					goto done_1;
				}
				ERROR(pdev, "ve_send_encode_cmd() retry over\n");

				/* create struct veu_event */
				veu_internal_add_event(pdev, ptask, VEU_EVT_ENCODED,
					penc->pic.frame_id, -EVEURETRYOVER);
			} else {
				ERROR(pdev, "ve_send_encode_cmd() failed [err=%d]\n", veret);
				/* create struct veu_event */
				veu_internal_add_event(pdev, ptask, VEU_EVT_ENCODED,
					penc->pic.frame_id, -EVEUVEAPI);
			}
			/* wakeup for encode finish */
			set_bit(VEU_COND_ENCODE, &ptask->wait_cond);
			wake_up(&ptask->task_waitq);
			/* delete struct veu_enc */
			list_del(&penc->list);
			spin_unlock_irqrestore(&pdev->splock, flags);
			veu_internal_unmap_ma(pdev, penc->fd_luma,
				penc->sgt_luma);
			veu_internal_unmap_ma(pdev, penc->fd_chroma,
				penc->sgt_chroma);
			spin_lock_irqsave(&pdev->splock, flags);
			kfree(penc);
			continue;
		} else {
			DBG(pdev, "frameid=%lld\n", penc->pic.frame_id);
			veu_com_frameid_add(&ptask->frameid_tbl,
				penc->pic.frame_id);
			penc->encsts = VEU_ENC_STAT_RUNNING;
			pdev->devsts = VEU_STAT_RUNNING;
			/* add entry to list head */
			list_del(&ptask->list);
			list_add(&ptask->list, &pdev->task_head);
			break;
		}
	}

done_1:
	spin_unlock_irqrestore(&pdev->splock, flags);
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static int veu_internal_finished_encode(struct veu_driver *pdev)
{
	int ierr = 0;
	int result;
	int resp_res;
	struct veu_task *ptask;
	struct veu_enc *penc, *rmpenc;
	struct ve_response resp;
	unsigned long flags;
	struct ve_output_entry entry;
	union {
		uint64_t u64;
		uint32_t u32[2];
	} frame_id;

	DBG(pdev, "enter\n");

	spin_lock_irqsave(&pdev->splock, flags);

	if (list_empty(&pdev->task_head)) {
		pdev->devsts = VEU_STAT_IDLE;
		goto done_1;
	}
	ptask = list_entry(pdev->task_head.next, struct veu_task, list);
	if (list_empty(&ptask->encoding_head)) {
		pdev->devsts = VEU_STAT_IDLE;
		goto done_1;
	}
	/* 20130410A */
	resp_res = veu_internal_response_result(pdev, ptask,
					VEU_COND_ENCODE, &resp);
	if (resp_res)
		goto done_1;

	penc = list_entry(ptask->encoding_head.next, struct veu_enc, list);
	if (penc->encsts != VEU_ENC_STAT_FINISHED) {
		pdev->devsts = VEU_STAT_IDLE;
		goto done_1;
	}

	/* check encode result */
	switch (resp.param[0]) {
	case 0:
		/* success */
		result = VENC_ENC_RES_SUCCESS;
		break;
	case 2:
		/* failed to sync frame */
		result = VENC_ENC_RES_SYNC_FAIL;
		break;
	default:
	case 1:
		/* failed to encode or flush*/
		result = VENC_ENC_RES_FAIL;
		break;
	}
	veu_internal_add_event(pdev, ptask, VEU_EVT_ENCODED,
		penc->pic.frame_id, result);
	veu_com_frameid_encoded(&ptask->frameid_tbl);

	/* check response and read output data */
	if ((resp.num_of_params > 1) && (resp.param[1])) {
		DBG(pdev, "add event(VEU_EVT_NALOUT)\n");
		/* create struct veu_event */
		result = veu_internal_naloutsize(pdev, ptask, &entry);
		veu_internal_add_event(pdev, ptask, VEU_EVT_NALOUT,
			entry.frame_id, result);
		veu_com_frameid_nalout(&ptask->frameid_tbl);
		if (resp.param[1] == 2) {
			/* eos */
			ptask->is_eos = 1;
			ptask->eos_frame_id = entry.frame_id;
		}
	}

	/* check response and release input frame(s) */
	if (resp.num_of_params > 3) {
		if (!list_empty(&ptask->encoded_head)) {
			rmpenc = list_entry(ptask->encoded_head.next,
				struct veu_enc, list);
			list_del(&rmpenc->list);
			spin_unlock_irqrestore(&pdev->splock, flags);
			veu_internal_unmap_ma(pdev, rmpenc->fd_luma,
				rmpenc->sgt_luma);
			veu_internal_unmap_ma(pdev, rmpenc->fd_chroma,
				rmpenc->sgt_chroma);
			spin_lock_irqsave(&pdev->splock, flags);
			kfree(rmpenc);
		}
		DBG(pdev, "add event(VEU_EVT_RELEASE) frameid=0x%08X%08X\n",
			resp.param[3], resp.param[2]);
		frame_id.u32[0] = resp.param[2];
		frame_id.u32[1] = resp.param[3];
		veu_internal_add_event(pdev, ptask, VEU_EVT_RELEASE,
			frame_id.u64, 0);
		veu_com_frameid_release(&ptask->frameid_tbl);
	}

	/* move struct veu_enc */
	list_del(&penc->list);
	if (!penc->flush)
		list_add_tail(&penc->list, &ptask->encoded_head);
	else
		kfree(penc);

	/* rotation struct veu_task */
	list_del(&ptask->list);
	list_add_tail(&ptask->list, &pdev->task_head);

	/* wakeup for encode finish */
	set_bit(VEU_COND_ENCODE, &ptask->wait_cond);
	wake_up(&ptask->task_waitq);

	pdev->devsts = VEU_STAT_IDLE;

done_1:
	spin_unlock_irqrestore(&pdev->splock, flags);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static int veu_internal_abort_encode(struct veu_driver *pdev,
	struct veu_task *ptask)
{
	int ierr = 0;
	int resp_res;
	enum ve_result veret;
	struct ve_response resp;
	uint32_t fw_state;
	int32_t retry;
	unsigned long flags;

	DBG(pdev, "enter\n");

	/* call ve_send_kill_task_cmd for VE_API */
	retry = VEU_VEAPI_RETRY_MAX;
	clear_bit(VEU_COND_KILL_TASK, &ptask->wait_cond);
	while (retry--) {
		veret = ve_send_kill_task_cmd(ptask->ctx, 0);
		if (veret != VE_OK) {
			if (veret == VE_ERROR_MBOX_BUSY) {
				veu_internal_sleep(VEU_VEAPI_RETRY_TIME);
				continue;
			}
			veret = ve_get_fw_state(&fw_state, 0);
			if (veret != VE_OK) {
				ERROR(pdev, "ve_get_fw_state() failed [err=%d]\n", veret);
				ierr = -EVEUVEAPI;
				goto fail_1;
			}
			if (fw_state == VE_FW_STATE_RUNNING) {
				/* ve_send_kill_task_cmd success */
				veret = VE_OK;
				break;
			}
			ERROR(pdev, "ve_send_kill_task_cmd() failed [err=%d]\n", veret);
			ierr = -EVEUVEAPI;
			goto fail_1;
		}
rewait:
		wait_event_timeout(ptask->task_waitq,
			test_bit(VEU_COND_KILL_TASK, &ptask->wait_cond),
			VEU_VEAPI_RSP_TIMEOUT);
		if (!test_bit(VEU_COND_KILL_TASK, &ptask->wait_cond)) {
			ERROR(pdev, "ve_send_kill_task_cmd() timeout\n");
			ierr = -EVEUTIMEDOUT;
			goto fail_1;
		}
		clear_bit(VEU_COND_KILL_TASK, &ptask->wait_cond);
		/* 20130410A */
		spin_lock_irqsave(&pdev->splock, flags);
		resp_res = veu_internal_response_result(pdev,
				ptask, VEU_COND_KILL_TASK, &resp);
		spin_unlock_irqrestore(&pdev->splock, flags);
		if (resp_res) {
			/* rewait */
			goto rewait;
		}
		if (resp.param[0]) {
			veret = ve_get_fw_state(&fw_state, 0);
			if (veret != VE_OK) {
				ERROR(pdev, "ve_get_fw_state() failed [err=%d]\n", veret);
				ierr = -EVEUVEAPI;
				goto fail_1;
			}
			if (fw_state == VE_FW_STATE_RUNNING) {
				/* ve_send_kill_task_cmd success */
				veret = VE_OK;
				break;
			}
			ierr = -EVEUVEAPI;
			goto fail_1;
		}
		break;
	}
	if (veret == VE_ERROR_MBOX_BUSY) {
		/* retry over */
		ierr = -EVEURETRYOVER;
		goto fail_1;
	}
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static void veu_internal_sleep(long time)
{
	wait_queue_head_t waitq;
	init_waitqueue_head(&waitq);
	interruptible_sleep_on_timeout(&waitq, time);
}

static int veu_internal_naloutsize(struct veu_driver *pdev, struct veu_task *ptask,
	struct ve_output_entry *entry)
{
	enum ve_result veret;
	int read_begin;
	int occupancy = 0;

	DBG(pdev, "enter\n");

	/* call ve_get_output_buf_entry for VE_API */
	veret = ve_get_output_buf_entry(ptask->ctx, entry);
	if (veret != VE_OK) {
		ERROR(pdev, "ve_get_output_buf_entry() failed [err=%d]\n",
			veret);
		goto done_1;
	}
#ifdef __DEBUG
	printk(KERN_DEBUG "[OUT]:0x%llx\n", entry->frame_id);
#endif
	read_begin = entry->begin;
	if (entry->end < read_begin) {  /* wrapping */
		occupancy = (ptask->outbuf_e - ptask->outbuf_b) - read_begin;
		read_begin = 0;
	}
	if (read_begin < entry->end)
		occupancy += (entry->end - read_begin);

#ifdef __NO_BUG
	ptask->entry = *entry;
#endif

done_1:
	DBG(pdev, "leave [occupancy=%d]\n", occupancy);
	return occupancy;
}

static int veu_internal_nalout(struct veu_driver *pdev, struct veu_task *ptask,
	uint32_t outbuf, uint32_t *written, struct ve_output_entry *entry)
{
	int ierr = 0;
	enum ve_result veret;
	uint32_t read_begin;
	uint32_t occupancy;
	char *rp;

	DBG(pdev, "enter\n");

	*written = 0;
#ifdef __NO_BUG
	*entry = ptask->entry;
#else
	veret = ve_get_output_buf_entry(ptask->ctx, entry);
#endif
	if (veret == VE_OK) {
		read_begin = entry->begin;
		if (entry->end < read_begin) {  /* wrapping */
			rp = ptask->outbuf_b + read_begin;
			occupancy = (ptask->outbuf_e - ptask->outbuf_b) -
				read_begin;
			if (outbuf) {
				if (copy_to_user((void __user *)outbuf, (const void *)rp, occupancy)) {
					ERROR(pdev, "copy_to_user() failed [user addr=%x][kernel addr=%x][size=%d]\n",
						(u32)outbuf,
						(u32)rp, occupancy);
					ierr = -EFAULT;
					goto fail_1;
				}
				outbuf += occupancy;
				*written += occupancy;
			}
			read_begin = 0;
		}
		if (read_begin < entry->end) {
			rp = ptask->outbuf_b + read_begin;
			occupancy = entry->end - read_begin;
			if (outbuf) {
				if (copy_to_user((void __user *)outbuf, (const void *)rp, occupancy)) {
					ERROR(pdev, "copy_to_user() failed [user addr=%x][kernel addr=%x][size=%d]\n",
						(u32)outbuf,
						(u32)rp, occupancy);
					ierr = -EFAULT;
					goto fail_1;
				}
				outbuf += occupancy;
				*written += occupancy;
			}
		}
		veret = ve_next_output_buf_entry(ptask->ctx);
		if (veret != VE_OK) {
#ifdef __NO_BUG
			if (veret != VE_ERROR_STATE) {
#endif
				ERROR(pdev, "ve_next_output_buf_entry() failed [err=%d]\n", veret);
				ierr = -EVEUVEAPI;
				goto fail_1;
#ifdef __NO_BUG
			}
#endif
		}
	} else if (veret == VE_ERROR_NONEXISTENT) {
		ierr = -EAGAIN;
		goto fail_1;
	} else {
		ERROR(pdev, "ve_get_output_buf_entry() failed [err=%d]\n",
			veret);
		ierr = -EVEUVEAPI;
		goto fail_1;
	}

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

static enum ve_frame_rate veu_internal_ve_fps(enum venc_frame_rate venc_fps)
{
	enum ve_frame_rate ve_fps = VE_FPS_11_98HZ;

	switch (venc_fps) {
	case VENC_FPS_11_98HZ:
		ve_fps = VE_FPS_11_98HZ;
		break;
	case VENC_FPS_14_98HZ:
		ve_fps = VE_FPS_14_98HZ;
		break;
	case VENC_FPS_15HZ:
		ve_fps = VE_FPS_15HZ;
		break;
	case VENC_FPS_23_97HZ:
		ve_fps = VE_FPS_23_97HZ;
		break;
	case VENC_FPS_24HZ:
		ve_fps = VE_FPS_24HZ;
		break;
	case VENC_FPS_25HZ:
		ve_fps = VE_FPS_25HZ;
		break;
	case VENC_FPS_29_97HZ:
		ve_fps = VE_FPS_29_97HZ;
		break;
	case VENC_FPS_30HZ:
		ve_fps = VE_FPS_30HZ;
		break;
	case VENC_FPS_47_95HZ:
		ve_fps = VE_FPS_47_95HZ;
		break;
	case VENC_FPS_48HZ:
		ve_fps = VE_FPS_48HZ;
		break;
	case VENC_FPS_50HZ:
		ve_fps = VE_FPS_50HZ;
		break;
	case VENC_FPS_59_94HZ:
		ve_fps = VE_FPS_59_94HZ;
		break;
	case VENC_FPS_60HZ:
		ve_fps = VE_FPS_60HZ;
		break;
	}
	return ve_fps;
}

static enum venc_frame_rate veu_internal_venc_fps(enum ve_frame_rate ve_fps)
{
	enum venc_frame_rate venc_fps = VENC_FPS_11_98HZ;

	switch (ve_fps) {
	case VE_FPS_11_98HZ:
		venc_fps = VENC_FPS_11_98HZ;
		break;
	case VE_FPS_14_98HZ:
		venc_fps = VENC_FPS_14_98HZ;
		break;
	case VE_FPS_15HZ:
		venc_fps = VENC_FPS_15HZ;
		break;
	case VE_FPS_23_97HZ:
		venc_fps = VENC_FPS_23_97HZ;
		break;
	case VE_FPS_24HZ:
		venc_fps = VENC_FPS_24HZ;
		break;
	case VE_FPS_25HZ:
		venc_fps = VENC_FPS_25HZ;
		break;
	case VE_FPS_29_97HZ:
		venc_fps = VENC_FPS_29_97HZ;
		break;
	case VE_FPS_30HZ:
		venc_fps = VENC_FPS_30HZ;
		break;
	case VE_FPS_47_95HZ:
		venc_fps = VENC_FPS_47_95HZ;
		break;
	case VE_FPS_48HZ:
		venc_fps = VENC_FPS_48HZ;
		break;
	case VE_FPS_50HZ:
		venc_fps = VENC_FPS_50HZ;
		break;
	case VE_FPS_59_94HZ:
		venc_fps = VENC_FPS_59_94HZ;
		break;
	case VE_FPS_60HZ:
		venc_fps = VENC_FPS_60HZ;
		break;
	}

	return venc_fps;
}

/* 20130410A */
static enum ve_profile veu_internal_ve_profile(enum venc_profile venc_profile)
{
	enum ve_profile ve_profile = VENC_PF_ANY;

	switch (venc_profile) {
	case VENC_PF_ANY:
		ve_profile = VE_PF_ANY;
		break;
	case VENC_PF_BASELINE:
		ve_profile = VE_PF_BASELINE;
		break;
	case VENC_PF_MAIN:
		ve_profile = VE_PF_MAIN;
		break;
	case VENC_PF_HIGH:
		ve_profile = VE_PF_HIGH;
		break;
	}

	return ve_profile;
}

static void veu_internal_add_event(struct veu_driver *pdev,
	struct veu_task *ptask, enum veu_event_code evcode, uint64_t frameid,
	int32_t result)
{
	struct veu_event *pevt;

	DBG(pdev, "enter\n");

	/* create struct veu_event */
	pevt = kmalloc(sizeof(struct veu_event), GFP_KERNEL);
	if (!pevt) {
		ERROR(pdev, "kernel memory allocate failed [struct veu_event][size=%d]\n", sizeof(struct veu_event));
		goto fail_1;
	}
	pevt->event = evcode;
	pevt->frameid = frameid;
	pevt->result = result;

	/* queuing to struct veu_task */
	switch (evcode) {
	case VEU_EVT_ENCODED:
		list_add_tail(&pevt->list, &ptask->encfin_head);
		break;
	case VEU_EVT_NALOUT:
		list_add_tail(&pevt->list, &ptask->nal_head);
		break;
	case VEU_EVT_RELEASE:
		list_add_tail(&pevt->list, &ptask->rel_head);
		break;
	case VEU_EVT_MAX:
		break;
	}

	DBG(pdev, "leave\n");
	return;

fail_1:
	DBG(pdev, "leave\n");
	return;
}

static uint32_t veu_internal_phys_to_veu(uint32_t phys)
{
	/* 20130410A */
	return (phys & 0xE0000000) | ((phys & 0x1FF00000) >> 10);
}

static void veapi_lock(void *lock)
{
	DBG(&s_veu_dev, "enter\n");
	spin_lock_irqsave((spinlock_t *)lock, veapi_lock_flags);
}

static void veapi_unlock(void *lock)
{
	DBG(&s_veu_dev, "enter\n");
	spin_unlock_irqrestore((spinlock_t *)lock, veapi_lock_flags);
}

static int veu_internal_vconv(struct veu_driver *pdev,
	struct veu_task *ptask, struct veu_enc *penc)
{
	int ierr = 0;
	struct file *filp;
	struct venc_shmem shmem;

	DBG(pdev, "enter\n");

	filp = filp_open(VCONV_DEVICE_FILE, O_RDONLY, 0600);
	if (IS_ERR(filp)) {
		ERROR(pdev, "vconv driver open failed [file=%s]\n",
			VCONV_DEVICE_FILE);
		ierr = -EVEUVCONV;
		goto fail_1;
	}

	if (filp->f_op->unlocked_ioctl(filp,
		IOC_VCONV_START, (unsigned long)&penc->vconv_param) < 0) {
		ERROR(pdev, "vconv driver IOC_VCONV_START failed\n");
		ierr = -EVEUVCONV;
		goto fail_2;
	}
	filp_close(filp, NULL);

	/* luma mmap */
	shmem.fd = penc->vconv_param.out_buffer[0].fd;
	shmem.offset = penc->vconv_param.out_buffer[0].offset;
	ierr = veu_internal_map_ma(pdev, &shmem,
		&penc->pic.luma, &penc->sgt_luma);
	if (ierr != 0)
		goto fail_1;
	penc->fd_luma = penc->vconv_param.out_buffer[0].fd;

	/* chroma mmap */
	shmem.fd = penc->vconv_param.out_buffer[1].fd;
	shmem.offset = penc->vconv_param.out_buffer[1].offset;
	ierr = veu_internal_map_ma(pdev, &shmem,
		&penc->pic.chroma, &penc->sgt_chroma);
	if (ierr != 0)
		goto fail_1;
	penc->fd_chroma = penc->vconv_param.out_buffer[1].fd;

	/* check MSB */
	if ((penc->pic.luma&0xc0000000) !=
	    (ptask->tail_ve_buf_ref&0xc0000000)) {
		ERROR(pdev, "illegal input luma buffer address [ref=%08x][buf=%08x]\n",
			ptask->tail_ve_buf_ref, penc->pic.luma);
			goto fail_1;
	}
	if ((penc->pic.chroma&0xc0000000) !=
	    (ptask->tail_ve_buf_ref&0xc0000000)) {
		ERROR(pdev, "illegal input chroma buffer address [ref=%08x][buf=%08x]\n",
			ptask->tail_ve_buf_ref, penc->pic.chroma);
			goto fail_1;
	}

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_2:
	filp_close(filp, NULL);
fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

/* 20130410A */
static int veu_internal_response_result(struct veu_driver *pdev,
	struct veu_task *ptask, unsigned long cond, struct ve_response *ve_resp)
{
	int rtn = 0;
	struct veu_response *presp;

	switch (cond) {
	case VEU_COND_START_UP_PU:
	case VEU_COND_SHUT_DOWN_PU:
		if (list_empty(&pdev->resp_head)) {
			DBG(pdev, "not response(%s)\n",
				veu_internal_to_str(cond));
			rtn = 1;
			break;
		}
		presp = list_entry(pdev->resp_head.next,
				struct veu_response, list);
		if (!test_bit(cond, &presp->resp_flag)) {
			DBG(pdev, "%s unmatch response(0x%x!=0x%x)\n",
				veu_internal_to_str(cond),
				(u32)cond, (u32)presp->resp_flag);
			rtn = 1;
			break;
		}
		list_del(&presp->list);
		pdev->resp_num--;
		if (presp->resp.num_of_params != 1)
			WARN(pdev, "%s has wrong num_of_params(%d)\n",
				veu_internal_to_str(cond),
				presp->resp.num_of_params);
		*ve_resp = presp->resp;
		kfree(presp);
		break;
	case VEU_COND_INITIALIZE_TASK:
	case VEU_COND_INITIALIZE_IOBUFFER:
	case VEU_COND_ENCODE:
		if (!ptask) {
			rtn = 1;
			break;
		}
		if (list_empty(&ptask->resp_head)) {
			DBG(pdev, "not response(%s)\n",
				veu_internal_to_str(cond));
			rtn = 1;
			break;
		}
		presp = list_entry(ptask->resp_head.next,
				struct veu_response, list);
		if (!test_bit(cond, &presp->resp_flag)) {
			DBG(pdev, "%s unmatch response(0x%x!=0x%x)\n",
				veu_internal_to_str(cond),
				(u32)cond, (u32)presp->resp_flag);
			rtn = 1;
			break;
		}
		list_del(&presp->list);
		ptask->resp_num--;
		if (cond != VEU_COND_ENCODE) {
			if (presp->resp.num_of_params != 1)
				WARN(pdev, "%s has wrong num_of_params(%d)\n",
					veu_internal_to_str(cond),
					presp->resp.num_of_params);
		}
		*ve_resp = presp->resp;
		kfree(presp);
		break;
	default:
	case VEU_COND_KILL_TASK:
		if (!ptask) {
			rtn = 1;
			break;
		}
		if (list_empty(&ptask->resp_head)) {
			DBG(pdev, "not response(%s)\n",
				veu_internal_to_str(cond));
			rtn = 1;
			break;
		}
		presp = list_entry(ptask->resp_head.next,
				struct veu_response, list);
		if (!test_bit(cond, &presp->resp_flag)) {
			DBG(pdev, "%s unmatch response(0x%x!=0x%x)\n",
				veu_internal_to_str(cond),
				(u32)cond, (u32)presp->resp_flag);
			rtn = 1;
			break;
		}
		list_del(&presp->list);
		ptask->resp_num--;
		ve_resp->task = presp->msg.task;
		ve_resp->command = VE_CMD_KILL_TASK;
		ve_resp->num_of_params = 1;
		ve_resp->param[0] = presp->msg.param;
		kfree(presp);
		break;
	}

	return rtn;
}

/* 20130410A */
static int veu_internal_searchtask_for_ctx(struct veu_driver *pdev,
		struct ve_task *ctx, struct veu_task **rtask)
{
	int ierr = -EVEUBTSKID;
	struct veu_task *ptask, *next;

	DBG(pdev, "enter\n");

	*rtask = NULL;

	list_for_each_entry_safe(ptask, next, &pdev->task_head, list) {
		if (ctx == ptask->ctx) {
			*rtask = ptask;
			ierr = 0;
			break;
		}
	}

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

/* 20130410A */
static char *veu_internal_to_str(unsigned long cond)
{
	switch (cond) {
	case VEU_COND_START_UP_PU:
		return "VE_CMD_START_UP_PU";
	case VEU_COND_SHUT_DOWN_PU:
		return "VE_CMD_SHUT_DOWN_PU";
	case VEU_COND_INITIALIZE_TASK:
		return "VE_CMD_INITIALIZE_TASK";
	case VEU_COND_INITIALIZE_IOBUFFER:
		return "VE_CMD_INITIALIZE_IOBUFFER";
	case VEU_COND_ENCODE:
		return "VE_CMD_ENCODE";
	case VEU_COND_KILL_TASK:
		return "VE_CMD_KILL_TASK";
	default:
		 return "UNKNOWN";
	}

}

#ifdef __KEEP_FWAREA
int veu_internal_alloc_fwarea(struct veu_driver *pdev)
{
	int ierr = 0;

	/* allocate VIP4 FW area */
	ierr = veu_internal_memory_alloc(pdev, pdev->device, VEU_FW_AREA_SIZE,
		VEU_MEM_TYPE_DMA_FW, VEU_MEM_ALIGN_16M, &ve_fw_area);
	if (ierr != 0)
		return ierr;

	return ierr;
}

void veu_internal_free_fwarea(struct veu_driver *pdev)
{
	/* free VE_FW_AREA */
	veu_internal_memory_free(pdev, pdev->device, &ve_fw_area);
}
#endif

int veu_internal_alloc_tracearea(struct veu_driver *pdev, int area_size)
{
	int ierr = 0;

	/* allocate trace area */
	ierr = veu_internal_memory_alloc(pdev, pdev->device, area_size*1024,
		VEU_MEM_TYPE_DMA, VEU_MEM_ALIGN_16, &ve_trace_area);
	if (ierr != 0)
		return ierr;

	return ierr;
}

void veu_internal_free_tracearea(struct veu_driver *pdev)
{
	/* free trace area */
	veu_internal_memory_free(pdev, pdev->device, &ve_trace_area);
}

int veu_internal_get_tracearea(struct veu_driver *pdev,
	uint32_t *v_addr, uint32_t *p_addr)
{
	*v_addr = 0;
	*p_addr = 0;
	if (ve_trace_area.size > 0) {
		*v_addr = (uint32_t)ve_trace_area.addr;
		*p_addr = (uint32_t)ve_trace_area.dma_addr;
	}

	return (int)ve_trace_area.size;
}
