#ifndef __AVL_H__
#define __AVL_H__

typedef struct _albo{
	void* dato;
	struct _albo *izq, *der;
	int altura;
}_avl;

typedef enum {
  AVL_RECORRIDO_IN,  /** Inorden */
  AVL_RECORRIDO_PRE, /** Preorden */
  AVL_RECORRIDO_POST /** Postorden */
} AVLRecorrido;

typedef void *(*FuncionCopia)(void *data);
typedef int (*FuncionComparadora)(void * data1, void * data2);
typedef void (*FuncionDestructora)(void *data);
typedef void (*FuncionVisitante)(void *data);
typedef void (*FuncionVisitanteExtra)(void *data, void *extra);

typedef _avl* Avl;

Avl avl_crear();

int max(int a, int b);

void avl_destruir(Avl raiz, FuncionDestructora destruir);

void avl_map(Avl raiz, AVLRecorrido rec, FuncionVisitante visita);

int avl_altura_nodo(Avl nodo);

int avl_altura_max_nodo_hijos(Avl nodo);

int avl_factor_balance(Avl nodo);

Avl avl_rotacion_simple_der(Avl nodo);

Avl avl_rotacion_simple_izq(Avl nodo);

Avl avl_balancear_nodo(Avl nodo);

Avl avl_insertar(Avl raiz, void* dato, FuncionComparadora comp, FuncionCopia copia);

Avl avl_eliminar(Avl raiz, void* dato, FuncionDestructora destruir, FuncionComparadora comp);

#endif