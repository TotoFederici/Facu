#include "tablahashmio2.h"
#include "glist.h"
#include "contacto.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 11
/** Capacidad inicial para la tabla hash */

/**
 * Caso de prueba: Tabla hash para contactos
 */
int main() {

  // Iniciar tabla hash
  TablaHash tabla = tablahash_crear(
      CAPACIDAD_INICIAL, (FuncionCopiadora)contacto_copia,
      (FuncionComparadora)contacto_comparar,
      (FuncionDestructora)contacto_destruir, (FuncionHash)contacto_heashear);

  // Contactos
  Contacto *agenda[13];
  agenda[0] = contacto_crear("Pepe Argento", "3412695452", 61);
  agenda[1] = contacto_crear("Moni Argento", "3412684759", 60);
  agenda[2] = contacto_crear("Coqui Argento", "3415694286", 32);
  agenda[3] = contacto_crear("Paola Argento", "3416259862", 29);
  agenda[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
  agenda[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);
	agenda[6] = contacto_crear("Toto", "3416894526", 19);
	agenda[7] = contacto_crear("Tomy", "3416894526", 20);
	agenda[8] = contacto_crear("Mati", "3416894526", 19);
	agenda[9] = contacto_crear("Tincho", "3416894526", 20);
	agenda[10] = contacto_crear("Peluka", "3416894526", 20);
	agenda[11] = contacto_crear("Ivo", "3416894526", 19);
	agenda[12] = contacto_crear("Lolen", "3416894526", 21);

  // Insertar
  printf("Insercion:\n");
  for (int i = 0; i < 13; ++i) {
    printf("Insertando el contacto: ");
    contacto_imprimir(agenda[i]);
    printf(" en la casilla %d.\n",
           contacto_heashear(agenda[i]) % tablahash_capacidad(tabla));
    int nElems = tablahash_nelems(tabla);
    tablahash_insertar(tabla, agenda[i]);
    if (tablahash_nelems(tabla) == nElems)
      printf("\tInsercion fallida: Colision.\n");
    else
      printf("\tInsercion exitosa.\n");
  }

  // Buscar
  printf("\nBusqueda:\n");
  for (int i = 0; i < 13; ++i) {
    printf("Buscando el contacto: ");
    contacto_imprimir(agenda[i]);
    puts("");
    Contacto *ret = tablahash_buscar(tabla, agenda[i]);
    if (ret != NULL)
      printf("\tSe encuentra en la tabla.\n");
    else
      printf("\tNo se encuentra en la tabla.\n");
  }

	printf("ACA ACA ACA\n");

		for(int i = 0; i < 13; i++){
		if(tabla->elems[i].estado == OCUPADO){
			printf("%d:", i);
			contacto_imprimir(tabla->elems[i].dato);
			puts("");
		}
	}

  // Eliminar
  printf("\nEliminacion:\n");
  for (int i = 9; i > 4; --i) {
    printf("Eliminando el contacto: ");
    contacto_imprimir(agenda[i]);
    puts("");
    tablahash_eliminar(tabla, agenda[i]);
  }

  // Buscar
  printf("\nBusqueda:\n");
  for (int i = 0; i < 13; ++i) {
    printf("Buscando el contacto: ");
    contacto_imprimir(agenda[i]);
    puts("");
    Contacto *ret = tablahash_buscar(tabla, agenda[i]);
    if (ret != NULL)
      printf("\tSe encuentra en la tabla.\n");
    else
      printf("\tNo se encuentra en la tabla.\n");
  }

  // Sobrescribir un contacto
  Contacto *nuevoContacto = contacto_crear("Pepe Argento", "3410000000", 71);
  printf("\nSobrescribiendo el contacto: ");
  contacto_imprimir(agenda[0]);
  printf("\n\tpor: ");
  contacto_imprimir(nuevoContacto);
  puts("");
  tablahash_insertar(tabla, nuevoContacto);
  // Chequeamos que se haya sobrescrito
  Contacto *ret = tablahash_buscar(
      tabla, agenda[0]); // Es equivalente a buscar nuevoContacto porque se
                         // compara por nombre
  printf("El nuevo contacto es: ");
  contacto_imprimir(ret);
  puts("");

	printf("ACA ACA ACA\n");

	for(int i = 0; i < 13; i++){
		if(tabla->elems[i].estado == OCUPADO){
			printf("%d:", i);
			contacto_imprimir(tabla->elems[i].dato);
			puts("");
		}
	}

  // Liberar memoria
  tablahash_destruir(tabla);
  for (int i = 0; i < 13; ++i)
    contacto_destruir(agenda[i]);
  contacto_destruir(nuevoContacto);

  return 0;
}