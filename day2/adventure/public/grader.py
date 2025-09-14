import adventure

N, M, Q = map(int, input().split())

U, V, L, R = [], [], [], []
U2, V2, L2, R2 = [], [], [], []

for i in range(M):
    u, v, l, r = map(int, input().split())
    U.append(u)
    V.append(v)
    L.append(l)
    R.append(r)

for i in range(Q):
    u2, v2, l2, r2 = map(int, input().split())
    U2.append(u2)
    V2.append(v2)
    L2.append(l2)
    R2.append(r2)

ans = adventure.add_roads(N, M, Q, U, V, L, R, U2, V2, L2, R2)
for result in ans:
    print(int(result))

ans2 = adventure.assign_times()
for time in ans2:
    print(time)
