/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __KVM_MOTOROLA_FIX_C_H__
#define __KVM_MOTOROLA_FIX_C_H__

/* C-only compatibility fixes for KVM (no s3_ definitions) */
#include <asm/sysreg.h>

#ifndef SCTLR_ELx_M
#define SCTLR_ELx_M (1UL << 0)
#endif

#ifndef SYS_PAR_EL1_F
#define SYS_PAR_EL1_F (1UL << 0)
#endif

#ifndef SYS_PMBLIMITR_EL1_E_SHIFT
#define SYS_PMBLIMITR_EL1_E_SHIFT 0
#endif

#ifndef TRBLIMITR_ENABLE
#define TRBLIMITR_ENABLE (1UL << 0)
#endif

/* Define missing sys_reg values for C code */
#ifndef SYS_HFGWTR_EL2
#define SYS_HFGWTR_EL2 sys_reg(3, 4, 1, 1, 1)
#endif
#ifndef SYS_HFGRTR_EL2
#define SYS_HFGRTR_EL2 sys_reg(3, 4, 1, 1, 0)
#endif
#ifndef SYS_PMBIDR_EL1
#define SYS_PMBIDR_EL1 sys_reg(3, 0, 9, 10, 7)
#endif
#ifndef SYS_PMSCR_EL2
#define SYS_PMSCR_EL2 sys_reg(3, 4, 9, 9, 0)
#endif
#ifndef SYS_TRBIDR_EL1
#define SYS_TRBIDR_EL1 sys_reg(3, 0, 9, 11, 7)
#endif
#ifndef SYS_ICC_SRE_EL2
#define SYS_ICC_SRE_EL2 sys_reg(3, 4, 12, 9, 5)
#endif
#ifndef SYS_ICH_HCR_EL2
#define SYS_ICH_HCR_EL2 sys_reg(3, 4, 12, 11, 0)
#endif

#define ID_AA64DFR0_TRBE_SHIFT 44
#define TRBIDR_PROG (1UL << 0)

/* Masks and flags potentially missing on Motorola headers */
#ifndef HFGxTR_EL2_nSMPRI_EL1_MASK
#define HFGxTR_EL2_nSMPRI_EL1_MASK BIT(54)
#endif
#ifndef HFGxTR_EL2_nTPIDR2_EL0_MASK
#define HFGxTR_EL2_nTPIDR2_EL0_MASK BIT(55)
#endif

/* Missing SYS_* registers used in switch.c */
#ifndef SYS_AFSR1_EL1
#define SYS_AFSR1_EL1 sys_reg(3, 0, 5, 1, 1)
#endif
#ifndef SYS_MAIR_EL1
#define SYS_MAIR_EL1 sys_reg(3, 0, 10, 2, 0)
#endif
#ifndef SYS_AMAIR_EL1
#define SYS_AMAIR_EL1 sys_reg(3, 0, 10, 2, 1)
#endif
#ifndef SYS_APGAKEYLO_EL1
#define SYS_APGAKEYLO_EL1 sys_reg(3, 0, 2, 3, 0)
#endif
#ifndef SYS_APGAKEYHI_EL1
#define SYS_APGAKEYHI_EL1 sys_reg(3, 0, 2, 3, 1)
#endif

/* CPACR SMEN bits (may be absent in older headers) */
#ifndef CPACR_EL1_SMEN_EL0EN
#define CPACR_EL1_SMEN_EL0EN (1UL << 24)
#endif
#ifndef CPACR_EL1_SMEN_EL1EN
#define CPACR_EL1_SMEN_EL1EN (1UL << 25)
#endif

#ifndef CPACR_EL1_FPEN_EL1EN
#define CPACR_EL1_FPEN_EL1EN (1UL << 20)
#endif
#ifndef CPACR_EL1_FPEN_EL0EN
#define CPACR_EL1_FPEN_EL0EN (1UL << 21)
#endif

#ifndef ARM64_FEATURE_MASK
#define ARM64_FEATURE_MASK(field) GENMASK_ULL(field##_SHIFT + 3, field##_SHIFT)
#endif

#endif /* __KVM_MOTOROLA_FIX_C_H__ */
