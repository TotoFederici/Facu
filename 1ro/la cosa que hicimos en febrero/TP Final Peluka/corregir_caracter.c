#include <ctype.h>

// Devuelve el caracter a escribir en el archivo de Entradas.
// La funcion retorna -1 en caso de que el caracter recibido no deba ser escrito en el archivo
// Si el caracter que recibe la funcion es alguno de los siguientes: '.', '\n', ' ',
// la variable anterior cambiara su valor a 1, de modo que ignorara todos los caracteres siguientes hasta
// que la funcion reciba un caracter alfabetico donde en ese caso anterior volvera a tener como valor 0.
char corregir_caracter(char caracter, int* anterior){

    if(isalpha(caracter)){
        *anterior = 0;
        return tolower(caracter);
    }
    if(caracter == '.' && *anterior == 0){
        *anterior = 1;
        return '\n';
    }
    if((caracter == ' ' || caracter == '\n') && *anterior == 0){
        *anterior = 1;
        return ' ';
    }

    return -1;
}