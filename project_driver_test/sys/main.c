#include "ui.h"

int main(int argc, char *argv[]) {
  ui_init();

  while (1) {
    lv_timer_handler();
    usleep(5000);
  }

  return 0;
}