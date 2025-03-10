#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void set_first(int a[]) {
    a[0] = 0;
    printf("%d\n", a[0]);
}

int main() {
    int x[] = {1,2,3,4,5};
    set_first(x);
    return 0;
}