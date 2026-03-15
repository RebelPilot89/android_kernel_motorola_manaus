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
 * Export MUSB tracepoints so that musb_boost.ko (and any other
 * out-of-tree consumer) can call register_trace_musb_*().
 *
 * Use the standard EXPORT_TRACEPOINT_SYMBOL_GPL() compound macro —
 * the same pattern used by kernel/softirq.c, kernel/time/timer.c,
 * kernel/workqueue.c etc.  It exports __tracepoint_<name>,
 * __traceiter_<name>, and the static-call key in one shot.
 */
EXPORT_TRACEPOINT_SYMBOL_GPL(musb_gadget_enable);
EXPORT_TRACEPOINT_SYMBOL_GPL(musb_gadget_disable);
EXPORT_TRACEPOINT_SYMBOL_GPL(musb_g_giveback);
EXPORT_TRACEPOINT_SYMBOL_GPL(musb_host_urb_giveback);

