# include <stdio.h>
void nullify ( int* a ) {
a = NULL ;
}
int main () {
int a [67];
a [0] = 123;
printf ("%d\n", a [0]) ;
nullify ( a ) ;
printf ("%d\n", a [0]) ;
return 0;
}