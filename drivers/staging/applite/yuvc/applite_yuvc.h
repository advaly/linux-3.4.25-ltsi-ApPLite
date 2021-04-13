/*
 * linux/drivers/staging/applite/applite_yuvc.h
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

#if !defined(__APPLITE_YUVC_H__)
#define __APPLITE_YUVC_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*===================================
 include Files
===================================*/
#include <linux/ioctl.h>


/*===================================
 Types and structures   defined
===================================*/

enum yuvc_buffer_mode {
	YUVC_USE_FD = 1,
	YUVC_USE_ADDRESS
};

enum yuvc_input_format {
	YUVC_YUY2 = 0,			/* 422 */
	YUVC_YUY2_1,			/* 422 */
	YUVC_NV12,				/* 420 */
	YUVC_I420				/* 420 */
};

enum yuvc_output_format {
	YUVC_ARGB8888 = 0,
	YUVC_RGBA8888,
	YUVC_RGB888,
	YUVC_RGB565
};

/* index of in_offset[], in_buffer[] */
enum yuvc_input_yuv {
	YUVC_INPUT_Y = 0,
	YUVC_INPUT_U,
	YUVC_INPUT_V,
	YUVC_INPUT_YUV_MAX
};

/* index of ycoef[]/ucoef[]/vcoef[] */
enum yuvc_input_coef {
	YUVC_INPUT_COEF_R = 0,
	YUVC_INPUT_COEF_G,
	YUVC_INPUT_COEF_B,
	YUVC_INPUT_COEF_MAX
};

/* index of out_offset[] */
enum yuvc_output_rgb {
	YUVC_OUTPUT_R = 0,
	YUVC_OUTPUT_G,
	YUVC_OUTPUT_B,
	YUVC_OUTPUT_RGB_MAX
};


/* structures */
struct yuvc_rect {
	__u16			h;
	__u16			v;
};


struct yuvc_mtx {
	__s16			in_offset[YUVC_INPUT_YUV_MAX];
	__s16			ycoef[YUVC_INPUT_COEF_MAX];
	__s16			ucoef[YUVC_INPUT_COEF_MAX];
	__s16			vcoef[YUVC_INPUT_COEF_MAX];
	__s16			out_offset[YUVC_OUTPUT_RGB_MAX];
};

struct yuvc_img_param {
	/* colorformat, planes, scan type */
	__u8			in_format;
	__u8			out_format;
	/* hsize, vsize */
	struct yuvc_rect	size;
	/* for ARGB(888/RBA8888) */
	__u8			out_alpha;

};

struct yuvc_buffer {
	enum yuvc_buffer_mode	mode;
	int				fd;
	__u8			*phys_addr;
	size_t			offset;
	__u16			pitch;
};

#define YUVC_INPUT_BUF_NUM		(3)
#define YUVC_OUTPUT_BUF_NUM		(1)
struct yuvc_param {
	/* input buffer parameters */
	struct yuvc_buffer	in_buffer[YUVC_INPUT_BUF_NUM];
	/* output buffer parameters */
	struct yuvc_buffer	out_buffer;
	/* input image parameters */
	struct yuvc_img_param	img;
	/* color conversion parameters */
	struct yuvc_mtx		conv;
};

struct yuvc_verify {
	struct yuvc_buffer	buf;
	/* expect data buffer */
	__u8			*exp_buf;
	/* expect data size */
	size_t			exp_size;
	struct yuvc_rect	exp_rect;
};

/* ioctl command code */
#define	IOC_YUVC_START		_IOWR('y', 11, struct yuvc_param)
#define IOC_YUVC_CANCEL		_IO('y', 12)

/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

#ifdef __KERNEL__
long yuvc_start(struct yuvc_param *param);
long yuvc_cancel(void);
#endif	/* __KERNEL__ */


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __APPLITE_YUVC_H__ */

