#include <stdio.h>

int main() {
    int a[10];
    int n;
    int encontrado = -1;

    printf("ingrese 10 numeros separadaos por espacios: ");
    scanf("%d%d%d%d%d%d%d%d%d%d", &a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9]);
    printf("ingrese otro numero: ");
    scanf("%d", &n);

    for (int i = 0; i < 10; i++) {
        if (n == a[i]) {
            printf("el numero %d esta en la posicion %d de el arreglo\n", n, i);
            encontrado = 0;
        }
    }
    if (encontrado == -1) {
        printf("%d\n", encontrado);
    }
    return 0;
}