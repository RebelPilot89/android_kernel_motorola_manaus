// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#define pr_fmt(fmt) KBUILD_MODNAME "@(%s:%d) " fmt, __func__, __LINE__

#include <linux/memblock.h>
#include "../include/emi_mng.h"
#include "include/mt6886.h"
#include "include/mt6886_emi.h"
#include "include/mt6886_pos.h"

/* For EMI MPU */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0))
#include <soc/mediatek/emi.h>
#else
#include <memory/mediatek/emi.h>
#endif
/* For MCIF */
#include "../../../../../../include/mt-plat/mtk_ccci_common.h"

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#define REGION_CONN 27

#define DOMAIN_AP 0
#define DOMAIN_CONN 2
#define DOMAIN_SCP 3

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

extern unsigned long long g_con_emi_size;
extern phys_addr_t g_con_emi_phy_base;

struct consys_platform_emi_ops g_consys_platform_emi_ops_mt6886 = {
	.consys_ic_emi_mpu_set_region_protection =
		consys_emi_mpu_set_region_protection_mt6886,
	.consys_ic_emi_set_remapping_reg = consys_emi_set_remapping_reg_mt6886,
	.consys_ic_emi_get_md_shared_emi = consys_emi_get_md_shared_emi_mt6886,
};

int consys_emi_mpu_set_region_protection_mt6886(void)
{
	pr_info("[%s] is not supported. MPU is set in lk\n", __func__);
	return 0;
}

void consys_emi_get_md_shared_emi_mt6886(phys_addr_t *base, unsigned int *size)
{
	phys_addr_t mdPhy = 0;
	int ret = 0;

#if IS_ENABLED(CONFIG_MTK_ECCCI_DRIVER)
	mdPhy = get_smem_phy_start_addr(MD_SYS1, SMEM_USER_RAW_MD_CONSYS, &ret);
#else
	pr_info("[%s] ECCCI Driver is not supported.\n", __func__);
#endif

	if (ret && mdPhy) {
		/* Validar que la memoria esté dentro de la DRAM */
		phys_addr_t dram_start = memblock_start_of_DRAM();
		phys_addr_t dram_end = memblock_end_of_DRAM();

		if (mdPhy < dram_start || (mdPhy + ret) > dram_end) {
			pr_err("MCIF memory out of bounds! "
			       "mdPhy=0x%llx size=0x%x, DRAM=[0x%llx-0x%llx]\n",
			       (u64)mdPhy, ret, (u64)dram_start, (u64)dram_end);
			/* No asignar, tratar como no disponible */
			if (base)
				*base = 0;
			if (size)
				*size = 0;
			return;
		}

		pr_info("MCIF base=0x%llx size=0x%x", (u64)mdPhy, ret);
		if (base)
			*base = mdPhy;
		if (size)
			*size = ret;
	} else {
		pr_info("MCIF is not supported");
		if (base)
			*base = 0;
		if (size)
			*size = 0;
	}
}
