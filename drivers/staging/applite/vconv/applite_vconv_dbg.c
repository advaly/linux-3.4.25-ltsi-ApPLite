/*
 * linux/drivers/staging/applite/applite_vconv_dbg.c
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
#include <linux/uaccess.h>

#include <linux/applite/applite_vconv.h>
#include "applite_vconv_internal.h"
#include "applite_vconv_regs.h"
#include "applite_vconv_dbg.h"


/*===================================
Static Variables and Functions prototypes
===================================*/


/*===================================
Global Variables and Functions prototypes
===================================*/
#if 0
__u32 ul_logflags =
	(VCONV_LOG_FUNCTION | VCONV_LOG_PERFORMANCE | VCONV_LOG_INFORMATION);
#else
__u32 ul_logflags;
#endif


/*===================================
Macros
===================================*/

/*===================================
Function Definitions
===================================*/

/*===================================
Module source
===================================*/

#if defined(_TEST_BUILD_)

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
void vconv_dump_spinlock_t(spinlock_t *lock, char *name)
{
	if (lock == NULL) {
		VCONV_ERR("invalid parameter lock(%p)\n", lock);
		return;
	}

#if defined(CONFIG_SMP)
	pr_info("=== spinlock_t (%s:%p) : [%d]=====\n", name, lock,
			lock->rlock.raw_lock.lock);
#endif
}

#endif	/* _TEST_BUILD_ */

/** <name>
   *  Function:
   *  Purpose:
   *  Inputs:
   *  Outputs:
   *  Return Values:
   *  Limitations:
   * Side Effects:
**/
void vconv_dump_vconv_dev(struct vconv_dev *pdev)
{
	if (pdev == NULL) {
		VCONV_ERR("invalid parameter pdev(%p)\n", pdev);
		return;
	}

	pr_info("=== struct vconv_dev =====: [%p] =====\n", pdev);
	pr_info("  device              : %p\n", pdev->device);
#if defined(CONFIG_SMP)
	pr_info("  lock_dev            : %d\n",
			pdev->lock_dev.rlock.raw_lock.lock);
	pr_info("  lock_reg            : %d\n",
			pdev->lock_reg.rlock.raw_lock.lock);
	pr_info("  mutex_run           : %d / %d\n",
			atomic_read(&(pdev->mutex_run.count)),
			pdev->mutex_run.wait_lock.rlock.raw_lock.lock);
#endif
	pr_info("  ul_open_count       : %d\n",
			atomic_read(&(pdev->ul_open_count)));
	pr_info("  b_run               : %d\n", pdev->b_run);
	pr_info("  vconvbase           : %p\n", pdev->vconvbase);
	pr_info("  pmubase             : %p\n", pdev->pmubase);
	pr_info("  interrupt           : %d/%d/%d/%d/%d\n",
			pdev->ul_num_frame_end_irq,
			pdev->ul_num_start_err_irq,
			pdev->ul_num_reg_err_irq,
			pdev->ul_num_disp_err_irq,
			pdev->ul_num_merge_err_irq);
	pr_info("==================================\n");
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
void vconv_dump_conv_adr(struct vconv_conv_adr *adr)
{
	if (adr == NULL) {
		VCONV_ERR("invalid parameter adr(%p)\n", adr);
		return;
	}

	pr_info("struct vconv_conv_adr : [%p] =====\n", adr);
	pr_info("  enable              : %d\n", adr->enable);
	pr_info("  dma_buf             : %p\n", adr->db);
	pr_info("  dma_buf_attachment  : %p\n", adr->dba);
	pr_info("  sg_table            : %p\n", adr->sg);
	pr_info("  addr                : %08x\n", adr->addr);
	pr_info("==================================\n");
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
char *vconv_format_to_str(__u32 format)
{
	static char *color_list[] = {
		"RGB", "YCbCr4:4:4", "YCbCr4:2:2", "YCbCr4:2:0" };
	static char *scan_list[] = {
		"raster", "tile" };
	static char *plane_list[] = {
		"pack", "part", "full" };
	static char buf[128];

	if (VCONV_VALID_FORMAT(format)) {
		sprintf(buf, "%s/%s/%s:%d[%08x]",
			color_list[VCONV_GET_COLOR(format)],
			plane_list[VCONV_GET_PLANE(format)-1],
			scan_list[VCONV_GET_SCAN(format)],
			VCONV_GET_FORMAT_ID(format),
			format);
	} else {
		sprintf(buf, "invalid format[%08x]", format);
	}
	return buf;
}

static __u32 bs(__u32 adr, __u8 msb, __u8 lsb)
{
	int i;
	__u32 mask = 0;

	for (i = lsb; i <= msb; i++)
		mask = (mask << 1) + 1;

	return (adr >> lsb) & mask;
}

static __u32 vtile_convert(__u32 adr, int tps)
{
	__u32 t_adr;
	switch (tps) {
	case 2:
		t_adr = (bs(adr, 31, 29) << 29) |
			(bs(adr, 18,  9) << 19) |
			(bs(adr, 28, 25) << 15) |
			(bs(adr, 24, 24) << 14) |
			((bs(adr, 9,  9) ^ bs(adr, 23, 23)) << 13) |
			(bs(adr, 22, 22) << 12) |
			(bs(adr, 21, 19) <<  9) |
			bs(adr, 8, 0);
		break;
	default:
		t_adr = adr;
	}
	return t_adr;
}

/* out_adr : vtile address(physical address)  */
/* exp_adr : expect data address(user space)  */
/* h, v    : check size                       */
int check_veu_data(__u32 out_adr, __u32 exp_adr, __u16 h, __u16 v)
{
	int x, y, ret = 0;
	__u32 adr, t_adr;
	__u32 matched = 0;
	__u32 __user *exp = (__u32 __user *)exp_adr;
	__u32 chk_data;

	VCONV_FUNC_START("%08x, %08x, %d, %d\n", out_adr, exp_adr, h, v);
	for (x = 0; x < (h * 2); x += 8) {
		adr = out_adr + (x / 8) * 0x80000;
		for (y = 0; (y < (v / 2)) && (ret == 0); y++) {
			/* vtile address convert */
			t_adr = vtile_convert(adr, 2);
			VCONV_TEST("t_adr[%08x <- %08x]\n", t_adr, adr);
			/* get data from user space */
			if (get_user(chk_data, exp)) {
				VCONV_ERR("get_user() failed\n");
				return VCONV_NG;
			}
			/* data compare */
			if (*((__u32 *)phys_to_virt(t_adr)) != chk_data) {
				VCONV_ERR("data unmatch [%d, %d]dat:" \
					"%08x[%p]/%08x, exp:%p/%08x\n",
					x, y, t_adr, phys_to_virt(t_adr),
					*((__u32 *)phys_to_virt(t_adr)),
					exp, chk_data);
				return VCONV_NG;
			}
			matched += 8;
			exp += 2;
			adr += 8;
		}
	}
	VCONV_FUNC_END("matched : %d\n", matched);
	return VCONV_OK;
}

