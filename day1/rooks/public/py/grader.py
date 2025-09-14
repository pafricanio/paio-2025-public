import rooks
import sys

def main():

    line_nmk = sys.stdin.readline().split()
    assert len(line_nmk) == 3
    N, M, K = map(int, line_nmk)
    
    A = []
    for i in range(N):
        row = list(map(int, sys.stdin.readline().split()))
        assert len(row) == M
        A.append(row)

    moves = rooks.calculate_moves(A, K)

    assert isinstance(moves, list)
    assert len(moves) == N
    
    
    for i in range(N):
        assert isinstance(moves[i], list)
        assert len(moves[i]) == M
        print(*moves[i])

if __name__ == "__main__":
    main()
