#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *nombre;
  int prioridad;
} _Invitado;

typedef _Invitado* Invitado;

typedef struct _Nodo {
  Invitado invitado;
  struct _Nodo *sig, *ant;
} Nodo;

typedef Nodo* Lista;

typedef void (*FuncionVis)(Invitado);

Invitado crear_invitado(char* nombre, int prioridad) {
  Invitado invitado = malloc(sizeof(_Invitado));
  invitado->nombre = nombre;
  invitado->prioridad = prioridad;
  return invitado;
}

void destruir_invitado(Invitado invitado) {
  free(invitado->nombre);
  free(invitado);
}

void imprimir_invitado(Invitado invitado) {
  printf("%s, %d\n", invitado->nombre, invitado->prioridad);
}

void recorrer_lista(Lista listaDeInvitados, FuncionVis vis) {
  for (; listaDeInvitados != NULL; listaDeInvitados = listaDeInvitados->sig) {
    vis(listaDeInvitados->invitado);
  }
}

void destruir_lista(Lista listaDeInvitados) {
  Nodo *aux;
  while (listaDeInvitados != NULL) {
    aux = listaDeInvitados;
    listaDeInvitados = listaDeInvitados->sig;
    destruir_invitado(aux->invitado);
    free(aux);
  }
}

Lista agregar(Invitado invitado, Lista listaDeInvitados) {
  Nodo *nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->invitado = invitado;
  if (listaDeInvitados == NULL) {
    nuevoNodo->sig = NULL;
    nuevoNodo->ant = NULL;
    return nuevoNodo;
  }
  Nodo *temp = listaDeInvitados;
  Nodo *aux = NULL;
  for (; (temp != NULL) && (invitado->prioridad > temp->invitado->prioridad); aux = temp, temp = temp->sig);
  if (temp == listaDeInvitados) {
    nuevoNodo->sig = temp;
    nuevoNodo->ant = NULL;
    temp->ant = nuevoNodo;
    listaDeInvitados = nuevoNodo;
  } else if (temp == NULL) {
    nuevoNodo->ant = aux;
    nuevoNodo->sig = NULL;
    aux->sig = nuevoNodo;
  } else {
    nuevoNodo->sig = temp;
    nuevoNodo->ant = temp->ant;
    temp->ant->sig = nuevoNodo;
    temp->ant = nuevoNodo;
  }
  return listaDeInvitados;
}

Lista eliminar(Lista *listaDeInvitados, int prioridad) {
  Lista eliminados = NULL;
  if (*listaDeInvitados == NULL) {
    return eliminados;
  }
  Lista temp = *listaDeInvitados;
  for (; (temp != NULL) && (temp->invitado->prioridad != prioridad); temp = temp->sig);
  if (temp != NULL) {
    Lista aux = temp->ant;
    while ((temp != NULL) && (temp->invitado->prioridad == prioridad)) {
      eliminados = agregar(temp->invitado, eliminados);
      temp = temp->sig;
    }
    if (aux != NULL) {
      aux->sig = temp;
    } else {
      *listaDeInvitados = temp; 
    }
    if (temp != NULL) {
      temp->ant = aux;
    }
  }
  return eliminados;
}

int main() {
  Invitado invitados[10];
  invitados[0] = crear_invitado("Toto", 3);
  invitados[1] = crear_invitado("Lolen", 1);
  invitados[2] = crear_invitado("Peluka", 2);
  invitados[3] = crear_invitado("Papa",1);
  invitados[4] = crear_invitado("TomaMate", 3);
  invitados[5] = crear_invitado("Sato", 2);
  invitados[6] = crear_invitado("Fideo", 6);
  invitados[7] = crear_invitado("Mirko", 0);
  invitados[8] = crear_invitado("Tincho", 2);
  invitados[9] = crear_invitado("Valegen", 1);

  Lista lista = NULL;
  for (int i = 0; i < 10; i++) {
    lista = agregar(invitados[i], lista);
  }

  printf("Lista:\n");
  recorrer_lista(lista, (FuncionVis)imprimir_invitado);

  Lista eliminados3 = NULL;
  eliminados3 = eliminar(&lista, 3);

  printf("\nLista sin 3\n");
  recorrer_lista(lista, (FuncionVis)imprimir_invitado);
  printf("\nEliminados 3:\n");
  recorrer_lista(eliminados3, (FuncionVis)imprimir_invitado);

  Lista eliminados0 = NULL;
  eliminados0 = eliminar(&lista, 0);

  printf("\nLista sin 0\n");
  recorrer_lista(lista, (FuncionVis)imprimir_invitado);
  printf("\nEliminados 0:\n");
  recorrer_lista(eliminados0, (FuncionVis)imprimir_invitado);
  
  return 0;
}