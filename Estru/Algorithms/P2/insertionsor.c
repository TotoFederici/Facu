#include <stdio.h>

void insertion(int* arr, int len){
	int inserted;

	for(int i = 1; i < len; i++){
		inserted = 0;

		for(int j = i; (inserted == 0 && j > 0); j--){
			if(arr[j-1] > arr[j]){
				int aux = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = aux;
			} else {
				inserted = 1;
			}
		}
	}
}

void mover_array(int* arr, int inicio, int final){
	for(; final >= inicio; final--){
		arr[final] = arr[final-1];
	}
}

void insertion_mejor(int* arr, int len){
	for(int i = 1; i < len; i++){
		int aux = arr[i];
		int j = i-1;
		for(; (j >= 0 && arr[i] < arr[j]); j--);
		mover_array(arr, j+1, i);
		arr[j+1] = aux;
	}
}

int main(){
	int len = 10;
	int arr[] = {3,6,4,8,1,5,0,9,2,7};

	for(int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	insertion_mejor(arr, len);
	for(int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}