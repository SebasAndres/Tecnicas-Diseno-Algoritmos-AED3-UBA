# Arboles y recorridos BFS, DFS

- <b>Arbol</b>: Es un grafo conexo sin circuitos simples.

- <b>Puente</b>: Una arista $e \in X(G)$ es puente si $G-e$ tiene mas componentes conexas que $G$.

- <b>Punto de articulacion</b>: Un vertice $v \in V(G)$ es un punto de articulacion si $G-v$ tiene mas componentes conexas que $G$.

- <b>Arbol enraizado</b>: Es un arbol que tiene un vertice distinguido que llamamos raiz. Explicitamente define un <b>arbol dirigido</b>.

- <b>Nivel</b>: Es la distancia de la raiz a ese vertice (un padre siempre tiene menor nivel que un hijo).

- <b>Altura (h)</b>: Es el maximo nivel de sus vertices.

- <b>Vertices internos</b>: Son aquellos que no son ni hojas ni la raiz.

- <b>Arbol balanceado</b>: Un arbol esta balanceado si todas sus hojas estan a nivel h o h-1.

- <b>Arbol balanceado completo</b>: Un arbol es balanceado  completo si todas sus hojas estan a nivel h.

## Teoremas y lemas

No importan los nombres.

### 1. Equivalencia Arbol-Grafo: 
Dado un grafo $G=(V,X)$, son equivalentes:

1. G es un arbol.
2. G es un grafo sin circuitos simples pero si se le agrega una arista $e$ resulta un grafo con exactamente un circuito simple que contiene a $e$.
3. Existe exactamente un camino entre todo par de nodos.
4. Toda arista de G es puente. Es decir, G es conexo, pero si se le quita cualquier arista a $G$ queda un grafo no conexo. 

O tambien equivale:

1. G es un arbol.
2. G es un grafo sin circuitos simples y $|X|=|V|-1$.
3. G es conexo y $|X|=|V|-1$.

### Lema 1: 
Sea $G=(V,X)$ un grafo conexo y $e\in X$:
$$G-e \text{ es conexo} \iff e \text{ pertenece a algun circuito simple de }G$$

### Lema 2: 
Todo arbol no trivial tiene al menos dos hojas.

### Lema 3: 
Sea $G=(V,X)$ arbol, entonces $|X|=|V|-1$

### Corolario 1:
Sea $G=(V,X)$ sin circuitos simples y $c$ componentes conexas, entonces: $|X| = |V| - c$

### Corolario 2: 
Sea $G=(V,X)$ con $c$ componentes conexas, entonces:

$|X| \geq |V|-c$

## Arbol m-ario:
Un arbol es m-ario si todos sus vertices internos tienen grado a lo sumo $m+1$ (m hijos + el padre).

Se dice exactamente m-ario si todos los nodos internos tienen grado $m+1$ y la raiz grado $m$.

- Un arbol m-ario de altura $h$ tiene a lo sumo $m^h$ hojas.
- Un arbol exactamente m-ario de altura $h$ tiene exactamente $m^h$ hojas.
- Un arbol m-ario con $I$ hojas tiene $h\geq \lceil log_m I \rceil$
- Si $T$ es un arbol exactamente m-ario balanceado no trivial entonces $h=\lceil log_m I \rceil$

## Arboles generadores (AG)
Un arbol generador (AG) de un grafo $G$ es un subgrafo generador (con el mismo conjunto de vertices) de $G$ que es arbol.

#### Teorema: 
- Todo grafo conexo tiene al menos un arbol generador.
- G conexo y G tiene un unico AG $\iff$ G es arbol.
- Sea $T=(V,X_T)$ un AG de $G=(V,X)$ y $e \in X - X_T$. Entonces $T' = T + e - f = (V, X_T \cup \{ e \} - \{ f \})$ es un arbol generador de G. Siendo $f$ una arista del  unico circuito de $T+e$.

## Recorrido de grafos/arboles/digrafos.
Queremos recorrer los vertices exactamente una vez.

~~~python
def recorrer(G):
    """
    pred[i]: padre de v_i
    orden[i]: numero asignado a v_i
    """

    next = 1 # es el primer nodo recorrido
    r = G.root # un vertice elegido arbitrariamente
    pred[r] = 0
    orden[r] = next

    LISTA = {r}

    # mientras la lista no esta vacia
    while len(lista) != 0:

        # agarro un nodo de la lista        
        nodo = lista.get()

        # vemos los hijos de ese nodo
        for child in G.getChildren(nodo):                 
            if child not in LISTA:
                # marcamos el vertice child
                pred[child] = nodo
                next++
                orden[j] = next
                # lo agregamos a la lista de nodos por recorrer
                LISTA.add(child)

        LISTA.remove(nodo)

    return pred, orden
~~~


Tenemos dos opciones: 
- <b>Breadth-First Search</b>: Se visita cada vertice en un nivel antes de pasar al siguiente nivel. Se implementa con una cola.

    Usos:     
    1. Calcular distancias.
    2. 

- <b>Depth-First Search</b>: Se explora por cada rama lo mas profundo posible antes de retroceder. Se implementa con una pila.

    Usos:  
    1. .


### Tipos de arcos en un digrafo:
Si aplicamos DFS para enumerar los vertices de un digrafo, podemos clasificar a los arcos en 4 tipos:
    
- <b>tree edges</b>: arcos que forman el bosque DFS.
- <b>backward edges</b>: van hacia un ancestro.
- <b>forward edges</b>: van hacia un descendiente.
- <b>cross edges</b>: van hacia otro arbol del bosque o al de otra rama (anterior en ambos casos).

Para clasificar a los arcos, usando el mismo recorrido por DFS, utilizamos las estructuras `desde`, `hasta`.

El intervalo `(desde[i], hasta[i])` representa el lapso de tiempo en el que el nodo `i` estuvo en la pila.

Para cualquier par de intervalos `(desde[i], hasta[i]), (desde[j], hasta[j])`:

- o hay una relacion de contencion entre ellos
- o son disjuntos

Entonces vale que:
