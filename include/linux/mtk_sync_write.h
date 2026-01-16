#ifndef _LINUX_MTK_SYNC_WRITE_H
#define _LINUX_MTK_SYNC_WRITE_H

#include <linux/io.h>
#include <asm/barrier.h>

/*
 * MediaTek synchronization write/read functions
 * These provide memory barriers for register access
 */

static inline void mt_reg_sync_writel(u32 val, void __iomem *addr)
{
    writel(val, addr);
    mb(); /* memory barrier */
}

static inline u32 mt_reg_sync_readl(const void __iomem *addr)
{
    u32 val = readl(addr);
    mb(); /* memory barrier */
    return val;
}

#endif /* _LINUX_MTK_SYNC_WRITE_H */
