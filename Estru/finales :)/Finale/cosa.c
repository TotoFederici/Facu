#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glist.h"

int* copiar(int* n){return n;}
void destruir(int* n){return;}

typedef struct _arr{
	int* arreglo;
	int suma;
	int len;
} Arr;

typedef struct _P{
	GList p1;
	GList p2;
} Particiones;

Arr* crear_arrenteros(char* entrada){
	Arr* S = malloc(sizeof(Arr));
	S->arreglo = malloc(sizeof(int)*strlen(entrada));
	int j = 0;

	for(int i = 0; entrada[i] != '\0'; i++){
		if(entrada[i] != '[' && entrada[i] != ']' && entrada[i] != ',' && entrada[i] != ' ') {
			char* cosa = malloc(sizeof(char)*10);
			for(int k = 0; entrada[i] != ',' && entrada[i] != ']'; i++, k++){
				cosa[k] = entrada[i];
			}
			int num = atoi(cosa);
			S->arreglo[j] = num;
			S->suma += num;
			j++;
		}
	}
	S->arreglo = realloc(S->arreglo, sizeof(int)*j);
	S->len = j;
	return S;
}

Particiones* particiones(Arr* S){
	if(S->suma % 2 != 0){
		printf("No se puede(impar)\n");
		return NULL;
	}
	Particiones* P = malloc(sizeof(Particiones));
	GList lista1 = glist_create();
	GList lista2 = glist_create();
	int sumaParcial = 0, i = 0;

	for(; i < S->len && sumaParcial != S->suma/2; i++){
		sumaParcial += S->arreglo[i];
		lista1 = glist_append_first(lista1, &(S->arreglo[i]), (CopyFunction)copiar);
	}

	if(sumaParcial == S->suma/2){
		for(; i < S->len; i++){
			lista2 = glist_append_first(lista2, &(S->arreglo[i]), (CopyFunction)copiar);
		}
		P->p1 = lista1;
		P->p2 = lista2;
		return P;
	} else {
		printf("Objetivo era: %d\nSalio: %d\n", S->suma/2, sumaParcial);
		glist_destroy(lista1, (DestroyFunction)destruir);
		free(P);
		printf("No se puede(no dan las cuentas, crack)\n");
		return NULL;
	}
}

int main(){
	char entrada[] = "[3, 5, -4, 8, -9, -4, 1, 9, 1, 2, 12]";
	Arr* S = crear_arrenteros(entrada);
	for(int i = 0; i < S->len; i++){
		printf("%d ", S->arreglo[i]);
	}
	printf("\n");

	Particiones* P = particiones(S);

	if(P != NULL){
		GList p1 = P->p1;
		GList p2 = P->p2;

		printf("particion 1: ");
		for(; p1 != NULL; p1 = p1->next){
			printf("%d ", *(int*)p1->data);
		}
		printf("\nparticion 2: ");
		for(; p2 != NULL; p2 = p2->next){
			printf("%d ", *(int*)p2->data);
		}
		printf("\n");
	}
	return 0;
}