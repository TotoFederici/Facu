#include <stdio.h>
#include <stdlib.h>
#include "Matrix_Bi.h"

matrixBi matrix_create(int rows, int columns) {
  matrixBi mat;
  int** M = malloc(sizeof(int*)*rows);
  for (int i = 0; i < rows; i++) {
    M[i] = malloc(sizeof(int)*columns);
  }
  mat.rows = rows;
  mat.columns = columns;
  mat.Matrix = M;
  return mat;
}

void matrix_destroy(matrixBi mat) {
  for (int i = 0; i < mat.rows; i++) {
    free(mat.Matrix[i]);
  }
  free(mat.Matrix);
}

void matrix_write(matrixBi mat, int posR,int posC, int data) {
  if ((posR < 0 || posR > mat.rows) || (posC < 0 || posC > mat.columns)) {
    printf("esa pos no existe maestro\n");
  } else {
    mat.Matrix[posR][posC] = data;
  }
}

int leer_matriz(matrixBi mat, int posR, int posC) {
  if ((posR < 0 || posR > mat.rows) || (posC < 0 || posC > mat.columns)) {
    printf("esa pos no existe maestro\n");
  } else {
    return mat.Matrix[posR][posC];
  }
}

void matrixBi_print(matrixBi M) {
  for(int i = 0; i < M.rows; i++){
    printf("( ");
    for(int j = 0; j < M.columns; j++){
      printf("%i ", M.Matrix[i][j]);
    }
  printf(")\n");
  }
}

/* int main() {
  matrixBi mat = crear_matriz(3, 3);
	int numeritos[] = {6, 9, 1, 3, 2, 7, 1, 1, 0};
	for(int i = 0; i < mat.rows; i++) {
		for(int j = 0; j < mat.columns; j++){
			escribir_matriz(mat, i, j, numeritos[(3*i) + j]);
		}
	}
	matrixBi_print(mat);
	destruir_matriz(mat);
	return 0;
} */