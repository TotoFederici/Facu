#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5
#define S 15

int morfi;
sem_t plato_vacio;
sem_t plato_lleno;
pthread_mutex_t lock;

void llenar(){
    printf("Cocinero llenando el plato...\n");
    sleep(2);
}

void servirse(int p){
    printf("Se sirve el salvaje %d\n", p);
}

void* cooker(void* p){
    while(1){ 
        sem_wait(&plato_vacio);
        llenar();
        sem_post(&plato_lleno);
    }
    return NULL;
}

void* salvaje(void* p){
    while(1){
        pthread_mutex_lock(&lock);
        if(morfi == 0){
            printf("El salvaje %d encontro el plato vacio\n", p);
            sem_post(&plato_vacio);
            morfi = M;
            sem_wait(&plato_lleno);
        }
        morfi--;
        servirse(p);
        pthread_mutex_unlock(&lock);
        sleep(3);
    }
    return NULL;
}

int main() {
    pthread_t cocinero, salvajes[S];
    morfi = M;
    sem_init(&plato_vacio,0,0);
    sem_init(&plato_lleno,0,0);
    
    pthread_create(&cocinero, NULL, cooker, NULL);

    for(int i = 0; i < S; i++){
        pthread_create(&salvajes[i], NULL, salvaje, i+(void*)0);
    }
    pthread_join(cocinero, NULL);
    return 0;
}