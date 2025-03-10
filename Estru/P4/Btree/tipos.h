#ifndef TIPOS_H
#define TIPOS_H

typedef void (*DestroyFunction)(void *data);
typedef void *(*CopyFunction)(void *data);
typedef void (*VisitorFunction)(void *data);
typedef void (*ExtraVisitorFunction) (int dato, void *extra);
typedef void (*VisitorFunctionInt)(int dato);

#endif /* TIPOS_H */