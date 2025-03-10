#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int comp_int(int* x, int* y) {
    if(*x > *y) return 1;
    if(*x < *y) return -1;
    return 0;
}

void* no_copiar(void* i) {
    return i;
}
int* si_copiar(int* i) {
    int* n = malloc(sizeof(int));
    *n = *i;
    return n;
}
void no_destruir(void* i) {
    return;
}
void si_destruir(void* i) {
    free(i);
}

void imprimir_int(void* a) {
    printf("%i ", *(int*)a);
}

void prueba1() {
    int dato = 50;
    int dato2 = 40;
    int dato3 = 30;
    int dato4 = 31;
    int dato5 = 32;

    BHeap heap = bheap_crear(5, (FuncionComparadora)comp_int);

    heap = bheap_insertar(heap, &dato, no_copiar);
    heap = bheap_insertar(heap, &dato2, no_copiar);
    heap = bheap_insertar(heap, &dato3, no_copiar);
    heap = bheap_insertar(heap, &dato4, no_copiar);
    heap = bheap_insertar(heap, &dato5, no_copiar);

    bheap_recorrer(heap, imprimir_int);
    puts("");
    bheap_eliminar(heap, &dato5, no_destruir);
    bheap_recorrer(heap, imprimir_int);
}

void prueba2() {
    int* arr[5];
    int dato = 32;  arr[0] = &dato;
    int dato2 = 30; arr[1] = &dato2;
    int dato3 = 40; arr[2] = &dato3;
    int dato4 = 31; arr[3] = &dato4;
    int dato5 = 50; arr[4] = &dato5;

    heapify((void**)arr, 5, (FuncionComparadora)comp_int);
    for(int i=0; i<5; i++) {
        printf("%i ", *arr[i]); // <- Negrada
    }
    BHeap yippee = bheap_crear_desde_arr((void**)arr, 5, (FuncionCopia)si_copiar, (FuncionComparadora)comp_int);
    bheap_recorrer(yippee, imprimir_int);
    puts("");
}

int main() {
    prueba2();

    return 0;
}