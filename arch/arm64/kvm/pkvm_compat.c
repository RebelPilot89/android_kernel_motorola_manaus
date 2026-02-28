// SPDX-License-Identifier: GPL-2.0-only

#include <linux/errno.h>
#include <linux/jump_label.h>
#include <linux/kvm_host.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

#include <asm/kvm_mmu.h>
#include <asm/kvm_pkvm.h>

int kvm_share_hyp(void *from, void *to)
{
	return 0;
}

void kvm_unshare_hyp(void *from, void *to)
{
}

void kvm_arch_free_vm(struct kvm *kvm)
{
	if (!kvm)
		return;

	if (is_vmalloc_addr(kvm))
		vfree(kvm);
	else
		kfree(kvm);
}

#ifndef CONFIG_KVM_ARM_PROTECTED_STATE
DEFINE_STATIC_KEY_FALSE(kvm_protected_mode_initialized);

int pkvm_init_host_vm(struct kvm *kvm, unsigned long type)
{
	return 0;
}

int pkvm_create_hyp_vm(struct kvm *kvm)
{
	return -ENOSYS;
}

void pkvm_destroy_hyp_vm(struct kvm *kvm)
{
}

void pkvm_host_reclaim_page(struct kvm *host_kvm, phys_addr_t ipa)
{
}

int pkvm_vm_ioctl_enable_cap(struct kvm *kvm, struct kvm_enable_cap *cap)
{
	return -ENOSYS;
}
#endif
