/*
 * linux/drivers/staging/applite/irecog/common/include/drv_signal.h
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
#ifndef DRV_SIGNAL_H_
#define DRV_SIGNAL_H_

#include <linux/signal.h>

static inline void drv_sigmask(sigset_t *oldset)
{
	sigset_t blocked;

	sigemptyset(&blocked);
	sigaddset(&blocked, SIGPROF);
	sigaddset(&blocked, SIGINT);
	sigaddset(&blocked, SIGTERM);
	sigprocmask(SIG_BLOCK, &blocked, oldset);
}

static inline void drv_sigunmask(sigset_t *oldset)
{
	sigprocmask(SIG_SETMASK, oldset, NULL);
}

#endif /* DRV_SIGNAL_H__ */
