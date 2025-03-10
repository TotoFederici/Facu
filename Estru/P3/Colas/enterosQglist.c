#include "Qglist.h"
#include <stdlib.h>
#include <stdio.h>

void print_int(int *data){
	printf("%d\n", *data);
}

void destroy_int(void *data){
	data = data;
	return;
}

int* copy_int(int *data){
	return data;
}