#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char palo;
    int valor;
} carta;

carta* mazo[60];

void llenar(carta** mazo) {
    char palos[] = {'E', 'C', 'O', 'B'};
    for(int i = 0; i < 48; i++) {
        carta* card = malloc(sizeof(carta));
        card->palo = palos[i % 4];
        card->valor = (i / 4) + 1;
        *mazo[i] = *card;
        printf("%i %c\n", (*mazo)[i].valor, (*mazo)[i].palo);
    }
}

int main() {
    llenar(mazo);
    return 0;
}