#include <stdio.h>
#include <string.h>
#include <ctype.h>

int palinpal(char p1[], char p2[]) {
    int largo1 = strlen(p1), largo2 = (strlen(p2));
    int pos,res = 0;
    for (int i = 0,j = 0;((i < largo1) && (j < largo2));i++) {
        if (p1[i] == p2[j]) {
            int k = i;
            while ((p1[k] == p2[j]) && (k < largo1)) {
                k++, j++;
            }
        if (j == largo2) {
            res = 1;
            }
        else {
            j = 0;
            }
        }
    }    
    return res;
    }        
        /* if (p2[j] == p1[i]) {
            j++;
            pos++;
        }
        else if (p2[j] != p1[i]) {
            j = 0;
            pos = 0;
            if (p2[j] == p1[i]) {
                j++;
            }
        }
    } */
int main() {
    char p1[100], p2[] = {"jajaja mundo"};

    printf("frase: %s\n", p2);
    printf("ingresa un texto: ");
    scanf("%[^\n]",p1);

    if (palinpal(p2,p1) == 1) {
        printf("tu texto esta contenido en la frase\n");
    }
    else {
        printf("tu texto no esta contenido en la frase\n");
    }
    return 0;
}