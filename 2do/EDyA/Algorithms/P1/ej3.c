#include <stdio.h>

int max(int* arr, int len) {
	int max = 0, elemMax = arr[0];
	for(int i = 1; i < len; i++) {
		if (arr[i] > arr[max]) {
			max = i;
		}
	}
	return max;
}

int main() {
	int arr[] = {10,2,3,4,3,2,6};
	printf("pos of max element: %d\n", max(arr, 7));
	return 0;
}