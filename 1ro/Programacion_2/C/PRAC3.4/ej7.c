#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char bucle[5] = {'b','u','c','l','e'};
    char pal[5];
    int n;
    char letra = 't';

    for (n = 5; n > 0; n--, letra--) {
        pal[5-n] = bucle[5-n];
        if ((n % 2) == 0) {
            printf("%s %d %c\n", pal, n, letra);
        }
        else {
            printf("%s %d %c\n", pal, n, toupper(letra));
        }
    }

    return 0;
}