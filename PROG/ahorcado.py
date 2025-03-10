from random import *

palabrasfijasRandom = ["computadora", "programacion", "inteligencia", "artificial", "ciencia",
                       "tecnologia", "robot", "espacio", "galaxia", "astronomia", "montana",
                       "oceanoo", "naturaleza", "animales", "jardin", "creatividad", "innovacion",
                       "cultura", "historia", "musica", "literatura", "poesia", "pintura",
                       "escultura", "arquitectura", "viaje", "aventura", "exploracion",
                       "descubrimiento", "imaginacion", "energia", "sostenibilidad", 
                       "ecologia", "cambio", "climatico", "salud", "bienestar",
                       "ejercicio", "alimentacion", "meditacion", "felicidad", 
                       "amor", "amistad", "paz", "tolerancia", "equidad", 
                       "derechos", "humanos", "educacion", "aprendizaje", 
                       "tecnologia", "innovacion", "emprendimiento", 
                       "negocios", "economia", "politica", "democracia", "justicia", "libertad", "igualdad", "sociedad", "comunidad", "cultura", "entretenimiento", "deporte", "viaje", "aventura", "relax", "vacaciones", "ocio", "moda", "diseno", "arquitectura", "urbanismo", "viaje", "aventura", "exploracion", "descubrimiento", "imaginacion", "fantasia","astronomia", "biologia", "quimica", "fisica", "matematicas","espejo", "orquidea", "helado", "pantalla", "turquesa", "almohada", "ventana", "caminar", "bicicleta", "telefono", "ordenador", "elefante", "jardin", "playa", "cancion", "montana", "estrella", "cafe", "teclado", "boligrafo", "diario", "telescopio", "ocean", "almuerzo", "desayuno", "cena", "reloj", "calendario", "guitarra", "pintura", "globo", "ciencia", "radiador", "papel", "gafas", "velero", "pastel", "puente", "fruta", "piano", "tecnico", "vaso", "zapato", "anillo", "flores", "rayo", "pajaro", "misterio", "romance", "orquidea", "helado", "espejo", "pantalla", "turquesa", "ventana", "caminar", "bicicleta", "telefono", "ordenador", "elefante", "jardin", "playa", "cancion", "montana", "estrella", "cafe", "teclado", "boligrafo", "diario", "telescopio", "ocean", "almuerzo", "desayuno", "cena", "reloj", "calendario", "guitarra", "pintura", "globo", "ciencia", "radiador", "papel", "gafas", "velero", "pastel", "puente", "fruta", "piano", "tecnico", "vaso", "zapato", "anillo", "flores", "rayo", "pajaro", "misterio", "romance", "orquidea", "helado", "espejo", "pantalla", "turquesa"]

def eligePalabras():
    return palabrasfijasRandom[randint(0, len(palabrasfijasRandom)-1)]

def posLetra(l: list, c: str):
    pos = []
    largo = len(l)
    for i in range(largo):
        if l[i] == c:
            pos += [i]
    return pos

# 1: ganó, 0: sigue jugando, -1: perdió. 
# estado del juego: (situacion del jugador, palabra que se esta adivinando, fallos restantes)

def jugada(letra: str, palabra: list, repetidas: list, estado: list):
    palabraList = list(palabra)
     
    if letra in repetidas:
        estado = [0, estado[1], estado[2]]
        print("esa letra ya la usaste bobi")
    else:
        if posLetra(palabraList, letra) == []:
            estado[2] -= 1
            estado = [0, estado[1], estado[2]]
            repetidas += [letra]
            if estado[2] == 0:
                estado = [-1, estado[1], estado[2]]
        else:
            for i in posLetra(palabraList, letra):
                estado[1][i] = letra
            if estado[1] == palabraList:
                estado = [1, estado[1], estado[2]]
            else:
                estado = [0, estado[1], estado[2]]
            repetidas += [letra]
    return estado

def juego():
    repetidas = []
    palabra = eligePalabras()
    oculta = list(palabra)
    for i in range(len(palabra)):
        oculta[i] = "_"
    estado = [0, oculta, 3]
    print("tenes que adivinar una palabra oculta bobi", oculta)
    while estado[0] == 0:
        letra = input("ingresa una letra bobi: ")
        while letra > "z" or letra < "a" or len(letra) != 1:
            print("ese caracter no es valido, ingresa letras minusculas bobi")
            letra = input("ingresa una letra bobi: ")
        estado = jugada(letra, palabra, repetidas, estado)
        if estado[0] == 1:
            print("ganaste bobi!!!!\nla palabra era", palabra)
        elif estado[0] == -1:
            print("perdiste bobi!!!!\nla palabra era", palabra)
        else:
            print("hasta ahora descubriste:", "".join(estado[1]), "\nte quedan", estado[2], "intentos, bobi.\n")
    return 0

juego()