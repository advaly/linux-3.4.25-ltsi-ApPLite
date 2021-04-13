/*
 * drivers/staging/applite/veu/applite_veu.h
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

#if !defined(__VEU_DRIVER_MODULE_H__)
#define __VEU_DRIVER_MODULE_H__

#ifdef __cplusplus
extern "C" {
#endif        /* __cplusplus */


/*===================================
include Files
===================================*/
#include <linux/ioctl.h>
#include <linux/applite/applite_vconv.h>


/*===================================
Types and structures defined
===================================*/

struct venc_shmem{
	int32_t fd;         /* shared memory fd */
	uint32_t offset;    /* shared memory offset */
};

/* fps */
enum venc_frame_rate{
	VENC_FPS_11_98HZ = 0,
	VENC_FPS_14_98HZ,
	VENC_FPS_15HZ,
	VENC_FPS_23_97HZ,
	VENC_FPS_24HZ,
	VENC_FPS_25HZ,
	VENC_FPS_29_97HZ,
	VENC_FPS_30HZ,
	VENC_FPS_47_95HZ,
	VENC_FPS_48HZ,
	VENC_FPS_50HZ,
	VENC_FPS_59_94HZ,
	VENC_FPS_60HZ,
	/* TODO do i need to add some fpses? */
};

/* profile */ /* 20130410A */
enum venc_profile {
	VENC_PF_ANY = 0,
	VENC_PF_BASELINE,
	VENC_PF_MAIN,
	VENC_PF_HIGH,
};

struct venc_setparam{
	uint32_t output_mode;
	uint32_t profile;
	uint32_t level;
	uint32_t horizontal_pixels;
	uint32_t vertical_pixels;
	enum venc_frame_rate fps;
	uint32_t kbps;
	uint32_t max_kbps;
	uint32_t cpb_size_kbits;
	uint32_t rate_control_mode;
	uint32_t m;
	uint32_t n;
	uint32_t idr_freq;
	uint32_t picture_struct;
	uint32_t slice_num_minus1;
	uint32_t scaling_matrix;
	uint32_t entropy_coding;
	uint32_t weighted_pred;
	uint32_t reference_b;
	uint32_t inter_view_pred;
	uint32_t vui_parameters;
	uint32_t sei0;

	uint32_t aspect_ratio_info_present_flag;
	uint32_t aspect_ratio_idc;
	uint32_t sar_width;
	uint32_t sar_height;
	uint32_t overscan_info_present_flag;
	uint32_t overscan_appropriate_flag;
	uint32_t video_signal_type_present_flag;
	uint32_t video_format;
	uint32_t video_full_range_flag;
	uint32_t colour_description_present_flag;
	uint32_t colour_primaries;
	uint32_t transfer_characteristics;
	uint32_t matrix_coefficients;
	uint32_t chroma_loc_info_present_flag;
	uint32_t chroma_sample_loc_type_top_field;
	uint32_t chroma_sample_loc_type_bottom_field;
	uint32_t timing_info_present_flag;
	uint32_t num_units_in_tick;
	uint32_t time_scale;
	uint32_t fixed_frame_rate_flag;
	uint32_t nal_hrd_parameters_present_flag;
	uint32_t vcl_hrd_parameters_present_flag;
	uint32_t low_delay_hrd_flag;
	uint32_t pic_struct_present_flag;
	uint32_t bitstream_restriction_flag;
};

struct venc_getparam{
	uint32_t in_horizontal_pixels;  /* horizontal pix for input picture */
	uint32_t in_vertical_pixels;    /* vertical pix for input picture */
	uint32_t in_kbps;               /* bit frame for input picture */
	enum venc_frame_rate in_fps;    /* frame rate for input picture */
	enum venc_profile in_profile;   /* profile */ /* 20130410A */
	struct venc_setparam out_param;
};

struct venc_setinframe{
	uint64_t in_frameid;	/* input frame id */
	struct venc_shmem in_lumainputbuf;
				/* luma buffer for input picture */
	struct venc_shmem in_chromainputbuf;
				/* chroma buffer for input picture */
	uint32_t in_sync_frame; /* picture sync frame */
};

struct venc_waitforevents{
	uint64_t out_encframeid;  /* encoded frame id */
	uint32_t out_encresult;   /* encoded result */
	uint64_t out_outframeid;  /* output frame id */
	uint32_t out_outsize;     /* output picture size */
	uint64_t out_relframeid;  /* release enable frame id */
};

struct venc_getoutframe{
	uint32_t in_outputbuf;    /* output picture buffer */
	uint32_t out_outsize;     /* output picture size */
	uint32_t out_attribute;   /* output picture attribte */
};

struct venc_setinframewithcnv{
	uint64_t in_frameid;      /* input frame id */
	/**/
	struct vconv_param in_vconv_param;
};

/* veu ioctl command */
#define IOC_VENC_GETPARAM       _IOWR('c', 1, struct venc_getparam)
#define IOC_VENC_SETPARAM       _IOW('c', 2, struct venc_setparam)
#define IOC_VENC_SETINFRAME     _IOW('c', 3, struct venc_setinframe)
#define IOC_VENC_WAITFOREVENTS  _IOWR('c', 4, struct venc_waitforevents)
#define IOC_VENC_GETOUTFRAME    _IOWR('c', 5, struct venc_getoutframe)
#define IOC_VENC_SETINFRAMEWITHCONVERT _IOW('c', 6, \
					struct venc_setinframewithcnv)

/* invalid frame id */
#define VENC_INVALID_FRAME_ID	(0xffffffffffffffffULL)

/* encoded result */
#define VENC_ENC_RES_SUCCESS	0	/* success */
#define VENC_ENC_RES_FAIL	1	/* fail */
#define VENC_ENC_RES_SYNC_FAIL	2	/* faied to sync frame */

/* output picture attribute */
#define VENC_PIC_ATTR_SYNC_FRAME (1<<0)	/* IDR frame */
#define VENC_PIC_ATTR_EOS	 (1<<1)	/* end of stream */

/* veu errno */
#define VENC_ERRNO          400
#define EVEUBTSKID          (VENC_ERRNO+1)    /* Bad task id */
#define EVEUNOINIT          (VENC_ERRNO+2)    /* No initialize */
#define EVEUVEAPI           (VENC_ERRNO+3)    /* VE_API operation error */
#define EVEUTIMEDOUT        (VENC_ERRNO+4)    /* VE_API response time out */
#define EVEURETRYOVER       (VENC_ERRNO+5)    /* VE_API retry over */
#define EVEUVCONV           (VENC_ERRNO+6)    /* vconv error */

/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

#ifdef __cplusplus
}
#endif     /* __cplusplus */


#endif    /* __VEU_DRIVER_MODULE_H__ */

