/*
  使用方式：./led_driver led0/led1 0/1
  0：熄灭
  1：点亮
*/

#include "led_operation.h"
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "led_device"
#define CLASS_NAME "led_class"
#define NUM_DEVICES 2

struct dev_inf {
  // 设备号
  dev_t dev_number;
  // 设备名称
  char *dev_name;
  // 类名
  char *class_name;
  // 设备类
  struct class *dev_class;
  // 字符设备
  struct cdev dev_cdev;
};
static struct dev_inf *led_dev;
const struct led_operations *led_opr;

/*
 * @description: 这相当于一个信号处理函数，用来在底层总线匹配到时创建设备节点
 * @param: 要销毁的次设备号，需要和主设备号组合
 * @return: 无
 */
void led_device_create(int minor) {
  unsigned int major = MAJOR(led_dev->dev_number);
  device_create(led_dev->dev_class, NULL, MKDEV(major, minor), NULL,
                "Device_LED%d", minor);
}

/*
 * @description: 这相当于一个信号处理函数，用来在底层总线remove时销毁设备节点
 * @param: 要销毁的次设备号，需要和主设备号组合
 * @return: 无
 */
void led_device_destroy(int minor) {
  unsigned int major = MAJOR(led_dev->dev_number);
  device_destroy(led_dev->dev_class, MKDEV(major, minor));
}

/*
 * @description:
 * 这相当于一个信号处理函数，用来在底层总线匹配到时激活led_operations结构体
 * @param: 准备好的结构体，带有对LED操作的函数
 * @return: 无
 */
void active_led_operation(const struct led_operations *opr) { led_opr = opr; }

static int led_driver_open(struct inode *inode, struct file *file) {

  unsigned int minor = iminor(inode);

  // 检查led操作集是否存在，以及是否进行过初始化
  if (!led_opr || !led_opr->led_init) {
    return -ENODEV;
  }

  // 调用底层的LED初始化函数进行初始化，这样以后led_driver_open就不用修改了
  led_opr->led_init(minor);

  return 0;
}

static int led_driver_release(struct inode *inode, struct file *file) {
  return 0;
}

static ssize_t led_driver_read(struct file *file, char __user *buf, size_t len,
                               loff_t *offset) {
  return 0;
}

static ssize_t led_driver_write(struct file *file, const char __user *buf,
                                size_t len, loff_t *offset) {
  unsigned int status;
  unsigned int minor = iminor(file->f_inode);

  if (len != sizeof(status))
    return -EINVAL;

  if (copy_from_user(&status, buf, sizeof(status)))
    return -EFAULT;

  if (!led_opr || !led_opr->led_ctl) {
    return -ENODEV;
  }

  if (status > 1) { // 验证输入值
    return -EINVAL;
  }

  led_opr->led_ctl(minor, status);

  return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_driver_open,
    .release = led_driver_release,
    .read = led_driver_read,
    .write = led_driver_write,
};

static int __init led_driver_init(void) {
  int ret;

  // 分配设备结构内存
  led_dev = kzalloc(sizeof(*led_dev), GFP_KERNEL);
  if (!led_dev)
    return -ENOMEM;

  led_dev->dev_name = DEVICE_NAME;
  led_dev->class_name = CLASS_NAME;
  // 动态分配设备号
  ret = alloc_chrdev_region(&(led_dev->dev_number), 0, NUM_DEVICES,
                            led_dev->dev_name);
  if (ret < 0) {
    pr_err("Failed to allocate device numbers: %d\n", ret);
    goto free_dev;
  }
  // 创建字符设备
  cdev_init(&(led_dev->dev_cdev), &fops);
  led_dev->dev_cdev.owner = THIS_MODULE;
  ret = cdev_add(&(led_dev->dev_cdev), led_dev->dev_number, NUM_DEVICES);
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

  // 创建设备节点的步骤放到底层做

  printk(KERN_INFO "Device driver loaded\n");

  return 0;

del_cdev:
  cdev_del(&led_dev->dev_cdev);
unreg_chrdev:
  unregister_chrdev_region(led_dev->dev_number, NUM_DEVICES);
free_dev:
  kfree(led_dev);
  led_dev = NULL;
  return ret;
}

static void __exit led_driver_exit(void) {
  // 1. 销毁设备节点，留到底层做

  // 2. 销毁设备类
  class_destroy(led_dev->dev_class);

  // 3. 删除字符设备
  cdev_del(&(led_dev->dev_cdev));

  // 4. 释放设备号
  unregister_chrdev_region(led_dev->dev_number, 1);

  printk(KERN_INFO "My device driver unloaded\n");
}

EXPORT_SYMBOL(led_device_create);
EXPORT_SYMBOL(led_device_destroy);
EXPORT_SYMBOL(active_led_operation);

module_init(led_driver_init);
module_exit(led_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CCoisini");
MODULE_DESCRIPTION("LED Top driver");