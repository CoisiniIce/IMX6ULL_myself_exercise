#include "led_operation.h"
#include <asm/io.h>
#include <linux/gfp.h>

/* GPIO5_IO03 */
/* a. 使能 GPIO5
 * set CCM to enable GPIO5
 * CCM_CCGR1[CG15] 0x20C406C
 * bit[31:30] = 0b11
 */

/* b. 设置 GPIO5_IO03 用于 GPIO
 * set IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3
 * to configure GPIO5_IO03 as GPIO
 * IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 0x2290014
 * bit[3:0] = 0b0101 alt5
 */

/* c. 设置 GPIO5_IO03 作为 output 引脚
 * set GPIO5_GDIR to configure GPIO5_IO03 as output
 * GPIO5_GDIR 0x020AC000 + 0x4
 * bit[3] = 0b1
 */
/* d. 设置 GPIO5_DR 输出低电平
 * set GPIO5_DR to configure GPIO5_IO03 output 0
 * GPIO5_DR 0x020AC000 + 0
 * bit[3] = 0b0
 */
/* e. 设置 GPIO5_IO3 输出高电平
 * set GPIO5_DR to configure GPIO5_IO03 output 1
 * GPIO5_DR 0x020AC000 + 0
 * bit[3] = 0b1
 */

#define MAP_SIZE 4

static volatile unsigned int *CCM_CCGR1;
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
static volatile unsigned int *GPIO5_GDIR;
static volatile unsigned int *GPIO5_DR;

static int led_init_operation(unsigned int whichLed) {
  // 用于判断之前是否进行过初始化
  static bool is_executed = false;
  if (!is_executed) {
    // 首次执行
    if (whichLed == 0) {
      printk("初始化了LED：%d", whichLed);
      // 获取虚拟地址
      CCM_CCGR1 = ioremap(0x20C406C, MAP_SIZE);
      IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x2290014, MAP_SIZE);
      GPIO5_GDIR = ioremap(0x020AC000 + 0x4, MAP_SIZE);
      GPIO5_DR = ioremap(0x020AC000 + 0x0, MAP_SIZE);
      // 操作GPIO
      *CCM_CCGR1 |= (3 << 30);
      *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 &= ~(0xf);
      *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 |= (5);
      *GPIO5_GDIR |= (1 << 3);
    } else {
      printk("使用了别的LED\r\n");
    }
    is_executed = true;
  } else {
    // 非首次执行
    return 0;
  }

  return 0;
}

static int led_ctl_operation(unsigned int whichLed, unsigned int level) {
  printk("LED: %d, %s\r\n", whichLed, level ? "亮" : "灭");
  if (whichLed == 0) {

    if (level == 0)
      *GPIO5_DR &= ~(1 << 3);
    else
      *GPIO5_DR |= (1 << 3);

  } else {
    printk("暂时无法控制\r\n");
  }

  return 0;
}

static struct led_operations ledops = {.led_init = led_init_operation,
                                       .led_ctl = led_ctl_operation};

struct led_operations *get_led_operations(void) {
  return &ledops;
}
