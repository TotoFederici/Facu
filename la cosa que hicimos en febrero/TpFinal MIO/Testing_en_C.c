#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "comandos.c"
#include "limpiar_textos.c"

// Compara dos textos caracter a caracter para verificar si son iguales
int archivos_iguales(FILE* texto1, FILE* texto2) {
    char char_texto1 = fgetc(texto1);
    char char_texto2 = fgetc(texto2);
    
    // La primer condicion es para el caso en que los textos sean iguales,
    // ya que en tal caso, sin esta condicion el bucle while seria infinito
    while ((char_texto1 != EOF && char_texto2 != EOF) && (char_texto1 == char_texto2)) {
        char_texto1 = fgetc(texto1);
        char_texto2 = fgetc(texto2);
    }
    if (char_texto1 != char_texto2) {
        return 0;
    }
    return 1;
}

void test_limpiar_textos() {
    limpiar_textos("Testing_en_C");
    FILE* texto_esperado = fopen("./Test_C/Test_salida_esperada.txt", "r");
    FILE* texto_salida = fopen("./Entradas/Testing_en_C.txt", "r");

    if (archivos_iguales(texto_salida, texto_esperado) == 0) {
        printf("(!!) Los archivos no son iguales\n");
    }
    fclose(texto_esperado);
    fclose(texto_salida);
}

int main() {
    buscar_textos("Testing_en_C");
    test_limpiar_textos();
    return 0;
}