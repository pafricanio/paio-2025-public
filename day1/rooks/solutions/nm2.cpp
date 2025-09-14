// O((NM)^2))

#include <vector>
#include <queue>
#include "rooks.h"

std::vector<std::vector<int>> calculate_moves(std::vector<std::vector<int>> A, int K) {
    int N = A.size();
    int M = A[0].size();

    std::vector<std::vector<int>> dist(N, std::vector<int>(M, -1));

    std::queue<std::pair<int, int>> q;
    int start_r, start_c;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (A[i][j] == 1) {
                start_r = i;
                start_c = j;
                break;
            }
        }
    }

    dist[start_r][start_c] = 0;
    q.push({start_r, start_c});

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();
        int r = current.first;
        int c = current.second;

        for (int r_prime = 0; r_prime < N; ++r_prime) {
            for (int c_prime = 0; c_prime < M; ++c_prime) {
                if ((r == r_prime || c == c_prime) && (r != r_prime || c != c_prime)) {
                    if (A[r_prime][c_prime] - A[r][c] > 0 && A[r_prime][c_prime] - A[r][c] <= K) {
                        if (dist[r_prime][c_prime] == -1) {
                            dist[r_prime][c_prime] = dist[r][c] + 1;
                            q.push({r_prime, c_prime});
                        }
                    }
                }
            }
        }
    }

    return dist;
}