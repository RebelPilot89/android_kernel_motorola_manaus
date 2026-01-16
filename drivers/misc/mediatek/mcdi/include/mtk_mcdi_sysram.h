#ifndef _MTK_MCDI_SYSRAM_H
#define _MTK_MCDI_SYSRAM_H

/* Definiciones de constantes faltantes */
#define CPC_DORMANT_COUNTER           0x00000000
#define SYSRAM_CPC_CLUSTER_CNT        0x00000004
#define CPC_SPMC_PWR_STATUS           0x00000008
#define CPC_CPU_LATENCY(cpu)          (0x00000010 + (cpu) * 4)
#define CPC_CLUSTER_ON_LATENCY        0x00000030
#define CPC_CLUSTER_OFF_LATENCY       0x00000034
#define CPC_MCUSYS_LATENCY            0x00000038
#define CPC_CPU_ON_SW_HINT_CLR        0x00000040

/* Macros para perfilado */
#define PROF_OFF_CNT_REG(i)           (0x00000100 + (i) * 4)
#define PROF_ON_CNT_REG(i)            (0x00000120 + (i) * 4)
#define PROF_CPU_RATIO_REG(i)         (0x00000140 + (i) * 4)
#define PROF_CLUSTER_RATIO_REG(i)     (0x00000160 + (i) * 4)
#define SYSRAM_PROF_RARIO_DUR         0x00000180

/* Estados MCDI (delegado a encabezados de plataforma para evitar redefinición) */
#if 0
enum {
    MCDI_STATE_CPU_OFF = 0,
    MCDI_STATE_CLUSTER_OFF,
    MCDI_STATE_SODI,
    MCDI_STATE_SODI3,
    MCDI_STATE_DPIDLE,
    NF_MCDI_STATE
};
#endif

/* Configuración SYSRAM */
#define MCDI_SYSRAM_SIZE              0x1000
#ifndef MCDI_MBOX_PROF_CMD
#define MCDI_MBOX_PROF_CMD            0x00000200
#endif

#endif /* _MTK_MCDI_SYSRAM_H */
