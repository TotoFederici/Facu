#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int string_len(char* str) {
  int cont = 0;
  for (; str[cont] != '\0'; cont++) {
  }
  return cont;
}

void string_reverse(char* str) {
  int len = string_len(str);
  char* temp = malloc(sizeof(char)*len);
  strcpy(temp, str);
  for (int i = (len - 1); *temp != '\0'; i--, *temp++) {
    str[i] = *temp;
  }
  printf("%s\n", str);
}

int string_concat(char* str1, char* str2, int max) {
  int len1 = string_len(str1);
  int len2 = string_len(str2);
  int i = 0;
  if ((len1 - len2) < max) {
    printf("No entra el estrin\n");
  } else {
    for (; (i < max && str2[i] != '\0'); i++) {
      str1[len1 + i] = str2[i];
    }
    str1[len1 + i + 1] = '\0';
  }
  return i;
}

int string_compare(char* str1, char* str2) {
  int i = 0;
  for (; (str1[i] == str2[i] && (str1[i] != '\0' && str2[i] != '\0')); i++);
  if (str1[i] < str2[i]) {
    i = -1;
  } else if (str1[i] > str2[i]) {
    i = 1;
  } else {
    i = 0;
  }
  return i;
}

int string_substr(char* str1, char* str2) {
  int j = 0, k = 0, FirstAppear = -1;
  while (str1[j] != '\0' && str2[k] != '\0') {
    if (str1[j + k] == str2[k]) {
      k++;
    } else {
      k = 0;
      j++;
    }
  }
  if (str2[k] == '\0') {
    FirstAppear = j;
  } else {
    FirstAppear = -1;
  }
  return FirstAppear;
}

void string_join(char* strArray[], int n, char* sep, char* res, int lenRes) {
  int totalLen = string_len(sep) * (n - 1);
  for (int j = 0; j < n; j++) {
    totalLen += string_len(strArray[j]);
  }
  if (totalLen > lenRes) {
    printf("no entra el estrin\n");
    exit(0);
  }
  int i = 0;
  while (i < n) {
    strcat(res, strArray[i]);
    if (i != (n - 1)) {
      strcat(res, sep);
    }
    i++;
  }
  printf("%s\n", res);
}

int main() {
  char res[150];
  char* arr[] = {"hola", "LOCO", "soy", "Roberto", "Musso"};
  char sep[] = " ";
  string_join(arr, 5, sep, res, 150);
}