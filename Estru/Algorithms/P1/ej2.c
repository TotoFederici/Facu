#include <stdio.h>

int exp(int b, int n) {
  if (n == 1) {return b;}
  return b * exp(b, n - 1);
}

int main() {
  int n1 = 2, n2 = 4;
  printf("%d to the power of %d = %d\n", n1, n2, exp(n1, n2));
  return 0;
}