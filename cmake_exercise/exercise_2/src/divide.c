#include <stdio.h>

float divide(int a, int b)
{
    if (b == 0) {
        printf("错误：除数不能为零\n");
        return 0;
    }
    return (float)a / b;
}