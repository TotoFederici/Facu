#include "contacto.h"
#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  GList list1 = glist_create();
  Contact *contacts[7];
  contacts[0] = contact_create("Pepe Argento", "3412695452", 61);
  contacts[1] = contact_create("Moni Argento", "3412684759", 60);
  contacts[2] = contact_create("Coqui Argento", "3415694286", 32);
  contacts[3] = contact_create("Paola Argento", "3416259862", 29);
  contacts[4] = contact_create("Maria Elena Fuseneco", "3416874594", 59);
  contacts[5] = contact_create("Dardo Fuseneco", "3416894526", 64);
  contacts[6] = contact_create("Fatiga", "3416731900", 40);

  for (int i = 0; i < 7; ++i) {
    list1 =
        glist_append_first(list1, contacts[i], (CopyFunction)contact_copy);
    /* contact_destroy(contacts[i]); */
  }

  GList list2 = glist_create();
  Contact *contacts2[3];
  contacts2[0] = contact_create("TOMAS FEDERICI", "3412695452", 19);
  contacts2[1] = contact_create("ARIEL LEONARDO FIDELEFF", "3412684759", 20);
  contacts2[2] = contact_create("GIAN LUCA JUAREZ", "3415694286", 19);
  for (int i = 0; i < 3; ++i) {
    list2 =
        glist_append_first(list2, contacts2[i], (CopyFunction)contact_copy);
    /* contact_destroy(contacts[i]); */
  }
  list2->next->next->next = list1->next->next->next;
  

  printf("list1:\n");
  glist_traverse(list1, (VisitorFunction)contact_print);
  printf("\n");
  printf("list2:\n");
  glist_traverse(list2, (VisitorFunction)contact_print);
  printf("\n");

  list1 = glist_intersection(list1, list2);

  printf("interseccion:\n");
  glist_traverse(list1, (VisitorFunction)contact_print);
  printf("\n");

  return 0;
}