from func_listas import *
from buscar_posibles import *

def Entradas(nombre: str) -> list[str]:
    '''
    Carga las lineas del texto procesado por el programa en C.
    '''
    
    texto_Entradas = open("./Entradas/{}.txt".format(nombre), 'r')
    lineas_Entradas = texto_Entradas.readlines()
    texto_Entradas.close()
    
    return lineas_Entradas

def Frases(nombre: str) -> list[str]:
    '''
    Carga las frases incompletas.
    '''
    
    texto_Frases = open("./Frases/{}.txt".format(nombre), 'r')
    lineas_Frases = texto_Frases.readlines()
    texto_Frases.close()
    
    return lineas_Frases

def preprocesado(entradas: list[str], n: int):
    '''
    Generar n-gramas de palabras con "n" un numero natural dado mayor a tres,
    los n-gramas se guardan en un diccionario, cuyas claves son una tupla con
    la primera y ultima palabra de cada n-grama, de valor una lista con listas de los n-gramas
    que comienzan y terminan con dichas palabras.
    '''
    
    ngramas = {}
    caso_nulo = []
    
    for linea in entradas:
        
        palabras_por_linea = linea.split()
        
        # Se aprovecha este preprocesado para obtener el elemento mas frecuente de todo el texto
        # que sera usado en caso de no encontrar palabras posibles en las predicciones
        caso_nulo.append(elemento_mas_frecuente(palabras_por_linea)[ELEMENTO])
        long = len(palabras_por_linea)
        
        for pos in range(0,long-(n-1)):
            
            referencia = (palabras_por_linea[pos], palabras_por_linea[pos+(n-1)])
            if (referencia not in ngramas):
                ngramas[referencia] = [(palabras_por_linea[pos:pos+n])]
            else:
                ngramas[referencia].append(palabras_por_linea[pos:pos+n])
    
    palabra_mas_frecuente = elemento_mas_frecuente(caso_nulo)[ELEMENTO]
    return (ngramas, palabra_mas_frecuente)