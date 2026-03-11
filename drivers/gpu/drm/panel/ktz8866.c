// SPDX-License-Identifier: GPL-2.0
/*
 * KTZ8866 LCD Backlight and Bias I2C Driver
 *
 * Ported from OnePlusOSS/android_kernel_oneplus_mt6789 to the
 * Motorola Edge 40 Neo (manaus / MT6879) kernel tree.
 * Removed get_PCB_Version() dependency — not present in this tree.
 *
 * Copyright (c) 2021 MediaTek Inc.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/backlight.h>
#include <linux/gpio/consumer.h>

#include "ktz8866.h"

#define LCD_BL_I2C_ID_NAME "lcd_bl"

#define KTZ8866_I2C0_NAME "0-0011"
#define KTZ8866_I2C3_NAME "3-0011"

int g_lcd_bias_id = KTZ8866_ID;
struct i2c_client *lcd_bl_i2c0_aw3750x;

struct i2c_client *lcd_bl_i2c0_client;
struct i2c_client *lcd_bl_i2c3_client;
static DEFINE_MUTEX(read_lock);

EXPORT_SYMBOL(g_lcd_bias_id);
EXPORT_SYMBOL(lcd_bl_i2c0_aw3750x);
EXPORT_SYMBOL(lcd_bl_i2c0_client);
EXPORT_SYMBOL(lcd_bl_i2c3_client);

static int lcd_bl_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int lcd_bl_i2c_remove(struct i2c_client *client);

int lcd_bl_i2c_write_dual(struct i2c_client *i2c_client0,
		unsigned char i2c_client0_addr, unsigned char i2c_client0_value,
		struct i2c_client *i2c_client1,
		unsigned char i2c_client1_addr, unsigned char i2c_client1_value)
{
	int ret = 0;
	unsigned char write_data[2] = {0};

	if (i2c_client0) {
		write_data[0] = i2c_client0_addr;
		write_data[1] = i2c_client0_value;
		ret = i2c_master_send(i2c_client0, write_data, 2);
		if (ret < 0)
			pr_err("[LCD][BL] i2c write data fail %s !!\n",
			       dev_name(&i2c_client0->dev));
	}

	if (i2c_client1) {
		write_data[0] = i2c_client1_addr;
		write_data[1] = i2c_client1_value;
		ret = i2c_master_send(i2c_client1, write_data, 2);
		if (ret < 0)
			pr_err("[LCD][BL] i2c write data fail %s !!\n",
			       dev_name(&i2c_client1->dev));
	}

	return ret;
}
EXPORT_SYMBOL(lcd_bl_i2c_write_dual);

int lcd_bl_i2c_read_dual(struct i2c_client *i2c_client0,
		unsigned char i2c_client0_addr, unsigned char *i2c_client0_buf,
		struct i2c_client *i2c_client1,
		unsigned char i2c_client1_addr, unsigned char *i2c_client1_buf)
{
	int res = 0;

	mutex_lock(&read_lock);

	if (i2c_client0) {
		res = i2c_master_send(i2c_client0, &i2c_client0_addr, 0x1);
		if (res <= 0) {
			mutex_unlock(&read_lock);
			pr_err("[LCD][BL] read reg send res = %d %s\n", res,
			       dev_name(&i2c_client0->dev));
			return res;
		}
		res = i2c_master_recv(i2c_client0, i2c_client0_buf, 0x1);
		if (res <= 0) {
			mutex_unlock(&read_lock);
			pr_err("[LCD][BL] read reg recv res = %d %s\n", res,
			       dev_name(&i2c_client0->dev));
			return res;
		}
	} else {
		pr_info("[LCD][BL] i2c_client0 is NULL\n");
	}

	if (i2c_client1) {
		res = i2c_master_send(i2c_client1, &i2c_client1_addr, 0x1);
		if (res <= 0) {
			mutex_unlock(&read_lock);
			pr_err("[LCD][BL] read reg send res = %d %s\n", res,
			       dev_name(&i2c_client1->dev));
			return res;
		}
		res = i2c_master_recv(i2c_client1, i2c_client1_buf, 0x1);
		if (res <= 0) {
			mutex_unlock(&read_lock);
			pr_err("[LCD][BL] read reg recv res = %d %s\n", res,
			       dev_name(&i2c_client1->dev));
			return res;
		}
	} else {
		pr_info("[LCD][BL] i2c_client1 is NULL\n");
	}

	mutex_unlock(&read_lock);

	return res;
}
EXPORT_SYMBOL(lcd_bl_i2c_read_dual);

int lcd_bl_write_byte(unsigned char addr, unsigned char value)
{
	int ret = 0;
	unsigned char write_data[2] = {0};

	write_data[0] = addr;
	write_data[1] = value;

	if (!lcd_bl_i2c0_client) {
		pr_debug("[LCD][BL] lcd_bl_i2c0_client is null!!\n");
		return -EINVAL;
	}
	ret = i2c_master_send(lcd_bl_i2c0_client, write_data, 2);
	if (ret < 0)
		pr_debug("[LCD][BL] i2c write data fail !!\n");

	return ret;
}
EXPORT_SYMBOL(lcd_bl_write_byte);

static int lcd_bl_read_byte(u8 regnum)
{
	u8 buffer[1], reg_value[1];
	int res = 0;

	if (!lcd_bl_i2c0_client) {
		pr_debug("[LCD][BL] lcd_bl_i2c0_client is null!!\n");
		return -EINVAL;
	}

	mutex_lock(&read_lock);

	buffer[0] = regnum;
	res = i2c_master_send(lcd_bl_i2c0_client, buffer, 0x1);
	if (res <= 0) {
		mutex_unlock(&read_lock);
		pr_debug("read reg send res = %d\n", res);
		return res;
	}
	res = i2c_master_recv(lcd_bl_i2c0_client, reg_value, 0x1);
	if (res <= 0) {
		mutex_unlock(&read_lock);
		pr_debug("read reg recv res = %d\n", res);
		return res;
	}
	mutex_unlock(&read_lock);

	return reg_value[0];
}

int lcd_bl_set_led_brightness(int value)
{
	pr_debug("%s: bl = %d\n", __func__, value);

	if (value < 0) {
		pr_debug("%s: invalid value=%d\n", __func__, value);
		return 0;
	}

	if (value > 0) {
		lcd_bl_write_byte(0x04, value & 0x07);
		lcd_bl_write_byte(0x05, (value >> 3) & 0xFF);
	} else {
		lcd_bl_write_byte(0x04, 0x00);
		lcd_bl_write_byte(0x05, 0x00);
	}

	return 0;
}
EXPORT_SYMBOL(lcd_bl_set_led_brightness);

int lcd_set_bias(int enable)
{
	pr_debug("%s: enable=%d\n", __func__, enable);
	if (enable) {
		lcd_bl_write_byte(0x09, 0x9C); /* enable OUTP */
		msleep(5);
		lcd_bl_write_byte(0x09, 0x9E); /* enable OUTN */
	} else {
		lcd_bl_write_byte(0x09, 0x9C); /* Disable OUTN */
		msleep(5);
		lcd_bl_write_byte(0x09, 0x98); /* Disable OUTP */
	}
	return 0;
}
EXPORT_SYMBOL(lcd_set_bias);

int lcd_set_bl_bias_reg(struct device *pdev, int enable)
{
	struct device *dev = pdev;
	struct gpio_desc *hw_led_en;
	int res = 0;

	if (enable) {
		hw_led_en = devm_gpiod_get(dev, "pm-enable", GPIOD_OUT_HIGH);
		if (IS_ERR(hw_led_en))
			pr_debug("could not get pm-enable gpio\n");
		else {
			gpiod_set_value(hw_led_en, 1);
			devm_gpiod_put(dev, hw_led_en);
		}
		usleep_range(125, 130);

		lcd_bl_write_byte(0x0C, 0x30); /* LCD_BOOST_CFG */
		lcd_bl_write_byte(0x0D, 0x28); /* OUTP = 6.0V */
		lcd_bl_write_byte(0x0E, 0x28); /* OUTN = -6.0V */

		lcd_bl_write_byte(0x09, 0x9C); /* enable OUTP */
		msleep(5);
		lcd_bl_write_byte(0x09, 0x9E); /* enable OUTN */

		lcd_bl_write_byte(0x02, 0x3B); /* BL_CFG1: OVP=34V, linear dimming */
		lcd_bl_write_byte(0x11, 0x37); /* BL_OPTION2: 4.7uH, 2.5A limit */
		lcd_bl_write_byte(0x15, 0xB0); /* Full-scale LED current 22.8mA/CH */
		lcd_bl_write_byte(0x08, 0x5F); /* BL enabled, sinks 1-5 enabled */
	} else {
		hw_led_en = devm_gpiod_get(dev, "pm-enable", GPIOD_OUT_HIGH);
		if (IS_ERR(hw_led_en))
			pr_debug("could not get pm-enable gpio\n");

		lcd_bl_write_byte(0x09, 0x9C); /* Disable OUTN */
		msleep(5);
		lcd_bl_write_byte(0x09, 0x98); /* Disable OUTP */
		lcd_bl_write_byte(0x08, 0x00); /* BL disabled */

		if (!IS_ERR(hw_led_en)) {
			gpiod_set_value(hw_led_en, 0);
			devm_gpiod_put(dev, hw_led_en);
		}
	}
	res = lcd_bl_read_byte(0x0f);
	pr_debug("%s: ktz8866 0x0f = 0x%x\n", __func__, res);

	return 0;
}
EXPORT_SYMBOL(lcd_set_bl_bias_reg);

#ifdef CONFIG_OF
static const struct of_device_id i2c_of_match[] = {
	{ .compatible = "ktz,ktz8866", },
	{},
};
#endif

static const struct i2c_device_id lcd_bl_i2c_id[] = {
	{ LCD_BL_I2C_ID_NAME, 0 },
	{},
};

static struct i2c_driver lcd_bl_i2c_driver = {
	.id_table = lcd_bl_i2c_id,
	.probe = lcd_bl_i2c_probe,
	.remove = lcd_bl_i2c_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name = LCD_BL_I2C_ID_NAME,
#ifdef CONFIG_OF
		.of_match_table = i2c_of_match,
#endif
	},
};

static int lcd_bl_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	int ret;
	struct device_node *np;

	if (!client) {
		pr_err("[LCD][BL] i2c_client is NULL\n");
		return -EINVAL;
	}

	pr_info("%s dev_name:%s\n", __func__, dev_name(&client->dev));

	if (!strcmp(dev_name(&client->dev), KTZ8866_I2C0_NAME)) {
		lcd_bl_i2c0_client = client;
		np = client->dev.of_node;
		if (of_property_read_bool(np, "skip_ktz8866_i2c0")) {
			pr_warn("[lcd_info] skip %s %s\n", __func__, KTZ8866_I2C0_NAME);
			return 0;
		}
	}

	if (!strcmp(dev_name(&client->dev), KTZ8866_I2C3_NAME)) {
		lcd_bl_i2c3_client = client;
		np = client->dev.of_node;
		if (of_property_read_bool(np, "skip_ktz8866_i2c3")) {
			pr_warn("[lcd_info] skip %s %s\n", __func__, KTZ8866_I2C3_NAME);
			return 0;
		}
	}

	/* Initialise bias and backlight registers */
	ret = lcd_bl_write_byte(0x0C, 0x30); /* LCD_BOOST_CFG */
	ret = lcd_bl_write_byte(0x0D, 0x28); /* OUTP = 6.0V */
	ret = lcd_bl_write_byte(0x0E, 0x28); /* OUTN = -6.0V */
	ret = lcd_bl_write_byte(0x09, 0x9C); /* enable OUTP */
	msleep(5);
	ret = lcd_bl_write_byte(0x09, 0x9E); /* enable OUTN */
	ret = lcd_bl_write_byte(0x02, 0x3B); /* BL_CFG1 */
	ret = lcd_bl_write_byte(0x11, 0x37); /* BL_OPTION2 */
	ret = lcd_bl_write_byte(0x15, 0xB0); /* Full-scale LED current */
	ret = lcd_bl_write_byte(0x08, 0x5F); /* BL enabled */

	if (ret < 0) {
		pr_err("[LCD][BL] %s: I2C write failed\n", __func__);
		return -EINVAL;
	}

	pr_info("[LCD][BL] %s: KTZ8866 initialised\n", __func__);
	return 0;
}

static int lcd_bl_i2c_remove(struct i2c_client *client)
{
	lcd_bl_i2c0_client = NULL;
	lcd_bl_i2c3_client = NULL;
	i2c_unregister_device(client);
	return 0;
}

static int __init lcd_bl_init(void)
{
	pr_debug("lcd_bl_init\n");
	if (i2c_add_driver(&lcd_bl_i2c_driver)) {
		pr_err("[LCD][BL] Failed to register lcd_bl_i2c_driver!\n");
		return -EINVAL;
	}
	return 0;
}

static void __exit lcd_bl_exit(void)
{
	i2c_del_driver(&lcd_bl_i2c_driver);
}

module_init(lcd_bl_init);
module_exit(lcd_bl_exit);

MODULE_AUTHOR("MediaTek LCD BL Driver (ported to manaus/MT6879)");
MODULE_DESCRIPTION("KTZ8866 LCD Backlight and Bias I2C Driver");
MODULE_LICENSE("GPL v2");
