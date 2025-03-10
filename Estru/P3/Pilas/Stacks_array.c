#include "arregloenteros.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _Stack{
	intArray *arr;
	int last;
};

typedef struct _Stack *Stack;

Stack stack_create(int cap){
	Stack p = malloc(sizeof(struct _Stack));
	p->arr = int_array_create(cap);
	p->last = -1;
	return p;
}

void stack_destroy(Stack p){
	free(p->arr->dir);
	free(p->arr);
	free(p);
}

int stack_is_empty(Stack p){
	if (p->last == -1){
		return 1;
	}
	return 0;
}

int stack_top(Stack p){
	return p->arr->dir[p->last];
}

void stack_push(Stack p, int dato){
	if (p->last == p->arr->capacity - 1){
		int_array_fix(p->arr);
	}
	p->last++;
	p->arr->dir[p->last] = dato;
}

void stack_pop(Stack p){
	
	p->last--;
}

void stack_print(Stack p){
	for (int i = p->last; i >= 0; i--){
		printf("%d\n", p->arr->dir[i]);
	}
}

int main(){
	Stack p = stack_create(10);
	for (int i = 0; i < 10; i++){
		stack_push(p, i);
	}
	printf("Pila:\n");
	stack_print(p);
	stack_destroy(p);

	return 0;
}