#ifndef __ASM_SYSREG_H
#define __ASM_SYSREG_H

#include <linux/bits.h>
#include <linux/stringify.h>

#ifndef __ASSEMBLY__
#include <linux/types.h>

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

/* 2. Macros para Ensamblador Inline (Corregidas para Clang) */
/* Estas no deben llevar paréntesis de función en su definición de texto */
#define __mrs_s(r, v) "mrs_s " v ", " __stringify(r)
#define __msr_s(r, v) "msr_s " __stringify(r) ", " v

/* Registro PAR para KVM */
#define read_sysreg_par() read_sysreg(par_el1)

#endif /* __ASSEMBLY__ */

/* 3. El generador de Motorola */
#ifndef sys_reg
#define sys_reg(op0, op1, crn, crm, op2) \
	((((op0) & 3) << 14) | (((op1) & 7) << 11) | (((crn) & 15) << 7) | \
	 (((crm) & 15) << 3) | (((op2) & 7) << 0))
#endif

/* 4. Registros Críticos Manuales */
#define SYS_MIDR_EL1			sys_reg(3, 0, 0, 0, 0)
#define SYS_MPIDR_EL1			sys_reg(3, 0, 0, 0, 5)
#define SYS_REVIDR_EL1			sys_reg(3, 0, 0, 0, 6)
#define SYS_SCTLR_EL1			sys_reg(3, 0, 1, 0, 0)
#define SYS_CPACR_EL1			sys_reg(3, 0, 1, 0, 2)
#define SYS_PAR_EL1			sys_reg(3, 0, 7, 4, 0)
#define SYS_ICC_PMR_EL1			sys_reg(3, 0, 4, 6, 0)
#define SYS_RNDR_EL0			sys_reg(3, 3, 2, 4, 0)

/* Pointer Auth Keys */
#define SYS_APIAKEYLO_EL1		sys_reg(3, 0, 2, 1, 0)
#define SYS_APIAKEYHI_EL1		sys_reg(3, 0, 2, 1, 1)
#define SYS_APIBKEYLO_EL1		sys_reg(3, 0, 2, 1, 2)
#define SYS_APIBKEYHI_EL1		sys_reg(3, 0, 2, 1, 3)
#define SYS_APDAKEYLO_EL1		sys_reg(3, 0, 2, 2, 0)
#define SYS_APDAKEYHI_EL1		sys_reg(3, 0, 2, 2, 1)
#define SYS_APDBKEYLO_EL1		sys_reg(3, 0, 2, 2, 2)
#define SYS_APDBKEYHI_EL1		sys_reg(3, 0, 2, 2, 3)

/* 5. Inclusión del generado (Motorola) */
#include <asm/sysreg-defs.h>

/* 6. SHIFTS y Constantes (Para cpufeature.h) */
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

#define ID_AA64PFR0_EL1_32BIT_64BIT	0x2
#define ID_AA64PFR0_EL0_32BIT_64BIT	0x2

/* Bits de control */
#define SCTLR_ELx_ENIA			BIT(31)
#define SCTLR_ELx_ENIB			BIT(30)
#define SCTLR_ELx_ENDA			BIT(13)
#define SCTLR_ELx_ENDB			BIT(12)
#define CPACR_EL1_ZEN_EL0EN		(BIT(17))
#define CPACR_EL1_ZEN_EL1EN		(BIT(16))

#include <asm/sysreg-fallbacks.h>

#endif /* __ASM_SYSREG_H */
