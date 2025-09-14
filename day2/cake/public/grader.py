import cake

T = int(input())

for _ in range(T):
    N, M = map(int, input().split())
    result = cake.count_square_cakes(N, M)
    print(result)
