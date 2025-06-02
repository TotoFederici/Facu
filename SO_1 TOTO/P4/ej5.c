#include <stdio.h>
#include <stdlib.h>
#include "timing.h"

#define N 1000

int A[N][N], B[N][N], C[N][N];

void mult(int A[N][N], int B[N][N], int C[N][N]){
    #pragma omp parallel
    {
        int i, j, k;
        #pragma omp for
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                C[i][j] = 0;
                for (k = 0; k < N; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
    printf("%d\n", C[0][0]);
}

/* void mult2(int A[N][N], int B[N][N], int C[N][N])
{
    int i, j, k;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            C[i][j] = 0;
            for (k = 0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    printf("%d\n", C[0][0]);
} */

int main(){
    int i, j;
    float time;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = random() % 1000;
            B[i][j] = random() % 1000;
        }
    }
    TIME_void(mult(A, B, C),&time);
    //mult2(A, B, C);
    return 0;
}