/* SPDX-License-Identifier: GPL-2.0 */
/*
 * mtk_ram_console.h - MediaTek RAM console API shim.
 *
 * On Linux 5.10+ the legacy mtk_ram_console driver has been superseded by
 * the upstream pstore/ramoops subsystem (CONFIG_PSTORE_RAM).  This header
 * is retained as a compatibility shim so that legacy driver headers that
 * still include it (e.g. gpu/mediatek/gpufreq/v1) can continue to compile.
 *
 * The persistent-log write path is provided by aee_sram_printk(), which is
 * declared in <mt-plat/aee.h> and implemented in
 * drivers/misc/mediatek/aee/mrdump/mboot_params.c.
 */

#ifndef __MTK_RAM_CONSOLE_H__
#define __MTK_RAM_CONSOLE_H__

#include <mt-plat/aee.h>

/*
 * mtk_ram_console_write() - write a message to the persistent RAM console.
 *
 * Alias for aee_sram_printk().  Kept for source-level compatibility with
 * out-of-tree MediaTek drivers that call this symbol directly.
 */
#define mtk_ram_console_write(fmt, args...)	aee_sram_printk(fmt, ##args)

#endif /* __MTK_RAM_CONSOLE_H__ */
