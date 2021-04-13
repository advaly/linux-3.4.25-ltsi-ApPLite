/*
 * drivers/staging/applite/veu/ve_trace.c
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

#include "ve_trace.h"
#include "ve_access.h"
#include "ve_task.h"

#ifdef VE_LOG_TRACE
void ve_log_trace(uint32_t id, uint32_t value)
{

	uint32_t trace_enable;
	uint32_t begin;
	uint32_t end;
	uint32_t cur;
	uint32_t seq_num;

	acs_rev_read32(CMN_VE_LOG_BEGIN, &trace_enable);
	if (trace_enable == 0)
		return;

	acs_rev_read32(CMN_VE_LOG_BEGIN, &begin);
	acs_rev_read32(CMN_VE_LOG_END, &end);
	acs_rev_read32(CMN_VE_LOG_CUR, &cur);
	acs_rev_read32(CMN_VE_LOG_SEQ, &seq_num);

	if ((begin + 16) > end) {  /* empty area */
		return;
	}
	if (!(id & VE_LT_LEVEL_MASK)) {  /* not trace level */
		return;
	}

	/* update sequence number */
	seq_num = (seq_num+1) & 0xffffffff;
	acs_rev_write32(CMN_VE_LOG_SEQ, seq_num);

	/* turn around */
	if ((cur + 16) > end)
		cur = begin;

	acs_rev_write32(cur, seq_num);
	cur += 4;
	acs_rev_write32(cur, 0);
	cur += 4;
	acs_rev_write32(cur, id);
	cur += 4;
	acs_rev_write32(cur, value);
	cur += 4;

	if (cur >= end)
		cur = begin;

	acs_rev_write32(CMN_VE_LOG_CUR, cur);
}
#endif

