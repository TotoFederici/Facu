#ifndef __ARREGLOENTEROS_H__
#define __ARREGLOENTEROS_H__

typedef struct{
	int *dir;
	int capacity;
} intArray;

intArray *int_array_create(int cap);

void int_array_destroy(intArray *a);

int int_array_read(intArray *a, int pos);

void int_array_write(intArray *a, int pos, int dato);

int int_array_capacity(intArray *a);

void int_array_print(intArray *a);

void int_array_fix(intArray *a);

#endif