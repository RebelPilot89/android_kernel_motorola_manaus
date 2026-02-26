/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2021 MediaTek Inc.
 * BT Configuration for MT6879
 */

#ifndef __BT_CONFIG_H__
#define __BT_CONFIG_H__

/* BT feature configuration flags */
#define CFG_BT_ATF_SUPPORT 0 /* ATF (ARM Trusted Firmware) support disabled */
#define CFG_BT_POWER_THROTTLING 1 /* Power throttling support enabled */
#define CFG_BT_CHIP_RESET_SUPPORT 1 /* Chip reset support enabled */
#define CFG_BT_FW_DOWNLOAD 1 /* Firmware download support enabled */

/* BT subsystem control */
#define BT_SUBSYS_ENABLED 1
#define BGF_SUBSYS_ENABLED 1

/* BT UART configuration (if used) */
#define CFG_BT_UART_BAUDRATE 3000000 /* 3Mbps default */

#endif /* __BT_CONFIG_H__ */
