#include <stdio.h>

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

float ladosTriangulo(float L1, float L2, float L3){
    float ladomayor = maximo3(L1, L2, L3), banderita = 0;

    if ((ladomayor == L1) && ((L2 + L3) > ladomayor))
    {
        banderita = 1;
    }
    else if ((ladomayor == L2) && ((L1 + L3) > ladomayor))
    {
        banderita = 1;
    }
    else if ((ladomayor == L3) && ((L2 + L1) > ladomayor))
    {
        banderita = 1;
    }
    return banderita;
}

int main() {
    float L1, L2, L3;

    printf("ingrese tres numeros enteros positivos: ");
    scanf("%f%f%f", &L1, &L2, &L3);

    if (ladosTriangulo(L1, L2, L3) == 1) {
        printf("es un trianglulo\n");
    }
    else {
        printf("no es un trianglulo\n");
    }

    return 0;
}