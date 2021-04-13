#
# linux/drivers/staging/applite/yuvc
#

obj-${CONFIG_APPLITE_YUVC} 		+= yuvc.o
ccflags-$(CONFIG_APPLITE_YUVC_DEBUG)	+= -D_TEST_BUILD_

yuvc-objs 	:= applite_yuvc_if.o applite_yuvc_procfs.o applite_yuvc_core.o applite_yuvc_dbg.o applite_yuvc_dma.o
