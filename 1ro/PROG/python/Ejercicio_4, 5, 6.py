#la funcion toma 2 argumentos, un numero y el punto de partida de la suma, osea el 0
#la funcion suma el numero "n" y le resta 1, y se repite hasta llegar a 0
#cuando "n" llega al valor "fin" la funcion se detiene e imprime la suma total
def sumar(n, suma = 0, fin = 10):
    if n == fin:
        print(suma)
    else:
        sumar(n - 1, suma + n)

m = 100

sumar(m)