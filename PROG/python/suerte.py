from random import *

def dado():
    n = 0
    tiros = 0
    while n != 6:
        n = randint(1,6)
        tiros = tiros + 1
        print(n)
    print("sacaste un 6 en", tiros, "tiros!!")
    
def dadoUsuario():
    n = int(input("cuantas veces quiere tirar el dado? "))
    coincidencias = 0
    while n > 0:
        k = randint(1,6)
        l = randint(1,6)
        print(k, l)
        n = n - 1
        if k == l:
            coincidencias = coincidencias + 1
    print("los dados coincidieron", coincidencias, "veces")
    
def timba():
    n = int(input("cuantos veces queres tirar? "))
    pesos = 0
    dolares = 0
    while n > 0:
        k = randint(1,6)
        print("salio", k)
        n = n - 1
        if k == 6:
            pesos = pesos + 400
            print("ganaste 400 pesos!!")
        elif k == 3:
            dolares = dolares + 1
            print("ganaste 1 dolar!!")
        elif k == 2 or k == 4 or k == 5:
            pesos = pesos - 200
            print("perdiste 200 pesos")
    print("fin del juego, te quedaste con", pesos, "pesos y", dolares, "dolares!!!")
    return