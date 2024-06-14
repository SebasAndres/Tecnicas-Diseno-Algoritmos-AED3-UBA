class Graph:
    def __init__(self, nodes):
        self.nodes=nodes
        self.L={n:{} for n in nodes} 
            
def solve(g:Graph, order) ->int:
    """
    Invertimos el orden de las torres a destruir y vamos calculando Floyd
    a partir de un grafo al cual le vamos agregando torres (en orden inverso).

    A medida que calculamos Floyd-Warshal aprovechamos las soluciones parciales
    """
    order = order[::-1]
    D = g.L # distances matrix (L)
    S = [order[0]]    
    i = 0
    k_val = 0
    acc = 0

    while(i != len(order)):
        # Para cada torre en S, calculamos D con un pivot (Floyd-Marshal)
        for v in S:
            for w in S:
                for k in S:
                    if v != w:
                        D[v][w] = min(D[v][w], D[v][k] + D[k][w])

        # Calculamos la suma de las distancias de las torres en Sk
        k_val = sum([D[x][y] for x in S for y in S if x != y])

        # Acumuladores
        acc += k_val
        i += 1
        k_val = 0

        # Agregamos la siguiente torre
        if i < len(order):
            S.append(order[i])

    return acc

testCases = int(input())
res = [-1] * testCases
for t in range(testCases):
    # Input
    n = int(input())
    g = Graph([i for i in range(n)])
    for tower in range(n):
        ws = [int(w) for w in input().split()]       
        for i in range(n):
            g.L[tower].update({i:ws[i]})   
    order = [int(o) for o in input().split()]
    val = solve(g, order)
    res[t] = val   

for t in res:
    print(t)