#include <stdio.h>
#include <cstdlib>

int main() {
    int pares[51];

    for (int i = 0 , j = 100 ; i <= 50 ; i++, j+=2) {
        pares[i] = j;
    }
    for (int i = 50;i >= 0;i--) {
        printf("%d\n", pares[i]);
    }
    return 0;
}