#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t tabaco, papel, fosforo, otra_vez;
sem_t tabacoSem, papelSem, fosforoSem;
pthread_mutex_t tutu = PTHREAD_MUTEX_INITIALIZER;
int isTabaco, isPapel, isFosforo;

void agente()
{
    while (1) {
        sem_wait(&otra_vez);
        int caso = random() % 3;
        if (caso != 0) sem_post(&fosforo);
        if (caso != 1) sem_post(&papel);
        if (caso != 2) sem_post(&tabaco);
    }
}

void* pusher1(){
    while(1){
        sem_wait(&tabaco);
        pthread_mutex_lock(&tutu);
        if(isPapel){
            isPapel = 0;
            sem_post(&fosforoSem);
        }
        else if(isFosforo){
            isFosforo = 0;
            sem_post(&papelSem);
        }
        else{
            isTabaco = 1; 
        }
        pthread_mutex_unlock(&tutu);
    }
}

void* pusher2(){
    while(1){
        sem_wait(&papel);
        pthread_mutex_lock(&tutu);
        if(isFosforo){
            isFosforo = 0;
            sem_post(&tabacoSem);
        }
        else if(isTabaco){
            isTabaco = 0;
            sem_post(&fosforoSem);
        }
        else{
            isPapel = 1; 
        }
        pthread_mutex_unlock(&tutu);
    }
}

void* pusher3(){
    while(1){
        sem_wait(&fosforo);
        pthread_mutex_lock(&tutu);
        if(isTabaco){
            isTabaco = 0;
            sem_post(&papelSem);
        }
        else if(isPapel){
            isPapel = 0;
            sem_post(&tabacoSem);
        }
        else{
            isFosforo = 1; 
        }
        pthread_mutex_unlock(&tutu);
    }
}

void fumar(int fumador)
{
    printf("Fumador %d: Puf! Puf! Puf!\n", fumador);
    sleep(1);
}

void * fumador1(void *arg)
{
    while (1) {
        sem_wait(&tabacoSem);
        fumar(1);
        sem_post(&otra_vez);
    }
}

void * fumador2(void *arg)
{
    while (1) {
        sem_wait(&papelSem);
        fumar(2);
        sem_post(&otra_vez);
    }
}

void * fumador3(void *arg)
{
    while (1) {
        sem_wait(&fosforoSem);
        fumar(3);
        sem_post(&otra_vez);
    }
}

int main()
{
    pthread_t s1, s2, s3, c1, c2, c3;
    sem_init(&tabaco, 0, 0);
    sem_init(&papel, 0, 0);
    sem_init(&fosforo, 0, 0);
    sem_init(&tabacoSem, 0, 0);
    sem_init(&papelSem, 0, 0);
    sem_init(&fosforoSem, 0, 0);
    sem_init(&otra_vez, 0, 1);
    pthread_create(&s1, NULL, fumador1, NULL);
    pthread_create(&s2, NULL, fumador2, NULL);
    pthread_create(&s3, NULL, fumador3, NULL);
    pthread_create(&c1, NULL, pusher1, NULL);
    pthread_create(&c2, NULL, pusher2, NULL);
    pthread_create(&c3, NULL, pusher3, NULL);
    agente();
    return 0;
}