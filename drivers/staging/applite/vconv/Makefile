#
# linux/drivers/staging/applite/vconv
#

obj-${CONFIG_APPLITE_VCONV} 		+= vconv.o
ccflags-$(CONFIG_APPLITE_VCONV_DEBUG)	+= -D_TEST_BUILD_

vconv-objs 	:= applite_vconv_if.o applite_vconv_procfs.o applite_vconv_core.o applite_vconv_dbg.o
