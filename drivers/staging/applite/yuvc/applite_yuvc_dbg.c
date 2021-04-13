/*
 * linux/drivers/staging/applite/applite_yuvc_dbg.c
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
#include <linux/uaccess.h>
#include <linux/dma-buf.h>

#include <linux/applite/applite_yuvc.h>
#include "applite_yuvc_internal.h"
#include "applite_yuvc_regs.h"
#include "applite_yuvc_dbg.h"


/*===================================
Static Variables and Functions prototypes
===================================*/

/*===================================
Global Variables and Functions prototypes
===================================*/
#if 0
__u32 ul_logflags =
	(YUVC_LOG_FUNCTION | YUVC_LOG_PERFORMANCE | YUVC_LOG_INFORMATION);
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
void yuvc_dump_spinlock_t(spinlock_t *lock, char *name)
{
	if (lock == NULL) {
		YUVC_ERR("invalid parameter lock(%p)\n", lock);
		return;
	}

#if 0
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
void yuvc_dump_yuvc_dev(struct yuvc_dev *pdev)
{
	if (pdev == NULL) {
		YUVC_ERR("invalid parameter pdev(%p)\n", pdev);
		return;
	}

	pr_info("=== struct yuvc_dev =====: [%p] =====\n", pdev);
	pr_info("  device              : %p\n", pdev->device);
#if 0
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
	pr_info("  yuvcbase            : %p\n", pdev->yuvcbase);
/*	pr_info("  yvdmacbase          : %p\n", pdev->yvdmacbase); */
	pr_info("  pmubase             : %p\n", pdev->pmubase);
#if 0
	pr_info("  interrupt           : %d/%d/%d/%d/%d\n",
			pdev->ul_num_frame_end_irq,
			pdev->ul_num_start_err_irq,
			pdev->ul_num_reg_err_irq,
			pdev->ul_num_disp_err_irq,
			pdev->ul_num_merge_err_irq);
#endif
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
void yuvc_dump_conv_adr(struct yuvc_conv_adr *adr)
{
	if (adr == NULL) {
		YUVC_ERR("invalid parameter adr(%p)\n", adr);
		return;
	}

	pr_info("struct yuvc_conv_adr : [%p] =====\n", adr);
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
char *yuvc_format_to_str(__u32 format)
{
	static char *input_format[] = {
		"YUY2(422)", "YUY2(422)", "NV12(420)", "I420(420)" };
	static char buf[128];

	if (YUVC_VALID_IN_FORMAT(format)) {
		sprintf(buf, "%s", input_format[format]);
		YUVC_INFO("%s:format is %d\n", __func__, format);
	} else {
		sprintf(buf, "invalid format[%08x]", format);
		YUVC_INFO("%s:format is failed format=%d\n", __func__, format);
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

	YUVC_FUNC_START("%08x, %08x, %d, %d\n", out_adr, exp_adr, h, v);
	for (x = 0; x < (h * 2); x += 8) {
		adr = out_adr + (x / 8) * 0x80000;
		for (y = 0; (y < (v / 2)) && (ret == 0); y++) {
			/* vtile address convert */
			t_adr = vtile_convert(adr, 2);
			YUVC_TEST("t_adr[%08x <- %08x]\n", t_adr, adr);
			/* get data from user space */
			if (get_user(chk_data, exp)) {
				YUVC_ERR("get_user() failed\n");
				return YUVC_NG;
			}
			/* data compare */
			if (*((__u32 *)phys_to_virt(t_adr)) != chk_data) {
				YUVC_ERR("data unmatch [%d, %d]dat:" \
					"%08x[%p]/%08x, exp:%p/%08x\n",
					x, y, t_adr, phys_to_virt(t_adr),
					*((__u32 *)phys_to_virt(t_adr)),
					exp, chk_data);
				return YUVC_NG;
			}
			matched += 8;
			exp += 2;
			adr += 8;
		}
	}
	YUVC_FUNC_END("matched : %d\n", matched);
	return YUVC_OK;
}

void yuvc_dump_all_regs(struct yuvc_dev *pdev)
{
	__u32	regs;

	YUVC_INFO("all regs dump()\n");

	YUVC_READ_2(pdev,	START, regs);
	YUVC_READ_2(pdev,	RESET, regs);
	YUVC_READ_2(pdev,	MODE, regs);
	YUVC_READ_2(pdev,	SIZE, regs);
	YUVC_READ_2(pdev,	OFFSET_Y, regs);
	YUVC_READ_2(pdev,	OFFSET_UV, regs);
	YUVC_READ_2(pdev,	YCOEF_RG, regs);
	YUVC_READ_2(pdev,	YCOEF_B, regs);
	YUVC_READ_2(pdev,	UCOEF_RG, regs);
	YUVC_READ_2(pdev,	UCOEF_B, regs);
	YUVC_READ_2(pdev,	VCOEF_RG, regs);
	YUVC_READ_2(pdev,	VCOEF_B, regs);
	YUVC_READ_2(pdev,	OFFSET_RG, regs);
	YUVC_READ_2(pdev,	OFFSET_B, regs);
	YUVC_READ_2(pdev,	STADR, regs);
	YUVC_READ_2(pdev,	ENDADR, regs);
	YUVC_READ_2(pdev,	CFG, regs);
	YUVC_READ_2(pdev,	INT_MASK, regs);
	YUVC_READ_2(pdev,	W_ENABLE, regs);
	YUVC_READ_2(pdev,	W00_STADR, regs);
	YUVC_READ_2(pdev,	W00_ENDADR, regs);
	YUVC_READ_2(pdev,	W00_HEIGHT, regs);
	YUVC_READ_2(pdev,	W00_PITCH, regs);
	YUVC_READ_2(pdev,	W00_CFG0, regs);
	YUVC_READ_2(pdev,	W00_SRAM_BASE, regs);
	YUVC_READ_2(pdev,	W00_SRAM_SIZE, regs);
	YUVC_READ_2(pdev,	W01_STADR, regs);
	YUVC_READ_2(pdev,	W01_ENDADR, regs);
	YUVC_READ_2(pdev,	W01_HEIGHT, regs);
	YUVC_READ_2(pdev,	W01_PITCH, regs);
	YUVC_READ_2(pdev,	W01_CFG0, regs);
	YUVC_READ_2(pdev,	W01_CFG1, regs);
	YUVC_READ_2(pdev,	W01_SRAM_BASE, regs);
	YUVC_READ_2(pdev,	W01_SRAM_SIZE, regs);
	YUVC_READ_2(pdev,	STATUS, regs);
	YUVC_READ_2(pdev,	INT, regs);
	YUVC_READ_2(pdev,	W_SRAM, regs);
	YUVC_READ_2(pdev,	W_STOP, regs);
	YUVC_READ_2(pdev,	W_RUN, regs);

	return;
}

#if defined(_TEST_BUILD_)
void yuvc_dump_buff(struct yuvc_conv_adr *a_adr, int a_idx, size_t a_offset)
{
	__u8 *p, *p2;
	int i;

	p2 = dma_buf_kmap(a_adr[a_idx].db, 0);
	p = p2 + a_offset;
	YUVC_TEST("plane No.%d, addr:%p\n", a_idx, p);

	for (i = 0; i < (800*4*2); i += 16) {
		YUVC_TEST("%08x %02x %02x %02x %02x %02x %02x " \
			"%02x %02x %02x %02x %02x %02x %02x %02x " \
			"%02x %02x\n",
			i, p[i + 0], p[i + 1], p[i + 2], p[i + 3],
			p[i + 4], p[i + 5], p[i + 6], p[i + 7],
			p[i + 8], p[i + 9], p[i + 10], p[i + 11],
			p[i + 12], p[i + 13], p[i + 14], p[i + 15]);
	}
	dma_buf_kunmap(a_adr[a_idx].db, 0, p2);
}
#endif  /* _TEST_BUILD_ */
