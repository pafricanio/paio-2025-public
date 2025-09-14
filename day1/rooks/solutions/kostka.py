import collections


def calculate_moves(A, K):
    N = len(A)
    M = len(A[0])
    total_elements = N * M

    pos = [None] * (total_elements + 1)
    for r in range(N):
        for c in range(M):
            pos[A[r][c]] = (r, c)

    INF = float('inf')
    dist = [INF] * (total_elements + 1)

    dist[1] = 0

    row_deques = [collections.deque() for _ in range(N)]
    col_deques = [collections.deque() for _ in range(M)]

    if total_elements > 0:
        start_r, start_c = pos[1]
        row_deques[start_r].append((0, 1))
        col_deques[start_c].append((0, 1))

    for val in range(2, total_elements + 1):
        r, c = pos[val]

        min_moves = INF

        while row_deques[r] and row_deques[r][0][1] < val - K:
            row_deques[r].popleft()
        if row_deques[r]:
            min_moves = min(min_moves, row_deques[r][0][0] + 1)

        while col_deques[c] and col_deques[c][0][1] < val - K:
            col_deques[c].popleft()
        if col_deques[c]:
            min_moves = min(min_moves, col_deques[c][0][0] + 1)

        dist[val] = min_moves

        while row_deques[r] and row_deques[r][-1][0] >= dist[val]:
            row_deques[r].pop()
        row_deques[r].append((dist[val], val))

        while col_deques[c] and col_deques[c][-1][0] >= dist[val]:
            col_deques[c].pop()
        col_deques[c].append((dist[val], val))

    result_matrix = [[0] * M for _ in range(N)]
    for i in range(1, total_elements + 1):
        r, c = pos[i]
        result_matrix[r][c] = -1 if dist[i] == INF else int(dist[i])

    return result_matrix