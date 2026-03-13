# Copyright (C) 2019 MediaTek Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See http://www.gnu.org/licenses/gpl-2.0.html for more details.
#
#
demo_mkp = true
ifdef demo_mkp
ccflags-y += -DDEMO_MKP
ccflags-y += -DDEBUG_MKP_ENABLED
endif

ccflags-y += -I$(src)              # needed for trace events
ccflags-y += -DTEXT_OFFSET=$(TEXT_OFFSET)
ccflags-y += -I$(srctree)/arch/arm/include/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/geniezone/public
ccflags-y += -I$(srctree)/drivers/misc/mediatek/mkp
ccflags-y += -I$(srctree)/security/selinux/include/
obj-$(CONFIG_MTK_MKP) += mkp.o
# CONFIG_MTK_MKP may be =m; use ifneq so source files are always
# added to the composite object when MKP support is present.
ifneq (,$(filter y m,$(CONFIG_MTK_MKP)))
mkp-y += mkp_main.o
mkp-y += policy.o
mkp-y += mkp_hvc.o
mkp-y += mkp_api.o
mkp-y += ksym.o
ifdef demo_mkp
mkp-y += mkp_demo.o
mkp-y += mkp_rbtree.o
mkp-y += helper.o
mkp-y += mkp_module.o
endif
mkp-y += ext/mkp_pcpu.o
endif
