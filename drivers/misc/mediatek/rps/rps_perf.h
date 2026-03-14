/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (C) 2015 MediaTek Inc.
 */


#ifndef __RPS_PERF_H__
#define __RPS_PERF_H__

#include <linux/kconfig.h>
#if IS_BUILTIN(CONFIG_MTK_NET_RPS) || \
    (IS_MODULE(CONFIG_MTK_NET_RPS) && defined(MODULE))
int set_rps_map(struct netdev_rx_queue *queue, unsigned long rps_value);
#else
static inline int set_rps_map(struct netdev_rx_queue *queue,
			      unsigned long rps_value) { return 0; }
#endif

#endif /* __RPS_PERF_H__ */

