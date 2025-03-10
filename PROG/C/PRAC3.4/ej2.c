#include <stdio.h>

int main(){
    int i;

    printf("habitacion.1 - 2 camas - primera planta\n");
    printf("habitacion.2 - 1 camas - primera planta\n");
    printf("habitacion.3 - 3 camas - segunda planta\n");
    printf("habitacion.4 - 2 camas - segunda planta\n");
    printf("habitacion.5 - 1 camas - tercera planta\n");

    printf("que habitacion quiere reservar?: ");
    scanf("%d", &i);
    
    switch (i)
    {
    case 1:
        printf("su habitacion tiene 2 camas - esta en la primera planta\n");
        break;
    case 2:
        printf("su habitacion tiene 1 cama - esta en la primera planta\n");
        break;
    case 3:
        printf("su habitacion tiene 3 camas - esta en la segunda planta\n");
        break;
    case 4:
        printf("su habitacion tiene 2 camas - esta en la segunda planta\n");
        break;
    case 5:
        printf("su habitacion tiene 1 cama - esta en la tercera planta\n");
        break;
    default:
        printf("esa habitacion no existe\n");
    }

    return 0;
}