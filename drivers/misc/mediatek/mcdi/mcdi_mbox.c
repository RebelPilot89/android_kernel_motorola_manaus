#include "include/mcdi_common.h"
#include <linux/io.h>

unsigned int __attribute__((weak)) mcdi_mbox_read(unsigned int cmd)
{
    /* Dummy implementation (weak symbol so a strong implementation can override it) */
    return 0;
}

void __attribute__((weak)) mcdi_mbox_write(unsigned int cmd, unsigned int val)
{
    /* Dummy implementation (weak symbol so a strong implementation can override it) */
}
