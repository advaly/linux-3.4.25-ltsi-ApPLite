/*
 * linux/include/media/applite-camera.h
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

#ifndef __MEDIA_APPLITE_CAMERA_H_
#define __MEDIA_APPLITE_CAMERA_H_

enum applie_camera_lane_config {
	LANE_CONFIG_1LANEx4,	/* 4-Camera, default */
	LANE_CONFIG_2LANEx2,
	LANE_CONFIG_4LANEx1,
};

struct applite_camera_platform_data {
	bool	csirx_unused;	/* true: csirx not access */
	int	lane_config;
};

#endif /* __MEDIA_APPLITE_CAMERA_H_ */
