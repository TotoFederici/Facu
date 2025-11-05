#include <stdio.h>

#define MAXN 20
#define MAXM 20

int n, m;
int tablero[MAXN][MAXM];

int check() {
	int filas[MAXN] = {};
	int columnas[MAXM] = {};
	int diag1[MAXN + MAXM - 1] = {};
	int diag2[MAXM + MAXM - 1] = {};

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int x = tablero[i][j];
			filas[i] += x;
			columnas[j] += x;
			diag1[i+j] += x;
			diag2[i-j+m-1] += x;
		}
	}

	for (int i = 0; i < n; ++i) if (filas[i] > 1) return 0;
	for (int i = 0; i < m; ++i) if (columnas[i] > 1) return 0;
	for (int i = 0; i < n+m-1; ++i) if (diag1[i] > 1) return 0;
	for (int i = 0; i < n+m-1; ++i) if (diag2[i] > 1) return 0;

	return 1;
}

int filas[MAXN];
int columnas[MAXM];
int diag1[MAXN + MAXM - 1];
int diag2[MAXM + MAXM - 1];

int reinas(int k) {
	if (k == 0) {
		return check();
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!tablero[i][j] && !filas[i] && !columnas[j] && !diag1[i+j] && !diag2[i-j+m-1]) {
				tablero[i][j] = 1;

				filas[i] = 1;
				columnas[j] = 1;
				diag1[i+j] = 1;
				diag2[i-j+m-1] = 1;

				if (reinas(k - 1)) return 1;

				filas[i] = 0;
				columnas[j] = 0;
				diag1[i+j] = 0;
				diag2[i-j+m-1] = 0;

				tablero[i][j] = 0;
			}	
		}
	}

	return 0;
}

int main() {
	scanf("%d", &n);
	m = n;

	if (reinas(n)) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				printf("%c ", tablero[i][j] ? '#' : '_');
			}
			printf("\n");
		}
	} else {
		printf("NO SE PUEDE\n");
	}
}
