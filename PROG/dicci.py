def cosoDiccionario(l: list) -> dict:
    dic = {}
    for i in l:
        if i[0] in dic.keys():
            dic[i[0]] += [i[1]]
        else:
            dic[i[0]] = [i[1]]
    return dic

# l = [("hola", "Don Pepito"), ("hola", "Don Jose"), ("chau", "picho")]
# print(cosoDiccionario(l))

""" def la_mas_larga(string: str) -> dict:
    dic = {}
    string2 = string.lower()
    listString = string2.split()
    for i in string2:
        for j in listString:
            if i in j:
                if j not in dic. """

#print(la_mas_larga("El solitario monje recorria la sierra cordobesa"))

def la_mas_larga2(string: str) -> dict:
    dic = {}
    string2 = string.lower()
    listString = string2.split()
    letras = set(string2)
    for i in letras:
        for j in listString:
            if (i in j) and (i not in dic.keys()):
                dic[i] = j
            elif (i in j) and (len(dic[i]) < len(j)):
                dic[i] = j 
    print(dic)
    return dic

la_mas_larga2("El solitario monje recorria la sierra cordobesa")

la_mas_larga2("habia una vez un mono escoces")