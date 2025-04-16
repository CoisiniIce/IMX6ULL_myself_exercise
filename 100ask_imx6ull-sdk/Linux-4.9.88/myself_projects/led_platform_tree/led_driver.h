
#ifndef _LEDDRV_H
#define _LEDDRV_H

#include "led_operation.h"

void led_device_create(int minor);
void led_device_destroy(int minor);
void active_led_operation(const struct led_operations* opr);

#endif /* _LEDDRV_H */
