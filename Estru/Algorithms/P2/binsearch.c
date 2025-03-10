#include <stdio.h>

int binsearch(int a[], int len, int v){
	int medio = len / 2;
	if (a[medio] == v){
		return 1;
	}
	if(medio == 0){
		return -1;
	}
	if(a[medio] > v){
		return binsearch(a, medio, v);
	}
	a = a + medio + 1;
	return binsearch(a, medio, v);
}

int main(){
	int a[] = {0,1,2,3,4,5,6};
	int b[] = {0,1,2,3,4,5,6,7};

	printf("1 en a: %d\n", binsearch(a, 7, 1));
	printf("6 en a: %d\n", binsearch(a, 7, 6));
	printf("0 en b: %d\n", binsearch(b, 8, 0));
	printf("5 en b: %d\n", binsearch(b, 8, 5));
	printf("7 en a: %d\n", binsearch(a, 7, 7));
	printf("-1 en b: %d\n", binsearch(b, 8, -1));
	return 0;
}