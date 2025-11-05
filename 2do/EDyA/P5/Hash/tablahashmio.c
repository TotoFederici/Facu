#include "tablahashmio.h"
#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia,
                          FuncionComparadora comp, FuncionDestructora destr,
                          FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
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

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].lista = NULL;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */

void tablahash_destruir(TablaHash tabla){
	for(unsigned i = 0; i < tabla->capacidad; i++){
		glist_destroy(tabla->elems[i].lista, tabla->destr);
	}
	free(tabla->elems);
	free(tabla);
}

void tablahash_insertar(TablaHash tabla, void *dato){
	unsigned idx = tabla->hash(dato) % tabla->capacidad;
	int sobreEscribi = 0;

	for(GNode* temp = tabla->elems[idx].lista; (temp != NULL && !sobreEscribi); temp = temp->next){
		if(tabla->comp(temp->data, dato) == 0){
			temp->data = tabla->copia(dato);
			sobreEscribi = 1;
		}
	}
	if(!sobreEscribi){
		tabla->elems[idx].lista = glist_append_first(tabla->elems[idx].lista, dato, tabla->copia);
		tabla->numElems++;
	}
}

void *tablahash_buscar(TablaHash tabla, void *dato){
	unsigned idx = tabla->hash(dato) % tabla->capacidad;
	void* buscado = NULL;

	for(GNode* temp = tabla->elems[idx].lista; temp != NULL; temp = temp->next){
		if(tabla->comp(temp->data, dato) == 0){
			buscado = temp->data;
		}
	}
	return buscado;
}

void tablahash_eliminar(TablaHash tabla, void *dato){
	unsigned idx = tabla->hash(dato) % tabla->capacidad;
	GNode* temp = tabla->elems[idx].lista;

	if(tabla->comp(temp->data, dato) == 0){
		tabla->destr(temp->data);
		tabla->elems[idx].lista = temp->next;
		free(temp);
		tabla->numElems--;
		return;
	}

	int eliminado = 0;

	for(; (!eliminado && temp->next != NULL); temp = temp->next){
		if(tabla->comp(temp->next->data, dato) == 0){
			GNode* aux = temp->next;
			temp->next = temp->next->next;
			tabla->destr(aux->data);
			free(aux);
			tabla->numElems--;
			eliminado = 1;
		}
	}
}