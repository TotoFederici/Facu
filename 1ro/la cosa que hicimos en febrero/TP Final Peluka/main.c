#include "filtrar_texto.c"

int main(int argc, char* argv[]){

    if(argc != 2){
        printf("(!!) La cantidad de argumentos ingresados no es correcta.\n");
        return -1;
    }

    filtrar_texto(argv[1]);
    ejecutar_python(argv[1]);

    return 0;
}