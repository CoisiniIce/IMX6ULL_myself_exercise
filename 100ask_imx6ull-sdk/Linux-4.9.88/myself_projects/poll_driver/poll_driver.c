#include <linux/device.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/major.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/tty.h>
#include <linux/wait.h>
#include <linux/workqueue.h>

// 定义设备名称和最大GPIO数量
#define DEVICE_NAME "ccoisini-keys"
#define MAX_GPIO_KEYS 32

// 设备数据结构
struct gpio_keys_device {
  struct gpio_desc *gpiod;
  int gpio;
  int flag;
  int irq;
  int last_value;          // 记录上一次的值
  struct work_struct work; // 工作队列项
};
// 全局设备状态
struct gpio_keys_driver_data {
  struct gpio_keys_device *keys;
  int gpio_count;
  wait_queue_head_t waitq; // 等待队列
  unsigned int event_flag; // 事件标志
  struct mutex lock;       // 互斥锁
};

static struct gpio_keys_driver_data *drv_data;

// 工作队列处理函数
static void gpio_key_work_handler(struct work_struct *work) {

  struct gpio_keys_device *key =
      container_of(work, struct gpio_keys_device, work);
  int val = gpiod_get_value(key->gpiod);

  // 只处理值变化的情况
  if (val != key->last_value) {
    key->last_value = val;

    mutex_lock(&drv_data->lock);
    drv_data->event_flag = 1;                // 设置事件标志
    wake_up_interruptible(&drv_data->waitq); // 唤醒等待队列
    mutex_unlock(&drv_data->lock);

    printk("key %d %d\n", key->gpio, val);
  }
}

static irqreturn_t gpio_key_isr(int irq, void *dev_id) {

  struct gpio_keys_device *key = dev_id;
  // 调度工作队列处理
  schedule_work(&key->work);

  return IRQ_HANDLED;
}

// poll操作函数
static unsigned int gpio_keys_poll(struct file *file, poll_table *wait) {
  unsigned int mask = 0;

  // 将等待队列添加到poll_table
  poll_wait(file, &drv_data->waitq, wait);

  mutex_lock(&drv_data->lock);
  if (drv_data->event_flag) {
    mask |= POLLIN | POLLRDNORM; // 可读事件
  }
  mutex_unlock(&drv_data->lock);

  return mask;
}

// 文件操作结构体
static const struct file_operations gpio_keys_fops = {
    .owner = THIS_MODULE,
    .poll = gpio_keys_poll,
};

int gpio_interrupt_test_probe(struct platform_device *pdev) {

  int i, ret;
  int gpio_count;
  enum of_gpio_flags gpio_flag;
  struct device_node *dev_node = pdev->dev.of_node;

  // 分配驱动数据结构
  drv_data = kzalloc(sizeof(struct gpio_keys_driver_data), GFP_KERNEL);
  if (!drv_data) {
    return -ENOMEM;
  }

  // 初始化互斥锁和等待队列
  mutex_init(&drv_data->lock);
  init_waitqueue_head(&drv_data->waitq);

  // 获取GPIO数量
  gpio_count = of_gpio_count(dev_node);
  if (gpio_count <= 0 || gpio_count > MAX_GPIO_KEYS) {
    pr_err("Invalid gpio count %d\n", gpio_count);
    ret = -EINVAL;
    goto err_free_drv_data;
  }

  drv_data->gpio_count = gpio_count;
  drv_data->keys =
      kzalloc(sizeof(struct gpio_keys_device) * gpio_count, GFP_KERNEL);
  if (!drv_data->keys) {
    ret = -ENOMEM;
    goto err_free_drv_data;
  }

  // 初始化每个GPIO
  for (i = 0; i < gpio_count; i++) {
    struct gpio_keys_device *key = &drv_data->keys[i];

    key->gpio = of_get_gpio_flags(dev_node, i, &gpio_flag);
    if (key->gpio < 0) {
      pr_err("Failed to get gpio %d\n", i);
      ret = key->gpio;
      goto err_free_keys;
    }

    key->gpiod = gpio_to_desc(key->gpio);
    key->flag = gpio_flag & OF_GPIO_ACTIVE_LOW;
    key->irq = gpio_to_irq(key->gpio);
    key->last_value = gpiod_get_value(key->gpiod);

    // 初始化工作队列
    INIT_WORK(&key->work, gpio_key_work_handler);

    // 请求中断
    ret = request_irq(key->irq, gpio_key_isr,
                      IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                      "ccoisini-key-irq", key);
    if (ret) {
      pr_err("Failed to request irq %d\n", key->irq);
      goto err_free_irqs;
    }
  }

  // 注册字符设备
  ret = misc_register(&(struct miscdevice){
      .minor = MISC_DYNAMIC_MINOR,
      .name = DEVICE_NAME,
      .fops = &gpio_keys_fops,
  });
  if (ret) {
    pr_err("Failed to register misc device\n");
    goto err_free_irqs;
  }

  return 0;

err_free_irqs:
  for (i--; i >= 0; i--) {
    free_irq(drv_data->keys[i].irq, &drv_data->keys[i]);
  }
err_free_keys:
  kfree(drv_data->keys);
err_free_drv_data:
  kfree(drv_data);
  return ret;
}

int gpio_interrupt_test_remove(struct platform_device *pdev) {

  int i;

  // 注销字符设备
  misc_deregister(&(struct miscdevice){
      .minor = MISC_DYNAMIC_MINOR,
      .name = DEVICE_NAME,
  });

  // 释放中断和工作队列
  for (i = 0; i < drv_data->gpio_count; i++) {
    free_irq(drv_data->keys[i].irq, &drv_data->keys[i]);
    cancel_work_sync(&drv_data->keys[i].work);
  }

  // 释放内存
  kfree(drv_data->keys);
  kfree(drv_data);

  return 0;
}

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
