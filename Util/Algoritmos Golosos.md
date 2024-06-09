# Algoritmos golosos 

### Heuristicas
Una heuristica es un procedimiento computacional que intenta
obtener soluciones de buena calidad para un problema,
intentando que su comportamiento sea lo m´as preciso posible

### Algoritmos $\epsilon$-aproximados
Sea $\epsilon \geq 0$, decimos que $A$ es un algoritmo e-aproximado si 
$$|\frac{X_A - X_{OPT}}{X_{OPT}}| \leq \epsilon$$

### Algoritmos golosos
La idea es construir una solucion seleccionando en cada paso la mejor alternativa local, sin considerar (o haciendolo debilmente) las implicancias de esta seleccion.

Ejemplos:
-  <b>Problema de la mochila: </b> 

    "Agregar a la mochila el objeto que maximice $beneficio_i/peso_i$"

- <b>Problema del cambio: </b>

    "Seleccionar la moneda de mayor valor que no exceda la cantidad restante por devolver, agregar esta moneda a la lista de la solucion y sustraer su valor a la cantidad restante por devolver"

    Funciona si las denominaciones de las monedas cumplen que $a_1\dots a_k \in \Z_+$, con $a_i > a_{i+1}$, y existen $m_2 \dots m_k \in \Z_{\geq2}$ tales que $a_i=m_{i+1}a_{i+1}$.

    Sea $t$ la cantidad a devolver, entonces en estos casos usamos $\lfloor t/a_i \rfloor$ monedas de tipo $a_i$.

- <b>Tiempo de espera en un sistema: </b>

    "En cada paso atender al cliente con menor tiempo de atencion"
### Demostracion inductiva

La idea es que podemos hacer induccion sobre los pasos del algoritmo goloso.

$B_i$ es la i-esima eleccion y las sucesivas elecciones son $B_1 \dots B_i$

Para el caso base demostramos/explicamos porque la eleccion que tomamos es optima para extender la solucion a futuro (ej. deja mas tiempo disponible para otras actividades futuras).

Para el paso inductivo asumimos que las primeras $B_1 \dots B_i$ elecciones son optimas y armamos una solucion optima $B_1 \dots B_i+ C_{i+1} \dots C_j$ con $C_{i+1} \neq B_{i+1}$ y probamos que la solucion alcanzada tambien puede lograrse eligiendo $B_{i+1}$ en vez de $C_{i+1}.$