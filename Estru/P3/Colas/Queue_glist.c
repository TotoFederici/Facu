#include <stdlib.h>
#include <stdio.h>
#include "Qglist.h"
#include "enterosQglist.h"

Queue queue_create(){
	Queue queue = glist_create();
	return queue;
}

void queue_destroy(Queue queue, DestroyFunction destroy){
	gList_destroy(queue, destroy);
}

int queue_is_empty(Queue queue){
	return gList_is_empty(queue);
}

void* queue_start(Queue queue){
	if (queue.first == NULL) {
		return NULL;
	}
	return queue.first->data;
}

Queue queue_enqueue(Queue queue, void* data, CopyFunction copy){
	return glist_agregar_final(queue, data, copy);
}

Queue queue_dequeue(Queue queue, DestroyFunction destroy){
	if (queue.first == NULL) {
		return queue;
	}
	if (queue.first == queue.last) {
		queue.last = NULL;
	}
	GNode* nodeToDelete = queue.first;
	queue.first = queue.first->next;
	destroy(nodeToDelete);
	free(nodeToDelete);
	return queue;
}

void queue_print(Queue queue, VisitorFunction visit){
	glist_visit(queue, visit);
}

int main() {
	Queue queue = queue_create();
	int *numeros[5];
	int a = 0, b = 1, c = 2, d = 3, e = 4;
	numeros[0] = &a;
	numeros[1] = &b;
	numeros[2] = &c;
	numeros[3] = &d;
	numeros[4] = &e;

	for (int i = 0; i < 5; i++){
		printf("Cola:\n");
		queue_print(queue, (VisitorFunction)print_int);
		printf("\n");
		queue = queue_enqueue(queue, numeros[i], (CopyFunction)copy_int);
	}
	printf("Cola Completa:\n");
	queue_print(queue, (VisitorFunction)print_int);
	printf("\n");
	queue = queue_dequeue(queue, (DestroyFunction)destroy_int);
	printf("Cola Elemento Desencolado:\n");
	queue_print(queue, (VisitorFunction)print_int);
	printf("\n");
	queue = queue_dequeue(queue, (DestroyFunction)destroy_int);
	printf("Cola Elemento Desencolado:\n");
	queue_print(queue, (VisitorFunction)print_int);
	printf("\n");
	queue_destroy(queue, destroy_int);
	return 0;
}