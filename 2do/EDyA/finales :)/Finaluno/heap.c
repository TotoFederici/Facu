#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "tipos.h"

void swap(void** a, void** b){
   void* aux = *a;
    *a = *b;
    *b = aux;
}

int padre(int x){return x/2;}
int hijo_izq(int x){return 2*x;}
int hijo_der(int x){return (2*x) + 1;}

Heap crear_heap(int capacidad, FuncionComparadora comp, FuncionCopiadora copia){
	Heap heap = malloc(sizeof(_Heap));
	heap->elems = malloc(sizeof(void*)*(capacidad+1));
	heap->capacidad = capacidad;
	heap->ultimo = 0;
	heap->copia = copia;
	heap->comp = comp;
	return heap;
}

void flotar(Heap heap, int pos){
	for(; pos > 1 && heap->comp(heap->elems[pos], heap->elems[padre(pos)]) > 0; pos = padre(pos)){
		swap(&heap->elems[pos], &heap->elems[padre(pos)]);
	}
}

void hundir(Heap heap, int pos){

	int mayor = pos;
	int izq = hijo_izq(pos);
	int der = hijo_der(pos);
	
	if(izq <= heap->ultimo && heap->comp(heap->elems[izq], heap->elems[mayor]) > 0){
		mayor = izq;
	}
	if(der <= heap->ultimo && heap->comp(heap->elems[der], heap->elems[mayor]) > 0){
		mayor = der;
	}

	if(mayor != pos){
		swap(&heap->elems[pos], &heap->elems[mayor]);
		hundir(heap, mayor);
	}
}

void heap_insertar(Heap heap, void* dato){
	heap->ultimo++;
	heap->elems[heap->ultimo] = heap->copia(dato);
	flotar(heap, heap->ultimo);
}

void heap_pop(Heap heap, void* dato){
	int pos, encontrado = 0;
	for(pos = 1; pos <= heap->ultimo && encontrado == 0; pos++){
		if(heap->comp(heap->elems[pos], dato) == 0){
			encontrado = 1;
		}
	}
	pos--;
	heap->elems[pos] = heap->elems[heap->ultimo];
	heap->ultimo--;
	hundir(heap, pos);
}

void* heap_top(Heap heap){
	if(heap->ultimo >= 0){
		return heap->elems[1];
	} else {
		return NULL;
	}
}