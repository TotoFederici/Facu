#include <omp.h>
#include <stdio.h>

int main(){
    int a[100];
    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0; i < 100; i++)
        {
            int id = omp_get_thread_num();
            a[i] = 2*i;
            printf("THREAD %d GUARDO: %d\n", id, a[i]);
        }
    }
    return 0;
}