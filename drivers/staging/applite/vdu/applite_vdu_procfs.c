/*
 * drivers/staging/applite/vdu/applite_vdu_procfs.c
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
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/applite/applite_vdu.h>
#include "applite_vdu_internal.h"


/*===================================
Static Variables and Functions prototypes
===================================*/

#if defined(CONFIG_PROC_FS)
static void *vdu_seq_start(struct seq_file *seq, loff_t *pos);
static void *vdu_seq_next(struct seq_file *seq, void *v, loff_t *pos);
static void vdu_seq_stop(struct seq_file *seq, void *v);
static int vdu_seq_show(struct seq_file *seq, void *v);
static int vdu_seq_open(struct inode *inode, struct file *file);

static const struct seq_operations vdu_seq_ops = {
	.start = vdu_seq_start,
	.next  = vdu_seq_next,
	.stop  = vdu_seq_stop,
	.show  = vdu_seq_show,
};

static const struct file_operations vdu_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = vdu_seq_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release,
};

#endif     /* CONFIG_PROC_FS */


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




#if defined(CONFIG_PROC_FS)
static void *vdu_seq_start(struct seq_file *seq, loff_t *pos)
{
	return NULL;
}
static void *vdu_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	return NULL;
}
static void vdu_seq_stop(struct seq_file *seq, void *v)
{
}
static int vdu_seq_show(struct seq_file *seq, void *v)
{
	return 0;
}
static int vdu_seq_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &vdu_seq_ops);
}

#endif     /* CONFIG_PROC_FS */

void vdu_procfs_create(void)
{
#if defined(CONFIG_PROC_FS)
	proc_create(VDU_PROC_DEVICE_NAME, 0, NULL, &vdu_proc_fops);
#endif     /* CONFIG_PROC_FS */
}

void vdu_procfs_remove(void)
{
#if defined(CONFIG_PROC_FS)
	remove_proc_entry(VDU_PROC_DEVICE_NAME, NULL);
#endif     /* CONFIG_PROC_FS */
}
