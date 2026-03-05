/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Network filesystem tracing points.
 *
 * Copyright (C) 2021 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM netfs

#if !defined(_TRACE_NETFS_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_NETFS_H

#include <linux/tracepoint.h>

/*
 * Define enums for tracing information — guarded so they're defined
 * exactly once even when the header is re-included for TRACE_HEADER_MULTI_READ.
 */
#ifndef __NETFS_DECLARE_TRACE_ENUMS_ONCE_ONLY
#define __NETFS_DECLARE_TRACE_ENUMS_ONCE_ONLY

enum netfs_rreq_ref_trace {
	netfs_rreq_trace_assess,
	netfs_rreq_trace_copy,
	netfs_rreq_trace_done,
	netfs_rreq_trace_free,
	netfs_rreq_trace_get_hold,
	netfs_rreq_trace_get_subreq,
	netfs_rreq_trace_put_complete,
	netfs_rreq_trace_put_discard,
	netfs_rreq_trace_put_failed,
	netfs_rreq_trace_put_hold,
	netfs_rreq_trace_put_subreq,
	netfs_rreq_trace_put_zero_len,
	netfs_rreq_trace_resubmit,
	netfs_rreq_trace_unlock,
};

enum netfs_sreq_ref_trace {
	netfs_sreq_trace_download_instead,
	netfs_sreq_trace_free,
	netfs_sreq_trace_get_copy_to_cache,
	netfs_sreq_trace_get_resubmit,
	netfs_sreq_trace_get_short_read,
	netfs_sreq_trace_prepare,
	netfs_sreq_trace_put_clear,
	netfs_sreq_trace_put_failed,
	netfs_sreq_trace_put_merged,
	netfs_sreq_trace_put_no_copy,
	netfs_sreq_trace_put_terminated,
	netfs_sreq_trace_resubmit_short,
	netfs_sreq_trace_submit,
	netfs_sreq_trace_terminated,
	netfs_sreq_trace_write,
	netfs_sreq_trace_write_skip,
	netfs_sreq_trace_write_term,
};

enum netfs_failure_trace {
	netfs_fail_check_write_begin,
	netfs_fail_copy_to_cache,
	netfs_fail_prepare_write,
	netfs_fail_read,
	netfs_fail_short_read,
};

enum netfs_read_trace {
	netfs_read_trace_expanded,
	netfs_read_trace_readahead,
	netfs_read_trace_readpage,
	netfs_read_trace_write_begin,
};

#endif /* __NETFS_DECLARE_TRACE_ENUMS_ONCE_ONLY */

/*
 * Export enum values for userspace tools via perf.
 */
#define netfs_rreq_ref_traces \
	EM(netfs_rreq_trace_assess,		"ASSESS  ") \
	EM(netfs_rreq_trace_copy,		"COPY    ") \
	EM(netfs_rreq_trace_done,		"DONE    ") \
	EM(netfs_rreq_trace_free,		"FREE    ") \
	EM(netfs_rreq_trace_get_hold,		"GET hold") \
	EM(netfs_rreq_trace_get_subreq,		"GET subreq") \
	EM(netfs_rreq_trace_put_complete,	"PUT complete") \
	EM(netfs_rreq_trace_put_discard,	"PUT discard") \
	EM(netfs_rreq_trace_put_failed,		"PUT failed") \
	EM(netfs_rreq_trace_put_hold,		"PUT hold") \
	EM(netfs_rreq_trace_put_subreq,		"PUT subreq") \
	EM(netfs_rreq_trace_put_zero_len,	"PUT zero") \
	EM(netfs_rreq_trace_resubmit,		"RESUBMIT") \
	E_(netfs_rreq_trace_unlock,		"UNLOCK  ")

#define netfs_sreq_ref_traces \
	EM(netfs_sreq_trace_download_instead,	"DL instead") \
	EM(netfs_sreq_trace_free,		"FREE      ") \
	EM(netfs_sreq_trace_get_copy_to_cache,	"GET copy  ") \
	EM(netfs_sreq_trace_get_resubmit,	"GET resubm") \
	EM(netfs_sreq_trace_get_short_read,	"GET short ") \
	EM(netfs_sreq_trace_prepare,		"PREPARE   ") \
	EM(netfs_sreq_trace_put_clear,		"PUT clear ") \
	EM(netfs_sreq_trace_put_failed,		"PUT failed") \
	EM(netfs_sreq_trace_put_merged,		"PUT merged") \
	EM(netfs_sreq_trace_put_no_copy,	"PUT nocopy") \
	EM(netfs_sreq_trace_put_terminated,	"PUT term  ") \
	EM(netfs_sreq_trace_resubmit_short,	"RESUBMIT  ") \
	EM(netfs_sreq_trace_submit,		"SUBMIT    ") \
	EM(netfs_sreq_trace_terminated,		"TERM      ") \
	EM(netfs_sreq_trace_write,		"WRITE     ") \
	EM(netfs_sreq_trace_write_skip,		"WRITESKIP ") \
	E_(netfs_sreq_trace_write_term,		"WRITETERM ")

#define netfs_failure_traces \
	EM(netfs_fail_check_write_begin,	"chk-wr-beg") \
	EM(netfs_fail_copy_to_cache,		"copy2cache") \
	EM(netfs_fail_prepare_write,		"prep-write") \
	EM(netfs_fail_read,			"read      ") \
	E_(netfs_fail_short_read,		"short-read")

#define netfs_read_traces \
	EM(netfs_read_trace_expanded,		"EXPANDED  ") \
	EM(netfs_read_trace_readahead,		"READAHEAD ") \
	EM(netfs_read_trace_readpage,		"READPAGE  ") \
	E_(netfs_read_trace_write_begin,	"WRITEBEG  ")

#undef EM
#undef E_
#define EM(a, b)	TRACE_DEFINE_ENUM(a);
#define E_(a, b)	TRACE_DEFINE_ENUM(a);

netfs_rreq_ref_traces;
netfs_sreq_ref_traces;
netfs_failure_traces;
netfs_read_traces;

#undef EM
#undef E_
#define EM(a, b)	{ a, b },
#define E_(a, b)	{ a, b }

TRACE_EVENT(netfs_rreq,
	    TP_PROTO(struct netfs_io_request *rreq, enum netfs_rreq_ref_trace what),
	    TP_ARGS(rreq, what),
	    TP_STRUCT__entry(
		    __field(unsigned int,		rreq	)
		    __field(enum netfs_rreq_ref_trace,	what	)
		    ),
	    TP_fast_assign(
		    __entry->rreq = rreq->debug_id;
		    __entry->what = what;
		    ),
	    TP_printk("R=%08x %s",
		      __entry->rreq,
		      __print_symbolic(__entry->what, netfs_rreq_ref_traces))
	    );

TRACE_EVENT(netfs_sreq,
	    TP_PROTO(struct netfs_io_subrequest *subreq, enum netfs_sreq_ref_trace what),
	    TP_ARGS(subreq, what),
	    TP_STRUCT__entry(
		    __field(unsigned int,		rreq	)
		    __field(unsigned short,		index	)
		    __field(enum netfs_sreq_ref_trace,	what	)
		    ),
	    TP_fast_assign(
		    __entry->rreq  = subreq->rreq->debug_id;
		    __entry->index = subreq->debug_index;
		    __entry->what  = what;
		    ),
	    TP_printk("R=%08x[%x] %s",
		      __entry->rreq, __entry->index,
		      __print_symbolic(__entry->what, netfs_sreq_ref_traces))
	    );

TRACE_EVENT(netfs_failure,
	    TP_PROTO(struct netfs_io_request *rreq, struct netfs_io_subrequest *subreq,
		     int error, enum netfs_failure_trace what),
	    TP_ARGS(rreq, subreq, error, what),
	    TP_STRUCT__entry(
		    __field(unsigned int,		rreq	)
		    __field(unsigned short,		index	)
		    __field(int,			error	)
		    __field(enum netfs_failure_trace,	what	)
		    ),
	    TP_fast_assign(
		    __entry->rreq  = rreq ? rreq->debug_id : 0;
		    __entry->index = subreq ? subreq->debug_index : 0;
		    __entry->error = error;
		    __entry->what  = what;
		    ),
	    TP_printk("R=%08x[%x] %s e=%d",
		      __entry->rreq, __entry->index,
		      __print_symbolic(__entry->what, netfs_failure_traces),
		      __entry->error)
	    );

TRACE_EVENT(netfs_read,
	    TP_PROTO(struct netfs_io_request *rreq, loff_t start, size_t len,
		     enum netfs_read_trace what),
	    TP_ARGS(rreq, start, len, what),
	    TP_STRUCT__entry(
		    __field(unsigned int,		rreq	)
		    __field(loff_t,			start	)
		    __field(size_t,			len	)
		    __field(enum netfs_read_trace,	what	)
		    ),
	    TP_fast_assign(
		    __entry->rreq  = rreq->debug_id;
		    __entry->start = start;
		    __entry->len   = len;
		    __entry->what  = what;
		    ),
	    TP_printk("R=%08x %s s=%llx %zx",
		      __entry->rreq,
		      __print_symbolic(__entry->what, netfs_read_traces),
		      __entry->start, __entry->len)
	    );

TRACE_EVENT(netfs_rreq_ref,
	    TP_PROTO(unsigned int rreq_debug_id, int ref, enum netfs_rreq_ref_trace what),
	    TP_ARGS(rreq_debug_id, ref, what),
	    TP_STRUCT__entry(
		    __field(unsigned int,		rreq	)
		    __field(int,			ref	)
		    __field(enum netfs_rreq_ref_trace,	what	)
		    ),
	    TP_fast_assign(
		    __entry->rreq = rreq_debug_id;
		    __entry->ref  = ref;
		    __entry->what = what;
		    ),
	    TP_printk("R=%08x %s r=%d",
		      __entry->rreq,
		      __print_symbolic(__entry->what, netfs_rreq_ref_traces),
		      __entry->ref)
	    );

TRACE_EVENT(netfs_sreq_ref,
	    TP_PROTO(unsigned int rreq_debug_id, unsigned int subreq_debug_index,
		     int ref, enum netfs_sreq_ref_trace what),
	    TP_ARGS(rreq_debug_id, subreq_debug_index, ref, what),
	    TP_STRUCT__entry(
		    __field(unsigned int,		rreq	)
		    __field(unsigned int,		index	)
		    __field(int,			ref	)
		    __field(enum netfs_sreq_ref_trace,	what	)
		    ),
	    TP_fast_assign(
		    __entry->rreq  = rreq_debug_id;
		    __entry->index = subreq_debug_index;
		    __entry->ref   = ref;
		    __entry->what  = what;
		    ),
	    TP_printk("R=%08x[%x] %s r=%d",
		      __entry->rreq, __entry->index,
		      __print_symbolic(__entry->what, netfs_sreq_ref_traces),
		      __entry->ref)
	    );

#undef EM
#undef E_

#endif /* _TRACE_NETFS_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
