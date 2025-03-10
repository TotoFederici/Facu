#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

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

int medianaR(int* arr, int len, int mid) {
  int pivote = arr[0];
  int nizq = 1 + lomuto(arr+1, pivote, len-1);
  swap(&arr[0], &arr[nizq]);
  if(nizq == mid) {
    return arr[nizq];
  } else if(nizq < mid) {
    return medianaR(arr+nizq+1, len-nizq-1, mid-nizq-1);
  } else {
    return medianaR(arr, nizq, mid);
	}
}

int mediana(int* arr, int len) {
  return medianaR(arr, len, len/2);
}

int main(){
	int len = 7;

	int arr[] = {4,3,1,5,2,6,7};

	printf("%d\n", mediana(arr, len));
	return 0;
}