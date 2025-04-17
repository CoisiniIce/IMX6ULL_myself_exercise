#ifndef __PAGE_MANAGER_H__
#define __PAGE_MANAGER_H__

#include "ui.h"

typedef struct Page_Opr {
    char* name;                   // 页面名称
    bool (*Create)(void);         // 页面创建函数
    bool (*Run)(void *pParams);   // 页面运行函数
    struct Page_Opr *next;        // 指向下一个页面的指针（单向链表）
} Page_Opr, *PPage_Opr;

/*
 * @description: 添加页面到链表
 * @param: 新页面
 * @return: true/false
 */
bool Register_Page(PPage_Opr newPage);

/*
 * @description: 通过名字查找对应页面
 * @param: 页面名
 * @return: true/false
 */
PPage_Opr Find_Page_By_Name(char *name);

/*
 * @description: 初始化界面管理器
 * @param: 无
 * @return: true/false
 */
void Page_System_Init(void);

/*
 * @description: 注册主页面，加入到管理器链表
 * @param: 无
 * @return: true/false
*/
bool Main_Page_Register(void);

#endif // !__PAGE_MANAGER_H__