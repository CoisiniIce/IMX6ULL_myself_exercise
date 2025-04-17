#include "page_manager.h"

static lv_obj_t *camera_page = NULL;
static int fb_fd;
static char *fbp;

static void Btn_Return_Callback(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e); // 获取事件类型
  lv_obj_t *btn = lv_event_get_target(e);      // 获取触发控件
  if (code == LV_EVENT_CLICKED) {
    Find_Page_By_Name("Main_Page")->Run(NULL);
  }
}

/*
 * @description: 初始化LCD，目的是为了快速显示，不利用lvgl的中间层
 * @param: 无
 * @return: true/flase
 */
static bool LCD_Init(void) {

  fb_fd = open("/dev/fb0", O_RDWR);
  if (fb_fd < 0) {
    perror("打开LCD失败\r\n");
    exit(EXIT_FAILURE);
  }

  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo fix;

  ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);
  // 计算屏幕大小（字节）
  long screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
  // 映射framebuffer到内存，MAP_SHARED 表示该区域是共享的。该返回值得到的是
  // Frambuffer 的基地址。
  fbp = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);

  // 绘制操作

  return true;
}

static bool Camera_Page_Init(void) {

  // 设置背景图片
  lv_obj_t *img = lv_img_create(camera_page);
  LV_IMG_DECLARE(camera_bg);
  lv_img_set_src(img, &camera_bg);
  lv_obj_center(img);

  // 设置字体大小
  ft_set_font_size(20);
  // 返回按钮
  lv_obj_t *btn_return = lv_btn_create(camera_page);
  lv_obj_set_size(btn_return, 80, 50);
  lv_obj_align(btn_return, LV_ALIGN_TOP_LEFT, 20, 20);
  lv_obj_t *label_return = lv_label_create(btn_return);
  lv_obj_set_style_text_font(label_return, ft_info.font, LV_STATE_DEFAULT);
  lv_label_set_text(label_return, "返回");
  lv_obj_align(label_return, LV_ALIGN_CENTER, 0, 0);

  /* 创建外层容器作为背景框 */
  lv_obj_t *cam_container = lv_obj_create(camera_page);
  lv_obj_set_size(cam_container, 371, 308);
  lv_obj_align(cam_container, LV_ALIGN_CENTER, 0, 0);
  // 禁用容器滚动
  lv_obj_clear_flag(cam_container, LV_OBJ_FLAG_SCROLLABLE);
  /* 设置容器样式 - 背景框效果 */
  static lv_style_t container_style;
  lv_style_init(&container_style);
  lv_style_set_bg_opa(&container_style, LV_OPA_TRANSP);
  lv_style_set_border_width(&container_style, 3);
  lv_style_set_border_color(&container_style, lv_color_hex(0x3498db));
  lv_style_set_radius(&container_style, 10);
  lv_style_set_pad_all(&container_style, 0); // 确保无内边距
  lv_obj_add_style(cam_container, &container_style, LV_STATE_DEFAULT);
  /* 创建实际显示摄像头图像的img组件 */
  lv_obj_t *cam_img = lv_img_create(cam_container);
  lv_obj_set_size(cam_img, 365, 302);
  lv_obj_align(cam_img, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_bg_opa(cam_img, LV_OPA_TRANSP, LV_STATE_DEFAULT);

  // 返回按钮回调
  lv_obj_add_event_cb(btn_return, Btn_Return_Callback, LV_EVENT_CLICKED, NULL);

  return true;
}

static bool Camera_Page_Create(void) {
  camera_page = lv_obj_create(NULL);
  if (camera_page) {
    return true;
  }
  return false;
}

static bool Camera_Page_Run(void *pParams) {

  // 清理对象的所有子对象
  lv_obj_clean(lv_scr_act());
  // 初始化新页面的内容
  Camera_Page_Init();
  // 切换屏幕
  lv_scr_load(camera_page);

  return true;
}

static Page_Opr Camera_Page = {
    .name = "Camera_Page",
    .Create = Camera_Page_Create,
    .Run = Camera_Page_Run,
};

bool Camera_Page_Register(void) {

  if (!Register_Page(&Camera_Page)) {
    return false;
  }

  return true;
}
