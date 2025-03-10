#ifndef __USUARIO_H__
#define __USUARIO_H__

typedef struct _usuario{
	char* nombre;
	int premium;
	int tiempoDeSuscripcion;
} usuario;

typedef usuario* Usuario;

Usuario crear_usuario(char* nombre, int premium, int tiempoDeSuscripcion);

Usuario copiar_usuario(Usuario usuario);

int comparar_suscripcion(Usuario u1, Usuario u2);

void destruir_usuario(Usuario u1);

void imprimir_usuario(Usuario u1);

unsigned hashear_usuario(Usuario u1);

#endif