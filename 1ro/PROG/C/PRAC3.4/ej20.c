#include <string.h>
#include <stdio.h>

int main() {
    char texto[50];
    int largo;

    printf("ingrese un texto: ");
    scanf("%[^\n]", texto);
    largo = strlen(texto);

    for (int i = (largo-1);i >= 0;i--) {
        printf("%c", texto[i]);
    }
    printf("\n");
    return 0;
}