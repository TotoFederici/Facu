#include <stdio.h>

int main() {
    int multiplos[50];

    for (int i = 0; i < 50; i++) {
        multiplos[i] = i*3;
    }
    for (int i = 49; i >= 0; i--) {
        printf("%d\n", multiplos[i]);
    }
    return 0;
}