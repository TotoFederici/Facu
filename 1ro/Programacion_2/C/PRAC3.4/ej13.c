#include <stdio.h>

int main() {
    int n, suma = 0, ingreso;
    int a[100];
    
    do {
    printf("ingrese un numero entero entre 5 y 100: ");
    scanf("%d", &n);}
    while ((n < 5) || (n > 100));

    for (int i = 0 ; i < n; i++) {
        printf("ingrese un numero entero: ");
        scanf("%d", &ingreso);
        suma += ingreso;
        a[i] = ingreso;
    }
    if (suma >= 30) {
        printf("suman mas de 30\n");
    }
    return 0;    
}