""" tablero = [["A","_|_|_|_|_|_|_|_|_|_"],
           ["B","_|_|_|_|_|_|_|_|_|_"],
           ["C","_|_|_|_|_|_|_|_|_|_"],
           ["D","_|_|_|_|_|_|_|_|_|_"],
           ["E","_|_|_|_|_|_|_|_|_|_"],
           ["F","_|_|_|_|_|_|_|_|_|_"],
           ["G","_|_|_|_|_|_|_|_|_|_"],
           ["H","_|_|_|_|_|_|_|_|_|_"],
           ["I","_|_|_|_|_|_|_|_|_|_"],
           ["J","_|_|_|_|_|_|_|_|_|_"],
           [" ","1","2","3","4","5","6","7","8","9","0"]] """

#batalla naval, tutu rutu tuuuuu!!!!

tablero = [[" ","1","2","3","4","5","6","7","8","9","0"],
           ["1","_","_","_","_","_","_","_","_","_","_"],
           ["2","_","_","_","_","_","_","_","_","_","_"],
           ["3","_","_","_","_","_","_","_","_","_","_"],
           ["4","_","_","_","_","_","_","_","_","_","_"],
           ["5","_","_","_","_","_","_","_","_","_","_"],
           ["6","_","_","_","_","_","_","_","_","_","_"],
           ["7","_","_","_","_","_","_","_","_","_","_"],
           ["8","_","_","_","_","_","_","_","_","_","_"],
           ["9","_","_","_","_","_","_","_","_","_","_"],
           ["0","_","_","_","_","_","_","_","_","_","_"],
           [" ","1","2","3","4","5","6","7","8","9","0"]]

#porta-aviones: 5 casillas
#buque: 4 casillas
#submarino 3 casillas
#crucero: 2 casillas
#lancha: 1 casilla

barquitos = {}
nameBarquitos = ("porta-aviones", "buque", "submarino", "crucero", "lancha")

def main():
    for i in nameBarquitos:
        print("Vamos a ubicar el", i)
        orientacion = (input("• Ingresá cómo te gusta el barquito: ")).lower()
        posicionVer = int(input("• Ingresá en qué fila te gusta el barquito: "))
        posicionHor = int(input("• Ingresá en qué columna te gusta el barquito: "))
        barquitos[i] = (orientacion, posicionHor, posicionVer)
        colocarBarcos(i)
    print(barquitos)
    


def colocarBarcos(barco: str):
    
    if barquitos[barco][0] == "horizontal":
        for j in range(1,11):
            nuevafila = [j]
            if barquitos[barco][2] == j:
                nuevafila.append("X")
            else:
                nuevafila.append("_")
        for i in range(1,11):
            tablero[barquitos[barco][1]][i] = nuevafila[i]

for i in tablero:
    print(i)

main()

