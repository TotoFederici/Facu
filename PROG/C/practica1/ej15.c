#include <stdio.h>

int maximo(int pri, int seg){
    if (pri > seg) {
        return pri;
    }
    else {
        return seg;
    }
}

int main() {
    int pri, seg, ter, cua, mayor;
    
    printf("ingrese 4 numeros enteros para calcular el mayor entre ellos: ");
    scanf("%d%d%d%d", &pri, &seg, &ter, &cua);
    
    mayor = maximo(maximo(pri, seg), maximo(ter, cua));

    printf("el maximo entre %d %d %d %d es %d\n", pri, seg, ter, cua, mayor);

    return 0;
}