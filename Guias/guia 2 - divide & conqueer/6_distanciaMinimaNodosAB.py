# distancia maxima de dos nodos en un arbol: diametro de un arbol

def alturaYDiametro(raiz):
    if raiz == None:
        return 0, 0
    else:
        subarbol_izq = alturaYDiametro(raiz.izq)
        subarbol_der = alturaYDiametro(raiz.der)

        altura_izq = subarbol_izq[0]
        altura_der = subarbol_der[0]
        diametro_izq = subarbol_izq[1]
        diametro_der = subarbol_der[1]

        altura = 1 + max(altura_izq, altura_der)
        diametro = max(altura_izq + altura_der - 1, diametro_izq, diametro_der)
 
        return altura, diametro