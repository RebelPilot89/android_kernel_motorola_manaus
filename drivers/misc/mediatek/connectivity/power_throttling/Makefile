# drivers/misc/mediatek/connectivity/common/power_throttling/Makefile

obj-y += mtk_pwr_throttle.o

# Consolidamos los archivos que subiste
mtk_pwr_throttle-objs := core.o \
                         adapter.o

# El test solo se compila si el debug está activo para ahorrar espacio
mtk_pwr_throttle-$(CONFIG_CONN_PWR_DEBUG) += test.o

# Flags de compilación para el MT6879
ccflags-y += -I$(srctree)/$(src)/ \
             -I$(srctree)/$(src)/../../common/include \
             -I$(srctree)/drivers/misc/mediatek/power_throttling \
             -DMTK_POWER_THROTTLING_V2
