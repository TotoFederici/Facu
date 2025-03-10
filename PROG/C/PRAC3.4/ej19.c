#include <stdio.h>
#include <string.h>

int charTimes(char text[], char letr) {
    int largo = (strlen(text)-1);
    int apariciones = 0;

    for (largo;largo >= 0;largo--) {
        if (letr == text[largo]) {
            apariciones += 1;
        }
    }
    return apariciones;
}

int main() {
    char texto[50];
    char letra = 'g';

    printf("ingrese una cadena de texto: ");
    scanf("%[^\n]", texto);

    printf("la letra %c aparece %d veces en la cadena\n", letra, charTimes(texto,letra));
    return 0;
}