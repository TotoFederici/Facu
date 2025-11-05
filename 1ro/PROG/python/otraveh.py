from math import *
from random import *

def posicionMultiplo(l: list, n: int) -> list:
    largo = len(l)
    resultado = []
    for i in range(0,largo,n):
        resultado.append(l[i])
    return resultado

def test_posicionMultiplo():
    l1 = [1,2,3,4,5,6,7]
    l2 = ["hola", "adioh", "toto", "locura", "integrales", "teorema", "chilli"]
    l3 = [3,-3,2,-2,1,-1,0]
    assert posicionMultiplo(l1,2) == [1,3,5,7]
    assert posicionMultiplo(l2,6) == ["hola", "chilli"]
    assert posicionMultiplo(l3,1) == l3
    
def sumaAcum(l: list) -> list:
    resultado = []
    sumaActual = 0
    for i in l:
        sumaActual += i
        resultado.append(sumaActual)
    return resultado

def test_sumaAcum():
    l1 = [1,2,3,4]
    l2 = [31,-4,-25,0,2]
    l3 = [pi,e]
    assert sumaAcum(l1) == [1,3,6,10]
    assert sumaAcum(l2) == [31,27,2,2,4]
    assert sumaAcum(l3) == [pi, pi+e]
    
def elimina(l: list) -> list: 
    return l[1:len(l)-1]

def ordenado(l: list) -> list:
    elementoActual = l[0]
    i = 1
    while (i < len(l)) and (elementoActual <= l[i]):
        elementoActual = l[i]
        i += 1
    return i == len(l)

def test_ordenado():
    l1 = [1,2,3,4,5,6]
    l2 = [1,4,8,8,3]
    l3 = ["hola", "chau", "zapallo"]
    assert ordenado(l1) == True
    assert ordenado(l2) == False
    assert ordenado(l3) == False

def sinonimos(s: str, d: dict) -> str:
    for i in d:
        if i in s:
            s = s.replace(i,d[i][randint(0,(len(d[i])-1))])
    return s

texto = "tienes una don innato para resolver ecuaciones diferenciales. Su capacidad para abordar y encontrar soluciones a problemas matemáticos desafiantes es asombrosa, haciendo que esta tarea parezca casi instintiva. Su destreza matemática es verdaderamente excepcional"

innato = ["inherente", "congénito", "intrínseco", "natural", "heredado"]
ecuaciones = ["fórmulas", "expresiones matemáticas", "cálculos", "problemas matemáticos", "ecuaciones algebraicas"]
capacidad = ["aptitud", "habilidad", "destreza", "competencia", "potencial"]
soluciones = ["respuestas", "alternativas", "medidas", "remedios", "opciones"]
problemas = ["dificultades", "desafíos", "contratiempos", "cuestiones", "obstáculos"]
matematicos = ["calculistas", "numéricos", "geómetras", "aritméticos", "analíticos"]
asombrosa = ["sorprendente", "asombrosa", "impresionante", "maravillosa", "extraordinaria"]
tarea = ["labores", "deberes", "ocupación", "trabajo", "obligación"]
destreza = ["habilidad", "pericia", "maestría", "competencia", "destrezamiento"]

sinonimos1 = {"innato":innato, "ecuaciones":ecuaciones, "capacidad":capacidad, "soluciones":soluciones, "problemas":problemas, "matematicos":matematicos, "asombrosa":asombrosa, "tarea":tarea, "destreza":destreza}

sinonimos(texto,sinonimos1)