#include <stdio.h>

int main() {
    int pacientes;
    float paci[2];

    do {
        printf("cuantos pacientes ingresaran?: ");
        scanf("%d", &pacientes); 
    }
    while (pacientes <= 0);

    int i = pacientes;
    int cantIngr = 0;
    int cantOper = 0;
    float mediaEdadAn = 0;
    float mediaEdadIn = 0;
    float mediaEdadOp = 0;

    while (i > 0) {

        do {
            printf("que edad tiene el paciente?: ");
            scanf("%f", &paci[0]);
            printf("que indice de la enfermedad tiene el paciente?: ");
            scanf("%f", &paci[1]);
        }
        while ((paci[0] <= 0) && (paci[1] <= 0));
    
    mediaEdadAn += paci[0];

    if ((paci[1] > 0.6)) {
        mediaEdadIn += paci[0];
        cantIngr++;
    }
    else {
        mediaEdadOp += paci[0];
        cantOper++;
    }
        i--;
    }
    mediaEdadAn /= pacientes;
    mediaEdadIn /= cantIngr;   
    mediaEdadOp /= cantOper;

    printf("la media de edad de los analizados es %f\n", mediaEdadAn);
    printf("la media de edad de los ingresados es %f\n", mediaEdadIn);
    printf("la media de edad de los operados es %f\n", mediaEdadOp);

    return 0;
}