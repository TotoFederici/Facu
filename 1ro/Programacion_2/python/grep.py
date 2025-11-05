def grep(s, a):
    arch = open(a,"r")
    linea = arch.readline()
    while linea != "":
        if s in linea:
            print(linea)
        linea = arch.readline()
    arch.close()
    return 0