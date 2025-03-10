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

#endif