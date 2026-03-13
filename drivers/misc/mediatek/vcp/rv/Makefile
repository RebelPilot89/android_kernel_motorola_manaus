obj-$(CONFIG_MTK_TINYSYS_VCP_SUPPORT) += vcp_status.o

obj-$(CONFIG_MTK_TINYSYS_VCP_SUPPORT) += vcp.o
# CONFIG_MTK_TINYSYS_VCP_SUPPORT may be =m; use ifneq so source files
# are always added to the composite object when VCP support is present.
ifneq (,$(filter y m,$(CONFIG_MTK_TINYSYS_VCP_SUPPORT)))
vcp-y += vcp_helper.o
vcp-y += vcp_excep.o
vcp-y += vcp_irq.o
vcp-y += vcp_logger.o
vcp-y += vcp_l1c.o
vcp-y += vcp_vcpctl.o
vcp-y += vcp_feature_table.o
vcp-y += vcp_awake.o
endif

ccflags-y += -D DEBUG_DO
ifeq ($(CONFIG_CC_IS_GCC),y)
ccflags-y += -fno-pic -mcmodel=large
endif
ccflags-y += -I$(srctree)/drivers/misc/mediatek/vcp/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/vcp/rv
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat
ccflags-y += -I$(srctree)/drivers/clk/mediatek