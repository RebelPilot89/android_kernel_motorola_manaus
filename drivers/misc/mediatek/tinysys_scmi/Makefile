# SPDX-License-Identifier: GPL-2.0
ifneq (,$(filter y m,$(CONFIG_MTK_TINYSYS_SCMI)))
obj-$(CONFIG_MTK_TINYSYS_SCMI) += tinysys-scmi.o
else
obj-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += tinysys-scmi.o
endif

tinysys-scmi-y := tinysys-scmi-drv.o tinysys.o


ccflags-y += -I$(srctree)/drivers/firmware/arm_scmi

ccflags-y += -DTINYSYS_SCMI_DEBUG
