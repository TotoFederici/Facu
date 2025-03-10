#ifndef __AVLTOTO_H__
#define __AVLTOTO_H__

typedef void *(*CopyFunction)(void *data);
typedef int (*CompareFunction)(void * data1, void * data2);
typedef void (*DestroyFunction)(void *data);
typedef void (*VisitorFunction)(void *data);
typedef void (*ExtraVisitorFunction)(void *data, void *extra);

typedef enum {
  AVL_VISIT_IN,  /** Inorden */
  AVL_VISIT_PRE, /** Preorden */
  AVL_VISIT_POST /** Postorden */
} mapOrder;

typedef struct _AVL_Node {
  void* data;
  struct _AVL_Node* left, * right, * father;
} AVL_Node;

typedef AVL_Node *AVL;

AVL avl_create();

void avl_destroy(AVL tree, DestroyFunction destroy);

int max(int x, int y);

int avl_heigth(AVL tree);

int avl_search(AVL tree, void* data, CompareFunction comp);

AVL avl_insert(AVL tree, void *data, CopyFunction copy, CompareFunction comp);

void avl_map(AVL tree, mapOrder order, VisitorFunction visit);

int avl_validate_abb(AVL tree, CompareFunction comp);

int avl_validate_R(AVL tree);

int avl_validate(AVL tree, CompareFunction comp);

AVL avl_rotate_simple_l(AVL tree);

AVL avl_rotate_simple_r(AVL tree);

int balance_factor(AVL node);

AVL avl_balance(AVL unbNode, CompareFunction comp);

AVL avl_insert_balanced(AVL tree, void *data, CopyFunction copy, CompareFunction comp);

#endif