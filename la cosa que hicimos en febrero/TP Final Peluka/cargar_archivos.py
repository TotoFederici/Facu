def cargar_textos(nombre):
    texto = open("./Entradas/{}.txt".format(nombre), 'r')
    return texto.readlines()
            
def cargar_frases(nombre):
    try:
        frases = open("./Frases/{}.txt".format(nombre), 'r')
    except:
        print("Error: no se encontraron frases de {}.\n"
              "Por favor revise si existe el archivo correspondiente en la carpeta 'Frases'.".format(nombre))
        exit(0)
    return frases.read().splitlines()