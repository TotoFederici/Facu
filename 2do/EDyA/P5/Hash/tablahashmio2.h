#ifndef __TABLAHASHMIO_H__
#define __TABLAHASHMIO_H__

#include "tablahashmio.h"
#include "glist.h"
#include <assert.h>
#include <stdlib.h>

#define LIBRE 0
#define OCUPADO 1
#define ELIMINADO 2

typedef void *(*FuncionCopiadora)(void *dato);
/** Retorna una copia fisica del dato */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2  */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato);
/** Retorna un entero sin signo para el dato */

typedef struct _TablaHash *TablaHash;

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void *dato;
	int estado;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash);

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla);

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla);

void tablahash_insertarR(TablaHash tabla, void *dato, unsigned idx);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato);

#endif /* __GLIST_H__ */
