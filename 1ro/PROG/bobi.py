lista_personas = [["peluka",32,"rosario","ingeniero termonuclear"],
                  ["papapvp",14,"villa lugano","rappi"],
                  ["flacoestereo",47,"empalme","computer scientist"],
                  ["tincho",60,"lomas de zamora","astronauta"],
                  ["fideleff",3,"rosario","programador"]]

def mayores(l: list) -> list:
    listMayores = []
    for i in lista_personas:
        if i[1] >= 30:
            listMayores.append(i)
    for i in listMayores:
        print(i)
    return listMayores

#mayores(lista_personas)

info_empresa = ("PAPA.INC", 1986, 150, "papua nueva guinea")

def mostrar_empresa(t: tuple):
    a = t[0]
    b = t[1]
    c = t[2]
    d = t[3]
    print("la empresa", a,"fundada en el año", b,",cuenta con", c,"empleados y con sucursales en", d)
    
#mostrar_empresa(info_empresa)

empleados_actuales = {"papapvp","peluka","flacostereo","tincho","fideleff","silvio","la porro","el diego","smoke"}
empleados_nuevos = {"smoke","silvio","la porro","cabrera","galassi"}

def mostrarEmpleados(s1: set, s2: set):
    print("los nuevos empleados, ya ingresados son: ", s2.intersection(s1))
    print("los nuevos empleados, aun no ingresados son", s2-s1)
    
#mostrarEmpleados(empleados_actuales,empleados_nuevos)