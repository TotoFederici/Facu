#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Devuelve una list vacía.
 */
GList glist_create() { return NULL; }

int glist_len(GList list) {
  int i = 0;
  if (list == NULL) {
    return -1;
  }
  for (GNode *temp = list; temp != NULL; temp = temp->next, i++);
  return i;
}

/**
 * Destruccion de la list.
 * destroy es una función que libera el data almacenado.
 */
void glist_destroy(GList list, DestroyFunction destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la list es vacía.
 */
int glist_empty(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la list.
 * copy es una función que retorna una copia física del data.
 */
GList glist_append_first(GList list, void *data, CopyFunction copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}