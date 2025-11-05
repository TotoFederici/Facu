#include <stdio.h>
#include <stdlib.h>
#include "Sglist.h"

GList Sglist_create(){
	return NULL;
}

void Sglist_destroy(GList list, DestroyFunction destroy){
	GList temp;
	while (list != NULL){
		temp = list;
		list = list->next;
		destroy(temp->data);
		free(temp);
	}
}

int Sglist_empty(GList list){
	return list == NULL;
}

void Sglist_traverse(GList list, VisitorFunction visit){
	for (; list != NULL; list = list->next){
		visit(list->data);
	}
}

GList Sglist_append_first(GList list, void *data, CopyFunction copy){
	GList newNodo = malloc(sizeof(GNode));
	newNodo->data = copy(data);
	if (Sglist_empty(list)){
		newNodo->next = NULL;
		return newNodo;
	}
	newNodo->next = list;
	return newNodo;
}
