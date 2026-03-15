/* SPDX-License-Identifier: GPL-2.0 */
/*
 * musb_trace_export.h - Declarations for MUSB tracepoint wrapper functions
 *
 * These wrappers are defined in musb_trace.c and exported from musb_hdrc.ko.
 * They let consumers (e.g. musb_boost.ko) register tracepoint probes without
 * holding a direct reference to __tracepoint_musb_* data objects, which are
 * unreliable to export under CONFIG_LTO_CLANG_THIN + CONFIG_CFI_CLANG.
 *
 * Copyright (C) 2022 MediaTek Inc.
 */

#ifndef __MUSB_TRACE_EXPORT_H
#define __MUSB_TRACE_EXPORT_H

#include "musb_core.h"
#include <linux/usb.h>

int musb_trace_probe_gadget_enable(void (*fn)(void *, struct musb_ep *),
				   void *data);
int musb_trace_probe_gadget_disable(void (*fn)(void *, struct musb_ep *),
				    void *data);
int musb_trace_probe_g_giveback(void (*fn)(void *, struct musb_request *),
				void *data);
int musb_trace_probe_host_urb_giveback(void (*fn)(void *, struct urb *),
				       void *data);

#endif /* __MUSB_TRACE_EXPORT_H */
