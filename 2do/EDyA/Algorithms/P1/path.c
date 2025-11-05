#include <stdio.h>
#include <stdlib.h>
#include "Matrix_Bi.h"

int min(int x, int y){
	if (x < y){return x;}return y;
}

int dijkstra(matrixBi mat, int n, int m){
	if ((n == 0) && (m == 0)) {
		return mat.Matrix[n][m];
	} else if (m == 0) {
		return mat.Matrix[n][0] + dijkstra(mat, n-1, 0);
	} else if (n == 0) {
		return mat.Matrix[0][m] + dijkstra(mat, 0, m-1);
	} else {
		return mat.Matrix[n][m] + min(dijkstra(mat, n-1, m), dijkstra(mat, n, m-1));
	}
}

int main() {
	matrixBi mat = matrix_create(10, 10);
	/* int numeritos[] = {1,2,3,
										    4,5,6,
										    7,8,9}; */
	for(int i = 0; i < mat.rows; i++) {
		for(int j = 0; j < mat.columns; j++){
			matrix_write(mat, i, j, i+j);
		}
	}
	/* matrixBi_print(mat); */
	printf("%d\n", dijkstra(mat, 9, 9));
	matrix_destroy(mat);
	return 0;
}