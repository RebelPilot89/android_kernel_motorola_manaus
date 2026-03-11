# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2022 MediaTek Inc.

subdir-ccflags-y += -Werror

CAM_CAL_SRC_PATH := $(srctree)/drivers/misc/mediatek/cam_cal/src_v4l2
CAM_CAL_CUSTOM_SRC_PATH := $(CAM_CAL_SRC_PATH)/custom
MTK_CUSTOM_PATH := $(srctree)/drivers/misc/mediatek
MOT_PROJECT := $(subst ",,$(CONFIG_MTK_EEPROM_PROJECT))

ifneq ($(MOT_PROJECT),)
CAM_CAL_CUSTOM_SRC_LAYOUT_PATH := $(CAM_CAL_CUSTOM_SRC_PATH)/camera_project/$(MOT_PROJECT)
else
CAM_CAL_CUSTOM_SRC_LAYOUT_PATH := $(CAM_CAL_CUSTOM_SRC_PATH)/layout
endif

COMMON_VERSION := v2

subdir-ccflags-y += -I$(MTK_CUSTOM_PATH)/imgsensor/inc \
                    -I$(MTK_CUSTOM_PATH)/cam_cal/inc \
                    -I$(CAM_CAL_CUSTOM_SRC_PATH) \
                    -I$(CAM_CAL_SRC_PATH)/common/$(COMMON_VERSION)

# V4L2 EEPROM driver
obj-$(CONFIG_MTK_CAM_CAL_V4L2) += camera_eeprom_v4l2.o

camera_eeprom_v4l2-objs := ../common/$(COMMON_VERSION)/eeprom_driver.o
camera_eeprom_v4l2-objs += ../common/$(COMMON_VERSION)/eeprom_i2c_common_driver.o
camera_eeprom_v4l2-objs += ../common/$(COMMON_VERSION)/eeprom_utils.o
camera_eeprom_v4l2-objs += eeprom_i2c_custom_driver.o
camera_eeprom_v4l2-objs += cam_cal_list.o

comma := ,
empty :=
space := $(empty) $(empty)

KERNEL_CAM_CAL_SRC := $(notdir $(wildcard $(CAM_CAL_CUSTOM_SRC_LAYOUT_PATH)/*.c))
ifneq ($(MOT_PROJECT),)
KERNEL_CAM_CAL_OBJ := $(addprefix camera_project/$(MOT_PROJECT)/,$(patsubst %.c,%.o,$(KERNEL_CAM_CAL_SRC)))
else
KERNEL_CAM_CAL_OBJ := $(addprefix layout/,$(patsubst %.c,%.o,$(KERNEL_CAM_CAL_SRC)))
endif

KERNEL_CAM_CAL := $(basename $(KERNEL_CAM_CAL_SRC))
CAM_CAL_CONFIG_LIST := $(subst $(space),$(comma),$(foreach e,$(subst ",,$(KERNEL_CAM_CAL)),E($(e))))
subdir-ccflags-y += -D'CAM_CAL_CONFIG_LIST=$(CAM_CAL_CONFIG_LIST)'

camera_eeprom_v4l2-objs += cam_cal_config.o
camera_eeprom_v4l2-objs += $(KERNEL_CAM_CAL_OBJ)
