#ifndef __CSTACK_H__
#define __CSTACK_H__

#include <pthread.h>
#include "stack_unbound.h"

#define MAX_STACK 20

typedef struct _cstack{
    StackNode* root;
    pthread_mutex_t c_mutex;
    int index;
} cstack;

cstack* c_create();

int c_isEmpty(cstack* stack);

int c_isFull(cstack* stack);

void c_push(cstack** stack, int data);

int c_pop(cstack** stack);

int c_top(cstack* stack);

void c_stackFree(cstack* stack);


#endif /* Stack Concurrente */