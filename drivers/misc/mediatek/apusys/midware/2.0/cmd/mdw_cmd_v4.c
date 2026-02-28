// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#include "mdw_cmn.h"
#include "mdw_cmd.h"

int mdw_cmd_get_cmdbufs_with_apummu(struct mdw_fpriv *mpriv, struct mdw_cmd *c)
{
	return mdw_cmd_get_cmdbufs(mpriv, c);
}

void mdw_cmd_history_init(struct mdw_device *mdev)
{
}

void mdw_cmd_history_deinit(struct mdw_device *mdev)
{
}

struct mdw_cmd_history_tbl *mdw_cmd_ch_tbl_find(struct mdw_cmd *c)
{
	return NULL;
}

int mdw_cmd_ioctl_v4(struct mdw_fpriv *mpriv, void *data)
{
	return mdw_cmd_ioctl_v3(mpriv, data);
}
