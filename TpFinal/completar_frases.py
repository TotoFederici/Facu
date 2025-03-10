from func_listas import *
from buscar_posibles import *
from preprocesado import *

def predicciones(nombre: str):
    '''
    Itera sobre las frases y escribe en el archivo de salida la frase,
    reemplazando en '_' con la palabra que se obtiene de la prediccion
    '''
    
    try:
        frases = Frases(nombre)
    except:
        print("Advertencia: No se encontraron frases incompletas de la persona, ingrese un nombre valido")
        exit(0)
    
    entradas = Entradas(nombre)
    informacion = preprocesado(entradas, 3)
    ngramas = informacion[0]
    caso_nulo = informacion[1]
    frases_completas = open("./Salidas/{}.txt".format(nombre), 'w')
    
    for linea in frases:
        cercanas = palabras_cercanas(linea)
        posibles = lista_posibles(ngramas, cercanas)
        
        if (posibles != []):
            palabra = elemento_mas_frecuente(posibles)[ELEMENTO]
        else:
            palabra = caso_nulo
        
        linea_completa = linea.replace("_", palabra)
        frases_completas.write(linea_completa)
        
    frases_completas.close()