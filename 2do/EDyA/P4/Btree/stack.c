#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "Sglist.h"

Stack stack_create() {
	return NULL;
}

int stack_is_empty (Stack stack) {
	return Sglist_empty(stack);
}

Stack stack_push(Stack stack, void* data, CopyFunction copy) {
	return Sglist_append_first(stack, data, copy);
}

void* stack_top(Stack stack, CopyFunction copy) {
	return copy(stack->data);
}

Stack stack_pop(Stack stack, DestroyFunction destroy) {
	Stack toPop = stack;
	stack = stack->next;
	destroy(toPop->data);
	free(toPop);
	return stack;
}

void stack_destroy(Stack stack, DestroyFunction destroy) {
	Sglist_destroy(stack, destroy);
}