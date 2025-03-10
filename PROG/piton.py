from random import *


""" def votante():
    edad = int(input("Ingresa tu edad: "))
    if edad <= 0:
        print("sos pelotudo")
    elif edad < 18:
        print("Faltan", 18-edad, "años para votar.")
    else:
        print("Podes votar!!!") """

def mayor(l):
    if l == []:
        print("la lista esta vacia.")
    else:
        mayor = l[0]
        for i in l:
            if i > mayor:
                mayor = i
    return mayor

def mayor2(l):
    if len(l) < 2:
        print("no hay elementos suficientes para buscar")
    else:
        mayor = l[0]
        segundo = l[0]
        for i in l:
            if i > mayor:
                segundo = mayor
                mayor = i
            elif i > segundo and i != mayor:
                segundo = i
    print(segundo)
    return segundo

def nMayor(l, n):
    if len(l) < n:
        print("no hay elementos suficientes para buscar")
    else:
        mayor = l[0]
        temp = l[1]
        while n > 1:
            for i in l:
                if i > mayor:
                    temp = mayor
                    mayor = i
                elif i > temp and i != mayor:
                    temp = i
            mayor = temp
            n -= 1
    print(mayor)
    return mayor

l = [9,4,5,6,8,1]
l2 = [1,2,3,4,5,6,7]
nMayor(l, 4)