/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020 Google LLC.
 * Written by David Brazdil <dbrazdil@google.com>
 *
 * Linker script used for partial linking of nVHE EL2 object files.
 */

#include <asm/hyp_image.h>
#include <asm-generic/vmlinux.lds.h>
#include <asm/cache.h>
#include <asm/memory.h>

SECTIONS {
	HYP_SECTION(.idmap.text)
	__hyp_idmap_text_start = HYP_SECTION_SYMBOL_NAME(.idmap.text);
	. = ALIGN(PAGE_SIZE);
	__hyp_idmap_text_end = .;

	HYP_SECTION(.text)
	__hyp_text_start = HYP_SECTION_SYMBOL_NAME(.text);
	. = ALIGN(PAGE_SIZE);
	__hyp_text_end = .;

	HYP_SECTION(.data..ro_after_init)
	HYP_SECTION(.rodata)
	__hyp_rodata_start = HYP_SECTION_SYMBOL_NAME(.data..ro_after_init);
	. = ALIGN(PAGE_SIZE);
	__hyp_rodata_end = .;
#ifdef CONFIG_TRACING
	. = ALIGN(PAGE_SIZE);
	__hyp_event_ids_start = .;
	HYP_SECTION(.event_ids)
	__hyp_event_ids_end = .;
#endif

	/*
	 * .hyp..data..percpu needs to be page aligned to maintain the same
	 * alignment for when linking into vmlinux.
	 */
	. = ALIGN(PAGE_SIZE);
	BEGIN_HYP_SECTION(.data..percpu)
		PERCPU_INPUT(L1_CACHE_BYTES)
	END_HYP_SECTION

	HYP_SECTION(.bss)
	__hyp_bss_start = HYP_SECTION_SYMBOL_NAME(.bss);
	. = ALIGN(PAGE_SIZE);
	__hyp_bss_end = .;

	HYP_SECTION(.data)
	__hyp_data_start = HYP_SECTION_SYMBOL_NAME(.data);
	. = ALIGN(PAGE_SIZE);
	__hyp_data_end = .;
}
