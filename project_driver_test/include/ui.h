#ifndef __UI_H__
#define __UI_H__

#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lvgl/lvgl.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

extern lv_indev_t *mouse_indev;
extern lv_ft_info_t ft_info;

bool ui_init(void);
bool ft_set_font_size(uint8_t f_size);
uint32_t custom_tick_get(void);

#endif // !__UI_H__
