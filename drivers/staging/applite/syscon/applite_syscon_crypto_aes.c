/*
 * linux/drivers/staging/applite/syscon/applite_syscon_crypto_aes.c
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

#include <linux/scatterlist.h>
#include <linux/workqueue.h>

#include <crypto/internal/hash.h>

#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)


/*===================================
Static Variables and Functions prototypes
===================================*/

static int syscon_aes_handle_req(__u8 queno);
static int syscon_aes_setkey(struct crypto_ablkcipher *tfm,
				const u8 *key, unsigned int keylen);
static int syscon_aes_ssk_setkey(struct crypto_ablkcipher *tfm,
				const u8 *key, unsigned int keylen);
static int syscon_aes_huk_setkey(struct crypto_ablkcipher *tfm,
				const u8 *key, unsigned int keylen);
static int syscon_aes_ecb_encrypt(struct ablkcipher_request *req);
static int syscon_aes_ecb_decrypt(struct ablkcipher_request *req);
static int syscon_aes_cbc_encrypt(struct ablkcipher_request *req);
static int syscon_aes_cbc_decrypt(struct ablkcipher_request *req);
static int syscon_aes_ctr_encrypt(struct ablkcipher_request *req);
static int syscon_aes_ctr_decrypt(struct ablkcipher_request *req);
static int syscon_aes_crypt(struct ablkcipher_request *req,
					__u32 algo, __u8 mode);
static int syscon_aes_cra_init(struct crypto_tfm *tfm);
static void syscon_aes_cra_exit(struct crypto_tfm *tfm);

static void syscon_aes_handler0(struct work_struct *work);
static void syscon_aes_handler1(struct work_struct *work);
static void syscon_aes_handler2(struct work_struct *work);
static void syscon_aes_handler3(struct work_struct *work);

static DECLARE_WORK(syscon_aes_work0, syscon_aes_handler0);
static DECLARE_WORK(syscon_aes_work1, syscon_aes_handler1);
static DECLARE_WORK(syscon_aes_work2, syscon_aes_handler2);
static DECLARE_WORK(syscon_aes_work3, syscon_aes_handler3);
static struct work_struct *syscon_aes_work[] = {
	&syscon_aes_work0,
	&syscon_aes_work1,
	&syscon_aes_work2,
	&syscon_aes_work3
};


static struct crypto_alg aes_algs[] = {
	{
		.cra_name = "ecb(aes)",
		.cra_driver_name = "ecb-aes-applite",
		.cra_priority = 300,
		.cra_ctxsize = sizeof(struct syscon_ctx),
		.cra_module = THIS_MODULE,
		.cra_init = syscon_aes_cra_init,
		.cra_exit = syscon_aes_cra_exit,
		.cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER |
				CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_alignmask = 3,
		.cra_type = &crypto_ablkcipher_type,
		.cra_u.ablkcipher = {
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.setkey = syscon_aes_setkey,
			.encrypt = syscon_aes_ecb_encrypt,
			.decrypt = syscon_aes_ecb_decrypt,
			.ivsize = 0,
		},
	},
	{
		.cra_name = "cbc(aes)",
		.cra_driver_name = "cbc-aes-applite",
		.cra_priority = 300,
		.cra_ctxsize = sizeof(struct syscon_ctx),
		.cra_module = THIS_MODULE,
		.cra_init = syscon_aes_cra_init,
		.cra_exit = syscon_aes_cra_exit,
		.cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER |
				CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_alignmask = 3,
		.cra_type = &crypto_ablkcipher_type,
		.cra_u.ablkcipher = {
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.setkey = syscon_aes_setkey,
			.encrypt = syscon_aes_cbc_encrypt,
			.decrypt = syscon_aes_cbc_decrypt,
			.ivsize = SYSCON_IV_SIZE,
		},
	},
	{
		.cra_name = "ctr(aes)",
		.cra_driver_name = "ctr-aes-applite",
		.cra_priority = 300,
		.cra_ctxsize = sizeof(struct syscon_ctx),
		.cra_module = THIS_MODULE,
		.cra_init = syscon_aes_cra_init,
		.cra_exit = syscon_aes_cra_exit,
		.cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER |
				CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_alignmask = 3,
		.cra_type = &crypto_ablkcipher_type,
		.cra_u.ablkcipher = {
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.setkey = syscon_aes_setkey,
			.encrypt = syscon_aes_ctr_encrypt,
			.decrypt = syscon_aes_ctr_decrypt,
			.ivsize = SYSCON_IV_SIZE,
		},
	},
	{
		.cra_name = "cbc(aes)-ssk",
		.cra_driver_name = "cbc-aes-ssk-applite",
		.cra_priority = 300,
		.cra_ctxsize = sizeof(struct syscon_ctx),
		.cra_module = THIS_MODULE,
		.cra_init = syscon_aes_cra_init,
		.cra_exit = syscon_aes_cra_exit,
		.cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER |
				CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_alignmask = 3,
		.cra_type = &crypto_ablkcipher_type,
		.cra_u.ablkcipher = {
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.setkey = syscon_aes_ssk_setkey,
			.encrypt = syscon_aes_cbc_encrypt,
			.decrypt = syscon_aes_cbc_decrypt,
			.ivsize = SYSCON_IV_SIZE,
		},
	},
	{
		.cra_name = "cbc(aes)-huk",
		.cra_driver_name = "cbc-aes-huk-applite",
		.cra_priority = 300,
		.cra_ctxsize = sizeof(struct syscon_ctx),
		.cra_module = THIS_MODULE,
		.cra_init = syscon_aes_cra_init,
		.cra_exit = syscon_aes_cra_exit,
		.cra_flags = CRYPTO_ALG_TYPE_ABLKCIPHER |
				CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC,
		.cra_blocksize = AES_BLOCK_SIZE,
		.cra_alignmask = 3,
		.cra_type = &crypto_ablkcipher_type,
		.cra_u.ablkcipher = {
			.min_keysize = AES_MIN_KEY_SIZE,
			.max_keysize = AES_MAX_KEY_SIZE,
			.setkey = syscon_aes_huk_setkey,
			.encrypt = syscon_aes_cbc_encrypt,
			.decrypt = syscon_aes_cbc_decrypt,
			.ivsize = SYSCON_IV_SIZE,
		},
	},
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
static int syscon_aes_handle_req(__u8 queno)
{
	struct crypto_async_request *async_req, *backlog;
	struct crypto_ablkcipher *tfm;
	struct syscon_aes_reqctx *rctx = NULL;
	struct ablkcipher_request *req;
	int ierr = 0, total, ivlen;
	unsigned long flags;
	struct scatterlist *in_sg, *out_sg, *next_in_sg, *next_out_sg;
	struct scatterlist *prv_in_sg, *prv_out_sg;
	__u32 rem_in_sg, rem_out_sg, sg_size, offset_in_sg, offset_out_sg;

	SYSCON_FUNC_START("\n");
	spin_lock_irqsave(&(s_dev.lock), flags);
	backlog = crypto_get_backlog(&(s_dev.queue[queno]));
	async_req = crypto_dequeue_request(&(s_dev.queue[queno]));
	if (async_req == NULL)
		clear_bit(FLAGS_BUSY, &(s_dev.crypto_stat[queno]));
	spin_unlock_irqrestore(&(s_dev.lock), flags);
	if (async_req == NULL) {
		SYSCON_INFO("request is NULL\n");
		return -ENODATA;
	}

	req = ablkcipher_request_cast(async_req);
	if (queno >= SYSCON_SLOTC_Q_MAX) {
		SYSCON_ERR("queue is full(%d)\n", queno);
		ierr = -EBUSY;
		goto fail_exit;
	}

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	if ((req->src == NULL) || (req->dst == NULL)) {
		SYSCON_ERR("invalide address(src:%p, dst:%p)\n",
					req->src, req->dst);
		ierr = -EINVAL;
		goto fail_exit;
	}

	in_sg = req->src;
	out_sg = req->dst;
	total = req->nbytes;
	SYSCON_INFO("SYSCON crypto (%p, %p, %d)\n", in_sg, out_sg, total);

	tfm = crypto_ablkcipher_reqtfm(req);
	rctx = ablkcipher_request_ctx(req);
	rctx->cmd.ctx = crypto_ablkcipher_ctx(tfm);

	ivlen = crypto_ablkcipher_ivsize(tfm);
	if (ivlen == SYSCON_IV_SIZE) {
		memcpy(s_dev.wk_virt[queno], (__u8 *)(req->info),
							SYSCON_IV_SIZE);
		syscon_dump_buf((__u8 *)(s_dev.wk_virt[queno]), SYSCON_IV_SIZE);
	}
	rctx->cmd.iv = s_dev.wk_phys[queno];

	rctx->cmd.mode |= SCOMM_MODE_HEAD;
	rem_in_sg = sg_dma_len(in_sg);
	rem_out_sg = sg_dma_len(out_sg);
	offset_in_sg = 0;
	offset_out_sg = 0;
	prv_in_sg = NULL;
	prv_out_sg = NULL;
	while (total) {
		next_in_sg = sg_next(in_sg);
		next_out_sg = sg_next(out_sg);

		/* check transfer size */
		if (rem_in_sg == rem_out_sg)
			sg_size = rem_in_sg;
		else
			sg_size = min_t(int, rem_in_sg, rem_out_sg);

		/* lock phys address */
		ierr = dma_map_sg(s_dev.device, in_sg, 1, DMA_TO_DEVICE);
		if (ierr == 0) {
			SYSCON_ERR("dma_map_sg(in_sg) failed\n");
			ierr = -EFAULT;
			goto fail_exit;
		}
		ierr = dma_map_sg(s_dev.device, out_sg, 1, DMA_FROM_DEVICE);
		if (ierr == 0) {
			SYSCON_ERR("dma_map_sg(out_sg) failed\n");
			dma_unmap_sg(s_dev.device, in_sg, 1, DMA_TO_DEVICE);
			ierr = -EFAULT;
			goto fail_exit;
		}
REMAIN_EXEC:
		/* get phys address */
		rctx->cmd.src = sg_dma_address(in_sg) + offset_in_sg;
		rctx->cmd.dst = sg_dma_address(out_sg) + offset_out_sg;
		rctx->cmd.len = min_t(int, sg_size, SYSCON_REQ_SIZE_MAX);
		SYSCON_INFO("[%08x -> %08x size(%d) : in(%d), out(%d)\n",
				rctx->cmd.src, rctx->cmd.dst, rctx->cmd.len,
				rem_in_sg, rem_out_sg);

		/* check & set TAIL flag */
		if ((next_in_sg == NULL) && (rctx->cmd.len == rem_in_sg)) {
			SYSCON_INFO("set TAIL flag\n");
			rctx->cmd.mode |= SCOMM_MODE_TAIL;
		}

		/* start crypto & wait completion */
		ierr = syscon_exec_c_slot(&s_dev, &(rctx->cmd));

		if ((ierr == SYSCON_OK) && (sg_size > rctx->cmd.len)) {
			SYSCON_INFO("size is over max size(%d). retry\n",
				SYSCON_REQ_SIZE_MAX);
			offset_in_sg += rctx->cmd.len;
			offset_out_sg += rctx->cmd.len;
			sg_size -= rctx->cmd.len;
			goto REMAIN_EXEC;
		}

		if (prv_in_sg)
			dma_unmap_sg(s_dev.device, prv_in_sg, 1, DMA_TO_DEVICE);

		if (prv_out_sg)
			dma_unmap_sg(s_dev.device, prv_out_sg, 1,
					DMA_FROM_DEVICE);

		if (rctx->cmd.mode & SCOMM_MODE_TAIL) {
			dma_unmap_sg(s_dev.device, in_sg, 1, DMA_TO_DEVICE);
			dma_unmap_sg(s_dev.device, out_sg, 1, DMA_FROM_DEVICE);
		} else {
			prv_in_sg = in_sg;
			prv_out_sg = out_sg;
		}

		if (ierr != SYSCON_OK)
			goto fail_exit;

		rctx->cmd.mode &= ~(SCOMM_MODE_HEAD);

		/* update parameter for next scatterlist */
		total -= rctx->cmd.len;
		rem_in_sg -= rctx->cmd.len;
		rem_out_sg -= rctx->cmd.len;
		SYSCON_INFO("in[%p,%p, %d], out[%p, %p, %d]\n",
			in_sg, next_in_sg, rem_in_sg,
			out_sg, next_out_sg, rem_out_sg);

		if (total) {
			if (rem_in_sg == 0) {
				if (next_in_sg == NULL) {
					SYSCON_ERR("next_in_sg failed\n");
					goto fail_exit;
				}
				in_sg = next_in_sg;
				offset_in_sg = 0;
				rem_in_sg = sg_dma_len(in_sg);
			} else
				offset_in_sg += rctx->cmd.len;
			if (rem_out_sg == 0) {
				if (next_out_sg == NULL) {
					SYSCON_ERR("next_out_sg failed\n");
					goto fail_exit;
				}
				out_sg = next_out_sg;
				offset_out_sg = 0;
				rem_out_sg = sg_dma_len(out_sg);
			} else
				offset_out_sg += rctx->cmd.len;
		}

		WARN_ON((total && ((in_sg == NULL) || (out_sg == NULL))));
	}
	if (ivlen == SYSCON_IV_SIZE)
		memcpy((__u8 *)(req->info), s_dev.wk_virt[queno],
							SYSCON_IV_SIZE);

fail_exit:
	spin_lock_irqsave(&(s_dev.lock), flags);
	if (rctx)
		syscon_release_queno(&(s_dev), queno);
	spin_unlock_irqrestore(&(s_dev.lock), flags);
	if (req->base.complete)
		req->base.complete(&req->base, ierr);

	if (ierr)
		clear_bit(FLAGS_BUSY, &(s_dev.crypto_stat[queno]));
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
static int syscon_aes_setkey(struct crypto_ablkcipher *tfm,
				const u8 *key, unsigned int keylen)
{
	struct syscon_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	int ierr = 0;

	SYSCON_FUNC_START("\n");
	/* check key len */
	if ((keylen != AES_KEYSIZE_128) && (keylen != AES_KEYSIZE_192) &&
		(keylen != AES_KEYSIZE_256)) {
		SYSCON_ERR("unsupported key size(%d)\n", keylen);
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	/* check key data */
	if (key == NULL) {
		SYSCON_ERR("invalid key data\n");
		return -EINVAL;
	}

	ctx->keylen = keylen;
	memcpy(ctx->key, key, keylen);
	memset(&ctx->key[keylen], 0, (0x20 - keylen));

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
static int syscon_aes_ssk_setkey(struct crypto_ablkcipher *tfm,
				const u8 *key, unsigned int keylen)
{
	struct syscon_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	int ierr = 0;

	SYSCON_FUNC_START("\n");
	/* check key len */
	if (keylen != AES_KEYSIZE_256) {
		SYSCON_ERR("unsupported key size(%d)\n", keylen);
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	/* check key data */
	if (key == NULL) {
		SYSCON_ERR("invalid key data\n");
		return -EINVAL;
	}

	ctx->keylen = AES_KEYSIZE_256;
	ctx->keyno = *((unsigned int *)key) + 32;

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
static int syscon_aes_huk_setkey(struct crypto_ablkcipher *tfm,
				const u8 *key, unsigned int keylen)
{
	struct syscon_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	int ierr = 0;

	SYSCON_FUNC_START("\n");
	/* check key len */
	if (keylen != AES_KEYSIZE_256) {
		SYSCON_ERR("unsupported key size(%d)\n", keylen);
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	/* check key data */
	if (key == NULL) {
		SYSCON_ERR("invalid key data\n");
		return -EINVAL;
	}

	ctx->keylen = AES_KEYSIZE_256;
	ctx->keyno = *((unsigned int *)key) + 40;

	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return ierr;
}

static int syscon_aes_ecb_encrypt(struct ablkcipher_request *req)
{
	return syscon_aes_crypt(req, SCOMM_ALGO_AES_ECB, SCOMM_MODE_ENC);
}

static int syscon_aes_ecb_decrypt(struct ablkcipher_request *req)
{
	return syscon_aes_crypt(req, SCOMM_ALGO_AES_ECB, SCOMM_MODE_DEC);
}

static int syscon_aes_cbc_encrypt(struct ablkcipher_request *req)
{
	return syscon_aes_crypt(req, SCOMM_ALGO_AES_CBC, SCOMM_MODE_ENC);
}

static int syscon_aes_cbc_decrypt(struct ablkcipher_request *req)
{
	return syscon_aes_crypt(req, SCOMM_ALGO_AES_CBC, SCOMM_MODE_DEC);
}

static int syscon_aes_ctr_encrypt(struct ablkcipher_request *req)
{
	return syscon_aes_crypt(req, SCOMM_ALGO_AES_CTR, SCOMM_MODE_ENC);
}

static int syscon_aes_ctr_decrypt(struct ablkcipher_request *req)
{
	return syscon_aes_crypt(req, SCOMM_ALGO_AES_CTR, SCOMM_MODE_DEC);
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
static int syscon_aes_crypt(struct ablkcipher_request *req,
					__u32 algo, __u8 mode)
{
	struct syscon_aes_reqctx *rctx = ablkcipher_request_ctx(req);
	int ierr = 0, busy;
	unsigned long flags;

	SYSCON_FUNC_START("algo:%08x, mode:%02x\n", algo, mode);
	rctx->cmd.algo = algo;
	rctx->cmd.mode = mode;
	spin_lock_irqsave(&(s_dev.lock), flags);
	rctx->cmd.queno = syscon_get_free_queno(&(s_dev));
	if (rctx->cmd.queno == SYSCON_INVALID_QNO) {
		spin_unlock_irqrestore(&(s_dev.lock), flags);
		ierr = -EFAULT;
		SYSCON_FUNC_END("ret(%d)\n", ierr);
		return ierr;
	}
	ierr = ablkcipher_enqueue_request(&(s_dev.queue[rctx->cmd.queno]), req);
	busy = test_and_set_bit(FLAGS_BUSY,
				&(s_dev.crypto_stat[rctx->cmd.queno]));
	spin_unlock_irqrestore(&(s_dev.lock), flags);

	if (busy == 0)
		queue_work(syscon_wq[rctx->cmd.queno],
					syscon_aes_work[rctx->cmd.queno]);

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
static void syscon_aes_handler0(struct work_struct *work)
{
	int ierr;

	SYSCON_FUNC_START("\n");
	do {
		ierr = syscon_aes_handle_req(0);
	} while (ierr == SYSCON_OK);
	SYSCON_FUNC_END("\n");
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
static void syscon_aes_handler1(struct work_struct *work)
{
	int ierr;

	SYSCON_FUNC_START("\n");
	do {
		ierr = syscon_aes_handle_req(1);
	} while (ierr == SYSCON_OK);
	SYSCON_FUNC_END("\n");
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
static void syscon_aes_handler2(struct work_struct *work)
{
	int ierr;

	SYSCON_FUNC_START("\n");
	do {
		ierr = syscon_aes_handle_req(2);
	} while (ierr == SYSCON_OK);
	SYSCON_FUNC_END("\n");
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
static void syscon_aes_handler3(struct work_struct *work)
{
	int ierr;

	SYSCON_FUNC_START("\n");
	do {
		ierr = syscon_aes_handle_req(3);
	} while (ierr == SYSCON_OK);
	SYSCON_FUNC_END("\n");
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
static int syscon_aes_cra_init(struct crypto_tfm *tfm)
{
	SYSCON_FUNC_START("\n");
	tfm->crt_ablkcipher.reqsize = sizeof(struct syscon_aes_reqctx);
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
static void syscon_aes_cra_exit(struct crypto_tfm *tfm)
{
	SYSCON_FUNC_START("\n");
	SYSCON_FUNC_END("\n");
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
int syscon_crypto_aes_init(struct syscon_dev *pdev)
{
	int i, ierr = 0;

	SYSCON_FUNC_START("\n");

	for (i = 0; i < ARRAY_SIZE(aes_algs); i++) {
		INIT_LIST_HEAD(&aes_algs[i].cra_list);
		ierr = crypto_register_alg(&aes_algs[i]);
		if (ierr != 0)
			goto fail_crypto_register_aes_alg;
	}
	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return SYSCON_OK;

fail_crypto_register_aes_alg:
	for (--i; i >= 0; i--)
		crypto_unregister_alg(&aes_algs[i]);


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
void syscon_crypto_aes_exit(struct syscon_dev *pdev)
{
	int i;

	SYSCON_FUNC_START("\n");

	for (i = 0; i < ARRAY_SIZE(aes_algs); i++)
		crypto_unregister_alg(&aes_algs[i]);
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++)
		cancel_work_sync(syscon_aes_work[i]);
	SYSCON_FUNC_END("ret\n");
}
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */


