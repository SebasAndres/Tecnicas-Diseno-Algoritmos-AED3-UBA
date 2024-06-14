class Graph:
    def __init__(self, nodes):
        self.nodes=nodes
        self.L={n:{} for n in nodes} 
            
def solve(g:Graph, order) ->int:
    """
    Invertimos el orden de las torres a destruir y vamos calculando D
    con el ultimo nodo restaurado como pivot.
    """

    order.reverse()
    D = g.L # distances matrix (L)
    S = [0] * len(order)
    energy = 0

    for k in order:
        S[k] = 1
        
        # Actualizo los caminos minimos con el nodo restaurado como pivot
        for u in g.nodes:
            for v in g.nodes:
                D[u][v] = min(D[u][v], D[u][k] + D[k][v])

        # sumamos las distancias minimas de los nodos restaurados
        for u in g.nodes:
            if S[u]:
                for v in g.nodes:
                    if S[u] and S[v]:
                        energy += D[u][v]
    return energy

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