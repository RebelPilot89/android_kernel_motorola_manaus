# SPDX-License-Identifier: GPL-2.0

ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat
ccflags-y += -I$(srctree)/drivers/usb/host
ccflags-y += -I$(srctree)/drivers/usb/mtu3
ccflags-y += -I$(srctree)/drivers/misc/mediatek/usb20

ifeq ($(CONFIG_MTK_USB_BOOST),y)
ifeq ($(CONFIG_USB_MTU3),y)
obj-y += usb_boost.o
usb_boost-y := usb_boost_common.o usb_boost_plat.o
else ifeq ($(CONFIG_USB_MTK_HDRC),y)
obj-y += musb_boost.o
musb_boost-y := musb_boost_common.o usb_boost_plat.o
endif
endif
