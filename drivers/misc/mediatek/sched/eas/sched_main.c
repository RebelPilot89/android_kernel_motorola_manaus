// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021 MediaTek Inc.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/cpumask.h>
#include <linux/seq_file.h>
#include <linux/energy_model.h>
#include <linux/jump_label.h>
#include <trace/events/sched.h>
#include <trace/events/task.h>
#include <trace/hooks/sched.h>
#include <sched/sched.h>
#include "common.h"
#include "eas_plus.h"
#include "sched_sys_common.h"

#define CREATE_TRACE_POINTS
#include "eas_trace.h"

int mtk_sched_asym_cpucapacity = 1;

static inline void sched_asym_cpucapacity_init(void)
{
	struct perf_domain *pd;
	struct root_domain *rd;
	int pd_count = 0;

	preempt_disable();
	rd = cpu_rq(smp_processor_id())->rd;

	rcu_read_lock();
	pd = rcu_dereference(rd->pd);
	for (; pd; pd = pd->next)
		pd_count++;
	rcu_read_unlock();
	preempt_enable();
	if (pd_count <= 1)
		mtk_sched_asym_cpucapacity = 0;
}

static void sched_task_util_hook(void *data, struct sched_entity *se)
{
	if (trace_sched_task_util_enabled()) {
		struct task_struct *p;
		struct sched_avg *sa;

		if (!entity_is_task(se))
			return;

		p = container_of(se, struct task_struct, se);
		sa = &se->avg;

		trace_sched_task_util(p->pid, sa->util_avg,
				      sa->util_est.enqueued, sa->util_est.ewma);
	}
}

static void sched_task_uclamp_hook(void *data, struct sched_entity *se)
{
	if (trace_sched_task_uclamp_enabled()) {
		struct task_struct *p;
		struct sched_avg *sa;
		struct util_est ue;
		unsigned long util;

#if IS_ENABLED(CONFIG_UCLAMP_TASK)
		struct uclamp_se *uc_min_req, *uc_max_req;
#endif

		if (!entity_is_task(se))
			return;

		p = container_of(se, struct task_struct, se);
		sa = &se->avg;
		ue = READ_ONCE(se->avg.util_est);
		util = max(ue.ewma, ue.enqueued);
		util = max(util, READ_ONCE(se->avg.util_avg));

#if IS_ENABLED(CONFIG_UCLAMP_TASK)
		uc_min_req = &p->uclamp_req[UCLAMP_MIN];
		uc_max_req = &p->uclamp_req[UCLAMP_MAX];

		trace_sched_task_uclamp(
			p->pid, util, p->uclamp[UCLAMP_MIN].active,
			p->uclamp[UCLAMP_MIN].value,
			p->uclamp[UCLAMP_MAX].value, uc_min_req->user_defined,
			uc_min_req->value, uc_max_req->user_defined,
			uc_max_req->value);
#else
		trace_sched_task_uclamp(p->pid, util, 0, 0, 0, 0, 0, 0, 0);
#endif
	}
}

static int enqueue;
static int dequeue;
static void __maybe_unused sched_queue_task_hook(void *data, struct rq *rq,
						 struct task_struct *p,
						 int flags)
{
	int cpu = rq->cpu;
	int type = *(int *)data;
	if (trace_sched_queue_task_enabled()) {
		unsigned long util = READ_ONCE(rq->cfs.avg.util_avg);

		util = max_t(unsigned long, util,
			     READ_ONCE(rq->cfs.avg.util_est.enqueued));

#if IS_ENABLED(CONFIG_UCLAMP_TASK)
		trace_sched_queue_task(cpu, p->pid, type, util,
				       rq->uclamp[UCLAMP_MIN].value,
				       rq->uclamp[UCLAMP_MAX].value,
				       p->uclamp[UCLAMP_MIN].value,
				       p->uclamp[UCLAMP_MAX].value);
#else
		trace_sched_queue_task(cpu, p->pid, type, util, 0, 0, 0, 0);
#endif
	}

#if IS_ENABLED(CONFIG_MTK_CPUFREQ_SUGOV_EXT)
	spin_lock(&per_cpu(cpufreq_idle_cpu_lock, cpu));
	if ((type == dequeue) && dequeue_idle_cpu(cpu) &&
	    (flags & DEQUEUE_SLEEP))
		per_cpu(cpufreq_idle_cpu, cpu) = 1;
	else
		per_cpu(cpufreq_idle_cpu, cpu) = 0;
	spin_unlock(&per_cpu(cpufreq_idle_cpu_lock, cpu));
#endif
}

/*
 * mtk_uclamp_hint_handler - android_rvh_uclamp_eff_get handler
 *
 * Original MTK Implementation (Backported from 6.6)
 *
 * Intercepts the kernel's uclamp effective-value calculation for tasks
 * that have been marked by set_curr_uclamp_hint().  When the hint is
 * active, the handler substitutes the task's own requested UCLAMP_MAX
 * value and sets *ret = 1, signalling uclamp_eff_get() to use that
 * value instead of being capped by the system default.
 *
 * This enables C2PS camera pipeline tasks to drive their CPU frequency
 * to the level they need, bypassing sysctl_sched_util_clamp_max.
 */
#if IS_ENABLED(CONFIG_UCLAMP_TASK)
static void mtk_uclamp_hint_handler(void *data,
				    struct task_struct *p,
				    enum uclamp_id clamp_id,
				    struct uclamp_se *uclamp_max,
				    struct uclamp_se *uclamp_eff,
				    int *ret)
{
	if (clamp_id != UCLAMP_MAX)
		return;
	if (READ_ONCE(p->android_vendor_data1[MTK_UCLAMP_HINT_IDX]) == 0ULL)
		return;

	/* Let the task's own requested uclamp_max pass through uncapped. */
	*uclamp_eff = p->uclamp_req[UCLAMP_MAX];
	*ret = 1;
}
#endif /* CONFIG_UCLAMP_TASK */

static void mtk_sched_trace_init(void)
{
	int ret = 0;

	enqueue = 1;
	dequeue = -1;

#if IS_ENABLED(CONFIG_ANDROID_VENDOR_HOOKS)
	ret = register_trace_android_rvh_enqueue_task(sched_queue_task_hook,
						      &enqueue);
	if (ret)
		pr_info("register android_rvh_enqueue_task failed!\n");
	ret = register_trace_android_rvh_dequeue_task(sched_queue_task_hook,
						      &dequeue);
	if (ret)
		pr_info("register android_rvh_dequeue_task failed!\n");
#endif

	ret = register_trace_pelt_se_tp(sched_task_util_hook, NULL);
	if (ret)
		pr_info("register sched_task_util_hook failed!\n");

	ret = register_trace_pelt_se_tp(sched_task_uclamp_hook, NULL);
	if (ret)
		pr_info("register sched_task_uclamp_hook failed!\n");
}

static void mtk_sched_trace_exit(void)
{
	unregister_trace_pelt_se_tp(sched_task_util_hook, NULL);
	unregister_trace_pelt_se_tp(sched_task_uclamp_hook, NULL);
}

static int __init mtk_scheduler_init(void)
{
	int ret = 0;

	ret = init_sched_common_sysfs();
	if (ret)
		return ret;

	mtk_static_power_init();

#if IS_ENABLED(CONFIG_MTK_EAS)
	mtk_freq_limit_notifier_register();

	ret = init_sram_info();
	if (ret)
		return ret;

#if IS_ENABLED(CONFIG_ANDROID_VENDOR_HOOKS)
	ret = register_trace_android_rvh_find_busiest_group(
		mtk_find_busiest_group, NULL);
	if (ret)
		pr_info("register android_rvh_find_busiest_group failed\n");

	ret = register_trace_android_rvh_find_energy_efficient_cpu(
		mtk_find_energy_efficient_cpu, NULL);
	if (ret)
		pr_info("register android_rvh_find_energy_efficient_cpu failed\n");

	ret = register_trace_android_rvh_cpu_overutilized(mtk_cpu_overutilized,
							  NULL);
	if (ret)
		pr_info("register trace_android_rvh_cpu_overutilized failed\n");

	ret = register_trace_android_rvh_tick_entry(mtk_tick_entry, NULL);
	if (ret)
		pr_info("register android_rvh_tick_entry failed\n");

	ret = register_trace_android_vh_set_wake_flags(mtk_set_wake_flags,
						       NULL);
	if (ret)
		pr_info("register android_vh_set_wake_flags failed\n");

	ret = register_trace_android_rvh_update_cpu_capacity(
		mtk_update_cpu_capacity, NULL);
	if (ret)
		pr_info("register android_rvh_update_cpu_capacity failed\n");

#if IS_ENABLED(CONFIG_MTK_NEWIDLE_BALANCE)
	ret = register_trace_android_rvh_sched_newidle_balance(
		mtk_sched_newidle_balance, NULL);
	if (ret)
		pr_info("register android_rvh_sched_newidle_balance failed\n");
#endif
#endif
#endif

#if IS_ENABLED(CONFIG_ANDROID_VENDOR_HOOKS)
	ret = register_trace_android_vh_scheduler_tick(hook_scheduler_tick,
						       NULL);
	if (ret)
		pr_info("scheduler: register scheduler_tick hooks failed, returned %d\n",
			ret);

	ret = register_trace_android_rvh_after_enqueue_task(
		mtk_hook_after_enqueue_task, NULL);
	if (ret)
		pr_info("register android_rvh_after_enqueue_task failed, returned %d\n",
			ret);
#endif

#if IS_ENABLED(CONFIG_MTK_SCHED_BIG_TASK_ROTATE)
#if IS_ENABLED(CONFIG_ANDROID_VENDOR_HOOKS)
	ret = register_trace_android_rvh_new_task_stats(rotat_task_stats, NULL);
	if (ret)
		pr_info("register android_rvh_new_task_stats failed, returned %d\n",
			ret);
#endif

	ret = register_trace_task_newtask(rotat_task_newtask, NULL);
	if (ret)
		pr_info("register trace_task_newtask failed, returned %d\n",
			ret);
#endif
#if IS_ENABLED(CONFIG_ANDROID_VENDOR_HOOKS)
	ret = register_trace_android_rvh_select_task_rq_rt(
		mtk_select_task_rq_rt, NULL);
	if (ret)
		pr_info("register mtk_select_task_rq_rt hooks failed, returned %d\n",
			ret);
#endif

	sched_asym_cpucapacity_init();

	mtk_sched_trace_init();

#if IS_ENABLED(CONFIG_UCLAMP_TASK) && IS_ENABLED(CONFIG_ANDROID_VENDOR_HOOKS)
	ret = register_trace_android_rvh_uclamp_eff_get(
		mtk_uclamp_hint_handler, NULL);
	if (ret)
		pr_info("register android_rvh_uclamp_eff_get failed\n");
#endif

	return ret;
}

static void __exit mtk_scheduler_exit(void)
{
	mtk_sched_trace_exit();

#if IS_ENABLED(CONFIG_UCLAMP_TASK) && IS_ENABLED(CONFIG_ANDROID_VENDOR_HOOKS)
	unregister_trace_android_rvh_uclamp_eff_get(
		mtk_uclamp_hint_handler, NULL);
#endif

#if IS_ENABLED(CONFIG_ANDROID_VENDOR_HOOKS)
	unregister_trace_android_vh_scheduler_tick(hook_scheduler_tick, NULL);
#endif
#if IS_ENABLED(CONFIG_MTK_SCHED_BIG_TASK_ROTATE)
	unregister_trace_task_newtask(rotat_task_newtask, NULL);
#endif
	cleanup_sched_common_sysfs();
}

module_init(mtk_scheduler_init);
module_exit(mtk_scheduler_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MediaTek scheduler");
MODULE_AUTHOR("MediaTek Inc.");
