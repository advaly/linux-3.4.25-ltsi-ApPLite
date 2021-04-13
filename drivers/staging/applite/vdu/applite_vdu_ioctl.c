/*
 * drivers/staging/applite/vdu/applite_vdu_ioctl.c
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
#include <linux/sched.h>         /* task_struct */
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

#include <linux/applite/applite_vdu.h>
#include "applite_vdu_internal.h"

/*===================================
Static Variables and Functions prototypes
===================================*/


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

int vdu_ioctl_start(struct vdu_driver *pdev,
	struct vdec_start *pstart, uint32_t *taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	/* check parameter */
	if (pstart->in_outbuffer.fd < 0) {
		ERROR(pdev, "invalid argument [in_outbuffer.fd=%d]\n",
			pstart->in_outbuffer.fd);
		ierr = -EINVAL;
		goto fail_1;
	}
	if (pstart->in_outbuffersize < VDU_TASK_FRAME_SIZE_KiB) {
		ERROR(pdev, "invalid argument [in_outbuffersize=%d]\n",
			pstart->in_outbuffersize);
		ierr = -EINVAL;
		goto fail_1;
	}
	if (pstart->in_uf_thr > (pdev->vdu_task_std_size-1)) {
		ERROR(pdev, "invalid argument [in_uf_thr=%d]\n",
			pstart->in_uf_thr);
		ierr = -EINVAL;
		goto fail_1;
	}
	if (pstart->in_decoder != VDEC_DECODER_TYPE_H264) {
		ERROR(pdev, "invalid argument [decoder=%d]\n",
			pstart->in_decoder);
		ierr = -EINVAL;
		goto fail_1;
	}

	ierr = vdu_internal_start(pdev, pstart, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_ioctl_stop(struct vdu_driver *pdev, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_stop(pdev, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_ioctl_getininfo(struct vdu_driver *pdev,
	struct vdec_getininfo *pgetininfo, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_getininfo(pdev, pgetininfo, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_ioctl_setindata(struct vdu_driver *pdev,
	struct vdec_setindata *psetindata, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_setindata(pdev, psetindata, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_ioctl_getoutframe(struct vdu_driver *pdev,
	struct vdec_getoutframe *pgetoutframe, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_getoutframe(pdev, pgetoutframe, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_ioctl_reloutframe(struct vdu_driver *pdev, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_reloutframe(pdev, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}


int vdu_ioctl_waitforinbuf(struct vdu_driver *pdev,
	struct vdec_waitforinbuf *pwaitforinbuf, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_waitforinbuf(pdev, pwaitforinbuf, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_ioctl_waitforoutframe(struct vdu_driver *pdev,
	struct vdec_waitforoutframe *pwaitforoutframe, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_waitforoutframe(pdev, pwaitforoutframe, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_ioctl_cancel(struct vdu_driver *pdev, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_cancel(pdev, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int vdu_ioctl_getoutframewithconv(struct vdu_driver *pdev,
	struct vdec_getoutframewithconv *pgetoutframewithconv,
	uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = vdu_internal_getoutframewithconv(pdev,
		pgetoutframewithconv, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}
