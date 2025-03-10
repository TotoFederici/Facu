#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "funcEnteros.h"

Queue queue_create(){
	Queue queue = Qglist_create();
	return queue;
}

void queue_destroy(Queue queue, DestroyFunction destroy){
	Qglist_destroy(queue, destroy);
}

int queue_is_empty(Queue queue){
	return Qglist_is_empty(queue);
}

void* queue_start(Queue queue){
	if (queue.first == NULL) {
		return NULL;
	}
	return queue.first->data;
}

Queue queue_enqueue(Queue queue, void* data, CopyFunction copy){
	return Qglist_append_last(queue, data, copy);
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
	Qglist_traverse(queue, visit);
}