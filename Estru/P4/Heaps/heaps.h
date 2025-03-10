#ifndef __HEAPS_H__
#define __HEAPS_H__

typedef int (*CompareFunction)(void*, void*);
typedef void (*DestroyFunction)(void*);
typedef void (*VisitorFunction)(void*);
typedef void* (*CopyFunction)(void*);

typedef struct _BHeap {
void **arr;
int capacity;
int last;
CompareFunction comp;
} *BHeap;

typedef BHeap PQueue;

int int_compare(int* a, int* b);

void int_destroy(int* a);

void print_int(int* a);

int* copy_int(int* a);

int int_equal(int* a, int* b);

BHeap heap_create(int capacity, CompareFunction comp);

void heap_destroy(BHeap heap, DestroyFunction destroy);

int heap_is_empty(BHeap heap);

void heap_map(BHeap heap, VisitorFunction visit);

BHeap heap_insert(BHeap heap, void* data, CopyFunction copy);

BHeap heap_delete(BHeap heap, void* data, DestroyFunction destroy, CompareFunction equal);

int pqueue_is_empty(PQueue queue);

void* queue_max(PQueue queue);

void queue_delete_max(PQueue queue,DestroyFunction destroy,CompareFunction comp);

PQueue queue_insert(PQueue queue,void* data,CopyFunction copy);

#endif