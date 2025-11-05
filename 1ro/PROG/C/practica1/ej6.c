#include <stdio.h>

int main() {
    int dia, mes;

    printf("ingrese su dia y mes de nacimiento: ");
    scanf("%d%d", &dia, &mes);
    
    // esta seccion comprueba que tanto el mes como el dia sean validos

    if (mes < 1 || mes > 12)
    {
        printf("ese mes no existe\n");
    }
    else if (mes == 2 && (dia > 28 || dia < 1))
    {
        printf("ese dia no existe\n");
    }
    else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && (dia < 1 || dia > 30))
    {
        printf("ese dia no existe\n");
    }
    else if (dia > 31 || dia < 1)
    {
        printf("ese dia no existe\n");
    }

    // esta seccion revisa el signo segun la fecha ingresada

    else if (mes == 1)
    {
        if (dia <= 20)
        {
            printf("tu signo es capricornio\n");
        }
        else
        {
            printf("tu signo es acuario\n");
        }
    }

    else if (mes == 2)
    {
        if (dia <= 19)
        {
            printf("tu signo es acuario\n");
        }
        else
        {
            printf("tu signo es piscis\n");
        }
    }

    else if (mes == 3)
    {
        if (dia <= 20)
        {
            printf("tu signo es piscis\n");
        }
        else
        {
            printf("tu signo es aries\n");
        }
    }

    else if (mes == 4)
    {
        if (dia <= 19)
        {
            printf("tu signo es aries\n");
        }
        else
        {
            printf("tu signo es tauro\n");
        }
    }

    else if (mes == 5)
    {
        if (dia <= 20)
        {
            printf("tu signo es tauro\n");
        }
        else
        {
            printf("tu signo es geminis\n");
        }
    }

    else if (mes == 6)
    {
        if (dia <= 21)
        {
            printf("tu signo es geminis\n");
        }
        else
        {
            printf("tu signo es cancer\n");
        }
    }

    else if (mes == 7)
    {
        if (dia <= 21)
        {
            printf("tu signo es cancer\n");
        }
        else
        {
            printf("tu signo es leo\n");
        }
    }

    else if (mes == 8)
    {
        if (dia <= 21)
        {
            printf("tu signo es leo\n");
        }
        else
        {
            printf("tu signo es virgo\n");
        }
    }

    else if (mes == 9)
    {
        if (dia <= 22)
        {
            printf("tu signo es virgo\n");
        }
        else
        {
            printf("tu signo es libra\n");
        }
    }

    else if (mes == 10)
    {
        if (dia <= 22)
        {
            printf("tu signo es libra\n");
        }
        else
        {
            printf("tu signo es escorpio\n");
        }
    }

    else if (mes == 11)
    {
        if (dia <= 21)
        {
            printf("tu signo es escorpio\n");
        }
        else
        {
            printf("tu signo es sagitario\n");
        }
    }

    else if (mes == 12)
    {
        if (dia <= 21)
        {
            printf("tu signo es sagitario\n");
        }
        else
        {
            printf("tu signo es capricornio\n");
        }
    }
    return 0;
    }