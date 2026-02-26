# drivers/misc/mediatek/connectivity/bt/mt6879/Makefile

# Nombre del módulo final
obj-$(CONFIG_MTK_CONN_BT_6879) += mtk_stp_bt_6879.o

# Lista de objetos basada en tu árbol actualizado
mtk_stp_bt_6879-objs := btmtk_main.o \
                        btmtk_beif.o \
                        btmtk_beif_plat.o \
                        btmtk_btif_main.o \
                        btmtk_char_dev.o \
                        btmtk_chip_reset.o \
                        btmtk_dbg.o \
                        btmtk_dbg_tp_evt_if.o \
                        btmtk_fw_log.o \
                        btmtk_irq.o \
                        btmtk_queue.o \
                        btmtk_woble.o \
                        btmtk_mt66xx.o \
                        btmtk_buffer_mode.o \
                        bgf_csr_ops.o

# Flags de compilación para forzar BEIF y la arquitectura 6879
ccflags-y += -DCHIP_IF_BTIF
ccflags-y += -DMTK_BT_SYS_IF_BEIF
ccflags-y += -DSUPPORT_BEIF
ccflags-y += -DLOG_TAG=\"[BT_Drv][bt6879]\"

# Rutas de headers locales y del sistema common
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/conninfra/conn_drv/connv2/debug_utility
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/conninfra/conn_drv/connv2/debug_utility/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/conninfra/conn_drv/connv2/debug_utility/coredump
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/conninfra/conn_drv/connv2/debug_utility/metlog
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/common/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/bt/include/btif
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/bt/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/bt/mt6879/include
ccflags-y += -I$(srctree)/$(src)
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/conninfra/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/conninfra/platform/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/power_throttling
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/common
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/common/debug_utility
ccflags-y += -I$(srctree)/drivers/misc/mediatek/connectivity/connfem/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/btif/common/inc
ccflags-y += -I$(srctree)/drivers/gpu/drm/mediatek/mediatek_v2
ccflags-y += -DBUILD_QA_DBG=0
ccflags-y += -DDTS_REORDERED=0
ccflags-y += -DPM_QOS_CONTROL=0
ccflags-y += -DUSE_DEVICE_NODE=1
ccflags-y += -DCONNAC20_CHIPID=6879
ccflags-y += -DCFG_BT_ATF_SUPPORT=0
ccflags-y += -DBT_COREDUMP_CHECK=0
ccflags-y += -DCUSTOMER_FW_UPDATE=0
ccflags-y += -DBEIF_EMI_OFFSET=0xBA0000
ccflags-y += -DBEIF_EMI_SIZE=32768
ccflags-y += -DFW_LOG_DEFAULT_ON=0
