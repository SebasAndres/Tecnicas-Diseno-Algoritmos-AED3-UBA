def puedoPonerLaCaja(caja, pila):
    return

def noPuedoPonerNingunaCaja(i, pila):
    return

def esMejor(pila, maxPila):
    return  

# cada indice corresponde a una caja enumerada
# cajas[i] = (peso, soporte)
cajas = [(1,2), (2,4), (3,5), (4,6)]
N = len(cajas)

def backtrack(i,pila):
    if len(pila) == 0 or puedoPonerLaCaja(cajas[i], pila):
        pila.agregar(cajas[i])
        backtrack(i+1,pila)
        pila.sacar(cajas[i])
        return

    if len(pila)==N or noPuedoPonerNingunaCaja(i, pila):
        if esMejor(pila, maxPila):
            maxPila = pila
        return        
