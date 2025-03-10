#include <stdio.h>

void bubble_sort(float array[], int len) {
  for (int iter = 0 ; iter < len - 1 ; iter++) {
    for (int i = 0 ; i < len - iter - 1; i++) {
      if (array[i] > array[i + 1]) {
        float aux = array[i];
        array[i] = array[i + 1];
        array[i + 1] = aux;
      }
    }
  }
}

float mediana(float *array, int len) {
    bubble_sort(array, len);
    if ((len % 2) == 0) {
      return (((array[(len / 2) - 1]) + (array[len / 2])) / 2);
    } else {
      return (array[(len / 2)]);
    }
}

int main() {
  float arr1[] = {-1.0, 2.2, 2.9, 3.1, 3.5};
  float arr2[] = {1.6, 5.7, 0.5, 14.1};
  printf("mediana = %f\n", mediana(arr1, 5));
  printf("mediana = %f\n", mediana(arr2, 4));
}