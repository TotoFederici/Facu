#include <stdio.h>
#include <stdlib.h>

typedef struct {
int* dir;
int capacity;
} intArray;

intArray* int_array_create(int capacity) {
  intArray* arrStruct = malloc(sizeof(intArray));
  arrStruct->dir = malloc(sizeof(int)*capacity);
  arrStruct->capacity = capacity;
  return arrStruct;
}

void int_array_destroy(intArray* array) {
  free(array->dir);
  free(array);
}

int int_array_read(intArray* array, int pos) {
  if ((pos < 0) || (pos >= array->capacity)) {
    printf("Esa pos no existe mi loco.\n");  
  } else {
    return array->dir[pos];
  }
}

void int_array_write(intArray* array, int pos, int data) {
  if ((pos < 0) || (pos >= array->capacity)) {
    printf("Esa pos no existe mi loco.\n");  
  } else {
    array->dir[pos] = data;
  }
}

int int_array_capacity(intArray* array) {
  return array->capacity;
}

void int_array_print(intArray* array) {
  for (int i = 0; i < array->capacity; i++) {
    printf("%d\n", array->dir[i]);
  }
}

void int_array_fix(intArray* array, int capacity) {
  int* newDir = malloc(sizeof(int)*capacity);
  for (int i = 0; i < capacity; i++) {
    newDir[i] = array->dir[i];
  }
  array->dir = newDir;
  array->capacity = capacity;
}

void int_array_instert(intArray* array, int pos, int data) {
  int* newDir = malloc(sizeof(int)*(array->capacity + 1));
  array->capacity++;
  for (int i = 0; i < array->capacity + 1; i++) {
    if (i < pos) {
      newDir[i] = array->dir[i];
    } else if (i == pos) {
      newDir[i] = data;
    } else {
      newDir[i] = array->dir[i - 1];
    }
  }
  array->dir = newDir;
}

void int_array_pop(intArray* array, int pos) {
  int* newDir = malloc(sizeof(int)*(array->capacity - 1));
  for (int i = 0; i < array->capacity - 1; i++) {
    if (i < pos) {
      newDir[i] = array->dir[i];
    } else {
      newDir[i] = array->dir[i + 1];
    }
  }
  array->dir = newDir;
  array->capacity--;
}

int main() {
  intArray* arrStr = int_array_create(7);
  int arr[] = {84, 11, 6, -167, 121, 27, 53};
  arrStr->dir = arr;

  int_array_pop(arrStr, 5);
  int_array_print(arrStr);
}