#
# Makefile for the ApP Lite series framebuffer device driver
#

ifeq ($(CONFIG_FB_APPLITE_BASIC),y)
  ifeq ($(CONFIG_FB_APPLITE_BASIC_GFX_MERGED),y)
    subdir-ccflags-y			  += -D_FIXUP_ADDR_VIRT_ -D_MERGE_FBDEV_
    obj-$(CONFIG_FB_TZ2000)		  += tz2000fb.o
  else
    subdir-ccflags-y			  += -D_FIXUP_ADDR_VIRT_ -U_MERGE_FBDEV_
    obj-$(CONFIG_FB_TZ2000)		  += tz2000fb.o
    obj-$(CONFIG_FB_TZ2000)		  += tz2000gfx.o
  endif
  obj-$(CONFIG_FB_TZ3000)		  += tz3000fb.o

  ifeq ($(CONFIG_FB_TZ2000),y)
    ifeq ($(CONFIG_FB_APPLITE_BASIC_GFX_MERGED),y)
      tz2000fb-y := tz2000fb_base.o tz2000gfx_base.o
    else
      tz2000fb-y := tz2000fb_base.o
      tz2000gfx-y := tz2000gfx_driver.o tz2000gfx_base.o
    endif
  endif
  ifeq ($(CONFIG_FB_TZ2000),m)
    ifeq ($(CONFIG_FB_APPLITE_BASIC_GFX_MERGED),y)
      tz2000fb-y := tz2000fb_base.o tz2000gfx_base.o
    else
      tz2000fb-y := tz2000fb_base.o
      tz2000gfx-y := tz2000gfx_driver.o tz2000gfx_base.o
    endif
  endif
else
  subdir-ccflags-y			  += -U_FIXUP_ADDR_VIRT_ -D_MERGE_FBDEV_
  obj-$(CONFIG_FB_TZ3000)		  += applitefb.o
  obj-$(CONFIG_FB_TZ2000)		  += applitefb.o

  ifeq ($(CONFIG_FB_TZ3000),y)
    applitefb-y := applitefb_base.o applitefb_tz3000.o
  endif
  ifeq ($(CONFIG_FB_TZ3000),m)
    applitefb-y := applitefb_base.o applitefb_tz3000.o
  endif
  ifeq ($(CONFIG_FB_TZ2000),y)
    applitefb-y := applitefb_base.o applitefb_tz2000.o applitefb_tz2000gfx.o
  endif
  ifeq ($(CONFIG_FB_TZ2000),m)
    applitefb-y := applitefb_base.o applitefb_tz2000.o applitefb_tz2000gfx.o
  endif
  ifeq ($(CONFIG_D2DP),y)
    applitefb-y += d2dp.o
  endif
endif
