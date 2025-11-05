#include <stdio.h>

#define MAXN 20
#define MAXM 20

int n, m;
int tablero[MAXN][MAXM];

int filas[MAXN];
int columnas[MAXM];
int diag1[MAXN + MAXM - 1];
int diag2[MAXM + MAXM - 1];

int reinas(int k) {
	if (k == 0) {
		return 1;
	}

	int i = n - k;

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
