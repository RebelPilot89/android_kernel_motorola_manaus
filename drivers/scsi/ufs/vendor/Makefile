# SPDX-License-Identifier: GPL-2.0
# Mediatek UFS extended features makefile

ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/
ccflags-y += -I$(srctree)/drivers/scsi/ufs/
ifneq ($(filter y m, $(CONFIG_TRUSTONIC_TEE_SUPPORT)),)
include $(srctree)/drivers/tee/gud/Makefile.include
endif

obj-$(CONFIG_SCSI_UFS_MEDIATEK) += ufs-mediatek-mod.o
ufs-mediatek-mod-y := ../ufs-mediatek.o
ufs-mediatek-mod-$(CONFIG_UFSFEATURE) += ufsfeature.o ufsfeature-mimic.o
ufs-mediatek-mod-$(CONFIG_UFSSHPB) += ufsshpb.o
ufs-mediatek-mod-$(CONFIG_UFSTW) += ufstw.o
ufs-mediatek-mod-$(CONFIG_UFSHID) += ufshid.o
ufs-mediatek-mod-$(CONFIG_SCSI_SKHID) += ufs-manual-gc.o
ufs-mediatek-mod-$(CONFIG_UFSRINGBUF) += ufsringbuf.o
ufs-mediatek-mod-$(CONFIG_SCSI_UFS_CRYPTO) += ../ufshcd-moto-crypto.o
# ufshcd-moto-crypto.c is also needed when fscrypt wrapped-key mode is enabled
# (CONFIG_FSCRYPT_WRAPED_KEY_MODE_SUPPORT), even when the generic
# CONFIG_SCSI_UFS_CRYPTO path is not active (requires BLK_INLINE_ENCRYPTION).
ifeq ($(CONFIG_FSCRYPT_WRAPED_KEY_MODE_SUPPORT),y)
ifneq ($(CONFIG_SCSI_UFS_CRYPTO),y)
ufs-mediatek-mod-y += ../ufshcd-moto-crypto.o
endif
endif
