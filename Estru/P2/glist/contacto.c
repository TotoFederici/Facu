#include "contacto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glist.h"

/**
 * Crea un new contact.
 */
Contact *contact_create(char *name, char *tel, unsigned int age) {
  Contact *new = malloc(sizeof(Contact));

  new->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(new->name, name);

  new->tel = malloc(sizeof(char) * (strlen(tel) + 1));
  strcpy(new->tel, tel);

  new->age = age;

  return new;
}

/**
 * Crea una copia física del contact.
 */
Contact *contact_copy(Contact *contact) {
  Contact *copy =
      contact_create(contact->name, contact->tel, contact->age);
  return copy;
}

/**
 * Compara el name de dos contacts en orden lexicográfico. Devuelve 0 si son
 * iguales, < 0 si el primero es menor que el segundo y > 0 si el primero es
 * mayor que el segundo.
 */
int contact_compare(Contact *c1, Contact *c2) {
  return (strcmp(c1->name, c2->name));
}

/**
 * Función destructora de un contact.
 */
void contact_destroy(Contact *contact) {
  free(contact->name);
  free(contact->tel);
  free(contact);
}

/**
 * Imprime por pantalla un contact.
 */
void contact_print(Contact *contact) {
  printf("%s, %s, %d.\n", contact->name, contact->tel, contact->age);
}

int contact_is_greater_than(void* data) {
  unsigned int age = ((Contact*)(data))->age;
  if (age >= 60) {
    return 1;
  } return 0;
}

int compare_age(void* new, void* data) {
  if (((Contact*)(new))->age < ((Contact*)(data))->age) {return 1;} return 0;
}

int compare_lists(GList p1, GList* p2) {
  if (p1 == *p2) {return 1;} return 0;
}

GList node_copy(GList list) {
  GList copy = malloc(sizeof(GList));
  copy = list;
  return copy;
}