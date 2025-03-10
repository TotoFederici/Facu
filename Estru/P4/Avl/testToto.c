#include "avlToto.h"
#include <stdio.h>
#include <stdlib.h>

void *copy_int(void *data){
  int *p = malloc(sizeof(int));
  *p = *(int *)data;
	return p;
}

int comp_int(void *data1, void *data2){
  int a = *(int *)data1;
  int b = *(int *)data2;

  if (a < b)
    return -1;
  else if (a > b)
    return 1;
	return 0;
}

void visit_int(void *data) { printf("%d ", *(int *)data); }

int main(){
	int data1 = 1;
  int data2 = 2;
  int data3 = 3;
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;
  int data8 = 8;
  int data9 = 9;
  int data10 = 10;

  AVL tree = avl_create();
  tree = avl_insert(tree, &data5, copy_int, comp_int);
  tree = avl_insert(tree, &data3, copy_int, comp_int);
  tree = avl_insert(tree, &data9, copy_int, comp_int);
  tree = avl_insert(tree, &data7, copy_int, comp_int);
	//tree = avl_insert(tree, &data8, copy_int, comp_int);
  tree = avl_insert_balanced(tree, &data8, copy_int, comp_int);

  avl_map(tree, AVL_VISIT_PRE, visit_int);

  printf("\n%d", avl_validate(tree, comp_int));

	printf("\n");

	return 0;
}