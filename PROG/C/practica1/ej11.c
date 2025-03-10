#include <stdio.h>

int main() {
    int primero ;
    int segundo ;
    printf("ingrese un numero: ");  
    scanf("%d", &primero);
    
    do
    {
        printf("ingrese un numero mayor al anterior: ");  
        scanf("%d", &segundo);
    } while (primero >= segundo);
    
    for (int i = primero; i <= segundo; i++) {
        printf("%d ", i);
    }
    return 0;
}