#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#define TAM 15

int* copiar_entero(int* n){return n;}
void destruir_entero(int* n){return;}
int comparar_enteros(int* a, int* b){
	if(*a < *b){return -1;}
	if(*a > *b){return 1;}
	return 0;
}

void imprimir_entero(int* n){printf("%d ", *n);}

int main(){

	int numeritos[TAM] = {273, 14, 19, 200, -551, 256, 0, 1729, 8, 110, 1, 998, 51, 53, 777};

	Avl raiz = avl_crear();
	for(int i = 0; i < TAM; i++){
		raiz = avl_insertar(raiz, &numeritos[i], (FuncionComparadora)comparar_enteros, (FuncionCopia)copiar_entero);
		/* avl_map(raiz, AVL_RECORRIDO_IN, (FuncionVisitante)imprimir_entero);
		printf("\n"); */
	}

	avl_map(raiz, AVL_RECORRIDO_IN, (FuncionVisitante)imprimir_entero);
	printf("\n");

	printf("Eliminar 8:\n");
	raiz = avl_eliminar(raiz, &numeritos[8], (FuncionDestructora)destruir_entero, (FuncionComparadora)comparar_enteros);
	avl_map(raiz, AVL_RECORRIDO_IN, (FuncionVisitante)imprimir_entero);
	printf("\nEliminar 273:\n");
	raiz = avl_eliminar(raiz, &numeritos[0], (FuncionDestructora)destruir_entero, (FuncionComparadora)comparar_enteros);
	avl_map(raiz, AVL_RECORRIDO_IN, (FuncionVisitante)imprimir_entero);
	printf("\nEliminar 51:\n");
	raiz = avl_eliminar(raiz, &numeritos[12], (FuncionDestructora)destruir_entero, (FuncionComparadora)comparar_enteros);
	avl_map(raiz, AVL_RECORRIDO_IN, (FuncionVisitante)imprimir_entero);
	printf("\n");

	return 0;
}