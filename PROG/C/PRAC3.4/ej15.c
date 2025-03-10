#include <stdio.h>

int sumaArr(int ent[], int largo) {
    int suma = 0;

    for (int i = largo-1;i >= 0;i--) {
        suma += ent[i];
    }
    return suma;
}

int main() {
    int a[5] = {6,3,8,2,4};
    int b[16] = {8,4,1,5,7,8,6,1,4,3,2,4,1,6,0,7};

    int f = sumaArr(a,5);
    int g = sumaArr(b,16);

    printf("la suma del array a es %d\n", f);
    printf("la suma del array b es %d\n", g);

    return 0;
}