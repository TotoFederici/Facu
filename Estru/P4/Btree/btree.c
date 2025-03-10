#include "btree.h"
#include "funcEnteros.h"
#include "Sglist.h"
#include "stack.h"
#include <assert.h>
#include <stdlib.h>

struct _BTNode {
  int data;
  struct _BTNode *left;
  struct _BTNode *right;
};

/**
 * Devuelve un arbol vacío.
 */
BTree btree_create() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destroy(BTree node) {
  if (node != NULL) {
    btree_destroy(node->left);
    btree_destroy(node->right);
    free(node);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree node) { return node == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_join(int data, BTree left, BTree right) {
  BTree newNode = malloc(sizeof(struct _BTNode));
  assert(newNode != NULL);
  newNode->data = data;
  newNode->left = left;
  newNode->right = right;
  return newNode;
}

void* not_copy(void* data){
  return data;
}

void not_destroy(void* data){
  return;
}

void btree_traverse(BTree tree, BTreeTraverseOrder order, VisitorFunctionInt visit){
	if(!btree_empty(tree)  && order == BTREE_TRAVERSE_PRE){
		visit(tree->data);
		btree_traverse(tree->left, order, visit);
		btree_traverse(tree->right, order, visit);
	} else if (!btree_empty(tree) && order == BTREE_TRAVERSE_IN){
		btree_traverse(tree->left, order, visit);
		visit(tree->data);
	  btree_traverse(tree->right, order, visit);
	} else if (!btree_empty(tree) && order == BTREE_TRAVERSE_POST){
		btree_traverse(tree->left, order, visit);
		btree_traverse(tree->right, order, visit);
		visit(tree->data);
	}
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_traverse_pre_it(BTree tree, VisitorFunctionInt visit) {
  if (btree_empty(tree))
    return;

  Stack nodeStack = stack_create();

  nodeStack = stack_push(nodeStack, tree, not_copy);

  while(!stack_is_empty(nodeStack)) {

    BTree auxNode = stack_top(nodeStack, not_copy);
    visit(auxNode->data);

    nodeStack = stack_pop(nodeStack, not_destroy);

    if (!btree_empty(auxNode->right))
      nodeStack = stack_push(nodeStack, auxNode->right, not_copy);

    if (!btree_empty(auxNode->left))
      nodeStack = stack_push(nodeStack, auxNode->left, not_copy);
  }
  stack_destroy(nodeStack, not_destroy);  
}

int btree_nnodes(BTree tree){
	if(btree_empty(tree)){
		return 0;
	}
	return 1 + btree_nnodes(tree->left) + btree_nnodes(tree->right);
}

int btree_search(BTree tree, int data){
	if(btree_empty(tree)){
		return 0;
	}
	if(tree->data == data){
		return 1;
	}
	return btree_search(tree->left, data) || btree_search(tree->right, data);
}

BTree btree_copia(BTree tree){
	if(btree_empty(tree)){
		return tree;
	}
	BTree newTree = malloc(sizeof(struct _BTNode));
	newTree->left = btree_copia(tree->left);
	newTree->right = btree_copia(tree->right);
	newTree->data = tree->data;
	return newTree;
}

int btree_height(BTree tree){
	if(btree_empty(tree)){
		return -1;
	}
	return max(1 + btree_height(tree->left), 1 + btree_height(tree->right));
}

int btree_nnodes_depth(BTree tree, int depth){
	if(btree_empty(tree)){
		return 0;
	}
	if(depth == 0){
		return 1;
	}
	return (btree_nnodes_depth(tree->left, depth - 1) + btree_nnodes_depth(tree->right, depth - 1));
}

int btree_depth(BTree tree, int data){
	if(btree_empty(tree)){
		return -1;
	}
	if(tree->data == data){
		return 0;
	}
	int left = btree_depth(tree->left, data);
	int right = btree_depth(tree->right, data);
	if (left != -1){
		return left+1;
	}
	if (right != -1){
		return right+1;
	}
	return -1;
}

int btree_sum(BTree tree){
	if(btree_empty(tree)){
		return 0;
	}
	return tree->data + btree_sum(tree->left) + btree_sum(tree->right);
}

BTree btree_traverse_extra(BTree tree, BTreeTraverseOrder order, ExtraVisitorFunction visit, void* extra){
	if(!btree_empty(tree)  && order == BTREE_TRAVERSE_PRE){
		visit(tree->data, extra);
		btree_traverse_extra(tree->left, order, visit, extra);
		btree_traverse_extra(tree->right, order, visit, extra);
	} else if (!btree_empty(tree) && order == BTREE_TRAVERSE_IN){
		btree_traverse_extra(tree->left, order, visit, extra);
		visit(tree->data, extra);
	  btree_traverse_extra(tree->right, order, visit, extra);
	} else if (!btree_empty(tree) && order == BTREE_TRAVERSE_POST){
		btree_traverse_extra(tree->left, order, visit, extra);
		btree_traverse_extra(tree->right, order, visit, extra);
		visit(tree->data, extra);
	}
}

void btree_bfs(BTree tree, VisitorFunction visit){

}