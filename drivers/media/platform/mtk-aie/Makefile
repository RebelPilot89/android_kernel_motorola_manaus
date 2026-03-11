# SPDX-License-Identifier: GPL-2.0

ccflags-y += -I$(srctree)/drivers/misc/mediatek/mtk-interconnect/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/cmdq/mailbox/
ccflags-y += -I$(srctree)/drivers/dma-buf/heaps/
ccflags-y += -I$(srctree)/drivers/media/platform/mtk-isp/imgsys/
ccflags-y += -I$(srctree)/drivers/media/platform/mtk-videobuf/
ccflags-y += -I$(srctree)/drivers/iommu
ccflags-y += -I$(srctree)/drivers/misc/mediatek/iommu
ccflags-y += -I$(srctree)/include/

ifneq ($(wildcard $(srctree)/include/dt-bindings/memory/mt6897-larb-port.h),)
ccflags-y += -DAIE_TF_DUMP_7SP
endif

ifneq ($(wildcard $(srctree)/include/dt-bindings/memory/mt6989-larb-port.h),)
ccflags-y += -DAIE_TF_DUMP_7SP_1
endif

ifneq ($(wildcard $(srctree)/include/dt-bindings/memory/mt6878-larb-port.h),)
ccflags-y += -DAIE_TF_DUMP_7SP_2
endif

# Legacy ISP7 driver (ISP7)
mtk_aie-objs := \
mtk_aie_53.o \
mtk_aie_drv.o

obj-$(CONFIG_MTK_CAMERA_FD_ISP7) += mtk_aie.o

# ISP7S/ISP7SP driver (CONFIG_MTK_CAMERA_FD_ISP7S_ISP7SP)
mtk_aie_isp7s_isp7sp-objs := \
mem/aie_videobuf2-dma-contig.o \
mem/aie_videobuf2-memops.o \
mem/aie_videobuf2-vmalloc.o \
mtk_aie_53.o \
mtk_aie-trace.o \
mtk_aie_drv_isp7s.o \
mtk_aie_drv_isp7sp.o

obj-$(CONFIG_MTK_CAMERA_FD_ISP7S_ISP7SP) += mtk_aie_isp7s_isp7sp.o
obj-$(CONFIG_MTK_CAMERA_FD_ISP7S_ISP7SP) += mtk_aie_debug_7sp.o
obj-$(CONFIG_MTK_CAMERA_FD_ISP7S_ISP7SP) += mtk_aie_debug_7sp_1.o
obj-$(CONFIG_MTK_CAMERA_FD_ISP7S_ISP7SP) += mtk_aie_debug_7sp_2.o
