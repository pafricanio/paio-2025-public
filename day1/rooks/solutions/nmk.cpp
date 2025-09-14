// O(NMK)

#include <vector>
#include <queue>
#include <algorithm>
#include "rooks.h"

const int INF = 1e9;

std::vector<std::vector<int>> calculate_moves(std::vector<std::vector<int>> A, int K) {
    int N = A.size();
    int M = A[0].size();
    int total_elements = N * M;

    std::vector<std::pair<int, int>> pos(total_elements + 1);
    std::vector<int> dist(total_elements + 1, INF);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            pos[A[i][j]] = {i, j};
        }
    }

    std::queue<int> dq;
    dist[1] = 0;
    dq.push(1);

    while (!dq.empty()) {
        int val = dq.front();
        dq.pop();
        int moves = dist[val];

        int r = pos[val].first;
        int c = pos[val].second;

        for (int next_val = val + 1; next_val <= std::min(val + K, total_elements); ++next_val) {
            int next_r = pos[next_val].first;
            int next_c = pos[next_val].second;
            
            if ((r == next_r || c == next_c) && moves + 1 < dist[next_val]) {
                dist[next_val] = moves + 1;
                dq.push(next_val);
            }
        }
    }

    std::vector<std::vector<int>> result_matrix(N, std::vector<int>(M));
    for (int i = 1; i <= total_elements; ++i) {
        result_matrix[pos[i].first][pos[i].second] = dist[i] == INF ? -1 : dist[i];
    }

    return result_matrix;
}