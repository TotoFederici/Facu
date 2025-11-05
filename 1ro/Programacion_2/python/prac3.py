from random import *

#ej1

def posMult(l: list, n: int) -> list:
    '''
    la funcion toma como argumento una lista y un numero entero positivo
    y devuelve otra lista con los elementos en las posiciones multiplo
    de ese numero n
    '''
    k = []
    for i in range(0, len(l), n):
        k.append(l[i])
    return k

#ej2

def sumarLista(l: list) -> int:
    '''
    funcion auxiliar que suma todos los numeros de una lista
    '''
    suma = 0
    for i in l:
        suma += i
    return suma

def sumaAcum(l: list) -> list:
    '''
    la funcion toma una lista de numeros, y devuelve otra lista donde
    el n-esimo elemento es la suma de los primeros n elementos
    '''
    k = []
    for i in range(1, len(l)):
        k.append(sumarLista(l[:i]))
    return k

#ej3

def eliminar(l: list) -> list:
    '''
    la funcion elimina el primer y ultimo elemento de una lista
    '''
    return l[1:-1]

#ej4

def ordenar(l: list) -> bool:
    '''
    ordenar recibe com argumento una lista con numeros o strings(letras) de
    longitud 1, y verifica si esos numeros y strings(letras) estan ordenados,
    en caso de las letras, segun su codigo unicode - 97
    '''
    for i in range(len(l)):
        if type(l[i]) == str:
            l[i] = ord(l[i]) - 97

    i = 0
    k = len(l) - 2
    while i < k and l[i] < l[i + 1]:
        i +=1
    return l[i] < l[i + 1]

def test_ordenar():
    assert ordenar([-234, -40, "p", 52]) == True
    assert ordenar([123, 1, 12343, 12]) == False
    assert ordenar(["a", "b", "c"]) == True
    assert ordenar(["c", 15, "a", 0]) == False

#ej5

def duplicado(l: list) -> bool:
    '''
    la funcion recibe de argumento una lista 
    y verifica si la lista tiene algun elemento duplicado
    '''
    for i in range(len(l)):
        for j in l[:i] + l[i + 1:]:
            if l[i] == j:
                return True
    return False

def test_duplicado():
    assert duplicado([34,5,3,12,34]) == True
    assert duplicado([1,2,3,4,5,6]) == False
    assert duplicado([7]) == False
    assert duplicado([]) == False

#ej6

def eliminaDuplicados(l):
    '''
    la funcion elimina los elementos duplicados de una lista dada, 
    en caso de haberlos, solo deja uno de ellos
    ''' 
    l.sort()
    k = []
    
    for i in range(len(l)):
        if i == 0 or l[i] != l[i - 1]:
            k.append(l[i])
    return k
    
def test_eliminaDuplicados():
    assert eliminaDuplicados([]) == []
    assert eliminaDuplicados([1,2,3,4]) == [1,2,3,4]
    assert eliminaDuplicados([1,2,3,4,3,2,1]) == [1,2,3,4]

#ej7

def lenExclusivo(l: list) -> None:
    '''
    la funcion recibe una lista e imprime un mensaje diciendo
    la cantidad de elementos unicos que tiene esa lista
    '''
    n = len(eliminaDuplicados(l))
    print("tu lista tiene", n, "elementos distintos")
    
#ej8

def dicotomica(l: list, s: str) -> bool:
    l.sort()
    m = len(l) // 2
    if l == []:
        return False
    if l[m] < s:
        return dicotomica(l[m+1:], s)
    if l[m] > s:
        return dicotomica(l[:m], s)
    return True

#ej9

def letras(s: str) -> None:
    k = len(s) - 1
    for i in range(len(s)):
        print(s[k - i])

#ej10

def contar(s: str, c: str) -> int:
    veces = 0
    for i in s:
        if i == c:
            veces += 1
    return veces

#ej11

def vocales(s: str) -> None:
    a = contar(s, "a") + contar(s, "A")
    e = contar(s, "e") + contar(s, "E")
    i = contar(s, "i") + contar(s, "I")
    o = contar(s, "o") + contar(s, "O")
    u = contar(s, "u") + contar(s, "U")
    print("hay", a, "a's,", e, "e's,", i, "i's,", o, "o's y", u, "u's")
    
#ej13

#represento cartas de poker de esta manerta con tuplas
# (A, Cor) (7, Tre) (K, Dia)

palos = ["Cor" , "Dia" , "Tre" , "Pic"]
valorCartas = ["A",2,3,4,5,6,7,8,9,10,"J","Q","K"]

def baraja():
    mazo = []
    for i in palos:
        for n in valorCartas:
            mazo.append((n, i))            
    return mazo

def repartir(n):
    mano = []
    
    for i in range(n):
        mano.append(baraja()[randint(0,51)])
    return mano
    
def cartas(l):
    
    valores = []
    
    for i in l:
        if type(i[0]) == str:
            valores.append(ord(i[0]))
        else:
            valores.append(i[0])
            
    valores.sort()
    return valores

def poker(n):
    
    poker = False
    mano = repartir(n)
    print(mano)
    
    M = cartas(mano)
    
    repetidas = 1
    largo = len(M) - 1
    i = 0
    
    while repetidas < 4 and i < largo:
        if M[i] == M[i + 1]:
            repetidas += 1
            i += 1
        elif M[i] != M[i + 1]:
            repetidas = 1
            i += 1

    if repetidas == 4:
        poker = True

    if poker:
        print("POKER!!!")
        
#ej14

#represento el tiempo de esta forma 
# "(dias, horas, minutos, segundos)" con tuplas
a = (2, 6, 25, 47)
b = (2, 17, 50, 13)
#(5, 0, 16, 0)

def sumatiempo(t: tuple, s: tuple) -> tuple:
    segs = t[3] + s[3]
    min = t[2] + s[2]
    hora = t[1] + s[1]
    dias = t[0] + t[0]
    
    if segs >= 60:
        min += 1
        segs -= 60
    
    if min >= 60:
        hora += 1
        min -= 60
    
    if hora >= 24:
        dias += 1
        hora -= 24

    time = (dias, hora, min, segs)       
        
    return time

#ej15

#dias: (DIA, MES, AÑO) numeros enteros

def diasiguienteE(t: tuple) -> tuple:
    dia = t[0]
    mes = t[1]
    año = t[2]
    
    if dia >= 32 or dia <= 0:
        return "ese dia no existe"
    elif dia >= 31:
        if mes == 4 or mes == 6 or mes == 9 or mes == 11:
            return "ese dia no existe"
    elif dia >= 29 and mes == 2:
        return "ese dia no"
    elif mes >= 13 or mes <= 0:
        return "ese mes no existe"
    
    dia += 1    

    if dia == 29 and mes == 2:
        dia = 1
        mes += 1
    if dia == 31:
        if mes == 4 or mes == 6 or mes == 9 or mes == 11:
            dia = 1
            mes += 1
    if dia == 32 and not mes == 12:
        dia = 1
        mes += 1
    elif dia == 32 and mes == 12:
        dia = 1
        mes = 1
        año += 1
            
    return (dia, mes, año)