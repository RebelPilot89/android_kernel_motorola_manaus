# Copyright (c) 2013-2022 TRUSTONIC LIMITED
# All Rights Reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

#
# Makefile for the Kinibi core driver (backported to kernel 5.10)
#

GUD_ROOT_FOLDER := $(srctree)/drivers/tee/gud/$(CONFIG_TRUSTONIC_TEE_VERSION)

# Single in-tree module.  ARM FFA transport (CONFIG_ARM_FFA_TRANSPORT) is not
# present in 5.10 MTK; platform.h will leave MC_FFA_FASTCALL undefined and
# ffa_dummy.c compiles to empty stubs, so ffa.o is replaced by ffa_dummy.o.
obj-$(CONFIG_TRUSTONIC_TEE_SUPPORT) += mcDrvModule.o

mcDrvModule-y := \
	admin.o \
	client.o \
	clientlib.o \
	clock.o \
	fastcall.o \
	ffa_dummy.o \
	iwp.o \
	logging.o \
	main.o \
	mcp.o \
	mmu.o \
	nq.o \
	protocol.o \
	protocol_be.o \
	protocol_fe.o \
	session.o \
	teeclientapi.o \
	user.o \
	vlx_be.o \
	vlx_common.o \
	vlx_fe.o \
	xen_be.o \
	xen_common.o \
	xen_fe.o

# Support HW wrapped key mode for FBE.
mcDrvModule-$(CONFIG_FSCRYPT_WRAPED_KEY_MODE_SUPPORT) += hwkm.o

# Release mode by default
ccflags-y += -DNDEBUG
ccflags-y += -Wno-declaration-after-statement
ccflags-y += -I$(srctree)/drivers/misc/mediatek/trusted_mem/

ccflags-$(CONFIG_TRUSTONIC_TEE_DEBUG) += -DDEBUG

# MobiCore Driver includes
ccflags-y += -I$(GUD_ROOT_FOLDER)/MobiCoreDriver
