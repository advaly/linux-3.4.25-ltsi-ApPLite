/*
 * linux/drivers/staging/applite/syscon/applite_syscon_crypto_sha.c
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

static int syscon_sha_handle_req(__u8 queno);
static int syscon_sha1_init(struct ahash_request *req);
static int syscon_sha224_init(struct ahash_request *req);
static int syscon_sha256_init(struct ahash_request *req);
static int syscon_sha_init(struct ahash_request *req, __u32 algo);
static int syscon_sha_update(struct ahash_request *req);
static int syscon_sha_final(struct ahash_request *req);
static int syscon_sha_finup(struct ahash_request *req);
static int syscon_sha1_digest(struct ahash_request *req);
static int syscon_sha224_digest(struct ahash_request *req);
static int syscon_sha256_digest(struct ahash_request *req);
static int syscon_sha_digest(struct ahash_request *req, __u32 algo);
static int syscon_hmac_sha1_init(struct ahash_request *req);
static int syscon_hmac_sha224_init(struct ahash_request *req);
static int syscon_hmac_sha256_init(struct ahash_request *req);
static int syscon_hmac_sha_init(struct ahash_request *req, __u32 algo);
static int syscon_hmac_sha_update(struct ahash_request *req);
static int syscon_hmac_sha_final(struct ahash_request *req);
static int syscon_hmac_sha_finup(struct ahash_request *req);
static int syscon_hmac_sha1_digest(struct ahash_request *req);
static int syscon_hmac_sha224_digest(struct ahash_request *req);
static int syscon_hmac_sha256_digest(struct ahash_request *req);
static int syscon_hmac_sha_digest(struct ahash_request *req, __u32 algo);
static int syscon_hmac_sha1_setkey(struct crypto_ahash *tfm,
				const u8 *key, unsigned int keylen);
static int syscon_hmac_sha224_setkey(struct crypto_ahash *tfm,
				const u8 *key, unsigned int keylen);
static int syscon_hmac_sha256_setkey(struct crypto_ahash *tfm,
				const u8 *key, unsigned int keylen);
static int syscon_hmac_sha_setkey(struct crypto_ahash *tfm, const u8 *key,
					unsigned int keylen, __u32 algo);
static void syscon_hash_complete(struct crypto_async_request *req, int err);
static int syscon_request_hash(struct syscon_hmac_ctx *ctx,
			struct scatterlist *sg, unsigned int len, u8 *result);

static int syscon_sha_cra_init(struct crypto_tfm *tfm);
static void syscon_sha_cra_exit(struct crypto_tfm *tfm);
static int syscon_hmac_sha_cra_init(struct crypto_tfm *tfm);
static void syscon_hmac_sha_cra_exit(struct crypto_tfm *tfm);


static void syscon_sha_handler0(struct work_struct *work);
static void syscon_sha_handler1(struct work_struct *work);
static void syscon_sha_handler2(struct work_struct *work);
static void syscon_sha_handler3(struct work_struct *work);

static DECLARE_WORK(syscon_sha_work0, syscon_sha_handler0);
static DECLARE_WORK(syscon_sha_work1, syscon_sha_handler1);
static DECLARE_WORK(syscon_sha_work2, syscon_sha_handler2);
static DECLARE_WORK(syscon_sha_work3, syscon_sha_handler3);
static struct work_struct *syscon_sha_work[] = {
	&syscon_sha_work0,
	&syscon_sha_work1,
	&syscon_sha_work2,
	&syscon_sha_work3
};

static struct ahash_alg sha_algs[] = {
	{
		.init = syscon_sha1_init,
		.update = syscon_sha_update,
		.final = syscon_sha_final,
		.finup = syscon_sha_finup,
		.digest = syscon_sha1_digest,
		.halg = {
			.digestsize = SHA1_DIGEST_SIZE,
			.base = {
				.cra_name = "sha1",
				.cra_driver_name = "sha1-applite",
				.cra_priority = 300,
				.cra_ctxsize = sizeof(struct syscon_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = syscon_sha_cra_init,
				.cra_exit = syscon_sha_cra_exit,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
						CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_alignmask = 3,
			}
		}
	},
	{
		.init = syscon_sha224_init,
		.update = syscon_sha_update,
		.final = syscon_sha_final,
		.finup = syscon_sha_finup,
		.digest = syscon_sha224_digest,
		.halg = {
			.digestsize = SHA224_DIGEST_SIZE,
			.base = {
				.cra_name = "sha224",
				.cra_driver_name = "sha224-applite",
				.cra_priority = 300,
				.cra_ctxsize = sizeof(struct syscon_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = syscon_sha_cra_init,
				.cra_exit = syscon_sha_cra_exit,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
						CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_alignmask = 3,
			}
		}
	},
	{
		.init = syscon_sha256_init,
		.update = syscon_sha_update,
		.final = syscon_sha_final,
		.finup = syscon_sha_finup,
		.digest = syscon_sha256_digest,
		.halg = {
			.digestsize = SHA256_DIGEST_SIZE,
			.base = {
				.cra_name = "sha256",
				.cra_driver_name = "sha256-applite",
				.cra_priority = 300,
				.cra_ctxsize = sizeof(struct syscon_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = syscon_sha_cra_init,
				.cra_exit = syscon_sha_cra_exit,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
						CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_alignmask = 3,
			}
		}
	},
	{
		.init = syscon_hmac_sha1_init,
		.update = syscon_hmac_sha_update,
		.final = syscon_hmac_sha_final,
		.finup = syscon_hmac_sha_finup,
		.digest = syscon_hmac_sha1_digest,
		.setkey = syscon_hmac_sha1_setkey,
		.halg = {
			.digestsize = SHA1_DIGEST_SIZE,
			.base = {
				.cra_name = "hmac(sha1)",
				.cra_driver_name = "hmac-sha1-applite",
				.cra_priority = 300,
				.cra_ctxsize = sizeof(struct syscon_hmac_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = syscon_hmac_sha_cra_init,
				.cra_exit = syscon_hmac_sha_cra_exit,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
						CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_alignmask = 3,
			}
		}
	},
	{
		.init = syscon_hmac_sha224_init,
		.update = syscon_hmac_sha_update,
		.final = syscon_hmac_sha_final,
		.finup = syscon_hmac_sha_finup,
		.digest = syscon_hmac_sha224_digest,
		.setkey = syscon_hmac_sha224_setkey,
		.halg = {
			.digestsize = SHA224_DIGEST_SIZE,
			.base = {
				.cra_name = "hmac(sha224)",
				.cra_driver_name = "hmac-sha224-applite",
				.cra_priority = 300,
				.cra_ctxsize = sizeof(struct syscon_hmac_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = syscon_hmac_sha_cra_init,
				.cra_exit = syscon_hmac_sha_cra_exit,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
						CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_alignmask = 3,
			}
		}
	},
	{
		.init = syscon_hmac_sha256_init,
		.update = syscon_hmac_sha_update,
		.final = syscon_hmac_sha_final,
		.finup = syscon_hmac_sha_finup,
		.digest = syscon_hmac_sha256_digest,
		.setkey = syscon_hmac_sha256_setkey,
		.halg = {
			.digestsize = SHA256_DIGEST_SIZE,
			.base = {
				.cra_name = "hmac(sha256)",
				.cra_driver_name = "hmac-sha256-applite",
				.cra_priority = 300,
				.cra_ctxsize = sizeof(struct syscon_hmac_ctx),
				.cra_module = THIS_MODULE,
				.cra_init = syscon_hmac_sha_cra_init,
				.cra_exit = syscon_hmac_sha_cra_exit,
				.cra_flags = CRYPTO_ALG_TYPE_AHASH |
						CRYPTO_ALG_KERN_DRIVER_ONLY |
						CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_alignmask = 3,
			}
		}
	}
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

static inline void syscon_get_result(__u32 algo, __u8 qno, __u8 *result)
{
	switch (algo) {
	case SCOMM_ALGO_SHA1:
		memcpy(result, s_dev.wk_virt[qno], SHA1_DIGEST_SIZE); break;
	case SCOMM_ALGO_SHA2_224:
		memcpy(result, s_dev.wk_virt[qno], SHA224_DIGEST_SIZE); break;
	case SCOMM_ALGO_SHA2_256:
		memcpy(result, s_dev.wk_virt[qno], SHA256_DIGEST_SIZE); break;
	default:
		SYSCON_ERR("invalide algo(%08x)\n", algo);
	}
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
static int syscon_sha_handle_req(__u8 queno)
{
	struct crypto_async_request *async_req, *backlog;
	struct syscon_hash_reqctx *rctx = NULL;
	struct ahash_request *req;
	int ierr = 0, total;
	unsigned long flags;
	struct scatterlist *in_sg, *next_in_sg;

	SYSCON_FUNC_START("(queno:%d)\n", queno);
	spin_lock_irqsave(&(s_dev.lock), flags);
	backlog = crypto_get_backlog(&(s_dev.queue[queno]));
	async_req = crypto_dequeue_request(&(s_dev.queue[queno]));
	if (async_req == NULL)
		clear_bit(FLAGS_BUSY, &(s_dev.crypto_stat[queno]));
	if (async_req != NULL) {
		req = ahash_request_cast(async_req);
		rctx = ahash_request_ctx(req);
	}
	spin_unlock_irqrestore(&(s_dev.lock), flags);
	if (async_req == NULL) {
		SYSCON_INFO("request is NULL\n");
		return -ENODATA;
	}

	if (queno >= SYSCON_SLOTC_Q_MAX) {
		SYSCON_ERR("queue is full(%d)\n", queno);
		ierr = -EBUSY;
		goto fail_exit;
	}

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	if (req->src == NULL) {
		SYSCON_ERR("invalide address(src:%p, result:%p)\n",
						req->src, req->result);
		ierr = -EINVAL;
		goto fail_exit;
	}

	in_sg = req->src;
	total = req->nbytes;
	SYSCON_INFO("SYSCON crypto (%p, %d)\n", in_sg, total);

	while (total) {
		next_in_sg = sg_next(in_sg);
		/* add TAIL flag, when last sg and not 4byte boundary */
		if ((next_in_sg == NULL) && (sg_dma_len(in_sg) & 0x3)) {
			SYSCON_INFO("add TAIL flag (%d)\n", sg_dma_len(in_sg));
			rctx->cmd.mode |= SCOMM_MODE_TAIL;
		}

		/* lock phys address */
		ierr = dma_map_sg(s_dev.device, in_sg, 1, DMA_TO_DEVICE);
		if (ierr == 0) {
			SYSCON_ERR("dma_map_sg(in_sg) failed\n");
			ierr = -EFAULT;
			goto fail_exit;
		}
		/* get phys address */
		rctx->cmd.src = sg_dma_address(in_sg);
		rctx->cmd.dst = s_dev.wk_phys[queno];
		rctx->cmd.len = min_t(int, sg_dma_len(in_sg),
						SYSCON_REQ_SIZE_MAX);
		rctx->cmd.iv = 0;

		/* start crypto & wait completion */
		ierr = syscon_exec_c_slot(&s_dev, &(rctx->cmd));

		dma_unmap_sg(s_dev.device, in_sg, 1, DMA_TO_DEVICE);
		if (ierr != SYSCON_OK)
			goto fail_exit;

		/* remove HEAD flag */
		rctx->cmd.mode &= ~(SCOMM_MODE_HEAD);

		total -= rctx->cmd.len;
		in_sg = next_in_sg;
		WARN_ON(((total != 0) && (in_sg == NULL)));
	}
	if (req->result != NULL)
		syscon_get_result(rctx->cmd.algo, queno, req->result);

fail_exit:
	spin_lock_irqsave(&(s_dev.lock), flags);
	if (rctx->free_queue == 1)
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
static int syscon_sha_init(struct ahash_request *req, __u32 algo)
{
	int ierr = 0;
	struct syscon_hash_reqctx *rctx;
	struct crypto_ahash *tfm;

	SYSCON_FUNC_START("algo:%08x\n", algo);
	tfm = crypto_ahash_reqtfm(req);
	rctx = ahash_request_ctx(req);
	rctx->cmd.ctx = crypto_ahash_ctx(tfm);
	rctx->cmd.algo = algo;
	rctx->cmd.queno = SYSCON_INVALID_QNO;
	rctx->cmd.mode = SCOMM_MODE_HEAD;
	rctx->free_queue = 0;
	rctx->pre_hash = 0;
	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return ierr;
}


static int syscon_sha1_init(struct ahash_request *req)
{
	return syscon_sha_init(req, SCOMM_ALGO_SHA1);
}

static int syscon_sha224_init(struct ahash_request *req)
{
	return syscon_sha_init(req, SCOMM_ALGO_SHA2_224);
}

static int syscon_sha256_init(struct ahash_request *req)
{
	return syscon_sha_init(req, SCOMM_ALGO_SHA2_256);
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
static int syscon_sha_update(struct ahash_request *req)
{
	int ierr = 0, busy;
	unsigned long flags;
	struct syscon_hash_reqctx *rctx;

	SYSCON_FUNC_START("\n");
	rctx = ahash_request_ctx(req);
	spin_lock_irqsave(&(s_dev.lock), flags);
	/* get queue no */
	if (rctx->cmd.queno == SYSCON_INVALID_QNO)
		rctx->cmd.queno = syscon_get_free_queno(&(s_dev));
	if (rctx->cmd.queno == SYSCON_INVALID_QNO) {
		spin_unlock_irqrestore(&(s_dev.lock), flags);
		ierr = -EFAULT;
		SYSCON_FUNC_END("ret(%d)\n", ierr);
		return ierr;
	}
	/* check wq status */
	busy = test_and_set_bit(FLAGS_BUSY,
				&(s_dev.crypto_stat[rctx->cmd.queno]));
	/* enqueue request */
	ierr = ahash_enqueue_request(&(s_dev.queue[rctx->cmd.queno]), req);
	spin_unlock_irqrestore(&(s_dev.lock), flags);

	/* execute wq */
	if (busy == 0)
		queue_work(syscon_wq[rctx->cmd.queno],
					syscon_sha_work[rctx->cmd.queno]);

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
static int syscon_sha_final(struct ahash_request *req)
{
	int ierr = 0;
	struct syscon_hash_reqctx *rctx;

	SYSCON_FUNC_START("\n");
	rctx = ahash_request_ctx(req);
	/* check result buffer */
	if (req->result != NULL) {
		SYSCON_INFO("get result alg(%08x), que(%d)\n",
				rctx->cmd.algo, rctx->cmd.queno);
		syscon_get_result(rctx->cmd.algo, rctx->cmd.queno, req->result);
	} else {
		SYSCON_ERR("result is NULL\n");
		ierr = -EINVAL;
	}
	/* release queue */
	syscon_release_queno(&(s_dev), rctx->cmd.queno);

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
static int syscon_sha_finup(struct ahash_request *req)
{
	int ierr = 0, busy;
	unsigned long flags;
	struct syscon_hash_reqctx *rctx;

	SYSCON_FUNC_START("\n");
	if (req->result == NULL) {
		SYSCON_ERR("result is NULL\n");
		ierr = -EINVAL;
	}
	rctx = ahash_request_ctx(req);
	spin_lock_irqsave(&(s_dev.lock), flags);
	/* get queue no */
	if (rctx->cmd.queno == SYSCON_INVALID_QNO)
		rctx->cmd.queno = syscon_get_free_queno(&(s_dev));
	if (rctx->cmd.queno == SYSCON_INVALID_QNO) {
		spin_unlock_irqrestore(&(s_dev.lock), flags);
		ierr = -EFAULT;
		SYSCON_FUNC_END("ret(%d)\n", ierr);
		return ierr;
	}
	/* check wq status */
	busy = test_and_set_bit(FLAGS_BUSY,
				&(s_dev.crypto_stat[rctx->cmd.queno]));
	/* enqueue request */
	ierr = ahash_enqueue_request(&(s_dev.queue[rctx->cmd.queno]), req);
	spin_unlock_irqrestore(&(s_dev.lock), flags);
	rctx->free_queue = 1;

	/* execute wq */
	if (busy == 0)
		queue_work(syscon_wq[rctx->cmd.queno],
					syscon_sha_work[rctx->cmd.queno]);

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
static int syscon_sha_digest(struct ahash_request *req, __u32 algo)
{
	int ierr = 0, busy;
	unsigned long flags;
	struct syscon_hash_reqctx *rctx;
	struct crypto_ahash *tfm;

	SYSCON_FUNC_START("algo:%08x\n", algo);
	tfm = crypto_ahash_reqtfm(req);
	rctx = ahash_request_ctx(req);
	/* initialize request context */
	rctx->cmd.ctx = crypto_ahash_ctx(tfm);
	rctx->cmd.algo = algo;
	rctx->cmd.mode = SCOMM_MODE_HEAD;
	rctx->free_queue = 1;

	spin_lock_irqsave(&(s_dev.lock), flags);
	/* get queue no */
	rctx->cmd.queno = syscon_get_free_queno(&(s_dev));
	if (rctx->cmd.queno == SYSCON_INVALID_QNO) {
		spin_unlock_irqrestore(&(s_dev.lock), flags);
		ierr = -EFAULT;
		SYSCON_FUNC_END("ret(%d)\n", ierr);
		return ierr;
	}
	/* check wq status */
	busy = test_and_set_bit(FLAGS_BUSY,
				&(s_dev.crypto_stat[rctx->cmd.queno]));
	/* enqueue request */
	ierr = ahash_enqueue_request(&(s_dev.queue[rctx->cmd.queno]), req);
	spin_unlock_irqrestore(&(s_dev.lock), flags);

	if (busy == 0)
		queue_work(syscon_wq[rctx->cmd.queno],
					syscon_sha_work[rctx->cmd.queno]);

	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return ierr;
}


static int syscon_sha1_digest(struct ahash_request *req)
{
	return syscon_sha_digest(req, SCOMM_ALGO_SHA1);
}

static int syscon_sha224_digest(struct ahash_request *req)
{
	return syscon_sha_digest(req, SCOMM_ALGO_SHA2_224);
}

static int syscon_sha256_digest(struct ahash_request *req)
{
	return syscon_sha_digest(req, SCOMM_ALGO_SHA2_256);
}


static void syscon_hash_complete(struct crypto_async_request *req, int err)
{
	struct syscon_hmac_ctx *ctx = req->data;

	SYSCON_FUNC_START("\n");
	if (err == -EINPROGRESS)
		return;

	ctx->err = err;
	complete(&(ctx->comp));
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
static int syscon_request_hash(struct syscon_hmac_ctx *ctx,
			struct scatterlist *sg, unsigned int len, u8 *result)
{
	int ierr;

	SYSCON_FUNC_START("(sg:%p, len:%d, result:%p)\n", sg, len, result);

	init_completion(&(ctx->comp));
	/* set callback function */
	ahash_request_set_callback(ctx->req, CRYPTO_TFM_REQ_MAY_BACKLOG,
			syscon_hash_complete, ctx);

	/* set request scatterlist & result buffer */
	ahash_request_set_crypt(ctx->req, sg, result, len);
	/* execute hash request */
	ierr = crypto_ahash_update(ctx->req);
	switch (ierr) {
	case 0:
		break;
	case -EINPROGRESS:
	case -EBUSY:
		ierr = wait_for_completion_interruptible(&(ctx->comp));
		if (ierr == 0)
			ierr = ctx->err;
		break;
	default:
		break;
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
static int syscon_hmac_sha_setkey(struct crypto_ahash *tfm, const u8 *key,
					unsigned int keylen, __u32 algo)
{
	int ierr = 0, i;
	struct syscon_hash_reqctx *rctx;
	struct syscon_hmac_ctx *ctx = crypto_ahash_ctx(tfm);
	int blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	int digestsize = crypto_ahash_digestsize(tfm);
	struct scatterlist sg[1];

	SYSCON_FUNC_START("\n");
	/* check key data */
	if (key == NULL) {
		SYSCON_ERR("invalid key data\n");
		return -EINVAL;
	}
	/* check key len */
	SYSCON_INFO("keylen(%d), blocksize(%d)\n", keylen, blocksize);
	syscon_dump_buf((__u8 *)key, keylen);
	if (keylen > blocksize) {
		/* hash key */
		rctx = ahash_request_ctx(ctx->req);
		rctx->cmd.ctx = crypto_ahash_ctx(tfm);
		rctx->cmd.algo = algo;
		rctx->cmd.queno = SYSCON_INVALID_QNO;
		rctx->cmd.mode = SCOMM_MODE_HEAD | SCOMM_MODE_TAIL;
		rctx->free_queue = 1;
		rctx->pre_hash = 0;
		sg_init_one(sg, key, keylen);
		ierr = syscon_request_hash(ctx, sg, keylen, ctx->i_key);
		if (ierr != 0) {
			crypto_ahash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
			return -EINVAL;
		}
		keylen = digestsize;
	} else
		memcpy(ctx->i_key, key, keylen);

	/* save key */
	memset(ctx->i_key + keylen, 0, blocksize - keylen);
	memcpy(ctx->o_key, ctx->i_key, blocksize);

	/* XOR key data */
	for (i = 0; i < blocksize; i++) {
		ctx->i_key[i] ^= 0x36;
		ctx->o_key[i] ^= 0x5C;
	}
	ctx->keylen = blocksize;

	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return ierr;
}

static int syscon_hmac_sha1_setkey(struct crypto_ahash *tfm,
				const u8 *key, unsigned int keylen)
{
	return syscon_hmac_sha_setkey(tfm, key, keylen, SCOMM_ALGO_SHA1);
}

static int syscon_hmac_sha224_setkey(struct crypto_ahash *tfm,
				const u8 *key, unsigned int keylen)
{
	return syscon_hmac_sha_setkey(tfm, key, keylen, SCOMM_ALGO_SHA2_224);
}

static int syscon_hmac_sha256_setkey(struct crypto_ahash *tfm,
				const u8 *key, unsigned int keylen)
{
	return syscon_hmac_sha_setkey(tfm, key, keylen, SCOMM_ALGO_SHA2_256);
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
static int syscon_hmac_sha_init(struct ahash_request *req, __u32 algo)
{
	int ierr = 0;
	struct syscon_hash_reqctx *rctx;
	struct crypto_ahash *tfm;

	SYSCON_FUNC_START("algo:%08x\n", algo);
	tfm = crypto_ahash_reqtfm(req);
	rctx = ahash_request_ctx(req);
	rctx->cmd.ctx = crypto_ahash_ctx(tfm);
	rctx->cmd.algo = algo;
	rctx->cmd.mode = 0;
	rctx->cmd.queno = SYSCON_INVALID_QNO;
	rctx->free_queue = 0;
	rctx->pre_hash = 1;

	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return ierr;
}


static int syscon_hmac_sha1_init(struct ahash_request *req)
{
	return syscon_hmac_sha_init(req, SCOMM_ALGO_SHA1);
}

static int syscon_hmac_sha224_init(struct ahash_request *req)
{
	return syscon_hmac_sha_init(req, SCOMM_ALGO_SHA2_224);
}

static int syscon_hmac_sha256_init(struct ahash_request *req)
{
	return syscon_hmac_sha_init(req, SCOMM_ALGO_SHA2_256);
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
static int syscon_hmac_sha_update(struct ahash_request *req)
{
	int ierr = 0, busy;
	unsigned long flags;
	struct syscon_hash_reqctx *rctx;
	struct syscon_hash_reqctx *rctx2;
	struct syscon_hmac_ctx *ctx;
	struct scatterlist sg[1];

	SYSCON_FUNC_START("\n");
	rctx = ahash_request_ctx(req);

	spin_lock_irqsave(&(s_dev.lock), flags);
	if (rctx->cmd.queno == SYSCON_INVALID_QNO)
		rctx->cmd.queno = syscon_get_free_queno(&(s_dev));
	spin_unlock_irqrestore(&(s_dev.lock), flags);
	if (rctx->cmd.queno == SYSCON_INVALID_QNO) {
		ierr = -EFAULT;
		SYSCON_FUNC_END("ret(%d)\n", ierr);
		return ierr;
	}

	if (rctx->pre_hash) {
		rctx->pre_hash = 0;

		ctx = (struct syscon_hmac_ctx *)(rctx->cmd.ctx);
		rctx2 = ahash_request_ctx(ctx->req);

		SYSCON_INFO("hash i_keypad (%p/%p)\n", rctx, rctx2);
		syscon_dump_buf((__u8 *)ctx->i_key, ctx->keylen);
		rctx2->cmd.ctx = rctx->cmd.ctx;
		rctx2->cmd.algo = rctx->cmd.algo;
		rctx2->cmd.mode = SCOMM_MODE_HEAD | SCOMM_MODE_TAIL;
		rctx2->cmd.queno = rctx->cmd.queno;
		rctx2->free_queue = 0;
		rctx2->pre_hash = 0;
		SYSCON_INFO("qno:%d, key:%p, len:%d\n", rctx->cmd.queno,
						ctx->i_key, ctx->keylen);
		memcpy(s_dev.hmac_wk_virt[rctx->cmd.queno],
					ctx->i_key, ctx->keylen);

		sg_init_one(sg, s_dev.hmac_wk_virt[rctx->cmd.queno],
					ctx->keylen);
		SYSCON_INFO("sg:%p, buf:%p, len:%d\n", sg,
			s_dev.hmac_wk_virt[rctx->cmd.queno], ctx->keylen);
		ierr = syscon_request_hash(ctx, sg, ctx->keylen, NULL);
		if (ierr) {
			SYSCON_FUNC_END("ret(%d)\n", ierr);
			return ierr;
		}
	}

	spin_lock_irqsave(&(s_dev.lock), flags);
	ierr = ahash_enqueue_request(&(s_dev.queue[rctx->cmd.queno]), req);
	busy = test_and_set_bit(FLAGS_BUSY,
				&(s_dev.crypto_stat[rctx->cmd.queno]));
	spin_unlock_irqrestore(&(s_dev.lock), flags);

	if (busy == 0)
		queue_work(syscon_wq[rctx->cmd.queno],
					syscon_sha_work[rctx->cmd.queno]);

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
static int syscon_hmac_sha_final(struct ahash_request *req)
{
	int ierr = 0;
	struct syscon_hash_reqctx *rctx, *rctx2;
	struct crypto_ahash *tfm;
	struct syscon_hmac_ctx *ctx;
	int digestsize;
	struct scatterlist sg[1];

	SYSCON_FUNC_START("\n");
	if (req->result == NULL) {
		SYSCON_ERR("result is NULL\n");
		ierr = -EINVAL;
	}

	tfm = crypto_ahash_reqtfm(req);
	digestsize = crypto_ahash_digestsize(tfm);
	rctx = ahash_request_ctx(req);
	ctx = crypto_ahash_ctx(tfm);
	rctx2 = ahash_request_ctx(ctx->req);
	SYSCON_INFO("hash o_keypad (%p/%p)\n", rctx, rctx2);
	rctx2->cmd.ctx = rctx->cmd.ctx;
	rctx2->cmd.algo = rctx->cmd.algo;
	rctx2->cmd.mode = SCOMM_MODE_HEAD | SCOMM_MODE_TAIL;
	rctx2->cmd.queno = rctx->cmd.queno;
	rctx2->free_queue = 1;
	memcpy(s_dev.hmac_wk_virt[rctx->cmd.queno], ctx->o_key, ctx->keylen);
	syscon_get_result(rctx->cmd.algo, rctx->cmd.queno,
		(__u8 *)&(s_dev.hmac_wk_virt[rctx->cmd.queno][ctx->keylen]));

	sg_init_one(sg, s_dev.hmac_wk_virt[rctx->cmd.queno],
						ctx->keylen + digestsize);
	ierr = syscon_request_hash(ctx, sg, ctx->keylen + digestsize,
						req->result);

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
static int syscon_hmac_sha_finup(struct ahash_request *req)
{
	int ierr = 0, busy;
	unsigned long flags;
	struct syscon_hash_reqctx *rctx, *rctx2;
	struct syscon_hmac_ctx *ctx;
	struct crypto_ahash *tfm;

	SYSCON_FUNC_START("\n");
	if (req->result == NULL) {
		SYSCON_ERR("result is NULL\n");
		ierr = -EINVAL;
	}
	rctx = ahash_request_ctx(req);
	spin_lock_irqsave(&(s_dev.lock), flags);
	if (rctx->cmd.queno == SYSCON_INVALID_QNO)
		rctx->cmd.queno = syscon_get_free_queno(&(s_dev));
	if (rctx->cmd.queno == SYSCON_INVALID_QNO) {
		spin_unlock_irqrestore(&(s_dev.lock), flags);
		ierr = -EFAULT;
		SYSCON_FUNC_END("ret(%d)\n", ierr);
		return ierr;
	}
	busy = test_and_set_bit(FLAGS_BUSY,
				&(s_dev.crypto_stat[rctx->cmd.queno]));
	ierr = ahash_enqueue_request(&(s_dev.queue[rctx->cmd.queno]), req);
	spin_unlock_irqrestore(&(s_dev.lock), flags);

	ctx = (struct syscon_hmac_ctx *)(rctx->cmd.ctx);
	rctx2 = ahash_request_ctx(ctx->req);
	SYSCON_INFO("hash i_keypad (%p/%p)\n", rctx, rctx2);
	rctx2->cmd.ctx = rctx->cmd.ctx;
	rctx2->cmd.algo = rctx->cmd.algo;
	rctx2->cmd.mode = rctx->cmd.mode;
	rctx2->cmd.queno = rctx->cmd.queno;
	rctx2->pre_hash = rctx->pre_hash;

	/* execute remain data */
	ierr = syscon_request_hash(ctx, ctx->req->src, ctx->req->nbytes, NULL);

	tfm = crypto_ahash_reqtfm(req);
	tfm->final(req);

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
static int syscon_hmac_sha_digest(struct ahash_request *req, __u32 algo)
{
	int ierr = 0;
	struct crypto_ahash *tfm;

	SYSCON_FUNC_START("algo:%08x\n", algo);
	tfm = crypto_ahash_reqtfm(req);
	ierr = tfm->init(req);
	if (ierr)
		return ierr;

	ierr = tfm->finup(req);

	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return ierr;
}


static int syscon_hmac_sha1_digest(struct ahash_request *req)
{
	return syscon_hmac_sha_digest(req, SCOMM_ALGO_SHA1);
}

static int syscon_hmac_sha224_digest(struct ahash_request *req)
{
	return syscon_hmac_sha_digest(req, SCOMM_ALGO_SHA2_224);
}

static int syscon_hmac_sha256_digest(struct ahash_request *req)
{
	return syscon_hmac_sha_digest(req, SCOMM_ALGO_SHA2_256);
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
static int syscon_sha_cra_init(struct crypto_tfm *tfm)
{
	struct crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	SYSCON_FUNC_START("\n");
	crypto_ahash_set_reqsize(ahash, sizeof(struct syscon_hash_reqctx));
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
static int syscon_hmac_sha_cra_init(struct crypto_tfm *tfm)
{
	int ierr;
	struct crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	struct syscon_hmac_ctx *ctx = crypto_ahash_ctx(ahash);

	SYSCON_FUNC_START("\n");
	ierr = syscon_sha_cra_init(tfm);
	if (ierr != 0)
		return ierr;
	ctx->req = ahash_request_alloc(ahash, GFP_KERNEL);
	if (ctx->req == NULL) {
		SYSCON_ERR("ahash_request_alloc is NULL\n");
		return -ENOMEM;
	}

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
static void syscon_sha_cra_exit(struct crypto_tfm *tfm)
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
static void syscon_hmac_sha_cra_exit(struct crypto_tfm *tfm)
{
	struct crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	struct syscon_hmac_ctx *ctx = crypto_ahash_ctx(ahash);

	SYSCON_FUNC_START("\n");
	ahash_request_free(ctx->req);
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
static void syscon_sha_handler0(struct work_struct *work)
{
	int ierr;

	SYSCON_FUNC_START("\n");
	do {
		ierr = syscon_sha_handle_req(0);
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
static void syscon_sha_handler1(struct work_struct *work)
{
	int ierr;

	SYSCON_FUNC_START("\n");
	do {
		ierr = syscon_sha_handle_req(1);
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
static void syscon_sha_handler2(struct work_struct *work)
{
	int ierr;

	SYSCON_FUNC_START("\n");
	do {
		ierr = syscon_sha_handle_req(2);
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
static void syscon_sha_handler3(struct work_struct *work)
{
	int ierr;

	SYSCON_FUNC_START("\n");
	do {
		ierr = syscon_sha_handle_req(3);
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
int syscon_crypto_sha_init(struct syscon_dev *pdev)
{
	int i, ierr = 0;

	SYSCON_FUNC_START("\n");

	for (i = 0; i < ARRAY_SIZE(sha_algs); i++) {
		INIT_LIST_HEAD(&sha_algs[i].halg.base.cra_list);
		ierr = crypto_register_ahash(&sha_algs[i]);
		if (ierr != 0)
			goto fail_crypto_register_sha_alg;
	}
	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return SYSCON_OK;

fail_crypto_register_sha_alg:
	for (--i; i >= 0; i--)
		crypto_unregister_ahash(&sha_algs[i]);


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
void syscon_crypto_sha_exit(struct syscon_dev *pdev)
{
	int i;

	SYSCON_FUNC_START("\n");

	for (i = 0; i < ARRAY_SIZE(sha_algs); i++)
		crypto_unregister_ahash(&sha_algs[i]);
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++)
		cancel_work_sync(syscon_sha_work[i]);
	SYSCON_FUNC_END("ret\n");
}


#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

