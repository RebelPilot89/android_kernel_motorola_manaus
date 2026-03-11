# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2022 MediaTek Inc.
# C2PS - Camera 2-Phase Scheduler for MediaTek

C2PS_TOP := $(srctree)/drivers/misc/mediatek/sched/c2ps

subdir-ccflags-y += \
	-I$(srctree)/include \
	-I$(srctree)/kernel \
	-I$(srctree)/drivers/misc/mediatek/sched/ \
	-I$(C2PS_TOP)/common/include/ \
	-I$(C2PS_TOP)/monitor/include/ \
	-I$(C2PS_TOP)/uclamp_regulator/include/

mtk_c2ps-objs += c2ps_main.o
mtk_c2ps-objs += common/src/c2ps_common.o
mtk_c2ps-objs += common/src/c2ps_sysfs.o
mtk_c2ps-objs += monitor/src/c2ps_monitor.o
mtk_c2ps-objs += uclamp_regulator/src/c2ps_uclamp_regulator.o
mtk_c2ps-objs += uclamp_regulator/src/c2ps_regulator_policy.o

obj-$(CONFIG_MTK_C2PS) += mtk_c2ps.o
