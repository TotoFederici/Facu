#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MAX 500000000

int min;

int main(){
    #pragma omp parallel
    {
        int* arr = malloc(sizeof(double)*MAX);
        min = arr[0];
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        int part = MAX / nt;

        #pragma omp for
        for(int i = id*part; i < (id+1)*part; i++){
            arr[i] = 1;
        }
        arr[1895823] = 0;

        #pragma omp for
        for(int j = id*part; j < (id+1)*part; j++){
            if (arr[j] < min){
                min = arr[j];
            }
        }
    }
    printf("%d\n", min);
    return 0;
}