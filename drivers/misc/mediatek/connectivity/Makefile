# drivers/misc/mediatek/connectivity/Makefile

# Definimos la ruta base
MTK_CONN_PATH := drivers/misc/mediatek/connectivity

# 1. Infraestructura Base (Primero)
ifneq (,$(filter y m,$(CONFIG_MTK_CONN_INFRA)))
obj-$(CONFIG_MTK_CONN_INFRA)   += conninfra/
else
obj-$(CONFIG_MTK_CONN_COMMON)  += common/
endif

# 2. Power Throttling (siempre necesario con ConnInfra)
obj-$(CONFIG_MTK_CONN_INFRA)   += power_throttling/

# 3. Hardware de Radio (Front-End)
obj-$(CONFIG_MTK_CONNFEM)      += connfem/

# 4. Subsistemas de Radio (Orden de dependencia)
obj-$(CONFIG_MTK_WLAN_DEVICE)  += wlan/
obj-$(CONFIG_MTK_CONN_BT)      += bt/
obj-$(CONFIG_MTK_GPS)          += gps/
obj-$(CONFIG_MTK_FM)           += fmradio/

# Flags de compilación globales robustecidos
ccflags-y += -I$(srctree)/$(MTK_CONN_PATH)/common/include \
             -I$(srctree)/$(MTK_CONN_PATH)/common/common_main/include \
             -I$(srctree)/$(MTK_CONN_PATH)/conninfra/include \
             -DMTK_WLAN_VIRTUALIZATION_SUPPORT
