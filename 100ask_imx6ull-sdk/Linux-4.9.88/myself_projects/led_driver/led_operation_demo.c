#include <linux/gfp.h>
#include "led_operation.h"

static int led_init_operation (unsigned int whichLed)
{
    printk("初始化了LED：%d",whichLed);
    return 0;
}

static int led_ctl_operation (unsigned int whichLed,unsigned int level)
{
    printk("LED: %d, %s\r\n",whichLed,level ? "亮" : "灭");
    return 0;
}

static struct led_operations ledops = {
    .led_init = led_init_operation,
    .led_ctl = led_ctl_operation
};

struct led_operations *get_led_operations(void)
{
    return &ledops;
}
