/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Power Suspend v2.0
 *
 * Provides a screen-state notification framework as a modern replacement
 * for the legacy early_suspend mechanism. Drivers register handlers that
 * are called when the display powers down or resumes.
 *
 * Based on faux123/franco kernel power_suspend implementation.
 * Adapted for MediaTek mtk_disp_notify on Android kernel 5.10.
 */

#ifndef _LINUX_POWER_SUSPEND_H
#define _LINUX_POWER_SUSPEND_H

#include <linux/list.h>

#define POWER_SUSPEND_INACTIVE	0
#define POWER_SUSPEND_ACTIVE	1

struct power_suspend {
	struct list_head link;
	void (*suspend)(struct power_suspend *h);
	void (*resume)(struct power_suspend *h);
};

#ifdef CONFIG_POWER_SUSPEND
void register_power_suspend(struct power_suspend *handler);
void unregister_power_suspend(struct power_suspend *handler);
#else
static inline void register_power_suspend(struct power_suspend *handler) {}
static inline void unregister_power_suspend(struct power_suspend *handler) {}
#endif /* CONFIG_POWER_SUSPEND */

#endif /* _LINUX_POWER_SUSPEND_H */
