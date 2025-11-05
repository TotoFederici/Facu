#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "funcEnteros.h"

int main() {
  BTree rrr = btree_join(1, btree_create(), btree_create());
  BTree lr = btree_join(2, btree_create(), btree_create());
  BTree rl = btree_join(3, btree_create(), btree_create());
  BTree rr = btree_join(4, btree_create(), rrr);
  BTree l = btree_join(5, btree_create(), lr);
  BTree r = btree_join(6, rl, rr);
  BTree tree1 = btree_join(7, l, r);
/*printf("cant de nodos de profundidad 3: %d\n", btree_nnodes_depth(tree1, 3));
	printf("cant de nodos de profundidad 2: %d\n", btree_nnodes_depth(tree1, 2));
	printf("cant de nodos de profundidad 1: %d\n", btree_nnodes_depth(tree1, 1));
	printf("cant de nodos de profundidad 0: %d\n", btree_nnodes_depth(tree1, 0));
	printf("cant de nodos de profundidad 5: %d\n", btree_nnodes_depth(tree1, 5)); */

	printf("suma de los elementos del arbol: %d\n", btree_sum(tree1));

  btree_destroy(tree1);

  return 0;
}