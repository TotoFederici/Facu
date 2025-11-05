#include <stdio.h>
#include <stdlib.h>

typedef struct _GNode{
  int data;
  struct _GNode *next;
} GNode;

typedef struct{
  GNode *first;
  GNode *last;
} GList;

GList glist_create(){
	GList list;
	list.first = NULL;
	list.last = NULL;
	return list;
}

void glist_destroy(GList list){
	list.last->next = NULL;
	GNode* temp;
	while (list.first != NULL){
		temp = list.first;
		list.first = list.first->next;
		free(temp);
	}
}

GList append_first(GList list, int data) {
	GNode* newNode = malloc(sizeof(GNode));
	newNode->data = data;
	if (list.first == NULL) {
		newNode->next = newNode;
		list.last = newNode;
	} else {
		newNode->next = list.first;
		list.last->next = newNode;
	}
	list.first = newNode;
	return list;
}

void print_glist(GNode* list) {
	printf("%d ", list->data);
	for(GNode* temp = list->next; temp != list; temp = temp->next) {
		printf("%d ", temp->data);
	}
	printf("\n");
}

GList from_1_to_n(int n) {
	GList list = glist_create();
	for(int i = n; i >= 1; i--) {
		list = append_first(list, i);
	}
	return list;
}

int survivor(int n) {
	GList list = from_1_to_n(n);
	GNode* start = list.first;
	print_glist(list.first);
	int flag = 1;
	for (GNode* temp = list.first->next; list.first->next != list.first; print_glist(start)) {
		if (flag == 1) {
			list.first->next = temp->next;
			GNode* delete = temp;
			if (delete == list.last) {
				list.last = list.first;
			}
			if (delete == start) {
				start = temp->next;
			}
			temp = temp->next;
			free(delete);
			list.first = list.first->next;
			flag = 0;
		} else {
			temp = temp->next;
			flag = 1;
		}
	}
	int res = list.first->data;
	free(list.first);
	return res;
}

int main() {
	printf("El ganador para 10 fichas es: %d\n", survivor(10));
	return 0; 
}