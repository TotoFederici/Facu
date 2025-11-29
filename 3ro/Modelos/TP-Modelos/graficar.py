from calculo import *
import numpy as np
import plotly.graph_objects as go        

def graficar(x0,y0,z0,T,vx0,vy0,vz0):

  r0 = [x0,y0,z0]
  v0 = [vx0,vy0,vz0]
  # === Cálculo ===
  t_impacto = cerosTiro(r0[2],v0[2])
  t_impacto = min(t_impacto,T)

  tIntervalo = np.linspace(0, t_impacto, int(t_impacto*1000))
  calc = tiroParabolico(r0,v0,t_impacto)
  
  vectorResultado = tiroParabolico(r0,v0,tIntervalo)
  x = vectorResultado[:,0]
  y = vectorResultado[:,1]
  z = vectorResultado[:,2]

  # --- Cortar en el piso ---
  suelo = np.where(z <= 0)[0]

  if len(suelo) > 0:
        idx = suelo[0]
        x = x[:idx+1]
        y = y[:idx+1]
        z = z[:idx+1]
        t = tIntervalo[:idx+1]

  fig = go.Figure()

  fig.add_trace(go.Scatter3d(
        x=x, y=y, z=z,
        mode='lines',
        name="Parabola",
        line=dict(width=6)
    ))

  fig.add_trace(go.Scatter3d(
        x=[x0], y=[y0], z=[z0],
        mode='markers',
        name="Punto Inicial",
        marker=dict(size=5)
    ))

  fig.add_trace(go.Scatter3d(
        x=[calc[0]], y=[calc[1]], z=[calc[2]],
        mode='markers',
        name="Punto Final",
        marker=dict(size=5)
    ))

  fig.add_annotation(
        xref="paper", yref="paper",
        x=0.0, y=0.98,
        text=(
            f"<b>Vector resultado</b><br>"
            f"─────────────────<br>"
            f"X = {calc[0]:>7.2f} m<br>"
            f"Y = {calc[1]:>7.2f} m<br>"
            f"Z = {calc[2]:>7.2f} m"
        ),
        showarrow=False,
        align="left",
        xanchor="left",
        yanchor="top",
        borderwidth=2,
        borderpad=8
    )

  fig.update_layout(
        title={
            'text': "Tiro parabólico 3D",
            'x': 0.5,  # Centrar título
            'xanchor': 'center',
            'font': {'size': 20, 'family': 'Arial, sans-serif'}
        },
        scene=dict(
            xaxis_title="X [m]",
            yaxis_title="Y [m]",
            zaxis_title="Z [m]",
            aspectmode='data',
            camera=dict(
                eye=dict(x=1.5, y=1.5, z=1.2)  # Mejor ángulo de vista
            )
        ),
        template="plotly_white",
    )

  fig.show()

