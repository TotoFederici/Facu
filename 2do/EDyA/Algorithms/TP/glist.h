#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef void *(*FuncionCopia)(void *dato);

typedef struct _GNode{
	void *dato;
	struct _GNode *sig;
} GNode;

typedef GNode *GList;

typedef GList GSList;

GList glist_crear();

void glist_destruir(GList lista, FuncionDestructora destruir);

int glist_esta_vacia(GList lista);

void glist_recorrer(GList lista, FuncionVisitante visita);

GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copia);

#endif