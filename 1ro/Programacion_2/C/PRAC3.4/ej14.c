#include <stdio.h>

int main() {
    int ingreso, mayor = 0, posicion = 0;
    int a[100];

    for (int i = 0;i < 100;i++) {
        a[i] = 0;
    }

    for (;ingreso >= 0;) {
        printf("ingrese un numero entre 0 y 99: ");
        scanf("%d", &ingreso);
        if (a[ingreso] > 0) {
            a[ingreso] += 1;
        }
        else {
            a[ingreso] = 1;
        }
    }

    for (int i = 0;i < 100;i++) {
        if (a[i] > mayor) {
            mayor = a[i];
            posicion = i;
        }
    }
    printf("el numero mas ingresado fue el %d y fue ingresado %d veces\n",posicion, mayor);

    return 0;
}