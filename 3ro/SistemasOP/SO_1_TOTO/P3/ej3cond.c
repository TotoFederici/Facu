#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5
#define N 5
#define SZ 8

/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */
pthread_mutex_t acceso;
pthread_cond_t ok = PTHREAD_COND_INITIALIZER;

int *buffer[SZ];
int idxProd = 0;
int idxCons = 0;
int cant_elem = 0;

void enviar(int *p)
{
    buffer[idxProd] = p;
    idxProd = (idxProd+1) % SZ;
    cant_elem++;
	return;
}

int * recibir()
{
    int* p = buffer[idxCons];
    idxCons = (idxCons+1) % SZ;
    cant_elem--;
	return p;
}

void * prod_f(void *arg)
{
    int id = arg - (void*)0;
	while (1) {
        sleep(random() % 3);
        
		int *p = malloc(sizeof *p);
		*p = random() % 100;
		printf("Productor %d: produje %p->%d\n", id, p, *p);

        pthread_mutex_lock(&acceso);
        while(cant_elem == SZ){
            pthread_cond_wait(&ok,&acceso);
        }
		enviar(p);
        pthread_mutex_unlock(&acceso);
        pthread_cond_signal(&ok);
	}
	return NULL;
}

void * cons_f(void *arg)
{
	int id = arg - (void*)0;
	while (1) {
		sleep(random() % 3);

        pthread_mutex_lock(&acceso);
        while(cant_elem == 0){
            pthread_cond_wait(&ok,&acceso);
        }
		int *p = recibir();
        pthread_mutex_unlock(&acceso);
        pthread_cond_signal(&ok);
        
		printf("Consumidor %d: obtuve %p->%d\n", id, p, *p);
		free(p);
	}
	return NULL;
}

int main()
{
	pthread_t productores[M], consumidores[N];
	int i;

	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

	pthread_join(productores[0], NULL); /* Espera para siempre */
	return 0;
}
