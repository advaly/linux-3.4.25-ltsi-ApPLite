#
# gdmac pyramid driver
#
GDMAC_COMMON_DIR = ../gdmac_common
PYRAMID_DIR      = ../pyramid

ccflags-y += -I$(obj)
ccflags-y += -I$(obj)/../common/include
ccflags-y += -I$(obj)/$(PYRAMID_DIR)
ccflags-y += -I$(obj)/$(GDMAC_COMMON_DIR)/include


obj-${CONFIG_APPLITE_IRECOG_GDMAC_PYRAMID}	+= gdmac_pyramid.o
gdmac_pyramid-objs := gdmac_pyramid_driver.o pyramid.o 
