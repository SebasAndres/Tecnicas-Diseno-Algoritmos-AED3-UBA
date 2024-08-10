# Una heuristica es ir hasta la estacion mas lejana antes de terminar la capapacidad del tanque
def g(L,C):
	tanque = C
	n_estaciones = 0
	estaciones = []
	i = 0	
	N = len(L)
	while i<N:
		if tanque > L[i]:
			estaciones.append(i)
			n_estaciones += 1 
		tanque -= L[i]
		i+=1
	return estaciones

