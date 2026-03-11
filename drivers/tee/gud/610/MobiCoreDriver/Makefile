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

# Single in-tree module.  When CONFIG_ARM_FFA_TRANSPORT is enabled the real
# ffa.c is compiled (MC_FFA_FASTCALL becomes active via platform.h /
# IS_REACHABLE); otherwise ffa_dummy.c provides empty stubs.
obj-$(CONFIG_TRUSTONIC_TEE_SUPPORT) += mcDrvModule.o

mcDrvModule-y := \
	admin.o \
	client.o \
	clientlib.o \
	clock.o \
	fastcall.o \
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
	xen_fe.o \
	raite_be.o \
	raite_common.o \
	raite_fe.o

# FFA backend: use the real implementation when ARM FFA transport is present
ifneq ($(filter y m,$(CONFIG_ARM_FFA_TRANSPORT)),)
mcDrvModule-y += ffa.o
else
mcDrvModule-y += ffa_dummy.o
endif

# Hardware Key Manager (HWKM): TEE-backed wrapped-key operations used by
# the UFS inline crypto driver (ufshcd-moto-crypto.c).
mcDrvModule-y += hwkm.o

# Release mode by default
ccflags-y += -DNDEBUG
ccflags-y += -Wno-declaration-after-statement
ccflags-y += -I$(srctree)/drivers/misc/mediatek/trusted_mem/
ccflags-y += -DMTK_ADAPTED

ccflags-$(CONFIG_TRUSTONIC_TEE_DEBUG) += -DDEBUG

# MobiCore Driver includes
ccflags-y += -I$(GUD_ROOT_FOLDER)/MobiCoreDriver
