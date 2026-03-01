/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __KVM_MOTOROLA_FIX_H__
#define __KVM_MOTOROLA_FIX_H__

#ifdef __ASSEMBLY__
/* --- Solo para Ensamblador (.S) --- */
#include <asm/sysreg.h>

/* Definiciones numéricas para registros de sistema opacos */
/* MTE Registers */
.ifndef s3_0_c1_c0_5
.set s3_0_c1_c0_5, 0x3085
.endif
.ifndef s3_0_c1_c0_6
.set s3_0_c1_c0_6, 0x3086
.endif

/* Pointer Authentication Registers (PAC) */
.ifndef s3_0_c2_c1_0
.set s3_0_c2_c1_0, 0x3108
.endif
.ifndef s3_0_c2_c1_1
.set s3_0_c2_c1_1, 0x3109
.endif
.ifndef s3_0_c2_c1_2
.set s3_0_c2_c1_2, 0x310a
.endif
.ifndef s3_0_c2_c1_3
.set s3_0_c2_c1_3, 0x310b
.endif
.ifndef s3_0_c2_c2_0
.set s3_0_c2_c2_0, 0x3110
.endif
.ifndef s3_0_c2_c2_1
.set s3_0_c2_c2_1, 0x3111
.endif
.ifndef s3_0_c2_c2_2
.set s3_0_c2_c2_2, 0x3112
.endif
.ifndef s3_0_c2_c2_3
.set s3_0_c2_c2_3, 0x3113
.endif
.ifndef s3_0_c2_c3_0
.set s3_0_c2_c3_0, 0x3118
.endif
.ifndef s3_0_c2_c3_1
.set s3_0_c2_c3_1, 0x3119
.endif

/* GIC/Other */
.ifndef s3_0_c12_c1_1
.set s3_0_c12_c1_1, 0x3609
.endif

/* KVM nvhe/hyp-init additional opaque system regs */
.ifndef s3_4_c1_c1_0
.set s3_4_c1_c1_0, 0xe888
.endif
.ifndef s3_4_c1_c1_1
.set s3_4_c1_c1_1, 0xe889
.endif
.ifndef s3_0_c9_c10_7
.set s3_0_c9_c10_7, 0xc4d7
.endif
.ifndef s3_4_c9_c9_0
.set s3_4_c9_c9_0, 0xccc8
.endif
.ifndef s3_0_c9_c11_7
.set s3_0_c9_c11_7, 0xc4df
.endif
.ifndef s3_0_c10_c4_3
.set s3_0_c10_c4_3, 0xc523
.endif
.ifndef s3_4_c12_c9_5
.set s3_4_c12_c9_5, 0xce4d
.endif
.ifndef s3_4_c12_c11_0
.set s3_4_c12_c11_0, 0xce58
.endif
.ifndef s3_4_c1_c2_0
.set s3_4_c1_c2_0, 0xc890
.endif

#define SYS_HFGWTR_EL2 s3_4_c1_c1_1
#define SYS_HFGRTR_EL2 s3_4_c1_c1_0
#define SYS_TCR_EL1 s3_0_c2_c0_2
#define SYS_ESR_EL1 s3_0_c5_c2_0
#define SYS_AFSR0_EL1 s3_0_c5_c1_0

#undef SYS_RGSR_EL1
#define SYS_RGSR_EL1 s3_0_c1_c0_5
#undef SYS_GCR_EL1
#define SYS_GCR_EL1 s3_0_c1_c0_6
#undef SYS_DISR_EL1
#define SYS_DISR_EL1 s3_0_c12_c1_1

#undef SYS_APIAKEYLO_EL1
#define SYS_APIAKEYLO_EL1 s3_0_c2_c1_0
#undef SYS_APIAKEYHI_EL1
#define SYS_APIAKEYHI_EL1 s3_0_c2_c1_1
#ifndef SYS_RGSR_EL1
#define SYS_RGSR_EL1 sys_reg(3, 0, 1, 0, 5)
#endif
#ifndef SYS_GCR_EL1
#define SYS_GCR_EL1 sys_reg(3, 0, 1, 0, 6)
#endif
#ifndef SYS_DISR_EL1
#define SYS_DISR_EL1 sys_reg(3, 0, 12, 1, 1)
#endif
#ifndef SYS_APGAKEYLO_EL1
#define SYS_APGAKEYLO_EL1 sys_reg(3, 0, 2, 3, 0)
#endif
#ifndef SYS_APGAKEYHI_EL1
#define SYS_APGAKEYHI_EL1 sys_reg(3, 0, 2, 3, 1)
#endif
#undef SYS_APIBKEYLO_EL1
#define SYS_APIBKEYLO_EL1 s3_0_c2_c1_2
#undef SYS_APIBKEYHI_EL1
#define SYS_APIBKEYHI_EL1 s3_0_c2_c1_3
#undef SYS_APDAKEYLO_EL1
#define SYS_APDAKEYLO_EL1 s3_0_c2_c2_0
#undef SYS_APDAKEYHI_EL1
#define SYS_APDAKEYHI_EL1 s3_0_c2_c2_1
#undef SYS_APDBKEYLO_EL1
#define SYS_APDBKEYLO_EL1 s3_0_c2_c2_2
#undef SYS_APDBKEYHI_EL1
#define SYS_APDBKEYHI_EL1 s3_0_c2_c2_3
#undef SYS_APGAKEYLO_EL1
#define SYS_APGAKEYLO_EL1 s3_0_c2_c3_0
#undef SYS_APGAKEYHI_EL1
#define SYS_APGAKEYHI_EL1 s3_0_c2_c3_1

#undef SYS_PMBIDR_EL1
#define SYS_PMBIDR_EL1 s3_0_c9_c10_7
#undef SYS_PMSCR_EL2
#define SYS_PMSCR_EL2 s3_4_c9_c9_0
#undef SYS_TRBIDR_EL1
#define SYS_TRBIDR_EL1 s3_0_c9_c11_7
#undef SYS_ICC_SRE_EL2
#define SYS_ICC_SRE_EL2 s3_4_c12_c9_5
#undef SYS_ICH_HCR_EL2
#define SYS_ICH_HCR_EL2 s3_4_c12_c11_0
#undef SYS_ZCR_EL2
#define SYS_ZCR_EL2 s3_4_c1_c2_0
#undef SYS_LORC_EL1
#define SYS_LORC_EL1 s3_0_c10_c4_3

#ifndef SET_PSTATE_PAN
#define SET_PSTATE_PAN(x) nop
#endif

#ifndef SB_BARRIER_INSN
#define SB_BARRIER_INSN dsb nsh
#endif

#else
/* --- Solo para C (.c) --- */
#include <asm/sysreg.h>

/* Definición de sysreg_clear_set_s si no existe */
#ifndef sysreg_clear_set_s
#define sysreg_clear_set_s(r, clear, set)                                      \
	do {                                                                   \
		u64 __scs_old = read_sysreg_s(r);                                \
		u64 __scs_new = (__scs_old & ~((u64)(clear))) | (u64)(set);      \
		if (__scs_new != __scs_old)                                      \
			write_sysreg_s(__scs_new, r);                               \
	} while (0)
#endif

/* Registros faltantes en C */
#ifndef SYS_HFGRTR_EL2
#define SYS_HFGRTR_EL2 sys_reg(3, 4, 1, 3, 0)
#endif
#ifndef SYS_HFGWTR_EL2
#define SYS_HFGWTR_EL2 sys_reg(3, 4, 1, 3, 1)
#endif
#ifndef SYS_TCR_EL1
#define SYS_TCR_EL1 sys_reg(3, 0, 2, 0, 2)
#endif
#ifndef SYS_ESR_EL1
#define SYS_ESR_EL1 sys_reg(3, 0, 5, 2, 0)
#endif
#ifndef SYS_AFSR0_EL1
#define SYS_AFSR0_EL1 sys_reg(3, 0, 5, 1, 0)
#endif

/* Máscaras de bits HFGxTR (ARMv8.6+) */
#ifndef HFGxTR_EL2_nSMPRI_EL1_MASK
#define HFGxTR_EL2_nSMPRI_EL1_MASK BIT(54)
#endif
#ifndef HFGxTR_EL2_nTPIDR2_EL0_MASK
#define HFGxTR_EL2_nTPIDR2_EL0_MASK BIT(55)
#endif

/* Bits de FP/SIMD */
#ifndef CPACR_EL1_FPEN_EL0EN
#define CPACR_EL1_FPEN_EL0EN (1U << 21)
#endif
#ifndef CPACR_EL1_FPEN_EL1EN
#define CPACR_EL1_FPEN_EL1EN (1U << 20)
#endif

/* Compatibilidad de nombres ICH_* en bases antiguas */
#ifndef ICH_HCR_EN
#define ICH_HCR_EN (1U << 0)
#endif
#ifndef ICH_HCR_UIE
#define ICH_HCR_UIE (1U << 1)
#endif
#ifndef ICH_HCR_TC
#define ICH_HCR_TC (1U << 10)
#endif
#ifndef ICH_HCR_TALL0
#define ICH_HCR_TALL0 (1U << 11)
#endif
#ifndef ICH_HCR_TALL1
#define ICH_HCR_TALL1 (1U << 12)
#endif
#ifndef ICH_HCR_TDIR
#define ICH_HCR_TDIR (1U << 14)
#endif
#ifndef ICH_HCR_EOIcount_SHIFT
#define ICH_HCR_EOIcount_SHIFT 27
#endif
#ifndef ICH_LR_STATE
#define ICH_LR_STATE (3ULL << 62)
#endif
#ifndef ICH_LR_PENDING_BIT
#define ICH_LR_PENDING_BIT (1ULL << 62)
#endif
#ifndef ICH_LR_ACTIVE_BIT
#define ICH_LR_ACTIVE_BIT (1ULL << 63)
#endif
#ifndef ICH_LR_GROUP
#define ICH_LR_GROUP (1ULL << 60)
#endif
#ifndef ICH_LR_HW
#define ICH_LR_HW (1ULL << 61)
#endif
#ifndef ICH_LR_EOI
#define ICH_LR_EOI (1ULL << 41)
#endif
#ifndef ICH_LR_VIRTUAL_ID_MASK
#define ICH_LR_VIRTUAL_ID_MASK ((1ULL << 32) - 1)
#endif
#ifndef ICH_LR_PHYS_ID_SHIFT
#define ICH_LR_PHYS_ID_SHIFT 32
#endif
#ifndef ICH_LR_PHYS_ID_MASK
#define ICH_LR_PHYS_ID_MASK (0x3ffULL << ICH_LR_PHYS_ID_SHIFT)
#endif
#ifndef ICH_LR_PRIORITY_SHIFT
#define ICH_LR_PRIORITY_SHIFT 48
#endif
#ifndef ICH_LR_PRIORITY_MASK
#define ICH_LR_PRIORITY_MASK (0xffULL << ICH_LR_PRIORITY_SHIFT)
#endif

#ifndef ICH_VMCR_ENG0_SHIFT
#define ICH_VMCR_ENG0_SHIFT 0
#endif
#ifndef ICH_VMCR_ENG0_MASK
#define ICH_VMCR_ENG0_MASK (1U << ICH_VMCR_ENG0_SHIFT)
#endif
#ifndef ICH_VMCR_ENG1_SHIFT
#define ICH_VMCR_ENG1_SHIFT 1
#endif
#ifndef ICH_VMCR_ENG1_MASK
#define ICH_VMCR_ENG1_MASK (1U << ICH_VMCR_ENG1_SHIFT)
#endif
#ifndef ICH_VMCR_CBPR_SHIFT
#define ICH_VMCR_CBPR_SHIFT 4
#endif
#ifndef ICH_VMCR_CBPR_MASK
#define ICH_VMCR_CBPR_MASK (1U << ICH_VMCR_CBPR_SHIFT)
#endif
#ifndef ICH_VMCR_EOIM_SHIFT
#define ICH_VMCR_EOIM_SHIFT 9
#endif
#ifndef ICH_VMCR_EOIM_MASK
#define ICH_VMCR_EOIM_MASK (1U << ICH_VMCR_EOIM_SHIFT)
#endif
#ifndef ICH_VMCR_ACK_CTL_SHIFT
#define ICH_VMCR_ACK_CTL_SHIFT 2
#endif
#ifndef ICH_VMCR_ACK_CTL_MASK
#define ICH_VMCR_ACK_CTL_MASK (1U << ICH_VMCR_ACK_CTL_SHIFT)
#endif
#ifndef ICH_VMCR_FIQ_EN_SHIFT
#define ICH_VMCR_FIQ_EN_SHIFT 3
#endif
#ifndef ICH_VMCR_FIQ_EN_MASK
#define ICH_VMCR_FIQ_EN_MASK (1U << ICH_VMCR_FIQ_EN_SHIFT)
#endif
#ifndef ICH_VMCR_PMR_SHIFT
#define ICH_VMCR_PMR_SHIFT 24
#endif
#ifndef ICH_VMCR_PMR_MASK
#define ICH_VMCR_PMR_MASK (0xffU << ICH_VMCR_PMR_SHIFT)
#endif
#ifndef ICH_VMCR_BPR0_SHIFT
#define ICH_VMCR_BPR0_SHIFT 21
#endif
#ifndef ICH_VMCR_BPR0_MASK
#define ICH_VMCR_BPR0_MASK (0x7U << ICH_VMCR_BPR0_SHIFT)
#endif
#ifndef ICH_VMCR_BPR1_SHIFT
#define ICH_VMCR_BPR1_SHIFT 18
#endif
#ifndef ICH_VMCR_BPR1_MASK
#define ICH_VMCR_BPR1_MASK (0x7U << ICH_VMCR_BPR1_SHIFT)
#endif

#ifndef ICH_VTR_SEIS_MASK
#define ICH_VTR_SEIS_MASK (1ULL << 22)
#endif
#ifndef ICH_VTR_A3V_MASK
#define ICH_VTR_A3V_MASK (1ULL << 21)
#endif
#ifndef ICH_VTR_TDS_MASK
#define ICH_VTR_TDS_MASK (1ULL << 19)
#endif
#ifndef ICH_VTR_ID_BITS_SHIFT
#define ICH_VTR_ID_BITS_SHIFT 23
#endif
#ifndef ICH_VTR_ID_BITS_MASK
#define ICH_VTR_ID_BITS_MASK (0x7ULL << ICH_VTR_ID_BITS_SHIFT)
#endif
#ifndef ICH_VTR_PRI_BITS_SHIFT
#define ICH_VTR_PRI_BITS_SHIFT 29
#endif
#ifndef ICH_VTR_PRI_BITS_MASK
#define ICH_VTR_PRI_BITS_MASK (0x7ULL << ICH_VTR_PRI_BITS_SHIFT)
#endif

#ifndef SYS_ICC_IAR0_EL1
#define SYS_ICC_IAR0_EL1 sys_reg(3, 0, 12, 8, 0)
#endif
#ifndef SYS_ICC_EOIR0_EL1
#define SYS_ICC_EOIR0_EL1 sys_reg(3, 0, 12, 8, 1)
#endif
#ifndef SYS_ICC_IAR1_EL1
#define SYS_ICC_IAR1_EL1 sys_reg(3, 0, 12, 12, 0)
#endif
#ifndef SYS_ICC_EOIR1_EL1
#define SYS_ICC_EOIR1_EL1 sys_reg(3, 0, 12, 12, 1)
#endif
#ifndef SYS_ICC_BPR1_EL1
#define SYS_ICC_BPR1_EL1 sys_reg(3, 0, 12, 12, 3)
#endif
#ifndef SYS_ICC_IGRPEN1_EL1
#define SYS_ICC_IGRPEN1_EL1 sys_reg(3, 0, 12, 12, 7)
#endif
#ifndef SYS_ICC_HPPIR0_EL1
#define SYS_ICC_HPPIR0_EL1 sys_reg(3, 0, 12, 8, 2)
#endif
#ifndef SYS_ICC_BPR0_EL1
#define SYS_ICC_BPR0_EL1 sys_reg(3, 0, 12, 8, 3)
#endif
#ifndef SYS_ICC_AP0Rn_EL1
#define SYS_ICC_AP0Rn_EL1(n) sys_reg(3, 0, 12, 8, 4 | (n))
#endif
#ifndef SYS_ICC_AP1Rn_EL1
#define SYS_ICC_AP1Rn_EL1(n) sys_reg(3, 0, 12, 9, (n))
#endif
#ifndef SYS_ICC_AP0R0_EL1
#define SYS_ICC_AP0R0_EL1 SYS_ICC_AP0Rn_EL1(0)
#endif
#ifndef SYS_ICC_AP0R1_EL1
#define SYS_ICC_AP0R1_EL1 SYS_ICC_AP0Rn_EL1(1)
#endif
#ifndef SYS_ICC_AP0R2_EL1
#define SYS_ICC_AP0R2_EL1 SYS_ICC_AP0Rn_EL1(2)
#endif
#ifndef SYS_ICC_AP0R3_EL1
#define SYS_ICC_AP0R3_EL1 SYS_ICC_AP0Rn_EL1(3)
#endif
#ifndef SYS_ICC_AP1R0_EL1
#define SYS_ICC_AP1R0_EL1 SYS_ICC_AP1Rn_EL1(0)
#endif
#ifndef SYS_ICC_AP1R1_EL1
#define SYS_ICC_AP1R1_EL1 SYS_ICC_AP1Rn_EL1(1)
#endif
#ifndef SYS_ICC_AP1R2_EL1
#define SYS_ICC_AP1R2_EL1 SYS_ICC_AP1Rn_EL1(2)
#endif
#ifndef SYS_ICC_AP1R3_EL1
#define SYS_ICC_AP1R3_EL1 SYS_ICC_AP1Rn_EL1(3)
#endif
#ifndef SYS_ICC_DIR_EL1
#define SYS_ICC_DIR_EL1 sys_reg(3, 0, 12, 11, 1)
#endif
#ifndef SYS_ICC_RPR_EL1
#define SYS_ICC_RPR_EL1 sys_reg(3, 0, 12, 11, 3)
#endif
#ifndef SYS_ICC_HPPIR1_EL1
#define SYS_ICC_HPPIR1_EL1 sys_reg(3, 0, 12, 12, 2)
#endif
#ifndef SYS_ICC_CTLR_EL1
#define SYS_ICC_CTLR_EL1 sys_reg(3, 0, 12, 12, 4)
#endif
#ifndef SYS_ICC_IGRPEN0_EL1
#define SYS_ICC_IGRPEN0_EL1 sys_reg(3, 0, 12, 12, 6)
#endif
#ifndef SYS_ICC_SGI1R_EL1
#define SYS_ICC_SGI1R_EL1 sys_reg(3, 0, 12, 11, 5)
#endif
#ifndef SYS_ICC_ASGI1R_EL1
#define SYS_ICC_ASGI1R_EL1 sys_reg(3, 0, 12, 11, 6)
#endif
#ifndef SYS_ICC_SGI0R_EL1
#define SYS_ICC_SGI0R_EL1 sys_reg(3, 0, 12, 11, 7)
#endif
#ifndef SYS_ICC_SRE_EL1
#define SYS_ICC_SRE_EL1 sys_reg(3, 0, 12, 12, 5)
#endif

#ifndef SYS_SPSR_EL1
#define SYS_SPSR_EL1 sys_reg(3, 0, 4, 0, 0)
#endif
#ifndef SYS_ELR_EL1
#define SYS_ELR_EL1 sys_reg(3, 0, 4, 0, 1)
#endif
#ifndef SYS_VBAR_EL1
#define SYS_VBAR_EL1 sys_reg(3, 0, 12, 0, 0)
#endif
#ifndef SYS_ESR_EL1
#define SYS_ESR_EL1 sys_reg(3, 0, 5, 2, 0)
#endif
#ifndef SYS_AFSR1_EL1
#define SYS_AFSR1_EL1 sys_reg(3, 0, 5, 1, 1)
#endif
#ifndef SYS_RGSR_EL1
#define SYS_RGSR_EL1 sys_reg(3, 0, 1, 0, 5)
#endif
#ifndef SYS_GCR_EL1
#define SYS_GCR_EL1 sys_reg(3, 0, 1, 0, 6)
#endif
#ifndef SYS_DISR_EL1
#define SYS_DISR_EL1 sys_reg(3, 0, 12, 1, 1)
#endif
#ifndef SYS_APGAKEYLO_EL1
#define SYS_APGAKEYLO_EL1 sys_reg(3, 0, 2, 3, 0)
#endif
#ifndef SYS_APGAKEYHI_EL1
#define SYS_APGAKEYHI_EL1 sys_reg(3, 0, 2, 3, 1)
#endif
#ifndef SYS_MAIR_EL1
#define SYS_MAIR_EL1 sys_reg(3, 0, 10, 2, 0)
#endif
#ifndef SYS_AMAIR_EL1
#define SYS_AMAIR_EL1 sys_reg(3, 0, 10, 3, 0)
#endif
#ifndef SYS_CNTKCTL_EL1
#define SYS_CNTKCTL_EL1 sys_reg(3, 0, 14, 1, 0)
#endif
#ifndef SYS_TFSR_EL1
#define SYS_TFSR_EL1 sys_reg(3, 0, 5, 6, 0)
#endif
#ifndef SYS_TFSRE0_EL1
#define SYS_TFSRE0_EL1 sys_reg(3, 0, 5, 6, 1)
#endif

#ifndef SYS_SPSR_EL2
#define SYS_SPSR_EL2 sys_reg(3, 4, 4, 0, 0)
#endif
#ifndef SYS_ELR_EL2
#define SYS_ELR_EL2 sys_reg(3, 4, 4, 0, 1)
#endif
#ifndef SYS_ESR_EL2
#define SYS_ESR_EL2 sys_reg(3, 4, 5, 2, 0)
#endif
#ifndef SYS_VSESR_EL2
#define SYS_VSESR_EL2 sys_reg(3, 4, 5, 2, 3)
#endif
#ifndef SYS_VDISR_EL2
#define SYS_VDISR_EL2 sys_reg(3, 4, 12, 1, 1)
#endif
#ifndef SYS_IFSR32_EL2
#define SYS_IFSR32_EL2 sys_reg(3, 4, 5, 0, 1)
#endif
#ifndef SYS_FPEXC32_EL2
#define SYS_FPEXC32_EL2 sys_reg(3, 4, 5, 3, 0)
#endif

#ifndef SYS_SCTLR_EL12
#define SYS_SCTLR_EL12 sys_reg(3, 5, 1, 0, 0)
#endif
#ifndef SYS_TCR_EL12
#define SYS_TCR_EL12 sys_reg(3, 5, 2, 0, 2)
#endif
#ifndef SYS_AFSR0_EL12
#define SYS_AFSR0_EL12 sys_reg(3, 5, 5, 1, 0)
#endif
#ifndef SYS_AFSR1_EL12
#define SYS_AFSR1_EL12 sys_reg(3, 5, 5, 1, 1)
#endif
#ifndef SYS_ESR_EL12
#define SYS_ESR_EL12 sys_reg(3, 5, 5, 2, 0)
#endif
#ifndef SYS_TFSR_EL12
#define SYS_TFSR_EL12 sys_reg(3, 5, 5, 6, 0)
#endif
#ifndef SYS_ELR_EL12
#define SYS_ELR_EL12 sys_reg(3, 5, 4, 0, 1)
#endif
#ifndef SYS_SPSR_EL12
#define SYS_SPSR_EL12 sys_reg(3, 5, 4, 0, 0)
#endif
#ifndef SYS_VBAR_EL12
#define SYS_VBAR_EL12 sys_reg(3, 5, 12, 0, 0)
#endif
#ifndef SYS_VBAR_EL1
#define SYS_VBAR_EL1 sys_reg(3, 0, 12, 0, 0)
#endif
#ifndef SYS_TTBR0_EL12
#define SYS_TTBR0_EL12 sys_reg(3, 5, 2, 0, 0)
#endif
#ifndef SYS_TTBR1_EL12
#define SYS_TTBR1_EL12 sys_reg(3, 5, 2, 0, 1)
#endif
#ifndef SYS_CNTKCTL_EL12
#define SYS_CNTKCTL_EL12 sys_reg(3, 5, 14, 1, 0)
#endif
#ifndef SYS_MAIR_EL12
#define SYS_MAIR_EL12 sys_reg(3, 5, 10, 2, 0)
#endif
#ifndef SYS_AMAIR_EL12
#define SYS_AMAIR_EL12 sys_reg(3, 5, 10, 3, 0)
#endif
#ifndef SYS_SCTLR_EL2
#define SYS_SCTLR_EL2 sys_reg(3, 4, 1, 0, 0)
#endif
#ifndef SYS_ICH_VTR_EL2
#define SYS_ICH_VTR_EL2 sys_reg(3, 4, 12, 11, 1)
#endif
#ifndef SYS_ICH_HCR_EL2
#define SYS_ICH_HCR_EL2 sys_reg(3, 4, 12, 11, 0)
#endif
#ifndef SYS_ICH_VMCR_EL2
#define SYS_ICH_VMCR_EL2 sys_reg(3, 4, 12, 11, 7)
#endif
#ifndef SYS_ICC_SRE_EL2
#define SYS_ICC_SRE_EL2 sys_reg(3, 4, 12, 9, 5)
#endif
#ifndef SYS_ICH_AP0R0_EL2
#define SYS_ICH_AP0R0_EL2 sys_reg(3, 4, 12, 8, 4)
#endif
#ifndef SYS_ICH_AP0R1_EL2
#define SYS_ICH_AP0R1_EL2 sys_reg(3, 4, 12, 8, 5)
#endif
#ifndef SYS_ICH_AP0R2_EL2
#define SYS_ICH_AP0R2_EL2 sys_reg(3, 4, 12, 8, 6)
#endif
#ifndef SYS_ICH_AP0R3_EL2
#define SYS_ICH_AP0R3_EL2 sys_reg(3, 4, 12, 8, 7)
#endif
#ifndef SYS_ICH_AP1R0_EL2
#define SYS_ICH_AP1R0_EL2 sys_reg(3, 4, 12, 9, 0)
#endif
#ifndef SYS_ICH_AP1R1_EL2
#define SYS_ICH_AP1R1_EL2 sys_reg(3, 4, 12, 9, 1)
#endif
#ifndef SYS_ICH_AP1R2_EL2
#define SYS_ICH_AP1R2_EL2 sys_reg(3, 4, 12, 9, 2)
#endif
#ifndef SYS_ICH_AP1R3_EL2
#define SYS_ICH_AP1R3_EL2 sys_reg(3, 4, 12, 9, 3)
#endif
#ifndef SYS_ICH_ELRSR_EL2
#define SYS_ICH_ELRSR_EL2 sys_reg(3, 4, 12, 11, 5)
#endif
#ifndef SYS_ICH_LR0_EL2
#define SYS_ICH_LR0_EL2 sys_reg(3, 4, 12, 12, 0)
#define SYS_ICH_LR1_EL2 sys_reg(3, 4, 12, 12, 1)
#define SYS_ICH_LR2_EL2 sys_reg(3, 4, 12, 12, 2)
#define SYS_ICH_LR3_EL2 sys_reg(3, 4, 12, 12, 3)
#define SYS_ICH_LR4_EL2 sys_reg(3, 4, 12, 12, 4)
#define SYS_ICH_LR5_EL2 sys_reg(3, 4, 12, 12, 5)
#define SYS_ICH_LR6_EL2 sys_reg(3, 4, 12, 12, 6)
#define SYS_ICH_LR7_EL2 sys_reg(3, 4, 12, 12, 7)
#define SYS_ICH_LR8_EL2 sys_reg(3, 4, 12, 13, 0)
#define SYS_ICH_LR9_EL2 sys_reg(3, 4, 12, 13, 1)
#define SYS_ICH_LR10_EL2 sys_reg(3, 4, 12, 13, 2)
#define SYS_ICH_LR11_EL2 sys_reg(3, 4, 12, 13, 3)
#define SYS_ICH_LR12_EL2 sys_reg(3, 4, 12, 13, 4)
#define SYS_ICH_LR13_EL2 sys_reg(3, 4, 12, 13, 5)
#define SYS_ICH_LR14_EL2 sys_reg(3, 4, 12, 13, 6)
#define SYS_ICH_LR15_EL2 sys_reg(3, 4, 12, 13, 7)
#endif
#ifndef SYS_CNTV_CTL_EL0
#define SYS_CNTV_CTL_EL0 sys_reg(3, 3, 14, 3, 1)
#endif
#ifndef SYS_CNTV_CVAL_EL0
#define SYS_CNTV_CVAL_EL0 sys_reg(3, 3, 14, 3, 2)
#endif
#ifndef SYS_CNTV_CTL_EL02
#define SYS_CNTV_CTL_EL02 sys_reg(3, 5, 14, 3, 1)
#endif
#ifndef SYS_CNTV_CVAL_EL02
#define SYS_CNTV_CVAL_EL02 sys_reg(3, 5, 14, 3, 2)
#endif

#ifndef sys_reg_Op0
#define sys_reg_Op0(id) (((id) >> 14) & 0x3)
#endif
#ifndef sys_reg_Op1
#define sys_reg_Op1(id) (((id) >> 11) & 0x7)
#endif
#ifndef sys_reg_CRn
#define sys_reg_CRn(id) (((id) >> 7) & 0xf)
#endif
#ifndef sys_reg_CRm
#define sys_reg_CRm(id) (((id) >> 3) & 0xf)
#endif
#ifndef sys_reg_Op2
#define sys_reg_Op2(id) ((id) & 0x7)
#endif

#ifndef SYS_MDSCR_EL1
#define SYS_MDSCR_EL1 sys_reg(2, 0, 0, 2, 2)
#endif
#ifndef SYS_MDCCINT_EL1
#define SYS_MDCCINT_EL1 sys_reg(2, 0, 0, 2, 0)
#endif
#ifndef SYS_MDRAR_EL1
#define SYS_MDRAR_EL1 sys_reg(2, 0, 1, 0, 0)
#endif
#ifndef SYS_DBGBVRn_EL1
#define SYS_DBGBVRn_EL1(n) sys_reg(2, 0, 0, (n), 4)
#endif
#ifndef SYS_DBGBCRn_EL1
#define SYS_DBGBCRn_EL1(n) sys_reg(2, 0, 0, (n), 5)
#endif
#ifndef SYS_DBGWVRn_EL1
#define SYS_DBGWVRn_EL1(n) sys_reg(2, 0, 0, (n), 6)
#endif
#ifndef SYS_DBGWCRn_EL1
#define SYS_DBGWCRn_EL1(n) sys_reg(2, 0, 0, (n), 7)
#endif
#ifndef SYS_OSLAR_EL1
#define SYS_OSLAR_EL1 sys_reg(2, 0, 1, 0, 4)
#endif
#ifndef SYS_OSLSR_EL1
#define SYS_OSLSR_EL1 sys_reg(2, 0, 1, 1, 4)
#endif
#ifndef SYS_OSDLR_EL1
#define SYS_OSDLR_EL1 sys_reg(2, 0, 1, 3, 4)
#endif
#ifndef SYS_DBGPRCR_EL1
#define SYS_DBGPRCR_EL1 sys_reg(2, 0, 1, 4, 4)
#endif
#ifndef SYS_DBGCLAIMSET_EL1
#define SYS_DBGCLAIMSET_EL1 sys_reg(2, 0, 7, 8, 6)
#endif
#ifndef SYS_DBGCLAIMCLR_EL1
#define SYS_DBGCLAIMCLR_EL1 sys_reg(2, 0, 7, 9, 6)
#endif
#ifndef SYS_DBGAUTHSTATUS_EL1
#define SYS_DBGAUTHSTATUS_EL1 sys_reg(2, 0, 7, 14, 6)
#endif
#ifndef SYS_MDCCSR_EL0
#define SYS_MDCCSR_EL0 sys_reg(2, 3, 0, 1, 0)
#endif
#ifndef SYS_DBGDTR_EL0
#define SYS_DBGDTR_EL0 sys_reg(2, 3, 0, 4, 0)
#endif
#ifndef SYS_DBGDTRRX_EL0
#define SYS_DBGDTRRX_EL0 sys_reg(2, 3, 0, 5, 0)
#endif
#ifndef SYS_DBGDTRTX_EL0
#define SYS_DBGDTRTX_EL0 sys_reg(2, 3, 0, 5, 0)
#endif
#ifndef SYS_DBGVCR32_EL2
#define SYS_DBGVCR32_EL2 sys_reg(2, 4, 0, 7, 0)
#endif

#ifndef SYS_ID_PFR0_EL1
#define SYS_ID_PFR0_EL1 sys_reg(3, 0, 0, 1, 0)
#endif
#ifndef SYS_ID_PFR1_EL1
#define SYS_ID_PFR1_EL1 sys_reg(3, 0, 0, 1, 1)
#endif
#ifndef SYS_ID_DFR0_EL1
#define SYS_ID_DFR0_EL1 sys_reg(3, 0, 0, 1, 2)
#endif
#ifndef SYS_ID_AFR0_EL1
#define SYS_ID_AFR0_EL1 sys_reg(3, 0, 0, 1, 3)
#endif
#ifndef SYS_ID_MMFR0_EL1
#define SYS_ID_MMFR0_EL1 sys_reg(3, 0, 0, 1, 4)
#endif
#ifndef SYS_ID_MMFR1_EL1
#define SYS_ID_MMFR1_EL1 sys_reg(3, 0, 0, 1, 5)
#endif
#ifndef SYS_ID_MMFR2_EL1
#define SYS_ID_MMFR2_EL1 sys_reg(3, 0, 0, 1, 6)
#endif
#ifndef SYS_ID_MMFR3_EL1
#define SYS_ID_MMFR3_EL1 sys_reg(3, 0, 0, 1, 7)
#endif

#ifndef SYS_ID_ISAR0_EL1
#define SYS_ID_ISAR0_EL1 sys_reg(3, 0, 0, 2, 0)
#endif
#ifndef SYS_ID_ISAR1_EL1
#define SYS_ID_ISAR1_EL1 sys_reg(3, 0, 0, 2, 1)
#endif
#ifndef SYS_ID_ISAR2_EL1
#define SYS_ID_ISAR2_EL1 sys_reg(3, 0, 0, 2, 2)
#endif
#ifndef SYS_ID_ISAR3_EL1
#define SYS_ID_ISAR3_EL1 sys_reg(3, 0, 0, 2, 3)
#endif
#ifndef SYS_ID_ISAR4_EL1
#define SYS_ID_ISAR4_EL1 sys_reg(3, 0, 0, 2, 4)
#endif
#ifndef SYS_ID_ISAR5_EL1
#define SYS_ID_ISAR5_EL1 sys_reg(3, 0, 0, 2, 5)
#endif
#ifndef SYS_ID_MMFR4_EL1
#define SYS_ID_MMFR4_EL1 sys_reg(3, 0, 0, 2, 6)
#endif
#ifndef SYS_ID_ISAR6_EL1
#define SYS_ID_ISAR6_EL1 sys_reg(3, 0, 0, 2, 7)
#endif

#ifndef SYS_MVFR0_EL1
#define SYS_MVFR0_EL1 sys_reg(3, 0, 0, 3, 0)
#endif
#ifndef SYS_MVFR1_EL1
#define SYS_MVFR1_EL1 sys_reg(3, 0, 0, 3, 1)
#endif
#ifndef SYS_MVFR2_EL1
#define SYS_MVFR2_EL1 sys_reg(3, 0, 0, 3, 2)
#endif
#ifndef SYS_ID_PFR2_EL1
#define SYS_ID_PFR2_EL1 sys_reg(3, 0, 0, 3, 4)
#endif
#ifndef SYS_ID_DFR1_EL1
#define SYS_ID_DFR1_EL1 sys_reg(3, 0, 0, 3, 5)
#endif
#ifndef SYS_ID_MMFR5_EL1
#define SYS_ID_MMFR5_EL1 sys_reg(3, 0, 0, 3, 6)
#endif

#ifndef SYS_CCSIDR_EL1
#define SYS_CCSIDR_EL1 sys_reg(3, 1, 0, 0, 0)
#endif
#ifndef SYS_CLIDR_EL1
#define SYS_CLIDR_EL1 sys_reg(3, 1, 0, 0, 1)
#endif
#ifndef SYS_CSSELR_EL1
#define SYS_CSSELR_EL1 sys_reg(3, 2, 0, 0, 0)
#endif
#ifndef SYS_CTR_EL0
#define SYS_CTR_EL0 sys_reg(3, 3, 0, 0, 1)
#endif
#ifndef SYS_AIDR_EL1
#define SYS_AIDR_EL1 sys_reg(3, 1, 0, 0, 7)
#endif

#ifndef SYS_ACTLR_EL1
#define SYS_ACTLR_EL1 sys_reg(3, 0, 1, 0, 1)
#endif

#ifndef SYS_CNTP_TVAL_EL0
#define SYS_CNTP_TVAL_EL0 sys_reg(3, 3, 14, 2, 0)
#endif
#ifndef SYS_CNTP_CTL_EL0
#define SYS_CNTP_CTL_EL0 sys_reg(3, 3, 14, 2, 1)
#endif
#ifndef SYS_CNTP_CVAL_EL0
#define SYS_CNTP_CVAL_EL0 sys_reg(3, 3, 14, 2, 2)
#endif

#ifndef SYS_PMSCR_EL1
#define SYS_PMSCR_EL1 sys_reg(3, 0, 9, 9, 0)
#endif
#ifndef SYS_PMSNEVFR_EL1
#define SYS_PMSNEVFR_EL1 sys_reg(3, 0, 9, 9, 1)
#endif
#ifndef SYS_PMSICR_EL1
#define SYS_PMSICR_EL1 sys_reg(3, 0, 9, 9, 2)
#endif
#ifndef SYS_PMSIRR_EL1
#define SYS_PMSIRR_EL1 sys_reg(3, 0, 9, 9, 3)
#endif
#ifndef SYS_PMSFCR_EL1
#define SYS_PMSFCR_EL1 sys_reg(3, 0, 9, 9, 4)
#endif
#ifndef SYS_PMSEVFR_EL1
#define SYS_PMSEVFR_EL1 sys_reg(3, 0, 9, 9, 5)
#endif
#ifndef SYS_PMSLATFR_EL1
#define SYS_PMSLATFR_EL1 sys_reg(3, 0, 9, 9, 6)
#endif
#ifndef SYS_PMSIDR_EL1
#define SYS_PMSIDR_EL1 sys_reg(3, 0, 9, 9, 7)
#endif
#ifndef SYS_PMBLIMITR_EL1
#define SYS_PMBLIMITR_EL1 sys_reg(3, 0, 9, 10, 0)
#endif
#ifndef SYS_PMBPTR_EL1
#define SYS_PMBPTR_EL1 sys_reg(3, 0, 9, 10, 1)
#endif
#ifndef SYS_PMBSR_EL1
#define SYS_PMBSR_EL1 sys_reg(3, 0, 9, 10, 3)
#endif
#ifndef SYS_PMINTENSET_EL1
#define SYS_PMINTENSET_EL1 sys_reg(3, 0, 9, 14, 1)
#endif
#ifndef SYS_PMINTENCLR_EL1
#define SYS_PMINTENCLR_EL1 sys_reg(3, 0, 9, 14, 2)
#endif
#ifndef SYS_PMMIR_EL1
#define SYS_PMMIR_EL1 sys_reg(3, 0, 9, 14, 6)
#endif

#ifndef SYS_PMCR_EL0
#define SYS_PMCR_EL0 sys_reg(3, 3, 9, 12, 0)
#endif
#ifndef SYS_PMCNTENSET_EL0
#define SYS_PMCNTENSET_EL0 sys_reg(3, 3, 9, 12, 1)
#endif
#ifndef SYS_PMCNTENCLR_EL0
#define SYS_PMCNTENCLR_EL0 sys_reg(3, 3, 9, 12, 2)
#endif
#ifndef SYS_PMOVSCLR_EL0
#define SYS_PMOVSCLR_EL0 sys_reg(3, 3, 9, 12, 3)
#endif
#ifndef SYS_PMSWINC_EL0
#define SYS_PMSWINC_EL0 sys_reg(3, 3, 9, 12, 4)
#endif
#ifndef SYS_PMSELR_EL0
#define SYS_PMSELR_EL0 sys_reg(3, 3, 9, 12, 5)
#endif
#ifndef SYS_PMCEID0_EL0
#define SYS_PMCEID0_EL0 sys_reg(3, 3, 9, 12, 6)
#endif
#ifndef SYS_PMCEID1_EL0
#define SYS_PMCEID1_EL0 sys_reg(3, 3, 9, 12, 7)
#endif
#ifndef SYS_PMCCNTR_EL0
#define SYS_PMCCNTR_EL0 sys_reg(3, 3, 9, 13, 0)
#endif
#ifndef SYS_PMXEVTYPER_EL0
#define SYS_PMXEVTYPER_EL0 sys_reg(3, 3, 9, 13, 1)
#endif
#ifndef SYS_PMXEVCNTR_EL0
#define SYS_PMXEVCNTR_EL0 sys_reg(3, 3, 9, 13, 2)
#endif
#ifndef SYS_PMUSERENR_EL0
#define SYS_PMUSERENR_EL0 sys_reg(3, 3, 9, 14, 0)
#endif
#ifndef SYS_PMOVSSET_EL0
#define SYS_PMOVSSET_EL0 sys_reg(3, 3, 9, 14, 3)
#endif
#ifndef SYS_PMCCFILTR_EL0
#define SYS_PMCCFILTR_EL0 sys_reg(3, 3, 14, 15, 7)
#endif
#ifndef SYS_TPIDRRO_EL0
#define SYS_TPIDRRO_EL0 sys_reg(3, 3, 13, 0, 3)
#endif
#ifndef SYS_TPIDR_EL0
#define SYS_TPIDR_EL0 sys_reg(3, 3, 13, 0, 2)
#endif
#ifndef SYS_TPIDR2_EL0
#define SYS_TPIDR2_EL0 sys_reg(3, 3, 13, 0, 5)
#endif
#ifndef SYS_SCXTNUM_EL0
#define SYS_SCXTNUM_EL0 sys_reg(3, 3, 13, 0, 7)
#endif

#ifndef SYS_AM_EL0
#define SYS_AM_EL0(crm, op2) sys_reg(3, 3, 13, (crm), (op2))
#endif
#ifndef SYS_AMCR_EL0
#define SYS_AMCR_EL0 SYS_AM_EL0(2, 0)
#endif
#ifndef SYS_AMCFGR_EL0
#define SYS_AMCFGR_EL0 SYS_AM_EL0(2, 1)
#endif
#ifndef SYS_AMCGCR_EL0
#define SYS_AMCGCR_EL0 SYS_AM_EL0(2, 2)
#endif
#ifndef SYS_AMUSERENR_EL0
#define SYS_AMUSERENR_EL0 SYS_AM_EL0(2, 3)
#endif
#ifndef SYS_AMCNTENCLR0_EL0
#define SYS_AMCNTENCLR0_EL0 SYS_AM_EL0(2, 4)
#endif
#ifndef SYS_AMCNTENSET0_EL0
#define SYS_AMCNTENSET0_EL0 SYS_AM_EL0(2, 5)
#endif
#ifndef SYS_AMCNTENCLR1_EL0
#define SYS_AMCNTENCLR1_EL0 SYS_AM_EL0(3, 0)
#endif
#ifndef SYS_AMCNTENSET1_EL0
#define SYS_AMCNTENSET1_EL0 SYS_AM_EL0(3, 1)
#endif

#ifndef SYS_AMEVCNTR0_EL0
#define SYS_AMEVCNTR0_EL0(n) sys_reg(3, 3, 13, (4 + ((n) >> 3)), ((n) & 7))
#endif
#ifndef SYS_AMEVTYPER0_EL0
#define SYS_AMEVTYPER0_EL0(n) sys_reg(3, 3, 13, (6 + ((n) >> 3)), ((n) & 7))
#endif
#ifndef SYS_AMEVCNTR1_EL0
#define SYS_AMEVCNTR1_EL0(n) sys_reg(3, 3, 13, (12 + ((n) >> 3)), ((n) & 7))
#endif
#ifndef SYS_AMEVTYPER1_EL0
#define SYS_AMEVTYPER1_EL0(n) sys_reg(3, 3, 13, (14 + ((n) >> 3)), ((n) & 7))
#endif

#ifndef SYS_PMEVCNTRn_EL0
#define SYS_PMEVCNTRn_EL0(n) sys_reg(3, 3, 14, (8 + ((n) >> 3)), ((n) & 7))
#endif
#ifndef SYS_PMEVTYPERn_EL0
#define SYS_PMEVTYPERn_EL0(n) sys_reg(3, 3, 14, (12 + ((n) >> 3)), ((n) & 7))
#endif
#ifndef SYS_TRBLIMITR_EL1
#define SYS_TRBLIMITR_EL1 sys_reg(3, 0, 9, 11, 0)
#endif
#ifndef SYS_TRFCR_EL1
#define SYS_TRFCR_EL1 sys_reg(3, 0, 1, 2, 1)
#endif

#ifndef SYS_ERRIDR_EL1
#define SYS_ERRIDR_EL1 sys_reg(3, 0, 5, 3, 0)
#endif
#ifndef SYS_ERRSELR_EL1
#define SYS_ERRSELR_EL1 sys_reg(3, 0, 5, 3, 1)
#endif
#ifndef SYS_ERXFR_EL1
#define SYS_ERXFR_EL1 sys_reg(3, 0, 5, 4, 0)
#endif
#ifndef SYS_ERXCTLR_EL1
#define SYS_ERXCTLR_EL1 sys_reg(3, 0, 5, 4, 1)
#endif
#ifndef SYS_ERXSTATUS_EL1
#define SYS_ERXSTATUS_EL1 sys_reg(3, 0, 5, 4, 2)
#endif
#ifndef SYS_ERXADDR_EL1
#define SYS_ERXADDR_EL1 sys_reg(3, 0, 5, 4, 3)
#endif
#ifndef SYS_ERXMISC0_EL1
#define SYS_ERXMISC0_EL1 sys_reg(3, 0, 5, 5, 0)
#endif
#ifndef SYS_ERXMISC1_EL1
#define SYS_ERXMISC1_EL1 sys_reg(3, 0, 5, 5, 1)
#endif

#endif /* __ASSEMBLY__ */

/* --- Común para ambos --- */
#ifndef SCTLR_ELx_M
#define SCTLR_ELx_M (1UL << 0)
#endif

#ifndef SCTLR_ELx_DSSBS
#define SCTLR_ELx_DSSBS (1UL << 44)
#endif

#ifndef ID_AA64DFR0_TRBE_SHIFT
#define ID_AA64DFR0_TRBE_SHIFT 44
#endif

#ifndef TRBIDR_PROG
#define TRBIDR_PROG (1UL << 0)
#endif

#ifndef SYS_PMBIDR_EL1_P_SHIFT
#define SYS_PMBIDR_EL1_P_SHIFT 0
#endif

#ifndef SYS_PMBLIMITR_EL1_E_SHIFT
#define SYS_PMBLIMITR_EL1_E_SHIFT 0
#endif

#ifndef TRBLIMITR_ENABLE
#define TRBLIMITR_ENABLE (1UL << 0)
#endif

#ifndef SYS_PMSCR_EL2_PA_SHIFT
#define SYS_PMSCR_EL2_PA_SHIFT 4
#endif

#ifndef SYS_PMSCR_EL2_PCT_SHIFT
#define SYS_PMSCR_EL2_PCT_SHIFT 6
#endif

#ifndef ID_AA64MMFR0_PARANGE_MAX
#ifdef CONFIG_ARM64_PA_BITS_52
#define ID_AA64MMFR0_PARANGE_MAX 6
#else
#define ID_AA64MMFR0_PARANGE_MAX 5
#endif
#endif

#ifndef ID_AA64MMFR0_PARANGE_48
#define ID_AA64MMFR0_PARANGE_48 0x5
#endif

#ifndef ID_AA64MMFR0_TGRAN_2_SUPPORTED_DEFAULT
#define ID_AA64MMFR0_TGRAN_2_SUPPORTED_DEFAULT 0x0
#endif

#ifndef ID_AA64MMFR0_TGRAN_2_SUPPORTED_NONE
#define ID_AA64MMFR0_TGRAN_2_SUPPORTED_NONE 0x1
#endif

#ifndef ID_AA64MMFR0_TGRAN_2_SUPPORTED_MIN
#define ID_AA64MMFR0_TGRAN_2_SUPPORTED_MIN 0x2
#endif

#ifndef ID_AA64MMFR0_TGRAN_2_SUPPORTED_MAX
#define ID_AA64MMFR0_TGRAN_2_SUPPORTED_MAX 0x7
#endif

#ifndef SYS_OSLSR_OSLK
#define SYS_OSLSR_OSLK BIT(1)
#endif

#ifndef SYS_OSLSR_OSLM_IMPLEMENTED
#define SYS_OSLSR_OSLM_IMPLEMENTED BIT(3)
#endif

#ifndef SYS_OSLAR_OSLK
#define SYS_OSLAR_OSLK BIT(0)
#endif

#ifndef sys_insn
#define sys_insn sys_reg
#endif

#ifndef SYS_DC_ISW
#define SYS_DC_ISW sys_insn(1, 0, 7, 6, 2)
#endif

#ifndef SYS_DC_CSW
#define SYS_DC_CSW sys_insn(1, 0, 7, 10, 2)
#endif

#ifndef SYS_DC_CISW
#define SYS_DC_CISW sys_insn(1, 0, 7, 14, 2)
#endif

#ifndef SYS_AARCH32_CNTP_TVAL
#define SYS_AARCH32_CNTP_TVAL sys_reg(0, 0, 14, 2, 0)
#endif

#ifndef SYS_AARCH32_CNTP_CTL
#define SYS_AARCH32_CNTP_CTL sys_reg(0, 0, 14, 2, 1)
#endif

#ifndef SYS_AARCH32_CNTP_CVAL
#define SYS_AARCH32_CNTP_CVAL sys_reg(0, 2, 0, 14, 0)
#endif

#ifndef ARM64_FEATURE_MASK
#define ARM64_FEATURE_MASK(field) GENMASK_ULL(field##_SHIFT + 3, field##_SHIFT)
#endif

#ifndef ID_DFR0_PERFMON_8_4
#define ID_DFR0_PERFMON_8_4 0x5
#endif

#ifndef ARM64_FEATURE_FIELD_BITS
#define ARM64_FEATURE_FIELD_BITS 4
#endif

#ifndef ID_AA64PFR0_EL1_ELx_64BIT_ONLY
#define ID_AA64PFR0_EL1_ELx_64BIT_ONLY 0x1
#endif

#endif /* __KVM_MOTOROLA_FIX_H__ */
