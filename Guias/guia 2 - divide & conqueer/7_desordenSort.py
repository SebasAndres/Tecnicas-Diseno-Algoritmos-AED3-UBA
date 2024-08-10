def desordenSort(A):
    parejasDesordenadas = 0

    if len(A) == 1:
        return A    
    
    mitad1 = A[:len(A)//2]
    mitad2 = A[len(A)//2:]
    
    sorted1 = desordenSort(mitad1)
    sorted2 = desordenSort(mitad2)

    while (sorted1 != [] and sorted2 != []):
        if sorted1[0] > sorted2[0]:
            parejasDesordenadas += len(sorted1)
            sorted2.pop(0)
        else:
            sorted1.pop(0)
