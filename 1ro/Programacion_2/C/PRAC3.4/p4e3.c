#include <stdio.h>

#define SIZE 100

char buenas[20] = "hola que tal";
char *hola = buenas;


int main() {
    int *a = malloc(sizeof(int));
    free(a);
    printf("%d\n", SIZE);
}