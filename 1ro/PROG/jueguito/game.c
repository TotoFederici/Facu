#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char* name;
    int* hp;
} player;

typedef struct {
    char* name;
    int* stat;
    int* type; // 0: espada, 1: escudo
    int* uses;
} item;

typedef struct {
    item** inventario;
    int* espacios;
} inventario;

typedef struct {
    int* hp;
    char* name;
    int* damage;
} enemy;

player* crea_pj() {
    player* pj = malloc(sizeof(player));
    pj->hp = malloc(sizeof(int));
    pj->name = malloc(sizeof(char)*20);
    *pj->hp = 100;
    return pj;
}

item* Crea_Espada() {
    item* espada = malloc(sizeof(item));
    espada->name = malloc(sizeof(char)*15);
    
    espada->stat = malloc(sizeof(int));

    int random_stat = (rand() % 15 + 5);
    *(espada->stat) = random_stat;
    
    espada->uses = malloc(sizeof(int));

    if (*(espada->stat) < 10) {
        strcpy(espada->name, "wooden sword");
        *espada->uses = 2;
    }
    else if (*(espada->stat) < 15) {
        strcpy(espada->name, "sharp sword");
        *espada->uses = 4;
    }
    else{
        strcpy(espada->name, "forged sword");
        *espada->uses = 6;
    }

    espada->type = malloc(sizeof(int));
    *espada->type = 0;

    return espada;
}

item* Crea_Escudo() {
    item* escudo = malloc(sizeof(item));
    escudo->name = malloc(sizeof(char) * 15);

    escudo->stat = malloc(sizeof(int));

    int random_stat = (rand() % 15 + 5);
    *(escudo->stat) = random_stat;

    escudo->uses = malloc(sizeof(int));

    if (*(escudo->stat) < 10) {
        strcpy(escudo->name, "wooden shield");
        *escudo->uses = 2;
    } 
    else if (*(escudo->stat) < 15) {
        strcpy(escudo->name, "steel shield");
        *escudo->uses = 4;
    } 
    else {
        strcpy(escudo->name, "hard shield");
        *escudo->uses = 6;
    }

    escudo->type = malloc(sizeof(int));
    *escudo->type = 1;

    return escudo;
}

inventario* crea_inventario() {
    inventario* inv = malloc(sizeof(inventario));
    inv->espacios = malloc(sizeof(int));
    *(inv->espacios) = 0;
    inv->inventario = malloc(sizeof(item*)*5);
    return inv;
}

enemy* crea_enemigo() {
    enemy* enemigo = malloc(sizeof(enemy));
    enemigo->name = malloc(sizeof(char)*40);
    enemigo->hp = malloc(sizeof(int));
    enemigo->damage = malloc(sizeof(int));

    return enemigo;
}

void showHp(player* pj) {
    printf("HP: %d\n", *pj->hp);
}

void agrega_inventario(inventario* inv, item* object) {
    if (*(inv->espacios) == 5) {
        printf("your inventory is full\n");
    }
    else {
        inv->inventario[*(inv->espacios)] = object;
        (*inv->espacios)++;
    }
    printf("items you have: \n");
    for (int i = 0; i < *(inv->espacios); i++) {
        if (*(inv->inventario[i])->type == 0) {
            printf("%s: %d damage, %d uses\n", inv->inventario[i]->name, *(inv->inventario[i]->stat), *(inv->inventario[i]->uses));
        }
        else if (*(inv->inventario[i])->type == 1) {
            printf("%s: %d defense, %d uses\n", inv->inventario[i]->name, *(inv->inventario[i]->stat), *(inv->inventario[i]->uses));
        }
    }
}

int main() {
    srand(time(NULL));
    player* pj = crea_pj();
    printf("enter your playername: ");
    scanf("%s", pj->name);

    printf("-------------------\nplayername: %s\n", pj->name);
    showHp(pj);

    inventario* inv1 = crea_inventario();

    item* arma_1 = Crea_Espada();
    printf("-------------------\nyou found: %s\ndamage: %d\n-------------------\n", arma_1->name, *(arma_1->stat));

    agrega_inventario(inv1, arma_1);
    
    item* esc_1 = Crea_Escudo();
    printf("-------------------\nyou found: %s\ndefense: %d\n-------------------\n", esc_1->name, *(esc_1->stat));
    
    agrega_inventario(inv1, esc_1);

    enemy* ene_1 = crea_enemigo();

    
    free(pj->name),free(pj->hp),free(pj);
    free(arma_1->name),free(arma_1->stat),free(arma_1->uses),free(arma_1->type),free(arma_1);
    free(esc_1->name),free(esc_1->stat),free(esc_1->uses),free(esc_1->type),free(esc_1);
    free(inv1->espacios),free(inv1->inventario),free(inv1);

    return 0;
}