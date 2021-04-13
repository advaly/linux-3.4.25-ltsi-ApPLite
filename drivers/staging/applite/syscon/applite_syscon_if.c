/*
 * linux/drivers/staging/applite/syscon/applite_syscon_if.c
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
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>

#include <linux/applite/applite_syscon.h>
#include "applite_syscon_internal.h"

#if IS_BUILTIN(CONFIG_APPLITE_SYSCON)
/* fw download timing */
/*  builtin : in open */
/*  module  : in probe */
#define __FW_DL_IN_OPEN__
#endif

/* MODULE INFORMATION */
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("SYSCON Driver");
MODULE_VERSION(SYSCON_DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("syscon");

static __u32 utid;
module_param(utid, uint, S_IRUGO | S_IWUSR | S_IWGRP);
MODULE_PARM_DESC(utid, "unit test id");

__u32 dbg_lv;
module_param(dbg_lv, uint, S_IRUGO | S_IWUSR | S_IWGRP);
MODULE_PARM_DESC(dbg_lv, "log level for SYSCON");

module_param(ul_logflags, uint, S_IRUGO | S_IWUSR | S_IWGRP);
MODULE_PARM_DESC(ul_logflags, "log level for syscon driver");

char *fw_path = SYSCON_DEF_FW_NAME;
module_param(fw_path, charp, S_IRUGO | S_IWUSR | S_IWGRP);
MODULE_PARM_DESC(fw_path, "path for syscon f/w");


/*===================================
Static Variables and Functions prototypes
===================================*/

static struct class *psyscon_class;
static dev_t syscon_number;
struct syscon_dev s_dev;

static int syscon_open(struct inode *inode, struct file *file);
static int syscon_release(struct inode *inode, struct file *file);
static long syscon_ioctl(struct file *file,
				unsigned int cmd, unsigned long arg);
static irqreturn_t syscon_irq(int irq, void *arg);

static int __devinit syscon_probe(struct platform_device *pdev);
static int __devexit syscon_remove(struct platform_device *pdev);
static int syscon_suspend(struct device *dev);
static int syscon_resume(struct device *dev);

static ssize_t syscon_fw_info_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_counter_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_timer_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_boot_device_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_memory_size_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_memory_type_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_sys_config0_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_sys_config1_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_wakeup_trigger_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_fw_download_show(struct class *cls,
				struct class_attribute *attr, char *buf);
static ssize_t syscon_wakeup_trigger_store(struct class *cls,
		struct class_attribute *attr, const char *buf, size_t count);


static const struct file_operations syscon_fops = {
	.owner		= THIS_MODULE,
	.open		= syscon_open,
	.release	= syscon_release,
	.unlocked_ioctl	= syscon_ioctl,
};

static const struct dev_pm_ops applite_syscon_pm_ops = {
	.suspend	= syscon_suspend,
	.resume		= syscon_resume,
};

static struct platform_driver syscon_driver = {
	.probe		= syscon_probe,
	.remove		= syscon_remove,
	.driver		= {
		.name	= PLAT_DEVICE_NAME,
		.owner	= THIS_MODULE,
		.pm = &applite_syscon_pm_ops,
	},
};

/*===================================
Global Variables and Functions prototypes
===================================*/

static CLASS_ATTR(fw_info, 0444, syscon_fw_info_show, NULL);
static CLASS_ATTR(counter, 0444, syscon_counter_show, NULL);
static CLASS_ATTR(timer, 0444, syscon_timer_show, NULL);
static CLASS_ATTR(boot_device, 0444, syscon_boot_device_show, NULL);
static CLASS_ATTR(memory_size, 0444, syscon_memory_size_show, NULL);
static CLASS_ATTR(memory_type, 0444, syscon_memory_type_show, NULL);
static CLASS_ATTR(sys_config0, 0444, syscon_sys_config0_show, NULL);
static CLASS_ATTR(sys_config1, 0444, syscon_sys_config1_show, NULL);
static CLASS_ATTR(fw_download, 0444, syscon_fw_download_show, NULL);
static CLASS_ATTR(wakeup_trigger, 0666, syscon_wakeup_trigger_show,
						syscon_wakeup_trigger_store);

static CLASS_ATTR_STRING(dbg_file, S_IRUGO, NULL);

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
static int syscon_open(struct inode *inode, struct file *file)
{
	int ierr = 0;
	struct syscon_dev *pdev =
			container_of(inode->i_cdev, struct syscon_dev, cdev);
	SYSCON_FUNC_START("pdev(%p)\n", pdev);

	if (pdev == NULL) {
		SYSCON_ERR("invalid parameter\n");
		return -EINVAL;
	}

	file->private_data = pdev;

#if defined(__FW_DL_IN_OPEN__)
	mutex_lock(&(pdev->mutex_dev));
	/* exclusive internal parameter access */
	if (pdev->b_download == SYSCON_DL_NOT) {
		/* load F/W */
		if (syscon_load_fw(pdev) != SYSCON_OK)
			SYSCON_ERR("syscon_load_fw() failed\n");
		else {
			/* register to crypto API */
			syscon_crypto_init(pdev);
			pdev->b_download = SYSCON_DL_DONE;
		}
	}
	mutex_unlock(&(pdev->mutex_dev));
#endif	/* __FW_DL_IN_OPEN__ */
	SYSCON_FUNC_END("ret(%d)\n", ierr);

	return ierr;
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
static int syscon_release(struct inode *inode, struct file *file)
{
	int ierr = 0;
	struct syscon_dev *pdev = file->private_data;

	SYSCON_FUNC_START("\n");

	if (pdev == NULL) {
		SYSCON_ERR("invalid parameter\n");
		return -EINVAL;
	}

	SYSCON_FUNC_END("ret(%d)\n", ierr);

	return ierr;
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
static long syscon_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ierr = 0;
	struct syscon_dev *pdev = file->private_data;
	struct syscon_cmd prm;

	SYSCON_FUNC_START("cmd:%08x, arg:%08lx\n", cmd, arg);

	if (pdev->b_download != SYSCON_DL_DONE) {
		SYSCON_ERR("not downloaded 3rd F/W\n");
		return -EFAULT;
	}
	/* parameter check */
	switch (cmd) {
	case IOC_SYSCON_L_CMD:
		if (copy_from_user(&prm, (void __user *)arg,
					sizeof(struct syscon_cmd))) {
			SYSCON_ERR("copy_from_user() failed\n");
			ierr = -EFAULT;
			break;
		}
		ierr = syscon_exec_l_slot(pdev, &prm);
		if (ierr == 0) {
			if (copy_to_user((void __user *)arg, &prm,
					sizeof(struct syscon_cmd))) {
				SYSCON_ERR("copy_to_user() failed\n");
				ierr = -EFAULT;
			}
		}
		break;
	case IOC_SYSCON_S_CMD:
		if (copy_from_user(&prm, (void __user *)arg,
					sizeof(struct syscon_cmd))) {
			SYSCON_ERR("copy_from_user() failed\n");
			ierr = -EFAULT;
			break;
		}
		ierr = syscon_exec_s_slot(pdev, &prm);
		if (ierr == 0) {
			if (copy_to_user((void __user *)arg, &prm,
					sizeof(struct syscon_cmd))) {
				SYSCON_ERR("copy_to_user() failed\n");
				ierr = -EFAULT;
			}
		}
		break;
	default:
		SYSCON_ERR("invalid cmd[%08x]\n", cmd);
		ierr = -ENOIOCTLCMD;
	}
	SYSCON_FUNC_END("ret(%ld)\n", ierr);
	return ierr;
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
static irqreturn_t syscon_irq(int irq, void *arg)
{
	irqreturn_t ierr = IRQ_NONE;
	__u32 reg_008, reg_010;
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	__u32 reg_011;
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
	struct syscon_dev *pdev = (struct syscon_dev *)arg;
	__u32 slot;
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	__u8 queno;
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	SYSCON_FUNC_START("\n");

	if (pdev == NULL) {
		SYSCON_ERR("invalid argument\n");
		return ierr;
	}
	reg_008 = mbox_read(pdev, MBOX_REG(REG008_SET));
	mbox_write(pdev, MBOX_REG(REG008_CLEAR), reg_008);
	reg_010 = mbox_read(pdev, MBOX_REG(REG010_SET));
	mbox_write(pdev, MBOX_REG(REG010_CLEAR), reg_010);
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	reg_011 = mbox_read(pdev, MBOX_REG(REG011_SET));
	mbox_write(pdev, MBOX_REG(REG011_CLEAR), reg_011);

	if (reg_011) {
		if (reg_011 & MBOX_CMD_CMP_C_Q0_S) {
			SYSCON_INFO("CMD_CMP_SLOT_C_Q0(S)\n");
			pdev->result_c_slot[0] = 0;
			complete(&(pdev->comp_c_slot[0]));
		}
		if (reg_011 & MBOX_CMD_CMP_C_Q1_S) {
			SYSCON_INFO("CMD_CMP_SLOT_C_Q1(S)\n");
#if (SYSCON_SLOTC_Q_MAX > 1)
			pdev->result_c_slot[1] = 0;
			complete(&(pdev->comp_c_slot[1]));
#endif
		}
		if (reg_011 & MBOX_CMD_CMP_C_Q2_S) {
			SYSCON_INFO("CMD_CMP_SLOT_C_Q2(S)\n");
#if (SYSCON_SLOTC_Q_MAX > 2)
			pdev->result_c_slot[2] = 0;
			complete(&(pdev->comp_c_slot[2]));
#endif
		}
		if (reg_011 & MBOX_CMD_CMP_C_Q3_S) {
			SYSCON_INFO("CMD_CMP_SLOT_C_Q3(S)\n");
#if (SYSCON_SLOTC_Q_MAX > 3)
			pdev->result_c_slot[3] = 0;
			complete(&(pdev->comp_c_slot[3]));
#endif
		}
		if (reg_011 & MBOX_CMD_CMP_C_Q0_N) {
			SYSCON_INFO("CMD_CMP_SLOT_C_Q0(N)\n");
			pdev->result_c_slot[0] = 0;
			complete(&(pdev->comp_c_slot[0]));
		}
		if (reg_011 & MBOX_CMD_CMP_C_Q1_N) {
			SYSCON_INFO("CMD_CMP_SLOT_C_Q1(N)\n");
#if (SYSCON_SLOTC_Q_MAX > 1)
			pdev->result_c_slot[1] = 0;
			complete(&(pdev->comp_c_slot[1]));
#endif
		}
		if (reg_011 & MBOX_CMD_CMP_C_Q2_N) {
			SYSCON_INFO("CMD_CMP_SLOT_C_Q2(N)\n");
#if (SYSCON_SLOTC_Q_MAX > 2)
			pdev->result_c_slot[2] = 0;
			complete(&(pdev->comp_c_slot[2]));
#endif
		}
		if (reg_011 & MBOX_CMD_CMP_C_Q3_N) {
			SYSCON_INFO("CMD_CMP_SLOT_C_Q3(N)\n");
#if (SYSCON_SLOTC_Q_MAX > 3)
			pdev->result_c_slot[3] = 0;
			complete(&(pdev->comp_c_slot[3]));
#endif
		}
		ierr = IRQ_HANDLED;
	}
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
	if (reg_010) {
		if (reg_010 & MBOX_CMD_CMP_NOTIFY_S) {
			SYSCON_INFO("CMD_CMP_NOTIFY_S\n");
			slot = scomm_read(pdev, SCOMM_RSP_SLOT_OFFS);
			switch (slot) {
			case SCOMM_SLOT_L:
				pdev->result_l_slot = 0;
				complete(&(pdev->comp_l_slot));
				break;
			case SCOMM_SLOT_S:
				pdev->result_s_slot = 0;
				complete(&(pdev->comp_s_slot));
				break;
			default:
				SYSCON_ERR("invalid slot:%08x\n", slot);
			}
			ierr = IRQ_HANDLED;
		}
		if (reg_010 & MBOX_CMD_REQ_ERROR_S) {
			SYSCON_INFO("CMD_REQ_ERROR_S\n");
			slot = scomm_read(pdev, SCOMM_REQ_SLOT_OFFS);
			syscon_free_tas(pdev);
			switch (slot) {
			case SCOMM_SLOT_L:
				pdev->result_l_slot =
					scomm_read(pdev, SCOMM_REG(REQ_RESULT));
				complete(&(pdev->comp_l_slot));
				break;
			case SCOMM_SLOT_S:
				pdev->result_s_slot =
					scomm_read(pdev, SCOMM_REG(REQ_RESULT));
				complete(&(pdev->comp_s_slot));
				break;
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
			case SCOMM_SLOT_C:
				queno = scomm_read8(pdev,
						SCOMM_REG(REQ_C_QUENO));
				pdev->result_c_slot[queno] =
					scomm_read(pdev, SCOMM_REG(REQ_RESULT));
				pdev->result_c_slot_caller[queno] =
					scomm_read(pdev, SCOMM_REG(REQ_C_RET));
				pdev->result_c_slot_sub[queno] =
					scomm_read(pdev,
						SCOMM_REG(REQ_C_ERRSUB));
				complete(&(pdev->comp_c_slot[queno]));
				break;
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
			default:
				SYSCON_ERR("invalid slot:%08x\n", slot);
			}
			ierr = IRQ_HANDLED;
		}
		if (reg_010 & MBOX_CMD_CMP_NOTIFY_N) {
			SYSCON_INFO("CMD_CMP_NOTIFY_N\n");
			ierr = IRQ_HANDLED;
		}
		if (reg_010 & MBOX_CMD_REQ_ERROR_N) {
			SYSCON_INFO("CMD_REQ_ERROR_N\n");
			ierr = IRQ_HANDLED;
		}
	}

	if (reg_008) {
		if (reg_008 & MBOX_FW_DL_RSP) {
			SYSCON_INFO("FW_DL_RSP\n");
			complete(&(pdev->comp));
			ierr = IRQ_HANDLED;
		}
		if (reg_008 & MBOX_BUF_FREE_RSP) {
			SYSCON_INFO("BUF_FREE_RSP\n");
			complete(&(pdev->comp));
			ierr = IRQ_HANDLED;
		}
	}
	return ierr;
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
static ssize_t syscon_fw_info_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	__u64 fw_info;

	SYSCON_FUNC_START("\n");

	/* get information */
	fw_info = syscon_get_fw_info(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "0x%016llx\n", fw_info);
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
static ssize_t syscon_counter_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	__u64 val;

	SYSCON_FUNC_START("\n");

	/* get information */
	val = syscon_get_counter(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "%lld\n", val);
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
static ssize_t syscon_timer_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	__u32 val;

	SYSCON_FUNC_START("\n");

	/* get information */
	val = syscon_get_timer(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
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
static ssize_t syscon_boot_device_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	char *str;

	SYSCON_FUNC_START("\n");

	/* get information */
	str = syscon_get_bootdevice_str(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "%s\n", str);
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
static ssize_t syscon_memory_size_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	__u32 val;

	SYSCON_FUNC_START("\n");

	/* get information */
	val = syscon_get_memorysize(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "%d\n", (val / 1024 / 1024));
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
static ssize_t syscon_memory_type_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	char *str;

	SYSCON_FUNC_START("\n");

	/* get information */
	str = syscon_get_memorytype_str(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "%s\n", str);
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
static ssize_t syscon_sys_config0_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	__u32 val;

	SYSCON_FUNC_START("\n");

	/* get information */
	val = syscon_get_sysconfig0(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "0x%08x\n", val);
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
static ssize_t syscon_sys_config1_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	__u32 val;

	SYSCON_FUNC_START("\n");

	/* get information */
	val = syscon_get_sysconfig1(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "0x%08x\n", val);
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
static ssize_t syscon_fw_download_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	SYSCON_FUNC_START("\n");

	/* get information */
	if (s_dev.b_download == SYSCON_DL_NOT) {
		/* check F/W version */
		if (syscon_check_fw(&s_dev) == SYSCON_OK) {
			/* load F/W */
			if (syscon_load_fw(&s_dev) != SYSCON_OK) {
				SYSCON_ERR("syscon_load_fw() failed\n");
				/* output to sysfs */
				return snprintf(buf, PAGE_SIZE, "fail\n");
			}
			/* register to crypto API */
			syscon_crypto_init(&s_dev);
		}
		s_dev.b_download = SYSCON_DL_DONE;
	}

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "pass\n");
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
static ssize_t syscon_wakeup_trigger_show(struct class *cls,
				struct class_attribute *attr, char *buf)
{
	char *str;

	SYSCON_FUNC_START("\n");

	/* get information */
	str = syscon_get_wakeup_trigger_str(&s_dev);

	/* output to sysfs */
	return snprintf(buf, PAGE_SIZE, "%s\n", str);
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
static int syscon_pwmn_config(struct syscon_dev *pdev, __u32 *config)
{
	int ierr;
	struct syscon_cmd cmd;

	SYSCON_FUNC_START("%08x/%08x/%08x/%08x\n",
		config[0], config[1], config[2], config[3]);

	memset(&cmd, 0, sizeof(struct syscon_cmd));

	*(__u32 *)(&(cmd.cmd_req[0x00])) = 1;
	*(__u32 *)(&(cmd.cmd_req[0x10])) = config[0];
	*(__u32 *)(&(cmd.cmd_req[0x14])) = config[1];
	*(__u32 *)(&(cmd.cmd_req[0x18])) = config[2];
	*(__u32 *)(&(cmd.cmd_req[0x1C])) = config[3];

	ierr = syscon_exec_s_slot(&s_dev, &cmd);
	if (ierr != 0) {
		SYSCON_ERR("s slot failed %d\n", ierr);
		return SYSCON_NG;
	}
	/* check result */
	if (*(__u32 *)&(cmd.cmd_rsp[0x04]) != 0) {
		SYSCON_ERR("pwmn cfg failed %d\n",
			*(__u32 *)&(cmd.cmd_rsp[0x04]));
		return SYSCON_NG;
	}
	SYSCON_FUNC_END("Result:OK\n");

	return SYSCON_OK;
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
static ssize_t syscon_wakeup_trigger_store(struct class *cls,
		struct class_attribute *attr, const char *buf, size_t count)
{
	int ierr;
	__u32 config[4];

	SYSCON_FUNC_START("[%s]\n", buf);

	if (s_dev.b_download != SYSCON_DL_DONE) {
		SYSCON_ERR("not downloaded 3rd F/W\n");
		return count;
	}
	if ((strcmp(buf, "gpio-falling") == 0) ||
		(strcmp(buf, "gpio-falling\n") == 0)) {
		config[0] = SCOMM_WKUP_GPIO_FALL;
		config[1] = 0;
	} else if ((strcmp(buf, "gpio-rising") == 0) ||
		(strcmp(buf, "gpio-rising\n") == 0)) {
		config[0] = SCOMM_WKUP_GPIO_RISE;
		config[1] = 0;
	} else if (strncmp(buf, "timer-", 6) == 0) {
		config[0] = SCOMM_WKUP_TIMER;
		ierr = kstrtou32(&buf[6], 10, &config[1]);
		if (ierr != 0) {
			SYSCON_ERR("kstrtoint(%s) failed %d\n", &buf[6], ierr);
			return count;
		}
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
	} else if ((strcmp(buf, "rtc-alarm") == 0) ||
		(strcmp(buf, "rtc-alarm\n") == 0)) {
		config[0] = SCOMM_WKUP_RTC;
		config[1] = RTC_RTC_INTMASK_ALARM_INTMASK_MASK;
	} else if ((strcmp(buf, "rtc-periodic") == 0) ||
		(strcmp(buf, "rtc-periodic\n") == 0)) {
		config[0] = SCOMM_WKUP_RTC;
		config[1] = RTC_RTC_INTMASK_PERIOD_INTMASK_MASK;
#else
	} else if ((strcmp(buf, "rtc") == 0) ||
		(strcmp(buf, "rtc\n") == 0)) {
		config[0] = SCOMM_WKUP_RTC;
		config[1] = 0;
#endif	/* CONFIG_ARCH_TZ2000 */
	} else if ((strcmp(buf, "i2c") == 0) ||
		(strcmp(buf, "i2c\n") == 0)) {
		config[0] = SCOMM_WKUP_I2C;
		config[1] = 0;
	} else {
		SYSCON_ERR("unknown parameter:%s\n", buf);
		return count;
	}

	config[2] = syscon_get_pwmn_config2(&s_dev);
	config[3] = syscon_get_pwmn_config3(&s_dev);

	ierr = syscon_pwmn_config(&s_dev, config);
	if (ierr != 0)
		SYSCON_ERR("pwmn cfg failed %d\n", ierr);

	return count;
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
static int syscon_create_sysfs(struct class *cls)
{
	int ierr = 0;

	class_attr_dbg_file.str = s_dev.virt + (64 * 1024);
	ierr = class_create_file(cls, &class_attr_dbg_file.attr);
	if (ierr) {
		SYSCON_ERR("class_create_file(dbg_file) failed %d\n", ierr);
		goto fail_class_create_file_dbg_file;
	}
	ierr = class_create_file(cls, &class_attr_fw_info);
	if (ierr) {
		SYSCON_ERR("class_create_file(fw_info) failed %d\n", ierr);
		goto fail_class_create_file_fw_info;
	}
	ierr = class_create_file(cls, &class_attr_counter);
	if (ierr) {
		SYSCON_ERR("class_create_file(counter) failed %d\n", ierr);
		goto fail_class_create_file_counter;
	}
	ierr = class_create_file(cls, &class_attr_timer);
	if (ierr) {
		SYSCON_ERR("class_create_file(timer) failed %d\n", ierr);
		goto fail_class_create_file_timer;
	}
	ierr = class_create_file(cls, &class_attr_boot_device);
	if (ierr) {
		SYSCON_ERR("class_create_file(boot_device) failed %d\n", ierr);
		goto fail_class_create_file_boot_device;
	}
	ierr = class_create_file(cls, &class_attr_memory_size);
	if (ierr) {
		SYSCON_ERR("class_create_file(memory_size) failed %d\n", ierr);
		goto fail_class_create_file_memory_size;
	}
	ierr = class_create_file(cls, &class_attr_memory_type);
	if (ierr) {
		SYSCON_ERR("class_create_file(memory_type) failed %d\n", ierr);
		goto fail_class_create_file_memory_type;
	}
	if (dbg_lv >= 0x00010000) {
		ierr = class_create_file(cls, &class_attr_sys_config0);
		if (ierr) {
			SYSCON_ERR("class_create_file(sys_config0) failed %d\n",
							ierr);
			goto fail_class_create_file_sys_config0;
		}
		ierr = class_create_file(cls, &class_attr_sys_config1);
		if (ierr) {
			SYSCON_ERR("class_create_file(sys_config1) failed %d\n",
							ierr);
			goto fail_class_create_file_sys_config1;
		}
	}
	ierr = class_create_file(cls, &class_attr_wakeup_trigger);
	if (ierr) {
		SYSCON_ERR("class_create_file(wakeup_trigger) failed %d\n",
									ierr);
		goto fail_class_create_file_wakeup_trigger;
	}
	ierr = class_create_file(cls, &class_attr_fw_download);
	if (ierr) {
		SYSCON_ERR("class_create_file(fw_download) failed %d\n", ierr);
		goto fail_class_create_file_fw_download;
	}
	return SYSCON_OK;

fail_class_create_file_fw_download:
	class_remove_file(cls, &class_attr_wakeup_trigger);
fail_class_create_file_wakeup_trigger:
	class_remove_file(cls, &class_attr_sys_config1);
fail_class_create_file_sys_config1:
	class_remove_file(cls, &class_attr_sys_config0);
fail_class_create_file_sys_config0:
	class_remove_file(cls, &class_attr_memory_type);
fail_class_create_file_memory_type:
	class_remove_file(cls, &class_attr_memory_size);
fail_class_create_file_memory_size:
	class_remove_file(cls, &class_attr_boot_device);
fail_class_create_file_boot_device:
	class_remove_file(cls, &class_attr_timer);
fail_class_create_file_timer:
	class_remove_file(cls, &class_attr_counter);
fail_class_create_file_counter:
	class_remove_file(cls, &class_attr_fw_info);
fail_class_create_file_fw_info:
	class_remove_file(cls, &class_attr_dbg_file.attr);
fail_class_create_file_dbg_file:
	return SYSCON_NG;
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
static void syscon_remove_sysfs(struct class *cls)
{
	class_remove_file(cls, &class_attr_fw_download);
	class_remove_file(cls, &class_attr_wakeup_trigger);
	if (dbg_lv >= 0x00010000) {
		class_remove_file(cls, &class_attr_sys_config1);
		class_remove_file(cls, &class_attr_sys_config0);
	}
	class_remove_file(cls, &class_attr_memory_type);
	class_remove_file(cls, &class_attr_memory_size);
	class_remove_file(cls, &class_attr_boot_device);
	class_remove_file(cls, &class_attr_timer);
	class_remove_file(cls, &class_attr_counter);
	class_remove_file(cls, &class_attr_fw_info);
	class_remove_file(cls, &class_attr_dbg_file.attr);

}

static int syscon_suspend(struct device *dev)
{
	return 0;
}

static int syscon_resume(struct device *dev)
{
	if (syscon_reset_register(&s_dev) != SYSCON_OK)
		return -EFAULT;
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
void applitesyscon_pm_request(int arg)
{
	syscon_set_pm(&s_dev, arg);
}
EXPORT_SYMBOL(applitesyscon_pm_request);

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
static int __devinit syscon_probe(struct platform_device *pdev)
{
	int ierr = 0, i;
	struct resource *res;

	SYSCON_FUNC_START("\n");

	/* initialize internal parameters */
	memset((void *)&s_dev, 0, sizeof(struct syscon_dev));

	init_completion(&(s_dev.comp));
	init_completion(&(s_dev.comp_l_slot));
	init_completion(&(s_dev.comp_s_slot));
	mutex_init(&(s_dev.mutex_l_slot));
	mutex_init(&(s_dev.mutex_s_slot));
	mutex_init(&(s_dev.mutex_dev));
	mutex_init(&(s_dev.mutex_scomm_rsp));
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++) {
		init_completion(&(s_dev.comp_c_slot[i]));
		mutex_init(&(s_dev.mutex_c_slot[i]));
	}
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	/* allocate charctor device number */
	ierr = alloc_chrdev_region(&syscon_number, 0, 1, DEVICE_NAME);
	if (ierr) {
		SYSCON_ERR("alloc_chrdev_region() failed %d\n", ierr);
		return ierr;
	}

	/* create syscon class */
	psyscon_class = class_create(THIS_MODULE, DEVICE_NAME);
	if (IS_ERR(psyscon_class)) {
		ierr = PTR_ERR(psyscon_class);
		SYSCON_ERR("class_create() failed %d\n", ierr);
		goto fail_class_create;
	}

	/* initialize cdev structure */
	cdev_init(&(s_dev.cdev), &syscon_fops);
	s_dev.cdev.owner = THIS_MODULE;

	/* register cdev structure */
	ierr = cdev_add(&(s_dev.cdev), syscon_number, 1);
	if (ierr) {
		SYSCON_ERR("cdev_add() failed %d\n", ierr);
		goto fail_cdev_add;
	}

	/* create device structure */
	s_dev.device = device_create(psyscon_class, NULL, syscon_number,
						NULL, DEVICE_NAME);
	if (IS_ERR(s_dev.device)) {
		ierr = PTR_ERR(s_dev.device);
		SYSCON_ERR("device_create() failed %d\n", ierr);
		goto fail_device_create;
	}
	s_dev.device->dma_mem = pdev->dev.dma_mem;
	s_dev.device->dma_mask = pdev->dev.dma_mask;
	s_dev.device->coherent_dma_mask = pdev->dev.coherent_dma_mask;

	/* remapping registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		ierr = -EBUSY;
		SYSCON_ERR("platform_get_resource(0) failed %d\n", ierr);
		goto fail_request_get_resource_scomm;
	}
	s_dev.scommbase =
		(__u8 __iomem *)ioremap_nocache(res->start, SCOMM_REG_SIZE);
	if (s_dev.scommbase == NULL) {
		SYSCON_ERR("ioremap() failed SCOMM Register[%08x - %d]\n",
			res->start, SCOMM_REG_SIZE);
		goto fail_ioremap_scomm;
	}
	SYSCON_INFO("ioremap SCOMM Register[%08x - %d] -> %p\n",
			res->start, SCOMM_REG_SIZE, s_dev.scommbase);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (res == NULL) {
		ierr = -EBUSY;
		SYSCON_ERR("platform_get_resource(1) failed %d\n", ierr);
		goto fail_request_get_resource_mbox;
	}
	s_dev.mboxbase =
		(__u8 __iomem *)ioremap_nocache(res->start, CPU_MBOX_REG_SIZE);
	if (s_dev.mboxbase == NULL) {
		SYSCON_ERR("ioremap() failed MBOX Register[%08x - %d]\n",
			res->start, CPU_MBOX_REG_SIZE);
		goto fail_ioremap_mbox;
	}
	SYSCON_INFO("ioremap MBOX Register[%08x - %d] -> %p\n",
			res->start, CPU_MBOX_REG_SIZE, s_dev.mboxbase);

	/* register interrupt handler */
	for (i = 0; i < SYSCON_IRQ_MAX; i++) {
		s_dev.irq[i] = platform_get_irq(pdev, i);
		ierr = request_irq(s_dev.irq[i], syscon_irq, SYSCON_IRQ_FLAG,
						DEVICE_NAME, &s_dev);
		if (ierr != 0) {
			SYSCON_ERR("request_irq(%d) failed %d\n",
						s_dev.irq[i], ierr);
			goto fail_request_irq;
		}
	}

	platform_set_drvdata(pdev, &s_dev);

	/* init mbox */
	ierr = syscon_init_hw(&s_dev);
	if (ierr != SYSCON_OK) {
		SYSCON_ERR("syscon_init_hw() failed %d\n", ierr);
		goto fail_init_hw;
	}

	/* notify drv initialize to SYSCON */
	syscon_set_init_notify(&s_dev);

	/* register sysfs */
	if (syscon_create_sysfs(psyscon_class) != SYSCON_OK)
		goto fail_class_create_file;

#if IS_ENABLED(CONFIG_HW_RANDOM_APPLITE)
	if (syscon_rng_init(&s_dev) != SYSCON_OK)
		goto fail_rng_init;

#endif	/* CONFIG_HW_RANDOM_APPLITE */

#if !defined(__FW_DL_IN_OPEN__)
	/* exclusive internal parameter access */
	if (s_dev.b_download == SYSCON_DL_NOT) {
		/* load F/W */
		if (syscon_load_fw(&s_dev) != SYSCON_OK)
			SYSCON_ERR("syscon_load_fw() failed\n");
		else {
			/* register to crypto API */
			syscon_crypto_init(&s_dev);
			s_dev.b_download = SYSCON_DL_DONE;
		}
	}
#endif	/* __FW_DL_IN_OPEN__ */

	pr_info("SYSCON Driver [%s] Initialized.[%d.%d]\n",
		SYSCON_DRIVER_VERSION,
		MAJOR(syscon_number), MINOR(syscon_number));

	SYSCON_FUNC_END("\n");

	return 0;

#if IS_ENABLED(CONFIG_HW_RANDOM_APPLITE)
fail_rng_init:
#endif	/* CONFIG_HW_RANDOM_APPLITE */

	syscon_remove_sysfs(psyscon_class);
fail_class_create_file:
	syscon_exit_hw(&s_dev);
fail_init_hw:
fail_request_irq:
	for (i = 0; i < SYSCON_IRQ_MAX; i++) {
		if (s_dev.irq[i])
			free_irq(s_dev.irq[i], &s_dev);
	}
	iounmap(s_dev.mboxbase);
fail_ioremap_mbox:
fail_request_get_resource_mbox:
	iounmap(s_dev.scommbase);
fail_ioremap_scomm:
fail_request_get_resource_scomm:
	device_destroy(psyscon_class, syscon_number);
fail_device_create:
	cdev_del(&(s_dev.cdev));
fail_cdev_add:
	class_destroy(psyscon_class);
fail_class_create:
	unregister_chrdev_region(MAJOR(syscon_number), 1);

	SYSCON_ERR("SYSCON Driver [%s] load failed.\n", SYSCON_DRIVER_VERSION);

	SYSCON_FUNC_END("\n");

	return ierr;
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
static int __devexit syscon_remove(struct platform_device *pdev)
{
	int i;

	SYSCON_FUNC_START("\n");

#if IS_ENABLED(CONFIG_HW_RANDOM_APPLITE)
	syscon_rng_exit(&s_dev);
#endif	/* CONFIG_HW_RANDOM_APPLITE */

#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	syscon_crypto_exit(&s_dev);
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	syscon_remove_sysfs(psyscon_class);
	syscon_exit_hw(&s_dev);
	for (i = 0; i < SYSCON_IRQ_MAX; i++) {
		if (s_dev.irq[i])
			free_irq(s_dev.irq[i], &s_dev);
	}
	iounmap(s_dev.mboxbase);
	iounmap(s_dev.scommbase);
	device_destroy(psyscon_class, syscon_number);
	cdev_del(&(s_dev.cdev));
	unregister_chrdev_region(MAJOR(syscon_number), 1);
	class_destroy(psyscon_class);

	SYSCON_INFO("SYSCON Driver Uninitialized.\n");
	SYSCON_FUNC_END("\n");
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
int syscon_init(void)
{
	SYSCON_FUNC_START("\n");
	return platform_driver_register(&syscon_driver);
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
void syscon_exit(void)
{
	SYSCON_FUNC_START("\n");
	platform_driver_unregister(&syscon_driver);
	SYSCON_FUNC_END("\n");
}


module_init(syscon_init);
module_exit(syscon_exit);



