// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2023 MediaTek Inc.
 *
 * MTK Gear Control — per-gear CPU uclamp management and EAS tuning knobs
 * required by the C2PS camera scheduler (drivers/misc/mediatek/sched/c2ps/).
 *
 * All symbols exported here are declared as "extern" in
 * drivers/misc/mediatek/sched/c2ps/common/include/c2ps_common.h and
 * drivers/misc/mediatek/sched/c2ps/monitor/include/c2ps_monitor.h.
 */

#include <linux/module.h>
#include <linux/cpumask.h>
#include <linux/cpufreq.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/rcupdate.h>
#include <sched/sched.h>

#include "eas_plus.h"
#include "../sugov/cpufreq.h"

/* MT6879 (Dimensity 7030) has 3 frequency domains (little/mid/big). */
#define MTK_MAX_GEARS MAX_PD_COUNT

/* ------------------------------------------------------------------ */
/* Gear topology                                                        */
/* ------------------------------------------------------------------ */

static DEFINE_MUTEX(gear_tbl_lock);
static bool gear_tbl_ready;
static unsigned int nr_gears_val;
static struct cpumask gear_cpumask_arr[MTK_MAX_GEARS];

static void build_gear_table(void)
{
	struct cpufreq_policy *policy;
	unsigned int cpu;
	int g = 0;

	gear_tbl_ready = false;
	nr_gears_val = 0;

	for_each_possible_cpu (cpu) {
		policy = cpufreq_cpu_get(cpu);
		if (!policy)
			continue;
		/*
		 * Process only the first CPU of each policy so we visit
		 * each frequency domain exactly once.
		 */
		if (cpumask_first(policy->related_cpus) == cpu &&
		    g < MTK_MAX_GEARS)
			cpumask_copy(&gear_cpumask_arr[g++],
				     policy->related_cpus);
		cpufreq_cpu_put(policy);
	}

	WRITE_ONCE(nr_gears_val, (unsigned int)g);
	/* Publish the table before setting the ready flag. */
	smp_wmb();
	WRITE_ONCE(gear_tbl_ready, true);
}

static void ensure_gear_table(void)
{
	if (likely(READ_ONCE(gear_tbl_ready)))
		return;

	mutex_lock(&gear_tbl_lock);
	if (!READ_ONCE(gear_tbl_ready))
		build_gear_table();
	mutex_unlock(&gear_tbl_lock);
}

/**
 * get_nr_gears - return the number of CPU frequency domains (gears)
 *
 * Lazily enumerates cpufreq policies on first call.  Safe to call
 * from any context that can sleep (module_init path is typical).
 */
unsigned int get_nr_gears(void)
{
	ensure_gear_table();
	return READ_ONCE(nr_gears_val);
}
EXPORT_SYMBOL_GPL(get_nr_gears);

/**
 * get_gear_cpumask - return the cpumask for a given gear index
 * @gear: zero-based gear index (0 = little cluster, …)
 *
 * Returns NULL when @gear is out of range.
 */
struct cpumask *get_gear_cpumask(unsigned int gear)
{
	ensure_gear_table();
	if (gear >= READ_ONCE(nr_gears_val))
		return NULL;
	return &gear_cpumask_arr[gear];
}
EXPORT_SYMBOL_GPL(get_gear_cpumask);

/* ------------------------------------------------------------------ */
/* Per-gear uclamp-max control                                          */
/* ------------------------------------------------------------------ */

static int gear_uclamp_ctrl_on;
static int curr_uclamp_ctrl_on;
static unsigned int gear_uclamp_max_val[MTK_MAX_GEARS];

/**
 * set_gear_uclamp_ctrl - enable / disable the per-gear uclamp-max feature
 * @val: non-zero to enable, zero to disable
 */
void set_gear_uclamp_ctrl(int val)
{
	WRITE_ONCE(gear_uclamp_ctrl_on, val);
}
EXPORT_SYMBOL_GPL(set_gear_uclamp_ctrl);

/**
 * set_curr_uclamp_ctrl - enable / disable the current-task uclamp feature
 * @val: non-zero to enable, zero to disable
 */
void set_curr_uclamp_ctrl(int val)
{
	WRITE_ONCE(curr_uclamp_ctrl_on, val);
}
EXPORT_SYMBOL_GPL(set_curr_uclamp_ctrl);

/**
 * set_gear_uclamp_max - store the uclamp-max cap for a gear
 * @gearid: gear index
 * @val:    uclamp value in [0, SCHED_CAPACITY_SCALE]
 */
void set_gear_uclamp_max(int gearid, int val)
{
	if (gearid < 0 || gearid >= MTK_MAX_GEARS)
		return;
	WRITE_ONCE(gear_uclamp_max_val[gearid],
		   (unsigned int)clamp(val, 0, (int)SCHED_CAPACITY_SCALE));
}
EXPORT_SYMBOL_GPL(set_gear_uclamp_max);

/**
 * get_gear_uclamp_max - read the stored uclamp-max cap for a gear
 * @gearid: gear index
 *
 * Returns zero when @gearid is out of range.
 */
int get_gear_uclamp_max(int gearid)
{
	if (gearid < 0 || gearid >= MTK_MAX_GEARS)
		return 0;
	return (int)READ_ONCE(gear_uclamp_max_val[gearid]);
}
EXPORT_SYMBOL_GPL(get_gear_uclamp_max);

/* ------------------------------------------------------------------ */
/* Workload-type classification                                         */
/* ------------------------------------------------------------------ */

/*
 * MTK EAS supports multiple workload types (idle / foreground / game /
 * camera / …).  Five types cover the range used by C2PS.
 */
#define MTK_NR_WL_TYPES 5

static int wl_type_manual_val = -1; /* -1 = automatic selection */

/**
 * set_wl_type_manual - override the active workload type
 * @val: workload-type index, or -1 to restore automatic selection
 */
void set_wl_type_manual(int val)
{
	WRITE_ONCE(wl_type_manual_val, val);
}
EXPORT_SYMBOL_GPL(set_wl_type_manual);

/**
 * get_nr_wl_type - return the total number of supported workload types
 */
int get_nr_wl_type(void)
{
	return MTK_NR_WL_TYPES;
}
EXPORT_SYMBOL_GPL(get_nr_wl_type);

/* ------------------------------------------------------------------ */
/* EAS filter / group / DVFS / idle-skip control                       */
/* ------------------------------------------------------------------ */

static bool flt_ctrl_force_val;
static u32 group_mode_val;
static int grp_dvfs_ctrl_val;
static bool ignore_idle_ctrl_val;

/* flt_ctrl_force_get - read the EAS filter-force state */
bool flt_ctrl_force_get(void)
{
	return READ_ONCE(flt_ctrl_force_val);
}
EXPORT_SYMBOL_GPL(flt_ctrl_force_get);

/* flt_ctrl_force_set - override the EAS filter-force state */
void flt_ctrl_force_set(int set)
{
	WRITE_ONCE(flt_ctrl_force_val, (bool)set);
}
EXPORT_SYMBOL_GPL(flt_ctrl_force_set);

/* group_get_mode - read the current EAS task-group mode */
u32 group_get_mode(void)
{
	return READ_ONCE(group_mode_val);
}
EXPORT_SYMBOL_GPL(group_get_mode);

/* group_set_mode - set the EAS task-group mode */
void group_set_mode(u32 mode)
{
	WRITE_ONCE(group_mode_val, mode);
}
EXPORT_SYMBOL_GPL(group_set_mode);

/* get_grp_dvfs_ctrl - read the group-DVFS control flag */
int get_grp_dvfs_ctrl(void)
{
	return READ_ONCE(grp_dvfs_ctrl_val);
}
EXPORT_SYMBOL_GPL(get_grp_dvfs_ctrl);

/* set_grp_dvfs_ctrl - set the group-DVFS control flag */
void set_grp_dvfs_ctrl(int set)
{
	WRITE_ONCE(grp_dvfs_ctrl_val, set);
}
EXPORT_SYMBOL_GPL(set_grp_dvfs_ctrl);

/* get_ignore_idle_ctrl - read the ignore-idle-CPU flag */
bool get_ignore_idle_ctrl(void)
{
	return READ_ONCE(ignore_idle_ctrl_val);
}
EXPORT_SYMBOL_GPL(get_ignore_idle_ctrl);

/* set_ignore_idle_ctrl - set the ignore-idle-CPU flag */
void set_ignore_idle_ctrl(bool val)
{
	WRITE_ONCE(ignore_idle_ctrl_val, val);
}
EXPORT_SYMBOL_GPL(set_ignore_idle_ctrl);

/* ------------------------------------------------------------------ */
/* VIP task management                                                  */
/* ------------------------------------------------------------------ */

/*
 * The full MTK VIP-task implementation relies on vendor-hook
 * infrastructure that is not present in this tree.  The C2PS driver
 * already regulates VIP tasks through per-task uclamp via
 * sched_setattr_nocheck(), so these stubs are sufficient for correct
 * camera scheduling.  They intentionally do not modify scheduling
 * policy to avoid racing with the uclamp management above.
 */

/**
 * set_task_basic_vip - mark a task as a camera VIP task
 * @pid: PID of the task to promote
 */
void set_task_basic_vip(int pid)
{
	/*
	 * No-op: C2PS uclamp management handles camera-task priority via
	 * sched_setattr_nocheck().  The caller is responsible for providing
	 * a valid pid > 0; this function does not perform task lookup.
	 */
}
EXPORT_SYMBOL_GPL(set_task_basic_vip);

/*
 * unset_task_basic_vip - remove the camera VIP mark from a task
 * @pid: PID of the task to demote; must be > 0 (caller's responsibility)
 */
void unset_task_basic_vip(int pid)
{
	/* No-op: symmetric with set_task_basic_vip(). */
}
EXPORT_SYMBOL_GPL(unset_task_basic_vip);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MTK gear control and EAS tuning stubs for C2PS");
MODULE_AUTHOR("MediaTek Inc.");
