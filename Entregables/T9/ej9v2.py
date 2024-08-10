from collections import defaultdict
from heapq import *

def diff_minima(digito1, digito2):
    diff = abs(digito1 - digito2)
    return min(diff, 10 - diff)

def contrasena_con_menor_diff(contrasena_dada, contrasenas):
    min_diff = float('inf')
    min_contrasena = None
    for contrasena in contrasenas:
        diff_total = sum(diff_minima(int(d1), int(d2)) for d1, d2 in zip(contrasena_dada, contrasena))
        if diff_total < min_diff:
            min_diff = diff_total
            min_contrasena = contrasena
    return min_contrasena

class Grafo:
    def __init__(self):
        self.grafo = defaultdict(dict)

    def agregar_borde(self, u, v, peso):
        self.grafo[u][v] = peso
        self.grafo[v][u] = peso

    def prim(self):
        visitado = {clave: False for clave in self.grafo}
        pesos = {clave: float('inf') if clave != "0000" else 0 for clave in self.grafo}
        vertices = list(self.grafo.keys())
        comienzo = contrasena_con_menor_diff("0000", vertices)
        pesos[comienzo] = sum(diff_minima(int(d1), int(d2)) for d1, d2 in zip("0000", comienzo))
        cola_prioridad = [(0, comienzo)]
        while cola_prioridad:
            g, u  = heappop(cola_prioridad)
            if not visitado[u]:
                visitado[u] = True
                for v in self.grafo[u]:
                    if not visitado[v]:
                        pesos[v] = min(pesos[v], self.grafo[u][v])
                        heappush(cola_prioridad, (pesos[v], v))
                for v in self.grafo[u]:
                    if visitado[v]:
                        self.grafo[u][v] = 0
        return sum(pesos.values())

def psa():
    T = int(input())
    res = []
    for _ in range(T):
        entrada = input().split()  # Dividir la entrada en componentes
        N = int(entrada[0])  # Convertir el primer componente a un entero
-        contrasenas = entrada[1:]  # El resto de la entrada son las contraseñas
        g = Grafo()
        if N == 1:
            res.append(sum(diff_minima(int(d1), int(d2)) for d1, d2 in zip(contrasenas[0], "0000")))
            continue
        for contra in contrasenas:
            for contra2 in contrasenas:
                if contra != contra2:    
                    g.agregar_borde(contra , contra2, sum(diff_minima(int(d1), int(d2)) for d1, d2 in zip(contra, contra2)))
        r = g.prim()
        res.append(r)
    print("\n".join(str(x) for x in res))

psa()