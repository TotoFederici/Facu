#include <stdio.h>

int main() {
    int cien[100];
    
    for (int i = 0;i < 100;i++) {
        cien[i] = i+1;
    }
    for (int i = 0;i < 100;i++) {
        printf("%d\n", cien[i]);
    }
    return 0;
}