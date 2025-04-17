#ifndef __UI_H__
#define __UI_H__

#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lvgl/lvgl.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

extern lv_indev_t *mouse_indev;

bool ui_init(void);
uint32_t custom_tick_get(void);

#endif // !__UI_H__
