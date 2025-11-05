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
void no_destruir(void* i) {
    return;
}
void si_destruir(void* i) {
    free(i);
}

void imprimir_int(void* a) {
    printf("%i ", *(int*)a);
}

int main() {
    int* arr[5];
    for(int i=0; i<5; i++) {
        arr[i] = malloc(sizeof(int));
        *arr[i] = 10*(i+1);
    }

    BHeap heap = bheap_crear(5, (FuncionComparadora)comp_int);

    for(int i=0; i<5; i++) {
        heap = bheap_insertar(heap, arr[i], no_copiar);
    }
 
    bheap_recorrer(heap, imprimir_int);
    puts("");

    int* a = malloc(sizeof(int));
    *a = 125;
    bheap_eliminar(heap, arr[1], si_destruir);

    bheap_recorrer(heap, imprimir_int);
    puts("");

    for(int i=0; i<5; i++) {
        free(arr[i]);
    }
    free(a);
    bheap_destruir(heap, no_destruir);

   return 0;
}