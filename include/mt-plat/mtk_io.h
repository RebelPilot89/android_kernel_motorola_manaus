#ifndef _MTK_IO_H
#define _MTK_IO_H

#include <linux/io.h>
#include <linux/mtk_sync_write.h>

/* Check if ioremap_wc is already defined before redefining */
#ifndef ioremap_wc
#define ioremap_wc ioremap
#endif

#ifndef ioremap_wt
#define ioremap_wt ioremap
#endif

#endif /* _MTK_IO_H */
