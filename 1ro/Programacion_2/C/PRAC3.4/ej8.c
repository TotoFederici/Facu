#include <stdio.h>

int main() {
    int numerito,pasos;

    printf("ingrese un numero natural para aplicar la conjetura de collatz: ");
    scanf("%d", &numerito);
    printf("valor inicial es %d\n", numerito);
    
    for (pasos = 0;numerito != 1;pasos++) {
        if (numerito < 1) {
            printf("eso no es un numero natural\n");
        }
        else {
            if ((numerito % 2) == 0) {
               numerito /= 2;
               printf("el siguiente valor es %d\n", numerito);
            }
            else {
                numerito = (numerito * 3) + 1;
                printf("el siguiente valor es %d\n", numerito);
            }
        }
    }
    printf("llegaste al 1 en %d pasos\n", pasos);

    return 0;
}