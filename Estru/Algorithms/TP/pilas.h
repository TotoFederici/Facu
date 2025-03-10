#ifndef __PILAS_H__
#define __PILAS_H__

Pila pila_crear();

void pila_destruir(Pila pila, FuncionDestructora destroy);

int pila_esta_vacia(Pila pila);

Pila pila_push(Pila pila, void *dato, FuncionCopia copy);

void* pila_pop(Pila *pila);

#endif