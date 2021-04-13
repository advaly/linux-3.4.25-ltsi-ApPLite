/*
 * linux/drivers/staging/applite/applite_vconv_dbg.h
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

#if !defined(__VCONV_DRIVER_DBG_H__)
#define __VCONV_DRIVER_DBG_H__

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

#define VCONV_LOG_NONE			(0x00000000)
#define VCONV_LOG_FUNCTION		(0x00000001)
#define VCONV_LOG_PERFORMANCE		(0x00000002)
#define VCONV_LOG_INFORMATION		(0x00000004)

#define VCONV_LOG_HDR			"[%s] %s "

#define VCONV_VERIFY_BUF_SIZE		(1024)

/*===================================
Exported Variables
===================================*/
extern __u32 ul_logflags;


/*===================================
Macros
===================================*/

#define VCONV_DBG_LOG(flg, fmt, ...)			\
do {							\
	if (ul_logflags & flg)				\
		pr_info(fmt, ##__VA_ARGS__);            \
} while (0);

#define VCONV_FUNC_START(fmt, ...)			\
		VCONV_DBG_LOG(VCONV_LOG_FUNCTION,       \
			"[%s] %s start : " fmt,		\
			DEVICE_NAME, __func__, ##__VA_ARGS__)
#define VCONV_FUNC_END(fmt, ...)			\
		VCONV_DBG_LOG(VCONV_LOG_FUNCTION,	\
			"[%s] %s end : " fmt,		\
			DEVICE_NAME, __func__, ##__VA_ARGS__)
#define VCONV_PM_START(fmt)				\
		VCONV_DBG_LOG(VCONV_LOG_PERFORMANCE,	\
			"[%s ms] %s start [%u]: " fmt,	\
			DEVICE_NAME, __func__, jiffies_to_msecs(jiffies))
#define VCONV_PM_END(fmt)				\
		VCONV_DBG_LOG(VCONV_LOG_PERFORMANCE,	\
			"[%s ms] %s end [%u]: " fmt,	\
			DEVICE_NAME, __func__, jiffies_to_msecs(jiffies))
#define VCONV_INFO(fmt, ...)				\
		VCONV_DBG_LOG(VCONV_LOG_INFORMATION,	\
			"[%s] %s : " fmt, DEVICE_NAME, __func__, ##__VA_ARGS__)

#define VCONV_ERR(fmt, ...)				\
		pr_err("[%s] %s : --ERROR-- "fmt, DEVICE_NAME, \
			__func__, ##__VA_ARGS__)


#if defined(_TEST_BUILD_)
#define DUMP_SPINLOCK(p, n)		vconv_dump_spinlock_t(p, n)
#define DUMP_VCONV_DEV(p)		vconv_dump_vconv_dev(p)
#define DUMP_VCONV_CONV_ADR(p)		vconv_dump_conv_adr(p)
#define VCONV_TEST			VCONV_INFO
#else
#define DUMP_SPINLOCK(p, n)
#define DUMP_VCONV_DEV(p)
#define DUMP_VCONV_CONV_ADR(p)
#define VCONV_TEST(fmt, ...)
#endif	/* _TEST_BUILD_ */


/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

#if defined(_TEST_BUILD_)
void vconv_dump_spinlock_t(spinlock_t *lock, char *name);
#endif	/* _TEST_BUILD_ */

void vconv_dump_vconv_dev(struct vconv_dev *pdev);
void vconv_dump_conv_adr(struct vconv_conv_adr *adr);
char *vconv_format_to_str(__u32 format);
int check_veu_data(__u32 out_adr, __u32 exp_adr, __u16 h, __u16 v);


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __VCONV_DRIVER_DBG_H__ */

