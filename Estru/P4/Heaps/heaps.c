#include "heaps.h"
#include <stdio.h>
#include <stdlib.h>

int int_compare(int* a, int* b){
  return *a > *b;
}

int padre(int x){return x/2;}
int hij_izq(int x){return 2*x;}
int hij_der(int x){return (2*x) * 1;}

void int_destroy(int* a){
  return;
}

void print_int(int* a){
  printf("%d ", *a);
}

int* copy_int(int* a){
  return a;
}

void swap(void** a, void** b){
   void* aux = *a;
    *a = *b;
    *b = aux;
}

int int_equal(int* a, int* b){
  return *a == *b;
}

BHeap heap_create(int capacity, CompareFunction comp){
  BHeap heap = malloc(sizeof(struct _BHeap));
  heap->arr = malloc(sizeof(void*)*(capacity+1));
  heap->capacity = capacity+1;
  heap->comp = comp;
  heap->last = 0;
  return heap;
}

void heap_destroy(BHeap heap, DestroyFunction destroy){
  for(int i = 1; i < heap->capacity; i++){
    destroy(heap->arr[i]);
  }
  free(heap->arr);
  free(heap);
}

int heap_is_empty(BHeap heap){
  return !heap->last;
}

void heap_map(BHeap heap, VisitorFunction visit){
  for(int i = 1; i <= heap->last; i++){
    visit(heap->arr[i]);
  }
}

BHeap heap_insert(BHeap heap, void* data, CopyFunction copy){
  if (heap->last+1 >= heap->capacity){return heap;}

  heap->last += 1;
  int last = heap->last;
  void** arr = heap->arr;
  CompareFunction comp = heap->comp;

  arr[last]=copy(data);
  while(last > 1 && comp(arr[last], arr[last/2])){
    swap(&arr[last/2], &arr[last]);
    last /= 2;
  }
  return heap;
}

BHeap heap_delete(BHeap heap, void* data, DestroyFunction destroy, CompareFunction equal){
  int capacity = heap->capacity, last = heap->last;
  void** arr = heap->arr;
  CompareFunction comp = heap->comp;

  int found = 0;
  for(int i = 1; (!found) && (i <= last); i++){
    if(equal(arr[i], data)){
      destroy(arr[i]);
      if(i < last){
        arr[i] = arr[last];
        found = i;
      }
      heap->last -= 1;
    }
  }
  if(found){
    for(; found*2 <= heap->last;){

      if(comp(arr[found*2], arr[found]) && comp(arr[(found*2)+1], arr[found])){
        if(comp(arr[found*2], arr[(found*2)+1])){
          swap(&arr[found*2], &arr[found]);
          found *= 2;
        } else {
          swap(&arr[(found*2)+1], &arr[found]);
          found = (found*2)+1;
        }
      } else if(comp(arr[found*2], arr[found])){
        swap(&arr[found*2], &arr[found]);
        found *= 2;

      } else if(comp(arr[(found*2)+1], arr[found])){
        swap(&arr[(found*2)+1], &arr[found]);
        found = (found*2)+1;
      }
    }
  }
  return heap;
}


int pqueue_is_empty(PQueue queue){
  return queue->last==0;
}

void* queue_max(PQueue queue){
  return queue->arr[1];
}

void queue_delete_max(PQueue queue,DestroyFunction destroy,CompareFunction comp){
  heap_delete(queue,queue->arr[1],destroy,comp);
}

PQueue queue_insert(PQueue queue,void* data,CopyFunction copy){
  return heap_insert(queue,data,copy);
}

void heapsort(int* arr, int len){
	
}