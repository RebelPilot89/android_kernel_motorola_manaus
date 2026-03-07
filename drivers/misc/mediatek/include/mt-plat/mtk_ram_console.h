/* SPDX-License-Identifier: GPL-2.0 */
/*
 * mtk_ram_console.h - MediaTek RAM console API shim.
 *
 * On Linux 5.10+ the legacy mtk_ram_console driver has been superseded by
 * the upstream pstore/ramoops subsystem (CONFIG_PSTORE_RAM). This header
 * remains as a compatibility shim for source files that still include it.
 *
 * The persistent-log write path is provided by aee_sram_printk(), declared
 * in <mt-plat/aee.h> and implemented in mboot_params.c.
 */

#ifndef __MTK_RAM_CONSOLE_H__
#define __MTK_RAM_CONSOLE_H__

#include <mt-plat/aee.h>

/* Keep source-level compatibility with legacy MediaTek callers. */
#define mtk_ram_console_write(fmt, args...) aee_sram_printk(fmt, ##args)

#endif /* __MTK_RAM_CONSOLE_H__ */
