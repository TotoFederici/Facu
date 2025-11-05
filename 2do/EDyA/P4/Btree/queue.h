#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Qglist.h"
#include "tipos.h"

typedef GList Queue;

Queue queue_create();

void queue_destroy(Queue queue, DestroyFunction destroy);

int queue_is_empty(Queue queue);

void* queue_start(Queue queue);

Queue queue_enqueue(Queue queue, void* data, CopyFunction copy);

Queue queue_dequeue(Queue queue, DestroyFunction destroy);

void queue_print(Queue queue, VisitorFunction visit);

#endif