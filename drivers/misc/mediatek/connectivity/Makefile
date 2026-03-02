# drivers/misc/mediatek/connectivity/Makefile

# Definimos la ruta base
MTK_CONN_PATH := drivers/misc/mediatek/connectivity

# 1. Infraestructura Base (Primero)
# ConnInfra y Common no son excluyentes en este árbol: múltiples símbolos
# WMT/STP exportados por common/ son consumidos por wlan/, gps/ y fmradio/
# aun cuando conninfra está habilitado.
obj-$(CONFIG_MTK_CONN_COMMON)  += common/
obj-$(CONFIG_MTK_CONN_INFRA)   += conninfra/

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
