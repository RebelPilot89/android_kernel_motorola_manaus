#ifndef _MTK_MCDI_PLAT_H
#define _MTK_MCDI_PLAT_H

#include <linux/types.h>

/* Funciones de plataforma */
unsigned int mcdi_get_cluster_off_cnt(unsigned int cluster);
void mcdi_set_state_lat(int state, int cpu, unsigned int lat);
void mcdi_set_state_res(int state, int cpu, unsigned int res);

/* Funciones de registro */
void mcdi_log(const char *fmt, ...);
int mcdi_is_cpc_mode(void);

/* Funciones de mailbox */
void mcdi_mbox_write(unsigned int cmd, unsigned int val);
unsigned int mcdi_mbox_read(unsigned int cmd);

#endif /* _MTK_MCDI_PLAT_H */
