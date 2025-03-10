#include <stdio.h>
#include <math.h>

int main() {
    int numerito, i = 2;

    do {
    printf("ingrese un numero entero mayor que 1 para ver si es primo: ");
    scanf("%d", &numerito);
    }
    while (numerito <= 1);

    while (i != sqrt(numerito) && ((numerito % i) != 0))
    {
          i++;
    }
    
    if (i == numerito) {
        printf("el numero es primo\n");
    }
    else {
        printf("el numero no es primo\n");
    }

    return 0;
}