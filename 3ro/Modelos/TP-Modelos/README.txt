Se proveen tanto una carpeta comprimida con los códigos como un ejecutable.

------------------------
-- Ejecutable --

El nombre del archivo ejecutable es "graficadora.exe"
Al ejecutarlo, puede llegar a decir que el archivo es peligroso, en realidad el problema es que windows desconoce al autor del archivo (nosotros) debería clickear en ejecutar de todos modos.
Se podrán cambiar los parámetros iniciales sin necesidad de cerrar la interfaz, simplemente cambiando los parámetros y clickeando "graficar" se inicia otra pagina con el nuevo 	  grafico.
------------------------

------------------------
-- Carpeta comprimida --

Archivos Importantes:
 
. calculo.py: Dados los datos iniciales realiza el calculo del punto final como se pide así como de la trayectoria de la partícula y se provee esa información a graficar.py

. graficar.py: Se encarga de realizar el grafico con los cálculos obtenidos en calculo.py

. GUI.py: Corre la interfaz grafica donde se deben insertar los valores iniciales de la simulación, cuando se hace click en "graficar" se redirige al usuario a una pagina web donde se          	  mostrara el grafico (si la pagina web tarda en mostrar el grafico, recargar la pagina con F5).
	  Se podrán cambiar los parámetros iniciales sin necesidad de cerrar la interfaz, simplemente cambiando los parámetros y clickeando "graficar" se inicia otra pagina con el nuevo 	  grafico.

. Si no se desea usar el ejecutable (No recomendado), la forma de compilar seria:

   - en windows:
	 
	- abrir una terminal en el directorio "TP-Modelos-Cicerchia-Marelli-Federici"
	- si no se tiene instalado python se puede instalar por la pagina web https://www.python.org/downloads/
	- ahora hay que descargar algunas extensiones de python, con los siguientes comandos:
		pip install numpy
		pip install plotly
		pip install tk
	- luego para ejecutar el programa con el comando:
		python3 GUI.py

   - en Linux:
	
	- abrir una terminal en el directorio "TP-Modelos-Cicerchia-Marelli-Federici"
	- instalar python si no lo está con el comando:
		sudo apt install python3
	- instalar make con el comando:
		sudo apt install make
	- ejecutar:
		python3 -m venv venv
		source venv/bin/activate
	- luego para correr el programa se deben ejecutar los siguientes comandos:
		make install (una sola vez)
		make run (para ejecutar)
	- es posible que no se abra la pagina directamente y en su lugar se muestre por la terminal un mensaje con un link parecido a "gio: http://127.0.0.1:33229: Operation not supported"
	  simplemente usar (ctrl + click) en ese link o copiarlo en el navegador debería redirigir al grafico
------------------------