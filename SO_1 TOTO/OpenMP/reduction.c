#include <omp.h>
#include <stdio.h>

int main(){
    int sum;
    #pragma omp parallel
    {
        #pragma omp for reduction(+: sum)
        for(int i = 0; i < 100; i++)
        {
            sum = sum + 5;
            printf("SUMO THREAD %d\n", omp_get_thread_num());
        }
    }
    printf("SUMA FINAL: %d\n", sum);
    return 0;
}