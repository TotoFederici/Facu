#include "slist.h"
#include <stdlib.h>

SList slist_create() {
  return NULL;
}

void slist_destroy(SList list) {
  SNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    free(nodeToDelete);
  }
}

int slist_empty(SList list) {
  return list == NULL;
}

void slist_append_last(SList* list, int data) {
  SNode *newNode = malloc(sizeof(SNode));
  newNode->data = data;
  newNode->next = NULL;

  if (*list == NULL)
    *list = newNode;

  SList node = *list;
  for (;node->next != NULL;node = node->next);
  // Ahora 'node' apunta al ultimo elemento en la list.
  node->next = newNode;
}

void slist_append_first(SList* list, int data) {
  SNode *newNode = malloc(sizeof(SNode));
  newNode->data = data;
  newNode->next = *list;
  *list = newNode;
}

void slist_traverse(SList list, VisitorFunction visit) {
  for (SNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

int slist_len(SList list) {
  int i = 0;
  if (list == NULL) {
    return -1;
  }
  for (SNode *temp = list; temp != NULL; temp = temp->next, i++);
  return i;
}

SList slist_concat(SList list1, SList list2) {
  if (list1 == NULL) {
    return list2;
  }
  SNode *temp = list1;
  for (; temp->next != NULL; temp = temp->next);
  temp->next = list2;
  return list1;
}

void slist_insert(SList* list, int data, int pos) {
  SNode* newNode = malloc(sizeof(SNode));
  newNode->data = data;
  if (*list == NULL) {
    newNode->next = NULL;
    *list = newNode;
  } else {
    SNode* temp = *list;
    for (int i = 0; i < (pos - 1); temp = temp->next, i++);
    newNode->next = temp->next;
    temp->next = newNode;
  }
}

void slist_pop(SList* list, int pos) {
  SNode *aux ,*temp = *list;
  for (int i = 0; i < (pos - 1); temp = temp->next, i++);
  // Se utiliza aux para liberar el node que se elimina de la list.
  aux = temp->next;
  temp->next = temp->next->next;
  free(aux);
}

int slist_contain(SList* list, int data) {
  int coin = 0;
  for (SNode* temp = *list; temp->next != NULL; temp = temp->next) {
    if (temp->data == data) {
      coin = 1;
    }
  }
  return coin;
}

int slist_index(SList* list, int data) {
  int pos = -1, i = 0;
  for (SNode* temp = *list; pos == -1 && temp->next != NULL; temp = temp->next, i++) {
    if (temp->data == data) {
      pos = i;
    }
  }
  return pos;
}

