#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[1024];

void* readint() {
  int *x = malloc(sizeof(int));
  scanf("%d%*c",x);
  return x;
}

void* readfloat() { 
  char *x = malloc(sizeof(float));
  scanf("%f%*c", (float *)x); //*c lee caracter y descarta
  return x;
}

void* readchar() {
  char *x = malloc(sizeof(char));
  scanf("%c",x);
  return x;
}

void* readstr() { 
  scanf("%[^\n]%*c", buf);
  int len = strlen(buf);
  char *x = malloc(sizeof(char)*(len+1));
  strcpy(x,buf);
  return x;
}

// void (*pf1[])(void *) = {&readint};

void printint(void* ptr) {
  printf("%d", *((int*)ptr));
}

void printfloat (void* ptr){
  printf("%lf", *((float*) ptr));
}

void printchar (void* ptr) {
  printf("%c", *((char*)ptr));
}

void printstr (void* ptr) {
  printf("%s",(char*)ptr);
}

void freeint (void* ptr) { free((int*)ptr); }
void freefloat (void* ptr) { free((float*)ptr); }
void freestr (void* ptr) { free((char*)ptr); }
void freechar (void* ptr) { freestr(ptr); }

/*
 * Using indices for each of the types:
 * INT_TYPE -> 0
 * FLOAT_TYPE -> 1
 * CHAR_TYPE -> 2
 * STRING_TYPE -> 3
 */

void* (*const READ_FUNC[])() = {&readint, &readfloat, &readchar, &readstr}; //(1)
void (*const PRINT_FUNC[])(void*) = {&printint, &printfloat, &printchar, &printstr};
void (*const FREE_FUNC[])(void*) = {&freeint, &freefloat, &freechar, &freestr};

typedef struct {
  void *value;
  int type;
} PythonList;

PythonList* new_python_list (int n) {
  return malloc(sizeof(PythonList)*n);
}

void free_element (PythonList element) {
  int type = element.type;
  (*FREE_FUNC[type])(element.value);
}

void free_python_list(PythonList *list, int n) {
  for (int i = 0; i < n; i++)
    free_element(list[i]);
  
  free(list);
}

int main() {
  PythonList *list;
  // void (*const READ_FUNC)(void *) = malloc(sizeof(void *) * 4); //Equivalente
  // a 1?

  printf("Ingrese la cantidad de elementos:");
  int n;
  scanf("%d%*c", &n);

  list = new_python_list(n);

  for (int i = 0; i < n; i++) {
    printf("Ingrese el tipo del elemento (0 - 3): ");
    int type;
    scanf("%d%*c", &type);

    void *value = (*READ_FUNC[type])();

    list[i] = (PythonList){value,type}; //?????
  }

  printf("Los elementos de tu lista son:\n");
  for (int i = 0; i < n; i++) {
    int type = list[i].type;
    (*PRINT_FUNC[type])(list[i].value);
    printf("\n");
  }

  free_python_list(list, n);

  return 0;
}