#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float* Matrix;
  int rows;
  int columns;
} matrixUni;

matrixUni* matrix_create(int rows, int columns) {
  matrixUni* mat = malloc(sizeof(matrixUni));
  mat->Matrix = malloc(sizeof(float) * rows * columns);
  mat->rows = rows;
  mat->columns = columns;
  return mat;
}

void matrix_destroy(matrixUni* mat) {
  free(mat->Matrix);
  free(mat);
}

void matrix_write(matrixUni* mat, int posR, int posC, float data) {
  if ((posR < 0 || posR > mat->rows) || (posC < 0 || posC > mat->columns)) {
    printf("esa pos no existe maestro\n");
  } else {
    mat->Matrix[(posR * (posR + 1)) + posC] = data;
  }
}

float matrix_read(matrixUni* mat, int posR, int posC) {
  if ((posR < 0 || posR > mat->rows) || (posC < 0 || posC > mat->columns)) {
    printf("esa pos no existe maestro\n");
  } else {
    return mat->Matrix[(posR * (posR + 1)) + posC];
  }
}

int main() {
  matrixUni* mat = matrix_create(3, 3);
  float Matrix[] = {2.3, 8.89, 3.14, 2.64, 18.89, 2.71, 1.59, 0.01, 1.61};
  mat->Matrix = Matrix;
  printf("%f\n", matrix_read(mat, 2, 0));
  matrix_write(mat, 2, 0, 1.41);
  printf("%f\n", matrix_read(mat, 2, 0));
}