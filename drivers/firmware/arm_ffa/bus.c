// SPDX-License-Identifier: GPL-2.0-only
/*
 * Arm Firmware Framework for Arm (FF-A) — virtual bus
 *
 * Backported to Linux 5.10 for MediaTek MT6879 / Trustonic MobiCore 610.
 * No Device Tree node is required; the transport probes via SMC.
 *
 * Copyright (C) 2021 ARM Ltd.
 * Backport/adaptation Copyright (C) 2024 RebelPilot89
 */

#include <linux/arm_ffa.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uuid.h>

/* ------------------------------------------------------------------------ */
/* FFA bus type                                                              */
/* ------------------------------------------------------------------------ */

static int ffa_device_match(struct device *dev, struct device_driver *drv)
{
	const struct ffa_device_id *id_table;
	struct ffa_driver *ffa_drv;
	struct ffa_device *ffa_dev;

	ffa_dev = to_ffa_dev(dev);
	ffa_drv = to_ffa_driver(drv);
	id_table = ffa_drv->id_table;

	while (!uuid_is_null(&id_table->uuid)) {
		if (uuid_equal(&ffa_dev->uuid, &id_table->uuid))
			return 1;
		id_table++;
	}

	return 0;
}

static int ffa_device_probe(struct device *dev)
{
	struct ffa_driver *ffa_drv = to_ffa_driver(dev->driver);
	struct ffa_device *ffa_dev = to_ffa_dev(dev);

	return ffa_drv->probe(ffa_dev);
}

static void ffa_device_remove(struct device *dev)
{
	struct ffa_driver *ffa_drv = to_ffa_driver(dev->driver);

	if (ffa_drv->remove)
		ffa_drv->remove(to_ffa_dev(dev));
}

static int ffa_device_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct ffa_device *ffa_dev = to_ffa_dev(dev);
	char buf[UUID_STRING_LEN + 1];

	uuid_unparse_lower(ffa_dev->uuid, buf);
	return add_uevent_var(env, "MODALIAS=ffa:%s", buf);
}

static ssize_t modalias_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct ffa_device *ffa_dev = to_ffa_dev(dev);
	char uuid_buf[UUID_STRING_LEN + 1];

	uuid_unparse_lower(ffa_dev->uuid, uuid_buf);
	return sysfs_emit(buf, "ffa:%s\n", uuid_buf);
}
static DEVICE_ATTR_RO(modalias);

static ssize_t id_show(struct device *dev, struct device_attribute *attr,
		       char *buf)
{
	return sysfs_emit(buf, "0x%x\n", to_ffa_dev(dev)->id);
}
static DEVICE_ATTR_RO(id);

static ssize_t vm_id_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	return sysfs_emit(buf, "0x%x\n", to_ffa_dev(dev)->vm_id);
}
static DEVICE_ATTR_RO(vm_id);

static struct attribute *ffa_device_attributes[] = {
	&dev_attr_modalias.attr,
	&dev_attr_id.attr,
	&dev_attr_vm_id.attr,
	NULL,
};
ATTRIBUTE_GROUPS(ffa_device);

struct bus_type ffa_bus_type = {
	.name		= "arm_ffa",
	.match		= ffa_device_match,
	.probe		= ffa_device_probe,
	.remove		= ffa_device_remove,
	.uevent		= ffa_device_uevent,
	.dev_groups	= ffa_device_groups,
};
EXPORT_SYMBOL_GPL(ffa_bus_type);

/* ------------------------------------------------------------------------ */
/* FFA device lifecycle                                                      */
/* ------------------------------------------------------------------------ */

static void ffa_release_device(struct device *dev)
{
	struct ffa_device *ffa_dev = to_ffa_dev(dev);

	kfree(ffa_dev);
}

struct ffa_device *ffa_device_register(const uuid_t *uuid, int vm_id,
					const struct ffa_ops *ops)
{
	static atomic_t dev_cnt = ATOMIC_INIT(0);
	struct ffa_device *ffa_dev;
	int id, ret;

	ffa_dev = kzalloc(sizeof(*ffa_dev), GFP_KERNEL);
	if (!ffa_dev)
		return ERR_PTR(-ENOMEM);

	uuid_copy(&ffa_dev->uuid, uuid);
	ffa_dev->vm_id = vm_id;
	ffa_dev->ops   = ops;
	ffa_dev->id    = (u32)atomic_inc_return(&dev_cnt);

	ffa_dev->dev.bus     = &ffa_bus_type;
	ffa_dev->dev.release = ffa_release_device;

	id = dev_set_name(&ffa_dev->dev, "arm-ffa-%d", ffa_dev->id);
	if (id) {
		kfree(ffa_dev);
		return ERR_PTR(id);
	}

	ret = device_register(&ffa_dev->dev);
	if (ret) {
		put_device(&ffa_dev->dev);
		return ERR_PTR(ret);
	}

	return ffa_dev;
}
EXPORT_SYMBOL_GPL(ffa_device_register);

void ffa_device_unregister(struct ffa_device *ffa_dev)
{
	if (!ffa_dev)
		return;
	device_unregister(&ffa_dev->dev);
}
EXPORT_SYMBOL_GPL(ffa_device_unregister);

bool ffa_device_is_valid(struct ffa_device *ffa_dev)
{
	/* If CONFIG_ARM_FFA_TRANSPORT is reachable, any registered device is valid. */
	return (ffa_dev && ffa_dev->dev.bus == &ffa_bus_type);
}
EXPORT_SYMBOL_GPL(ffa_device_is_valid);

/* ------------------------------------------------------------------------ */
/* FFA driver registration                                                   */
/* ------------------------------------------------------------------------ */

int ffa_driver_register(struct ffa_driver *driver, struct module *owner,
			const char *mod_name)
{
	if (!driver->probe)
		return -EINVAL;

	driver->driver.bus    = &ffa_bus_type;
	driver->driver.name   = driver->name;
	driver->driver.owner  = owner;
	driver->driver.mod_name = mod_name;

	return driver_register(&driver->driver);
}
EXPORT_SYMBOL_GPL(ffa_driver_register);

void ffa_driver_unregister(struct ffa_driver *driver)
{
	driver_unregister(&driver->driver);
}
EXPORT_SYMBOL_GPL(ffa_driver_unregister);

/* ------------------------------------------------------------------------ */
/* Module init / exit                                                        */
/* ------------------------------------------------------------------------ */

int __init arm_ffa_bus_init(void)
{
	return bus_register(&ffa_bus_type);
}

void __exit arm_ffa_bus_exit(void)
{
	bus_unregister(&ffa_bus_type);
}
