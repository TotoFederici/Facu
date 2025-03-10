from func_listas import *
from buscar_posibles import *
from preprocesado import *

# Ngramas que utilizo para el testing
ngramas = {('el', 'despues'):       [['el', 'amor', 'despues']], 
           ('amor', 'del'):         [['amor', 'despues', 'del']], 
           ('despues', 'amor'):     [['despues', 'del', 'amor']], 
           ('del', 'tal'):          [['del', 'amor', 'tal']], 
           ('amor', 'vez'):         [['amor', 'tal', 'vez']], 
           ('tal', 'se'):           [['tal', 'vez', 'se']], 
           ('vez', 'parezca'):      [['vez', 'se', 'parezca']], 
           ('se', 'a'):             [['se', 'parezca', 'a']], 
           ('parezca', 'este'):     [['parezca', 'a', 'este']], 
           ('a', 'rayo'):           [['a', 'este', 'rayo']], 
           ('este', 'de'):          [['este', 'rayo', 'de']], 
           ('rayo', 'sol'):         [['rayo', 'de', 'sol']], 
           ('y', 'que'):            [['y', 'ahora', 'que'], ['y', 'ahora', 'que']], 
           ('ahora', 'busque'):     [['ahora', 'que', 'busque']], 
           ('que', 'y'):            [['que', 'busque', 'y']], 
           ('busque', 'ahora'):     [['busque', 'y', 'ahora']], 
           ('ahora', 'encontre'):   [['ahora', 'que', 'encontre']], 
           ('que', 'el'):           [['que', 'encontre', 'el'], ['que', 'lleva', 'el']], 
           ('encontre', 'perfume'): [['encontre', 'el', 'perfume']], 
           ('el', 'que'):           [['el', 'perfume', 'que']], 
           ('perfume', 'lleva'):    [['perfume', 'que', 'lleva']], 
           ('lleva', 'dolor'):      [['lleva', 'el', 'dolor']]}

def test_preprocesado():
    assert (preprocesado(Entradas("Test_en_Python"), 3) == (ngramas, "amor"))

# Test de la funcion interseccion
def test_interseccion():
    assert (interseccion(["hola", "como", "va"],["hola", "todo", "bien"]) == ["hola"])
    assert (interseccion(["el", "amor", "despues", "amor"],["el", "amor", "despues"]) == ["el", "amor", "despues", "amor"])
    assert (interseccion(["el", "amor", "despues"],[]) == [])
    assert (interseccion([],[]) == [])

# Test de la funcion elemento_mas_frecuente
def test_elemento_mas_frecuente():
    assert (elemento_mas_frecuente(["vi", "vi", "vi", "amor"]) == ("vi", 3))
    assert (elemento_mas_frecuente(["el", "amor", "despues"]) == ("el",1))
    assert (elemento_mas_frecuente(["simplemente", "vi", "vi", "simplemente"]) == ("simplemente", 2))
    assert (elemento_mas_frecuente([]) == (None, 0))
    
# Test de la funcion palabras_cercanas
def test_palabras_cercanas():
    frase1 = "vencido porque el cuerpo _ los dos"
    frase2 = "en mi persiana _"
    frase3 = "_ comprender como soy"
    frase4 = "oso _"
    frase5 = "_ entonces"
    frase6 = "de _ ligera"
    assert (palabras_cercanas(frase1) == (TIPO_MEDIO, "cuerpo", "los"))
    assert (palabras_cercanas(frase2) == (TIPO_DER, "persiana", "mi"))
    assert (palabras_cercanas(frase3) == (TIPO_IZQ, "comprender", "como"))
    assert (palabras_cercanas(frase4) == (TIPO_DER, "oso", 0))
    assert (palabras_cercanas(frase5) == (TIPO_IZQ, "entonces", 0))
    assert (palabras_cercanas(frase6) == (TIPO_MEDIO, "de", "ligera"))

def test_palabras_posibles():
    
    # Usando de ejemplo estas frases
    # frase1: "no hacías otra _ que escribir"
    # frase2: "tengo amor _"
    # frase3: "_ el amor"
    # frase4: "la suerte _ con cartas sin marcar"
    # frase5: "es _"
    # frase6: "_ perfume"
    
    cercanas1 = (TIPO_MEDIO, "otra", "que")
    cercanas2 = (TIPO_DER, "amor", "tengo") 
    cercanas3 = (TIPO_IZQ, "el", "amor")
    cercanas4 = (TIPO_MEDIO, "suerte", "con")
    cercanas5 = (TIPO_DER, "es", 0)
    cercanas6 = (TIPO_IZQ, "perfume", 0)
    
    assert (palabras_posibles(ngramas,cercanas1) == ([],["ahora", "ahora", "perfume"],[]))
    assert (palabras_posibles(ngramas,cercanas2) == (["despues", "tal"],[],[]))
    assert (palabras_posibles(ngramas,cercanas3) == (["encontre", "lleva"], ["despues"],[]))
    assert (palabras_posibles(ngramas,cercanas4) == ([],[],[]))
    assert (palabras_posibles(ngramas,cercanas5) == ([],[],[]))
    assert (palabras_posibles(ngramas,cercanas6) == (["el"],[],[]))
    
# Test de la funcion palabras_posibles
def test_lista_posibles():
    
    # Usando de ejemplo estas frases
    # frase1: "no hacías otra _ que escribir"
    # frase2: "tengo amor _"
    # frase3: "_ el amor"
    # frase4: "la suerte _ con cartas sin marcar"
    # frase5: "es _"
    # frase6: "_ perfume"

    cercanas1 = (TIPO_MEDIO, "otra", "que")
    cercanas2 = (TIPO_DER, "amor", "tengo") 
    cercanas3 = (TIPO_IZQ, "el", "amor")
    cercanas4 = (TIPO_MEDIO, "suerte", "con")
    cercanas5 = (TIPO_DER, "es", 0)
    cercanas6 = (TIPO_IZQ, "perfume", 0)
    
    assert (lista_posibles(ngramas, cercanas1) == ["ahora", "ahora", "perfume"])
    assert (lista_posibles(ngramas, cercanas2) == ["despues", "tal"])
    assert (lista_posibles(ngramas, cercanas3) == ["encontre", "lleva"])
    assert (lista_posibles(ngramas, cercanas4) == [])
    assert (lista_posibles(ngramas, cercanas5) == [])
    assert (lista_posibles(ngramas, cercanas6) == ["el"])

test_preprocesado()
test_interseccion()
test_elemento_mas_frecuente()
test_palabras_cercanas()
test_palabras_posibles()
test_lista_posibles()