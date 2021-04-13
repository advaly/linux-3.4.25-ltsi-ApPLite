/*
 * linux/drivers/staging/applite/irecog/common/include/drv_defs.h
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
#ifndef _DRV_DEFS_H_
#define _DRV_DEFS_H_

#ifdef ENABLE_SPYESIDE_SIM
/* --- for qemu --- */

/* rpyramid */
#define PYRAMID_BASE 0x12000000
#define PYRAMID_SIZE 0x2000
#define PYM_BASE     0x0000
#define RSCALER_BASE 0x1000
#define PYRAMID_IRQ  85

/* raffine */
#define AFFINE_BASE 0x12002000
#define AFFINE_SIZE 0x400
#define AFFINE_IRQ  86

/* rhist */
#define HIST_BASE
#define HIST_SIZE
#define HIST_IRQ

/* rfilter */
#define FILTER_BASE 0x12002c00
#define FILTER_SIZE 0x400
#define FILTER_IRQ  91

/* rgohog */
#define HOG0_BASE 0x12003000
#define HOG0_SIZE 0x400
#define HOG0_IRQ  89
#define HOG1_BASE 0x12003400
#define HOG1_SIZE 0x400
#define HOG1_IRQ  90
#define DICT_BASE 0x12003800
#define DICT_SIZE 0x400

/* gdmac */
#define GDMAC_BASE           0x12004000
#define GDMAC_NONSECURE_BASE 0x12004000
#define GDMAC_SIZE           0x1000
#define GDMAC_EVENT_IRQ0 82	/* gdmac_pyramid */
#define GDMAC_EVENT_IRQ1 82	/* gdmac_hand    */
#define GDMAC_INT0       0	/* gdmac_pyramid */
#define GDMAC_INT1       0	/* gdmac_hand    */

/* mailbox */
#define MAILBOX_BASE 0x12005000
#define MAILBOX_SIZE 0x1000

/* pmu */
#define PMU_BASE 0x00440000
#define PMU_SIZE 0x1000

/* gconf */
#define GCONF_BASE 0x00401000
#define GCONF_SIZE 0x1000

#else

/* --- for speyside board --- */
#define IRECOG_BASE 0x0B140000

/* rpyramid */
#define PYRAMID_BASE (IRECOG_BASE + 0x0000)
#define PYRAMID_SIZE 0x1800
#define PYM_BASE     0x0000
#define RSCALER_BASE 0x1000
#define PYRAMID_IRQ  184

/* raffine */
#define AFFINE_BASE (IRECOG_BASE + 0x1800)
#define AFFINE_SIZE 0x400
#define AFFINE_IRQ  185

/* rhist */
#define HIST_BASE (IRECOG_BASE + 0x1C00)
#define HIST_SIZE 0x400
#define HIST_IRQ  186

/* rfilter */
#define FILTER_BASE (IRECOG_BASE + 0x2400)
#define FILTER_SIZE 0x400
#define FILTER_IRQ  190

/* rgohog */
#define HOG0_BASE (IRECOG_BASE + 0x2800)
#define HOG0_SIZE 0x400
#define HOG0_IRQ  188
#define HOG1_BASE (IRECOG_BASE + 0x2C00)
#define HOG1_SIZE 0x400
#define HOG1_IRQ  189
#define DICT_BASE (IRECOG_BASE + 0x3000)
#define DICT_SIZE 0x400

/* gdmac */
#define GDMAC_BASE      0x08100000
#define GDMAC_NONSECURE_BASE 0x08101000
#define GDMAC_SIZE      0x1000
#define GDMAC_EVENT_IRQ0 136	/* gdmac_pyramid */
#define GDMAC_EVENT_IRQ1 137	/* gdmac_hand    */
#define GDMAC_INT0       0	/* gdmac_pyramid */
#define GDMAC_INT1       1	/* gdmac_hand    */

/* mailbox */
#define MAILBOX_BASE 0x080c0000
#define MAILBOX_SIZE 0x20000

/* pmu */
#define PMU_BASE 0x00440000
#define PMU_SIZE 0x1000

/* gconf */
#define GCONF_BASE 0x00401000
#define GCONF_SIZE 0x1000

#endif

#endif /* _DRV_DEFS_H_ */
