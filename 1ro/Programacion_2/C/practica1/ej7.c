#include<stdio.h>

int main() {
    
    int year;
    printf("ingrese un year para ver si es bisiesto:\n ");
    scanf("%d", &year);
    
    if (((year % 4) == 0) && ((year % 100) != 0)) {
        printf("el year %d es biciesto\n", year); }
    else {
        printf("el year %d no es biciesto\n", year); }
    
    return 0;
}