#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define BUFFER 255


char corregir_char(char caracter) {

    if ((isalpha(caracter)) || (caracter == ' ')) {
        return tolower(caracter);
    }
    if (caracter == '.') {
        return '\n';
    }
    return -1;
}

// Funcion que filtra los caracteres que se colocan y los que no.
//
// Utilizo una variable caracter que es la que va a escribirse en el texto
// Y tambien para evaluar los casos en que, se encuentre un punto, espacio o salto de linea.
//
// Otra variable, caracter_siguiente que se usa para llevar un control del caracter que sigue a "caracter"
// Y asi saber que se debe hacer en cada caso.
char escribir_char(FILE* texto, FILE* textos_filtrados, char caracter, char caracter_siguiente) {
    
    caracter_siguiente = fgetc(texto);
    char caracter_corregido = corregir_char(caracter);

            // En este caso, se verifica si el caracter es un punto.
            if ((caracter == '.') && (caracter_siguiente != EOF)) {
                while (!isalpha(caracter_siguiente) && (caracter_siguiente != EOF)) {
                    caracter_siguiente = fgetc(texto);
                }
                if (caracter_siguiente != EOF)
                    fputc(caracter_corregido, textos_filtrados);
            }

            // En este caso, se verifica si el caracter es un espacio.
            else if (caracter == ' ') {
                while (!isalpha(caracter_siguiente) && (caracter_siguiente != '.')) {
                    caracter_siguiente = fgetc(texto);
                }
                fputc(caracter_corregido, textos_filtrados);
            }

            // En este caso, se verifica si el caracter es un salto de linea.
            else if (caracter == '\n') {
                while (!(isalpha(caracter_siguiente))){
                    caracter_siguiente = fgetc(texto);
                }
                fputc(' ',textos_filtrados);
            }

            else if ((caracter_corregido != -1) && (caracter_corregido != '\n')) {
                fputc(caracter_corregido, textos_filtrados);
            }

    return caracter_siguiente;
}

// Funcion que crea el archivo donde se van a escribir los textos corregidos
// itera sobre los textos y llama a la funcion escribir_char para corregir los textos.
void limpiar_textos(char *nombre) {
    
    char linea[BUFFER-100];
    char dir_entradas[BUFFER];
    char dir_archivos[BUFFER];
    int archivos_leidos = 0;

    sprintf(dir_entradas, "./Entradas/%s.txt", nombre);
    
    FILE *archivos = fopen("archivos.txt", "r");
    FILE *textos_filtrados = fopen(dir_entradas, "w");
    FILE *texto;
    
    // La condicion se cumple mientras no se llegue al final del archivo que guarda los nombres de los textos
    // y ademas guarda en "linea" el proximo texto que se va a leer.
    while (fscanf(archivos, "%s", linea) != EOF) {
        sprintf(dir_archivos, "./Textos/%s/%s", nombre, linea);
        texto = fopen(dir_archivos, "r");

        char caracter_siguiente = 'a';
        char caracter = fgetc(texto);

        // Esta condicion agrega el salto de linea que separa entre archivos.
        if (archivos_leidos > 0) {
            fputc('\n', textos_filtrados);
        }

        while (caracter_siguiente != EOF) {

            caracter_siguiente = escribir_char(texto, textos_filtrados, caracter, caracter_siguiente);
            caracter = caracter_siguiente;
        }
        
        fclose(texto);
        archivos_leidos++;
    }
    fclose(textos_filtrados);
}