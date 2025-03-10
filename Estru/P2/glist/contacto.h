#ifndef __CONTACTO_H__
#define __CONTACTO_H__
#include "glist.h"

/**
 * Estructura que representa un contacto.
 */
typedef struct {
  char *name;
  char *tel;
  unsigned int age;
} Contact;

/**
 * Crea un nuevo contacto.
 */
Contact *contact_create();

/**
 * Crea una copia física del contacto.
 */
Contact *contact_copy(Contact *contact);

/**
 * Compara el nombre de dos contactos en orden lexicográfico. Devuelve 0 si son
 * iguales, < 0 si el primero es menor que el segundo y > 0 si el primero es
 * mayor que el segundo.
 */
int contact_compare(Contact *c1, Contact *c2);

/**
 * Función destructora de un contacto.
 */
void contact_destroy(Contact *contact);

/**
 * Imprime por pantalla un contacto.
 */
void contact_print(Contact *contact);

int contact_is_greater_than(void* data);

int compare_age(void* new, void* age);

int compare_lists(GList p1, GList* p2);

GList node_copy(GList list);

#endif /* __CONTACTO_H__ */