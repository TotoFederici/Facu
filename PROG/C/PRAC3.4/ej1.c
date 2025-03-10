#include <stdio.h>
#include <math.h>

struct punto {
        double x;
        double y;
};

char pos(struct punto p) {
    char cuad;

    if ((p.x == 0) && (p.y == 0)) {
        cuad = 'o';
    }
    else if ((p.x == 0) && (p.y != 0)) {
        cuad = 'y';
    }
    else if ((p.y == 0) && (p.x != 0)) {
        cuad = 'x';
    }
    else if ((p.x > 0) && (p.y > 0)) {
        cuad = '1';
    }
    else if ((p.x < 0) && (p.y > 0)) {
        cuad = '2';
    }
    else if ((p.x < 0) && (p.y < 0)) {
        cuad = '3';
    }
    else if ((p.x > 0) && (p.y < 0)) {
        cuad = '4';
    }
    return cuad;
}

double dist(struct punto p1, struct punto p2) {
    double distX = (p2.x - p1.x), distY = (p2.y - p1.y);
    double distancia = sqrt((pow(distX, 2)) + (pow(distY, 2)));
}

int main() {
    struct punto p1, p2;

    printf("ingrese dos numeros que representen las coordenadas x e y de un punto: ");
    scanf("%lf%lf", &p1.x, &p1.y);
    printf("ingrese otros dos numeros que representen las coordenadas x e y de un punto: ");
    scanf("%lf%lf", &p2.x, &p2.y);

    printf("el punto 1 esta en %c el punto 2 esta en %c\n", pos(p1), pos(p2));
    printf("y la distancia entre ellos es de %lf", dist(p1,p2));

    return 0;
}