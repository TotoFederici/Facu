import tkinter as tk
from tkinter import messagebox
from graficar import *

# ===========================================================
#                  PLANTILLA DE INTERFAZ GRÁFICA
# ===========================================================

def pedir_positivo(nombre,self):
    while True:
        valor = float(self.inputs[f"{nombre}"].get())
        if valor < 0:
            messagebox.showerror("Error", "Ingresá un valor positivo para este parametro.")
        else:
            return valor

class App:
    def __init__(self, root):
        self.root = root
        self.root.title("Graficadora")

        # ---- Frame principal ----
        frame = tk.Frame(root, padx=20, pady=20)
        frame.pack()

        campos_columna_1 = ["x0", "y0", "z0"]
        campos_columna_2 = ["vx0", "vy0", "vz0"]
        campos_columna_3 = ["Tiempo T"]

        self.inputs = {}

        # --- Columna 1 ---
        for i, campo in enumerate(campos_columna_1):
            tk.Label(frame, text=campo).grid(row=i, column=0, sticky="w", padx=5, pady=5)
            entry = tk.Entry(frame)
            entry.grid(row=i, column=1, padx=5, pady=5)
            self.inputs[campo] = entry

        # --- Columna 2 ---
        offset = len(campos_columna_1)  # para seguir debajo o alineado
        for i, campo in enumerate(campos_columna_2):
            tk.Label(frame, text=campo).grid(row=i, column=2, sticky="w", padx=5, pady=5)
            entry = tk.Entry(frame)
            entry.grid(row=i, column=3, padx=5, pady=5)
            self.inputs[campo] = entry

        # --- Columna 3 ---
        for i, campo in enumerate(campos_columna_3):
            tk.Label(frame, text=campo).grid(row=i, column=4, sticky="w", padx=5, pady=5)
            entry = tk.Entry(frame)
            entry.grid(row=i, column=5, padx=5, pady=5)
            self.inputs[campo] = entry

        # ---- Botón ----
        tk.Button(
            frame,
            text="Graficar",
            command=self.ejecutar_programa
        ).grid(row=3, column=2, columnspan=3, pady=15)


    # =======================================================
    #         Acá va tu código de simulación y gráfica
    # =======================================================
    def ejecutar_programa(self):
        try:
            # Tomar valores
            x0 = float(self.inputs["x0"].get())
            y0 = float(self.inputs["y0"].get())
            z0 = pedir_positivo("z0",self)           

            vx0 = float(self.inputs["vx0"].get())
            vy0 = float(self.inputs["vy0"].get())
            vz0 = float(self.inputs["vz0"].get())

            T  = pedir_positivo("Tiempo T",self)

        except ValueError:
            messagebox.showerror("Error", "Ingresá valores numéricos válidos.")
            return

        graficar(x0,y0,z0,T,vx0,vy0,vz0)


# ===========================================================
#                  EJECUCIÓN DE LA APLICACIÓN
# ===========================================================

if __name__ == "__main__":
    root = tk.Tk()
    App(root)
    root.mainloop()
