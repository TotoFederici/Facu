#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//------------------------------------------------------

/* int main () {
    int* punt ;
    int x = 7, y = 5;
    
    punt = &x;
    *punt = 4;
    
    printf (" %d %d\n", x , y );
    return 0;
} */
//x = 7, punt guarda la direccion de x y luego donde apunta punt se le asigna 4 lo cual cambia el valor de x
//por pantalla se imprime 4 5

//------------------------------------------------------

/* int main () {
    int* punt;
    int x = 7, y = 5;
    
    punt = &x;
    x = 4;
    punt = &y;
    
    printf("%d %d\n",*punt,x); 
    return 0; 
} */
//x = 7, y = 5, punt guarda la direccion de x, cambia el valor de x a 4 y a punt se le asigna la direccion de y
//por pantalla se imprime 5 4

//------------------------------------------------------

/* int main () {
    int *punt ,i;
    int x[] = {1 ,2 ,3 ,4 ,5};

    punt = x;
    *punt = 9;
    for (i = 0; i < 5; i++)
        printf ("%d,", x[i]);
    return 0;
} */
//crea un puntero entero, y un array de 5 enteros, guarda el array en el puntero y a donde el puntero apunta le asigna 9
//es hace que se modifique el primer valor del array osea x[0], resultando {9,2,3,4,5}

//------------------------------------------------------

/* int main () {
    int* punt, i;
    int x[] = {1 ,2 ,3 ,4 ,5};

    punt = x;
    *(punt + 2) = 9;
    *(x + 3) = 7;
    punt[1] = 11;
    for (i = 0; i < 5; i++)
        printf ("%d,", *(punt + i));
    return 0;
} */
//crea un puntero entero, y un array de 5 enteros, guarda el array en el puntero
//luego asigna un 9 dos lugares mas desde donde esta el puntero en x[0]
//luego desde donde comienza el array se mueve tres lugares y asigna un 7
//finalemnte en la posicion 1 desde el inicio del puntero asigna un 11
//la salida es 1,11,9,7,5

//------------------------------------------------------

int main () {
    int* punt ,i;
    int x[5] = {1 ,2 ,3 ,4 ,5};

    punt = &x[0] + 3;
    *(punt - 2) = 9;
    punt--;
    *(punt) = 7;
    punt[1] = 11;
    punt = x;
 
    for (i = 0; i < 5; i++)
    printf("%d,",punt[i]) ;
 
    return 0;
}
//

//------------------------------------------------------



//------------------------------------------------------



//------------------------------------------------------



//------------------------------------------------------