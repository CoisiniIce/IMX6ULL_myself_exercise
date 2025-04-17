#include "page_manager.h"

int main(int argc, char *argv[]) {
  Page_System_Init();
  Find_Page_By_Name("Main_Page")->Run(NULL);
  while (1) {
    lv_timer_handler();
    usleep(5000);
  }

  return 0;
}