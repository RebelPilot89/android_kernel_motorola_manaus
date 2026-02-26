#ifdef CONFIG_ARM64_4K_PAGES
#define KVM_PGTABLE_MIN_BLOCK_LEVEL     1U
#else
#define KVM_PGTABLE_MIN_BLOCK_LEVEL     2U
#endif
static inline u64 kvm_granule_shift(u32 level)
{
        return ARM64_HW_PGTABLE_LEVEL_SHIFT(level);
}
static inline u64 kvm_granule_size(u32 level)
{
        return BIT(kvm_granule_shift(level));
}
