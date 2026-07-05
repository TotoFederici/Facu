from calculo import *
import numpy as np

# ============================================
# TESTS DE CASOS BORDE
# ============================================

def test_lanzamiento_desde_suelo_velocidad_cero():
    """Objeto en el suelo sin velocidad inicial - debe quedarse en el suelo"""
    r0 = [0, 0, 0]
    v0 = [0, 0, 0]
    t = 1.0
    resultado = tiroParabolico(r0, v0, t)
    assert np.allclose(resultado, [0, 0, 0]), "Debe permanecer en el origen"


def test_lanzamiento_desde_suelo_velocidad_positiva():
    """Lanzamiento vertical desde el suelo hacia arriba"""
    r0 = [0, 0, 0]
    v0 = [0, 0, 10]
    t = 1.0
    resultado = tiroParabolico(r0, v0, t)
    # z = 0 + 10*1 - 4.904*1^2 = 10 - 4.904 = 5.096
    assert np.isclose(resultado[2], 5.096), f"Altura incorrecta: {resultado[2]}"
    

def test_tiempo_mayor_que_impacto():
    """Solicitar tiempo mayor al de impacto - debe limitarse al impacto"""
    r0 = [0, 0, 10]
    v0 = [0, 0, 0]
    t = 100.0  # Tiempo muy grande
    resultado = tiroParabolico(r0, v0, t)
    # El objeto debe estar en z=0 (suelo), no debajo
    assert np.isclose(resultado[2], 0, atol=1e-10), f"Debe estar en el suelo, no en {resultado[2]}"


def test_caida_libre_desde_altura():
    """Caída libre pura desde 20m"""
    r0 = [0, 0, 20]
    v0 = [0, 0, 0]
    t_impacto = cerosTiro(20, 0)
    resultado = tiroParabolico(r0, v0, t_impacto)
    assert np.isclose(resultado[2], 0, atol=1e-10), "Debe llegar al suelo"


def test_tiempo_cero():
    """Tiempo t=0 - debe devolver posición inicial"""
    r0 = [5, 10, 15]
    v0 = [2, 3, 4]
    t = 0.0
    resultado = tiroParabolico(r0, v0, t)
    assert np.allclose(resultado, r0), "En t=0 debe estar en la posición inicial"


def test_velocidad_negativa_inicial():
    """Lanzamiento hacia abajo desde altura"""
    r0 = [0, 0, 50]
    v0 = [0, 0, -10]  # Velocidad hacia abajo
    t = 1.0
    resultado = tiroParabolico(r0, v0, t)
    # z = 50 - 10*1 - 4.904*1 = 50 - 10 - 4.904 = 35.096
    assert np.isclose(resultado[2], 35.096), f"Altura incorrecta: {resultado[2]}"


def test_movimiento_horizontal_sin_altura():
    """Movimiento horizontal puro a ras del suelo"""
    r0 = [0, 0, 0]
    v0 = [10, 5, 0]
    t = 2.0
    resultado = tiroParabolico(r0, v0, t)
    # Sin altura, no hay movimiento (t se limita a 0)
    assert np.allclose(resultado, [0, 0, 0]), "Sin altura inicial no hay movimiento"


def test_movimiento_horizontal_con_altura():
    """Movimiento horizontal desde altura"""
    r0 = [0, 0, 100]
    v0 = [10, 0, 0]
    t = 1.0
    resultado = tiroParabolico(r0, v0, t)
    # x = 0 + 10*1 = 10
    # z = 100 + 0*1 - 4.904*1 = 95.096
    assert np.isclose(resultado[0], 10), f"Desplazamiento X incorrecto: {resultado[0]}"
    assert np.isclose(resultado[2], 95.096), f"Altura incorrecta: {resultado[2]}"


def test_trayectoria_completa_45_grados():
    """Lanzamiento a 45 grados aproximadamente"""
    r0 = [0, 0, 0]
    v0 = [10, 0, 10]  # Componentes iguales ≈ 45°
    t_impacto = cerosTiro(0, 10)
    resultado = tiroParabolico(r0, v0, t_impacto)
    assert np.isclose(resultado[2], 0, atol=1e-10), "Debe terminar en el suelo"
    assert resultado[0] > 0, "Debe haber desplazamiento horizontal"


def test_altura_maxima_alcanzada():
    """Verificar altura máxima en lanzamiento vertical"""
    r0 = [0, 0, 0]
    v0 = [0, 0, 20]
    # En altura máxima: v = v0 + gt = 0 => t = v0/g = 20/9.807 ≈ 2.04s
    t_max = 20 / 9.807
    resultado = tiroParabolico(r0, v0, t_max)
    # h_max = v0²/(2g) = 400/(2*9.807) ≈ 20.39m
    altura_teorica = 400 / (2 * 9.807)
    assert np.isclose(resultado[2], altura_teorica, rtol=0.01), f"Altura máxima incorrecta: {resultado[2]} vs {altura_teorica}"


def test_discriminante_negativo():
    """Caso donde no hay solución real (objeto ya bajo tierra) - debe fallar"""
    r0 = [0, 0, -10]  # Bajo tierra
    v0 = [0, 0, -5]   # Velocidad hacia abajo
    with pytest.raises(ValueError):
        # Esto debería fallar porque sqrt de negativo
        cerosTiro(-10, -5)


def test_valores_muy_grandes():
    """Valores numéricos extremos"""
    r0 = [0, 0, 1e6]  # 1 millón de metros de altura
    v0 = [1000, 0, 0]
    t = 10.0
    resultado = tiroParabolico(r0, v0, t)
    assert np.isfinite(resultado).all(), "Debe manejar valores grandes sin overflow"
    assert resultado[0] == 10000, "Desplazamiento X incorrecto"


def test_valores_muy_pequenos():
    """Valores numéricos muy pequeños"""
    r0 = [0, 0, 1e-6]
    v0 = [1e-6, 0, 0]
    t = 1.0
    resultado = tiroParabolico(r0, v0, t)
    assert np.isfinite(resultado).all(), "Debe manejar valores pequeños sin underflow"


def test_posiciones_iniciales_negativas_xy():
    """Posiciones iniciales negativas en X e Y (válido)"""
    r0 = [-10, -20, 50]
    v0 = [5, 5, 0]
    t = 1.0
    resultado = tiroParabolico(r0, v0, t)
    assert resultado[0] == -5, "X debe ser -10 + 5*1 = -5"
    assert resultado[1] == -15, "Y debe ser -20 + 5*1 = -15"


def test_tiempo_negativo_ceros_tiro():
    """cerosTiro debe devolver tiempo positivo"""
    r0z = 10
    v0z = 10
    t = cerosTiro(r0z, v0z)
    assert t > 0, f"El tiempo debe ser positivo, obtenido: {t}"


def test_precision_numerica_tiempo_impacto():
    """Verificar que en el tiempo de impacto z ≈ 0"""
    r0 = [0, 0, 100]
    v0 = [10, 5, 20]
    t_impacto = cerosTiro(100, 20)
    resultado = tiroParabolico(r0, v0, t_impacto)
    assert np.isclose(resultado[2], 0, atol=1e-8), f"En t_impacto, z debe ser ≈0, obtenido: {resultado[2]}"