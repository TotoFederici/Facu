#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define BUFFER 255

// Esta funcion ejecuta un comando para obtener los nombres de los archivos que se encuentren en un directorio.
void buscar_textos(char *nombre) {
    char comando[BUFFER], linea[BUFFER];
    FILE *archivos = fopen("archivos.txt", "w+");
    sprintf(comando, "cd Textos/%s && ls > ../../archivos.txt", nombre);
    system(comando);

    if (fscanf(archivos, "%s", linea) == EOF) {
        printf("Advertencia: No hay textos con ese nombre, ingresar un nombre valido\n");
        fclose(archivos);
        exit(0);
    }
    fclose(archivos);
}

// Esta funcion ejecuta en comando de python
void comando_python(char *nombre) {
    char comando[BUFFER];
    sprintf(comando, "python3 main.py %s", nombre);
    system(comando);
}