#include "funcEnteros.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(int data){
  printf("%d ", data);
}

int max(int x, int y){
	if(x < y){return y;}return x;
}