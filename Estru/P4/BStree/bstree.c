#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */
struct _BST_Nodo {
  void *dato;
  struct _BST_Nodo *izq, *der;
};

/**
 * bstee_crear: Retorna un arbol de busqueda binaria vacio
 */
BSTree bstee_crear() { return NULL; }

/**
 * bstree_destruir: Destruye el arbol y sus datos
 */
void bstree_destruir(BSTree raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    bstree_destruir(raiz->izq, destr);
    bstree_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
};

/**
 * bstree_buscar: Retorna 1 si el dato se encuentra y 0 en caso
 * contrario
 */
int bstree_buscar(BSTree raiz, void *dato, FuncionComparadora comp) {
  if (raiz == NULL)
    return 0;
  else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
    return 1;
  else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    return bstree_buscar(raiz->izq, dato, comp);
  else // raiz->dato < dato
    return bstree_buscar(raiz->der, dato, comp);
}

/**
 * bstree_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad del arbol de busqueda binaria
 */
BSTree bstree_insertar(BSTree raiz, void *dato, FuncionCopiadora copia, FuncionComparadora comp) {
  if (raiz == NULL) { // insertar el dato en un nuevo nodo
    struct _BST_Nodo *nuevoNodo = malloc(sizeof(struct _BST_Nodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copia(dato);
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
  } else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    raiz->izq = bstree_insertar(raiz->izq, dato, copia, comp);
  else if (comp(dato, raiz->dato) > 0) // raiz->dato < dato
    raiz->der = bstree_insertar(raiz->der, dato, copia, comp);
  // si el dato ya se encontraba, no es insertado
  return raiz;
}

/**
 * bstree_recorrer: Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree raiz, BSTreeRecorrido orden, FuncionVisitanteExtra visita, void *extra) {
  if (raiz != NULL) {
    if (orden == BTREE_RECORRIDO_PRE)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->izq, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_IN)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->der, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_POST)
      visita(raiz->dato, extra);
  }
}

BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora cmp, FuncionDestructora destroy) {
  if (arbol == NULL)
    return NULL;

  if (!cmp(arbol->dato, dato)) {
    BSTree reemplazo;
    if (!arbol->der || !arbol->izq) {
      reemplazo = arbol->der ? arbol->der : arbol->izq;
      arbol->izq = arbol->der = NULL;
      bstree_destruir(arbol, destroy);
      arbol = reemplazo;
    }
    else {
      BSTree* reemplazoPtr = &(arbol->der);
      reemplazo = arbol->der;

      if (reemplazo->izq) {
        for (; reemplazo->izq->izq; reemplazo = reemplazo->izq);
        	reemplazoPtr = &(reemplazo->izq);
          reemplazo = reemplazo->izq;
      }

      dato = arbol->dato;
      arbol->dato = reemplazo->dato;
      reemplazo->dato = dato;
      *reemplazoPtr = bstree_eliminar(reemplazo, dato, cmp, destroy);
    }
  }
  else if (cmp(arbol->dato, dato) < 0)
    arbol->der = bstree_eliminar(arbol->der, dato, cmp, destroy);
  else 
    arbol->izq = bstree_eliminar(arbol->izq, dato, cmp, destroy);
	return arbol;
}

void* validarR2(BSTree arbol, FuncionComparadora comp){
	if(!arbol){return arbol;}
	if(!arbol->izq && !arbol->der)
    return arbol->dato;

  void* dato = validarR2(arbol->izq, comp);
  if(dato != NULL){
    if(comp(arbol->dato, dato) < 0){return NULL;}
	}

  dato = validarR2(arbol->der, comp);
  if(dato != NULL){
  	if(comp(arbol->dato, dato) > 0){return NULL;}
	}

  return dato;
}

void* validarR(BSTree arbol, FuncionComparadora comp){
	if(!arbol->izq && !arbol->der)
    return arbol->dato;

  void* dato = validarR(arbol->izq, comp);
  if(dato == NULL)
    return NULL;
  if(comp(arbol->dato, dato) < 0)
    return NULL;

  dato = validarR(arbol->der, comp);
  if(dato == NULL)
    return NULL;
  if(comp(arbol->dato, dato) > 0)
    return NULL;

  return dato;
}

int validar(BSTree arbol, FuncionComparadora comp) {
	if(arbol == NULL){return 1;}
  return validarR2(arbol, comp) != NULL ? 1 : 0;
}

BSTree btree_join(void* data, BSTree left, BSTree right, FuncionCopiadora copy) {
  BSTree newNode = malloc(sizeof(struct _BST_Nodo));
  assert(newNode != NULL);
  newNode->dato = copy(data);
  newNode->izq = left;
  newNode->der = right;
  return newNode;
}

BSTree mirror(BSTree arbol){
	if(arbol != NULL){
	BSTree temp = arbol->der;
	arbol->der = mirror(arbol->izq);
	arbol->izq = mirror(temp);
	}
	return arbol;
}