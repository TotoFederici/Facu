#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_new_line(void) {
    char* salida = malloc(sizeof(char)*255);
    scanf("texto: %[^\n]", &salida);
    return salida;
}

