/*
 * linux/drivers/staging/applite/syscon/applite_syscon_dbg.h
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

#if !defined(__SYSCON_DRIVER_DBG_H__)
#define __SYSCON_DRIVER_DBG_H__

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

#define SYSCON_LOG_NONE			(0x00000000)
#define SYSCON_LOG_FUNCTION		(0x00000001)
#define SYSCON_LOG_PERFORMANCE		(0x00000002)
#define SYSCON_LOG_INFORMATION		(0x00000004)
#define SYSCON_LOG_DEBUG		(0x00000008)

#define SYSCON_LOG_HDR			"[%s] %s "


/*===================================
Exported Variables
===================================*/
extern __u32 ul_logflags;


/*===================================
Macros
===================================*/

#define SYSCON_LOG(flg, fmt, ...)			\
do {							\
	if (ul_logflags & flg)				\
		pr_info(fmt, ##__VA_ARGS__);            \
} while (0);

#define SYSCON_FUNC_START(fmt, ...)			\
		SYSCON_LOG(SYSCON_LOG_FUNCTION,		\
			"[%s] %s start : " fmt,		\
			DEVICE_NAME, __func__, ##__VA_ARGS__)
#define SYSCON_FUNC_END(fmt, ...)			\
		SYSCON_LOG(SYSCON_LOG_FUNCTION,		\
			"[%s] %s end : " fmt,		\
			DEVICE_NAME, __func__, ##__VA_ARGS__)
#define SYSCON_PM_START(fmt)				\
		SYSCON_LOG(SYSCON_LOG_PERFORMANCE,	\
			"[%s ms] %s start [%u]: " fmt,	\
			DEVICE_NAME, __func__, jiffies_to_msecs(jiffies))
#define SYSCON_PM_END(fmt)				\
		SYSCON_LOG(SYSCON_LOG_PERFORMANCE,	\
			"[%s ms] %s end [%u]: " fmt,	\
			DEVICE_NAME, __func__, jiffies_to_msecs(jiffies))
#define SYSCON_INFO(fmt, ...)				\
		SYSCON_LOG(SYSCON_LOG_INFORMATION,	\
			"[%s] %s : " fmt, DEVICE_NAME, __func__, ##__VA_ARGS__)
#define SYSCON_DBG(fmt, ...)				\
		SYSCON_LOG(SYSCON_LOG_DEBUG,		\
			"[%s] %s : " fmt, DEVICE_NAME, __func__, ##__VA_ARGS__)

#define SYSCON_ERR(fmt, ...)				\
		pr_err("[%s] %s : --ERROR-- "fmt, DEVICE_NAME, \
			__func__, ##__VA_ARGS__)

#define SYSCON_FORCE_LOG(fmt, ...)			\
		pr_info("[%s] : "fmt, DEVICE_NAME, ##__VA_ARGS__)



/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/
void syscon_dump_buf(__u8 *buf, __u32 size);



#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __SYSCON_DRIVER_DBG_H__ */

