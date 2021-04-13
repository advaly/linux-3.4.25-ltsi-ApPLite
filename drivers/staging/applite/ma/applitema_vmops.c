/*
 * linux/drivers/staging/applite/ma/applitema_vmops.c
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * original code from drivers/media/video/videobuf2-memops.c
 */

#include <linux/module.h>
#include <linux/mm.h>
#include "applitema_vmops.h"

/**
 * applitema_common_vm_open() - increase refcount of the vma
 * @vma:	virtual memory region for the mapping
 *
 * This function adds another user to the provided vma. It expects
 * struct applitema_vmarea_handler pointer in vma->vm_private_data.
 */
static void applitema_common_vm_open(struct vm_area_struct *vma)
{
	struct applitema_vmarea_handler *h = vma->vm_private_data;

	atomic_inc(h->refcount);
}

/**
 * applitema_common_vm_close() - decrease refcount of the vma
 * @vma:	virtual memory region for the mapping
 *
 * This function releases the user from the provided vma. It expects
 * struct applitema_vmarea_handler pointer in vma->vm_private_data.
 */
static void applitema_common_vm_close(struct vm_area_struct *vma)
{
	struct applitema_vmarea_handler *h = vma->vm_private_data;

	h->put(h->arg);
}

/**
 * applitema_common_vm_ops - common vm_ops used for tracking refcount of mmaped
 * video buffers
 */
const struct vm_operations_struct applitema_common_vm_ops = {
	.open = applitema_common_vm_open,
	.close = applitema_common_vm_close,
};
EXPORT_SYMBOL_GPL(applitema_common_vm_ops);

