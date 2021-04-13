/*
 * linux/drivers/staging/applite/applite_vconv_procfs.c
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

#include <linux/applite/applite_vconv.h>
#include "applite_vconv_internal.h"
#include "applite_vconv_dbg.h"


/*===================================
Static Variables and Functions prototypes
===================================*/
#define VCONV_MAX_BUF_SIZE			(20)
#define VCONV_DUMP_REG_LINE			(20)

static struct proc_dir_entry *pst_vconv_proc;

#if defined(CONFIG_PROC_FS)

static void *vconv_reg_seq_start(struct seq_file *seq, loff_t *pos);
static void *vconv_reg_seq_next(struct seq_file *seq, void *v, loff_t *pos);
static void vconv_reg_seq_stop(struct seq_file *seq, void *v);
static int vconv_reg_seq_show(struct seq_file *seq, void *v);
static int vconv_reg_seq_open(struct inode *inode, struct file *file);

static const struct seq_operations vconv_reg_seq_ops = {
	.start = vconv_reg_seq_start,
	.next  = vconv_reg_seq_next,
	.stop  = vconv_reg_seq_stop,
	.show  = vconv_reg_seq_show,
};

static const struct file_operations vconv_reg_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = vconv_reg_seq_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release,
};

static int vconv_sts_seq_show(struct seq_file *seq, void *v);
static int vconv_sts_seq_open(struct inode *inode, struct file *file);

static const struct file_operations vconv_sts_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = vconv_sts_seq_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

static int vconv_log_seq_show(struct seq_file *seq, void *v);
static int vconv_log_seq_open(struct inode *inode, struct file *file);
static ssize_t vconv_log_seq_write(struct file *file, const char __user *buf,
					size_t count, loff_t *ppos);

static const struct file_operations vconv_log_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = vconv_log_seq_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.write   = vconv_log_seq_write,
	.release = single_release,
};

static struct vconv_reg_list {
	__u32	offset;
	char	*name;
} g_reg_list[] = {
	{VCONV_REG(START),			"START"},
	{VCONV_REG(ABORT),			"ABORT"},
	{VCONV_REG(SET_DUMMY_READ),		"SET_DUMMY_READ"},
	{VCONV_REG(SET_BUSIF),			"SET_BUSIF"},
	{VCONV_REG(SET_SEL_ALPHA),		"SET_SEL_ALPHA"},
	{VCONV_REG(IRQ),			"IRQ"},
	{VCONV_REG(SET_IRQ_MASK),		"SET_IRQ_MASK"},
	{VCONV_REG(SET_Y2RMTX_OFFSET),		"SET_Y2RMTX_OFFSET"},
	{VCONV_REG(SET_Y2RMTX_COEF00),		"SET_Y2RMTX_COEF00"},
	{VCONV_REG(SET_Y2RMTX_COEF01),		"SET_Y2RMTX_COEF01"},
	{VCONV_REG(SET_Y2RMTX_COEF02),		"SET_Y2RMTX_COEF02"},
	{VCONV_REG(SET_Y2RMTX_COEF10),		"SET_Y2RMTX_COEF10"},
	{VCONV_REG(SET_Y2RMTX_COEF11),		"SET_Y2RMTX_COEF11"},
	{VCONV_REG(SET_Y2RMTX_COEF12),		"SET_Y2RMTX_COEF12"},
	{VCONV_REG(SET_Y2RMTX_COEF20),		"SET_Y2RMTX_COEF20"},
	{VCONV_REG(SET_Y2RMTX_COEF21),		"SET_Y2RMTX_COEF21"},
	{VCONV_REG(SET_Y2RMTX_COEF22),		"SET_Y2RMTX_COEF22"},
	{VCONV_REG(SET_RGBLIMIT),		"SET_RGBLIMIT"},
	{VCONV_REG(SET_R2YMTX_OFFSET),		"SET_R2YMTX_OFFSET"},
	{VCONV_REG(SET_R2YMTX_COEF00),		"SET_R2YMTX_COEF00"},
	{VCONV_REG(SET_R2YMTX_COEF01),		"SET_R2YMTX_COEF01"},
	{VCONV_REG(SET_R2YMTX_COEF02),		"SET_R2YMTX_COEF02"},
	{VCONV_REG(SET_R2YMTX_COEF10),		"SET_R2YMTX_COEF10"},
	{VCONV_REG(SET_R2YMTX_COEF11),		"SET_R2YMTX_COEF11"},
	{VCONV_REG(SET_R2YMTX_COEF12),		"SET_R2YMTX_COEF12"},
	{VCONV_REG(SET_R2YMTX_COEF20),		"SET_R2YMTX_COEF20"},
	{VCONV_REG(SET_R2YMTX_COEF21),		"SET_R2YMTX_COEF21"},
	{VCONV_REG(SET_R2YMTX_COEF22),		"SET_R2YMTX_COEF22"},
	{VCONV_REG(SET_YLIMIT),			"SET_YLIMIT"},
	{VCONV_REG(SET_CLIMIT),			"SET_CLIMIT"},
	{VCONV_REG(TRANS_IN_FORMAT),		"TRANS_IN_FORMAT"},
	{VCONV_REG(TRANS_IN_HSIZE),		"TRANS_IN_HSIZE"},
	{VCONV_REG(TRANS_IN_VSIZE),		"TRANS_IN_VSIZE"},
	{VCONV_REG(TRANS_IN_BASEADDR_A),	"TRANS_IN_BASEADDR_A"},
	{VCONV_REG(TRANS_IN_BASEADDR_B),	"TRANS_IN_BASEADDR_B"},
	{VCONV_REG(TRANS_IN_BASEADDR_C),	"TRANS_IN_BASEADDR_C"},
	{VCONV_REG(TRANS_IN_PITCH_A),		"TRANS_IN_PITCH_A"},
	{VCONV_REG(TRANS_IN_PITCH_B),		"TRANS_IN_PITCH_B"},
	{VCONV_REG(TRANS_IN_PITCH_C),		"TRANS_IN_PITCH_C"},
	{VCONV_REG(TRANS_OUT_FORMAT),		"TRANS_OUT_FORMAT"},
	{VCONV_REG(TRANS_OUT_HSIZE),		"TRANS_OUT_HSIZE"},
	{VCONV_REG(TRANS_OUT_VSIZE),		"TRANS_OUT_VSIZE"},
	{VCONV_REG(TRANS_OUT_BASEADDR_A),	"TRANS_OUT_BASEADDR_A"},
	{VCONV_REG(TRANS_OUT_BASEADDR_B),	"TRANS_OUT_BASEADDR_B"},
	{VCONV_REG(TRANS_OUT_BASEADDR_C),	"TRANS_OUT_BASEADDR_C"},
	{VCONV_REG(TRANS_OUT_PITCH_A),		"TRANS_OUT_PITCH_A"},
	{VCONV_REG(TRANS_OUT_PITCH_B),		"TRANS_OUT_PITCH_B"},
	{VCONV_REG(TRANS_OUT_PITCH_C),		"TRANS_OUT_PITCH_C"},
	{VCONV_REG(TRANS_OUT_HOFFSET),		"TRANS_OUT_HOFFSET"},
	{VCONV_REG(TRANS_OUT_VOFFSET),		"TRANS_OUT_VOFFSET"},
	{VCONV_REG(TRANS_OUT_HSCALE),		"TRANS_OUT_HSCALE"},
	{VCONV_REG(TRANS_OUT_VSCALE),		"TRANS_OUT_VSCALE"},
	{VCONV_REG(TRANS_OUT_HDELTA),		"TRANS_OUT_HDELTA"},
	{VCONV_REG(TRANS_OUT_VDELTA),		"TRANS_OUT_VDELTA"},
	{VCONV_REG(TRANS_FORCE_MODE),		"TRANS_FORCE_MODE"},
	{VCONV_REG(CH_FORCE_GY),		"CH_FORCE_GY"},
	{VCONV_REG(CH_FORCE_BCB),		"CH_FORCE_BCB"},
	{VCONV_REG(CH_FORCE_R),			"CH_FORCE_R"},
	{VCONV_REG(CH_FORCE_A),			"CH_FORCE_A"},
	{VCONV_REG(TRANS_CROP),			"TRANS_CROP"},
	{VCONV_REG(TRANS_STATUS),		"TRANS_STATUS"},
	{VCONV_REG(TRANS_LINE),			"TRANS_LINE"},
	{VCONV_REG(SET_IN_FORMAT0),		"SET_IN_FORMAT0"},
	{VCONV_REG(SET_IN_HSIZE0),		"SET_IN_HSIZE0"},
	{VCONV_REG(SET_IN_VSIZE0),		"SET_IN_VSIZE0"},
	{VCONV_REG(SET_IN_BASEADDR_A0),		"SET_IN_BASEADDR_A0"},
	{VCONV_REG(SET_IN_BASEADDR_B0),		"SET_IN_BASEADDR_B0"},
	{VCONV_REG(SET_IN_BASEADDR_C0),		"SET_IN_BASEADDR_C0"},
	{VCONV_REG(SET_IN_PITCH_A0),		"SET_IN_PITCH_A0"},
	{VCONV_REG(SET_IN_PITCH_B0),		"SET_IN_PITCH_B0"},
	{VCONV_REG(SET_IN_PITCH_C0),		"SET_IN_PITCH_C0"},
	{VCONV_REG(SET_OUT_FORMAT0),		"SET_OUT_FORMAT0"},
	{VCONV_REG(SET_OUT_HSIZE0),		"SET_OUT_HSIZE0"},
	{VCONV_REG(SET_OUT_VSIZE0),		"SET_OUT_VSIZE0"},
	{VCONV_REG(SET_OUT_BASEADDR_A0),	"SET_OUT_BASEADDR_A0"},
	{VCONV_REG(SET_OUT_BASEADDR_B0),	"SET_OUT_BASEADDR_B0"},
	{VCONV_REG(SET_OUT_BASEADDR_C0),	"SET_OUT_BASEADDR_C0"},
	{VCONV_REG(SET_OUT_PITCH_A0),		"SET_OUT_PITCH_A0"},
	{VCONV_REG(SET_OUT_PITCH_B0),		"SET_OUT_PITCH_B0"},
	{VCONV_REG(SET_OUT_PITCH_C0),		"SET_OUT_PITCH_C0"},
	{VCONV_REG(SET_OUT_HOFFSET0),		"SET_OUT_HOFFSET0"},
	{VCONV_REG(SET_OUT_VOFFSET0),		"SET_OUT_VOFFSET0"},
	{VCONV_REG(SET_OUT_HSCALE0),		"SET_OUT_HSCALE0"},
	{VCONV_REG(SET_OUT_VSCALE0),		"SET_OUT_VSCALE0"},
	{VCONV_REG(SET_OUT_HDELTA0),		"SET_OUT_HDELTA0"},
	{VCONV_REG(SET_OUT_VDELTA0),		"SET_OUT_VDELTA0"},
	{VCONV_REG(SET_FORCE_MODE0),		"SET_FORCE_MODE0"},
	{VCONV_REG(SET_FORCE_GY0),		"SET_FORCE_GY0"},
	{VCONV_REG(SET_FORCE_BCB0),		"SET_FORCE_BCB0"},
	{VCONV_REG(SET_FORCE_RCR0),		"SET_FORCE_RCR0"},
	{VCONV_REG(SET_FORCE_A0),		"SET_FORCE_A0"},
	{VCONV_REG(SET_CROP0),			"SET_CROP0"},
#if 1
	{VCONV_REG(SET_IN_FORMAT1),		"SET_IN_FORMAT1"},
	{VCONV_REG(SET_IN_HSIZE1),		"SET_IN_HSIZE1"},
	{VCONV_REG(SET_IN_VSIZE1),		"SET_IN_VSIZE1"},
	{VCONV_REG(SET_IN_BASEADDR_A1),		"SET_IN_BASEADDR_A1"},
	{VCONV_REG(SET_IN_BASEADDR_B1),		"SET_IN_BASEADDR_B1"},
	{VCONV_REG(SET_IN_BASEADDR_C1),		"SET_IN_BASEADDR_C1"},
	{VCONV_REG(SET_IN_PITCH_A1),		"SET_IN_PITCH_A1"},
	{VCONV_REG(SET_IN_PITCH_B1),		"SET_IN_PITCH_B1"},
	{VCONV_REG(SET_IN_PITCH_C1),		"SET_IN_PITCH_C1"},
	{VCONV_REG(SET_OUT_FORMAT1),		"SET_OUT_FORMAT1"},
	{VCONV_REG(SET_OUT_HSIZE1),		"SET_OUT_HSIZE1"},
	{VCONV_REG(SET_OUT_VSIZE1),		"SET_OUT_VSIZE1"},
	{VCONV_REG(SET_OUT_BASEADDR_A1),	"SET_OUT_BASEADDR_A1"},
	{VCONV_REG(SET_OUT_BASEADDR_B1),	"SET_OUT_BASEADDR_B1"},
	{VCONV_REG(SET_OUT_BASEADDR_C1),	"SET_OUT_BASEADDR_C1"},
	{VCONV_REG(SET_OUT_PITCH_A1),		"SET_OUT_PITCH_A1"},
	{VCONV_REG(SET_OUT_PITCH_B1),		"SET_OUT_PITCH_B1"},
	{VCONV_REG(SET_OUT_PITCH_C1),		"SET_OUT_PITCH_C1"},
	{VCONV_REG(SET_OUT_HOFFSET1),		"SET_OUT_HOFFSET1"},
	{VCONV_REG(SET_OUT_VOFFSET1),		"SET_OUT_VOFFSET1"},
	{VCONV_REG(SET_OUT_HSCALE1),		"SET_OUT_HSCALE1"},
	{VCONV_REG(SET_OUT_VSCALE1),		"SET_OUT_VSCALE1"},
	{VCONV_REG(SET_OUT_HDELTA1),		"SET_OUT_HDELTA1"},
	{VCONV_REG(SET_OUT_VDELTA1),		"SET_OUT_VDELTA1"},
	{VCONV_REG(SET_FORCE_MODE1),		"SET_FORCE_MODE1"},
	{VCONV_REG(SET_FORCE_GY1),		"SET_FORCE_GY1"},
	{VCONV_REG(SET_FORCE_BCB1),		"SET_FORCE_BCB1"},
	{VCONV_REG(SET_FORCE_RCR1),		"SET_FORCE_RCR1"},
	{VCONV_REG(SET_FORCE_A1),		"SET_FORCE_A1"},
	{VCONV_REG(SET_CROP1),			"SET_CROP1"},
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
static void vconv_dump_vconv_dev_info(struct seq_file *seq)
{
	seq_printf(seq, "struct vconv_dev : [0x%p] =====\n", &s_vconv_dev);
/*	seq_printf(seq, "\tcdev           : ----\n"); */
	seq_printf(seq, "\tdevice         : 0x%p\n", s_vconv_dev.device);
/*	seq_printf(seq, "\twait           : ----\n"); */
#if defined(CONFIG_SMP)
	seq_printf(seq, "\tlock_dev       : [%d]\n",
		s_vconv_dev.lock_dev.rlock.raw_lock.lock);
	seq_printf(seq, "\tlock_reg       : [%d]\n",
		s_vconv_dev.lock_reg.rlock.raw_lock.lock);
	seq_printf(seq, "\tmutex_run      : [%d/%d]\n",
		atomic_read(&(s_vconv_dev.mutex_run.count)),
		s_vconv_dev.mutex_run.wait_lock.rlock.raw_lock.lock);
#endif
	seq_printf(seq, "\tul_open_count  : %d\n",
		atomic_read(&(s_vconv_dev.ul_open_count)));
	seq_printf(seq, "\tb_run          : %d\n", s_vconv_dev.b_run);
	seq_printf(seq, "==  ioremap address\n");
	seq_printf(seq, "\tvconvbase      : 0x%p\n", s_vconv_dev.vconvbase);
	seq_printf(seq, "\tpmubase        : 0x%p\n", s_vconv_dev.pmubase);
	seq_printf(seq, "==  interrupt counter\n");
	seq_printf(seq, "\tframe_end      : %d\n",
		s_vconv_dev.ul_num_frame_end_irq);
	seq_printf(seq, "\tstart err      : %d\n",
		s_vconv_dev.ul_num_start_err_irq);
	seq_printf(seq, "\treg err        : %d\n",
		s_vconv_dev.ul_num_reg_err_irq);
	seq_printf(seq, "\tdisp err       : %d\n",
		s_vconv_dev.ul_num_disp_err_irq);
	seq_printf(seq, "\tmerge err      : %d\n",
		s_vconv_dev.ul_num_merge_err_irq);
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
static void *vconv_reg_seq_start(struct seq_file *seq, loff_t *pos)
{
	VCONV_FUNC_START("seq(%p), *pos(%lld)\n", seq, *pos);
	if (*pos >= ARRAY_SIZE(g_reg_list))
		return NULL;

	if (*pos != 0)
		*pos += (VCONV_DUMP_REG_LINE - 1);

	VCONV_FUNC_END("\n");
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
static void *vconv_reg_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	VCONV_FUNC_START("seq(%p), v(%p), *pos(%lld), size(%d)\n",
				seq, v, *pos, ARRAY_SIZE(g_reg_list));
	if (*pos < ARRAY_SIZE(g_reg_list)) {
		*pos += VCONV_DUMP_REG_LINE;
	} else {
		VCONV_INFO("over reg list[%lld, %d]\n",
				*pos, ARRAY_SIZE(g_reg_list));
		pos = NULL;
	}
	VCONV_FUNC_END("\n");

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
static void vconv_reg_seq_stop(struct seq_file *seq, void *v)
{
	VCONV_FUNC_START("seq(%p), v(%p)(%08x)\n",
				seq, v, v == NULL ? 0 : *((__u32 *)(v)));
	VCONV_FUNC_END("\n");
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
static int vconv_reg_seq_show(struct seq_file *seq, void *v)
{
	int i, j;
	VCONV_FUNC_START("seq(%p), v(%p)(%d)\n",
				seq, v, v == NULL ? 0 : *((__u32 *)(v)));
	i = *(int *)v;
	if (i == 0)
		seq_printf(seq, "No.\tREGISTER NAME       : OFFSET   : VAL\n");

	if (i < ARRAY_SIZE(g_reg_list)) {
		for (j = 0;
			(i < ARRAY_SIZE(g_reg_list)) &&
				(j < VCONV_DUMP_REG_LINE); i++, j++) {
			seq_printf(seq, "%3d\t%20s:[%08x]: %08x\n",
				i,
				g_reg_list[i].name,
				g_reg_list[i].offset,
				__raw_readl(s_vconv_dev.vconvbase +
						g_reg_list[i].offset));
		}
	}
	VCONV_FUNC_END("\n");

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
static int vconv_reg_seq_open(struct inode *inode, struct file *file)
{
	VCONV_FUNC_START("\n");

	return seq_open(file, &vconv_reg_seq_ops);
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
static int vconv_sts_seq_show(struct seq_file *seq, void *v)
{
	vconv_dump_vconv_dev_info(seq);
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
static int vconv_sts_seq_open(struct inode *inode, struct file *file)
{
	VCONV_FUNC_START("\n");
	return single_open(file, vconv_sts_seq_show, NULL);
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
static int vconv_log_seq_show(struct seq_file *seq, void *v)
{
	static char *f[] =  {"ON", "OFF"};

	VCONV_FUNC_START("\n");
	seq_printf(seq, "log level = %d\n", ul_logflags);
	seq_printf(seq, "    FUNCTION IN/OUT LOG : %s\n",
			(ul_logflags & VCONV_LOG_FUNCTION ? f[0] : f[1]));
	seq_printf(seq, "    PERFORMANCE LOG     : %s\n",
			(ul_logflags & VCONV_LOG_PERFORMANCE ? f[0] : f[1]));
	seq_printf(seq, "    OTHER LOG           : %s\n",
			(ul_logflags & VCONV_LOG_INFORMATION ? f[0] : f[1]));

	VCONV_FUNC_END("\n");
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
static int vconv_log_seq_open(struct inode *inode, struct file *file)
{
	VCONV_FUNC_START("\n");
	return single_open(file, vconv_log_seq_show, NULL);
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
static ssize_t vconv_log_seq_write(struct file *file, const char __user *buf,
				size_t count, loff_t *ppos)
{
	int iret;
	unsigned long logflags;

	VCONV_FUNC_START("\n");

	iret = kstrtoul_from_user(buf, count, 10, &logflags);
	if (iret != 0) {
		VCONV_ERR("kstrtoul_from_user() failed\n");
		return iret;
	}

	ul_logflags = logflags;

	VCONV_FUNC_END("\n");
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
void vconv_procfs_create(void)
{
	VCONV_FUNC_START("\n");

#if defined(CONFIG_PROC_FS)
	/* create /proc/vconv/ directory */
	pst_vconv_proc = proc_mkdir(PROC_DEVICE_NAME, NULL);
	VCONV_INFO("/proc/%s entry = %p\n", PROC_DEVICE_NAME, pst_vconv_proc);
	if (pst_vconv_proc == NULL) {
		VCONV_ERR("proc_mkdir(%s) failed\n", PROC_DEVICE_NAME);
		return;
	}
	/* create /proc/vconv/status file with read-only */
	proc_create(PROC_STS_NAME, 0, pst_vconv_proc, &vconv_sts_proc_fops);
	/* create /proc/vconv/regs file with read-only */
	proc_create(PROC_REG_NAME, 0, pst_vconv_proc, &vconv_reg_proc_fops);
	/* create /proc/vconv/logflag file with read-write */
	proc_create(PROC_LOGFLAG_NAME, S_IRUGO | S_IWUGO,
					pst_vconv_proc, &vconv_log_proc_fops);
#endif	/* CONFIG_PROC_FS */

	VCONV_FUNC_END("\n");
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
void vconv_procfs_remove(void)
{
	VCONV_FUNC_START("\n");

#if defined(CONFIG_PROC_FS)
	VCONV_INFO("/proc/%s entry = %p\n", PROC_DEVICE_NAME, pst_vconv_proc);
	if (pst_vconv_proc != NULL) {
		/* remove /proc/vconv/status file */
		VCONV_INFO("remove /proc/%s/%s\n",
			PROC_DEVICE_NAME, PROC_STS_NAME);
		remove_proc_entry(PROC_STS_NAME, pst_vconv_proc);
		/* remove /proc/vconv/regs file */
		VCONV_INFO("remove /proc/%s/%s\n",
			PROC_DEVICE_NAME, PROC_REG_NAME);
		remove_proc_entry(PROC_REG_NAME, pst_vconv_proc);
		/* remove /proc/vconv/logflag file */
		VCONV_INFO("remove /proc/%s/%s\n",
			PROC_DEVICE_NAME, PROC_LOGFLAG_NAME);
		remove_proc_entry(PROC_LOGFLAG_NAME, pst_vconv_proc);
		/* remove /proc/vconv/ directory */
		VCONV_INFO("remove /proc/%s/\n", PROC_DEVICE_NAME);
		remove_proc_entry(PROC_DEVICE_NAME, NULL);
	}
#endif	/* CONFIG_PROC_FS */

	VCONV_FUNC_END("\n");
}
