#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    int palo; // 1: oro, 2: copa, 3: espada, 4: basto
    int valor;
} cartas;

cartas* mazo(){
    cartas* a = malloc(sizeof(cartas)*48);
    return a;
}

void llenar_mazo(cartas* mazo) {
     for(int i = 1;i < 5;i++) {
        for(int j = 1;j < 13;j++){
            cartas card;
            card.palo = i;
            card.valor = j;
            *mazo = card;
            mazo++;
        }
     }
     *(mazo - 48);
}

void mezclar_mazo(cartas* mazo){
    int j= rand() % 47 + 1;
    if (mazo[j].palo == 1){
        printf("tu carta es el %d de oro\n", mazo[j].valor);
    }
    else if (mazo[j].palo == 2) {
        printf("tu carta es el %d de copa\n", mazo[j].valor);
    }
    else if (mazo[j].palo == 3) {
        printf("tu carta es el %d de espada\n", mazo[j].valor);
    }
    else {
        printf("tu carta es el %d de basto\n", mazo[j].valor);
    }
}

int main() {
    srand(time(NULL));
    cartas* baraja = mazo();
    llenar_mazo(baraja);
    for (int i = 0;i < 48;i++) {
        printf("%d - %d\n", baraja[i].palo, baraja[i].valor);
    }
    mezclar_mazo(baraja);
    free(baraja);
    return 0;
}