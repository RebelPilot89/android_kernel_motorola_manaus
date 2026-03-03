# SPDX-License-Identifier: GPL-2.0

ifeq ($(CONFIG_MTK_GCOV_KERNEL),y)
GCOV_PROFILE := y
endif
DSP_VERSION := hifi3_v2

# adsp include path
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/audio_ipi/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/adsp/include

# common driver
obj-$(CONFIG_SND_SOC_MEDIATEK) += snd-soc-mtk-common.o
snd-soc-mtk-common-objs += mtk-afe-platform-driver.o mtk-afe-fe-dai.o mtk-mmap-ion.o
snd-soc-mtk-common-$(CONFIG_MTK_ECCCI_DRIVER) += mtk-usip.o
snd-soc-mtk-common-$(CONFIG_SND_SOC_MTK_SRAM) += mtk-sram-manager.o
snd-soc-mtk-common-$(CONFIG_SND_SOC_MTK_SMART_PHONE) += mtk-sp-pcm-ops.o mtk-afe-debug.o

# functions for external modules; built-in when SND_SOC_MEDIATEK=y so that
# the strong register_3way_semaphore_notifier/unregister_3way_semaphore_notifier
# definitions override the __weak stubs in scp_wrapper_ipi.c at link time.
obj-$(CONFIG_SND_SOC_MEDIATEK) += mtk-afe-external.o

# speaker dynamic detect; must be built-in when SND_SOC_MEDIATEK=y so that
# mt6879-mt6368.c (and other machine drivers) can link mtk_spk_* at vmlinux
# link time rather than resolving them from a module at runtime.
obj-$(CONFIG_SND_SOC_MEDIATEK) += mtk-sp-spk-amp.o

# BT CVSD driver
obj-$(CONFIG_SND_SOC_MTK_BTCVSD) += mtk-btcvsd.o
