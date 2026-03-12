#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

# MTK Platform Support

# scp audio include path
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/audio_ipi/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/scp/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/scp/rv

# platform include path
subdir-ccflags-y += -I$(srctree)/sound/soc/mediatek/common

# object code
mtk-scp-audiocommon-objs := scp_audio_ipi.o audio_mbox.o
obj-$(CONFIG_MTK_SCP_AUDIO) += mtk-scp-audiocommon.o
# When CONFIG_SND_SOC_MTK_AUDIO_DSP is enabled, audio_dsp/audio_buf.c is
# already compiled into the kernel and exports all shared RingBuf symbols
# (RingBuf_getDataCount, RingBuf_Reset, release_snd_dmabuffer, etc.).
# Using the full scp_audio_buf.o on top of that causes duplicate-symbol
# linker errors.  Use the minimal stub instead so that only the
# SCP-unique dram_to_snd_dmabuffer() helper is compiled a second time.
# Long-term: factor the shared RingBuf primitives into a common library
# (e.g., sound/soc/mediatek/common/audio_ringbuf.c) so both subsystems
# can link against a single copy without conditional compilation.
ifeq ($(CONFIG_SND_SOC_MTK_AUDIO_DSP),y)
mtk-scp-audio-objs := scp_audio_buf_stub.o mtk-scp-audio-driver.o mtk-scp-audio-pcm.o mtk-scp-audio-mem-control.o
else
mtk-scp-audio-objs := scp_audio_buf.o mtk-scp-audio-driver.o mtk-scp-audio-pcm.o mtk-scp-audio-mem-control.o
endif
obj-$(CONFIG_MTK_SCP_AUDIO) += mtk-scp-audio.o
