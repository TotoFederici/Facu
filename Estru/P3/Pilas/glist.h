#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*DestroyFunction)(void *data);
typedef void (*VisitorFunction)(void *data);
typedef void *(*CopyFunction)(void *data);

typedef struct _GNode{
	void *data;
	struct _GNode *next;
} GNode;

typedef GNode *GList;

typedef GList GSList;

GList glist_create();

void glist_destroy(GList list, DestroyFunction destroy);

int glist_empty(GList list);

void glist_traverse(GList list, VisitorFunction visit);

GList glist_append_first(GList list, void *data, CopyFunction copy);

#endif