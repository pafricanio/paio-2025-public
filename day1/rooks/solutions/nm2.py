import collections

def calculate_moves(A, K):
    N = len(A)
    M = len(A[0])

    dist = [[-1 for _ in range(M)] for _ in range(N)]
    q = collections.deque()

    start_pos = None
    for r in range(N):
        for c in range(M):
            if A[r][c] == 1:
                start_pos = (r, c)
                break
        if start_pos:
            break

    if not start_pos:
        return dist

    start_r, start_c = start_pos
    dist[start_r][start_c] = 0
    q.append(start_pos)

    while q:
        r, c = q.popleft()

        for r_prime in range(N):
            for c_prime in range(M):
                is_rook_move = (r == r_prime or c == c_prime)
                is_different_square = (r != r_prime or c != c_prime)

                if is_rook_move and is_different_square:
                    value_diff = A[r_prime][c_prime] - A[r][c]
                    if 0 < value_diff <= K:
                        if dist[r_prime][c_prime] == -1:
                            dist[r_prime][c_prime] = dist[r][c] + 1
                            q.append((r_prime, c_prime))

    return dist