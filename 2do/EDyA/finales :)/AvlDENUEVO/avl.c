#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

Avl avl_crear(){
	return NULL;
}

void avl_destruir(Avl raiz, FuncionDestructora destruir){
	if(raiz == NULL){
		return;
	}
	avl_destruir(raiz->izq, destruir);
	avl_destruir(raiz->der, destruir);
	destruir(raiz->dato);
	free(raiz);
}

void avl_map(Avl raiz, AVLRecorrido rec, FuncionVisitante visita){
	if(raiz != NULL){
		if(rec == AVL_RECORRIDO_PRE){
			visita(raiz->dato);
			printf(": %d\n", avl_altura_nodo(raiz));
		}
		avl_map(raiz->izq, rec, visita);
		if(rec == AVL_RECORRIDO_IN){
			visita(raiz->dato);
			printf(": %d\n", avl_altura_nodo(raiz));
		}
		avl_map(raiz->der, rec, visita);
		if(rec == AVL_RECORRIDO_POST){
			visita(raiz->dato);
			printf(": %d\n", avl_altura_nodo(raiz));
		}
	}
}

int avl_altura_nodo(Avl nodo){
	return nodo == NULL ? -1 : nodo->altura;
}

int avl_altura_max_nodo_hijos(Avl nodo){
	return avl_altura_nodo(nodo->izq) > avl_altura_nodo(nodo->der) ? avl_altura_nodo(nodo->izq) : avl_altura_nodo(nodo->der);
}

int avl_factor_balance(Avl nodo){
	return avl_altura_nodo(nodo->izq) - avl_altura_nodo(nodo->der);
}

Avl avl_rotacion_simple_izq(Avl nodo){
	Avl der = nodo->der;
	if(der != NULL){
		nodo->der = der->izq;
		der->izq = nodo;
		nodo->altura = 1 + avl_altura_max_nodo_hijos(nodo);
		der->altura = 1 + avl_altura_max_nodo_hijos(der);
		return der;
	}
}

Avl avl_rotacion_simple_der(Avl nodo){
	Avl izq = nodo->izq;
	if(izq != NULL){
		nodo->izq = izq->der;
		izq->der = nodo;
		nodo->altura = 1 + avl_altura_max_nodo_hijos(nodo);
		izq->altura = 1 + avl_altura_max_nodo_hijos(izq);
		return izq;
	}
}

Avl avl_balancear_nodo(Avl nodo){
	if(nodo != NULL){

		int factor = avl_factor_balance(nodo);

		if(factor == 2){
			if(avl_factor_balance(nodo->izq) == -1){
				nodo->izq = avl_rotacion_simple_izq(nodo->izq);
			}
			nodo = avl_rotacion_simple_der(nodo);
		}

		if(factor == -2){
			if(avl_factor_balance(nodo->der) == 1){
				nodo->der = avl_rotacion_simple_der(nodo->der);
			}
			nodo = avl_rotacion_simple_izq(nodo);
		}
	}
	return nodo;
}

Avl avl_insertar(Avl raiz, void* dato, FuncionComparadora comp, FuncionCopia copia){
	if(raiz == NULL){
		Avl nuevoNodo = malloc(sizeof(_avl));
		nuevoNodo->altura = 0;
		nuevoNodo->izq = NULL;
		nuevoNodo->der = NULL;
		nuevoNodo->dato = copia(dato);
		return nuevoNodo;
	}
	if(comp(dato,raiz->dato) < 0){
		raiz->izq = avl_insertar(raiz->izq, dato, comp, copia);
		raiz = avl_balancear_nodo(raiz);
		raiz->altura = 1 + avl_altura_max_nodo_hijos(raiz);
	}
	else{
		raiz->der = avl_insertar(raiz->der, dato, comp, copia);
		raiz = avl_balancear_nodo(raiz);	
		raiz->altura = 1 + avl_altura_max_nodo_hijos(raiz);
	}
	return raiz;
}

Avl avl_eliminar(Avl raiz, void* dato, FuncionDestructora destruir, FuncionComparadora comp){
	if(raiz == NULL){
		return NULL;
	}	
	if(comp(dato, raiz->dato) == 0){
		Avl swap;
		if(raiz->izq == NULL || raiz->der == NULL){
			swap = raiz->izq ? raiz->izq : raiz->der;
			destruir(raiz->dato);
			free(raiz);
			raiz = swap;
		} else {
			swap = raiz->der;
			for(; swap->izq != NULL; swap = swap->izq);
			dato = raiz->dato;
			raiz->dato = swap->dato;
			swap->dato = dato;
			raiz->der = avl_eliminar(raiz->der, dato, destruir, comp);
		}
	}
	else if(comp(dato, raiz->dato) < 0){
		raiz->izq = avl_eliminar(raiz->izq, dato, destruir, comp);
		raiz = avl_balancear_nodo(raiz);
		raiz->altura = 1 + avl_altura_max_nodo_hijos(raiz);
	}
	else{
		raiz->der = avl_eliminar(raiz->der, dato, destruir, comp);
		raiz = avl_balancear_nodo(raiz);
		raiz->altura = 1 + avl_altura_max_nodo_hijos(raiz);
	}
	return raiz;
}
