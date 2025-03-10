#include <stdio.h>
#define TAM_BUFFER 255

// Crea un archivo en el cual escribe los nombres de los textos que se encuentran en la carpenta 
// correspondiente al nombre ingresado
void buscar_archivos(char* nombre){
    char comando[TAM_BUFFER], archivo[TAM_BUFFER];
    sprintf(comando, "cd Textos/%s && ls > ../../archivos.txt", nombre);

    FILE *nombres_archivos = fopen("./archivos.txt", "w+");
    system(comando);

    if(fscanf(nombres_archivos, "%s", archivo) == EOF){
        printf("Error: no se encotraron textos con ese nombre.\n"
        "Por favor revise el nombre ingresado o la carpeta donde se encuentran los textos.\n");
        fclose(nombres_archivos);
        exit(0);
    }

    fclose(nombres_archivos);
}


// Ejecuta la parte del programa en python
void ejecutar_python(char* nombre){
    char comando[TAM_BUFFER];
    sprintf(comando, "python3 main.py %s", nombre);

    system(comando);
}