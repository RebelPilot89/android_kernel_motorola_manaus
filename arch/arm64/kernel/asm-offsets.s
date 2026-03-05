	.text
	.section	.note.gnu.property,"a",@note
	.p2align	3, 0x0
	.word	4
	.word	16
	.word	5
	.asciz	"GNU"
	.word	3221225472
	.word	4
	.word	3
	.word	0
.Lsec_end0:
	.text
	.file	"asm-offsets.c"
                                        // Start of file scope inline assembly
.set __SYSREG_MRSMSR_S_DEFINED, 1
.set __sysreg_gpr_x0, 0
.set __sysreg_gpr_x1, 1
.set __sysreg_gpr_x2, 2
.set __sysreg_gpr_x3, 3
.set __sysreg_gpr_x4, 4
.set __sysreg_gpr_x5, 5
.set __sysreg_gpr_x6, 6
.set __sysreg_gpr_x7, 7
.set __sysreg_gpr_x8, 8
.set __sysreg_gpr_x9, 9
.set __sysreg_gpr_x10, 10
.set __sysreg_gpr_x11, 11
.set __sysreg_gpr_x12, 12
.set __sysreg_gpr_x13, 13
.set __sysreg_gpr_x14, 14
.set __sysreg_gpr_x15, 15
.set __sysreg_gpr_x16, 16
.set __sysreg_gpr_x17, 17
.set __sysreg_gpr_x18, 18
.set __sysreg_gpr_x19, 19
.set __sysreg_gpr_x20, 20
.set __sysreg_gpr_x21, 21
.set __sysreg_gpr_x22, 22
.set __sysreg_gpr_x23, 23
.set __sysreg_gpr_x24, 24
.set __sysreg_gpr_x25, 25
.set __sysreg_gpr_x26, 26
.set __sysreg_gpr_x27, 27
.set __sysreg_gpr_x28, 28
.set __sysreg_gpr_x29, 29
.set __sysreg_gpr_x30, 30
.set __sysreg_gpr_xzr, 31


.set __SYSREG_S_EQU_DEFINED, 1
.set SYS_SPSR_EL2, 57856
.set SYS_SPSR_EL1, 49664
.set SYS_ESR_EL2, 58000
.set SYS_ESR_EL1, 49808
.set SYS_ELR_EL2, 57857
.set SYS_ELR_EL1, 49665
.set SYS_VSESR_EL2, 58003
.set SYS_SCTLR_EL12, 59520
.set SYS_TCR_EL12, 59650
.set SYS_AFSR0_EL12, 60040
.set SYS_AFSR1_EL12, 60041
.set SYS_ESR_EL12, 60048
.set SYS_ELR_EL12, 59905
.set SYS_TTBR0_EL12, 59648
.set SYS_TTBR1_EL12, 59649
.set SYS_MAIR_EL12, 60688
.set SYS_AMAIR_EL12, 60696
.set SYS_SCTLR_EL2, 57472
.set SYS_ICH_VTR_EL2, 58969
.set SYS_CNTV_CTL_EL0, 57113
.set SYS_CNTV_CVAL_EL0, 57114
.set SYS_CNTV_CTL_EL02, 61209
.set SYS_CNTV_CVAL_EL02, 61210
.set SYS_ICH_HCR_EL2, 58968
.set SYS_ICH_ELRSR_EL2, 58973
.set SYS_ICH_LR0_EL2, 58976
.set SYS_ICH_LR1_EL2, 58977
.set SYS_ICH_LR2_EL2, 58978
.set SYS_ICH_LR3_EL2, 58979
.set SYS_ICH_LR4_EL2, 58980
.set SYS_ICH_LR5_EL2, 58981
.set SYS_ICH_LR6_EL2, 58982
.set SYS_ICH_LR7_EL2, 58983
.set SYS_ICH_LR8_EL2, 58984
.set SYS_ICH_LR9_EL2, 58985
.set SYS_ICH_LR10_EL2, 58986
.set SYS_ICH_LR11_EL2, 58987
.set SYS_ICH_LR12_EL2, 58988
.set SYS_ICH_LR13_EL2, 58989
.set SYS_ICH_LR14_EL2, 58990
.set SYS_ICH_LR15_EL2, 58991
.set SYS_SCTLR_EL1, 49280
.set SYS_CPACR_EL1, 49282
.set SYS_TTBR0_EL1, 49408
.set SYS_TTBR1_EL1, 49409
.set SYS_TCR_EL1, 49410
.set SYS_AFSR0_EL1, 49800
.set SYS_AFSR1_EL1, 49801
.set SYS_FAR_EL1, 49920
.set SYS_MAIR_EL1, 50448
.set SYS_VBAR_EL1, 50688
.set SYS_CONTEXTIDR_EL1, 50817
.set SYS_AMAIR_EL1, 50456
.set SYS_CNTKCTL_EL1, 50952
.set SYS_TFSR_EL1, 49840
.set SYS_ZCR_EL1, 49296
.set SYS_ZCR_EL2, 57488
.set SYS_CPACR_EL12, 59522
.set SYS_FAR_EL12, 60160
.set SYS_VBAR_EL12, 60928
.set SYS_CNTKCTL_EL12, 61192
.set SYS_TFSR_EL12, 60080
.set SYS_ZCR_EL12, 59536
.set SYS_SPSR_EL12, 59904
.set SYS_TRBLIMITR_EL1, 50392
.set SYS_TRFCR_EL1, 49297
.set SYS_ICH_AP0R0_EL2, 58948
.set SYS_ICH_AP0R1_EL2, 58949
.set SYS_ICH_AP0R2_EL2, 58950
.set SYS_ICH_AP0R3_EL2, 58951
.set SYS_ICH_AP1R0_EL2, 58952
.set SYS_ICH_AP1R1_EL2, 58953
.set SYS_ICH_AP1R2_EL2, 58954
.set SYS_ICH_AP1R3_EL2, 58955
.set SYS_TPIDR_EL0, 56962
.set SYS_TPIDRRO_EL0, 56963

                                        // End of file scope inline assembly
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
// %bb.0:
	hint	#25
	//APP

	.ascii	"->TSK_ACTIVE_MM 1224 offsetof(struct task_struct, active_mm)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->TSK_TI_FLAGS 0 offsetof(struct task_struct, thread_info.flags)"
	//NO_APP
	//APP

	.ascii	"->TSK_TI_PREEMPT 16 offsetof(struct task_struct, thread_info.preempt_count)"
	//NO_APP
	//APP

	.ascii	"->TSK_TI_ADDR_LIMIT 8 offsetof(struct task_struct, thread_info .addr_limit)"
	//NO_APP
	//APP

	.ascii	"->TSK_TI_CPU 40 offsetof(struct task_struct, thread_info.cpu)"
	//NO_APP
	//APP

	.ascii	"->TSK_SCS_BASE 64 offsetof(struct task_struct, scs_base)"
	//NO_APP
	//APP

	.ascii	"->TSK_TI_SCS_BASE 24 offsetof(struct task_struct, thread_info.scs_base)"
	//NO_APP
	//APP

	.ascii	"->TSK_TI_SCS_SP 32 offsetof(struct task_struct, thread_info.scs_sp)"
	//NO_APP
	//APP

	.ascii	"->TSK_STACK 56 offsetof(struct task_struct, stack)"
	//NO_APP
	//APP

	.ascii	"->TSK_STACK_CANARY 1400 offsetof(struct task_struct, stack_canary)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->THREAD_CPU_CONTEXT 3664 offsetof(struct task_struct, thread.cpu_context)"
	//NO_APP
	//APP

	.ascii	"->THREAD_SCTLR_USER 4744 offsetof(struct task_struct, thread.sctlr_user)"
	//NO_APP
	//APP

	.ascii	"->THREAD_KEYS_USER 4640 offsetof(struct task_struct, thread.keys_user)"
	//NO_APP
	//APP

	.ascii	"->THREAD_KEYS_KERNEL 4720 offsetof(struct task_struct, thread.keys_kernel)"
	//NO_APP
	//APP

	.ascii	"->THREAD_MTE_CTRL 4736 offsetof(struct task_struct, thread.mte_ctrl)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->S_X0 0 offsetof(struct pt_regs, regs[0])"
	//NO_APP
	//APP

	.ascii	"->S_X2 16 offsetof(struct pt_regs, regs[2])"
	//NO_APP
	//APP

	.ascii	"->S_X4 32 offsetof(struct pt_regs, regs[4])"
	//NO_APP
	//APP

	.ascii	"->S_X6 48 offsetof(struct pt_regs, regs[6])"
	//NO_APP
	//APP

	.ascii	"->S_X8 64 offsetof(struct pt_regs, regs[8])"
	//NO_APP
	//APP

	.ascii	"->S_X10 80 offsetof(struct pt_regs, regs[10])"
	//NO_APP
	//APP

	.ascii	"->S_X12 96 offsetof(struct pt_regs, regs[12])"
	//NO_APP
	//APP

	.ascii	"->S_X14 112 offsetof(struct pt_regs, regs[14])"
	//NO_APP
	//APP

	.ascii	"->S_X16 128 offsetof(struct pt_regs, regs[16])"
	//NO_APP
	//APP

	.ascii	"->S_X18 144 offsetof(struct pt_regs, regs[18])"
	//NO_APP
	//APP

	.ascii	"->S_X20 160 offsetof(struct pt_regs, regs[20])"
	//NO_APP
	//APP

	.ascii	"->S_X22 176 offsetof(struct pt_regs, regs[22])"
	//NO_APP
	//APP

	.ascii	"->S_X24 192 offsetof(struct pt_regs, regs[24])"
	//NO_APP
	//APP

	.ascii	"->S_X26 208 offsetof(struct pt_regs, regs[26])"
	//NO_APP
	//APP

	.ascii	"->S_X28 224 offsetof(struct pt_regs, regs[28])"
	//NO_APP
	//APP

	.ascii	"->S_FP 232 offsetof(struct pt_regs, regs[29])"
	//NO_APP
	//APP

	.ascii	"->S_LR 240 offsetof(struct pt_regs, regs[30])"
	//NO_APP
	//APP

	.ascii	"->S_SP 248 offsetof(struct pt_regs, sp)"
	//NO_APP
	//APP

	.ascii	"->S_PSTATE 264 offsetof(struct pt_regs, pstate)"
	//NO_APP
	//APP

	.ascii	"->S_PC 256 offsetof(struct pt_regs, pc)"
	//NO_APP
	//APP

	.ascii	"->S_SYSCALLNO 280 offsetof(struct pt_regs, syscallno)"
	//NO_APP
	//APP

	.ascii	"->S_ORIG_ADDR_LIMIT 288 offsetof(struct pt_regs, orig_addr_limit)"
	//NO_APP
	//APP

	.ascii	"->S_PMR_SAVE 296 offsetof(struct pt_regs, pmr_save)"
	//NO_APP
	//APP

	.ascii	"->S_STACKFRAME 304 offsetof(struct pt_regs, stackframe)"
	//NO_APP
	//APP

	.ascii	"->S_FRAME_SIZE 336 sizeof(struct pt_regs)"
	//NO_APP
	//APP

	.ascii	"->PT_REGS_SIZE 336 sizeof(struct pt_regs)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->COMPAT_SIGFRAME_REGS_OFFSET 32 offsetof(struct compat_sigframe, uc.uc_mcontext.arm_r0)"
	//NO_APP
	//APP

	.ascii	"->COMPAT_RT_SIGFRAME_REGS_OFFSET 160 offsetof(struct compat_rt_sigframe, sig.uc.uc_mcontext.arm_r0)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->MM_CONTEXT_ID 760 offsetof(struct mm_struct, context.id.counter)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->VMA_VM_MM 64 offsetof(struct vm_area_struct, vm_mm)"
	//NO_APP
	//APP

	.ascii	"->VMA_VM_FLAGS 80 offsetof(struct vm_area_struct, vm_flags)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->VM_EXEC 4 VM_EXEC"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->PAGE_SZ 4096 PAGE_SIZE"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->DMA_TO_DEVICE 1 DMA_TO_DEVICE"
	//NO_APP
	//APP

	.ascii	"->DMA_FROM_DEVICE 2 DMA_FROM_DEVICE"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->PREEMPT_DISABLE_OFFSET 1 PREEMPT_DISABLE_OFFSET"
	//NO_APP
	//APP

	.ascii	"->SOFTIRQ_SHIFT 8 SOFTIRQ_SHIFT"
	//NO_APP
	//APP

	.ascii	"->IRQ_CPUSTAT_SOFTIRQ_PENDING 0 offsetof(irq_cpustat_t, __softirq_pending)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->CPU_BOOT_STACK 0 offsetof(struct secondary_data, stack)"
	//NO_APP
	//APP

	.ascii	"->CPU_BOOT_TASK 8 offsetof(struct secondary_data, task)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->FTR_OVR_VAL_OFFSET 0 offsetof(struct arm64_ftr_override, val)"
	//NO_APP
	//APP

	.ascii	"->FTR_OVR_MASK_OFFSET 8 offsetof(struct arm64_ftr_override, mask)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->VCPU_CONTEXT 1264 offsetof(struct kvm_vcpu, arch.ctxt)"
	//NO_APP
	//APP

	.ascii	"->VCPU_FAULT_DISR 3176 offsetof(struct kvm_vcpu, arch.fault.disr_el1)"
	//NO_APP
	//APP

	.ascii	"->VCPU_HCR_EL2 3120 offsetof(struct kvm_vcpu, arch.hcr_el2)"
	//NO_APP
	//APP

	.ascii	"->CPU_USER_PT_REGS 0 offsetof(struct kvm_cpu_context, regs)"
	//NO_APP
	//APP

	.ascii	"->CPU_RGSR_EL1 1752 offsetof(struct kvm_cpu_context, sys_regs[RGSR_EL1])"
	//NO_APP
	//APP

	.ascii	"->CPU_GCR_EL1 1760 offsetof(struct kvm_cpu_context, sys_regs[GCR_EL1])"
	//NO_APP
	//APP

	.ascii	"->CPU_APIAKEYLO_EL1 1608 offsetof(struct kvm_cpu_context, sys_regs[APIAKEYLO_EL1])"
	//NO_APP
	//APP

	.ascii	"->CPU_APIBKEYLO_EL1 1624 offsetof(struct kvm_cpu_context, sys_regs[APIBKEYLO_EL1])"
	//NO_APP
	//APP

	.ascii	"->CPU_APDAKEYLO_EL1 1640 offsetof(struct kvm_cpu_context, sys_regs[APDAKEYLO_EL1])"
	//NO_APP
	//APP

	.ascii	"->CPU_APDBKEYLO_EL1 1656 offsetof(struct kvm_cpu_context, sys_regs[APDBKEYLO_EL1])"
	//NO_APP
	//APP

	.ascii	"->CPU_APGAKEYLO_EL1 1672 offsetof(struct kvm_cpu_context, sys_regs[APGAKEYLO_EL1])"
	//NO_APP
	//APP

	.ascii	"->HOST_CONTEXT_VCPU 1816 offsetof(struct kvm_cpu_context, __hyp_running_vcpu)"
	//NO_APP
	//APP

	.ascii	"->HOST_DATA_CONTEXT 0 offsetof(struct kvm_host_data, host_ctxt)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_MAIR_EL2 0 offsetof(struct kvm_nvhe_init_params, mair_el2)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_TCR_EL2 8 offsetof(struct kvm_nvhe_init_params, tcr_el2)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_TPIDR_EL2 16 offsetof(struct kvm_nvhe_init_params, tpidr_el2)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_STACK_HYP_VA 24 offsetof(struct kvm_nvhe_init_params, stack_hyp_va)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_PGD_PA 40 offsetof(struct kvm_nvhe_init_params, pgd_pa)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_HCR_EL2 48 offsetof(struct kvm_nvhe_init_params, hcr_el2)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_HFGWTR_EL2 56 offsetof(struct kvm_nvhe_init_params, hfgwtr_el2)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_VTTBR 64 offsetof(struct kvm_nvhe_init_params, vttbr)"
	//NO_APP
	//APP

	.ascii	"->NVHE_INIT_VTCR 72 offsetof(struct kvm_nvhe_init_params, vtcr)"
	//NO_APP
	//APP

	.ascii	"->CPU_CTX_SP 104 offsetof(struct cpu_suspend_ctx, sp)"
	//NO_APP
	//APP

	.ascii	"->MPIDR_HASH_MASK 0 offsetof(struct mpidr_hash, mask)"
	//NO_APP
	//APP

	.ascii	"->MPIDR_HASH_SHIFTS 8 offsetof(struct mpidr_hash, shift_aff)"
	//NO_APP
	//APP

	.ascii	"->SLEEP_STACK_DATA_SYSTEM_REGS 0 offsetof(struct sleep_stack_data, system_regs)"
	//NO_APP
	//APP

	.ascii	"->SLEEP_STACK_DATA_CALLEE_REGS 112 offsetof(struct sleep_stack_data, callee_saved_regs)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_RES_X0_OFFS 0 offsetof(struct arm_smccc_res, a0)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_RES_X2_OFFS 16 offsetof(struct arm_smccc_res, a2)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_QUIRK_ID_OFFS 0 offsetof(struct arm_smccc_quirk, id)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_QUIRK_STATE_OFFS 8 offsetof(struct arm_smccc_quirk, state)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X0_OFFS 0 offsetof(struct arm_smccc_1_2_regs, a0)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X2_OFFS 16 offsetof(struct arm_smccc_1_2_regs, a2)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X4_OFFS 32 offsetof(struct arm_smccc_1_2_regs, a4)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X6_OFFS 48 offsetof(struct arm_smccc_1_2_regs, a6)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X8_OFFS 64 offsetof(struct arm_smccc_1_2_regs, a8)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X10_OFFS 80 offsetof(struct arm_smccc_1_2_regs, a10)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X12_OFFS 96 offsetof(struct arm_smccc_1_2_regs, a12)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X14_OFFS 112 offsetof(struct arm_smccc_1_2_regs, a14)"
	//NO_APP
	//APP

	.ascii	"->ARM_SMCCC_1_2_REGS_X16_OFFS 128 offsetof(struct arm_smccc_1_2_regs, a16)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->HIBERN_PBE_ORIG 8 offsetof(struct pbe, orig_address)"
	//NO_APP
	//APP

	.ascii	"->HIBERN_PBE_ADDR 0 offsetof(struct pbe, address)"
	//NO_APP
	//APP

	.ascii	"->HIBERN_PBE_NEXT 16 offsetof(struct pbe, next)"
	//NO_APP
	//APP

	.ascii	"->ARM64_FTR_SYSVAL 24 offsetof(struct arm64_ftr_reg, sys_val)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->TRAMP_VALIAS -4322250752 TRAMP_VALIAS"
	//NO_APP
	//APP

	.ascii	"->PTRAUTH_USER_KEY_APIA 0 offsetof(struct ptrauth_keys_user, apia)"
	//NO_APP
	//APP

	.ascii	"->PTRAUTH_KERNEL_KEY_APIA 0 offsetof(struct ptrauth_keys_kernel, apia)"
	//NO_APP
	//APP

	.ascii	"->"
	//NO_APP
	//APP

	.ascii	"->KIMAGE_ARCH_DTB_MEM 648 offsetof(struct kimage, arch.dtb_mem)"
	//NO_APP
	//APP

	.ascii	"->KIMAGE_ARCH_EL2_VECTORS 712 offsetof(struct kimage, arch.el2_vectors)"
	//NO_APP
	//APP

	.ascii	"->KIMAGE_ARCH_ZERO_PAGE 704 offsetof(struct kimage, arch.zero_page)"
	//NO_APP
	//APP

	.ascii	"->KIMAGE_ARCH_PHYS_OFFSET 680 offsetof(struct kimage, arch.phys_offset)"
	//NO_APP
	//APP

	.ascii	"->KIMAGE_ARCH_TTBR1 688 offsetof(struct kimage, arch.ttbr1)"
	//NO_APP
	//APP

	.ascii	"->KIMAGE_HEAD 0 offsetof(struct kimage, head)"
	//NO_APP
	//APP

	.ascii	"->KIMAGE_START 24 offsetof(struct kimage, start)"
	//NO_APP
	mov	w0, wzr
	//APP

	.ascii	"->"
	//NO_APP
	hint	#29
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
                                        // -- End function
	.ident	"Ubuntu clang version 18.1.3 (1ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
