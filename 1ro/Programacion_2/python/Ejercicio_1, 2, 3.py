#EJERCICIO 1, 2 y 3

n = 50 #numero inicial, importante no ingresar numeros impares, ni negativos

ParesBuscados = 10 

#la funcion toma la variable "n" de valor 2 y lo imprime
#la parte recursiva de la funcion, suma 2 a "n" y suma 1 al contador
#la funcion termina cuando el contador llega al numero de pares buscados
def pares(n, contador = 0):
    if contador == ParesBuscados:
        print("esos son los", ParesBuscados, "primeros pares a partir de", n - (ParesBuscados * 2))
    else:
        print(n)

        pares(n + 2, contador + 1)
    

pares(n, 0)

