#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_barrier_t barrier;

void* func_thread(void* p){
    printf("Thread %d", (int)p);
    pthread_barrier_wait(&barrier);
}

int main(){

    pthread_barrier_init(&barrier,NULL,3);

    pthread_t threads[3];

    for(int i = 0; i < 3; i++){
        pthread_create(&threads[i],NULL,func_thread,(void*)i);
    }

    return 0;
}