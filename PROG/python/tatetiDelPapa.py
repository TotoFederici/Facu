def Tablero(a):
    '''
    Tablero2 : List(List) -> None
    Dibuja el tablero a partir del arreglo
    '''
    for i in a:
        line = ""
        for j in i:
            if a.index(i) < 1 or j == "O" or j == "X":
                line += j + "  | "
            else:
                line += j + " | "
        print(line)
        print("-----"*len(a))

def create_list(size: int) -> list:
    return [[str(x) for x in range(((y+1)*size-size), size*(y+1))] for y in range(size)]

def Append_all(a):
    '''
    Append_all: List(List) -> List
    Toma una arreglo de dos dimensiones, luego devuelve el arreglo original de posiciones
    '''
    b = create_list(len(a))
    for i in a:
        b = b + i
    return b

def Change(a, P1):

    '''
    Change : List(List) Bool -> None
    Toma la lista y una bandera de jugador, luego modifica esta con el valor ingresado
    '''

    Tablero(a)
    if P1:
        inp = input("ingrese la O en pos:")
    else:
        inp = input("ingrese la X en pos:")

    if inp not in Append_all(a):
        print("ingrese un valor valido")
        Change(a, P1)
    else:
        Tablero(Validate(a, inp, P1))

def validate2(a, inp):
    for i in a:
        for j in i:
            if inp == j:
                a[a.index(i)][i.index(j)] = "O"
                return a

def Validate(a, inp, P1):

    '''
    Validate : List(List) Str Bool -> Str
    Toma un input representando la posicion, una lista y un jugador.
    Luego devuelve una "O" o "X" en la posicion y dependiendo del jugador
    '''

    for i in range(len(a)):
        for j in range(len(a[i])):
            if inp == a[i][j]:
                if P1:
                    a[i][j] = "O"
                else:
                    a[i][j] = "X"
                return a

def Game(size):

    '''
    Game : None -> None
    Corre el tateti. 
    Inicializa variables y llama a las funciones 
    '''

    a= create_list(size) #Lista de posiciones
    P1 = True                                           #Representa si el player es o no el 1
    Turn = 1                                            #Turno actual del juego
    print("TATETI")
    while Turn <= size**2:
        Change(a, P1)
        Turn += 1
        if Turn%2 == 0:                                 #Dependiendo de la paridad del turno, determina a que player le toca
            P1 = False
        else:
            P1 = True
        if Turn >= (size*2)-1:                                   #Comienza a preguntarse si hay un ganador a partir del turno 5
            if Check(a):
                print("win")
                return

def is_row_comp(r: list) -> bool:

    '''
    is_row_comp : list -> bool
    Toma una lista y determina si esta tiene solo "X" o "O" en ella
    '''

    for j in r:
        if not(j == 'X' or j == "O"):
            return False
    return True
    
def Check_line(a: list) -> bool:

    '''
    Check_line : list(list) -> bool
    Toma una lista y determina si es una lista ganadora o no
    '''

    for i in a:
        if is_row_comp(i):                 #si la linea no esta completa con "O" o "X" es false
            return is_repeated(i)          #devuelve true se estan repetidas, es decir, si se gano
    return False
    
def is_repeated(r):

    '''
    is_repreated : List -> bool
    Toma una lista y determina si la "O" o "X" estan repetidas 3 veces
    '''

    o = 0
    x = 0
    for i in r:
        if i == "O":
            o = o + 1
        else:
            x = x + 1
    if x == len(r) or o == len(r):
        return True 

def Permute(a):

    '''
    Permute: List(List) -> List(List)
    Toma una lista de dos dimensiones luego devueve la misma, pero conformada por los primeros elementos de estas
    Permute([[1, 2, 3], [4, 5, 6], [7, 8, 9]]) == [[1, 4, 7], [2, 5, 8] [3, 6, 9]]
    '''

    b = []
    for i in range(len(a)):
        b.append([x[i] for x in a if x[i]])
    return b

def Check(a):

    '''
    Check: List(List) -> bool
    Toma una lista de dos dimensiones luego checkea si algunas de las combinaciones necesarias para ganar, es el caso.
    Sea el dicho, devuelve true
    '''

    if Check_line(a):
        return Check_line(a)
    if Check_line(Permute(a)):
        return Check_line(Permute(a))
    if check_dia(a):
        return check_dia(a)

def check_dia(a):

    '''
    check_dia : List(List) -> bool
    Toma una lista de dos dimensiones, luego comprueba si hay figuras "O" o "X" en diagonal repetidas llamando is_repeated
    Sea ese el caso devuelve true, caso contrario false
    '''

    d1 = []
    d2 = []
    for i in range(len(a)):
        d1.append(a[i][i])
        d2.append(a[i][(len(a)-1)-i])
    if is_row_comp(d1):   #si la linea no esta completa con O o X es false
            return is_repeated(d1)
    if is_row_comp(d2):   #si la linea no esta completa con O o X es false
            return is_repeated(d2)
    return False
    

Game(10)


