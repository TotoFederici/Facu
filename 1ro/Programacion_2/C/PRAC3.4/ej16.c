#include <stdio.h>

int prodArr(int ent[], int largo) {
    int prod = 1;

    for (int i = 0;i < largo;i+=2) {
        prod *= ent[i];
    }
    return prod;
}

int main() {
    int a[5] = {6,3,8,2,4};
    int b[16] = {8,4,1,5,7,8,6,1,4,3,2,4,1,6,1,7};

    int f = prodArr(a,5);
    int g = prodArr(b,16);

    printf("elproducto del array a es %d\n", f);
    printf("elproducto del array b es %d\n", g);

    return 0;
}