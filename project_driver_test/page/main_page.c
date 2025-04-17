#include "page_manager.h"

static lv_obj_t *main_page = NULL;

static bool Main_Page_Init() {

  // 设置背景图片
  lv_obj_t *img = lv_img_create(main_page);
  LV_IMG_DECLARE(bg_1024x600);
  lv_img_set_src(img, &bg_1024x600);
  lv_obj_center(img);

  // 按钮
  lv_obj_t *btn = lv_btn_create(img);
  lv_obj_set_size(btn, 100, 50);
  lv_obj_center(btn);
  // 按钮标签
  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, "Click Me!");
  lv_obj_center(label);

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