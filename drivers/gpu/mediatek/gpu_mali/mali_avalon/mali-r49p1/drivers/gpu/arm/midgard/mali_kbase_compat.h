/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/**
 * Zero-intrusion compatibility shims for Mali r49p1 vendor helpers.
 *
 * These wrappers centralize the small `kbase_*` helpers that differ
 * between the DDK and the host kernel so the core .c files remain untouched.
 */

#ifndef _MALI_KBASE_COMPAT_H_
#define _MALI_KBASE_COMPAT_H_

#include <linux/refcount.h>
#include <linux/shrinker.h>
#include <linux/list.h>
#include <linux/page-flags.h>
#include <linux/pagemap.h>

typedef refcount_t kbase_refcount_t;

static inline void kbase_refcount_set(kbase_refcount_t *r, int v)
{
	refcount_set((refcount_t *)r, v);
}

static inline int kbase_refcount_read(const kbase_refcount_t *r)
{
	return refcount_read((const refcount_t *)r);
}

static inline bool kbase_refcount_inc_not_zero(kbase_refcount_t *r)
{
	return refcount_inc_not_zero((refcount_t *)r);
}

static inline bool kbase_refcount_dec_and_test(kbase_refcount_t *r)
{
	return refcount_dec_and_test((refcount_t *)r);
}

static inline void kbase_refcount_inc(kbase_refcount_t *r)
{
	refcount_inc((refcount_t *)r);
}

static inline void kbase_refcount_dec(kbase_refcount_t *r)
{
	refcount_dec((refcount_t *)r);
}

static inline struct folio *kbase_page_folio(struct page *page)
{
	return page_folio(page);
}

static inline struct list_head *kbase_page_lru(struct page *page)
{
	return &kbase_page_folio(page)->lru;
}

#define KBASE_PAGE_LRU(page) kbase_page_lru(page)
#define KBASE_PAGE_LRU_NEXT(page) (kbase_page_lru(page)->next)
#define KBASE_PAGE_LRU_PREV(page) (kbase_page_lru(page)->prev)

#define kbase_page_mapping(page) folio_mapping(kbase_page_folio(page))

#ifndef DEFINE_KBASE_SHRINKER
#define DEFINE_KBASE_SHRINKER struct shrinker
#endif

#endif /* _MALI_KBASE_COMPAT_H_ */