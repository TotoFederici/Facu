#ifndef __BHEAP_H__
#define __BHEAP_H__

typedef int (*FuncionComparadora)(void* dato1, void* dato2);
typedef void (*FuncionDestructora)(void* dato);
typedef void (*FuncionVisitante)(void* dato);
typedef void* (*FuncionCopia)(void* dato);

typedef struct _BHeap {
    void** arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
} *BHeap;

BHeap bheap_crear(int capacidad, FuncionComparadora comp);

void bheap_destruir(BHeap heap, FuncionDestructora destruir);

int bheap_vacio(BHeap heap);

void bheap_recorrer(BHeap heap, FuncionVisitante visit);

BHeap bheap_insertar(BHeap heap, void* dato, FuncionCopia copiar);

void bheap_eliminar(BHeap heap, void* dato, FuncionDestructora destruir);

void bheap_extraer_maximo(BHeap heap);

#endif