# Grafos

<b>Definicion: </b>Un grafo $G = (V, X)$ es un par de conjuntos, donde V es un conjunto de puntos o nodos o vertices y $X$ es un subconjunto del conjunto de pares no ordenados de elementos distintos de $V$. Los elementos de $X$ se llaman aristas o ejes.

Dos nodos $v,w \in V$ se dicen incidentes si existe un eje $e \in X$ que los conecta. Ese eje se dice incidente a $v$ y $w$.


<b>Notaciones:</b>

$n_G = |V|$

$m_G = |X|$

$N(v)$: es el conjunto de vertices que son adyacentes a v.

$d(v) = |N(n)|$


## Tipos de grafos

- <b>Multigrafo</b>: Es un grafo en el que puede haber varias aristas entre el mismo par de vertices distintos.

- <b>Pseudografo</b>: Es un grafo en el que puede haber varias aristas entre cada par de vertices y tambien haber aristas que unan a un vertice con si mismo (multigrafo + loops).

### Grados en grafos

El grado de un vertice en un grafo $d_G(v)$ o $d(v)$ es la cantidad de aristas incidentes a él en G. 
Llamamos $\Delta(G)$ al maximo grado de los vertices de $G$ y $\delta(G)$ al minimo.

### Teorema
$$\sum_{v \in V} d(v) = 2m$$

### Grafo complementario
Dado un grafo $G=(V,X)$, su grafo complemento $\bar G = (V, \bar X) = G^c$ es el grafo con el mismo conjunto de vertices y con los ejes tales que un par de vertices es adyacente si solo si no son adyacentes en $G$.

### Subgrafo

Dado un grafo $G=(V_G,X_G)$, un subgrafo de G es un grafo $H=(V_H, X_H)$ tal que:

. $V_H \subset V_G$ 

.  $X_H \subset X_G \cap (V_H \times V_H)$

Lo notamos $H \subset G$.

#### Subgrafo propo

Si $H \subset G$ y $H \neq G$, entonces $H$ es subgrafo propio de $G$.

#### Subgrafo inducido

Un subgrafo $H$ de $G$ se dice inducido si todo par de vertices en comun tiene las mismas conexiones. 

$(\forall v,w \in V_H) ((u,v) \in X_G \rightarrow (u,v) \in X_H)$

A los subgrafos inducidos se los nota $G_{[V_H]}$

## Recorrido de grafos

Un <b>recorrido</b> de un grafo es una secuencia alternada de vertices y aristas. En los grafos (no multi ni pseudo), basta con aclarar los vertices.

- $P = v_0e_1v_1e_2\dots v_{k-1}e_kv_k$. Decimos que P es un recorrido entre $v_0$ y $v_k$.

- La longitud de un recorrido $l(P)$ es la cantidad de aristas que tiene.

- La distancia entre dos vertices $d(v,w)$ es la longitud del recorrido mas corto entre ambos.

Un <b>camino</b> es un recorrido que no pasa dos veces por el mismo vertice.

Una <b>seccion</b> es una subsecuencia de un camino.

Un <b>circuito</b> es un recorrido que empieza y termina en el mismo vertice.

Un <b>circuito simple o ciclo</b> es un circuito de 3 o mas vertices que no pasa dos veces por el mismo vertice.

### Propiedades

- Si un recorrido $P$ entre $v$ y $w$ tiene longitud $d(v,w)$ entonces $P$ es un camino.

- $d(u,w) \leq d(u,v) + d(v,w)$

## Clasificacion de grafos

### Conexos
- Un grafo se dice <b>conexo</b> si existe camino entre todo par de vertices.

- Una <b>componente conexa</b> de un grafo G es un subgrafo conexo maximal de G.

- Un grafo conexo se dice biconexo si para desconectarlo no alcanza con suprimir un vertice, es decir, si no tiene vértices de corte.

- Un grafo se dice <b> fuertemente conexo</b> si es dirigido y todos sus vertices tienen camino entre si (hay ida y vuelta por otro camino).

### Bipartitos
- Un grafo es bipartito si existen dos conjuntos disjuntos ($V_1, V_2$) entre los vertices tales que todas las aristas tienen un extremo en distintos subconjuntos.

- Un grafo es bipartito completo si todo vertice en $V_1$ es adyacente a todo vertice en $V_2$.

- Teo: Un grafo es bipartito $\iff$ no tiene ciclos de longitud impar.

