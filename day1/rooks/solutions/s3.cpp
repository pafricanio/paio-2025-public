// Works only for K = N*M

#include <vector>
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

    dist[1] = 0;
    std::vector<int> min_row_dist(N, INF);
    std::vector<int> min_col_dist(M, INF);

    int start_r = pos[1].first;
    int start_c = pos[1].second;
    min_row_dist[start_r] = 0;
    min_col_dist[start_c] = 0;

    for (int val = 2; val <= total_elements; ++val) {
        int r = pos[val].first;
        int c = pos[val].second;
        
        int current_min_moves = 1 + std::min(min_row_dist[r], min_col_dist[c]);
        dist[val] = current_min_moves;

        min_row_dist[r] = std::min(min_row_dist[r], dist[val]);
        min_col_dist[c] = std::min(min_col_dist[c], dist[val]);
    }

    std::vector<std::vector<int>> result_matrix(N, std::vector<int>(M));
    for (int i = 1; i <= total_elements; ++i) {
        result_matrix[pos[i].first][pos[i].second] = dist[i] >= INF ? -1 : dist[i];
    }
    
    return result_matrix;
}