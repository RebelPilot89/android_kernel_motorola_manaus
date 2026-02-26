obj-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_helper.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_excep.o
ifeq (,$(filter y m,$(CONFIG_MTK_SCP)))
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_wrapper_ipi.o
endif
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_irq.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_logger.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_l1c.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_scpctl.o

scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_feature_table.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_awake.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_dvfs.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_hwvoter_dbg.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_compat_stub.o

ccflags-y += -D DEBUG_DO

ifeq ($(CONFIG_CC_IS_GCC),y)
ccflags-y += -fno-pic -mcmodel=large
endif
ccflags-y += -I$(srctree)/drivers/misc/mediatek/scp/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
ccflags-y += -I$(srctree)/drivers/clk/mediatek/
ccflags-y += -I$(srctree)/sound/soc/mediatek/common
