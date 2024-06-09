import heapq

class Graph:
    def __init__(self, floors, times):
        self.nodes = set() # (ascensor, piso)
        self.edges = dict() # lista ady
        self.unique_vertex = dict() # floor -> [ascensor1, ascensor2, ...]

        for i in range(len(floors)):
            last = None
            for floor in floors[i]:
                # Agrego nodo al grafo e inicializo lista de adyacencia para ese nodo
                self.nodes.add((i, floor))
                self.edges[(i, floor)] = []

                # Agrego aristas entre los nodos del mismo ascensor
                if last != None:
                    _, f = last
                    self.edges[last].append(((i,floor), times[i]*(floor-f))) # Edge en lista de ady: ((ascensor1, piso1), tiempoAscensor1)
                    self.edges[(i,floor)].append((last, times[i]*(floor-f)))
                last = (i, floor)
                
                # Agrego aristas ente los nodos de la misma planta
                if floor in self.unique_vertex:
                    for j in self.unique_vertex[floor]:
                        self.edges[(i, floor)].append(((j, floor), 60))
                        self.edges[(j, floor)].append(((i, floor), 60))
                if floor not in self.unique_vertex:
                    self.unique_vertex[floor] = []
                self.unique_vertex[floor].append(i)

    def dijkstra(self, start):
        # Algoritmo de Dijkstra para encontrar el camino más corto desde el nodo dado    
        # usando una cola de prioridad
        queue = []
        heapq.heappush(queue, (0, start))        
        visited = set()
        dist = {vertex: float('infinity') for vertex in self.nodes}
        dist[start] = 0
        while queue:
            current_distance, current_vertex = heapq.heappop(queue)
            if current_vertex in visited:
                continue
            visited.add(current_vertex)
            for neighbor, weight in self.edges[current_vertex]:
                distance = current_distance + weight
                if distance < dist[neighbor]:
                    dist[neighbor] = distance
                    heapq.heappush(queue, (distance, neighbor))
        return dist

def solve(n,k,times,floors):
    # Armamos el grafo
    G = Graph(floors, times)    

    # Agregamos un nodo fantasma con aristas a todos los nodos de la planta 0
    G.nodes.add((-1, -1))
    G.edges[(-1, -1)] = []
    for asc in G.unique_vertex[0]:
        G.edges[(-1, -1)].append(((asc,0),0))

    # Corremos el algoritmo de Dijkstra desde el nodo fantasma
    dist = G.dijkstra((-1, -1))

    # Buscamos el nodo con el menor tiempo
    minSeg = float('infinity')
    if k not in G.unique_vertex:
        return "IMPOSSIBLE"
    
    for asc in G.unique_vertex[k]:
        if dist[(asc,k)] < minSeg:
            minSeg = dist[(asc,k)]

    if minSeg == float('infinity'):
        return "IMPOSSIBLE"
    return minSeg

if __name__ == '__main__':
    response = []
    while True:
        try:
            nk = input().split()
            if not nk:
                break
            n, k = map(int, nk) 
            times = list(map(int, input().split()))
            floors = [list(map(int, input().split())) for _ in range(n)]
            response.append(solve(n,k,times,floors))
        except EOFError:    
            break
    print("\n".join(str(x) for x in response))