/*
 * drivers/staging/applite/veu/applite_veu_ioctl.c
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
#include <linux/list.h>
#include <linux/firmware.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/sched.h>	 /* task_struct */
#include <linux/wait.h>
#include <linux/semaphore.h>
#include <linux/platform_device.h>

#include <linux/applite/applite_veu.h>
#include "applite_veu_internal.h"
#include "applite_veu_common.h"

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

int veu_ioctl_getparam(struct veu_driver *pdev,
	struct venc_getparam *pgetparam, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = veu_internal_getparam(pdev, pgetparam, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_ioctl_setparam(struct veu_driver *pdev,
	struct venc_setparam *psetparam, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = veu_internal_setparam(pdev, psetparam, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_ioctl_setinframe(struct veu_driver *pdev,
	struct venc_setinframe *psetinframe, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	/* check frame id */
	if (psetinframe->in_frameid == VENC_INVALID_FRAME_ID) {
		ERROR(pdev, "invalid frame id\n");
		ierr = -EINVAL;
		goto fail_1;
	}

	ierr = veu_internal_setinframe(pdev, psetinframe, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;

fail_1:
	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_ioctl_waitforevents(struct veu_driver *pdev,
	struct venc_waitforevents *pwaitforevents, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = veu_internal_waitforevents(pdev, pwaitforevents, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_ioctl_getoutframe(struct veu_driver *pdev,
	struct venc_getoutframe *pgetoutframe, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = veu_internal_getoutframe(pdev, pgetoutframe, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);
	return ierr;
}

int veu_ioctl_setinframewithcnv(struct veu_driver *pdev,
	struct venc_setinframewithcnv *psetinframewithcnv, uint32_t taskid)
{
	int ierr = 0;

	DBG(pdev, "enter\n");

	ierr = veu_internal_setinframewithcnv(pdev, psetinframewithcnv, taskid);

	DBG(pdev, "leave [rtn=%d]\n", ierr);

	return ierr;
}
