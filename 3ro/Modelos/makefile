# Makefile simple para proyecto Python

.PHONY: install run test clean all

# Instalar dependencias
install:
	pip install -r requirements.txt

# Ejecutar calculo.py
run:
	python3 GUI.py
	
# Limpiar archivos temporales
clean:
	find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true
	find . -type f -name "*.pyc" -delete

# Instalar y ejecutar
all: install run