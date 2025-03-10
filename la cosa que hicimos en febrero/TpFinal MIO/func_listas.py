def interseccion(lista1: list, lista2: list):
    '''
    Realiza la interseccion entre dos listas
    '''
    
    resultado = []
    # Pongo los elementos en un conjunto para solo hacer un recuento de los elementos unicos
    conj = set(lista2)
    
    for elemento in lista1:
        if elemento in conj:
            resultado.append(elemento)
    return resultado

def elemento_mas_frecuente(lista: list):
    '''
    Busca el elemento mas frecuente en una lista
    Retorna el elemento mas frecuente y su frecuencia
    '''
    max_frecuencia = 0
    elemento_mas_frecuente = None
    
    # En caso de haber varios elementos con la misma frecuencia,
    # se retorna el primer elemento en aparecer en la lista
    for elemento in lista:
        frecuencia_actual = lista.count(elemento)
        
        if frecuencia_actual > max_frecuencia:
            max_frecuencia = frecuencia_actual
            elemento_mas_frecuente = elemento
            
    return (elemento_mas_frecuente, max_frecuencia)