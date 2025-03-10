#ifndef __GLIST_H__
#define __GLIST_H__

#include "tipos.h"

typedef struct _GNode{
	void *data;
	struct _GNode *next;
} GNode;

typedef GNode *GList;

GList Sglist_create();

void Sglist_destroy(GList list, DestroyFunction destroy);

int Sglist_empty(GList list);

void Sglist_traverse(GList list, VisitorFunction visit);

GList Sglist_append_first(GList list, void *data, CopyFunction copy);

#endif