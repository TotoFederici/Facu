#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char* array = "que hace doña";
    printf("%p %p %p %p %p", &array[0], &array[1], &array[2], &array[3], &array[4]);
    return 0;
}