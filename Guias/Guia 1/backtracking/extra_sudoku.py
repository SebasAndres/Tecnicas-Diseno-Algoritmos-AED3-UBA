def sudoku(T):
	if T.estaCompleto():
		return T
	for n in range(10):
		if T.esValidoInsertar(n):
			T.insertar(n)
			res = sudoku(T)
            # necesitamos validar si la solucion actual lleva a una sol valida antes de revertir la accion
			if res is not None:
				return res
			T.sacar(n)
	return None