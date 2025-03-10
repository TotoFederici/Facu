#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arregloenteros.h"

intArray *int_array_create(int cap){
	intArray *a = malloc(sizeof(intArray));
	int *dir = malloc(sizeof(int) * cap);
	a->dir = dir;
	a->capacity = cap;
	return a;
}

void int_array_destroy(intArray *a){
	free(a->dir);
	free(a);
}

int int_array_read(intArray *a, int pos){
	return (a->dir[pos]);
}

void int_array_write(intArray *a, int pos, int dato){
	a->dir[pos] = dato;
}

int int_array_capacity(intArray *a){
	return a->capacity;
}

void int_array_print(intArray *a){
	for (int i = 0; i < a->capacity; i++){
		printf("%d\n", a->dir[i]);
	}
}

void int_array_fix(intArray *a){
	a->capacity = a->capacity * 2;
	a->dir = realloc(a->dir, sizeof(intArray) * (a->capacity));
}