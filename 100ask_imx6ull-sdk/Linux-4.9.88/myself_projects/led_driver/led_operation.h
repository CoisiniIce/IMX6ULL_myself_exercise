#ifndef __LED_OPERATION_H__
#define __LED_OPERATION_H__

struct led_operations {
    int (*led_init) (unsigned int whichLed);
    int (*led_ctl)(unsigned int whichLed,unsigned int level);
};

struct led_operations *get_led_operations(void);

#endif // !__LED_OPERATION_H__