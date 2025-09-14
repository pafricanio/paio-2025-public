// O(NM log(NM))

#include <vector>
#include <set>
#include <algorithm>
#include "rooks.h"

const int INF = 1e9;

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

    std::vector<std::set<std::pair<int, int>>> row_sets(N);
    std::vector<std::set<std::pair<int, int>>> col_sets(M);

    row_sets[pos[1].first].insert({0, 1});
    col_sets[pos[1].second].insert({0, 1});

    for (int val = 2; val <= total_elements; ++val) {
        int r = pos[val].first;
        int c = pos[val].second;

        int min_moves = INF;

        while (!row_sets[r].empty() && row_sets[r].begin()->second < val - K) {
            row_sets[r].erase(row_sets[r].begin());
        }
        if (!row_sets[r].empty()) {
            min_moves = std::min(min_moves, row_sets[r].begin()->first + 1);
        }

        while (!col_sets[c].empty() && col_sets[c].begin()->second < val - K) {
            col_sets[c].erase(col_sets[c].begin());
        }
        if (!col_sets[c].empty()) {
            min_moves = std::min(min_moves, col_sets[c].begin()->first + 1);
        }

        dist[val] = min_moves;

        if (dist[val] != INF) {
            row_sets[r].insert({dist[val], val});
            col_sets[c].insert({dist[val], val});
        }
    }

    std::vector<std::vector<int>> result_matrix(N, std::vector<int>(M));
    for (int i = 1; i <= total_elements; ++i) {
        result_matrix[pos[i].first][pos[i].second] = dist[i] == INF ? -1 : dist[i];
    }

    return result_matrix;
}