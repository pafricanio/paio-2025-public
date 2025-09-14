import towers

t = int(input())

for _ in range(t):
    n, m, k = map(int, input().split())
    result = towers.solve(n, m, k)
    print(result)
