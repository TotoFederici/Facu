#include <stdio.h>
#include <stdlib.h>
#include "glist.h"

GList glist_create(){
	return NULL;
}

void glist_destroy(GList list, DestroyFunction destroy){
	GList temp;
	while (list != NULL){
		temp = list;
		list = list->next;
		destroy(temp->data);
		free(temp);
	}
}

int glist_empty(GList list){
	return list == NULL;
}

void glist_traverse(GList list, VisitorFunction visit){
	for (; list != NULL; list = list->next){
		visit(list->data);
	}
}

GList glist_append_first(GList list, void *data, CopyFunction copy){
	GList newNode = malloc(sizeof(GNode));
	newNode->data = copy(data);
	if (glist_empty(list)){
		newNode->next = NULL;
		return newNode;
	}
	newNode->next = list;
	return newNode;
}