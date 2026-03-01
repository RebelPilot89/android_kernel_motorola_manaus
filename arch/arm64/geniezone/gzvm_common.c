// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2023 MediaTek Inc.
 *
 * Common GenieZone VM driver helpers.
 */

#include <linux/errno.h>
#include <linux/gzvm_drv.h>
#include <linux/mm.h>

/**
 * gzvm_err_to_errno() - Translate a GenieZone hypervisor error to Linux errno.
 * @err: Error code returned by the hypervisor (unsigned long).
 *
 * Return: Corresponding negative Linux errno, or 0 on success.
 */
int gzvm_err_to_errno(unsigned long err)
{
	int ret = (int)err;

	if (!ret)
		return 0;

	switch (ret) {
	case ERR_NO_MEMORY:
		return -ENOMEM;
	case ERR_INVALID_ARGS:
		return -EINVAL;
	case ERR_NOT_SUPPORTED:
		return -EOPNOTSUPP;
	case ERR_NOT_IMPLEMENTED:
		return -ENOSYS;
	case ERR_FAULT:
		return -EFAULT;
	default:
		break;
	}

	return -EINVAL;
}

/**
 * gzvm_gfn_to_hva_memslot() - Convert guest frame number to host virtual address.
 * @memslot: Pointer to the memory slot.
 * @gfn:     Guest frame number.
 *
 * Return: Host virtual address corresponding to the given gfn, or 0 on error.
 */
u64 gzvm_gfn_to_hva_memslot(struct gzvm_memslot *memslot, u64 gfn)
{
	u64 offset;

	if (!memslot || gfn < memslot->base_gfn)
		return 0;

	offset = gfn - memslot->base_gfn;
	if (offset >= memslot->npages)
		return 0;

	return memslot->userspace_addr + (offset << PAGE_SHIFT);
}

/**
 * gzvm_gfn_to_pfn_memslot() - Convert guest frame number to host physical frame number.
 * @memslot: Pointer to the memory slot descriptor.
 * @gfn:     Guest frame number to translate.
 * @pfn:     Output pointer for the resulting host physical frame number.
 *
 * Return: 0 on success, negative errno on failure.
 */
int gzvm_gfn_to_pfn_memslot(struct gzvm_memslot *memslot, u64 gfn, u64 *pfn)
{
	u64 hva;
	u64 pa;

	hva = gzvm_gfn_to_hva_memslot(memslot, gfn);
	if (!hva)
		return -EINVAL;

	pa = gzvm_hva_to_pa_arch(hva);
	if (pa == GZVM_PA_ERR_BAD)
		return -EFAULT;

	*pfn = pa >> PAGE_SHIFT;
	return 0;
}
