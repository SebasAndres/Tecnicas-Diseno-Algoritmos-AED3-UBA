# Divide & Conqueer

### Complejidad:

Tienen la forma
$$T(n) := aT(\frac{n}{c})+bn^d$$

Donde,
- $c$ : proporción del tamaño original con el que llamamos recursivamente.
- $a$ : cantidad de llamados recursivos a partir de una llamada. 
- $b$ :
- $d$ : 

Para la demostración asumimos que $\exists g: \N \rightarrow \N$ tal que $T(n) \in O(g)$. Entonces, usando el caso base $g(1) = b$ y propiedades de series llegamos a que:

$$T(n) := aT(\frac{n}{c})+bn^d \leq g(n) = ag(\frac{n}{c})+bn^d$$

Sup. $n=c^k$, entonces:

$$g(c^k) = a^j g(c^{k-j}) + b\sum_{i=0}^{j-1} a^i c^{(k-i)d} = bc^{dk}\sum_{i=0}^k a^i c^{-di}$$

Dependiendo la relación entre cada una de estas variables se converge a las siguientes complejidades:

1. Si d=0 y a=1, entonces queda $O(\log_cn)$

2. Si d=1 (division+union costo lineal):
    
    2.a. Si a < c, entonces queda $O(n)$

    2.b. Si a = c, entonces queda $O(n log n)$

    2.c. Si a > c, entonces queda $O(n^{log_c a})$