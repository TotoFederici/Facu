# Constantes
IZQ = 0
DER = 1


def buscar_palabras(texto_preproc:dict, palabras_ref:list, lado:int) -> list[tuple]:
    """
    Busca los datos de las palabras de referencia en palabras_ref.
    Devuelve una lista de tuplas que contiene la posición de la palabra de referencia en palabras_ref, las palabras 
    adyacentes del lado indicado y la cantidad de apariciones de la palabra de referencia en el texto preprocesado.
    """
    
    palabras_encontradas = []
    i = 1
    for pref in palabras_ref:
        if pref in texto_preproc:
            cantidad_apariciones = texto_preproc[pref][0]
            cercanas = []
            for j in range(1, len(texto_preproc[pref])):
                if texto_preproc[pref][j][lado] != []:
                    cercanas.append(texto_preproc[pref][j][lado])

            palabras_encontradas.append((i, cercanas, cantidad_apariciones))
        i+=1

    return palabras_encontradas


def calcular_puntajes(palabras_encontradas:list):
    """
    Calcula el puntaje para cada una de las palabras en palabras_encontradas.
    """
    
    valores = {}
    for lado in (IZQ, DER):
        for tupla in palabras_encontradas[lado]:
            for lista_palabras in tupla[1]:
                i=0
                s = len(lista_palabras[0:tupla[0]])
                for palabra in lista_palabras:
                    if palabra in valores:
                        valores[palabra] += 1/(s*tupla[2])
                    else:
                        valores[palabra] = 1/(s*tupla[2])
                    i+=1
                    if i < tupla[0]:
                        s -= 1
                    else:
                        s += 1

    return valores