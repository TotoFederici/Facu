def palabras_de_referencia(frase:str, n:int):
    """
    Devuelve un entorno de palabras alrededor del '_'.
    Si es posible, toma n palabras hacia cada lado. En caso de que no haya n palabras hacia uno de los lados toma las
    que faltan del otro lado. En caso de que no haya suficientes toma todas las palabras de la frase.
    """
    
    fsp = frase.split()
    long = len(fsp)
    
    p = fsp.index('_')
    indice_izq = p
    indice_der = p
    faltan = 2*n
    
    while indice_izq > 0 and indice_der < long-1 and faltan > 0:
        indice_izq -= 1
        indice_der += 1
        faltan -= 2
            
    if indice_izq == 0 and faltan > 0:
        while indice_der <= long and faltan > 0:
            indice_der+=1
            faltan-=1
            
    if indice_der == long-1 and faltan > 0:
        while indice_izq > 0 and faltan > 0:
            indice_izq-=1
            faltan-=1
    
    palabras_izq = fsp[indice_izq:p]
    palabras_der = fsp[p+1:indice_der+1]
    return (palabras_izq[::-1], palabras_der)