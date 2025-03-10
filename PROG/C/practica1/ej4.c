#include <stdio.h>

int main() {
    int temp;
    
    printf("a que temperatua esta el agua?: ");
    scanf("%d",&temp);
    
    if (temp <= 0) {
        printf("el agua esta en estado solido\n");
    }
    else if (temp <= 100) {
        printf("el agua esta en estado liquido\n");
    }
    else {
        printf("el agua esta en estado gaseoso\n");
    }   
    return 0;
    }