/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2018 MediaTek Inc.
 */

#ifndef AUDIO_TASK_MANAGER_H
#define AUDIO_TASK_MANAGER_H

#include <linux/types.h>

#include <audio_task.h>
#include <audio_messenger_ipi.h>


/*
 * =============================================================================
 *                     public function
 * =============================================================================
 */

void audio_task_manager_init(void);
void audio_task_manager_deinit(void);
#if IS_BUILTIN(CONFIG_MTK_AUDIO_IPI) || \
    (IS_MODULE(CONFIG_MTK_AUDIO_IPI) && defined(MODULE))
int audio_task_register_callback(
	const uint8_t task_scene,
	recv_message_t recv_message);
#else
static inline int audio_task_register_callback(
	const uint8_t task_scene, recv_message_t recv_message)
{ return -ENODEV; }
#endif

#endif /* end of AUDIO_TASK_MANAGER_H */

