from math import sqrt

lis = [1, 4, 5]
e = 1

def buscar(l, e):
    k = len(l) - 1
    i = 0
    while (i < k) and not (l[i] == e):
        i += 1
    return l[i] == e

buscar(lis, 9)

#ej2 y 3

def domino(n):
    for x in range(0, n+1):
        for m in range(x, n+1):
            print(x, m)

#ej4

def factorial(n: int) -> int:
    if n < 0:
        return "no existe el factorial de un numero negativo"
    
    elif n == 0:
        return 1

    else:
        x = 1
        factorial = 1
        while x <= n:
            factorial = factorial * x
            x = x + 1
            
        return factorial  

def userFactorial():
    m = int(input("cuando factoriales quiere calcular? "))
    if m <= 0:
        print("no quiere calcular ningun factorial")
    
    else:
        while m > 0:
            x = int(input("ingrese un numero "))

            m = m - 1

            print("el factorial de", x, "es", factorial(x))
       
        print("fin del proceso")

#ej5

# Representamos temperaturas mediante n ú meros enteros
# farCel : Int -> Int
# El par á metro representa una temperatura en Fahrenheit y ,
# se retorna su equivalente en Celsius .
# entrada : 32 , salida : 0
# entrada : 212 , salida : 100
# entrada : -40 , salida : -40

def farCel (f: int) -> float:
    return (f -32) *5/9

def tabla120F():
    for f in range(0, 121, 10):
        print(f, "grados Fahrenheit equivalen a", round(farCel(f), 2), "grados Celsius")

#ej6

#tringulares: int -> int
#la fincion recibe un numero natural n y calcula todos los numeros tringulares hasta n

def triang(n: int):
    for x in range(1, n+1):
        print((x * (x+1)) // 2)

#ej7

def pedirPositivo():
    x = int(input("ingrese un numero positivo: "))

    while x <= 0:
        print("eso no es un numero positivo")
        x = int(input("ingrese un numero positivo "))
    
    print("gracias")

#ej8

def ingresarnota():
    suma = 0
    contador = 0 
    nota = 0
    a = "si"
    while a == "si":
        nota = int(input("ingresar nota: "))
        suma = suma+nota
        contador += 1
        a = input("queres ingresar mas notas? si o no: ")
    print("el promedio es de", suma / contador)

#ej9

def enteros():
    x = int(input("ingrese un numero entero. "))
    
    y = int(input("ingrese otro numero entero. "))

    while y <= x:
        y = int(input("ingrese otro numero entero, mayor que el primero. "))

    print(x, y)
    
#ej10

#con for:

def multiplos1(x: int, y: int):
    for n in range(x, y, x):
        print(n)

#con while:

def multiplos2(x: int, y: int):
    k = x
    while x < y:
        print(x)
        x = x + k

#ej11

def contraseña():
    contraseña = "Hormiga"  
    intentos = 5
    c = input("ingrese la contraseña. ")   

    while c != contraseña and not intentos < 0: 
        intentos = intentos - 1
        c = input("contraseña incorrecta, intente otra vez. ")
        
    return c == contraseña

#ej12    

def esPrimo(n: int) -> bool:
    m = 2
    while n % m != 0 and not m == n:
        m = m + 1
    return m == n

def esPrimo2(n:int) -> bool:
    res = True
    for i in range(2, n):
        if n % i == 0:
            res = False
    return res
        
    
def primosMenoresFor(numero):
    for i in range(2, numero + 1):
        if esPrimo(i):
            print(i)
            
#ej13

def esPotDe2(n):
    m = 1
    while n != 2**m and n > 2**m:
        m = m + 1
    return n == 2**m

def sumaPot(n, m):
    suma = 0
    for i in range(n, m + 1):
        if esPotDe2(i):
            suma = suma + i
    return suma