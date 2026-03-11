# Makefile for Focaltech V3 Touchscreen Driver (In-tree built-in)
ccflags-y += -Wall
ccflags-y += -I$(srctree)/drivers/input/touchscreen/focaltech_touch_v3
ccflags-y += -I$(srctree)/drivers/input/touchscreen/focaltech_touch_v3/include
ccflags-y += -I$(srctree)/drivers/input/touchscreen/focaltech_touch_v3/focaltech_test
ccflags-y += -I$(srctree)/drivers/input/touchscreen/touchscreen_mmi
ccflags-y += -I$(srctree)/drivers/misc/motorola/include
ccflags-y += -I$(srctree)/drivers/gpu/drm/mediatek/mediatek_v2/
ccflags-y += -DCONFIG_INPUT_TOUCHSCREEN_MMI
ccflags-y += -DCONFIG_INPUT_FOCALTECH_V3_MMI_IC_NAME_FT3681
ccflags-y += -DPRODUCT_MANAUS

obj-$(CONFIG_TOUCHSCREEN_FTS) += focaltech_v3.o

focaltech_v3-objs := \
	focaltech_core.o \
	focaltech_ex_fun.o \
	focaltech_ex_mode.o \
	focaltech_gesture.o \
	focaltech_esdcheck.o \
	focaltech_point_report_check.o \
	focaltech_flash.o \
	focaltech_spi.o \
	focaltech_ts_config.o

ifeq ($(CONFIG_INPUT_FTS_TEST_SUPPORT),y)
	ccflags-y += -DFTS_TEST_SUPPORT
	focaltech_v3-objs += focaltech_test/focaltech_test.o
	focaltech_v3-objs += focaltech_test/focaltech_test_ini.o
	focaltech_v3-objs += focaltech_test/supported_ic/focaltech_test_ft3681.o
endif

ifeq ($(CONFIG_INPUT_TOUCHSCREEN_MMI),y)
	focaltech_v3-objs += focaltech_ts_mmi.o
endif
