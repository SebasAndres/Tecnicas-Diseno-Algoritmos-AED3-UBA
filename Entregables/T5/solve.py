# Usuario vJudge: sebasAndres

res = []

def solve(A):
    n = len(A)
    cont = 0
    work = 0
    for i in range(n):
        cont += A[i]
        work += abs(cont)    
    return work

while True:
    n = int(input())
    if n==0:
        break

    A = list(map(int, input().split()))
    r = solve(A)
    res.append(r)

for r in res:
    print(r)