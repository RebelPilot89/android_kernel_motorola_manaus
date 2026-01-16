#ifndef _MCDI_COMMON_H
#define _MCDI_COMMON_H

#include <linux/types.h>

/* Global MCDI variables */
extern unsigned int mcdi_sysram_base;

/* MCDI mailbox functions */
unsigned int mcdi_mbox_read(unsigned int cmd);
void mcdi_mbox_write(unsigned int cmd, unsigned int val);

#endif /* _MCDI_COMMON_H */
