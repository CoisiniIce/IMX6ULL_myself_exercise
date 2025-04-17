#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"

extern lv_indev_t *mouse_indev;

bool ui_init(void);
uint32_t custom_tick_get(void);
uint32_t custom_tick_get(void);


#endif // !__UI_H__
