#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* nombre;
    char* numero;
    unsigned int edad;
} contacto;

typedef struct {
    contacto** contactos;
    unsigned int* cantidad;
} agenda;

contacto* crea_contacto() {
    contacto* nuevo = malloc(sizeof(contacto));

    char* name = malloc(sizeof(char)*50);
    char* number = malloc(sizeof(char)*20);
    unsigned int age = 23;

    printf("ingresa tu nombre: \n");
    scanf("%s", name);
    getchar(); //ilegalisimo
    printf("ingresa tu numero: \n");
    scanf("%s", number);
    getchar(); //ilegalisimo
    printf("ingresa tu edad: \n");
    scanf("%d", &age);
    getchar();

    nuevo->nombre = name;
    nuevo->numero = number;
    nuevo->edad = age;

    free(nuevo->nombre), free(nuevo->numero);
    return nuevo;
}

agenda* crea_agenda() {
    agenda* ag = malloc(sizeof(agenda));
    ag->cantidad = malloc(sizeof(unsigned int));
    *ag->cantidad = 0;
    ag->contactos = malloc(sizeof(contacto*));
    return ag;
}

void actualizar_edad(contacto* nuevo) {
    unsigned int age;
    printf("ingrsa tu edad actual: ");
    scanf("%d", &age);
    nuevo->edad = age;
}

void alta_contacto(agenda* agenda) {
    contacto* nuevo = crea_contacto();
    (agenda->contactos)[*agenda->cantidad] = nuevo;
    *agenda->cantidad++;
}

int main() {
    contacto* a = crea_contacto();
    printf("%s, %s, %d", a->nombre, a->numero, a->edad);
    //printf("%d\n%d\n", ((ag1->contactos)[0])->edad, ((ag1->contactos)[1])->edad);
    return 0;
}