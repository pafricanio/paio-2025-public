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

int get_min_from_deque(std::deque<DistValue>& dq, int val, int k) {
    while (!dq.empty() && dq.front().val < val - k) {
        dq.pop_front();
    }
    return dq.empty() ? INF : dq.front().dist;
}

void update_deque(std::deque<DistValue>& dq, int val, int dist_val) {
    while (!dq.empty() && dq.back().dist >= dist_val) {
        dq.pop_back();
    }
    dq.push_back({dist_val, val});
}

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

    update_deque(row_deques[pos[1].first], 1, dist[1]);
    update_deque(col_deques[pos[1].second], 1, dist[1]);

    for (int val = 2; val <= total_elements; ++val) {
        int r = pos[val].first;
        int c = pos[val].second;

        int min_moves = INF;

        min_moves = std::min(min_moves, get_min_from_deque(row_deques[r], val, K) + 1);
        min_moves = std::min(min_moves, get_min_from_deque(col_deques[c], val, K) + 1);

        dist[val] = min_moves;

        if (dist[val] != INF) {
            update_deque(row_deques[r], val, dist[val]);
            update_deque(col_deques[c], val, dist[val]);
        }
    }

    std::vector<std::vector<int>> result_matrix(N, std::vector<int>(M));
    for (int i = 1; i <= total_elements; ++i) {
        result_matrix[pos[i].first][pos[i].second] = dist[i] == INF ? -1 : dist[i];
    }

    return result_matrix;
}