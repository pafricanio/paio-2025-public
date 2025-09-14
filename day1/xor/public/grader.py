import xor

n = int(input())
a = list(map(int, input().split()))

result = xor.find_multiset(n, a)

print(result[0])  # XOR value
print(len(result[1]))  # Size of multiset
if result[1]:
    print(' '.join(map(str, result[1])))
