import exhibition

N, M = map(int, input().split())

A = list(map(int, input().split()))
B = list(map(int, input().split()))
S = list(map(int, input().split()))

result = exhibition.max_paintings(N, M, A, B, S)
print(result)
