def wp(a):
    arch = open(a,"r")
    lineas = 0
    palabras = 0
    caracteres = 0
    lineaActual = arch.readline()
    while lineaActual != "":
        lineas += 1
        palabras = palabras + len(lineaActual.split(" "))
        caracteres = caracteres + (len(lineaActual)-1)
        lineaActual = arch.readline()
    arch.close()
    print("tiene", lineas, "lineas", palabras, "palabras y", caracteres, "caracteres.")
    return 0