# Suma Dados

### [a] Caso dados distinguibles:
$$f(n,s) = \begin{cases}
    1 & si & n==1 \\
    \sum_{i=1}^k f(n-1, s-i)   & cc.
\end{cases}$$

### [b] Caso dados indistinguibles:
$$g(n,s,k) = \begin{cases}
    1 & si & n==1 \\
    \sum_{i=1}^k g(n-1, s-i, i)   & cc.
\end{cases}$$

Ahora $g(n-1,s-i,i)$ considera todas las maneras de obtener $s-1$ con $n-1$ dados con $i$ siendo el valor maximo que cada uno de esos datos puede obtener.

