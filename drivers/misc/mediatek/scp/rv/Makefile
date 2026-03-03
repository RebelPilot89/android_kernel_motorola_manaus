obj-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_helper.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_excep.o
# Always compile the full wrapper IPI implementation (scp_wrapper_ipi.c).
# It defines scp_mboxdev, scp_mbox_info, scp_mbox_pin_recv/send and all IPI
# registration functions needed by scp_helper.c. scp_compat_stub.c was a minimal
# stub that lacked these data definitions, causing undefined symbol errors at link time.
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_wrapper_ipi.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_irq.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_logger.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_l1c.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_scpctl.o

scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_feature_table.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_awake.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_dvfs.o
scp-$(CONFIG_MTK_TINYSYS_SCP_SUPPORT) += scp_hwvoter_dbg.o

ccflags-y += -D DEBUG_DO

ifeq ($(CONFIG_CC_IS_GCC),y)
ccflags-y += -fno-pic -mcmodel=large
endif
ccflags-y += -I$(srctree)/drivers/misc/mediatek/scp/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
ccflags-y += -I$(srctree)/drivers/clk/mediatek/
ccflags-y += -I$(srctree)/sound/soc/mediatek/common
