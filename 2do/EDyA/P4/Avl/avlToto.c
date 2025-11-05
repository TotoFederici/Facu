#include "avlToto.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

AVL avl_create(){
	return NULL;
}

void avl_destroy(AVL tree, DestroyFunction destroy){
	if (tree != NULL){
		avl_destroy(tree->left, destroy);
		avl_destroy(tree->right, destroy);
		destroy(tree->data);
		free(tree);
	}
}

int max(int x, int y){
	return (x > y ? x : y);
}

int avl_heigth(AVL tree){
	if (tree == NULL){
		return -1;
	}
	return max(1 + avl_heigth(tree->left), 1 + avl_heigth(tree->right));
}


int avl_search(AVL tree, void* data, CompareFunction comp){
	if(tree == NULL) return 0;
	if(comp(data, tree->data) == 0) return 1;
	if(comp(data, tree->data) < 0){
		return avl_search(tree->left, data, comp);
	}
	return avl_search(tree->right, data, comp);
}

AVL avl_insert(AVL tree, void *data, CopyFunction copy, CompareFunction comp){
  if (tree == NULL) {
    AVL newNode = malloc(sizeof(AVL_Node));
    assert(newNode != NULL);
    newNode->data = copy(data);
    newNode->left = newNode->right = NULL;
    return newNode;
  } else if (comp(data, tree->data) < 0)
    tree->left = avl_insert(tree->left, data, copy, comp);
  else if (comp(data, tree->data) > 0)
    tree->right = avl_insert(tree->right, data, copy, comp);
  return tree;
}

int avl_validate_abb(AVL tree, CompareFunction comp){
	if(tree == NULL) return 1;
	if((tree->left != NULL) && (comp(tree->left->data, tree->data) > 0)){
		return 0;
	}
	if((tree->right != NULL) && (comp(tree->right->data, tree->data) < 0)){
		return 0;
	}
	return (1 && avl_validate_abb(tree->left, comp) && avl_validate_abb(tree->right, comp));
}

int avl_validate_R(AVL tree){
  if (tree == NULL)
    return 1;

  int left = avl_heigth(tree->left);
  int right = avl_heigth(tree->right);

  if ((left - right) < -1 || (left - right) > 1)
    return 0;
	return (avl_validate_R(tree->left) == avl_validate_R(tree->right));
}

int avl_validate(AVL tree, CompareFunction comp){
	return (avl_validate_abb(tree, comp) && avl_validate_R(tree));
}

AVL avl_rotate_simple_l(AVL tree){
  AVL aux = tree->right->left;
  AVL a = tree->right;
  tree->right->left = tree;
  tree->right = aux;

  return a;
}

AVL avl_rotate_simple_r(AVL tree){
  AVL aux = tree->left->right;
  AVL a = tree->left;
	tree->left->right = tree;
  tree->left = aux;

  return a;
}

int balance_factor(AVL node){
	if (node == NULL){
		return 0;
	}
	int leftHeigth = avl_heigth(node->left);
	int rightHeigth = avl_heigth(node->right);
	return leftHeigth - rightHeigth;
}

AVL avl_balance(AVL unbNode, CompareFunction comp){
	if(avl_validate(unbNode, comp) == 1){return unbNode;}
	
	int balance = balance_factor(unbNode);

	if(balance == 2){
		if(balance_factor(unbNode->left) == -1){
			unbNode->left = avl_rotate_simple_l(unbNode->left);
		}
		unbNode = avl_rotate_simple_r(unbNode);

	} else if (balance == -2) {
		if(balance_factor(unbNode->right) == 1){
			unbNode->right = avl_rotate_simple_r(unbNode->right);
		}
		unbNode = avl_rotate_simple_l(unbNode);
	}
	return unbNode;
}

void avl_map(AVL tree, mapOrder order, VisitorFunction visit){
	if(tree != NULL){
		if(order == AVL_VISIT_PRE){visit(tree->data);}
		avl_map(tree->left, order, visit);
		if(order == AVL_VISIT_IN){visit(tree->data);}
		avl_map(tree->right, order, visit);
		if(order == AVL_VISIT_POST){visit(tree->data);}
	}
}

AVL avl_insert_balanced(AVL tree, void *data, CopyFunction copy, CompareFunction comp){
  if (tree == NULL) {
    AVL newNode = malloc(sizeof(AVL_Node));
    assert(newNode != NULL);
    newNode->data = copy(data);
    newNode->left = newNode->right = NULL;
    return newNode;
  } else if (comp(data, tree->data) < 0)
    tree->left = avl_insert_balanced(tree->left, data, copy, comp);
  else if (comp(data, tree->data) > 0)
    tree->right = avl_insert_balanced(tree->right, data, copy, comp);
  return avl_balance(tree, comp);
}