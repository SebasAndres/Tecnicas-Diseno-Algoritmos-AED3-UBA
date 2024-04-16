## Enfoque Bottom Up

La idea es que vale esto...

$maxB(height, tree) = \begin{cases}
tree[height] + \max_{tr \in Forest}(\text{maxB(height-feet, tr)}, maxB(height-1, tree))& si & height-feet>=0 \\
\sum_{h=0}^{height} tree[h] & cc.
\end{cases}$

Entonces la solucion se obtiene con $\max_{t \in Forest} maxB(0, t)$

Podemos calcular de antemano los maxB(h,t) iterativamente para darle un enfoque bottom-up, ya que para el nivel `h` del arbol `t` solo necesitamos el nivel `h-1` del mismo `t` y `h-feetJump` del resto de arboles `tr`.