#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "comandos.c"
#include "limpiar_textos.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("(!!) Hay argumentos de mas, o faltan argumentos\n"
        "Se debe ejecutar el programa con el nombre de la persona cuyos textos se van a analizar\n");
        return -1;
    }
    buscar_textos(argv[1]);
    limpiar_textos(argv[1]);
    comando_python(argv[1]);
    return 0;
}