/*
 * linux/drivers/staging/applite/applite_yuvc_procfs.c
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

/*===================================
Include Files
===================================*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/applite/applite_yuvc.h>
#include "applite_yuvc_internal.h"
#include "applite_yuvc_dbg.h"


/*===================================
Static Variables and Functions prototypes
===================================*/
#define YUVC_MAX_BUF_SIZE			(20)
#define YUVC_DUMP_REG_LINE			(20)

static struct proc_dir_entry *pst_yuvc_proc;

#if defined(CONFIG_PROC_FS)

static void *yuvc_reg_seq_start(struct seq_file *seq, loff_t *pos);
static void *yuvc_reg_seq_next(struct seq_file *seq, void *v, loff_t *pos);
static void yuvc_reg_seq_stop(struct seq_file *seq, void *v);
static int yuvc_reg_seq_show(struct seq_file *seq, void *v);
static int yuvc_reg_seq_open(struct inode *inode, struct file *file);

static const struct seq_operations yuvc_reg_seq_ops = {
	.start = yuvc_reg_seq_start,
	.next  = yuvc_reg_seq_next,
	.stop  = yuvc_reg_seq_stop,
	.show  = yuvc_reg_seq_show,
};

static const struct file_operations yuvc_reg_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = yuvc_reg_seq_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release,
};

static int yuvc_sts_seq_show(struct seq_file *seq, void *v);
static int yuvc_sts_seq_open(struct inode *inode, struct file *file);

static const struct file_operations yuvc_sts_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = yuvc_sts_seq_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

static int yuvc_log_seq_show(struct seq_file *seq, void *v);
static int yuvc_log_seq_open(struct inode *inode, struct file *file);
static ssize_t yuvc_log_seq_write(struct file *file, const char __user *buf,
					size_t count, loff_t *ppos);

static const struct file_operations yuvc_log_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = yuvc_log_seq_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.write   = yuvc_log_seq_write,
	.release = single_release,
};

static struct yuvc_reg_list {
	__u32	offset;
	char	*name;
} g_reg_list[] = {
	{YUVC_REG(START),					"START"},
	{YUVC_REG(RESET),					"RESET"},
	{YUVC_REG(MODE),					"MODE"},
	{YUVC_REG(SIZE),					"SIZE"},
	{YUVC_REG(OFFSET_Y),				"OFFSET_Y"},
	{YUVC_REG(OFFSET_UV),				"OFFSET_UV"},
	{YUVC_REG(YCOEF_RG),				"YCOEF_RG"},
	{YUVC_REG(YCOEF_B),					"YCOEF_B"},
	{YUVC_REG(UCOEF_RG),				"UCOEF_RG"},
	{YUVC_REG(UCOEF_B),					"UCOEF_B"},
	{YUVC_REG(VCOEF_RG),				"VCOEF_RG"},
	{YUVC_REG(VCOEF_B),					"VCOEF_B"},
	{YUVC_REG(OFFSET_RG),				"OFFSET_RG"},
	{YUVC_REG(OFFSET_B),				"OFFSET_B"},
	{YUVC_REG(STADR),					"STADR"},
	{YUVC_REG(ENDADR),					"ENDADR"},
	{YUVC_REG(DMRADR),					"DMRADR"},
	{YUVC_REG(CFG),						"CFG"},
	{YUVC_REG(INT_MASK),				"INT_MASK"},
	{YUVC_REG(W_ENABLE),				"W_ENABLE"},
	{YUVC_REG(W00_STADR),				"W00_STADR"},
	{YUVC_REG(W00_ENDADR),				"W00_ENDADR"},
	{YUVC_REG(W00_HEIGHT),				"W00_HEIGHT"},
	{YUVC_REG(W00_PITCH),				"W00_PITCH"},
	{YUVC_REG(W00_CFG0),				"W00_CFG0"},
	{YUVC_REG(W00_SRAM_BASE),			"W00_SRAM_BASE"},
	{YUVC_REG(W00_SRAM_SIZE),			"W00_SRAM_SIZE"},
#if 0
	{YUVC_REG(W01_STADR),				"W01_STADR"},
	{YUVC_REG(W01_ENDADR),				"W01_ENDADR"},
	{YUVC_REG(W01_HEIGHT),				"W01_HEIGHT"},
	{YUVC_REG(W01_PITCH),				"W01_PITCH"},
	{YUVC_REG(W01_CFG0),				"W01_CFG0"},
	{YUVC_REG(W01_CFG1),				"W01_CFG1"},
	{YUVC_REG(W01_SRAM_BASE),			"W01_SRAM_BASE"},
	{YUVC_REG(W01_SRAM_SIZE),			"W01_SRAM_SIZE"},
	{YUVC_REG(W01_INTL),				"W01_INTL"},
	{YUVC_REG(MODE_BUF),				"MODE_BUF"},
	{YUVC_REG(SIZE_BUF),				"SIZE_BUF"},
	{YUVC_REG(OFFSET_Y_BUF),			"OFFSET_Y_BUF"},
	{YUVC_REG(OFFSET_UV_BUF),			"OFFSET_UV_BUF"},
	{YUVC_REG(YCOEF_RG_BUF),			"YCOEF_RG_BUF"},
	{YUVC_REG(YCOEF_B_BUF),				"YCOEF_B_BUF"},
	{YUVC_REG(UCOEF_RG_BUF),			"UCOEF_RG_BUF"},
	{YUVC_REG(UCOEF_B_BUF),				"UCOEF_B_BUF"},
	{YUVC_REG(VCOEF_RG_BUF),			"VCOEF_RG_BUF"},
	{YUVC_REG(VCOEF_B_BUF),				"VCOEF_B_BUF"},
	{YUVC_REG(OFFSET_RG_BUF),			"OFFSET_RG_BUF"},
	{YUVC_REG(OFFSET_B_BUF),			"OFFSET_B_BUF"},
	{YUVC_REG(W_ENABLE_BUF),			"W_ENABLE_BUF"},
	{YUVC_REG(W00_STADR_BUF),			"W00_STADR_BUF"},
	{YUVC_REG(W00_ENDADR_BUF),			"W00_ENDADR_BUF"},
	{YUVC_REG(W00_HEIGHT_BUF),			"W00_HEIGHT_BUF"},
	{YUVC_REG(W00_PITCH_BUF),			"W00_PITCH_BUF"},
	{YUVC_REG(W00_CFG0_BUF),			"W00_CFG0_BUF"},
	{YUVC_REG(W00_CFG1_BUF),			"W00_CFG1_BUF"},
	{YUVC_REG(W01_STADR_BUF),			"W01_STADR_BUF"},
	{YUVC_REG(W01_ENDADR_BUF),			"W01_ENDADR_BUF"},
	{YUVC_REG(W01_HEIGHT_BUF),			"W01_HEIGHT_BUF"},
	{YUVC_REG(W01_PITCH_BUF),			"W01_PITCH_BUF"},
	{YUVC_REG(W01_CFG0_BUF),			"W01_CFG0_BUF"},
	{YUVC_REG(W01_CFG1_BUF),			"W01_CFG1_BUF"},
#endif
	{YUVC_REG(STATUS),					"STATUS"},
	{YUVC_REG(INT),						"INT"},
	{YUVC_REG(W_STOP),					"W_STOP"},
	{YUVC_REG(W_RUN),					"W_RUN"},
#if 0
	{YUVC_REG(D00_STADRMON),			"D00_STADRMON"},
	{YUVC_REG(W00_LINEMON),				"W00_LINEMON"},
	{YUVC_REG(W00_STADRMON),			"W00_STADRMON"},
	{YUVC_REG(W01_LINEMON),				"W01_LINEMON"},
	{YUVC_REG(W01_STADRMON),			"W01_STADRMON"},
#endif
};

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



/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static void yuvc_dump_yuvc_dev_info(struct seq_file *seq)
{
	seq_printf(seq, "struct yuvc_dev : [0x%p] =====\n", &s_yuvc_dev);
	seq_printf(seq, "\tdevice         : 0x%p\n", s_yuvc_dev.device);
#if 0
	seq_printf(seq, "\tlock_dev       : [%d]\n", s_yuvc_dev.lock_dev.rlock.raw_lock.lock);
	seq_printf(seq, "\tlock_reg       : [%d]\n", s_yuvc_dev.lock_reg.rlock.raw_lock.lock);
	seq_printf(seq, "\tmutex_run      : [%d/%d]\n",
		atomic_read(&(s_yuvc_dev.mutex_run.count)),
		s_yuvc_dev.mutex_run.wait_lock.rlock.raw_lock.lock);
#endif	/* notdef */
	seq_printf(seq, "\tul_open_count  : %d\n",
		atomic_read(&(s_yuvc_dev.ul_open_count)));
	seq_printf(seq, "\tb_run          : %d\n", s_yuvc_dev.b_run);
	seq_printf(seq, "==  ioremap address\n");
	seq_printf(seq, "\tyuvcbase       : 0x%p\n", s_yuvc_dev.yuvcbase);
/*	seq_printf(seq, "\tyvdmacbase     : 0x%p\n", s_yuvc_dev.yvdmacbase); */
	seq_printf(seq, "\tpmubase        : 0x%p\n", s_yuvc_dev.pmubase);

#if 0
	seq_printf(seq, "==  interrupt counter\n");
	seq_printf(seq, "\tframe_end      : %d\n",
		s_yuvc_dev.ul_num_frame_end_irq);
	seq_printf(seq, "\tstart err      : %d\n",
		s_yuvc_dev.ul_num_start_err_irq);
	seq_printf(seq, "\treg err        : %d\n",
		s_yuvc_dev.ul_num_reg_err_irq);
	seq_printf(seq, "\tdisp err       : %d\n",
		s_yuvc_dev.ul_num_disp_err_irq);
	seq_printf(seq, "\tmerge err      : %d\n",
		s_yuvc_dev.ul_num_merge_err_irq);
#endif
	seq_printf(seq, "==================================\n");
}


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static void *yuvc_reg_seq_start(struct seq_file *seq, loff_t *pos)
{
	YUVC_FUNC_START("seq(%p), *pos(%lld)\n", seq, *pos);
	if (*pos >= ARRAY_SIZE(g_reg_list))
		return NULL;

	if (*pos != 0)
		*pos += (YUVC_DUMP_REG_LINE - 1);

	YUVC_FUNC_END("\n");
	return pos;
}
/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static void *yuvc_reg_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	YUVC_FUNC_START("seq(%p), v(%p), *pos(%lld), size(%d)\n",
				seq, v, *pos, ARRAY_SIZE(g_reg_list));
	if (*pos < ARRAY_SIZE(g_reg_list)) {
		*pos += YUVC_DUMP_REG_LINE;
	} else {
		YUVC_INFO("over reg list[%lld, %d]\n",
				*pos, ARRAY_SIZE(g_reg_list));
		pos = NULL;
	}
	YUVC_FUNC_END("\n");

	return pos;
}
/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static void yuvc_reg_seq_stop(struct seq_file *seq, void *v)
{
	YUVC_FUNC_START("seq(%p), v(%p)(%08x)\n",
				seq, v, v == NULL ? 0 : *((__u32 *)(v)));
	YUVC_FUNC_END("\n");
}
/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int yuvc_reg_seq_show(struct seq_file *seq, void *v)
{
	int i, j;
	YUVC_FUNC_START("seq(%p), v(%p)(%d)\n",
				seq, v, v == NULL ? 0 : *((__u32 *)(v)));
	i = *(int *)v;
	if (i == 0)
		seq_printf(seq, "No.\tREGISTER NAME       : OFFSET   : VAL\n");

	if (i < ARRAY_SIZE(g_reg_list)) {
		for (j = 0;
			(i < ARRAY_SIZE(g_reg_list)) &&
				(j < YUVC_DUMP_REG_LINE); i++, j++) {
			seq_printf(seq, "%3d\t%20s:[%08x]: %08x\n",
				i,
				g_reg_list[i].name,
				g_reg_list[i].offset,
				__raw_readl(s_yuvc_dev.yuvcbase +
						g_reg_list[i].offset));
		}
	}
	YUVC_FUNC_END("\n");

	return 0;
}
/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int yuvc_reg_seq_open(struct inode *inode, struct file *file)
{
	YUVC_FUNC_START("\n");

	return seq_open(file, &yuvc_reg_seq_ops);
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int yuvc_sts_seq_show(struct seq_file *seq, void *v)
{
	yuvc_dump_yuvc_dev_info(seq);
	return 0;
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int yuvc_sts_seq_open(struct inode *inode, struct file *file)
{
	YUVC_FUNC_START("\n");
	return single_open(file, yuvc_sts_seq_show, NULL);
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int yuvc_log_seq_show(struct seq_file *seq, void *v)
{
	static char *f[] =  {"ON", "OFF"};

	YUVC_FUNC_START("\n");
	seq_printf(seq, "log level = %d\n", ul_logflags);
	seq_printf(seq, "    FUNCTION IN/OUT LOG : %s\n",
			(ul_logflags & YUVC_LOG_FUNCTION ? f[0] : f[1]));
	seq_printf(seq, "    PERFORMANCE LOG     : %s\n",
			(ul_logflags & YUVC_LOG_PERFORMANCE ? f[0] : f[1]));
	seq_printf(seq, "    OTHER LOG           : %s\n",
			(ul_logflags & YUVC_LOG_INFORMATION ? f[0] : f[1]));

	YUVC_FUNC_END("\n");
	return 0;
}
/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int yuvc_log_seq_open(struct inode *inode, struct file *file)
{
	YUVC_FUNC_START("\n");
	return single_open(file, yuvc_log_seq_show, NULL);
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static ssize_t yuvc_log_seq_write(struct file *file, const char __user *buf,
				size_t count, loff_t *ppos)
{
	int iret;
	unsigned long logflags;

	YUVC_FUNC_START("\n");

	iret = kstrtoul_from_user(buf, count, 10, &logflags);
	if (iret != 0) {
		YUVC_ERR("kstrtoul_from_user() failed\n");
		return iret;
	}

	ul_logflags = logflags;

	YUVC_FUNC_END("\n");
	return count;
}

#endif	/* CONFIG_PROC_FS */

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
void yuvc_procfs_create(void)
{
	YUVC_FUNC_START("\n");

#if defined(CONFIG_PROC_FS)
	/* create /proc/yuvc/ directory */
	pst_yuvc_proc = proc_mkdir(PROC_DEVICE_NAME, NULL);
	YUVC_INFO("/proc/%s entry = %p\n", PROC_DEVICE_NAME, pst_yuvc_proc);
	if (pst_yuvc_proc == NULL) {
		YUVC_ERR("proc_mkdir(%s) failed\n", PROC_DEVICE_NAME);
		return;
	}
	/* create /proc/yuvc/status file with read-only */
	proc_create(PROC_STS_NAME, 0, pst_yuvc_proc, &yuvc_sts_proc_fops);
	/* create /proc/yuvc/regs file with read-only */
	proc_create(PROC_REG_NAME, 0, pst_yuvc_proc, &yuvc_reg_proc_fops);
	/* create /proc/yuvc/logflag file with read-write */
	proc_create(PROC_LOGFLAG_NAME, S_IRUGO | S_IWUGO,
					pst_yuvc_proc, &yuvc_log_proc_fops);
#endif	/* CONFIG_PROC_FS */

	YUVC_FUNC_END("\n");
}

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
void yuvc_procfs_remove(void)
{
	YUVC_FUNC_START("\n");

#if defined(CONFIG_PROC_FS)
	YUVC_INFO("/proc/%s entry = %p\n", PROC_DEVICE_NAME, pst_yuvc_proc);
	if (pst_yuvc_proc != NULL) {
		/* remove /proc/yuvc/status file */
		YUVC_INFO("remove /proc/%s/%s\n",
			PROC_DEVICE_NAME, PROC_STS_NAME);
		remove_proc_entry(PROC_STS_NAME, pst_yuvc_proc);
		/* remove /proc/yuvc/regs file */
		YUVC_INFO("remove /proc/%s/%s\n",
			PROC_DEVICE_NAME, PROC_REG_NAME);
		remove_proc_entry(PROC_REG_NAME, pst_yuvc_proc);
		/* remove /proc/yuvc/logflag file */
		YUVC_INFO("remove /proc/%s/%s\n",
			PROC_DEVICE_NAME, PROC_LOGFLAG_NAME);
		remove_proc_entry(PROC_LOGFLAG_NAME, pst_yuvc_proc);
		/* remove /proc/yuvc/ directory */
		YUVC_INFO("remove /proc/%s/\n", PROC_DEVICE_NAME);
		remove_proc_entry(PROC_DEVICE_NAME, NULL);
	}
#endif	/* CONFIG_PROC_FS */

	YUVC_FUNC_END("\n");
}
