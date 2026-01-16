#ifndef _MT_CPUFREQ_H
#define _MT_CPUFREQ_H

#include <linux/types.h>

struct mt_cpu_freq_info {
    unsigned int cpu_id;
    unsigned int freq;
    unsigned int voltage;
};

unsigned int mt_cpufreq_get_cur_freq(unsigned int cpu);
unsigned int mt_cpufreq_get_cur_volt(unsigned int cpu);

#endif /* _MT_CPUFREQ_H */
