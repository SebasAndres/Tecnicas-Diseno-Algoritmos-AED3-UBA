cajas = []
N = len(cajas)

def solve():
    # solucion bottom-up
    
    # dp[i][j] = maximo numero de cajas que se pueden apilar si la caja i es la base y la caja j es la cima    
    dp = [[0 for j in range(N+1)] for i in range(N+1)]

    for i in range(1,N+1):
        for j in range(1,N+1):
            if cajas[i-1][0] > cajas[j-1][1]:
                # si la caja i soporta a la caja j
                # dp[i][j] = maximo entre no poner la caja j y ponerla
                
                dp[i][j] = max(dp[i-1][j],  # maximo sin poner la caja j
                               dp[i][j-1])  # maximo poniendo la caja j
            else:
                # si la caja i no soporta a la caja j
                dp[i][j] = dp[i-1][j] # maximo sin poner la caja j
                
    return dp[N][N]