# Cache OPT

Dados cache C de tamaño K y requests R de tamaño N, minimizar la cantidad de cache misses eligiendo las memorias r que van en la caché.

Observaciones:

$CacheMisses(C,R,i) = \sum_{j=i}^N \text{if } r_i \notin C \text{ then 1 else 0 endif}$


### [a] Armar funcion recursiva $f(i,mem)$

- Definir una función recursiva f(i, mem) que tome un índice y un estado de la memoria y devuelva la mínima cantidad de caché misses que deben ocurrir para procesar todas las consultas {ri, ri+1, . . . , rn} si el estado actual de la memoria es mem

$$f(i,mem) := \begin{cases}
    0 & si & i > N \\
    f(i+1,mem)& si & r_i \in mem \\
    1+f(i+1,mem+\{r_i\})& si & |mem|<k \\
    1+f(i+1,mem-\{e\}+\{r_i\})& si & |mem|=k \text{,  e elegido segun furthest-in-future}

\end{cases}$$

- Con esta formulacion el problema se resuelve pidiendo $f(1,\{\})$.