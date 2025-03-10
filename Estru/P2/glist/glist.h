#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*DestroyFunction)(void *data);
typedef void *(*CopyFunction)(void *data);
typedef void (*VisitorFunction)(void *data);
typedef int (*Predicate)(void* data);
typedef int (*CompareFunction)(void*, void*);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode* GList;

/**
 * Devuelve una list vacía.
 */
GList glist_create();

/**
 * Destruccion de la list.
 */
void glist_destroy(GList list, DestroyFunction destroy);

/**
 * Determina si la list es vacía.
 */
int glist_empty(GList list);

/**
 * Agrega un elemento al inicio de la list.
 */
GList glist_append_first(GList list, void *data, CopyFunction copy);

/**
 * Recorrido de la list, utilizando la funcion pasada.
 */
void glist_traverse(GList list, VisitorFunction visit);

/**
 * Filtra los elementos de una list respecto de un predicado pasado como funcion.
 */
GList glist_filter(GList list, CopyFunction c, Predicate p);

GList glist_bucle(GList list, CopyFunction copy, CompareFunction compare);

/*-----------------------------------------O----------------------------------------------*/
/*Listas Generales Ordenadas*/

typedef GList SGList;

/**
 * Devuelve una list ordenada vacia.
 */
SGList sglist_create();

/**
 * Destruccion de la list ordenada.
 */
void sglist_destroy(SGList list, DestroyFunction destroy);

/**
 * Determina si la list ordenada es vacía.
 */
int sglist_empty(SGList list);

/**
 * Recorrido de la list ordenada, utilizando la funcion pasada.
 */
void sglist_traverse(SGList list, VisitorFunction visita);

SGList sglist_insert(SGList list, void* data, CopyFunction copy, CompareFunction compare);

void sglist_insertR_aux(SGList* list, SGList anterior, void* data, CopyFunction copy, CompareFunction compare);

SGList sglist_insertR(SGList list, void* data, CopyFunction copy, CompareFunction compare);

GList glist_intersection(GList list1, GList list2);

#endif /* __GLIST_H__ */
