#include <stdio.h>

void bubblesort(int* arr, int len){
	int swap = 1;
	while (swap){
		swap = 0;
		for(int i = 0; i < len-1; i++){
			if(arr[i] > arr[i+1]){
				int aux = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = aux;
				swap = 1;
			}
		}
	}
}

int main(){
	int len = 1000000;
	int arr[1000000];
	for(int i = 1000000; i > 0; i--){
		arr[1000000 - i] = i;
	}
	printf("\n");
	bubblesort(arr, len);
	printf("\n");
	return 0;
}