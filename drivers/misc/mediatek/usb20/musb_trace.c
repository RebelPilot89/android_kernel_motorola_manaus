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
 * Export individual tracepoint structs so that musb_boost.ko (and any
 * other out-of-tree consumer) can call register_trace_musb_*().
 *
 * We intentionally use per-symbol EXPORT_SYMBOL_GPL() instead of the
 * compound EXPORT_TRACEPOINT_SYMBOL_GPL() macro.  The latter also calls
 * EXPORT_STATIC_CALL_GPL(tp_func_<name>) which, on ARM64 (no
 * CONFIG_HAVE_STATIC_CALL), has been observed to silently break under
 * Clang LTO — the __SCK__tp_func_* reference can be optimised away
 * before the __ksymtab entry is emitted, leaving the tracepoint
 * invisible to modpost.  Exporting only the symbols that consumers
 * actually reference avoids the problem entirely.
 */
EXPORT_SYMBOL_GPL(__tracepoint_musb_gadget_enable);
EXPORT_SYMBOL_GPL(__tracepoint_musb_gadget_disable);
EXPORT_SYMBOL_GPL(__tracepoint_musb_g_giveback);
EXPORT_SYMBOL_GPL(__tracepoint_musb_host_urb_giveback);

