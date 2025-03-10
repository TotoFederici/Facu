estudiantes = [
    {"nombre": "toto", "calificaciones": {"matematica": 90, "fisica": 55, "ingles": 95}},
    {"nombre": "pepe", "calificaciones": {"matematica": 80, "fisica": 92, "ingles": 48}},
    {"nombre": "franco", "calificaciones": {"matematica": 55, "fisica": 78, "ingles": 90}},
    {"nombre": "martin", "calificaciones": {"matematica": 88, "fisica": 67, "ingles": 50}},
    {"nombre": "juan", "calificaciones": {"matematica": 43, "fisica": 80, "ingles": 100}},
    {"nombre": "gian", "calificaciones": {"matematica": 91, "fisica": 30, "ingles": 82}}]

def aprobados_Por_Materia(estudiantes: list, materia: str) -> list:
    aprobados = []
    for i in estudiantes:
        if i["calificaciones"][materia] >= 70:
            aprobados.append(i["nombre"])
    print("los aprobados de", materia, "son", aprobados)
    return aprobados

#aprobados_Por_Materia(estudiantes,"fisica")
#aprobados_Por_Materia(estudiantes,"matematica")
#aprobados_Por_Materia(estudiantes,"ingles")

def calificacion_mas_alta(estudiantes: list) -> dict:
    listMaterias = ["matematica", "fisica", "ingles"]
    mayoresNotas = {}
    mayoresNotas["matematica"] = ""
    mayoresNotas["fisica"] = ""
    mayoresNotas["ingles"] = ""
    
    for i in listMaterias:
        mayorActual = 0
        for j in estudiantes:
            if j["calificaciones"][i] > mayorActual:
                mayorActual = j["calificaciones"][i]
                mayoresNotas[i] = j["nombre"]
    print(mayoresNotas)
    return mayoresNotas

calificacion_mas_alta(estudiantes)