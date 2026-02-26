/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Code copied from arch/arm64/mm/cache.S.
 */

#include <linux/linkage.h>
#include <asm/assembler.h>
#include <asm/alternative.h>

SYM_FUNC_START(__pi_dcache_clean_inval_poc)
	dcache_by_line_op civac, sy, x0, x1, x2, x3
	ret
SYM_FUNC_END(__pi_dcache_clean_inval_poc)

SYM_FUNC_START(dcache_clean_inval_poc)
	b	__pi_dcache_clean_inval_poc
SYM_FUNC_END(dcache_clean_inval_poc)

SYM_FUNC_START(__pi_icache_inval_pou)
alternative_if ARM64_HAS_CACHE_DIC
	isb
	ret
alternative_else_nop_endif

	invalidate_icache_by_line x0, x1, x2, x3, 9998f

9998:
	ret
SYM_FUNC_END(__pi_icache_inval_pou)

SYM_FUNC_START(icache_inval_pou)
	b	__pi_icache_inval_pou
SYM_FUNC_END(icache_inval_pou)
