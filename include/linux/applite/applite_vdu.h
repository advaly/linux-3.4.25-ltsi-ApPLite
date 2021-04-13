/*
 * drivers/staging/applite/vdu/applite_vdu.h
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

#if !defined(__APPLITE_VDU_H__)
#define __APPLITE_VDU_H__

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

struct vdec_shmem {
	int32_t fd;         /* shared memory fd */
	uint32_t offset;    /* shared memory offset */
};

enum vdec_decoder_type{
	VDEC_DECODER_TYPE_H264 = 0
};

struct vdec_start {
	struct vdec_shmem in_outbuffer;    /* output frame storage area */
	int32_t in_outbuffersize;	   /* output frame area size */
	int32_t in_uf_thr;		   /* threshold of input buffer free event */
	enum vdec_decoder_type in_decoder; /* decoder type */
};

struct vdec_getininfo {
	uint32_t out_inbuf_max_size; /* free size of input buffer for decode */
};

struct vdec_setindata {
	uint32_t in_eod;	/* end of stream */
	uint32_t in_buffer;	/* input data storage area */
	uint32_t in_buffersize;	/* size of input data */

	uint32_t out_inbuf_max_size; /* free size of input buffer for decode */
};

struct vdec_frame_info {
	struct vdec_shmem outbuffer;
	uint32_t id0[2];
	uint32_t id1[2];
	uint32_t width;
	uint32_t height;
	uint32_t crop_top;
	uint32_t crop_bottom;
	uint32_t crop_left;
	uint32_t crop_right;
	uint32_t num_units_in_tick;
	uint32_t time_scale;
	uint32_t sar_width;
	uint32_t sar_height;
	uint32_t interlaced;
	uint32_t eod;
};

struct vdec_getoutframe {
	int32_t in_timeout;	   /* latency of output frame */
	uint32_t out_is_available; /* available of output frame */
				   /*  0:not 1:available */
				   /*  1:available */
	struct vdec_frame_info out_frame_info; /* info of output frame */
};

struct vdec_waitforinbuf {
	int32_t in_timeout;        /* latency of input buffer free event */
	uint32_t out_inbuf_max_size;
		/* free size of input buffer for decode */
};

struct vdec_waitforoutframe {
	int32_t in_timeout;	        /* latency of output frame */
	uint32_t out_is_available;	/* available of output frame */
					/*  0:not 1:available */
					/*  1:available */
	struct vdec_frame_info out_frame_info; /* info of output frame */
};

struct vdec_getoutframewithconv {
	int32_t in_timeout;	   /* latency of output frame */
	struct vconv_param in_vconv_param; /* vconv parameter */
					   /* see applite_vconv.h */
	uint32_t out_is_available;	/* available of next output frame */
					/*  0:not 1:available */
					/*  1:available */
	struct vdec_frame_info out_frame_info; /* info of output frame */
};

/* vdu ioctl command */
#define IOC_VDEC_START		_IOW('d', 1, struct vdec_start)
#define IOC_VDEC_STOP		_IO('d', 2)
#define IOC_VDEC_GETININFO	_IOR('d', 3, struct vdec_getininfo)
#define IOC_VDEC_SETINDATA	_IOWR('d', 4, struct vdec_setindata)
#define IOC_VDEC_GETOUTFRAME	_IOR('d', 5, struct vdec_getoutframe)
#define IOC_VDEC_RELOUTFRAME	_IO('d', 6)
#define IOC_VDEC_WAITFORINBUF	_IOWR('d', 7, struct vdec_waitforinbuf)
#define IOC_VDEC_WAITFOROUTFRAME _IOWR('d', 8, \
					struct vdec_waitforoutframe)
#define IOC_VDEC_CANCEL		_IO('d', 9)
#define IOC_VDEC_GETOUTFRAMEWITHCONV _IOR('c', 10, \
					struct vdec_getoutframewithconv)

/* veu errno */
#define VDEC_ERRNO	500
#define EVDUBTSKID	(VDEC_ERRNO+1)    /* Bad task id */
#define EVDUNOINIT	(VDEC_ERRNO+2)    /* No initialize */
#define EVDUVDAPI	(VDEC_ERRNO+3)    /* VD_API operation error */
#define EVDUTIMEDOUT	(VDEC_ERRNO+4)    /* VD_API response time out */
#define EVDUESTAT	(VDEC_ERRNO+5)    /* Illegal status */
#define EVDUVCONV	(VDEC_ERRNO+6)    /* vconv error */
#define EVDUCANCEL	(VDEC_ERRNO+7)    /* cancel */

/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

#ifdef __cplusplus
}
#endif     /* __cplusplus */


#endif    /* __APPLITE_VDU_H__ */

