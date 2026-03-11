# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2022 MediaTek Inc.

subdir-ccflags-y += \
	-I$(srctree)/$(src) \
	-I$(srctree)/drivers/rpmsg \
	-I$(srctree)/include/

ccd_rpmsg-objs := mtk_ccd_rpmsg.o mtk_ccd_rpmsg_ipi.o

obj-$(CONFIG_RPMSG_MTK_CCD) += ccd_rpmsg.o
