#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

int es_primo(long num){
    int check = 1;
    int root = sqrt(num);

    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 2; i < root; i++){
            if(num % i == 0){
                check = 0;
            }
        }
    }
    return check;
}

int main(){
    printf("%d\n", es_primo(500000003));
    return 0; 
}