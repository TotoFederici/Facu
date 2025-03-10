#ifndef __QGLIST_H__
#define __QGLIST_H__

typedef void (*DestroyFunction)(void *data);
typedef void (*VisitorFunction)(void *data);
typedef void *(*CopyFunction)(void *data);


typedef struct _GNode{
	void* data;
	struct _GNode *next;
} GNode;

typedef struct __Queue{
	GNode *first;
	GNode *last;
} GList;

typedef GList Queue;

GList glist_create();

void gList_destroy(GList list, DestroyFunction destroy);

int gList_is_empty(GList list);

GList glist_agregar_final(GList list, void* data, CopyFunction copy);

void glist_visit(GList list, VisitorFunction visit);

#endif