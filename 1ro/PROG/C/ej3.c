#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void set_in(int* x) {
  if (*x != 0) {
    *x = 1;
  }
}

int main() {
  int x = 0;
  int y = 9;
  int* num1 = &x;
  int* num2 = &y;
  printf("x: %d, y: %d\n", *num1, *num2);
  set_in(num1);
  set_in(num2);
  printf("x: %d, y: %d\n", *num1, *num2);
  return 0;
}