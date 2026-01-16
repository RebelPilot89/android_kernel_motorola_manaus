#ifndef _MT_PLAT_AEE_H
#define _MT_PLAT_AEE_H

#include <linux/kernel.h>

/* Dummy AEE (Android Error Exceptions) definitions */
#define aee_kernel_warning(module, msg) \
    pr_warn("AEE Warning: %s: %s\n", module, msg)

#define aee_kernel_exception(module, msg) \
    pr_err("AEE Exception: %s: %s\n", module, msg)

#endif /* _MT_PLAT_AEE_H */
