#include <stdio.h>

int main() {
    int nota;

    printf("que nota sacaste?: ");
    scanf("%d", &nota);

    if (nota > 10 || nota < 1)
    {
        printf("esa nota no es valida\n");
    }

    else if (nota >= 1 && nota <= 5)
    {
        printf("tu condicion es insuficiente\n");
    }

    else if (nota == 6)
    {
        printf("tu condicion es aprobado/a\n");
    }

    else if (nota == 7)
    {
        printf("tu condicion es bueno\n");
    }
    
    else if (nota == 8)
    {
        printf("tu condicion es muy bueno\n");
    }
    
    else if (nota == 9)
    {
        printf("tu condicion es distinguido/a\n");
    }

    else
    {
        printf("tu condicion es sobresaliente\n");
    }

    return 0;
}