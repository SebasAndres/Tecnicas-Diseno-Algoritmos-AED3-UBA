import sys

class Graph:
    def __init__(self, nodes):
        self.nodes=nodes
        self.L={n:{} for n in nodes} 
            
def solve(g:Graph, order) ->int:
    """
    Calculamos las distancias con el algoritmo de Dantzig, agregando los nodos a 
    Gk en el orden inverso que son destruidas las torres.
    """
    D = g.L 
    L = g.L
    S = set()
    t = sys.maxsize
    order = order[::-1]

    acc = 0
    c = 0
    for k in order:

        print("C:",c)
        print("K:",k)
        S_ = list(S)
        S_.sort()
        print("S:"," ".join([str(i) for i in S_]))
 
        # Calculo las distancias de cada {1...k-1} respecto al pivot K (ida y vuelta)
        for i in S:
            for j in S: # j: pivot
                D[i][k] = min(D[i][k], D[i][j] + L[j][k]) # ida 
                D[k][i] = min(D[k][i], D[k][j] + L[j][i]) # vuelta
            t = min(t, D[k][i]+D[i][k])
        
        if t<0:
            return -1 # Existe ciclo negativo

        # Recalculo las distancias entre los elementos de {1..k-1} con k como pivot
        for i in S:
            for j in S:
                D[i][j] = min(D[i][j], D[i][k]+D[k][j])
        
        # Agregamos el nodo a Gk+1        
        S.add(k)
        Ss = list(S)
        Ss.sort()

        # Sumador de distancias!
        i_val = 0
        for i in Ss:
            for j in Ss:
                acc += D[i][j]
                i_val += D[i][j]

        print(c, "i", i_val)
        print()
        c+=1

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