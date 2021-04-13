COMMON_DIR = ./common
GDMAC_COMMON_DIR = ./gdmac_common
FILTER_DIR       = ./filter
PYRAMID_DIR      = ./pyramid

ccflags-y += -I$(obj)/$(COMMON_DIR)/include
ccflags-y += -I$(obj)/$(FILTER_DIR)
ccflags-y += -I$(obj)/$(PYRAMID_DIR)
ccflags-y += -I$(obj)/$(GDMAC_COMMON_DIR)/include

ifdef CONFIG_APPLITE_IRECOG_PYRAMID
  PYRAMID_OBJ := y
endif
ifdef CONFIG_APPLITE_IRECOG_GDMAC_PYRAMID
  PYRAMID_OBJ := y
  GDMAC_OBJ := y
endif
ifdef CONFIG_APPLITE_IRECOG_GDMAC_HAND_DETECT_ISOLATE
  GDMAC_OBJ := y
endif

ifeq ($(PYRAMID_OBJ), y)
_pyramid_dummy := $(shell mkdir -p $(obj)/$(PYRAMID_DIR))
obj-y += $(PYRAMID_DIR)/pyramid_tap_coeff.o
endif

ifeq ($(GDMAC_OBJ), y)
_gdmac_common_dummy := $(shell mkdir -p $(obj)/$(GDMAC_COMMON_DIR))
obj-y += $(GDMAC_COMMON_DIR)/gdmac_instructions.o
endif

obj-$(CONFIG_APPLITE_IRECOG_AFFINE)			+= affine/
obj-$(CONFIG_APPLITE_IRECOG_FILTER)			+= filter/
obj-$(CONFIG_APPLITE_IRECOG_HOG)			+= hog/
obj-$(CONFIG_APPLITE_IRECOG_PYRAMID)			+= pyramid/
obj-$(CONFIG_APPLITE_IRECOG_GDMAC_PYRAMID)		+= gdmac_pyramid/
obj-$(CONFIG_APPLITE_IRECOG_GDMAC_HAND_DETECT_ISOLATE)	+= gdmac_hand_detect_isolate/
obj-$(CONFIG_APPLITE_IRECOG_KMEM_ALLOCATOR)		+= kmem_allocator/
obj-$(CONFIG_APPLITE_IRECOG_HIST)			+= hist/
