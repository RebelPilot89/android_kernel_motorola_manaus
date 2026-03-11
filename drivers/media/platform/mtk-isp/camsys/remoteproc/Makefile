# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2022 MediaTek Inc.

subdir-ccflags-y += \
	-I$(srctree)/$(src) \
	-I$(srctree)/drivers/remoteproc \
	-I$(srctree)/include/ \
	-I$(srctree)/drivers/misc/mediatek/iommu/

mtk_ccd_remoteproc-objs := mtk_ccd.o mtk_ccd_mem.o

obj-$(CONFIG_MTK_CCD_REMOTEPROC) += mtk_ccd_remoteproc.o
