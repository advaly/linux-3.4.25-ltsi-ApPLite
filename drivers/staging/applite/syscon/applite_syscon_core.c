/*
 * linux/drivers/staging/applite/syscon/applite_syscon_core.c
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
#include <linux/sched.h>
#include <linux/dma-buf.h>
#include <linux/firmware.h>
#include <linux/delay.h>
#include <linux/uaccess.h>

#include <linux/applite/applite_syscon.h>
#include "applite_syscon_internal.h"

#undef __USE_FW_DL_NOWAIT__

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


/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
int syscon_reset_register(struct syscon_dev *pdev)
{
	SYSCON_FUNC_START("\n");

	if (pdev == NULL) {
		SYSCON_ERR("invalid parameters pdev(%p)\n", pdev);
		return SYSCON_NG;
	}

	/* MBOXx set */
	mbox_write(pdev, MBOX_REG(REG000_SET), 0);
	mbox_write(pdev, MBOX_REG(REG002_SET), 0);
	mbox_write(pdev, MBOX_REG(REG008_SET), 0);
	mbox_write(pdev, MBOX_REG(REG010_SET), 0);
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	mbox_write(pdev, MBOX_REG(REG011_SET), 0);
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
	/* MBOXx clear */
	mbox_write(pdev, MBOX_REG(REG000_CLEAR), 0);
	mbox_write(pdev, MBOX_REG(REG002_CLEAR), 0);
	mbox_write(pdev, MBOX_REG(REG008_CLEAR), 0);
	mbox_write(pdev, MBOX_REG(REG010_CLEAR), 0);
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	mbox_write(pdev, MBOX_REG(REG011_CLEAR), 0);
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
	/* MBOXx mask */
	mbox_write(pdev, MBOX_REG(REG008_MASK), ~(MBOX_008_INT_MASK));
	mbox_write(pdev, MBOX_REG(REG010_MASK), ~(MBOX_010_INT_MASK));
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	mbox_write(pdev, MBOX_REG(REG011_MASK), ~(MBOX_011_INT_MASK));
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	SYSCON_FUNC_END("OK\n");
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
int syscon_init_hw(struct syscon_dev *pdev)
{
	SYSCON_FUNC_START("\n");

	if (pdev == NULL) {
		SYSCON_ERR("invalid parameters pdev(%p)\n", pdev);
		return SYSCON_NG;
	}
	/* allocate 64KiB continuous region */
	pdev->virt = dma_alloc_coherent(pdev->device, SYSCON_AREA,
			&(pdev->phys), (GFP_KERNEL | GFP_DMA));
	if (pdev->virt == NULL) {
		SYSCON_ERR("dma_alloc_coherent(%d) failed\n", SYSCON_AREA);
		return SYSCON_NG;
	}
	SYSCON_INFO("SYSCON area (%p/%08x, %08x)\n", pdev->virt, pdev->phys,
				SYSCON_AREA);

	if (syscon_reset_register(pdev) != SYSCON_OK)
		return SYSCON_NG;

	/* SCOMM set */
	scomm_write(pdev, SCOMM_REG(DRV_ABI), SCOMM_SPEC);
	scomm_write(pdev, SCOMM_REG(DBG_LV), dbg_lv);
	scomm_write(pdev, SCOMM_REG(DRAM_WORK), pdev->phys);
	scomm_write(pdev, SCOMM_REG(DRAM_DEBUG), (pdev->phys + (64 * 1024)));
	scomm_memset(pdev, SCOMM_REG(RESERVED), 0, SCOMM_RESERVED_SIZE);

	SYSCON_FUNC_END("OK\n");
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
int syscon_exit_hw(struct syscon_dev *pdev)
{
	unsigned long to;
	__u32 use;

	SYSCON_FUNC_START("\n");

	if (pdev == NULL) {
		SYSCON_ERR("invalid parameters pdev(%p)\n", pdev);
		return SYSCON_NG;
	}
	if (pdev->virt) {
		/* buff free request */
		syscon_set_buf_free_req(pdev);

		/* wait for response from F/W */
		SYSCON_INFO("wait_for_completion\n");
		to = wait_for_completion_timeout(&(pdev->comp),
				msecs_to_jiffies(SYSCON_FREE_TIMEOUT));
		SYSCON_INFO("wake up (%ld)\n", to);
		if (to == 0) {
			/* timeout */
			SYSCON_ERR("buffer free response timeout\n");
			goto fail_buff_free;
		}
		/* check buffer use */
		use = scomm_read(pdev, SCOMM_REG(STATUS));
		if (use & SCOMM_BUF_USE) {
			SYSCON_ERR("buffer use\n");
			goto fail_buff_free;
		}
		/* free 64KiB continuous region */
		dma_free_coherent(pdev->device, SYSCON_AREA,
					pdev->virt, pdev->phys);
		pdev->virt = NULL;
		pdev->phys = 0;
	}
fail_buff_free:
	/* MBOXx mask */
	mbox_write(pdev, MBOX_REG(REG008_MASK), 0xFFFFFFFF);
	mbox_write(pdev, MBOX_REG(REG010_MASK), 0xFFFFFFFF);
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	mbox_write(pdev, MBOX_REG(REG011_MASK), 0xFFFFFFFF);
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	syscon_set_fin_notify(pdev);

	SYSCON_FUNC_END("OK\n");
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
int syscon_check_fw(struct syscon_dev *pdev)
{
	__u32 ver;

	SYSCON_FUNC_START("\n");
	if (pdev == NULL) {
		SYSCON_ERR("invalid parameters pdev(%p)\n", pdev);
		return SYSCON_NG;
	}

	/* load f/w version */
	ver = scomm_read(pdev, SCOMM_REG(STATUS));
	SYSCON_INFO("F/W version %x\n", ((ver & SCOMM_VER_MASK) >> 16));
	if ((ver & SCOMM_VER_MASK) == SCOMM_VER_2ND) {
		SYSCON_FUNC_END("OK\n");
		return SYSCON_OK;
	}
	SYSCON_FORCE_LOG("3rd f/w downloaded, already");
	SYSCON_FUNC_END("NG\n");
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
#if defined(__USE_FW_DL_NOWAIT__)
static void syscon_cont(const struct firmware *fw, void *context)
{
	__u32 reg;
	unsigned long	timeout;
	struct syscon_dev *pdev = (struct syscon_dev *)context;

	SYSCON_FUNC_START("\n");

	/* communicate to syscon f/w */
	SYSCON_INFO("SYSCON F/W (path:%s, %p, size:%d)\n",
					fw_path, fw->data, fw->size);
	memcpy(pdev->virt, fw->data, fw->size);

	/* free F/W */
	release_firmware(fw);

	/* F/W download request */
	syscon_set_dl_req(pdev);

	/* wait for response from F/W */
	SYSCON_INFO("wait_for_completion\n");
	timeout = wait_for_completion_timeout(&(pdev->comp),
				msecs_to_jiffies(SYSCON_DW_TIMEOUT));
	SYSCON_INFO("wake up (%ld)\n", timeout);
	if (timeout == 0) {
		/* timeout */
		SYSCON_ERR("F/W download response timeout\n");
		goto fail_response_firmware;
	}
	/* check result */
	reg = scomm_read(pdev, SCOMM_REG(RESULT));
	if (reg != SCOMM_SUCCESS) {
		SYSCON_ERR("F/W download response failed %08x\n", reg);
		goto fail_response_firmware;
	}

	SYSCON_FUNC_END("OK\n");

fail_response_firmware:
	return;
}
#endif /* __USE_FW_DL_NOWAIT__ */

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
int syscon_load_fw(struct syscon_dev *pdev)
{
#if defined(__USE_FW_DL_NOWAIT__)
	int ierr = 0;
#else
	int ierr = 0;
	__u32 reg;
	unsigned long	timeout;
	const struct firmware *fw;
#endif

	SYSCON_FUNC_START("\n");

	if (pdev == NULL) {
		SYSCON_ERR("invalid parameters pdev(%p)\n", pdev);
		return SYSCON_NG;
	}
	/* check F/W version */
	if (syscon_check_fw(pdev) != SYSCON_OK) {
		/* already 3rd F/W running */
		return SYSCON_OK;
	}

	/* load F/W */
#if defined(__USE_FW_DL_NOWAIT__)
	ierr = request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
		fw_path, pdev->device, GFP_KERNEL, pdev, syscon_cont);
	if (ierr < 0) {
		SYSCON_ERR("request_firmware(%s) failed %d\n", fw_path, ierr);
		goto fail_request_firmware;
	}
	SYSCON_FUNC_END("OK\n");

	return SYSCON_OK;
#else
	ierr = request_firmware(&fw, fw_path, pdev->device);
	if (ierr < 0) {
		SYSCON_ERR("request_firmware(%s) failed %d\n", fw_path, ierr);
		goto fail_request_firmware;
	}
	/* communicate to syscon f/w */
	SYSCON_INFO("SYSCON F/W (path:%s, %p, size:%d)\n",
					fw_path, fw->data, fw->size);
	memcpy(pdev->virt, fw->data, fw->size);

	/* free F/W */
	release_firmware(fw);

	/* F/W download request */
	syscon_set_dl_req(pdev);

	/* wait for response from F/W */
	SYSCON_INFO("wait_for_completion\n");
	timeout = wait_for_completion_timeout(&(pdev->comp),
				msecs_to_jiffies(SYSCON_DW_TIMEOUT));
	SYSCON_INFO("wake up (%ld)\n", timeout);
	if (timeout == 0) {
		/* timeout */
		SYSCON_ERR("F/W download response timeout\n");
		goto fail_response_firmware;
	}
	/* check result */
	reg = scomm_read(pdev, SCOMM_REG(RESULT));
	if (reg != SCOMM_SUCCESS) {
		SYSCON_ERR("F/W download response failed %08x\n", reg);
		goto fail_response_firmware;
	}

	SYSCON_FUNC_END("OK\n");

	return SYSCON_OK;


fail_response_firmware:
#endif /* __USE_FW_DL_NOWAIT__ */
fail_request_firmware:
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
static int syscon_cmd_req(struct syscon_dev *pdev,
				struct syscon_cmd *cmd, __u32 slot)
{
	int ierr = 0;
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	struct syscon_cmd_c *c_cmd = (struct syscon_cmd_c *)cmd;
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	SYSCON_FUNC_START("\n");

	if (slot == SCOMM_SLOT_L) {
		/* write user data to DRAM */
		/* cmd->req_size is checked in syscon_exec_l_slot() */
		if (copy_from_user(pdev->virt, (void __user *)(cmd->req_data),
					cmd->req_size)) {
			SYSCON_ERR("copy_from_user() failed\n");
			ierr = -EFAULT;
			goto fail_copy_from_user;
		}
	}

	/* lock SCOMM */
	ierr = syscon_get_tas(pdev);
	if (ierr != 0)
		return -EBUSY;

	/* write command */
	scomm_write(pdev, SCOMM_REG(REQ_SLOT), slot);
	scomm_write(pdev, SCOMM_REG(REQ_RESULT), 0);
	scomm_write(pdev, SCOMM_REG(REQ_REQID), pdev->counter++);
	scomm_write(pdev, SCOMM_REG(REQ_DRVDATA), 0);
	scomm_write(pdev, SCOMM_REG(REQ_RESERVED0), 0);
	scomm_write(pdev, SCOMM_REG(REQ_RESERVED1), 0);
	scomm_write(pdev, SCOMM_REG(REQ_RESERVED2), 0);
	scomm_write(pdev, SCOMM_REG(REQ_RESERVED3), 0);
	switch (slot) {
	case SCOMM_SLOT_L:
	case SCOMM_SLOT_S:
		scomm_write_buf(pdev, SCOMM_REG(REQ_REQUEST),
				cmd->cmd_req, SYSCON_MAX_CMD_SIZE);
		break;
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	case SCOMM_SLOT_C:
		scomm_write(pdev, SCOMM_REG(REQ_C_REQID), 0);
		scomm_write(pdev, SCOMM_REG(REQ_C_RET), 0);
		scomm_write(pdev, SCOMM_REG(REQ_C_ERRSUB), 0);
		scomm_write(pdev, SCOMM_REG(REQ_C_RESERVED1), 0);
		scomm_write(pdev, SCOMM_REG(REQ_C_DST), c_cmd->dst);
		scomm_write(pdev, SCOMM_REG(REQ_C_SRC), c_cmd->src);
		scomm_write(pdev, SCOMM_REG(REQ_C_LEN), c_cmd->len);
		scomm_write(pdev, SCOMM_REG(REQ_C_IV), c_cmd->iv);
		scomm_write(pdev, SCOMM_REG(REQ_C_ALGO), c_cmd->algo);
		scomm_write8(pdev, SCOMM_REG(REQ_C_MODE), c_cmd->mode);
		scomm_write8(pdev, SCOMM_REG(REQ_C_KEYBITS),
						(c_cmd->ctx->keylen / 8));
		scomm_write8(pdev, SCOMM_REG(REQ_C_KEYNO), c_cmd->ctx->keyno);
		scomm_write8(pdev, SCOMM_REG(REQ_C_QUENO), c_cmd->queno);
		scomm_memset(pdev, SCOMM_REG(REQ_C_RESERVED2), 0,
			(SCOMM_REG(REQ_C_KEY) - SCOMM_REG(REQ_C_RESERVED2)));
		scomm_write_buf(pdev, SCOMM_REG(REQ_C_KEY), c_cmd->ctx->key,
				c_cmd->ctx->keylen);
		scomm_memset(pdev, SCOMM_REG(REQ_C_RESERVED3), 0,
				(SCOMM_REG(RSP_SLOT) - SCOMM_REG(REQ_C_KEY)));
		SYSCON_INFO("KEY [%02X %02X %02X %02X %02X %02X %02X %02X]\n",
			c_cmd->ctx->key[0], c_cmd->ctx->key[1],
			c_cmd->ctx->key[2], c_cmd->ctx->key[3],
			c_cmd->ctx->key[4], c_cmd->ctx->key[5],
			c_cmd->ctx->key[6], c_cmd->ctx->key[7]);
		SYSCON_INFO("    [%02X %02X %02X %02X %02X %02X %02X %02X]\n",
			c_cmd->ctx->key[8], c_cmd->ctx->key[9],
			c_cmd->ctx->key[10], c_cmd->ctx->key[11],
			c_cmd->ctx->key[12], c_cmd->ctx->key[13],
			c_cmd->ctx->key[14], c_cmd->ctx->key[15]);
		SYSCON_INFO("    [%02X %02X %02X %02X %02X %02X %02X %02X]\n",
			c_cmd->ctx->key[16], c_cmd->ctx->key[17],
			c_cmd->ctx->key[18], c_cmd->ctx->key[19],
			c_cmd->ctx->key[20], c_cmd->ctx->key[21],
			c_cmd->ctx->key[22], c_cmd->ctx->key[23]);
		SYSCON_INFO("    [%02X %02X %02X %02X %02X %02X %02X %02X]\n",
			c_cmd->ctx->key[24], c_cmd->ctx->key[25],
			c_cmd->ctx->key[26], c_cmd->ctx->key[27],
			c_cmd->ctx->key[28], c_cmd->ctx->key[29],
			c_cmd->ctx->key[30], c_cmd->ctx->key[31]);
		break;
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
	default:
		SYSCON_ERR("invalid slot(%d)\n", slot);
		return -EINVAL;
	}
	/* issue interrupt */
	scomm_write(pdev, SCOMM_REG(INT_SECURE), 1);

fail_copy_from_user:
	SYSCON_FUNC_END("ret=%d\n", ierr);
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
static int syscon_cmd_rsp(struct syscon_dev *pdev,
				struct syscon_cmd *cmd, __u32 slot)
{
	int ierr = 0;
	__u32 result;

	SYSCON_FUNC_START("\n");

	/* lock scomm */
	mutex_lock(&(pdev->mutex_scomm_rsp));

	/* read response */
	result = scomm_read(pdev, SCOMM_REG(RSP_RESULT));
	if (result != 0) {
		SYSCON_ERR("result : %08x\n", result);
		ierr = -EFAULT;
		goto fail_result;
	}
	/* reqid and drvdata is not used */
	scomm_read(pdev, SCOMM_REG(RSP_REQID));
	scomm_read(pdev, SCOMM_REG(RSP_DRVDATA));

	scomm_read_buf(pdev, SCOMM_REG(RSP_RESPONSE),
				cmd->cmd_rsp, SYSCON_MAX_CMD_SIZE);
	if (slot == SCOMM_SLOT_L) {
		/* read user data from DRAM */
		/* cmd->rsp_size is checked in syscon_exec_l_slot() */
		if (copy_to_user((void __user *)(cmd->rsp_data), pdev->virt,
					cmd->rsp_size)) {
			SYSCON_ERR("copy_to_user() failed\n");
			ierr = -EFAULT;
			goto fail_copy_to_user;
		}
	}
fail_copy_to_user:
fail_result:
	/* issue interrupt */
	syscon_set_cmd_rsp_ack_s(pdev);

	/* unlock scomm */
	mutex_unlock(&(pdev->mutex_scomm_rsp));
	SYSCON_FUNC_END("ret=%d\n", ierr);
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
int syscon_exec_l_slot(struct syscon_dev *pdev, struct syscon_cmd *cmd)
{
	int ierr = 0;
	unsigned long	to;

	SYSCON_FUNC_START("\n");

	if ((pdev == NULL) || (cmd == NULL)) {
		SYSCON_ERR("invalid parameters pdev(%p), cmd(%p)\n", pdev, cmd);
		return -EINVAL;
	}
	if ((cmd->req_size > SYSCON_MAX_DRAM_SIZE) ||
		(cmd->rsp_size > SYSCON_MAX_DRAM_SIZE)) {
		SYSCON_ERR("requested dram size(req:%d/rsp:%d) is over %d\n",
			cmd->req_size, cmd->rsp_size, SYSCON_MAX_DRAM_SIZE);
		return -EINVAL;
	}
	/* lock slot */
	mutex_lock(&(pdev->mutex_l_slot));

	/* request phase */
	ierr = syscon_cmd_req(pdev, cmd, SCOMM_SLOT_L);
	if (ierr != 0) {
		SYSCON_ERR("request phase failed\n");
		goto fail_request_phase;
	}
	/* wait MBOX interrupt */
	SYSCON_INFO("wait_for_completion\n");
	to = wait_for_completion_timeout(&(pdev->comp_l_slot),
				msecs_to_jiffies(SYSCON_SLOT_TIMEOUT));
	SYSCON_INFO("wake up (%ld)\n", to);
	if (to == 0) {
		/* timeout */
		SYSCON_ERR("SLOT L response timeout\n");
		ierr = -ETIMEDOUT;
		goto fail_response;
	}
	if (pdev->result_l_slot != 0) {
		ierr = -EFAULT;
		goto fail_result;
	}
	/* response phase */
	ierr = syscon_cmd_rsp(pdev, cmd, SCOMM_SLOT_L);
	if (ierr != 0) {
		SYSCON_ERR("response phase failed\n");
		goto fail_response_phase;
	}

fail_response_phase:
fail_result:
fail_response:
fail_request_phase:
	/* unlock slot */
	mutex_unlock(&(pdev->mutex_l_slot));
	SYSCON_FUNC_END("ret=%d\n", ierr);
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
int syscon_exec_s_slot(struct syscon_dev *pdev, struct syscon_cmd *cmd)
{
	int ierr = 0;
	unsigned long	to;

	SYSCON_FUNC_START("\n");

	if ((pdev == NULL) || (cmd == NULL)) {
		SYSCON_ERR("invalid parameters pdev(%p), cmd(%p)\n", pdev, cmd);
		return -EINVAL;
	}
	/* lock slot */
	mutex_lock(&(pdev->mutex_s_slot));

	/* request phase */
	ierr = syscon_cmd_req(pdev, cmd, SCOMM_SLOT_S);
	if (ierr != 0) {
		SYSCON_ERR("request phase failed\n");
		goto fail_request_phase;
	}
	/* wait MBOX interrupt */
	SYSCON_INFO("wait_for_completion\n");
	to = wait_for_completion_timeout(&(pdev->comp_s_slot),
				msecs_to_jiffies(SYSCON_SLOT_TIMEOUT));
	SYSCON_INFO("wake up (%ld)\n", to);
	if (to == 0) {
		/* timeout */
		SYSCON_ERR("SLOT S response timeout\n");
		ierr = -ETIMEDOUT;
		goto fail_response;
	}
	if (pdev->result_s_slot != 0) {
		ierr = -EFAULT;
		goto fail_result;
	}
	/* for debug */
/*	scomm_dump(pdev, SCOMM_REG(REQ_SLOT), 256); */
	/* response phase */
	ierr = syscon_cmd_rsp(pdev, cmd, SCOMM_SLOT_S);
	if (ierr != 0) {
		SYSCON_ERR("response phase failed\n");
		goto fail_response_phase;
	}

fail_response_phase:
fail_result:
fail_response:
fail_request_phase:
	/* unlock slot */
	mutex_unlock(&(pdev->mutex_s_slot));
	SYSCON_FUNC_END("ret=%d\n", ierr);
	return ierr;
}

#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
__u8 syscon_get_free_queno(struct syscon_dev *pdev)
{
	__u8 i, chk = 1;

	SYSCON_FUNC_START("(%p)\n", pdev);
	if (down_interruptible(&(pdev->q_sem))) {
		/* error */
		return SYSCON_INVALID_QNO;
	}
	mutex_lock(&(pdev->mutex_dev));
	SYSCON_INFO("free queue state(%02x)\n", pdev->use_q);
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++, chk <<= 1) {
		if ((pdev->use_q & chk) == 0) {
			pdev->use_q |= chk;
			break;
		}
	}
	mutex_unlock(&(pdev->mutex_dev));
	SYSCON_INFO("free queue no(%d), state(%02x), sem(%d)\n",
				i, pdev->use_q, pdev->q_sem.count);
	return i;
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
void syscon_release_queno(struct syscon_dev *pdev, int queno)
{
	__u8 chk = (1 << queno);

	SYSCON_FUNC_START("(%p, %d)\n", pdev, queno);
	if (queno >= SYSCON_SLOTC_Q_MAX) {
		SYSCON_ERR("invalid parameters queno(%d)\n", queno);
		return;
	}
	mutex_lock(&(pdev->mutex_dev));
	pdev->use_q &= ~(chk);
	up(&(pdev->q_sem));
	mutex_unlock(&(pdev->mutex_dev));
	SYSCON_INFO("free queue state(%02x) sem(%d)\n",
				pdev->use_q, pdev->q_sem.count);
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
int syscon_exec_c_slot(struct syscon_dev *pdev, struct syscon_cmd_c *cmd)
{
	int ierr = 0;
	unsigned long	to;

	SYSCON_FUNC_START("\n");

	if ((pdev == NULL) || (cmd == NULL)) {
		SYSCON_ERR("invalid parameters pdev(%p), cmd(%p)\n", pdev, cmd);
		return -EINVAL;
	}

	/* request phase */
	ierr = syscon_cmd_req(pdev, (struct syscon_cmd *)cmd, SCOMM_SLOT_C);
	if (ierr != 0) {
		SYSCON_ERR("request phase failed\n");
		goto fail_request_phase;
	}
	/* wait MBOX interrupt */
	SYSCON_INFO("wait_for_completion qno[%d]\n", cmd->queno);
	to = wait_for_completion_timeout(&(pdev->comp_c_slot[cmd->queno]),
				msecs_to_jiffies(SYSCON_SLOT_TIMEOUT));
	SYSCON_INFO("wake up qno[%d] (%ld)\n", cmd->queno, to);
	if (to == 0) {
		/* timeout */
		SYSCON_ERR("SLOT C QUENO(%d) response timeout\n", cmd->queno);
		ierr = -ETIMEDOUT;
		goto fail_response;
	}
	if (pdev->result_c_slot[cmd->queno] != 0) {
		SYSCON_ERR("SLOT C request QNO[%d] erro(%d/%d/%d)\n",
				cmd->queno,
				pdev->result_c_slot[cmd->queno],
				pdev->result_c_slot_caller[cmd->queno],
				pdev->result_c_slot_sub[cmd->queno]);
		ierr = -EFAULT;
	}

fail_response:
fail_request_phase:
	SYSCON_FUNC_END("ret=%d\n", ierr);
	return ierr;
}

#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

