#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void swap(int* x, int* y) {
    int z = *y;
    *y = *x;
    *x = z; 
}

int main(){
    int num1 = 0;
    int num2 = 5;
    int* x = &num1;
    int* y = &num2;
    printf("x: %d, y: %d\n", *x, *y);
    swap(x,y);
    printf("x: %d, y: %d\n", *x, *y);
    return 0;
}