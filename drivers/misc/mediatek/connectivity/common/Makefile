# drivers/misc/mediatek/connectivity/common/Makefile

obj-$(CONFIG_MTK_CONN_COMMON) += mtk_wmt_detect.o

# Sub-rutas basadas en tu árbol
CORE_DIR := common_main/core
LINUX_DIR := common_main/linux
PLAT_DIR := common_main/platform

# Objetos CORE (WMT / STP)
mtk_wmt_detect-objs := $(CORE_DIR)/wmt_core.o \
                       $(CORE_DIR)/wmt_ctrl.o \
                       $(CORE_DIR)/wmt_func.o \
                       $(CORE_DIR)/wmt_lib.o \
                       $(CORE_DIR)/wmt_conf.o \
                       $(CORE_DIR)/wmt_exp.o \
                       $(CORE_DIR)/btm_core.o \
                       $(CORE_DIR)/stp_core.o \
                       $(CORE_DIR)/stp_exp.o \
                       $(CORE_DIR)/psm_core.o

# Objetos LINUX (OSAL / Glue)
mtk_wmt_detect-objs += $(LINUX_DIR)/osal.o \
                       $(LINUX_DIR)/wmt_dev.o \
                       $(LINUX_DIR)/wmt_idc.o \
                       $(LINUX_DIR)/wmt_user_proc.o \
                       $(LINUX_DIR)/wmt_proc_dbg.o \
                       $(LINUX_DIR)/wmt_dbg.o \
                       $(LINUX_DIR)/wmt_alarm.o \
                       $(LINUX_DIR)/stp_dbg.o \
                       $(LINUX_DIR)/stp_uart.o

# OBJETOS DE PLATAFORMA (Específicos para MT6879/MT6835)
mtk_wmt_detect-objs += $(PLAT_DIR)/mtk_wcn_cmb_hw.o \
                       $(PLAT_DIR)/mtk_wcn_dump_util.o \
                       $(PLAT_DIR)/wmt_plat_alps.o \
                       $(PLAT_DIR)/wmt_plat_stub.o
ifeq (,$(filter y m,$(CONFIG_MTK_CONN_INFRA)))
mtk_wmt_detect-objs += $(PLAT_DIR)/mtk_wcn_consys_hw.o
endif

# DEBUG UTILITY
# connsys_debug_utility.o provides the common log API. When CONFIG_MTK_CONN_INFRA
# is enabled, connsyslog.o (part of conninfra) already exports the same symbols,
# so skip this file to avoid duplicate symbol link errors.
ifneq ($(CONFIG_MTK_CONN_INFRA),y)
mtk_wmt_detect-objs += debug_utility/connsys_debug_utility.o
endif
mtk_wmt_detect-objs += debug_utility/ring.o \
                       debug_utility/ring_emi.o

# Flags de compilación e Includes
ccflags-y += -DCONFIG_MTK_WCN_CORE_EN
ccflags-y += -DMTK_WCN_WMT_STP_EXP_SYMBOL_ABSTRACT
ccflags-y += -I$(srctree)/$(src)/include \
             -I$(srctree)/$(src)/common_main/include \
             -I$(srctree)/$(src)/common_main/core/include \
             -I$(srctree)/$(src)/common_main/linux/include \
             -I$(srctree)/$(src)/common_main/platform/include \
             -I$(srctree)/$(src)/common_detect \
             -I$(srctree)/drivers/misc/mediatek/include/mt-plat \
             -I$(srctree)/drivers/misc/mediatek/btif/common/inc \
             -I$(srctree)/drivers/mmc/core \
             -I$(srctree)/drivers/gpu/drm/mediatek/mediatek_v2 \
             -I$(srctree)/$(src)/debug_utility
ccflags-y += -DWMT_IDC_SUPPORT=0
ccflags-y += -DWMT_PLAT_ALPS=1
ccflags-y += -DWMT_UART_RX_MODE_WORK=0
ccflags-y += -DWMT_SDIO_MODE=0
ccflags-y += -DWMT_DBG_SUPPORT=1
ccflags-y += -DWMT_CREATE_NODE_DYNAMIC=0
