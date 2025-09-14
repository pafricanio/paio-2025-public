import gcd
import sys

N, K, V = map(int, input().split())
A = list(map(int, input().split()))

result = gcd.calculate_sum(N, K, V, A)

print(result)
