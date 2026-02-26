/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#ifndef __CONN_CFG_REGS_H__
#define __CONN_CFG_REGS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ************************************************************************** */
/* */
/* CONN_CFG CR Definitions */
/* */
/* ************************************************************************** */
#if defined(_HIF_AXI)
#define CONN_INFRA_CFG_BASE (0x18001000 + CONN_INFRA_REMAPPING_OFFSET)
#endif

#if defined(_HIF_PCIE)
#define CONN_INFRA_CFG_BASE 0x7C001000
#define CONN_INFRA_CFG_AP2WF_BUS_ADDR 0x7C500000
#define CONN_INFRA_CFG_PCIE2AP_REMAP_2_ADDR_DE_HARDCODE 0x18501844
#endif

/* Main control registers */
#define CONN_CFG_CONN_HW_VER_ADDR (CONN_INFRA_CFG_BASE + 0x000)

#define CONN_CFG_ID_ADDR (CONN_INFRA_CFG_BASE + 0x004)

#define CONN_CFG_STRAP_STATUS_ADDR (CONN_INFRA_CFG_BASE + 0x010)

#define CONN_CFG_BOOT_ADDR (CONN_INFRA_CFG_BASE + 0x014)

#define CONN_CFG_EFUSE_ADDR (CONN_INFRA_CFG_BASE + 0x020)

/* Power control registers */
#define CONN_CFG_CONN_INFRA_CFG_PWRCTRL0_ADDR (CONN_INFRA_CFG_BASE + 0x200)

#define CONN_CFG_CONN_INFRA_CFG_FM_PWRCTRL0_ADDR (CONN_INFRA_CFG_BASE + 0x204)

#define CONN_CFG_CONN_INFRA_CFG_BT_PWRCTRL0_ADDR (CONN_INFRA_CFG_BASE + 0x208)

#define CONN_CFG_CONN_INFRA_CFG_GPS_PWRCTRL0_ADDR (CONN_INFRA_CFG_BASE + 0x20C)

/* Manual control registers */
#define CONN_CFG_CONN_INFRA_CFG_BT_MANUAL_CTRL_ADDR                            \
	(CONN_INFRA_CFG_BASE + 0x108)

#define CONN_CFG_CONN_INFRA_CFG_GPS_MANUAL_CTRL_ADDR                           \
	(CONN_INFRA_CFG_BASE + 0x10C)

/* Sleep control registers */
#define CONN_CFG_CONN_INFRA_SLP_CNT_CTL_ADDR (CONN_INFRA_CFG_BASE + 0x0A0)

#define CONN_CFG_CONN_INFRA_CONN_INFRA_SLP_CNT_ADDR                            \
	(CONN_INFRA_CFG_BASE + 0x0B0)

#define CONN_CFG_CONN_INFRA_WFTOP_SLP_CNT_ADDR (CONN_INFRA_CFG_BASE + 0x0C0)

/* Mailbox registers */
#define CONN_CFG_CONN_INFRA_CFG_CONN2AP_MAILBOX_ADDR                           \
	(CONN_INFRA_CFG_BASE + 0x100)

#define CONN_CFG_CONN_INFRA_CFG_AP2CONN_MAILBOX_ADDR                           \
	(CONN_INFRA_CFG_BASE + 0x104)

#ifdef __cplusplus
}
#endif

#endif /* __CONN_CFG_REGS_H__ */
