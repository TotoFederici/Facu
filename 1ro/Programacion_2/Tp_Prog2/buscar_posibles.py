from func_listas import *

# Constantes.
TIPO_MEDIO = 0
TIPO_IZQ = 1
TIPO_DER = 2

CERCANAS_L1 = 0
CERCANAS_L2 = 1
AMBAS = 2

ELEMENTO = 0
FRECUENCIA = 1

def palabras_cercanas(linea: str):
    '''
    Busca las palabras cercanas a el guion bajo en la frase
    si la frase es suficientemente larga, se toman dos palabras
    sino se toma solo una.
    '''
    
    palabras_por_linea = linea.split()
    indice_guion = palabras_por_linea.index('_')
    
    # Comienzo Frase.
    if (indice_guion == 0):
        
        if (len(palabras_por_linea) > 2):
            return (TIPO_IZQ, palabras_por_linea[indice_guion + 1], palabras_por_linea[indice_guion + 2])
        else:
            return (TIPO_IZQ, palabras_por_linea[indice_guion + 1], 0)
    
    # Final frase.
    if(indice_guion == len(palabras_por_linea) - 1):
        
        if (len(palabras_por_linea) > 2):
            return (TIPO_DER, palabras_por_linea[indice_guion - 1], palabras_por_linea[indice_guion - 2])
        else:
            return (TIPO_DER, palabras_por_linea[indice_guion - 1], 0)
        
    # Medio frase
    else:
        return (TIPO_MEDIO, palabras_por_linea[indice_guion - 1], palabras_por_linea[indice_guion + 1])
  
def palabras_posibles(ngramas: dict[tuple,list], cercanas: tuple):
    '''
    Se buscan coincidencias en los n-gramas, se guardan las coincidencias con las palabras cercanas al guion
    pal_cercana1 y pal_cercana2 en las listas posibles1 y posibles2 respectivamente
    si coinciden ambas se guarda en ambas.
    Se retorna una tupla con posibles1, posibles2 y ambas.
    '''
    
    tipo = cercanas[0]
    pal_cercana1 = cercanas[1]
    pal_cercana2 = cercanas[2]
    
    posibles1 = []
    posibles2 = []
    ambas = []
    
    for clave in ngramas.keys():
        palabra_izq = clave[0]
        palabra_der = clave[1]
        largo = len(ngramas[clave])
        
        for pos in range(largo):    
            if tipo == TIPO_MEDIO:
                if pal_cercana1 == palabra_izq:
                    if pal_cercana2 == ngramas[clave][pos][2]:
                        ambas.append(ngramas[clave][pos][1])
                    posibles1.append(ngramas[clave][pos][1])
            
                if pal_cercana2 == palabra_der:
                    posibles2.append(ngramas[clave][pos][-2])

            elif tipo == TIPO_DER:
                if pal_cercana2 == palabra_izq:
                    if pal_cercana1 == ngramas[clave][pos][1]:
                        ambas.append(ngramas[clave][pos][2])
                    posibles2.append(ngramas[clave][pos][2])
            
                if pal_cercana1 == palabra_izq:
                    posibles1.append(ngramas[clave][pos][1])
            
            else:
                if pal_cercana2 == palabra_der:
                    if pal_cercana1 == ngramas[clave][pos][-2]:
                        ambas.append(ngramas[clave][pos][-3])
                    posibles2.append(ngramas[clave][pos][-3])
            
                if (pal_cercana1 == palabra_der):
                    posibles1.append(ngramas[clave][pos][-2])
                    
    return (posibles1, posibles2, ambas)

def lista_posibles(ngramas: dict[tuple,list], cercanas: tuple):
    '''
    Se llama a la funcion palabras_posibles, y se retorna la lista
    que contiene la palabras con mas posibilidad de ser la que se busca
    '''
    
    posibles = palabras_posibles(ngramas, cercanas)
    
    if (posibles[AMBAS] != []):
        return posibles[AMBAS]
    
    intersec = interseccion(posibles[CERCANAS_L1], posibles[CERCANAS_L2])
    if ((intersec) != []):
        return intersec
    
    max_frecuencia_L1 = elemento_mas_frecuente(posibles[CERCANAS_L1])[FRECUENCIA]
    max_frecuencia_L2 = elemento_mas_frecuente(posibles[CERCANAS_L2])[FRECUENCIA]
    
    if (max_frecuencia_L1 >= max_frecuencia_L2):
        return posibles[CERCANAS_L1]
    return posibles[CERCANAS_L2]