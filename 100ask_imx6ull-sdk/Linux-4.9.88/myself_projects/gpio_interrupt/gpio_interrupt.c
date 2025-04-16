#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>

struct gpio_keys_information {
  struct gpio_desc *gpiod;
  int gpio;
  int flag;
  int irq;
};

static struct gpio_keys_information *gpio_keys;

static irqreturn_t gpio_key_isr(int irq, void *single_gpio_key)
{
    int val;
    struct gpio_keys_information* gpio_key = single_gpio_key;
    val = gpiod_get_value(gpio_key->gpiod);

    printk("key %d %d\n", gpio_key->gpio, val);

    return IRQ_HANDLED;
}

int gpio_interrupt_test_probe(struct platform_device *pdev) {

  int i;
  int ret;
  int gpio_count;
  enum of_gpio_flags gpio_flag;

  struct device_node *dev_node = pdev->dev.of_node;

  gpio_count = of_gpio_count(dev_node);
  if (gpio_count < 0) {
    pr_err("Failed to get gpio count\r\n");
    return -1;
  }
  gpio_keys =
      kzalloc(sizeof(struct gpio_keys_information) * gpio_count, GFP_KERNEL);

  for (i = 0; i < gpio_count; i++) {
    gpio_keys[i].gpio = of_get_gpio_flags(dev_node, i, &gpio_flag);
    if (gpio_keys[i].gpio < 0) {
      printk("%s %s line %d, of_get_gpio_flags fail\n", __FILE__, __FUNCTION__,
             __LINE__);
      return -1;
    }
    gpio_keys[i].gpiod = gpio_to_desc(gpio_keys[i].gpio);
    gpio_keys[i].flag = gpio_flag & OF_GPIO_ACTIVE_LOW;
    gpio_keys[i].irq = gpio_to_irq(gpio_keys[i].gpio);
  }

  for (i = 0; i < gpio_count; i++) {
    ret = request_irq(gpio_keys[i].irq, gpio_key_isr,
                      IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                      "ccoisini-key-irq", &gpio_keys[i]);
  }

  return 0;
}

int gpio_interrupt_test_remove(struct platform_device *pdev) { 
    
    struct device_node *dev_node = pdev->dev.of_node;
    int i;
    int gpio_count;

    gpio_count = of_gpio_count(dev_node);

    for(i = 0;i < gpio_count;i++){
        free_irq(gpio_keys[i].irq, &gpio_keys[i]);
    }

    kfree(gpio_keys);

    return 0; }

static const struct of_device_id gpio_interrupt_test_match_table[] = {
    {.compatible = "ccoisini-keys"}, {}};

static struct platform_driver gpio_interrupt_test_driver = {
    .probe = gpio_interrupt_test_probe,
    .remove = gpio_interrupt_test_remove,
    .driver = {
        .name = "ccoisini-keys",
        .of_match_table = gpio_interrupt_test_match_table,
    }};

static int __init gpio_interrupt_test_init(void) {
  return platform_driver_register(&gpio_interrupt_test_driver);
}

static void __exit gpio_interrupt_test_exit(void) {
  platform_driver_unregister(&gpio_interrupt_test_driver);
}

module_init(gpio_interrupt_test_init);
module_exit(gpio_interrupt_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CCoisini");
MODULE_DESCRIPTION("GPIO Interrupt Test");
