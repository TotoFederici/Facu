#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CANT_ASIENTOS 4
#define CANT_CLI 100

sem_t clientes;
sem_t asientos;
sem_t corte;
sem_t pago;
pthread_t client[CANT_CLI];
pthread_t barber;

void cortando(){
    printf("Te estoy cortando\n");
    sem_post(&corte);
}
void me_cortan(){
    sem_wait(&corte);
    printf("Me estan cortando\n");
}
void pagando(){
    printf("Te estoy pagando\n");
    sem_post(&pago);
}
void me_pagan(){
    sem_wait(&pago);
    printf("Me estan pagando\n");
}


void* barbero(void* p){
    while(1){
        sem_wait(&clientes);
        sem_post(&asientos);
        cortando();
        me_pagan();
    }
    return NULL;
}

void* cliente(void* p){
    while(1){
        if(sem_trywait(&asientos)){
            sleep(2);
            cliente(p);
        }
        sem_post(&clientes);
        me_cortan();
        pagando();
    }
    return NULL;
}

int main(){
    sem_init(&asientos,0,CANT_ASIENTOS);
    sem_init(&clientes,0,0);
    sem_init(&corte,0,0);
    sem_init(&pago,0,0);

    pthread_create(&barber,NULL,barbero,NULL);

    for (int i = 0; i < CANT_CLI; i++){
        pthread_create(&client[i],NULL,cliente,NULL);
    }
    pthread_join(barber,NULL);

    return 0;
}