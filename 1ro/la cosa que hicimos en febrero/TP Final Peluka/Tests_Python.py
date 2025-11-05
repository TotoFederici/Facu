from palabras_de_referencia import *
from preprocesar_texto import *
from calcular_puntajes import *
from cargar_archivos import cargar_textos


# Aclaracion: los casos de testing estan hechos para n=1, m=2
# El archivo se debe ejecutar con esta configuracion


def test_palabras_de_referencia():
    frase1 = "vencido porque el cuerpo _ los dos"
    frase2 = "que aprender a pedir _"
    frase3 = "y _ rendiste en febrero"
    frase4 = "_ lo mas vital"
    frase5 = "no _"
    frase6 = "ha _ siete"
    frase7 = "_"
    
    assert palabras_de_referencia(frase1, 1) == (["cuerpo"], ["los"])
    assert palabras_de_referencia(frase2, 1) == (["pedir", "a"], [])
    assert palabras_de_referencia(frase3, 1) == (["y"], ["rendiste"])
    assert palabras_de_referencia(frase4, 1) == ([], ["lo", "mas"])
    assert palabras_de_referencia(frase5, 1) == (["no"], [])
    assert palabras_de_referencia(frase6, 1) == (["ha"], ["siete"])
    assert palabras_de_referencia(frase7, 1) == ([], [])


def test_preprocesar_texto():
    texto1 = "flaca no me claves tus punales por la espalda tan profundo no me duelen no me hacen mal"
    texto2 = "te quiero me dejaste el florero y te llevaste la flor pero igual te quiero"
    
    texto_preproc1 = {'flaca': [1, (['no', 'me'], [])], 
                        'no': [3, (['me', 'claves'], ['flaca']), (['me', 'duelen'], ['profundo', 'tan']), (['me', 'hacen'], ['duelen', 'me'])], 
                        'me': [3, (['claves', 'tus'], ['no', 'flaca']), (['duelen', 'no'], ['no', 'profundo']), (['hacen', 'mal'], ['no', 'duelen'])], 
                        'claves': [1, (['tus', 'punales'], ['me', 'no'])], 
                        'tus': [1, (['punales', 'por'], ['claves', 'me'])], 
                        'punales': [1, (['por', 'la'], ['tus', 'claves'])], 
                        'por': [1, (['la', 'espalda'], ['punales', 'tus'])], 
                        'la': [1, (['espalda', 'tan'], ['por', 'punales'])], 
                        'espalda': [1, (['tan', 'profundo'], ['la', 'por'])], 
                        'tan': [1, (['profundo', 'no'], ['espalda', 'la'])], 
                        'profundo': [1, (['no', 'me'], ['tan', 'espalda'])],
                        'duelen': [1, (['no', 'me'], ['me', 'no'])], 
                        'hacen': [1, (['mal'], ['me', 'no'])], 
                        'mal': [1, ([], ['hacen', 'me'])]}
    
    texto_preproc2 = {'te': [3, (['quiero', 'me'], []), (['llevaste', 'la'], ['y', 'florero']), (['quiero'], ['igual', 'pero'])], 
                        'quiero': [2, (['me', 'dejaste'], ['te']), ([], ['te', 'igual'])], 
                        'me': [1, (['dejaste', 'el'], ['quiero', 'te'])], 
                        'dejaste': [1, (['el', 'florero'], ['me', 'quiero'])], 
                        'el': [1, (['florero', 'y'], ['dejaste', 'me'])], 
                        'florero': [1, (['y', 'te'], ['el', 'dejaste'])], 
                        'y': [1, (['te', 'llevaste'], ['florero', 'el'])], 
                        'llevaste': [1, (['la', 'flor'], ['te', 'y'])], 
                        'la': [1, (['flor', 'pero'], ['llevaste', 'te'])], 
                        'flor': [1, (['pero', 'igual'], ['la', 'llevaste'])], 
                        'pero': [1, (['igual', 'te'], ['flor', 'la'])], 
                        'igual': [1, (['te', 'quiero'], ['pero', 'flor'])]}

    assert preprocesar_texto([texto1], 2) == (('no', 3), texto_preproc1)
    assert preprocesar_texto([texto2], 2) == (('te', 3), texto_preproc2)
    assert preprocesar_texto([""], 2) == (("", 0), {})


def test_buscar_palabras():
    
    texto_preproc1 = {'flaca': [1, (['no', 'me'], [])], 
                        'no': [3, (['me', 'claves'], ['flaca']), (['me', 'duelen'], ['profundo', 'tan']), (['me', 'hacen'], ['duelen', 'me'])], 
                        'me': [3, (['claves', 'tus'], ['no', 'flaca']), (['duelen', 'no'], ['no', 'profundo']), (['hacen', 'mal'], ['no', 'duelen'])], 
                        'claves': [1, (['tus', 'punales'], ['me', 'no'])]}
    
    texto_preproc2 = {'me': [1, (['dejaste', 'el'], ['quiero', 'te'])], 
                        'dejaste': [1, (['el', 'florero'], ['me', 'quiero'])], 
                        'el': [1, (['florero', 'y'], ['dejaste', 'me'])], 
                        'florero': [1, (['y', 'te'], ['el', 'dejaste'])]}
    
    assert buscar_palabras(texto_preproc1, ["flaca"], IZQ) == [(1, [['no', 'me']], 1)]
    assert buscar_palabras(texto_preproc1, ["me"], DER) == [(1, [['no', 'flaca'], ['no', 'profundo'], ['no', 'duelen']], 3)]
    assert buscar_palabras(texto_preproc2, ["florero"], IZQ) == [(1, [['y', 'te']], 1)]
    assert buscar_palabras(texto_preproc2, ["dejaste"], DER) == [(1, [['me', 'quiero']], 1)]
    assert buscar_palabras({}, ["el"], IZQ) == []
    assert buscar_palabras(texto_preproc1, [], DER) == []


def test_calcular_coincidencias():
    tupla1 = ([(1, [['vi', 'juntabas'], ['trate', 'bastante'], ['vi'], ['vi', 'saliste'], ['vi'], ['vi', 'te'], ['vi', 'te'], ['vi'], ['vi']], 9)],[])
    tupla2 = ([(1, [['angel', 'o'], ['rubi', 'o'], ['rato', 'no']], 3)],[(1, [['rayo', 'este'], ['esencia', 'la'], ['esencia', 'la']], 5)])
    
    assert calcular_puntajes(tupla1) == {'vi': 0.8888888888888891, 
                                         'juntabas': 0.05555555555555555, 
                                         'trate': 0.1111111111111111, 
                                         'bastante': 0.05555555555555555, 
                                         'saliste': 0.05555555555555555, 
                                         'te': 0.1111111111111111}
    
    assert calcular_puntajes(tupla2) == {'angel': 0.3333333333333333, 
                                         'o': 0.3333333333333333, 
                                         'rubi': 0.3333333333333333, 
                                         'rato': 0.3333333333333333, 
                                         'no': 0.16666666666666666, 
                                         'rayo': 0.2, 
                                         'este': 0.1, 
                                         'esencia': 0.4,
                                         'la': 0.2}



test_palabras_de_referencia()
test_preprocesar_texto()
test_buscar_palabras()
test_calcular_coincidencias()