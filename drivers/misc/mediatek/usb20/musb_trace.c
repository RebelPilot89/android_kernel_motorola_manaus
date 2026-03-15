// SPDX-License-Identifier: GPL-2.0
/*
 * musb_trace.c - MUSB Controller Trace Support
 *
 * Copyright (C) 2022 MediaTek Inc.
 *
 */

#define CREATE_TRACE_POINTS
#include "musb_trace.h"

void musb_dbg(struct musb *musb, const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	trace_musb_log(musb, &vaf);

	va_end(args);
}

/*
 * Wrapper functions for musb_boost.ko to register/unregister MUSB tracepoint
 * probes without referencing __tracepoint_musb_* data objects directly.
 *
 * Exporting the raw tracepoint structs via EXPORT_TRACEPOINT_SYMBOL_GPL() is
 * unreliable under CONFIG_LTO_CLANG_THIN + CONFIG_CFI_CLANG.  Regular
 * EXPORT_SYMBOL_GPL on a plain C function always survives LTO linking.
 */
int musb_trace_probe_gadget_enable(void (*fn)(void *, struct musb_ep *),
				   void *data)
{
	return register_trace_musb_gadget_enable(fn, data);
}
EXPORT_SYMBOL_GPL(musb_trace_probe_gadget_enable);

int musb_trace_probe_gadget_disable(void (*fn)(void *, struct musb_ep *),
				    void *data)
{
	return register_trace_musb_gadget_disable(fn, data);
}
EXPORT_SYMBOL_GPL(musb_trace_probe_gadget_disable);

int musb_trace_probe_g_giveback(void (*fn)(void *, struct musb_request *),
				void *data)
{
	return register_trace_musb_g_giveback(fn, data);
}
EXPORT_SYMBOL_GPL(musb_trace_probe_g_giveback);

int musb_trace_probe_host_urb_giveback(void (*fn)(void *, struct urb *),
				       void *data)
{
	return register_trace_musb_host_urb_giveback(fn, data);
}
EXPORT_SYMBOL_GPL(musb_trace_probe_host_urb_giveback);

