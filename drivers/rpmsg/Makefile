# SPDX-License-Identifier: GPL-2.0
obj-y			+= rpmsg_core.o
obj-$(CONFIG_RPMSG_CHAR)	+= rpmsg_char.o
ifeq ($(CONFIG_RPMSG_MTK_CCD),)
obj-$(CONFIG_RPMSG_MTK_SCP)	+= mtk_rpmsg.o
endif
qcom_glink-objs			:= qcom_glink_native.o qcom_glink_ssr.o
obj-$(CONFIG_RPMSG_QCOM_GLINK) += qcom_glink.o
obj-$(CONFIG_RPMSG_MTK)	+= mtk_rpmsg_mbox.o
ccd_rpmsg-objs			:= mtk_ccd_rpmsg.o mtk_ccd_rpmsg_ipi.o
obj-$(CONFIG_RPMSG_MTK_CCD)	+= ccd_rpmsg.o
obj-$(CONFIG_RPMSG_QCOM_GLINK_RPM) += qcom_glink_rpm.o
obj-$(CONFIG_RPMSG_QCOM_GLINK_SMEM) += qcom_glink_smem.o
obj-$(CONFIG_RPMSG_QCOM_SMD)	+= qcom_smd.o
obj-$(CONFIG_RPMSG_VIRTIO)	+= virtio_rpmsg_bus.o
