// 这个文件控制的是GPIO5_3对应的LED
#include "led_driver.h"
#include "led_operation.h"
#include "led_resource.h"
#include <linux/gfp.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>

static void led_dev_release(struct device *dev) {}

static struct resource resources[] = {
    {
        .start = GROUP_PIN(5, 3),
        .flags = IORESOURCE_IO,
        .name = "ccoisini_led_pin",
    },
};

static struct platform_device led_A_platform_device = {
    .name = "ccoisini_led",
    .num_resources = ARRAY_SIZE(resources),
    .resource = resources,
    .dev =
        {
            .release = led_dev_release,
        },
};

static int __init led_dev_init(void) {
  return platform_device_register(&led_A_platform_device);
}

static void __exit led_dev_exit(void) {
  platform_device_unregister(&led_A_platform_device);
}

module_init(led_dev_init);
module_exit(led_dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CCoisini");
MODULE_DESCRIPTION("LED Platform Device");