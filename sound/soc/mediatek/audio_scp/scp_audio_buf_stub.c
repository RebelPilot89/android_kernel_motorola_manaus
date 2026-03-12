// SPDX-License-Identifier: GPL-2.0
/*
 * scp_audio_buf_stub.c -- SCP-specific audio buffer helpers
 *
 * Used when CONFIG_SND_SOC_MTK_AUDIO_DSP=y, which already compiles
 * audio_dsp/audio_buf.c into the kernel image and provides all shared
 * RingBuf / audiobuffer symbols via EXPORT_SYMBOL.  Compiling the full
 * scp_audio_buf.c on top of that would produce duplicate-symbol linker
 * errors (RingBuf_getDataCount, RingBuf_Reset, release_snd_dmabuffer,
 * etc. defined twice).
 *
 * This stub contains *only* the SCP-unique helper that is absent from
 * audio_dsp/audio_buf.c: dram_to_snd_dmabuffer().  Every other symbol
 * needed by the SCP audio PCM driver is satisfied by audio_buf.c.
 *
 * Copyright (c) 2018 MediaTek Inc.
 */

#include <linux/kernel.h>
#include <sound/memalloc.h>
#include "scp_audio_buf.h"

/* Map an audio_dsp_dram descriptor to a snd_dma_buffer view. */
int dram_to_snd_dmabuffer(struct audio_dsp_dram *dsp_dram,
			  struct snd_dma_buffer *dma_buffer)
{
	if (!dsp_dram)
		return -1;
	if (!dma_buffer)
		return -1;

	dma_buffer->area  = dsp_dram->vir_addr;
	dma_buffer->addr  = dsp_dram->phy_addr;
	dma_buffer->bytes = dsp_dram->size;
	return 0;
}
