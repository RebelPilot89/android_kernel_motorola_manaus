#ifndef _MTK_MCDI_UTIL_H
#define _MTK_MCDI_UTIL_H

#include <linux/io.h>
#include <linux/mtk_sync_write.h>

/* Safe read/write macros that handle integer to pointer conversion */
#define mcdi_read(addr) ({ \
    uintptr_t __addr = (uintptr_t)(addr); \
    void __iomem *__ptr = (void __iomem *)(uintptr_t)__addr; \
    __raw_readl(__ptr); \
})

#define mcdi_write(addr, val) do { \
    uintptr_t __addr = (uintptr_t)(addr); \
    void __iomem *__ptr = (void __iomem *)(uintptr_t)__addr; \
    mt_reg_sync_writel(val, __ptr); \
} while (0)

#endif /* _MTK_MCDI_UTIL_H */
