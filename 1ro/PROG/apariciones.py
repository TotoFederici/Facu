def apariciones(string: str) -> dict:
    dic = {}
    listString = string.split()
    for i in listString:
        if i not in dic.keys():
            dic[i] = 1
        else:
            dic[i] += 1
    print(dic)
    return(dic)

apariciones("que lindo dia que hace")

#apariciones("""en el parque, los niños jugaban y reían.
#            el sol brillaba, y los árboles verdes ofrecían sombra.
#            jugaban a la pelota y corrían por el césped.
#            la alegría de los niños era contagiosa, y todos disfrutaban del día soleado.""")