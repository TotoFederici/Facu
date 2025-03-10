#include "glist.h"
#include "enterosGlist.h"
#include <stdio.h>
#include <stdlib.h>

typedef GList Stack;

Stack stack_create(){
	return NULL;
}

void stack_destroy(Stack p, DestroyFunction destroy){
	glist_destroy(p, destroy);
}

int stack_is_empty(Stack p){
	if (glist_empty(p)){
		return 1;
	}
	return 0;
}

void *stack_top(Stack p){
	return p->data;
}

Stack stack_push(Stack p, void *data, CopyFunction copy){
	return glist_append_first(p, data, copy);
}

void stack_pop(Stack *p){
	if (!stack_is_empty(*p)){
		Stack nodo = *p;
		*p = (*p)->next;
		free(nodo);
	}
}

void stack_print(Stack p, VisitorFunction visit){
	glist_traverse(p, visit);
}

//-----------------------------0-------------------------------

GList revert_list(GList list, CopyFunction copy, DestroyFunction destroy){
	Stack s = stack_create();
	for (GList temp = list; temp != NULL; temp = temp->next) {
		s = stack_push(s, temp->data, copy);
	}
	glist_destroy(list, destroy);
	return s;
}

//-----------------------------0-------------------------------

int main(){
	Stack p = stack_create();
	int *numeros[5];
	int a = 0, b = 1, c = 2, d = 3, e = 4;
	numeros[0] = &a;
	numeros[1] = &b;
	numeros[2] = &c;
	numeros[3] = &d;
	numeros[4] = &e;

	for (int i = 0; i < 5; i++){
		printf("Pila:\n");
		stack_print(p, (VisitorFunction)print_int);
		printf("\n");
		p = stack_push(p, numeros[i], (CopyFunction)copy_int);
	}
	printf("Pila Completa:\n");
	stack_print(p, (VisitorFunction)print_int);
	printf("\n");
	stack_pop(&p);
	printf("Pila Elemento Desapilado:\n");
	stack_print(p, (VisitorFunction)print_int);
	printf("\n");
	stack_pop(&p);
	printf("Pila Elemento Desapilado:\n");
	stack_print(p, (VisitorFunction)print_int);
	printf("\n");

	stack_destroy(p, destroy_int);
	return 0;
}
