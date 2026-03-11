// SPDX-License-Identifier: GPL-2.0-only
/*
 * Arm Firmware Framework for Arm (FF-A 1.0, DEN0077A) — transport driver
 *
 * DTS-agnostic: probes FFA support via the FFA_VERSION SMC at boot and
 * activates the driver without requiring any 'arm,ffa' Device Tree node.
 * Memory sharing (FFA_MEM_LEND / FFA_MEM_SHARE / FFA_MEM_RECLAIM) and
 * direct messaging (FFA_MSG_SEND_DIRECT_REQ) are fully implemented.
 *
 * Backported to Linux 5.10 for MediaTek MT6879 / Trustonic MobiCore 610.
 *
 * Copyright (C) 2021 ARM Ltd.
 * Backport/adaptation Copyright (C) 2024 RebelPilot89
 */

#include <linux/arm-smccc.h>
#include <linux/arm_ffa.h>
#include <linux/bitfield.h>
#include <linux/device.h>
#include <linux/gfp.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/mutex.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include <linux/uuid.h>
#include <asm/page.h>

/* Forward declaration from bus.c */
int  __init arm_ffa_bus_init(void);
void __exit arm_ffa_bus_exit(void);

/* ----------------------------------------------------------------------- */
/* FFA version negotiation                                                  */
/* ----------------------------------------------------------------------- */

static u32 ffa_version_compiled = FFA_VERSION_1_0;

/* ----------------------------------------------------------------------- */
/* RXTX buffer management                                                   */
/* ----------------------------------------------------------------------- */

/*
 * The FFA specification requires a pair of 4 KiB-aligned, physically
 * contiguous pages as the RXTX buffer.  We allocate them with get_free_page
 * (guaranteed to be page-aligned and physically contiguous for order-0).
 */
struct ffa_rxtx {
	void    *tx;		/* normal-memory, kernel-mapped TX page */
	void    *rx;		/* normal-memory, kernel-mapped RX page */
	struct mutex lock;	/* serialises access while tx/rx in use */
};

static struct ffa_rxtx g_rxtx;
static u16 g_vm_id;

/* ----------------------------------------------------------------------- */
/* Low-level SMC helpers                                                    */
/* ----------------------------------------------------------------------- */

static int ffa_to_linux_errno(int errno_ffa)
{
	switch (errno_ffa) {
	case FFA_RET_SUCCESS:        return 0;
	case FFA_RET_NOT_SUPPORTED:  return -EOPNOTSUPP;
	case FFA_RET_INVALID_PARAMETERS: return -EINVAL;
	case FFA_RET_NO_MEMORY:      return -ENOMEM;
	case FFA_RET_BUSY:           return -EBUSY;
	case FFA_RET_INTERRUPTED:    return -EINTR;
	case FFA_RET_DENIED:         return -EACCES;
	case FFA_RET_RETRY:          return -EAGAIN;
	case FFA_RET_ABORTED:        return -ECANCELED;
	default:                     return -EIO;
	}
}

/*
 * A successful FFA call returns FFA_SUCCESS in a0 and the payload in
 * a2..a7.  An error is indicated by FFA_ERROR in a0 and the code in a2.
 */
static int ffa_smc(unsigned long func, unsigned long a1, unsigned long a2,
		   unsigned long a3, unsigned long a4, unsigned long a5,
		   unsigned long a6, struct arm_smccc_res *out)
{
	struct arm_smccc_res res;

	arm_smccc_smc(func, a1, a2, a3, a4, a5, a6, 0, &res);

	if (out)
		*out = res;

	if ((u32)res.a0 == (u32)FFA_ERROR)
		return ffa_to_linux_errno((int)res.a2);

	/* FFA_SUCCESS_SMC32 = 0x84000061  */
	return 0;
}

/* ----------------------------------------------------------------------- */
/* FFA_VERSION probe                                                        */
/* ----------------------------------------------------------------------- */

static int ffa_version_check(u32 *ver)
{
	struct arm_smccc_res res;

	arm_smccc_smc(FFA_VERSION, ffa_version_compiled, 0, 0, 0, 0, 0, 0,
		      &res);

	/* FFA_VERSION returns the negotiated version in a0. */
	if ((int)res.a0 == FFA_RET_NOT_SUPPORTED)
		return -EOPNOTSUPP;

	*ver = (u32)res.a0;
	return 0;
}

/* ----------------------------------------------------------------------- */
/* RXTX buffer setup                                                        */
/* ----------------------------------------------------------------------- */

static int ffa_rxtx_map(phys_addr_t tx_phys, phys_addr_t rx_phys)
{
	return ffa_smc(FFA_FN_NATIVE(RXTX_MAP),
		       (unsigned long)tx_phys,
		       (unsigned long)rx_phys,
		       1 /* number of 4 KiB pages */, 0, 0, 0, NULL);
}

static void ffa_rxtx_unmap(u16 vm_id)
{
	ffa_smc(FFA_RXTX_UNMAP, FIELD_PREP(GENMASK(31, 16), (u32)vm_id),
		0, 0, 0, 0, 0, NULL);
}

static int ffa_rx_release(void)
{
	return ffa_smc(FFA_RX_RELEASE, 0, 0, 0, 0, 0, 0, NULL);
}

/* ----------------------------------------------------------------------- */
/* FFA_ID_GET                                                               */
/* ----------------------------------------------------------------------- */

static int ffa_id_get(u16 *vm_id)
{
	struct arm_smccc_res res;
	int ret;

	ret = ffa_smc(FFA_ID_GET, 0, 0, 0, 0, 0, 0, &res);
	if (ret)
		return ret;

	*vm_id = (u16)(res.a2 & 0xffff);
	return 0;
}

/* ----------------------------------------------------------------------- */
/* FFA_PARTITION_INFO_GET                                                   */
/* ----------------------------------------------------------------------- */

#define MAX_FFA_PARTITIONS	16

static int ffa_partition_info_get(const uuid_t *uuid,
				  struct ffa_partition_info *partitions,
				  unsigned int *count)
{
	struct arm_smccc_res res;
	unsigned int n, total;
	const u32 *uu;
	int ret;

	uu = (const u32 *)uuid;

	ret = ffa_smc(FFA_PARTITION_INFO_GET,
		      le32_to_cpu(uu[0]), le32_to_cpu(uu[1]),
		      le32_to_cpu(uu[2]), le32_to_cpu(uu[3]),
		      0, 0, &res);
	if (ret)
		return ret;

	total = (unsigned int)(res.a2 & 0xffffffff);
	if (total == 0) {
		*count = 0;
		ffa_rx_release();
		return 0;
	}

	n = min(total, (unsigned int)MAX_FFA_PARTITIONS);
	memcpy(partitions, g_rxtx.rx,
	       n * sizeof(struct ffa_partition_info));

	ffa_rx_release();

	*count = n;
	return 0;
}

/* ----------------------------------------------------------------------- */
/* Memory operations                                                        */
/* ----------------------------------------------------------------------- */

/*
 * Build the FFA memory region descriptor in the TX buffer and call the
 * appropriate SMC (FFA_MEM_LEND or FFA_MEM_SHARE).
 *
 * The TX buffer is a single 4 KiB page; if the descriptor is larger,
 * the fragmented path (FFA_MEM_FRAG_TX) would be required.  For now we
 * return -E2BIG if the descriptor overflows the buffer.
 *
 * Locking: caller must hold g_rxtx.lock.
 */
static int ffa_memory_ops(struct ffa_mem_ops_args *args, bool lend)
{
	struct ffa_mem_region *region;
	struct ffa_composite_mem_region *composite;
	struct ffa_mem_region_addr_range *constituents;
	struct scatterlist *sg;
	size_t region_sz, needed_sz;
	u32 n_sg, ep_count;
	unsigned int i;
	struct arm_smccc_res res;
	int ret;
	u32 func;

	ep_count = args->nattrs;

	/* Count scatter-gather entries */
	n_sg = 0;
	for_each_sg(args->sg, sg, sg_nents(args->sg), i)
		n_sg++;

	/* Compute total descriptor size */
	needed_sz = COMPOSITE_CONSTITUENTS_OFFSET(ep_count, n_sg);
	if (needed_sz > FFA_PAGE_SIZE)
		return -E2BIG;

	memset(g_rxtx.tx, 0, FFA_PAGE_SIZE);

	region = g_rxtx.tx;
	region->sender_id  = 0; /* filled by secure world */
	region->attributes = FFA_MEM_NORMAL | FFA_MEM_WRITE_BACK
			     | FFA_MEM_INNER_SHAREABLE;
	region->flags      = args->flags;
	region->handle     = 0;
	region->tag        = args->tag;
	region->ep_count   = ep_count;

	for (i = 0; i < ep_count; i++) {
		region->ep_mem_access[i].receiver     = args->attrs[i].receiver;
		region->ep_mem_access[i].attrs        = args->attrs[i].attrs;
		region->ep_mem_access[i].composite_off =
			(u32)COMPOSITE_OFFSET(ep_count);
	}

	composite = (struct ffa_composite_mem_region *)
		((u8 *)g_rxtx.tx + COMPOSITE_OFFSET(ep_count));
	composite->total_pg_cnt  = 0;
	composite->addr_range_cnt = n_sg;

	constituents = composite->constituents;
	i = 0;
	for_each_sg(args->sg, sg, sg_nents(args->sg), i) {
		constituents[i].address    = (u64)sg_phys(sg);
		constituents[i].pg_cnt     = sg->length >> PAGE_SHIFT;
		composite->total_pg_cnt   += constituents[i].pg_cnt;
	}

	region_sz = needed_sz;

	func = lend ? FFA_FN_NATIVE(MEM_LEND) : FFA_FN_NATIVE(MEM_SHARE);

	arm_smccc_smc(func,
		      (unsigned long)region_sz,	/* total fragment length */
		      (unsigned long)region_sz,	/* fragment length = total */
		      0, 0, 0, 0, 0, &res);

	if ((u32)res.a0 == (u32)FFA_ERROR)
		return ffa_to_linux_errno((int)res.a2);

	/* a2:a3 contain the 64-bit global handle */
	args->g_handle = PACK_HANDLE((u32)res.a2, (u32)res.a3);
	return 0;
}

static int ffa_memory_lend(struct ffa_mem_ops_args *args)
{
	int ret;

	mutex_lock(&g_rxtx.lock);
	ret = ffa_memory_ops(args, true);
	mutex_unlock(&g_rxtx.lock);
	return ret;
}

static int ffa_memory_share(struct ffa_mem_ops_args *args)
{
	int ret;

	mutex_lock(&g_rxtx.lock);
	ret = ffa_memory_ops(args, false);
	mutex_unlock(&g_rxtx.lock);
	return ret;
}

static int ffa_memory_reclaim(u64 handle, u32 flags)
{
	return ffa_smc(FFA_MEM_RECLAIM,
		       HANDLE_LOW(handle), HANDLE_HIGH(handle),
		       (unsigned long)flags, 0, 0, 0, NULL);
}

/* ----------------------------------------------------------------------- */
/* Direct messaging                                                         */
/* ----------------------------------------------------------------------- */

static int ffa_sync_send_receive(struct ffa_device *dev,
				 struct ffa_send_direct_data *data)
{
	struct arm_smccc_res res;
	unsigned long func;

	func = dev->mode_32bit ? FFA_MSG_SEND_DIRECT_REQ :
				 FFA_FN_NATIVE(MSG_SEND_DIRECT_REQ);

	arm_smccc_smc(func,
		      FIELD_PREP(GENMASK(31, 16), 0) |		/* src id */
		      FIELD_PREP(GENMASK(15,  0), (u32)dev->vm_id),
		      0,
		      data->data0, data->data1,
		      data->data2, data->data3,
		      data->data4, &res);

	if ((u32)res.a0 == (u32)FFA_ERROR)
		return ffa_to_linux_errno((int)res.a2);

	data->data0 = res.a3;
	data->data1 = res.a4;
	data->data2 = res.a5;
	data->data3 = res.a6;
	data->data4 = res.a7;

	return 0;
}

static void ffa_mode_32bit_set(struct ffa_device *dev)
{
	dev->mode_32bit = true;
}

/* ----------------------------------------------------------------------- */
/* Info ops                                                                 */
/* ----------------------------------------------------------------------- */

static u32 ffa_api_version_get(void)
{
	return ffa_version_compiled;
}

static int ffa_partition_info_get_wrapper(const char *uuid_str,
					  struct ffa_partition_info *buffer)
{
	uuid_t uuid;
	unsigned int count = 0;
	int ret;

	if (uuid_parse(uuid_str, &uuid))
		return -EINVAL;

	ret = ffa_partition_info_get(&uuid, buffer, &count);
	if (ret)
		return ret;

	return (int)count;
}

/* ----------------------------------------------------------------------- */
/* Static ops table                                                         */
/* ----------------------------------------------------------------------- */

static const struct ffa_info_ops g_info_ops = {
	.api_version_get    = ffa_api_version_get,
	.partition_info_get = ffa_partition_info_get_wrapper,
};

static const struct ffa_msg_ops g_msg_ops = {
	.mode_32bit_set     = ffa_mode_32bit_set,
	.sync_send_receive  = ffa_sync_send_receive,
};

static const struct ffa_mem_ops g_mem_ops = {
	.memory_reclaim = ffa_memory_reclaim,
	.memory_share   = ffa_memory_share,
	.memory_lend    = ffa_memory_lend,
};

static const struct ffa_ops g_ffa_ops = {
	.info_ops = &g_info_ops,
	.msg_ops  = &g_msg_ops,
	.mem_ops  = &g_mem_ops,
};

/* ----------------------------------------------------------------------- */
/* Partition discovery and device registration                             */
/* ----------------------------------------------------------------------- */

/*
 * Try to find and register a single secure-world partition identified by
 * @uuid.  Returns 0 if the partition was found and registered, -ENODEV if
 * no partition matched, or a negative errno on error.
 */
static int ffa_register_partition(const uuid_t *uuid)
{
	struct ffa_partition_info parts[MAX_FFA_PARTITIONS];
	struct ffa_device *ffa_dev;
	unsigned int i, count = 0;
	int ret;

	ret = ffa_partition_info_get(uuid, parts, &count);
	if (ret)
		return ret;

	if (count == 0)
		return -ENODEV;

	for (i = 0; i < count; i++) {
		uuid_t part_uuid;

		/* The partition_info uuid is stored as four LE u32 words */
		memcpy(&part_uuid, parts[i].uuid, sizeof(part_uuid));

		ffa_dev = ffa_device_register(&part_uuid,
					      (int)parts[i].id,
					      &g_ffa_ops);
		if (IS_ERR(ffa_dev)) {
			pr_err("arm_ffa: failed to register partition %04x: %ld\n",
			       parts[i].id, PTR_ERR(ffa_dev));
			continue;
		}

		pr_info("arm_ffa: registered secure partition VM 0x%04x\n",
			parts[i].id);
	}

	return 0;
}

/* ----------------------------------------------------------------------- */
/* Module init / exit (DTS-agnostic via late_initcall)                     */
/* ----------------------------------------------------------------------- */

static int ffa_init(void)
{
	u32 version;
	u16 vm_id = 0;
	phys_addr_t tx_phys, rx_phys;
	int ret;

	/* Step 1 — check FFA support by issuing FFA_VERSION */
	ret = ffa_version_check(&version);
	if (ret) {
		pr_debug("arm_ffa: FFA_VERSION SMC returned not-supported, "
			 "FFA disabled\n");
		return 0;	/* silently absent, not a fatal error */
	}

	pr_info("arm_ffa: Firmware Framework for Arm detected (version %u.%u)\n",
		FFA_MAJOR_VERSION(version), FFA_MINOR_VERSION(version));

	/* Step 2 — register the FFA virtual bus */
	ret = arm_ffa_bus_init();
	if (ret) {
		pr_err("arm_ffa: bus init failed: %d\n", ret);
		return ret;
	}

	/* Step 3 — allocate and map RXTX pages */
	g_rxtx.tx = (void *)get_zeroed_page(GFP_KERNEL);
	g_rxtx.rx = (void *)get_zeroed_page(GFP_KERNEL);
	if (!g_rxtx.tx || !g_rxtx.rx) {
		ret = -ENOMEM;
		goto err_free_pages;
	}

	mutex_init(&g_rxtx.lock);

	tx_phys = virt_to_phys(g_rxtx.tx);
	rx_phys = virt_to_phys(g_rxtx.rx);

	ret = ffa_rxtx_map(tx_phys, rx_phys);
	if (ret) {
		pr_err("arm_ffa: FFA_RXTX_MAP failed: %d\n", ret);
		goto err_free_pages;
	}

	/* Step 4 — get our own VM ID */
	ret = ffa_id_get(&vm_id);
	if (ret) {
		pr_warn("arm_ffa: FFA_ID_GET failed (%d), assuming VM 0\n",
			ret);
		vm_id = 0;
	}

	g_vm_id = vm_id;
	pr_info("arm_ffa: normal-world VM id = 0x%04x\n", vm_id);

	/*
	 * Step 5 — discover secure-world partitions.
	 *
	 * Use a null UUID to enumerate all partitions.  Each partition that
	 * matches a loaded ffa_driver's id_table will be probed automatically
	 * by the FFA bus match/probe machinery.
	 */
	{
		static const uuid_t null_uuid = UUID_INIT(0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0);

		ffa_register_partition(&null_uuid);
		/* Ignore return — absence of partitions is not fatal */
	}

	return 0;

err_free_pages:
	if (g_rxtx.tx) {
		free_page((unsigned long)g_rxtx.tx);
		g_rxtx.tx = NULL;
	}
	if (g_rxtx.rx) {
		free_page((unsigned long)g_rxtx.rx);
		g_rxtx.rx = NULL;
	}
	arm_ffa_bus_exit();
	return ret;
}

static void ffa_exit(void)
{
	if (g_rxtx.tx) {
		ffa_rxtx_unmap(g_vm_id);
		free_page((unsigned long)g_rxtx.tx);
		g_rxtx.tx = NULL;
	}
	if (g_rxtx.rx) {
		free_page((unsigned long)g_rxtx.rx);
		g_rxtx.rx = NULL;
	}

	arm_ffa_bus_exit();
}

/*
 * Use late_initcall so that the RXTX allocation happens after the
 * memory allocator is fully operational and the IRQ/CPU subsystems
 * are up — but still before any drivers that depend on FFA are probed.
 */
late_initcall(ffa_init);
module_exit(ffa_exit);

MODULE_ALIAS("arm-ffa-transport");
MODULE_AUTHOR("ARM Ltd., RebelPilot89");
MODULE_DESCRIPTION("Arm Firmware Framework for Arm (FF-A) transport "
		   "(DTS-agnostic, Linux 5.10 backport)");
MODULE_LICENSE("GPL v2");
