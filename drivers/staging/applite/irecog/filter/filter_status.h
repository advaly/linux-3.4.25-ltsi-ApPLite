/*
 * linux/drivers/staging/applite/irecog/filter/filter_status.h
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
#ifndef FILTER_STATUS_H
#define FILTER_STATUS_H

enum filter_queue_status_e {
	FILTER_SUCCESS = 0,	    /**< Success Request */
	FILTER_ERROR = -20	       /**< Failed Request */
};
typedef enum filter_queue_status_e FILTER_STATUS;

#endif /* FILTER_STATUS_H */
