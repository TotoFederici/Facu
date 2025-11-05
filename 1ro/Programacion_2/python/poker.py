from random import *

#represento cartas de poker de esta manerta con tuplas
# (A, Cor) (7, Tre) (K, Dia)

palos = ["Cor" , "Dia" , "Tre" , "Pic"]
valorCartas = ["A",2,3,4,5,6,7,8,9,10,"J","Q","K"]

def baraja() -> list:
    '''
    esta funcion no recibe argumentos
    solo genera una lista con tuplas, donde cada tupla contiene dos elementos
    el primero, el valor de la carta, y el segundo el palo o figura
    '''
    mazo = []
    for i in palos:
        for n in valorCartas:
            mazo.append((n, i))            
    return mazo

def repartir(n: int) -> list:
    '''
    esta funcion agarra n elementos de la lista baraja para formar una mano de poker, de forma aleatoria
    esto usando como indice para extraer elementos de la lista, una funcion que genera
    numeros aleatorios entre 0 y 51, que son los indices de cada carta
    '''
    mano = []
    
    for i in range(n):
        mano.append(baraja()[randint(0,51)])
    return mano
    
def cartas(l: list) -> list:
    '''
    esta funcion recibe una lista con cartas(tuplas) y toma el valor de cada carta
    (primer elemento de cada tupla) y lo pone en una nueva lista, en caso de ser letras
    como los ases (A), o las cartas J Q K, se usa su unicode, con la funcion ord
    al final antes de devolver la lista, se usa la funcion sort para que la lista este ordenada
    '''
    valores = []
    
    for i in l:
        if type(i[0]) == str:
            valores.append(ord(i[0]))
        else:
            valores.append(i[0])
            
    valores.sort()
    return valores

def poker(n = 5):
    '''
    funcion que inicia el juego de poker, utilizando las funciones anteriores
    se reparte una mano de n cartas y se muestran al jugador, si el jugador tiene
    al menos 4 cartas con el mismo valor, es un POKER
    '''
    poker = False
    mano = repartir(n)
    print(mano)
    
    M = cartas(mano)  #llamo M a la lista con los valores de cartas de la mano del jugador, ordenados
     
    repetidas = 1
    largo = len(M) - 1
    i = 0
    
    while repetidas < 4 and i < largo:   #uso este bucle para iterar sobre la lsita M
        if M[i] == M[i + 1]:             #y asi ver si hay al menos 4 numeros iguales
            repetidas += 1               #en tal caso, equivaldria a que el jugador
            i += 1                       #tiene un poker en la mano
        elif M[i] != M[i + 1]:
            repetidas = 1
            i += 1

    if repetidas == 4:
        poker = True

    if poker:
        print("POKER!!!")