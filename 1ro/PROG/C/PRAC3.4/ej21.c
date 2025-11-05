#include <stdio.h>
#include <string.h>

int capicua(char texto[]) {
    int largo = (strlen(texto)-1);
    int inicio = 0, capicua = 0;

    for (largo,inicio;(largo >= inicio);largo--,inicio++) {
        while ((texto[largo] == ' '))
                largo--;
        while ((texto[inicio] == ' '))
                inicio++;
        if (texto[inicio] != texto[largo]) {
            capicua = 1;
        }
    }
    return capicua;
}

int main() {
    char palabra[] = "son robos no solo son sobornos";

    printf("%d\n", capicua(palabra));
    return 0;
}