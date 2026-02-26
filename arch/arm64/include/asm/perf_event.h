/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */

#ifndef __ASM_PERF_EVENT_H
#define __ASM_PERF_EVENT_H

/* Statistical profiling extension microarchitectural events */
#define	ARMV8_SPE_PERFCTR_SAMPLE_POP				0x4000
#define	ARMV8_SPE_PERFCTR_SAMPLE_FEED				0x4001
#define	ARMV8_SPE_PERFCTR_SAMPLE_FILTRATE			0x4002
#define	ARMV8_SPE_PERFCTR_SAMPLE_COLLISION			0x4003

/* AMUv1 architecture events */
#define	ARMV8_AMU_PERFCTR_CNT_CYCLES				0x4004
#define	ARMV8_AMU_PERFCTR_STALL_BACKEND_MEM			0x4005

/* long-latency read miss events */
#define	ARMV8_PMUV3_PERFCTR_L1I_CACHE_LMISS			0x4006
#define	ARMV8_PMUV3_PERFCTR_L2D_CACHE_LMISS_RD			0x4009
#define	ARMV8_PMUV3_PERFCTR_L2I_CACHE_LMISS			0x400A
#define	ARMV8_PMUV3_PERFCTR_L3D_CACHE_LMISS_RD			0x400B

/* additional latency from alignment events */
#define	ARMV8_PMUV3_PERFCTR_LDST_ALIGN_LAT			0x4020
#define	ARMV8_PMUV3_PERFCTR_LD_ALIGN_LAT			0x4021
#define	ARMV8_PMUV3_PERFCTR_ST_ALIGN_LAT			0x4022

/* Armv8.5 Memory Tagging Extension events */
#define	ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED			0x4024
#define	ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED_RD			0x4025
#define	ARMV8_MTE_PERFCTR_MEM_ACCESS_CHECKED_WR			0x4026


/*
 * Per-CPU PMCR: config reg
 */
#define ARMV8_PMU_PMCR_E	(1 << 0) /* Enable all counters */
#define ARMV8_PMU_PMCR_P	(1 << 1) /* Reset all counters */
#define ARMV8_PMU_PMCR_C	(1 << 2) /* Cycle counter reset */
#define ARMV8_PMU_PMCR_D	(1 << 3) /* CCNT counts every 64th cpu cycle */
#define ARMV8_PMU_PMCR_X	(1 << 4) /* Export to ETM */
#define ARMV8_PMU_PMCR_DP	(1 << 5) /* Disable CCNT if non-invasive debug*/
#define ARMV8_PMU_PMCR_LC	(1 << 6) /* Overflow on 64 bit cycle counter */
#define ARMV8_PMU_PMCR_LP	(1 << 7) /* Long event counter enable */
#define	ARMV8_PMU_PMCR_N_SHIFT	11	 /* Number of counters supported */
#define	ARMV8_PMU_PMCR_N_MASK	0x1f
#define	ARMV8_PMU_PMCR_MASK	0xff	 /* Mask for writable bits */

/*
 * PMOVSR: counters overflow flag status reg
 */
#define	ARMV8_PMU_OVSR_MASK		0xffffffff	/* Mask for writable bits */
#define	ARMV8_PMU_OVERFLOWED_MASK	ARMV8_PMU_OVSR_MASK

/*
 * PMXEVTYPER: Event selection reg
 */
#define	ARMV8_PMU_EVTYPE_MASK	0xc800ffff	/* Mask for writable bits */
#define	ARMV8_PMU_EVTYPE_EVENT	0xffff		/* Mask for EVENT bits */

/*
 * Event filters for PMUv3
 */
#define	ARMV8_PMU_EXCLUDE_EL1	(1U << 31)
#define	ARMV8_PMU_EXCLUDE_EL0	(1U << 30)
#define	ARMV8_PMU_INCLUDE_EL2	(1U << 27)

/*
 * PMUSERENR: user enable reg
 */
#define ARMV8_PMU_USERENR_MASK	0xf		/* Mask for writable bits */
#define ARMV8_PMU_USERENR_EN	(1 << 0) /* PMU regs can be accessed at EL0 */
#define ARMV8_PMU_USERENR_SW	(1 << 1) /* PMSWINC can be written at EL0 */
#define ARMV8_PMU_USERENR_CR	(1 << 2) /* Cycle counter can be read at EL0 */
#define ARMV8_PMU_USERENR_ER	(1 << 3) /* Event counter can be read at EL0 */

/* PMMIR_EL1.SLOTS mask */
#define ARMV8_PMU_SLOTS_MASK	0xff

#ifdef CONFIG_PERF_EVENTS
struct pt_regs;
extern unsigned long perf_instruction_pointer(struct pt_regs *regs);
extern unsigned long perf_misc_flags(struct pt_regs *regs);
#define perf_misc_flags(regs)	perf_misc_flags(regs)
#define perf_arch_bpf_user_pt_regs(regs) &regs->user_regs
#endif

#define perf_arch_fetch_caller_regs(regs, __ip) { \
	(regs)->pc = (__ip);    \
	(regs)->regs[29] = (unsigned long) __builtin_frame_address(0); \
	(regs)->sp = current_stack_pointer; \
	(regs)->pstate = PSR_MODE_EL1h;	\
}

#endif
