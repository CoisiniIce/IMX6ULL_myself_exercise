#include "ui.h"

#define DISP_BUF_SIZE (1024 * 128)
#define FREETYPE_FONT_FILE ("/etc/JetBrainsMono-Regular.ttf")

lv_indev_t *mouse_indev;
lv_ft_info_t ft_info;

bool ui_init(void) {
  // lvgl初始化
  lv_init();
  // 显示器初始化
  fbdev_init();
  // 初始化 freetype
  lv_freetype_init(8, 64, 64);
  // 绘制屏幕内容时的buffer
  static lv_color_t buf[DISP_BUF_SIZE];
  // 初始化buffer描述符
  static lv_disp_draw_buf_t disp_buf;
  lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

  // 初始化并注册一个显示器驱动
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.draw_buf = &disp_buf;
  disp_drv.flush_cb = fbdev_flush;
  disp_drv.hor_res = 1024;
  disp_drv.ver_res = 600;
  lv_disp_drv_register(&disp_drv);

  /* Linux input device init */
  evdev_init();

  /* Initialize and register a display input driver */
  static lv_indev_drv_t indev_drv_1;
  lv_indev_drv_init(&indev_drv_1);
  indev_drv_1.type = LV_INDEV_TYPE_POINTER;

  /*This function will be called periodically (by the library) to get the mouse
   * position and state*/
  indev_drv_1.read_cb = evdev_read;
  mouse_indev = lv_indev_drv_register(&indev_drv_1);

  // Freetype
  ft_info.name = FREETYPE_FONT_FILE;
  ft_info.weight = 24;
  ft_info.style = FT_FONT_STYLE_NORMAL;
  ft_info.mem = NULL;
  if (!lv_ft_font_init(&ft_info)) {
    printf("create fialed.\r\n");
  }

  // 使用输入设备必须创建一个组
  lv_group_t *g = lv_group_create();
  // 添加到默认组
  lv_group_set_default(g);
  // 输入设备添加进组
  lv_indev_set_group(mouse_indev, g);

  return true;
}

bool ft_set_font_size(uint8_t f_size) {

  ft_info.weight = f_size;
  lv_ft_font_init(&ft_info);
  return true;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void) {
  static uint64_t start_ms = 0;
  if (start_ms == 0) {
    struct timeval tv_start;
    gettimeofday(&tv_start, NULL);
    start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
  }

  struct timeval tv_now;
  gettimeofday(&tv_now, NULL);
  uint64_t now_ms;
  now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

  uint32_t time_ms = now_ms - start_ms;
  return time_ms;
}