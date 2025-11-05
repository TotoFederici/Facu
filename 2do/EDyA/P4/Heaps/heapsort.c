#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyR(int* arr, int len, int root){
	int largest = root;
	int left = root*2 + 1;
	int right = root*2 + 2;

	if(left < len && arr[left] > arr[largest]){
		largest = left;
	}

	if(right < len && arr[right] > arr[largest]){
		largest = right;
	}

	if(largest != root){
		swap(&arr[root], &arr[largest]);
		heapifyR(arr, len, largest);
	}
}

void heapify(int* arr, int len){
	for(int i = len/2 - 1; i >= 0; i--){
		heapifyR(arr, len, i);
	}
}

int main(){

	int  len = 5;
	int arr[] = {32, 30, 40, 31, 50};

	heapify(arr, len);

	for(int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}