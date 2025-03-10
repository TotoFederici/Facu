#include <stdio.h>
#include <stdlib.h>
#include "corregir_caracter.c"


int test_corregir_caracter(){
    int f;
    
    //test 1
    f = 0;
    if(corregir_caracter('a', &f) != 'a'){
        printf("Fallo el test 1");
        exit(0);
    }

    //test 2
    f = 0;
    if(corregir_caracter('A', &f) != 'a'){
        printf("Fallo el test 2");
        exit(0);
    }

    //test 3
    f = 0;
    if(corregir_caracter(' ', &f) != ' '){
        printf("Fallo el test 3");
        exit(0);
    }

    //test 4
    f = 1;
    if(corregir_caracter(' ', &f) != -1){
        printf("Fallo el test 4");
        exit(0);
    }

    //test 5
    f = 0;
    if(corregir_caracter('.', &f) != '\n'){
        printf("Fallo el test 5");
        exit(0);
    }

    //test 6
    f = 1;
    if(corregir_caracter('.', &f) != -1){
        printf("Fallo el test 6");
        exit(0);
    }

    //test 7
    f = 0;
    if(corregir_caracter('&', &f) != -1){
        printf("Fallo el test 7");
        exit(0);
    }

    return 0;
}


int main(){
    test_corregir_caracter();

    return 0;
}