#include <omp.h>
#include <stdio.h>

int main(){
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();

        printf("thread id %d y num threads %d\n", id, nt);
    }
    return 0;
}