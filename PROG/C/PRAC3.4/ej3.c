#include <stdio.h>
#include <math.h>

int main() {
    float suma = 0;
    float n = 2;
    
    for(;n <= 10;n++) {
        suma += n * (n + 1);
    }

    printf("la suma es %f\n", suma);

    return 0;
}