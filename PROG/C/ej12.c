#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct{
    float x;
    float y;
} punto;

punto medio(punto p1 , punto p2 ){
    punto medio;
    medio.x = (p1.x +p2.x)/2;
    medio.y =(p1.y +p2.y)/2;
    return medio; 
}

int main() {
    punto pt1;
    punto pt2;
    punto pt3;
    punto pt4;
    punto med1;
    punto med2;
    pt1.x = 4;
    pt1.y = 10;
    pt2.x = 0.36;
    pt2.y = 11.6;
    pt3.x = 0;
    pt3.y = 0;
    pt4.x = 7;
    pt4.y = 7;
    med1 = medio(pt1,pt2);
    med2 = medio(pt3,pt4);
    printf("medio entre pt1 y pt2: (%f,%f)\n", med1.x, med1.y);
    printf("medio entre pt3 y pt4: (%f,%f)\n", med2.x, med2.y);
    return 0;
}