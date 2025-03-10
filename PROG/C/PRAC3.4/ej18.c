#include <stdio.h>
#include <string.h>

int charIn(char text[], char letr) {
    int largo = (strlen(text)-1);
    int banderita = 1;

    for (largo;largo >= 0;largo--) {
        if (letr == text[largo]) {
            banderita = 0;
        }
    }
    return banderita;
}

int main() {
    char texto[50];
    char letra = 'g';

    printf("ingrese una cadena de texto: ");
    scanf("%[^\n]", texto);

    if (charIn(texto,letra) == 0) {
        printf("la letra %c estaba en la cadena\n", letra);
    }
    else {
        printf("la letra %c no estaba en la cadena\n", letra);
    }
    return 0;
}