#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define R 9
#define E 10

int problemas;
int renos_esperando;
int renos_listos;
sem_t santa_sem;
sem_t reno_sem;
sem_t elfo_sem;
pthread_mutex_t lock;
pthread_mutex_t lock_reno;

void laburar(){
    sleep(2 + (random() % 13));
}

void* santa(void* p){
    while(1){
        while(renos_esperando > 0){
            pthread_mutex_lock(&lock_reno);
            renos_esperando--;
            renos_listos++;
            if(renos_listos == 9){
                printf("Santa se fue, Feliz navidad\n");
                return NULL;
            }
            sem_post(&reno_sem);
            pthread_mutex_unlock(&lock_reno);
        }
        sem_wait(&santa_sem);
        printf("Santa esta ayudando...\n");
        sleep(3);
        problemas = 0;
        sem_post(&elfo_sem);
        sem_post(&elfo_sem);
        sem_post(&elfo_sem);
    }
    return NULL;
}

void* elfo(void* p){
    while(1){
        laburar();
        sem_wait(&elfo_sem);
        pthread_mutex_lock(&lock);
        printf("Elfo %d tiene un problema\n", p);
        problemas++;
        if(problemas == 3){
            sem_post(&santa_sem);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void vacaciones(){
    sleep(10 + random()%10);
}

void* reno(void* p){
    vacaciones();
    pthread_mutex_lock(&lock_reno);
    printf("Reno %d esperando\n",p);
    renos_esperando++;
    pthread_mutex_unlock(&lock_reno);
    sem_wait(&reno_sem);
    printf("Reno %d llego\n",p);
}

int main(){
    pthread_t santaclaus, elfos[E], renos[R];
    renos_esperando = 0;
    problemas = 0;
    sem_init(&santa_sem,0,0);
    sem_init(&elfo_sem,0,3);
    sem_init(&reno_sem,0,0);
    
    pthread_create(&santaclaus, NULL, santa, NULL);

    for(int i = 0; i < E; i++){
        pthread_create(&elfos[i], NULL, elfo, i+(void*)0);
    }
    for(int i = 0; i < R; i++){
        pthread_create(&renos[i], NULL, reno, i+(void*)0);
    }
    pthread_join(santaclaus, NULL);
    return 0;
}