#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//----------------------------------------------CATEDRA--------------------------------------------------

int lomuto(int* arr, int pivote, int len) {
  int j = -1;
  for(int i=0; i < len; i++) {
    if(arr[i] <= pivote) {
      j++;
      swap(&arr[i], &arr[j]);
    }
	}
  return j;
}

void quicksort(int* arr, int len){
	if(len < 2) return;
	int pivote = arr[0];
	int posPivote = 1 + lomuto(arr+1, pivote, len);
	swap(&arr[0], &arr[posPivote]);
	quicksort(arr, posPivote);
	quicksort(arr + posPivote + 1, len - posPivote - 1);
}

//----------------------------------------------BROCODE--------------------------------------------------

int lomuto2(int* arr, int pivote, int len){
	int j = -1;
	for(int i = 0; arr[i] != pivote ; i++){
		if(pivote >= arr[i]){
			j++;
			swap(&arr[i], &arr[j]);
		}
	}
	j++;
	swap(&arr[j], &arr[len-1]);
	return j;
}

void quicksort2(int* arr, int len){
	if(len < 2) return;
	int pivote = arr[len-1];
	int posPivote = lomuto2(arr, pivote, len);
	quicksort2(arr, posPivote);
	quicksort2(arr + posPivote + 1, len - posPivote - 1);
}

//----------------------------------------------------------------------------------------------------------------

void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&array[i], &array[j]);
    }
}

void imprimir_array(int* arr, int len){
	for(int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}
}

int main(){
	int len = 100000;

	int arr[len];
  for (int i = 0; i < len; i++) {
    arr[i] = i + 1;
  }
  srand(time(NULL));
  shuffle(arr, len);
	imprimir_array(arr, len);
	printf("\n\n\n ACA \n\n\n");
	quicksort(arr, len);
	imprimir_array(arr, len);
	return 0;
}