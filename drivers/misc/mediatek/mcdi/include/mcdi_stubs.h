// SPDX-License-Identifier: GPL-2.0
// Stubs y macros para compilar mtk_mcdi_main.c
#ifndef __MCDI_STUBS_H__
#define __MCDI_STUBS_H__

#define NF_MCDI_STATE 4
#define NF_ANY_CORE_CPU_COND_INFO 5

// Estados MCDI
#define MCDI_STATE_WFI 0
#define MCDI_STATE_CPU_OFF 1
#define MCDI_STATE_CLUSTER_OFF 2
#define MCDI_STATE_SODI 3
#define MCDI_STATE_DPIDLE 4
#define MCDI_STATE_SODI3 5

// Estructura stub
struct mtk_mcdi_buf { int dummy; };

// Funciones stub
static inline void reset_mcdi_buf(struct mtk_mcdi_buf buf) {}
static inline void mcdi_buf_append(struct mtk_mcdi_buf buf, const char *str, ...) {}
static inline const char *get_mcdi_buf(struct mtk_mcdi_buf buf) { return ""; }
static inline int mcdi_fw_is_ready(void) { return 1; }

// Macros y defines faltantes
#define MCDI_MBOX_PAUSE_ACTION 0
#define MCDI_MBOX_PAUSE_ACK 0
#define MCDI_MBOX_AVAIL_CPU_MASK 0
#define MCDI_SYSRAM 0x0C570000

// Funciones stub
static inline void mcdi_log(const char *fmt, ...) {}
static inline int mcdi_get_cluster_off_cnt(int i) { return 0; }
static inline int mcdi_is_cpc_mode(void) { return 0; }
static inline void mcdi_set_state_lat(int a, int b, int c) {}
static inline void mcdi_set_state_res(int a, int b, int c) {}
static inline struct cpuidle_driver *mcdi_state_tbl_get(int cpu) { return NULL; }

// Macros stub
#define PROC_FOPS_MCDI(x) int dummy_proc_fops_##x(void) __attribute__((used)); int dummy_proc_fops_##x(void) { return 0; }
#define PROC_CREATE_MCDI(dir, x) do {} while(0)

// Additional stubs for governor_lib
#ifndef MCDI_MBOX_PENDING_ON_EVENT
#define MCDI_MBOX_PENDING_ON_EVENT 0
#endif
#ifndef CPU_CLUSTER
#define CPU_CLUSTER 0
#endif
#ifndef CPU_IN_OTHER_CLUSTER
#define CPU_IN_OTHER_CLUSTER 1
#endif
static inline unsigned int mcdi_get_raw_pwr_sta(void) { return 0; }

// Variables stub
static int state = 0;
static int info = 0;

#endif // __MCDI_STUBS_H__
