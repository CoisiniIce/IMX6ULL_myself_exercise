#ifndef __DISP_MANAGER_H__
#define __DISP_MANAGER_H__

typedef struct Region {
  // 要刷新区域的左上角坐标
  int left_up_x;
  int left_up_y;
  // 要刷新区域的长宽
  int width;
  int height;
} Region, *PRegion;

// 显示设备管理结构，采用链表形式支持多设备，目的是为了支持多个设备，如LCD、web网页等，它们都使用该结构体，只是内部的函数实现不一样
typedef struct Disp_Manager_Struct {
  // name 用于区分不同的结构体
  char *name;
  // 获取显存 buffer
  // 参数1：x轴像素 参数2：y轴像素 参数3：(bits per pixel)每个像素使用多少位
  // 返回值：显存起始地址
  char *(*getBuffer)(int *xRes, int *yRes, int *pBpp);
  // 刷新显示器某个区域
  // 参数1：要刷新的位置
  // 返回值：0 成功，其他失败
  int (*flushRegion)(PRegion pRegion, char *buffer);
  // 指向下一个显示设备
  struct Disp_Manager_Struct *pNext;
} Disp_Manager_Struct;

#endif // !__DISP_MANAGER_H__
