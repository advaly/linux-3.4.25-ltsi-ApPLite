/*
 * drivers/staging/applite/veu/applite_veu_procfs.c
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
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/interrupt.h> /* tasklet */
#include <linux/sched.h>     /* task_struct */
#include <linux/wait.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>

#include <linux/applite/applite_veu.h>
#include "applite_veu_internal.h"


/*===================================
Static Variables and Functions prototypes
===================================*/

#if defined(CONFIG_PROC_FS)
static int veu_proc_trace_open(struct inode *, struct file *);
static ssize_t veu_proc_trace_write(struct file *, const char __user *,
	size_t, loff_t *);
static int veu_proc_dump_open(struct inode *, struct file *);


static const struct file_operations veu_proc_trace_fops = {
	.owner   = THIS_MODULE,
	.open    = veu_proc_trace_open,
	.read    = seq_read,
	.write   = veu_proc_trace_write,
	.llseek  = seq_lseek,
	.release = seq_release,
};
static const struct file_operations veu_proc_dump_fops = {
	.owner   = THIS_MODULE,
	.open    = veu_proc_dump_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release,
};
static struct proc_dir_entry *veu_proc_trace_e;
static struct proc_dir_entry *veu_proc_dump_e;
static struct proc_dir_entry *veu_proc_root;
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
static int veu_dump_show(struct seq_file *seq, void *v)
{
	int trace_area_size;
	int i;
	uint32_t v_addr;
	uint32_t p_addr;
	unsigned char *c;

	DBG(&s_veu_dev, "enter\n");
	trace_area_size = veu_internal_get_tracearea(&s_veu_dev,
		&v_addr, &p_addr);
	if (trace_area_size && v_addr) {
		c = (unsigned char *)v_addr;
		for (i = 0; i < trace_area_size; i++, c++)
			seq_printf(seq, "%c", *c);
	}
	DBG(&s_veu_dev, "leave\n");
	return 0;
}

static int veu_proc_dump_open(struct inode *inode, struct file *file)
{
	int ierr = 0;
	DBG(&s_veu_dev, "enter\n");
	ierr = single_open(file, veu_dump_show, PDE(inode)->data);
	DBG(&s_veu_dev, "leave\n");
	return ierr;
}

static ssize_t veu_proc_trace_write(struct file *file, const char __user *buf,
	size_t count, loff_t *pos)
{
	char lbuf[256];
	int trace_area_size;

	DBG(&s_veu_dev, "enter [count=%d]\n", count);

	down(&s_veu_dev.veu_sem);

	if (s_veu_dev.devsts != VEU_STAT_NOFW) {
		WARNING(&s_veu_dev, "not setup trace area\n");
		up(&s_veu_dev.veu_sem);
		return -1;
	}

	if (count > sizeof(lbuf)-1) {
		ERROR(&s_veu_dev, "illegal string(over flow)\n");
		up(&s_veu_dev.veu_sem);
		return -1;
	}
	memset(lbuf, 0x00, sizeof(lbuf));
	if (copy_from_user((void *)lbuf, (const void __user *)buf, count)) {
		ERROR(&s_veu_dev, "copy_from_user() failed\n");
		up(&s_veu_dev.veu_sem);
		return -1;
	}
	if (strlen(lbuf) > 1)
		lbuf[strlen(lbuf)-1] = 0x00;
	if (!strlen(lbuf)) {
		up(&s_veu_dev.veu_sem);
		return 0;
	}

	sscanf(lbuf, "%d", &trace_area_size);
	if (trace_area_size && (trace_area_size < 1024)) {
		ERROR(&s_veu_dev, "illegal trace area size(%d:set more than 1024KiB)\n", trace_area_size);
		up(&s_veu_dev.veu_sem);
		return -1;
	}
	veu_internal_free_tracearea(&s_veu_dev);
	if (trace_area_size) {
		if (veu_internal_alloc_tracearea(&s_veu_dev,
					trace_area_size) < 0) {
			up(&s_veu_dev.veu_sem);
			return -1;
		}
	}

	up(&s_veu_dev.veu_sem);

	INFO(&s_veu_dev, "trace buffer size:%dKiB\n",
		trace_area_size);

	return count;
}

static int veu_trace_show(struct seq_file *seq, void *v)
{
	int trace_area_size;
	uint32_t v_addr;
	uint32_t p_addr;

	DBG(&s_veu_dev, "enter\n");

	/* trace buffer info */
	trace_area_size = veu_internal_get_tracearea(&s_veu_dev,
		&v_addr, &p_addr);
	seq_printf(seq, "%08X %08X\n", trace_area_size, p_addr);

	DBG(&s_veu_dev, "leave\n");
	return 0;
}

static int veu_proc_trace_open(struct inode *inode, struct file *file)
{
	int ierr = 0;
	DBG(&s_veu_dev, "enter\n");
	ierr = single_open(file, veu_trace_show, PDE(inode)->data);
	DBG(&s_veu_dev, "leave\n");
	return ierr;
}
#endif     /* CONFIG_PROC_FS */

void veu_procfs_create(void)
{
#if defined(CONFIG_PROC_FS)
	veu_proc_trace_e = NULL;
	veu_proc_dump_e = NULL;
	veu_proc_root = NULL;
	DBG(&s_veu_dev, "enter\n");
	veu_proc_root = proc_mkdir(VEU_PROC_DEVICE_NAME, NULL);
	if (!veu_proc_root) {
		ERROR(&s_veu_dev, "proc_mkdir() failed\n");
		return;
	}
	veu_proc_trace_e = proc_create_data("trace", S_IFREG | S_IRUGO | S_IWUSR,
		veu_proc_root, &veu_proc_trace_fops, (void *)0);
	if (!veu_proc_trace_e) {
		ERROR(&s_veu_dev, "proc_create_data(trace) failed\n");
		remove_proc_entry(veu_proc_root->name, NULL);
		veu_proc_root = (struct proc_dir_entry *)0;
		return;
	}
	veu_proc_dump_e = proc_create_data("dump", S_IFREG | S_IRUGO | S_IWUSR,
		veu_proc_root, &veu_proc_dump_fops, (void *)0);
	if (!veu_proc_dump_e) {
		ERROR(&s_veu_dev, "proc_create_data(dump) failed\n");
		remove_proc_entry(veu_proc_trace_e->name, veu_proc_root);
		remove_proc_entry(veu_proc_root->name, NULL);
		veu_proc_root = (struct proc_dir_entry *)0;
		veu_proc_trace_e = (struct proc_dir_entry *)0;
		return;
	}
	DBG(&s_veu_dev, "leave\n");
#endif     /* CONFIG_PROC_FS */
}

void veu_procfs_remove(void)
{
#if defined(CONFIG_PROC_FS)
	DBG(&s_veu_dev, "enter\n");
	if (veu_proc_trace_e)
		remove_proc_entry(veu_proc_trace_e->name, veu_proc_root);
	if (veu_proc_dump_e)
		remove_proc_entry(veu_proc_dump_e->name, veu_proc_root);
	if (veu_proc_root)
		remove_proc_entry(veu_proc_root->name, NULL);
	DBG(&s_veu_dev, "leave\n");
#endif     /* CONFIG_PROC_FS */
}

