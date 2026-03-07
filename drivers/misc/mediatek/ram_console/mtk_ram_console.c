// SPDX-License-Identifier: GPL-2.0
/*
 * mtk_ram_console.c – MediaTek persistent RAM console for MT6879 / Dimensity 7030.
 *
 * Purpose
 * -------
 * When a custom kernel is flashed on the Motorola Edge 40 Neo (manaus) the
 * stock dtbo.img cannot be replaced (it would brick the device).  Crash or
 * panic logs would otherwise be lost between reboots, leaving no way to
 * diagnose boot failures.
 *
 * This driver provides two complementary log-retrieval mechanisms:
 *
 *   1. /proc/last_kmsg
 *      The previous boot's AEE mboot_params console ring-buffer is exposed
 *      as a read-only procfs file.  Android init scripts and bug-report
 *      tools read this path during early userspace.
 *
 *   2. Bootloader SRAM log (via DT /chosen::ram_console property)
 *      If the bootloader advertises a persistent SRAM region through the
 *      "ram_console" property in the /chosen node (struct mem_desc_t), the
 *      driver maps that region and appends its contents to last_kmsg so
 *      that preloader / LK boot-stage messages are also visible.
 *
 * The cross-reboot console ring-buffer is kept in the ramoops region at
 * physical address 0x48000000 (2 MiB, defined in the base DTS of mt6879).
 * The upstream pstore/ramoops driver exposes it via /sys/fs/pstore/ after
 * the filesystem is mounted.
 *
 * This driver is intentionally minimal: write-path logging is handled by
 * aee_sram_printk() from drivers/misc/mediatek/aee/mrdump/mboot_params.c,
 * which registers a "ram" console and writes to the mboot_params DRAM
 * buffer.  We only add the read-side /proc/last_kmsg interface here.
 */

#include <linux/init.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/string.h>

#include <mt-plat/mboot_params.h>

#define MTK_RAM_CONSOLE_TAG	"[mtk_ram_console] "

/* -----------------------------------------------------------------------
 * Bootloader SRAM descriptor (matches the layout passed via /chosen).
 * This mirrors struct mem_desc_t in mboot_params.c; we redeclare it here
 * to avoid a direct dependency on that translation-unit-private struct.
 * ----------------------------------------------------------------------- */
struct mtk_ram_console_bl_desc {
	u32 start;
	u32 size;
	u32 def_type;
	u32 offset;
};

/* Mapped virtual address and length of the bootloader SRAM log (optional) */
static void __iomem *bl_sram_va;
static u32           bl_sram_size;

/* -----------------------------------------------------------------------
 * /proc/last_kmsg implementation
 * ----------------------------------------------------------------------- */

static int last_kmsg_show(struct seq_file *m, void *v)
{
	unsigned long addr = 0, size = 0, start = 0;

	/*
	 * get_mbootlog_buffer() returns the virtual address and length of
	 * the AEE mboot_params ring-buffer that was populated during the
	 * *previous* boot (saved by mboot_params_save_old() in mboot_params.c).
	 * The 'start' parameter is the current write index within the ring; a
	 * non-zero value means the buffer wrapped at least once.
	 */
	get_mbootlog_buffer(&addr, &size, &start);

	if (!addr || !size) {
		seq_puts(m, MTK_RAM_CONSOLE_TAG
			 "mboot_params log unavailable\n");
		goto out_sram;
	}

	if (start != 0) {
		/* Ring buffer has wrapped: print from start→end, then 0→start */
		seq_write(m, (const void *)(addr + start), size - start);
		seq_write(m, (const void *)addr, start);
	} else {
		seq_write(m, (const void *)addr, size);
	}

out_sram:
	/* Optionally append the bootloader SRAM log */
	if (bl_sram_va && bl_sram_size)
		seq_write(m, bl_sram_va, bl_sram_size);

	return 0;
}

static int last_kmsg_open(struct inode *inode, struct file *file)
{
	return single_open(file, last_kmsg_show, NULL);
}

static const struct proc_ops last_kmsg_fops = {
	.proc_open    = last_kmsg_open,
	.proc_read    = seq_read,
	.proc_lseek   = seq_lseek,
	.proc_release = single_release,
};

/* -----------------------------------------------------------------------
 * Bootloader SRAM mapping (optional, best-effort)
 * ----------------------------------------------------------------------- */

static void __init mtk_ram_console_map_bl_sram(void)
{
	struct device_node *chosen;
	const struct mtk_ram_console_bl_desc *desc;
	int len;

	chosen = of_find_node_by_path("/chosen");
	if (!chosen)
		chosen = of_find_node_by_path("/chosen@0");
	if (!chosen)
		return;

	desc = (const struct mtk_ram_console_bl_desc *)
		of_get_property(chosen, "ram_console", &len);
	of_node_put(chosen);

	if (!desc || len < (int)sizeof(*desc)) {
		pr_debug(MTK_RAM_CONSOLE_TAG
			 "no valid ram_console DT property\n");
		return;
	}

	if (!desc->start || !desc->size) {
		pr_debug(MTK_RAM_CONSOLE_TAG
			 "ram_console DT property has zero start/size\n");
		return;
	}

	bl_sram_va = ioremap_wc((phys_addr_t)desc->start, desc->size);
	if (!bl_sram_va) {
		pr_warn(MTK_RAM_CONSOLE_TAG
			"failed to map bootloader SRAM 0x%x+0x%x\n",
			desc->start, desc->size);
		return;
	}

	bl_sram_size = desc->size;
	pr_info(MTK_RAM_CONSOLE_TAG
		"mapped bootloader SRAM log: 0x%x @ 0x%x\n",
		desc->size, desc->start);
}

/* -----------------------------------------------------------------------
 * Module init / exit
 * ----------------------------------------------------------------------- */

static int __init mtk_ram_console_init(void)
{
	struct proc_dir_entry *entry;

	/* Try to map the optional bootloader SRAM log region */
	mtk_ram_console_map_bl_sram();

	entry = proc_create("last_kmsg", 0444, NULL, &last_kmsg_fops);
	if (!entry) {
		pr_warn(MTK_RAM_CONSOLE_TAG "failed to create /proc/last_kmsg\n");
		if (bl_sram_va)
			iounmap(bl_sram_va);
		return -ENOMEM;
	}

	pr_info(MTK_RAM_CONSOLE_TAG "/proc/last_kmsg ready\n");
	return 0;
}

static void __exit mtk_ram_console_exit(void)
{
	remove_proc_entry("last_kmsg", NULL);

	if (bl_sram_va) {
		iounmap(bl_sram_va);
		bl_sram_va = NULL;
	}
}

module_init(mtk_ram_console_init);
module_exit(mtk_ram_console_exit);

MODULE_DESCRIPTION("MediaTek RAM console – /proc/last_kmsg provider for MT6879");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Motorola Edge 40 Neo Lab-Server Project");
