#include "heap.h"
#include <stdlib.h>

int maxH(int pos, void* x, void* y, FuncionComparadora comp) {
    return comp(x, y) > 0 ? 2*(pos-1) : 2*(pos-1)+1;
}

int hijo_izq(int j) {
    return 2*j+1;
}

int hijo_der(int j) {
    return 2*j+2;
}

int padre(int j) {
    return (j-1)/2;
}

void flotar(BHeap heap, int pos) {
    while(pos >= 0 && heap->comp(heap->arr[pos], heap->arr[padre(pos)]) > 0) {
        void* temp = heap->arr[pos];
        heap->arr[pos] = heap->arr[padre(pos)];
        heap->arr[padre(pos)] = temp;
        pos = padre(pos);
    }
}

void hundir(BHeap heap, int pos) {
    int hijoMax;
    while(pos <= heap->ultimo && heap->comp(heap->arr[pos], heap->arr[hijoMax]) < 0) {
        hijoMax = maxH(pos, heap->arr[hijo_izq(pos)], heap->arr[hijo_der(pos)], heap->comp);
        void* temp = heap->arr[pos];
        heap->arr[pos] = heap->arr[hijoMax];
        heap->arr[hijoMax] = temp;
        pos = hijoMax;
    }
}

BHeap bheap_crear(int capacidad, FuncionComparadora comp) {
    BHeap nuevo = malloc(sizeof(struct _BHeap));
    nuevo->arr = malloc(sizeof(void*)*capacidad);
    nuevo->capacidad = capacidad;
    nuevo->ultimo = -1;
    nuevo->comp = comp;
    return nuevo;
}

void bheap_destruir(BHeap heap, FuncionDestructora destruir) {
    for(int i=0; i<heap->capacidad; i++) {
        destruir(heap->arr[i]);
    }
    free(heap->arr);
    free(heap);
}

int bheap_vacio(BHeap heap) {
    return heap->ultimo == -1;
}

void bheap_recorrer(BHeap heap, FuncionVisitante visit) {
    if(heap->ultimo != -1) {
        for(int i=0; i <= heap->ultimo; i++) {
            visit(heap->arr[i]);
        }
    }
}

int bheap_buscar(BHeap heap, void* dato) {
    int pos = 0;
    for(; pos <= heap->ultimo && heap->comp(heap->arr[pos], dato) != 0; pos++);
    return heap->comp(heap->arr[pos], dato) == 0 ? pos : -1;
}

BHeap bheap_insertar(BHeap heap, void* dato, FuncionCopia copiar) {
    if(heap->ultimo == heap->capacidad-1) {
        heap->capacidad = heap->capacidad*2;
        heap->arr = realloc(heap->arr, heap->capacidad);
    }
    heap->ultimo++;
    heap->arr[heap->ultimo] = copiar(dato);
    flotar(heap, heap->ultimo);
    return heap;
}

void bheap_eliminar(BHeap heap, void* dato, FuncionDestructora destruir) {
    int pos = bheap_buscar(heap, dato);
    if(pos != -1) {
        destruir(heap->arr[pos]);
        heap->arr[pos] = heap->arr[heap->ultimo];
        heap->ultimo--;
        hundir(heap, pos);
    }
}

void bheap_extraer_maximo(BHeap heap) { // Esto esta en la teoria pero no se que onda (?)
    int esMayor=1, j=1, k;
    void* temp, *m;
    m = heap->arr[1];
    while(2*j <= heap->ultimo && esMayor) {
        k = 2*j;
        if(k+1<=heap->ultimo && heap->comp(heap->arr[k+1], heap->arr[k]) == 1)
            k = k+1;
        if(heap->comp(heap->arr[j], heap->arr[k]) == 1)
            esMayor = 0;
        else {
            temp = heap->arr[j];
            heap->arr[j] = heap->arr[k];
            heap->arr[k] = temp;
        }
    }
}

BHeap bheap_crear_desde_arr(void** arr, int largo, FuncionCopia copiar, FuncionComparadora comp) {
    BHeap heap = bheap_crear(largo, comp);
    return heap;
}

