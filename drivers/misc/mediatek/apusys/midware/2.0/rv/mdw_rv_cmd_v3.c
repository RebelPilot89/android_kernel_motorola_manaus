// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#include "mdw_rv.h"

static struct mdw_rv_cmd *mdw_rv_cmd_create_v3(struct mdw_fpriv *mpriv,
					       struct mdw_cmd *c)
{
	return mdw_rv_cmd_create(mpriv, c);
}

static int mdw_rv_cmd_delete_v3(struct mdw_cmd *c)
{
	(void)c;
	return 0;
}

static void mdw_rv_cmd_done_v3(struct mdw_rv_cmd *rc, int ret)
{
	mdw_rv_cmd_done(rc, ret);
}

const struct {
	struct mdw_rv_cmd *(*create)(struct mdw_fpriv *mpriv,
				     struct mdw_cmd *c);
	int (*delete)(struct mdw_cmd *c);
	void (*done)(struct mdw_rv_cmd *rc, int ret);
} mdw_rv_cmd_func_v3 = {
	.create = mdw_rv_cmd_create_v3,
	.delete = mdw_rv_cmd_delete_v3,
	.done = mdw_rv_cmd_done_v3,
};
