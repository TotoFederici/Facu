#include <stdio.h>

int fibonacci(int n) {
  if (n == 1) {return 0;}
  if (n == 2) {return 1;}
  return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
  int number = 10;
  printf("Fibonacci pos %d = %d\n", number, fibonacci(number));
  return 0;
}