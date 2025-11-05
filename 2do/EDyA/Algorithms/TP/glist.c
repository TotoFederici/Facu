#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

GList glist_crear(){
	return NULL;
}

void glist_destruir(GList lista, FuncionDestructora destruir){
	GList temp;
	while (lista != NULL){
		temp = lista;
		lista = lista->sig;
		destruir(temp->dato);
		free(temp);
	}
}

int glist_esta_vacia(GList lista){
	return lista == NULL;
}

void glist_recorrer(GList lista, FuncionVisitante visita){
	for (; lista != NULL; lista = lista->sig){
		visita(lista->dato);
	}
}

GList glist_agragar_inicio(GList lista, void *dato, FuncionCopia copia){
	GList nuevoNodo = malloc(sizeof(GNode));
	nuevoNodo->dato = copia(dato);
	if (glist_esta_vacia(lista)){
		nuevoNodo->sig = NULL;
		return nuevoNodo;
	}
	nuevoNodo->sig = lista;
	return nuevoNodo;
}