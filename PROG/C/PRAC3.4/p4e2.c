#include <stdio.h>

int vector[5] = {10 , 20 , 30 , 40 , 50};
int a = 3;
int *ptr=&a;
int *qtr=vector;

int main() {
    printf("%i\n", a); // numerito = 3
    printf("%p\n", &a);
    printf("%p\n", ptr);
    printf("%p\n", &ptr);
    printf("%i\n", *ptr);
    printf("%p\n", qtr);
    printf("%p\n", &qtr);
    printf("%i\n", *qtr);
    printf("%p\n", vector);
    printf("%p\n", &vector);
    printf("%i\n", *vector);
    printf("%p\n", ++qtr);
    printf("%i\n", ++*qtr);
    printf("%i\n", ++*vector);
    printf("%p\n", *&ptr);
}