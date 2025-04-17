#include "page_manager.h"

LV_FONT_DECLARE(font_image)
#define ICONFONT_IMAGE "\xEE\x99\x89"

static lv_obj_t *main_page = NULL;

static void Btn_Image_Callback(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e); // 获取事件类型
  lv_obj_t *btn = lv_event_get_target(e);      // 获取触发控件
  if (code == LV_EVENT_CLICKED) {
    Find_Page_By_Name("Camera_Page")->Run(NULL);
  }
}

static bool Main_Page_Init(void) {

  ft_set_font_size(16);
  // 设置背景图片
  lv_obj_t *img = lv_img_create(main_page);
  LV_IMG_DECLARE(bg_1024x600);
  lv_img_set_src(img, &bg_1024x600);
  lv_obj_center(img);
  // 按钮样式
  static lv_style_t style_btn;
  lv_style_init(&style_btn);
  lv_style_set_radius(&style_btn, 8);
  lv_style_set_width(&style_btn, 80);
  lv_style_set_height(&style_btn, 80);
  lv_style_set_pad_all(&style_btn, 3);
  lv_style_set_bg_color(&style_btn, lv_color_hex(0x009688));
  lv_style_set_text_color(&style_btn, lv_color_hex(0xffffff));
  // 相册按钮
  lv_obj_t *btn_image = lv_btn_create(main_page);
  lv_obj_add_style(btn_image, &style_btn, LV_STATE_DEFAULT);
  lv_obj_align(btn_image, LV_ALIGN_TOP_LEFT, 100, 120);
  // 设置默认样式应用字体
  static lv_style_t style_image;
  lv_style_init(&style_image);
  lv_style_set_text_font(&style_image, &font_image);
  lv_style_set_text_color(&style_image, lv_color_hex(0xffffff));
  // 按钮图标
  lv_obj_t *label_font_image = lv_label_create(btn_image);
  lv_label_set_text(label_font_image, ICONFONT_IMAGE);
  lv_obj_add_style(label_font_image, &style_image, LV_STATE_DEFAULT);
  lv_obj_center(label_font_image);
  // 按钮下方标签
  lv_obj_t *label_text = lv_label_create(main_page);
  lv_label_set_recolor(label_text, true);
  lv_label_set_text_fmt(label_text, "#FFFFFF 相片#");
  lv_obj_set_style_text_font(label_text, ft_info.font, LV_STATE_DEFAULT);
  lv_obj_align_to(label_text, btn_image, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

  lv_obj_add_event_cb(btn_image, Btn_Image_Callback, LV_EVENT_CLICKED, NULL);

  return true;
}

static bool Main_Page_Create(void) {
  main_page = lv_obj_create(NULL);
  if (main_page) {
    return true;
  }
  return false;
}

static bool Main_Page_Run(void *pParams) {

  // 清理对象的所有子对象
  lv_obj_clean(lv_scr_act());
  // 初始化新页面的内容
  Main_Page_Init();
  // 切换屏幕
  lv_scr_load(main_page);

  return true;
}

static Page_Opr Main_Page = {
    .name = "Main_Page",
    .Create = Main_Page_Create,
    .Run = Main_Page_Run,
};

bool Main_Page_Register(void) {

  if (!Register_Page(&Main_Page)) {
    return false;
  }

  return true;
}