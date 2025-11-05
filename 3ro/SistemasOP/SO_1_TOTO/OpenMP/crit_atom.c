#include <omp.h>
#include <stdio.h>

#define VISIT 10000

int visitantes = 0;

void molinete(void){
    for(int i = 0; i < VISIT; i++)
    #pragma omp critical
    {
        visitantes++;
    }
}

int main(){
    int num_threads = 1;
    #pragma omp parallel num_threads(num_threads)
    {
        molinete();
    }

    printf("VISITANTES: %d\n",visitantes);
    return 0;
}