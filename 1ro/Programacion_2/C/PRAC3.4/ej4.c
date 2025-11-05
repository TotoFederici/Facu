#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c;
    

    for (a = 1;a <= 20;a++) {
        for (b = 1;b <= 30; b++) {
            c = sqrt((pow(a,2) + pow(b,2)));

            if (c == sqrt((pow(a,2) + pow(b,2)))) {
                printf("terna: %d,%d,%d\n", a, b, c);
            }
        }
    }
}