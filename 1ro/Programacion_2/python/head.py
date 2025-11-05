def contar(a, n):
    archivo = open(a, "r")
    while n > 0:
        print(archivo.readline())
        n-=1
    archivo.close()
    return 0