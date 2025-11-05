#ifndef __BTREE_H__
#define __BTREE_H__

#include "tipos.h"

typedef enum {
  BTREE_TRAVERSE_IN,
  BTREE_TRAVERSE_PRE,
  BTREE_TRAVERSE_POST
} BTreeTraverseOrder;

typedef struct _BTNode *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_create();

/**
 * Destruccion del árbol.
 */
void btree_destroy(BTree node);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree node);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_join(int data, BTree left, BTree right);

/**
 * Recorrido del arbol preorder iterativo, utilizando la funcion pasada.
 */
void btree_traverse_pre_it(BTree tree, VisitorFunctionInt visit);

int btree_nnodes(BTree tree);

int btree_search(BTree tree, int data);

BTree btree_copia(BTree tree);

void btree_traverse(BTree tree, BTreeTraverseOrder order, VisitorFunctionInt visit);

int btree_height(BTree tree);

int btree_nnodes_depth(BTree tree, int depth);

int btree_depth(BTree tree, int data);

int btree_sum(BTree tree);

void btree_bfs(BTree tree, VisitorFunction visit);

#endif /* __BTREE_H__ */
