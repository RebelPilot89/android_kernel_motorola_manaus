/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */
#ifndef _SCHED_COMMON_H
#define _SCHED_COMMON_H

#if IS_ENABLED(CONFIG_NONLINEAR_FREQ_CTL)
extern void mtk_map_util_freq(void *data, unsigned long util, unsigned long freq,
			struct cpumask *cpumask, unsigned long *next_freq);
#else
#define mtk_map_util_freq(data, util, freq, cap, next_freq)
#endif /* CONFIG_NONLINEAR_FREQ_CTL */

#if IS_ENABLED(CONFIG_MTK_CPUFREQ_SUGOV_EXT)
DECLARE_PER_CPU(int, cpufreq_idle_cpu);
DECLARE_PER_CPU(spinlock_t, cpufreq_idle_cpu_lock);
unsigned long mtk_cpu_util(int cpu, unsigned long util_cfs,
				unsigned long max, enum schedutil_type type,
				struct task_struct *p);
int dequeue_idle_cpu(int cpu);
#endif
__always_inline
unsigned long mtk_uclamp_rq_util_with(struct rq *rq, unsigned long util,
				  struct task_struct *p);

/*
 * MTK uclamp hint — android_vendor_data1[] slot assignments
 *
 * This index MUST be kept in sync across all MTK modules that read or
 * write the per-task uclamp-hint flag:
 *   - drivers/misc/mediatek/sched/eas/sched_main.c  (hook handler)
 *   - drivers/misc/mediatek/sched/c2ps/common/src/c2ps_common.c (setter)
 *
 * Existing allocations in android_vendor_data1[]:
 *   [0]  reserved / unused
 *   [1]  cache-auditor: MPAM partid  (mpam_proto.c)
 *   [2]  cache-auditor: task rank    (mpam_proto.c)
 *   [3]  EAS big-task rotation ts   (eas/rotate.c)
 *   [4]  MTK uclamp hint flag       (this file)
 */
#define MTK_UCLAMP_HINT_IDX  4

#endif /* _SCHED_COMMON_H */
