#ifndef __HEAP_H__
#define __HEAP_H__

#include "tipos.h"

typedef struct _heap {
	void** elems;
	int ultimo;
	int capacidad;
	FuncionComparadora comp;
	FuncionCopiadora copia;
	FuncionVisitante visita;
} _Heap;

typedef _Heap* Heap;

void swap(void** a, void** b);

int hijo_izq(int x);
int hijo_der(int x);
int padre(int x);

Heap crear_heap(int capacidad, FuncionComparadora comp, FuncionCopiadora copia);

void flotar(Heap heap, int pos);

void hundir(Heap heap, int pos);

void heap_insertar(Heap heap, void* dato);

void heap_pop(Heap heap, void* dato);

void* heap_top(Heap heap);

#endif