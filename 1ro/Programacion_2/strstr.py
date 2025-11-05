#devolver la posicion del primer caracter de "haystack" en "needle"
#ejemplo "haystack" = sol, "needle" = girasol -> devuelve 4

def strstr(str2: str, str1: str) -> int:
    if str1 not in str2:
        print(str1, "no esta en", str2)
        return -1
    else:
        i = 0
        while i < len(str2):
            if str2[i] == str1[0]:
                j = 0
                pos = i
                while j < len(str1) and str2[i] == str1[j]:
                    i += 1
                    j += 1
                i = pos
                if j == len(str1):
                    print(pos)
            i += 1

str11 = "jajaja mundo"
str22 = "jaja mundo"
strstr(str11,str22)