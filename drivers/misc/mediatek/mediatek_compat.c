// SPDX-License-Identifier: GPL-2.0
/* Global weak compatibility stubs to satisfy missing platform symbols
 * Added to help complete the build for testing purpose only.
 */

 #include <linux/types.h>
 #include <linux/thermal.h>
 #include <linux/proc_fs.h>
 #include <linux/errno.h>
 #include <linux/printk.h>

/* Thermal immediate wrappers */
int __weak get_immediate_ts1_wrap(void) { return 0; }
int __weak get_immediate_ts2_wrap(void) { return 0; }
int __weak get_immediate_ts3_wrap(void) { return 0; }
int __weak get_immediate_ts4_wrap(void) { return 0; }
int __weak get_immediate_ts5_wrap(void) { return 0; }
int __weak get_immediate_ts6_wrap(void) { return 0; }
int __weak get_immediate_ts7_wrap(void) { return 0; }
int __weak get_immediate_ts8_wrap(void) { return 0; }

/* Generic immediate wrapper array fallback */
int (*__weak __aligned(8) get_immediate_tsX[8])(void) = { get_immediate_ts1_wrap, get_immediate_ts2_wrap, get_immediate_ts3_wrap, get_immediate_ts4_wrap, get_immediate_ts5_wrap, get_immediate_ts6_wrap, get_immediate_ts7_wrap, get_immediate_ts8_wrap };

/* tscpu/timers/vars */
int __weak __aligned(8) tscpu_debug_log = 0;
int __weak __aligned(8) mtktspmic_debug_log = 0;
int __weak __aligned(8) tscpu_g_curr_temp = 0;
int __weak __aligned(8) tscpu_g_curr_fp_factor = 0;
int __weak tscpu_get_temperature_range(void) { return 0; }
int __weak tscpu_get_curr_temp(void) { return 0; }
int __weak tscpu_get_curr_max_ts_temp(void) { return 0; }
void __weak tscpu_workqueue_start_timer(void) { }

/* upower / ppm placeholders */
void *__weak __aligned(8) p_upower_tbl_infos = NULL;
int __weak upower_bank_to_spower_bank(int b) { return 0; }
int __weak mt_spower_get_leakage(int a) { return 0; }

/* ppm/clients */
int __weak mt_ppm_register_client(void *c) { return 0; }

/* cpufreq / dvfs placeholders */
int __weak _mt_cpufreq_get_cpu_level(int cpu) { return 0; }
int __weak cpufreq_get_cluster_id(int cpu) { return 0; }
int __weak cpuhvfs_set_dvfs(unsigned int cpu, int val) { return 0; }
int __weak cpufreq_get_cluster_cpus(int cluster) { return 0; }
int __weak cpu_type_idx_get(int cpu) { return 0; }
int __weak get_original_table(void) { return 0; }

/* mcdi / cpc */
void *__weak __aligned(8) cpc_base = NULL;
int __weak get_pwr_stat_check_map(void) { return 0; }
int __weak mcdi_get_mcdi_idle_state(void) { return 0; }

/* idle / mcdi helpers */
int __weak mtk_idle_select(int arg) { return 0; }
int __weak mtk_get_gpu_loading(unsigned int *loading)
{
	if (loading)
		*loading = 0;
	return 0;
}

/* turbo and other flags */
int __weak turbo_flag;

/* miscellaneous stubs */
int __weak get_immediate_cpuL_wrap(void) { return 0; }
int __weak get_immediate_cpuB_wrap(void) { return 0; }
int __weak get_immediate_gpu_wrap(void) { return 0; }

/* safe no-op printk wrappers used by thermal code */
void __weak tscpu_dprintk(const char *fmt, ...) { }
void __weak tscpu_warn(const char *fmt, ...) { }

/* Additional weak stubs for remaining unresolved symbols */
void __weak mcdi_status_init(void) { }

/* cpufreq / dvfs arrays and placeholders (weak to let platform override) */
void *__weak __aligned(8) cpu_dvfs = NULL;
void *__weak __aligned(8) opp_tbls = NULL;
void *__weak __aligned(8) mt_cpufreq_regulator_map = NULL;
void *__weak __aligned(8) mt_cpufreq_dts_map = NULL;

int __weak cpuhvfs_set_cluster_on_off(int cluster, int on) { return 0; }
int __weak set_cur_volt_wrapper(unsigned int cpu, unsigned int v) { return 0; }
int __weak cpuhvfs_set_init_sta(void) { return 0; }
int __weak cpuhvfs_set_sched_dvfs_disable(int on) { return 0; }
int __weak prepare_pll_addr(void) { return 0; }
int __weak prepare_pmic_config(void) { return 0; }
int __weak cpufreq_get_nr_clusters(void) { return 1; }
int __weak cpuhvfs_pre_module_init(void) { return 0; }
int __weak cpuhvfs_module_init(void) { return 0; }

/* mml / GPU placeholders */
int __weak mml_drm_query_cap(void *a, void *b) { return 0; }
int __weak mml_drm_submit(void *a, void *b) { return 0; }
int __weak mml_drm_racing_stop_sync(void) { return 0; }
int __weak mml_drm_racing_config_sync(void) { return 0; }
void *__weak mml_get_plat_device(void) { return NULL; }
void *__weak mml_drm_get_context(void) { return NULL; }

/* additional generic weak stubs */

/* Small MML/GPU stubs */
struct mml_submit;
void __weak mml_drm_split_info(struct mml_submit *submit, struct mml_submit *submit_pq) { }
struct mml_drm_ctx;
void __weak mml_drm_put_context(struct mml_drm_ctx *ctx) { }

/* End of mediatek_compat.c */
