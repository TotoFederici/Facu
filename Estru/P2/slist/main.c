#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void print_int(int data) {
  printf("%d ", data);
}

int main(int argc, char *argv[]) {

  SList list = slist_create();

  slist_append_first(&list, 3);
  slist_append_first(&list, 2);
  slist_append_first(&list, 1);

  SList L1 = slist_create();

  slist_append_first(&L1, 6);
  slist_append_first(&L1, 5);
  slist_append_first(&L1, 4);

  list = slist_concat(list, L1);

  slist_traverse(list, print_int);
  puts("");

  slist_insert(&list, 0, 3);

  slist_traverse(list, print_int);
  puts("");

  printf("La list contiene al 0? (1 = si, 0 = no): %d\n", slist_contain(&list, 0));
  printf("el primer 0 está en la posicion (-1 si no se encontró): %d\n", slist_index(&list, 0));

  slist_pop(&list, 3);
  
  slist_traverse(list, print_int);
  puts("");

  printf("La list contiene al 0? (1 = si, 0 = no): %d\n", slist_contain(&list, 0));
  printf("el primer 0 está en la posicion (-1 si no se encontró): %d\n", slist_index(&list, 0));

  slist_destroy(list);

  return 0;
}