#Platform for the emmc driver
PLATFORM=LINUX
BOARD=glen
test=n

ifeq ($(BOARD),glen)
# for Glenfiddich
KERNELDIR ?= /home/emmc/toolchain/linux-3.4.25/modules/lib/modules/3.4.25-ltsi-ApPLite-20130312/build
CC_OPTS = ARCH=arm CROSS_COMPILE=/opt/arm-2010q1/bin/arm-none-linux-gnueabi-
ccflags-y += -D__GLEN
ccflags-y += -D__OTP
ccflags-y += -D__32BIT
ccflags-y += -D__KERNEL_3_4_25
else
# for Orion
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
CC_OPTS =
endif

#Current working directory
SRC_PATH  = ./drivers/staging/applite/emmc/bld

# SUB DIRECTORIES
DEBUG_PATH      = ../debug
DEVICE_PATH     = ../dev
BUILD_PATH      = ../bld
CMD_PATH        = ../cmd
HOST_PATH       = ../host
INTR_PATH       = ../intr
API_PATH        = ../api
BM_PATH         = ../bm
OS_PATH         = ../os
APP_PATH        = ../app
ifeq ($(BOARD),glen)
LINUX_PATH      = ../os/linux-glen
else
LINUX_PATH      = ../os/linux
endif
COMMON_PATH     = ../common

# Includes for dependencies
INCLUDES += -I$(SRC_PATH)/$(DEBUG_PATH)
INCLUDES += -I$(SRC_PATH)/$(DEVICE_PATH)
INCLUDES += -I$(SRC_PATH)/$(BUILD_PATH)
INCLUDES += -I$(SRC_PATH)/$(CMD_PATH)
INCLUDES += -I$(SRC_PATH)/$(HOST_PATH)
INCLUDES += -I$(SRC_PATH)/$(INTR_PATH)
INCLUDES += -I$(SRC_PATH)/$(API_PATH)
INCLUDES += -I$(SRC_PATH)/$(BM_PATH)
INCLUDES += -I$(SRC_PATH)/$(OS_PATH)
INCLUDES += -I$(SRC_PATH)/$(APP_PATH)
INCLUDES += -I$(SRC_PATH)/$(COMMON_PATH)

ifeq ($(PLATFORM),LINUX)
    #default for linux
	INCLUDES += -I$(SRC_PATH)/$(LINUX_PATH)
	EMMCDRV_OBJS = $(LINUX_PATH)/os.o
	EMMCDRV_OBJS += $(LINUX_PATH)/os_resource.o
else ifeq ($(PLATFORM),others)
    #extended to other platforms
endif

WARN := -Wall -Wstrict-prototypes -Wmissing-prototypes
EXTRA_CFLAGS += $(INCLUDES) $(WARN)

EMMCDRV_OBJS += \
	$(CMD_PATH)/cmd_api.o \
	$(DEVICE_PATH)/seq.o \
	$(DEVICE_PATH)/pm.o \
	$(DEVICE_PATH)/datarem_prot.o \
	$(INTR_PATH)/intr.o \
	$(BM_PATH)/bm.o \
	$(HOST_PATH)/hc_api.o \
	$(API_PATH)/emmc_api.o \
	$(DEBUG_PATH)/debug.o \

#ifeq ($(test),n)
#obj-m += emmc_block.o
#ccflags-y += -Wall
#else ifeq ($(test),t)
#obj-m += testDrv.o
#else
#obj-m += emmc_unit.o
#ccflags-y += -Wall
#endif

#ifeq ($(BOARD),glen)
#obj-m += emmc_part.o
#endif

obj-$(CONFIG_APPLITE_EMMC) += emmc_block.o
ccflags-y += -Wall
ifeq ($(APPLITE_EMMC_TEST),y)
obj-$(CONFIG_APPLITE_EMMC) += emmc_part.o
obj-$(CONFIG_APPLITE_EMMC) += emmc_unit.o
endif

emmc_block-objs :=  $(EMMCDRV_OBJS) $(APP_PATH)/basic_blk.o
emmc_unit-objs := $(EMMCDRV_OBJS) $(APP_PATH)/basic.o
emmc_part-objs := $(EMMCDRV_OBJS) $(APP_PATH)/basic_part.o
testDrv-objs := $(EMMCDRV_OBJS) $(APP_PATH)/testDrv.o

#For device error handling, performance measurement & debug messages
ccflags-y += -D__DEVERR_HANDLING
#ccflags-y += -D__PERFORMANCE_MEASUREMENT
ccflags-y += -D__DEBUG

#all:
#	make -C $(KERNELDIR) M=$(SRC_PATH) $(EXTRA_CFLAGS) modules $(CC_OPTS)
#	$(RM) .emmc_block.* emmc_block.ko.* emmc_block.mod.* emmc_block.o*
#	$(RM) .emmc_unit.* emmc_unit.ko.* emmc_unit.mod.* emmc_unit.o*
#	$(RM) .emmc_part.* emmc_part.ko.* emmc_part.mod.* emmc_part.o*
#	$(RM) .testDrv.* testDrv.ko.* testDrv.mod.* testDrv.o*
#	$(RM) -r modules.order Module.symvers .tmp_versions
#
#clean:
#	make -C $(KERNELDIR) M=$(SRC_PATH) clean
#	$(RM) ./.tmp_versions ./*~ ./*.markers ./*.order
#	find $(DEBUG_PATH) $(DEVICE_PATH) $(BUILD_PATH) $(CMD_PATH) $(HOST_PATH) $(INTR_PATH) \
#	    $(API_PATH) $(BM_PATH) $(OS_PATH) $(APP_PATH) $(LINUX_PATH) -name *.o -delete
#	find $(DEBUG_PATH) $(DEVICE_PATH) $(BUILD_PATH) $(CMD_PATH) $(HOST_PATH) $(INTR_PATH) \
#	    $(API_PATH) $(BM_PATH) $(OS_PATH) $(APP_PATH) $(LINUX_PATH) -name .*.o.cmd -delete
#	find $(DEBUG_PATH) $(DEVICE_PATH) $(BUILD_PATH) $(CMD_PATH) $(HOST_PATH) $(INTR_PATH) \
#	    $(API_PATH) $(BM_PATH) $(OS_PATH) $(APP_PATH) $(LINUX_PATH) -name *.mod -delete
#	find $(DEBUG_PATH) $(DEVICE_PATH) $(BUILD_PATH) $(CMD_PATH) $(HOST_PATH) $(INTR_PATH) \
#	    $(API_PATH) $(BM_PATH) $(OS_PATH) $(APP_PATH) $(LINUX_PATH) -name *.mod.c -delete
#
#depend .depend dep:
#	$(CC) $(EXTRA_CFLAGS) -M *.c > .depend
#
#ifeq (.depend,$(wildcard .depend))
#include .depend
#endif
