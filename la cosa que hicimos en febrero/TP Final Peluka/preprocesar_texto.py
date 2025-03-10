def preprocesar_texto(texto:list[str], m:int) -> tuple[tuple,dict]:
    """
    Realiza un preprocesamiento del texto, analizando la frecuencia y contexto de cada palabra.
    El parametro m define la amplitud del contexto a considerar alrededor de cada palabra.
    
    Retorna una tupla que contiene la palabra mas frecuente y un diccionario que asocia cada palabra del texto con 
    una lista que como primer elemento tiene la cantidad de apariciones de la palabra y los demas elementos son 
    tuplas que contienen las palabras adyacentes a izquierda y derecha en cada aparicion de esa palabra.
    """
    
    dicc_palabras = {}
    mas_frecuente = ("", 0)
    
    for linea in texto:
        lsp = linea.split()
        long = len(lsp)
        
        i = 0
        for palabra in lsp:
            mi = min(i+m+1, long)
            Mi = max(i-m, 0)
            
            if palabra in dicc_palabras:
                dicc_palabras[palabra].append((lsp[i+1:mi], lsp[Mi:i][::-1]))
                dicc_palabras[palabra][0] += 1
                if mas_frecuente[1] < dicc_palabras[palabra][0]:
                    mas_frecuente = (palabra, dicc_palabras[palabra][0])
                    
            else:
                dicc_palabras[palabra] = [1, (lsp[i+1:mi], lsp[Mi:i][::-1])]
                if mas_frecuente == ("", 0):
                    mas_frecuente = (palabra, dicc_palabras[palabra][0])
            i+=1
            
    return (mas_frecuente, dicc_palabras)