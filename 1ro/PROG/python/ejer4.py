from random import *

#ej1 a)

def repeticionesA(l: list, e: any) -> int:
    '''
    recibe una lista, un elemento, y devuelve las ocurrencias del mismo 
    '''
    repeticiones = 0
    for x in l:
        if x == e:
            repeticiones += 1
    return repeticiones

def test_repeticionesA():
    assert repeticionesA([1, 2, 2, 3, "hola", "ok"], 2) == 2
    assert repeticionesA([], "no") == 0
    assert repeticionesA(["hola", "chau", "chau"], 4) == 0
    
#ej1 b)

def repeticionesB(l: list, e: any) -> int:
    '''
    recibe una lista, un elemento y devuelve la posicion de la primera ocurrencia del mismo
    '''
    i = 0
    largo = len(l)
    while i < largo and l[i] != e:
        i += 1
    if i == largo:
        print("el elemento no esta en la lista")
        return -1
    return i

def test_repeticionesB():
    assert repeticionesB([1, 2, 2, 3, "hola", "ok"], 2) == 1
    assert repeticionesB([], "no") == -1
    assert repeticionesB(["hola", "chau", "chau"], "hola") == 0

#ej1 c)

def repeticionesC(l: list, e: any) -> list:
    '''
    recibe una lista, un elemento y devuelve una lista con las posiciones de las
    ocurrencias del mismo
    '''
    i = 0
    posiciones = []
    largo = len(l)
    while i < largo:
        if l[i] == e:
            posiciones.append(i)
        i += 1
    return posiciones
    
def test_repeticionesC():
    assert repeticionesC([1, 2, 2, 3, "hola", "ok"], 2) == [1, 2]
    assert repeticionesC([], "no") == []
    assert repeticionesC(["hola", "chau", "chau"], "hola") == [0]

#ej2 a)b)

def maximo(l: list) -> tuple:
    '''
    recibe una lista con numeros y devuelve una tupla con el numero con mayor valor y la posicion del mismo
    '''
    if l == []:
        print("la lista esta vacia")
        return ()
    
    i = 0
    posMayor = 0
    mayor = l[0]
    largo = len(l)
    
    while i < largo:
        if l[i] > mayor:
            mayor = l[i]
            posMayor = i
        i += 1
    return (mayor, posMayor)

def test_maximo():
    assert maximo([7,4,9,2]) == (9, 2)
    assert maximo([0]) == (0, 0)
    assert maximo([]) == ()

#ej3

#....
        
#ej4

def asignacion(l: list) -> dict:
    '''
    la funcion recube una lista de tuplas de dos elementos,
    y crea un diccionario, siendo los primeros elementos de las tuplas
    las claves, y los segundos los valores dentro de una lista, 
    Si una clave esta repetida, agrega el valor a la lista
    '''
    d = {}
    claves = d.keys()
    for t in l:
        if t[0] in claves:
            d[t[0]] = d[t[0]] + [t[1]]
        else:
            d[t[0]] = [t[1]]
    return d

#ej5a

def aparicionesWord(s: str) -> dict:
    '''
    recibe un texto y crea un diccionario donde las claves son las palabras del texto
    y los valores son la cantidad de veces que aparece cada palabra
    '''
    d = {}
    pal = s.split()
    for p in pal:
        if p in d.keys():
            d[p] += 1
        else:
            d[p] = 1
    return d

#ej5b

def aparicionesChar(s: str) -> dict:
    '''
    recibe un texto y crea un diccionario donde las claves son los caracteres del texto
    y los valores son la cantidad de veces que aparece cada caracter
    '''
    d = {}
    for p in s:
        if p in d.keys():
            d[p] += 1
        else:
            d[p] = 1
    return d

#ej5c

def timba(x: int) -> dict:
    '''
    la funcion recibe un entero, que representa la cantidad de tiradas de dos dados
    y crea un diccionario con los numeros que pueden salir en los dados de clave, y los valores,
    la cantidad de veces que salio ese numero en los dados
    '''
    d = {}
    while x != 0:
        tirada = randint(1,6) + randint(1,6)
        if tirada in d.keys():
            d[tirada] += 1
        else:
            d[tirada] = 1
        x -= 1
    return d

#ej6
    
def longestWord(s: str) -> dict:
    '''
    recibe un texto y crea un diccionario siendo los caracteres del texto, las claves
    y a cada clave le asigna la palabra mas larga en la cual aparece el caracter
    '''
    d = {}
    for palabra in s.split():
        n = len(palabra)
        palabra = palabra.lower()
        for l in palabra:
            if (l not in d) or (len(d[l]) < n):
                d[l] = palabra
    return d

#ej7

com1 = {"toto":[9, 7.50, 10], "papa-pvp":[8, 6.50, 7], "lolen": [10, 8, 7.50]}
com2 = {"fideleff":[10, 10, 10], "peluka":[9, 8, 8.50], "ian": [1, 1, 1]}

def promedio(d: dict, n: str) -> int:
    '''
    la funcion recibe un diccionario con alumnos como clave, y sus notas en listas como valores y el nombre de un alumno
    devolvera el promedio de el alumno ingersado
    '''
    promedio = 0
    if n in d:
        for nota in d[n]:
            promedio += nota
        return promedio / len(d[n])
    else:
        return "el estudiante no esta registrado"
    
def mayorPromedio(d: dict) -> list:
    '''
    la funcion recibe un diccionario con alumnos como clave, y sus notas en listas como valores
    devuelve el nombre del alumno con mejor promedio y su promedio
    '''
    mayorprom = 0
    for clave in d.keys():
        prom = promedio(d, clave)
        if prom > mayorprom:
            mayorprom = prom
            estprom = clave
    return [estprom, mayorprom]

#ej8

sinonimos1 = {"gato": "michi", "amigo": "compadre", "dinero": "plata"}
sinonimos2 = {"computadora": "PC",  "raton": "mouse", "monitor": "pantalla"}
frase1 = "no sabes amigo , mi gato se perdio, estoy ofreciendo dinero a quien lo encuentre"
frase2 = "cuando compre mi computadora mi raton y mi monitor aun estaban baratos"

def sinonimos(s: str, d: dict) -> str:
    '''
    recibe un texto y un diccionario con palabras y sinonimos, si alguna palabra en el diccionario
    esta tambien en el texto, la reemplazara con un sinonimo en el texto, y devuelve el texto
    '''
    l = s.split()
    for p in l:
        if p in d:
            s = s.replace(p, d[p])
    return s

#ej9

precios = {"arroz": 600, "aceite": 1200, "pan": 300, "oreo": 350, "manteca": 200, "crema": 450}
carrito = {"arroz": 4, "aceite": 2, "pan": 3, "crema": 1}

def supermercado(d: dict, t: dict) -> float:
    '''
    la funcion recibe dos diccionarios, uno con los productos del supermercado como clave y su precio como valor
    y el otro recibe los productos que se van a comprar como clave y al cantidad como valor
    devuelve el monto total de la compra
    '''
    lista = t.keys()
    monto = 0
    for i in lista:
        if i in d:
            monto += d[i]*t[i]
    return monto
    
#ej10

def elimDuplicados(l: list) -> list:
    '''
    recibe una lista y elimina los elementos duplicados
    '''
    c = set(l)
    lSinDup = [i for i in c]
    return lSinDup
        
#ej11

def palabrasComun(s: str, t: str) -> set:
    '''
    recibe dos textos y devuelve las palabras en comun entre ellos
    '''
    s = s.lower()
    t = t.lower()
    palabrasDeS = s.split(" ,")
    palabrasDeT = t.split(" ,")
    conjS = set(palabrasDeS)
    conjT = set(palabrasDeT)
    return conjS & conjT

#ej12

def diferenciaSimetrica(s: set, t: set) -> set:
    '''
    calcula la diferencia simetrica entre dos conjuntos
    '''
    interseccionST = s & t
    unionST = s | t
    return unionST - interseccionST

#ej13

def natMenores(l: list) -> set:
    '''
    recibe una lista de numeros naturales y devuelve un conjunto con los numeros naturales
    anteriores al mayor de la lista yque no esten en la lista
    '''
    l.sort()
    maximo = l[-1]
    natAnteriores = []
    for i in range(1, maximo):
        if i not in l:
            natAnteriores.append(i)
    return natAnteriores

#ej14

grupo1 = {"juan": ["lunes", "jueves"], "pedro": ["lunes", "jueves"], "virginia": ["lunes", "jueves"]}

def reunion(d: dict) -> set:
    '''
    recibe un diccionario con personas como claves cuyos valores son listas con los dias en los que
    pueden asistir a la reunion
    devuelve un conjunto con los dias en que todos pueden asistir a la vez
    '''
    diasHabiles = {"lunes", "martes", "miercoles", "jueves", "viernes"}
    for persona in d:
        diasHabiles = diasHabiles.intersection(set(d[persona]))
    return diasHabiles