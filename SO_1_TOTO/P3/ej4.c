#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define M 5
#define N 5
#define ARRLEN 10240

pthread_mutex_t acceso_r;
pthread_mutex_t acceso_w;
pthread_cond_t writer = PTHREAD_COND_INITIALIZER;
pthread_cond_t reader = PTHREAD_COND_INITIALIZER;
int cant_lectores = 0;
int escribiendo = 0;

int arr[ARRLEN];

void * escritor(void *arg)
{
    int i;
    int num = arg - (void*)0;
    while (1) {
        sleep(random() % 3);

        pthread_mutex_lock(&acceso_w);
        while (cant_lectores > 0){
            pthread_cond_wait(&writer,&acceso_w);
        }
        escribiendo++;
        printf("Escritor %d escribiendo\n", num);
        for (i = 0; i < ARRLEN; i++){
            arr[i] = num;
        }
        escribiendo--;
        pthread_mutex_unlock(&acceso_w);
        pthread_cond_broadcast(&reader);
    }
    return NULL;
}

void * lector(void *arg) {
    int v, i;
    int num = arg - (void*)0;

    while (1) {
        sleep(random() % 3);
        
        pthread_mutex_lock(&acceso_r);
        while(escribiendo > 0){
            pthread_cond_wait(&reader,&acceso_r);
        }
        cant_lectores++;
        pthread_mutex_unlock(&acceso_r);
        
        v = arr[0];
        for (i = 1; i < ARRLEN; i++) {
            if (arr[i] != v) break;
        }
        if (i < ARRLEN) printf("Lector %d, error de lectura\n", num);
        else printf("Lector %d, dato %d\n", num, v);
        
        pthread_mutex_lock(&acceso_r);
        cant_lectores--;
        if(cant_lectores == 0) pthread_cond_signal(&writer);

        pthread_mutex_unlock(&acceso_r);

    }
    return NULL;
}

int main()
{
    pthread_t lectores[M], escritores[N];
    pthread_mutex_init(&acceso_r,NULL);
    pthread_mutex_init(&acceso_w,NULL);
    int i;
    for (i = 0; i < M; i++){
        pthread_create(&lectores[i], NULL, lector, i + (void*)0);
    }
    for (i = 0; i < N; i++){
        pthread_create(&escritores[i], NULL, escritor, i + (void*)0);
    }
    pthread_join(lectores[0], NULL); /* Espera para siempre */
    return 0;
}