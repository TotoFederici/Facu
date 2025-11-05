#include <stdlib.h>
#include <stdio.h>
#include "Qglist.h"

GList glist_create(){
	GList list;
	list.first = NULL;
	list.last = NULL;
	return list;
}

void gList_destroy(GList list, DestroyFunction destroy){
	GNode* temp;
	while (list.first != NULL){
		temp = list.first;
		list.first = list.first->next;
		destroy(temp->data);
		free(temp);
	}
}

int gList_is_empty(GList list){
	if (list.first == NULL) {return 1;}
	return 0;
}

GList glist_agregar_final(GList list, void* data, CopyFunction copy){
	GNode* newNode = malloc(sizeof(GNode));
	newNode->data = copy(data);
	newNode->next = NULL;
	if (list.first == NULL) {
		list.first = newNode;
	} else {
		list.last->next = newNode;
	}
	list.last = newNode;
	return list;
}

void glist_visit(GList list, VisitorFunction visit) {
	for (; list.first != NULL; list.first = list.first->next){
		visit(list.first->data);
	}
}