// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/sync_file.h>
#include <linux/timekeeping.h>

#include "mdw_trace.h"
#include "mdw_cmn.h"
#include "mdw_cmd.h"
#include "mdw_mem.h"
#include "mdw_mem_pool.h"
#include "rv/mdw_rv_tag.h"

static int mdw_cmd_run(struct mdw_fpriv *mpriv, struct mdw_cmd *c)
{
	struct mdw_device *mdev = mpriv->mdev;
	struct dma_fence *f = &c->fence->base_fence;
	int ret = 0;

	mdw_cmd_show(c, mdw_cmd_debug);

	ktime_get_ts64(&c->start_ts);
	if (mdev->dev_funcs && mdev->dev_funcs->run_cmd)
		ret = mdev->dev_funcs->run_cmd(mpriv, c);
	else {
		pr_err("mdw run_cmd hook unavailable\n");
		ret = -ENODEV;
	}
	if (ret) {
		mdw_drv_err("s(0x%llx) run cmd(0x%llx) fail(%d)\n",
			    (uint64_t)c->mpriv, c->kid, ret);
		dma_fence_set_error(f, ret);
		if (dma_fence_signal(f)) {
			mdw_drv_warn("c(0x%llx) signal fence fail\n",
				     (uint64_t)c);
			if (f->ops->get_timeline_name &&
			    f->ops->get_driver_name) {
				mdw_drv_warn(" fence name(%s-%s)\n",
					     f->ops->get_driver_name(f),
					     f->ops->get_timeline_name(f));
			}
		}
		dma_fence_put(f);
	} else {
		mdw_flw_debug("s(0x%llx) cmd(0x%llx) run\n", (uint64_t)c->mpriv,
			      c->kid);
	}

	return ret;
}

static int mdw_cmd_complete(struct mdw_cmd *c, int ret)
{
	struct dma_fence *f = &c->fence->base_fence;
	struct mdw_fpriv *mpriv = c->mpriv;
	struct timespec64 total_ts;

	mdw_trace_begin("apumdw:cmd_complete|cmd:0x%llx/0x%llx", c->uid,
			c->kid);
	mutex_lock(&c->mtx);

	ktime_get_ts64(&c->end_ts);
	total_ts = timespec64_sub(c->end_ts, c->start_ts);
	c->einfos->c.total_us =
		div_s64(timespec64_to_ns(&total_ts), NSEC_PER_USEC);
	mdw_flw_debug(
		"s(0x%llx) c(0x%llx/0x%llx/0x%llx) ret(%d) sc_rets(0x%llx) complete, pid(%d/%d)(%d)\n",
		(uint64_t)mpriv, c->uid, c->kid, c->rvid, ret,
		c->einfos->c.sc_rets, c->pid, c->tgid, task_pid_nr(current));

	/* check subcmds return value */
	if (c->einfos->c.sc_rets) {
		if (!ret)
			ret = -EIO;

		mdw_cmd_check_rets(c, ret);
	} else if (ret == -EBUSY) {
		mdw_exception("uP busy:ret(%d/0x%llx)pid(%d/%d)\n", ret,
			      c->einfos->c.sc_rets, c->pid, c->tgid);
	}
	c->einfos->c.ret = ret;

	if (ret) {
		mdw_drv_err(
			"s(0x%llx) c(0x%llx/0x%llx/0x%llx) ret(%d/0x%llx) time(%llu) pid(%d/%d)\n",
			(uint64_t)mpriv, c->uid, c->kid, c->rvid, ret,
			c->einfos->c.sc_rets, c->einfos->c.total_us, c->pid,
			c->tgid);
		dma_fence_set_error(f, ret);

		/* Eliminado por refactorización de API moderna */
	} else {
		mdw_flw_debug(
			"s(0x%llx) c(0x%llx/0x%llx/0x%llx) ret(%d/0x%llx) time(%llu) pid(%d/%d)\n",
			(uint64_t)mpriv, c->uid, c->kid, c->rvid, ret,
			c->einfos->c.sc_rets, c->einfos->c.total_us, c->pid,
			c->tgid);
	}

	mdw_cmd_cmdbuf_out(mpriv, c);

	/* signal done */
	c->fence = NULL;
	/* atomic running counter was removed from struct mdw_cmd */
	if (dma_fence_signal(f)) {
		mdw_drv_warn("c(0x%llx) signal fence fail\n", (uint64_t)c);
		if (f->ops->get_timeline_name && f->ops->get_driver_name) {
			mdw_drv_warn(" fence name(%s-%s)\n",
				     f->ops->get_driver_name(f),
				     f->ops->get_timeline_name(f));
		}
	}
	dma_fence_put(f);
	/* atomic active cmd counter was removed from struct mdw_fpriv */
	mutex_unlock(&c->mtx);

	/* check mpriv to clean cmd */
	mutex_lock(&mpriv->mtx);
	pr_err("mdw release_cmd hook unavailable\n");
	mutex_unlock(&mpriv->mtx);

	/* put cmd execution ref */
	mdw_cmd_put(c);
	mdw_trace_end();

	return 0;
}

static void mdw_cmd_trigger_func(struct work_struct *wk)
{
	struct mdw_cmd *c = container_of(wk, struct mdw_cmd, t_wk);
	int ret = 0;

	if (c->wait_fence) {
		dma_fence_wait(c->wait_fence, false);
		dma_fence_put(c->wait_fence);
	}

	mdw_flw_debug("s(0x%llx) c(0x%llx) wait fence done, start run\n",
		      (uint64_t)c->mpriv, c->kid);
	mutex_lock(&c->mtx);
	ret = mdw_cmd_run(c->mpriv, c);
	mutex_unlock(&c->mtx);

	/* put cmd execution ref */
	if (ret) {
		/* atomic running counter was removed from struct mdw_cmd */
		mdw_cmd_put(c);
	}
}

static struct mdw_cmd *mdw_cmd_create(struct mdw_fpriv *mpriv,
				      union mdw_cmd_args *args)
{
	struct mdw_cmd_in *in = (struct mdw_cmd_in *)args;
	struct mdw_cmd *c = NULL;

	mdw_trace_begin("apumdw:cmd_create|s:0x%llx", (uint64_t)mpriv);

	/* check num subcmds maximum */
	if (in->exec.num_subcmds > MDW_SUBCMD_MAX) {
		mdw_drv_err("too much subcmds(%u)\n", in->exec.num_subcmds);
		goto out;
	}

	/* alloc mdw cmd */
	c = kzalloc(sizeof(*c), GFP_KERNEL);
	if (!c)
		goto out;

	mutex_init(&c->mtx);
	c->mpriv = mpriv;
	/* Eliminado por refactorización de API moderna */

	/* setup cmd info */
	c->pid = task_pid_nr(current);
	c->tgid = task_tgid_nr(current);
	c->kid = (uint64_t)c;
	c->uid = in->exec.uid;
	c->priority = in->exec.priority;
	c->hardlimit = in->exec.hardlimit;
	c->softlimit = in->exec.softlimit;
	c->power_save = in->exec.power_save;
	c->power_plcy = in->exec.power_plcy;
	c->power_dtime = in->exec.power_dtime;
	c->app_type = in->exec.app_type;
	c->num_subcmds = in->exec.num_subcmds;
	c->exec_infos = mdw_mem_get(mpriv, in->exec.exec_infos);
	if (!c->exec_infos) {
		mdw_drv_err("get exec info fail\n");
		goto free_cmd;
	}

	/* check input params */
	if (mdw_cmd_sanity_check(c)) {
		mdw_drv_err("cmd sanity check fail\n");
		goto put_execinfos;
	}

	/* subcmds/ksubcmds */
	c->subcmds = kzalloc(c->num_subcmds * sizeof(*c->subcmds), GFP_KERNEL);
	if (!c->subcmds)
		goto put_execinfos;
	if (copy_from_user(c->subcmds, (void __user *)in->exec.subcmd_infos,
			   c->num_subcmds * sizeof(*c->subcmds))) {
		mdw_drv_err("copy subcmds fail\n");
		goto free_subcmds;
	}
	if (mdw_cmd_sc_sanity_check(c)) {
		mdw_drv_err("sc sanity check fail\n");
		goto free_subcmds;
	}

	c->ksubcmds =
		kzalloc(c->num_subcmds * sizeof(*c->ksubcmds), GFP_KERNEL);
	if (!c->ksubcmds)
		goto free_subcmds;

	/* adj matrix */
	c->adj_matrix = kzalloc(
		c->num_subcmds * c->num_subcmds * sizeof(uint8_t), GFP_KERNEL);
	if (!c->adj_matrix)
		goto free_ksubcmds;
	if (copy_from_user(
		    c->adj_matrix, (void __user *)in->exec.adj_matrix,
		    (c->num_subcmds * c->num_subcmds * sizeof(uint8_t)))) {
		mdw_drv_err("copy adj matrix fail\n");
		goto free_adj;
	}
	if (g_mdw_klog & MDW_DBG_CMD) {
		print_hex_dump(KERN_INFO,
			       "[apusys] adj matrix: ", DUMP_PREFIX_OFFSET, 16,
			       1, c->adj_matrix,
			       c->num_subcmds * c->num_subcmds, 0);
	}
	if (mdw_cmd_adj_check(c))
		goto free_adj;

	/* Eliminado por refactorización de API moderna */

	/* create infos */
	if (mdw_cmd_create_infos(mpriv, c)) {
		mdw_drv_err("create cmd info fail\n");
		goto free_adj;
	}

	c->mpriv->get(c->mpriv);
	c->complete = mdw_cmd_complete;
	INIT_WORK(&c->t_wk, &mdw_cmd_trigger_func);
	/* Eliminado por refactorización de API moderna */
	mdw_cmd_show(c, mdw_drv_debug);

	goto out;

free_adj:
	kfree(c->adj_matrix);
free_ksubcmds:
	kfree(c->ksubcmds);
free_subcmds:
	kfree(c->subcmds);
put_execinfos:
	mdw_mem_put(mpriv, c->exec_infos);
free_cmd:
	kfree(c);
	c = NULL;
out:
	mdw_trace_end();
	return c;
}

static int mdw_cmd_ioctl_run_v3(struct mdw_fpriv *mpriv,
				union mdw_cmd_args *args)
{
	struct mdw_cmd_in *in = (struct mdw_cmd_in *)args;
	struct mdw_cmd *c = NULL;
	struct sync_file *sync_file = NULL;
	int ret = 0, fd = 0, wait_fd = 0;

	/* Eliminado por refactorización de API moderna */

	/* get wait fd */
	wait_fd = in->exec.fence;

	mutex_lock(&mpriv->mtx);
	/* Eliminado por refactorización de API moderna */
	mdw_cmd_debug("s(0x%llx) create new\n", (uint64_t)mpriv);

	/* create cmd */
	c = mdw_cmd_create(mpriv, args);
	if (!c) {
		mdw_drv_err("create cmd fail\n");
		ret = -EINVAL;
		goto out;
	}
	memset(args, 0, sizeof(*args));
	mutex_lock(&c->mtx);
	/* Eliminado por refactorización de API moderna */
	/* get sync_file fd */
	fd = get_unused_fd_flags(O_CLOEXEC);
	if (fd < 0) {
		mdw_drv_err("get unused fd fail\n");
		ret = -EINVAL;
		goto delete_idr;
	}
	/* Eliminado por refactorización de API moderna */
	/* if (mdw_fence_init(c, fd)) {
	 * 	mdw_drv_err("cmd init fence fail\n");
	 * 	goto put_fd;
	 * }
	 */
	sync_file = sync_file_create(&c->fence->base_fence);
	if (!sync_file) {
		mdw_drv_err("create sync file fail\n");
		dma_fence_put(&c->fence->base_fence);
		ret = -ENOMEM;
		goto put_fd;
	}

	/* Eliminado por refactorización de API moderna */
	mdw_cmd_get(c);

	/* check wait fence from other module */
	mdw_flw_debug("s(0x%llx)c(0x%llx) wait fence(%d)...\n",
		      (uint64_t)c->mpriv, c->kid, wait_fd);
	c->wait_fence = sync_file_get_fence(wait_fd);
	if (!c->wait_fence) {
		mdw_flw_debug(
			"s(0x%llx)c(0x%llx) no wait fence, trigger directly\n",
			(uint64_t)c->mpriv, c->kid);
		ret = mdw_cmd_run(mpriv, c);
	} else {
		/* wait fence from wq */
		schedule_work(&c->t_wk);
	}

	if (ret) {
		/* put cmd execution ref */
		/* atomic running counter was removed from struct mdw_cmd */
		mdw_cmd_put(c);
		goto put_file;
	}

	/* assign fd */
	fd_install(fd, sync_file->file);

	/* Eliminado por refactorización de API moderna */

	/* return fd */
	args->out.exec.fence = fd;
	args->out.exec.id = 0;
	mdw_flw_debug("async fd(%d) id(%d)\n", fd, args->out.exec.id);
	mutex_unlock(&c->mtx);
	goto out;

put_file:
	fput(sync_file->file);
put_fd:
	put_unused_fd(fd);
delete_idr:
	/* Eliminado por refactorización de API moderna */
	mutex_unlock(&c->mtx);
	mdw_cmd_delete(c);
out:
	mutex_unlock(&mpriv->mtx);
	/* Eliminado por refactorización de API moderna */

	mdw_trace_end();

	return ret;
}
int mdw_cmd_ioctl_v3(struct mdw_fpriv *mpriv, void *data)
{
	union mdw_cmd_args *args = (union mdw_cmd_args *)data;
	int ret = 0;

	mdw_flw_debug("s(0x%llx) op::%d\n", (uint64_t)mpriv, args->in.op);

	switch (args->in.op) {
	case MDW_CMD_IOCTL_RUN:
		ret = mdw_cmd_ioctl_run_v3(mpriv, args);
		break;
		/* Eliminado por refactorización de API moderna */

	default:
		ret = -EINVAL;
		break;
	}
	mdw_flw_debug("done\n");

	return ret;
}
