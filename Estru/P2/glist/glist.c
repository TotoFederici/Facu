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

/**
 * Recorrido de la list, utilizando la funcion pasada.
 */
void glist_traverse(GList list, VisitorFunction visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

GList glist_filter(GList list, CopyFunction c, Predicate p) {
  if (list == NULL) {
    GList newList = glist_create();
    return newList;
  }
  if (p(list->data)) {
    void* data = list->data;
    return glist_append_first(glist_filter(list->next, c, p), data, c);
  } else {
    return glist_filter(list->next, c, p);
  }
}

int glist_contain(GList list, void* data, CompareFunction compare) {
  int coin = 0;
  for (GNode* temp = list; temp->next != NULL; temp = temp->next) {
    if (compare(data, temp->data) == 1) {
      coin = 1;
    }
  }
  return coin;
}

GList glist_bucle(GList list, CopyFunction copy, CompareFunction compare) {
  GList listAux = glist_create();
  for (int found = 0; ((found == 0) && (list != NULL)); list = list->next) {
    for (GNode* temp = listAux; temp != NULL; temp = temp->next) {
      if (compare(list, temp->data) == 1) {
        found = 1;
      }
    }
    listAux = glist_append_first(listAux, &list, copy);
  }
  return list;
}

GList glist_intersection(GList list1, GList list2) {
  int long1 = glist_len(list1);
  int long2 = glist_len(list2);
  int extra = abs(long1 - long2);
  if (long1 > long2) {
    for (int i = 0; i < extra; list1 = list1->next, i++);
  } else {
    for (int i = 0; i < extra; list2 = list2->next, i++);
  }
  GList intersection = glist_create();
  for (; ((intersection == NULL) && (list1 != NULL)); list1 = list1->next, list2 = list2->next) {
    if (list1 == list2) {
      intersection = list1;
    }
  }
  return intersection;
}

/*-----------------------------------------O----------------------------------------------*/
/*Listas Generales Ordenadas*/

SGList sglist_create() {
  return NULL;
}

void sglist_destroy(SGList list, DestroyFunction destroy) {
  GNode* nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete);
    free(nodeToDelete);
  }
}

int sglist_empty(SGList list) {
  if (list == NULL) {return 1; } return 0;
}

void sglist_traverse(SGList list, VisitorFunction visit) {
  for (; list != NULL; list = list->next) {
    visit(list->data);
  }
}

SGList sglist_insert(SGList list, void* data, CopyFunction copy, CompareFunction compare) {
  GNode* newNode = malloc(sizeof(GNode));
  SGList temp = list;
  newNode->data = copy(data);
  if (temp == NULL) {
    newNode->next = temp;
    return newNode;
  }
  if (compare(data, list->data) == 1) {
    newNode->next = list;
    return newNode;
  }
  GNode* prev = list;
  while ((temp != NULL) && (compare(data, temp->data) == 0)) {
    prev = temp;
    temp = temp->next;
  }
  newNode->next = temp;
  prev->next = newNode;
  return list;
}

void sglist_insertR_aux(SGList* list, SGList prev, void* data, CopyFunction copy, CompareFunction compare){
  if ((*list == NULL) || (compare(data, (*list)->data))) {
    GNode* newNode = malloc(sizeof(GNode));
    newNode->data = copy(data);
    newNode->next = *list;
    *list = newNode;
    if (prev != NULL) {
      prev->next = newNode;
    }
  } else {
    sglist_insertR_aux(&((*list)->next), *list, data, copy, compare);
  }
}

SGList sglist_insertR(SGList list, void* data, CopyFunction copy, CompareFunction compare) {
  GNode* prev = NULL;
  sglist_insertR_aux(&(list), prev , data, copy, compare);
  return list;
}

GList glist_reverseR_aux(GList list, GList newList, CopyFunction copy) {
  if (list == NULL) {
    return newList;
  }
  return glist_reverseR_aux(list->next, glist_append_first(newList, list->data, copy), copy);
}

GList glist_reverseR(GList list, CopyFunction copy){
  GList newList = glist_create();
  return glist_reverseR_aux(list, newList, copy);
}