#ifndef __MATRIX_BI_H__
#define __MATRIX_BI_H__

typedef struct {
  int** Matrix;
  int rows;
  int columns;
} matrixBi;

matrixBi matrix_create(int rows, int columns);

void matrix_destroy(matrixBi mat);

void matrix_write(matrixBi mat, int posR,int posC, int data);

int matrix_reed(matrixBi mat, int posR, int posC);

void matrixBi_print(matrixBi mat);

#endif