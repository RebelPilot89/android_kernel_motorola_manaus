// SPDX-License-Identifier: GPL-2.0
/* Compatibility stubs to satisfy linker when platform thermal monitor is not present */
#include <linux/thermal.h>
#include <linux/proc_fs.h>
#include "../../include/mt-plat/mtk_thermal_monitor.h"

int __weak mtk_thermal_get_temp(enum mtk_thermal_sensor_id id)
{
	return 0;
}

struct proc_dir_entry *__weak mtk_thermal_get_proc_drv_therm_dir_entry(void)
{
	return NULL;
}

/* Additional stubs */
int __weak tscpu_get_temperature_range(void) { return 0; }
int __weak tscpu_get_curr_temp(void) { return 0; }
int __weak tscpu_curr_cpu_temp;
int __weak tscpu_curr_gpu_temp;
int __weak tscpu_get_curr_max_ts_temp(void) { return 0; }
int __weak tscpu_cur_fp_factor;

int (*__weak __aligned(8) get_immediate_tsX[8])(void) = { 0 };

int __weak mtktspmic_cali_prepare(void) { return 0; }
int __weak mtktspmic_cali_prepare2(void) { return 0; }
int __weak mtktspmic_get_from_dts(void) { return 0; }
int __weak mtk_wcn_cmb_stub_query_ctrl(void) { return 0; }

void __weak tscpu_workqueue_start_timer(void) { }

void __weak tscpu_dprintk(const char *fmt, ...) { }
void __weak tscpu_warn(const char *fmt, ...) { }
void __weak set_taklking_flag(bool flag) { }

unsigned char __weak __aligned(8) upower_recognize_by_eem[8] = { 0 };
int __weak __aligned(8) degree_set[8] = { 0 };

struct thermal_zone_device *__weak mtk_thermal_zone_device_register_wrapper(char *type, int trips, void *devdata, const struct thermal_zone_device_ops *ops, int tc1, int tc2, int passive_delay, int polling_delay)
{
	return NULL;
}

void __weak mtk_thermal_zone_device_unregister_wrapper(struct thermal_zone_device *tz) { }

struct thermal_cooling_device *__weak mtk_thermal_cooling_device_register_wrapper(char *type, void *devdata, const struct thermal_cooling_device_ops *ops)
{
	return NULL;
}

struct thermal_cooling_device *__weak mtk_thermal_cooling_device_register_wrapper_extra(char *type, void *devdata, const struct thermal_cooling_device_ops *ops, const struct thermal_cooling_device_ops_extra *ops_ext)
{
	return NULL;
}

int __weak mtk_thermal_cooling_device_add_exit_point(struct thermal_cooling_device *cdev, int exit_point)
{
	return 0;
}

void __weak mtk_thermal_cooling_device_unregister_wrapper(struct thermal_cooling_device *cdev) { }

int __weak mtk_thermal_zone_bind_cooling_device_wrapper(struct thermal_zone_device *tz, int trip,
	struct thermal_cooling_device *cdev)
{
	return 0;
}

int __weak mtk_thermal_zone_bind_trigger_trip(struct thermal_zone_device *tz, int trip, int mode)
{
	return 0;
}

/* Misc variables used by thermal code */
int __weak __aligned(8) tscpu_debug_log = 0;
int __weak __aligned(8) mtktspmic_debug_log = 0;
unsigned int __weak __aligned(8) Num_of_GPU_OPP = 0;
unsigned int __weak __aligned(8) mtk_gpu_power[1] = {0};
unsigned int __weak __aligned(8) gpu_max_opp = 0;



/* Some wrapper getters */
int __weak mtktspmic_get_hw_temp(void) { return 0; }

/* get_immediate wrappers often pointed to functions in mtk_thermal.h */
int __weak get_immediate_cpuL_wrap(void) { return 0; }
int __weak get_immediate_cpuB_wrap(void) { return 0; }
int __weak get_immediate_gpu_wrap(void) { return 0; }
int __weak get_immediate_tsX_wrapper(void) { return 0; }

