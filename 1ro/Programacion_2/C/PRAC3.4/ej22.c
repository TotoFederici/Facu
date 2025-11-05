#include <stdio.h>
#include <string.h>
#include <ctype.h>

//felipe zeballos comia kiwi excitado por el viaje a yapeyu, que podria salir mal, hora de guardar sus pertenencias

int fijate(char letra, char texto[]) {
    int esta = 0, largo = strlen(texto);
    
    for (int i = 0;i < largo;i++) {
        if (letra == texto[i]) {
            esta = 1;
        }
    }
    return esta;
}

int pan() {
    int abc[26];
    char texto[500];
    int pan = 1;

    for (int i = 0;i < 26;i++) {
        abc[i] = 0;
    }

    printf("ingresa un texto: ");
    scanf("%[^\n]", texto);

    int largo = strlen(texto);

    for (int i = 0; i < largo;i++) {
        int ascii = texto[i] - 97;
        abc[ascii]++;
    }
    
    for (int i = 0;i < 26;i++) {
        if (abc[i] == 0) {
            pan = 0;
        }
    }
    return pan;
}

int main() {
    if (pan() == 1) {
        printf("es pangrama pibe🗿\n");
    }
    else {
        printf("no es pangrama pibe💩\n");
    }
    return 0;
}