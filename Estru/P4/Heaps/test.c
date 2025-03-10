#include "heaps.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  int a,b,c,d,e,f,g,h,i;
  a = 10, b = 20, c = 15, d = 25, e = 30, f = 16, g = 18, h = 19, i = 5;

  BHeap heap = heap_create(8, (CompareFunction)int_compare);
  heap = heap_insert(heap, &a, (CopyFunction)copy_int);
  heap = heap_insert(heap, &b, (CopyFunction)copy_int);
  heap = heap_insert(heap, &c, (CopyFunction)copy_int);
  heap = heap_insert(heap, &d, (CopyFunction)copy_int);
  heap = heap_insert(heap, &e, (CopyFunction)copy_int);
  heap = heap_insert(heap, &f, (CopyFunction)copy_int);
  heap = heap_insert(heap, &g, (CopyFunction)copy_int);
  heap = heap_insert(heap, &h, (CopyFunction)copy_int);
  heap = heap_insert(heap, &i, (CopyFunction)copy_int);


  heap_map(heap, (VisitorFunction)print_int);
  printf("\n");
  printf("%d\n", heap->last);
  heap = heap_delete(heap, &a, (DestroyFunction)int_destroy, (CompareFunction)int_equal);
  heap_map(heap, (VisitorFunction)print_int);
  printf("\n");
  printf("%d\n", heap->last);
  heap_destroy(heap, (DestroyFunction)int_destroy);

  return 0;
}