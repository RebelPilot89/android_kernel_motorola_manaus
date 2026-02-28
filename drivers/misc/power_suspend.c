// SPDX-License-Identifier: GPL-2.0-only
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

#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/workqueue.h>
#include <linux/power_suspend.h>

#include "../gpu/drm/mediatek/mediatek_v2/mtk_disp_notify.h"

static DEFINE_MUTEX(power_suspend_lock);
static LIST_HEAD(power_suspend_handlers);
static struct workqueue_struct *suspend_work_queue;

static int power_suspend_state = POWER_SUSPEND_INACTIVE;

static void power_suspend_work(struct work_struct *work);
static void power_resume_work(struct work_struct *work);

static DECLARE_WORK(suspend_work, power_suspend_work);
static DECLARE_WORK(resume_work, power_resume_work);

/**
 * register_power_suspend - Register a power suspend handler.
 * @handler: handler with suspend/resume callbacks to register
 *
 * Adds a handler to the list. Handlers are called on screen-off
 * (suspend) and screen-on (resume) events.
 */
void register_power_suspend(struct power_suspend *handler)
{
	struct power_suspend *pos;

	mutex_lock(&power_suspend_lock);
	list_for_each_entry(pos, &power_suspend_handlers, link) {
		if (pos == handler)
			goto out;
	}
	list_add_tail(&handler->link, &power_suspend_handlers);
out:
	mutex_unlock(&power_suspend_lock);
}
EXPORT_SYMBOL(register_power_suspend);

/**
 * unregister_power_suspend - Unregister a power suspend handler.
 * @handler: handler to remove
 */
void unregister_power_suspend(struct power_suspend *handler)
{
	mutex_lock(&power_suspend_lock);
	list_del_init(&handler->link);
	mutex_unlock(&power_suspend_lock);
}
EXPORT_SYMBOL(unregister_power_suspend);

static void power_suspend_work(struct work_struct *work)
{
	struct power_suspend *handler;

	mutex_lock(&power_suspend_lock);
	list_for_each_entry(handler, &power_suspend_handlers, link) {
		if (handler->suspend)
			handler->suspend(handler);
	}
	mutex_unlock(&power_suspend_lock);
}

static void power_resume_work(struct work_struct *work)
{
	struct power_suspend *handler;

	mutex_lock(&power_suspend_lock);
	list_for_each_entry_reverse(handler, &power_suspend_handlers, link) {
		if (handler->resume)
			handler->resume(handler);
	}
	mutex_unlock(&power_suspend_lock);
}

static int power_suspend_notifier_callback(struct notifier_block *nb,
					   unsigned long event, void *data)
{
	int *blank = (int *)data;

	if (event != MTK_DISP_EVENT_BLANK || !blank)
		return NOTIFY_OK;

	if (*blank == MTK_DISP_BLANK_POWERDOWN) {
		if (power_suspend_state != POWER_SUSPEND_ACTIVE) {
			power_suspend_state = POWER_SUSPEND_ACTIVE;
			queue_work(suspend_work_queue, &suspend_work);
		}
	} else if (*blank == MTK_DISP_BLANK_UNBLANK) {
		if (power_suspend_state != POWER_SUSPEND_INACTIVE) {
			power_suspend_state = POWER_SUSPEND_INACTIVE;
			queue_work(suspend_work_queue, &resume_work);
		}
	}

	return NOTIFY_OK;
}

static struct notifier_block power_suspend_notifier = {
	.notifier_call = power_suspend_notifier_callback,
};

static int __init power_suspend_init(void)
{
	int ret;

	suspend_work_queue = alloc_ordered_workqueue("power_suspend", 0);
	if (!suspend_work_queue)
		return -ENOMEM;

	ret = mtk_disp_notifier_register("power_suspend", &power_suspend_notifier);
	if (ret) {
		pr_err("power_suspend: failed to register display notifier: %d\n", ret);
		destroy_workqueue(suspend_work_queue);
		return ret;
	}

	pr_info("power_suspend: initialized\n");
	return 0;
}

static void __exit power_suspend_exit(void)
{
	mtk_disp_notifier_unregister(&power_suspend_notifier);
	flush_workqueue(suspend_work_queue);
	destroy_workqueue(suspend_work_queue);
}

module_init(power_suspend_init);
module_exit(power_suspend_exit);

MODULE_AUTHOR("faux123, franco, adapted for MTK");
MODULE_DESCRIPTION("Power Suspend v2.0 - screen-state notification framework");
MODULE_LICENSE("GPL v2");
