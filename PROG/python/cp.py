def copy(a, b):
    ar1 = open(a, "r")
    ar2 = open(b, "w")
    textoCopy = ar1.read(100)
    while textoCopy != "":
        ar2.write(textoCopy)
        textoCopy = ar1.read(100)
    ar1.close()
    ar2.close()
    return 0

