

def suma(a, b):
    return(a + b)

def resta(a, b):
    return(a - b)

def producto(a, b):
    return(a * b)
    
def division(a, b):
    return(a / b)

def operar():
    n = int(input("elija una de estas opciones: 1.Suma 2.Resta 3.Producto 4.Division 5.Salir (ingrese el numero de su opcion) " ))
    if n == 1:
        print(suma(int(input("ingrese un numero que quiera sumar ")), int(input("ingrese otro numero que quiera sumar "))), "es el resultado de la suma")
        operar()
    if n == 2:
        print(resta(int(input("ingrese un numero que quiera restar ")), int(input("ingrese un numero que quiera rastarle "))), "es el resultado de la resta")
        operar()    
    if n == 3:
        print(producto(int(input("ingrese un numero que quiera multiplicar ")), int(input("ingrese otro numero que quiera multiplicar "))), "es el resultado del producto")
        operar()    
    if n == 4:
        print(division(int(input("ingrese un numero que quiera dividir ")), int(input("ingrese el numero que quiera dividirle "))), "es el resultado de la division")
        operar()
    if n == 5:
        print("fin de las operaciones, por ahora")

