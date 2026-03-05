/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_CACHEFLUSH_H
#define _LINUX_CACHEFLUSH_H

#include <asm/cacheflush.h>

#if ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE
extern void flush_dcache_page(struct page *);

#ifndef ARCH_IMPLEMENTS_FLUSH_DCACHE_FOLIO
struct page;
static inline void flush_dcache_folio(struct page *folio)
{
	flush_dcache_page(folio);
}
#define ARCH_IMPLEMENTS_FLUSH_DCACHE_FOLIO 1
#endif

#else
struct page;
static inline void flush_dcache_folio(struct page *folio)
{
}
#define ARCH_IMPLEMENTS_FLUSH_DCACHE_FOLIO 0
#endif /* ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE */

#endif /* _LINUX_CACHEFLUSH_H */
