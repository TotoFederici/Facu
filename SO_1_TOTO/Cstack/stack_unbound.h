#ifndef STACK_UNBOUND_H
#define STACK_UNBOUND_H

#include <stdlib.h>

// A structure to represent a stack
// here we use a linked list to represent the unbound stack
typedef struct _StackNode {
    int data;
    struct _StackNode* next;
} StackNode;

StackNode* newNode(int data);

int isEmpty(StackNode* root);

void push(StackNode** root, int data);

int pop(StackNode** root);

int top(StackNode* root);

void stackFree(StackNode* root);

#endif /* CONCURRENT_STACK_H */