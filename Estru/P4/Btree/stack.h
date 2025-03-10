#ifndef __STACK_H__
#define __STACK_H__

#include "Sglist.h"
#include "tipos.h"

typedef GList Stack;

Stack stack_create();

int stack_is_empty (Stack stack);

Stack stack_push(Stack, void* dato, CopyFunction copy);

void* stack_top(Stack, CopyFunction copy);

Stack stack_pop(Stack, DestroyFunction destroy);

void stack_destroy(Stack p, DestroyFunction destroy);

#endif /* PILA_H */