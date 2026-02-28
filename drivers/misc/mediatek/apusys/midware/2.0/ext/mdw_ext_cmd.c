// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2023 MediaTek Inc.
 */

#include "mdw_ext.h"
#include "mdw_ext_cmn.h"
#include "mdw_ext_ioctl.h"
#include "mdw_ext_export.h"
#include "mdw_cmd.h"

void mdw_ext_cmd_get_id(struct mdw_cmd *c)
{
	(void)c;
}

void mdw_ext_cmd_put_id(struct mdw_cmd *c)
{
	(void)c;
}

int mdw_ext_cmd_ioctl(void *data)
{
	union mdw_ext_cmd_args *args = (union mdw_ext_cmd_args *)data;

	if (!args)
		return -EINVAL;

	memset(args, 0, sizeof(*args));
	return -EOPNOTSUPP;
}
