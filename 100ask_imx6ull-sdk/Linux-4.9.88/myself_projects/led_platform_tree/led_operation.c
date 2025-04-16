#include "led_operation.h"
#include "led_driver.h"
#include "led_resource.h"
#include <linux/gfp.h>
#include <linux/gpio.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>

static int ledpins[100];
static int ledcnt = 0;

// int led_operations_led_init(unsigned int whichLed) {
//   printk("init gpio: group %d, pin %d\n", GROUP(ledpins[whichLed]),
//          PIN(ledpins[whichLed]));

//   return 0;
// }

// int led_operations_led_ctl(unsigned int whichLed, unsigned int level) {
//   printk("set led %s: group %d, pin %d\n", level ? "off" : "on",
//          GROUP(ledpins[whichLed]), PIN(ledpins[whichLed]));

//   return 0;
// }

int led_operations_led_init(unsigned int whichLed) {
  int group = GROUP(ledpins[whichLed]);
  int pin = PIN(ledpins[whichLed]);
  int gpio = (group - 1) * 32 + pin;
  int ret;

  ret = gpio_request(gpio, "ccoisini_led");
  if (ret) {
    pr_err("Failed to request GPIO %d\n", gpio);
    return ret;
  }

  gpio_direction_output(gpio, 1); // 默认关闭LED

  pr_info("Initialized GPIO: group %d, pin %d (GPIO %d)\n", group, pin, gpio);
  return 0;
}
int led_operations_led_ctl(unsigned int whichLed, unsigned int level) {
  int group = GROUP(ledpins[whichLed]);
  int pin = PIN(ledpins[whichLed]);
  int gpio = (group - 1) * 32 + pin;

  gpio_set_value(gpio, level);

  pr_debug("Set LED %s: group %d, pin %d (GPIO %d)\n", level ? "off" : "on",
           group, pin, gpio);
  return 0;
}

static struct led_operations led_opr = {
    .led_init = led_operations_led_init,
    .led_ctl = led_operations_led_ctl,
};

struct led_operations *get_led_operations(void) {
  return &led_opr;
}

int led_platform_driver_probe(struct platform_device *pdev) {

  int gpio_pin;
  // 获取设备节点
  struct device_node *dev_node = pdev->dev.of_node;
  if (!dev_node) {
    dev_err(&pdev->dev, "No device tree node found\n");
    return -EINVAL;
  }

  // 读取值，读取到的值是GROUP+PIN组成的数字，用到时需要拆分
  if (of_property_read_u32(dev_node, "pin", &gpio_pin)) {
    dev_err(&pdev->dev, "Failed to get pin property\n");
    return -EINVAL;
  }

  if (ledcnt >= ARRAY_SIZE(ledpins)) {
    dev_err(&pdev->dev, "Too many LEDs, maximum is %d\n", ARRAY_SIZE(ledpins));
    return -ENOMEM;
  }
  // 使用数组存储该值
  ledpins[ledcnt] = gpio_pin;
  // 激活顶层驱动中的创建设备节点
  led_device_create(ledcnt);
  // 用于下一次probe触发时存储的索引位置、计算当前有多少led、创建设备节点
  ledcnt++;

  // 将led_operations激活给顶层驱动使用
  active_led_operation(&led_opr);

  return 0;
}

int led_platform_driver_remove(struct platform_device *pdev) {

  int i;
  int gpio_pin;
  int res_ledcnt;
  struct device_node *dev_node = pdev->dev.of_node;
  if (!dev_node) {
    return -1;
  }

  // 确定触发remove的对应gpio
  of_property_read_u32(dev_node, "pin", &gpio_pin);
  // 查询数组，删除对应的设备节点
  res_ledcnt = ledcnt;
  for (i = 0; i < ledcnt; i++) {
    if (gpio_pin == ledpins[i]) {
      led_device_destroy(i);
      ledpins[i] = -1;
      res_ledcnt--;
      break;
    }
  }
  ledcnt = res_ledcnt;

  return 0;
}

static const struct of_device_id led_platform_match_table[] = {
    {.compatible = "ccoisini,led_drv"},
    {},
};

static struct platform_driver led_platform_driver = {
    .probe = led_platform_driver_probe,
    .remove = led_platform_driver_remove,
    .driver = {
        .name = "ccoisini_led",
        .of_match_table = led_platform_match_table,
    }};

static int __init led_platform_driver_init(void) {
  return platform_driver_register(&led_platform_driver);
}

static void __exit led_platform_driver_exit(void) {
  platform_driver_unregister(&led_platform_driver);
}

module_init(led_platform_driver_init);
module_exit(led_platform_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CCoisini");
MODULE_DESCRIPTION("LED Platform Driver");
