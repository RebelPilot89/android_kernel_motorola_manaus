# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2022 MediaTek Inc.

subdir-ccflags-y += -DMTK_VPU_KERNEL

ccflags-y += -I$(srctree)/drivers/remoteproc
ccflags-y += -I$(srctree)/drivers/misc/mediatek/mtk-interconnect/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/iommu
ccflags-y += -I$(srctree)/drivers/iommu/arm/arm-smmu-v3
ccflags-y += -I$(srctree)/drivers/dma-buf/heaps

obj-$(CONFIG_MTK_CCU_RPROC) += mtk_ccuv.o

mtk_ccuv-objs := mtk_ccu_isp71.o mtk_ccu_common.o mtk_ccu_ipi.o
