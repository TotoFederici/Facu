// C program for linked list implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cstack.h"

// source: https://www.geeksforgeeks.org/stack-data-structure-introduction-program/

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

cstack* c_create(){
    cstack* stack = malloc(sizeof(cstack));
    stack->root = NULL;
    stack->index = 0;
    pthread_mutex_init(&(stack->c_mutex),NULL);
    return stack;
}

int c_isEmpty(cstack* stack){
    return !(stack->root);
}

int c_isFull(cstack* stack){
    return MAX_STACK == stack->index;
}

void c_push(cstack** stack, int data){

    pthread_mutex_lock(&(*stack)->c_mutex);

    push(&((*stack)->root),data);
    (*stack)->index++;

    pthread_mutex_unlock(&(*stack)->c_mutex);
    
}

int c_pop(cstack** stack){
    if(c_isEmpty(*stack)){return INT_MIN;}

    pthread_mutex_lock(&(*stack)->c_mutex);

    int popped = pop(&((*stack)->root));
    (*stack)->index--;

    pthread_mutex_unlock(&(*stack)->c_mutex);

    return popped;
}

int c_top(cstack* stack){
    if(c_isEmpty(stack)){return INT_MIN;}
    return stack->root->data;
}

void c_stackFree(cstack* stack){
    while(!c_isEmpty(stack)){
        c_pop(&stack);
    }
}