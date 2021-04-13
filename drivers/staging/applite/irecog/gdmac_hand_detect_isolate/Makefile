#
# gdmac hand_detect_isolate driver
#
GDMAC_COMMON_DIR = ../gdmac_common
HOG_DIR          = ../hog
FILTER_DIR       = ../filter

ccflags-y += -I$(obj)
ccflags-y += -I$(obj)/../common/include
ccflags-y += -I$(obj)/$(HOG_DIR)
ccflags-y += -I$(obj)/$(FILTER_DIR)
ccflags-y += -I$(obj)/$(GDMAC_COMMON_DIR)/include


obj-${CONFIG_APPLITE_IRECOG_GDMAC_HAND_DETECT_ISOLATE}	+= gdmac_hand_detect_isolate.o
gdmac_hand_detect_isolate-objs := gdmac_hand_detect_isolate_driver.o hand_detect_isolate.o hog.o gdmac_filter.o sl_filter_gdmac.o filter_util_gdmac.o 
