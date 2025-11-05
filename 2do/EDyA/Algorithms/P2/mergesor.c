#include <stdio.h>
#include <stdlib.h>

void mezclar(int* arr, int* left, int* right, int lenLeft, int lenRight){
	int i = 0, j = 0, k = 0;
	while(i < lenLeft && j < lenRight){
		if(left[i] < right[j]){
			arr[k] = left[i];
			i++, k++;
		} else {
			arr[k] = right[j];
			j++, k++;
		}
	}

	while(i < lenLeft){
		arr[k] = left[i];
		i++, k++;
	}
	while(j < lenRight){
		arr[k] = right[j];
		j++, k++;
	}
}

//-----------------------------------------0------------------------------------------------

void mergesort(int* arr, int len){
	if(len <= 1) return;
	
	int mid = len/2;
	int left[mid];
	int right[len - mid];

	for(int i = 0; i < mid; i++){
		left[i] = arr[i];
	}
	for(int i = mid; i < len; i++){
		right[i - mid] = arr[i];
	}	
	mergesort(left, mid);
	mergesort(right, len - mid);
	mezclar(arr, left, right, mid, len - mid);
}

//-----------------------------------------0------------------------------------------------

void mergesort_R(int* arr, int* temp, int len){
	if(len <= 1){return;}
	int mid = len/2;
	
	mergesort_R(temp, arr, mid);
	mergesort_R(temp + mid, arr + mid, len - mid);
	mezclar(arr, temp, temp + mid, mid, len - mid);
}

void mergesort2(int* arr, int len){
	int* temp = malloc(sizeof(int)*len);
	for(int i = 0; i < len; i++){
		temp[i] = arr[i];
	}
	mergesort_R(arr, temp, len);
	free(temp);
}

int main(){
	int len = 10000;
	int arr[len];

	for(int i = len; i > 0; i--){
		arr[len - i] = i;
	}
	mergesort2(arr, len);
	for(int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}