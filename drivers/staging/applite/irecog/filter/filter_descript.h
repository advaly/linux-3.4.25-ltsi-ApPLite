/*
 * linux/drivers/staging/applite/irecog/filter/filter_descript.h
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
#ifndef FILTER_DESCRIPT_H
#define FILTER_DESCRIPT_H

#include <linux/applite/irecog/basic_type.h>

/*----------------------------------------------------------------*/
/*                      Macro Definition                          */
/*----------------------------------------------------------------*/
/*----------------------------------------------------------------*/
/*                      Macro Function Definition                 */
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*                      typedef Definition                        */
/*----------------------------------------------------------------*/
/*----------------------------------------------------------------*/
/*                      struct/enum Definition                    */
/*----------------------------------------------------------------*/

struct filter_ctrl_register_s {
	UINT rst;
	UINT cmd;
	UINT intmask;
	UINT intclr;
};
typedef struct filter_ctrl_register_s FILTER_CTRL;

struct filter_kick_register_s {
	UINT initkick;
	UINT imgkick;
};
typedef struct filter_kick_register_s FILTER_KICK;

struct filter_info {
	USHORT inittrnum;
    /*----- Only Used for Queue Handling */
	UCHAR mode;
	UCHAR reserved;
    /*-----------------------------------*/

	UINT imgfrmchnum;
	UINT prmtrnum;

    /*----- Only Used for Queue Handling */
	UINT sequence_id;
    /*-----------------------------------*/
};
typedef struct filter_info FILTER_INFO;

struct filter_image_info {
	UINT initaddr;
	UINT ratiooffset;
};
typedef struct filter_image_info FILTER_IMAGE_INFO;

/**
 * @brief Struct of Modification Set on FILTER Sequence HIF Parameter
 */
struct filter_hif_param_s {
	SSHORT *addr;
	SSHORT data;
};
typedef struct filter_hif_param_s FILTER_HIF_PARAM;

/**
 * @brief Struct for Filter HW Register Set
 * @note  1 Input/1 Output & No Parameter Transfer
 */
struct filter_descript_s {
	/*
	 * Number Infomation Registers
	 * +0x0040-0x0048
	 */
	FILTER_INFO info;	   /**< Frame Number, Channel Number etc.(12Bytes) */

	/*
	 * Filter Initialization Regsters
	 * +0x004C-0x0088
	 */
	UINT init_param[16];	  /**< Initialize parameters (64Bytes) */

	/* Filter Input/OutputImage input 4ch & output 4ch */

	FILTER_IMAGE_INFO image_set[8];

	/* Filter Parameter */
	UINT transparam[16];

	/* for HIF Modification */
	SSHORT *ioc_addr;	 /**< Main Bus Address of IOC data */
	USHORT ihwid;		 /**< Input Image Width */
	USHORT ihwidbl;		 /**< Input Image Width with Banking */
	SSHORT hbgn;		 /**< Horizontal Start Point of Output Image */
	SSHORT hend;		 /**< Horizontal End Point of Output Image */

	USHORT ivwid;		 /**< Input Image Height */
	USHORT ivwidbl;		 /**< Input Image Height with Banking */
	SSHORT vbgn;		 /**< Vertical Start Point of Output Image */
	SSHORT vend;		 /**< Vertical End Point of Output Image */

	/* For Filter Param Modification */
	UINT hif_param_num;
	FILTER_HIF_PARAM *hif_param;

};

typedef struct filter_descript_s FILTER_DESCRIPT;

#endif /* FILTER_DESCRIPT_H */
