#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "usuario.h"

Usuario crear_usuario(char* nombre, int premium, int tiempoDeSuscripcion){
	Usuario usuario = malloc(sizeof(usuario));
	usuario->nombre = malloc(sizeof(char)*strlen(nombre));
	strcpy(usuario->nombre, nombre);
	usuario->premium = premium;
	usuario->tiempoDeSuscripcion = tiempoDeSuscripcion;
	return usuario;
}

Usuario copiar_usuario(Usuario usuario){
	return crear_usuario(usuario->nombre, usuario->premium, usuario->tiempoDeSuscripcion);
}

int comparar_suscripcion(Usuario u1, Usuario u2){
	if(u1->tiempoDeSuscripcion > u2->tiempoDeSuscripcion){
		return 1;
	} else if(u1->tiempoDeSuscripcion < u2->tiempoDeSuscripcion){
		return -1;
	} else {
		return 0;
	}
}

void destruir_usuario(Usuario usuario){
	free(usuario->nombre);
	free(usuario);
}

void imprimir_usuario(Usuario u1){
	printf("%s", u1->nombre);
}

unsigned hashear_usuario(Usuario u1){
	KRHash(u1->nombre);
}