# Makefile for Goodix Berlin Touchscreen Driver (In-tree built-in)
ccflags-y += -Wall
ccflags-y += -I$(srctree)/drivers/input/touchscreen/goodix_brl_mmi
ccflags-y += -I$(srctree)/drivers/input/touchscreen/touchscreen_mmi
ccflags-y += -I$(srctree)/drivers/misc/motorola/include
ccflags-y += -I$(srctree)/drivers/gpu/drm/mediatek/mediatek_v2/
ccflags-y += -DCONFIG_INPUT_TOUCHSCREEN_MMI
ccflags-y += -DCONFIG_TOUCHSCREEN_GOODIX_BRL_SPI
ccflags-y += -DPRODUCT_MANAUS

obj-$(CONFIG_TOUCHSCREEN_GOODIX_BRL) += goodix_brl_mmi.o

goodix_brl_mmi-objs := \
	goodix_brl_i2c.o \
	goodix_brl_spi.o \
	goodix_ts_core.o \
	goodix_brl_hw.o \
	goodix_cfg_bin.o \
	goodix_ts_utils.o \
	goodix_brl_fwupdate.o \
	goodix_ts_inspect.o \
	goodix_ts_tools.o \
	goodix_ts_config.o

ifeq ($(CONFIG_GTP_FOD),y)
	ccflags-y += -DCONFIG_GTP_FOD
	goodix_brl_mmi-objs += goodix_ts_gesture_fod.o
else
	goodix_brl_mmi-objs += goodix_ts_gesture.o
endif

ifeq ($(CONFIG_TOUCHSCREEN_MMI),y)
	goodix_brl_mmi-objs += goodix_ts_mmi.o
endif
