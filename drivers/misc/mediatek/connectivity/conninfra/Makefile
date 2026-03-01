# drivers/misc/mediatek/connectivity/conninfra/Makefile

obj-$(CONFIG_MTK_CONN_INFRA) += mtk_conninfra.o

# Rutas de carpetas según tu tree
ADP  := adaptor
BASE := base
CONF := conf
DRV  := conn_drv/connv2
DRV3 := conn_drv/connv3
CONNV2_DBG  := $(DRV)/debug_utility
CMN  := ../common

# Construcción del objeto principal
mtk_conninfra-objs := $(ADP)/conninfra_dev.o \
                      $(ADP)/conn_kern_adaptor.o \
                      $(ADP)/connadp_internal.o \
                      $(ADP)/connsyslog/connsyslog_to_user.o \
                      $(ADP)/connsyslog/fw_log_mcu.o \
                      $(ADP)/coredump/conndump_netlink.o

mtk_conninfra-objs += $(BASE)/msg_thread.o \
                      $(BASE)/osal.o \
                      $(BASE)/ring.o

mtk_conninfra-objs += $(CONF)/conninfra_conf.o

# Lógica del Driver ConnV2 (Core y Platform)
mtk_conninfra-objs += $(DRV)/src/conninfra.o \
                      $(DRV)/src/connv2_drv.o \
                      $(DRV)/core/conninfra_core.o

# ConnV2 Debug Utilities
mtk_conninfra-objs += $(CONNV2_DBG)/conninfra_dbg.o \
                      $(CONNV2_DBG)/connsyslog/connsyslog.o \
                      $(CONNV2_DBG)/connsyslog/ring_emi.o \
                      $(CONNV2_DBG)/coredump/connsys_coredump.o \
                      $(CONNV2_DBG)/coredump/coredump_mng.o \
                      $(CONNV2_DBG)/metlog/metlog.o

# ConnV3 Driver
mtk_conninfra-objs += $(DRV3)/src/connv3_drv.o \
                      $(DRV3)/src/connv3.o

# Common adapters (needed when CONFIG_MTK_CONN_INFRA=y, common/ is excluded)
mtk_conninfra-objs += $(CMN)/wmt_build_in_adapter.o \
                      $(CMN)/connectivity_build_in_adapter.o \
                      $(CMN)/debug_utility/connsys_debug_utility.o

# Soporte de Plataforma (Aquí es donde entra tu hardware)
# Nota: Si tu SoC usa la carpeta mt6886, lo incluimos así:
ifeq ($(CONFIG_MTK_CONN_CONNV2_MT6886),y)
PLAT_DIR := $(DRV)/platform
mtk_conninfra-objs += $(PLAT_DIR)/consys_hw.o \
                      $(PLAT_DIR)/consys_hw_plat_data.o \
                      $(PLAT_DIR)/consys_reg_mng.o \
                      $(PLAT_DIR)/emi_mng.o \
                      $(PLAT_DIR)/clock_mng.o \
                      $(PLAT_DIR)/pmic_mng.o \
                      $(PLAT_DIR)/mt6886/mt6886.o \
                      $(PLAT_DIR)/mt6886/mt6886_ops.o \
                      $(PLAT_DIR)/mt6886/mt6886_soc.o \
                      $(PLAT_DIR)/mt6886/mt6886_emi.o \
                      $(PLAT_DIR)/mt6886/mt6886_pos.o \
                      $(PLAT_DIR)/mt6886/mt6886_pos_gen.o \
                      $(PLAT_DIR)/mt6886/mt6886_atf.o \
                      $(PLAT_DIR)/mt6886/mt6886_consys_reg.o \
                      $(PLAT_DIR)/mt6886/mt6886_consys_reg_atf.o \
                      $(PLAT_DIR)/mt6886/mt6886_debug_gen.o \
                      $(PLAT_DIR)/mt6886/mt6886_pmic.o \
                      $(PLAT_DIR)/mt6886/mt6886_coredump.o \
                      $(PLAT_DIR)/mt6886/mt6886_emi_atf.o \
                      $(PLAT_DIR)/mt6886/mt6886_coredump_atf.o
endif

# Includes Críticos
ccflags-y += -DMTK_WCN_WMT_STP_EXP_SYMBOL_ABSTRACT
ccflags-y += -DWMT_IDC_SUPPORT=0

ccflags-y += -I$(srctree)/$(src)/include \
             -I$(srctree)/$(src)/$(ADP)/include \
             -I$(srctree)/$(src)/$(ADP)/connsyslog \
             -I$(srctree)/$(src)/$(ADP)/coredump \
             -I$(srctree)/$(src)/$(BASE)/include \
             -I$(srctree)/$(src)/$(CONF)/include \
             -I$(srctree)/$(src)/$(DRV)/src \
             -I$(srctree)/$(src)/$(DRV)/core/include \
             -I$(srctree)/$(src)/$(DRV)/platform/include \
             -I$(srctree)/$(src)/$(DRV)/platform/mt6886/include \
             -I$(srctree)/$(src)/$(DRV)/debug_utility/include \
             -I$(srctree)/$(src)/$(DRV)/debug_utility/connsyslog \
             -I$(srctree)/$(src)/$(DRV)/debug_utility/coredump \
             -I$(srctree)/$(src)/$(DRV)/debug_utility/metlog \
             -I$(srctree)/$(src)/conn_drv/connv3/src \
             -I$(srctree)/$(src)/conn_drv/connv3/core/include \
             -I$(srctree)/$(src)/conn_drv/connv3/platform/include \
             -I$(srctree)/$(src)/conn_drv/connv3/debug_utility \
             -I$(srctree)/$(src)/conn_drv/connv3/debug_utility/include \
             -I$(srctree)/$(src)/../common \
             -I$(srctree)/$(src)/../common/include \
             -I$(srctree)/$(src)/../common/common_main/include \
             -I$(srctree)/$(src)/../common/common_main/linux/include \
             -I$(srctree)/$(src)/../common/common_main/platform/include \
             -I$(srctree)/$(src)/../common/debug_utility \
             -I$(srctree)/drivers/misc/mediatek/include/mt-plat \
             -I$(srctree)/drivers/misc/mediatek/modem/common/include \
             -I$(srctree)/drivers/gpu/drm/mediatek/mediatek_v2
