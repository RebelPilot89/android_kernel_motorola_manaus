# SPDX-License-Identifier: GPL-2.0

ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat
ccflags-y += -I$(srctree)/drivers/usb/host
ccflags-y += -I$(srctree)/drivers/usb/mtu3
ccflags-y += -I$(srctree)/drivers/misc/mediatek/usb20

ifneq ($(filter y m,$(CONFIG_MTK_USB_BOOST)),)
ifeq ($(CONFIG_USB_MTU3),y)
obj-$(CONFIG_MTK_USB_BOOST) += usb_boost.o
usb_boost-y := usb_boost_common.o usb_boost_plat.o
else ifneq (,$(filter y m,$(CONFIG_USB_MTK_HDRC)))
obj-$(CONFIG_MTK_USB_BOOST) += musb_boost.o
musb_boost-y := musb_boost_common.o usb_boost_plat.o
endif
endif
