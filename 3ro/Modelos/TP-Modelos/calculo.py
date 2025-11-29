#
import numpy as np
import pytest

# 9.807 / 2 = 4.904. Directamente consideramos g * 1 /2
g = np.array([0,0,-4.904], dtype=np.float64)


# CerosTiro recibe la posicion inicial y velocidad en su componente z
# y resuelve la ecuacion cuadratica devolviendo la mayor raiz de ambas.

# r0z + v0z * t + -1/2g * t^2
def cerosTiro(r0z: float, v0z: float) -> float:
	discriminante = v0z**2 - 4* r0z * g[2]
	if discriminante < 0 : 
		raise ValueError("Discriminante negativo, no tiene solucion real.")
	sqrt_disc = np.sqrt(discriminante)


	da = g[2]*2 # 2*a
	t1 = (-v0z + sqrt_disc) / da
	t2 = (-v0z - sqrt_disc) / da

	if (t1 < 0) and (t2 < 0) :
		raise ValueError("La particula inicia su desplazamiento desde abajo del suelo.")

	tfinal = max(t1,t2)
	return tfinal


# Definimos una funcion que recibe dos listas correspondientes a la posicion y velocidad inicial
# y un float que representa al tiempo.
def tiroParabolico(r0: list, v0: list, t) -> np.ndarray:
	r0 = np.array(r0, dtype=np.float64) # Convertimos ambas listas a arreglos de floats de 64 bits
	v0 = np.array(v0, dtype=np.float64)
	if np.isscalar(t):
		t = min(cerosTiro(r0[2],v0[2]),t) 
		res = r0 + v0 * t + g * (t**2) # Realizamos el calculo.
	else:
		t = np.minimum(cerosTiro(r0[2],v0[2]), t)
		res = r0 + v0 * t[:, np.newaxis] + g * (t[:, np.newaxis]**2)
	return res