#include "../include/header.h"
#include <stdio.h>

int main() {
    int x = 10, y = 5;
    
    printf("%d + %d = %d\n", x, y, add(x, y));
    printf("%d - %d = %d\n", x, y, subtract(x, y));
    printf("%d * %d = %d\n", x, y, multiply(x, y));
    printf("%d / %d = %.2f\n", x, y, divide(x, y));
    
    return 0;
}
