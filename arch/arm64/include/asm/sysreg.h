#ifndef __ASM_SYSREG_H
#define __ASM_SYSREG_H

#include <linux/bits.h>
#include <linux/stringify.h>

#ifndef __ASSEMBLY__
#include <linux/types.h>

#ifndef __SYSREG_MRSMSR_S_INLINE_DEF
#define __SYSREG_MRSMSR_S_INLINE_DEF
asm(
".ifndef __SYSREG_MRSMSR_S_DEFINED\n"
".set __SYSREG_MRSMSR_S_DEFINED, 1\n"
".equ __sysreg_gpr_x0, 0\n"
".equ __sysreg_gpr_x1, 1\n"
".equ __sysreg_gpr_x2, 2\n"
".equ __sysreg_gpr_x3, 3\n"
".equ __sysreg_gpr_x4, 4\n"
".equ __sysreg_gpr_x5, 5\n"
".equ __sysreg_gpr_x6, 6\n"
".equ __sysreg_gpr_x7, 7\n"
".equ __sysreg_gpr_x8, 8\n"
".equ __sysreg_gpr_x9, 9\n"
".equ __sysreg_gpr_x10, 10\n"
".equ __sysreg_gpr_x11, 11\n"
".equ __sysreg_gpr_x12, 12\n"
".equ __sysreg_gpr_x13, 13\n"
".equ __sysreg_gpr_x14, 14\n"
".equ __sysreg_gpr_x15, 15\n"
".equ __sysreg_gpr_x16, 16\n"
".equ __sysreg_gpr_x17, 17\n"
".equ __sysreg_gpr_x18, 18\n"
".equ __sysreg_gpr_x19, 19\n"
".equ __sysreg_gpr_x20, 20\n"
".equ __sysreg_gpr_x21, 21\n"
".equ __sysreg_gpr_x22, 22\n"
".equ __sysreg_gpr_x23, 23\n"
".equ __sysreg_gpr_x24, 24\n"
".equ __sysreg_gpr_x25, 25\n"
".equ __sysreg_gpr_x26, 26\n"
".equ __sysreg_gpr_x27, 27\n"
".equ __sysreg_gpr_x28, 28\n"
".equ __sysreg_gpr_x29, 29\n"
".equ __sysreg_gpr_x30, 30\n"
".equ __sysreg_gpr_xzr, 31\n"
".macro mrs_s rt, sreg\n"
".inst (0xd5300000 | ((\\sreg) << 5) | __sysreg_gpr_\\rt)\n"
".endm\n"
".macro msr_s sreg, rt\n"
".inst (0xd5100000 | ((\\sreg) << 5) | __sysreg_gpr_\\rt)\n"
".endm\n"
".endif\n");
#endif

/* 1. Definiciones de acceso estándar */
#define read_sysreg(r) ({					\
	u64 __val;						\
	asm volatile("mrs %0, " __stringify(r) : "=r" (__val));	\
	__val;							\
})

#define write_sysreg(v, r) do {					\
	u64 __val = (u64)(v);					\
	asm volatile("msr " __stringify(r) ", %x0"		\
		     : : "rZ" (__val));				\
} while (0)

#define read_sysreg_s(r) ({					\
	u64 __val;						\
	asm volatile("mrs_s %0, " __stringify(r) : "=r" (__val)); \
	__val;							\
})

#define write_sysreg_s(v, r) do {				\
	u64 __val = (u64)(v);					\
	asm volatile("msr_s " __stringify(r) ", %x0"		\
		     : : "rZ" (__val));				\
} while (0)

/* Macro para modificar bits de un registro */
#define sysreg_clear_set(sysreg, clear, set) do {			\
	u64 __scs_val = read_sysreg(sysreg);				\
	u64 __scs_new = (__scs_val & ~(u64)(clear)) | (set);		\
	if (__scs_new != __scs_val)					\
		write_sysreg(__scs_new, sysreg);			\
} while (0)

/* Variant using read_sysreg_s/write_sysreg_s (numeric sysreg ID) */
#define sysreg_clear_set_s(sysreg, clear, set) do {			\
	u64 __scs_val = read_sysreg_s(sysreg);				\
	u64 __scs_new = (__scs_val & ~(u64)(clear)) | (set);		\
	if (__scs_new != __scs_val)					\
		write_sysreg_s(__scs_new, sysreg);			\
} while (0)

/* SCTLR_ELx bit definitions (for C code) */
#ifndef SCTLR_ELx_M
#define SCTLR_ELx_M		(1UL << 0)
#endif

/* 2. Macros para Ensamblador Inline (Corregidas) */
#define __mrs_s(v, r) "mrs_s " v ", " __stringify(r)
#define __msr_s(r, v) "msr_s " __stringify(r) ", " v

/* Registro PAR para KVM */
#define read_sysreg_par() read_sysreg(par_el1)

#endif /* __ASSEMBLY__ */

/* 3. Capa 1: Definición matemática pura (Sin funciones de C) */
#ifndef sys_reg
#define sys_reg(op0, op1, crn, crm, op2) \
	((((op0) & 3) << 14) | (((op1) & 7) << 11) | (((crn) & 15) << 7) | \
	 (((crm) & 15) << 3) | (((op2) & 7) << 0))
#endif

#ifndef sys_reg_Op0
#define sys_reg_Op0(id)		(((id) >> 14) & 0x3)
#endif
#ifndef sys_reg_Op1
#define sys_reg_Op1(id)		(((id) >> 11) & 0x7)
#endif
#ifndef sys_reg_CRn
#define sys_reg_CRn(id)		(((id) >> 7) & 0xf)
#endif
#ifndef sys_reg_CRm
#define sys_reg_CRm(id)		(((id) >> 3) & 0xf)
#endif
#ifndef sys_reg_Op2
#define sys_reg_Op2(id)		((id) & 0x7)
#endif

/* 4. Registros Críticos Manuales (Capa 2) */
#define SYS_MIDR_EL1			sys_reg(3, 0, 0, 0, 0)
#define SYS_MPIDR_EL1			sys_reg(3, 0, 0, 0, 5)
#define SYS_REVIDR_EL1			sys_reg(3, 0, 0, 0, 6)
#define SYS_SCTLR_EL1			sys_reg(3, 0, 1, 0, 0)
#define SYS_CPACR_EL1			sys_reg(3, 0, 1, 0, 2)
#define SYS_PAR_EL1			sys_reg(3, 0, 7, 4, 0)
#define SYS_ICC_PMR_EL1			sys_reg(3, 0, 4, 6, 0)
#define SYS_RNDR_EL0			sys_reg(3, 3, 2, 4, 0)

/* Auto-generated register definitions (from arch/arm64/tools/sysreg via gen-sysreg.awk).
 * Must be included BEFORE the #ifndef fallbacks below so the generated file
 * takes precedence and the fallbacks only activate for any remaining gaps. */
#if defined(__has_include)
#if __has_include(<asm/sysreg-defs.h>)
#include <asm/sysreg-defs.h>
#endif
#else
#include <asm/sysreg-defs.h>
#endif

/* EL1 translation/fault registers required by KVM hypervisor */
#ifndef SYS_TTBR0_EL1
#define SYS_TTBR0_EL1			sys_reg(3, 0, 2, 0, 0)
#endif
#ifndef SYS_TTBR1_EL1
#define SYS_TTBR1_EL1			sys_reg(3, 0, 2, 0, 1)
#endif
#ifndef SYS_TCR_EL1
#define SYS_TCR_EL1			sys_reg(3, 0, 2, 0, 2)
#endif
#ifndef SYS_AFSR0_EL1
#define SYS_AFSR0_EL1			sys_reg(3, 0, 5, 1, 0)
#endif
#ifndef SYS_AFSR1_EL1
#define SYS_AFSR1_EL1			sys_reg(3, 0, 5, 1, 1)
#endif
#ifndef SYS_ESR_EL1
#define SYS_ESR_EL1			sys_reg(3, 0, 5, 2, 0)
#endif
#ifndef SYS_FAR_EL1
#define SYS_FAR_EL1			sys_reg(3, 0, 6, 0, 0)
#endif
#ifndef SYS_MAIR_EL1
#define SYS_MAIR_EL1			sys_reg(3, 0, 10, 2, 0)
#endif
#ifndef SYS_AMAIR_EL1
#define SYS_AMAIR_EL1			sys_reg(3, 0, 10, 3, 0)
#endif
#ifndef SYS_CONTEXTIDR_EL1
#define SYS_CONTEXTIDR_EL1		sys_reg(3, 0, 13, 0, 1)
#endif

/* EL2 system registers required by KVM hypervisor */
#ifndef SYS_ZCR_EL2
#define SYS_ZCR_EL2			sys_reg(3, 4, 1, 2, 0)
#endif
#ifndef SYS_HFGRTR_EL2
#define SYS_HFGRTR_EL2			sys_reg(3, 4, 1, 3, 0)
#endif
#ifndef SYS_HFGWTR_EL2
#define SYS_HFGWTR_EL2			sys_reg(3, 4, 1, 3, 1)
#endif
#ifndef SYS_VSESR_EL2
#define SYS_VSESR_EL2			sys_reg(3, 4, 5, 2, 3)
#endif

/* Hard-defines canónicos para rutas C/LTO cuando falta sysreg-defs.h */
#ifndef SYS_ICC_SRE_EL1
#define SYS_ICC_SRE_EL1			sys_reg(3, 0, 12, 12, 5)
#endif
#ifndef SYS_DISR_EL1
#define SYS_DISR_EL1			sys_reg(3, 0, 12, 1, 1)
#endif
#ifndef SYS_CNTP_CTL_EL02
#define SYS_CNTP_CTL_EL02		sys_reg(3, 5, 14, 2, 1)
#endif
#ifndef SYS_CNTP_CVAL_EL02
#define SYS_CNTP_CVAL_EL02		sys_reg(3, 5, 14, 2, 2)
#endif
#ifndef SYS_PMMIR_EL1
#define SYS_PMMIR_EL1			sys_reg(3, 0, 9, 14, 6)
#endif
#ifndef SYS_ICC_IAR1_EL1
#define SYS_ICC_IAR1_EL1		sys_reg(3, 0, 12, 12, 0)
#endif
#ifndef SYS_ICC_EOIR1_EL1
#define SYS_ICC_EOIR1_EL1		sys_reg(3, 0, 12, 12, 1)
#endif
#ifndef SYS_ICC_DIR_EL1
#define SYS_ICC_DIR_EL1		sys_reg(3, 0, 12, 11, 1)
#endif
#ifndef SYS_ICC_BPR1_EL1
#define SYS_ICC_BPR1_EL1		sys_reg(3, 0, 12, 12, 3)
#endif
#ifndef SYS_ICC_CTLR_EL1
#define SYS_ICC_CTLR_EL1		sys_reg(3, 0, 12, 12, 4)
#endif
#ifndef SYS_ICC_SGI1R_EL1
#define SYS_ICC_SGI1R_EL1		sys_reg(3, 0, 12, 11, 5)
#endif
#ifndef SYS_ICC_IGRPEN1_EL1
#define SYS_ICC_IGRPEN1_EL1		sys_reg(3, 0, 12, 12, 7)
#endif
#ifndef SYS_ICC_AP0R0_EL1
#define SYS_ICC_AP0R0_EL1		sys_reg(3, 0, 12, 8, 4)
#endif
#ifndef SYS_ICC_AP0R1_EL1
#define SYS_ICC_AP0R1_EL1		sys_reg(3, 0, 12, 8, 5)
#endif
#ifndef SYS_ICC_AP0R2_EL1
#define SYS_ICC_AP0R2_EL1		sys_reg(3, 0, 12, 8, 6)
#endif
#ifndef SYS_ICC_AP0R3_EL1
#define SYS_ICC_AP0R3_EL1		sys_reg(3, 0, 12, 8, 7)
#endif
#ifndef SYS_ICC_AP1R0_EL1
#define SYS_ICC_AP1R0_EL1		sys_reg(3, 0, 12, 9, 0)
#endif
#ifndef SYS_ICC_AP1R1_EL1
#define SYS_ICC_AP1R1_EL1		sys_reg(3, 0, 12, 9, 1)
#endif
#ifndef SYS_ICC_AP1R2_EL1
#define SYS_ICC_AP1R2_EL1		sys_reg(3, 0, 12, 9, 2)
#endif
#ifndef SYS_ICC_AP1R3_EL1
#define SYS_ICC_AP1R3_EL1		sys_reg(3, 0, 12, 9, 3)
#endif
#ifndef SYS_PMBIDR_EL1
#define SYS_PMBIDR_EL1			sys_reg(3, 0, 9, 10, 7)
#endif
#ifndef SYS_PMSIDR_EL1
#define SYS_PMSIDR_EL1			sys_reg(3, 0, 9, 9, 7)
#endif
#ifndef SYS_PMSCR_EL1
#define SYS_PMSCR_EL1			sys_reg(3, 0, 9, 9, 0)
#endif
#ifndef SYS_PMBLIMITR_EL1
#define SYS_PMBLIMITR_EL1		sys_reg(3, 0, 9, 10, 0)
#endif
#ifndef SYS_PMBPTR_EL1
#define SYS_PMBPTR_EL1			sys_reg(3, 0, 9, 10, 1)
#endif
#ifndef SYS_PMBSR_EL1
#define SYS_PMBSR_EL1			sys_reg(3, 0, 9, 10, 3)
#endif
#ifndef SYS_PMSIRR_EL1
#define SYS_PMSIRR_EL1			sys_reg(3, 0, 9, 9, 2)
#endif
#ifndef SYS_PMSICR_EL1
#define SYS_PMSICR_EL1			sys_reg(3, 0, 9, 9, 3)
#endif
#ifndef SYS_PMSFCR_EL1
#define SYS_PMSFCR_EL1			sys_reg(3, 0, 9, 9, 4)
#endif
#ifndef SYS_PMSEVFR_EL1
#define SYS_PMSEVFR_EL1			sys_reg(3, 0, 9, 9, 5)
#endif
#ifndef SYS_PMSLATFR_EL1
#define SYS_PMSLATFR_EL1		sys_reg(3, 0, 9, 9, 6)
#endif
#ifndef SYS_TRBIDR_EL1
#define SYS_TRBIDR_EL1			sys_reg(3, 0, 9, 11, 7)
#endif
#ifndef SYS_AMEVCNTR0_CORE_EL0
#define SYS_AMEVCNTR0_CORE_EL0		sys_reg(3, 3, 13, 2, 0)
#endif
#ifndef SYS_AMEVCNTR0_CONST_EL0
#define SYS_AMEVCNTR0_CONST_EL0		sys_reg(3, 3, 13, 2, 1)
#endif
#ifndef SYS_GCR_EL1
#define SYS_GCR_EL1			sys_reg(3, 0, 1, 0, 6)
#endif
#ifndef SYS_RGSR_EL1
#define SYS_RGSR_EL1			sys_reg(3, 0, 1, 0, 5)
#endif
#ifndef SYS_TFSR_EL1
#define SYS_TFSR_EL1			sys_reg(3, 0, 5, 6, 0)
#endif
#ifndef SYS_TFSRE0_EL1
#define SYS_TFSRE0_EL1			sys_reg(3, 0, 5, 6, 1)
#endif
#ifndef SYS_APGAKEYLO_EL1
#define SYS_APGAKEYLO_EL1		sys_reg(3, 0, 2, 3, 0)
#endif
#ifndef SYS_APGAKEYHI_EL1
#define SYS_APGAKEYHI_EL1		sys_reg(3, 0, 2, 3, 1)
#endif

/* Pointer Auth Keys */
#define SYS_APIAKEYLO_EL1		sys_reg(3, 0, 2, 1, 0)
#define SYS_APIAKEYHI_EL1		sys_reg(3, 0, 2, 1, 1)
#define SYS_APIBKEYLO_EL1		sys_reg(3, 0, 2, 1, 2)
#define SYS_APIBKEYHI_EL1		sys_reg(3, 0, 2, 1, 3)
#define SYS_APDAKEYLO_EL1		sys_reg(3, 0, 2, 2, 0)
#define SYS_APDAKEYHI_EL1		sys_reg(3, 0, 2, 2, 1)
#define SYS_APDBKEYLO_EL1		sys_reg(3, 0, 2, 2, 2)
#define SYS_APDBKEYHI_EL1		sys_reg(3, 0, 2, 2, 3)

/* sysreg-defs.h is now included early (before #ifndef fallbacks) above. */

#ifndef __ASSEMBLY__
#ifdef SYS_SPSR_EL2
#define __SYSREG_EQ_SYS_SPSR_EL2 ".equ SYS_SPSR_EL2, " __stringify(SYS_SPSR_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_SPSR_EL2 ""
#endif
#ifdef SYS_SPSR_EL1
#define __SYSREG_EQ_SYS_SPSR_EL1 ".equ SYS_SPSR_EL1, " __stringify(SYS_SPSR_EL1) "\n"
#else
#define __SYSREG_EQ_SYS_SPSR_EL1 ""
#endif
#ifdef SYS_ESR_EL2
#define __SYSREG_EQ_SYS_ESR_EL2 ".equ SYS_ESR_EL2, " __stringify(SYS_ESR_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_ESR_EL2 ""
#endif
#ifdef SYS_ESR_EL1
#define __SYSREG_EQ_SYS_ESR_EL1 ".equ SYS_ESR_EL1, " __stringify(SYS_ESR_EL1) "\n"
#else
#define __SYSREG_EQ_SYS_ESR_EL1 ""
#endif
#ifdef SYS_ELR_EL2
#define __SYSREG_EQ_SYS_ELR_EL2 ".equ SYS_ELR_EL2, " __stringify(SYS_ELR_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_ELR_EL2 ""
#endif
#ifdef SYS_ELR_EL1
#define __SYSREG_EQ_SYS_ELR_EL1 ".equ SYS_ELR_EL1, " __stringify(SYS_ELR_EL1) "\n"
#else
#define __SYSREG_EQ_SYS_ELR_EL1 ""
#endif
#ifdef SYS_VSESR_EL2
#define __SYSREG_EQ_SYS_VSESR_EL2 ".equ SYS_VSESR_EL2, " __stringify(SYS_VSESR_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_VSESR_EL2 ""
#endif
#ifdef SYS_SCTLR_EL12
#define __SYSREG_EQ_SYS_SCTLR_EL12 ".equ SYS_SCTLR_EL12, " __stringify(SYS_SCTLR_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_SCTLR_EL12 ""
#endif
#ifdef SYS_TCR_EL12
#define __SYSREG_EQ_SYS_TCR_EL12 ".equ SYS_TCR_EL12, " __stringify(SYS_TCR_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_TCR_EL12 ""
#endif
#ifdef SYS_AFSR0_EL12
#define __SYSREG_EQ_SYS_AFSR0_EL12 ".equ SYS_AFSR0_EL12, " __stringify(SYS_AFSR0_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_AFSR0_EL12 ""
#endif
#ifdef SYS_AFSR1_EL12
#define __SYSREG_EQ_SYS_AFSR1_EL12 ".equ SYS_AFSR1_EL12, " __stringify(SYS_AFSR1_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_AFSR1_EL12 ""
#endif
#ifdef SYS_ESR_EL12
#define __SYSREG_EQ_SYS_ESR_EL12 ".equ SYS_ESR_EL12, " __stringify(SYS_ESR_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_ESR_EL12 ""
#endif
#ifdef SYS_ELR_EL12
#define __SYSREG_EQ_SYS_ELR_EL12 ".equ SYS_ELR_EL12, " __stringify(SYS_ELR_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_ELR_EL12 ""
#endif
#ifdef SYS_TTBR0_EL12
#define __SYSREG_EQ_SYS_TTBR0_EL12 ".equ SYS_TTBR0_EL12, " __stringify(SYS_TTBR0_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_TTBR0_EL12 ""
#endif
#ifdef SYS_TTBR1_EL12
#define __SYSREG_EQ_SYS_TTBR1_EL12 ".equ SYS_TTBR1_EL12, " __stringify(SYS_TTBR1_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_TTBR1_EL12 ""
#endif
#ifdef SYS_MAIR_EL12
#define __SYSREG_EQ_SYS_MAIR_EL12 ".equ SYS_MAIR_EL12, " __stringify(SYS_MAIR_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_MAIR_EL12 ""
#endif
#ifdef SYS_AMAIR_EL12
#define __SYSREG_EQ_SYS_AMAIR_EL12 ".equ SYS_AMAIR_EL12, " __stringify(SYS_AMAIR_EL12) "\n"
#else
#define __SYSREG_EQ_SYS_AMAIR_EL12 ""
#endif
#ifdef SYS_SCTLR_EL2
#define __SYSREG_EQ_SYS_SCTLR_EL2 ".equ SYS_SCTLR_EL2, " __stringify(SYS_SCTLR_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_SCTLR_EL2 ""
#endif
#ifdef SYS_ICH_VTR_EL2
#define __SYSREG_EQ_SYS_ICH_VTR_EL2 ".equ SYS_ICH_VTR_EL2, " __stringify(SYS_ICH_VTR_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_ICH_VTR_EL2 ""
#endif
#ifdef SYS_CNTV_CTL_EL0
#define __SYSREG_EQ_SYS_CNTV_CTL_EL0 ".equ SYS_CNTV_CTL_EL0, " __stringify(SYS_CNTV_CTL_EL0) "\n"
#else
#define __SYSREG_EQ_SYS_CNTV_CTL_EL0 ""
#endif
#ifdef SYS_CNTV_CVAL_EL0
#define __SYSREG_EQ_SYS_CNTV_CVAL_EL0 ".equ SYS_CNTV_CVAL_EL0, " __stringify(SYS_CNTV_CVAL_EL0) "\n"
#else
#define __SYSREG_EQ_SYS_CNTV_CVAL_EL0 ""
#endif
#ifdef SYS_CNTV_CTL_EL02
#define __SYSREG_EQ_SYS_CNTV_CTL_EL02 ".equ SYS_CNTV_CTL_EL02, " __stringify(SYS_CNTV_CTL_EL02) "\n"
#else
#define __SYSREG_EQ_SYS_CNTV_CTL_EL02 ""
#endif
#ifdef SYS_CNTV_CVAL_EL02
#define __SYSREG_EQ_SYS_CNTV_CVAL_EL02 ".equ SYS_CNTV_CVAL_EL02, " __stringify(SYS_CNTV_CVAL_EL02) "\n"
#else
#define __SYSREG_EQ_SYS_CNTV_CVAL_EL02 ""
#endif
#ifdef SYS_ICH_HCR_EL2
#define __SYSREG_EQ_SYS_ICH_HCR_EL2 ".equ SYS_ICH_HCR_EL2, " __stringify(SYS_ICH_HCR_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_ICH_HCR_EL2 ""
#endif
#ifdef SYS_ICH_ELRSR_EL2
#define __SYSREG_EQ_SYS_ICH_ELRSR_EL2 ".equ SYS_ICH_ELRSR_EL2, " __stringify(SYS_ICH_ELRSR_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_ICH_ELRSR_EL2 ""
#endif
#ifdef SYS_ICH_LR0_EL2
#define __SYSREG_EQ_SYS_ICH_LR0_EL2 ".equ SYS_ICH_LR0_EL2, " __stringify(SYS_ICH_LR0_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR1_EL2 ".equ SYS_ICH_LR1_EL2, " __stringify(SYS_ICH_LR1_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR2_EL2 ".equ SYS_ICH_LR2_EL2, " __stringify(SYS_ICH_LR2_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR3_EL2 ".equ SYS_ICH_LR3_EL2, " __stringify(SYS_ICH_LR3_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR4_EL2 ".equ SYS_ICH_LR4_EL2, " __stringify(SYS_ICH_LR4_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR5_EL2 ".equ SYS_ICH_LR5_EL2, " __stringify(SYS_ICH_LR5_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR6_EL2 ".equ SYS_ICH_LR6_EL2, " __stringify(SYS_ICH_LR6_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR7_EL2 ".equ SYS_ICH_LR7_EL2, " __stringify(SYS_ICH_LR7_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR8_EL2 ".equ SYS_ICH_LR8_EL2, " __stringify(SYS_ICH_LR8_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR9_EL2 ".equ SYS_ICH_LR9_EL2, " __stringify(SYS_ICH_LR9_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR10_EL2 ".equ SYS_ICH_LR10_EL2, " __stringify(SYS_ICH_LR10_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR11_EL2 ".equ SYS_ICH_LR11_EL2, " __stringify(SYS_ICH_LR11_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR12_EL2 ".equ SYS_ICH_LR12_EL2, " __stringify(SYS_ICH_LR12_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR13_EL2 ".equ SYS_ICH_LR13_EL2, " __stringify(SYS_ICH_LR13_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR14_EL2 ".equ SYS_ICH_LR14_EL2, " __stringify(SYS_ICH_LR14_EL2) "\n"
#define __SYSREG_EQ_SYS_ICH_LR15_EL2 ".equ SYS_ICH_LR15_EL2, " __stringify(SYS_ICH_LR15_EL2) "\n"
#else
#define __SYSREG_EQ_SYS_ICH_LR0_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR1_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR2_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR3_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR4_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR5_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR6_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR7_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR8_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR9_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR10_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR11_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR12_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR13_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR14_EL2 ""
#define __SYSREG_EQ_SYS_ICH_LR15_EL2 ""
#endif

#ifndef __SYSREG_S_EQU_INLINE_DEF
#define __SYSREG_S_EQU_INLINE_DEF
asm(
".ifndef __SYSREG_S_EQU_DEFINED\n"
".set __SYSREG_S_EQU_DEFINED, 1\n"
__SYSREG_EQ_SYS_SPSR_EL2
__SYSREG_EQ_SYS_SPSR_EL1
__SYSREG_EQ_SYS_ESR_EL2
__SYSREG_EQ_SYS_ESR_EL1
__SYSREG_EQ_SYS_ELR_EL2
__SYSREG_EQ_SYS_ELR_EL1
__SYSREG_EQ_SYS_VSESR_EL2
__SYSREG_EQ_SYS_SCTLR_EL12
__SYSREG_EQ_SYS_TCR_EL12
__SYSREG_EQ_SYS_AFSR0_EL12
__SYSREG_EQ_SYS_AFSR1_EL12
__SYSREG_EQ_SYS_ESR_EL12
__SYSREG_EQ_SYS_ELR_EL12
__SYSREG_EQ_SYS_TTBR0_EL12
__SYSREG_EQ_SYS_TTBR1_EL12
__SYSREG_EQ_SYS_MAIR_EL12
__SYSREG_EQ_SYS_AMAIR_EL12
__SYSREG_EQ_SYS_SCTLR_EL2
__SYSREG_EQ_SYS_ICH_VTR_EL2
__SYSREG_EQ_SYS_CNTV_CTL_EL0
__SYSREG_EQ_SYS_CNTV_CVAL_EL0
__SYSREG_EQ_SYS_CNTV_CTL_EL02
__SYSREG_EQ_SYS_CNTV_CVAL_EL02
__SYSREG_EQ_SYS_ICH_HCR_EL2
__SYSREG_EQ_SYS_ICH_ELRSR_EL2
__SYSREG_EQ_SYS_ICH_LR0_EL2
__SYSREG_EQ_SYS_ICH_LR1_EL2
__SYSREG_EQ_SYS_ICH_LR2_EL2
__SYSREG_EQ_SYS_ICH_LR3_EL2
__SYSREG_EQ_SYS_ICH_LR4_EL2
__SYSREG_EQ_SYS_ICH_LR5_EL2
__SYSREG_EQ_SYS_ICH_LR6_EL2
__SYSREG_EQ_SYS_ICH_LR7_EL2
__SYSREG_EQ_SYS_ICH_LR8_EL2
__SYSREG_EQ_SYS_ICH_LR9_EL2
__SYSREG_EQ_SYS_ICH_LR10_EL2
__SYSREG_EQ_SYS_ICH_LR11_EL2
__SYSREG_EQ_SYS_ICH_LR12_EL2
__SYSREG_EQ_SYS_ICH_LR13_EL2
__SYSREG_EQ_SYS_ICH_LR14_EL2
__SYSREG_EQ_SYS_ICH_LR15_EL2
".endif\n");
#endif
#endif

/* 6. SHIFTS y Constantes faltantes (Capa 4) */
#define ID_AA64MMFR1_VMIDBITS_SHIFT	4
#define ID_AA64MMFR1_VMIDBITS_8		1
#define ID_AA64MMFR1_VMIDBITS_16	2

#ifndef pstate_field
#define pstate_field(op1, op2)		(((op1) << 11) | ((op2) << 0))
#endif
#ifndef PSTATE_Imm_shift
#define PSTATE_Imm_shift		3
#endif
#ifndef PSTATE_SSBS
#define PSTATE_SSBS			pstate_field(3, 1)
#endif
#ifndef SCTLR_ELx_DSSBS
#define SCTLR_ELx_DSSBS			BIT(44)
#endif
#ifndef SCTLR_ELx_TCF_SHIFT
#define SCTLR_ELx_TCF_SHIFT		40
#endif
#ifndef SCTLR_ELx_TCF_MASK
#define SCTLR_ELx_TCF_MASK		(UL(0x3) << SCTLR_ELx_TCF_SHIFT)
#endif
#ifndef SCTLR_ELx_TCF_NONE
#define SCTLR_ELx_TCF_NONE		(UL(0x0) << SCTLR_ELx_TCF_SHIFT)
#endif
#ifndef ID_AA64MMFR1_ECBHB_SHIFT
#define ID_AA64MMFR1_ECBHB_SHIFT	60
#endif

/* Constantes existentes (se mantienen) */
#define ID_AA64PFR0_EL1_SHIFT		4
#define ID_AA64PFR0_EL0_SHIFT		0
#define ID_AA64PFR0_FP_SHIFT		16
#define ID_AA64PFR0_ASIMD_SHIFT		20
#define ID_AA64PFR0_SVE_SHIFT		32
#define ID_AA64PFR0_CSV2_SHIFT		56

#define ID_AA64MMFR0_PARANGE_SHIFT	0
#define ID_AA64MMFR0_BIGENDEL_SHIFT	8
#define ID_AA64MMFR0_BIGENDEL0_SHIFT	16
#define ID_AA64MMFR0_TGRAN16_SHIFT	20
#define ID_AA64MMFR0_TGRAN64_SHIFT	24
#define ID_AA64MMFR0_TGRAN4_SHIFT	28

#define ID_AA64MMFR0_TGRAN4_SUPPORTED_MIN	0x0
#define ID_AA64MMFR0_TGRAN4_SUPPORTED_MAX	0x7
#define ID_AA64MMFR0_TGRAN64_SUPPORTED_MIN	0x0
#define ID_AA64MMFR0_TGRAN64_SUPPORTED_MAX	0x7
#define ID_AA64MMFR0_TGRAN16_SUPPORTED_MIN	0x1
#define ID_AA64MMFR0_TGRAN16_SUPPORTED_MAX	0xf

#define ID_AA64DFR0_BRPS_SHIFT		12
#define ID_AA64DFR0_WRPS_SHIFT		20

#ifndef ID_AA64DFR0_PMUVER_8_0
#define ID_AA64DFR0_PMUVER_8_0		0x1
#endif
#ifndef ID_AA64DFR0_PMUVER_8_1
#define ID_AA64DFR0_PMUVER_8_1		0x4
#endif
#ifndef ID_AA64DFR0_PMUVER_8_4
#define ID_AA64DFR0_PMUVER_8_4		0x5
#endif
#ifndef ID_AA64DFR0_PMUVER_8_5
#define ID_AA64DFR0_PMUVER_8_5		0x6
#endif

#define ID_AA64PFR0_EL1_32BIT_64BIT	0x2
#define ID_AA64PFR0_EL0_32BIT_64BIT	0x2

#ifndef SCTLR_ELx_ATA
#define SCTLR_ELx_ATA			BIT(43)
#endif

#ifndef ID_AA64PFR0_SVE
#define ID_AA64PFR0_SVE			0x1
#endif
#ifndef ID_AA64PFR0_RAS_V1
#define ID_AA64PFR0_RAS_V1		0x1
#endif
#ifndef ID_AA64PFR0_AMU
#define ID_AA64PFR0_AMU			0x1
#endif

#ifndef ID_AA64ISAR0_TLB_RANGE
#define ID_AA64ISAR0_TLB_RANGE		0x2
#endif

#ifndef ID_AA64PFR1_SSBS_PSTATE_ONLY
#define ID_AA64PFR1_SSBS_PSTATE_ONLY	1
#endif

#ifndef ID_AA64ISAR1_API_IMP_DEF
#define ID_AA64ISAR1_API_IMP_DEF	0x1
#endif
#ifndef ID_AA64ISAR1_GPI_IMP_DEF
#define ID_AA64ISAR1_GPI_IMP_DEF	0x1
#endif

#ifndef ID_AA64PFR1_BT_BTI
#define ID_AA64PFR1_BT_BTI		0x1
#endif
#ifndef ID_AA64PFR1_MTE
#define ID_AA64PFR1_MTE			0x2
#endif

#ifndef ID_AA64ISAR2_WFXT_SUPPORTED
#define ID_AA64ISAR2_WFXT_SUPPORTED	0x2
#endif

#ifndef ID_AA64ZFR0_SVEVER_SVE2
#define ID_AA64ZFR0_SVEVER_SVE2		0x1
#endif
#ifndef ID_AA64ZFR0_AES
#define ID_AA64ZFR0_AES			0x1
#endif
#ifndef ID_AA64ZFR0_AES_PMULL
#define ID_AA64ZFR0_AES_PMULL		0x2
#endif
#ifndef ID_AA64ZFR0_BITPERM
#define ID_AA64ZFR0_BITPERM		0x1
#endif
#ifndef ID_AA64ZFR0_BF16
#define ID_AA64ZFR0_BF16		0x1
#endif
#ifndef ID_AA64ZFR0_SHA3
#define ID_AA64ZFR0_SHA3		0x1
#endif
#ifndef ID_AA64ZFR0_SM4
#define ID_AA64ZFR0_SM4			0x1
#endif
#ifndef ID_AA64ZFR0_I8MM
#define ID_AA64ZFR0_I8MM		0x1
#endif
#ifndef ID_AA64ZFR0_F32MM
#define ID_AA64ZFR0_F32MM		0x1
#endif
#ifndef ID_AA64ZFR0_F64MM
#define ID_AA64ZFR0_F64MM		0x1
#endif

#ifndef ID_AA64PFR1_SSBS_PSTATE_INSNS
#define ID_AA64PFR1_SSBS_PSTATE_INSNS	2
#endif

#ifndef SYS_MPIDR_SAFE_VAL
#define SYS_MPIDR_SAFE_VAL		(BIT(31))
#endif

#ifndef SYS_PAR_EL1_F
#define SYS_PAR_EL1_F			BIT(0)
#endif
#ifndef SYS_PAR_EL1_FST
#define SYS_PAR_EL1_FST			GENMASK(6, 1)
#endif

#ifndef MAIR_ATTR_NORMAL_TAGGED
#define MAIR_ATTR_NORMAL_TAGGED		UL(0xf0)
#endif
#ifndef MAIR_ATTR_MASK
#define MAIR_ATTR_MASK			UL(0xff)
#endif
#ifndef MAIR_ATTRIDX
#define MAIR_ATTRIDX(attr, idx)		((attr) << ((idx) * 8))
#endif

#ifndef SYS_GCR_EL1_RRND
#define SYS_GCR_EL1_RRND		(BIT(16))
#endif
#ifndef SYS_GCR_EL1_EXCL_MASK
#define SYS_GCR_EL1_EXCL_MASK		0xffffUL
#endif
#ifndef KERNEL_GCR_EL1
#define KERNEL_GCR_EL1			(SYS_GCR_EL1_RRND | SYS_GCR_EL1_EXCL_MASK)
#endif

#ifndef SYS_RGSR_EL1_SEED_SHIFT
#define SYS_RGSR_EL1_SEED_SHIFT		8
#endif
#ifndef SYS_RGSR_EL1_SEED_MASK
#define SYS_RGSR_EL1_SEED_MASK		0xffffUL
#endif

#ifndef SYS_PMSCR_EL1_E0SPE_SHIFT
#define SYS_PMSCR_EL1_E0SPE_SHIFT	0
#endif
#ifndef SYS_PMSCR_EL1_E1SPE_SHIFT
#define SYS_PMSCR_EL1_E1SPE_SHIFT	1
#endif
#ifndef SYS_PMSCR_EL1_CX_SHIFT
#define SYS_PMSCR_EL1_CX_SHIFT		3
#endif
#ifndef SYS_PMSCR_EL1_PA_SHIFT
#define SYS_PMSCR_EL1_PA_SHIFT		4
#endif
#ifndef SYS_PMSCR_EL1_TS_SHIFT
#define SYS_PMSCR_EL1_TS_SHIFT		5
#endif
#ifndef SYS_PMSCR_EL1_PCT_SHIFT
#define SYS_PMSCR_EL1_PCT_SHIFT		6
#endif

#ifndef SYS_PMSIRR_EL1_RND_SHIFT
#define SYS_PMSIRR_EL1_RND_SHIFT	0
#endif
#ifndef SYS_PMSIRR_EL1_INTERVAL_SHIFT
#define SYS_PMSIRR_EL1_INTERVAL_SHIFT	8
#endif
#ifndef SYS_PMSIRR_EL1_INTERVAL_MASK
#define SYS_PMSIRR_EL1_INTERVAL_MASK	0xffffffUL
#endif

#ifndef SYS_PMSFCR_EL1_FE_SHIFT
#define SYS_PMSFCR_EL1_FE_SHIFT		0
#endif
#ifndef SYS_PMSFCR_EL1_FT_SHIFT
#define SYS_PMSFCR_EL1_FT_SHIFT		1
#endif
#ifndef SYS_PMSFCR_EL1_FL_SHIFT
#define SYS_PMSFCR_EL1_FL_SHIFT		2
#endif
#ifndef SYS_PMSFCR_EL1_B_SHIFT
#define SYS_PMSFCR_EL1_B_SHIFT		16
#endif
#ifndef SYS_PMSFCR_EL1_LD_SHIFT
#define SYS_PMSFCR_EL1_LD_SHIFT		17
#endif
#ifndef SYS_PMSFCR_EL1_ST_SHIFT
#define SYS_PMSFCR_EL1_ST_SHIFT		18
#endif

#ifndef SYS_PMSLATFR_EL1_MINLAT_SHIFT
#define SYS_PMSLATFR_EL1_MINLAT_SHIFT	0
#endif

#ifndef SYS_PMBLIMITR_EL1_E_SHIFT
#define SYS_PMBLIMITR_EL1_E_SHIFT	0
#endif

#ifndef SYS_PMBSR_EL1_S_SHIFT
#define SYS_PMBSR_EL1_S_SHIFT		17
#endif
#ifndef SYS_PMBSR_EL1_DL_SHIFT
#define SYS_PMBSR_EL1_DL_SHIFT		19
#endif

#ifndef SYS_PMBSR_EL1_COLL_SHIFT
#define SYS_PMBSR_EL1_COLL_SHIFT	16
#endif
#ifndef SYS_PMBSR_EL1_EC_SHIFT
#define SYS_PMBSR_EL1_EC_SHIFT		26
#endif
#ifndef SYS_PMBSR_EL1_EC_MASK
#define SYS_PMBSR_EL1_EC_MASK		0x3fUL
#endif
#ifndef SYS_PMBSR_EL1_EC_BUF
#define SYS_PMBSR_EL1_EC_BUF		(0x0UL << SYS_PMBSR_EL1_EC_SHIFT)
#endif
#ifndef SYS_PMBSR_EL1_EC_FAULT_S1
#define SYS_PMBSR_EL1_EC_FAULT_S1	(0x24UL << SYS_PMBSR_EL1_EC_SHIFT)
#endif
#ifndef SYS_PMBSR_EL1_EC_FAULT_S2
#define SYS_PMBSR_EL1_EC_FAULT_S2	(0x25UL << SYS_PMBSR_EL1_EC_SHIFT)
#endif
#ifndef SYS_PMBSR_EL1_BUF_BSC_SHIFT
#define SYS_PMBSR_EL1_BUF_BSC_SHIFT	0
#endif
#ifndef SYS_PMBSR_EL1_BUF_BSC_MASK
#define SYS_PMBSR_EL1_BUF_BSC_MASK	0x3fUL
#endif
#ifndef SYS_PMBSR_EL1_BUF_BSC_FULL
#define SYS_PMBSR_EL1_BUF_BSC_FULL	(0x1UL << SYS_PMBSR_EL1_BUF_BSC_SHIFT)
#endif

#ifndef SYS_PMBIDR_EL1_ALIGN_SHIFT
#define SYS_PMBIDR_EL1_ALIGN_SHIFT	0
#endif
#ifndef SYS_PMBIDR_EL1_ALIGN_MASK
#define SYS_PMBIDR_EL1_ALIGN_MASK	0xfU
#endif
#ifndef SYS_PMBIDR_EL1_P_SHIFT
#define SYS_PMBIDR_EL1_P_SHIFT		4
#endif

#ifndef SYS_PMSIDR_EL1_FE_SHIFT
#define SYS_PMSIDR_EL1_FE_SHIFT		0
#endif
#ifndef SYS_PMSIDR_EL1_FT_SHIFT
#define SYS_PMSIDR_EL1_FT_SHIFT		1
#endif
#ifndef SYS_PMSIDR_EL1_FL_SHIFT
#define SYS_PMSIDR_EL1_FL_SHIFT		2
#endif
#ifndef SYS_PMSIDR_EL1_ARCHINST_SHIFT
#define SYS_PMSIDR_EL1_ARCHINST_SHIFT	3
#endif
#ifndef SYS_PMSIDR_EL1_LDS_SHIFT
#define SYS_PMSIDR_EL1_LDS_SHIFT	4
#endif
#ifndef SYS_PMSIDR_EL1_ERND_SHIFT
#define SYS_PMSIDR_EL1_ERND_SHIFT	5
#endif
#ifndef SYS_PMSIDR_EL1_INTERVAL_SHIFT
#define SYS_PMSIDR_EL1_INTERVAL_SHIFT	8
#endif
#ifndef SYS_PMSIDR_EL1_INTERVAL_MASK
#define SYS_PMSIDR_EL1_INTERVAL_MASK	0xfUL
#endif
#ifndef SYS_PMSIDR_EL1_MAXSIZE_SHIFT
#define SYS_PMSIDR_EL1_MAXSIZE_SHIFT	12
#endif
#ifndef SYS_PMSIDR_EL1_MAXSIZE_MASK
#define SYS_PMSIDR_EL1_MAXSIZE_MASK	0xfUL
#endif
#ifndef SYS_PMSIDR_EL1_COUNTSIZE_SHIFT
#define SYS_PMSIDR_EL1_COUNTSIZE_SHIFT	16
#endif
#ifndef SYS_PMSIDR_EL1_COUNTSIZE_MASK
#define SYS_PMSIDR_EL1_COUNTSIZE_MASK	0xfUL
#endif

#ifdef __ASSEMBLY__
#undef SYS_AMUSERENR_EL0
#define SYS_AMUSERENR_EL0	((((3) & 3) << 14) | (((3) & 7) << 11) | (((13) & 15) << 7) | (((2) & 15) << 3) | (((3) & 7) << 0))
#undef SYS_DISR_EL1
#define SYS_DISR_EL1		((((3) & 3) << 14) | (((0) & 7) << 11) | (((12) & 15) << 7) | (((1) & 15) << 3) | (((1) & 7) << 0))

#undef SCTLR_ELx_M
#define SCTLR_ELx_M		(1 << 0)

#undef MAIR_ATTR_DEVICE_nGnRnE
#define MAIR_ATTR_DEVICE_nGnRnE	0x00
#undef MAIR_ATTR_DEVICE_nGnRE
#define MAIR_ATTR_DEVICE_nGnRE	0x04
#undef MAIR_ATTR_NORMAL_NC
#define MAIR_ATTR_NORMAL_NC	0x44
#undef MAIR_ATTR_NORMAL
#define MAIR_ATTR_NORMAL	0xff
#undef MAIR_ATTR_NORMAL_iNC_oWB
#define MAIR_ATTR_NORMAL_iNC_oWB	0xf4

#undef ID_AA64MMFR0_PARANGE_MAX
#define ID_AA64MMFR0_PARANGE_MAX	0x5
#endif

#ifndef ZCR_ELx_LEN_SIZE
#define ZCR_ELx_LEN_SIZE		4
#endif

#ifndef SYS_ID_PFR0_EL1
#define SYS_ID_PFR0_EL1			sys_reg(3, 0, 0, 1, 0)
#endif
#ifndef SYS_ID_PFR1_EL1
#define SYS_ID_PFR1_EL1			sys_reg(3, 0, 0, 1, 1)
#endif
#ifndef SYS_ID_DFR0_EL1
#define SYS_ID_DFR0_EL1			sys_reg(3, 0, 0, 1, 2)
#endif
#ifndef SYS_ID_MMFR0_EL1
#define SYS_ID_MMFR0_EL1		sys_reg(3, 0, 0, 1, 4)
#endif
#ifndef SYS_ID_MMFR1_EL1
#define SYS_ID_MMFR1_EL1		sys_reg(3, 0, 0, 1, 5)
#endif
#ifndef SYS_ID_MMFR2_EL1
#define SYS_ID_MMFR2_EL1		sys_reg(3, 0, 0, 1, 6)
#endif
#ifndef SYS_ID_MMFR3_EL1
#define SYS_ID_MMFR3_EL1		sys_reg(3, 0, 0, 1, 7)
#endif
#ifndef SYS_ID_ISAR0_EL1
#define SYS_ID_ISAR0_EL1		sys_reg(3, 0, 0, 2, 0)
#endif
#ifndef SYS_ID_ISAR1_EL1
#define SYS_ID_ISAR1_EL1		sys_reg(3, 0, 0, 2, 1)
#endif
#ifndef SYS_ID_ISAR2_EL1
#define SYS_ID_ISAR2_EL1		sys_reg(3, 0, 0, 2, 2)
#endif
#ifndef SYS_ID_ISAR3_EL1
#define SYS_ID_ISAR3_EL1		sys_reg(3, 0, 0, 2, 3)
#endif
#ifndef SYS_ID_ISAR4_EL1
#define SYS_ID_ISAR4_EL1		sys_reg(3, 0, 0, 2, 4)
#endif
#ifndef SYS_ID_ISAR5_EL1
#define SYS_ID_ISAR5_EL1		sys_reg(3, 0, 0, 2, 5)
#endif
#ifndef SYS_ID_MMFR4_EL1
#define SYS_ID_MMFR4_EL1		sys_reg(3, 0, 0, 2, 6)
#endif
#ifndef SYS_ID_ISAR6_EL1
#define SYS_ID_ISAR6_EL1		sys_reg(3, 0, 0, 2, 7)
#endif
#ifndef SYS_MVFR0_EL1
#define SYS_MVFR0_EL1			sys_reg(3, 0, 0, 3, 0)
#endif
#ifndef SYS_MVFR1_EL1
#define SYS_MVFR1_EL1			sys_reg(3, 0, 0, 3, 1)
#endif
#ifndef SYS_MVFR2_EL1
#define SYS_MVFR2_EL1			sys_reg(3, 0, 0, 3, 2)
#endif
#ifndef SYS_ID_PFR2_EL1
#define SYS_ID_PFR2_EL1			sys_reg(3, 0, 0, 3, 4)
#endif
#ifndef SYS_ID_DFR1_EL1
#define SYS_ID_DFR1_EL1			sys_reg(3, 0, 0, 3, 5)
#endif
#ifndef SYS_ID_MMFR5_EL1
#define SYS_ID_MMFR5_EL1		sys_reg(3, 0, 0, 3, 6)
#endif
#ifndef SYS_CNTFRQ_EL0
#define SYS_CNTFRQ_EL0			sys_reg(3, 3, 14, 0, 0)
#endif

/* Bits de control */
#define SCTLR_ELx_ENIA			BIT(31)
#define SCTLR_ELx_ENIB			BIT(30)
#define SCTLR_ELx_ENDA			BIT(13)
#define SCTLR_ELx_ENDB			BIT(12)
#define CPACR_EL1_ZEN_EL0EN		(BIT(17))
#define CPACR_EL1_ZEN_EL1EN		(BIT(16))

/* 7. Bloque de constantes MMU para ensamblador */
#ifdef __ASSEMBLY__
#include <asm/gpr-num.h>

/* Valores pre-calculados para Motorola Edge 40 Neo (MT6879) */
#define INIT_SCTLR_EL1_MMU_ON  UL(0x2034f4d91d)
#define INIT_SCTLR_EL1_MMU_OFF UL(0x30500800)
#define INIT_SCTLR_EL2_MMU_ON  UL(0x30ed183d)
#define INIT_SCTLR_EL2_MMU_OFF UL(0x30c50830)

/* Alias de registro para evitar errores de expresión constante */
#undef SYS_SCTLR_EL12
#define SYS_SCTLR_EL12         ((((3) & 3) << 14) | (((5) & 7) << 11) | (((1) & 15) << 7) | (((0) & 15) << 3) | (((0) & 7) << 0))

.ifndef __SYSREG_ASM_MRSMSR_DEFINED
.set __SYSREG_ASM_MRSMSR_DEFINED, 1
.macro mrs_s, rt, sreg
	.inst 0xd5300000 | ((\sreg) << 5) | (.L__gpr_num_\rt)
.endm
.macro msr_s, sreg, rt
	.inst 0xd5100000 | ((\sreg) << 5) | (.L__gpr_num_\rt)
.endm
.endif

#ifndef SB_BARRIER_INSN
#define SB_BARRIER_INSN	dsb nsh
#endif

#ifndef SET_PSTATE_TCO
#define SET_PSTATE_TCO(x)	nop
#endif

#ifndef SYS_TFSR_EL1_TF0_SHIFT
#define SYS_TFSR_EL1_TF0_SHIFT	0
#endif

#ifndef SCTLR_ELx_ENIA_SHIFT
#define SCTLR_ELx_ENIA_SHIFT	31
#endif

#ifndef SYS_TFSRE0_EL1
#define SYS_TFSRE0_EL1	((((3) & 3) << 14) | (((0) & 7) << 11) | (((5) & 15) << 7) | (((6) & 15) << 3) | (((1) & 7) << 0))
#endif

#ifndef SYS_ICC_CTLR_EL1
#define SYS_ICC_CTLR_EL1	((((3) & 3) << 14) | (((0) & 7) << 11) | (((12) & 15) << 7) | (((12) & 15) << 3) | (((4) & 7) << 0))
#endif

#ifndef SYS_VBAR_EL12
#define SYS_VBAR_EL12	((((3) & 3) << 14) | (((5) & 7) << 11) | (((12) & 15) << 7) | (((0) & 15) << 3) | (((0) & 7) << 0))
#endif
#ifndef SYS_TCR_EL12
#define SYS_TCR_EL12	((((3) & 3) << 14) | (((5) & 7) << 11) | (((2) & 15) << 7) | (((0) & 15) << 3) | (((2) & 7) << 0))
#endif
#ifndef SYS_TTBR0_EL12
#define SYS_TTBR0_EL12	((((3) & 3) << 14) | (((5) & 7) << 11) | (((2) & 15) << 7) | (((0) & 15) << 3) | (((0) & 7) << 0))
#endif
#ifndef SYS_TTBR1_EL12
#define SYS_TTBR1_EL12	((((3) & 3) << 14) | (((5) & 7) << 11) | (((2) & 15) << 7) | (((0) & 15) << 3) | (((1) & 7) << 0))
#endif
#ifndef SYS_MAIR_EL12
#define SYS_MAIR_EL12	((((3) & 3) << 14) | (((5) & 7) << 11) | (((10) & 15) << 7) | (((2) & 15) << 3) | (((0) & 7) << 0))
#endif
#endif

#ifndef __ASSEMBLY__
#ifndef SET_PSTATE_PAN
#define SET_PSTATE_PAN(x)	"nop"
#endif
#ifndef SET_PSTATE_UAO
#define SET_PSTATE_UAO(x)	"nop"
#endif
#ifndef SET_PSTATE_SSBS
#define SET_PSTATE_SSBS(x)	"nop"
#endif
#ifndef SET_PSTATE_TCO
#define SET_PSTATE_TCO(x)	"nop"
#endif

#ifndef set_pstate_pan
#define set_pstate_pan(x)	asm volatile(SET_PSTATE_PAN(x))
#endif
#ifndef set_pstate_uao
#define set_pstate_uao(x)	asm volatile(SET_PSTATE_UAO(x))
#endif
#ifndef set_pstate_ssbs
#define set_pstate_ssbs(x)	asm volatile(SET_PSTATE_SSBS(x))
#endif
#endif

#include <asm/sysreg-fallbacks.h>

#endif /* __ASM_SYSREG_H */
