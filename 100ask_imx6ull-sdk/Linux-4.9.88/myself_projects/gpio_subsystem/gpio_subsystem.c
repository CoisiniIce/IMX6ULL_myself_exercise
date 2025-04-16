#include <linux/device.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/major.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/tty.h>

#define DEVICE_NAME "led_device"
#define CLASS_NAME "led_class"

struct led_driver_struct {
  dev_t dev_number;
  struct class *dev_class;
  struct gpio_desc *dev_gpio;
  struct cdev dev_cdev;
  // 设备名称
  char *dev_name;
  // 类名
  char *class_name;
};

static struct led_driver_struct *led_dev;

static ssize_t led_opr_read(struct file *file, char __user *buf, size_t size,
                            loff_t *offset) {
  printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
  return 0;
}

/* write(fd, &val, 1); */
static ssize_t led_opr_write(struct file *file, const char __user *buf,
                             size_t size, loff_t *offset) {

  unsigned int status;
  if (copy_from_user(&status, buf, sizeof(status))) {
    return -EFAULT;
  }

  gpiod_set_value(led_dev->dev_gpio, status);

  return 1;
}

static int led_opr_open(struct inode *node, struct file *file) {
  printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

  // 初始化LED
  gpiod_direction_output(led_dev->dev_gpio, 0);
  return 0;
}

static int led_opr_close(struct inode *node, struct file *file) {
  printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
  return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_opr_open,
    .read = led_opr_read,
    .write = led_opr_write,
    .release = led_opr_close,
};

int led_platform_probe(struct platform_device *pdev) {

  int ret;

  printk("2");

  // 分配设备结构内存
  led_dev = kzalloc(sizeof(*led_dev), GFP_KERNEL);
  if (!led_dev)
    return -ENOMEM;

  led_dev->dev_name = DEVICE_NAME;
  led_dev->class_name = CLASS_NAME;

  ret = alloc_chrdev_region(&(led_dev->dev_number), 0, 1, led_dev->dev_name);
  if (ret < 0) {
    pr_err("Failed to allocate device numbers: %d\n", ret);
    goto free_dev;
  }
  // 创建字符设备
  cdev_init(&(led_dev->dev_cdev), &fops);
  led_dev->dev_cdev.owner = THIS_MODULE;
  ret = cdev_add(&(led_dev->dev_cdev), led_dev->dev_number, 1);
  if (ret < 0) {
    pr_err("Failed to add cdev: %d\n", ret);
    goto unreg_chrdev;
  }
  // 创建设备类
  led_dev->dev_class = class_create(THIS_MODULE, led_dev->class_name);
  if (IS_ERR(led_dev->dev_class)) {
    ret = PTR_ERR(led_dev->dev_class);
    pr_err("Failed to create class: %pe\n", led_dev->dev_class);
    goto del_cdev;
  }

  // 获取GPIO描述符
  led_dev->dev_gpio = gpiod_get(&pdev->dev, "ccoisini_led", GPIOD_OUT_LOW);
  if (IS_ERR(led_dev->dev_gpio)) {
    ret = PTR_ERR(led_dev->dev_gpio);
    pr_err("Failed to get gpio: %pe\n", led_dev->dev_gpio);
    goto gpio_delete;
  }

  device_create(led_dev->dev_class, NULL, led_dev->dev_number, NULL,
                "ccoisini_led");

  printk(KERN_INFO "Device driver loaded\n");

  return 0;

gpio_delete:
  gpiod_put(led_dev->dev_gpio);
del_cdev:
  cdev_del(&led_dev->dev_cdev);
unreg_chrdev:
  unregister_chrdev_region(led_dev->dev_number, 1);
free_dev:
  kfree(led_dev);
  led_dev = NULL;
  return ret;
}

int led_platform_remove(struct platform_device *pdev) {
  // 1. 销毁设备节点
  device_destroy(led_dev->dev_class, led_dev->dev_number);
  // 2. 销毁设备类
  class_destroy(led_dev->dev_class);
  // 3. 删除字符设备
  cdev_del(&(led_dev->dev_cdev));
  // 4. 释放设备号
  unregister_chrdev_region(led_dev->dev_number, 1);
  return 0;
}

static const struct of_device_id led_platform_match_table[] = {
    {.compatible = "ccoisini_led"}, {}};

static struct platform_driver led_platform_driver = {
    .probe = led_platform_probe,
    .remove = led_platform_remove,
    .driver = {
        .name = "ccoisini_led",
        .of_match_table = led_platform_match_table,
    }};

static int __init led_driver_init(void) {
  printk("1");
  return platform_driver_register(&led_platform_driver);
}

static void __exit led_driver_exit(void) {
  platform_driver_unregister(&led_platform_driver);
}

module_init(led_driver_init);
module_exit(led_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CCoisini");
MODULE_DESCRIPTION("GPIO subsystem for LED");
