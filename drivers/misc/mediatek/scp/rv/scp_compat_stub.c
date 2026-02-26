// SPDX-License-Identifier: GPL-2.0

#include <linux/notifier.h>

#include "scp_ipi.h"

int register_3way_semaphore_notifier(struct notifier_block *nb)
{
	return 0;
}
EXPORT_SYMBOL_GPL(register_3way_semaphore_notifier);

int unregister_3way_semaphore_notifier(struct notifier_block *nb)
{
	return 0;
}
EXPORT_SYMBOL_GPL(unregister_3way_semaphore_notifier);

struct mtk_ipi_device scp_ipidev;
EXPORT_SYMBOL_GPL(scp_ipidev);

enum scp_ipi_status scp_legacy_ipi_init(void)
{
	return SCP_IPI_DONE;
}
EXPORT_SYMBOL_GPL(scp_legacy_ipi_init);

bool mbox_check_recv_table(unsigned int id)
{
	return false;
}
EXPORT_SYMBOL_GPL(mbox_check_recv_table);
