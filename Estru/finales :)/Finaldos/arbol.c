#include <stdlib.h>
#include <stdio.h>

typedef enum color {Rojo, Azul, Neutro} Color;

typedef struct Nodo_ {
	char* cdato;
	Color colorNodo;
	struct Nodo_ *der, *izq;
} Nodo;

typedef Nodo* ArbolBinarioColoreado;

void colorR(ArbolBinarioColoreado nodo, int* azules, int* rojos){
	if(nodo != NULL){
		colorR(nodo->izq, azules, rojos);
		if(nodo->colorNodo == Azul){
			*azules++;
		} else {
			*rojos++;
		}
		colorR(nodo->der, azules, rojos);
	}
}

// Retorna el color del Arbol.
Color color(ArbolBinarioColoreado inicio){
	int *azules, *rojos;
	*azules = 0, *rojos = 0;
	colorR(inicio, azules, rojos);

	if(*azules > *rojos){return Azul;}
	if(*rojos > *azules){return Rojo;}
	return Neutro;
}

void cantidadPurasR(ArbolBinarioColoreado nodo, Color colorNodo, int* puras){
	if(nodo->der == NULL && nodo->izq == NULL){
		*puras++;
	}
	if(nodo->izq->colorNodo == colorNodo){
		cantidadPurasR(nodo->izq, colorNodo, puras);
	}
	if(nodo->der->colorNodo == colorNodo){
		cantidadPurasR(nodo->der, colorNodo, puras);
	}
}

// Retorna la cantidad de hojas puras.
int CantidadPuras(ArbolBinarioColoreado inicio){
	int* puras, *puras = 0;
	cantidadPurasR(inicio, inicio->colorNodo, puras);
	return *puras;
}