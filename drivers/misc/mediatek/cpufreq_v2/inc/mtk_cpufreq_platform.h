#ifndef _MTK_CPUFREQ_PLATFORM_H
#define _MTK_CPUFREQ_PLATFORM_H

#include <linux/types.h>
#include <linux/cpufreq.h>

/* Estructuras básicas */

/* Definiciones de struct duplicadas, ver mtk_cpufreq_struct.h */


extern struct buck_ctrl_t buck_ctrl[NR_MT_BUCK];
extern struct pll_ctrl_t pll_ctrl[NR_MT_PLL];
unsigned char get_posdiv(struct pll_ctrl_t *pll_p);
unsigned char get_clkdiv(struct pll_ctrl_t *pll_p);
void aee_record_cpu_dvfs_step(int step);

/* Definiciones de operación */
#define VOLT_TOL        25000
#define POSDIV_1        0x0
#define POSDIV_2        0x1
#define POSDIV_4        0x2
#define POSDIV_8        0x3
#define POSDIV_16       0x4
#define POSDIV_MASK     0x7

/* Funciones de la plataforma */
extern struct mt_cpu_dvfs *id_to_cpu_dvfs(unsigned int id);
extern int mt_cpufreq_set_by_wfi_load_cluster(unsigned int cluster_id, 
                                               unsigned int freq);
extern void mt_cpufreq_set_voltage(unsigned int cluster_id, 
                                    unsigned int volt);
extern unsigned int mt_cpufreq_get_cur_volt(unsigned int cluster_id);
// extern int mt_cpufreq_update_volt(unsigned int cluster_id, 
//                                   unsigned int *volt_tbl, 
//                                   unsigned int nr_volt_tbl);

/* Funciones de registro y depuración */
extern void aee_record_cpu_dvfs_in(struct mt_cpu_dvfs *p);
extern void aee_record_cpu_dvfs_out(struct mt_cpu_dvfs *p);
extern void aee_record_cpu_volt(struct mt_cpu_dvfs *p, unsigned int volt);
extern void aee_record_freq_idx(struct mt_cpu_dvfs *p, int idx);

#endif /* _MTK_CPUFREQ_PLATFORM_H */
