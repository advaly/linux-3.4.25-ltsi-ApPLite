/*
 * linux/drivers/staging/applite/syscon/applite_syscon_crypto_rng.c
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

#include <linux/hw_random.h>

#if IS_ENABLED(CONFIG_HW_RANDOM_APPLITE)


/*===================================
Static Variables and Functions prototypes
===================================*/

static int syscon_rng_data_read(struct hwrng *rng, u32 *data);
static int syscon_rng_read(struct hwrng *rng, void *data,
						size_t max, bool wait);

static struct hwrng syscon_rng_ops = {
	.name = "applite",
	.data_read = syscon_rng_data_read,
	.read = syscon_rng_read,
};


/*===================================
Global Variables and Functions prototypes
===================================*/


/*===================================
Macros
===================================*/

#define RANDOM_DATA_OFFSET (SCOMM_RSP_RNG_DATA_OFFS - SCOMM_RSP_RESPONSE_OFFS)

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
static int syscon_rng_data_read(struct hwrng *rng, u32 *data)
{
	int ierr = 0;
	struct syscon_cmd cmd;

	SYSCON_FUNC_START("\n");

	memset(&cmd, 0, sizeof(struct syscon_cmd));
	*((__u32 *)(cmd.cmd_req)) = SCOMM_RNG_CMDID;
	ierr = syscon_exec_s_slot(&s_dev, &cmd);

	if (ierr != SYSCON_OK)
		goto fail_exit;

	*data = *(u32 *)&(cmd.cmd_rsp[RANDOM_DATA_OFFSET]);
	SYSCON_FUNC_END("ret(%d)\n", 4);
	return 4;

fail_exit:

	SYSCON_FUNC_END("ret(%d)\n", 0);
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
static int syscon_rng_read(struct hwrng *rng, void *data, size_t max, bool wait)
{
	int ierr = 0;
	struct syscon_cmd cmd;
	size_t size = min_t(size_t, SYSCON_RNG_SIZE, max);

	SYSCON_FUNC_START("(size:%d,wait:%d)\n", max, wait);

	memset(&cmd, 0, sizeof(struct syscon_cmd));
	*((__u32 *)(cmd.cmd_req)) = SCOMM_RNG_CMDID;

	ierr = syscon_exec_s_slot(&s_dev, &cmd);

	if (ierr != SYSCON_OK)
		goto fail_exit;

	memcpy(data, &(cmd.cmd_rsp[RANDOM_DATA_OFFSET]), size);
	syscon_dump_buf(data, size);
	SYSCON_FUNC_END("ret(%d)\n", size);
	return size;

fail_exit:

	SYSCON_FUNC_END("ret(%d)\n", 0);
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
int syscon_rng_init(struct syscon_dev *pdev)
{
	int ierr = SYSCON_OK;

	SYSCON_FUNC_START("\n");

	ierr = hwrng_register(&syscon_rng_ops);
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
void syscon_rng_exit(struct syscon_dev *pdev)
{
	SYSCON_FUNC_START("\n");

	hwrng_unregister(&syscon_rng_ops);
	SYSCON_FUNC_END("ret\n");
}
#endif	/* CONFIG_HW_RANDOM_APPLITE */


