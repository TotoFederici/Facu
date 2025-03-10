#ifndef __QGLIST_H__
#define __QGLIST_H__

#include "tipos.h"

typedef struct _GNode{
	void* data;
	struct _GNode *next;
} GNode;

typedef struct __Queue{
	GNode *first;
	GNode *last;
} GList;

GList Qglist_create();

void Qglist_destroy(GList list, DestroyFunction destroy);

int Qglist_is_empty(GList list);

GList Qglist_append_last(GList list, void* data, CopyFunction copy);

void Qglist_traverse(GList list, VisitorFunction visit);

#endif