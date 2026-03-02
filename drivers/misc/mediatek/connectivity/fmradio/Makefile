# drivers/misc/mediatek/connectivity/fmradio/Makefile

obj-$(CONFIG_MTK_FM) += mtk_fm_drv.o

# Core del Driver
mtk_fm_drv-objs := core/fm_main.o \
                   core/fm_config.o \
                   core/fm_module.o \
                   core/fm_utils.o \
                   core/fm_cmd.o \
                   core/fm_link.o \
                   core/fm_rds_parser.o \
                   core/fm_eint.o \
                   core/fm_patch.o \
                   core/fm_reg_utils.o

# Platform interface (conn_infra for CONNAC2X)
mtk_fm_drv-$(CONFIG_MTK_FM_CHIP_CONNAC2X) += plat/conn_infra.o

# MT6635 chip RDS ops (mt6635_fm_rds_ops_register/unregister called by conn_infra.c)
mtk_fm_drv-$(CONFIG_MTK_FM_CHIP_CONNAC2X) += chips/mt6635/pub/mt6635_fm_rds.o
mtk_fm_drv-$(CONFIG_MTK_FM_CHIP_CONNAC2X) += chips/mt6635/pub/mt6635_fm_lib.o

# Soporte específico para MT6879 (CONNAC2X)
mtk_fm_drv-$(CONFIG_MTK_FM_CHIP_CONNAC2X) += chips/connac2x/pub/connac2x_fm_lib.o

# Headers - propagados a todo el subárbol fmradio (chips/core/plat)
subdir-ccflags-y += -I$(srctree)/$(src)/inc \
                    -I$(srctree)/$(src)/core/inc \
                    -I$(srctree)/$(src)/plat/inc \
                    -I$(srctree)/$(src)/chips/connac2x/inc \
                    -I$(srctree)/$(src)/chips/mt6635/inc \
                    -I$(srctree)/$(src)/../conninfra/include \
                    -I$(srctree)/$(src)/../common/include \
                    -I$(srctree)/$(src)/../common/common_main/include \
                    -I$(srctree)/$(src)/../common/common_main/linux/include \
                    -I$(srctree)/drivers/misc/mediatek/include/mt-plat

subdir-ccflags-y += -DMTK_WCN_WMT_STP_EXP_SYMBOL_ABSTRACT
subdir-ccflags-y += -DWMT_IDC_SUPPORT=0

# Flags de robustecimiento
ccflags-y += -DMTK_FM_CONNAC2X_SUPPORT
ccflags-y += -DCFG_FM_CONNAC2=1
