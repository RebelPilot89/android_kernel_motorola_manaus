# Makefile for DRV2624 Haptic Driver (In-tree built-in)
ccflags-y += -Wall
ccflags-y += -I$(srctree)/drivers/misc/motorola/drv2624_mmi
ccflags-y += -I$(srctree)/drivers/misc/motorola/include
ccflags-y += -DPRODUCT_MANAUS

obj-$(CONFIG_INPUT_DRV2624_MMI) += drv2624_mmi.o
