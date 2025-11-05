#include "glist.h"
#include "pilas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef GList Pila;

Pila pila_crear(){
	return NULL;
}

void pila_destruir(Pila pila, FuncionDestructora destroy){
	glist_destroy(pila, destroy);
}

int pila_esta_vacia(Pila pila){
	if (glist_empty(pila)){
		return 1;
	}
	return 0;
}

Pila pila_push(Pila pila, void *dato, FuncionCopia copy){
	return glist_append_first(pila, dato, copy);
}

void* pila_pop(Pila *pila){
	if (!pila_esta_vacia(*pila)){
		Pila nodo = *pila;
		void* dato = nodo->dato;
		*pila = (*pila)->sig;
		free(nodo);
		return dato;
	}
}