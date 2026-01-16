 #define _NR_MT_BUCK                   3
 #define _NR_MT_PLL                    3

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef _MTK_CPUFREQ_CONFIG_H
#define _MTK_CPUFREQ_CONFIG_H

/* Configuración básica de CPUFreq */
#define NR_FREQ               16
 #define _NR_MT_CPU_DVFS        3
#define NR_CPU_LEVEL          2
#define CCI_MUX_TBL           NULL

/* Estructura mt_cpu_dvfs */
/* struct mt_cpu_dvfs está definida en mtk_cpufreq_struct.h */

#endif /* _MTK_CPUFREQ_CONFIG_H */
