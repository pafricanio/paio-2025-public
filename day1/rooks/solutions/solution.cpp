// O(NM)

#include <vector>
#include <deque>
#include <algorithm>
#include "rooks.h"

const int INF = 1e9;

struct DistValue {
    int dist;
    int val;
};

std::vector<std::vector<int>> calculate_moves(std::vector<std::vector<int>> A, int K) {
    int N = A.size();
    int M = A[0].size();
    int total_elements = N * M;

    std::vector<std::pair<int, int>> pos(total_elements + 1);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            pos[A[i][j]] = {i, j};
        }
    }

    std::vector<int> dist(total_elements + 1, INF);
    dist[1] = 0;

    std::vector<std::deque<DistValue>> row_deques(N);
    std::vector<std::deque<DistValue>> col_deques(M);

    row_deques[pos[1].first].push_back({0, 1});
    col_deques[pos[1].second].push_back({0, 1});

    for (int val = 2; val <= total_elements; ++val) {
        int r = pos[val].first;
        int c = pos[val].second;

        int min_moves = INF;

        while (!row_deques[r].empty() && row_deques[r].front().val < val - K) {
            row_deques[r].pop_front();
        }
        if (!row_deques[r].empty()) {
            min_moves = std::min(min_moves, row_deques[r].front().dist + 1);
        }

        while (!col_deques[c].empty() && col_deques[c].front().val < val - K) {
            col_deques[c].pop_front();
        }
        if (!col_deques[c].empty()) {
            min_moves = std::min(min_moves, col_deques[c].front().dist + 1);
        }

        dist[val] = min_moves;

        while (!row_deques[r].empty() && row_deques[r].back().dist >= dist[val]) {
            row_deques[r].pop_back();
        }
        row_deques[r].push_back({dist[val], val});

        while (!col_deques[c].empty() && col_deques[c].back().dist >= dist[val]) {
            col_deques[c].pop_back();
        }
        col_deques[c].push_back({dist[val], val});
    }

    std::vector<std::vector<int>> result_matrix(N, std::vector<int>(M));
    for (int i = 1; i <= total_elements; ++i) {
        result_matrix[pos[i].first][pos[i].second] = dist[i] == INF ? -1 : dist[i];
    }

    return result_matrix;
}