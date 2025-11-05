#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* get_new_line() {
    char* cad = malloc(sizeof(char)*100);
    printf("ingresa algo: ");
    scanf("%[^\n]", cad);
    return cad;
}

int main() {
    char* a = get_new_line();
    printf("%s\n", a);
    free(a);
    return 0;
}