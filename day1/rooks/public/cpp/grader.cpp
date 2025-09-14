#include "rooks.h"
#include <cassert>
#include <cstdio>
#include <vector>

int main() {
    int N, M, K;
    assert(scanf("%d %d %d", &N, &M, &K) == 3);
    std::vector<std::vector<int>> A(N, std::vector<int>(M));
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) assert(scanf("%d", &A[i][j]) == 1);
    }
    std::vector<std::vector<int>> moves = calculate_moves(A, K);
    assert(moves.size() == N);
    for (int i=0; i<N; i++) {
        assert(moves[i].size() == M);
        for (int j=0; j<M; j++) printf("%d ", moves[i][j]);
        printf("\n");
    }
    return 0;
}
