# Makefile for SX937X SAR sensor (In-tree built-in)
ccflags-y += -Wall
ccflags-y += -I$(srctree)/drivers/misc/motorola/sx937x
ccflags-y += -I$(srctree)/drivers/misc/motorola/include
ccflags-y += -DPRODUCT_MANAUS

obj-$(CONFIG_SX937X_MULTI) += sx937x_multi.o
sx937x_multi-objs := sx937x_multi_core.o sx937x_multi_mmi.o
