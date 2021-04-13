/*
 * TZ2000 Graphics Device
 *
 * Copyright (C) 2006-2008  IGEL Co.,Ltd
 *
 * Written by Denis Oliver Kropp <dok@directfb.org>
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v2
 * as published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/version.h>

#include <asm/io.h>
#include <asm/processor.h>

#include "tz2000gfx_internal.h"


/******************************************************************************/


/******************************************************************************/

static int __init
tz2000_driver_init(void)
{
	return tz2000gfx_init();
}

module_init(tz2000_driver_init);

/******************************************************************************/

static void __exit
tz2000_driver_exit(void)
{
	tz2000gfx_exit();
}

module_exit(tz2000_driver_exit);

/******************************************************************************/

MODULE_AUTHOR("TOSHIBA, Co.Ltd");
MODULE_LICENSE("GPL v2");

