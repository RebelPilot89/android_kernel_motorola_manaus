#ifndef _TSCPU_SETTINGS_H
#define _TSCPU_SETTINGS_H

/* Thermal sensor CPU settings */
#define MAX_TS_PROBE_NUM 8
#define THERMAL_NAME_LENGTH 20

/* Number of CPU cores for thermal zone */
#define TZCPU_NO_CPU_CORES 8

struct tscpu_settings {
    int ts_probe_num;
    char thermal_name[THERMAL_NAME_LENGTH];
};

/* GPU loading function - prefer header fallback */
#include "mtk_gpu_loading.h"

#endif /* _TSCPU_SETTINGS_H */
