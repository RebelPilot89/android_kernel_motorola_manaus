// SPDX-License-Identifier: GPL-2.0-only
extern void __flush_icache_range(unsigned long start, unsigned long end);
extern long __flush_cache_user_range(unsigned long start, unsigned long end);
extern void __flush_dcache_area(void *addr, unsigned long len);
extern void __clean_dcache_area_pou(void *addr, unsigned long len);
extern void __clean_dcache_area_poc(void *addr, unsigned long len);
extern void __clean_dcache_area_pop(void *addr, unsigned long len);
extern void __inval_dcache_area(void *addr, unsigned long len);
extern int invalidate_icache_range(unsigned long start, unsigned long end);

static inline unsigned long cache_range_size(unsigned long start,
					     unsigned long end)
{
	if (end <= start)
		return 0;
	return end - start;
}

void caches_clean_inval_pou(unsigned long start, unsigned long end)
{
	if (!cache_range_size(start, end))
		return;

	__flush_icache_range(start, end);
}

long caches_clean_inval_user_pou(unsigned long start, unsigned long end)
{
	if (!cache_range_size(start, end))
		return 0;

	return __flush_cache_user_range(start, end);
}

void icache_inval_pou(unsigned long start, unsigned long end)
{
	if (!cache_range_size(start, end))
		return;

	invalidate_icache_range(start, end);
}

void dcache_clean_inval_poc(unsigned long start, unsigned long end)
{
	unsigned long len = cache_range_size(start, end);

	if (!len)
		return;

	__flush_dcache_area((void *)start, len);
}

void dcache_inval_poc(unsigned long start, unsigned long end)
{
	unsigned long len = cache_range_size(start, end);

	if (!len)
		return;

	__inval_dcache_area((void *)start, len);
}

void dcache_clean_poc(unsigned long start, unsigned long end)
{
	unsigned long len = cache_range_size(start, end);

	if (!len)
		return;

	__clean_dcache_area_poc((void *)start, len);
}

void dcache_clean_pop(unsigned long start, unsigned long end)
{
	unsigned long len = cache_range_size(start, end);

	if (!len)
		return;

	__clean_dcache_area_pop((void *)start, len);
}

void dcache_clean_pou(unsigned long start, unsigned long end)
{
	unsigned long len = cache_range_size(start, end);

	if (!len)
		return;

	__clean_dcache_area_pou((void *)start, len);
}
