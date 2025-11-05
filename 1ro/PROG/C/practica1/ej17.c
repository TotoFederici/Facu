#include <stdio.h>
#include <math.h>

float maximo3(float pri, float seg, float ter){
    float banderita;

    if (pri > seg){
        if (pri > ter){
            banderita = pri;
        }
    }
    else if (seg > ter) {
        banderita = seg;
    }
    else {
        banderita = ter;
    }
    return banderita;
}

float rectangulo(float l1, float l2, float l3) {
    float ladomayor = maximo3(l1, l2, l3), rect = 0; 

    if ((ladomayor == l1) && ((ladomayor) == (sqrt(pow(l2,2) + pow(l3,2)))))
    {
        rect = 1;
    }
    else if ((ladomayor == l2) && ((ladomayor) == (sqrt(pow(l1,2) + pow(l3,2)))))
    {
        rect = 1;
    }
    else if ((ladomayor == l3) && ((ladomayor) == (sqrt(pow(l2,2) + pow(l1,2)))))
    {
        rect = 1;
    }
    return rect;
}

int main() {
    float l1, l2, l3;

    printf("ingrese tres numeros enteros positivos: ");
    scanf("%f%f%f", &l1, &l2, &l3);

    if (rectangulo(l1,l2,l3) == 1) {
        printf("es un triangulo rectangulo\n");
    }
    else {
        printf("no es un triangulo rectangulo\n");
    }
    return 0;
}