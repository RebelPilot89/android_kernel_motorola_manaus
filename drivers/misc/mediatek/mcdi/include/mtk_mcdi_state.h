#ifndef _MTK_MCDI_STATE_H
#define _MTK_MCDI_STATE_H

/* Distributed tracking numbers */
#define DISTRIBUTE_NUM 16

/* Offset definitions for latency registers */
#define ID_OFS  0
#define AVG_OFS 1
#define MAX_OFS 2
#define CNT_OFS 3

/* CPU Latency Register Macros */
#define CPU_OFF_LATENCY_REG(ofs) (0x0C530000 + ((ofs) * 4))
#define CPU_ON_LATENCY_REG(ofs)  (0x0C530100 + ((ofs) * 4))

/* Cluster Latency Register Macros */
#define Cluster_OFF_LATENCY_REG(ofs) (0x0C530200 + ((ofs) * 4))
#define Cluster_ON_LATENCY_REG(ofs)  (0x0C530300 + ((ofs) * 4))

/* Profile Counter Registers */
#define PROF_OFF_CNT_REG(idx)     (0x0C540000 + ((idx) * 4))
#define PROF_ON_CNT_REG(idx)      (0x0C540100 + ((idx) * 4))
#define PROF_CPU_RATIO_REG(idx)   (0x0C540200 + ((idx) * 4))
#define PROF_CLUSTER_RATIO_REG(idx) (0x0C540300 + ((idx) * 4))

/* System RAM Profile Registers */
#define SYSRAM_PROF_RARIO_DUR     0x0C550000

/* MCDI Mailbox Commands */
#define MCDI_MBOX_PROF_CMD        0x0C560000
#define MCDI_MBOX_PROF_CLUSTER    0x0C560004

/* System RAM Base and Size */
#define MCDI_SYSRAM_BASE          0x0C570000
#define MCDI_SYSRAM_SIZE          0x1000

/* CPC (CPU Power Control) Registers */
#define CPC_DORMANT_COUNTER       0x0C580000
#define CPC_CPU_LATENCY(cpu)      (0x0C580100 + ((cpu) * 4))
#define CPC_CLUSTER_ON_LATENCY    0x0C580200
#define CPC_CLUSTER_OFF_LATENCY   0x0C580204
#define CPC_MCUSYS_LATENCY        0x0C580208
#define CPC_CPU_ON_SW_HINT_CLR    0x0C580300

/* External variable declarations */
extern unsigned int mcdi_sysram_base;

#endif /* _MTK_MCDI_STATE_H */
