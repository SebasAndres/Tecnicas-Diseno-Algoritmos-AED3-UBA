

$$
f_S(i,k) = \begin{cases} 
    seqUnosMasLarga(S) && si && k=0 \\
    \max \{ f_S(i+1,k), f_{S-S[i]}(i,k-1) \} && si && S[i]=0 \\
    f_S(i+1,k) && cc
\end{cases}
$$

Donde $seqUnosMasLarga(S,i)$ es $O(|S|)$, porque recorro todos los elementos una vez con contadores cada vez que encuentro un 1, si encuentro un 0, me fijo si es mayor a la longitud maxima de secuencia de 1 que encontre hasta ese momento.

Hay $N$ indices posibles para $i$ y $k$ opciones posibles, justamente, dado un $k$.

Luego hay $nk$ estados posibles sin contar los posibles $S$. 

Respecto a los posibles $S$, sabemos que solo uno de ellos va a tener $N$ elementos y el resto va a tener $|S|<N$.

Entonces, podemos amortizar que cada llamada a seqUnosMasLarga va a ser ~$O(1)$.

La complejidad del algoritmo es:
- Temporal: $O(nk)$, porque ejecutamos $O(1)$ $nk$ veces (si usamos memoizacion).
- Espacial: $O(nk)$, tenemos una matriz $M$ con N*K elementos que guarda la secuencia mas larga calculada para $S$ a partir del indice $i$.

Algoritmo:
~~~python
def f(S,i,k):    
    if memo[i][k] != -1:
        return memo[i][k]
    
    if k==0:
        res = seqMasLargaUnos(S)
    
    if S[i]==0:
        res = max(f(S,i+1,k), f(S.removeAt(i), i, k-1))
    else:
       res = f(S,i+1,k)

    memo[i][k] = res
    return res
~~~

