/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#ifndef __CONN_HOST_CSR_TOP_REGS_H__
#define __CONN_HOST_CSR_TOP_REGS_H__

/* ************************************************************************** */
/* */
/* CONN_HOST_CSR_TOP CR Definitions */
/* */
/* ************************************************************************** */

#if defined(_HIF_AXI)
#define CONN_HOST_CSR_TOP_BASE (0x18060000 + CONN_INFRA_REMAPPING_OFFSET)
#endif

#if defined(_HIF_PCIE)
#define CONN_HOST_CSR_TOP_BASE (0x7C060000)
#endif

/* BGF (Bluetooth GPS Frontend) registers */
#define CONN_HOST_CSR_TOP_BGF_LPCTL_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0030)

#define CONN_HOST_CSR_TOP_BGF_IRQ_STAT_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0034)

#define CONN_HOST_CSR_TOP_BGF_IRQ_ENA_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0038)

#define CONN_HOST_CSR_TOP_BGF_FW_OWN_IRQ_ADDR (CONN_HOST_CSR_TOP_BASE + 0x003C)

/* WF Band 0 registers */
#define CONN_HOST_CSR_TOP_WF_BAND0_LPCTL_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0010)

#define CONN_HOST_CSR_TOP_WF_BAND0_IRQ_STAT_ADDR                               \
	(CONN_HOST_CSR_TOP_BASE + 0x0014)

#define CONN_HOST_CSR_TOP_WF_BAND0_IRQ_ENA_ADDR                                \
	(CONN_HOST_CSR_TOP_BASE + 0x0018)

/* WF Band 1 registers */
#define CONN_HOST_CSR_TOP_WF_BAND1_LPCTL_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0020)

#define CONN_HOST_CSR_TOP_WF_BAND1_IRQ_STAT_ADDR                               \
	(CONN_HOST_CSR_TOP_BASE + 0x0024)

#define CONN_HOST_CSR_TOP_WF_BAND1_IRQ_ENA_ADDR                                \
	(CONN_HOST_CSR_TOP_BASE + 0x0028)

/* GPS registers */
#define CONN_HOST_CSR_TOP_GPS_LPCTL_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0040)

#define CONN_HOST_CSR_TOP_GPS_IRQ_STAT_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0044)

#define CONN_HOST_CSR_TOP_GPS_IRQ_ENA_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0048)

/* BUS_MCU_STAT */
#define CONN_HOST_CSR_TOP_BUS_MCU_STAT_ADDR (CONN_HOST_CSR_TOP_BASE + 0x0000)

#endif /* __CONN_HOST_CSR_TOP_REGS_H__ */
