#include "page_manager.h"

// 链表头
static PPage_Opr head = NULL;

bool Register_Page(PPage_Opr newPage) {

  newPage->Create();

  newPage->next = head;
  head = newPage;

  return true;
}

PPage_Opr Find_Page_By_Name(char *name) {
  PPage_Opr current = head;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0)
      return current;
    current = current->next;
  }
  return NULL;
}

void Page_System_Init(void) {
  // 初始化LVGL图形库
  ui_init();
  // 加载页面
  Main_Page_Register();
  Camera_Page_Register();
}