/*
 * linux/drivers/staging/applite/syscon/applite_syscon_crypto.c
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



/*===================================
Static Variables and Functions prototypes
===================================*/

struct workqueue_struct	*syscon_wq[SYSCON_SLOTC_Q_MAX];


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
int syscon_crypto_init(struct syscon_dev *pdev)
{
	int ierr = 0;
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	int i;
	__u32 val;
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	SYSCON_FUNC_START("\n");

	if (pdev->b_regist != SYSCON_REG_CRYPTO_INIT)
		return SYSCON_OK;

#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)

	/* check crypto api support */
	val = syscon_get_sysconfig1(pdev);
	if (!(val & SCOMM_SUPPORT_CRYPTO)) {
		pdev->b_regist = SYSCON_REG_CRYPTO_NOT;
		return SYSCON_NG;
	}

	/* allocate work area : used for aes iv and sha dst */
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++) {
		pdev->hmac_wk_virt[i] = dma_alloc_coherent(pdev->device,
					SYSCON_WK_BUF_SIZE,
					&(pdev->hmac_wk_phys[i]),
					(GFP_KERNEL | GFP_DMA));
		if (pdev->hmac_wk_virt[i] == NULL) {
			SYSCON_ERR("dma_alloc_coherent(%d) failed\n",
							SYSCON_WK_BUF_SIZE);
			for (i--; i >= 0; i--)
				dma_free_coherent(pdev->device,
						SYSCON_WK_BUF_SIZE,
						pdev->wk_virt[i],
						pdev->wk_phys[i]);

			pdev->b_regist = SYSCON_REG_CRYPTO_NOT;
			return SYSCON_NG;
		}
		pdev->wk_virt[i] = pdev->hmac_wk_virt[i] +
						SYSCON_HMAC_WORK_BUF_SIZE;
		pdev->wk_phys[i] = pdev->hmac_wk_phys[i] +
						SYSCON_HMAC_WORK_BUF_SIZE;
		SYSCON_INFO("SYSCON area[%08x] (%p/%08x) + (%p/%08x)\n",
				SYSCON_WK_BUF_SIZE,
				pdev->hmac_wk_virt[i], pdev->hmac_wk_phys[i],
				pdev->wk_virt[i], pdev->wk_phys[i]);
	}

	spin_lock_init(&(s_dev.lock));
	sema_init(&(s_dev.q_sem), SYSCON_SLOTC_Q_MAX);
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++) {
		crypto_init_queue(&(s_dev.queue[i]), SYSCON_QUEUE_LEN);
		syscon_wq[i] = alloc_workqueue("syscon_wq",
						WQ_HIGHPRI | WQ_UNBOUND, 1);
		if (syscon_wq[i] == NULL) {
			for (i--; i >= 0; i--)
				destroy_workqueue(syscon_wq[i]);
			ierr = -EFAULT;
			SYSCON_ERR("alloc_workqueue() failed\n");
			goto fail_alloc_workqueue;
		}
	}

	ierr = syscon_crypto_aes_init(pdev);
	if (ierr != SYSCON_OK)
		goto fail_crypto_register_aes_alg;

	ierr = syscon_crypto_sha_init(pdev);
	if (ierr != SYSCON_OK)
		goto fail_crypto_register_sha_alg;

	pdev->b_regist = SYSCON_REG_CRYPTO_DONE;

	SYSCON_FUNC_END("ret(%d)\n", ierr);
	return SYSCON_OK;

fail_crypto_register_sha_alg:
	syscon_crypto_aes_exit(pdev);
fail_crypto_register_aes_alg:
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++) {
		destroy_workqueue(syscon_wq[i]);
		syscon_wq[i] = NULL;
	}
fail_alloc_workqueue:
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++)
		dma_free_coherent(pdev->device, SYSCON_WK_BUF_SIZE,
				pdev->hmac_wk_virt[i], pdev->hmac_wk_phys[i]);

#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	pdev->b_regist = SYSCON_REG_CRYPTO_NOT;

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
void syscon_crypto_exit(struct syscon_dev *pdev)
{
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	int i;
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

	SYSCON_FUNC_START("\n");

#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	if (pdev->b_regist != SYSCON_REG_CRYPTO_DONE)
		return;

	syscon_crypto_sha_exit(pdev);
	syscon_crypto_aes_exit(pdev);
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++)
		destroy_workqueue(syscon_wq[i]);
	for (i = 0; i < SYSCON_SLOTC_Q_MAX; i++)
		dma_free_coherent(pdev->device, SYSCON_WK_BUF_SIZE,
				pdev->hmac_wk_virt[i], pdev->hmac_wk_phys[i]);
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
	SYSCON_FUNC_END("ret\n");
}





