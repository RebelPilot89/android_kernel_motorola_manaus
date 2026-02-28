// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#include "mdw_rv.h"

static struct mdw_rv_cmd *mdw_rv_cmd_create_v4(struct mdw_fpriv *mpriv,
					       struct mdw_cmd *c)
{
	return mdw_rv_cmd_create(mpriv, c);
}

static int mdw_rv_cmd_delete_v4(struct mdw_cmd *c)
{
	(void)c;
	return 0;
}

static void mdw_rv_cmd_done_v4(struct mdw_rv_cmd *rc, int ret)
{
	mdw_rv_cmd_done(rc, ret);
}

static bool mdw_rv_cmd_poll_v4(struct mdw_rv_cmd *rc)
{
	(void)rc;
	return false;
}

static void mdw_rv_cmd_cp_execinfo_v4(struct mdw_rv_cmd *rc)
{
	(void)rc;
}

const struct {
	struct mdw_rv_cmd *(*create)(struct mdw_fpriv *mpriv,
				     struct mdw_cmd *c);
	int (*delete)(struct mdw_cmd *c);
	void (*done)(struct mdw_rv_cmd *rc, int ret);
	bool (*poll)(struct mdw_rv_cmd *rc);
	void (*cp_execinfo)(struct mdw_rv_cmd *rc);
} mdw_rv_cmd_func_v4 = {
	.create = mdw_rv_cmd_create_v4,
	.delete = mdw_rv_cmd_delete_v4,
	.done = mdw_rv_cmd_done_v4,
	.poll = mdw_rv_cmd_poll_v4,
	.cp_execinfo = mdw_rv_cmd_cp_execinfo_v4,
};
