/*
 * linux/drivers/staging/applite/applite_vconv.h
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

#if !defined(__APPLITE_VCONV_H__)
#define __APPLITE_VCONV_H__

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

/* types */
enum vconv_outstand_cmd {
	CMD1 = 1,
	CMD2 = 2,
	CMD4 = 4,
	CMD8 = 8
};

enum vconv_alpha_mode {
	VCONV_ALPHA_USE_REG = 0,
	VCONV_ALPHA_USE_IMG
};


enum vconv_colorformat {
	VCONV_RGB = 0,
	VCONV_YCBCR444,
	VCONV_YCBCR422,
	VCONV_YCBCR420,
	VCONV_COLOR_MAX
};

enum vconv_plane {
	VCONV_PLANE_A = 0,
	VCONV_PLANE_B,
	VCONV_PLANE_C,
	VCONV_PLANE_MAX
};


enum vconv_scan_type {
	VCONV_RASTER = 0,
	VCONV_TILE,
	VCONV_SCAN_MAX
};

#define MK_FORMAT(clr, pln, scn, id)	\
		((__u32)VCONV_##clr | ((__u32)pln << 4) | \
		((__u32)VCONV_##scn << 8) | ((__u32)id << 16))
#define VCONV_GET_COLOR(fmt)		\
		(((__u32)fmt & 0x00000003) >>  0)
#define VCONV_GET_PLANE(fmt)		\
		(((__u32)fmt & 0x00000030) >>  4)
#define VCONV_GET_SCAN(fmt)		\
		(((__u32)fmt & 0x00000100) >>  8)
#define VCONV_GET_FORMAT_ID(fmt)	\
		(((__u32)fmt & 0x00ff0000) >> 16)

#define VCONV_PK_R_BGR565		MK_FORMAT(RGB,      1, RASTER, 0)
#define VCONV_PK_R_RGB565		MK_FORMAT(RGB,      1, RASTER, 1)
#define VCONV_PK_R_ABGR1555		MK_FORMAT(RGB,      1, RASTER, 2)
#define VCONV_PK_R_ARGB1555		MK_FORMAT(RGB,      1, RASTER, 3)
#define VCONV_PK_R_ABGR8888		MK_FORMAT(RGB,      1, RASTER, 4)
#define VCONV_PK_R_ARGB8888		MK_FORMAT(RGB,      1, RASTER, 5)
#define VCONV_PK_T_BGR565		MK_FORMAT(RGB,      1, TILE,   0)
#define VCONV_PK_T_RGB565		MK_FORMAT(RGB,      1, TILE,   1)
#define VCONV_PK_T_ABGR1555		MK_FORMAT(RGB,      1, TILE,   2)
#define VCONV_PK_T_ARGB1555		MK_FORMAT(RGB,      1, TILE,   3)
#define VCONV_PK_T_ABGR8888		MK_FORMAT(RGB,      1, TILE,   4)
#define VCONV_PK_T_ARGB8888		MK_FORMAT(RGB,      1, TILE,   5)
#define VCONV_FL_R_R8G8B8		MK_FORMAT(RGB,      3, RASTER, 0)
#define VCONV_FL_T_R8G8B8		MK_FORMAT(RGB,      3, TILE,   0)
#define VCONV_PK_R_AYCBCR8888		MK_FORMAT(YCBCR444, 1, RASTER, 0)
#define VCONV_PK_R_ACBCRY8888		MK_FORMAT(YCBCR444, 1, RASTER, 1)
#define VCONV_PK_T_AYCBCR8888		MK_FORMAT(YCBCR444, 1, TILE,   0)
#define VCONV_PK_T_ACBCRY8888		MK_FORMAT(YCBCR444, 1, TILE,   1)
#define VCONV_FL_R_Y8CB8CR8_444		MK_FORMAT(YCBCR444, 3, RASTER, 0)
#define VCONV_FL_R_Y8CB8CR8_422		MK_FORMAT(YCBCR422, 3, RASTER, 0)
#define VCONV_PK_T_VDU1			MK_FORMAT(YCBCR420, 1, TILE,   0)
#define VCONV_PK_T_VDU2			MK_FORMAT(YCBCR420, 1, TILE,   1)
#define VCONV_PT_R_Y8CBCR16		MK_FORMAT(YCBCR420, 2, RASTER, 0)
#define VCONV_PT_T_Y8CBCR16		MK_FORMAT(YCBCR420, 2, TILE,   0)
#define VCONV_PT_T_Y8CB8CR8		MK_FORMAT(YCBCR420, 2, TILE,   1)
#define VCONV_PT_T_VEU			MK_FORMAT(YCBCR420, 2, TILE,   2)
#define VCONV_FL_R_Y8CB8CR8_420		MK_FORMAT(YCBCR420, 3, RASTER, 0)

#define VCONV_PT_R_GPU			VCONV_PT_R_Y8CBCR16
#define VCONV_PT_T_GPU			VCONV_PT_T_Y8CBCR16
#define VCONV_PT_T_VENEZIA		VCONV_PT_T_Y8CB8CR8
#define VCONV_FL_R_VENEZIA		VCONV_FL_R_Y8CB8CR8_420

enum vconv_force_mode {
	VCONV_FORCE_MODE_OFF = 0,
	VCONV_FORCE_MODE_ON
};

/* structures */
struct vconv_rect {
	__u16			h;
	__u16			v;
};

struct vconv_scale {
	__u16			fraction;
	__u8			integer;
};

struct vconv_offset {
	__u8			y_offset;
	__u8			c_offset;
};

struct vconv_limit {
	__u8			max;
	__u8			min;
};

struct vconv_coef {
	__s16			coef[3][3];
};

struct vconv_y2r {
	__u8			y_offset;
	__u8			c_offset;
	__s16			coef[3][3];
	__u8			max;
	__u8			min;
};

struct vconv_r2y {
	__u8			y_offset;
	__u8			c_offset;
	__s16			coef[3][3];
	__u8			y_max;
	__u8			y_min;
	__u8			c_max;
	__u8			c_min;
};

union vconv_mtx {
	struct vconv_y2r	y2r;
	struct vconv_r2y	r2y;
};

struct vconv_img_param {
	/* colorformat, planes, scan type */
	__u32			format;
	/* hsize, vsize */
	struct vconv_rect	size;
	/* hoffset, voffset */
	struct vconv_rect       offset;
	/* hscale : only out image */
	struct vconv_scale	hscale;
	/* vscale : only out image */
	struct vconv_scale	vscale;
	/* hdelta, vdelta */
	struct vconv_rect	delta;
};

struct vconv_force {
	enum vconv_force_mode	mode;
	__u8			gy;
	__u8			bcb;
	__u8			rcr;
	__u8			alpha;
};

struct vconv_crop {
	__u8			upper;
	__u8			lower;
	__u8			left;
	__u8			right;
};

struct vconv_buffer {
	int			fd;
	size_t			offset;
	__u16			pitch;
};

enum vconv_buffer_mode {
	VCONV_USE_FD = 0,
	VCONV_USE_ADDRESS
};

struct vconv_buffer_ex {
	enum vconv_buffer_mode	mode;
	int			fd;
	void			*phys;
	size_t			offset;
	__u16			pitch;
};

struct vconv_out_buffer {
	int			fd;
	size_t			offset;
	__u16			pitch;
};

struct vconv_param {
	/* input buffer parameters */
	struct vconv_buffer	in_buffer[VCONV_PLANE_MAX];
	/* output buffer parameters */
	struct vconv_buffer	out_buffer[VCONV_PLANE_MAX];
	/* imput image parameters */
	struct vconv_img_param	in_img;
	/* output image parameters */
	struct vconv_img_param	out_img;
	/* force mode paramters */
	struct vconv_force	force_mode;
	/* cropping parameters */
	struct vconv_crop	crop;
	/* color conversion parameters */
	union vconv_mtx		conv;
	/* alpha mode parameters */
	enum vconv_alpha_mode	alpha;
};

struct vconv_param_ex {
	/* input buffer parameters */
	struct vconv_buffer_ex	in_buffer[VCONV_PLANE_MAX];
	/* output buffer parameters */
	struct vconv_buffer_ex	out_buffer[VCONV_PLANE_MAX];
	/* imput image parameters */
	struct vconv_img_param	in_img;
	/* output image parameters */
	struct vconv_img_param	out_img;
	/* force mode paramters */
	struct vconv_force	force_mode;
	/* cropping parameters */
	struct vconv_crop	crop;
	/* color conversion parameters */
	union vconv_mtx		conv;
	/* alpha mode parameters */
	enum vconv_alpha_mode	alpha;
};

struct vconv_verify {
	struct vconv_buffer	buf;
	/* expect data buffer */
	__u8			*exp_buf;
	/* expect data size */
	size_t			exp_size;
	struct vconv_rect	exp_rect;
};

/* ioctl command code */
#define	IOC_VCONV_START		_IOWR('c', 1, struct vconv_param)
#define IOC_VCONV_CANCEL	_IO('c', 2)
#define IOC_VCONV_VERIFY	_IOWR('C', 3, struct vconv_verify)
#define	IOC_VCONV_START_EX	_IOWR('c', 4, struct vconv_param_ex)



/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

#ifdef __KERNEL__
long vconv_start(struct vconv_param *param);
long vconv_start_ex(struct vconv_param_ex *param);
long vconv_cancel(void);
#endif	/* __KERNEL__ */


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __APPLITE_VCONV_H__ */

