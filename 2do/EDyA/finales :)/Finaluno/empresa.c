#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "heap.h"
#include "hash.h"
#include "usuario.h"
#include "utils.h"
#define CANT 10

void agregar_usuario(TablaHash hash, Usuario usuario, FuncionCopiadora copia){
	tablahash_insertar(hash, usuario);
}

void* buscar_usuario(TablaHash hash, Usuario usuario){
	return tablahash_buscar(hash, usuario);
}

void agregar_en_espera(Heap heap, Usuario usuario){
	heap_insertar(heap, usuario);
}

void eliminar_de_espera(Heap heap, Usuario usuario){
	heap_pop(heap, usuario);
}

void* mostrar_siguiente(Heap heap){
	heap_top(heap);
}

int main(){
	Usuario personas[CANT];

	personas[0] = crear_usuario("Tomy", 1, 3);
	personas[1] = crear_usuario("Pelu", 0, 0);
	personas[2] = crear_usuario("Lolen", 0, 0);
	personas[3] = crear_usuario("Papa", 1, 1);
	personas[4] = crear_usuario("Mati", 0, 0);
	personas[5] = crear_usuario("Toto", 1, 15);
	personas[6] = crear_usuario("Valegen", 1, 2);
	personas[7] = crear_usuario("Tincho", 0, 0);
	personas[8] = crear_usuario("Ivo", 1, 8);
	personas[9] = crear_usuario("Sato", 1, 13);

	Heap espera = crear_heap(CANT*2, (FuncionComparadora)comparar_suscripcion, (FuncionCopiadora)copiar_usuario);
	TablaHash ingresados = tablahash_crear(CANT*2, (FuncionCopiadora)copiar_usuario, (FuncionComparadora)comparar_suscripcion,
																								 (FuncionDestructora)destruir_usuario, (FuncionHash)hashear_usuario);

	for(int i = 0; i < CANT; i++){
		agregar_en_espera(espera, personas[i]);
	}

	printf("Espera:\n");
	for(int i = 1; i <= espera->ultimo; i++){
		imprimir_usuario((Usuario)espera->elems[i]);
		printf(" Tiempo De Sub: %d\n", ((Usuario)espera->elems[i])->tiempoDeSuscripcion);
	}

	printf("\n");

	Usuario next;

	for(int i = 0; i < CANT; i++){
		next = mostrar_siguiente(espera);
		eliminar_de_espera(espera, next);
		agregar_usuario(ingresados, next, (FuncionCopiadora)copiar_usuario);
		imprimir_usuario(next);
		printf(" Tiempo De Sub: %d\n", next->tiempoDeSuscripcion);

		printf("Espera:\n");
		for(int i = 1; i <= espera->ultimo; i++){
			imprimir_usuario((Usuario)espera->elems[i]);
			printf(" Tiempo De Sub: %d\n", ((Usuario)espera->elems[i])->tiempoDeSuscripcion);
		}

		printf("\n");
	}
	return 0;
}