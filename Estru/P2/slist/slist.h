#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

typedef void (*VisitorFunction) (int data);

typedef struct _SNode {
  int data;
  struct _SNode *next;
} SNode;

typedef SNode *SList;

/**
 * Devuelve una list vacía.
 */
SList slist_create();

/**
 * Destruccion de la list.
 */
void slist_destroy(SList list);

/**
 * Determina si la list es vacía.
 */
int slist_empty(SList list);

/**
 * Agrega un elemento al final de la list.
 */
void slist_append_last(SList* list, int data);

/**
 * Agrega un elemento al inicio de la list.
 */
void slist_append_first(SList* list, int data);

/**
 * Recorrido de la list, utilizando la funcion pasada.
 */
void slist_traverse(SList list, VisitorFunction visit);

/**
 * Calcula la longitud de la list.
 */
int slist_len(SList list);

/**
 * Concatena list1 con list2. 
 */
SList slist_concat(SList list1, SList list2);

/**
 * Inserta el elemento pasado en la posicion pasada.
 */
void slist_insert(SList* list, int data, int pos);

/**
 * Elimina el elemento en la posicion pasada.
 */
void slist_pop(SList* list, int pos);

/**
 * Verifica si el elemento pasado está en la list, en tal caso retorna 1, sino retorna 0.
 */
int slist_contain(SList* list, int data);

/**
 * Retorna el indice de la primera aparicion del elemento pasado, sino retora -1. 
 */
int slist_index(SList* list, int data);

#endif /* __SLIST_H__ */
