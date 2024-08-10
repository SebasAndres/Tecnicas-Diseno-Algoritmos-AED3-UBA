from numpy import log2

def potenciaSum(A,n):
    if n == 1:
        return A
    k = log2(n)
    mitad = potenciaSum(A,n//2)
    return mitad + A^(2**(k-1)) @ mitad
