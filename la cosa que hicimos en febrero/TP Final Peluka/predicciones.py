from calcular_puntajes import *
from preprocesar_texto import *
from palabras_de_referencia import *
from cargar_archivos import *

# Constantes
N = 1
M = 2


def predicciones(nombre:str) -> None:
    """
    Realiza la prediccion y escribe la frase reemplazando el '_' con la palabra obtenida 
    en el archivo creado en la carpeta Salidas.
    En caso de que no se haya conseguido una prediccion, se completa con la palabra mas frecuente del texto.
    """
    
    textos = cargar_textos(nombre)
    frases = cargar_frases(nombre)
    
    mas_frecuente, texto_preproc = preprocesar_texto(textos, M)
    
    archivo_salida = open("./Salidas/{}.txt".format(nombre), 'w')
    for frase in frases:
        palabras_ref_frases = palabras_de_referencia(frase, N)
        
        palabras_encontradas = (buscar_palabras(texto_preproc, palabras_ref_frases[IZQ], IZQ), 
                                buscar_palabras(texto_preproc, palabras_ref_frases[DER], DER))
        
        if palabras_encontradas[IZQ] != [] or palabras_encontradas[DER] != []:
            dicc_valores = calcular_puntajes(palabras_encontradas)
            archivo_salida.write(frase.replace('_', max(dicc_valores, key=dicc_valores.get)) + "\n")
        else:
            archivo_salida.write(frase.replace('_', mas_frecuente[0]) + "\n")
    
    archivo_salida.close()