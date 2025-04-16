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
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "led_device"
#define CLASS_NAME "led_class"
#define DEVICE_COUNT 2 // 支持2个LED设备
struct led_operations *ledops;

static int minors[DEVICE_COUNT] = {0,1}; // 次设备号数组
static int major;
static struct class *ledClass = NULL;
static struct cdev ledCdev;

static int led_driver_open(struct inode *inode, struct file *file) {
  // 初始化灯，APP 需要传入次设备号
  unsigned int minor = iminor(inode);
  if (minor >= DEVICE_COUNT) {
    // 使用方式错误
    pr_err("从设备号错误\n");
    return -ENODEV;
  }

  ledops->led_init(minor);

  return 0;
}

static int led_driver_release(struct inode *inode, struct file *file) {
  // 关闭设备实现
  return 0;
}

static ssize_t led_driver_read(struct file *file, char __user *buf, size_t len,
                               loff_t *offset) {
  int state;
  unsigned int minor = iminor(file->f_inode);
  if (minor >= DEVICE_COUNT) {
    // 使用方式错误
    pr_err("从设备号错误\n");
    return -ENODEV;
  }

  return sizeof(state);
}

static ssize_t led_driver_write(struct file *file, const char __user *buf,
                                size_t len, loff_t *offset) {
  unsigned int state;
  unsigned int minor = iminor(file->f_inode);
  if (minor >= DEVICE_COUNT)
    return -ENODEV;

  // 传入的数据的大小是否正确
  if (len != sizeof(state))
    return -EINVAL;

  // 传入的数据保存在state
  if (copy_from_user(&state, buf, sizeof(state)))
    return -EFAULT;

  // 判断传入的是否是0/1
  if (state != 0 && state != 1)
    return -EINVAL;

  // 设置LED的开/关
  ledops->led_ctl(minor,state);

  return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_driver_open,
    .release = led_driver_release,
    .read = led_driver_read,
    .write = led_driver_write,
};

static int __init led_driver_init(void) {
  dev_t dev = 0;
  unsigned int i = 0;

  // 1. 分配设备号
  if (alloc_chrdev_region(&dev, minors[0], DEVICE_COUNT, DEVICE_NAME) < 0) {
    return -1;
  }
  major = MAJOR(dev);

  // 2. 初始化并添加字符设备
  cdev_init(&ledCdev, &fops);
  if (cdev_add(&ledCdev, dev, DEVICE_COUNT) < 0) {
    unregister_chrdev_region(dev, DEVICE_COUNT);
    pr_err("Failed to add cdev\n");
    return -1;
  }

  // 3. 创建设备类
  ledClass = class_create(THIS_MODULE, CLASS_NAME);
  if (IS_ERR(ledClass)) {
    pr_err("Failed to create class\n");
    cdev_del(&ledCdev);
    unregister_chrdev_region(dev, DEVICE_COUNT);
    return -ENODEV;
  }

  // 4. 创建设备节点
  for (i = 0; i < DEVICE_COUNT; i++) {
    device_create(ledClass, NULL, MKDEV(major, minors[i]), NULL, "%s%d",
                  DEVICE_NAME, i);
  }

  printk(KERN_INFO "LED driver loaded\n");

  // 获取led操作集
  ledops = get_led_operations();

  return 0;
}

static void __exit led_driver_exit(void) {
  unsigned int i = 0;

  // 1. 销毁设备节点
  for (i = 0; i < DEVICE_COUNT; i++) {
    device_destroy(ledClass, MKDEV(major, minors[i]));
  }

  // 2. 销毁设备类
  class_destroy(ledClass);

  // 3. 删除字符设备
  cdev_del(&ledCdev);

  // 4. 释放设备号
  unregister_chrdev_region(MKDEV(major, 0), DEVICE_COUNT);

  printk(KERN_INFO "LED driver unloaded\n");
}

module_init(led_driver_init);
module_exit(led_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CCoisini");
MODULE_DESCRIPTION("LED driver");