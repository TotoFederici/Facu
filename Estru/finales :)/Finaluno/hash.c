#include "hash.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia, FuncionComparadora comp, FuncionDestructora destr, FuncionHash hash){
	TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

	for(unsigned i = 0; i < tabla->capacidad; i++){
		tabla->elems[i].dato = NULL;
		tabla->elems[i].estado = LIBRE;
	}
	return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla){return tabla->numElems;}

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla){return tabla->capacidad;}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla){
	for(int i = 0; i < tabla->capacidad; i++){
		if(tabla->elems[i].estado == OCUPADO){
			tabla->destr(tabla->elems[i].dato);
		}
	}
	free(tabla->elems);
	free(tabla);
}


/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato){
	if(tabla->capacidad == tabla->numElems){
		return;
	}
	unsigned idx = tabla->hash(dato) % tabla->capacidad;
	
	for(int c = 0, insertado = 0; (c < tabla->capacidad && !insertado); c++){
		if(tabla->elems[idx].estado != OCUPADO){
			tabla->elems[idx].dato = tabla->copia(dato);
			tabla->elems[idx].estado = OCUPADO;
			tabla->numElems++;
			insertado = 1;
		} else {
			if(tabla->comp(tabla->elems[idx].dato, dato) == 0){
				tabla->destr(tabla->elems[idx].dato);
				tabla->elems[idx].dato = tabla->copia(dato);
				insertado = 1;
			} else {
				idx = (idx + 1) % tabla->capacidad;
			}
		}
	}
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void* tablahash_buscar(TablaHash tabla, void *dato){
	unsigned idx = tabla->hash(dato) % tabla->capacidad;
	int encontrado = 0;
	void* buscado = NULL;

	for(int c = tabla->capacidad; (c > 0 && !encontrado); c--, idx = (idx + 1) % tabla->capacidad){
		if(tabla->elems[idx].estado == LIBRE){
			encontrado = 1;
		} else if(tabla->elems[idx].estado == OCUPADO && tabla->comp(tabla->elems[idx].dato, dato) == 0){
			encontrado = 1;
			buscado = dato;
		}
	}
	return buscado;
}