#include <stdio.h>
#define adivinar 1

int main() {
    int n;
    int intentos;

    for (intentos = 15; intentos > 0; intentos--) {
        printf("tiene %d intentos para adivinar el numero entre 0 y 500, inrese un numero: ", intentos);
        scanf("%d", &n);
        if (n == adivinar) {
            printf("adivinaste!!!\n");
            intentos = 0;
        }
        else if (n > adivinar) {
            printf("%d es mayor que el numero que debe adivinar\n", n);
        }
        else {
            printf("%d es menor que el numero que debe adivinar\n", n);
        }
    }   
    return 0;
}