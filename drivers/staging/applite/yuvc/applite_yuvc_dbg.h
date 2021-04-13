/*
 * linux/drivers/staging/applite/applite_yuvc_dbg.h
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

#if !defined(__YUVC_DRIVER_DBG_H__)
#define __YUVC_DRIVER_DBG_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*===================================
include Files
===================================*/
#include <linux/kernel.h>

/*===================================
Types and structures   defined
===================================*/

#define YUVC_LOG_NONE			(0x00000000)
#define YUVC_LOG_FUNCTION		(0x00000001)
#define YUVC_LOG_PERFORMANCE	(0x00000002)
#define YUVC_LOG_INFORMATION	(0x00000004)

#define YUVC_LOG_HDR			"[%s] %s "

#define YUVC_VERIFY_BUF_SIZE	(1024)

/*===================================
Exported Variables
===================================*/
extern __u32 ul_logflags;

/*===================================
Macros
===================================*/

#define YUVC_DBG_LOG(flg, fmt, ...)			\
do {							\
	if (ul_logflags & flg)				\
		pr_info(fmt, ##__VA_ARGS__);            \
} while (0);

#define YUVC_FUNC_START(fmt, ...)			\
		YUVC_DBG_LOG(YUVC_LOG_FUNCTION,       \
			"[%s] %s start : " fmt,		\
			DEVICE_NAME, __func__, ##__VA_ARGS__)
#define YUVC_FUNC_END(fmt, ...)			\
		YUVC_DBG_LOG(YUVC_LOG_FUNCTION,	\
			"[%s] %s end : " fmt,		\
			DEVICE_NAME, __func__, ##__VA_ARGS__)
#define YUVC_PM_START(fmt)				\
		YUVC_DBG_LOG(YUVC_LOG_PERFORMANCE,	\
			"[%s ms] %s start [%u]: " fmt,	\
			DEVICE_NAME, __func__, jiffies_to_msecs(jiffies))
#define YUVC_PM_END(fmt)				\
		YUVC_DBG_LOG(YUVC_LOG_PERFORMANCE,	\
			"[%s ms] %s end [%u]: " fmt,	\
			DEVICE_NAME, __func__, jiffies_to_msecs(jiffies))
#define YUVC_INFO(fmt, ...)				\
		YUVC_DBG_LOG(YUVC_LOG_INFORMATION,	\
			"[%s] %s : " fmt, DEVICE_NAME, __func__, ##__VA_ARGS__)

#define YUVC_ERR(fmt, ...)				\
		pr_err("[%s] %s : --ERROR-- "fmt, DEVICE_NAME, \
			__func__, ##__VA_ARGS__)


#if defined(_TEST_BUILD_)
#define DUMP_SPINLOCK(p, n)				yuvc_dump_spinlock_t(p, n)
#define DUMP_YUVC_DEV(p)				yuvc_dump_yuvc_dev(p)
#define DUMP_YUVC_CONV_ADR(p)			yuvc_dump_conv_adr(p)
#define DUMP_YUVC_REGS(p)				yuvc_dump_all_regs(p)
#define DUMP_YUVC_BUFF(p, i, o)			yuvc_dump_buff(p, i, o)
#define YUVC_TEST			YUVC_INFO
#else
#define DUMP_SPINLOCK(p, n)
#define DUMP_YUVC_DEV(p)
#define DUMP_YUVC_CONV_ADR(p)
#define DUMP_YUVC_REGS(p)
#define YUVC_TEST(fmt, ...)
#endif	/* _TEST_BUILD_ */


/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

#if defined(_TEST_BUILD_)
void yuvc_dump_spinlock_t(spinlock_t *lock, char *name);
#endif	/* _TEST_BUILD_ */

void yuvc_dump_yuvc_dev(struct yuvc_dev *pdev);
void yuvc_dump_conv_adr(struct yuvc_conv_adr *adr);
char *yuvc_format_to_str(__u32 format);
void yuvc_dump_all_regs(struct yuvc_dev *pdev);
void yuvc_dump_buff(struct yuvc_conv_adr *a_adr, int a_idx, size_t a_offset);
int check_veu_data(__u32 out_adr, __u32 exp_adr, __u16 h, __u16 v);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __YUVC_DRIVER_DBG_H__ */

