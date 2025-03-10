#include <stdio.h>

void sort(int* arr, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	int extra = (n+1)*(n+2)/2 - sum;

	for (int i = 0; i < n; i++) {
		if (i+1 < extra) {
			arr[i] = i+1;
		} else {
			arr[i] = i+2;
		}
	}
}

int main() {
	int len = 10;
	int arr[10] = {9,4,1,5,8,10,2,3,6,11};
	sort(arr, len);
	for (int i = 0; i < 10; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}