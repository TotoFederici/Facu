#include <stdio.h>

int main(){
    int numerito;
    double factorial = 1;

    do {
    printf("ingrese un numero para calcular su factorial: ");
    scanf("%d", &numerito);
    }
    while (numerito < 0);

    if (numerito == 0) {
        printf("su factorial es %lf\n", factorial);
    }
    else {
        while (numerito > 0) 
        {
            factorial *= numerito;
            numerito--;
        }
    printf("su factorial es %lf\n", factorial);
    }

    return 0;
}