#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buscar_archivos.c"
#include "corregir_caracter.c"

// Constantes
#define TAM_BUFFER 255
#define TAM_NOMBRE 100


// Lee los textos y crea el archivo asociado a la persona en la carpeta Entradas
void filtrar_texto(char* nombre_persona){
    buscar_archivos(nombre_persona);

    char dir_entradas[TAM_BUFFER];
    sprintf(dir_entradas, "./Entradas/%s.txt", nombre_persona);
    char dir_textos[TAM_BUFFER];

    FILE *texto_filtrado = fopen(dir_entradas, "w");
    FILE *nombres_archivos = fopen("./archivos.txt", "r");

    char archivo[TAM_NOMBRE];
    int f; // Bandera para la funcion corregir_caracter
    int contador_archivos = 0;
    char caracter_obtenido, caracter_corregido = 0;
    while(fscanf(nombres_archivos, "%s", archivo) != EOF){
        if(contador_archivos != 0 && f != 1){
            fputc('\n', texto_filtrado); // Coloca un salto de linea en caso de que el texto no tenga un punto final
        }
        contador_archivos++;

        sprintf(dir_textos, "./Textos/%s/%s", nombre_persona, archivo);
        FILE *texto = fopen(dir_textos, "r");

        f = 1;
        caracter_obtenido = 0;
        while(caracter_obtenido != EOF){
            caracter_obtenido = fgetc(texto);
            caracter_corregido = corregir_caracter(caracter_obtenido, &f);

            if(caracter_corregido != -1){
                fputc(caracter_corregido, texto_filtrado);
            }
        }
        fclose(texto);
    }
    fclose(texto_filtrado);
    fclose(nombres_archivos);

}