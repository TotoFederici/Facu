#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//-----------------------------------------estructuras de datos------------------------------------------

typedef struct _S {
	int* arr;
	int suma;
	int len;
} ArrEnteros;

typedef struct _P {
	int* arr1;
	int len1;
	int* arr2;
	int len2;
} Particiones;

typedef struct _Pila {
	int* arr;
	int ultimo;
} Pila;

Pila* crear_pila(int capacidad){
	int* arr = malloc(sizeof(int)*capacidad);
	Pila *pila = malloc(sizeof(Pila));
	pila->arr = arr;
	pila->ultimo = -1;
	return pila;
}

void* apilar_pila(Pila* pila, int dato){
	pila->arr[++pila->ultimo] = dato;
}

int pila_desapilar(Pila* pila){
	return pila->arr[pila->ultimo--];
}

ArrEnteros* crear_arrenteros(char* entrada){
	ArrEnteros* S = malloc(sizeof(ArrEnteros));
	S->arr = malloc(sizeof(int)*strlen(entrada));
	int j = 0;

	for(int i = 0; entrada[i] != '\0'; i++){
		if(entrada[i] != '[' && entrada[i] != ']' && entrada[i] != ',' && entrada[i] != ' ') {
			if(entrada[i] == '-'){
				i++;
				S->arr[j] = '0' - entrada[i];
				S->suma += '0' - entrada[i];
				j++;
			} else {
				S->arr[j] = entrada[i] - '0';
				S->suma += entrada[i] - '0';
				j++;
			}
		}
	}
	S->arr = realloc(S->arr, sizeof(int)*j);
	S->len = j;
	return S;
}

//----------------------------------merge----------------------------------------

void mezclar(int* arr, int* left, int* right, int lenLeft, int lenRight){
	int i = 0, j = 0, k = 0;
	while(i < lenLeft && j < lenRight){
		if(left[i] > right[j]){
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

//-----------------------------------------la funcion de todos los tiempos---------------------------------------------

Particiones* obtener_particiones(char* entrada){
	ArrEnteros* S = crear_arrenteros(entrada);
	if(S->suma % 2 == 0){
		mergesort(S->arr, S->len);

		Particiones* P = malloc(sizeof(Particiones));
		P->arr1 = malloc(sizeof(int)*S->len);
		P->arr2 = malloc(sizeof(int)*S->len);

		Pila* pila = crear_pila(S->len);
		int sumaPila = 0;
		int* indicesPila = malloc(sizeof(int)*S->len);

		for(int i = 0, j = 0; sumaPila != S->suma/2 && i < S->len;){
			if(sumaPila < S->suma/2){
				apilar_pila(pila, S->arr[i]);
				sumaPila += S->arr[i];
				indicesPila[j] = i;
				i++, j++;
			} else if(sumaPila > S->suma/2){
				int desapilado = pila_desapilar(pila);
				sumaPila -= desapilado;
				j--;
			}
		}
		if(sumaPila == S->suma/2){
			for(int i = 0; pila->ultimo != -1; i++){
				P->arr1[i] = pila_desapilar(pila);
				P->len1++;
			}
			for(int i = 0, j = 0, k = 0; i < S->len; i++){
				if(i != indicesPila[j]){
					P->arr2[k] = S->arr[i];
					P->len2++;
					k++;
				} else {
					j++;
				}
			}
			free(pila->arr), free(pila);
			return P;
		}
	}
	printf("no es posible formar las particiones\n");
	return NULL;
}

int main(){
	char entrada[] = "[20, 2]";
	Particiones* P = obtener_particiones(entrada);
	if(P != NULL){
		for(int i = 0; i < P->len1; i++){
			printf("%d ", P->arr1[i]);
		}
		printf("\n");
		for(int i = 0; i < P->len2; i++){
			printf("%d ", P->arr2[i]);
		}
		printf("\n");
	}

	return 0;
}