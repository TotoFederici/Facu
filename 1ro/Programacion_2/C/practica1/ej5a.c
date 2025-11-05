#include <stdio.h>

int main() {
    int nota;

    printf("que nota sacaste?: ");
    scanf("%d", &nota);

    if (!nota >= 1 || !nota <= 10)
    {
        printf("esa nota no es valida\n");
    }

    if (nota >= 1 && nota <= 5)
    {
        printf("tu condicion es insuficiente\n");
    }
    
    if (nota == 6)
    {
        printf("tu condicion es aprobado/a\n");
    }
    
    if (nota == 7)
    {
        printf("tu condicion es bueno\n");
    }

    if (nota == 8)
    {
        printf("tu condicion es muy bueno\n");
    }
    
    if (nota == 9)
    {
        printf("tu condicion es dsitinguido/a\n");
    }
    
    if (nota == 10)
    {
        printf("tu condicion es sobresaliente\n");
    }
    
    return 0;
}