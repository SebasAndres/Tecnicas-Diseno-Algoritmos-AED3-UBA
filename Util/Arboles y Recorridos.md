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
    1. Encontrar componentes (fuertemente) conexas.
    2. Ver si un grafo es conexo.
    3. Encontrar ditancia de aristas uno a todos.
    4. Ver si un (di)grafo tiene ciclos.
    5. Etc


- <b>Depth-First Search</b>: Se explora por cada rama lo mas profundo posible antes de retroceder. Se implementa con una pila.

    Usos:  
    1. Encontrar componentes (fuertemente) conexas.
    2. Ver si un grafo es conexo.
    3. Ver si un (di)grafo tiene ciclos.
    4. Encontrar puentes y puntos de articulacion.
    5. Etc

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

Entonces vale que, para un arco $i \rightarrow j$:
- Es tree edge si: $i = pred[j]$
- Es backward edge: si $(desde_j, hasta_j)$ contiene a $(desde_i, hasta_i)$
- Es forward edge: si $(desde_i, hasta_i)$ contiene a $(desde_j,hasta_j)$ y $i\neq pred_j$
- Es cross edge: si $hasta_j < desde_i$

## Generación del Árbol Generador (AG) mediante DFS

Para generar un árbol generador (AG) de un grafo $G$ utilizando el recorrido en profundidad (DFS, por sus siglas en inglés Depth-First Search), inicias seleccionando un vértice como raíz (en este caso $r$) y a partir de ahí, exploras tan profundo como sea posible a lo largo de cada rama antes de retroceder. Este proceso se repite para todos los vértices no visitados hasta que se haya visitado cada vértice del grafo $G$, asegurando que el algoritmo atraviese todo el grafo.

Durante el recorrido DFS, cada vez que visitas un nuevo vértice, creas una arista en el AG desde el vértice actual hasta el nuevo vértice visitado. Este conjunto de aristas formará tu árbol generador $T$ de $G$. Es importante notar que en un AG, por definición, no hay ciclos, y cada vértice (excepto la raíz) tiene exactamente un vértice padre.

Propiedades de un Árbol DFS Profundización antes de expansión: 

1. El DFS explora tan lejos como sea posible a lo largo de cada rama antes de retroceder. Esto significa que el árbol DFS puede alcanzar nodos "profundos" rápidamente, lo cual es útil para tareas como encontrar componentes conexas en un grafo.

2. Ciclos y Back Edges: El DFS puede identificar back edges, que son aristas que apuntan a un ancestro en el árbol DFS. Estas aristas son cruciales para identificar ciclos dentro del grafo, lo que es relevante para tu primer ejercicio, ya que una arista que forma parte de un ciclo no puede ser un puente.

3. Utilización de la pila: El DFS utiliza una pila (explícitamente o mediante la recursión) para gestionar el proceso de búsqueda, lo que impacta en el orden en el que se visitan y se descubren los nodos.


#### Aristas en $E(G) - E(T)$:

Si una arista (vw) está en (E(G)) pero no en (E(T)), significa que esta arista no fue utilizada para formar el árbol DFS. Esto puede suceder por dos razones principales en un grafo conexo:

1. Durante el recorrido DFS, uno de los vértices (v) o (w) fue visitado antes que el otro. Esto implica que, en el momento de considerar la arista (vw), uno de los vértices ya era parte del árbol DFS y, por ende, el otro vértice se conectó al árbol a través de otra arista. En este escenario, el vértice visitado primero es ancestro del visitado después en el árbol DFS, ya que el proceso de DFS asegura un camino continuo desde el vértice raíz del árbol DFS hasta cada vértice que se va añadiendo.

2. La conexión (vw) podría haber creado un ciclo si se hubiera incluido en (T). Dado que un árbol no puede tener ciclos por definición, y el árbol DFS se construye asegurando esto, cualquier arista que pudiera generar un ciclo se excluye de (E(T)). Sin embargo, al ser (G) un grafo conexo y (T) un árbol que abarca todos los vértices de (G), la exclusión de (vw) de (E(T)) implica necesariamente que existe otro camino en (T) que conecta (v) y (w), confirmando que uno de estos vértices es ancestro del otro en el árbol DFS.

## Generación del Árbol Generador (AG) mediante BFS

La generacion del AG tiene la misma idea que en un DFS pero el  recorrido en este caso es con BFS.

Propiedades de un Árbol BFS Expansión nivel por nivel: 

1. El BFS explora todos los vecinos de un nodo antes de moverse a los nodos en el siguiente nivel. Esto asegura que si existe un camino entre dos nodos, el BFS encontrará el camino más corto en términos de aristas atravesadas.

2. Capas y distancia mínima: Cada nodo descubierto en un árbol BFS está lo más cerca posible del nodo raíz en términos de la cantidad de aristas. Esto es especialmente útil para calcular distancias mínimas y para algoritmos de ruta más corta en grafos sin ponderar.

3. Utilización de la cola: El BFS utiliza una cola para gestionar el orden de visita de los nodos, asegurando que se explore cada nivel completamente antes de pasar al siguiente.

## Tips ejs grafos:

#### Teorema de Robbins:
Este teorema establece que un grafo no dirigido tiene una orientación fuertemente conexa si y solo si es biconexo. Un grafo es biconexo si no contiene vértices de corte, es decir, su eliminación (junto con las aristas incidentes) no aumenta el número de componentes conexas del grafo.

### Algoritmo para encontrar una orientación fuertemente conexa:
Paso 1: Verificar si el grafo (G) es biconexo, es decir, si hay puntos de corte. 
Paso 2: Si el grafo (G) es biconexo, entonces procede a orientar sus aristas para hacerlo fuertemente conexo. Si no es biconexo, entonces no es posible encontrar tal orientación. Una forma de orientar las aristas de un grafo biconexo es realizar un recorrido DFS y orientar todas las aristas en la dirección del recorrido. Esto garantiza que haya al menos un camino dirigido entre cualquier par de vértices.
Si G no es biconexo no hay un D(T) fuertemente conexo.