#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

ifneq ($(CONFIG_MTK_GPU_VERSION),"")
MTK_GPU_VERSION = $(subst ",,$(CONFIG_MTK_GPU_VERSION))

$(info MTK_GPU_VERSION = $(MTK_GPU_VERSION))

ifneq ($(CONFIG_MTK_PLATFORM),)
export MTK_PLATFORM = $(subst ",,$(CONFIG_MTK_PLATFORM))
else ifeq ($(CONFIG_MTK_GPU_MT6789_SUPPORT),y)
export MTK_PLATFORM = mt6789
else ifeq ($(CONFIG_MTK_GPU_MT6833_SUPPORT),y)
export MTK_PLATFORM = mt6833
else ifeq ($(CONFIG_MTK_GPU_MT6855_SUPPORT),y)
export MTK_PLATFORM = mt6855
else ifeq ($(CONFIG_MTK_GPU_MT6879_SUPPORT),y)
export MTK_PLATFORM = mt6879
else ifeq ($(CONFIG_MTK_GPU_MT6893_SUPPORT),y)
export MTK_PLATFORM = mt6893
else ifeq ($(CONFIG_MTK_GPU_MT6895_SUPPORT),y)
export MTK_PLATFORM = mt6895
else ifeq ($(CONFIG_MTK_GPU_MT6983_SUPPORT),y)
export MTK_PLATFORM = mt6983
else
export MTK_PLATFORM = $(word 4,$(MTK_GPU_VERSION))
endif

ifeq ($(MTK_PLATFORM),mt6873)
subdir-ccflags-y += -DCONFIG_GPU_MT6873
else ifeq ($(MTK_PLATFORM),mt6893)
subdir-ccflags-y += -DCONFIG_GPU_MT6893
else ifeq ($(MTK_PLATFORM),mt6853)
subdir-ccflags-y += -DCONFIG_GPU_MT6853
endif
endif

ifneq ($(CONFIG_MTK_GPU_SUPPORT),)
    obj-y += ged/
    obj-y += hal/
    obj-y += gpufreq/
    obj-y += gpu_bm/
    obj-y += gpueb/

ifneq ($(CONFIG_MTK_GPU_VERSION),"")
# GPU R5P0
ifeq ($(CONFIG_MTK_GPU_R5P0),y)
    obj-y += $(subst ",,$(CONFIG_MTK_PLATFORM))/
else ifneq ($(word 1,$(MTK_GPU_VERSION)),)
    obj-y += gpu_$(word 1,$(MTK_GPU_VERSION))/
else
    obj-y += $(subst ",,$(CONFIG_MTK_PLATFORM))/
endif
endif

endif
