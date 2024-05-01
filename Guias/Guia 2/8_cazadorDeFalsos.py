# A in R^(n x n)

def conjuncionSubmatriz(A, i0, i1, j0, j1):
    # Asumimos que existe
    # Cuesta O(1)
    # Da True sii hay algun elemento Falso en la submatriz
    return

def algunFalso(A, i0, i1, j0, j1):
    # El problema dice que asumamos que hay un falso

    # Caso base
    if i0 == i1 and j0 == j1:
        return (i0, j0)

    # Caso recursivo    
    indice_mitad = (i0 + i1) // 2 # = (j0 + j1) // 2   
    if conjuncionSubmatriz(A, i0, indice_mitad, j0, indice_mitad):
        res = algunFalso(A, i0, indice_mitad, j0, indice_mitad)
    elif conjuncionSubmatriz(A, i0, indice_mitad, indice_mitad + 1, j1):
        res = algunFalso(A, i0, indice_mitad, indice_mitad + 1, j1)
    elif conjuncionSubmatriz(A, indice_mitad + 1, i1, j0, indice_mitad):
        res = algunFalso(A, indice_mitad + 1, i1, j0, indice_mitad)
    else:
        res = algunFalso(A, indice_mitad + 1, i1, indice_mitad + 1, j1)

    return res

def contarFalsos(A, i0, i1, j0, j1):
    # Caso base
    if i0 == i1 and j0 == j1:
        return 1 
          
    cont = 0 # Acumula la cantidad de Falsos en los 4 subcuadrantes
    indice_mitad = (i0 + i1) // 2 
    if conjuncionSubmatriz(A, i0, indice_mitad, j0, indice_mitad):
        cont += contarFalsos(A, i0, indice_mitad, j0, indice_mitad)
    if conjuncionSubmatriz(A, i0, indice_mitad, indice_mitad + 1, j1):
        cont += contarFalsos(A, i0, indice_mitad, indice_mitad + 1, j1)
    if conjuncionSubmatriz(A, indice_mitad + 1, i1, j0, indice_mitad):
        cont += contarFalsos(A, indice_mitad + 1, i1, j0, indice_mitad)
    if conjuncionSubmatriz(A, indice_mitad + 1, i1, indice_mitad + 1, j1):
        cont += contarFalsos(A, indice_mitad + 1, i1, indice_mitad + 1, j1)
    
    return cont



